/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:14:44 by mzutter           #+#    #+#             */
/*   Updated: 2025/08/31 18:06:36 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

#define EAST (0)
#define NORTH (M_PI / 2)
#define WEST (M_PI)
#define SOUTH (3 * M_PI / 2)

#define FOV (M_PI / 2)

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include "libft/libft.h"

typedef struct s_parse
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;		//all 4 of these are malloc'd, remember to free
	char	*texture_east;

	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_height;
	int		map_width;
} t_parse;

typedef struct s_player
{
	float	current_x;
	float	current_y;
	float	init_x;
	float	init_y;
	float	init_angle;
	float	direction_angle;
	float	fov;
	bool	collision;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	move_speed;
	float	angular_speed;
} t_player;

//maths
float	deg_to_rad(float degrees);
float	rad_to_deg(float rad);

//parsing
int 	is_texture_or_color(char *line);
void	parse_texture_or_color(char *line, t_parse *parse);


//utils
void	ft_free_str_array(char **arr);
int		array_size(char **arr);

#endif
