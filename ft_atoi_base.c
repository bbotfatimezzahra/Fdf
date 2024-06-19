#include "fdf.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || base[i] <= 32 || base[i] > 126)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

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
	str_tolower(str);
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

	converted = 0;
	length = 0;
	while (base[length])
		length++;
	index = char_in_base(*str, base);
	while (*str && index != -1)
	{
		converted = (converted * length) + index;
		str++;
		index = char_in_base(*str, base);
	}
	return (converted);
}

int	ft_atoi_base(char *str, char *base)
{
	int		sign;
	int		result;
	int		i;
	int		length;

	length = check_base(base);
	if (length <= 1)
		return (0);
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
	if (skip_prefix(str, i, length))
		i += 2;
	result = convert_to_decimal(&str[i], base);
	return (result * sign);
}
