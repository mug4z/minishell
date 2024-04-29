/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:09 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:24:10 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	get_builtin(char *command)
{
	if (!command)
		return (NULL);
	if (ft_strcmp(command, "echo") == 0)
		return (ms_echo);
	if (ft_strcmp(command, "cd") == 0)
		return (ms_cd);
	if (ft_strcmp(command, "pwd") == 0)
		return (ms_pwd);
	if (ft_strcmp(command, "export") == 0)
		return (ms_export);
	if (ft_strcmp(command, "unset") == 0)
		return (ms_unset);
	if (ft_strcmp(command, "env") == 0)
		return (ms_env);
	if (ft_strcmp(command, "exit") == 0)
		return (ms_exit);
	return (NULL);
}

int	execute_builtin(t_command *command)
{
	if (!get_builtin(command->name))
		return (minishell_error("builtin does not exist"));
	return (command->builtin(command));
}
