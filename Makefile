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

# src and obj files
SRC = 	main.c \
		init.c \
		map.c \
		raycast.c \
		utils.c \
		utils2.c \
		utils3.c \
		render.c \
		color.c \
		draw.c \
		input.c \
		malloc.c \
		update.c \
		color_utils.c \
		crc.c \
		filters.c \
		header.c \
		inflate_setups.c \
		inflate_trees.c \
		inflate_utils.c \
		inflate_utils2.c \
		inflate.c \
		parser_utils.c \
		parser_utils2.c \
		parser.c \
		texture.c \
		unfilter.c

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

# SDL compiler & lib flags && installation stuff
ABS_DIR = $(shell pwd)
SDL_ORIG = $(ABS_DIR)/SDL2-2.0.14/
SDL_NEW = $(ABS_DIR)/SDL2/
SDL_INC = -I ./SDL2/include/SDL2/
SDL_CFLAG = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --cflags)
SDL_LIBS = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --libs)

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
OBJDIR = ./objs/

all: SDL obj $(FT_LIB) $(NAME)

SDL:
	@if [ ! -d "$(SDL_NEW)" ] ; then \
	mkdir -p $(SDL_NEW) ; \
	cd $(SDL_NEW) && \
	$(SDL_ORIG)./configure --prefix=$(SDL_NEW) &&	\
	make -j10 && make install ; \
	else	\
	make -j10 -C $(SDL_NEW) ; \
	fi;

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
	@if [ -d "$(SDL_NEW)" ] ; then \
	make -C $(SDL_NEW) clean ;	\
	fi;

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean
	rm -rf $(SDL_NEW)

re: fclean all

.PHONY: all clean fclean re
.PRECIOUS: author