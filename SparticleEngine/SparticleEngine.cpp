#include "SparticleEngine.h"
#include <iostream>

SparticleEngine::SparticleEngine()
{
	initSDL();
}

SparticleEngine::~SparticleEngine() 
{
	shutdownSDL();
}

void SparticleEngine::initSDL()
{
	if ( !SDL_Init( SDL_INIT_VIDEO ) )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr );
		std::exit( 1 );
	}

	// Create the window
	m_sdlState.window = SDL_CreateWindow( "Sparticle Engine", m_sdlState.width, m_sdlState.height, SDL_WINDOW_RESIZABLE );

	if ( !m_sdlState.window )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr );
		SDL_Quit();
		std:exit(1);
	}

	// Create the renderer
	m_sdlState.renderer = SDL_CreateRenderer( m_sdlState.window, nullptr );

	if ( !m_sdlState.renderer )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr );
		SDL_DestroyWindow( m_sdlState.window );
		SDL_Quit();
		std::exit(1);
	}

	SDL_SetRenderLogicalPresentation(
		m_sdlState.renderer,
		m_sdlState.logicalWidth,
		m_sdlState.logicalHeight,
		SDL_LOGICAL_PRESENTATION_LETTERBOX
	);

	m_isRunning = true;
}

void SparticleEngine::shutdownSDL()
{
	if ( m_sdlState.renderer )
	{
		SDL_DestroyRenderer( m_sdlState.renderer );
		m_sdlState.renderer = nullptr;
	}

	if ( m_sdlState.window )
	{
		SDL_DestroyWindow( m_sdlState.window );
		m_sdlState.window = nullptr;
	}

	SDL_Quit();
}

void SparticleEngine::loadAssets()
{
	m_TEMP_spriteSheet = IMG_LoadTexture( m_sdlState.renderer, "assets/textures/spritesheet.png" );
	SDL_SetTextureScaleMode( m_TEMP_spriteSheet, SDL_SCALEMODE_NEAREST );
}

void SparticleEngine::unloadAssets()
{
	SDL_DestroyTexture( m_TEMP_spriteSheet );
}

void SparticleEngine::run()
{
	loadAssets();

	while ( m_isRunning )
	{
		this->processEvents();
		this->update();
		this->render();
	}

	unloadAssets();
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
				m_sdlState.width = event.window.data1;
				m_sdlState.height = event.window.data2;
				break;
			}
		}
	}
}

void SparticleEngine::update()
{
	// game logic
}

void SparticleEngine::render()
{
	SDL_SetRenderDrawColor( m_sdlState.renderer, 16, 16, 32, 255 );
	SDL_RenderClear( m_sdlState.renderer );

	SDL_FRect src{
		.x = 0,
		.y = 0,
		.w = 32,
		.h = 32
	};

	SDL_FRect dst{
		.x = 0,
		.y = 0,
		.w = 32,
		.h = 32
	};

	SDL_RenderTexture( m_sdlState.renderer, m_TEMP_spriteSheet, &src, &dst );

	SDL_RenderPresent( m_sdlState.renderer );
}
