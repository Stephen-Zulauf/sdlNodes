#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class FontAtlas {
private:
	string fileName;
	TTF_Font* font = nullptr;
	SDL_Renderer* renderer = nullptr;

	//starts at ascii code 32-126
	string key = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	int textSize = 0;
	SDL_Color color;

	//surface or texture
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	//vector of glyph textures
	vector<SDL_Texture*> glyphs;

	int textureW = 0;
	int textureH = 0;

public:

	FontAtlas(string nFileName, SDL_Renderer* nRenderer, int nTextSize, SDL_Color nColor) {
		//set fileName
		this->fileName = nFileName;
		//set renderer
		this->renderer = nRenderer;
		//set text size
		this->textSize = nTextSize;
		//set color
		this->color = nColor;

		//load font file
		this->font = TTF_OpenFont(this->fileName.c_str(), this->textSize);

		if (this->font) {
			for (int i = 0; i < key.size(); i++) {
				//create surface from file
				this->surface = TTF_RenderText_Solid(this->font, this->key.substr(i,1).c_str(), this->color);

				if (this->surface) {
					//render texture from surface
					SDL_Texture* temptext = SDL_CreateTextureFromSurface(this->renderer, this->surface);
					if (temptext) {
						glyphs.push_back(SDL_CreateTextureFromSurface(this->renderer, this->surface));
					}
					else {
						cout << "ERR FontAtlas: couldnt create texture" << endl;
					}
					//free created surface
					SDL_FreeSurface(this->surface);
				}
				else {
					cout << "ERR FontAtlas: couldnt create surface" << endl;
				}
			}
			//close font file
			TTF_CloseFont(this->font);
		}
		else {
			cout << "ERR FontAtlas: couldnt open font file" << endl;
		}
		
	}

	bool renderChar(SDL_Point nLocation, char nChar);
	bool renderString(SDL_Point nLocation, string nString);
};