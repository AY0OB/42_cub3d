/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:28:56 by amairia           #+#    #+#             */
/*   Updated: 2025/11/29 19:26:57 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	draw_loop(t_game *game)
{
	t_player	*p;

	p = &game->player;
	move_player(game, p);
	clear_img(game);
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

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	cube_parser(ac, av, &data);
	ft_memset(&game, 0, sizeof(game));
	init_game(&game, &data);
	cube_free_data(&data);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}
