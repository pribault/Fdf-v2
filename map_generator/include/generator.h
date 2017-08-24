/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:51:38 by pribault          #+#    #+#             */
/*   Updated: 2017/07/24 19:26:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include <ft_printf.h>
# include <sys/time.h>

# define SEED	1
# define TOP	2
# define ROOF	4

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct			s_env
{
	t_uchar				opt;
	t_uint				seed;
	t_uint				size;
	int					**map;
	int					min;
	int					max;
	t_uint				roof;
	t_uint				top;
	t_uint				step;
}						t_env;

#endif
