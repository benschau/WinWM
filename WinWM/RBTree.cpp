#include "RBTree.h"

using namespace RBTree;

template <typename t>
RedBlackTree::RedBlackTree() {
	head = nullptr;
}

template <typename t>
BOOL WINAPI RedBlackTree::insert(type t) {
	// all newly inserted nodes are red by default
	Node *node = new Node(t, false, nullptr, nullptr, nullptr);

	if (!root) { 
		// the parent node is always black.
		root = node;
		root->isBlack = true;

		return true;
	} 

	// standard BST insertion, iterative
	Node **pos;
	for (pos = &root; *pos != nullptr) {
		node->parent = *pos;
		if (t < (*pos)->val) {
			pos = &(*pos)->left;
		} else if (t > (*pos)->val) {
			pos = &(*pos)->right;
		} else {
			return false;
		}
	}
	*pos = node;

	// balance the tree by fixing the issues in it
	this->fixViolation(root, node);

	return true;
}

/**
 * Rotate part of a tree to the left.
 *	 If my tree initially looks like this:
 *		5
 *	   / \
 *	  7	  8
 */
void RedBlackTree::rotateLeft(Node *root, Node *node) {
	Node *node_right = node->right;
	
	node->right = node_right->left;
	if (!node->right)
		node->right->parent = node;

	node_right->parent = node->parent;
	
	if (node->parent)
		root = node_right;
	else if (node == node->parent->left)
		node->parent->left = node_right;
	else
		node->parent->right = node_right;

	node_right->left = node;
	node->parent = node_right;
}

void RedBlackTree::rotateRight(Node *root, Node *node) {
	Node *node_left = node->left;

	node->left = node_left->right;
}

void RedBlackTree::fixViolation(Node *root, Node *node) {
	Node *parent = nullptr, *grandparent = nullptr;
	
	// if the node isn't the root node, is red, and the parent is red, then it's a violation
	while ((node != root) && !(node->isBlack) && !(node->parent->isBlack)) {

	}
}

/**
 * inOrderTraversal (give nodes in increasing order)
 *	1. Traverse the left subtree.
 *	2. Get the root.
 *	3. Traverse the right subtree.
 */
void RedBlackTree::inOrderTraversal() {

}

/**
 * preOrderTraversal (used to copy the tree)
 *	1. Get the root.
 *	2. Traverse the left subtree.
 *	3. Traverse the right subtree.
 */
void RedBlackTree::preOrderTraversal() {

}

/**
 * postOrderTraversal (used to delete the tree)
 *	1. Traverse the left subtree.
 *	2. Traverse the right subtree.
 *	3. Get the root.
 */
void RedBlackTree::postOrderTraversal() {

}