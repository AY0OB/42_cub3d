/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <ledupont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:29:11 by amairia           #+#    #+#             */
/*   Updated: 2025/12/01 23:40:01 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../ft_printf_fd/ft_printf_fd.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>

typedef struct s_data
{
	char	**tab;
	char	*token;
	char	*cd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		xy[2];
	int		fc[2][3];
	int		player[3];
	char	*map[129];
}	t_data;

void	cube_abort(t_data *game, char *str);
void	cube_check_door(t_data *game, int i, int j);
int		cube_check_fc(char *str);
void	cube_check_first_half(t_data *game);
int		cube_check_line(t_data *game, int cur);
void	cube_check_map(t_data *game, int len);
int		cube_check_nswefc(t_data *game);
void	cube_check_second_half(t_data *game);
void	cube_check_sprites(t_data *game, int fd);
int		cube_check_surrounding(t_data *game, int i, int j);
void	cube_clean_map_left(t_data *game);
void	cube_clean_map_right(t_data *game);
void	cube_copy_map(t_data *game, int cur, int len);
void	cube_dispatch(t_data *game);
void	cube_fill_door(t_data *game, int cur);
void	cube_fill_east(t_data *game, int cur);
void	cube_fill_fc(t_data *game, int cur);
void	cube_fill_map(t_data *game, int cur);
void	cube_fill_north(t_data *game, int cur);
void	cube_fill_south(t_data *game, int cur);
void	cube_fill_tab(t_data *game, char *source, int size);
void	cube_fill_west(t_data *game, int cur);
void	cube_free2dstr(char **strs);
void	cube_free_data(t_data *game);
int		cube_height(char *source);
void	cube_parser(int argc, char **argv, t_data *game);
int		cube_where_are_you(t_data *game, int i, int j);
int		ft_isspace(char c);

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
# define SPC 32
# define CLC_LEFT 1

typedef struct s_player
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

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_lgth;
	int		endian;
}		t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*img;	
	char		*data;

	int			bpp;
	int			line_lgth;
	int			endian;

	t_player	player;
	char		**map;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;

	t_texture	textures[5];
	t_texture	sprites[6];
}		t_game;

typedef struct s_draw
{
	int				tex_x;
	int				tex_y;
	float			wall_x;
	float			step;
	float			tex_pos;
	unsigned int	color;
	int				bytes_per_pixel;
}		t_draw;

typedef struct s_minimap
{
	int	size;
	int	color;
}		t_minimap;

void	init_game(t_game *game, t_data *data);
void	init_player(t_player *player);
void	feed_game_data(t_game *game, t_data *data);

void	mlx_init_sec(t_game *game, t_data *data);
int		mlx_new_window_sec(t_game *game, int width, int height, char *title);
int		mlx_xpm_file_to_img_sec(t_game *game,
			t_texture *tex, char *path, int i);
int		mlx_get_data_addr_sec(t_texture *tex, char *path, int i);

int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_game *g);
void	move_player(t_game *game, t_player *p);
void	move_player_mouse(t_player *p, int mouse_x);
void	close_open(t_game *game);

void	raycast(t_player *p, t_game *game);
void	draw(t_player *p, t_game *game, t_texture *tex, int x);
void	draw_minimap(t_game *game);
bool	perform_dda(t_player *p, t_game *game, int hit, int steps);
void	put_pixel(int x, int y, int color, t_game *game);
void	cube_display_sprites(t_game *game);

void	clear_all(t_game *game);

#endif
