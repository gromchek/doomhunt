#ifndef GAMESTATE_GAMEOVER_H
#define GAMESTATE_GAMEOVER_H

#include "GameState.h"

#include <SFML/Graphics/Sprite.hpp>

class GameState_GameOver final : public GameState
{
private:
	sf::Sprite overlogo;

public:
	GameState_GameOver() = delete;
	explicit GameState_GameOver( const std::string &stateName );
	virtual ~GameState_GameOver() = default;

	virtual void Init() override;
	virtual void HandleEvents() override;

	virtual void Draw() override;
};

inline GameState_GameOver::GameState_GameOver( const std::string &stateName ) : GameState( stateName )
{
}

#endif // GAMESTATE_GAMEOVER_H
