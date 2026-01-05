#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// 1 represents red
	// choose direction
	while(true){
		if(start->data>newnodePtr->data){
			if(start->left==nullptr){
				start->left=newnodePtr;
				newnodePtr->parent=start;
				newnodePtr->color= 1 ;
				newnodePtr->left=nullptr;
				newnodePtr->right=nullptr;
				break;
			}
			start=start->left;
		}	
		else{
			if(start->right==nullptr){
				start->right=newnodePtr;
				newnodePtr->parent=start;
				newnodePtr->color= 1 ;
				newnodePtr->left=nullptr;
				newnodePtr->right=nullptr;
				break;
			}
			start=start->right;
		}
	}
	// recurse down the tree

	fixup(newnodePtr);

	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	ptr lloc=loc->left;
	if (lloc==nullptr) return;
	ptr ploc=loc->parent;
	ptr rlloc=lloc->right;
	if (ploc==nullptr){
		lloc->parent=nullptr;
		root = lloc;
		lloc->right=loc;
		if (rlloc != nullptr){
			rlloc->parent = loc;
		}
		loc->parent=lloc;
		loc->left=rlloc;
	}
	else if (ploc->left==loc){
		ploc->left=lloc;
		lloc->right=loc;
		lloc->parent=ploc;
		if (rlloc != nullptr){
			rlloc->parent = loc;
		}
		loc->parent=lloc;
		loc->left=rlloc;
	}
	else if(ploc->right==loc){
		ploc->right=lloc;
		lloc->right=loc;
		lloc->parent=ploc;
		if (rlloc != nullptr){
			rlloc->parent = loc;
		}
		loc->parent=lloc;
		loc->left=rlloc;
	}
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	ptr rloc=loc->right;
	if (rloc==nullptr) return;
	ptr ploc=loc->parent;
	ptr lrloc=rloc->left;
	if (ploc==nullptr){
		rloc->parent=nullptr;
		root = rloc;
		rloc->left=loc;
		if (lrloc != nullptr){
			lrloc->parent = loc;
		}
		loc->parent=rloc;
		loc->right=lrloc;
	}
	else if (ploc->left==loc){
		ploc->left=rloc;
		rloc->left=loc;
		rloc->parent=ploc;
		if (lrloc != nullptr){
			lrloc->parent = loc;
		}
		loc->parent=rloc;
		loc->right=lrloc;
	}
	else if(ploc->right==loc){
		ploc->right=rloc;
		rloc->left=loc;
		rloc->parent=ploc;
		if (lrloc != nullptr){
			lrloc->parent = loc;
		}
		loc->parent=rloc;
		loc->right=lrloc;
	}
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{
	ptr ploc=loc->parent;
	if(ploc==nullptr) {
		loc->color=0;
		return ;
	}
	// if ploc I mean parent of loc is root then it will be of black color any way that's why i coded like this with out checking pploc == root

	if (ploc->color==0){
		return;
	}
	ptr pploc=ploc->parent;
	if (pploc==nullptr){
		ploc->color=0;
		return;
	}
	ptr sploc;
	if (pploc->left==ploc){
		sploc=pploc->right;
	}
	else if(pploc->right==ploc){
		sploc=pploc->left;
	}
	if (sploc!=nullptr && sploc->color==1){
		pploc->color=1;
		sploc->color=0;
		ploc->color=0;
		RedBlackTree::fixup(pploc);
		return;
	}
		if(pploc->right==ploc&&ploc->left==loc){
			rightrotate(ploc);
			RedBlackTree::fixup(ploc);
			return;
		}
		else if(pploc->left==ploc&&ploc->right==loc){
			leftrotate(ploc);
			RedBlackTree::fixup(ploc);
			return;
		}
	if(pploc->left==ploc){
		rightrotate(pploc);
	}
	else{
		leftrotate(pploc);
	}
	int temp=pploc->color;
	pploc->color=ploc->color;
	ploc->color=temp;
	return;
}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}


