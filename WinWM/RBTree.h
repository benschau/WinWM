#ifndef RBTREE_H
#define RBTREE_H

#include <Windows.h>

namespace RBTree {
	template<typename type>
	typedef struct Node {
		type val;
		bool isBlack;
		Node *left;
		Node *right;
		Node *parent;

		Node() 
			: val(), isBlack(false), left(nullptr), right(nullptr), parent(nullptr) {}
		Node(type val, bool isBlack, Node *left, Node *right, Node *parent) 
			: val(val), isBlack(isBlack), left(left), right(right), parent(parent) {}
	};
	
	/**
	 * RedBlackTree
	 *	1) Every node is either red or black
	 *	2) Root of the tree is always black.
	 *	3) No two adjacent red nodes. (Red nodes can't have red parents or red children.)
	 *	4) Every path from root to a NULL node has the same number of black nodes.
	 */
	template<typename type>
	class RedBlackTree {
		Node *root;

		public:
			RedBlackTree();

			void inOrderTraversal();
			void preOrderTraversal();
			void postOrderTraversal();

			BOOL WINAPI insert(type t);
			void rotateRight(Node *root, Node *node);
			void rotateLeft(Node *root, Node *node);
		private:
			void fixViolation(Node *root, Node *node);

	};
}

#endif 