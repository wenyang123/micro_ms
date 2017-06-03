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
	/*************************路径规划************************/
	Map_Floot map_run_save[map_x_num*map_x_num];
	Map_Floot map_run_local;
	unsigned char map_run_local_num=0;

	map_num_sum_index -= 1;
	map_run_local.x = start_point_x;
	map_run_local.y = start_point_y;
	map_run_local_num = map_num_sum_index;


	for (int i = 0; i < map_num_sum_index; i++)
	{
		unsigned char map_wall_run_dir[4] = {0};

		if (map_run_local.y < end_point_y)
		{
			map_wall_run_dir[0] = 0;
			if (map_run_local.x < end_point_x)
			{
				map_wall_run_dir[1] = 1;
				map_wall_run_dir[2] = 2;
				map_wall_run_dir[3] = 3;
			}
			else
			{
				map_wall_run_dir[1] = 3;
				map_wall_run_dir[2] = 2;
				map_wall_run_dir[3] = 1;
			}
		}
		else
		{
			map_wall_run_dir[0] = 2;
			if (map_run_local.x < end_point_x)
			{
				map_wall_run_dir[1] = 1;
				map_wall_run_dir[2] = 0;
				map_wall_run_dir[3] = 3;
			}
			else
			{
				map_wall_run_dir[1] = 3;
				map_wall_run_dir[2] = 0;
				map_wall_run_dir[3] = 1;
			}
		}

		if (map_run_local.x == 0)
			map_wall_run_dir[3] = 1;

		if (map_run_local.x == (map_x_num - 1))
			map_wall_run_dir[3] = 3;

		if (map_run_local.y == 0)
			map_wall_run_dir[2] = 0;

		if (map_run_local.y == (map_y_num - 1))
			map_wall_run_dir[2] = 2;

		if (map_run_local.x == end_point_x && map_run_local.y == end_point_y)
			break;

	//	printf("%3d, %3d   ", map[map_run_local.x+1][map_run_local.y], map_run_local_num);
	//	printf("%3d, %3d, %3d, %3d  ---", map_wall_run_dir[0], map_wall_run_dir[1], map_wall_run_dir[2], map_wall_run_dir[3]);
		for (int i = 0; i < 4; i++)
		{
			bool map_wall_run_dir_choose=false;
			switch (map_wall_run_dir[i])
			{
				case 0:	if (((map_run_local_num - map[map_run_local.x][map_run_local.y + 1] ) == 1) && (wall[map_run_local.x][map_run_local.y].h != true))
				{
					map_run_local.y += 1;
					map_run_local_num -= 1;
					map_wall_run_dir_choose = true;
				}
				break;

				case 1:if (((map_run_local_num - map[map_run_local.x + 1][map_run_local.y]) == 1) && (wall[map_run_local.x][map_run_local.y].v != true))
				{
					map_run_local.x += 1;
					map_run_local_num -= 1;
					map_wall_run_dir_choose = true;
				}
				break;

				case 2:if (((map_run_local_num - map[map_run_local.x][map_run_local.y - 1]) == 1) && (wall[map_run_local.x][map_run_local.y - 1].h != true))
				{
					map_run_local.y -= 1;
					map_run_local_num -= 1;
					map_wall_run_dir_choose = true;
				}
				break;

				case 3:if (((map_run_local_num - map[map_run_local.x - 1][map_run_local.y]) == 1) && (wall[map_run_local.x - 1][map_run_local.y].v != true))
				{
					map_run_local.x -= 1;
					map_run_local_num -= 1;
					map_wall_run_dir_choose = true;
				}
				break;
			}
			if (map_wall_run_dir_choose == true)
			{
				map_run_save[map_num_sum_index - map_run_local_num - 1].x = map_run_local.x;
				map_run_save[map_num_sum_index - map_run_local_num - 1].y = map_run_local.y;
				break;
			}
		}
		
	}

//	for (int i = 0; i < map_num_sum_index; i++)
//	{
//		printf("%3d, %3d  \n", map_run_save[i].x, map_run_save[i].y);
//	}

	/*************************显示部分************************/
	unsigned char show_map_run_num=0;
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
			int map_run_sure=0;
#if switch_map_run
			if (map[j][map_y_num - 1 - i] == map_config_num)
				printf("   ");
			else
				printf("%3d", map[j][map_y_num - 1 - i]);
#else
			for (int k = 0; k < map_num_sum_index; k++)
			{
				if ((j == map_run_save[k].x) && ((map_y_num - 1 - i) == map_run_save[k].y))
				{
					printf("%3d", map[j][map_y_num - 1 - i]);
					map_run_sure = 1;
					break;
				}
			}
			if(map_run_sure == 0)
				printf("   ");
#endif


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