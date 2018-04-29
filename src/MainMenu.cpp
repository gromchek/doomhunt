#include "MainMenu.h"
#include "UserInput.h"
#include "Game.h"

void ItemNewGame::Action()
{
	game.NewGame();
}

void ItemViewscore::Action()
{
	game.states.SwitchTo( "scores" );
	game.scores.UpdateRecords();
}

void ItemQuitGame::Action()
{
	game.QuitGame();
}

void MainMenu::Init()
{
	items.emplace_back( std::make_shared<ItemNewGame>( "New Game" ) );
	items.emplace_back( std::make_shared<ItemViewscore>( "View Scores" ) );
	items.emplace_back( std::make_shared<ItemQuitGame>( "Quit Game" ) );

	currentItem = 0;

	items[currentItem]->Select();
}

const std::vector<MenuItemPtr> &MainMenu::GetItems() const
{
	return items;
}

void MainMenu::KeyInput()
{
	if( userInput.GetKeyState( sf::Keyboard::Up ) )
	{
		UpItem();
	}

	if( userInput.GetKeyState( sf::Keyboard::Down ) )
	{
		DownItem();
	}

	if( userInput.GetKeyState( sf::Keyboard::Return ) )
	{
		items[currentItem]->Action();
	}
}
