/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:19:32 by bgolding          #+#    #+#             */
/*   Updated: 2024/03/14 14:09:07 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Adds the node 'new' at the end of the list.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

/*

	
	> lst -> 1
	
		1	> content
			> next

	last = 1
	1	> next = new

*/