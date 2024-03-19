#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "fontAtlas.h"

using std::cout;
using std::endl;
using std::string;

enum Type {
	POINT,
	LINE,
	RECT,
	FILLRECT,
	NODE,
	TEXT
};

class DrawEvent {
private:
	Type type;
	DrawEvent* next = nullptr;
	SDL_Color color;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect rect = { 0,0,0,0 };
	SDL_Point start = { 0,0 };
	SDL_Point end = { 0,0 };
	int rad = 0;
	//font stuff
	string text;
	int textSize = 0;
	FontAtlas* atlas = nullptr;

	//surface or texture
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;


public:
	
	//point
	DrawEvent(Type nType,SDL_Color nColor, SDL_Renderer* nRenderer, SDL_Point nPoint) {
		this->type = nType;
		this->color = nColor;
		this->renderer = nRenderer;
		this->start = nPoint;
	}
	//line
	DrawEvent(Type nType, SDL_Color nColor, SDL_Renderer* nRenderer, SDL_Point nStart, SDL_Point nEnd) {
		this->type = nType;
		this->color = nColor;
		this->renderer = nRenderer;
		this->start = nStart;
		this->end = nEnd;
	}
	//rectangle / fill
	DrawEvent(Type nType, SDL_Color nColor, SDL_Renderer* nRenderer, SDL_Rect nRect) {
		this->type = nType;
		this->color = nColor;
		this->renderer = nRenderer;
		this->rect = nRect;
	}
	//Node
	DrawEvent(Type nType, SDL_Color nColor, SDL_Renderer* nRenderer, SDL_Point nCenter, int nRad) {
		this->type = nType;
		this->color = nColor;
		this->renderer = nRenderer;
		this->start = nCenter;
		this->rad = nRad;
	}
	//Text; currently needs the text, text-size, color
	DrawEvent(Type nType, SDL_Renderer* nRenderer, SDL_Point nStart, string nText, int nTextSize, FontAtlas* nAtlas) {
		this->type = nType;
		this->renderer = nRenderer;
		this->start = nStart;
		this->text = nText;
		this->textSize = nTextSize;
		this->atlas = nAtlas;

	}
	~DrawEvent() {
		//cout << "DRAWEVENT DESTRUCT" << endl;
		if (this->surface) {
			SDL_FreeSurface(this->surface);
		}
		if (this->texture) {
			SDL_DestroyTexture(this->texture);
		}
	}

	//set next
	void setNext(DrawEvent* nNext);

	//get next
	DrawEvent* getNext();

	//event.draw; (send to renderer backbuffer)
	bool draw();

};