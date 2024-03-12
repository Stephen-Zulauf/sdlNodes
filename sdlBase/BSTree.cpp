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
		if (stoi(start->getData()) > stoi(nData)) {
			if (start->getLeft() == nullptr) {
				temp = new BSTNode(nData);
				if (temp) {
					temp->setParent(start);
					start->setLeft(temp);
					return true;
				}

			}
			else {
				insertNode(nData, start->getLeft());
			}
		}
		//goes right
		else if (stoi(start->getData()) < stoi(nData)) {
			if (start->getRight() == nullptr) {
				temp = new BSTNode(nData);
				if (temp) {
					temp->setParent(start);
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

//depth
int BST::getMaxDepth(BSTNode* start) {
	if (start == nullptr) {
		return 0;
	}
	else {
		int left = getMaxDepth(start->getLeft());
		int right = getMaxDepth(start->getRight());

		if (left > right) {
			return (left + 1);
		}
		else {
			return (right + 1);
		}
	}
}

//set y level
void BST::setYlevel(int nLevel) {
	this->yLevel = nLevel;
}

//get y level
int BST::getYlevel() {
	return this->yLevel;
}

//set x level
void BST::setXlevel(int nLevel) {
	this->xLevel = nLevel;
}

//get x level
int BST::getXlevel() {
	return this->xLevel;
}

//send to renderer; preorder traversal
void BST::drawTree(Renderer* nRenderer, int width, int height, bool isLeft, BSTNode* start) {
	
	SDL_Color nodeColor = { 235, 52, 52, 255 };
	//vector<DrawEvent> history;

	if (start == nullptr) {
		return;
	}
	else
	{
		SDL_Point startPoint = { width, this->getYlevel()};
		SDL_Point dataPoint = { width + 20, this->getYlevel()};
		SDL_Point strPoint = { width - 20, this->getYlevel()};

		DrawEvent tText(Type::TEXT, nodeColor, nRenderer->getRenderer(), startPoint, "|--", 10, "RobotoMono-Thin.ttf");
		DrawEvent lText(Type::TEXT, nodeColor, nRenderer->getRenderer(), startPoint, "^--", 10, "RobotoMono-Thin.ttf");
		DrawEvent sText(Type::TEXT, nodeColor, nRenderer->getRenderer(), strPoint, "|  ", 10, "RobotoMono-Thin.ttf");
		DrawEvent dText(Type::TEXT, nodeColor, nRenderer->getRenderer(), dataPoint, start->getData(), 10, "RobotoMono-Thin.ttf");

		///////////////////////
		//std::cout << prefix;

		if (isLeft == true) {
			nRenderer->addDrawEvent(tText);
		}
		else {
			nRenderer->addDrawEvent(lText);
		}
		
		// print the value of the node
		nRenderer->addDrawEvent(dText);

		//increase y here
		this->yLevel += 20;
		
		// enter the next tree level - left and right branch
		if (isLeft == true) {
			//nHistory.push_back(sText);
			//nRenderer->addDrawEvent(sText);
			drawTree(nRenderer, startPoint.x + 20, startPoint.y, true, start->getLeft());
			drawTree(nRenderer, startPoint.x + 20, startPoint.y, false, start->getRight());
		}
		else {
			drawTree(nRenderer, startPoint.x + 20, startPoint.y, true, start->getLeft());
			drawTree(nRenderer, startPoint.x + 20, startPoint.y, false, start->getRight());
		}
		


	}

	
}