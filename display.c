/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:00:59 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 23:17:07 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		terminate(" ", fdf);
	return (0);
}

int	destroy(t_fdf *fdf)
{
	terminate(" ", fdf);
	return (0);
}

void	start_display(t_fdf *fdf)
{
	int		*l_length;
	int		*endian;
	char	*title;

	l_length = &fdf->line_length;
	endian = &fdf->endian;
	title = "FDF PROJECT ***FBBOT***";
	fdf->con = mlx_init();
	if (!fdf->con)
		terminate(ERR_CON, fdf);
	fdf->win = mlx_new_window(fdf->con, fdf->width, fdf->length, title);
	if (!fdf->win)
		terminate(ERR_WIN, fdf);
	fdf->img = mlx_new_image(fdf->con, fdf->width, fdf->length);
	if (!fdf->img)
		terminate(ERR_IMG, fdf);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, l_length, endian);
	fill_image(fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win, 17, 1L << 2, destroy, fdf);
	mlx_loop(fdf->con);
}
