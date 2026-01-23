/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/23 19:09:02 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_vertical_line(t_data *data, int x, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y <= y_end)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, color);
		y++;
	}
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
void	draw_crosshair(t_data *data)
{
	int	cx;
	int	cy;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;

	i = -6;
	while (i <= 6)
	{
		put_pixel_to_img(&data->mlx, cx + i, cy, 0x00FF0000);
		i++;
	}

	i = -6;
	while (i <= 6)
	{
		put_pixel_to_img(&data->mlx, cx, cy + i, 0x00FF0000);
		i++;
	}
}

// void	render_3d_walls(t_data *data)
// {
// 	int			x;
// 	double		cameraX;
// 	double		rayDirX;
// 	double		rayDirY;
// 	t_hit		h;

// 	int			lineHeight;
// 	int			drawStart;
// 	int			drawEnd;

// 	t_img_tex	*tex;
// 	double		wall_x;
// 	int			tex_x;

// 	double		step;
// 	double		tex_pos;
// 	int			y;
// 	int			tex_y;
// 	int			color;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		cameraX = 2.0 * x / (double)WIDTH - 1.0;

// 		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
// 		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

// 		h = cast_ray_dda(data, rayDirX, rayDirY);

// 		lineHeight = (int)(HEIGHT / h.perp_dist);

// 		drawStart = -lineHeight / 2 + HEIGHT / 2;
// 		drawEnd = lineHeight / 2 + HEIGHT / 2;

// 		if (drawStart < 0)
// 			drawStart = 0;
// 		if (drawEnd >= HEIGHT)
// 			drawEnd = HEIGHT - 1;

// 		y = 0;
// 		while (y < drawStart)
// 		{
// 			put_pixel_to_img(&data->mlx, x, y, data->ceiling.hex);
// 			y++;
// 		}

// 		tex = get_wall_texture(data, h, rayDirX, rayDirY);

// 		if (h.side == 0)
// 			wall_x = h.hit_y;
// 		else
// 			wall_x = h.hit_x;

// 		wall_x -= floor(wall_x);
// 		tex_x = (int)(wall_x * tex->w);

// 		if (h.side == 0 && rayDirX > 0)
// 			tex_x = tex->w - tex_x - 1;
// 		if (h.side == 1 && rayDirY < 0)
// 			tex_x = tex->w - tex_x - 1;

// 		step = (double)tex->h / lineHeight;
// 		tex_pos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

// 		y = drawStart;
// 		while (y <= drawEnd)
// 		{
// 			tex_y = (int)tex_pos;
// 			if (tex_y < 0)
// 				tex_y = 0;
// 			if (tex_y >= tex->h)
// 				tex_y = tex->h - 1;

// 			color = get_tex_color(tex, tex_x, tex_y);

// 			if (h.side == 1)
// 				color = (color >> 1) & 0x007F7F7F;

// 			put_pixel_to_img(&data->mlx, x, y, color);

// 			tex_pos += step;
// 			y++;
// 		}

// 		y = drawEnd + 1;
// 		while (y < HEIGHT)
// 		{
// 			put_pixel_to_img(&data->mlx, x, y, data->floor.hex);
// 			y++;
// 		}

// 		x++;
// 	}

// 	mlx_put_image_to_window(
// 		data->mlx.mlx,
// 		data->mlx.win,
// 		data->mlx.img,
// 		0, 0
// 	);
// }


void	render_frame(t_data *data)
{

	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);

	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img)
		print_error("mlx_new_image failed");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,&data->mlx.bpp,&data->mlx.line_len,&data->mlx.endian);
	if (!data->mlx.addr)
		print_error("mlx_get_data_addr failed");
	render_3d_walls(data);
	draw_crosshair(data);
	mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,data->mlx.img,0, 0
	);
}
