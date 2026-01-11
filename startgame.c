/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:16:19 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/11 10:05:25 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
 void	put_pixel(t_data *data, int x, int y, int color)
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
			// put_pixel(data, x + j, y + i, color);
			mlx_pixel_put(data->mlx.mlx,data->mlx.win,x + j, y + i,color);
			// usleep(250);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			// put_pixel(data, x + j, y + i, color);
			mlx_pixel_put(data->mlx.mlx,data->mlx.win,x + j, y + i,color);
			// usleep(250);
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

	// mlx_put_image_to_window(
	// 	data->mlx.mlx,
	// 	data->mlx.win,
	// 	data->mlx.img,
	// 	0, 0);
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
void	ecs(t_data *game)
{
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	if (game->mlx.mlx && game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.img)
    	mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	
	exit(0);
}
int hook(int keycode,t_data *data)
{
	
	 if (keycode == 65307)
        ecs(data);
    else if (keycode == 0 || keycode == 123)
        printf("LEFT (A / ARROW_LEFT)");
    else if (keycode == 2 || keycode == 124)
        printf("RIGHT (D / ARROW_RIGHT)");
    else if (keycode == 1 || keycode == 125)
        printf("DOWN (S / ARROW_DOWN)");
    else if (keycode == 13 || keycode == 126)
        printf("LEFT (A / ARROW_LEFT)");
    else
        printf("%d\n", keycode);
    return (0);
}
int	button_x(t_data *game)
{
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	if (game->mlx.mlx && game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.img)
    	mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	exit(0);
}
void start_game(t_data *data)
{
    init_mlx(data);
    render_frame(data);
	mlx_hook(data->mlx.win,2,1,hook,data);
	mlx_hook(data->mlx.win, 17, 0, button_x, data);
    mlx_loop(data->mlx.mlx);
}

