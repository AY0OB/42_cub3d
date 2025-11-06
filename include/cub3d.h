/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:29:11 by amairia           #+#    #+#             */
/*   Updated: 2025/11/04 11:15:19 by amairia          ###   ########.fr       */
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
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;

	float	cameraX;
	float	rayDirX;
	float	rayDirY;
	int		mapX;
	int		mapY;

	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	int		stepX;
	int		stepY;
	int		side;

	float	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
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
int		key_press(int keycode, t_player *player);
void	move_player(t_game *game, t_player *p);

void	raycast(t_player *p, t_game *game);
void	perform_dda(t_player *p, t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);

void		clear_all(t_game *game);

#endif
