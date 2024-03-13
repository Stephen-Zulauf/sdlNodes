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
	SDL_Color bgColor = { 0, 0, 0, 255 };

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "FAILED at SDL_INIT" << endl;
	}
	if (TTF_Init() < 0) {
		cout << "FAILED at TTF_Init" << endl;
	}

	//test window and renderer
	Window testW("test", 720, 450);
	Renderer testR(testW.getWindow(), bgColor);
	
	//test binary tree
	BST testTree;

	testTree.insertNode("60", testTree.getRoot());
	testTree.insertNode("50", testTree.getRoot());
	testTree.insertNode("70", testTree.getRoot());
	testTree.insertNode("40", testTree.getRoot());
	testTree.insertNode("55", testTree.getRoot());
	testTree.insertNode("65", testTree.getRoot());
	testTree.insertNode("80", testTree.getRoot());
	testTree.insertNode("30", testTree.getRoot());
	testTree.insertNode("45", testTree.getRoot());
	testTree.insertNode("53", testTree.getRoot());
	testTree.insertNode("58", testTree.getRoot());
	testTree.insertNode("63", testTree.getRoot());
	testTree.insertNode("68", testTree.getRoot());
	testTree.insertNode("75", testTree.getRoot());
	testTree.insertNode("90", testTree.getRoot());
	testTree.insertNode("20", testTree.getRoot());
	testTree.insertNode("35", testTree.getRoot());
	testTree.insertNode("42", testTree.getRoot());
	testTree.insertNode("41", testTree.getRoot());
	testTree.insertNode("99", testTree.getRoot());
	testTree.insertNode("100", testTree.getRoot());

	while (running) {
		testTree.drawTree(&testR, 0, 21, false, testTree.getRoot());
		
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

	TTF_Quit();
	SDL_Quit();
	return 0;
}