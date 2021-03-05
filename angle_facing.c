/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_facing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:49:10 by jdidier           #+#    #+#             */
/*   Updated: 2021/02/25 14:06:04 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		isfaceup(double angle)
{
	return (angle > 0 && angle < M_PI);
}

int		isfacedown(double angle)
{
	return (!isfaceup(angle));
}

int		isfaceleft(double angle)
{
	return (angle < M_PI_2 || angle > 1.5 * M_PI);
}

int		isfaceright(double angle)
{
	return (!isfaceleft(angle));
}
