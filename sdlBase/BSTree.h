#pragma once

#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include "BSTNode.h"
#include "Renderer.h"
#include "DrawEvent.h"

using std::queue;
using std::vector;
using std::cout;
using std::endl;

class BST {
private:
	BSTNode* root;

	//x level for drawing
	int xLevel = 0;
	//y level for drawing
	int yLevel = 0;

	//delete tree
	void destroyTree();

public:
	/*constructors*/
	BST(float nCenter) {
		this->root = nullptr;
	}
	/*destructor*/
	~BST() {
		destroyTree();
	}

	/*members*/
	//get root
	BSTNode* getRoot();

	//adds item allocates new node
	bool insertNode(string nData, BSTNode* start);

	//traversal
	void inOrderTraversal(BSTNode* start);

	void preOrderTraversal(BSTNode* start);

	void postOrderTraversal(BSTNode* start);

	//depth
	int getMaxDepth(BSTNode* start);

	//set y level
	void setYlevel(int nLevel);

	//get y level
	int getYlevel();

	//set x level
	void setXlevel(int nLevel);

	//get x level
	int getXlevel();

	//send to renderer
	void drawTree(Renderer* nRenderer, int width, int height, bool isLeft, BSTNode* start);

};