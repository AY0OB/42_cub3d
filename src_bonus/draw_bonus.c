/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:26:16 by amairia           #+#    #+#             */
/*   Updated: 2025/11/28 19:53:24 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	draw_textured_column(t_game *game, t_draw *draw,
		t_texture *tex, int y)
{
	int			i;
	t_player	*p;
	char		*pix_addr;

	p = &game->player;
	draw->tex_y = (int)draw->tex_pos;
	if (draw->tex_y < 0)
		draw->tex_y = 0;
	if (draw->tex_y >= tex->height)
		draw->tex_y = tex->height - 1;
	pix_addr = tex->data + draw->tex_y * tex->line_lgth
		+ draw->tex_x * draw->bytes_per_pixel;
	draw->color = 0;
	i = 0;
	while (i < draw->bytes_per_pixel && i < 4)
	{
		draw->color |= ((unsigned char)pix_addr[i]) << (8 * i);
		i++;
	}
	put_pixel(p->x, y, draw->color, game);
	draw->tex_pos += draw->step;
}

static void	draw_column(t_game *game, t_texture *tex, t_draw *draw)
{
	int			y;
	t_player	*p;

	p = &game->player;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < p->draw_start)
			put_pixel(p->x, y, game->ceiling_color, game);
		else if (y <= p->draw_end)
			draw_textured_column(game, draw, tex, y);
		else
			put_pixel(p->x, y, game->floor_color, game);
		y++;
	}
}

void	draw(t_player *p, t_game *game, t_texture *tex, int x)
{
	t_draw			draw;

	if (p->side == 0)
		draw.wall_x = p->pos_y + p->perp_wall_dist * p->raydir_y;
	else
		draw.wall_x = p->pos_x + p->perp_wall_dist * p->raydir_x;
	draw.wall_x -= floorf(draw.wall_x);
	draw.tex_x = (int)(draw.wall_x * (float)tex->width);
	if ((p->side == 0 && p->raydir_x < 0) || (p->side == 1 && p->raydir_y > 0))
		draw.tex_x = tex->width - draw.tex_x - 1;
	draw.step = (float)tex->height / (float)p->line_height;
	draw.tex_pos = (p->draw_start - HEIGHT / 2 + p->line_height / 2)
		* draw.step;
	draw.bytes_per_pixel = tex->bpp / 8;
	p->x = x;
	draw_column(game, tex, &draw);
}
