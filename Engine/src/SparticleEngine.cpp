#include <format>
#include <iostream>
#include "SparticleEngine.h"
#include "SDLState.h"
#include "ResourceManagerTypes.h"

SparticleEngine::SparticleEngine(const EngineConfig& config)
	: m_sdlState( std::make_unique<SDLState>())
{
	if ( !SDL_Init( SDL_INIT_VIDEO ) )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr );
		std::exit( 1 );
	}

	// Create the window
	m_sdlState->width = config.width;
	m_sdlState->height = config.height;
	Uint32 windowFlags = config.resizable ? SDL_WINDOW_RESIZABLE : 0;

	m_sdlState->window = SDL_CreateWindow(
		config.windowTitle.c_str(), 
		m_sdlState->width,
		m_sdlState->width,
		windowFlags 
	);

	if ( !m_sdlState->window )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr );
		SDL_Quit();
		std:exit(1);
	}

	// Create the renderer
	m_sdlState->renderer = SDL_CreateRenderer( m_sdlState->window, nullptr );

	if ( !m_sdlState->renderer )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr );
		SDL_DestroyWindow( m_sdlState->window );
		SDL_Quit();
		std::exit(1);
	}

	SDL_SetRenderLogicalPresentation(
		m_sdlState->renderer,
		m_sdlState->width,
		m_sdlState->width,
		SDL_LOGICAL_PRESENTATION_LETTERBOX
	);

	m_resources.m_renderer = m_sdlState->renderer;

	m_isRunning = true;
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
	// TEMP - to be handled by game code
	m_resources.loadSpriteSheet( 
		"spritesheet", 
		"assets/textures/spritesheet.png", 
		"assets/textures/spritesheet.atlas"
	);
	Sprite playerSprite = { "spritesheet", "ghost_dead_blue" };

	m_TEMP_player = this->createObject<GameObject>();
	m_TEMP_player->setSprite( playerSprite );


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

void SparticleEngine::update( double deltaTime )
{
	for ( auto& obj : m_objects )
	{
		obj->onUpdate( deltaTime );
	}
}

void SparticleEngine::render()
{
	SDL_Renderer* renderer = m_sdlState->renderer;

	SDL_SetRenderDrawColor( renderer, 16, 16, 32, 255 );
	SDL_RenderClear( renderer );

	for ( auto& obj : m_objects )
	{
		const Sprite& sprite = obj->m_sprite;
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

		SDL_FRect src = frame->rect;
		SDL_FRect dst{ .x = obj->x, .y = -obj->y, .w = src.w, .h = src.h };

		SDL_RenderTexture( renderer, resource->texture.get(), &src, &dst);
	}

	SDL_RenderPresent( renderer );
}