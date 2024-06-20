/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/14 10:32:44 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	scale_point(t_point b, t_fdf *fdf)
{
	t_point	a;

	a.x = b.x * fdf->scale + fdf->map.x_offset;
	a.y = b.y * fdf->scale + fdf->map.y_offset;
	a.color = b.color;
	return (a);
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < (fdf->width) && y < (fdf->length))
	{
		dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	angled_line(t_fdf *fdf, t_point a, t_point b)
{
	int	dx;
	int	dy;
	int	error[2];
	int	sx;
	int	sy;

	dx = abs(b.x - a.x);
	dy = -abs(b.y - a.y);
	sx = (b.x > a.x) ? 1 : -1;
	sy = (b.y > a.y) ? 1 : -1;
	error[0] = dx + dy;
	while ((a.x != b.x) || (a.y != b.y))
	{
		put_pixel(fdf, a.x, a.y, a.color);
		if ((error[1] = error[0] * 2) > dy)
		{
			error[0] += dy;
			a.x += sx;
		}
		if (error[1] < dx)
		{
			error[0] += dx;
			a.y += sy;
		}
	}
}

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (fdf->width))
	{
		j = 0;
		while (j < (fdf->length))
			put_pixel(fdf, i, j++, BLACK);
		i++;
	}
}


t_point	rotate_x(t_point a, int angle)
{
	int	y;
	int	z;

	y = a.y;
	z = a.z;
	a.y = y * cos(angle) - z * sin(angle);
	a.z = y * sin(angle) + z * cos(angle);
	return (a);
}

t_point	rotate_y(t_point a, int angle)
{
	int	x;
	int	z;

	x = a.x;
	z = a.z;
	a.x = x * cos(angle) + z * sin(angle);
	a.z = -x * sin(angle) + z * cos(angle);
	return (a);
}

t_point	rotate_z(t_point a, double angle)
{
	int	y;
	int	x;

	y = a.y;
	x = a.x;
	a.x = x * cos(angle) - y * sin(angle);
	a.y = x * sin(angle) + y * cos(angle);
	return (a);
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, int projection)
{
	(void) projection;
	a = scale_point(a, fdf);
	b = scale_point(b, fdf);
	//a = rotate_x(a, -45);
	//b = rotate_x(b, -45);
	
	//a = rotate_y(a, -45);
	//b = rotate_y(b, -45);
	
	//a = rotate_z(a, 45.5);
	//b = rotate_z(b, 45.5);
	angled_line(fdf, a, b);
}
void	fill_image(t_fdf *fdf)
{
	int		i;
	int		j;

	draw_background(fdf);
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			if ((j + 1) < fdf->map.cols)
				draw_line(fdf, fdf->map.points[i][j], fdf->map.points[i][j + 1], 0);
			if ((i + 1) < fdf->map.rows)
				draw_line(fdf, fdf->map.points[i][j], fdf->map.points[i + 1][j], 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->con, fdf->win, fdf->img, 0, 0);
}
