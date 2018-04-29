#include "Common.h"
#include "Render.h"

#include <SFML/Graphics/Text.hpp>

void Render::InitView( sf::View &view, const sf::Vector2u &size )
{
	const auto &winSize = win->getSize();

	float dx = ( winSize.x - size.x ) / 2.0f;
	float dy = ( winSize.y - size.y ) / 2.0f;

	view.reset( { -dx, -dy, float( winSize.x ), float( winSize.y ) } );
}

void Render::Init( sf::RenderWindow &window )
{
	win = &window;
	InitView( fullScreen, win->getSize() );

	font.loadFromFile( baseDir + "font.ttf" );
}

void Render::Clear( const sf::Color &c )
{
	win->clear( c );
}

void Render::SwapBuffer()
{
	win->display();
}

void Render::SetRenderView( const sf::View &renderView )
{
	win->setView( renderView );
}

void Render::Draw( sf::Drawable &e )
{
	win->draw( e );
}

void Render::DrawText( sf::Text &text )
{
	text.setFont( font );
	win->draw( text );
}

Render render;
