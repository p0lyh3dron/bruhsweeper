#include "../../inc/shared/minesweeper.h"

#include <stdlib.h>
#include <malloc.h>

void tiles_init( MinesweeperGame* game )
{
	for ( int i = 0; i < game->width * game->height; ++i )
	{
		game->tiles[ i ].isBomb = 0;
		game->tiles[ i ].state = DEFAULT;
	}
}

void game_init( MinesweeperGame* game, unsigned int width, unsigned int height, unsigned int mineCount )
{
	game->tiles = ( MinesweeperTile* )malloc( ( game->width * game->height ) * sizeof( MinesweeperTile ) );
	
	game->width = width;
	game->height = height;
	game->mineCount = mineCount;
	game->openTileCount = 0;
	game->minesLeft = mineCount;
	game->state = GAME_IDLE;
	tiles_init( game );

	srand( ( unsigned int ) 42069 );
	
	for ( int i = 0; i < mineCount; ++i )
	{
		game->tiles[ rand(  ) % ( game->width * game->height ) ].isBomb = 1;
	}
}

void game_delete( MinesweeperGame* game )
{
	free( game->tiles );
}
