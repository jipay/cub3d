/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 22:42:49 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/03 11:48:27 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ismap(char *str)
{
	unsigned int	i;
	char			c;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		c = str[i];
		if (!(c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' ||
		c == 'E' || c == 'W' || c == ' '))
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(char *line, t_cub3d *cub)
{
	int		line_len;

	if (ismap(line))
	{
		if (cub->map.inmap && cub->map.blank)
			send_error(11, cub);
		if (!cub->map.inmap)
			cub->map.inmap = 1;
		line_len = ft_strlen(line);
		if (line_len > cub->map.w)
			cub->map.w = line_len;
		get_player_pos(cub, line);
		cub->map.h += 1;
	}
	else if (cub->map.inmap)
	{
		if (*line)
			send_error(12, cub);
		else if (!cub->map.blank)
			cub->map.blank = 1;
	}
}

void	get_player_pos(t_cub3d *cub, char *s)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if ((s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W'))
		{
			if (!found && !cub->map.player_parsed)
			{
				found = 1;
				parse_player_pos(cub, i, s[i]);
			}
			else
				send_error(13, cub);
		}
		i++;
	}
}

void	parse_player_pos(t_cub3d *cub, int x, int direction)
{
	double	angle;

	if (direction == 'S')
		angle = M_PI_2;
	else if (direction == 'N')
		angle = 1.5 * M_PI;
	else if (direction == 'E')
		angle = M_PI;
	else if (direction == 'W')
		angle = 0;
	cub->player = init_player((x * TILE_SIZE + TILE_SIZE / 2.0),
	(cub->map.h * TILE_SIZE + TILE_SIZE / 2.0), angle);
	cub->map.player_parsed = 1;
}

char	*format_line_to_map(t_cub3d *cub, char *s)
{
	char	*result;
	int		i;

	i = 0;
	if (!(result = malloc(sizeof(char) * (cub->map.w + 1))))
		send_error(10, cub);
	ft_memset(result, ' ', cub->map.w);
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[cub->map.w] = '\0';
	return (result);
}
