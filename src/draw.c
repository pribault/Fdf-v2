/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 19:48:45 by pribault          #+#    #+#             */
/*   Updated: 2017/07/24 17:48:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_color	define_color(t_env *env, int high)
{
	t_color	color;
	double	a;
	
	if (high >= env->moy)
	{
		a = (env->max != env->moy) ?
		(double)(high - env->moy) / (double)(env->max - env->moy) : 1;
		color.r = env->max_c.r * a + env->moy_c.r * (1 - a);
		color.g = env->max_c.g * a + env->moy_c.g * (1 - a);
		color.b = env->max_c.b * a + env->moy_c.b * (1 - a);
		color.a = env->max_c.a * a + env->moy_c.a * (1 - a);
	}
	else
	{
		a = (env->min != env->moy) ?
		(double)(env->moy - high) / (double)(env->moy - env->min) : 1;
		color.r = env->min_c.r * a + env->moy_c.r * (1 - a);
		color.g = env->min_c.g * a + env->moy_c.g * (1 - a);
		color.b = env->min_c.b * a + env->moy_c.b * (1 - a);
		color.a = env->min_c.a * a + env->moy_c.a * (1 - a);
	}
	return (color);
}

t_pixel	get_pixel(t_env *env, int i, int j)
{
	t_pixel			p;
	static double	a = -1;
	static double	b = -1;

	i = (i < 0) ? 0 : i;
	i = (i >= env->map_size.y) ? env->map_size.y - 1 : i;
	j = (j < 0) ? 0 : j;
	j = (j >= env->map_size.x) ? env->map_size.x - 1 : j;
	if (a == -1)
		a = (env->win.w - 1) / (double)(env->map_size.x - 1);
	if (b == -1)
		b = (env->win.h - 1) / (double)(env->map_size.y - 1);
	p.c = define_color(env, env->map[i][j]);
	p.x = a * j;
	p.y = b * i;
	p = smlx_rotate_pixel(env->mat, env->center, p);
	p.y = env->win.h / 2 + (p.y - env->win.h / 2) * cos(env->high) +
	env->map[i][j] * env->fact * -sin(env->high);
	return (p);
}

void	draw_surface(t_thread *thread, int i[2], char a[2])
{
	t_pixel	p[4];

	p[0] = get_pixel(thread->env, i[0], i[1]);
	p[1] = get_pixel(thread->env, i[0], (!a[1]) ? i[1] + 1 : i[1] - 1);
	p[2] = get_pixel(thread->env, (!a[0]) ? i[0] + 1 : i[0] - 1,
	(!a[1]) ? i[1] + 1 : i[1] - 1);
	p[3] = get_pixel(thread->env, (!a[0]) ? i[0] + 1 : i[0] - 1, i[1]);
	smlx_draw_full_polygone(thread->img, p, 4);
}

void	draw_fdf(t_thread *thread, int i[2], char a[2])
{
	t_pixel	p;

	p = get_pixel(thread->env, i[0], i[1]);
	smlx_draw_line(thread->img, p,
	get_pixel(thread->env, i[0], (!a[1]) ? i[1] + 1 : i[1] - 1));
	smlx_draw_line(thread->img, p,
	get_pixel(thread->env, (!a[0]) ? i[0] + 1 : i[0] - 1, i[1]));
}
