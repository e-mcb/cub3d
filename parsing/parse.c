#include "../cub3d.h"

int	convert_map_list_to_array(t_list *map_lines, t_parse *parse)
{
	t_list	*current;
	int		i;
	int		len;

	if (!map_lines || !parse)
		return (0);
	parse->map_height = ft_lstsize(map_lines);
	parse->map = malloc(sizeof(char *) * (parse->map_height + 1));
	if (!parse->map)
		return (0); // malloc error
	current = map_lines;
	i = 0;
	while (current)
	{
		parse->map[i] = ft_strdup(current->content);
		if (!parse->map[i])
		{
			while (i-- > 0)
				free(parse->map[i]);
			free(parse->map);
			parse->map = NULL;
			return (0);
		}
		len = ft_strlen(parse->map[i]);
		if (len > parse->map_width)
			parse->map_width = len;
		current = current->next;
		i++;
	}
	parse->map[i] = NULL;
	return (1);
}

int	read_map(char *filename, t_parse *parse)
{
	char	*line;
	bool	map_started;
	t_list	*map_lines;
	int		fd;

	map_started = false;
	map_lines = NULL;
	if (!filename || !parse)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (is_texture_or_color(line) && !map_started)
			parse_texture_or_color(line, parse);
		else if (line[0] == '\n' && !map_started)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else
			map_started = true;
		if (map_started)
			ft_lstadd_back(&map_lines, ft_lstnew(line));
		else
			free(line);
		line = get_next_line(fd);
	}
	if (!convert_map_list_to_array(map_lines, parse))
	{
		ft_lstclear(&map_lines, free);
		return (1); // error
	}
	ft_lstclear(&map_lines, free);
	close (fd);
}

