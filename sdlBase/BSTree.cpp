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
void BST::drawTree(Renderer* nRenderer, float startX, float nHeight, bool isLeft, BSTNode* start) {
	
	SDL_Color nodeColor = { 51, 150, 61, 255 };

	if (start == nullptr) {
		return;
	}
	else
	{
		SDL_Point dataPoint = { startX + nHeight, this->getYlevel()};
		SDL_Point lSPoint = { startX + nHeight/4, this->getYlevel() + nHeight/4 };
		SDL_Point lEPoint = { startX + (nHeight-nHeight/5), this->getYlevel() + nHeight/4 };

		DrawEvent dText(Type::TEXT, nodeColor, nRenderer->getRenderer(), dataPoint, start->getData(), nHeight/2, "RobotoMono-Thin.ttf");
		DrawEvent hLine(Type::LINE, nodeColor, nRenderer->getRenderer(), lSPoint, lEPoint);

		///////////////////////

		//save node x,y
		start->setX(lSPoint.x);
		start->setY(lSPoint.y);

		//only call if not root (draw connecting lines)
		if (start->getParent()) {
			SDL_Point tempStart = { start->getX(), start->getY() };
			SDL_Point tempEnd = { start->getParent()->getX() + nHeight, start->getParent()->getY() + nHeight/2 };
			DrawEvent vLine(Type::LINE, nodeColor, nRenderer->getRenderer(), tempStart, tempEnd);

			if (isLeft == true) {
				nRenderer->addDrawEvent(hLine);
				
			}
			else {
				nRenderer->addDrawEvent(hLine);
				nRenderer->addDrawEvent(vLine);
			}
		}
		
		// draw the value of the node
		nRenderer->addDrawEvent(dText);

		//increase y here
		this->yLevel += nHeight;
		
		// enter the next tree level - left and right branch (increase x level)
		if (isLeft == true) {
			drawTree(nRenderer, startX + nHeight, nHeight, true, start->getLeft());
			drawTree(nRenderer, startX + nHeight, nHeight, false, start->getRight());
		}
		else {
			drawTree(nRenderer, startX + nHeight, nHeight, true, start->getLeft());
			drawTree(nRenderer, startX + nHeight, nHeight, false, start->getRight());
		}
		
	}

}