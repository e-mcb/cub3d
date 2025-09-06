#include "../cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' ||
	c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
int	is_cardinal(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int validate_map_content(char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			char c = map[i][j];
			if (!is_valid_map_char(c))
			{
				return (0); //Error
			}
			if (is_cardinal(c))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		return (0); //Error
	}
	if (player_count > 1)
	{
		return (0); // Error
	}
	return (1);
}
