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

t_point	scale_point(t_point b, int scale)
{
	t_point	a;

	a.x = b.x * scale;
	a.y = b.y * scale;
	a.color = b.color;
	return (a);
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < (fdf->width + 1) && y < (fdf->length + 1))
	{
		dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	angled_line(t_fdf *fdf, t_point a, t_point b)
{
	int	dx;
	int	dy;
	int	error;
	int	sx;
	int	sy;

	dx = abs(b.x - a.x);
	dy = -abs(b.y - a.y);
	sx = (b.x > a.x) ? 1 : -1;
	sy = (b.y > a.y) ? 1 : -1;
	error = dx + dy;
	while ((a.x != b.x) || (a.y != b.y))
	{
		put_pixel(fdf, a.x, a.y, a.color);
		if (error * 2 >= dy)
		{
			error += dy;
			a.x += sx;
		}
		if (error * 2 <= dx)
		{
			error += dx;
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

void	draw_line(t_fdf *fdf, t_point a, t_point b, int projection)
{
	(void) projection;
	a = scale_point(a, fdf->scale);
	b = scale_point(b, fdf->scale);
	angled_line(fdf, a, b);
}
/*	
void	rotatex_map(t_fdf *fdf)
{
	int	i;
	int	j;
	int	*y;
	int	*z;
	t_point	*a;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = &fdf->map.points[i][j]
			y = &a.y;
			z = &a.z;
			y = a.y * cos(rad) - a.z * sin(rad);
			z = a.y * sin(rad) + a.z * cos(rad);
			j++;
		}
		i++;
	}
}
*/
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
