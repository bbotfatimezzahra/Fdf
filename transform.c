/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:03:54 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 18:40:44 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_fdf *fdf, float angle)
{
	t_point	a;
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

void	rotate_y(t_fdf *fdf, float angle)
{
	t_point	a;
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

void	rotate_z(t_fdf *fdf, float angle)
{
	t_point	a;
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

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			a = fdf->map.tmps[i][j];
			a.x += fdf->offset[0];
			a.y += fdf->offset[1];
			fdf->map.tmps[i][j] = a;
			j++;
		}
		i++;
	}
}
