/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:23:30 by melkhatr          #+#    #+#             */
/*   Updated: 2026/01/29 15:56:59 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "tools_game.h"
# include "types.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int			parse_file(char *filename, t_data *data);
int			parse_texture(char *line, char **texture);
int			parse_color(char *line, t_color *color);
int			parse_map(int fd, t_data *data);
int			validate_map(t_data *data);
int			validate_walls(t_data *data);
int			is_valid_char(char c);
int			check_player(t_data *data);
char		*get_next_line(int fd);
char		*ft_strdup(const char *s);
char		*ft_strtrim(char *s);
int			ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
int			ft_isspace(char c);
int			is_map_line(char *line);
void		print_error(char *msg);
void		init_data(t_data *data);
char		**realloc_map(char **map, int new_size);
int			is_player_char(char c);
int			check_file_extension(char *filename);
int			all_elements_parsed(t_data *data);
void		set_north_south(t_data *data, char orientation);
void		set_east_west(t_data *data, char orientation);
void		set_player_direction(t_data *data, char orientation);
int			process_player_cell(t_data *data, int x, int y);
int			check_position_walls(t_data *data, int x, int y);
int			skip_to_map(int fd, t_data *data);
int			check_space_sequence(char *str, int i, int space_count);
int			validate_rgb_value(int value);
int			parse_rgb_values(char **rgb, t_color *color);
int			add_map_line(t_data *data, char *line);
int			validate_rgb_string(char *str);
int			parse_element(char *line, t_data *data);

char		get_char_at(t_data *data, int x, int y);
t_data		*set_get_data(void *p);
int			get_tex_color(t_img_tex *tex, int x, int y);
void		free_garbage(t_lst_garbage **head);
void		*ft_malloc(size_t size, t_lst_garbage **head);
void		start_game(t_data *data);
void		free_textures(t_data *data);

int			hook(int keycode, t_data *data);
int			button_x(t_data *game);
void		render_frame(t_data *data);
void		load_texture(t_data *data, t_img_tex *tex, char *path);
void		load_all_textures(t_data *data);
t_img_tex	*get_wall_texture(t_data *data, t_hit h, double rayDirX,
				double rayDirY);
t_hit		cast_ray_dda(t_data *data, double rayDirX, double rayDirY);
void		render_3d_walls(t_data *data);
void		put_pixel_to_img(t_mlx *mlx, int x, int y, int color);
int			handle_map_line(t_data *data, char *line, int *map_started);
#endif
