#include "DrawEvent.h"

//set next
void DrawEvent::setNext(DrawEvent* nNext) {
	this->next = nNext;
}

//get next
DrawEvent* DrawEvent::getNext() {
	return this->next;
}

//event.draw; (send to renderer backbuffer) //TODO add colors
bool DrawEvent::draw() {
	switch (this->type) {
	case POINT:
		if (SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a) == 0) {
			if (SDL_RenderDrawPoint(this->renderer, start.x, start.y) == 0) {
				return true;
			}
			else {
				cout << "ERR DRAWEVENT: SDL_RenderDrawPoint failed" << endl;
				return false;
			}
		} 
		else {
			cout << "ERR DRAWEVENT: SDL_SetRenderDrawColor failed" << endl;
			return false;
		}
		break;

	case LINE:
		if (SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a) == 0) {
			if (SDL_RenderDrawLine(this->renderer, this->start.x, this->start.y, this->end.x, this->end.y) == 0) {
				return true;
			}
			else {
				cout << "ERR DRAWEVENT: SDL_RenderDrawLine failed" << endl;
				return false;
			}
		}
		else {
			cout << "ERR DRAWEVENT: SDL_SetRenderDrawColor failed" << endl;
			return false;
		}
		break;

	case RECT:
		if (SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a) == 0) {
			if (SDL_RenderDrawRect(this->renderer, &this->rect) == 0) {
				return true;
			}
			else {
				cout << "ERR DRAWEVENT: SDL_RenderDrawRect failed" << endl;
				return false;
			}
		}
		else {
			cout << "ERR DRAWEVENT: SDL_SetRenderDrawColor failed" << endl;
			return false;
		}
		break;

	case FILLRECT:
		if (SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a) == 0) {
			if (SDL_RenderFillRect(this->renderer, &this->rect) == 0) {
				return true;
			}
			else {
				cout << "ERR DRAWEVENT: SDL_RenderFillRect failed" << endl;
				return false;
			}
		}
		else {
			cout << "ERR DRAWEVENT: SDL_SetRenderDrawColor failed" << endl;
			return false;
		}
		break;

	case NODE:
		
		if (SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a) == 0) {
			const int32_t diameter = (this->rad * 2);

			int32_t x = (this->rad - 1);
			int32_t y = 0;
			int32_t tx = 1;
			int32_t ty = 1;
			int32_t error = (tx - diameter);

			while (x >= y)
			{
				//  Each of the following renders an octant of the circle
				SDL_RenderDrawPoint(this->renderer, this->start.x + x, this->start.y - y);
				SDL_RenderDrawPoint(this->renderer, this->start.x + x, this->start.y + y);
				SDL_RenderDrawPoint(this->renderer, this->start.x - x, this->start.y - y);
				SDL_RenderDrawPoint(this->renderer, this->start.x - x, this->start.y + y);
				SDL_RenderDrawPoint(this->renderer, this->start.x + y, this->start.y - x);
				SDL_RenderDrawPoint(this->renderer, this->start.x + y, this->start.y + x);
				SDL_RenderDrawPoint(this->renderer, this->start.x - y, this->start.y - x);
				SDL_RenderDrawPoint(this->renderer, this->start.x - y, this->start.y + x);

				if (error <= 0)
				{
					++y;
					error += ty;
					ty += 2;
				}

				if (error > 0)
				{
					--x;
					tx += 2;
					error += (tx - diameter);
				}
			}
		}
		else {
			cout << "ERR DRAWEVENT: SDL_SetRenderDrawColor failed" << endl;
			return false;
		}
		break;

	case TEXT:
		//load font file
		this->font = TTF_OpenFont(this->File.c_str(), this->textSize);
		if (this->font) {
			//create surface from file
			this->surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);

			if (this->surface) {
				//render texture from surface
				this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

				if (this->texture) {
					//copy rendered texture to render window
					int textW = 0;
					int textH = 0;
					SDL_QueryTexture(this->texture, NULL, NULL, &textW, &textH);
					SDL_Rect dest = { this->start.x, this->start.y,textW,textH };
					SDL_RenderCopy(this->renderer, this->texture, NULL, &dest);

					return true;
				}
				else {
					cout << "ERR DRAWEVENT TEXT: SDL_CreateTextureFromSurface failed" << endl;
					return false;
				}
			}
			else {
				cout << "ERR DRAWEVENT TEXT: TTF_RenderText_Solid failed" << endl;
				return false;
			}
		}
		else {
			cout << "ERR DRAWEVENT TEXT: TTF_OpenFont failed" << endl;
			return false;
		}
		break;

	default:
		cout << "ERR DRAWEVENT: failed to resolve switch case" << endl;
		return false;
	}
}