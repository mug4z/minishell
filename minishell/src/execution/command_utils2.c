/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:27 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:34:20 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipeline_cmds(t_pipeline *pipeline, t_token_list **tok)
{
	int				i;
	t_command		*new;

	i = 0;
	pipeline->token_lists = ft_calloc(pipeline->command_count + 1, \
										sizeof(t_token_list *));
	if (!pipeline->token_lists)
		return (minishell_error("init_pipeline_commands"));
	while (i < pipeline->command_count)
	{
		pipeline->token_lists[i] = extract_command(tok);
		new = new_command(&pipeline->token_lists[i], &pipeline->env);
		if (!new)
			return (-1);
		append_command(&pipeline->command, new);
		if (i != 0)
			new->input = pipeline->pipe_fd[i - 1].read;
		if (i < pipeline->command_count - 1)
			new->output = pipeline->pipe_fd[i].write;
		i++;
	}
	return (0);
}

void	append_command(t_command **list, t_command *new)
{
	t_command	*last;

	if (!list || !new)
		return ;
	last = get_last_command(*list);
	if (!last)
		*list = new;
	else
		last->next = new;
}

t_command	*get_last_command(t_command *list)
{
	t_command	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

t_token_list	*get_next_command(t_token_list *tokens)
{
	t_token_list	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->flags & IS_PIPE)
			return (current->next);
		current = current->next;
	}
	return (NULL);
}

t_token_list	*extract_command(t_token_list **list)
{
	t_token_list	*start;
	t_token_list	*current;
	t_token_list	*previous;

	start = *list;
	current = *list;
	previous = NULL;
	if (list == NULL || *list == NULL)
		return (NULL);
	while (current != NULL && !(current->flags & IS_PIPE))
	{
		previous = current;
		current = current->next;
	}
	if (current)
	{
		*list = current->next;
		pop_token(&start, current);
		if (previous)
			previous->next = NULL;
	}
	else
		*list = NULL;
	return (start);
}
