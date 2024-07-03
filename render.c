/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:43:32 by abamksa           #+#    #+#             */
/*   Updated: 2024/07/01 19:28:04 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_pixel_put(int *x, int *y, t_img *img, int color)
{
	int	offset;

	offset = (*y * img->line_len) + (*x * (img->byte_per_pix / 8));
	*(unsigned int *)(img->pix_ptr + offset) = color;
}

void	fract_set(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

t_complex	set_fract(char *name, t_complex z, t_complex c)
{
	t_complex	res;

	res = z;
	if (!ft_strncmp(name, "mandelbrot", 10))
		res = sum_complex(square_complex(z, 1), c);
	else if (!ft_strncmp(name, "julia", 5))
		res = sum_complex(square_complex(z, 1), c);
	else if (!ft_strncmp(name, "burningship", 12))
		res = sum_complex(square_complex(z, 0), c);
	else if (!ft_strncmp(name, "tricorn", 7))
		res = sum_complex(square_complex(z, -1), c);
	return (res);
}

void	handle_pixels(int *x, int *y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(*x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(*y, +2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	fract_set(&z, &c, fractal);
	while (i < fractal->iter)
	{
		z = set_fract(fractal->name, z, c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->esc)
		{
			color = map(i, BLACK, WHITE, fractal->iter);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			handle_pixels(&x, &y, fractal);
	}
	mlx_put_image_to_window(fractal->ptr, fractal->window, \
		fractal->img.ptr, 0, 0);
}
