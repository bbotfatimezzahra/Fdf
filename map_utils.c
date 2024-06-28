/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:44:04 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/28 19:27:27 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_color(char *str)
{
	char	*color;

	color = ft_strchr(str, ',');
	if (!color)
		return (GREEN);
	return (ft_atoi_base(&color[1], "0123456789abcdef"));
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	count_scale(t_fdf *fdf)
{
	int	midwid;
	int	midlen;

	midwid = (fdf->width - 10) / fdf->map.rows;
	midlen = (fdf->length - 10) / fdf->map.cols;
	fdf->scale = min(midwid, midlen) / 2;
	if (fdf->scale <= 0)
		fdf->scale = 1;
}

void	count_divisor(t_fdf *fdf)
{
	int	range;

	range = fdf->z_divisor[0] - fdf->z_divisor[1];
	if (range && range < 100)
		fdf->z_divisor[2] = fdf->length / 4 / range;
	if (range && range > 100)
		fdf->z_divisor[2] = fdf->length / 2.75 / range;
}
