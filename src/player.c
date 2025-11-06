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
	player->posX = 5.0;
	player->posY = 5.0;
	player->dirX = 0;	//UP
	player->dirY = -1;
	player->planeX = 0.66;
	player->planeY = 0.0;
	player->x = 0;
	player->cameraX = 2 * player->x / WIDTH - 1;
	player->rayDirX = player->dirX + player->planeX * player->cameraX;
	player->rayDirY = player->dirY + player->planeY * player->cameraX;
	player->mapX = (int)player->posX;
	player->mapY = (int)player->posY;
	//player->dirX = 0;	//UP
	//player->dirY = -1;
	//player->dirX = 0;	//UP
	//player->dirY = -1;
	//player->dirX = 0;	//UP
	//player->dirY = -1;
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
	float	oldDirX = p->dirX;
	float	oldPlaneX = p->planeX;

	if (p->l_rotate)
	{
		p->dirX = p->dirX * cosf(-rotSpeed) - p->dirY * sinf(-rotSpeed);
		p->dirY = oldDirX * sinf(-rotSpeed) + p->dirY * cosf(-rotSpeed);
		p->planeX = p->planeX * cosf(-rotSpeed) - p->planeY * sinf(-rotSpeed);
		p->planeY = oldPlaneX * sinf(-rotSpeed) + p->planeY * cosf(-rotSpeed);
	}
	if (p->r_rotate)
	{
		p->dirX = p->dirX * cosf(rotSpeed) - p->dirY * sinf(rotSpeed);
		p->dirY = oldDirX * sinf(rotSpeed) + p->dirY * cosf(rotSpeed);
		p->planeX = p->planeX * cosf(rotSpeed) - p->planeY * sinf(rotSpeed);
		p->planeY = oldPlaneX * sinf(rotSpeed) + p->planeY * cosf(rotSpeed);
	}
}

static void	move_axis(t_player *p, t_game *game, float moveX, float moveY)
{
	int	newMapX = (int)(p->posX + moveX);
	int	newMapY = (int)(p->posY + moveY);
	int	mapWidth = 0;
	int	mapHeight = 0;

	while (game->map[mapHeight]) mapHeight++;
	while (game->map[0][mapWidth]) mapWidth++;

	if (newMapX >= 0 && newMapX < mapWidth && game->map[(int)p->posY][newMapX] == '0')
		p->posX += moveX;
	if (newMapY >= 0 && newMapY < mapHeight && game->map[newMapY][(int)p->posX] == '0')
		p->posY += moveY;
}

void	move_player(t_game *game, t_player *p)
{
	float	moveSpeed = 0.1f;
	float	rotSpeed = 0.05f;

	rotate_player(p, rotSpeed);

	if (p->k_up)	move_axis(p, game, p->dirX * moveSpeed, p->dirY * moveSpeed);
	if (p->k_down)	move_axis(p, game, -p->dirX * moveSpeed, -p->dirY * moveSpeed);
	if (p->k_left)	move_axis(p, game, -p->planeX * moveSpeed, -p->planeY * moveSpeed);
	if (p->k_right)	move_axis(p, game, p->planeX * moveSpeed, p->planeY * moveSpeed);
}

/*void	move_player(t_game *game, t_player *p)
{
	float	moveSpeed = 0.1f;  // vitesse de déplacement
	float	rotSpeed = 0.05f;  // vitesse de rotation
	int		mapWidth;
	int		mapHeight;
	int		newMapX;
	int		newMapY;

	// Taille réelle de la map
	mapHeight = 0;
	while (game->map[mapHeight])
		mapHeight++;
	mapWidth = 0;
	while (game->map[0][mapWidth])
		mapWidth++;

	// 🔄 Rotation
	if (p->l_rotate)
	{
		float	oldDirX = p->dirX;
		p->dirX = p->dirX * cosf(-rotSpeed) - p->dirY * sinf(-rotSpeed);
		p->dirY = oldDirX * sinf(-rotSpeed) + p->dirY * cosf(-rotSpeed);
		float	oldPlaneX = p->planeX;
		p->planeX = p->planeX * cosf(-rotSpeed) - p->planeY * sinf(-rotSpeed);
		p->planeY = oldPlaneX * sinf(-rotSpeed) + p->planeY * cosf(-rotSpeed);
	}
	if (p->r_rotate)
	{
		float	oldDirX = p->dirX;
		p->dirX = p->dirX * cosf(rotSpeed) - p->dirY * sinf(rotSpeed);
		p->dirY = oldDirX * sinf(rotSpeed) + p->dirY * cosf(rotSpeed);
		float	oldPlaneX = p->planeX;
		p->planeX = p->planeX * cosf(rotSpeed) - p->planeY * sinf(rotSpeed);
		p->planeY = oldPlaneX * sinf(rotSpeed) + p->planeY * cosf(rotSpeed);
	}

	// 🔄 Déplacement avant/arrière
	if (p->k_up)
	{
		newMapX = (int)(p->posX + p->dirX * moveSpeed);
		newMapY = (int)(p->posY + p->dirY * moveSpeed);
		if (newMapX >= 0 && newMapX < mapWidth && game->map[(int)p->posY][newMapX] == '0')
			p->posX += p->dirX * moveSpeed;
		if (newMapY >= 0 && newMapY < mapHeight && game->map[newMapY][(int)p->posX] == '0')
			p->posY += p->dirY * moveSpeed;
	}
	if (p->k_down)
	{
		newMapX = (int)(p->posX - p->dirX * moveSpeed);
		newMapY = (int)(p->posY - p->dirY * moveSpeed);
		if (newMapX >= 0 && newMapX < mapWidth && game->map[(int)p->posY][newMapX] == '0')
			p->posX -= p->dirX * moveSpeed;
		if (newMapY >= 0 && newMapY < mapHeight && game->map[newMapY][(int)p->posX] == '0')
			p->posY -= p->dirY * moveSpeed;
	}

	// 🔄 Déplacement latéral (strafe)
	if (p->k_left)
	{
		newMapX = (int)(p->posX - p->planeX * moveSpeed);
		newMapY = (int)(p->posY - p->planeY * moveSpeed);
		if (newMapX >= 0 && newMapX < mapWidth && game->map[(int)p->posY][newMapX] == '0')
			p->posX -= p->planeX * moveSpeed;
		if (newMapY >= 0 && newMapY < mapHeight && game->map[newMapY][(int)p->posX] == '0')
			p->posY -= p->planeY * moveSpeed;
	}
	if (p->k_right)
	{
		newMapX = (int)(p->posX + p->planeX * moveSpeed);
		newMapY = (int)(p->posY + p->planeY * moveSpeed);
		if (newMapX >= 0 && newMapX < mapWidth && game->map[(int)p->posY][newMapX] == '0')
			p->posX += p->planeX * moveSpeed;
		if (newMapY >= 0 && newMapY < mapHeight && game->map[newMapY][(int)p->posX] == '0')
			p->posY += p->planeY * moveSpeed;
	}
}*/
