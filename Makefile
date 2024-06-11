# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbbot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 11:40:05 by fbbot             #+#    #+#              #
#    Updated: 2024/06/11 13:48:36 by fbbot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
CC	= gcc
LFLAGS	= -L. -lmlx_Linux -lXext -lX11 -lm -lbsd
SRC	= main.c Get_next_line/get_next_line.c map.c ft_split.c\
	Get_next_line/get_next_line_utils.c utils.c fdf_utils.c

OBJ	= $(SRC:%.c=%.o)

.PHONY : all bonus re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

clean:
	rm -f $(NAME) $(OBJ)
fclean: clean

re: clean all
