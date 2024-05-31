/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:31:34 by fbbot             #+#    #+#             */
/*   Updated: 2024/05/31 10:30:45 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"

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

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hello World!");
	img.img = mlx_new_image(mlx_ptr, 500, 500);
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
	mlx_loop(mlx_ptr);
}
