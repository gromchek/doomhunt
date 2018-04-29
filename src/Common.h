#ifndef COMMON_H
#define COMMON_H

#include <string>

const bool R_FULLSCREEN = true;
const int R_MAX_FPS = 60;

const int R_WIDTH = 1280;
const int R_HEIGHT = 1024;

const float R_GUN_BOB_Y = 17.0f;

const float PI2 = 3.1415926f * 2.0f;

const std::string baseDir( "base//" );
const std::string scoreFile( "score.txt" );

template <typename T, size_t N>
size_t countof( T const ( &array )[N] )
{
	return N;
}

bool isNumber( const std::string &str );

unsigned long HashString( const std::string &str );

#endif // COMMON_H
