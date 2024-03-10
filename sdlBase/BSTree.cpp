#include "BSTree.h"

/*members*/

//private


//delete tree
void BST::destroyTree() {
	if (this->root) {
		delete this->root;
	}
}

//get root
BSTNode* BST::getRoot() {
	return this->root;
}

//adds item allocates new node
bool BST::insertNode(string nData, BSTNode* start) {
	BSTNode* temp;
	if (this->root == nullptr) {
		temp = new BSTNode(nData);
		if (temp) {
			this->root = temp;
			return true;
		}
	}
	else {
		//goes left
		if (start->getData() > nData) {
			if (start->getLeft() == nullptr) {
				temp = new BSTNode(nData);
				if (temp) {
					start->setLeft(temp);
					return true;
				}

			}
			else {
				insertNode(nData, start->getLeft());
			}
		}
		//goes right
		else if (start->getData() < nData) {
			if (start->getRight() == nullptr) {
				temp = new BSTNode(nData);
				if (temp) {
					start->setRight(temp);
					return true;
				}

			}
			else {
				insertNode(nData, start->getRight());
			}

		}
	}

	return false;
}


void BST::inOrderTraversal(BSTNode* start) {

	if (start == nullptr) {
		return;
	}


	inOrderTraversal(start->getLeft());
	cout << *start;
	inOrderTraversal(start->getRight());

}

void BST::preOrderTraversal(BSTNode* start) {
	if (start == nullptr) {
		return;
	}

	cout << *start;
	preOrderTraversal(start->getLeft());
	preOrderTraversal(start->getRight());
}

void BST::postOrderTraversal(BSTNode* start) {
	if (start == nullptr) {
		return;
	}

	postOrderTraversal(start->getLeft());
	postOrderTraversal(start->getRight());

	cout << *start;
}