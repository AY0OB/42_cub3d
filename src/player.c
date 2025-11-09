/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:13:55 by amairia           #+#    #+#             */
/*   Updated: 2025/11/09 19:43:49 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == ESC)
	{
		ft_printf("window closing\n");
		clear_all(g);
		exit(0);
	}
	if (keycode == W)
		g->player.k_up = true;
	if (keycode == S)
		g->player.k_down = true;
	if (keycode == A)
		g->player.k_left = true;
	if (keycode == D)
		g->player.k_right = true;
	if (keycode == LEFT)
		g->player.l_rotate = true;
	if (keycode == RIGHT)
		g->player.r_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->k_up = false;
	if (keycode == S)
		player->k_down = false;
	if (keycode == A)
		player->k_left = false;
	if (keycode == D)
		player->k_right = false;
	if (keycode == LEFT)
		player->l_rotate = false;
	if (keycode == RIGHT)
		player->r_rotate = false;
	return (0);
}

static void	rotate_player(t_player *p, float rot_speed)
{
	float	olddir_x;
	float	oldplane_x;

	olddir_x = p->dir_x;
	oldplane_x = p->plane_x;
	if (p->l_rotate)
	{
		p->dir_x = p->dir_x * cosf(-rot_speed) - p->dir_y * sinf(-rot_speed);
		p->dir_y = olddir_x * sinf(-rot_speed) + p->dir_y * cosf(-rot_speed);
		p->plane_x = p->plane_x * cosf(-rot_speed)
			- p->plane_y * sinf(-rot_speed);
		p->plane_y = oldplane_x * sinf(-rot_speed)
			+ p->plane_y * cosf(-rot_speed);
	}
	if (p->r_rotate)
	{
		p->dir_x = p->dir_x * cosf(rot_speed) - p->dir_y * sinf(rot_speed);
		p->dir_y = olddir_x * sinf(rot_speed) + p->dir_y * cosf(rot_speed);
		p->plane_x = p->plane_x * cosf(rot_speed)
			- p->plane_y * sinf(rot_speed);
		p->plane_y = oldplane_x * sinf(rot_speed)
			+ p->plane_y * cosf(rot_speed);
	}
}

static void	move_axis(t_player *p, t_game *game, float moveX, float moveY)
{
	int	newmap_x;
	int	newmap_y;
	int	map_width;
	int	map_height;

	newmap_x = (int)(p->pos_x + moveX);
	newmap_y = (int)(p->pos_y + moveY);
	map_width = 0;
	map_height = 0;
	while (game->map[map_height])
		map_height++;
	while (game->map[0][map_width])
		map_width++;
	if (newmap_x >= 0 //&& newmap_x < map_width
		&& game->map[(int)p->pos_y][newmap_x] == '0')
		p->pos_x += moveX;
	if (newmap_y >= 0 //&& newmap_y < map_height
		&& game->map[newmap_y][(int)p->pos_x] == '0')
		p->pos_y += moveY;
}

void	move_player(t_game *game, t_player *p)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 0.1f;
	rot_speed = 0.05f;
	rotate_player(p, rot_speed);
	if (p->k_up)
		move_axis(p, game, p->dir_x * move_speed, p->dir_y * move_speed);
	if (p->k_down)
		move_axis(p, game, -p->dir_x * move_speed, -p->dir_y * move_speed);
	if (p->k_left)
		move_axis(p, game, -p->plane_x * move_speed, -p->plane_y * move_speed);
	if (p->k_right)
		move_axis(p, game, p->plane_x * move_speed, p->plane_y * move_speed);
}
