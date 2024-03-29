/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:33:04 by auferran          #+#    #+#             */
/*   Updated: 2023/06/21 20:30:59 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putstr(char *str)
{
	int	i;
	int	test;

	(void) test;
	i = 0;
	while (str[i])
		i++;
	test = write(1, str, i);
}

void	error(int nb)
{
	if (nb == 0)
	{
		ft_putstr("incorrect name of fractal, ");
		ft_putstr("only 'Mandelbrot', 'Julia', 'Julia 2' and 'Julia 3' ");
		ft_putstr("are available\n");
	}
	if (nb == 1)
		ft_putstr("incorrect number of arguments.\n");
	if (nb == 2)
		ft_putstr("malloc failure ?\n");
}
