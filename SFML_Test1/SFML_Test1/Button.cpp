#include"Button.h"

Button::Button()
{

}

void Button::setButtonTexture(sf::Texture *original, sf::Texture *focus)
{
	texture = original;
	texture_focus = focus;
}

bool Button::isCursor_on_button(const sf::Vector2i mouseposition)
{
	return mouseposition.x > this->getPosition().x &&
		mouseposition.y > this->getPosition().y &&
		mouseposition.x < (this->getPosition().x + this->getSize().x) &&
		mouseposition.y < (this->getPosition().y + this->getSize().y);
}

void Button::change_texture_to_normal()
{
	this->setTexture(texture);
}

void Button::change_texture_to_focus()
{
	this->setTexture(texture_focus);
}

