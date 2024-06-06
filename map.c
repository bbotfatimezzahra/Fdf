/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:44 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/06 15:36:20 by fbbot            ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - '0');
		if (result >= LONG_MAX && sign == 1)
			return (-1);
		else if (result > LONG_MAX && sign == -1)
			return (0);
		i++;
	}
	return (result * sign);
}

void	create_map(char *str, t_fdf *fdf)
{
	char	**rows;
	int	row;
	int	col;

	fdf->map.points = malloc(sizeof(t_point*) * (fdf->map.rows + 1));
	if (!fdf->map.points)
		terminate(ERR_MALOC, fdf);
	rows = ft_split(str, '\n');
	free(str);
	row = 0;
	while (rows[row])
	{
		col = 0;
		i = 0;
		while (rows[row][i])
		{
			
		
	printf("this the map :\n%s",map);


int	open_map(char *file, t_fdf *fdf)
{
	char	**str;
	char	*map;
	int	fd;
	int	i;
	t_point	*point;

	*str = ft_strchr(file, '.');
	if (!*str || ft_strncmp(*str, ".fdf", 5))
		terminate(ERR_USAGE, fdf);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		terminate(NULL, fdf);
	*str = get_next_line(fd);
	if (!*str)
		terminate("Empty map file", fdf);
	map = NULL;
	while(*str)
	{
		fdf->map.rows++;
		map = ft_strjoin(map,*str);
		*str = get_next_line(fd);
	}
	close(fd);
	create_map(map, fdf);
	return (0);
}
