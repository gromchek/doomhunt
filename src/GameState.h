#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "RenderView.h"
#include <string>

class GameState
{
private:
	std::string name;

public:
	GameState() = delete;
	explicit GameState( const std::string &stateName );
	virtual ~GameState() = default;

	virtual void Init();
	virtual void HandleEvents();
	virtual void Update( const unsigned int dt );
	virtual void Restart();

	virtual void Draw();

	const RenderView &GetRenderView() const;
	const std::string &GetName() const;

protected:
	RenderView renderView;
};

inline GameState::GameState( const std::string &stateName ) : name( stateName )
{
}

inline void GameState::Init()
{
}

inline void GameState::HandleEvents()
{
}

inline void GameState::Update( const unsigned int /*dt*/ )
{
}

inline void GameState::Restart()
{
}

inline void GameState::Draw()
{
}

inline const RenderView &GameState::GetRenderView() const
{
	return renderView;
}

inline const std::string &GameState::GetName() const
{
	return name;
}

#endif // GAMESTATE_H
