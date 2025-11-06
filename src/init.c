/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:35:45 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 18:39:41 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = 5.0;
	player->pos_y = 5.0;
	player->dir_x = 0;	//UP
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0.0;
	player->x = 0;
	player->camera_x = 2 * player->x / WIDTH - 1;
	player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
	player->raydir_y = player->dir_y + player->plane_y * player->camera_x;
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	//player->dir_x = 0;	//DOWN
	//player->dir_y = 1;
	//player->dir_x = 1;	//RIGHT
	//player->dir_y = 0;
	//player->dir_x = -1;	//LEFT
	//player->dir_y = 0;
	player->k_up = false;
	player->k_down = false;
	player->k_left = false;
	player->k_right = false;
	player->l_rotate = false;
	player->r_rotate = false;
}

static char	**get_map(void)
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
