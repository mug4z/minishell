/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:51 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:26:53 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*lst_new_token(char *content, int flags)
{
	t_token_list	*new;

	new = malloc(sizeof(t_token_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->flags = flags;
	new->next = NULL;
	return (new);
}

void	add_token(t_token_list **list, t_token_list *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}

t_token_list	*get_last_token(t_token_list *list)
{
	t_token_list	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

void	append_token(t_token_list **list, t_token_list *new_token)
{
	t_token_list	*last;

	if (!list || !new_token)
		return ;
	last = get_last_token(*list);
	if (!last)
		*list = new_token;
	else
		last->next = new_token;
}

void	token_lst_iter(t_token_list *list, void (*f)(char *))
{
	if (!list || !f)
		return ;
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}
