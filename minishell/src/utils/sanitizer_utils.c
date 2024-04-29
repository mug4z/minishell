/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:26 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:26:28 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rmv_null(t_token_list **list)
{
	t_token_list	*iter;
	t_token_list	*next;

	iter = *list;
	next = *list;
	while (iter)
	{
		if (ft_strcmp(iter->content, "\0") == 0)
		{
			next = iter->next;
			pop_token(list, iter);
			iter = next;
		}
		else
			iter = iter->next;
	}
}
