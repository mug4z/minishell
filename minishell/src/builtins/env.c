/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:48 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:39:31 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_list(t_env_list **env_list)
{
	t_env_list	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "?") && current->value)
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(current->value, STDOUT_FILENO);
		}
		current = current->next;
	}
}

int	ms_env(t_command *command)
{
	if (command->argv[1])
		return (minishell_error("env: options/arguments not handled"));
	else
		print_env_list(command->env);
	return (EXIT_SUCCESS);
}
