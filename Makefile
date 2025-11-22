# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amairia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:14:16 by amairia           #+#    #+#              #
#    Updated: 2025/11/22 21:19:52 by amairia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CUB3D = src/cub3d.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_FD_DIR = ft_printf_fd
PRINTF_FD = $(PRINTF_FD_DIR)/libftprintf_fd.a

FIC = src/
FICPARS = src_pars/
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
	$(FICPARS)cube_parser.c\

OBJ = $(SRC:.c=.o)

$(NAME) : $(CUB3D) $(LIBFT) $(MINILIBX) $(PRINTF_FD)
	$(CC) -o $@ $^ $(MLXFLAGS) $(CFLAGS) $(MTH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CUB3D) : $(OBJ)
	$(AR) $@ $^

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX) :
	$(MAKE) -C $(MINILIBX_DIR) all

$(PRINTF_FD) :
	$(MAKE) -C $(PRINTF_FD_DIR)

all : $(NAME)

clean :
	rm -f $(OBJ) $(CUB3D)
	$(MAKE) -C $(PRINTF_FD_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(PRINTF_FD)

re : fclean all

.PHONY : all clean fclean re
