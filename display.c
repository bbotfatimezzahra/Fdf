/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:00:59 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/12 14:16:04 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	escape(int keysym, t_fdf *fdf)
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
	fdf->con = mlx_init();
	if (!fdf->con)
		terminate(ERR_CON, fdf);
	fdf->win = mlx_new_window(fdf->con, 500, 500, "Hello World!");
	if (!fdf->win)
		terminate(ERR_WIN, fdf);
	create_image(fdf);
	mlx_put_image_to_window(fdf->con, fdf->win, fdf->img, 0, 0);
	mlx_key_hook(fdf->win, escape, fdf);
	mlx_hook(fdf->win, 17, 1L<<2, destroy, fdf);
	mlx_loop(fdf->con);
}
