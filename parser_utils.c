/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 22:41:42 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/05 20:11:41 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_ext(char *path, char *ext)
{
	size_t	ext_len;

	ext_len = ft_strlen(ext);
	path += (ft_strlen(path) - ext_len);
	if (!(ft_strncmp(path, ext, ext_len)))
		return (1);
	else
		return (0);
}

t_data	new_texture(t_cub3d *cub, char *path)
{
	t_data	t;

	t.img_ptr = mlx_xpm_file_to_image(cub->mlx, path, &t.width, &t.height);
	ft_lstadd_back(&cub->imgs, ft_lstnew(t.img_ptr));
	t.img_data = mlx_get_data_addr(t.img_ptr, &t.bpp, &t.size_line, &t.endian);
	return (t);
}

void	del_split(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = 0;
		i++;
	}
}

int		splitlen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int		isstrdig(char *str)
{
	unsigned	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
