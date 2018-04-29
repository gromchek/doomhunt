#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>

#include <vector>
#include <string>


class TextureManager
{
private:
	struct Texture
	{
		std::string name;
		sf::Texture handle;

		Texture() = default;
		explicit Texture( const std::string &textureName ) : name( textureName )
		{
		}
	};

	Texture defaultTex;
	std::vector<Texture> textures;

public:
	const unsigned int INVALID_TEXTURE = 0xFFFFFFFF;

	TextureManager() = default;
	~TextureManager() = default;

	void Init();

	unsigned int LoadTexture( const std::string &name, const bool smooth = true, const bool repeat = true );

	const sf::Texture &GetTextureByName( const std::string &name ) const;
	const sf::Texture &GetTextureByIndex( const unsigned int index ) const;

	unsigned int GetTextureIndex( const std::string &name ) const;
};

extern TextureManager texManager;

#endif // TEXTUREMANAGER_H
