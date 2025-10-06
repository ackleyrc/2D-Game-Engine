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
	int width = 800;
	int height = 600;
	m_sdlState.window = SDL_CreateWindow( "Sparticle Engine", width, height, 0 );

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

void SparticleEngine::run()
{
	while ( m_isRunning )
	{
		this->processEvents();
		this->update();
		this->render();
	}
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
		}
	}
}

void SparticleEngine::update()
{
	// game logic
}

void SparticleEngine::render()
{
	SDL_SetRenderDrawColor( m_sdlState.renderer, 255, 255, 255, 255 );
	SDL_RenderClear( m_sdlState.renderer );
	SDL_RenderPresent( m_sdlState.renderer );
}
