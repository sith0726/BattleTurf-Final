#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape
{
private:
	//the pointers to texture
	sf::Texture *texture;
	sf::Texture *texture_focus;
public:
	Button();
	//set the texture of button(original texture, and focus texture)
	void setButtonTexture(sf::Texture *texture, sf::Texture *texture_focus);
	//is cursor on the button?
	bool isCursor_on_button(const sf::Vector2i);
	//change texture to normal
	void change_texture_to_normal();
	//change texture to focus
	void change_texture_to_focus();
};