#include <format>
#include "ResourceManager.h"
#include "ResourceManagerTypes.h"

ResourceManager::~ResourceManager()
{
	unloadAssets();
}

void ResourceManager::loadSprite( const std::string& spriteResourceId, const std::string& imagePath )
{
	if ( m_spriteResources.contains( spriteResourceId ) )
	{
		std::string message = std::format( "A sprite resource with the ID {} already exists. All sprite resource IDs must be unique.", spriteResourceId );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr);
		return;
	}

	SDL_Texture* texture = IMG_LoadTexture( m_renderer, imagePath.c_str() );

	if ( !texture )
	{
		SDL_Log( "Failed to load texture '%s': %s", imagePath.c_str(), SDL_GetError() );
		return;
	}

	SDL_SetTextureScaleMode( texture, SDL_SCALEMODE_NEAREST );

	auto resource = std::make_unique<SpriteResource>();
	resource->texture.reset( texture );

	// Default frame = full texture
	float w, h;
	SDL_GetTextureSize( texture, &w, &h );
	resource->frames["default"] = { SDL_FRect{ 0, 0, w, h } };

	m_spriteResources[spriteResourceId] = std::move( resource );
}

void ResourceManager::loadSpriteSheet( const std::string& spriteResourceId, const std::string& imagePath, const std::string& atlasPath )
{
	if ( m_spriteResources.contains( spriteResourceId ) )
	{
		std::string message = std::format( "A sprite resource with the ID {} already exists. All sprite resource IDs must be unique.", spriteResourceId );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		return;
	}

	SDL_Texture* texture = IMG_LoadTexture( m_renderer, imagePath.c_str() );

	if ( !texture )
	{
		SDL_Log( "Failed to load texture '%s': %s", imagePath.c_str(), SDL_GetError() );
		return;
	}

	SDL_SetTextureScaleMode( texture, SDL_SCALEMODE_NEAREST );

	auto resource = std::make_unique<SpriteResource>();
	resource->texture.reset( texture );

	// TODO: read in source rects from sprite atlas
	//float w, h;
	//SDL_GetTextureSize( texture, &w, &h );
	resource->frames["default"] = { SDL_FRect{ 0, 0, 32, 32 } };

	m_spriteResources[spriteResourceId] = std::move( resource );
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

void ResourceManager::unloadAssets()
{
	m_spriteResources.clear();
}