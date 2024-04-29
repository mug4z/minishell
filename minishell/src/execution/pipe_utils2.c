/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:47 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 14:21:01 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Closes the file descriptors present in the provided t_pipe_fd struct.
	Will not attempt to close if the fd is less than 0 (not a valid fd). */
void	close_pipe(t_pipe_fd *pipe_fd)
{
	if (pipe_fd->read > -1)
	{
		if (close(pipe_fd->read) == -1)
			minishell_error("close pipe read");
		else
			pipe_fd->read = -1;
	}
	if (pipe_fd->write > -1)
	{
		if (close(pipe_fd->write) == -1)
			minishell_error("close pipe write");
		else
			pipe_fd->write = -1;
	}
}

/*	Closes pipe file descriptors still present in the pipeline. */
void	close_all_pipes(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->pipe_count)
		close_pipe(&pipeline->pipe_fd[i++]);
}

/*	Closes all pipes in the pipeline as well as freeing the memory allocated
	for the array of t_pipe_fd structs. */
void	destroy_pipes(t_pipeline *pipeline)
{
	if (pipeline->pipe_fd)
	{
		close_all_pipes(pipeline);
		free(pipeline->pipe_fd);
		pipeline->pipe_fd = NULL;
	}
}

/*	Closes all file descriptors associated with the given pipeline besides those
	provided as 'read_fd' and 'write_fd'. This enables a child process to close 
	all file descriptors it does not need access to. */
void	close_unused_pipes(t_pipeline *p, int read_fd, int write_fd)
{
	int	i;

	if (read_fd < 0 && write_fd < 0)
		close_all_pipes(p);
	i = 0;
	while (i < p->pipe_count)
	{
		if (p->pipe_fd[i].read != read_fd)
		{
			if (close(p->pipe_fd[i].read) == -1)
				perror("close pipe read");
			else
				p->pipe_fd[i].read = -1;
		}
		if (p->pipe_fd[i].write != write_fd)
		{
			if (close(p->pipe_fd[i].write) == -1)
				perror("close pipe write");
			else
				p->pipe_fd[i].write = -1;
		}
		i++;
	}
}

void	destroy_pipeline(t_pipeline *pipeline)
{
	t_command	*next;
	int			i;

	if (!pipeline)
		return ;
	destroy_pipes(pipeline);
	if (pipeline->command)
	{
		next = pipeline->command->next;
		while (pipeline->command)
		{
			destroy_command(pipeline->command);
			pipeline->command = next;
			if (next)
				next = next->next;
		}
	}
	if (pipeline->token_lists)
	{
		i = 0;
		while (pipeline->token_lists[i])
			del_token_list(&pipeline->token_lists[i++], free);
		free(pipeline->token_lists);
	}
}
