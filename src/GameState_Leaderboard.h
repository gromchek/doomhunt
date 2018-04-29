#ifndef GAMESTATE_LEADERBOARD_H
#define GAMESTATE_LEADERBOARD_H

#include "GameState.h"

class GameState_Leaderboard final : public GameState
{
private:
public:
	GameState_Leaderboard() = delete;
	explicit GameState_Leaderboard( const std::string &stateName );
	virtual ~GameState_Leaderboard() = default;

	virtual void Init() override;
	virtual void HandleEvents() override;

	virtual void Draw() override;
};

inline GameState_Leaderboard::GameState_Leaderboard( const std::string &stateName ) : GameState( stateName )
{
}

#endif // GAMESTATE_LEADERBOARD_H
