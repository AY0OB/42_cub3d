/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:27:05 by amairia           #+#    #+#             */
/*   Updated: 2025/11/28 20:14:28 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	raycast(t_player *p, t_game *game)
{
	int			x;
	t_texture	*tex;
	bool		door;

	x = 0;
	while (x < WIDTH)
	{
		calc_ray(p, x);
		door = perform_dda(p, game, 0, 0);
		calc_wall(p);
		if (door)
			tex = &game->textures[4];
		else if (p->side == 0 && p->raydir_x > 0)
			tex = &game->textures[0];
		else if (p->side == 0 && p->raydir_x <= 0)
			tex = &game->textures[1];
		else if (p->side != 0 && p->raydir_y > 0)
			tex = &game->textures[2];
		else
			tex = &game->textures[3];
		draw(p, game, tex, x);
		x++;
	}
}
