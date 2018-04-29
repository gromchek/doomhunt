#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "GameState.h"
#include <vector>
#include <string>
#include <memory>

using GameStatePtr = std::shared_ptr<GameState>;

class GameStateManager
{
private:
    std::vector<GameStatePtr> states;
    GameStatePtr currentState;

public:
    GameStateManager() = default;
    ~GameStateManager() = default;

    void Init();

    void SwitchTo( const std::string &stateName );

    GameStatePtr CurrentState() const;
};


#endif // GAMESTATEMANAGER_H
