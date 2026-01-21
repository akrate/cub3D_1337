/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:35:45 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/21 09:50:58 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	button_x(t_data *game)
{
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	free_textures(game);
	if (game->mlx.img)
    	mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.mlx && game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	
	exit(0);
}

static void	rotate_player(t_data *data, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rot) - data->player.dir_y * sin(rot);
	data->player.dir_y = old_dir_x * sin(rot) + data->player.dir_y * cos(rot);
	printf("rot == %f\n\nold_dir_x == %f\ndir x == %f\ndir y == %f\n",rot,old_dir_x,data->player.dir_x,data->player.dir_y);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rot) - data->player.plane_y * sin(rot);
	data->player.plane_y = old_plane_x * sin(rot) + data->player.plane_y * cos(rot);
	printf("old_plane_x == %f\nplane_x == %f\nplane_y == %f\n",old_plane_x,data->player.plane_x,data->player.plane_y);

}
static void	move_player(int keycode, t_data *data)
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
	}
	if (keycode == 115) // S
	{
		nx -= data->player.dir_x * speed;
		ny -= data->player.dir_y * speed;
	}
	if (keycode == 97) // A
	{
		nx -= data->player.plane_x * speed;
		ny -= data->player.plane_y * speed;
	}
	if (keycode == 100) // D
	{
		nx += data->player.plane_x * speed;
		ny += data->player.plane_y * speed;
	}
	if (data->map.grid[(int)data->player.pos_y][(int)nx] != '1' && data->map.grid[(int)ny][(int)data->player.pos_x] != '1')
		data->player.pos_x = nx;
	if (data->map.grid[(int)ny][(int)data->player.pos_x] != '1' && data->map.grid[(int)data->player.pos_y][(int)nx] != '1')
		data->player.pos_y = ny;
}
static void	ecs(t_data *game)
{
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	free_textures(game);
	if (game->mlx.img)
    	mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.mlx && game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	
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
    else if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
        move_player(keycode,data);
	else if (keycode == 65361) // ←
		rotate_player(data, -0.1);
	else if (keycode == 65363) // →
		rotate_player(data, 0.1);
	render_frame(data);
	
    return (0);
}
