/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:55 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/27 19:00:23 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cube_check_second_half(t_data *game)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (game->fc[0][i] < 0 || game->fc[0][i] > 255)
			cube_abort(game, "Error: invalid floor value\n");
	i = -1;
	while (++i < 3)
		if (game->fc[1][i] < 0 || game->fc[1][i] > 255)
			cube_abort(game, "Error: invalid ceiling value\n");
}

void	cube_check_first_half(t_data *game)
{
	int	fd;

	if (!game->no || !game->so || !game->we || !game->ea)
		cube_abort(game, "Error: imcomplete data\n");
	fd = open(game->no, O_RDONLY);
	if (fd < 0)
		cube_abort(game, "Error: invalid path\n");
	close(fd);
	fd = open(game->so, O_RDONLY);
	if (fd < 0)
		cube_abort(game, "Error: invalid path\n");
	close(fd);
	fd = open(game->we, O_RDONLY);
	if (fd < 0)
		cube_abort(game, "Error: invalid path\n");
	close(fd);
	fd = open(game->ea, O_RDONLY);
	if (fd < 0)
		cube_abort(game, "Error: invalid path\n");
	close(fd);
	cube_check_second_half(game);
}

int	cube_check_nswefc(t_data *game)
{
	if (game->no && game->so && game->we && game->ea && game->fc[0][0] > -1
		&& game->fc[1][0] > -1)
		return (1);
	return (0);
}

int	cube_check_fc(char *str)
{
	int	i;
	int	len;
	int	count;

	len = ft_strlen(str);
	i = 1;
	while (ft_isspace(str[i + 1]) || str[i + 1] == ' ')
		i++;
	count = 0;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ',')
			return (0);
		if (str[i] == ',')
			count++;
		if (count > 2 || (str[i] == ',' && (i == 2 || str[i - 1] == ','
					|| i == len - 1)))
			return (0);
	}
	if (count != 2)
		return (0);
	return (1);
}

int	cube_check_line(t_data *game, int cur)
{
	int	i;
	int	fill;

	fill = cube_check_nswefc(game);
	if (fill)
		return (1);
	i = -1;
	while (game->tab[cur][++i])
	{
		if (!fill && game->tab[cur][i] != ' '
			&& ft_isspace(game->tab[cur][i]) == 0)
			cube_abort(game, "Error: invalid line/missing terms\n");
	}
	return (0);
}
