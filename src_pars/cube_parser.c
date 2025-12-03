/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:55 by ledupont          #+#    #+#             */
/*   Updated: 2025/12/03 00:02:11 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cube_height(char *source)
{
	int		height;
	int		fd;
	char	*line;

	fd = open(source, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error: open\n");
		exit(1);
	}
	line = get_next_line(fd);
	height = 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	close (fd);
	return (height);
}

void	cube_fill_tab(t_data *game, char *source, int size)
{
	int	fd;
	int	i;

	fd = open(source, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error: open\n");
		exit(1);
	}
	game->tab = malloc(sizeof(char *) * size);
	if (!game->tab)
	{
		close(fd);
		ft_printf_fd(2, "Error: malloc fail\n");
		exit(1);
	}
	i = 0;
	game->tab[i] = get_next_line(fd);
	while (game->tab[i])
	{
		if (game->tab[i][ft_strlen(game->tab[i]) - 1] == '\n')
			game->tab[i][ft_strlen(game->tab[i]) - 1] = '\0';
		game->tab[++i] = get_next_line(fd);
	}
	close(fd);
}

void	cube_parser(int argc, char **argv, t_data *game)
{
	int	i;

	if (argc != 2)
	{
		ft_printf_fd(2, "Error: wrong count of argument(s)\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
	{
		ft_printf_fd(2, "Error: wrong format\n");
		exit(1);
	}
	i = cube_height(argv[1]);
	game->token = "01NSWE";
	cube_fill_tab(game, argv[1], i);
	game->fc[0][0] = -1;
	game->fc[1][0] = -1;
	game->player[0] = -1;
	cube_dispatch(game);
	cube_clean_map_left(game);
	cube_check_map(game, ft_strlen(game->map[0]));
}
