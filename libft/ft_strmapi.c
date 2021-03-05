/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:37:24 by jdidier           #+#    #+#             */
/*   Updated: 2020/05/12 17:51:15 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	i = 0;
	if (!(result = malloc(sizeof(*result) * (ft_strlen(s) + 1))))
		return (NULL);
	while (*s)
	{
		result[i] = f(i, *s);
		s++;
		i++;
	}
	result[i] = '\0';
	return (result);
}
