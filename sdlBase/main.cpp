#include <iostream>
#include <SDL.h>

#include "Renderer.h"
#include "Window.h"
#include "DrawEvent.h"

#include "IngestFile.h"

#include "BSTree.h"

using std::cout;
using std::endl;

int WIDTH = 720;
int HEIGHT = 1000;
bool running = true;

int main(int argc, char* argv[])
{
	//load and ingest file
	Ingest fileLoader("MorseTable.txt");
	fileLoader.ingestFile();
	fileLoader.medianCut(0,fileLoader.getKeyLength());

	//create tree
	BST tree;
	fileLoader.loadToTree(&tree);

	//test search
	string testString;
	tree.searchChar('k',tree.getRoot(), &testString);
	cout << testString << endl;


	//setup SDL
	SDL_Event e;
	SDL_Color bgColor = { 0, 0, 0, 255 };

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "FAILED at SDL_INIT" << endl;
	}
	if (TTF_Init() < 0) {
		cout << "FAILED at TTF_Init" << endl;
	}

	//create window and renderer
	Window window("Binary Visualizer", 720, 600);
	Renderer renderer(window.getWindow(), bgColor);
	
	while (running) {
		tree.drawTree(&renderer, 0, 20, false, tree.getRoot());
		
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				running = false;
			
			}
		}

		//update renderer & draw queue
		if (!renderer.updateRenderer()) {
			running = false;
		}

		tree.setYlevel(0);
		
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}