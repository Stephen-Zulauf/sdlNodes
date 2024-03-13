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
	cout << "//////////////////////////" << endl;
	fileLoader.printQueue();


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
	Window testW("test", 720, 600);
	Renderer testR(testW.getWindow(), bgColor);
	
	//create binary tree
	BST testTree;
	testTree.insertNode('g', "--.", testTree.getRoot());
	testTree.insertNode('9', "----.", testTree.getRoot());
	testTree.insertNode('q', "--.-", testTree.getRoot());
	testTree.insertNode('4', "....-", testTree.getRoot());
	testTree.insertNode('b', "-...", testTree.getRoot());
	testTree.insertNode('l', ".-..", testTree.getRoot());
	testTree.insertNode('v', "...-", testTree.getRoot());
	testTree.insertNode('1', ".----", testTree.getRoot());
	testTree.insertNode('6', "-....", testTree.getRoot());
	testTree.insertNode('.', ".-.-.-", testTree.getRoot());
	testTree.insertNode('d', "-..", testTree.getRoot());
	testTree.insertNode('i', "..", testTree.getRoot());
	testTree.insertNode('n', "-.", testTree.getRoot());
	testTree.insertNode('s', "...", testTree.getRoot());
	testTree.insertNode('x', "-..-", testTree.getRoot());
	testTree.insertNode('3', "...--", testTree.getRoot());
	testTree.insertNode('8', "---..", testTree.getRoot());
	testTree.insertNode('a', ".-", testTree.getRoot());
	testTree.insertNode('f', "..-.", testTree.getRoot());
	testTree.insertNode('k', "-.-", testTree.getRoot());
	testTree.insertNode('u', "..-", testTree.getRoot());
	testTree.insertNode('p', ".--.", testTree.getRoot());
	testTree.insertNode('z', "--..", testTree.getRoot());
	testTree.insertNode('2', "..---", testTree.getRoot());
	testTree.insertNode('7', "--...", testTree.getRoot());
	testTree.insertNode('?', "..--..", testTree.getRoot());
	testTree.insertNode('e', ".", testTree.getRoot());
	testTree.insertNode('j', ".---", testTree.getRoot());
	testTree.insertNode('o', "---", testTree.getRoot());
	testTree.insertNode('t', "-", testTree.getRoot());
	testTree.insertNode('y', "-.--", testTree.getRoot());
	////
	testTree.insertNode('0', "-----", testTree.getRoot());
	testTree.insertNode('5', ".....", testTree.getRoot());
	testTree.insertNode(',', "--..--", testTree.getRoot());
	testTree.insertNode('c', "-.-.", testTree.getRoot());
	testTree.insertNode('h', "....", testTree.getRoot());
	testTree.insertNode('m', "--", testTree.getRoot());
	testTree.insertNode('r', ".-.", testTree.getRoot());
	testTree.insertNode('w', ".--", testTree.getRoot());
	

	while (running) {
		testTree.drawTree(&testR, 0, 20, false, testTree.getRoot());
		
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