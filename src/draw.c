/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 18:26:38 by amairia          ###   ########.fr       */
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
		p->perp_wall_dist = ((float)p->map_x - p->pos_x + (1 - p->step_x) * 0.5f) /
			((p->raydir_x != 0.0f) ? p->raydir_x : 1e-6f);
	else
		p->perp_wall_dist = ((float)p->map_y - p->pos_y + (1 - p->step_y) * 0.5f) /
			((p->raydir_y != 0.0f) ? p->raydir_y : 1e-6f);


	p->line_height = (int)((float)HEIGHT / p->perp_wall_dist);
	p->draw_start = -p->line_height / 2 + HEIGHT / 2;
	if (p->draw_start < 0)
		p->draw_start = 0;
	p->draw_end = p->line_height / 2 + HEIGHT / 2;
	if (p->draw_end >= HEIGHT)
		p->draw_end = HEIGHT - 1;
}

static void draw_textured_column(t_player *p, t_game *game, int x)
{
    int             y;
    t_texture       *tex;
    int             tex_x;
    int             tex_y;
    float           wall_x;
    float           step;
    float           tex_pos;
    unsigned int    color;

    /* Choix de la texture selon la face du mur */
    if (p->side == 0)
    {
        if (p->raydir_x > 0)
            tex = &game->textures[0]; // mur Est
        else
            tex = &game->textures[1]; // mur Ouest
    }
    else
    {
        if (p->raydir_y > 0)
            tex = &game->textures[2]; // mur Sud
        else
            tex = &game->textures[3]; // mur Nord
    }

    /* Calcul de l'endroit exact du mur frappé */
    if (p->side == 0)
        wall_x = p->pos_y + p->perp_wall_dist * p->raydir_y;
    else
        wall_x = p->pos_x + p->perp_wall_dist * p->raydir_x;
    wall_x -= floorf(wall_x);

    /* Position dans la texture */
    tex_x = (int)(wall_x * (float)tex->width);
    if ((p->side == 0 && p->raydir_x < 0) || (p->side == 1 && p->raydir_y > 0))
        tex_x = tex->width - tex_x - 1;

    /* Calcul du pas de balayage dans la texture */
    step = (float)tex->height / p->line_height;
    tex_pos = (float)(p->draw_start - HEIGHT / 2 + p->line_height / 2) * step;

    y = 0;
    while (y < HEIGHT)
    {
        if (y < p->draw_start)
        {
            /* ciel */
            put_pixel(x, y, game->ceiling_color, game);
        }
        else if (y <= p->draw_end)
        {
            /* mur texturé */
            tex_y = (int)tex_pos & (tex->height - 1);
            color = tex->data[tex_y * tex->width + tex_x];
            put_pixel(x, y, color, game);
            tex_pos += step;
        }
        else
        {
            /* sol */
            put_pixel(x, y, game->floor_color, game);
        }
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
