#pragma once

typedef struct Wall
{
	bool h;
	bool v;
};

typedef struct Map_Floot
{
	unsigned char	x;
	unsigned char	y;
};

#define start_point_x			0
#define start_point_y			0
#define end_point_x				8
#define end_point_y				8

#define map_config_num			350
