/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 12:56:36 by pribault          #+#    #+#             */
/*   Updated: 2017/07/24 13:02:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS

# include "ft_printf.h"
# include "libsmlx.h"
# include <CL/cl.h>
# include <pthread.h>

typedef struct			s_thread
{
	struct s_env		*env;
	t_image				*img;
	int					i;
	int					j;
}						t_thread;

typedef struct			s_env
{
	t_win				win;
	t_point				map_size;
	int					**map;
	double				**mat;
	double				high;
	double				fact;
	t_point				center;
	t_uchar				opt;
	int					min;
	int					moy;
	int					max;
	t_color				min_c;
	t_color				moy_c;
	t_color				max_c;
	cl_context			context;
	cl_command_queue	queue;
	int					n_threads;
	t_thread			*threads;
}						t_env;

void					ft_error(int error, int state);

void					ft_keys(t_env *env);

void					loop(t_env *env);

void					draw_fdf(t_thread *thread, int i[2], char a[2]);
void					draw_surface(t_thread *thread, int i[2], char a[2]);

void					get_flags(int argc, char **argv, t_env *env);

void					alloc_threads(t_env *env, int n);

#endif
