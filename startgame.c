/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:16:19 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/09 12:08:21 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_len
			+ x * (data->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}
static void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
		{
			put_pixel(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

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
			if (c == '1')
				draw_square(data, x * TILE, y * TILE, 0x00FF0000); // 🔴 wall
			else if (c == '0')
				draw_square(data, x * TILE, y * TILE, 0x00000000); // ⬛ empty
			else if (c == 'E')
				draw_square(data, x * TILE, y * TILE, 0x0000FF00); // 🔵 player
			x++;
		}
		y++;
	}
}


void	render_frame(t_data *data)
{
	int	x;
	int	y;

	// background
	y = 0;
	while (y < data->map.height * TILE)
	{
		x = 0;
		while (x < data->map.width * TILE)
		{
			put_pixel(data, x, y, 0x00222222);
			x++;
		}
		y++;
	}

	// draw map
	draw_map_2d(data);

	mlx_put_image_to_window(
		data->mlx.mlx,
		data->mlx.win,
		data->mlx.img,
		0, 0);
}


void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (print_error("mlx_init failed"));

	data->mlx.win = mlx_new_window(data->mlx.mlx, data->map.width * 30, data->map.height  * 30, "cub3D");

	data->mlx.img = mlx_new_image(data->mlx.mlx, 1024, 768);

	data->mlx.addr = mlx_get_data_addr(
		data->mlx.img,
		&data->mlx.bpp,
		&data->mlx.line_len,
		&data->mlx.endian
	);
}

void start_game(t_data *data)
{
    init_mlx(data);
    render_frame(data);
    mlx_loop(data->mlx.mlx);
}

// void render_frame(t_data *data)
// {
//     // draw_ceiling_and_floor(data);
//     mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
// }
