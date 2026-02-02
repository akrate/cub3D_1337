/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:57:09 by aoussama          #+#    #+#             */
/*   Updated: 2026/02/02 13:47:47 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools_game.h"

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
