/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:04:47 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 20:04:47 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_size(t_lst_cmd *cmd)
{
	int			i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd != NULL)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void	ft_lst_clear(t_lst_cmd **cmd)
{
	int			i;
	int			size;
	t_lst_cmd	*tmp;

	if (!(*cmd))
		return ;
	i = 0;
	size = ft_lst_size(*cmd);
	while (i < size)
	{
		tmp = (*cmd)->next;
		free(*cmd);
		*cmd = tmp;
		i++;
	}
	*cmd = NULL;
}

t_lst_cmd	*ft_lst_last(t_lst_cmd *cmd)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lst_size(cmd);
	while (i < size - 1)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}

void	ft_lst_add_back(t_lst_cmd *lst_new, t_lst_cmd **cmd)
{
	t_lst_cmd	*tmp;

	if (!(*cmd))
	{
		*cmd = lst_new;
		return ;
	}
	tmp = ft_lst_last(*cmd);
	tmp->next = lst_new;
}

t_lst_cmd	*ft_lst_new(void)
{
	t_lst_cmd	*lst_new;

	lst_new = malloc(sizeof(t_lst_cmd));
	if (!lst_new)
		return (error("MALLOC FAILURE\n"), NULL);
	return (lst_new);
}