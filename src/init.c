/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:35:45 by amairia           #+#    #+#             */
/*   Updated: 2025/11/29 20:59:49 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->camera_x = 2 * player->x / WIDTH - 1;
	player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
	player->raydir_y = player->dir_y + player->plane_y * player->camera_x;
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	player->k_up = false;
	player->k_down = false;
	player->k_left = false;
	player->k_right = false;
	player->l_rotate = false;
	player->r_rotate = false;
}

static void	exit_prog(t_game *game, t_data *data)
{
	cube_free_data(data);
	clear_all(game);
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
}

void	init_game(t_game *game, t_data *data)
{
	init_player(&game->player);
	mlx_init_sec(game, data);
	load_textures(game, data);
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	if (mlx_new_window_sec(game, WIDTH, HEIGHT, "CUB3D") == -1)
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
