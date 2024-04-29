/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:59 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:27:00 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	del_token(t_token_list *token, void (*del)(void *))
{
	if (!token || !del)
		return ;
	if (token->content)
		del(token->content);
	free(token);
	token = NULL;
}

void	pop_token(t_token_list **list, t_token_list *token)
{
	t_token_list	*prev;
	t_token_list	*current;

	prev = NULL;
	if (list == NULL || *list == NULL || token == NULL)
		return ;
	current = *list;
	while (current && current != token)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (prev == NULL)
		*list = current->next;
	else
		prev->next = current->next;
	del_token(current, free);
}

int	token_list_size(t_token_list *list)
{
	int	n;

	n = 0;
	while (list)
	{
		list = list->next;
		n++;
	}
	return (n);
}

void	del_token_list(t_token_list **list, void (*del)(void *))
{
	if (!list || !del || !(*list))
		return ;
	del_token_list(&(*list)->next, del);
	del_token(*list, del);
	*list = NULL;
}

t_token_list	*copy_token(char *content, int flags)
{
	t_token_list	*new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->flags = flags;
	new_token->next = NULL;
	return (new_token);
}
