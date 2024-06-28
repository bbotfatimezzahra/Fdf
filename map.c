/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:44 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 23:50:40 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_point(char *column, int i, int j, t_fdf *fdf)
{
	fdf->map.points[i][j].x = j;
	fdf->map.points[i][j].y = i;
	fdf->map.points[i][j].z = ft_atoi(column);
	fdf->map.points[i][j].color = set_color(column);
	fdf->map.tmps[i][j].x = j;
	fdf->map.tmps[i][j].y = i;
	fdf->map.tmps[i][j].z = ft_atoi(column);
	fdf->map.tmps[i][j].color = set_color(column);
}

void	fill_row(char **rows, char **columns, int i, t_fdf *fdf)
{
	int	j;

	fdf->map.points[i] = ft_calloc((fdf->map.cols), sizeof(t_point));
	fdf->map.tmps[i] = ft_calloc((fdf->map.cols), sizeof(t_point));
	if (!fdf->map.points[i] || !fdf->map.tmps[i])
	{
		free_double(rows);
		free_double(columns);
		terminate(ERR_MALLOC, fdf);
	}
	j = 0;
	while (j < fdf->map.cols)
	{
		if (!ft_atoi(columns[j]) && (columns[j][0] != '0'))
		{
			free_double(rows);
			free_double(columns);
			terminate(ERR_MAP, fdf);
		}
		fill_point(columns[j], i, j, fdf);
		if (fdf->map.points[i][j].z > fdf->z_divisor[0])
			fdf->z_divisor[0] = fdf->map.points[i][j].z;
		fdf->z_divisor[1] = min(ft_atoi(columns[j]), fdf->z_divisor[1]);
		j++;
	}
}

void	fill_map(char **rows, char **columns, t_fdf *fdf)
{
	int		i;
	int		tmp;

	
	i = 0;
	while (i < fdf->map.rows)
	{
		fill_row(rows, columns, i, fdf);
		free_double(columns);
		columns = ft_split(rows[++i], ' ', &tmp);
		if (columns && tmp != fdf->map.cols)
		{
			free_double(rows);
			free_double(columns);
			terminate(ERR_MAP,fdf);
		}
	}
	fdf->map.points[i] = NULL;
	fdf->map.tmps[i] = NULL;
	free_double(columns);
	free_double(rows);
}

void	create_map(char *str, t_fdf *fdf)
{
	char	**rows;
	char	**columns;

	rows = ft_split(str, '\n', &fdf->map.rows);
	free(str);
	if (!rows)
		terminate(ERR_MALLOC, fdf);
	fdf->map.points = ft_calloc((fdf->map.rows + 1), sizeof(t_point *));
	fdf->map.tmps = ft_calloc((fdf->map.rows + 1), sizeof(t_point *));
	if (!fdf->map.points || !fdf->map.tmps)
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
	fill_map(rows, columns, fdf);
	count_scale(fdf);
	count_divisor(fdf);
	fdf->offset[0] = fdf->width / 2;
	fdf->offset[1] = fdf->length / 1.75;
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
