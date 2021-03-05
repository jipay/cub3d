/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:12:33 by jdidier           #+#    #+#             */
/*   Updated: 2021/02/27 21:49:08 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_mov(t_cub3d *cub)
{
	update_walk(cub);
	update_straf(cub);
}

void	update_walk(t_cub3d *cub)
{
	double nwalkx;
	double nwalky;

	nwalkx = cub->player.x + (cub->player.walk * cub->player.spd)
	* cos(cub->player.angle);
	nwalky = cub->player.y + (cub->player.walk * cub->player.spd)
	* sin(cub->player.angle);
	if (!(iswall(cub->map.g, nwalkx, cub->player.y)) &&
	!(issprite(cub->map.g, nwalkx, cub->player.y)))
		cub->player.x += (cub->player.walk * cub->player.spd)
		* cos(cub->player.angle);
	if (!(iswall(cub->map.g, cub->player.x, nwalky)) &&
	!(issprite(cub->map.g, cub->player.x, nwalky)))
		cub->player.y += (cub->player.walk * cub->player.spd)
		* sin(cub->player.angle);
}

void	update_straf(t_cub3d *cub)
{
	double nstrafx;
	double nstrafy;

	nstrafx = cub->player.x + (cub->player.straf * cub->player.spd)
	* cos(cub->player.angle + 90 * M_PI / 180);
	nstrafy = cub->player.y + (cub->player.straf * cub->player.spd)
	* sin(cub->player.angle + 90 * M_PI / 180);
	if (!(iswall(cub->map.g, nstrafx, cub->player.y)) &&
	!(issprite(cub->map.g, nstrafx, cub->player.y)))
		cub->player.x += (cub->player.straf * cub->player.spd)
		* cos(cub->player.angle + 90 * M_PI / 180);
	if (!(iswall(cub->map.g, cub->player.x, nstrafy)) &&
	!(issprite(cub->map.g, cub->player.x, nstrafy)))
		cub->player.y += (cub->player.straf * cub->player.spd)
		* sin(cub->player.angle + 90 * M_PI / 180);
}

int		key_press(int key, t_cub3d *cub)
{
	if (key == 119)
		cub->player.walk = 1;
	else if (key == 115)
		cub->player.walk = -1;
	if (key == 97)
		cub->player.straf = -1;
	else if (key == 100)
		cub->player.straf = 1;
	if (key == 65363)
		cub->player.turn = 1;
	else if (key == 65361)
		cub->player.turn = -1;
	if (key == 0xFF1B)
		ft_exit(cub);
	return (0);
}

int		key_release(int key, t_cub3d *cub)
{
	if (key == 119)
		cub->player.walk = 0;
	else if (key == 115)
		cub->player.walk = 0;
	if (key == 97)
		cub->player.straf = 0;
	else if (key == 100)
		cub->player.straf = 0;
	if (key == 65363)
		cub->player.turn = 0;
	else if (key == 65361)
		cub->player.turn = 0;
	return (0);
}
