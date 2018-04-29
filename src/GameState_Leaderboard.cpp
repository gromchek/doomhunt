#include "GameState_Leaderboard.h"
#include "Render.h"
#include "Game.h"
#include "UserInput.h"

const sf::Color SCORE_PRIZE_COLORS[3] =
{
    { 255, 215, 0 },
    { 225, 225, 225 },
    { 177, 86, 15 }
};

void GameState_Leaderboard::Init()
{
	const auto &size = render.GetSize();

	renderView.camera.reset( { 0.0f, 0.0f, float( size.x ), float( size.y ) } );
	renderView.camera.setViewport( { 0.125f, 0.125f, 0.75f, 0.75f } );

    renderView.clearColor = DEFAULT_CLEAR_COLOR;
}

void GameState_Leaderboard::HandleEvents()
{
	if( userInput.AnyKeyPressed() )
	{
		game.states.SwitchTo( "mainmenu" );
	}
}

void GameState_Leaderboard::Draw()
{
	const auto &camera = GetRenderView().camera;

	sf::Text text;
	text.setCharacterSize( 64 );
	text.setFillColor( sf::Color( 0, 255, 70 ) );
	text.setPosition( { camera.getSize().x / 3.5f, 0.0f } );

	text.setString( "View Scores" );
	render.DrawText( text );

	const auto &records = game.scores.GetRecords();

	const float indent = 128.0f;
	unsigned int place = 0;

	text.setCharacterSize( 48 );
	text.setFillColor( sf::Color::White );

	for( const auto &record : records )
	{
		text.setPosition( { camera.getSize().x / 4.5f, camera.getSize().y / 5.0f } );

		text.setFillColor( SCORE_PRIZE_COLORS[place] );

		text.move( { 0.0f, indent * place } );

		text.setString( std::to_string( place + 1 ) );

		render.DrawText( text );

		text.setString( record.name );
		text.move( { indent * 1.5f, 0.0f } );

		render.DrawText( text );

		text.setString( std::to_string( record.score ) );
		text.move( { indent * 3.0f, 0.0f } );

		render.DrawText( text );

		place += 1;
	}
}
