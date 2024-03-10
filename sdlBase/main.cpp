#include <iostream>
#include <SDL.h>

#include "Renderer.h"
#include "Window.h"

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

	Window testW("test", 720, 450);
	Renderer testR(testW.getWindow(), bgColor);

	while (running) {

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

	SDL_Quit();
	return 0;
}