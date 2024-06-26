/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:32 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 18:27:35 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

int	skip_prefix(char *str, int i, int base)
{
	if (str[i] == '0')
	{
		if (base == 2 && str[i + 1] == 'b')
			return (1);
		else if (base == 8 && str[i + 1] == 'o')
			return (1);
		else if (base == 16 && str[i + 1] == 'x')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	char_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	convert_to_decimal(char *str, char *base)
{
	int	converted;
	int	length;
	int	index;
	int	i;

	converted = 0;
	length = 0;
	i = 0;
	while (base[length])
		length++;
	index = char_in_base(str[i], base);
	while (str[i] && index != -1)
	{
		converted = (converted * length) + index;
		i++;
		index = char_in_base(str[i], base);
	}
	return (converted);
}

int	ft_atoi_base(char *str, char *base)
{
	int		sign;
	int		result;
	int		i;

	str_tolower(str);
	str_tolower(base);
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (skip_prefix(str, i, 16))
		i += 2;
	result = convert_to_decimal(&str[i], base);
	return (result * sign);
}
