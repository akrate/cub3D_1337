/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:16:19 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/19 10:11:35 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_data *data)
{
	int	px;
	int	py;
	int	len;

	double	left_x;
	double	left_y;
	double	right_x;
	double	right_y;

	px = (data->player.pos_x + 0.1) * TILE;
	py = (data->player.pos_y + 0.1)  * TILE;
	len = 120;

	/* 🖤 direction */
	draw_line(
		data,
		px, py,
		px + data->player.dir_x * len,
		py + data->player.dir_y * len,
		0x0000FF00
	);

	/* 🔴 left FOV */
	left_x = data->player.dir_x - data->player.plane_x;
	left_y = data->player.dir_y - data->player.plane_y;
	draw_line(
		data,
		px, py,
		px + left_x * len,
		py + left_y * len,
		0x0000FF00
	);

	/* 🔴 right FOV */
	right_x = data->player.dir_x + data->player.plane_x;
	right_y = data->player.dir_y + data->player.plane_y;
	draw_line(
		data,
		px, py,
		px + right_x * len,
		py + right_y * len,
		0x0000FF00
	);
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (print_error("mlx_init failed"));

	data->mlx.win = mlx_new_window(data->mlx.mlx, data->map.width * 32, data->map.height * 32, "cub3D");

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->map.width * 32, data->map.height * 32);

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
		load_all_textures(data);   // ⭐ جديد
    render_frame(data);
	mlx_hook(data->mlx.win,2,1,hook,data);
	mlx_hook(data->mlx.win, 17, 0, button_x, data);
    mlx_loop(data->mlx.mlx);
}

