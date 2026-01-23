/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:57:09 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/23 10:10:03 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	int			map_x;
	int			map_y;
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	int			step_x;
	int			step_y;
	int			side;
}			t_ray;

int	is_wall_cell(t_data *data, int my, int mx)
{
	if (my < 0 || my >= data->map.height)
		return (1);
	if (mx < 0 || mx >= (int)ft_strlen(data->map.grid[my]))
		return (1);
	if (data->map.grid[my][mx] == '1' || data->map.grid[my][mx] == ' ')
		return (1);
	return (0);
}

void	init_step(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
}

void	dda_loop(t_data *data, t_ray *ray)
{
	while (!is_wall_cell(data, ray->map_y, ray->map_x))
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

void	init_ray(t_ray *ray, t_data *data, double dir_x, double dir_y)
{
	ray->pos_x = data->player.pos_x;
	ray->pos_y = data->player.pos_y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->dir_x = dir_x;
	ray->dir_y = dir_y;
	ray->side = 0;
}

void	init_delta(t_ray *ray)
{
	if (ray->dir_x == 0.0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
}

static double	get_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map_x - ray->pos_x + (1 - ray->step_x) / 2.0)
			/ ray->dir_x);
	return ((ray->map_y - ray->pos_y + (1 - ray->step_y) / 2.0) / ray->dir_y);
}

void	fill_hit(t_hit *hit, t_ray *ray)
{
	hit->perp_dist = get_perp_dist(ray);
	hit->hit_x = ray->pos_x + ray->dir_x * hit->perp_dist;
	hit->hit_y = ray->pos_y + ray->dir_y * hit->perp_dist;
	hit->hit = 1;
	hit->side = ray->side;
	hit->map_x = ray->map_x;
	hit->map_y = ray->map_y;
}

t_hit	cast_ray_dda(t_data *data, double ray_dir_x, double ray_dir_y)
{
	t_ray	ray;
	t_hit	hit;

	init_ray(&ray, data, ray_dir_x, ray_dir_y);
	init_delta(&ray);
	init_step(&ray);
	dda_loop(data, &ray);
	fill_hit(&hit, &ray);
	return (hit);
}
