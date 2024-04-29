/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:31 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:32 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_strarray(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
			free(array[i++]);
		free(array);
	}
	return (0);
}

int	is_dir(char *path)
{
	struct stat	stat_buffer;

	if (stat(path, &stat_buffer) == 0)
		return (S_ISDIR(stat_buffer.st_mode));
	else
		perror("is_dir");
	return (0);
}

int	wait_for_children(t_pipeline *pipeline)
{
	int			exit_code;
	int			status;
	t_command	*command;

	exit_code = -1;
	command = pipeline->command;
	while (command)
	{
		waitpid(command->pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else
			exit_code = -1;
		command = command->next;
	}
	return (exit_code);
}
