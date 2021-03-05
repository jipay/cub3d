/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 10:35:38 by jdidier           #+#    #+#             */
/*   Updated: 2020/05/12 17:50:13 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordscounter(char const *s, char c)
{
	int flag;
	int result;

	flag = 0;
	result = 0;
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			result++;
		}
		if (*s == c)
			flag = 0;
		s++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	start;
	unsigned int	index;
	unsigned int	i;

	start = 0;
	index = 0;
	i = 0;
	if (!(result = malloc(sizeof(char*) * (ft_wordscounter(s, c) + 1))))
		return (NULL);
	while (s[index])
	{
		if (index > 0 && s[index] != c && s[index - 1] == c)
			start = index;
		if (index > 0 && s[index] == c && s[index - 1] != c)
			result[i++] = ft_substr(s, start, (index - start));
		index++;
	}
	if (index > 0 && s[index - 1] != c)
		result[i++] = ft_substr(s, start, (index - start));
	result[i] = NULL;
	return (result);
}
