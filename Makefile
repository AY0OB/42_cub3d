# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amairia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:14:16 by amairia           #+#    #+#              #
#    Updated: 2025/11/02 21:42:02 by amairia          ###   ########.fr        #
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
	$(FIC)player.c\
	$(FIC)draw.c\
	$(FIC)put_pixel.c\
	$(FIC)clear_all.c\
	$(FIC)check_co.c\

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
