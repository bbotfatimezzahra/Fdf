/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:44 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/13 20:15:34 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
int	set_color(char *str)
{
	char	*color;

	color = ft_strchr(str, ','); 
	if (!color)
		return (GREEN);
	return (ft_atoi_base(&color[1], "0123456789abcdef"));
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	fill_row(char **rows, char **columns, int i, t_fdf *fdf)
{
	int	j;

	fdf->map.points[i] = ft_calloc((fdf->map.cols), sizeof(t_point));
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
		if (!fdf->map.points[i][j].z && (columns[j][0] != '0'))
		{
			free_double(rows);
			free_double(columns);
			terminate(ERR_MAP, fdf);
		}
		fdf->map.points[i][j].color = set_color(columns[j]);
		j++;
	}
}

void	fill_map(char **rows, t_fdf *fdf)
{
	char	**columns;
	int		i;
	int		tmp;

	columns = ft_split(rows[0], ' ', &fdf->map.cols);
	if (!columns)
	{
		free_double(rows);
		terminate(ERR_MALLOC, fdf);
	}
	i = 0;
	while (i < fdf->map.rows)
	{
		fill_row(rows, columns, i, fdf);
		free_double(columns);
		columns = ft_split(rows[++i], ' ', &tmp);
		if (tmp != fdf->map.cols)
		{
			free_double(rows);
			free_double(columns);
			terminate(ERR_MAP, fdf);
		}
	}
	fdf->map.points[i] = NULL;
	free_double(columns);
}

void	create_map(char *str, t_fdf *fdf)
{
	char	**rows;

	rows = ft_split(str, '\n', &fdf->map.rows);
	free(str);
	if (!rows)
		terminate(ERR_MALLOC, fdf);
	fdf->map.points = ft_calloc((fdf->map.rows + 1), sizeof(t_point *));
	if (!fdf->map.points)
	{
		free_double(rows);
		terminate(ERR_MALLOC, fdf);
	}
	fill_map(rows, fdf);
	free_double(rows);
	fdf->scale = min((1700 - 10) / fdf->map.rows, (900 - 10) / fdf->map.cols);
	fdf->width = 1700;
	fdf->length = 900;
	int centerx = (fdf->map.points[fdf->map.rows - 1][0].x-fdf->map.points[0][0].x) * fdf->scale / 2;
	int centery = (fdf->map.points[0][fdf->map.cols - 1].y-fdf->map.points[0][0].y) * fdf->scale / 2;
	fdf->map.x_offset = (fdf->width / 2 )- centerx;
	fdf->map.y_offset = (fdf->length / 2 )- centery;
	printf("scale %d width %d rows %d x %d length %d cols %d y %d\n",fdf->scale,fdf->width,fdf->map.rows,fdf->map.x_offset,fdf->length,fdf->map.cols,fdf->map.y_offset );
	/*i = j = 0;
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
	}*/
}

int	parse_map(char *file, t_fdf *fdf)
{
	char	*str;
	char	*map;
	int		fd;

	str = ft_strchr(file, '.');
	if (!str || ft_strncmp(str, ".fdf", 5))
		terminate(ERR_USAGE, fdf);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		terminate(NULL, fdf);
	str = get_next_line(fd);
	if (!str)
		terminate("Empty map file", fdf);
	map = NULL;
	while (str)
	{
		map = ft_strjoin(map, str);
		if (!map)
			terminate(ERR_MALLOC, fdf);
		str = get_next_line(fd);
	}
	close(fd);
	create_map(map, fdf);
	return (0);
}
