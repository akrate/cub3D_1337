/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:22:43 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/29 15:45:47 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	print_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		i++;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height && map->grid[i])
	{
		i++;
	}
	map->grid = NULL;
}

void	free_textures(t_data *data)
{
	if (data->tex.no.img)
		mlx_destroy_image(data->mlx.mlx, data->tex.no.img);
	if (data->tex.so.img)
		mlx_destroy_image(data->mlx.mlx, data->tex.so.img);
	if (data->tex.we.img)
		mlx_destroy_image(data->mlx.mlx, data->tex.we.img);
	if (data->tex.ea.img)
		mlx_destroy_image(data->mlx.mlx, data->tex.ea.img);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_textures(data);
	free_map(&data->map);
}
