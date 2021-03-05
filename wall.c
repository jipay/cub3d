/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:08:37 by jdidier           #+#    #+#             */
/*   Updated: 2021/02/27 23:24:46 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(int x, t_cub3d *cub, t_ray ray, t_data *text)
{
	int		y_off;
	int		x_off;
	int		y_start;
	int		y_end;

	y_start = (cub->stripeh[x] > cub->w_height) ?
	0 : (cub->w_height / 2 - cub->stripeh[x] / 2);
	y_end = (cub->stripeh[x] > cub->w_height) ?
	cub->w_height : y_start + cub->stripeh[x];
	if (ray.hor)
		x_off = (int)ray.inter.x % TILE_SIZE;
	else
		x_off = (int)ray.inter.y % TILE_SIZE;
	x_off = (x_off * text->width) / TILE_SIZE;
	y_off = (cub->stripeh[x] > cub->w_height) ?
	(cub->stripeh[x] / 2 - cub->w_height / 2) : 0;
	while (y_start < y_end)
	{
		my_mlx_pixel_put(&cub->img, x, y_start,
		get_pixel_color(text, x_off, (y_off * text->height) / cub->stripeh[x]));
		y_start++;
		y_off++;
	}
}

t_data	*get_wall_text(t_cub3d *cub, double angle, int type)
{
	if (type)
	{
		if (isfaceup(angle))
			return (&cub->tab[0]);
		else
			return (&cub->tab[1]);
	}
	else
	{
		if (isfaceright(angle))
			return (&cub->tab[3]);
		else
			return (&cub->tab[2]);
	}
}

void	render_wall(t_cub3d *cub, char *img_data)
{
	t_ray	ray;
	int		pix;
	double	angle;

	pix = 0;
	ft_bzero(img_data, cub->w_width * cub->w_height * 4);
	draw_background(cub);
	while (pix < cub->w_width)
	{
		angle = normalize_angle(cub->player.angle +
		atan((pix - (cub->w_width / 2)) / cub->dstprojplane));
		ray = raycast(cub, angle);
		cub->raydst[pix] = ray.dst;
		ray.dst *= cos(angle - cub->player.angle);
		cub->stripeh[pix] = floor((TILE_SIZE / ray.dst) * cub->dstprojplane);
		draw_wall(pix, cub, ray, get_wall_text(cub, angle, ray.hor));
		pix++;
	}
}

int		iswall(char **map, double x, double y)
{
	int grid_x;
	int grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	return (map[grid_y][grid_x] == '1');
}

void	draw_background(t_cub3d *cub)
{
	int		x;
	int		y;

	y = 0;
	while (y < cub->w_height / 2)
	{
		x = 0;
		while (x < cub->w_width)
		{
			my_mlx_pixel_put(&cub->img, x, y, cub->c_color);
			x++;
		}
		y++;
	}
	while (y <= (cub->w_height))
	{
		x = 0;
		while (x < cub->w_width)
		{
			my_mlx_pixel_put(&cub->img, x, y, cub->f_color);
			x++;
		}
		y++;
	}
}
