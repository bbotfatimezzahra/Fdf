/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:49:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 01:52:18 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf *fdf, int a)
{
	if (a == 1)
		fdf->scale += 1;
	if (a == 2)
		fdf->scale -= 1; 
	fill_image(fdf, 1);
}

void	move(t_fdf *fdf, int a)
{
	if (a == 1)
		fdf->offset[1] -= 1;
	if (a == 2)
		fdf->offset[1] += 1;
	if (a == 3)
		fdf->offset[0] -= 1;
	if (a == 4)
		fdf->offset[0] += 1;
}

void	rotate(t_fdf *fdf, int a)
{
	if (a == 1)
		fdf->angle[0] -= 1;
	if (a == 2)
		fdf->angle[0] += 1;
	if (a == 3)
		fdf->angle[1] -= 1;
	if (a == 4)
		fdf->angle[1] += 1;
	if (a == 3)
		fdf->angle[2] -= 1;
	if (a == 4)
		fdf->angle[2] += 1;
}
