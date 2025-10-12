#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "EngineAPI.h"
#include "Sprite.h"

class SparticleEngine;
struct SDL_Renderer;
struct SDL_Texture;
struct SpriteResource;

class SPARTICLE_API ResourceManager
{
public:
	void loadSprite( const std::string& spriteResourceId, const std::string& imagePath );
	void loadSpriteSheet( const std::string& spriteResourceId, const std::string& imagePath, const std::string& atlasPath );
	void unloadSpriteResource( const std::string& spriteResourceId );
	void unloadAssets();

private:
	friend class SparticleEngine;

	ResourceManager() = default;
	~ResourceManager();

	SDL_Renderer* m_renderer = nullptr;

	SDL_Texture* loadTexture( const std::string& imagePath );

	const SpriteResource* getSpriteResource( const Sprite& sprite ) const;
	std::unordered_map<std::string, std::unique_ptr<SpriteResource>> m_spriteResources;
};