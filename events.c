/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:37:59 by abamksa           #+#    #+#             */
/*   Updated: 2024/07/03 20:00:40 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->ptr, fractal->img.ptr);
	mlx_destroy_window(fractal->ptr, fractal->window);
	mlx_destroy_display(fractal->ptr);
	free(fractal->ptr);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_PLUS)
		fractal->zoom *= 0.95;
	else if (keysym == XK_MINUS)
		fractal->zoom *= 1.05;
	else if (keysym == XK_j)
		fractal->julia_y += 0.1;
	else if (keysym == XK_k)
		fractal->julia_y -= 0.1;
	else if (keysym == XK_l)
		fractal->julia_x += 0.1;
	else if (keysym == XK_h)
		fractal->julia_x -= 0.1;
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == Button5)
		fractal->zoom *= 0.95;
	else if (button == Button4)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}
