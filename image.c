/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 01:26:06 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	if (fdf->scale <= 0)
		fdf->scale = 1;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			fdf->map.tmps[i][j].x = fdf->map.points[i][j].x * fdf->scale;
			fdf->map.tmps[i][j].y = fdf->map.points[i][j].y * fdf->scale;
			fdf->map.tmps[i][j].z = (fdf->map.points[i][j].z - fdf->z_divisor[1])*fdf->z_divisor[2];
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

void	draw_line(t_fdf *fdf, t_point a, t_point b)
{
	int	dx;
	int	dy;
	int	error[2];
	int	sx;
	int	sy;

//	printf("a(%d, %d) b(%d, %d)\n",a.x,a.y,b.x,b.y);
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
//		printf("background\n");
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
			a = fdf->map.tmps[i][j];
			y = a.y;
			z = a.z;
			a.y = y * cos(angle) - z * sin(angle);
			a.z = y * sin(angle) + z * cos(angle);
			fdf->map.tmps[i][j] = a;
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
			a = fdf->map.tmps[i][j];
			x = a.x;
			z = a.z;
			a.x = x * cos(angle) + z * sin(angle);
			a.z = -x * sin(angle) + z * cos(angle);
			fdf->map.tmps[i][j] = a;
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
			a = fdf->map.tmps[i][j];
			y = a.y;
			x = a.x;
			a.x = x * cos(angle) - y * sin(angle);
			a.y = x * sin(angle) + y * cos(angle);
			fdf->map.tmps[i][j] = a;
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

	//printf("translate 1\n");
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			a.x += fdf->offset[0];
			a.y += fdf->offset[1];
			a.z += fdf->offset[2];
			fdf->map.tmps[i][j] = a;
			j++;
		}
		i++;
	}
}

void	center_map(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	a;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			a.x -= (fdf->map.rows * fdf->scale)/2;
			a.y -= (fdf->map.cols * fdf->scale)/2;
			fdf->map.tmps[i][j] = a;
			j++;
		}
		i++;
	}
//	printf("center 2\n");
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
			a = fdf->map.tmps[i][j];
			b.x = (a.x + a.y) * cos(angle);// 0.98- a.z * sin(angle));
			b.y = (a.x - a.y ) * sin(angle) - a.z;// 0.88* cos(angle));
			b.z = a.z;
			b.color = a.color;
			fdf->map.tmps[i][j] = b;
			j++;
		}
		i++;
	}
}

void	convert_par(t_fdf *fdf)
{
	t_point	a;
	t_point	b;
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			b.x = (a.x + a.y);
			b.y = (a.x - a.y ) - a.z;
			b.z = a.z;
			b.color = a.color;
			fdf->map.tmps[i][j] = b;
			j++;
		}
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	t_point	a;
	int		i;
	int		j;

	draw_background(fdf);
//	printf("draw map 1\n");
	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			if ((j + 1) < fdf->map.cols)
				draw_line(fdf, a, fdf->map.tmps[i][j + 1]);
			if ((i + 1) < fdf->map.rows)
				draw_line(fdf, a, fdf->map.tmps[i + 1][j]);
			j++;
		}
		i++;
	}
//	printf("draw map 2\n");
	mlx_put_image_to_window(fdf->con, fdf->win, fdf->img, 0, 0);
}

void	fill_image(t_fdf *fdf, int projection)
{
	t_map	map;

	scale_map(fdf);
	printf("====================scale\n");
	printf("fdf a(%d,%d,%d) map b(%d,%d,%d)\n",fdf->map.points[0][0].x,fdf->map.points[0][0].y,fdf->map.points[0][0].z,fdf->map.tmps[0][0].x,fdf->map.tmps[0][0].y,fdf->map.tmps[0][0].z);
	center_map(fdf);
	printf("====================center\n");
	printf("fdf a(%d,%d,%d) map b(%d,%d,%d)\n",fdf->map.points[0][0].x,fdf->map.points[0][0].y,fdf->map.points[0][0].z,fdf->map.tmps[0][0].x,fdf->map.tmps[0][0].y,fdf->map.tmps[0][0].z);
	if (projection == 1)
		convert_iso(fdf);
	else if (projection == 2)
		convert_par(fdf);
	printf("====================projection\n");
	printf("fdf a(%d,%d,%d) map b(%d,%d,%d)\n",fdf->map.points[0][0].x,fdf->map.points[0][0].y,fdf->map.points[0][0].z,fdf->map.tmps[0][0].x,fdf->map.tmps[0][0].y,fdf->map.tmps[0][0].z);
	//rotate_x(fdf,30);
	//rotate_y(fdf,330);
	//rotate_z(fdf,30);
	translate_map(fdf);
	draw_map(fdf);
	printf("====================drawing\n");
	printf("fdf a(%d,%d,%d) map b(%d,%d,%d)\n",fdf->map.points[0][0].x,fdf->map.points[0][0].y,fdf->map.points[0][0].z,fdf->map.tmps[0][0].x,fdf->map.tmps[0][0].y,fdf->map.tmps[0][0].z);
}
