/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:47:57 by auferran          #+#    #+#             */
/*   Updated: 2022/09/29 20:51:20 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < argc)
	{	
		while (argv[j][i] != '\0')
		{	
			write(1, &argv[j][i], 1);
			i++;
		}
		write (1, "\n", 1);
		i = 0;
		j++;
	}
}