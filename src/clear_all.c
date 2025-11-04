/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:28:16 by amairia           #+#    #+#             */
/*   Updated: 2025/11/01 21:50:18 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_map(char ***map)
{
	/*int	i;

	i = 0;
	while (map[0][i])
		free(map[0][i++]);*/
	free(map[0]);
}

void	clear_all(t_game *game)
{
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
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
		{
			free_map(&game->map);
		}
	}
	exit(0);
}
