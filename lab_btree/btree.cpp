/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
    size_t first_larger_idx = insertion_idx(subroot->elements, key);
    if(first_larger_idx==subroot->elements.size()){
         if((*subroot).is_leaf==true){
         return V();
        }
         return find(subroot->children[first_larger_idx],key);
    }

    if(subroot->elements[first_larger_idx].key==key){
        return subroot->elements[first_larger_idx].value;
    }
    if((*subroot).is_leaf==true){
         return V();
    }

    return find(subroot->children[first_larger_idx],key);
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if(root == nullptr) {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if(root->elements.size() >= order) {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too 
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{

    BTreeNode* child = parent->children[child_idx];
    
    BTreeNode* new_left = child; 
    BTreeNode* new_right = new BTreeNode(child->is_leaf, order);

    size_t mid_elem_idx = (child->elements.size() - 1) / 2;
  
    /* Iterator for where we want to insert the new child. */
    auto child_itr = parent->children.begin() + child_idx + 1;
    /* Iterator for where we want to insert the new element. */
    auto elem_itr = parent->elements.begin() + child_idx;
    /* Iterator for the middle element. */
    auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
   
    parent->elements.insert(elem_itr,child->elements[mid_elem_idx]);

    vector<DataPair> splitright;
    for(size_t i=mid_elem_idx+1;i!=child->elements.size();i++){
        DataPair out=child->elements[i];
        splitright.push_back(out);
    }

    child->elements.erase(mid_elem_itr,child->elements.end());
    
    
    new_right->elements=splitright;
    parent->children.insert(child_itr,new_right);
    
    
    if(child->is_leaf){
        return;
    }

    else{
        std::vector<BTreeNode*> grandchild=child->children;
        vector<BTreeNode *> childright;
         vector<BTreeNode *> childleft;
        for(size_t i=0;i<mid_elem_idx+1;i++){
          childleft.push_back(grandchild[i]);
        }

         for(size_t i=mid_elem_idx+1;i<grandchild.size();i++){
          childright.push_back(grandchild[i]);
        }       
        grandchild.erase(grandchild.begin(),grandchild.end());
        new_right->children=childright;
        new_left->children=childleft;
    }


}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    /* There are two cases to consider. 
     * If the subroot is a leaf node and the key doesn't exist subroot, we 
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order. 
     */

    size_t first_larger_idx = insertion_idx(subroot->elements, pair);
    if(subroot->is_leaf==true){
        if(first_larger_idx==subroot->elements.size()){
             subroot->elements.push_back(pair);
        }
        else{
            if(subroot->elements[first_larger_idx]==pair){
                return;
            }
            else{
                subroot->elements.insert(subroot->elements.begin()+first_larger_idx,pair);
            }
        }
    }
    else{
        BTreeNode* child=subroot->children[first_larger_idx];
        insert(child,pair);
        if(child->elements.size() >= order){
            split_child(subroot,first_larger_idx);
        }
    }
  
}

