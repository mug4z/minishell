/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:42 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 14:24:25 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Initializes the correct amount of pipelines based on the tokens provided.
	Assumes at least one pipe is present. */
int	init_pipeline(t_pipeline *pipeline, t_token_list **tokens, t_env_list **env)
{
	pipeline->env = *env;
	pipeline->pipe_count = count_pipes(*tokens);
	if (init_pipes(pipeline))
		return (minishell_error("init_pipes"));
	pipeline->command_count = pipeline->pipe_count + 1;
	if (init_pipeline_cmds(pipeline, tokens))
		return (minishell_error("init_pipeline_commands"));
	return (0);
}

/*	Counts the number of pipe tokens found in the provided token list. */
int	count_pipes(t_token_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->flags & IS_PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

/*	Initializes the array of pipe_fd structures to store all the file
	descriptors in a more convenient way. */
int	init_pipes(t_pipeline *pipeline)
{
	int	i;

	pipeline->pipe_fd = ft_calloc(pipeline->pipe_count, sizeof(t_pipe_fd));
	if (!pipeline->pipe_fd)
		return (-1);
	i = 0;
	while (i < pipeline->pipe_count)
	{
		pipeline->pipe_fd[i].read = -1;
		pipeline->pipe_fd[i].write = -1;
		i++;
	}
	i = 0;
	while (i < pipeline->pipe_count)
	{
		if (create_pipe(&pipeline->pipe_fd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

/*	Creates a new pipe and stores the relevant file descriptors in the
	t_pipe_fd structure provided. */
int	create_pipe(t_pipe_fd *pipe_fd)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	pipe_fd->read = fd[0];
	pipe_fd->write = fd[1];
	return (0);
}

int	apply_pipe_redirects(t_pipeline *pipeline, t_command *command)
{
	if (command->input >= 0 && dup2(command->input, STDIN_FILENO) == -1)
	{
		minishell_error("dup2 (input)");
		close_all_pipes(pipeline);
		return (-1);
	}
	if (command->output >= 0 && dup2(command->output, STDOUT_FILENO) == -1)
	{
		minishell_error("dup2 (output)");
		close_all_pipes(pipeline);
		return (-1);
	}
	close_all_pipes(pipeline);
	return (0);
}
