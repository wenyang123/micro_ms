#include <iostream>
#include <string>
#include "map.h"
using namespace std;

int main(int argc, char** argv)
{
	/*************************初始化************************/

	//对格子权值初始化
	unsigned int map[18][18] = { 0 };
	for (int i=0; i < 18; i++)
	{
		for (int j=0; j < 18; j++)
		{
			map[i][j] = map_config_num;
		}
	}

	//对迷宫墙壁初始化
	Wall wall[18][18]; 
	for (int i = 0; i < 18; i++)
	{
		wall[i][17].h = true;
		wall[17][i].v = true;
	}

	//设立迷宫终点
	map[end_point_x][end_point_y] = 0;

	/*************************洪水算法************************/
	Map_Floot map_floot_last[100];

	unsigned char map_num_last_index = 0;
	unsigned int map_num_sum_index = 0;

	//加载终点坐标
	map_floot_last[0].x = end_point_x;
	map_floot_last[0].y = end_point_y;
	map_num_last_index = 1;
	map_num_sum_index = 1;

	//初始化迷宫挡板情况
	//							   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
	unsigned char map_wall[324] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    //0
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//1
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//2
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//3
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//4
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//5
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//6
								   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//7
								   1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,	//8
								   1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//9
								   1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//10
								   1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//11
								   1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//12
								   1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//13
								   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//14
								   1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//15
								   1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//16
							       0, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1		//17
	};

	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			wall[i][j].h = ((map_wall[i + (17 - j) * 18] >> 1) & 0x01);
			wall[i][j].v = (map_wall[i + (17 - j) * 18] & 0x01);
		}
	}

	//循环填充
	bool map_floot_end=false;
	while (map_floot_end == false)
	{
		Map_Floot map_floot_new[100];
		unsigned char map_num_new_index = 0;

		for (int i = 0; i < 100; i++)
		{
			map_floot_new[i].x = 0;
			map_floot_new[i].y = 0;
		}

		for (int i = 0; i < map_num_last_index; i++)
		{
			if (map_floot_last[i].x > 0)
			{
				if ((map[map_floot_last[i].x - 1][map_floot_last[i].y] == map_config_num) && (wall[map_floot_last[i].x - 1][map_floot_last[i].y].v != true))
				{
					map[map_floot_last[i].x - 1][map_floot_last[i].y] = map_num_sum_index;
					map_floot_new[map_num_new_index].x = map_floot_last[i].x - 1;
					map_floot_new[map_num_new_index].y = map_floot_last[i].y;
					map_num_new_index++;

				}
			}

			if (map_floot_last[i].y > 0)
			{
				if ((map[map_floot_last[i].x][map_floot_last[i].y - 1] == map_config_num) && (wall[map_floot_last[i].x][map_floot_last[i].y - 1].h != true))
				{
					map[map_floot_last[i].x][map_floot_last[i].y - 1] = map_num_sum_index;
					map_floot_new[map_num_new_index].x = map_floot_last[i].x;
					map_floot_new[map_num_new_index].y = map_floot_last[i].y - 1;
					map_num_new_index++;
				}
			}

			if (map_floot_last[i].x < 17)
			{
				if ((map[map_floot_last[i].x + 1][map_floot_last[i].y] == map_config_num) && (wall[map_floot_last[i].x][map_floot_last[i].y].v != true))
				{
					map[map_floot_last[i].x + 1][map_floot_last[i].y] = map_num_sum_index;
					map_floot_new[map_num_new_index].x = map_floot_last[i].x + 1;
					map_floot_new[map_num_new_index].y = map_floot_last[i].y;
					map_num_new_index++;
				}
			}

			if (map_floot_last[i].y < 17)
			{
				if ((map[map_floot_last[i].x][map_floot_last[i].y + 1] == map_config_num) && (wall[map_floot_last[i].x][map_floot_last[i].y].h != true))
				{
					map[map_floot_last[i].x][map_floot_last[i].y + 1] = map_num_sum_index;
					map_floot_new[map_num_new_index].x = map_floot_last[i].x;
					map_floot_new[map_num_new_index].y = map_floot_last[i].y + 1;
					map_num_new_index++;
				}
			}
		}

		for (int i = 0; i < map_num_last_index; i++)
		{
			map_floot_last[i].x = 0;
			map_floot_last[i].y = 0;
		}
		
		for (int i = 0; i < map_num_new_index; i++)
		{
			if ((map_floot_new[i].x == start_point_x) && (map_floot_new[i].y == start_point_y))
			{
				map_floot_end = true;
				break;
			}

			map_floot_last[i].x = map_floot_new[i].x;
			map_floot_last[i].y = map_floot_new[i].y;

		}

		map_num_last_index = map_num_new_index;
		map_num_sum_index ++;


	}

	/*************************显示部分************************/
	printf("\n ");
	for (int i=0; i < 18; i++)
	{ 
		printf("\n\n          %2d   ", 17 - i);
		for (int j=0; j < 18; j++)
		{
			if(map[j][17 - i] == map_config_num)
				printf("    ");
			else
				printf(" %2d ", map[j][17 - i]);
		}

	}

	printf("\n ");
	printf("\n\n               ");
	for (int i = 0; i < 18; i++)
	{
		printf(" %2d ", i);
	}

	
	while (1);
	return 0;
}