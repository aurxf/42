/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:10:15 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 20:04:48 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_nb_cmd(char *prompt)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

int	init_lst(char *prompt, t_lst_cmd **cmd)
{
	int			i;
	int			nb_cmd;
	t_lst_cmd	*lst_new;

	i = 0;
	lst_new = NULL;
	nb_cmd = check_nb_cmd(prompt) + 1;
	while (i < nb_cmd)
	{
		lst_new = ft_lst_new();
		if (!lst_new)
			return (ft_lst_clear(cmd), 0);
		ft_memset(lst_new, 0, sizeof(t_lst_cmd));
		ft_lst_add_back(lst_new, cmd);
		i++;
	}
	return (1);
}