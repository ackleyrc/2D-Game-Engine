#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>
#include <filesystem>

template<typename Func>
bool safeCall( const char* context, Func&& func )
{
	try
	{
		func();
		return true;
	}
	catch ( const std::exception& e )
	{
		std::string msg = std::format( "Exception: {}", e.what());
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "[%s] %s", context, msg.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Game Error", msg.c_str(), nullptr );
		return false;
	}
	catch ( ... )
	{
		std::string msg = std::string( "Unknown Exception" );
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "[%s] %s", context, msg.c_str() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Game Error", msg.c_str(), nullptr );
		return false;
	}
}