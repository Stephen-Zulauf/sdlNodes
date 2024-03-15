#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <SDL.h>

#include "DrawEvent.h"
#include "Renderer.h"

using std::string;
using std::istringstream;

class TextBox {
private:
	int row = 0;
	int column = 0;
	string buffer;
	Renderer* renderer;

	SDL_Color textColor;
	SDL_Color bgColor;
	SDL_Color frameColor;

	SDL_Rect location;
	int fontSize;

public:

	TextBox(Renderer* nRenderer, SDL_Color nText, SDL_Color nBGColor, SDL_Color nFrameColor, SDL_Rect nLoc, int nSize) {
		this->renderer = nRenderer;
		this->bgColor = nBGColor;
		this->frameColor = nFrameColor;
		this->textColor = nText;
		this->location = nLoc;
		this->fontSize = nSize;
	}

	//update buffer
	void updateBuffer(string nBuffer);

	//draw textbox
	void draw();

	//increase row (for when enter is pressed)
	void incRow();

};