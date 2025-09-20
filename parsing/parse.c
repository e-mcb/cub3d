#include "../cub3d.h"

static int	read_map_lines(int fd, t_parse *parse, t_list **map_lines)
{
	char	*line;
	bool	map_started;

	map_started = false;
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
			ft_lstadd_back(map_lines, ft_lstnew(line));
		else
			free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static int	finalize_map(t_parse *parse, t_list *map_lines)
{
	if (!convert_map_list_to_array(map_lines, parse))
	{
		ft_lstclear(&map_lines, free);
		return (1);
	}
	if (!pad_map_lines(parse))
	{
		ft_lstclear(&map_lines, free);
		return (1);
	}
	ft_lstclear(&map_lines, free);
	return (0);
}

int	read_map(char *filename, t_parse *parse)
{
	t_list	*map_lines;
	int		fd;

	if (!filename || !parse)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read_map_lines(fd, parse, &map_lines))
		return (1);
	close(fd);
	if (finalize_map(parse, map_lines))
		return (1);
	return (0);
}
