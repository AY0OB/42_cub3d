/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:13:55 by amairia           #+#    #+#             */
/*   Updated: 2025/11/01 22:01:17 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = (3 * PI) / 2; //UP
	//player->angle = 0; //RIGHT 
	//player->angle = PI / 2; //DOWN
	//player->angle = PI; //LEFT
	player->pos_x = player->x / BLOCK;
	player->pos_y = player->y / BLOCK;
	player->k_up = false;
	player->k_down = false;
	player->k_left = false;
	player->k_right = false;
	player->l_rotate = false;
	player->r_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->k_up = true;
	if (keycode == S)
		player->k_down = true;
	if (keycode == A)
		player->k_left = true;
	if (keycode == D)
		player->k_right = true;
	if (keycode == LEFT)
		player->l_rotate = true;
	if (keycode == RIGHT)
		player->r_rotate = true;
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

static void	move_player_bis(t_game *game, t_player *player, int speed)
{
	if (player->k_down)
	{
		if (check_x_demote(game, player, player->cos_angle))
			player->x -= player->cos_angle * speed;
		if (check_y_demote(game, player, player->sin_angle))
			player->y -= player->sin_angle * speed;
	}
	if (player->k_left)
	{
		if (check_x_add(game, player, player->sin_angle))
			player->x += player->sin_angle * speed;
		if (check_y_demote(game, player, player->cos_angle))
			player->y -= player->cos_angle * speed;
	}
	if (player->k_right)
	{
		if (check_x_demote(game, player, player->sin_angle))
			player->x -= player->sin_angle * speed;
		if (check_y_add(game, player, player->cos_angle))
			player->y += player->cos_angle * speed;
	}
}

void	move_player(t_game *game, t_player *player)
{
	int		speed;
	float	angle_speed;

	speed = 3;
	angle_speed = 0.03;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	player->pos_x = player->x / BLOCK;
	player->pos_y = player->y / BLOCK;
	if (player->l_rotate)
		player->angle -= angle_speed;
	if (player->r_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->k_up)
	{
		if (check_x_add(game, player, player->cos_angle))
			player->x += player->cos_angle * speed;
		if (check_y_add(game, player, player->sin_angle))
			player->y += player->sin_angle * speed;
	}
	move_player_bis(game, player, speed);
}
