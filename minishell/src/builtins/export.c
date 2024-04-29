/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:01 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:40:43 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	set_env_value(t_env_list *node, char *value)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	node->value = value;
}

static int	set_export_var(t_env_list *env, const char *arg)
{
	t_env_list	*new_env;
	t_env_list	*current;
	char		*tmp;

	tmp = ft_strdup(arg);
	if (!tmp)
		return (1);
	new_env = ft_env_sep(tmp);
	free(tmp);
	if (!new_env)
		return (1);
	current = ms_getenv_struct(new_env->key, env);
	if (!ft_strchr(arg, '='))
	{
		if (current)
			return (free(new_env), 0);
		free(new_env->value);
		new_env->value = NULL;
	}
	if (current)
		pop_env(&env, current);
	append_env(&env, new_env);
	return (0);
}

int	valid_identifier(const char *str)
{
	if (!str || !(*str))
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	ms_export(t_command *command)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!command->argv[i])
	{
		if (print_export_list(*command->env))
			return (minishell_error("export"));
	}
	else
	{
		while (command->argv[i])
		{
			if (!valid_identifier(command->argv[i]))
				exit_code = invalid_identifier(command->argv[i]);
			else if (set_export_var(*command->env, command->argv[i]))
				return (minishell_error("export"));
			i++;
		}
	}
	return (exit_code);
}
