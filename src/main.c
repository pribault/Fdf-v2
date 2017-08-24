/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 12:56:20 by pribault          #+#    #+#             */
/*   Updated: 2017/07/25 13:56:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_opencl(t_env *env)
{
	cl_platform_id	platform;
	cl_device_id	device;
	cl_int			error;
	char			name[128];

	if (clGetPlatformIDs(1, &platform, NULL) != CL_SUCCESS)
		ft_error(4, 1);
	if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL) !=
	CL_SUCCESS)
		ft_error(5, 1);
	env->context = clCreateContext(NULL, 1, &device, NULL, NULL, &error);
	env->queue = clCreateCommandQueue(env->context, device, 0, &error);
	clGetDeviceInfo(device, CL_DEVICE_NAME, 128, name, NULL);
	ft_printf("device: %s\n", name);
}

void	init_env(int argc, char **argv, t_env *env)
{
	env->mat = smlx_create_matrix(-44);
	env->high = PI / 4;
	env->map_size = smlx_create_point(-1, -1);
	env->map = NULL;
	env->opt = 2;
	env->win.w = 640;
	env->win.h = 480;
	env->min = 0;
	env->max = 0;
	env->min_c = smlx_create_color(0, 128, 128, 0);
	env->moy_c = smlx_create_color(128, 64, 0, 0);
	env->max_c = smlx_create_color(0, 128, 0, 0);
	env->fact = 0;
	env->win.title = "Fdf";
	get_flags(argc, argv, env);
	env->moy = 0;
	env->center = smlx_create_point(env->win.w / 2, env->win.h / 2);
	smlx_init(&env->win, env->win.w, env->win.h, env->win.title);
	smlx_set_flags(&env->win, SMLX_C_SLOPE | SMLX_MOUSE);
	env->threads = NULL;
	alloc_threads(env, 8);
	smlx_key_hook(&env->win);
	mlx_loop_hook(env->win.mlx, (void*)&loop, env);
}

int		main(int argc, char **argv)
{
	t_env	env;

	init_env(argc, argv, &env);
	init_opencl(&env);
	ft_printf("size %d x %d\n\n", env.map_size.x, env.map_size.y);
	mlx_loop(env.win.mlx);
	return (0);
}
