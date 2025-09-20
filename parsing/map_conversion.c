#include "../cub3d.h"

int	pad_map_lines(t_parse *parse)
{
	int		i;
	int		len;
	char	*padded;

	if (!parse || !parse->map)
		return (0);
	i = 0;
	while (parse->map[i])
	{
		len = ft_strlen(parse->map[i]);
		if (len < parse->map_width)
		{
			padded = malloc(parse->map_width + 1);
			if (!padded)
				return (0); // malloc error
			ft_memcpy(padded, parse->map[i], len);
			ft_memset(padded + len, ' ', parse->map_width - len);
			padded[parse->map_width] = '\0';
			free(parse->map[i]);
			parse->map[i] = padded;
		}
		i++;
	}
	return (1);
}

static char	*duplicate_map_line(t_list *node)
{
	if (!node || !node->content)
		return (NULL);
	return (ft_strdup(node->content));
}

static void	free_partial_map(char **map, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(map[i++]);
	free(map);
}

static int	process_map_line(t_parse *parse, t_list *node, int index)
{
	int	len;

	parse->map[index] = duplicate_map_line(node);
	if (!parse->map[index])
		return (0);
	len = ft_strlen(parse->map[index]);
	if (len > parse->map_width)
		parse->map_width = len;
	return (1);
}

int	convert_map_list_to_array(t_list *map_lines, t_parse *parse)
{
	int		i;

	if (!map_lines || !parse)
		return (0);
	parse->map_height = ft_lstsize(map_lines);
	parse->map = malloc(sizeof(char *) * (parse->map_height + 1));
	if (!parse->map)
		return (0);
	i = 0;
	while (map_lines)
	{
		if (!process_map_line(parse, map_lines, i))
		{
			free_partial_map(parse->map, i);
			parse->map = NULL;
			return (0);
		}
		map_lines = map_lines->next;
		i++;
	}
	parse->map[i] = NULL;
	return (1);
}
