/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:18:41 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/02 22:50:59 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	horizontal_inter(t_cub3d *cub, double angle)
{
	t_point	p;
	double	xstep;
	double	ystep;

	p.y = floor(cub->player.y / TILE_SIZE) * TILE_SIZE;
	p.y += TILE_SIZE * (isfaceup(angle));
	p.x = cub->player.x + ((p.y - cub->player.y) / tan(angle));
	ystep = TILE_SIZE;
	ystep *= (isfaceup(angle)) ? 1 : -1;
	xstep = TILE_SIZE / (tan(angle));
	xstep *= (isfaceright(angle) && xstep > 0) ? -1 : 1;
	xstep *= (isfaceleft(angle) && xstep < 0) ? -1 : 1;
	while (p.x >= 0.0 && p.x < (cub->map.w * TILE_SIZE) && p.y >= 0.0 &&
	p.y < (cub->map.h * TILE_SIZE))
	{
		if (iswall(cub->map.g, p.x, (p.y -= isfacedown(angle) * 0.001)))
			break ;
		p.x += xstep;
		p.y += ystep;
	}
	return (p);
}

t_point	vertical_inter(t_cub3d *cub, double angle)
{
	t_point	p;
	double	xstep;
	double	ystep;

	p.x = floor(cub->player.x / TILE_SIZE) * TILE_SIZE;
	p.x += TILE_SIZE * (isfaceleft(angle));
	p.y = cub->player.y + ((p.x - cub->player.x) * tan(angle));
	xstep = TILE_SIZE;
	xstep *= (isfaceleft(angle)) ? 1 : -1;
	ystep = TILE_SIZE * tan(angle);
	ystep *= ((isfacedown(angle)) && ystep > 0) ? -1 : 1;
	ystep *= ((isfaceup(angle)) && ystep < 0) ? -1 : 1;
	while (p.x >= 0.0 && p.x < (cub->map.w * TILE_SIZE) && p.y >= 0.0 &&
	p.y < (cub->map.h * TILE_SIZE))
	{
		if (iswall(cub->map.g, (p.x -= isfaceright(angle) * 0.001), p.y))
			break ;
		p.x += xstep;
		p.y += ystep;
	}
	return (p);
}

t_ray	raycast(t_cub3d *cub, double angle)
{
	t_point		hor_inter;
	t_point		ver_inter;
	double		hor_dist;
	double		ver_dist;

	hor_inter = horizontal_inter(cub, angle);
	ver_inter = vertical_inter(cub, angle);
	hor_dist = dst2pnts(cub->player.x, cub->player.y, hor_inter.x, hor_inter.y);
	ver_dist = dst2pnts(cub->player.x, cub->player.y, ver_inter.x, ver_inter.y);
	if (hor_dist < ver_dist)
		return (new_ray(hor_inter, hor_dist, 1));
	else
		return (new_ray(ver_inter, ver_dist, 0));
}

t_ray	new_ray(t_point inter, double dst, int type)
{
	t_ray	ray;

	ray.inter = inter;
	ray.dst = dst;
	ray.hor = type;
	return (ray);
}
