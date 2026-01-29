/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:28:15 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/29 15:47:48 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_texture(t_data *data, t_img_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &tex->w, &tex->h);
	if (!tex->img)
		print_error(" Error: failed to load texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}

void	load_all_textures(t_data *data)
{
	load_texture(data, &data->tex.no, data->textures.no);
	load_texture(data, &data->tex.so, data->textures.so);
	load_texture(data, &data->tex.we, data->textures.we);
	load_texture(data, &data->tex.ea, data->textures.ea);
}

t_img_tex	*get_wall_texture(t_data *data, t_hit h, double rayDirX,
		double rayDirY)
{
	if (h.side == 0)
	{
		if (rayDirX > 0)
			return (&data->tex.we);
		else
			return (&data->tex.ea);
	}
	else
	{
		if (rayDirY > 0)
			return (&data->tex.no);
		else
			return (&data->tex.so);
	}
}

int	get_tex_color(t_img_tex *tex, int x, int y)
{
	return (*(int *)(tex->addr + y * tex->line_len + x * (tex->bpp / 8)));
}
