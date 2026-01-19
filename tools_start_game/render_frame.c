/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:42 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/19 12:04:12 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_vertical_line(t_data *data, int x, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y <= y_end)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, color);
		y++;
	}
}
// void	render_3d_walls(t_data *data)
// {
// 	int		x;
// 	int		rays;
// 	double	cameraX;
// 	double	rayDirX;
// 	double	rayDirY;
// 	t_hit	h;

// 	int		lineHeight;
// 	int		drawStart;
// 	int		drawEnd;

// 	rays = WIDTH;   // عمود لكل pixel فالعرض
// 	x = 0;
// 	while (x < rays)
// 	{
// 		/* 1) فين ray فالعين */
// 		cameraX = 2.0 * x / (double)rays - 1.0;

// 		/* 2) اتجاه ray */
// 		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
// 		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

// 		/* 3) DDA */
// 		h = cast_ray_dda(data, rayDirX, rayDirY);

// 		/* 4) طول العمود */
// 		lineHeight = (int)(HEIGHT / h.perp_dist);

// 		/* 5) بداية ونهاية الرسم */
// 		drawStart = -lineHeight / 2 + HEIGHT / 2;
// 		drawEnd = lineHeight / 2 + HEIGHT / 2;

// 		if (drawStart < 0)
// 			drawStart = 0;
// 		if (drawEnd >= HEIGHT)
// 			drawEnd = HEIGHT - 1;
// 		t_img_tex	*tex;
// 		double		wall_x;
// 		int			tex_x;

// 		/* اختيار texture حسب الجهة */
// 		tex = get_wall_texture(data, h, rayDirX, rayDirY);

// 		/* فين ضرب ray فالحائط */
// 		if (h.side == 0)
// 			wall_x = h.hit_y;
// 		else
// 			wall_x = h.hit_x;

// 		wall_x -= floor(wall_x);
// 		tex_x = (int)(wall_x * tex->w);

// 		/* قلب texture فبعض الجهات */
// 		if (h.side == 0 && rayDirX > 0)
// 			tex_x = tex->w - tex_x - 1;
// 		if (h.side == 1 && rayDirY < 0)
// 			tex_x = tex->w - tex_x - 1;
// 		double	step;
// 		double	tex_pos;
// 		int		y;
// 		int		tex_y;

// 		step = (double)tex->h / lineHeight;
// 		tex_pos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

// 		y = drawStart;
// 		while (y <= drawEnd)
// 		{
// 			tex_y = (int)tex_pos;
// 			if (tex_y < 0)
// 				tex_y = 0;
// 			if (tex_y >= tex->h)
// 				tex_y = tex->h - 1;

// 			int color = get_tex_color(tex, tex_x, tex_y);
// 			put_pixel_to_img(&data->mlx, x, y, color);

// 			tex_pos += step;
// 			y++;
// 		}

// 		// /* 6) لون (مؤقت بلا texture) */
// 		// if (h.side == 0)
// 		// 	draw_vertical_line(data, x, drawStart, drawEnd, 0x00FF0000);
// 		// else
// 		// 	draw_vertical_line(data, x, drawStart, drawEnd, 0x00990000);

// 		x++;
// 	}
// }
void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (!mlx->addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
void	draw_crosshair(t_data *data)
{
	int	cx;
	int	cy;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;

	/* خط أفقي */
	i = -6;
	while (i <= 6)
	{
		put_pixel_to_img(&data->mlx, cx + i, cy, 0x00FF0000);
		i++;
	}

	/* خط عمودي */
	i = -6;
	while (i <= 6)
	{
		put_pixel_to_img(&data->mlx, cx, cy + i, 0x00FF0000);
		i++;
	}
}

void	render_3d_walls(t_data *data)
{
	int			x;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	t_hit		h;

	int			lineHeight;
	int			drawStart;
	int			drawEnd;

	t_img_tex	*tex;
	double		wall_x;
	int			tex_x;

	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			color;

	x = 0;
	while (x < WIDTH)
	{
		/* 1) cameraX: فين هاد العمود فـ screen */
		cameraX = 2.0 * x / (double)WIDTH - 1.0;

		/* 2) اتجاه ray */
		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

		/* 3) DDA */
		h = cast_ray_dda(data, rayDirX, rayDirY);

		/* 4) طول العمود */
		lineHeight = (int)(HEIGHT / h.perp_dist);

		/* 5) البداية والنهاية */
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		drawEnd = lineHeight / 2 + HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		/* ===== CEILING ===== */
		y = 0;
		while (y < drawStart)
		{
			put_pixel_to_img(&data->mlx, x, y, data->ceiling.hex);
			y++;
		}

		/* ===== اختيار texture ===== */
		tex = get_wall_texture(data, h, rayDirX, rayDirY);

		/* فين ضرب ray فالحائط */
		if (h.side == 0)
			wall_x = h.hit_y;
		else
			wall_x = h.hit_x;

		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * tex->w);

		/* قلب texture فبعض الجهات */
		if (h.side == 0 && rayDirX > 0)
			tex_x = tex->w - tex_x - 1;
		if (h.side == 1 && rayDirY < 0)
			tex_x = tex->w - tex_x - 1;

		/* ===== WALL (TEXTURE) ===== */
		step = (double)tex->h / lineHeight;
		tex_pos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

		y = drawStart;
		while (y <= drawEnd)
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= tex->h)
				tex_y = tex->h - 1;

			color = get_tex_color(tex, tex_x, tex_y);

			/* shading خفيف للجدران الجانبية */
			if (h.side == 1)
				color = (color >> 1) & 0x007F7F7F;

			put_pixel_to_img(&data->mlx, x, y, color);

			tex_pos += step;
			y++;
		}

		/* ===== FLOOR ===== */
		y = drawEnd + 1;
		while (y < HEIGHT)
		{
			put_pixel_to_img(&data->mlx, x, y, data->floor.hex);
			y++;
		}

		x++;
	}

	/* عرض الصورة */
	mlx_put_image_to_window(
		data->mlx.mlx,
		data->mlx.win,
		data->mlx.img,
		0, 0
	);
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

// 	px = data->player.pos_x * TILE;
// 	py = data->player.pos_y * TILE;
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
void	draw_rays_dda(t_data *data)
{
	int		i;
	int		rays;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	t_hit	h;

	int		px_pix;
	int		py_pix;

	rays = WIDTH;
	px_pix = (int)((data->player.pos_x + 0.1)* TILE);
	py_pix = (int)((data->player.pos_y + 0.1)* TILE);

	i = 0;
	while (i < rays)
	{
		/* cameraX من -1 حتى +1 */
		cameraX = 2.0 * i / (double)rays - 1.0;

		/* اتجاه ray */
		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

		/* DDA hit */
		h = cast_ray_dda(data, rayDirX, rayDirY);

		/* رسم من player حتى hit point */
		draw_line(
			data,
			px_pix, py_pix,
			(int)(h.hit_x * TILE), (int)(h.hit_y * TILE),
			0x00AAAAAA
		);

		i++;
	}
}

// void	draw_rays(t_data *data)
// {
// 	int		i;
// 	double	cameraX;
// 	double	rayx;
// 	double	rayy;
// 	double	hx;
// 	double	hy;

// 	int		px_pix;
// 	int		py_pix;


// 	px_pix = (data->player.pos_x + 0.1) * TILE;
// 	py_pix = (data->player.pos_y + 0.1) * TILE;

// 	i = 0;
// 	while (i < 300)
// 	{
// 		cameraX = 2.0 * i / 300.0 - 1.0;
// 		rayx = data->player.dir_x + data->player.plane_x * cameraX;
// 		rayy = data->player.dir_y + data->player.plane_y * cameraX;
		

// 		ray_hit_wall_step(data, rayx, rayy, &hx, &hy);

// 			draw_line(data,px_pix, py_pix,(int)(hx * TILE), (int)(hy * TILE),0x00AAAAAA);
// 			// usleep(900);

// 		i++;
// 	}
// }

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

// void	render_frame(t_data *data)
// {
// 	mlx_clear_window(data->mlx.mlx, data->mlx.win);
// 	draw_map_2d(data);
//     draw_fov(data);
// 	// render_3d_walls(data);
// 	// draw_rays_dda(data);

// }

void	render_frame(t_data *data)
{
	/* destroy old image */
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);

	/* create new image */
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img)
		print_error("mlx_new_image failed");

	data->mlx.addr = mlx_get_data_addr(
		data->mlx.img,
		&data->mlx.bpp,
		&data->mlx.line_len,
		&data->mlx.endian
	);
	if (!data->mlx.addr)
		print_error("mlx_get_data_addr failed");

	/* render 3D into image */
	render_3d_walls(data);
	draw_crosshair(data);
	/* put image to window */
	mlx_put_image_to_window(
		data->mlx.mlx,
		data->mlx.win,
		data->mlx.img,
		0, 0
	);
}
