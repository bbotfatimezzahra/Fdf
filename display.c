/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:00:59 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 14:13:11 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		terminate(" ", fdf);
	if (keysym == XK_plus || keysym == XK_KP_Add 
		|| keysym == XK_minus || keysym == XK_KP_Subtract)
		zoom(fdf, keysym);
	if (keysym == XK_Down || keysym == XK_Up 
		|| keysym == XK_Left || keysym == XK_Right)
		move(fdf, keysym);
	if (keysym == XK_i || keysym == XK_I 
		|| keysym == XK_p || keysym == XK_P)
		project(fdf, keysym);
	if (keysym == XK_1 || keysym == XK_2 || keysym == XK_4
		|| keysym == XK_6 || keysym == XK_8 || keysym == XK_9)
		rotate(fdf, keysym);
	if (keysym == XK_KP_1 || keysym == XK_KP_2 || keysym == XK_KP_4 
		|| keysym == XK_KP_6 || keysym == XK_KP_8 || keysym == XK_KP_9)
		rotate(fdf, keysym);
	return (0);
}

int	destroy(t_fdf *fdf)
{
	terminate(" ", fdf);
	return (0);
}


void	start_display(t_fdf *fdf)
{
	fdf->con = mlx_init();
	if (!fdf->con)
		terminate(ERR_CON, fdf);
	fdf->win = mlx_new_window(fdf->con, fdf->width, fdf->length, "FDF PROJECT");
	if (!fdf->win)
		terminate(ERR_WIN, fdf);
	fdf->img = mlx_new_image(fdf->con, fdf->width, fdf->length);
	if (!fdf->img)
		terminate(ERR_IMG, fdf);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->line_length, &fdf->endian);
	fill_image(fdf);
	mlx_hook(fdf->win, 2, 1L<<0, key_hook, fdf);
	mlx_hook(fdf->win, 17, 1L<<2, destroy, fdf);
	mlx_loop(fdf->con);
}
