/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:27:45 by jdidier           #+#    #+#             */
/*   Updated: 2020/11/19 11:23:17 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
	c == '\r')
		return (1);
	else
		return (0);
}

double	ft_atof(const char *str)
{
	double d1;
	double d2;
	int minus;

	minus = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		d1 = d1 * 10 + (*str - 48);
		str++;
	}
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		d2 = d2 *10 + (*str - 48);
		str++;
	}
	while (d2 > 1.0)
		d2 = d2 / 10;
	return ((d1 + d2) * minus);
}