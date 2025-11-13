/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secur.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:22:12 by amairia           #+#    #+#             */
/*   Updated: 2025/11/13 19:50:24 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mlx_init_sec(t_game *game)
{
	game->mlx = mlx_init();
	if (!(game->mlx))
	{
		ft_printf("mlx init fails to set up the connection ");
		ft_printf("to the graphical system\n");
		clear_all(game);
	}
}

void	mlx_xpm_file_to_img_sec(t_game *game, t_texture *tex, char *path, int i)
{
	tex->img = mlx_xpm_file_to_image(
			game->mlx, path, &tex->width, &tex->height);
	if (!(tex->img))
	{
		ft_printf("Texture of ");
		if (i == 0)
			ft_printf("east wall <%s> ", path);
		else if (i == 1)
			ft_printf("west wall <%s> ", path);
		else if (i == 2)
			ft_printf("south wall <%s> ", path);
		else
			ft_printf("north wall <%s> ", path);
		ft_printf("cant be charged\n");
		clear_all(game);
	}
}

void	mlx_get_data_addr_sec(t_game *game, t_texture *tex, char *path, int i)
{
	tex->data = mlx_get_data_addr(
			tex->img, &tex->bpp, &tex->line_lgth, &tex->endian);
	if (!(tex->data))
	{
		ft_printf("Data of ");
		if (i == 0)
			ft_printf("east wall img <%s> ", path);
		else if (i == 1)
			ft_printf("west wall img <%s> ", path);
		else if (i == 2)
			ft_printf("south wall img <%s> ", path);
		else
			ft_printf("north wall img <%s> ", path);
		ft_printf("cant be charged\n");
		clear_all(game);
	}
}

void	mlx_new_window_sec(t_game *game, int width, int height, char *title)
{
	game->window = mlx_new_window(game->mlx, width, height, title);
	if (!(game->window))
	{
		ft_printf("Failed to create a new window on the screen\n");
		clear_all(game);
	}
}
