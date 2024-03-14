#include "BSTNode.h"

/*Members*/
//setters
void BSTNode::setKey(char nKey) {
	this->key = nKey;
}
void BSTNode::setData(string nData) {
	this->data = nData;
}
void BSTNode::setLeft(BSTNode* nLeft) {
	this->left = nLeft;
}
void BSTNode::setRight(BSTNode* nRight) {
	this->right = nRight;
}
void BSTNode::setParent(BSTNode* nParent) {
	this->parent = nParent;
}
void BSTNode::setX(float nX) {
	this->X = nX;
}
void BSTNode::setY(float nY) {
	this->Y = nY;
}
void BSTNode::setMod(float nMod) {
	this->mod = nMod;
}
void BSTNode::visit() {
	this->visited = true;
}
void BSTNode::unVisit() {
	this->visited = false;
}

//getters
char BSTNode::getKey() const {
	return this->key;
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
BSTNode* BSTNode::getParent() const {
	return this->parent;
}
float BSTNode::getX() const{
	return this->X;
}
float BSTNode::getY() const{
	return this->Y;
}
float BSTNode::getMod() const{
	return this->mod;
}
bool BSTNode::checkVisited() {
	return this->visited;
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
	os << "X: " << node.getX() << endl;
	os << "Y: " << node.getY() << endl;
	os << "MOD: " << node.getMod() << endl;

	return os;

}