/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/02/02 14:27:55 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools_game.h"

void	compute_wall_height(t_column *c)
{
	c->height = (int)(HEIGHT / c->hit.perp_dist);
	c->start_raw = -c->height / 2 + HEIGHT / 2;
	c->start = c->start_raw;
	c->end = c->height / 2 + HEIGHT / 2;
	if (c->start < 0)
		c->start = 0;
	if (c->end >= HEIGHT)
		c->end = HEIGHT - 1;
}

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (!mlx->addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_data *data)
{
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img)
	{
		print_error("mlx_new_image failed");
		ecs(data, 1);
	}
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.endian);
	if (!data->mlx.addr)
	{
		print_error("mlx_get_data_addr failed");
		ecs(data, 1);
	}
	render_3d_walls(data);
}
