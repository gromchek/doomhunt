#include "SpawnAreas.h"

#include "Common.h"
#include "Rnd.h"

void SpawnAreas::Init()
{
	for( int x = 1; x < int( R_WIDTH / 64.0f ); x += 3 )
	{
		for( int y = 1; y < int( R_HEIGHT / 2.0f / 64.0f ); y += 2 )
		{
			areas.push_back( { x * 64.0f, y * 64.0f } );
		}
	}
}

Area SpawnAreas::GetRandomSpawnPoint() const
{
	const int idx = Rnd_GetInt( 0, areas.size() - 1 );

	return areas[idx];
}
