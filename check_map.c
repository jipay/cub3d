/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:49:06 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/04 15:50:34 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_cell(int x, int y, t_cub3d *cub)
{
	return (cub->map.g[y][x]);
}

void	test_cells(int x, int y, t_cub3d *cub, int (*map)[cub->map.w])
{
	int		c;

	c = get_cell(x, y, cub);
	map[y][x] = 1;
	if (c == ' ' || ((c == '0' || c == '2') && !(x > 0 && x < (cub->map.w - 1)
	&& y > 0 && y < (cub->map.h - 1))))
		send_error(14, cub);
	else if (c == '0' || c == '2')
	{
		if ((x + 1) < cub->map.w && map[y][x + 1] == 0)
			test_cells((x + 1), y, cub, map);
		if ((x - 1) >= 0 && map[y][x - 1] == 0)
			test_cells((x - 1), y, cub, map);
		if ((y + 1) < cub->map.h && map[y + 1][x] == 0)
			test_cells(x, (y + 1), cub, map);
		if ((y - 1) >= 0 && map[y - 1][x] == 0)
			test_cells(x, (y - 1), cub, map);
	}
}

void	check_map(t_cub3d *cub)
{
	int		i;
	int		j;
	int		map[cub->map.h][cub->map.w];

	j = 0;
	while (j < cub->map.h)
	{
		i = 0;
		while (i < cub->map.w)
		{
			map[j][i] = 0;
			i++;
		}
		j++;
	}
	test_cells((int)floor(cub->player.x / TILE_SIZE),
	(int)floor(cub->player.y / TILE_SIZE), cub, map);
}
