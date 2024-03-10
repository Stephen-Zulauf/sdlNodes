#pragma once

#pragma once

#include <iostream>
#include "BSTNode.h"
#include "Renderer.h"
#include "DrawEvent.h"

using std::cout;
using std::endl;

class BST {
private:
	BSTNode* root;

	//delete tree
	void destroyTree();

public:
	/*constructors*/
	BST() {
		this->root = nullptr;
	}
	/*destructor*/

	/*members*/
	//get root
	BSTNode* getRoot();

	//adds item allocates new node
	bool insertNode(string nData, BSTNode* start);

	//traversal
	void inOrderTraversal(BSTNode* start);

	void preOrderTraversal(BSTNode* start);

	void postOrderTraversal(BSTNode* start);

	//send to renderer

	bool drawTree(Renderer* nRenderer, SDL_Point startPoint, int radius);

};