#include <iostream>
#include <SDL.h>

#include "Renderer.h"
#include "Window.h"
#include "DrawEvent.h"

#include "IngestFile.h"

#include "BSTree.h"

using std::cout;
using std::endl;



//draw frames/textboxes
void drawLayout(Renderer* nRenderer, SDL_Color nColor, int nWidth, int nHeight) {
	
	SDL_Color textBG = { 10, 10, 10, 255 };

	//outer frame
	SDL_Rect outRect = { 0,0,nWidth,nHeight };
	DrawEvent outerFrame(Type::RECT, nColor, nRenderer->getRenderer(), outRect);
	
	//middle frame
	SDL_Point vL1start = { (nWidth / 2)+(nWidth / 200), 0 };
	SDL_Point vL1end = { (nWidth / 2)+(nWidth / 200), nHeight };
	SDL_Point vL2start = { (nWidth / 2)-(nWidth / 200), 0};
	SDL_Point vL2end = { (nWidth / 2)-(nWidth / 200), nHeight };

	DrawEvent vL1ine(Type::LINE, nColor, nRenderer->getRenderer(), vL1start, vL1end);
	DrawEvent vL2ine(Type::LINE, nColor, nRenderer->getRenderer(), vL2start, vL2end);

	//upper textbox
	SDL_Rect uTRect = { (nWidth / 2) + (nWidth / 100), (nWidth / 100), (nWidth / 2) - (nWidth / 65), (nHeight/2) - (nHeight / 65) };
	DrawEvent upperTboxBg(Type::FILLRECT, textBG, nRenderer->getRenderer(), uTRect);
	DrawEvent upperTboxBorder(Type::RECT, nColor, nRenderer->getRenderer(), uTRect);
	
	//lower textbox
	SDL_Rect lTRect = { (nWidth / 2) + (nWidth / 100), (nHeight / 2), (nWidth / 2) - (nWidth / 65), (nHeight / 2) - (nHeight / 65) };
	DrawEvent lowerTboxBg(Type::FILLRECT, textBG, nRenderer->getRenderer(), lTRect);
	DrawEvent lowerTboxBorder(Type::RECT, nColor, nRenderer->getRenderer(), lTRect);

	//queue events
	nRenderer->addDrawEvent(outerFrame);
	nRenderer->addDrawEvent(vL1ine);
	nRenderer->addDrawEvent(vL2ine);
	nRenderer->addDrawEvent(upperTboxBg);
	nRenderer->addDrawEvent(upperTboxBorder);
	nRenderer->addDrawEvent(lowerTboxBg);
	nRenderer->addDrawEvent(lowerTboxBorder);
}

int main(int argc, char* argv[])
{
	//Globals
	int WIDTH = 720;
	int HEIGHT = 600;
	bool running = true;
	string searchResult;
	string buffer;
	int textLine = 1;
	int textCol = 1;
	
	//load and ingest file
	Ingest fileLoader("MorseTable.txt");
	fileLoader.ingestFile();
	fileLoader.medianCut(0,fileLoader.getKeyLength());

	//create tree
	BST tree;
	fileLoader.loadToTree(&tree);

	////test search
	//string testString;
	//tree.searchChar('k',tree.getRoot(), &testString);
	//cout << testString << endl;


	//setup SDL
	SDL_Event e;
	SDL_Color bgColor = { 0, 0, 0, 255 };
	SDL_Color nodeColor = { 51, 150, 61, 255 };

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "FAILED at SDL_INIT" << endl;
	}
	if (TTF_Init() < 0) {
		cout << "FAILED at TTF_Init" << endl;
	}

	//create window and renderer
	Window window("Binary Visualizer", WIDTH, HEIGHT);
	Renderer renderer(window.getWindow(), bgColor);
	
	while (running) {

		drawLayout(&renderer, nodeColor, WIDTH, HEIGHT);
		tree.drawTree(&renderer, 0, 20, false, tree.getRoot());
		
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_TEXTINPUT:
				buffer += e.text.text;
				
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					buffer = buffer.substr(0, buffer.length() - 1);
				}
				else if (e.key.keysym.sym == SDLK_RETURN) {
					buffer += '~';
				}
				break;
			}
		}

		//print text input
		
		//check for out of bounds
		if (textCol * 13 > (WIDTH / 2) - (WIDTH / 65) - 13 && buffer[buffer.size()] != '~') {
			buffer += '~';
		}

		textLine = 1;
		textCol = 0;

		for (int i = 0; i < buffer.size(); i++) {
			string key(1, buffer[i]);

			//check for new line
			if (buffer[i] == '~') {
				textLine += 1;
				textCol = 0;
			}
			//print char
			else {
				
				SDL_Point textPos = { (WIDTH / 2) + (WIDTH / 90) + (textCol * 13), (WIDTH / 90) + (textLine * 13) };
				DrawEvent dText(Type::TEXT, nodeColor, renderer.getRenderer(), textPos, key, 13, "RobotoMono-Thin.ttf");
				renderer.addDrawEvent(dText);
				tree.searchChar(buffer[i], tree.getRoot(), &searchResult);
				textCol += 1;
			}
			
		}
		
		//print search output
		/*for (int i = 0; i < buffer.size(); i++) {
			string key(1, buffer[i]);
			SDL_Point textPos = { (WIDTH / 2) + (WIDTH / 90) + (i * 10), (WIDTH / 90) };
			DrawEvent dText(Type::TEXT, nodeColor, renderer.getRenderer(), textPos, key, 10, "RobotoMono-Thin.ttf");
			renderer.addDrawEvent(dText);
			tree.searchChar(buffer[i], tree.getRoot(), &searchResult);
		}*/

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