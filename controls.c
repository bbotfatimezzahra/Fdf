/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:49:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 19:21:51 by fbbot            ###   ########.fr       */
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
	if (a == XK_8 || a == XK_KP_8)
		angle(&fdf->angle[0], 0.5);
	if (a == XK_2 || a == XK_KP_2)
		angle(&fdf->angle[0], -0.5);
	if (a == XK_4 || a == XK_KP_4)
		angle(&fdf->angle[1], 0.5);
	if (a == XK_6 || a == XK_KP_6)
		angle(&fdf->angle[1], -0.5);
	if (a == XK_1 || a == XK_KP_1)
		angle(&fdf->angle[2], 0.5);
	if (a == XK_9 || a == XK_KP_9)
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
