/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:41 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:42 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_exit_code(t_minishell *ms)
{
	t_env_list	*node;
	char		*new_value;

	node = ms_getenv_struct("?", ms->env);
	if (!node)
	{
		if (append_literal_env(&ms->env, "?", "0"))
			return (minishell_error("update_exit_code"));
		node = ms_getenv_struct("?", ms->env);
		if (!node)
			return (minishell_error("update_exit_code: could not find $?"));
	}
	new_value = ft_itoa(ms->exit_code);
	if (!new_value)
		return (minishell_error("update_exit_code"));
	if (node->value)
		free(node->value);
	node->value = new_value;
	return (0);
}
