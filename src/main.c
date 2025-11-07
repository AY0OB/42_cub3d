/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:28:56 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 18:40:06 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		put_pixel(x, y + i, color, game);
		put_pixel(x + i, y + size, color, game);
		put_pixel(x + size, y + i, color, game);
		i++;
	}
}

void	clear_img(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*p;

	p = &game->player;
	move_player(game, p);
	clear_img(game);
	if (DEBUG == 1)
	{
		draw_square(p->pos_x * BLOCK, p->pos_y * BLOCK, 6, 0x00FF00, game);
		draw_map(game);
	}
	if (DEBUG == 0)
		raycast(p, game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	ft_printf("window closing\n");
	clear_all(game);
	return (0);
}

int	main(void)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	init_game(&game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}
