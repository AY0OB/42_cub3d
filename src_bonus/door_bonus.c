/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 19:03:20 by amairia           #+#    #+#             */
/*   Updated: 2025/11/27 20:10:45 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

#include <stdio.h>

void	close_open(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (game->map[(int)game->player.pos_y][(int)game->player.pos_x] == 'C')
	{
		ft_printf_fd(1, "You got crushed !!!\n");
		clear_all(game);
	}
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'D')
				game->map[i][j] = 'C';
			else if (game->map[i][j] == 'C')
				game->map[i][j] = 'D';
			j++;
		}
		i++;
	}
}
