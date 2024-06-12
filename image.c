/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/12 23:04:11 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	scale_point(t_point b, int scale)
{
	t_point	a;

	a.x = b.x * scale;
	a.x = (a.x - a.z) * cos(0.46365);
	a.y = b.y * scale;
	a.y = a.y + (a.x + a.z) * sin(0.46365);
	return (a);
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

void	straight_line(t_fdf *fdf, t_point a, t_point b)
{
	t_point	c;

	c = a;
	c.color = WHITE;
	if (a.x == b.x)
	{
		while ((c.y != b.y) && (c.x < 1920) && (c.y < 1080))
			put_pixel(fdf, c.x, ++c.y, c.color);
	}
	else if (a.y == b.y)
	{
		while ((c.x != b.x) && (c.x < 1920) && (c.y < 1080))
			put_pixel(fdf, ++c.x, c.y, c.color);
	}
}

void	angled_line(t_fdf *fdf, t_point a, t_point b)
{
	int		dx;
	int		dy;
	int		p;
	t_point	c;

	c = a;
	c.color = WHITE;
	dx = b.x - a.x;
	dy = b.y - a.y;
	p = 2 * dy - dx;
	while (((c.x != b.x) || (c.y != b.y)) && (c.x < 1920) && (c.y < 1080))
	{
		if (p > 0)
		{
			put_pixel(fdf, ++c.x, ++c.y, c.color);
			p += 2 * dy - 2 * dx;
		}
		else
		{
			put_pixel(fdf, ++c.x, c.y, c.color);
			p += 2 * dy - dx;
		}
	}
}

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < DIS_WIDTH)
	{
		j = 0;
		while (j < DIS_LENGTH)
			put_pixel(fdf, i, j++, 0x00000000);
		i++;
	}
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, int projection)
{
	(void) projection;
	a = scale_point(a, fdf->scale);
	b = scale_point(b, fdf->scale);
	if ((a.x != b.x) && (a.y != b.y))
		angled_line(fdf, a, b);
	else
		straight_line(fdf, a, b);
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
