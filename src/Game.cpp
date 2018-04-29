#include "Game.h"

Game::Game() : quit( false ), thisTime( 0 ), time( 0 ), oldTime( 0 )
{

}

void Game::Init()
{
	states.Init();
	states.SwitchTo( "mainmenu" );

	scores.Init();
	spawnAreas.Init();

	player.Init();

    for( auto &enemy : enemies )
    {
        enemy.Init();
    }
}

void Game::Update()
{
	auto state = states.CurrentState();

	state->HandleEvents();
	state->Update( time );
}

void Game::NewGame()
{
	states.SwitchTo( "newgame" );
	auto state = states.CurrentState();

	state->Restart();

	scores.Reset();
}

Game game;
