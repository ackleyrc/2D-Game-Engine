#include <format>
#include <iostream>
#include "SparticleEngine.h"
#include "EngineInternalUtils.h"
#include "SDLState.h"
#include "ResourceManagerTypes.h"

SparticleEngine::SparticleEngine( const EngineConfig& config, IGame* game ) : 
	m_engineConfig( config ),
	m_game( game )
{
	if ( !SDL_Init( SDL_INIT_VIDEO ) )
	{
		std::string message = "Error initializing SDL3";
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr);
		std::exit( 1 );
	}

	m_sdlState = std::make_unique<SDLState>();

	// Create the window
	m_sdlState->width = config.width;
	m_sdlState->height = config.height;
	Uint32 windowFlags = config.resizable ? SDL_WINDOW_RESIZABLE : 0;

	m_sdlState->window = SDL_CreateWindow(
		config.windowTitle.c_str(), 
		m_sdlState->width,
		m_sdlState->height,
		windowFlags 
	);

	if ( !m_sdlState->window )
	{
		std::string message = "Error creating window";
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		SDL_Quit();
		std:exit(1);
	}

	// Create the renderer
	m_sdlState->renderer = SDL_CreateRenderer( m_sdlState->window, nullptr );

	if ( !m_sdlState->renderer )
	{
		std::string message = "Error creating renderer";
		SDL_Log( message.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr );
		SDL_DestroyWindow( m_sdlState->window );
		SDL_Quit();
		std::exit(1);
	}

	SDL_SetRenderLogicalPresentation(
		m_sdlState->renderer,
		m_sdlState->width,
		m_sdlState->height,
		SDL_LOGICAL_PRESENTATION_LETTERBOX
	);

	m_resources.m_renderer = m_sdlState->renderer;

	if ( !safeCall( "Game::setEngine", [this]() { m_game->setEngine( this ); } ) )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Game failed to set engine." );
		throw std::runtime_error( "Game failed to set engine." );
	}

	if ( !safeCall( "Game::onInit", [this] () { m_game->onInit(); } ) )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Game initialization failed." );
		throw std::runtime_error( "Game initialization failed." );
	}
}

SparticleEngine::~SparticleEngine()
{
	if ( m_sdlState->renderer )
	{
		SDL_DestroyRenderer( m_sdlState->renderer );
		m_sdlState->renderer = nullptr;
	}

	if ( m_sdlState->window )
	{
		SDL_DestroyWindow( m_sdlState->window );
		m_sdlState->window = nullptr;
	}

	SDL_Quit();
}

void SparticleEngine::run()
{
	m_isRunning = true;

	Uint64 previousCounter = SDL_GetPerformanceCounter();
	Uint64 frequency = SDL_GetPerformanceFrequency();

	while ( m_isRunning )
	{
		Uint64 currentCounter = SDL_GetPerformanceCounter();
		double deltaTime = static_cast<double>( currentCounter - previousCounter ) / frequency;
		previousCounter = currentCounter;

		this->processEvents();
		this->update( deltaTime );
		this->render();
	}

	if ( !safeCall( "Game::onShutdown", [this] () { m_game->onShutdown(); } ) )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Game shutdown failed." );
		throw std::runtime_error( "Game shutdown failed." );
	}

	m_resources.unloadAssets();
}

void SparticleEngine::processEvents()
{
	SDL_Event event{ 0 };
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
			case SDL_EVENT_QUIT:
			{
				m_isRunning = false;
				break;
			}
			case SDL_EVENT_WINDOW_RESIZED:
			{
				m_sdlState->width = event.window.data1;
				m_sdlState->height = event.window.data2;
				break;
			}
		}
	}

	m_input.update();
}

void SparticleEngine::update( const double deltaTime )
{
	if ( !safeCall( "Game::onUpdate", [this, deltaTime] () { m_game->onUpdate( deltaTime ); } ) )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Game failed to update." );
		throw std::runtime_error( "Game failed to update." );
	}

	for ( auto& obj : m_objects )
	{
		obj->update( deltaTime );
	}
}

void SparticleEngine::render()
{
	SDL_Renderer* renderer = m_sdlState->renderer;

	SDL_SetRenderDrawColor( 
		renderer, 
		static_cast<Uint8>( m_engineConfig.backgroundColor.r * 255.0f ), 
		static_cast<Uint8>( m_engineConfig.backgroundColor.g * 255.0f ),
		static_cast<Uint8>( m_engineConfig.backgroundColor.b * 255.0f ),
		static_cast<Uint8>( m_engineConfig.backgroundColor.a * 255.0f )
	);


	SDL_RenderClear( renderer );

	for ( auto& [layer, spriteVec] : m_spriteLayers )
	{
		for ( auto* spriteComponent : spriteVec )
		{
			if ( !spriteComponent )
			{
				continue;
			}

			const Sprite& sprite = spriteComponent->getSprite();
			const SpriteResource* resource = m_resources.getSpriteResource( sprite );

			if ( !resource || !resource->texture )
			{
				std::string message = std::format( "Failed to find resource/texture for ID: {}", sprite.resourceId );
				SDL_Log( message.c_str(), SDL_GetError() );
				continue;
			}

			const SpriteFrame* frame = resource->getSpriteFrame( sprite.frameId );

			if ( !frame )
			{
				std::string message = std::format( "Failed to find sprite frame for ID: {}", sprite.frameId );
				SDL_Log( message.c_str(), SDL_GetError() );
				continue;
			}

			auto obj = spriteComponent->m_gameObject;

			SDL_FRect src = frame->rect;
			SDL_FRect dst { .x = obj->x, .y = obj->y, .w = src.w, .h = src.h };

			SDL_RenderTexture( renderer, resource->texture.get(), &src, &dst );
		}
	}

	SDL_RenderPresent( renderer );
}

GameObject* SparticleEngine::createGameObject()
{
	auto obj = std::unique_ptr<GameObject>( new GameObject( this ) );
	GameObject* ptr = obj.get();
	m_objects.push_back( std::move( obj ) );
	return ptr;
}

void SparticleEngine::registerSpriteComponent( SpriteComponent* spriteComponent )
{
	if ( !spriteComponent )
	{
		return;
	}

	int layer = spriteComponent->getLayer();
	auto& vec = m_spriteLayers[layer];

	if ( std::find( vec.begin(), vec.end(), spriteComponent ) == vec.end() )
	{
		vec.push_back( spriteComponent );
	}
}

void SparticleEngine::unregisterSpriteComponent( SpriteComponent* spriteComponent )
{
	if ( !spriteComponent )
	{
		return;
	}

	int layer = spriteComponent->getLayer();
	auto it = m_spriteLayers.find( layer );
	if ( it == m_spriteLayers.end() )
	{
		return;
	}

	auto& vec = it->second;
	vec.erase( std::remove( vec.begin(), vec.end(), spriteComponent ), vec.end() );

	if ( vec.empty() )
	{
		m_spriteLayers.erase( it );
	}
}