#include <iostream>
#include <SDL.h>

#include "Renderer.h"
#include "Window.h"
#include "DrawEvent.h"

#include "BSTree.h"

using std::cout;
using std::endl;

int WIDTH = 720;
int HEIGHT = 720;
bool running = true;

int main(int argc, char* argv[])
{
	SDL_Event e;
	SDL_Color bgColor = { 235, 168, 52, 255 };

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "FAILED at SDL_INIT" << endl;
	}
	if (TTF_Init() < 0) {
		cout << "FAILED at TTF_Init" << endl;
	}


	//test window and renderer
	Window testW("test", 720, 450);
	Renderer testR(testW.getWindow(), bgColor);

	////test draw events
	//SDL_Color lineColor = { 52, 104, 235, 255 };
	//SDL_Point lStart = { 0,0 };
	//SDL_Point lEnd = { 100, 200 };

	//DrawEvent* line = new DrawEvent(Type::LINE, lineColor, testR.getRenderer(), lStart, lEnd);

	//SDL_Color rectColor = { 52, 235, 192, 255 };
	//SDL_Rect rectD = { 0,200,30,30 };
	//DrawEvent fill(Type::FILLRECT, rectColor, testR.getRenderer(), rectD);

	//SDL_Color nodeColor = { 235, 52, 52, 255 };
	//SDL_Point nodeStart = { WIDTH/2, 30 };
	//DrawEvent node(Type::NODE, nodeColor, testR.getRenderer(), nodeStart, 20);

	//SDL_Point textStart = { (WIDTH / 2) - 12, 30-12 };
	//DrawEvent text(Type::TEXT, nodeColor, testR.getRenderer(), textStart, "THIS is a Test oopPOP", 20, "RobotoMono-Thin.ttf");
	
	//test binary tree
	BST testTree(WIDTH/2);

	testTree.insertNode("8", testTree.getRoot());
	testTree.insertNode("5", testTree.getRoot());
	testTree.insertNode("10", testTree.getRoot());
	testTree.insertNode("2", testTree.getRoot());
	testTree.insertNode("6", testTree.getRoot());
	testTree.insertNode("9", testTree.getRoot());
	testTree.insertNode("11", testTree.getRoot());
	
	/*testTree.insertNode("15", testTree.getRoot());
	testTree.insertNode("17", testTree.getRoot());
	testTree.insertNode("16", testTree.getRoot());*/

	//testTree.mapNodes(testTree.getRoot());
	
	int depth = testTree.getMaxDepth(testTree.getRoot());
	cout << "depth: " << depth << endl;

	testTree.postOrderTraversal(testTree.getRoot());

	SDL_Point nodeStart = { WIDTH / 2, 30 };

	while (running) {
		testTree.drawTree(&testR, 20, 11, false, testTree.getRoot());
		
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				running = false;
			
			}
		}

		//update renderer & draw queue
		if (!testR.updateRenderer()) {
			running = false;
		}

		testTree.setYlevel(0);
		testTree.setXlevel(0);
		
	}
	/*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "hello world","Success",NULL);*/

	TTF_Quit();
	SDL_Quit();
	return 0;
}