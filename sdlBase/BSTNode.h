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
	BSTNode* left;
	BSTNode* right;

public:
	/*Constructors*/
	BSTNode() {
		this->data = " ";
		this->left = nullptr;
		this->right = nullptr;
	}

	BSTNode(string nData) {
		this->data = nData;
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

	string getData() const;
	BSTNode* getLeft() const;
	BSTNode* getRight() const;

};

//overload for printing
ostream& operator<<(ostream& os, const BSTNode& node);