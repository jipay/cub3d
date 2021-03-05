/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:25:01 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/02 09:36:04 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_sprite(t_data *text, t_sprite *spt, int x, t_cub3d *cub)
{
	int				y_off;
	int				x_off;
	int				y_start;
	int				y_end;
	unsigned int	color;

	y_start = (spt->h > cub->w_height) ? 0 : (cub->w_height / 2 - spt->h / 2);
	y_end = (spt->h > cub->w_height) ? cub->w_height : y_start + spt->h;
	x_off = x - (spt->wx + (cub->w_width / 2) - (spt->w / 2.0));
	x_off = (x_off * text->height) / spt->w;
	y_off = (spt->h > cub->w_height) ? (spt->h / 2 - cub->w_height / 2) : 0;
	while (y_start < y_end)
	{
		color = get_pixel_color(text, x_off, (y_off * text->height) / spt->h);
		if (color != 4294902015 && color != 16711935)
			my_mlx_pixel_put(&cub->img, x, y_start, color);
		y_start++;
		y_off++;
	}
}

void		render_sprites(t_cub3d *cub)
{
	int		nb;
	int		id;
	int		xstart;
	int		xend;
	double	spriteangle;

	id = -1;
	nb = get_nb_visible_sprites(cub);
	cub->vis = fill_visible(nb, cub);
	while (++id < nb)
	{
		spriteangle = atan2(cub->vis[id].y - cub->player.y,
		cub->vis[id].x - cub->player.x) - cub->player.angle;
		cub->vis[id].wx = tan(spriteangle) * cub->dstprojplane;
		xstart = cub->vis[id].wx + (cub->w_width / 2) - (cub->vis[id].w / 2.0);
		xend = xstart + cub->vis[id].w;
		while (xstart++ <= xend)
		{
			if (xstart >= 0 && xstart < cub->w_width &&
			cub->raydst[xstart] > cub->vis[id].distance)
				draw_sprite(&cub->tab[4], &cub->vis[id], xstart, cub);
		}
	}
	free(cub->vis);
	cub->vis = 0;
}

t_sprite	*init_sprites(t_cub3d *cub)
{
	int			i;
	int			j;
	int			id;
	t_sprite	*sprites;

	j = 0;
	cub->n_sprites = get_nb_sprites(cub);
	if (!(sprites = malloc(sizeof(*sprites) * cub->n_sprites)))
		return (NULL);
	id = 0;
	while (j < cub->map.h)
	{
		i = 0;
		while (i < cub->map.w)
		{
			if (cub->map.g[j][i] == '2')
			{
				sprites[id] = new_sprite(i, j);
				id++;
			}
			i++;
		}
		j++;
	}
	return (sprites);
}

int			get_nb_sprites(t_cub3d *cub)
{
	int			i;
	int			j;
	int			sprites_counter;

	j = 0;
	sprites_counter = 0;
	while (j < cub->map.h)
	{
		i = 0;
		while (i < cub->map.w)
		{
			if (cub->map.g[j][i] == '2')
				sprites_counter++;
			i++;
		}
		j++;
	}
	return (sprites_counter);
}

t_sprite	new_sprite(int x, int y)
{
	t_sprite	sprite;

	sprite.x = x * TILE_SIZE + (TILE_SIZE / 2);
	sprite.y = y * TILE_SIZE + (TILE_SIZE / 2);
	sprite.angle = 0;
	sprite.distance = 0;
	sprite.visible = 0;
	sprite.h = 0;
	sprite.w = 0;
	return (sprite);
}
