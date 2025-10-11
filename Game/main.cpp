#include "SparticleEngine.h"
#include "EngineConfig.h"

int main( int argc, char* argv[] )
{
	EngineConfig config;
	config.width = 448;
	config.height = 512;
	config.windowTitle = "Maze Eater Game";
	config.resizable = true;

	SparticleEngine engine( config );
	engine.run();
	return 0;
}