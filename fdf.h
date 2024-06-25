/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:48:16 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/25 21:23:01 by fbbot            ###   ########.fr       */
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
# include <math.h>
# include <stdlib.h>

# define ERR_USAGE "Usage : ./fdf Map_file(file.fdf)"
# define ERR_MAP "Incorrect Map file"
# define ERR_CON "Fdf initialization failure"
# define ERR_WIN "Window initialization failure"
# define ERR_IMG "Image initialization failure"
# define ERR_MALLOC "Allocation failure"
# define USR_INT "User interruption"

# define BLACK 0x00000000
# define GREEN 0x0000FF00
# define COLOR 0x00FF0000

# define DIS_WIDTH 1920
# define DIS_LENGTH 1080

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
	int		scale;
	int		offset[3];
	int		width;
	int		length;
	t_map	map;
}			t_fdf;

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	free_double(char **ptr);
void	terminate(char *error, t_fdf *fdf);
void	zoom(t_fdf *fdf, int a);
char	**ft_split(const char *str, char c, int *length);
int		ft_atoi_base(char *str, char *base);
int		parse_map(char *file, t_fdf *fdf);
void	start_display(t_fdf *fdf);
t_map	scale_map(t_map map, int scale);
void	draw_map(t_fdf *fdf, t_map map);
void	fill_image(t_fdf *fdf, int projection);
#endif
