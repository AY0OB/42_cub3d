# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amairia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:14:16 by amairia           #+#    #+#              #
#    Updated: 2025/12/01 19:06:35 by amairia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS = cub3D_bonus

CUB3D = src/cub3d.a
CUB3D_BNS = src_bonus/cub3d_bonus.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_FD_DIR = ft_printf_fd
PRINTF_FD = $(PRINTF_FD_DIR)/libftprintf_fd.a

FIC = src/
FICPARS = src_pars/
FIC_BNS = src_bonus/
FICPARS_BNS = src_pars_bonus/
MINILIBX_DIR = minilibx-linux
MINILIBX = -L./$(MINILIBX_DIR)/

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
MTH = -lm
MLXFLAGS = -lmlx -lX11 -lXext

SRC =	$(FIC)main.c\
	$(FIC)init.c\
	$(FIC)secur.c\
	$(FIC)player.c\
	$(FIC)raycast.c\
	$(FIC)draw.c\
	$(FIC)dda.c\
	$(FIC)put_pixel.c\
	$(FIC)clear_all.c\
	$(FIC)feed_game_data.c\
	$(FICPARS)cube_fill_nswe.c\
	$(FICPARS)cube_parser_check.c\
	$(FICPARS)cube_parser_dispatch.c\
	$(FICPARS)cube_parser_map.c\
	$(FICPARS)cube_parser_utils.c\
	$(FICPARS)cube_map_cleaner.c\
	$(FICPARS)cube_parser.c\

OBJ = $(SRC:.c=.o)

SRC_BNS =	$(FIC_BNS)main.c\
		$(FIC_BNS)init.c\
		$(FIC_BNS)init_player.c\
		$(FIC_BNS)secur.c\
		$(FIC_BNS)player.c\
		$(FIC_BNS)mouse.c\
		$(FIC_BNS)door.c\
		$(FIC_BNS)raycast.c\
		$(FIC_BNS)minimap.c\
		$(FIC_BNS)draw.c\
		$(FIC_BNS)cube_sprite.c\
		$(FIC_BNS)dda.c\
		$(FIC_BNS)put_pixel.c\
		$(FIC_BNS)clear_all.c\
		$(FIC_BNS)feed_game_data.c\
		$(FICPARS_BNS)cube_fill_nswe_bonus.c\
		$(FICPARS_BNS)cube_parser_check_bonus.c\
		$(FICPARS_BNS)cube_parser_dispatch_bonus.c\
		$(FICPARS_BNS)cube_parser_map_bonus.c\
		$(FICPARS_BNS)cube_map_cleaner_bonus.c\
		$(FICPARS_BNS)cube_parser_utils_bonus.c\
		$(FICPARS_BNS)cube_parser_bonus.c\

OBJ_BNS = $(SRC_BNS:.c=.o)

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(CUB3D) $(LIBFT) $(MINILIBX) $(PRINTF_FD)
	$(CC) -o $@ $^ $(MLXFLAGS) $(CFLAGS) $(MTH)

$(BONUS) : $(CUB3D_BNS) $(LIBFT) $(MINILIBX) $(PRINTF_FD)
	$(CC) -o $@ $^ $(MLXFLAGS) $(CFLAGS) $(MTH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CUB3D) : $(OBJ)
	$(AR) $@ $^

$(CUB3D_BNS) : $(OBJ_BNS)
	$(AR) $@ $^

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX) :
	$(MAKE) -C $(MINILIBX_DIR) all

$(PRINTF_FD) :
	$(MAKE) -C $(PRINTF_FD_DIR)

clean :
	rm -f $(OBJ) $(CUB3D) $(OBJ_BNS) $(CUB3D_BNS)
	$(MAKE) -C $(PRINTF_FD_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUS)
	rm -f $(LIBFT)
	rm -f $(PRINTF_FD)

re : fclean all

.PHONY : all clean fclean re
