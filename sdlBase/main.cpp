#include <iostream>
#include <SDL.h>

#include "Renderer.h"
#include "Window.h"
#include "DrawEvent.h"

using std::cout;
using std::endl;

int WIDTH = 720;
int HEIGHT = 720;
SDL_Renderer* renderer;
SDL_Window* window;
SDL_Color color;
bool running = true;
int frameCount, timerFPS, lastFrame, fps;

//void render() {
//	frameCount++;
//	timerFPS = SDL_GetTicks() - lastFrame;
//	if (timerFPS > (100 / 60)) {
//		SDL_Delay((1000 / 60) - timerFPS);
//	}
//}

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

	//test draw events
	SDL_Color lineColor = { 52, 104, 235, 255 };
	SDL_Point lStart = { 0,0 };
	SDL_Point lEnd = { 100, 200 };

	DrawEvent* line = new DrawEvent(Type::LINE, lineColor, testR.getRenderer(), lStart, lEnd);

	SDL_Color rectColor = { 52, 235, 192, 255 };
	SDL_Rect rectD = { 0,200,30,30 };
	DrawEvent fill(Type::FILLRECT, rectColor, testR.getRenderer(), rectD);

	SDL_Color nodeColor = { 235, 52, 52, 255 };
	SDL_Point nodeStart = { WIDTH/2, 30 };
	DrawEvent node(Type::NODE, nodeColor, testR.getRenderer(), nodeStart, 20);

	SDL_Point textStart = { (WIDTH / 2) - 12, 30-12 };
	DrawEvent text(Type::TEXT, nodeColor, testR.getRenderer(), textStart, "99", 20, "RobotoMono-Thin.ttf");
	

	while (running) {
		testR.addDrawEvent(*line);
		testR.addDrawEvent(fill);
		testR.addDrawEvent(node);
		testR.addDrawEvent(text);

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
		
	}
	/*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "hello world","Success",NULL);*/

	TTF_Quit();
	SDL_Quit();
	return 0;
}