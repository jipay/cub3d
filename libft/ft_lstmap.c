/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:15:36 by jdidier           #+#    #+#             */
/*   Updated: 2020/05/12 21:28:58 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	const t_list	*lstp;
	void			*is_success;
	t_list			*ret;
	t_list			*new;

	lstp = lst;
	ret = NULL;
	new = NULL;
	while (lstp)
	{
		if ((is_success = f(lstp->content)))
		{
			if (!(new = ft_lstnew(is_success)))
			{
				ft_lstclear(&lst, del);
				return (NULL);
			}
			ft_lstadd_back(&ret, new);
		}
		lstp = lstp->next;
	}
	return (ret);
}
