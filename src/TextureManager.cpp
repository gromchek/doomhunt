#include <iostream>

#include "Common.h"
#include "TextureManager.h"


void TextureManager::Init()
{
	sf::Image defaultImage;
    defaultImage.create( 64, 64, { 0, 255, 0 } );

	defaultTex.handle.loadFromImage( defaultImage );
	defaultTex.handle.setRepeated( true );
	defaultTex.name = "_default";
}

unsigned int TextureManager::LoadTexture( const std::string &name, const bool smooth, const bool repeat )
{
	unsigned int idx = GetTextureIndex( name );

	if( idx != INVALID_TEXTURE )
	{
		return idx;
	}

	textures.push_back( Texture( name ) );

	if( !textures.back().handle.loadFromFile( baseDir + name + ".png" ) )
	{
		std::cout << "TextureManager: Error load texture: " << name << '\n';
		return INVALID_TEXTURE;
	}

	textures.back().handle.setSmooth( smooth );
	textures.back().handle.setRepeated( repeat );

	idx = textures.size() - 1;

	return idx;
}

const sf::Texture &TextureManager::GetTextureByName( const std::string &name ) const
{
	for( const auto &texture : textures )
	{
		if( texture.name == name )
		{
			return texture.handle;
		}
	}

	return defaultTex.handle;
}

const sf::Texture &TextureManager::GetTextureByIndex( const unsigned int index ) const
{
    if( index >= textures.size() )
    {
        return defaultTex.handle;
    }

	return textures[index].handle;
}

unsigned int TextureManager::GetTextureIndex( const std::string &name ) const
{
	for( auto i = 0u; i < textures.size(); i++ )
	{
		if( textures[i].name == name )
		{
			return i;
		}
	}

	return INVALID_TEXTURE;
}

TextureManager texManager;
