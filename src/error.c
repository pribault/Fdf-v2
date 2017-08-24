/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:31:23 by pribault          #+#    #+#             */
/*   Updated: 2017/07/23 17:55:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(int error, int state)
{
	ft_putstr_fd("\033[38;5;124merror: ", 2);
	if (error == 1)
		ft_putendl_fd("arguments not well formated, please check usage", 2);
	else if (error == 2)
		ft_putendl_fd("map not well formated", 2);
	else if (error == 3)
		ft_putendl_fd("cannot allocate memory", 2);
	else if (error == 4)
		ft_putendl_fd("cannot find platform", 2);
	else if (error == 5)
		ft_putendl_fd("cannot find device", 2);
	ft_putstr_fd("\033[0m", 2);
	if (state)
		exit(1);
}
