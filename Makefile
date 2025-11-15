# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amairia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:14:16 by amairia           #+#    #+#              #
#    Updated: 2025/11/15 04:36:42 by amairia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CUB3D = src/cub3d.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FIC = src/
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
	$(FIC)cube_fill_nswe.c\
	$(FIC)cube_parser_check.c\
	$(FIC)cube_parser_dispatch.c\
	$(FIC)cube_parser_map.c\
	$(FIC)cube_parser_utils.c\
	$(FIC)cube_parser.c\
	$(FIC)feed_game_data.c


OBJ = $(SRC:.c=.o)

$(NAME) : $(CUB3D) $(LIBFT) $(MINILIBX)
	$(CC) -o $@ $^ $(MLXFLAGS) $(CFLAGS) $(MTH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CUB3D) : $(OBJ)
	$(AR) $@ $^

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX) :
	$(MAKE) -C $(MINILIBX_DIR) all

all : $(NAME)

clean :
	rm -f $(OBJ) $(CUB3D)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all

.PHONY : all clean fclean re
