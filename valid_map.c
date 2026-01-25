/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:21:55 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/25 10:59:32 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_player_cell(t_data *data, int x, int y)
{
	data->map.player_count++;
	data->player.pos_x = (double)x + 0.4;
	data->player.pos_y = (double)y + 0.4;
	set_player_direction(data, data->map.grid[y][x]);
	if (!check_position_walls(data, x, y))
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_valid_content;

	if (!line || line[0] == '\0' || line[0] == '\n')
		return (0);
	i = 0;
	has_valid_content = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1' || is_player_char(line[i]))
			has_valid_content = 1;
		i++;
	}
	return (has_valid_content);
}

int	check_position_walls(t_data *data, int x, int y)
{
	char	c;

	c = get_char_at(data, x - 1, y);
	if (c == ' ' || c == '\0')
		return (0);
	c = get_char_at(data, x + 1, y);
	if (c == ' ' || c == '\0')
		return (0);
	c = get_char_at(data, x, y - 1);
	if (c == ' ' || c == '\0')
		return (0);
	c = get_char_at(data, x, y + 1);
	if (c == ' ' || c == '\0')
		return (0);
	return (1);
}

int	validate_map_characters(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (!is_valid_char(data->map.grid[y][x]))
				return (print_error("Invalid character in map"), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_data *data)
{
	if (!validate_map_characters(data))
		return (0);
	if (!check_player(data))
		return (0);
	if (!validate_walls(data))
		return (0);
	return (1);
}
