/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:17 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:26:19 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reflag(t_token_list **list, t_token_list *iter, int flags)
{
	iter->flags = flags;
	pop_token(list, iter->next);
}

int	is_flag(int flags, int flag)
{
	if (flags & flag)
		return (1);
	return (0);
}

void	ft_const_redirect(t_token_list **list)
{
	t_token_list	*iter;

	iter = *list;
	while (iter)
	{
		if (is_flag(iter->flags, IS_REDIRECT))
		{
			if (iter->next == NULL)
				return ;
		}
		if (is_flag(iter->flags, IS_INPUT))
		{
			if (is_flag(iter->next->flags, IS_INPUT)
				&& is_flag(iter->next->flags, IS_REDIRECT))
				ft_reflag(list, iter, IS_OPERATOR | IS_INPUT
					| IS_REDIRECT | IS_HEREDOC);
		}
		else if (is_flag(iter->flags, IS_OUTPUT))
		{
			if (is_flag(iter->next->flags, IS_OUTPUT)
				&& is_flag(iter->next->flags, IS_REDIRECT))
				ft_reflag(list, iter, IS_OPERATOR | IS_REDIRECT | IS_APPEND);
		}
		iter = iter->next;
	}
}
