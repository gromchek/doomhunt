#include <random>
#include <ctime>
#include "Rnd.h"

std::mt19937 engine;

int randBetween( const int min, const int max )
{
	return std::rand() % ( max - min + 1 ) + min;
}

void Rnd_Init()
{
	std::srand( unsigned( std::time( nullptr ) ) );

	unsigned int seed = randBetween( 0xFFF, 0xFFFFFF );

	engine.seed( seed );
}

int Rnd_GetInt( const int min, const int max )
{
	return std::uniform_int_distribution<int>( min, max )( engine );
}
