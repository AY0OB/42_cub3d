/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:09:37 by amairia           #+#    #+#             */
/*   Updated: 2025/11/27 19:18:18 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	draw_player(int x, int y, t_minimap *data, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size)
	{
		j = 0;
		while (j < data->size)
		{
			put_pixel(x + i, y + j, data->color, game);
			j++;
		}
		i++;
	}
}

static void	draw_square(int x, int y, t_minimap *data, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size)
	{
		j = 0;
		while (j < data->size)
		{
			put_pixel(x * data->size + i, y * data->size + j,
				data->color, game);
			j++;
		}
		i++;
	}
}

static void	draw_case(t_game *game, t_minimap *data, int x, int y)
{
	char	**map;

	map = game->map;
	if (map[y][x] == '1')
	{
		data->color = 0x000000;
		draw_square(x, y, data, game);
	}
	else if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		data->color = 0xFFFFFF;
		draw_square(x, y, data, game);
	}
	else if (map[y][x] == 'C')
	{
		data->color = 0x00F000;
		draw_square(x, y, data, game);
	}
	else if (map[y][x] == 'D')
	{
		data->color = 0xFF0000;
		draw_square(x, y, data, game);
	}
}

static void	draw_map(t_game *game, t_minimap *data)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			draw_case(game, data, x++, y);
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_player	*p;
	t_minimap	data_map;
	t_minimap	data_ply;
	int			size_mini;

	size_mini = 80;
	while (size_mini * game->map_height > 250)
		size_mini--;
	while (size_mini * game->map_width > 550)
		size_mini--;
	data_map.size = size_mini;
	data_ply.size = (int)(size_mini * 4 / 5);
	p = &game->player;
	draw_map(game, &data_map);
	data_ply.color = 0xF000F0;
	draw_player(p->pos_x * data_map.size - (int)(data_map.size / 2),
		p->pos_y * data_map.size - (int)(data_map.size / 2), &data_ply, game);
}
