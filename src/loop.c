/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:18:42 by pribault          #+#    #+#             */
/*   Updated: 2017/07/24 13:37:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	calculate_image(t_thread *t)
{
	int		i[2];
	char	a[2];

	a[0] = (t->env->mat[1][0] > 0) ? 1 : 0;
	a[1] = (t->env->mat[0][0] > 0) ? 1 : 0;
	a[0] = (t->env->high < 0) ? fabs(a[0] - 1) : a[0];
	a[1] = (t->env->high < 0) ? fabs(a[1] - 1) : a[1];
	i[0] = (a[1]) ? t->i : t->j;
	while ((a[1]) ? i[0] < t->j : i[0] >= t->i)
	{
		i[1] = (a[0]) ? 0 : t->env->map_size.x - 1;
		while ((a[0]) ? i[1] < t->env->map_size.x : i[1] >= 0)
		{
			if (t->env->opt & 1)
				draw_surface(t, i, a);
			else
				draw_fdf(t, i, a);
			i[1] += (a[0]) ? 1 : -1;
		}
		i[0] += (a[1]) ? 1 : -1;
	}
}

void	mix_images(t_image *a, t_image *b)
{
	t_color	c;
	int		i;

	i = 0;
	if (a->w != b->w || a->h != b->h)
		return ;
	while (i < a->w * a->h)
	{
		c = b->l[i];
		if (c.a != 255)
			a->l[i] = c;
		i++;
	}
}

void	draw_multithread_2(t_env *env)
{
	pthread_t	threads[env->n_threads];
	int			i;
	char		a;

	i = 0;
	while (i < env->n_threads)
	{
		smlx_clear_image(env->threads[i].img);
		pthread_create(&(threads[i]), NULL, (void*)&calculate_image,
		&(env->threads[i]));
		i++;
	}
	a = (env->mat[0][0] > 0) ? 1 : 0;
	i = (a) ? 0 : env->n_threads - 1;
	while ((a) ? i < env->n_threads : i >= 0)
	{
		pthread_join(threads[i], NULL);
		mix_images(env->threads[0].img, env->threads[i].img);
		i += (a) ? 1 : -1;
	}
	mlx_put_image_to_window(env->win.mlx, env->win.win,
	env->threads[0].img->img, 0, 0);
}

void	draw_multithread_1(t_env *env)
{
	pthread_t	threads[env->n_threads];
	int			i;

	i = 0;
	while (i < env->n_threads)
	{
		smlx_clear_image(env->threads[i].img);
		pthread_create(&(threads[i]), NULL, (void*)&calculate_image,
		&(env->threads[i]));
		i++;
	}
	i = 0;
	while (i < env->n_threads)
	{
		pthread_join(threads[i], NULL);
		mlx_put_image_to_window(env->win.mlx, env->win.win,
		env->threads[i].img->img, 0, 0);
		i++;
	}
}

void	loop(t_env *env)
{
	ft_keys(env);
	if (env->opt & 2)
		draw_multithread_2(env);
	else
		draw_multithread_1(env);
	printf("\033[1A\033[Kcos=%f sin=%f\n", env->mat[0][0], env->mat[1][0]);
}
