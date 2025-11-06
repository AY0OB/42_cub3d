/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:28:56 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 17:56:27 by amairia          ###   ########.fr       */
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

char	**get_map(void)
{
	char	**map;

	map = ft_calloc(sizeof(char *), 38);
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
	map[19] = "100000000000001";
	map[20] = "100000000000001";
	map[21] = "100000000000001";
	map[22] = "100000000000001";
	map[23] = "100000000000001";
	map[24] = "100000000000001";
	map[25] = "100000000000001";
	map[26] = "100000000000001";
	map[27] = "100000000000001";
	map[28] = "100000000000001";
	map[29] = "100000000000001";
	map[30] = "100000000000001";
	map[31] = "100000000000001";
	map[32] = "100000000000001";
	map[33] = "100000000000001";
	map[34] = "100000000000001";
	map[35] = "100000000000001";
	map[36] = "111111111111111";
	map[37] = NULL;
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
	game->floor_color = 0xA52A2A;
	game->ceiling_color = 0x87ceeb;
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

	init_game(&game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}
