/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:57:09 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/20 10:56:56 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



static int	is_wall_cell(t_data *data, int my, int mx)
{
	if (my < 0 || my >= data->map.height)
		return (1);
	if (mx < 0 || mx >= (int)ft_strlen(data->map.grid[my]))
		return (1);
	if (data->map.grid[my][mx] == '1' || data->map.grid[my][mx] == ' ')
		return (1);
	return (0);
}


t_hit	cast_ray_dda(t_data *data, double rayDirX, double rayDirY)
{
	t_hit	h;

	double	rayPosX = data->player.pos_x;
	double	rayPosY = data->player.pos_y;

	int		mapX = (int)rayPosX;
	int		mapY = (int)rayPosY;

    double deltaDistX;
    double deltaDistY;
    
    if (rayDirX == 0.0)
    	deltaDistX = 500;
    else
    	deltaDistX = fabs(1.0 / rayDirX);


    if (rayDirY == 0.0)
    {
        
        deltaDistY = 500;
    }
    else
    {

        deltaDistY = fabs(1.0 / rayDirY);
    }

	int		stepX;
	int		stepY;

	double	sideDistX;
	double	sideDistY;

	int		side = 0;

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (rayPosX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
	}


	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (rayPosY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
	}

	while (!is_wall_cell(data, mapY, mapX))
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}

	}

	if (side == 0)
		h.perp_dist = (mapX - rayPosX + (1 - stepX) / 2.0) / rayDirX;
		
	else
		h.perp_dist = (mapY - rayPosY + (1 - stepY) / 2.0) / rayDirY;
	

	h.hit_x = rayPosX + rayDirX * h.perp_dist;
	h.hit_y = rayPosY + rayDirY * h.perp_dist;

	h.hit = 1;
	h.side = side;
	h.map_x = mapX;
	h.map_y = mapY;
	return (h);
}
