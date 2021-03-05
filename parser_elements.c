/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 22:49:36 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/05 16:48:04 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_res(t_cub3d *cub, char **str)
{
	int		width;
	int		height;
	int		w_parsed;
	int		h_parsed;

	if (isstrdig(str[1]) && isstrdig(str[2]))
	{
		mlx_get_screen_size(cub->mlx, &width, &height);
		w_parsed = (ft_atoi(str[1]) > 20000) ? 20000 : ft_atoi(str[1]);
		h_parsed = (ft_atoi(str[2]) > 20000) ? 20000 : ft_atoi(str[2]);
		if (w_parsed <= 0 || h_parsed <= 0)
			send_error(7, cub);
		if (cub->save)
		{
			cub->w_width = w_parsed;
			cub->w_height = h_parsed;
		}
		else
		{
			cub->w_width = (w_parsed > width) ? width : w_parsed;
			cub->w_height = (h_parsed > height) ? height : h_parsed;
		}
	}
	else
		send_error(7, cub);
}

void	parse_path(t_cub3d *cub, char **str)
{
	int	fd;

	fd = open(str[1], O_RDONLY);
	if (fd == -1 || !check_ext(str[1], ".xpm"))
		send_error(8, cub);
	else
	{
		if (!ft_strcmp("NO", str[0]))
		{
			cub->tab[0] = new_texture(cub->mlx, str[1]);
			ft_lstadd_back(&cub->imgs, ft_lstnew(cub->tab[0].img_ptr));
		}
		else if (!ft_strcmp("SO", str[0]))
			cub->tab[1] = new_texture(cub->mlx, str[1]);
		else if (!ft_strcmp("WE", str[0]))
			cub->tab[2] = new_texture(cub->mlx, str[1]);
		else if (!ft_strcmp("EA", str[0]))
			cub->tab[3] = new_texture(cub->mlx, str[1]);
		else if (!ft_strcmp("S", str[0]))
			cub->tab[4] = new_texture(cub->mlx, str[1]);
	}
	close(fd);
}

void	parse_rgb(t_cub3d *cub, char **str)
{
	t_color	color;
	char	**rgb;

	rgb = ft_split(str[1], ',');
	if (splitlen(rgb) == 3)
	{
		if (((color.r = strisrgb(rgb[0])) != -1)
		&& ((color.g = strisrgb(rgb[1])) != -1)
		&& ((color.b = strisrgb(rgb[2])) != -1))
		{
			if (!ft_strcmp(str[0], "F"))
				cub->f_color = create_trgb(0, color.r, color.g, color.b);
			else if (!ft_strcmp(str[0], "C"))
				cub->c_color = create_trgb(0, color.r, color.g, color.b);
			del_split(str);
		}
		else
			send_error(9, cub);
	}
	else
		send_error(9, cub);
	del_split(rgb);
	free(rgb);
	rgb = 0;
}

int		strisrgb(char *str)
{
	int		value;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	value = ft_atoi(str);
	if (value > 255 || value < 0)
		return (-1);
	return (value);
}
