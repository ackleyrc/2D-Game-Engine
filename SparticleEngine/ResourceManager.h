#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Sprite.h"

class SparticleEngine;
struct SDL_Renderer;
struct SpriteResource;

class ResourceManager
{
public:
	void loadSprite( const std::string& spriteResourceId, const std::string& imagePath );
	void loadSpriteSheet( const std::string& spriteResourceId, const std::string& imagePath, const std::string& atlasPath );
	void unloadSpriteResource( const std::string& spriteResourceId );
	void unloadAssets();

private:
	friend class SparticleEngine;
	ResourceManager() = default;
	~ResourceManager() { unloadAssets(); }

	void setRenderer( SDL_Renderer* renderer ) { m_renderer = renderer; }
	SDL_Renderer* m_renderer = nullptr;

	const SpriteResource* getSpriteResource( const Sprite& sprite ) const;
	std::unordered_map<std::string, std::unique_ptr<SpriteResource>> m_spriteResources;
};