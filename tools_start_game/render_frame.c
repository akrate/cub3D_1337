/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/18 14:39:41 by aoussama         ###   ########.fr       */
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
void	render_3d_walls(t_data *data)
{
	int		x;
	int		rays;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	t_hit	h;

	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	rays = WIDTH;   // عمود لكل pixel فالعرض
	x = 0;
	while (x < rays)
	{
		/* 1) فين ray فالعين */
		cameraX = 2.0 * x / (double)rays - 1.0;

		/* 2) اتجاه ray */
		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

		/* 3) DDA */
		h = cast_ray_dda(data, rayDirX, rayDirY);

		/* 4) طول العمود */
		lineHeight = (int)(HEIGHT / h.perp_dist);

		/* 5) بداية ونهاية الرسم */
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		drawEnd = lineHeight / 2 + HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		/* 6) لون (مؤقت بلا texture) */
		if (h.side == 0)
			draw_vertical_line(data, x, drawStart, drawEnd, 0x00FF0000);
		else
			draw_vertical_line(data, x, drawStart, drawEnd, 0x00990000);

		x++;
	}
}

// void	draw_rays(t_data *data)
// {
// 	int		i;
// 	int		px;
// 	int		py;
// 	double	cameraX;
// 	double	ray_x;
// 	double	ray_y;
// 	int		len;

// 	px = data->player.pos_x * TILE;
// 	py = data->player.pos_y * TILE;
// 	len = 120;

// 	i = 0;
// 	while (i < 300) // عدد rays
// 	{
// 		cameraX = 2.0 * i / 300.0 - 1.0;

// 		ray_x = data->player.dir_x
// 			+ data->player.plane_x * cameraX;
// 		ray_y = data->player.dir_y
// 			+ data->player.plane_y * cameraX;

// 		draw_line(
// 			data,
// 			px, py,
// 			px + ray_x * len,
// 			py + ray_y * len,
// 			0x00AAAAAA // لون رمادي
// 		);
// 		i++;
// 	}
// }
void	draw_rays_dda(t_data *data)
{
	int		i;
	int		rays;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	t_hit	h;

	int		px_pix;
	int		py_pix;

	rays = WIDTH;
	px_pix = (int)((data->player.pos_x + 0.1)* TILE);
	py_pix = (int)((data->player.pos_y + 0.1)* TILE);

	i = 0;
	while (i < rays)
	{
		/* cameraX من -1 حتى +1 */
		cameraX = 2.0 * i / (double)rays - 1.0;

		/* اتجاه ray */
		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

		/* DDA hit */
		h = cast_ray_dda(data, rayDirX, rayDirY);

		/* رسم من player حتى hit point */
		draw_line(
			data,
			px_pix, py_pix,
			(int)(h.hit_x * TILE), (int)(h.hit_y * TILE),
			0x00AAAAAA
		);

		i++;
	}
}

// void	draw_rays(t_data *data)
// {
// 	int		i;
// 	double	cameraX;
// 	double	rayx;
// 	double	rayy;
// 	double	hx;
// 	double	hy;

// 	int		px_pix;
// 	int		py_pix;


// 	px_pix = (data->player.pos_x + 0.1) * TILE;
// 	py_pix = (data->player.pos_y + 0.1) * TILE;

// 	i = 0;
// 	while (i < 300)
// 	{
// 		cameraX = 2.0 * i / 300.0 - 1.0;
// 		rayx = data->player.dir_x + data->player.plane_x * cameraX;
// 		rayy = data->player.dir_y + data->player.plane_y * cameraX;
		

// 		ray_hit_wall_step(data, rayx, rayy, &hx, &hy);

// 			draw_line(data,px_pix, py_pix,(int)(hx * TILE), (int)(hy * TILE),0x00AAAAAA);
// 			// usleep(900);

// 		i++;
// 	}
// }

void	draw_map_2d(t_data *data)
{
	int	y;
	int	x;
	char	c;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(data->map.grid[y]))
		{
			c = data->map.grid[y][x];
			// if ()
			if (c == '1')
				draw_square(data, x * TILE, y * TILE, 0x00FF0000); // 🔴 wall
			else if (c != ' ')
				draw_square(data, x * TILE, y * TILE, 0xFFFFFF); // ⬛ empty
			
			x++;
		}
		y++;
	}
	draw_player(data, data->player.pos_x * TILE, data->player.pos_y * TILE, 0x0000FF00); // 🔵 player
}

void	render_frame(t_data *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	// draw_map_2d(data);
    // draw_fov(data);
	render_3d_walls(data);
	// draw_rays_dda(data);

}