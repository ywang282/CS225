/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree( vector<Frequency> frequencies ) {
	std::stable_sort( frequencies.begin(), frequencies.end() );
	buildTree( frequencies );
	vector<bool> path;
	buildMap( root, path );
}

HuffmanTree::HuffmanTree( const HuffmanTree & other ) {
	copy( other );
}

HuffmanTree::HuffmanTree( BinaryFileReader & bfile ) {
	root = readTree( bfile );
	vector<bool> path;
	buildMap( root, path );
}

HuffmanTree::~HuffmanTree() {
	clear( root );
}

const HuffmanTree & HuffmanTree::operator=( const HuffmanTree & rhs ) {
	if( this != &rhs ) {
		clear( root );
		copy( rhs );
	}
	return *this;
}

void HuffmanTree::clear( TreeNode * current ) {
	if( current == NULL )
		return;
	clear( current->left );
	clear( current->right );
	delete current;
}

void HuffmanTree::copy( const HuffmanTree & rhs ) {
	root = copy( rhs.root );
}

HuffmanTree::TreeNode * HuffmanTree::copy( const TreeNode * current ) {
	if( current == NULL )
		return NULL;
	TreeNode * node = new TreeNode( current->freq );
	node->left = copy( current->left );
	node->right = copy( current->right );
	return node;
}


HuffmanTree::TreeNode * HuffmanTree::removeSmallest( 
		queue<TreeNode *> & singleQueue, queue<TreeNode *> & mergeQueue ) {
	TreeNode * smallest = NULL;
	
	if(!singleQueue.empty()&&!mergeQueue.empty()){
		if(singleQueue.front()->freq.getFrequency()<=
					mergeQueue.front()->freq.getFrequency()){
			smallest=singleQueue.front();
			singleQueue.pop();
		}
		else{
			smallest=mergeQueue.front();
			mergeQueue.pop();
		}
	}
	else if(!singleQueue.empty()){
		smallest=singleQueue.front();
		singleQueue.pop();
	}
	else if(!mergeQueue.empty()){
		smallest=mergeQueue.front();
		mergeQueue.pop();
	}
	return smallest;
}

void HuffmanTree::buildTree( const vector<Frequency> & frequencies ) {
	queue<TreeNode *> singleQueue; // Queue containing the leaf nodes
	queue<TreeNode *> mergeQueue;  // Queue containing the inner nodes
	
	for(int i=0;i<frequencies.size();i++){
		TreeNode * treenode=new TreeNode(frequencies[i]);
		singleQueue.push(treenode);
	}
	
	
	while(singleQueue.size()+mergeQueue.size()>1){
		TreeNode* left=removeSmallest(singleQueue,mergeQueue);
		TreeNode* right=removeSmallest(singleQueue,mergeQueue);
		TreeNode* internal=new TreeNode(left->freq.getFrequency()
					+right->freq.getFrequency());
		internal->left=left;
		internal->right=right;
		mergeQueue.push(internal);
	}
	
	root=removeSmallest(singleQueue,mergeQueue);
}

string HuffmanTree::decodeFile( BinaryFileReader & bfile ) {
	stringstream ss;
    decode( ss, bfile );
	return ss.str();
}

void HuffmanTree::decode( stringstream & ss, BinaryFileReader & bfile ) {
	TreeNode * current = root;
	while( bfile.hasBits() ) {
		if(current->left!=NULL&&current->right!=NULL){
			bool nextbit=bfile.getNextBit();
			if(nextbit==0){
				current=current->left;
			}
			else{
				current=current->right;
			}
		}
		else{
			char output=current->freq.getCharacter();
			ss<<output;
                        current=root;
		}
	}
	
	char output=current->freq.getCharacter();
	ss<<output;
	
}

void HuffmanTree::writeTree( BinaryFileWriter & bfile ) {
	writeTree( root, bfile );
}

void HuffmanTree::writeTree( TreeNode * current, BinaryFileWriter & bfile ) {
	if(current->left==NULL&&current->right==NULL){
		bfile.writeBit(1);
		bfile.writeByte(current->freq.getCharacter());
		return;
	}
	bfile.writeBit(0);
	writeTree(current->left,bfile);
	writeTree(current->right,bfile);
}

HuffmanTree::TreeNode * HuffmanTree::readTree( BinaryFileReader & bfile ) {
	if(bfile.hasBits()){
		if(bfile.getNextBit()==1){
			TreeNode* leaf =new TreeNode(Frequency(bfile.getNextByte(),0));
			return leaf;
		}
		else{
			TreeNode* internal=new TreeNode(0);
			internal->left=readTree(bfile);
			internal->right=readTree(bfile);
			return internal;
		}
	}
	else{
		return NULL;
	}
}

void HuffmanTree::buildMap( TreeNode * current, vector<bool> & path ) {
	// Base case: leaf node.
	if( current->left == NULL && current->right == NULL ) {
		bitsMap[current->freq.getCharacter()] = path;
		return;
	}

	// Move left
	path.push_back( false );
	buildMap( current->left, path );
	path.pop_back();

	// Move right
	path.push_back( true );
	buildMap( current->right, path );
	path.pop_back();
}

void HuffmanTree::printInOrder() const {
	printInOrder( root );
	cout << endl;
}

void HuffmanTree::printInOrder( const TreeNode * current ) const {
	if( current == NULL )
		return;
	printInOrder( current->left );
	cout << current->freq.getCharacter() << ":" <<
		current->freq.getFrequency() << " ";
	printInOrder( current->right );
}

void HuffmanTree::writeToFile( const string & data, BinaryFileWriter & bfile ) {
	for( auto it = data.begin(); it != data.end(); ++it )
		writeToFile( *it, bfile );
}

void HuffmanTree::writeToFile( char c, BinaryFileWriter & bfile ) {
	vector<bool> bits = getBitsForChar( c );
	for( auto it = bits.begin(); it != bits.end(); ++it )
		bfile.writeBit( *it );
}

vector<bool> HuffmanTree::getBitsForChar( char c ) {
	return bitsMap[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor:
    public GenericNodeDescriptor< HuffmanTreeNodeDescriptor<TreeNode> >
{
	public:

	HuffmanTreeNodeDescriptor(const TreeNode* root): subRoot(root) { /* nothing */ }

	string key() const
	{
		std::stringstream ss;
        char ch = subRoot->freq.getCharacter();
		int freq = subRoot->freq.getFrequency();

        // print the sum of the two child frequencies
        if(ch == '\0')
		    ss << freq;
        // print the leaf containing a character and its count
        else
        {
            if(ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
		return ss.str();
	}

	bool isNull() const { return subRoot == NULL; }
	HuffmanTreeNodeDescriptor left() const { return HuffmanTreeNodeDescriptor(subRoot->left); }
	HuffmanTreeNodeDescriptor right() const { return HuffmanTreeNodeDescriptor(subRoot->right); }

	private:

    const TreeNode* subRoot;
};

int HuffmanTree::height(const TreeNode* subRoot) const
{
    if(subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream & out) const
{
    int h = height(root);
    if(h > _max_print_height)
    {
        out << "Tree is too big to print. Try with a small file (e.g. data/small.txt)" << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root), out);
}
