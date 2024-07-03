/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:10:18 by abamksa           #+#    #+#             */
/*   Updated: 2024/07/03 20:28:23 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*ft_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

void	error_message(void)
{
	write(1, "Invalid arguments\nUsage:./fractol \
		{mandelbrot | burningship | tricorn | julia [%d] [%d]}\n", 90);
	exit(1);
}

double	ft_clean(const char *nptr, long res)
{
	int		i;
	double	fract;
	double	power;

	i = 0;
	fract = 0;
	power = 1;
	while ((*nptr == '.' || (*nptr >= '0' && *nptr <= '9')) && !i)
	{
		if (*nptr == '.' && !i++ && res)
		{
			++nptr;
			break;
		}
		res = res * 10 + (*nptr - 48);
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		power /= 10;
		fract = fract + (*nptr - 48) * power;
		++nptr;
	}
	if ((*nptr > 31 && *nptr < 127))
		error_message();
	return (res + fract);
}

double	ft_check(const char *nptr)
{
	double	res;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' '))
	{
		++nptr;
		if (*nptr == '\0')
			error_message();
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		++nptr;
		if (!*nptr)
			error_message();
	}
	res = ft_clean(nptr, res);
	return (res * sign);
}

void	check_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!av[i])
			error_message();
		ft_check(av[i]);
		i++;
	}
}
