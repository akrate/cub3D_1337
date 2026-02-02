/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:08:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/02/02 14:15:00 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools_game.h"

void	draw_ceiling(t_data *data, int x, int end)
{
	int	y;

	y = 0;
	while (y < end)
	{
		put_pixel_to_img(&data->mlx, x, y, data->ceiling.hex);
		y++;
	}
}

void	draw_floor(t_data *data, int x, int start)
{
	int	y;

	y = start + 1;
	while (y < HEIGHT)
	{
		put_pixel_to_img(&data->mlx, x, y, data->floor.hex);
		y++;
	}
}

void	prepare_texture(t_data *data, t_column *c)
{
	double	wall_x;

	c->tex = get_wall_texture(data, c->hit, c->rx, c->ry);
	if (c->hit.side == 0)
		wall_x = c->hit.hit_y;
	else
		wall_x = c->hit.hit_x;
	wall_x -= floor(wall_x);
	c->tex_x = (int)(wall_x * c->tex->w);
	c->tex_x = c->tex->w - c->tex_x - 1;
}

void	draw_wall(t_data *data, t_column *c)
{
	double	step;
	double	pos;
	int		y;
	int		tex_y;
	int		color;

	step = (double)c->tex->h / (double)c->height;
	pos = (c->start - c->start_raw) * step;
	y = c->start;
	while (y <= c->end)
	{
		tex_y = (int)pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= c->tex->h)
			tex_y = c->tex->h - 1;
		color = get_tex_color(c->tex, c->tex_x, tex_y);
		if (c->hit.side == 1)
			color = (color >> 1) & 0x007F7F7F;
		put_pixel_to_img(&data->mlx, c->x, y, color);
		pos += step;
		y++;
	}
}

void	render_3d_walls(t_data *data)
{
	t_column	c;

	c.x = 0;
	while (c.x < WIDTH)
	{
		compute_ray(data, &c);
		c.hit = cast_ray_dda(data, c.rx, c.ry);
		compute_wall_height(&c);
		draw_ceiling(data, c.x, c.start);
		prepare_texture(data, &c);
		draw_wall(data, &c);
		draw_floor(data, c.x, c.end);
		c.x++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
