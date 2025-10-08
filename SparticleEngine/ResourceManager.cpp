#include "ResourceManager.h"

void ResourceManager::loadTexture( const std::string& id, const std::string& path )
{
	if ( m_textures.contains( id ) )
	{
		return;
	}

	SDL_Texture* texture = IMG_LoadTexture( m_renderer, path.c_str() );

	if ( !texture )
	{
		SDL_Log( "Failed to load texture '%s': %s", path.c_str(), SDL_GetError() );
		return;
	}

	SDL_SetTextureScaleMode( texture, SDL_SCALEMODE_NEAREST );

	m_textures[id] = { texture , SDLTextureDeleter{} };
}

void ResourceManager::unloadTexture( const std::string& id )
{
	auto it = m_textures.find( id );
	if ( it != m_textures.end() )
	{
		m_textures.erase( it );
	}
}

SDL_Texture* ResourceManager::getTexture( const std::string& id )
{
	auto it = m_textures.find( id );
	return ( it != m_textures.end() ) ? it->second.get() : nullptr;
}

void ResourceManager::unloadAssets()
{
	m_textures.clear();
}