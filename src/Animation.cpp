#include "Animation.h"

void Animation::Update( const unsigned int dt )
{
	time += dt;

	if( frames[currFrame].time < time )
	{
		time = 0;
		currFrame += 1;

		if( currFrame >= frames.size() )
		{
			finished = true;

			currFrame %= frames.size();
		}
	}
}
