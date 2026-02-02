/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_game.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 12:51:55 by aoussama          #+#    #+#             */
/*   Updated: 2026/02/02 13:53:01 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_GAME_H
# define TOOLS_GAME_H

# include "cub3d.h"
# include "types.h"

void	init_ray(t_ray *ray, t_data *data, double dir_x, double dir_y);
int		is_wall_cell(t_data *data, int my, int mx);
void	init_step(t_ray *ray);
void	move_up_done(int key, t_data *data);
void	move_left_right(int key, t_data *data);
void	compute_ray(t_data *data, t_column *c);
void	compute_wall_height(t_column *c);
void	ecs(t_data *game, int i);
#endif