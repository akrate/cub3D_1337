/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:33:13 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/29 15:54:04 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define BUFFER_SIZE 1024
# define TILE 32
# define WIDTH 1920
# define HEIGHT 1024

typedef struct s_img_tex
{
	void					*img;
	char					*addr;
	int						w;
	int						h;
	int						bpp;
	int						line_len;
	int						endian;
}							t_img_tex;

typedef struct s_mlx
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
}							t_mlx;
typedef struct s_lst_garbage
{
	void					*ptr;
	struct s_lst_garbage	*next;
}							t_lst_garbage;

typedef struct s_tex_paths
{
	char					*no;
	char					*so;
	char					*we;
	char					*ea;
}							t_tex_paths;

typedef struct s_hit
{
	int						hit;
	int						side;
	int						map_x;
	int						map_y;
	double					perp_dist;
	double					hit_x;
	double					hit_y;
}							t_hit;

typedef struct s_texpack
{
	t_img_tex				no;
	t_img_tex				so;
	t_img_tex				we;
	t_img_tex				ea;
}							t_texpack;

typedef struct s_color
{
	int						r;
	int						g;
	int						b;
	int						hex;
}							t_color;

typedef struct s_player
{
	double					pos_x;
	double					pos_y;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
	char					orientation;
}							t_player;

typedef struct s_map
{
	char					**grid;
	int						width;
	int						height;
	int						player_count;
}							t_map;

typedef struct s_data
{
	t_tex_paths				textures;
	t_texpack				tex;
	t_color					floor;
	t_color					ceiling;
	t_map					map;
	t_player				player;
	t_lst_garbage			*lst_gc_g;
	t_mlx					mlx;
}							t_data;
typedef struct s_ray
{
	double				pos_x;
	double				pos_y;
	int					map_x;
	int					map_y;
	double				dir_x;
	double				dir_y;
	double				delta_x;
	double				delta_y;
	double				side_x;
	double				side_y;
	int					step_x;
	int					step_y;
	int					side;
}						t_ray;

typedef struct s_column
{
	int						x;
	double					rx;
	double					ry;
	t_hit					hit;
	int						start;
	int						end;
	int						height;
	int						start_raw;
	t_img_tex				*tex;
	int						tex_x;
}							t_column;

#endif