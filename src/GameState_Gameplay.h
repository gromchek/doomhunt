#ifndef GAMESTATE_GAMEPLAY_H
#define GAMESTATE_GAMEPLAY_H

#include "GameState.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class GameState_GamePlay final : public GameState
{
private:
	sf::Sprite crosshair;
	sf::Sprite world;

	int spawnTime;

	float bobOffsetY;
	int lastMouseX;

public:
	GameState_GamePlay() = delete;
	explicit GameState_GamePlay( const std::string &stateName );
	virtual ~GameState_GamePlay() = default;

	virtual void Init() override;
	virtual void HandleEvents() override;
	virtual void Update( const unsigned int dt ) override;
	virtual void Restart() override;

	virtual void Draw() override;

	float CalcBobbing( const int mouseX );

	void DrawUI();
	void DrawWorld();

	void SpawnEnemy( const unsigned int dt );
};

inline GameState_GamePlay::GameState_GamePlay( const std::string &stateName ) :
    GameState( stateName ),
    spawnTime( 0 ),
    bobOffsetY( 0.0f ),
    lastMouseX( 0 )
{
}

#endif // GAMESTATE_GAMEPLAY_H
