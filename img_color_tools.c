/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_color_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 07:43:35 by jdidier           #+#    #+#             */
/*   Updated: 2021/02/25 14:06:31 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	get_pixel_color(t_data *text, int x, int y)
{
	char *dst;

	dst = text->img_data + (x * (text->bpp / 8) + y * text->size_line);
	return ((*(unsigned int*)dst));
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
