#include "SparticleEngine.h"
#include "EngineConfig.h"

int main( int argc, char* argv[] )
{
	EngineConfig config;
	SparticleEngine engine( config );
	engine.run();
	return 0;
}