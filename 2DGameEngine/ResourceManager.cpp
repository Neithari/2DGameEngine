#include "ResourceManager.h"

#include <cassert>
#include <iostream>

void ResourceManager::AddTexture( const std::string& name, const std::string& filename )
{
	// skip if a texture with the name already exists
	if( textures.find( name ) == textures.end() )
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
		textures.emplace( name, std::move( texture ) );
	}
}

sf::Texture& ResourceManager::GetTexture( const std::string& name )
{
	try
	{
		return textures.at( name );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no texture with name: " << name << std::endl;
		throw;
	}
}

void ResourceManager::AddFont( const std::string& name, const std::string& filename )
{
	// assert triggers if a font with the name already exists
	assert( fonts.find( name ) == fonts.end() );

	sf::Font font;
	if( !font.loadFromFile( filename ) )
	{
		throw std::runtime_error( filename + " could not be loaded" );
	}
	fonts.emplace( name, std::move( font ) );
}

sf::Font& ResourceManager::GetFont( const std::string& name )
{
	try
	{
		return fonts.at( name );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no font with name: " << name << std::endl;
		throw;
	}
}

void ResourceManager::AddSoundBuffer( const std::string& name, const std::string& filename )
{
	// assert triggers if a sound with the name already exists
	assert( soundBuffers.find( name ) == soundBuffers.end() );

	sf::SoundBuffer soundBuffer;
	if( !soundBuffer.loadFromFile( filename ) )
	{
		throw std::runtime_error( filename + " could not be loaded" );
	}
	soundBuffers.emplace( name, std::move( soundBuffer ) );
}

sf::SoundBuffer& ResourceManager::GetSoundBuffer( const std::string& name )
{
	try
	{
		return soundBuffers.at( name );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no soundbuffer with name: " << name << std::endl;
		throw;
	}
}

void ResourceManager::AddMusic( const std::string& name, const std::string& filename )
{
	// assert triggers if a texture with the name already exists
	assert( music.find( name ) == music.end() );

	auto pMusic = std::make_unique<sf::Music>();
	if( !pMusic->openFromFile( filename ) )
	{
		throw std::runtime_error( filename + " could not be loaded" );
	}
	music.emplace( name, std::move( pMusic ) );
}

sf::Music& ResourceManager::GetMusic( const std::string& name )
{
	try
	{
		return *music.at( name );
	}
	catch( const std::out_of_range )
	{
		std::cout << "There is no music with name: " << name << std::endl;
		throw;
	}
}
