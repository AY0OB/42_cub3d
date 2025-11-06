/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/04 11:15:31 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_map_size(t_game *game, int *width, int *height)
{
	*height = 0;
	while (game->map[*height])
		(*height)++;
	*width = 0;
	while (game->map[0][*width])
		(*width)++;
}

void	perform_dda(t_player *p, t_game *game)
{
	int hit = 0;
	int steps = 0;
	int mapWidth, mapHeight;

	get_map_size(game, &mapWidth, &mapHeight);

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
}
