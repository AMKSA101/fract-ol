/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 08:42:58 by abamksa           #+#    #+#             */
/*   Updated: 2024/07/02 09:48:22 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define XK_MINUS 65453
# define XK_PLUS 65451
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

typedef struct s_img
{
	void	*ptr;
	char	*pix_ptr;
	int		line_len;
	int		byte_per_pix;
	int		endian;
}			t_img;

typedef struct s_fractal
{
	char	*name;
	void	*ptr;
	void	*window;
	double	esc;
	int		iter;
	double	zoom;
	double	shift_x;
	double	shift_y;
	double	julia_x;
	double	julia_y;
	t_img	img;
}			t_fractal;

double		atod(char *s);
void		check_args(char **av);
void		error_message(void);
char		*ft_tolower(char *str);
t_complex	square_complex(t_complex z, int n);
void		fractal_init(t_fractal *fractal);
int			close_handler(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
int			ft_strncmp(char *s1, char *s2, int n);
t_complex	sum_complex(t_complex z1, t_complex z2);
int			key_handler(int keysym, t_fractal *fractal);
int			julia_mouse_track(int x, int y, t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
double		map(double unscaled_num, double new_min, double new_max, \
			double old_max);

#endif
