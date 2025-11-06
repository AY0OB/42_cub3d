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

static void	calc_ray(t_player *p, int x)
{
	p->cameraX = 2.0f * x / (float)WIDTH - 1.0f;
	p->rayDirX = p->dirX + p->planeX * p->cameraX;
	p->rayDirY = p->dirY + p->planeY * p->cameraX;
	p->mapX = (int)p->posX;
	p->mapY = (int)p->posY;
	p->deltaDistX = (p->rayDirX == 0.0f) ? 1e6f : fabsf(1.0f / p->rayDirX);
	p->deltaDistY = (p->rayDirY == 0.0f) ? 1e6f : fabsf(1.0f / p->rayDirY);
	if (p->rayDirX < 0) { p->stepX = -1; p->sideDistX = (p->posX - p->mapX) * p->deltaDistX; }
	else { p->stepX = 1; p->sideDistX = ((float)(p->mapX + 1) - p->posX) * p->deltaDistX; }
	if (p->rayDirY < 0) { p->stepY = -1; p->sideDistY = (p->posY - p->mapY) * p->deltaDistY; }
	else { p->stepY = 1; p->sideDistY = ((float)(p->mapY + 1) - p->posY) * p->deltaDistY; }
}

static void	calc_wall(t_player *p)
{
	if (p->side == 0)
		p->perpWallDist = ((float)p->mapX - p->posX + (1 - p->stepX) * 0.5f) /
			((p->rayDirX != 0.0f) ? p->rayDirX : 1e-6f);
	else
		p->perpWallDist = ((float)p->mapY - p->posY + (1 - p->stepY) * 0.5f) /
			((p->rayDirY != 0.0f) ? p->rayDirY : 1e-6f);
	p->lineHeight = (int)((float)HEIGHT / p->perpWallDist);
	p->drawStart = -p->lineHeight / 2 + HEIGHT / 2;
	if (p->drawStart < 0) p->drawStart = 0;
	p->drawEnd = p->lineHeight / 2 + HEIGHT / 2;
	if (p->drawEnd >= HEIGHT) p->drawEnd = HEIGHT - 1;
}


static void	draw_column(t_player *p, t_game *game, int x)
{
	int	y;
	int	color;

	for (y = 0; y < p->drawStart; y++)
		put_pixel(x, y, game->ceiling_color, game);

	color = (p->side == 0) ? 0xFFFFFF : 0xAAAAAA;
	for (y = p->drawStart; y <= p->drawEnd; y++)
		put_pixel(x, y, color, game);

	for (y = p->drawEnd + 1; y < HEIGHT; y++)
		put_pixel(x, y, game->floor_color, game);
}


void	raycast(t_player *p, t_game *game)
{
	int x;

	for (x = 0; x < WIDTH; x++)
	{
		calc_ray(p, x);
		perform_dda(p, game);
		calc_wall(p);
		draw_column(p, game, x);
	}
}


/*void	raycast(t_player *p, t_game *game)
{
	int		x;
	int		y;
	int		color;
	int		mapWidth;
	int		mapHeight;

	// Calcul des dimensions de la map
	mapHeight = 0;
	while (game->map[mapHeight])
		mapHeight++;
	mapWidth = 0;
	while (game->map[0][mapWidth])
		mapWidth++;

	for (x = 0; x < WIDTH; x++)
	{
		p->cameraX = 2.0f * x / (float)WIDTH - 1.0f;
		p->rayDirX = p->dirX + p->planeX * p->cameraX;
		p->rayDirY = p->dirY + p->planeY * p->cameraX;

		p->mapX = (int)p->posX;
		p->mapY = (int)p->posY;

		p->deltaDistX = (p->rayDirX == 0.0f) ? 1e6f : fabsf(1.0f / p->rayDirX);
		p->deltaDistY = (p->rayDirY == 0.0f) ? 1e6f : fabsf(1.0f / p->rayDirY);

		if (p->rayDirX < 0.0f)
		{
			p->stepX = -1;
			p->sideDistX = (p->posX - (float)p->mapX) * p->deltaDistX;
		}
		else
		{
			p->stepX = 1;
			p->sideDistX = ((float)(p->mapX + 1) - p->posX) * p->deltaDistX;
		}
		if (p->rayDirY < 0.0f)
		{
			p->stepY = -1;
			p->sideDistY = (p->posY - (float)p->mapY) * p->deltaDistY;
		}
		else
		{
			p->stepY = 1;
			p->sideDistY = ((float)(p->mapY + 1) - p->posY) * p->deltaDistY;
		}

		// DDA avec fail-safe
		int hit = 0;
		int steps = 0;
		while (!hit && steps < 1000)
		{
			if (p->sideDistX < p->sideDistY)
			{
				p->sideDistX += p->deltaDistX;
				p->mapX += p->stepX;
				p->side = 0;
			}
			else
			{
				p->sideDistY += p->deltaDistY;
				p->mapY += p->stepY;
				p->side = 1;
			}
			if (p->mapY >= 0 && p->mapY < mapHeight &&
				p->mapX >= 0 && p->mapX < mapWidth &&
				game->map[p->mapY][p->mapX] == '1')
				hit = 1;
			steps++;
		}

		// Distance perpendiculaire
		if (p->side == 0)
			p->perpWallDist = ((float)p->mapX - p->posX + (1 - p->stepX) * 0.5f) / ((p->rayDirX != 0.0f) ? p->rayDirX : 1e-6f);
		else
			p->perpWallDist = ((float)p->mapY - p->posY + (1 - p->stepY) * 0.5f) / ((p->rayDirY != 0.0f) ? p->rayDirY : 1e-6f);

		p->lineHeight = (int)((float)HEIGHT / p->perpWallDist);
		p->drawStart = -p->lineHeight / 2 + HEIGHT / 2;
		if (p->drawStart < 0) p->drawStart = 0;
		p->drawEnd = p->lineHeight / 2 + HEIGHT / 2;
		if (p->drawEnd >= HEIGHT) p->drawEnd = HEIGHT - 1;

		// Dessin plafond
		for (y = 0; y < p->drawStart; y++)
			put_pixel(x, y, game->ceiling_color, game);

		// Dessin mur
		color = (p->side == 0) ? 0xFFFFFF : 0xAAAAAA;
		for (y = p->drawStart; y <= p->drawEnd; y++)
			put_pixel(x, y, color, game);

		// Dessin sol
		for (y = p->drawEnd + 1; y < HEIGHT; y++)
			put_pixel(x, y, game->floor_color, game);
	}
}
*/