/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:35:46 by auferran          #+#    #+#             */
/*   Updated: 2023/03/17 22:27:17 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (!check_arg(argv))
			return (ft_error(), 0);
		push_swap(argv);
	}
	if (!argv)
		ft_error();
	return (0);
}
