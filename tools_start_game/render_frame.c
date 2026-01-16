/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/16 11:22:32 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rays(t_data *data)
{
	int		i;
	double	cameraX;
	double	rayx;
	double	rayy;
	double	hx;
	double	hy;

	int		px_pix;
	int		py_pix;


	px_pix = (data->player.pos_x + 0.1) * TILE;
	py_pix = (data->player.pos_y + 0.1) * TILE;

	i = 0;
	while (i < 600)
	{
		cameraX = 2.0 * i / 1024 - 1.0;
		rayx = data->player.dir_x + data->player.plane_x * cameraX;
		rayy = data->player.dir_y + data->player.plane_y * cameraX;
		

		ray_hit_wall_step(data, rayx, rayy, &hx, &hy);

			draw_line(data,px_pix, py_pix,(int)(hx * TILE), (int)(hy * TILE),0x00AAAAAA);
			// usleep(900);

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
	draw_map_2d(data);
    draw_fov(data);
	draw_rays(data);

}