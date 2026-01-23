/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:08:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/23 19:10:09 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../cub3d.h"

void	compute_ray(t_data *data, int x, double *rx, double *ry)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	*rx = data->player.dir_x + data->player.plane_x * camera_x;
	*ry = data->player.dir_y + data->player.plane_y * camera_x;
}

void	compute_wall_height(t_hit h, int *start, int *end, int *hgt)
{
	*hgt = (int)(HEIGHT / h.perp_dist);
	*start = -(*hgt) / 2 + HEIGHT / 2;
	*end = (*hgt) / 2 + HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}

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

void	prepare_texture(
	t_data *data, t_hit h, double rx, double ry,
	t_img_tex **tex, int *tex_x)
{
	double	wall_x;

	*tex = get_wall_texture(data, h, rx, ry);
	if (h.side == 0)
		wall_x = h.hit_y;
	else
		wall_x = h.hit_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (*tex)->w);
	if (h.side == 0 && rx > 0)
		*tex_x = (*tex)->w - *tex_x - 1;
	if (h.side == 1 && ry < 0)
		*tex_x = (*tex)->w - *tex_x - 1;
}

void	draw_wall(
	t_data *data, int x, t_hit h,
	t_img_tex *tex, int tex_x,
	int start, int end)
{
	double	step;
	double	pos;
	int	y;
	int	color;

	step = (double)tex->h / (end - start + 1);
	pos = 0;
	y = start;
	while (y <= end)
	{
		color = get_tex_color(tex, tex_x, (int)pos);
		if (h.side == 1)
			color = (color >> 1) & 0x007F7F7F;
		put_pixel_to_img(&data->mlx, x, y, color);
		pos += step;
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

void	render_3d_walls(t_data *data)
{
	int			x;
	double		rx;
	double		ry;
	t_hit		h;
	int			start;
	int			end;
	int			height;
	t_img_tex	*tex;
	int			tex_x;

	x = 0;
	while (x < WIDTH)
	{
		compute_ray(data, x, &rx, &ry);
		h = cast_ray_dda(data, rx, ry);
		compute_wall_height(h, &start, &end, &height);
		draw_ceiling(data, x, start);
		prepare_texture(data, h, rx, ry, &tex, &tex_x);
		draw_wall(data, x, h, tex, tex_x, start, end);
		draw_floor(data, x, end);
		x++;
	}
	mlx_put_image_to_window(
		data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
