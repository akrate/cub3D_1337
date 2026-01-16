#include "../includes/cub.h"

void	calculate_distance(t_global *global, double totalx, double totaly)
{
	if (global->ray.side == 0)
	{
		global->ray.distance = (totalx - global->ray.dx) * TILE_SIZE - 1;
	}
	else
	{
		global->ray.distance = (totaly - global->ray.dy) * TILE_SIZE - 1;
	}
}

void	perform_ray_march(t_global *g, double totalx, double totaly)
{
	g->ray.hit = 0;
	while (!g->ray.hit)
	{
		if (totalx < totaly)
		{
			totalx += g->ray.dx;
			g->ray.new_px += g->ray.stp_x;
			g->ray.side = 0;
		}
		else
		{
			totaly += g->ray.dy;
			g->ray.new_py += g->ray.stp_y;
			g->ray.side = 1;
		}
		if (g->ray.new_py < 0 || g->ray.new_py >= g->map->height
			|| g->ray.new_px < 0 || g->ray.new_px >= g->map->width)
		{
			g->ray.hit = 1;
			break ;
		}
		if (g->map->map[g->ray.new_py][g->ray.new_px] == '1')
			g->ray.hit = 1;
	}
	calculate_distance(g, totalx, totaly);
}

void	calculate_ray_direction(t_global *global, double posx, double posy)
{
	global->ray.dx = fabs(1.0 / cos(global->ray.angle * PI / 180.0));
	global->ray.dy = fabs(1.0 / sin(global->ray.angle * PI / 180.0));
	global->ray.new_px = (int)posx;
	global->ray.new_py = (int)posy;
}

void	calculate_step_and_total(t_global *global, double posx, double posy)
{
	double	totalx;
	double	totaly;

	if (cos(global->ray.angle * PI / 180.0) >= 0)
	{
		global->ray.stp_x = 1;
		totalx = (global->ray.new_px + 1.0 - posx) * global->ray.dx;
	}
	else
	{
		global->ray.stp_x = -1;
		totalx = (posx - global->ray.new_px) * global->ray.dx;
	}
	if (sin(global->ray.angle * PI / 180.0) >= 0)
	{
		global->ray.stp_y = 1;
		totaly = (global->ray.new_py + 1.0 - posy) * global->ray.dy;
	}
	else
	{
		global->ray.stp_y = -1;
		totaly = (posy - global->ray.new_py) * global->ray.dy;
	}
	perform_ray_march(global, totalx, totaly);
}

void	dda(t_global *global)
{
	double	posx;
	double	posy;

	posx = global->ray.start_x / TILE_SIZE;
	posy = global->ray.start_y / TILE_SIZE;
	calculate_ray_direction(global, posx, posy);
	calculate_step_and_total(global, posx, posy);
}