/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:55 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/23 19:25:41 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cube_fill_fc(t_data *game, int cur)
{
	char	**temp;
	int		index;

	temp = NULL;
	if (cube_check_fc(game->tab[cur]) == 1)
		temp = ft_split(game->tab[cur] + 2, ',');
	if (!temp)
		cube_abort(game, "Error: invalid Floor/Ceiling\n");
	index = 0;
	if (game->tab[cur][0] == 'C')
		index = 1;
	if (game->fc[index][0] != -1)
	{
		cube_free2dstr(temp);
		cube_abort(game, "Error: repeated Floor/Ceiling\n");
	}
	game->fc[index][0] = ft_atoi(temp[0]);
	game->fc[index][1] = ft_atoi(temp[1]);
	game->fc[index][2] = ft_atoi(temp[2]);
	cube_free2dstr(temp);
}

void	cube_dispatch(t_data *game)
{
	int	i;

	i = -1;
	while (game->tab[++i])
	{
		if (ft_strncmp(game->tab[i], "NO ", 3) == 0)
			cube_fill_north(game, i);
		else if (ft_strncmp(game->tab[i], "SO ", 3) == 0)
			cube_fill_south(game, i);
		else if (ft_strncmp(game->tab[i], "WE ", 3) == 0)
			cube_fill_west(game, i);
		else if (ft_strncmp(game->tab[i], "EA ", 3) == 0)
			cube_fill_east(game, i);
		else if (ft_strncmp(game->tab[i], "F ", 2) == 0
			|| ft_strncmp(game->tab[i], "C ", 2) == 0)
			cube_fill_fc(game, i);
		else if (cube_check_line(game, i))
			break ;
	}
	cube_check_first_half(game);
	cube_fill_map(game, i);
}
