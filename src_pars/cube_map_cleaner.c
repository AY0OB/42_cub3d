/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:12:21 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/23 22:59:42 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cube_clean_map_right(t_data *game)
{
	int	i;
	int	j;
	int	mod;

	mod = 0;
	while (!mod)
	{
		i = -1;
		j = ft_strlen(game->map[0]) - 1;
		while (!mod && game->map[++i])
		{
			if (game->map[i][j] != ' ')
				mod++;
		}
		if (!mod)
		{
			i = -1;
			while (game->map[++i])
				game->map[i][j] = '\0';
		}
	}
	game->xy[0] = ft_strlen(game->map[0]);
}

void	cube_clean_map_left(t_data *game)
{
	int	i;
	int	mod;

	mod = 0;
	while (!mod && game->map[0][0])
	{
		i = -1;
		while (!mod && game->map[++i])
		{
			if (game->map[i][0] != ' ')
				mod++;
		}
		if (!mod)
		{
			i = -1;
			while (game->map[++i])
			{
				ft_memmove(game->map[i], game->map[i] + 1,
					ft_strlen(game->map[i] + 1));
				game->map[i][ft_strlen(game->map[i]) - 1] = '\0';
			}
		}
	}
	cube_clean_map_right(game);
}
