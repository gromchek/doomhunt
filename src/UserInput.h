#ifndef USERINPUT_H
#define USERINPUT_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class UserInput
{
private:
	int keyState[512];

	int mouseX;
	int mouseY;

	bool anyKey;

public:
	UserInput() = default;
	~UserInput() = default;

	void ReleaseAllKey();

	void SetMouseKey( const int key, const bool val );
	void SetKey( const int key, const bool val );
	void SetMousePosition( const int x, const int y );

	void GetMousePosition( int &x, int &y ) const;
	bool GetMouseState( const int key ) const;
	bool GetKeyState( const int key ) const;

	bool AnyKeyPressed() const;
};

inline bool UserInput::AnyKeyPressed() const
{
	return anyKey;
}

extern UserInput userInput;

#endif // USERINPUT_H
