#include "GameState_GamePlay.h"
#include "Render.h"
#include "Game.h"
#include "UserInput.h"
#include "Common.h"
#include "TextureManager.h"

#include <algorithm>
#include <cmath>


const int ENEMY_SPAWN_TIME = 1000;

const sf::IntRect grass{ 0, 0, 507, 246 };
const sf::IntRect tree{ 510, 0, 186, 334 };
const sf::IntRect bush{ 699, 0, 88, 114 };

void GameState_GamePlay::Init()
{
	const auto &size = render.GetSize();

	renderView.camera.reset( { 0.0f, 0.0f, float( size.x ), float( size.y ) } );
	renderView.camera.setViewport( { 0.0f, 0.0f, 1.0f, 1.0f } );

    renderView.clearColor = DEFAULT_CLEAR_COLOR;

	crosshair.setTexture( texManager.GetTextureByName( "crosshair" ) );
	crosshair.scale( { 1.2f, 1.2f } );

	world.setTexture( texManager.GetTextureByName( "bg" ) );

	spawnTime = ENEMY_SPAWN_TIME;
}

void GameState_GamePlay::HandleEvents()
{
	if( userInput.GetKeyState( sf::Keyboard::Escape ) )
	{
		game.states.SwitchTo( "mainmenu" );
	}

	if( userInput.GetKeyState( sf::Keyboard::Space ) || userInput.GetMouseState( sf::Mouse::Button::Left ) )
	{
		game.player.Attack();
	}
}

void GameState_GamePlay::Update( const unsigned int dt )
{
	game.player.Update( dt );

	for( int i = 0; i < MAX_ENEMIES; i++ )
	{
		game.enemies[i].Update( dt );
	}

	if( game.player.GetHealth() <= 0 )
	{
        game.states.SwitchTo( "gameover" );
	}

	SpawnEnemy( dt );

	std::sort( game.enemies, game.enemies + MAX_ENEMIES,
			   []( Enemy &a, Enemy &b ) { return a.GetFactor() < b.GetFactor(); } );

	if( game.player.isAttacking() )
	{
		for( int i = 0; i < MAX_ENEMIES; i++ )
		{
			auto &enemy = game.enemies[i];

			if( enemy.isHidden() )
			{
				continue;
			}

			if( !enemy.isAttacking() )
			{
				continue;
			}

			const auto &model = enemy.GetRenderModel();

			if( model.getGlobalBounds().intersects( crosshair.getGlobalBounds() ) )
			{
				enemy.Kill();
				game.scores.AddScores();
				break;
			}
		}
	}

	const auto &camSize = GetRenderView().camera.getSize();

	int mouseX = 0;
	int mouseY = 0;

	userInput.GetMousePosition( mouseX, mouseY );

	auto &model = game.player.GetRenderModel();

	sf::Vector2f newPlayerPos;
	newPlayerPos.x = float( mouseX ) - model.getGlobalBounds().width / 2.0f + 8.0f;
    newPlayerPos.y = camSize.y - model.getGlobalBounds().height + 18.0f; //fullsreen little hack
	newPlayerPos.y -= CalcBobbing( mouseX );
	model.setPosition( newPlayerPos );

	sf::Vector2f newCrosshairPos;
	newCrosshairPos.x = float( mouseX ) - crosshair.getLocalBounds().width / 2.0f;
	newCrosshairPos.y = float( mouseY ) - crosshair.getLocalBounds().height / 2.0f;
	crosshair.setPosition( newCrosshairPos );
}

void GameState_GamePlay::Restart()
{
	const auto &camSize = GetRenderView().camera.getSize();

	game.player.Spawn();
	auto &playerModel = game.player.GetRenderModel();
    playerModel.setPosition( { camSize.x / 2.0f, camSize.y - playerModel.getGlobalBounds().height } );

	spawnTime = ENEMY_SPAWN_TIME;

    for( auto &enemy : game.enemies )
    {
        enemy.Hide();
    }
}

void GameState_GamePlay::Draw()
{
	DrawWorld();

    for( auto &enemy : game.enemies )
    {
        if( !enemy.isHidden() )
        {
            render.Draw( enemy.GetRenderModel() );
        }
    }

	render.Draw( game.player.GetRenderModel() );
	render.Draw( crosshair );

	DrawUI();
}

float GameState_GamePlay::CalcBobbing( const int mouseX )
{
	float bob = std::sin( bobOffsetY ) * R_GUN_BOB_Y;

	if( bobOffsetY > PI2 )
	{
        bobOffsetY = 0.0f;
	}

	if( std::abs( lastMouseX - mouseX ) > 1 )
	{
        bobOffsetY += 0.095f;
		lastMouseX = mouseX;
	}

	return bob;
}

void GameState_GamePlay::DrawUI()
{
	const auto &camSize = GetRenderView().camera.getSize();

	sf::Text text;
	text.setCharacterSize( 32 );
	text.setFillColor( sf::Color( 255, 215, 0 ) );
	text.setPosition( { 16.0f, 16.0f } );

	text.setString( "Health " + std::to_string( game.player.GetHealth() ) );
	render.DrawText( text );

	text.setPosition( { 16.0f, camSize.y - 96.0f } );

	text.setString( "Score " + std::to_string( game.scores.GetScores() ) );
	render.DrawText( text );
}

void GameState_GamePlay::DrawWorld()
{
	const auto &camSize = GetRenderView().camera.getSize();

	world.setTextureRect( tree );
	world.setPosition( { float( tree.width ), camSize.y - float( tree.height * 1.5f ) } );

	render.Draw( world );

	world.setTextureRect( bush );
	world.setPosition( { camSize.x - float( bush.width * 2.0f ), camSize.y - float( bush.height * 2.5f ) } );

	render.Draw( world );


	world.setTextureRect( grass );
	world.setPosition( { 0.0f, camSize.y - float( grass.height ) } );

	render.Draw( world );

	while( true )
	{
		if( world.getPosition().x > camSize.x )
		{
			break;
		}

		world.move( { float( grass.width ), 0.0f } );

		render.Draw( world );
	}
}

void GameState_GamePlay::SpawnEnemy( const unsigned int dt )
{
	if( spawnTime > 0 )
	{
		spawnTime -= dt;
		return;
	}

    for( auto &enemy : game.enemies )
    {
        if( enemy.isHidden() )
        {
            enemy.Spawn();
            spawnTime = ENEMY_SPAWN_TIME;

            break;
        }
    }
}
