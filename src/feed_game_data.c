/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_game_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 03:35:04 by amairia           #+#    #+#             */
/*   Updated: 2025/11/16 23:14:23 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_color(t_game *game, t_data *data)
{
	game->floor_color
		= data->fc[0][0] << 16 | data->fc[0][1] << 8 | data->fc[0][2];
	game->ceiling_color
		= data->fc[1][0] << 16 | data->fc[1][1] << 8 | data->fc[1][2];
}

static void	alloc_map(t_game *game, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
		i++;
	game->map = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		game->map[i] = ft_calloc(sizeof(char), j + 1);
		i++;
	}
}

static void	feed_map(t_game *game, t_data *data)
{
	int	i;
	int	j;

	alloc_map(game, data);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			game->map[i][j] = data->map[i][j];
			j++;
		}
		i++;
	}
	set_color(game, data);
}

void	feed_game_data(t_game *game, t_data *data)
{
	if (data->player[2] == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (data->player[2] == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (data->player[2] == 'W')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
	game->player.pos_x = data->player[1] + 0.5;
	game->player.pos_y = data->player[0] + 0.5;
	feed_map(game, data);
}
