/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/28 19:39:07 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < (fdf->width) && y < (fdf->length))
	{
		dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, t_bresen bren)
{
	bren.dx = abs(b.x - a.x);
	bren.dy = -abs(b.y - a.y);
	bren.sx = 1;
	bren.sy = 1;
	if (b.x < a.x)
		bren.sx *= -1;
	if (b.y < a.y)
		bren.sy *= -1;
	bren.error[0] = bren.dx + bren.dy;
	while ((a.x != b.x) || (a.y != b.y))
	{
		put_pixel(fdf, a.x, a.y, a.color);
		bren.error[1] = bren.error[0] * 2;
		if (bren.error[1] > bren.dy)
		{
			bren.error[0] += bren.dy;
			a.x += bren.sx;
		}
		if (bren.error[1] < bren.dx)
		{
			bren.error[0] += bren.dx;
			a.y += bren.sy;
		}
	}
}

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < fdf->width)
	{
		j = 0;
		while (j < fdf->length)
			put_pixel(fdf, i, j++, BLACK);
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	t_point		a;
	int			i;
	int			j;
	t_bresen	bren;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			if ((j + 1) < fdf->map.cols)
				draw_line(fdf, a, fdf->map.tmps[i][j + 1], bren);
			if ((i + 1) < fdf->map.rows)
				draw_line(fdf, a, fdf->map.tmps[i + 1][j], bren);
			j++;
		}
		i++;
	}
}

void	fill_image(t_fdf *fdf)
{
	scale_map(fdf);
	center_map(fdf);
	rotate_x(fdf, fdf->angle[0]);
	rotate_y(fdf, fdf->angle[1]);
	rotate_z(fdf, fdf->angle[2]);
	convert_iso(fdf);
	translate_map(fdf);
	draw_background(fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->con, fdf->win, fdf->img, 0, 0);
}
