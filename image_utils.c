/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:24:33 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 18:37:54 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			a.x -= (fdf->map.rows * fdf->scale) / 2;
			a.y -= (fdf->map.cols * fdf->scale) / 2;
			fdf->map.tmps[i][j] = a;
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
			a = fdf->map.tmps[i][j];
			b.x = (a.x - a.y) * cos(angle);
			b.y = (a.x + a.y) * sin(angle) - a.z;
			b.z = a.z;
			b.color = a.color;
			fdf->map.tmps[i][j] = b;
			j++;
		}
		i++;
	}
}

void	scale_map(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	a;
	t_point	b;

	i = 0;
	if (fdf->scale <= 0)
		fdf->scale = 1;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			b = fdf->map.points[i][j];
			a.x = b.x * fdf->scale;
			a.y = b.y * fdf->scale;
			a.z = (b.z - fdf->z_divisor[1]) * fdf->z_divisor[2];
			fdf->map.tmps[i][j] = a;
			j++;
		}
		i++;
	}
}
