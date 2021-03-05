/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 00:34:32 by jdidier           #+#    #+#             */
/*   Updated: 2021/02/20 11:47:21 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_fd	*ft_getdatas_fd(int fd, t_fd **origin)
{
	t_fd	*list;
	t_fd	*lastfd;

	list = *origin;
	lastfd = list;
	while (list)
	{
		if (list->fd == fd)
			return (list);
		lastfd = list;
		list = list->next;
	}
	if (!(list = malloc(sizeof(*list))))
		return (NULL);
	list->fd = fd;
	list->next = NULL;
	if (!(list->datas = ft_substr("", 0, 0)))
		return (NULL);
	if (lastfd)
		lastfd->next = list;
	else
		*origin = list;
	return (list);
}

char	*ft_read_fd(t_fd *live)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	while ((live->ret = read(live->fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[live->ret] = '\0';
		tmp = live->datas;
		if (!(live->datas = ft_strjoin(live->datas, buf)))
			return (NULL);
		free(tmp);
		tmp = 0;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (live->ret < 0)
		return (NULL);
	return (live->datas);
}

int		ft_copytoline(t_fd *live, char **line)
{
	char	*tmp;
	size_t	index;

	index = 0;
	tmp = live->datas;
	while (live->datas[index] && live->datas[index] != '\n')
		index++;
	if (!(*line = ft_substr(live->datas, 0, (index))))
		return (0);
	if (!(live->datas = ft_substr(live->datas, (index + 1),
	(ft_strlen(live->datas) - (index + 1)))))
		return (0);
	free(tmp);
	tmp = 0;
	return (1);
}

void	ft_delone_fd(t_fd *live, t_fd **origin)
{
	t_fd	*list;

	list = *origin;
	if (live == *origin)
		*origin = ((*origin)->next) ? ((*origin)->next) : NULL;
	else
		while (list)
		{
			if (list->next == live)
				list->next = live->next;
			list = list->next;
		}
	live->ret = -1;
	live->fd = -1;
	live->next = NULL;
	free(live->datas);
	live->datas = NULL;
	free(live);
	live = NULL;
}

int		get_next_line(int fd, char **line)
{
	static t_fd	*list;
	t_fd		*live;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(live = ft_getdatas_fd(fd, &list)))
		return (-1);
	if (!(ft_strchr(live->datas, '\n')))
		if (!(live->datas = ft_read_fd(live)))
		{
			ft_delone_fd(live, &list);
			return (-1);
		}
	if (!(ft_copytoline(live, line)))
	{
		ft_delone_fd(live, &list);
		return (-1);
	}
	if (live->ret > 0)
		return (1);
	else
	{
		ft_delone_fd(live, &list);
		return (0);
	}
}
