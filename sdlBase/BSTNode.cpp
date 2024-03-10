#include "BSTNode.h"

/*Members*/
void BSTNode::setData(string nData) {
	this->data = nData;
}
void BSTNode::setLeft(BSTNode* nLeft) {
	this->left = nLeft;
}
void BSTNode::setRight(BSTNode* nRight) {
	this->right = nRight;
}

string BSTNode::getData() const {
	return this->data;
}
BSTNode* BSTNode::getLeft() const {
	return this->left;
}
BSTNode* BSTNode::getRight() const {
	return this->right;
}

//overload for printing
ostream& operator<<(ostream& os, const BSTNode& node) {
	os << "data:" << node.getData() << endl;
	if (node.getLeft()) {
		os << "left:" << "true" << endl;
	}
	else {
		os << "left:" << "false" << endl;
	}
	if (node.getRight()) {
		os << "right:" << "true" << endl;
	}
	else {
		os << "right:" << "false" << endl;
	}

	return os;

}