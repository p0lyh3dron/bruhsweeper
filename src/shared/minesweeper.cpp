#include "../../inc/shared/minesweeper.h"

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

void tiles_init( MinesweeperGame* game )
{
	for ( int i = 0; i < game->height; ++i )
	{
		for ( int j = 0; j < game->width; ++j )
		{
			game->tiles[ i ][ j ].adjacentMines     = 0;
			game->tiles[ i ][ j ].state             = DEFAULT;
			game->tiles[ i ][ j ].isBomb            = 0;
		}
	}
}

void game_init( MinesweeperGame* game, unsigned int width, unsigned int height, unsigned int mineCount, char* seed )
{
	game->tiles = ( MinesweeperTile** )malloc( game->width * sizeof( MinesweeperTile ) );
	for ( int i = 0; i < height; ++i )
	{
		game->tiles[ i ] = ( MinesweeperTile* )malloc( sizeof( MinesweeperTile ) );
	}

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
	tiles_init( game );
	
	for ( int i = 0; i < mineCount; ++i )
	{
		game->tiles[ rand(  ) % game->width ][ rand (  ) % game->height ].isBomb = 1;
	}
	calc_adjacent_mines( game );
}

void calc_adjacent_mines( MinesweeperGame* game )
{
	for ( int x = 0; x < game->width; ++x )
	{
		for ( int y = 0; y < game->height; ++y )
		{
			if ( x == 0 && y == 0 )	//	Top left tile.
			{
				if ( game->tiles[ x + 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x == game->height - 1 && y == 0 )	//	Top right tile.
			{
				if ( game->tiles[ x - 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x == 0 && y == game->height - 1 )	//	Bottom left tile.
			{
				if ( game->tiles[ x + 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x == game->width - 1 && y == game->height - 1 )	// Bottom right tile.
			{
				if ( game->tiles[ x - 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y -1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x < game->width && y == 0 )	//	Top row tile.
			{
				if ( game->tiles[ x + 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y + 1 ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x < game->width && y == game->height - 1 )	//	Bottom row tile.
			{
				if ( game->tiles[ x + 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x == 0 )	//	Left column tile.
			{
				if ( game->tiles[ x + 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else if ( x == game->width - 1 )	//	Right column tile.
			{
				if ( game->tiles[ x - 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
			else	//	Tile surrounded by other tiles.
			{
				if ( game->tiles[ x ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x + 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y - 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
				if ( game->tiles[ x - 1 ][ y + 1 ].isBomb )
				{
					++game->tiles[ x ][ y ].adjacentMines;
				}
			}
		}

	}
}

/*
void calc_adjacent_mines( MinesweeperGame* game )
{
	for ( int i = 0; i < game->width * game->height; ++i )
	{
	        if ( i == 0 )	//	Top left tile.
		{
			if ( game->tiles[ i + 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width + 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
		}
		else if ( i < game->width - 1 )	//	Top row tile.
		{
			if ( game->tiles[ i + 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ i - 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width + i ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width + i + 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width + i - 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
		}
		else if ( i == game->width - 1 )	//	Top right tile.
		{
			if ( game->tiles[ i - 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width + i ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ game->width + i - 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
		}
		else if ( i == game->width * game->height )	//	Bottom right tile.
		{
			if ( game->tiles[ i - 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ ( game->width * ( game->height - 1 ) ) ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
			if ( game->tiles[ ( game->width * ( game->height - 1 ) ) - 1 ].isBomb )
			{
				++game->tiles[ i ].adjacentMines;
			}
		}
		else if ( i > game->width * ( game->height - 1 ) )	//	Bottom row tile.
		{
			
		}
		else if ( i == game->width * ( game->height - 1) )	//	Bottom left tile.
		{
			
		}
		else if ( ( i % game->width ) == 0 )	//	Left column tile
		{
			
		}
		else if ( ( i % game->width ) == ( game->width - 1 ) )	//	Right column tile
		{
			
		}
		else	//	Tile surrounded by other tiles.
		{
			
		}
	}
}
*/
	
void game_delete( MinesweeperGame* game )
{
	for ( int i = 0; i < game->width; ++i )
	{
		free( game->tiles[ i ] );
	}
	free( game->tiles );
}

void game_printf( MinesweeperGame* game )
{
	printf( "width = %i, height = %i, mines = %i\n", game->width, game->height, game->mineCount );
	for ( int i = 0; i < game->height; ++i )
	{
		for ( int j = 0; j < game->width; ++j )
		{
			if ( game->tiles[ i ][ j ].isBomb )
			{
				printf( "X" );
			}
			else
			{
				printf( "%i", game->tiles[ i ][ j ].adjacentMines );
			}
		}
		printf( "\n" );
	}
}
