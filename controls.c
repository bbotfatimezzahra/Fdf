/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:49:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 23:17:42 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf *fdf, int a)
{
	if (a == XK_KP_Add || a == XK_plus)
		fdf->scale += 1;
	if (a == XK_KP_Subtract || a == XK_minus)
		fdf->scale -= 1;
	fill_image(fdf);
}

void	move(t_fdf *fdf, int a)
{
	if (a == XK_Right)
		fdf->offset[0] += 5;
	if (a == XK_Left)
		fdf->offset[0] -= 5;
	if (a == XK_Up)
		fdf->offset[1] -= 5;
	if (a == XK_Down)
		fdf->offset[1] += 5;
	fill_image(fdf);
}

void	angle(float *angle, float value)
{
	*angle += value;
	if (*angle < 0)
		angle += 360;
	if (*angle >= 360)
		*angle -= 360;
}

void	rotate(t_fdf *fdf, int a)
{
	if (a == XK_x || a == XK_X)
		angle(&fdf->angle[0], 0.5);
	if (a == XK_s || a == XK_S)
		angle(&fdf->angle[0], -0.5);
	if (a == XK_y || a == XK_Y)
		angle(&fdf->angle[1], 0.5);
	if (a == XK_h || a == XK_Y)
		angle(&fdf->angle[1], -0.5);
	if (a == XK_z || a == XK_Z)
		angle(&fdf->angle[2], 0.5);
	if (a == XK_a || a == XK_A)
		angle(&fdf->angle[2], -0.5);
	fill_image(fdf);
}

void	reset(t_fdf *fdf, int a)
{
	if (a == XK_b || a == XK_B)
	{
		fdf->angle[0] = 0;
		fdf->angle[1] = 0;
		fdf->angle[2] = 0;
	}
	fill_image(fdf);
}
