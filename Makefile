# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 17:37:01 by rzukale           #+#    #+#              #
#    Updated: 2021/04/22 11:39:48 by rzukale          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
NAME = wolf3d

# src and obj files
SRC = 	main.c init.c map.c raycast.c utils.c utils2.c utils3.c render.c \
		color.c draw.c input.c malloc.c update.c color_utils.c crc.c \
		filters.c header.c inflate_setups.c inflate_trees.c inflate_utils.c \
		inflate_utils2.c inflate.c parser_utils.c parser_utils2.c parser.c \
		texture.c unfilter.c

OBJDIR = ./objs/
OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

# Dynamic evaluation querying your newly installed system libraries
SDL_CFLAG = $(shell pkg-config --cflags sdl2)
SDL_LIBS = $(shell pkg-config --libs sdl2)

# compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

# ft library
FT = ./libft/
FT_LIB = $(addprefix $(FT),libft.a)
FT_INC = -I ./libft/includes
FT_LNK = -L ./libft -lft

# sub-directories
SCRDIR = ./srcs/
INCDIR = ./includes/

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SCRDIR)%.c
	$(CC) $(CFLAGS) $(SDL_CFLAG) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) $(SDL_LIBS) -lm -o $(NAME) 

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all

.PHONY: all clean fclean re obj
.PRECIOUS: author