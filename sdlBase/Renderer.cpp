#include "Renderer.h"

//check if renderer created
bool Renderer::checkRenderer() {
	if (this->renderer) {
		return true;
	}
	else {
		return false;
	}
}

//Return renderer instance
SDL_Renderer* Renderer::getRenderer() {
	if (this->renderer) {
		return this->renderer;
	}
	else {
		cout << "ERR no renderer instance" << endl;
		return nullptr;
	}
}

//Update renderer
bool Renderer::updateRenderer() {

	if (SDL_SetRenderDrawColor(this->renderer, this->bgColor.r, this->bgColor.g, this->bgColor.b, this->bgColor.a) == 0) {
		if (SDL_RenderClear(this->renderer) == 0) {
			//draw queue here

			SDL_RenderPresent(this->renderer);

			return true;
		}
		else {
			cout << "ERR updateRenderer: RenderClear failed" << endl;
			return false;
		}
	}
	else {
		cout << "ERR updateRenderer: SetRenderDrawColor failed" << endl;
		return false;
	}
	
	
}