#include <format>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include "ResourceManager.h"
#include "ResourceManagerTypes.h"
#include "Sprite.h"
#include "AnimationData.h"

using json = nlohmann::json;

ResourceManager::~ResourceManager()
{
	unloadAssets();
}

SDL_Texture* ResourceManager::loadTexture( const std::string& imagePath )
{
	SDL_Texture* texture = IMG_LoadTexture( m_renderer, imagePath.c_str() );

	if ( !texture )
	{
		std::string message = std::format( "Failed to load texture '{}': {}", imagePath, SDL_GetError() );
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		return nullptr;
	}

	SDL_SetTextureScaleMode( texture, SDL_SCALEMODE_NEAREST );

	return texture;
}

void ResourceManager::loadSprite( const std::string& spriteResourceId, const std::string& imagePath )
{
	if ( m_spriteResources.contains( spriteResourceId ) )
	{
		std::string message = std::format( "A sprite resource with the ID {} already exists. All sprite resource IDs must be unique.", spriteResourceId );
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr);
		return;
	}

	SDL_Texture* texture = this->loadTexture( imagePath );

	if ( texture )
	{
		auto resource = std::make_unique<SpriteResource>();
		resource->texture.reset( texture );

		// Default frame = full texture
		float w, h;
		SDL_GetTextureSize( texture, &w, &h );
		resource->frames["default"] = { SDL_FRect{ 0, 0, w, h } };

		m_spriteResources[spriteResourceId] = std::move( resource );
	}
}

void ResourceManager::loadSpriteSheet( const std::string& spriteResourceId, const std::string& imagePath, const std::string& atlasPath )
{
	if ( m_spriteResources.contains( spriteResourceId ) )
	{
		std::string message = std::format( "A sprite resource with the ID {} already exists. All sprite resource IDs must be unique.", spriteResourceId );
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		return;
	}

	SDL_Texture* texture = this->loadTexture( imagePath );

	if ( texture )
	{
		auto resource = std::make_unique<SpriteResource>();
		resource->texture.reset( texture );

		std::ifstream atlasFile( atlasPath );

		if ( !atlasFile.is_open() )
		{
			std::string message = std::format( "Failed to open sprite atlas file: {}", atlasPath );
			SDL_Log( message.c_str() );
			SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
			return;
		}

		try
		{
			json data = json::parse( atlasFile );

			for ( const auto& sprite : data["sprites"] )
			{
				auto& id = sprite["id"];
				auto& rect = sprite["rect"];
				resource->frames[id] = { SDL_FRect{ rect[0], rect[1], rect[2], rect[3] } };
			}
		}
		catch ( json::parse_error& exception )
		{
			std::string message = std::format( "Failed to parse sprite atlas file: {} \n{}", atlasPath, exception.what() );
			SDL_Log( message.c_str() );
			SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		}

		m_spriteResources[spriteResourceId] = std::move( resource );
	}
}

void ResourceManager::unloadSpriteResource( const std::string& spriteResourceId )
{
	auto it = m_spriteResources.find( spriteResourceId );
	if ( it != m_spriteResources.end() )
	{
		m_spriteResources.erase( it );
	}
}

const SpriteResource* ResourceManager::getSpriteResource( const Sprite& sprite ) const
{
	auto it = m_spriteResources.find( sprite.resourceId );
	return ( it != m_spriteResources.end() ) ? it->second.get() : nullptr;
}

const AnimationData* ResourceManager::createAnimation(
	const std::string& name,
	const std::vector<Sprite>& frames,
	float frameDuration,
	bool loop
)
{
	auto it = m_animations.find( name );
	if ( it != m_animations.end() )
	{
		return it->second.get();
	}

	auto animation = std::make_unique<AnimationData>();
	animation->frames = frames;
	animation->frameDuration = frameDuration;
	animation->loop = loop;

	auto ptr = animation.get();
	m_animations[name] = std::move( animation );
	return ptr;
}

const AnimationData* ResourceManager::getAnimation( const std::string& name ) const
{
	auto it = m_animations.find( name );
	if ( it != m_animations.end() )
	{
		return it->second.get();
	}
	else
	{
		return nullptr;
	}
}

std::string ResourceManager::loadTextFile( const std::string& path )
{
	std::ifstream textFile( path );

	if ( !textFile.is_open() )
	{
		std::string message = std::format( "Failed to open text file: {}", path );
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		return std::string();
	}

	std::ostringstream contents;
	contents << textFile.rdbuf();
	return contents.str();
}

std::vector<std::string> ResourceManager::loadTextLines( const std::string& path )
{
	std::ifstream textFile( path );

	if ( !textFile.is_open() )
	{
		std::string message = std::format( "Failed to open text file: {}", path );
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		return {};
	}

	std::vector<std::string> lines;
	std::string line;

	while ( std::getline( textFile, line ) )
	{
		if ( !line.empty() && line.back() == '\r' )
		{
			line.pop_back();
		}

		lines.push_back( line );
	}

	return lines;
}

void ResourceManager::unloadAssets()
{
	m_spriteResources.clear();
	m_animations.clear();
}