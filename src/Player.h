#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include <SFML/Graphics/Sprite.hpp>

const int MAX_HEALTH = 5;

class Player
{
private:
	sf::Sprite model;

	enum State
	{
		STAND = 0,
		ATTACK,
		RELOAD,
		COUNT
	};

	Animation anims[COUNT];
	State state;

	int health;

public:
	Player() = default;
	~Player() = default;

	void Init();

	void Spawn();

	void Attack();
	bool isAttacking() const;

	int GetHealth() const;
	void Harm();

	void UpdateVisual();

	void Update( const unsigned int dt );

	sf::Sprite &GetRenderModel();
};

inline void Player::Spawn()
{
	state = STAND;

    for( auto &anim : anims )
    {
        anim.Reset();
    }

	health = MAX_HEALTH;
}

inline void Player::Attack()
{
	if( state == STAND )
	{
		state = ATTACK;
	}
}

inline bool Player::isAttacking() const
{
	return state == ATTACK;
}

inline int Player::GetHealth() const
{
	return health;
}

inline sf::Sprite &Player::GetRenderModel()
{
	return model;
}

#endif // PLAYER_H
