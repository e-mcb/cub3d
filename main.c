#include "cub3d.h"
#include "libft/libft.h"

//int main(void)
//{
//	int map[8][8] = {
//		{1,1,1,1,1,1,1,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,1,1,1,1,1,1,1}
//	};

//	double		player_x_init = 1.0;
//	double		player_y_init = 1.0;
//	double		theta = 0.0;
//	double		fov = 90.0;
//	int			mapX, mapY;
	
//	double	theta_min = theta - fov / 2;
//	double	theta_max = theta + fov / 2;

//	int		stepX, stepY;
//	double	DistX, DistY;

//	mapX = (int)player_x_init;
//	mapY = (int)player_y_init;
//	if (cos(theta_max) < 0)
//	{
//		stepX = -1;
//		DistX = 0;
//	}
//	else 
//	{
//		stepX = 1;
//		DistX = fabs(1 / cos(theta_max));
//	}
//	if (sin(theta_max) < 0)
//	{
//		stepY = -1;
//		DistY = 0;
//	}
//	else 
//	{
//		stepY = 1;
//		DistY = fabs(1 / sin(theta_max));
//	}

//	int hit = 0;
//	while (!hit)
//	{
//		if (DistX < DistY)
//		{
//			DistX += fabs(1/cos(theta_max));
//			mapX += stepX;
//		}
//		else 
//		{
//			DistY += fabs(1/sin(theta_max));
//			mapY += stepY;
//		}
//		if (map[mapY][mapX] == 1)
//			hit = 1;
//	}
//	float hypotenuse = (DistX < DistY) ? DistX : DistY;
//	printf("zebi %f\n", hypotenuse);
//	return 0;
//}

int	main(int argc, char **argv)
{
	t_parse		parse;
	t_player	player;

	init_parse(&parse);
	init_player(&player);
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3d <map.cub>\n");
		return (1);
	}
	if (read_map(argv[1], &parse) != 0)
	{
		printf("Error\nCould not read map file\n");
		return (1);
	}
	spawn_point(parse.map, &player);
	free_parse(&parse);
	return (0);
}