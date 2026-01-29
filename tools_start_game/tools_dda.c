/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 12:07:02 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/29 15:38:26 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools_game.h"

void	init_ray(t_ray *ray, t_data *data, double dir_x, double dir_y)
{
	ray->pos_x = data->player.pos_x;
	ray->pos_y = data->player.pos_y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->dir_x = dir_x;
	ray->dir_y = dir_y;
	ray->side = 0;
}

int	is_wall_cell(t_data *data, int my, int mx)
{
	if (mx < 0 || mx >= (int)ft_strlen(data->map.grid[my]))
		return (1);
	if (data->map.grid[my][mx] == '1' || data->map.grid[my][mx] == ' ')
		return (1);
	return (0);
}

void	init_step(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
}
