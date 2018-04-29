#include <cmath>

#include "Common.h"
#include "TextureManager.h"
#include "Enemy.h"

#include "Game.h"

sf::Vector2f Lerp( const sf::Vector2f &a, const sf::Vector2f &b, const float t )
{
	sf::Vector2f v;

	v.x = a.x + t * ( b.x - a.x );
	v.y = a.y + t * ( b.y - a.y );

	return v;
}

const int THINK_TIME = 4500;

const float BASE_SCALE_FACTOR = 2.0f;

const int CHASE_TIME_ANIM = 180;
const int STAND_TIME_ANIM = 140;
const int DYING_TIME_ANIM = 80;

const float CHASE_SCALING_FACTOR = 1.1f;
const float CHASE_MAX_SCALE = 18.0f;


const sf::IntRect FRAME_ANIMS[] =
{
    { 0, 0, 64, 64 },
    { 0, 64, 64, 64 },

    { 64, 0, 64, 64 },
    { 64, 64, 64, 64 },

    { 128, 0, 64, 64 },
    { 192, 0, 64, 64 },
    { 256, 0, 64, 64 },
    { 320, 0, 64, 64 },
    { 384, 0, 64, 64 },
    { 448, 0, 64, 64 }
};

void Enemy::UpdateStand( const unsigned int dt )
{
	if( state != STAND )
	{
		return;
	}

	if( thinktime < 0 )
	{
		Attack();
		return;
	}

	const auto newPos = Lerp( model.getPosition(), tarPos, dt * 0.0015f );

	model.setPosition( newPos );

	if( std::abs( tarPos.x - newPos.x ) <= 8.0f || std::abs( tarPos.y - newPos.y ) <= 8.0f )
	{
		tarPos = game.spawnAreas.GetRandomSpawnPoint();
	}
}

void Enemy::UpdateChase( const unsigned int /*dt*/ )
{
	if( state != CHASE )
	{
		return;
	}

	model.scale( { CHASE_SCALING_FACTOR, CHASE_SCALING_FACTOR } );

	frac = std::fabs( model.getScale().x );

	if( frac >= CHASE_MAX_SCALE )
	{
		game.player.Harm();
		state = DYING;
	}
}

void Enemy::UpdateDying( const unsigned int /*dt*/ )
{
	if( anims[DYING].isFinished() )
	{
		Hide();
	}
}

void Enemy::Init()
{
	for( auto &anim : anims )
	{
		anim.SetTextureIndex( texManager.GetTextureIndex( "soulsheet" ) );
	}

	anims[CHASE].AddFrame( { FRAME_ANIMS[0], CHASE_TIME_ANIM } );
	anims[CHASE].AddFrame( { FRAME_ANIMS[1], CHASE_TIME_ANIM } );

	anims[STAND].AddFrame( { FRAME_ANIMS[2], STAND_TIME_ANIM } );
	anims[STAND].AddFrame( { FRAME_ANIMS[3], STAND_TIME_ANIM } );

	for( auto i = 4u; i < countof( FRAME_ANIMS ); i++ )
	{
		anims[DYING].AddFrame( { FRAME_ANIMS[i], DYING_TIME_ANIM } );
	}

	model.setTexture( texManager.GetTextureByName( "soulsheet" ) );
	model.setTextureRect( anims[state].CurrentFrame() );
	model.setOrigin( { model.getTextureRect().width / 2.0f, model.getTextureRect().height / 2.0f } );
}


void Enemy::Spawn()
{
	state = STAND;

	thinktime = THINK_TIME;

	frac = BASE_SCALE_FACTOR;

	model.setScale( { BASE_SCALE_FACTOR, BASE_SCALE_FACTOR } );
	model.setRotation( 0.0f );

    for( auto &anim : anims )
    {
        anim.Reset();
    }

	model.setPosition( game.spawnAreas.GetRandomSpawnPoint() );

	tarPos = game.spawnAreas.GetRandomSpawnPoint();

	Show();
}

void Enemy::Update( const unsigned int dt )
{
	if( isHidden() )
	{
		return;
	}

	thinktime -= dt;

	anims[state].Update( dt );

	UpdateStand( dt );
	UpdateChase( dt );
	UpdateDying( dt );

	UpdateVisual();
}

void Enemy::UpdateVisual()
{
	model.setTextureRect( anims[state].CurrentFrame() );

	if( ( tarPos.x - model.getPosition().x ) < 0.0f )
	{
		model.setScale( { -frac, frac } );
	}
	else
	{
		model.setScale( { frac, frac } );
	}

	model.setOrigin( { model.getTextureRect().width / 2.0f, model.getTextureRect().height / 2.0f } );
}
