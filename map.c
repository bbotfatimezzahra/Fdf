/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:44 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/11 16:56:17 by fbbot            ###   ########.fr       */
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
	long long	result;
	long long	sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - '0');
		printf("while %llu sign %llu str %s\n", result,sign, str);
		if (((result * sign) > INT_MAX) || ((result * sign) > INT_MIN))
		{
			printf("hello %llu\n", result * sign);
			return (0);
		}
		i++;
	}
	return (result * sign);
}

void	create_map(char *str, t_fdf *fdf)
{
	char	**rows;
	char	**columns;
	int	i;
	int	j;
	int	tmp;

	rows = ft_split(str, '\n',&fdf->map.rows);
	free(str);
	if (!rows)
		terminate(ERR_MALLOC, fdf);
	fdf->map.points = malloc(sizeof(t_point*) * (fdf->map.rows + 1));
	if (!fdf->map.points)
	{
		free_double(rows);
		terminate(ERR_MALLOC, fdf);
	}
	columns = ft_split(rows[0], ' ', &fdf->map.cols);
	if (!columns)
	{
		free_double(rows);
		terminate(ERR_MALLOC, fdf);
	}
	i = 0;
	while (i < fdf->map.rows)
	{
		fdf->map.points[i] = malloc(sizeof(t_point) * (fdf->map.cols));
		if (!fdf->map.points[i])
		{
			free_double(rows);
			free_double(columns);
			terminate(ERR_MALLOC, fdf);
		}
		j = 0;
		while (j < fdf->map.cols)
		{
			fdf->map.points[i][j].x = i;
			fdf->map.points[i][j].y = j;
			fdf->map.points[i][j].z = ft_atoi(columns[j]);
		//	printf("row %d column %d : %s z = %d\n", i, j, columns[j],fdf->map.points[i]->z);
			if (!fdf->map.points[i]->z && columns[j][0] != '0')
			{
				free_double(rows);
				free_double(columns);
				terminate(ERR_MAP, fdf);
			}		
			j++;
		}
		free_double(columns);
		columns = ft_split(rows[++i], ' ', &tmp);
		if (tmp != fdf->map.cols)
		{
			free_double(rows);
			free_double(columns);
			terminate(ERR_MALLOC, fdf);
		}	
	}
	fdf->map.points[i] = NULL;
	free_double(columns);
	free_double(rows);
	i = j = 0;
	printf("this the map :\n");
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.cols)
		{
			printf("%d ",fdf->map.points[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

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
		map = ft_strjoin(map,*str);
		if (!map)
			terminate(ERR_MALLOC, fdf);
		*str = get_next_line(fd);
	}
	close(fd);
	create_map(map, fdf);
	return (0);
}
