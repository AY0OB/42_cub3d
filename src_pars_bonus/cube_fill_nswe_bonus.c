/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_fill_nswe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:55 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/23 23:35:03 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	cube_fill_north(t_data *game, int cur)
{
	int	i;
	int	j;

	if (game->no != NULL)
		cube_abort(game, "Error: repeating terms\n");
	game->no = malloc(sizeof(char) * (ft_strlen(game->tab[cur]) - 2));
	if (!game->no)
		cube_abort(game, "Error: malloc failure\n");
	i = 2;
	while (ft_isspace(game->tab[cur][i + 1]) || game->tab[cur][i + 1] == ' ')
		i++;
	j = i + 1;
	while (game->tab[cur][++i])
		game->no[i - j] = game->tab[cur][i];
	game->no[i - j] = '\0';
}

void	cube_fill_south(t_data *game, int cur)
{
	int	i;
	int	j;

	if (game->so != NULL)
		cube_abort(game, "Error: repeating terms\n");
	game->so = malloc(sizeof(char) * (ft_strlen(game->tab[cur]) - 2));
	if (!game->so)
		cube_abort(game, "Error: malloc failure\n");
	i = 2;
	while (ft_isspace(game->tab[cur][i + 1]) || game->tab[cur][i + 1] == ' ')
		i++;
	j = i + 1;
	while (game->tab[cur][++i])
		game->so[i - j] = game->tab[cur][i];
	game->so[i - j] = '\0';
}

void	cube_fill_west(t_data *game, int cur)
{
	int	i;
	int	j;

	if (game->we != NULL)
		cube_abort(game, "Error: repeating terms\n");
	game->we = malloc(sizeof(char) * (ft_strlen(game->tab[cur]) - 2));
	if (!game->we)
		cube_abort(game, "Error: malloc failure\n");
	i = 2;
	while (ft_isspace(game->tab[cur][i + 1]) || game->tab[cur][i + 1] == ' ')
		i++;
	j = i + 1;
	while (game->tab[cur][++i])
		game->we[i - j] = game->tab[cur][i];
	game->we[i - j] = '\0';
}

void	cube_fill_east(t_data *game, int cur)
{
	int	i;
	int	j;

	if (game->ea != NULL)
		cube_abort(game, "Error: repeating assets\n");
	game->ea = malloc(sizeof(char) * (ft_strlen(game->tab[cur]) - 2));
	if (!game->ea)
		cube_abort(game, "Error: malloc failure\n");
	i = 2;
	while (ft_isspace(game->tab[cur][i + 1]) || game->tab[cur][i + 1] == ' ')
		i++;
	j = i + 1;
	while (game->tab[cur][++i])
		game->ea[i - j] = game->tab[cur][i];
	game->ea[i - j] = '\0';
}
