#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// SDL_Deleter from SDL2 is no longer available in SDL3
struct SDLTextureDeleter
{
	void operator()( SDL_Texture* texture ) const noexcept
	{
		if ( texture ) SDL_DestroyTexture( texture );
	}
};

struct SpriteFrame
{
	SDL_FRect rect;
	// Other fields like pivot or offset might go here later
};

struct SpriteResource
{
	std::unique_ptr<SDL_Texture, SDLTextureDeleter> texture;
	std::unordered_map<std::string, SpriteFrame> frames;

	const SpriteFrame* getSpriteFrame( const std::string& frameId ) const
	{
		auto it = frames.find( frameId );
		return ( it != frames.end() ) ? &it->second : nullptr;
	}
};