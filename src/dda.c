/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 14:51:14 by amairia          ###   ########.fr       */
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

void	perform_dda(t_player *p, t_game *game, int hit, int steps)
{
	int	map_width;
	int	map_height;

	get_map_size(game, &map_width, &map_height);
	while (!hit && steps < 1000)
	{
		if (p->side_dist_x < p->side_dist_y)
		{
			p->side_dist_x += p->delta_dist_x;
			p->map_x += p->step_x;
			p->side = 0;
		}
		else
		{
			p->side_dist_y += p->delta_dist_y;
			p->map_y += p->step_y;
			p->side = 1;
		}
		if (p->map_y >= 0 && p->map_y < map_height
			&& p->map_x >= 0 && p->map_x < map_width
			&& game->map[p->map_y][p->map_x] == '1')
			hit = 1;
		steps++;
	}
}
