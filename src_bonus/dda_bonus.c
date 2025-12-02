/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/28 20:31:31 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	get_map_size(t_game *game, int *width, int *height)
{
	*height = 0;
	while (game->map[*height])
		(*height)++;
	*width = 0;
	while (game->map[0][*width])
		(*width)++;
}

static bool	check_side_hit(t_game *game,
	int map_height, int map_width, int *hit)
{
	t_player	*p;

	p = &game->player;
	if (p->map_y >= 0 && p->map_y < map_height
		&& p->map_x >= 0 && p->map_x < map_width
		&& game->map[p->map_y][p->map_x] == '1')
	{
		*hit = 1;
		return (false);
	}
	if (p->map_y >= 0 && p->map_y < map_height
		&& p->map_x >= 0 && p->map_x < map_width
		&& game->map[p->map_y][p->map_x] == 'D')
	{
		*hit = 1;
		return (true);
	}
	return (false);
}

bool	perform_dda(t_player *p, t_game *game, int hit, int steps)
{
	int		map_width;
	int		map_height;
	bool	door;

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
		door = check_side_hit(game, map_height, map_width, &hit);
		steps++;
	}
	return (door);
}
