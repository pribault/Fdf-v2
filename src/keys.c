/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:15:31 by pribault          #+#    #+#             */
/*   Updated: 2017/07/24 13:38:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	alloc_threads(t_env *env, int n)
{
	int		i;

	i = 0;
	env->n_threads = n;
	if (!(env->threads = (t_thread*)malloc(sizeof(t_thread) * n)))
		return ;
	while (i < n)
	{
		env->threads[i].env = env;
		env->threads[i].i = (i * env->map_size.y) / n;
		env->threads[i].j = ((i + 1) * env->map_size.y) / n;
		env->threads[i].img = smlx_new_image(&env->win, env->win.w,
		env->win.h);
		ft_printf("thread %d: %d to %d\n", i, env->threads[i].i, env->threads[i].j);
		i++;
	}
}

void	ft_keys(t_env *env)
{
	if (env->win.keys.tab[207])
		exit(0);
	if (env->win.keys.tab[261])
		smlx_rotate_matrix(env->mat, -2);
	if (env->win.keys.tab[263])
		smlx_rotate_matrix(env->mat, 2);
	if (env->win.keys.tab[262])
		env->high -= 0.05;
	if (env->win.keys.tab[264])
		env->high += 0.05;
	if (env->win.keys.tab[51])
		env->fact += 10 / (double)(env->max - env->min);
	if (env->win.keys.tab[53])
		env->fact -= 10 / (double)(env->max - env->min);
	if (env->win.keys.buttons[1])
		env->opt += (env->opt & 1) ? -1 : 1;
	env->high += (env->high < 0) ? 2 * PI : 0;
	env->high -= (env->high > 2 * PI) ? 2 * PI : 0;
}
