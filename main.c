/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:31:34 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/05 16:50:45 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

int	escape(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		terminate(USR_INT, fdf);
	return (0);
}

int	destroy(t_fdf *fdf)
{
	terminate(USR_INT, fdf);
	return (0);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->con = NULL;
	fdf->win = NULL;
	fdf->img = NULL;
	fdf->addr = NULL;
	fdf->bpp = 0;
	fdf->line_length = 0;
	fdf->endian = 0;
	fdf->map.rows = 0;
	fdf->map.columns = 0;
	fdf->map.points = NULL;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	errno = 0;
	init_fdf(&fdf);
	if (argc < 2 || open_map(argv[1], &fdf))
		terminate(ERR_USAGE, &fdf);
	printf("all good rows%d\n",fdf.map.rows);
	fdf.con = mlx_init();
	if (!fdf.con)
		terminate(ERR_CON, &fdf);
	fdf.win = mlx_new_window(fdf.con, 500, 500, "Hello World!");
	if (!fdf.win)
		terminate(ERR_WIN, &fdf);
	fdf.img = mlx_new_image(fdf.con, 1000, 1000);
	if (!fdf.img)
		terminate(ERR_IMG, &fdf);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_length, &fdf.endian);
	int	i = 10;
	while (i <= 20)
	{
		my_mlx_pixel_put(&fdf, i, 10, 0x00FF0000);
		my_mlx_pixel_put(&fdf, i++, 0, 0x00FF0000);
	}
	i = 10;
	while (i >= 0)
	{
		my_mlx_pixel_put(&fdf, 10, i, 0x00FF0000);
		my_mlx_pixel_put(&fdf, 20, i--, 0x00FF0000);
	}
	mlx_put_image_to_window(fdf.con, fdf.win, fdf.img, 0, 0);
	mlx_key_hook(fdf.win, escape, &fdf);
	mlx_hook(fdf.win, 17, 1L<<2, destroy, &fdf);
	mlx_loop(fdf.con);
	return (0);
}
