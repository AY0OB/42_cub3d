/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:29:11 by amairia           #+#    #+#             */
/*   Updated: 2025/11/06 17:59:02 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <math.h>

# define DEBUG 0

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64


# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364


# define PI 3.14159265359
# define FOV PI / 3

typedef struct	s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;

	float	camera_x;
	float	raydir_x;
	float	raydir_y;
	int		map_x;
	int		map_y;

	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;

	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		x;

	bool	k_up;
	bool	k_down;
	bool	k_left;
	bool	k_right;

	bool	l_rotate;
	bool	r_rotate;
}		t_player;

typedef struct	s_game
{
	void	*mlx;
	void	*window;
	void	*img;	
	char	*data;

	int		bpp;
	int		line_lgth;
	int		endian;

	t_player	player;
	char	**map;
	int		floor_color;
	int		ceiling_color;
}		t_game;

void	init_player(t_player *player);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_game *g);
void	move_player(t_game *game, t_player *p);

void	raycast(t_player *p, t_game *game);
void	perform_dda(t_player *p, t_game *game, int hit, int steps);
void	put_pixel(int x, int y, int color, t_game *game);

void		clear_all(t_game *game);

#endif
