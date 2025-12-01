/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:28:16 by amairia           #+#    #+#             */
/*   Updated: 2025/11/15 05:38:24 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}

void	clear_all(t_game *game)
{
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		free_textures(game);
		if (game->window)
		{
			mlx_clear_window(game->mlx, game->window);
			mlx_destroy_window(game->mlx, game->window);
		}
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		if (game->map)
			free_map(game->map);
	}
	exit(0);
}
