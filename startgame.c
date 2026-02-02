/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:16:19 by melkhatr          #+#    #+#             */
/*   Updated: 2026/02/02 13:55:10 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		print_error("mlx_init failed");
		ecs(data, 1);
	}
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->mlx.win)
	{
		print_error("mlx_window failed");
		ecs(data, 1);
	}
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img)
	{
		print_error("mlx_image failed");
		ecs(data, 1);
	}
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.endian);
	if (!data->mlx.addr)
	{
		print_error("mlx_addr failed");
		ecs(data, 1);
	}
}

void	start_game(t_data *data)
{
	init_mlx(data);
	load_all_textures(data);
	render_frame(data);
	mlx_hook(data->mlx.win, 2, 1, hook, data);
	mlx_hook(data->mlx.win, 17, 0, button_x, data);
	mlx_loop(data->mlx.mlx);
}
