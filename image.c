/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/25 21:25:14 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	scale_map(t_map map, int scale)
{
	int		i;
	int		j;

	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			map.points[i][j].x *= scale;
			map.points[i][j].y *= scale;
			map.points[i][j].z *= scale;
			j++;
		}
		i++;
	}
	printf("SCALE FUNC\n");
	return (map);
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

	printf("a(%d, %d) b(%d, %d)\n",a.x,a.y,b.x,b.y);
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
		printf("background\n");
		while (j < (fdf->length))
			put_pixel(fdf, i, j++, BLACK);
		i++;
	}
}


t_map	rotate_x(t_map map, double angle)
{
	t_point a;
	int		i;
	int		j;
	int		y;
	int		z;

	angle = angle * M_PI / 180;
	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			y = a.y;
			z = a.z;
			a.y = y * cos(angle) - z * sin(angle);
			a.z = y * sin(angle) + z * cos(angle);
			map.points[i][j] = a;
			j++;
		}
		i++;
	}
	return (map);
}

t_map	rotate_y(t_map map, double angle)
{
	t_point a;
	int		i;
	int		j;
	int		x;
	int		z;

	angle = angle * M_PI / 180;
	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			x = a.x;
			z = a.z;
			a.x = x * cos(angle) + z * sin(angle);
			a.z = -x * sin(angle) + z * cos(angle);
			map.points[i][j] = a;
			j++;
		}
		i++;
	}
	return (map);
}

t_map	rotate_z(t_map map, double angle)
{
	t_point a;
	int		i;
	int		j;
	int		x;
	int		y;

	angle = angle * M_PI / 180;
	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			y = a.y;
			x = a.x;
			a.x = x * cos(angle) - y * sin(angle);
			a.y = x * sin(angle) + y * cos(angle);
			map.points[i][j] = a;
			j++;
		}
		i++;
	}
	return (map);
}

t_map	translate_map(t_map map,int offset[3])
{
	t_point	a;
	int		i;
	int		j;

	printf("translate 1\n");
	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			a.x += offset[0];
			a.y += offset[1];
			a.z += offset[2];
			map.points[i][j] = a;
			j++;
		}
		i++;
	}
}

t_map	center_map(t_map map, int scale)
{
	int		i;
	int		j;
	t_point	a;

	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			a.x -= (map.rows * scale)/2;
			a.y -= (map.cols * scale)/2;
			map.points[i][j] = a;
			j++;
		}
		i++;
	}
	printf("center 2\n");
	return (map);
}

t_map	convert_iso(t_map map)
{
	double	angle;
	t_point	a;
	t_point	b;
	int		i;
	int		j;

	angle = 28.57 * M_PI / 180;
	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			b.x = (a.x + a.y) * cos(angle);// 0.98- a.z * sin(angle));
			b.y = (a.x - a.y ) * sin(angle) - a.z;// 0.88* cos(angle));
			b.color = a.color;
			map.points[i][j] = b;
			j++;
		}
		i++;
	}
	return (map);
}

t_map	convert_par(t_map map)
{
	t_point	a;
	t_point	b;
	int		i;
	int		j;

	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			b.x = (a.x + a.y);
			b.y = (a.x - a.y ) - a.z;
			b.color = a.color;
			map.points[i][j] = b;
			j++;
		}
		i++;
	}
	return (map);
}

void	draw_map(t_fdf *fdf, t_map map)
{
	t_point	a;
	int		i;
	int		j;

	draw_background(fdf);
	printf("draw map 1\n");
	i = 0;
	while (i < map.rows)
	{
		j = 0;
		while (j < map.cols)
		{
			a = map.points[i][j];
			if ((j + 1) < map.cols)
				draw_line(fdf, a, map.points[i][j + 1]);
			if ((i + 1) < map.rows)
				draw_line(fdf, a, map.points[i + 1][j]);
			j++;
		}
		i++;
	}
	printf("draw map 2\n");
	mlx_put_image_to_window(fdf->con, fdf->win, fdf->img, 0, 0);
}

void	fill_image(t_fdf *fdf, int projection)
{
	t_map	map;

	map = scale_map(fdf->map, fdf->scale);
	printf("hello\n");
	map = center_map(map, fdf->scale);
	printf("hi\n");
	if (projection == 1)
		map = convert_iso(map);
	else if (projection == 2)
		map = convert_par(map);
	//rotate_x(fdf,30);
	//rotate_y(fdf,330);
	//rotate_z(fdf,30);
	map = translate_map(map,fdf->offset);
	draw_map(fdf, map);
}
