/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:48:16 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/11 15:29:26 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include "./Get_next_line/get_next_line.h"
# include <limits.h>
# include <stdint.h>

# define ERR_USAGE "Usage : ./fdf Map_file(file.fdf)"
# define ERR_MAP "Incorrect Map file"
# define ERR_CON "Fdf initialization failure"
# define ERR_WIN "Window initialization failure"
# define ERR_IMG "Image initialization failure"
# define ERR_MALLOC "Allocation failure"
# define USR_INT "User interruption"

# define WHITE "FFFFFF"

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}		t_point;

typedef struct s_map
{
	int		rows;
	int		cols;
	t_point	**points;
}		t_map;

typedef struct s_fdf
{
	void	*con;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_map	map;
}			t_fdf;
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	free_double(char **ptr);
void	terminate(char *error, t_fdf *fdf);
char	**ft_split(const char *str, char c, int *length);
int	open_map(char *file, t_fdf *fdf);
#endif
