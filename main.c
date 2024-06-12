/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:31:34 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/12 21:20:06 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	fdf->map.cols = 0;
	fdf->map.points = NULL;
	fdf->scale = 10;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	init_fdf(&fdf);
	if (argc < 2 || parse_map(argv[1], &fdf))
		terminate(ERR_USAGE, &fdf);
	start_display(&fdf);
	return (0);
}
