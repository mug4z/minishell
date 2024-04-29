/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:58 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:59 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirected(t_command *command, int mode)
{
	if (mode == STDIN_FILENO && command->input != -1)
		return (1);
	if (mode == STDOUT_FILENO && command->output != -1)
		return (1);
	return (0);
}

int	duplicate_standard_fds(t_command *command)
{
	if (!is_redirected(command, STDIN_FILENO))
	{
		command->stdin_cpy = dup(STDIN_FILENO);
		if (command->stdin_cpy == -1)
			return (minishell_error("duplicate_standard_fds (input)"));
	}
	if (!is_redirected(command, STDOUT_FILENO))
	{
		command->stdout_cpy = dup(STDOUT_FILENO);
		if (command->stdout_cpy == -1)
		{
			if (command->stdin_cpy != -1)
				close(command->stdin_cpy);
			return (minishell_error("duplicate_standard_fds (output)"));
		}
	}
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	t_token_list	*redirect;

	redirect = cmd->redirections;
	while (redirect)
	{
		if (redirect->flags & IS_INPUT)
		{
			if (redirect_input(cmd, redirect))
				return (1);
		}
		else if (redirect->flags & IS_OUTPUT || redirect->flags & IS_APPEND)
		{
			if (redirect_output(cmd, redirect))
				return (1);
		}
		redirect = redirect->next;
	}
	return (0);
}

int	restore_standard_fds(t_command *command)
{
	int	value;

	value = 0;
	if (command->stdin_cpy > -1)
	{
		if (dup2(command->stdin_cpy, STDIN_FILENO) == -1)
			value += minishell_error("restore_standard_fds: dup2 (stdin)");
		if (close(command->stdin_cpy) == -1)
			value += minishell_error("restore_standard_fds: close stdin_cpy");
	}
	if (command->stdout_cpy > -1)
	{
		if (dup2(command->stdout_cpy, STDOUT_FILENO) == -1)
			value += minishell_error("restore_standard_fds: dup2 (stdout)");
		if (close(command->stdout_cpy) == -1)
			value += minishell_error("restore_standard_fds: close stdout_cpy");
	}
	return (value);
}

int	init_command_redirections(t_token_list **list, t_command *cmd)
{
	t_token_list	*current;
	t_token_list	*next;
	t_token_list	*new_token;

	current = *list;
	while (current)
	{
		next = current->next;
		if ((current->flags & IS_REDIRECT) && (next))
		{
			if (!(next->flags & IS_WORD))
				return (1);
			new_token = copy_token(next->content, current->flags);
			if (!new_token)
				return (minishell_error("init_command_redirections"));
			append_token(&cmd->redirections, new_token);
			pop_token(list, current);
			current = next->next;
			pop_token(list, next);
		}
		else
			current = current->next;
	}
	return (0);
}
