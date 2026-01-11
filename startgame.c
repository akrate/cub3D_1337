/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:16:19 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/11 11:19:24 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	x;
	double	y;

	dx = x1 - x0;
	dy = y1 - y0;

	steps = fabs(dx);
	if (fabs(dy) > steps)
		steps = fabs(dy);

	x = x0;
	y = y0;
	while (steps >= 0)
	{
		mlx_pixel_put(data->mlx.mlx,data->mlx.win, (int)x, (int)y, color);
		x += dx / steps;
		y += dy / steps;
		steps--;
	}
}

void	draw_fov(t_data *data)
{
	int	px;
	int	py;
	int	len;

	double	left_x;
	double	left_y;
	double	right_x;
	double	right_y;

	px = data->player.pos_x * TILE;
	py = data->player.pos_y * TILE;
	len = 120;

	/* 🖤 direction */
	draw_line(
		data,
		px, py,
		px + data->player.dir_x * len,
		py + data->player.dir_y * len,
		0x00000000
	);

	/* 🔴 left FOV */
	left_x = data->player.dir_x - data->player.plane_x;
	left_y = data->player.dir_y - data->player.plane_y;
	draw_line(
		data,
		px, py,
		px + left_x * len,
		py + left_y * len,
		0x00FF0000
	);

	/* 🔴 right FOV */
	right_x = data->player.dir_x + data->player.plane_x;
	right_y = data->player.dir_y + data->player.plane_y;
	draw_line(
		data,
		px, py,
		px + right_x * len,
		py + right_y * len,
		0x00FF0000
	);
}

//  void	put_pixel(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->mlx.addr + (y * data->mlx.line_len
// 			+ x * (data->mlx.bpp / 8));
// 	*(unsigned int *)dst = color;
// }
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
	draw_fov(data);
	// mlx_put_image_to_window(
	// 	data->mlx.mlx,
	// 	data->mlx.win,
	// 	data->mlx.img,
	// 	0, 0);
}
void	rotate_player(t_data *data, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rot)
		- data->player.dir_y * sin(rot);
	data->player.dir_y = old_dir_x * sin(rot)
		+ data->player.dir_y * cos(rot);

	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rot)
		- data->player.plane_y * sin(rot);
	data->player.plane_y = old_plane_x * sin(rot)
		+ data->player.plane_y * cos(rot);
	render_frame(data);
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
int moves(int keycode,t_data *data)
{
	double nx = data->player.pos_x;
    double ny = data->player.pos_y;
	
	if (keycode == 119) ny -= 0.1;
    if (keycode == 115) ny += 0.1;
    if (keycode == 97) nx -= 0.1;
    if (keycode == 100) nx += 0.1;


    // collision
    if (data->map.grid[(int)ny][(int)nx] != '1')
    {
        data->player.pos_x = nx;
        data->player.pos_y = ny;
    }

    render_frame(data);
    return (0);
}
int hook(int keycode,t_data *data)
{
	
	 if (keycode == 65307)
        ecs(data);
    else if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
        moves(keycode,data);
	else if (keycode == 65361) // ←
		rotate_player(data, -0.1);
	else if (keycode == 65363) // →
		rotate_player(data, 0.1);
    // else if (keycode == 2 || keycode == 124)
    //     printf("RIGHT (D / ARROW_RIGHT)");
    // else if (keycode == 1 || keycode == 125)
    //     printf("DOWN (S / ARROW_DOWN)");
    // else if (keycode == 13 || keycode == 126)
    //     printf("LEFT (A / ARROW_LEFT)");
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

