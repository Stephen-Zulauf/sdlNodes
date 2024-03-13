#pragma once

#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::endl;

class BSTNode {

private:
	char key;
	string data;
	float X = 0;
	float Y = 0;
	float mod = 0;
	BSTNode* parent;
	BSTNode* left;
	BSTNode* right;

	//color sent to rend
	//SDL_Color color;
	////visited change color if visited by search function
	bool visited = false;

public:
	/*Constructors*/
	BSTNode() {
		this->key = ' ';
		this->data = " ";
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	BSTNode(char nKey, string nData) {
		this->key = nKey;
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
	void setKey(char nKey);
	void setData(string nData);
	void setLeft(BSTNode* nLeft);
	void setRight(BSTNode* nRight);
	void setParent(BSTNode* nParent);
	void setX(float nX);
	void setY(float nY);
	void setMod(float nMod);
	void visit();

	char getKey() const;
	string getData() const;
	BSTNode* getLeft() const;
	BSTNode* getRight() const;
	BSTNode* getParent() const;
	float getX() const;
	float getY() const;
	float getMod() const;
	bool checkVisited();
	

};

//overload for printing
ostream& operator<<(ostream& os, const BSTNode& node);