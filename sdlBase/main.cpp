#include <iostream>
#include <SDL.h>

#include "Renderer.h"
#include "Window.h"
#include "DrawEvent.h"
#include "IngestFile.h"
#include "BSTree.h"
#include "TextBox.h"

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

	//queue events
	nRenderer->addDrawEvent(outerFrame);
	nRenderer->addDrawEvent(vL1ine);
	nRenderer->addDrawEvent(vL2ine);
}

int main(int argc, char* argv[])
{
	//Globals
	int WIDTH = 720;
	int HEIGHT = 600;
	bool running = true;
	string searchResult;
	string buffer;
	string outputBuffer;
	
	//load and ingest file
	Ingest fileLoader("MorseTable.txt");
	fileLoader.ingestFile();
	fileLoader.medianCut(0,fileLoader.getKeyLength());

	//create tree
	BST tree;
	fileLoader.loadToTree(&tree);

	//setup SDL
	SDL_Event e;
	SDL_Color bgColor = { 0, 0, 0, 255 };
	SDL_Color nodeColor = { 51, 150, 61, 255 };
	SDL_Color textBG = { 10, 10, 10, 255 };

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "FAILED at SDL_INIT" << endl;
	}
	if (TTF_Init() < 0) {
		cout << "FAILED at TTF_Init" << endl;
	}

	//create window and renderer
	Window window("Binary Visualizer", WIDTH, HEIGHT);
	Renderer renderer(window.getWindow(), bgColor);

	//create text boxes
	SDL_Rect upTxt = { (WIDTH / 2) + (WIDTH / 100), (HEIGHT/100), (WIDTH / 2) - (WIDTH / 65), (HEIGHT / 2) - (HEIGHT / 65) };
	TextBox upperText(&renderer, nodeColor, textBG, nodeColor, upTxt, 13);
	SDL_Rect lrTxt = { (WIDTH / 2) + (WIDTH / 100), (HEIGHT / 2), (WIDTH / 2) - (WIDTH / 65), (HEIGHT / 2) - (HEIGHT / 65) };
	TextBox lowerText(&renderer, nodeColor, textBG, nodeColor, lrTxt, 13);
	
	while (running) {

		
		
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_TEXTINPUT:

				//update input
				buffer += e.text.text;
				upperText.updateBuffer(buffer);

				//update output
				tree.searchString(buffer, tree.getRoot(), &outputBuffer);
				lowerText.updateBuffer(outputBuffer);

				//draw tree
				tree.drawTree(&renderer, 0, 20, false, tree.getRoot());

				//draw frames
				drawLayout(&renderer, nodeColor, WIDTH, HEIGHT);

				//print text input/output
				upperText.draw();
				lowerText.draw();

				//update renderer & draw queue
				if (!renderer.updateRenderer()) {
					running = false;
				}

				tree.setYlevel(0);
				
				break;

			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					buffer = buffer.substr(0, buffer.length() - 1);

					//clear visited
					tree.clearVisits(tree.getRoot());

					//update input
					upperText.updateBuffer(buffer);

					//update output
					tree.searchString(buffer, tree.getRoot(), &outputBuffer);
					lowerText.updateBuffer(outputBuffer);

					//draw tree
					tree.drawTree(&renderer, 0, 20, false, tree.getRoot());

					//draw frames
					drawLayout(&renderer, nodeColor, WIDTH, HEIGHT);

					//print text input/output
					upperText.draw();
					lowerText.draw();

					//update renderer & draw queue
					if (!renderer.updateRenderer()) {
						running = false;
					}

					tree.setYlevel(0);

				}
				else if (e.key.keysym.sym == SDLK_RETURN) {
					buffer += '~';
				}
				break;
			}
		}

		if (SDL_PollEvent(&e) == 0) {
			//draw tree
			tree.drawTree(&renderer, 0, 20, false, tree.getRoot());

			//draw frames
			drawLayout(&renderer, nodeColor, WIDTH, HEIGHT);

			//print text input/output
			upperText.draw();
			lowerText.draw();

			//update renderer & draw queue
			if (!renderer.updateRenderer()) {
				running = false;
			}

			tree.setYlevel(0);
		}
		

		
		
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}