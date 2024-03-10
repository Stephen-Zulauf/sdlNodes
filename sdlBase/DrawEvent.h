#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

using std::cout;
using std::endl;

enum Type {
	POINT,
	LINE,
	RECT,
	FILLRECT,
	NODE
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

	//set next
	void setNext(DrawEvent* nNext);

	//get next
	DrawEvent* getNext();

	//event.draw; (send to renderer backbuffer)
	bool draw();

};