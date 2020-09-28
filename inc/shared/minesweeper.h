typedef enum
{
	DEFAULT,
	OPENED,
	FLAGGED,
}TileState;

typedef enum
{
	GAME_IDLE,
	GAME_ACTIVE,
	GAME_WIN,
	GAME_LOSE
}GameState;
	
typedef struct
{
	int isBomb;
	TileState state;
}MinesweeperTile;

typedef struct
{
	unsigned int width;
	unsigned int height;
	unsigned int mineCount;
	unsigned int openTileCount;
	unsigned int minesLeft;
	union
	{
		unsigned int intSeed;
		char* strSeed;
	};
	MinesweeperTile* tiles;
	GameState state;
}MinesweeperGame;

void tiles_init( MinesweeperGame* game );

void game_init( MinesweeperGame* game, unsigned int width, unsigned int height, unsigned int mineCount, char* seed );

void get_tile_location( MinesweeperGame* game, unsigned int x, unsigned int y );

void game_delete( MinesweeperGame* game );

void game_printf( MinesweeperGame* game );
