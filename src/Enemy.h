#ifndef ENEMY_H
#define ENEMY_H

#include "Animation.h"
#include <SFML/Graphics/Sprite.hpp>


class Enemy
{
private:
	sf::Sprite model;

	enum State
	{
		STAND = 0,
		CHASE,
		DYING,
		COUNT
	};

	State state;

	Animation anims[COUNT];

	float frac;

	int thinktime;
	bool hidden;

	sf::Vector2f tarPos;

	void UpdateStand( const unsigned int dt );
	void UpdateChase( const unsigned int dt );
	void UpdateDying( const unsigned int dt );

public:
	Enemy();
	~Enemy() = default;

	void Init();

	void Spawn();

	void Kill();

	bool isHidden() const;
	void Hide();
	void Show();

	void Attack();
	bool isAttacking() const;

	float GetFactor() const;

	void UpdateVisual();

	void Update( const unsigned int dt );

	sf::Sprite &GetRenderModel();
};

inline Enemy::Enemy() : state( STAND )
{
	Hide();
}

inline void Enemy::Kill()
{
	if( state == CHASE )
	{
		state = DYING;
	}
}

inline void Enemy::Hide()
{
	hidden = true;
}

inline void Enemy::Show()
{
	hidden = false;
}

inline bool Enemy::isHidden() const
{
	return hidden;
}

inline void Enemy::Attack()
{
	if( state == STAND )
	{
		state = CHASE;
	}
}

inline bool Enemy::isAttacking() const
{
	return state == CHASE;
}

inline float Enemy::GetFactor() const
{
	return frac;
}

inline sf::Sprite &Enemy::GetRenderModel()
{
	return model;
}

#endif // ENEMY_H
