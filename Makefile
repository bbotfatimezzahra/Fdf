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
CFLAGS	= -Wall -Wextra -Werror 
LFLAGS	= -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
SRC	= main.c Get_next_line/get_next_line.c map.c ft_split.c\
	Get_next_line/get_next_line_utils.c utils.c fdf_utils.c

OBJ	= $(SRC:%.c=%.o)

.PHONY : all bonus re clean fclean

all: $(NAME)

#add the cflags
%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux $(LFLAGS) -o $(NAME)

clean:
	rm -f $(NAME) $(OBJ)

fclean: clean

re: clean all
