/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:24:31 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/02 22:41:01 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			get_nb_visible_sprites(t_cub3d *cub)
{
	int		id;
	int		nb_visible;

	id = 0;
	nb_visible = 0;
	while (id < cub->n_sprites)
	{
		cub->spts[id].angle = cub->player.angle -
		atan2(cub->spts[id].y - cub->player.y, cub->spts[id].x - cub->player.x);
		if (cub->spts[id].angle > M_PI)
			cub->spts[id].angle -= 2.0 * M_PI;
		if (cub->spts[id].angle < -M_PI)
			cub->spts[id].angle += 2.0 * M_PI;
		cub->spts[id].angle *= (cub->spts[id].angle < 0) ? -1 : 1;
		if (cub->spts[id].angle < (deg2rad((FOV / 2.0)) + 0.2))
		{
			cub->spts[id].visible = 1;
			nb_visible++;
		}
		else
			cub->spts[id].visible = 0;
		id++;
	}
	return (nb_visible);
}

t_sprite	*fill_visible(int nb, t_cub3d *cub)
{
	t_sprite	*vis;
	int			id;
	int			v;

	id = 0;
	v = 0;
	if (!(vis = malloc(sizeof(*vis) * nb)))
		return (NULL);
	while (id < cub->n_sprites)
	{
		if (cub->spts[id].visible)
		{
			vis[v] = cub->spts[id];
			vis[v].distance =
			dst2pnts(vis[v].x, vis[v].y, cub->player.x, cub->player.y);
			vis[v].h = (TILE_SIZE / (vis[v].distance * cos(vis[v].angle)))
			* cub->dstprojplane;
			vis[v].w = vis[v].h;
			v++;
		}
		id++;
	}
	sortvisibles(vis, nb);
	return (vis);
}

void		sortvisibles(t_sprite *visibles, int nb)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < (nb - 1))
	{
		j = i + 1;
		while (j < nb)
		{
			if (visibles[i].distance < visibles[j].distance)
			{
				tmp = visibles[i];
				visibles[i] = visibles[j];
				visibles[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int			issprite(char **map, double x, double y)
{
	int grid_x;
	int grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	return (map[grid_y][grid_x] == '2');
}
