/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:34 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:36 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command_line(t_minishell *ms)
{
	t_pipeline	pipeline;
	t_command	*command;
	int			exit_code;

	if (!ms->tokens || !ms->env)
		return (minishell_error("Could not execute command line"));
	if (count_pipes(ms->tokens) > 0)
	{
		ft_bzero(&pipeline, sizeof(pipeline));
		if (init_pipeline(&pipeline, &ms->tokens, &ms->env))
			exit_code = -1;
		else
			exit_code = execute_pipeline(&pipeline);
		destroy_pipeline(&pipeline);
	}
	else
	{
		command = new_command(&ms->tokens, &ms->env);
		if (!command)
			exit_code = -1;
		else
			exit_code = execute_command(command);
		destroy_command(command);
	}
	return (exit_code);
}

int	execute_pipeline(t_pipeline *pipeline)
{
	int				exit_code;
	t_command		*command;

	exit_code = 0;
	command = pipeline->command;
	while (command)
	{
		command->pid = fork();
		if (command->pid < 0)
			return (minishell_error("fork failed"));
		if (command->pid == 0)
		{
			if (apply_pipe_redirects(pipeline, command) != 0)
				exit(EXIT_FAILURE);
			exit(execute_command(command));
		}
		command = command->next;
	}
	close_all_pipes(pipeline);
	exit_code = wait_for_children(pipeline);
	return (exit_code);
}

int	execute_command(t_command *command)
{
	int	exit_code;

	if (command->redirections)
		if (duplicate_standard_fds(command) || apply_redirections(command))
			return (restore_standard_fds(command) + 1);
	if (command->argv)
	{
		if (command->builtin)
			exit_code = execute_builtin(command);
		else if (!command->path)
			exit_code = command_not_found(command->name);
		else
			exit_code = execute_system_command(command);
	}
	else
		exit_code = 0;
	if (command->redirections && restore_standard_fds(command))
		return (EXIT_FAILURE);
	return (exit_code);
}

int	execute_system_command(t_command *command)
{
	pid_t		pid;
	int			exit_status;

	exit_status = -1;
	pid = fork();
	if (pid < 0)
		return (minishell_error("fork failed"));
	if (pid == 0)
	{
		execute_child_system_command(command);
		handle_execution_failure(command->argv[0]);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = (WEXITSTATUS(exit_status));
		else
			exit_status = -1;
	}
	return (exit_status);
}

int	execute_child_system_command(t_command *command)
{
	char	**ms_envp;

	ms_envp = convert_envp(*command->env);
	if (!ms_envp)
		return (1);
	execve(command->path, command->argv, ms_envp);
	ft_free_strarray(ms_envp);
	return (2);
}
