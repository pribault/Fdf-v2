/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:22:32 by pribault          #+#    #+#             */
/*   Updated: 2017/07/24 16:23:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map(int fd, t_env *env)
{
	char	**array;
	char	*line;
	int		i;
	int		j;

	i = 0;
	lseek(fd, 0, SEEK_SET);
	if (!(env->map = (int**)malloc(sizeof(int*) * env->map_size.y)))
		ft_error(3, 1);
	while (ft_get_next_line(fd, &line) == 1)
	{
		if (!(env->map[i] = (int*)malloc(sizeof(int) * env->map_size.x)))
			ft_error(3, 1);
		array = ft_multisplit(line, " \a\b\t\v\f\r");
		j = 0;
		while (array[j])
		{
			env->map[i][j] = ft_atoi(array[j]);
			env->min = (env->map[i][j] < env->min) ? env->map[i][j] : env->min;
			env->max = (env->map[i][j] > env->max) ? env->map[i][j] : env->max;
			j++;
		}
		i++;
		ft_free_array((void**)array, j + 1);
		free(line);
	}
}

char	get_map(char *file, t_env *env)
{
	char	**array;
	char	*line;
	int		fd;
	int		l;
	int		n;

	l = 0;
	n = -1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	while (ft_get_next_line(fd, &line) == 1)
	{
		array = ft_multisplit(line, " \a\b\t\v\f\r");
		n = (n == -1) ? ft_arraylen(array) : n;
		if (ft_arraylen(array) != n)
			ft_error(2, 1);
		l++;
		ft_free_array((void**)array, n + 1);
		free(line);
	}
	env->map_size = smlx_create_point(n, l);
	fill_map(fd, env);
	close(fd);
	return (1);
}

void	get_flags(int argc, char **argv, t_env *env)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-title") && i < argc - 1)
			env->win.title = ft_strdup(argv[++i]);
		else if (!ft_strcmp(argv[i], "-size") && i < argc - 2)
		{
			env->win.w = ft_atoi(argv[++i]);
			env->win.h = ft_atoi(argv[++i]);
		}
		else if (!get_map(argv[i], env))
			ft_error(1, 1);
		i++;
	}
}
