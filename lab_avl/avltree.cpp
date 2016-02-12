/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* temp=t->right;
    t->right=temp->left;
    temp->left=t;
    t=temp;
    
 	temp=t->left;
    temp->height=max(height(temp->left),height(temp->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* temp=t->left;
    t->left=temp->right;
    temp->right=t;
    t=temp;
    
    temp=t->right;
    temp->height=max(height(temp->left),height(temp->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subtree, const K & key, const V & value)
{
    if(subtree==NULL){
    	subtree=new Node(key,value);
    }
    else if(key<subtree->key){
    	insert(subtree->left,key,value);
    	if(height(subtree->left)!=0){
	    	int balance=height(subtree->right)-height(subtree->left);
	    	int leftBalance=height(subtree->left->right)-height(subtree->left->left);
	    	if(balance==-2){
	    		if(leftBalance==1){
	    			rotateLeftRight(subtree);
	    		}
	    		else{
	    			rotateRight(subtree);
	    		}
	    	}
	    }
    }
    else{
    	insert(subtree->right,key,value);
    	if(height(subtree->right)!=0){
	    	int balance=height(subtree->right)-height(subtree->left);
	    	int rightBalance=height(subtree->right->right)-height(subtree->right->left);
	    	if(balance==2){
	    		if(rightBalance==-1){
	    			rotateRightLeft(subtree);
	    		}
	    		else{
	    			rotateLeft(subtree);
	    		}
	    	}
	    }
    }
    subtree->height=max(height(subtree->left),height(subtree->right))+1;
}


template <class K, class V>
int AVLTree<K, V>::height(Node* & subtree){
	if(subtree==NULL) {
		return -1;
	}
	else{
		return subtree->height;
	}
}

