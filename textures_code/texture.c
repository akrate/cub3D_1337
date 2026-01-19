/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:08:31 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/19 10:11:51 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


/* تحميل texture وحدة */
void	load_texture(t_data *data, t_img_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(
		data->mlx.mlx,
		path,
		&tex->w, //width
		&tex->h // height
	);
	if (!tex->img)
		print_error(" Error: failed to load texture");

	tex->addr = mlx_get_data_addr(
		tex->img,
		&tex->bpp,
		&tex->line_len,
		&tex->endian
	);
}

/* تحميل جميع textures */
void	load_all_textures(t_data *data)
{
	load_texture(data, &data->tex.no, data->textures.no);
	load_texture(data, &data->tex.so, data->textures.so);
	load_texture(data, &data->tex.we, data->textures.we);
	load_texture(data, &data->tex.ea, data->textures.ea);
}

/* اختيار texture حسب الجدار */
t_img_tex	*get_wall_texture(t_data *data, t_hit h,
								double rayDirX, double rayDirY)
{
	if (h.side == 0) // vertical wall
	{
		if (rayDirX > 0)
			return (&data->tex.we);
		else
			return (&data->tex.ea);
	}
	else // horizontal wall
	{
		if (rayDirY > 0)
			return (&data->tex.no);
		else
			return (&data->tex.so);
	}
}
int	get_tex_color(t_img_tex *tex, int x, int y)
{
	return (*(int *)(tex->addr
		+ y * tex->line_len
		+ x * (tex->bpp / 8)));
}
