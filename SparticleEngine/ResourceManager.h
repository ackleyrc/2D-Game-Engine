#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// forward declaration
class SparticleEngine;

// SDL_Deleter from SDL2 is no longer available in SDL3
struct SDLTextureDeleter
{
	void operator()( SDL_Texture* texture ) const noexcept
	{
		if ( texture ) SDL_DestroyTexture( texture );
	}
};

class ResourceManager
{
public:
	void loadTexture( const std::string& id, const std::string& path );
	void unloadTexture( const std::string& id );
	void unloadAssets();

private:
	friend class SparticleEngine;
	ResourceManager() = default;
	~ResourceManager() { unloadAssets(); }

	SDL_Texture* getTexture( const std::string& id );
	void setRenderer( SDL_Renderer* renderer ) { m_renderer = renderer; }

	SDL_Renderer* m_renderer = nullptr;
	std::unordered_map<std::string, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> m_textures;
};