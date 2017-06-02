#include "stdio.h"

typedef struct Position
{
	uint8_t row;
	uint8_t col;
};

typedef struct WallPosition
{
	bool h;
	bool v;
};

typedef struct FloodPosition
{
	bool gone;
	uint8_t go_num; 
};

bool affirm_gone[18][18];

Position Location;
WallPosition Wall[18][18];
FloodPosition Flood[18][18];
void Input_Wall(Location p; uint8_t i)
{
	Wall[p.row][p.col].h = (i&0x8)?TRUE:FALSE;
	Wall[p.row][p.col].v = (i&0x1)?TRUE:FALSE;
	Wall[p.row-1][p.col].h = (i&0x2)?TRUE:FALSE;
	Wall[p.row][p.col-1].v = (i&0x4)?TRUE:FALSE;
}

void Write_Map_Gone(Location p)
{
	affirm_gone[p.r][p.c] = TRUE;
}

void Read_Map_Gone(Location p)
{
	return affirm_gone[p.r][p.c];
}

int main()
{
	printf("hello world");
	return 0;
}