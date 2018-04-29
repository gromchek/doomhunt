#ifndef SPAWNAREAS_H
#define SPAWNAREAS_H

#include <SFML/System/Vector2.hpp>
#include <vector>

using Area = sf::Vector2f;

class SpawnAreas
{
private:
	std::vector<Area> areas;

public:
	SpawnAreas() = default;
	~SpawnAreas() = default;

	void Init();

	Area GetRandomSpawnPoint() const;
};


#endif // SPAWNAREAS_H
