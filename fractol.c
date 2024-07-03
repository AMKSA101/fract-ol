/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 08:43:03 by abamksa           #+#    #+#             */
/*   Updated: 2024/07/03 20:20:55 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	alloc_error(void)
{
	perror("Memory allocation failure!");
	exit(1);
}

static void	data_init(t_fractal *fractal)
{
	fractal->esc = 4;
	fractal->iter = 53;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->window, KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->window, ButtonPress, \
		ButtonPressMask, mouse_handler, fractal);
	mlx_hook(fractal->window, DestroyNotify, \
		StructureNotifyMask, close_handler, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->ptr = mlx_init();
	if (!fractal->ptr)
		alloc_error();
	fractal->window = mlx_new_window(fractal->ptr, \
		WIDTH, HEIGHT, fractal->name);
	if (!fractal->window)
	{
		mlx_destroy_display(fractal->ptr);
		free(fractal->ptr);
		alloc_error();
	}
	fractal->img.ptr = mlx_new_image(fractal->ptr, WIDTH, HEIGHT);
	if (!fractal->img.ptr)
	{
		mlx_destroy_window(fractal->ptr, fractal->window);
		mlx_destroy_display(fractal->ptr);
		free(fractal->ptr);
		alloc_error();
	}
	fractal->img.pix_ptr = mlx_get_data_addr(fractal->img.ptr, \
		&fractal->img.byte_per_pix, &fractal->img.line_len, \
		&fractal->img.endian);
	data_init(fractal);
	events_init(fractal);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	fractal.name = ft_tolower(av[1]);
	if ((ac == 2 && (!ft_strncmp(fractal.name, "mandelbrot", 10) \
		|| !ft_strncmp(fractal.name, "burningship", 11) \
		|| !ft_strncmp(fractal.name, "tricorn", 7))) \
		|| (ac == 4 && !ft_strncmp(fractal.name, "julia", 5)))
	{
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			check_args(av + 2);
			fractal.julia_x = atod(av[2]);
			fractal.julia_y = atod(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.ptr);
	}
	else
		error_message();
}
