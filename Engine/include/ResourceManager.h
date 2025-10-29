#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "EngineAPI.h"

class SparticleEngine;
struct SDL_Renderer;
struct SDL_Texture;
struct SpriteResource;
struct Sprite;
struct AnimationData;

class SPARTICLE_API ResourceManager
{
public:
	~ResourceManager();

	void loadSprite( const std::string& spriteResourceId, const std::string& imagePath );
	void loadSpriteSheet( const std::string& spriteResourceId, const std::string& imagePath, const std::string& atlasPath );
	void unloadSpriteResource( const std::string& spriteResourceId );
	void unloadAssets();

	const AnimationData* createAnimation(
		const std::string& name,
		const std::vector<Sprite>& frames,
		float frameDuration,
		bool loop = true
	);

	const AnimationData* getAnimation( const std::string& name ) const;

private:
	friend class SparticleEngine;

	ResourceManager() = default;

	SDL_Renderer* m_renderer = nullptr;

	SDL_Texture* loadTexture( const std::string& imagePath );

	const SpriteResource* getSpriteResource( const Sprite& sprite ) const;
	std::unordered_map<std::string, std::unique_ptr<SpriteResource>> m_spriteResources;

	std::unordered_map<std::string, std::unique_ptr<AnimationData>> m_animations;
};