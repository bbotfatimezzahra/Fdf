# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbbot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 11:40:05 by fbbot             #+#    #+#              #
#    Updated: 2024/06/26 18:26:04 by fbbot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror 
LFLAGS	= -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

NAME	= fdf
SRCS	= main.c map.c display.c image.c clean_utils.c str_utils.c map_utils.c\
	ft_split.c ft_atoi_base.c transform.c image_utils.c\
	Get_next_line/get_next_line_utils.c Get_next_line/get_next_line.c 
OBJS	= $(SRCS:%.c=%.o)

BONUS = fdf_bonus
BSRCS	= main.c map.c display_bonus.c image.c clean_utils.c str_utils.c map_utils.c\
	ft_split.c controls_bonus.c ft_atoi_base.c transform.c image_utils.c\
	Get_next_line/get_next_line_utils.c Get_next_line/get_next_line.c 
BOBJS	= $(BSRCS:%.c=%.o)

.PHONY : all bonus re clean fclean

all: $(NAME)

#add the cflags
%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux $(LFLAGS) -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(BOBJS)
	$(CC) $(BOBJS) -Lmlx_linux -lmlx_Linux $(LFLAGS) -o $(BONUS)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all
