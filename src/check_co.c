/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_co.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:45:34 by amairia           #+#    #+#             */
/*   Updated: 2025/11/04 11:11:28 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	check_x_add(t_game *game, t_player *player, float cos_sin)
{
	if (cos_sin >= 0
		&& game->map[(int)floorf(player->pos_y)][(int)ceilf(player->pos_x)]
		== '1' && player->pos_x > (ceilf(player->pos_x) - 0.2))
		return (false);
	if (cos_sin < 0
		&& game->map[(int)floorf(player->pos_y)][(int)floorf(player->pos_x) - 1]
		== '1' && player->pos_x < (floorf(player->pos_x) + 0.2))
		return (false);
	return (true);
}

bool	check_x_demote(t_game *game, t_player *player, float cos_sin)
{
	if (cos_sin < 0
		&& game->map[(int)floorf(player->pos_y)][(int)ceilf(player->pos_x)]
		== '1' && player->pos_x > (ceilf(player->pos_x) - 0.2))
		return (false);
	if (cos_sin >= 0
		&& game->map[(int)floorf(player->pos_y)][(int)floorf(player->pos_x) - 1]
		== '1' && player->pos_x < (floorf(player->pos_x) + 0.2))
		return (false);
	return (true);
}

bool	check_y_add(t_game *game, t_player *player, float cos_sin)
{
	if (cos_sin >= 0
		&& game->map[(int)ceilf(player->pos_y)][(int)floorf(player->pos_x)]
		== '1' && player->pos_y > (ceilf(player->pos_y) - 0.2))
		return (false);
	if (cos_sin < 0
		&& game->map[(int)floorf(player->pos_y) - 1][(int)floorf(player->pos_x)]
		== '1' && player->pos_y < (floorf(player->pos_y) + 0.2))
		return (false);
	return (true);
}

bool	check_y_demote(t_game *game, t_player *player, float cos_sin)
{
	if (cos_sin < 0
		&& game->map[(int)ceilf(player->pos_y)][(int)floorf(player->pos_x)]
		== '1' && player->pos_y > (ceilf(player->pos_y) - 0.2))
		return (false);
	if (cos_sin >= 0
		&& game->map[(int)floorf(player->pos_y) - 1][(int)floorf(player->pos_x)]
		== '1' && player->pos_y < (floorf(player->pos_y) + 0.2))
		return (false);
	return (true);
}

/* ADD XY ET DEMOTE XY*/
