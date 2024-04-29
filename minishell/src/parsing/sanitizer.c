/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:49 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:24:50 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rmv_space(t_token_list **list)
{
	t_token_list	*iter;
	t_token_list	*next;

	iter = *list;
	next = *list;
	while (iter)
	{
		if (ft_strcmp(iter->content, "\0") == 0
			|| ft_strcmp(iter->content, " ") == 0
			|| ft_strcmp(iter->content, "\t") == 0)
		{
			next = iter->next;
			pop_token(list, iter);
			iter = next;
		}
		else
			iter = iter->next;
	}
}

/**
 * @brief Remove the quote specified by the quote arguments.
 * 
 * @param line 
 * @param quote 
 */
void	ft_rmv_quote_pair(char *line, char quote)
{
	char	*y;
	int		flag;

	y = NULL;
	flag = 0;
	while (*line)
	{
		y = line;
		if (*line == quote && flag <= 1)
		{
			flag++;
			while (*y)
			{
				*y = *(y + 1);
				y++;
			}
		}
		else if (flag > 1)
		{
			ft_chk_characters(line, "\'\"", &quote);
			flag = 0;
		}
		else
			line++;
	}
}

/**
 * @brief Iter the through the t_token_list to find " or '.
 * 
 * @param list 
 */
static void	ft_rmv_quotes(t_token_list **list)
{
	t_token_list	*iter;
	char			quote;

	iter = *list;
	quote = 0;
	while (iter)
	{
		if (ft_chk_characters(iter->content, "\'\"", &quote) == 1)
			ft_rmv_quote_pair(iter->content, quote);
		iter = iter->next;
	}
}

void	ft_sanitizer(t_token_list **list)
{
	ft_rmv_space(list);
	ft_rmv_quotes(list);
}
