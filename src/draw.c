/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/08 17:18:36 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calc_ray_bis(t_player *p, int x)
{
	p->camera_x = 2.0f * x / (float)WIDTH - 1.0f;
	p->raydir_x = p->dir_x + p->plane_x * p->camera_x;
	p->raydir_y = p->dir_y + p->plane_y * p->camera_x;
	p->map_x = (int)p->pos_x;
	p->map_y = (int)p->pos_y;
	if (p->raydir_x == 0.0f)
		p->delta_dist_x = 1e6f;
	else
		p->delta_dist_x = fabsf(1.0f / p->raydir_x);
	if (p->raydir_y == 0.0f)
		p->delta_dist_y = 1e6f;
	else
		p->delta_dist_y = fabsf(1.0f / p->raydir_y);
}

static void	calc_ray(t_player *p, int x)
{
	calc_ray_bis(p, x);
	if (p->raydir_x < 0)
	{
		p->step_x = -1;
		p->side_dist_x = (p->pos_x - p->map_x) * p->delta_dist_x;
	}
	else
	{
		p->step_x = 1;
		p->side_dist_x = ((float)(p->map_x + 1) - p->pos_x) * p->delta_dist_x;
	}
	if (p->raydir_y < 0)
	{
		p->step_y = -1;
		p->side_dist_y = (p->pos_y - p->map_y) * p->delta_dist_y;
	}
	else
	{
		p->step_y = 1;
		p->side_dist_y = ((float)(p->map_y + 1) - p->pos_y) * p->delta_dist_y;
	}
}

static void	calc_wall(t_player *p)
{
	if (p->side == 0)
	{
		if (p->raydir_x != 0.0f)
			p->perp_wall_dist = ((float)p->map_x - p->pos_x
					+ (1 - p->step_x) * 0.5f) / p->raydir_x;
		else
			p->perp_wall_dist = ((float)p->map_x - p->pos_x
					+ (1 - p->step_x) * 0.5f) / 1e-6f;
	}
	else
	{
		if (p->raydir_y != 0.0f)
			p->perp_wall_dist = ((float)p->map_y - p->pos_y
					+ (1 - p->step_y) * 0.5f) / p->raydir_y;
		else
			p->perp_wall_dist = ((float)p->map_y - p->pos_y
					+ (1 - p->step_y) * 0.5f) / 1e-6f;
	}
	p->line_height = (int)((float)HEIGHT / p->perp_wall_dist);
	p->draw_start = -p->line_height / 2 + HEIGHT / 2;
	if (p->draw_start < 0)
		p->draw_start = 0;
	p->draw_end = p->line_height / 2 + HEIGHT / 2;
	if (p->draw_end >= HEIGHT)
		p->draw_end = HEIGHT - 1;
}

static void	draw_textured_column(t_player *p, t_game *game, int x)
{
	int				y;
	int				i;
	t_texture		*tex;
	t_draw			draw;
	char			*pix_addr;

	/* sélection de la texture selon la face */
	if (p->side == 0)
	{
		if (p->raydir_x > 0)
			tex = &game->textures[0]; /* Est */
		else
			tex = &game->textures[1]; /* Ouest */
	}
	else
	{
		if (p->raydir_y > 0)
			tex = &game->textures[2]; /* Sud */
		else
			tex = &game->textures[3]; /* Nord */
	}

	/* position exacte du point d'impact sur le mur */
	if (p->side == 0)
		draw.wall_x = p->pos_y + p->perp_wall_dist * p->raydir_y;
	else
		draw.wall_x = p->pos_x + p->perp_wall_dist * p->raydir_x;
	draw.wall_x -= floorf(draw.wall_x);

	/* coordonnée X dans la texture */
	draw.tex_x = (int)(draw.wall_x * (float)tex->width);

	/* IMPORTANT : inversion horizontale — signe choisi pour correspondre
	   au comportement de la première version (celle qui rendait correctement) */
	if ((p->side == 0 && p->raydir_x > 0) || (p->side == 1 && p->raydir_y < 0))
		draw.tex_x = tex->width - draw.tex_x - 1;

	/* préparation du balayage vertical (évite l'étirement) */
	draw.step = (float)tex->height / (float)p->line_height;
	draw.tex_pos = (p->draw_start - HEIGHT / 2 + p->line_height / 2) * draw.step;

	draw.bytes_per_pixel = tex->bpp / 8;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < p->draw_start)
			put_pixel(x, y, game->ceiling_color, game);
		else if (y <= p->draw_end)
		{
			/* mur texturé : calcul tex_y puis adresse du pixel */
			draw.tex_y = (int)draw.tex_pos;
			if (draw.tex_y < 0)
				draw.tex_y = 0;
			if (draw.tex_y >= tex->height)
				draw.tex_y = tex->height - 1;

			pix_addr = tex->data + draw.tex_y * tex->line_lgth + draw.tex_x * draw.bytes_per_pixel;

			/* lire la couleur en tenant compte de bpp (on suppose 24/32 bits)
			   on copie dans unsigned int pour éviter l'aliasing */
			draw.color = 0;
			i = 0;
			while (i < draw.bytes_per_pixel && i < 4)
			{
				draw.color |= ((unsigned char)pix_addr[i]) << (8 * i);
				i++;
			}

			put_pixel(x, y, draw.color, game);
			draw.tex_pos += draw.step;
		}
		else
			put_pixel(x, y, game->floor_color, game);
		y++;
	}
}

void	raycast(t_player *p, t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		calc_ray(p, x);
		perform_dda(p, game, 0, 0);
		calc_wall(p);
		draw_textured_column(p, game, x);
		x++;
	}
}
