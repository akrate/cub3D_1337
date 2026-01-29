/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:21:20 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/29 15:45:47 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	get_line_length(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

int	copy_line_to_map(char *line, char *map_line, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		map_line[i] = line[i];
		i++;
	}
	map_line[len] = '\0';
	return (1);
}

int	add_map_line(t_data *data, char *line)
{
	char	**new_map;
	char	*map_line;
	int		len;

	len = get_line_length(line);
	if (len > data->map.width)
		data->map.width = len;
	new_map = realloc_map(data->map.grid, data->map.height + 2);
	data->map.grid = new_map;
	map_line = ft_malloc(len + 1, &(set_get_data(NULL)->lst_gc_g));
	copy_line_to_map(line, map_line, len);
	data->map.grid[data->map.height] = map_line;
	data->map.grid[data->map.height + 1] = NULL;
	data->map.height++;
	return (1);
}

int	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	handle_map_line(t_data *data, char *line, int *map_started)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		if (!add_map_line(data, line))
			return (0);
	}
	else if (*map_started == 1)
	{
		if (is_only_spaces(line) || line[0] == '\n')
		{
			print_error("Newline inside map");
			return (0);
		}
		print_error("Invalid character in map");
		return (0);
	}
	return (1);
}
