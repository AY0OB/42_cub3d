/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:41:57 by amairia           #+#    #+#             */
/*   Updated: 2025/11/23 21:01:12 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	rotate_right(t_player *p, int mouse_x)
{
	float	olddir_x;
	float	oldplane_x;
	float	rot_speed;

	rot_speed = 0.002f * (mouse_x - WIDTH / 2);
	olddir_x = p->dir_x;
	oldplane_x = p->plane_x;
	p->dir_x = p->dir_x * cosf(rot_speed) - p->dir_y * sinf(rot_speed);
	p->dir_y = olddir_x * sinf(rot_speed) + p->dir_y * cosf(rot_speed);
	p->plane_x = p->plane_x * cosf(rot_speed)
		- p->plane_y * sinf(rot_speed);
	p->plane_y = oldplane_x * sinf(rot_speed)
		+ p->plane_y * cosf(rot_speed);
}

static void	rotate_left(t_player *p, int mouse_x)
{
	float	olddir_x;
	float	oldplane_x;
	float	rot_speed;

	rot_speed = 0.002f * (WIDTH / 2 - mouse_x);
	olddir_x = p->dir_x;
	oldplane_x = p->plane_x;
	p->dir_x = p->dir_x * cosf(-rot_speed) - p->dir_y * sinf(-rot_speed);
	p->dir_y = olddir_x * sinf(-rot_speed) + p->dir_y * cosf(-rot_speed);
	p->plane_x = p->plane_x * cosf(-rot_speed)
		- p->plane_y * sinf(-rot_speed);
	p->plane_y = oldplane_x * sinf(-rot_speed)
		+ p->plane_y * cosf(-rot_speed);
}

void	move_player_mouse(t_player *p, int mouse_x)
{
	if (mouse_x > WIDTH / 2)
		rotate_right(p, mouse_x);
	else if (mouse_x < WIDTH / 2)
		rotate_left(p, mouse_x);
}
