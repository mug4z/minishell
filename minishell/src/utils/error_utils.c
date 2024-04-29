/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:34 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:36 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		if (errno)
			perror(str);
		else
			ft_putendl_fd(str, STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

void	abort_minishell(t_minishell *ms, int exit_code)
{
	if (ms->env)
		del_env_list(&ms->env);
	if (ms->tokens)
		del_token_list(&ms->tokens, free);
	if (exit_code == EXIT_SUCCESS)
		ft_putendl_fd("exit", STDOUT_FILENO);
	else
		ft_putendl_fd("Could not initialize minishell: \
						aborting minishell", STDERR_FILENO);
	exit(exit_code);
}

void	handle_execution_failure(char *command)
{
	minishell_error(command);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

int	command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
