/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:51:26 by pribault          #+#    #+#             */
/*   Updated: 2017/07/25 13:53:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

void	ft_error(int error, int state)
{
	ft_putstr_fd("\033[38;5;124merror: ", 2);
	if (error == 1)
		ft_putendl_fd("arguments not well formated, please check usage", 2);
	else if (error == 2)
		ft_putendl_fd("step must be equal or greater than 2", 2);
	else
		ft_putendl_fd("unknown", 2);
	ft_putstr_fd("\033[0m", 2);
	if (state)
		exit(1);
}

void	get_args(t_env *env, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-seed") && *i < argc - 1)
	{
		env->opt += (env->opt & SEED) ? 0 : SEED;
		env->seed = ft_atou(argv[++(*i)]);
	}
	else if (!ft_strcmp(argv[*i], "-size") && *i < argc - 1)
		env->size = ft_atou(argv[++(*i)]);
	else if (!ft_strcmp(argv[*i], "-min") && *i < argc - 1)
		env->min = ft_atoi(argv[++(*i)]);
	else if (!ft_strcmp(argv[*i], "-max") && *i < argc - 1)
		env->max = ft_atoi(argv[++(*i)]);
	else if (!ft_strcmp(argv[*i], "-top") && *i < argc - 1)
	{
		env->opt += (env->opt & TOP) ? 0 : TOP;
		env->top = ft_atou(argv[++(*i)]);
	}
	else if (!ft_strcmp(argv[*i], "-roof") && *i < argc - 1)
	{
		env->opt += (env->opt & ROOF) ? 0 : ROOF;
		env->roof = ft_atou(argv[++(*i)]);
	}
	else if (!ft_strcmp(argv[*i], "-step") && *i < argc - 1)
	{
		env->step = ft_atou(argv[++(*i)]);
		if (env->step < 2)
			ft_error(2, 1);
	}
	else
		ft_error(1, 1);
}

void	get_flags(t_env *env, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			get_args(env, argc, argv, &i);
		else
			ft_error(1, 1);
		i++;
	}
}

void	init_struct(t_env *env, int argc, char **argv)
{
	t_uint		i;

	env->opt = 0;
	env->seed = 0;
	env->size = 32;
	env->min = -1;
	env->max = 1;
	env->step = 2;
	get_flags(env, argc, argv);
	if (!(env->opt & TOP))
		env->top = env->size;
	if (!(env->opt & ROOF))
		env->roof = 1;
	// ft_printf("min=%d max=%d\n", env->min, env->max);
	env->map = (int**)ft_alloc_array(env->size, env->size, sizeof(int));
	i = 0;
	while (i < env->size)
		ft_bzero(env->map[i++], env->size);
}

t_uint	get_seed(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec * t.tv_sec);
}

int		ft_rand(int min, int max)
{
	return (min + (ft_abs(rand()) % (max - min + 1)));
}

void	set_square(t_env *env, t_uint i, t_uint j, t_uint size)
{
	int		n;
	t_uint	k;
	t_uint	l;

	n = ft_rand(env->min, env->max);
	k = 0;
	while (k < size && i + k < env->size)
	{
		l = 0;
		while (l < size && j + l < env->size)
		{
			if (ft_sqrt(ft_power(size / 2 - k, 2) + ft_power(size / 2 - l, 2)) <= size / 2)
				env->map[i + k][j + l] += n;
			l++;
		}
		k++;
	}
}

void	generate_map(t_env *env)
{
	t_uint	size;
	t_uint	i;
	t_uint	j;

	size = env->roof;
	while (size < env->top)
	{
		i = 0;
		while (i < env->size)
		{
			j = 0;
			while (j < env->size)
			{
				// ft_printf("\033[1A\033[Ki=%u j=%u size=%u\n", i, j, size);
				set_square(env, i, j, size);
				j += size;
			}
			i += size;
		}
		size *= env->step;
	}
}

void	print_map(t_env *env)
{
	t_uint	i;
	t_uint	j;

	i = 0;
	while (i < env->size)
	{
		j = 0;
		while (j < env->size)
			ft_printf("%d ", env->map[i][j++]);
		ft_putchar('\n');
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_env	env;

	init_struct(&env, argc, argv);
	if (!(env.opt & SEED))
		env.seed = get_seed();
	srand(env.seed);
	generate_map(&env);
	print_map(&env);
	return (0);
}
