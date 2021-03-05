/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:49:32 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/02 21:36:43 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	header(t_cub3d *cub, t_data *img, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * cub->w_width * cub->w_height;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &cub->w_width, 4);
	write(fd, &cub->w_height, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &img->bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	save(t_cub3d *cub, t_data *img)
{
	int		fd;
	int		x;
	int		y;
	int		color;

	y = cub->w_height;
	fd = open("./save.bmp", O_CREAT | O_RDWR);
	header(cub, img, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < cub->w_width)
		{
			color = get_pixel_color(img, x, y);
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
	system("chmod 777 save.bmp");
	ft_exit(cub);
}
