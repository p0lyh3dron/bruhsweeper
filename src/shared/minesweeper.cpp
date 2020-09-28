#include "../../inc/shared/minesweeper.h"

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

void tiles_init( MinesweeperGame* game )
{
	for ( int i = 0; i < game->width * game->height; ++i )
	{
		game->tiles[ i ].isBomb = 0;
		game->tiles[ i ].state = DEFAULT;
	}
}

void game_init( MinesweeperGame* game, unsigned int width, unsigned int height, unsigned int mineCount, char* seed )
{
	game->tiles = ( MinesweeperTile* )malloc( ( game->width * game->height ) * sizeof( MinesweeperTile ) );

	if ( seed == NULL )
	{
		game->intSeed = ( unsigned int )time( 0 );
		srand( game->intSeed );
	}
	else
	{
		game->strSeed = seed;
		srand( *( unsigned int* )seed );
	}
	
	game->width = width;
	game->height = height;
	game->mineCount = mineCount;
	game->openTileCount = 0;
	game->minesLeft = mineCount;
	game->state = GAME_IDLE;
	game->strSeed = seed;
	tiles_init( game );;
	
	for ( int i = 0; i < mineCount; ++i )
	{
		game->tiles[ rand(  ) % ( game->width * game->height ) ].isBomb = 1;
	}
}

void game_delete( MinesweeperGame* game )
{
	free( game->tiles );
}

void game_printf( MinesweeperGame* game )
{
	printf( "width = %i, height = %i, mines = %i\n", game->width, game->height, game->mineCount );
	for ( int i = 0; i < game->height; ++i )
	{
		for ( int j = 0; j < game->width; ++j )
		{
			if ( game->tiles[ ( i * game->height ) + j ].isBomb )
			{
				printf( "X" );
			}
			else
			{
				printf( "O" );
			}
		}
		printf( "\n" );
	}
}
