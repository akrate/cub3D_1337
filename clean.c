/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:22:43 by melkhatr          #+#    #+#             */
/*   Updated: 2026/02/02 13:54:46 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
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
