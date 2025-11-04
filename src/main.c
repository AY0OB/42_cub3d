/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:28:56 by amairia           #+#    #+#             */
/*   Updated: 2025/11/02 16:37:39 by amairia          ###   ########.fr       */
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
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
}

char	**get_map(void)
{
	char	**map;

	map = ft_calloc(sizeof(char *), 21);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100010000100001";
	map[3] = "100100000010001";
	map[4] = "100000000000001";
	map[5] = "100000110000001";
	map[6] = "100000110000001";
	map[7] = "100000110000001";
	map[8] = "100000110000001";
	map[9] = "100000000000001";
	map[10] = "100000000000001";
	map[11] = "100000000000001";
	map[12] = "100000000000001";
	map[13] = "100000000000001";
	map[14] = "100000000000001";
	map[15] = "100000000000001";
	map[16] = "100000000000001";
	map[17] = "100000000000001";
	map[18] = "100000000000001";
	map[19] = "111111111111111";
	map[20] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->mlx = mlx_init();
	game->map = get_map();
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Recasting test");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_lgth, &game->endian);
	game->floor_color = 0x7c0000;
	game->ceiling_color = 0xFF4500;
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
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

#include <stdio.h>

int	draw_loop(t_game *game)
{
	t_player	*player;
	int		i;

	player = &game->player;
	printf("cos %f, sin %f\n", player->cos_angle, player->sin_angle);
	move_player(game, player);
	clear_img(game);
	if (DEBUG == 1)
	{
		draw_square(player->x - 3, player->y - 3, 6, 0x00FF00, game);
		draw_map(game);
	}

	/*player->ray_x = player->x;
	player->ray_y = player->y;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);

	while (!touch(game))
	{
		put_pixel(player->ray_x, player->ray_y, 0xFF0000, game);
		player->ray_x += player->cos_angle;
		player->ray_y += player->sin_angle;
	}*/

	player->fraction = PI / 3 / WIDTH;
	player->start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, i);
		player->start_x += player->fraction;
		i++;
	}
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

	init_game(&game);
	//mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.window, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}
