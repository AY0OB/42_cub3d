/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/04 11:15:31 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_check(t_player *player, int *x, int *y)
{
	if (player->cos_angle > 0.0 && player->sin_angle < 0.0)
	{
		*x = -1;
		*y = 1;
	}
	if (player->cos_angle > 0.0 && player->sin_angle > 0.0)
	{
		*x = -1;
		*y = -1;
	}
	if (player->cos_angle < 0.0 && player->sin_angle < 0.0)
	{
		*x = 1;
		*y = 1;
	}
	if (player->cos_angle < 0.0 && player->sin_angle > 0.0)
	{
		*x = 1;
		*y = -1;
	}
}

static bool	touch(t_game *game)
{
	int	x;
	int	y;
	int	check_x;
	int	check_y;

	x = game->player.ray_x / BLOCK;
	y = game->player.ray_y / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
	/* BUG */
	if (game->player.cos_angle == 0 || game->player.sin_angle == 0)
		return (false);
	set_check(&(game->player), &check_x, &check_y);
	if (game->map[y + check_y][x] == '1'
		&& game->map[y][x + check_x] == '1')
        	return (true);
	return (false);
}

static float	distance(float x, float y)
{
	float	res;

	res = sqrt(x * x + y * y);
	return (res);
}

static float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	dist = distance(delta_x, delta_y) * cos(angle);
	return (dist);
}

void	draw_line(t_player *player, t_game *game, int i)
{
	int	tmp;

	player->cos_angle = cos(player->start_x);
	player->sin_angle = sin(player->start_x);
	player->ray_x = player->x;
	player->ray_y = player->y;
	while (!touch(game))
	{
		if (DEBUG == 1)
			put_pixel(player->ray_x, player->ray_y, 0xFF0000, game);
		player->ray_x += player->cos_angle;
		player->ray_y += player->sin_angle;
	}
	player->dist = fixed_dist(player->x, player->y, player->ray_x, player->ray_y, game);
	player->height = (BLOCK / player->dist) * (WIDTH / 2);
	player->start_y = (HEIGHT - player->height) / 2;
	player->end = player->start_y + player->height;
	tmp = player->end;
	while (tmp < HEIGHT)
	{
		if (DEBUG == 0)
			put_pixel(i, tmp, game->floor_color, game);
		tmp++;
	}
	tmp = player->start_y;
	while (tmp > 0)
	{
		if (DEBUG == 0)
			put_pixel(i, tmp, game->ceiling_color, game);
		tmp--;
	}
	while (player->start_y < player->end)
	{
		if (DEBUG == 0)
			put_pixel(i, player->start_y, 225, game);
		player->start_y++;
	}
}
