#include "TextBox.h"

//update buffer
void TextBox::updateBuffer(string nBuffer) {
	this->buffer = nBuffer;
}

//draw textbox
void TextBox::draw() {

	DrawEvent backGround(Type::FILLRECT, this->bgColor, this->renderer->getRenderer(), this->location);
	DrawEvent border(Type::RECT, this->frameColor, this->renderer->getRenderer(), location);
	renderer->addDrawEvent(backGround);
	renderer->addDrawEvent(border);

	this->row = 1;
	this->column = 1;
	int i;

	for (i = 0; i < buffer.size(); i++) {

		if (buffer[i] == '~') {
			row += 1;
			column = 1;
		}

		string sub(1,buffer[i]);
		SDL_Point textPos = { this->location.x + (this->column * this->fontSize), this->location.y + (this->row * this->fontSize) };
		DrawEvent text(Type::TEXT, this->renderer->getRenderer(), textPos, sub, this->fontSize, this->atlas);
		renderer->addDrawEvent(text);

		column += 1;

		//check for out of bounds
		if (this->column * this->fontSize > this->location.w - fontSize) {
			row += 1;
			column = 1;
		}

	}

}

//increase row (for when enter is pressed)
void TextBox::incRow() {
	this->buffer += '~';
}