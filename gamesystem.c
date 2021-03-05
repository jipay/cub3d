/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamesystem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:42:58 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/04 15:52:04 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_event(t_cub3d *cub)
{
	cub->win = mlx_new_window(cub->mlx, cub->w_width, cub->w_height, "cub3D");
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);
	mlx_hook(cub->win, 33, 1L << 17, &ft_exit, cub);
	mlx_hook(cub->win, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, &key_release, cub);
	mlx_loop_hook(cub->mlx, &gameloop, cub);
	mlx_loop(cub->mlx);
}

void		init_parse(t_cub3d *cub, char *file)
{
	int fd;

	if (check_ext(file, ".cub") && ft_strlen(file) > 4)
		if ((fd = open(file, O_RDONLY | __O_NOFOLLOW)) < 0)
			send_error(1, cub);
		else
			parse(fd, cub);
	else
		send_error(1, cub);
}

t_player	init_player(double x, double y, double angle)
{
	t_player	player;

	player.x = x;
	player.y = y;
	player.walk = 0;
	player.turn = 0;
	player.straf = 0;
	player.rotspd = 0.8 * (M_PI / 180.0);
	player.angle = angle;
	player.spd = 0.5;
	return (player);
}

int			is_directory(int fd)
{
	return (read(fd, NULL, 0));
}
