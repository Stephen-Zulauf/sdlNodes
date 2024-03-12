#pragma once

#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::endl;

class BSTNode {

private:
	string data;
	float X = 0;
	float Y = 0;
	float mod = 0;
	BSTNode* parent;
	BSTNode* left;
	BSTNode* right;

public:
	/*Constructors*/
	BSTNode() {
		this->data = " ";
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	BSTNode(string nData) {
		this->data = nData;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	/*Destructor*/
	~BSTNode() {
		if (this->left) {
			delete this->left;
		}
		if (this->right) {
			delete this->right;
		}
	}

	/*Members*/
	void setData(string nData);
	void setLeft(BSTNode* nLeft);
	void setRight(BSTNode* nRight);
	void setParent(BSTNode* nParent);
	void setX(float nX);
	void setY(float nY);
	void setMod(float nMod);

	string getData() const;
	BSTNode* getLeft() const;
	BSTNode* getRight() const;
	BSTNode* getParent() const;
	float getX() const;
	float getY() const;
	float getMod() const;

};

//overload for printing
ostream& operator<<(ostream& os, const BSTNode& node);