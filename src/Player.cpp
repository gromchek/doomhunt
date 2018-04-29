#include "Player.h"
#include "Common.h"
#include "TextureManager.h"

#include "Render.h"

#include <SFML/Graphics/Rect.hpp>

const int ATTACK_TIME_ANIM = 70;
const int RELOAD_TIME_ANIM = 40;

const sf::IntRect PKSFrames[] =
{
    { 0, 0, 118, 149 },
    { 122, 0, 118, 149 },
    { 245, 0, 118, 149 },
    { 367, 0, 73, 149 },
    { 440, 0, 77, 149 },
    { 520, 0, 81, 149 },
    { 602, 0, 86, 149 },
    { 690, 0, 87, 149 },
    { 777, 0, 87, 149 },
    { 864, 0, 104, 149 },
    { 968, 0, 115, 149 },
    { 864, 0, 104, 149 },
    { 777, 0, 87, 149 },
    { 690, 0, 87, 149 },
    { 602, 0, 86, 149 },
    { 520, 0, 81, 149 },
    { 440, 0, 77, 149 },
    { 367, 0, 73, 149 }
};

void Player::Init()
{
	for( auto &anim : anims )
	{
		anim.SetTextureIndex( texManager.GetTextureIndex( "pks" ) );
	}

	anims[STAND].AddFrame( { PKSFrames[0], 0 } );

	anims[ATTACK].AddFrame( { PKSFrames[1], ATTACK_TIME_ANIM } );
	anims[ATTACK].AddFrame( { PKSFrames[2], ATTACK_TIME_ANIM } );

	for( auto i = 3u; i < countof( PKSFrames ); i++ )
	{
		anims[RELOAD].AddFrame( { PKSFrames[i], RELOAD_TIME_ANIM } );
	}

	model.setTexture( texManager.GetTextureByIndex( anims[STAND].GetTextureIndex() ) ); // one texture - all frames
	model.setTextureRect( anims[state].CurrentFrame() );

	model.scale( { 2.5f, 2.5f } );

	health = MAX_HEALTH;
}

void Player::Harm()
{
	health -= 1;
}

void Player::UpdateVisual()
{
	model.setTextureRect( anims[state].CurrentFrame() );
}

void Player::Update( const unsigned int dt )
{
	anims[state].Update( dt );

	if( anims[ATTACK].isFinished() )
	{
		state = RELOAD;
		anims[ATTACK].Reset();
	}

	if( anims[RELOAD].isFinished() )
	{
		state = STAND;
		anims[RELOAD].Reset();
	}

	UpdateVisual();
}
