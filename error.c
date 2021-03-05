/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:23:52 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/05 16:55:16 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_error	g_error_tab[] =
{
	{0, "Invalid Program's argument number : expect 1 or 2"},
	{1, "Invalid File, check path and should be .cub extension"},
	{2, "Map file open failed. Check path and .cub extension"},
	{3, "Invalid second argument, '--save' expected"},
	{4, "Invalid element in file, expect R NO SO WE EA S F C"},
	{5, "Invalid Element argument number expected"},
	{6, "Duplicated element detected in file. Make a choice!"},
	{7, "Resolution arguments should be a digit character, superior to 0"},
	{8, "Failed to open texture file, should be .xpm extension"},
	{9, "RGB format should be 3 digits in 0 ~ 255 ransge separated by ','"},
	{10, "Malloc error from the hell !!"},
	{11, "Empty line inserted in file's map part"},
	{12, "Line map format error, char expected : 0 1 2 N S E W"},
	{13, "Duplicate player's starting point detected, make a choice"},
	{14, "Map space where player starts is not closed! Check the wall."}
};

void	send_error(int id, t_cub3d *cub)
{
	ft_putstr_fd("ERROR\n", 1);
	ft_putstr_fd(g_error_tab[id].msg, 1);
	ft_exit(cub);
}

void	free_images(t_cub3d *cub)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (cub->tab[i].img_ptr)
			mlx_destroy_image(cub->mlx, cub->tab[i].img_ptr);
		i++;
	}
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
}

void	free_struct(t_cub3d *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->raydst)
		free(cub->raydst);
	if (cub->stripeh)
		free(cub->stripeh);
	if (cub->spts)
		free(cub->spts);
}

int		ft_exit(t_cub3d *cub)
{
	int		i;

	i = 0;
	if (cub->map.g)
	{
		i = 0;
		while (i < cub->map.h)
		{
			if (cub->map.g[i])
				free(cub->map.g[i]);
			i++;
		}
		free(cub->map.g);
	}
	free_struct(cub);
	free_images(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
	return (0);
}
