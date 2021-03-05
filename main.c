/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 11:27:24 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/04 15:37:03 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub3d *cub)
{
	int		i;

	i = 0;
	cub->save = 0;
	cub->mlx = mlx_init();
	cub->win = NULL;
	cub->raydst = NULL;
	cub->spts = NULL;
	cub->stripeh = NULL;
	cub->map.g = NULL;
	while (i < 5)
		cub->tab[i++].img_ptr = NULL;
	cub->img.img_ptr = NULL;
}

void	setup(t_cub3d *cub)
{
	cub->spts = init_sprites(cub);
	cub->raydst = malloc(sizeof(double) * cub->w_width);
	cub->stripeh = malloc(sizeof(int) * cub->w_width);
	cub->dstprojplane = (cub->w_width / 2) / tan(deg2rad(FOV / 2));
	cub->img.img_ptr = mlx_new_image(cub->mlx, cub->w_width, cub->w_height);
	cub->img.img_data = mlx_get_data_addr(cub->img.img_ptr, &cub->img.bpp,
	&cub->img.size_line, &cub->img.endian);
}

int		gameloop(t_cub3d *cub)
{
	cub->player.angle += cub->player.turn * cub->player.rotspd;
	cub->player.angle = normalize_angle(cub->player.angle);
	update_mov(cub);
	render_wall(cub, cub->img.img_data);
	render_sprites(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);
	return (1);
}

void	init_map(t_cub3d *cub, char *path)
{
	int		fd;
	int		i;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	if (!(cub->map.g = malloc(sizeof(char*) * cub->map.h)))
		send_error(10, cub);
	if ((fd = open(path, O_RDONLY)) < 0)
		send_error(2, cub);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ismap(line))
			cub->map.g[i++] = format_line_to_map(cub, line);
		free(line);
		line = 0;
	}
	cub->map.g[(int)floor(cub->player.y / TILE_SIZE)]
	[(int)floor(cub->player.x / TILE_SIZE)] = '0';
	close(fd);
}

int		main(int argc, char **argv)
{
	t_cub3d	cub;

	init(&cub);
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (!ft_strcmp(argv[2], "--save"))
				cub.save = 1;
			else
				send_error(3, &cub);
		}
		init_parse(&cub, argv[1]);
		init_map(&cub, argv[1]);
		check_map(&cub);
		setup(&cub);
		render_wall(&cub, cub.img.img_data);
		render_sprites(&cub);
		if (cub.save)
			save(&cub, &cub.img);
		init_event(&cub);
	}
	else
		send_error(0, &cub);
	return (0);
}
