/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:12:39 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/29 15:45:47 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	set_north_south(t_data *data, char orientation)
{
	if (orientation == 'N')
	{
		data->player.dir_x = 0.0001;
		data->player.dir_y = -1.0001;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0.0001;
	}
	else if (orientation == 'S')
	{
		data->player.dir_x = 0.0001;
		data->player.dir_y = 1.0001;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0.0001;
	}
}

void	set_east_west(t_data *data, char orientation)
{
	if (orientation == 'E')
	{
		data->player.dir_x = 1.0001;
		data->player.dir_y = 0.0001;
		data->player.plane_x = 0.0001;
		data->player.plane_y = 0.66;
	}
	else if (orientation == 'W')
	{
		data->player.dir_x = -1.0001;
		data->player.dir_y = 0.0001;
		data->player.plane_x = 0.0001;
		data->player.plane_y = -0.66;
	}
}

void	set_player_direction(t_data *data, char orientation)
{
	data->player.orientation = orientation;
	if (orientation == 'N' || orientation == 'S')
		set_north_south(data, orientation);
	else if (orientation == 'E' || orientation == 'W')
		set_east_west(data, orientation);
}

int	parse_map(int fd, t_data *data)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!handle_map_line(data, line, &map_started))
			return (0);
		line = get_next_line(fd);
	}
	if (data->map.height == 0)
		return (print_error("No map found"), 0);
	return (1);
}
