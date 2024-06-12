/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:58 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/12 14:13:03 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

void	create_image(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->con, 1000, 1000);
	if (!fdf->img)
		terminate(ERR_IMG, fdf);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->line_length, &fdf->endian);
	int	i = 10;
	while (i <= 20)
	{
		my_mlx_pixel_put(fdf, i, 10, WHITE);
		my_mlx_pixel_put(fdf, i++, 0, WHITE);
	}
	i = 10;
	while (i >= 0)
	{
		my_mlx_pixel_put(fdf, 10, i, WHITE);
		my_mlx_pixel_put(fdf, 20, i--, WHITE);
	}
}
