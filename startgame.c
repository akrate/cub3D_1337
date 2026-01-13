/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:16:19 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/13 13:33:40 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	double	dx = x1 - x0;
	double	dy = y1 - y0;
	int		steps = (int)fmax(fabs(dx), fabs(dy));
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	int		i;

	if (steps <= 0)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x0, y0, color);
		return ;
	}

	x_inc = dx / (double)steps;
	y_inc = dy / (double)steps;

	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

int	ray_hit_wall_step(t_data *data,double dirx,double diry,double *hit_x,double *hit_y)
{
	double	rx;
	double	ry;
	double	step;
	double	max_dist;
	double	dist;
	int		mx;
	int		my;

	/* بداية ray من اللاعب (map units) */
	rx = data->player.pos_x;
	ry = data->player.pos_y;

	step = 0.02;      /* صغّرها إلا كان ray كيطفر */
	max_dist = 50.0;  /* أقصى مسافة (باش ما تبقاش loop دايرة) */
	dist = 0.0;

	while (dist < max_dist)
	{
		rx += dirx * step;
		ry += diry * step;
		dist += step;

		mx = (int)rx;
		my = (int)ry;

		/* خرج من الماب = حبّس ray */
		if (my < 0 || my >= data->map.height
			|| mx < 0
			|| mx >= (int)ft_strlen(data->map.grid[my]))
		{
			*hit_x = rx;
			*hit_y = ry;
			return (1);
		}

		/* ضرب wall أو void */
		if (data->map.grid[my][mx] == '1')
		{
			*hit_x = rx;
			*hit_y = ry;
			return (1);
		}
	}
	return (0);
}
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
	while (i < 300)
	{
		cameraX = 2.0 * i / 1024 - 1.0;
		rayx = data->player.dir_x + data->player.plane_x * cameraX;
		rayy = data->player.dir_y + data->player.plane_y * cameraX;


		if (ray_hit_wall_step(data, rayx, rayy, &hx, &hy))
		{

			draw_line(
				data,
				px_pix, py_pix,
				(int)(hx * TILE), (int)(hy * TILE),
				0x00AAAAAA
			);
		}
		i++;
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

// 	px = (data->player.pos_x + 0.1) * TILE;
// 	py = (data->player.pos_y + 0.1) * TILE;
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
		0x00000000
	);

	/* 🔴 right FOV */
	right_x = data->player.dir_x + data->player.plane_x;
	right_y = data->player.dir_y + data->player.plane_y;
	draw_line(
		data,
		px, py,
		px + right_x * len,
		py + right_y * len,
		0x00000000
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
	while (i < 11)
	{
		j = 0;
		while (j < 11)
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
	// mlx_clear_window(data->mlx.mlx, data->mlx.win);
	draw_map_2d(data);
	// draw_fov(data);
	draw_rays(data);
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

	data->mlx.win = mlx_new_window(data->mlx.mlx, data->map.width * 32, data->map.height * 32, "cub3D");

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->map.width * 32, data->map.height * 32);

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
// int moves(int keycode,t_data *data)
// {
// 	double nx = data->player.pos_x;
//     double ny = data->player.pos_y;
	
// 	if (keycode == 119) ny -= 0.1;
//     if (keycode == 115) ny += 0.1;
//     if (keycode == 97) nx -= 0.1;
//     if (keycode == 100) nx += 0.1;


//     // collision
//     if (data->map.grid[(int)ny][(int)nx] != '1')
//     {
//         data->player.pos_x = nx;
//         data->player.pos_y = ny;
//     }

//     render_frame(data);
//     return (0);
// }
void	move_player(int keycode, t_data *data)
{
	double	nx;
	double	ny;
	double	speed;

	speed = 0.1;
	nx = data->player.pos_x;
	ny = data->player.pos_y;

	if (keycode == 119) // W
	{
		nx += data->player.dir_x * speed;
		ny += data->player.dir_y * speed;
		printf("pos_x == %f\npos_y == %f\n\n",data->player.pos_x,data->player.pos_y);

		printf("dir_x == %f\ndir_y == %f\n\n",data->player.dir_x,data->player.dir_y);
		printf("nx == %f\nny == %f\n\n",nx,ny);
		printf("-----------------------------------------------\n");

	}
	if (keycode == 115) // S
	{
		nx -= data->player.dir_x * speed;
		ny -= data->player.dir_y * speed;
		printf("pos_x == %f\npos_y == %f\n\n",data->player.pos_x,data->player.pos_y);

		printf("dir_x == %f\ndir_y == %f\n\n",data->player.dir_x,data->player.dir_y);
		printf("nx == %f\nny == %f\n\n",nx,ny);

		printf("-----------------------------------------------\n");

	}
	if (keycode == 97) // A
	{
		nx -= data->player.plane_x * speed;
		ny -= data->player.plane_y * speed;
		printf("pos_x == %f\npos_y == %f\n\n",data->player.pos_x,data->player.pos_y);

		printf("dir_x == %f\ndir_y == %f\n\n",data->player.dir_x,data->player.dir_y);
		printf("nx == %f\nny == %f\n\n",nx,ny);

		printf("-----------------------------------------------\n");

	}
	if (keycode == 100) // D
	{
		nx += data->player.plane_x * speed;
		ny += data->player.plane_y * speed;
		printf("pos_x == %f\npos_y == %f\n\n",data->player.pos_x,data->player.pos_y);

		printf("dir_x == %f\ndir_y == %f\n\n",data->player.dir_x,data->player.dir_y);
		printf("nx == %f\nny == %f\n\n",nx,ny);

		printf("-----------------------------------------------\n");
	}

	if (data->map.grid[(int)data->player.pos_y][(int)nx] != '1')
		data->player.pos_x = nx;
	if (data->map.grid[(int)ny][(int)data->player.pos_x] != '1')
		data->player.pos_y = ny;
    render_frame(data);

}

int hook(int keycode,t_data *data)
{
	
	 if (keycode == 65307)
        ecs(data);
    else if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
        move_player(keycode,data);
	else if (keycode == 65361) // ←
		rotate_player(data, -0.1);
	else if (keycode == 65363) // →
		rotate_player(data, 0.1);
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

