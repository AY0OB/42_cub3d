/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:55 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/17 17:52:43 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	cube_free2dstr(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		free(strs[i++]);
	free(strs);
}

void	cube_free_data(t_data *game)
{
	int	i;

	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->we)
		free(game->we);
	if (game->ea)
		free(game->ea);
	if (game->map[0])
	{
		i = -1;
		while (game->map[++i])
			free(game->map[i]);
	}
	if (game->tab)
		cube_free2dstr(game->tab);
}

void	cube_abort(t_data *game, char *str)
{
	cube_free_data(game);
	ft_printf_fd(2, str);
	exit(1);
}
