/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:03 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:04 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*lst_new_env(char *key, char *value)
{
	t_env_list	*new;

	new = ft_calloc(1, sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env_list	*get_last_env(t_env_list *list)
{
	t_env_list	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

void	append_env(t_env_list **list, t_env_list *new)
{
	t_env_list	*last;

	if (!list || !new)
		return ;
	last = get_last_env(*list);
	if (!last)
		*list = new;
	else
		last->next = new;
}

void	del_env(t_env_list *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
	node = NULL;
}

void	del_env_list(t_env_list **list)
{
	if (!list || !(*list))
		return ;
	del_env_list(&(*list)->next);
	del_env(*list);
}
