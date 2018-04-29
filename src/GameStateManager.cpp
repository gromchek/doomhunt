#include "GameStateManager.h"

#include "GameState_GameOver.h"
#include "GameState_Gameplay.h"
#include "GameState_Leaderboard.h"
#include "GameState_MainMenu.h"

void GameStateManager::Init()
{
	states.emplace_back( std::make_shared<GameState_MainMenu>( "mainmenu" ) );
	states.emplace_back( std::make_shared<GameState_GameOver>( "gameover" ) );
	states.emplace_back( std::make_shared<GameState_GamePlay>( "newgame" ) );
	states.emplace_back( std::make_shared<GameState_Leaderboard>( "scores" ) );

	for( auto state : states )
	{
		state->Init();
	}

	currentState = states[0];
}

void GameStateManager::SwitchTo( const std::string &stateName )
{
	if( currentState->GetName() == stateName )
	{
		return;
	}

	for( const auto &state : states )
	{
		if( state->GetName() == stateName )
		{
			currentState = state;
			break;
		}
	}
}

GameStatePtr GameStateManager::CurrentState() const
{
	return currentState;
}
