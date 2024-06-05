/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:44 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/05 15:45:02 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	i = 0;
	if (!n)
		return (0);
	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	while (tmps1[i] && tmps2[i] && (i < n - 1) && (tmps1[i] == tmps2[i]))
			i++;
	return (tmps1[i] - tmps2[i]);
}

int	open_map(char *file, t_fdf *fdf)
{
	char	*str;
	int	fd;

	str = ft_strchr(file, '.');
	if (!str || ft_strncmp(str, ".fdf", 5))
		terminate(ERR_USAGE, fdf);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		terminate(NULL, fdf);
	str = get_next_line(fd);
	while(str)
	{
		fdf->map->rows++;
		printf("%s",str);
		free(str);
		str = get_next_line(fd);
	}
	printf("all good rows%d\n",fdf->map->rows);
	close(fd);
	return (0);
}
