/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:54:34 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/11 15:28:58 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0 && s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (fd >= 0)
	{
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
	}
}

void	free_double(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	terminate(char *error, t_fdf *fdf)
{
	int	i;

	i = 0;
	if (fdf->map.points)
	{
		while (fdf->map.points[i])
			free(fdf->map.points[i++]);
		free(fdf->map.points);
	}
	if (fdf->img)
		mlx_destroy_image(fdf->con, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->con, fdf->win);
	if (fdf->con)
	{
		mlx_destroy_display(fdf->con);
		free(fdf->con);
	}
	if (error)
		ft_putendl_fd(error, 1);
	else
		perror(NULL);
	exit(0);
}
