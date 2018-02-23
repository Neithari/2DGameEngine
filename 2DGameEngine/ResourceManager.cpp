#include "ResourceManager.h"

#include <cassert>
#include <iostream>

void ResourceManager::AddTexture( const ecs::Texture rID, const std::string& filename )
{
	// skip if a texture with the name already exists
	if( textures.find( rID ) == textures.end() )
	{
		sf::Texture texture;
		// if the file can not be loaded then load a default magenta texture and output to console
		if( !texture.loadFromFile( filename ) )
		{
			const unsigned int width = 100;
			const unsigned int height = 100;
			texture.create( width, height );
			sf::Image defaultTexture;
			defaultTexture.create( width, height, sf::Color::Magenta );
			texture.update( defaultTexture );

			std::cout << filename << " could not be loaded" << std::endl;
		}
		textures.emplace( rID, std::move( texture ) );
	}
}

sf::Texture& ResourceManager::GetTexture( const ecs::Texture rID )
{
	try
	{
		return textures.at( rID );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no texture with id: " << static_cast<ecs::ResID>( rID ) << std::endl;
		throw;
	}
}

void ResourceManager::AddFont( const ecs::Font rID, const std::string& filename )
{
	// assert triggers if a font with the name already exists
	assert( fonts.find( rID ) == fonts.end() );

	sf::Font font;
	if( !font.loadFromFile( filename ) )
	{
		throw std::runtime_error( filename + " could not be loaded" );
	}
	fonts.emplace( rID, std::move( font ) );
}

sf::Font& ResourceManager::GetFont( const ecs::Font rID )
{
	try
	{
		return fonts.at( rID );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no font with id: " << static_cast<ecs::ResID>( rID ) << std::endl;
		throw;
	}
}

void ResourceManager::AddSoundBuffer( const ecs::Sound rID, const std::string& filename )
{
	// assert triggers if a sound with the name already exists
	assert( soundBuffers.find( rID ) == soundBuffers.end() );

	sf::SoundBuffer soundBuffer;
	if( !soundBuffer.loadFromFile( filename ) )
	{
		throw std::runtime_error( filename + " could not be loaded" );
	}
	soundBuffers.emplace( rID, std::move( soundBuffer ) );
}

sf::SoundBuffer& ResourceManager::GetSoundBuffer( const ecs::Sound rID )
{
	try
	{
		return soundBuffers.at( rID );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no soundbuffer with id: " << static_cast<ecs::ResID>( rID ) << std::endl;
		throw;
	}
}

void ResourceManager::AddMusic( const ecs::Music rID, const std::string& filename )
{
	// assert triggers if a texture with the name already exists
	assert( music.find( rID ) == music.end() );

	auto pMusic = std::make_unique<sf::Music>();
	if( !pMusic->openFromFile( filename ) )
	{
		throw std::runtime_error( filename + " could not be loaded" );
	}
	music.emplace( rID, std::move( pMusic ) );
}

sf::Music& ResourceManager::GetMusic( const ecs::Music rID )
{
	try
	{
		return *music.at( rID );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no music with id: " << static_cast<ecs::ResID>( rID ) << std::endl;
		throw;
	}
}
