#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <cassert>

struct AnimFrame
{
	sf::IntRect rect;
	unsigned int time;
};

class Animation
{
private:
	std::vector<AnimFrame> frames;
	unsigned int time;
	unsigned int currFrame;

	unsigned int texIndex;

	bool finished;

public:
	Animation();
	~Animation() = default;

	void AddFrame( const AnimFrame &frame );
	void Update( const unsigned int dt );

	const sf::IntRect &CurrentFrame();

	void SetTextureIndex( const unsigned int index );
	unsigned int GetTextureIndex() const;

	bool isFinished() const;
	void Reset();
};


inline Animation::Animation() : time( 0 ), currFrame( 0 ), texIndex( -1 ), finished( false )
{
}

inline void Animation::AddFrame( const AnimFrame &frame )
{
	frames.emplace_back( frame );
}

inline const sf::IntRect &Animation::CurrentFrame()
{
	assert( currFrame < frames.size() );
	return frames[currFrame].rect;
}

inline void Animation::SetTextureIndex( const unsigned int index )
{
	texIndex = index;
}

inline unsigned int Animation::GetTextureIndex() const
{
	return texIndex;
}

inline bool Animation::isFinished() const
{
	return finished;
}

inline void Animation::Reset()
{
	time = 0;
	currFrame = 0;
	finished = false;
}

#endif // ANIMATION_H
