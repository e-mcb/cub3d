#include "cub3d.h"

void	free_parse(t_parse *parse)
{
	int	i;

	if (!parse)
		return ;
	free(parse->texture_north);
	free(parse->texture_south);
	free(parse->texture_west);
	free(parse->texture_east);
	if (parse->map)
	{
		i = 0;
		while (i < parse->map_height)
		{
			free(parse->map[i]);
			i++;
		}
		free(parse->map);
		parse->map = NULL;
	}
}
