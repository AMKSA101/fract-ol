/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:40:22 by abamksa           #+#    #+#             */
/*   Updated: 2024/07/01 16:39:55 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (!s1 || !s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n-- > 0 && *s1)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

double	atod(char *s)
{
	long	integ;
	double	fract;
	double	pow;
	int		sign;

	integ = 0;
	fract = 0;
	sign = 1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		++s;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	while (*s != '.' && *s)
		integ = (integ * 10) + (*s++ - 48);
	if (*s == '.')
		s++;
	while (*s)
	{
		pow /= 10;
		fract = fract + (*s++ - 48) * pow;
	}
	return ((integ + fract) * sign);
}

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (unscaled_num - 0) / (old_max - 0) + new_min);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.x = z1.x + z2.x;
	res.y = z1.y + z2.y;
	return (res);
}

t_complex	square_complex(t_complex z, int n)
{
	t_complex	res;
	int			i;

	i = -1;
	if (!n)
	{
		res.x = (z.x * z.x) - (z.y * z.y);
		res.y = i * 2 * fabs(z.x * z.y);
	}
	else if (n < 0)
	{
		res.x = (z.x * z.x) - (z.y * z.y);
		res.y = i * 2 * z.x * z.y;
	}
	else
	{
		res.x = (z.x * z.x) - (z.y * z.y);
		res.y = 2 * z.x * z.y;
	}
	return (res);
}
