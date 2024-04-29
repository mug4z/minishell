/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_chk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:57 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:56:49 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the first element of the linked list is a pipe
 *
 * @param list
 * @return int Return -1 if a pipe is found as
 * 		   	   the first element of the linked list
 * 			   Return 0 if not a pipe is found as the first element
 */
int	ft_pipe_check(t_token_list **list)
{
	if (*list == NULL)
		return (-1);
	if (((*list)->flags & IS_PIPE) == IS_PIPE)
		return (minishell_error("syntax error"), -1);
	return (0);
}

int	is_invalid_char(char *content)
{
	if (!ft_strcmp(content, "\\"))
		return (1);
	if (!ft_strcmp(content, ";"))
		return (1);
	if (!ft_strcmp(content, "&"))
		return (1);
	if (!ft_strcmp(content, "*"))
		return (1);
	if (!ft_strcmp(content, "("))
		return (1);
	if (!ft_strcmp(content, ")"))
		return (1);
	return (0);
}

int	ft_meta_quoted_chk(t_token_list **list)
{
	t_token_list	*iter;

	iter = *list;
	while (iter)
	{
		if (is_invalid_char(iter->content))
			return (minishell_error("Invalid characters"), -1);
		iter = iter->next;
	}
	return (0);
}

int	ft_meta_syn_chk(t_token_list **list)
{
	t_token_list	*iter;

	iter = *list;
	while (iter)
	{
		if (is_flag(iter->flags, IS_PIPE) && iter->next == NULL)
			return (minishell_error("line not complete"), -1);
		if (is_flag(iter->flags, IS_REDIRECT))
		{
			if (iter->next == NULL || !is_flag(iter->next->flags, IS_WORD))
				return (minishell_error("syntax error"), -1);
		}
		if (is_flag(iter->flags, IS_OPERATOR))
		{
			if (is_flag(iter->next->flags, IS_REDIRECT))
				;
			else if (!is_flag(iter->next->flags, IS_WORD))
				return (minishell_error("syntax error"), -1);
		}
		iter = iter->next;
	}
	return (0);
}

int	ft_syntax_chk(t_token_list **list)
{
	if (*list == NULL)
		return (-1);
	if (ft_pipe_check(list) == -1 || ft_meta_quoted_chk(list) == -1
		|| ft_meta_syn_chk(list))
		return (-1);
	else
		return (0);
}
