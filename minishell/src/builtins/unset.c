/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:12 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:08 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(t_command *command)
{
	t_env_list	*node_to_delete;
	int			exit_code;
	int			i;

	exit_code = 0;
	i = 0;
	while (command->argv[++i])
	{
		if (!valid_identifier(command->argv[i]))
			exit_code = invalid_identifier(command->argv[i]);
		else if (ft_strcmp(command->argv[i], "_"))
		{
			node_to_delete = ms_getenv_struct(command->argv[i], *command->env);
			if (node_to_delete)
				pop_env(command->env, node_to_delete);
			exit_code = 0;
		}
	}
	return (exit_code);
}
