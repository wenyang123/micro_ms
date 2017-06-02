#include <iostream>
#include <string>
#include "map.h"
using namespace std;

int main(int argc, char** argv)
{
	/*************************初始化************************/

	//对格子权值初始化
	unsigned int map[map_x_num][map_y_num] = { 0 };
	for (int i=0; i < map_x_num; i++)
	{
		for (int j=0; j < map_y_num; j++)
		{
			map[i][j] = map_config_num;
		}
	}

	//对迷宫墙壁初始化
	Wall wall[map_x_num][map_y_num];
	for (int i = 0; i < map_x_num; i++)
	{
		wall[i][map_y_num-1].h = true;
		wall[map_x_num-1][i].v = true;
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
	//							   
	unsigned char map_wall[map_x_num*map_y_num] = map_wall_init;

	for (int i = 0; i < map_x_num; i++)
	{
		for (int j = 0; j < map_y_num; j++)
		{
			wall[i][j].h = ((map_wall[i + (map_y_num - 1 - j) * map_y_num] >> 1) & 0x01);
			wall[i][j].v = (map_wall[i + (map_y_num - 1 - j) * map_y_num] & 0x01);
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

			if (map_floot_last[i].x < (map_x_num-1))
			{
				if ((map[map_floot_last[i].x + 1][map_floot_last[i].y] == map_config_num) && (wall[map_floot_last[i].x][map_floot_last[i].y].v != true))
				{
					map[map_floot_last[i].x + 1][map_floot_last[i].y] = map_num_sum_index;
					map_floot_new[map_num_new_index].x = map_floot_last[i].x + 1;
					map_floot_new[map_num_new_index].y = map_floot_last[i].y;
					map_num_new_index++;
				}
			}

			if (map_floot_last[i].y < (map_y_num-1))
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
	for (int i=0; i < map_x_num; i++)
	{ 
		printf("\n                ");
		for (int j = 0; j < map_x_num; j++)
		{
			if (wall[j][map_x_num - 1 - i].h == true)
				printf("___ ");
			else
				printf("    ");
		}

		printf("\n          %2d   |", map_x_num - 1 - i);

		for (int j=0; j < map_y_num; j++)
		{
			if (map[j][map_y_num - 1 - i] == map_config_num)
				printf("   ");
			else
				printf(" %2d", map[j][map_y_num - 1 - i]);

			if (wall[j][map_x_num -1 - i].v == true)
				printf("|");
			else
				printf(" ");
		}

	}

	printf("\n ");
	printf("\n\n                ");
	for (int i = 0; i < map_x_num; i++)
	{
		printf(" %2d ", i);
	}

	
	while (1);
	return 0;
}