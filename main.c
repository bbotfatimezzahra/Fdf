/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:31:34 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/03 21:33:31 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

typedef struct s_con {
	void	*mlx;
	void	*win;
}	t_con;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	escape(int keysym, t_con *con)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(con->mlx, con->win);
		mlx_destroy_display(con->mlx);
		free(con->mlx);
		exit(0);
	}
	return (0);
}

int	destroy(t_con *con)
{
	if (con->win)
	{
		mlx_destroy_window(con->mlx, con->win);
		mlx_destroy_display(con->mlx);
		free(con->mlx);
		exit(0);
	}
	return (0);
}

int	main()
{
	t_con	con;
	t_data	img;

	con.mlx = mlx_init();
	con.win = mlx_new_window(con.mlx, 500, 500, "Hello World!");
/*	img.img = mlx_new_image(mlx_ptr, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 6, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 7, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 8, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 9, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 10, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 11, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 12, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 13, 5, 0x00FF0000);
	int	i = 10;
	while (i <= 20)
	{
		my_mlx_pixel_put(&img, i, 10, 0x00FF0000);
		my_mlx_pixel_put(&img, i++, 0, 0x00FF0000);
	}
	i = 10;
	while (i >= 0)
		my_mlx_pixel_put(&img, 10, i--, 0x00FF0000);
		my_mlx_pixel_put(&img, 20, i--, 0x00FF0000);

	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	*/
	mlx_key_hook(con.win, escape, &con);
	mlx_hook(con.win, 17, 1L<<2, destroy, &con);
	mlx_loop(con.mlx);
	return (0);
}
