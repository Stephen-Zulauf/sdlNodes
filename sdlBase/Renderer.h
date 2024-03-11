#pragma once

#include <SDL.h>
#include <iostream>
#include <queue>

#include "DrawEvent.h"

using std::cout;
using std::endl;

class Renderer {
private:
	SDL_Color bgColor;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
	//drawing queue
	std::queue<DrawEvent> dQueue;

public:
	//default black screen
	Renderer(SDL_Window* nWindow) {
		this->bgColor.r = 0;
		this->bgColor.g = 0;
		this->bgColor.b = 0;
		this->bgColor.a = 255;
		window = nWindow;
		renderer = SDL_CreateRenderer(nWindow, -1, SDL_RENDERER_ACCELERATED);
	}
	//specify background
	Renderer(SDL_Window* nWindow, SDL_Color nColor) {
		this->bgColor = nColor;
		window = nWindow;
		renderer = SDL_CreateRenderer(nWindow, -1, SDL_RENDERER_ACCELERATED);
	}
	~Renderer() {
		if (renderer) {
			SDL_DestroyRenderer(this->renderer);
		}
	}

	//check if renderer created
	bool checkRenderer();

	//Return renderer instance
	SDL_Renderer* getRenderer();

	//Update renderer
	bool updateRenderer();

	//add draw event
	void addDrawEvent(DrawEvent nEvent);
};