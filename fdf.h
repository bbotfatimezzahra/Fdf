/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:48:16 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/05 19:33:42 by fbbot            ###   ########.fr       */
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

# define ERR_USAGE "Usage : ./fdf Map_file(file.fdf)"
# define ERR_MAP "Incorrect Map file"
# define ERR_CON "Fdf initialization failure"
# define ERR_WIN "Window initialization failure"
# define ERR_IMG "Image initialization failure"
# define ERR_MALLOC "Allocation failure"
# define USR_INT "User interruption"

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_point	*next;
	struct s_point	*under;
}		t_point;

typedef struct s_map
{
	int		rows;
	int		columns;
	t_point	*points;
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
void	terminate(char *error, t_fdf *fdf);
int	open_map(char *file, t_fdf *fdf);
#endif
