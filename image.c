/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/25 18:18:43 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			fdf->map.points[i][j].x *= fdf->scale;
			fdf->map.points[i][j].y *= fdf->scale;
			fdf->map.points[i][j].z *= fdf->scale;
			j++;
		}
		i++;
	}
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


void	rotate_x(t_fdf *fdf, double angle)
{
	t_point a;
	int		i;
	int		j;
	int		y;
	int		z;

	angle = angle * M_PI / 180;
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.points[i][j];
			y = a.y;
			z = a.z;
			a.y = y * cos(angle) - z * sin(angle);
			a.z = y * sin(angle) + z * cos(angle);
			fdf->map.points[i][j] = a;
			j++;
		}
		i++;
	}
}

void	rotate_y(t_fdf *fdf, double angle)
{
	t_point a;
	int		i;
	int		j;
	int		x;
	int		z;

	angle = angle * M_PI / 180;
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.points[i][j];
			x = a.x;
			z = a.z;
			a.x = x * cos(angle) + z * sin(angle);
			a.z = -x * sin(angle) + z * cos(angle);
			fdf->map.points[i][j] = a;
			j++;
		}
		i++;
	}
}

void	rotate_z(t_fdf *fdf, double angle)
{
	t_point a;
	int		i;
	int		j;
	int		x;
	int		y;

	angle = angle * M_PI / 180;
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.points[i][j];
			y = a.y;
			x = a.x;
			a.x = x * cos(angle) - y * sin(angle);
			a.y = x * sin(angle) + y * cos(angle);
			fdf->map.points[i][j] = a;
			j++;
		}
		i++;
	}
}

void	translate_map(t_fdf *fdf)
{
	t_point	a;
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.points[i][j];
			a.x += fdf->map.x_offset;
			a.y += fdf->map.y_offset;
			a.z += fdf->map.z_offset;
			fdf->map.points[i][j] = a;
			j++;
		}
		i++;
	}
}

void	convert_iso(t_fdf *fdf)
{
	double	angle;
	t_point	a;
	t_point	b;
	int		i;
	int		j;

	angle = 28.57 * M_PI / 180;
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.points[i][j];
			b.x = (a.x + a.y) * cos(angle);// 0.98- a.z * sin(angle));
			b.y = (a.x - a.y ) * sin(angle) - a.z;// 0.88* cos(angle));
			b.color = a.color;
			fdf->map.points[i][j] = b;
			j++;
		}
		i++;
	}
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, int projection)
{
	(void) projection;
/*	a.x -= fdf->map.rows/2;
	a.y -= fdf->map.cols/2;
	b.x -= fdf->map.rows/2;
	b.y -= fdf->map.cols/2;
*/
//	a = convert_iso(a, fdf);
//	b = convert_iso(b, fdf);
	
//	a = rotate_x(a, 135);
//	b = rotate_x(b, 135);

	//a = scale_point(a, fdf);
	//b = scale_point(b, fdf);

	//a = rotate_y(a, 135);
	//b = rotate_y(b, 135);
	//a = rotate_z(a, 135);
	//b = rotate_z(b, 135);
//	a.y *= -1;
//	b.y *= -1;
	
	angled_line(fdf, a, b);
}
void	fill_image(t_fdf *fdf)
{
	int		i;
	int		j;

	draw_background(fdf);
	//convert_iso(fdf);
//	fdf->scale = 20;
	rotate_x(fdf,30);
	//rotate_y(fdf,330);
	//rotate_z(fdf,30);
	scale_map(fdf);
	translate_map(fdf);
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
