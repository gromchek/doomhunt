#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "RenderView.h"


const sf::Color DEFAULT_CLEAR_COLOR{ 60, 180, 252 };

class Render
{
private:
	sf::RenderWindow *win;

	sf::Font font;
	sf::View fullScreen;

public:
	Render() = default;
	~Render() = default;

	void Init( sf::RenderWindow &window );

	void InitView( sf::View &view, const sf::Vector2u &size );

	void Clear( const sf::Color &c = { 0, 0, 0 } );
	void SwapBuffer();

	void SetRenderView( const sf::View &renderView );

	sf::Vector2u GetSize() const;

	void Draw( sf::Drawable &e );
	void DrawText( sf::Text &text );
};

inline sf::Vector2u Render::GetSize() const
{
	return win->getSize();
}

extern Render render;

#endif // RENDER_H
