/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:37:38 by viburton          #+#    #+#             */
/*   Updated: 2022/10/06 15:16:09 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*next;

	if (lst && *lst && del)
	{
		new = *lst;
		while (new)
		{
			next = new->next;
			ft_lstdelone(new, del);
			new = next;
		}
		*lst = NULL;
	}
}
