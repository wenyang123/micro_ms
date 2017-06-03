#pragma once

struct Wall
{
	bool h;
	bool v;
};

struct Map_Floot
{
	unsigned char	x;
	unsigned char	y;
};

#define start_point_x			0
#define start_point_y			0
#define end_point_x				8
#define end_point_y				8

#define map_x_num				16
#define map_y_num				16

#define map_config_num			300

#define switch_map_run			1

								      
#define map_wall_init			/*15*/{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,\
								/*14*/ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,\
								/*13*/ 1, 0, 2, 2, 3, 2, 3, 2, 2, 2, 3, 2, 2, 3, 1, 1,\
								/*12*/ 1, 1, 2, 2, 1, 1, 0, 1, 2, 3, 1, 0, 3, 1, 1, 1,\
								/*11*/ 1, 1, 1, 1, 2, 1, 3, 2, 1, 1, 1, 2, 1, 1, 1, 1,\
								/*10*/ 1, 1, 1, 2, 1, 3, 0, 0, 3, 1, 1, 0, 3, 1, 1, 1,\
								/*09*/ 1, 1, 1, 1, 3, 0, 0, 2, 1, 0, 1, 2, 1, 1, 1, 1,\
								/*08*/ 1, 1, 0, 1, 0, 0, 3, 2, 3, 1, 2, 2, 1, 1, 1, 1,\
								/*07*/ 1, 1, 2, 2, 0, 2, 1, 0, 1, 0, 2, 1, 1, 1, 1, 1,\
								/*06*/ 1, 1, 0, 3, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 1, 1,\
								/*05*/ 1, 1, 2, 1, 0, 3, 1, 2, 2, 1, 1, 2, 1, 3, 1, 1,\
								/*04*/ 1, 1, 0, 3, 1, 1, 3, 2, 1, 1, 2, 1, 2, 1, 1, 1,\
								/*03*/ 1, 0, 3, 0, 1, 2, 1, 0, 3, 2, 1, 2, 1, 1, 1, 1,\
								/*02*/ 0, 3, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 2, 1, 1, 1,\
								/*01*/ 1, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1,\
								/*00*/ 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1} 
                                     /*0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
