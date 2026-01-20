/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:30:52 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/20 13:54:23 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


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
			mlx_pixel_put(data->mlx.mlx,data->mlx.win,x + j, y + i,color);
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
			mlx_pixel_put(data->mlx.mlx,data->mlx.win,x + j, y + i,color);
			j++;
		}
		i++;
	}
}


int	ray_hit_wall_step(t_data *data,double dirx,double diry,double *hit_x,double *hit_y)
{
	double	rx;
	double	ry;
	double	step;
	double	max_dist;
	double	dist;
	int		mx;
	int		my;

	rx = data->player.pos_x;
	ry = data->player.pos_y;

	step = 0.02;      
	max_dist = 50.0;  
	dist = 0.0;

	while (dist < max_dist)
	{
		rx += dirx * step;
		ry += diry * step;
		dist += step;

		mx = (int)rx;
		my = (int)ry;

		if (my < 0 || my >= data->map.height|| mx < 0|| mx >= (int)ft_strlen(data->map.grid[my]))
		{
			*hit_x = rx;
			*hit_y = ry;
			return (1);
		}

		if (data->map.grid[my][mx] == '1')
		{
			*hit_x = rx;
			*hit_y = ry;
			return (1);
		}
	}
	return (0);
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	double	dx = x1 - x0;
	double	dy = y1 - y0;
	int		steps = (int)fmax(fabs(dx), fabs(dy));
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	int		i;

	if (steps <= 0)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x0, y0, color);
		return ;
	}

	x_inc = dx / (double)steps;
	y_inc = dy / (double)steps;

	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}