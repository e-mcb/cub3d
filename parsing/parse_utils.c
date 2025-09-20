#include "../cub3d.h"

int	is_texture_or_color(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	parse_color_line(char *line, int color[3])
{
	char	**components;
	int		i;

	i = 0;
	components = ft_split(line, ',');
	if (!components)
		return (0); // malloc errors
	if (array_size(components) != 3)
	{
		ft_free_str_array(components);
		return (0); // invalid colours
	}
	while (i < 3)
	{
		color[i] = ft_atoi(components[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			ft_free_str_array(components);
			return (0);
		}
		i++;
	}
	ft_free_str_array(components);
	return (1);
}

void	parse_texture_or_color(char *line, t_parse *parse)
{
	char	*trimmed;
	char	*color_str;

	trimmed = ft_strtrim(line, " \n\t\v\f\r");
	if (!trimmed)
		return ;//malloc error
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		parse->texture_north = ft_strtrim(trimmed + 3, " \n\t\v\f\r");
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		parse->texture_south = ft_strtrim(trimmed + 3, " \n\t\v\f\r");
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		parse->texture_west = ft_strtrim(trimmed + 3, " \n\t\v\f\r");
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		parse->texture_east = ft_strtrim(trimmed + 3, " \n\t\v\f\r");
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		color_str = ft_strtrim(trimmed + 2, " \n\t\v\f\r");
		if (!parse_color_line(color_str, parse->floor_color))
		{
			//errors
		}
		free(color_str);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		color_str = ft_strtrim(trimmed + 2, " \n\t\v\f\r");
		if (!parse_color_line(color_str, parse->ceiling_color))
		{
			//errors
		}
		free(color_str);
	}
	free(trimmed);
}
