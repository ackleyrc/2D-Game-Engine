#pragma once

// Shared/static export logic for the engine
#if defined(_WIN32) && defined(SPARTICLE_BUILD_SHARED)
	#if defined(SparticleEngineLib_EXPORTS)
		#define SPARTICLE_API __declspec(dllexport)
	#else
		#define SPARTICLE_API __declspec(dllimport)
	#endif
#else
	#define SPARTICLE_API
#endif