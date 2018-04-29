#ifndef GAMESTATE_MAINMENU_H
#define GAMESTATE_MAINMENU_H

#include "GameState.h"
#include "MainMenu.h"

#include <SFML/Graphics/Sprite.hpp>

class GameState_MainMenu final : public GameState
{
private:
	sf::Sprite gamelogo;

	MainMenu menu;

public:
	GameState_MainMenu() = delete;
	explicit GameState_MainMenu( const std::string &stateName );
	virtual ~GameState_MainMenu() = default;

	virtual void Init() override;
	virtual void HandleEvents() override;

	virtual void Draw() override;
};

inline GameState_MainMenu::GameState_MainMenu( const std::string &stateName ) : GameState( stateName )
{
}

#endif // GAMESTATE_MAINMENU_H
