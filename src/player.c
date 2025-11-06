/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:13:55 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 15:19:09 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = 5.0;
	player->pos_y = 5.0;
	player->dir_x = 0;	//UP
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0.0;
	player->x = 0;
	player->camera_x = 2 * player->x / WIDTH - 1;
	player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
	player->raydir_y = player->dir_y + player->plane_y * player->camera_x;
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	//player->dir_x = 0;	//DOWN
	//player->dir_y = 1;
	//player->dir_x = 1;	//RIGHT
	//player->dir_y = 0;
	//player->dir_x = -1;	//LEFT
	//player->dir_y = 0;
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

static void	rotate_player(t_player *p, float rotSpeed)
{
	float	olddir_x = p->dir_x;
	float	oldplane_x = p->plane_x;

	if (p->l_rotate)
	{
		p->dir_x = p->dir_x * cosf(-rotSpeed) - p->dir_y * sinf(-rotSpeed);
		p->dir_y = olddir_x * sinf(-rotSpeed) + p->dir_y * cosf(-rotSpeed);
		p->plane_x = p->plane_x * cosf(-rotSpeed) - p->plane_y * sinf(-rotSpeed);
		p->plane_y = oldplane_x * sinf(-rotSpeed) + p->plane_y * cosf(-rotSpeed);
	}
	if (p->r_rotate)
	{
		p->dir_x = p->dir_x * cosf(rotSpeed) - p->dir_y * sinf(rotSpeed);
		p->dir_y = olddir_x * sinf(rotSpeed) + p->dir_y * cosf(rotSpeed);
		p->plane_x = p->plane_x * cosf(rotSpeed) - p->plane_y * sinf(rotSpeed);
		p->plane_y = oldplane_x * sinf(rotSpeed) + p->plane_y * cosf(rotSpeed);
	}
}

static void	move_axis(t_player *p, t_game *game, float moveX, float moveY)
{
	int	newmap_x = (int)(p->pos_x + moveX);
	int	newmap_y = (int)(p->pos_y + moveY);
	int	map_width = 0;
	int	map_height = 0;

	while (game->map[map_height]) map_height++;
	while (game->map[0][map_width]) map_width++;

	if (newmap_x >= 0 && newmap_x < map_width && game->map[(int)p->pos_y][newmap_x] == '0')
		p->pos_x += moveX;
	if (newmap_y >= 0 && newmap_y < map_height && game->map[newmap_y][(int)p->pos_x] == '0')
		p->pos_y += moveY;
}

void	move_player(t_game *game, t_player *p)
{
	float	moveSpeed = 0.1f;
	float	rotSpeed = 0.05f;

	rotate_player(p, rotSpeed);

	if (p->k_up)	move_axis(p, game, p->dir_x * moveSpeed, p->dir_y * moveSpeed);
	if (p->k_down)	move_axis(p, game, -p->dir_x * moveSpeed, -p->dir_y * moveSpeed);
	if (p->k_left)	move_axis(p, game, -p->plane_x * moveSpeed, -p->plane_y * moveSpeed);
	if (p->k_right)	move_axis(p, game, p->plane_x * moveSpeed, p->plane_y * moveSpeed);
}

/*void	move_player(t_game *game, t_player *p)
{
	float	moveSpeed = 0.1f;  // vitesse de déplacement
	float	rotSpeed = 0.05f;  // vitesse de rotation
	int		map_width;
	int		map_height;
	int		newmap_x;
	int		newmap_y;

	// Taille réelle de la map
	map_height = 0;
	while (game->map[map_height])
		map_height++;
	map_width = 0;
	while (game->map[0][map_width])
		map_width++;

	// 🔄 Rotation
	if (p->l_rotate)
	{
		float	olddir_x = p->dir_x;
		p->dir_x = p->dir_x * cosf(-rotSpeed) - p->dir_y * sinf(-rotSpeed);
		p->dir_y = olddir_x * sinf(-rotSpeed) + p->dir_y * cosf(-rotSpeed);
		float	oldplane_x = p->plane_x;
		p->plane_x = p->plane_x * cosf(-rotSpeed) - p->plane_y * sinf(-rotSpeed);
		p->plane_y = oldplane_x * sinf(-rotSpeed) + p->plane_y * cosf(-rotSpeed);
	}
	if (p->r_rotate)
	{
		float	olddir_x = p->dir_x;
		p->dir_x = p->dir_x * cosf(rotSpeed) - p->dir_y * sinf(rotSpeed);
		p->dir_y = olddir_x * sinf(rotSpeed) + p->dir_y * cosf(rotSpeed);
		float	oldplane_x = p->plane_x;
		p->plane_x = p->plane_x * cosf(rotSpeed) - p->plane_y * sinf(rotSpeed);
		p->plane_y = oldplane_x * sinf(rotSpeed) + p->plane_y * cosf(rotSpeed);
	}

	// 🔄 Déplacement avant/arrière
	if (p->k_up)
	{
		newmap_x = (int)(p->pos_x + p->dir_x * moveSpeed);
		newmap_y = (int)(p->pos_y + p->dir_y * moveSpeed);
		if (newmap_x >= 0 && newmap_x < map_width && game->map[(int)p->pos_y][newmap_x] == '0')
			p->pos_x += p->dir_x * moveSpeed;
		if (newmap_y >= 0 && newmap_y < map_height && game->map[newmap_y][(int)p->pos_x] == '0')
			p->pos_y += p->dir_y * moveSpeed;
	}
	if (p->k_down)
	{
		newmap_x = (int)(p->pos_x - p->dir_x * moveSpeed);
		newmap_y = (int)(p->pos_y - p->dir_y * moveSpeed);
		if (newmap_x >= 0 && newmap_x < map_width && game->map[(int)p->pos_y][newmap_x] == '0')
			p->pos_x -= p->dir_x * moveSpeed;
		if (newmap_y >= 0 && newmap_y < map_height && game->map[newmap_y][(int)p->pos_x] == '0')
			p->pos_y -= p->dir_y * moveSpeed;
	}

	// 🔄 Déplacement latéral (strafe)
	if (p->k_left)
	{
		newmap_x = (int)(p->pos_x - p->plane_x * moveSpeed);
		newmap_y = (int)(p->pos_y - p->plane_y * moveSpeed);
		if (newmap_x >= 0 && newmap_x < map_width && game->map[(int)p->pos_y][newmap_x] == '0')
			p->pos_x -= p->plane_x * moveSpeed;
		if (newmap_y >= 0 && newmap_y < map_height && game->map[newmap_y][(int)p->pos_x] == '0')
			p->pos_y -= p->plane_y * moveSpeed;
	}
	if (p->k_right)
	{
		newmap_x = (int)(p->pos_x + p->plane_x * moveSpeed);
		newmap_y = (int)(p->pos_y + p->plane_y * moveSpeed);
		if (newmap_x >= 0 && newmap_x < map_width && game->map[(int)p->pos_y][newmap_x] == '0')
			p->pos_x += p->plane_x * moveSpeed;
		if (newmap_y >= 0 && newmap_y < map_height && game->map[newmap_y][(int)p->pos_x] == '0')
			p->pos_y += p->plane_y * moveSpeed;
	}
}*/
