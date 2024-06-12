# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbbot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 11:40:05 by fbbot             #+#    #+#              #
#    Updated: 2024/06/12 14:15:27 by fbbot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror 
LFLAGS	= -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
SRC	= main.c map.c display.c image.c clean_utils.c str_utils.c map_utils.c\
	ft_split.c\
	Get_next_line/get_next_line_utils.c Get_next_line/get_next_line.c 
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
