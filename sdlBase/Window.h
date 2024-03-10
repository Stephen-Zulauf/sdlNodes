#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Window {
private:
	char title[100] = "default";
	int width = 720;
	int height = 720;
	int posX = 0;
	int posY = 0;
	SDL_Window* window = nullptr;

public:
	Window() {

	}
	//default centered postion
	Window(string nTitle, int nWidth, int nHeight) {
		strcpy_s(this->title, nTitle.c_str());
		width = nWidth;
		height = nHeight;
		window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	}
	//specify position
	Window(string nTitle, int nPosx, int nPosy, int nWidth, int nHeight) {
		strcpy_s(this->title, nTitle.c_str());
		posX = nPosx;
		posY = nPosy;
		width = nWidth;
		height = nHeight;
		window = SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_SHOWN);
	}
	//copy
	Window(Window &copy) {
		strcpy_s(copy.title, this->title);
		copy.posX = this->posX;
		copy.posY = this->posY;
		copy.width = this->width;
		copy.height = this->height;
		copy.window = SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_SHOWN);
	}
	~Window() {
		if (this->window) {
			SDL_DestroyWindow(this->window);
		}
	}

	//check if window created
	bool checkWindow();

	//return the window instance
	SDL_Window* getWindow();
};