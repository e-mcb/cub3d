#include "../cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_cardinal(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map_content(char **map)
{
	int		i;
	int		j;
	int		player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
				return (0); //Error
			if (is_cardinal(map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (0); //Error
	if (player_count > 1)
		return (0); // Error
	return (1);
}

int	flood_fill(char **map, t_parse *parse, int x, int y)
{
	char	c;

	if (x < 0 || y < 0 || y >= parse->map_height || x >= parse->map_width)
		return (0);
	c = map[y][x];
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '1' || c == 'V')
		return (1);
	if (!is_valid_map_char(c))
		return (0);
	map[y][x] = 'V';
	if (!flood_fill(map, parse, x + 1, y))
		return (0);
	if (!flood_fill(map, parse, x - 1, y))
		return (0);
	if (!flood_fill(map, parse, x, y + 1))
		return (0);
	if (!flood_fill(map, parse, x, y - 1))
		return (0);
	return (1);
}

int validate_map_closed(t_parse *parse, t_player *player)
{
	char	**map_copy;
	int		start_x;
	int		start_y;
	int		result;

	map_copy = duplicate_map(parse->map, parse->map_height);
	if (!map_copy)
		return (0); // malloc error
	start_x = (int)(player->init_x);
	start_y = (int)(player->init_y);
	if (start_y < 0 || start_y >= parse->map_height
		|| start_x < 0 || start_x >= parse->map_width)
	{
		ft_free_str_array(map_copy);
		return (0); // player out of bounds
	}
	result = flood_fill(map_copy, parse, start_x, start_y);
	ft_free_str_array(map_copy);
	return (result);
}
