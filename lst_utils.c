/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:39:11 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/05 16:50:41 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_lstsize(t_point *lst)
{
	int		i;
	t_point	*tmp;

	if (!lst)
		return (0);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_point	*ft_lstnew(int x, int y, int z, int color)
{
	t_point	*list;

	list = malloc(sizeof(t_point));
	if (!list)
		return (NULL);
	list->x = x;
	list->y = y;
	list->z = z;
	list->next = NULL;
	return (list);
}

t_point	*ft_lstlast(t_point *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_point **lst, t_point *new)
{
	t_point	*tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast(tmp);
		tmp->next = new;
	}
}
