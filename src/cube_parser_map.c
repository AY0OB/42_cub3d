/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:55 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/16 22:24:18 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cube_where_are_you(t_data *game, int i, int j)
{
	game->player[0] = i;
	game->player[1] = j;
	game->player[2] = game->map[i][j];
	return (1);
}

int	cube_check_surrounding(t_data *game, int i, int j)
{
	if (game->map[i + 1][j] == ' ')
		return (1);
	if (game->map[i - 1][j] == ' ')
		return (1);
	if (game->map[i][j + 1] == ' ')
		return (1);
	if (game->map[i][j - 1] == ' ')
		return (1);
	return (0);
}

void	cube_check_map(t_data *game, int len)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] != ' ' && game->map[i][j] != '1'
				&& game->map[i][j] != '0')
				count = count + cube_where_are_you(game, i, j);
			if (count > 1)
				cube_abort(game, "Error: this is no multiplayer game");
			if (game->map[i][j] != ' ' && game->map[i][j] != '1'
				&& (i == 0 || j == 0 || j == len - 1 || !game->map[i + 1]
				|| cube_check_surrounding(game, i, j)))
				cube_abort(game, "Error: invalid map");
		}
	}
	if (!count)
		cube_abort(game, "Error: missing starting point");
}

void	cube_copy_map(t_data *game, int cur, int len)
{
	int	i;
	int	j;
	int	empty;

	i = -1;
	while (game->tab[cur] && i < 128)
	{
		j = -1;
		empty = 0;
		game->map[++i] = ft_calloc(sizeof(char), len + 1);
		if (!game->map[i])
			cube_abort(game, "Error: malloc failure");
		while (game->tab[cur][++j] && j < 128)
		{
			game->map[i][j] = game->tab[cur][j];
			if (!empty && game->tab[cur][j] && game->tab[cur][j] != ' ')
				empty = 1;
		}
		while (j < len)
			game->map[i][j++] = ' ';
		if (!empty)
			cube_abort(game, "Error: empty line in map");
		cur++;
	}
	game->tab[cur] = NULL;
}

void	cube_fill_map(t_data *game, int cur)
{
	int	i;
	int	sl[2];

	sl[0] = 0;
	sl[1] = 0;
	while (game->tab[++cur])
	{
		i = -1;
		while (game->tab[cur][++i])
		{
			if (!sl[0] && ft_strchr(game->token, game->tab[cur][i]))
				sl[0] = cur;
			if (game->tab[cur][i] != ' ' && !ft_isspace(game->tab[cur][i])
				&& !ft_strchr(game->token, game->tab[cur][i]))
				cube_abort(game, "Error: invalid line/map character");
			if (sl[0] && game->tab[cur][i] != ' '
				&& !ft_strchr(game->token, game->tab[cur][i]))
				cube_abort(game, "Error: invalid map character");
		}
		if (sl[0] && i > sl[1])
			sl[1] = i;
	}
	if (!sl[0] || !sl[1])
		cube_abort(game, "Error: map unavailable");
	cube_copy_map(game, sl[0], sl[1]);
}
