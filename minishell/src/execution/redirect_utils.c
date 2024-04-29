/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:50 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:51 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirect(t_token_list *redirect)
{
	int	open_flags;

	open_flags = 0;
	if (redirect->flags & IS_INPUT)
		open_flags |= O_RDONLY;
	else
	{
		open_flags |= O_CREAT | O_WRONLY;
		if (redirect->flags & IS_OUTPUT)
			open_flags |= O_TRUNC;
		else if (redirect->flags & IS_APPEND)
			open_flags |= O_APPEND;
	}
	return (open(redirect->content, open_flags, 0600));
}

int	redirect_input(t_command *command, t_token_list *redirect)
{
	command->input = open_redirect(redirect);
	if (command->input == -1)
		return (minishell_error(redirect->content));
	if (redirect->flags & IS_HEREDOC && unlink(redirect->content))
		minishell_error(redirect->content);
	if (dup2(command->input, STDIN_FILENO) == -1)
		return (minishell_error(redirect->content));
	if (close(command->input) == -1)
		return (minishell_error(redirect->content));
	return (0);
}

int	redirect_output(t_command *command, t_token_list *redirect)
{
	command->output = open_redirect(redirect);
	if (command->output == -1)
		return (minishell_error(redirect->content));
	if (dup2(command->output, STDOUT_FILENO) == -1)
		return (minishell_error(redirect->content));
	if (close(command->output) == -1)
		return (minishell_error(redirect->content));
	return (0);
}
