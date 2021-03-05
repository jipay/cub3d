/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:49:43 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/04 15:38:28 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_token	g_tok_tab[] =
{
	{sizeof(RESOLUTION), 3, 0, RESOLUTION, &parse_res},
	{sizeof(NORTH_TEXTURE), 2, 0, NORTH_TEXTURE, &parse_path},
	{sizeof(SOUTH_TEXTURE), 2, 0, SOUTH_TEXTURE, &parse_path},
	{sizeof(WEST_TEXTURE), 2, 0, WEST_TEXTURE, &parse_path},
	{sizeof(EAST_TEXTURE), 2, 0, EAST_TEXTURE, &parse_path},
	{sizeof(SPRITE_TEXTURE), 2, 0, SPRITE_TEXTURE, &parse_path},
	{sizeof(FLOOR_COLOR), 2, 0, FLOOR_COLOR, &parse_rgb},
	{sizeof(CEILING_COLOR), 2, 0, CEILING_COLOR, &parse_rgb}
};

void	parse(int fd, t_cub3d *cub)
{
	int		ret;
	char	*line;

	cub->map.w = 0;
	cub->map.h = 0;
	cub->map.inmap = 0;
	cub->map.blank = 0;
	cub->map.player_parsed = 0;
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			send_error(1, cub);
		if (!isallparsed())
			parse_line(line, cub);
		else
			parse_map(line, cub);
		free(line);
		line = 0;
	}
}

int		iselement(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (-1);
	while (i < 8)
	{
		if (!ft_strcmp(g_tok_tab[i].elem, str))
			return (i);
		i++;
	}
	return (-1);
}

int		isallparsed(void)
{
	unsigned int	i;

	i = 0;
	while (i < 8)
	{
		if (!g_tok_tab[i].parsed)
			return (0);
		i++;
	}
	return (1);
}

void	parse_line(char *line, t_cub3d *cub)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if ((i = iselement(split[0])) != -1)
	{
		if (splitlen(split) == g_tok_tab[i].num)
		{
			if (!g_tok_tab[i].parsed)
				g_tok_tab[i].parsed = 1;
			else
				send_error(6, cub);
			g_tok_tab[i].func(cub, split);
		}
		else
			send_error(5, cub);
	}
	else if (split[0])
		send_error(4, cub);
	if (split != NULL)
	{
		del_split(split);
		free(split);
		split = 0;
	}
}
