#include "GameState_GameOver.h"
#include "Render.h"
#include "Game.h"
#include "UserInput.h"
#include "TextureManager.h"

const sf::Color YOUR_SCORE_COLOR{ 239, 239, 55 };

void GameState_GameOver::Init()
{
	const auto &size = render.GetSize();

	renderView.camera.reset( { 0.0f, 0.0f, float( size.x ), float( size.y ) } );
	renderView.camera.setViewport( { 0.1f, 0.125f, 0.75f, 0.75f } );

    renderView.clearColor = DEFAULT_CLEAR_COLOR;

	const auto &camSize = GetRenderView().camera.getSize();

	overlogo.setTexture( texManager.GetTextureByName( "gameover" ) );

	overlogo.setPosition( { 0.0f, 0.0f } );
	overlogo.scale( { 1.5f, 1.5f } );
	overlogo.move( ( camSize.x / 2.0f ) - overlogo.getGlobalBounds().width / 2.0f, 0.0f );
}

void GameState_GameOver::HandleEvents()
{
	if( userInput.AnyKeyPressed() )
	{
		game.states.SwitchTo( "mainmenu" );
	}
}

void GameState_GameOver::Draw()
{
	const auto &camSize = GetRenderView().camera.getSize();

	render.Draw( overlogo );

	sf::Text text;
	text.setString( "Your score " + std::to_string( game.scores.GetScores() ) );
	text.setCharacterSize( 64 );
    text.setFillColor( YOUR_SCORE_COLOR );

	text.setPosition( { camSize.x / 4.0f, overlogo.getGlobalBounds().height * 1.5f } );

	render.DrawText( text );
}
