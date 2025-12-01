/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:03:48 by ledupont          #+#    #+#             */
/*   Updated: 2025/12/01 22:55:28 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static long int	ft_clock_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

static void	draw_sword(t_game *game, t_texture *sprite, int addx, int addy)
{
	int		x;
	int		y;
	char	*pix_addr;
	int		color;
	int		scale;

	scale = 2;
	y = 0;
	while (y < sprite->height * scale)
	{
		x = 0;
		while (x < sprite->width * scale)
		{
			pix_addr = sprite->data + (y / scale) *(sprite->line_lgth)
				+ (x / scale) *(sprite->bpp / 8);
			color = (unsigned char)pix_addr[0]
				| ((unsigned char)pix_addr[1] << 8)
				| ((unsigned char)pix_addr[2] << 16);
			if (color != 0)
				put_pixel(x + addx, y + addy, color, game);
			x++;
		}
		y++;
	}
}

static void	draw_stick(t_game *game, t_texture *sprite, int addx, int addy)
{
	int		x;
	int		y;
	char	*pix_addr;
	int		color;
	float	scale;

	scale = 0.75;
	y = 0;
	while (y < sprite->height * scale)
	{
		x = 0;
		while (x < sprite->width * scale)
		{
			pix_addr = sprite->data + (int)(y / scale) *(sprite->line_lgth)
				+ (int)(x / scale) *(sprite->bpp / 8);
			color = (unsigned char)pix_addr[0]
				| ((unsigned char)pix_addr[1] << 8)
				| ((unsigned char)pix_addr[2] << 16);
			if (color != 0)
				put_pixel(x + addx, y + addy, color, game);
			x++;
		}
		y++;
	}
}

static void	draw_sprite(t_game *game, t_texture *sprite, int addx, int addy)
{
	int		x;
	int		y;
	char	*pix_addr;
	int		color;
	float	scale;

	scale = 1.5;
	y = 0;
	while (y < sprite->height * scale)
	{
		x = 0;
		while (x < sprite->width * scale)
		{
			pix_addr = sprite->data + (int)(y / scale) *(sprite->line_lgth)
				+ (int)(x / scale) *(sprite->bpp / 8);
			color = (unsigned char)pix_addr[0]
				| ((unsigned char)pix_addr[1] << 8)
				| ((unsigned char)pix_addr[2] << 16);
			if (color != 0)
				put_pixel(x + addx, y + addy, color, game);
			x++;
		}
		y++;
	}
}

void	cube_display_sprites(t_game *game)
{
	float	time;
	float	soc;

	time = ft_clock_ms() % 1000;
	soc = cos(time / 1000 * (3.1415 * 2)) * 10;
	if ((time > 0 && time < 126) || (time > 500 && time < 626))
		draw_sprite(game, &game->sprites[0], 770, 450);
	else if ((time > 125 && time < 251) || (time > 625 && time < 751))
		draw_sprite(game, &game->sprites[1], 770, 450);
	else if ((time > 250 && time < 376) || (time > 750 && time < 876))
		draw_sprite(game, &game->sprites[2], 770, 450);
	else
		draw_sprite(game, &game->sprites[3], 770, 450);
	if (game->player.k_down || game->player.k_right || game->player.k_left
		|| game->player.k_up)
		draw_sword(game, &game->sprites[5], 380 + soc, 420 - fabs(soc - 0.5));
	else if (time > 0 && time < 251)
		draw_sword(game, &game->sprites[5], 380 + soc, 420);
	else if (time > 250 && time < 501)
		draw_sword(game, &game->sprites[5], 380 + soc, 415);
	else if (time > 500 && time < 751)
		draw_sword(game, &game->sprites[5], 380 + soc, 410);
	else
		draw_sword(game, &game->sprites[5], 380 + soc, 415);
	draw_stick(game, &game->sprites[4], 580, 430);
}
