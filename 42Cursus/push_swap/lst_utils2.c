/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:12:42 by auferran          #+#    #+#             */
/*   Updated: 2023/03/17 23:50:43 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lst_clear(t_lst **lst)
{
	t_lst	*tmp;
	int		i;
	int		size;

	if (!*lst)
		return ;
	i = 0;
	size = ft_lst_size(*lst);
	while (i < size)
	{
		tmp = (*lst)->next;
		free (*lst);
		*lst = tmp;
		i++;
	}
	*lst = NULL;
}

t_lst	*ft_lstmap(t_lst *lst)
{
	t_lst	*new_lst;
	t_lst	*new_element;
	int		tmp;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	tmp = lst->nb;
	while (lst)
	{
		new_element = ft_lst_new(lst->nb, &new_lst);
		if (!new_element)
		{
			ft_lst_clear(&new_lst);
			return (NULL);
		}
		ft_add_back(&new_lst, new_element);
		if (lst->next->nb == tmp)
		{
			lst = lst->next;
			return (new_lst);
		}
	lst = lst->next;
	}
	return (new_lst);
}
