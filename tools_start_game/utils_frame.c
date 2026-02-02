/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:30:52 by aoussama          #+#    #+#             */
/*   Updated: 2026/02/01 16:22:49 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools_game.h"

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
		{
			mlx_pixel_put(data->mlx.mlx, data->mlx.win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 11)
		{
			mlx_pixel_put(data->mlx.mlx, data->mlx.win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	compute_ray(t_data *data, t_column *c)
{
	double	camera_x;

	camera_x = 2.0 * c->x / (double)WIDTH - 1.0;
	c->rx = data->player.dir_x + data->player.plane_x * camera_x;
	c->ry = data->player.dir_y + data->player.plane_y * camera_x;
}

void	move_up_done(int key, t_data *data)
{
	double	nx;
	double	ny;
	double	speed;

	speed = 0.1;
	nx = data->player.pos_x;
	ny = data->player.pos_y;
	if (key == 119)
	{
		nx += data->player.dir_x * speed;
		ny += data->player.dir_y * speed;
	}
	if (key == 115)
	{
		nx -= data->player.dir_x * speed;
		ny -= data->player.dir_y * speed;
	}
	if (data->map.grid[(int)data->player.pos_y][(int)nx] != '1')
		data->player.pos_x = nx;
	if (data->map.grid[(int)ny][(int)data->player.pos_x] != '1')
		data->player.pos_y = ny;
}

void	move_left_right(int key, t_data *data)
{
	double	nx;
	double	ny;
	double	speed;

	speed = 0.1;
	nx = data->player.pos_x;
	ny = data->player.pos_y;
	if (key == 97)
	{
		nx -= data->player.plane_x * speed;
		ny -= data->player.plane_y * speed;
	}
	if (key == 100)
	{
		nx += data->player.plane_x * speed;
		ny += data->player.plane_y * speed;
	}
	if (data->map.grid[(int)data->player.pos_y][(int)nx] != '1')
		data->player.pos_x = nx;
	if (data->map.grid[(int)ny][(int)data->player.pos_x] != '1')
		data->player.pos_y = ny;
}
