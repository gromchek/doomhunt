#ifndef GAME_H
#define GAME_H

#include "GameStateManager.h"
#include "Scores.h"
#include "SpawnAreas.h"

#include "Player.h"
#include "Enemy.h"

const int MAX_ENEMIES = 8;

class Game
{
private:
	bool quit;

public:
	int thisTime;
	int time;
	int oldTime;

	GameStateManager states;
	Leaderboard scores;
	SpawnAreas spawnAreas;

	Player player;
	Enemy enemies[MAX_ENEMIES];

    Game();
	~Game() = default;

	void Init();

	void Update();

	void NewGame();
	void QuitGame();

	bool Closing() const;
};

inline void Game::QuitGame()
{
	quit = true;
}

inline bool Game::Closing() const
{
	return quit;
}

extern Game game;

#endif // GAME_H
