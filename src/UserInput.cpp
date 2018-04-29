#include "UserInput.h"

#include <cstring>

void UserInput::ReleaseAllKey()
{
	memset( keyState, 0, sizeof( keyState ) );
	anyKey = false;
}

void UserInput::SetMouseKey( const int key, const bool val )
{
	const int mkey = sf::Keyboard::KeyCount + key + 1;
	SetKey( mkey, val );
	anyKey = false;
}

void UserInput::SetKey( const int key, const bool val )
{
	keyState[key] = val;
	anyKey = val;
}

void UserInput::SetMousePosition( const int x, const int y )
{
	mouseX = x;
	mouseY = y;
}

void UserInput::GetMousePosition( int &x, int &y ) const
{
	x = mouseX;
	y = mouseY;
}

bool UserInput::GetMouseState( const int key ) const
{
	const int mkey = sf::Keyboard::KeyCount + key + 1;
	return GetKeyState( mkey );
}

bool UserInput::GetKeyState( const int key ) const
{
	return keyState[key];
}

UserInput userInput;
