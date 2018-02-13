#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>
#include <memory>
class ResourceManager
{
public:
	void AddTexture( const std::string& name, const std::string& filename );
	sf::Texture& GetTexture( const std::string& name );
	void AddFont( const std::string& name, const std::string& filename );
	sf::Font& GetFont( const std::string& name );
	void AddSoundBuffer( const std::string& name, const std::string& filename );
	sf::SoundBuffer& GetSoundBuffer( const std::string& name );
	void AddMusic( const std::string& name, const std::string& filename );
	sf::Music& GetMusic( const std::string& name );
private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, std::unique_ptr<sf::Music> > music;
};

