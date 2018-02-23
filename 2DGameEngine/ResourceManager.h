#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>
#include <memory>
#include "Definitions.h"

class ResourceManager
{
public:
	void AddTexture( const ecs::Texture rID, const std::string& filename );
	sf::Texture& GetTexture( const ecs::Texture rID );
	void AddFont( const ecs::Font rID, const std::string& filename );
	sf::Font& GetFont( const ecs::Font rID );
	void AddSoundBuffer( const ecs::Sound rID, const std::string& filename );
	sf::SoundBuffer& GetSoundBuffer( const ecs::Sound rID );
	void AddMusic( const ecs::Music rID, const std::string& filename );
	sf::Music& GetMusic( const ecs::Music rID );
private:
	std::map<ecs::Texture, sf::Texture> textures;
	std::map<ecs::Font, sf::Font> fonts;
	std::map<ecs::Sound, sf::SoundBuffer> soundBuffers;
	std::map<ecs::Music, std::unique_ptr<sf::Music> > music;
};

