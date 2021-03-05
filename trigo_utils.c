/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:42:10 by jdidier           #+#    #+#             */
/*   Updated: 2021/02/24 15:47:17 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

float	deg2rad(float angle)
{
	return (((M_PI * angle) / 180));
}

double	dst2pnts(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}
