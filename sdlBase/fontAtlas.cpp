#include "fontAtlas.h"

bool FontAtlas::renderChar(SDL_Point nLocation, char nChar) {
	//copy rendered texture to render window

	
	//modify start location of source based on character being rendered

	int index = int(nChar)-32;
	int width = 0;
	int height = 0;
	SDL_QueryTexture(this->glyphs[index], NULL, NULL, &width, &height);
	
	SDL_Rect dest = { nLocation.x, nLocation.y, width, height};

	if (SDL_RenderCopy(this->renderer, this->glyphs[index], NULL, &dest) == 0) {
		return true;
	}
	else {
		string err = SDL_GetError();
		if (this->texture) {
			cout<< "texture present" << endl;
		}
		cout << "ERR FontAtlas: couldnt renderCopy for char: "<< nChar << endl;
		cout << "TextureWidth: "<< this->textureW << endl;
		cout << "TextureHeight: "<< this->textureH << endl;
		cout << "Texture: "<< this->textureH << endl;
		cout << err << endl;
		return false;
	}
}

bool FontAtlas::renderString(SDL_Point nLocation, string nString) {

	SDL_Point temp = nLocation;

	for (int i = 0; i < nString.size(); i++) {
		renderChar(temp, nString[i]);
		temp.x += this->textSize;
	}
	return true;
}