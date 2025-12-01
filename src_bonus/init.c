/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:35:45 by amairia           #+#    #+#             */
/*   Updated: 2025/12/01 23:58:27 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	exit_prog(t_game *game, t_data *data)
{
	cube_free_data(data);
	clear_all(game);
}

static void	load_texture_stick_sword(t_game *game, t_data *data)
{
	if (mlx_xpm_file_to_img_sec(game,
			&game->sprites[4], "textures/stick.xpm", 9) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->sprites[4],
			"textures/stick.xpm", 9) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game,
			&game->sprites[5], "textures/sword.xpm", 10) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->sprites[5],
			"textures/sword.xpm", 10) == -1)
		exit_prog(game, data);
}

static void	load_textures_sprites(t_game *game, t_data *data)
{
	if (mlx_xpm_file_to_img_sec(game,
			&game->sprites[0], "textures/sprite_one.xpm", 5) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->sprites[0],
			"textures/sprite_one.xpm", 5) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game,
			&game->sprites[1], "textures/sprite_two.xpm", 6) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->sprites[1],
			"textures/sprite_two.xpm", 6) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game,
			&game->sprites[2], "textures/sprite_three.xpm", 7) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->sprites[2],
			"textures/sprite_three.xpm", 7) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game,
			&game->sprites[3], "textures/sprite_four.xpm", 8) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->sprites[3],
			"textures/sprite_four.xpm", 8) == -1)
		exit_prog(game, data);
	load_texture_stick_sword(game, data);
}

static void	load_textures(t_game *game, t_data *data)
{
	if (mlx_xpm_file_to_img_sec(game, &game->textures[0], data->ea, 0) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->textures[0], data->ea, 0) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game, &game->textures[1], data->we, 1) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->textures[1], data->we, 1) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game, &game->textures[2], data->so, 2) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->textures[2], data->so, 2) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game, &game->textures[3], data->no, 3) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->textures[3], data->no, 3) == -1)
		exit_prog(game, data);
	if (mlx_xpm_file_to_img_sec(game, &game->textures[4], data->cd, 4) == -1)
		exit_prog(game, data);
	if (mlx_get_data_addr_sec(&game->textures[4], data->no, 4) == -1)
		exit_prog(game, data);
	load_textures_sprites(game, data);
}

void	init_game(t_game *game, t_data *data)
{
	init_player(&game->player);
	mlx_init_sec(game, data);
	load_textures(game, data);
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	if (mlx_new_window_sec(game, WIDTH, HEIGHT, "CUB3D BONUS") == -1)
		exit_prog(game, data);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->img))
	{
		ft_printf_fd(2, "Failed to creates a new image\n");
		clear_all(game);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_lgth, &game->endian);
	if (!(game->data))
	{
		ft_printf_fd(2, "Data of main img cant be charged\n");
		clear_all(game);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	feed_game_data(game, data);
}
