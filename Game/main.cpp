#include <SparticleEngine.h>
#include <EngineConfig.h>
#include "MazeEaterGame.h"
#include "GameConfig.h"

int main( int argc, char* argv[] )
{
	GameConfig gameConfig;
	MazeEaterGame game;
	SparticleEngine engine( gameConfig.engineConfig );

	engine.setGame( &game );
	engine.run();

	return 0;
}