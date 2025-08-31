/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:46:08 by mzutter           #+#    #+#             */
/*   Updated: 2025/08/31 17:54:12 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_cardinal(char c)
{
	if (c == 'w' || c == 'W' || c == 'e' || c == 'E'
		|| c == 's' || c == 'S' || c == 'n' || c == 'N')
    	return (1);
	else
		return (0);
}

float	initial_direction(char c)
{
	if (c == 'w' || c == 'W')
		return (WEST);
	if (c == 'n' || c == 'N')
		return (NORTH);
	if (c == 'e' || c == 'E')
		return (EAST);
	if (c == 's' || c == 'S')
		return (SOUTH);
	else 
		return (-1);
}

int	spawn_point(char **map, t_player *player)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	if (!map)
		return (-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0 && map[i][j] != '\n')
		{
			if (is_cardinal(map[i][j]))
			{
				player->init_angle = initial_direction(map[i][j]);
				player->init_x = (float)j;
				player->init_y = (float)i;
				found = 1;
			}
			j++;
		}
		i++;
	}
	return (found);
}
