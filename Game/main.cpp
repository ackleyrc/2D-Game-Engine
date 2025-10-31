#include <SparticleEngine.h>
#include <EngineConfig.h>
#include "MazeEaterGame.h"

int main( int argc, char* argv[] )
{
	MazeEaterGame game;

	EngineConfig config;
	config.width = 448;
	config.height = 512;
	config.windowTitle = "Maze Eater Game";
	config.backgroundColor = Color( 0.06f, 0.06f, 0.12f, 1.0f );
	config.resizable = true;

	SparticleEngine engine( config, &game );

	engine.run();

	return 0;
}