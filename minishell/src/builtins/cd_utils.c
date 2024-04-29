/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:29 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:24:30 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_new_node(t_env_list *env, char *key_literal, char *value)
{
	t_env_list	*node;
	char		*key;

	key = ft_strdup(key_literal);
	if (!key)
		return (1);
	node = lst_new_env(key, value);
	if (!node)
	{
		free(key);
		return (1);
	}
	append_env(&env, node);
	return (0);
}

static int	set_oldpwd(t_env_list *env, char *old_value)
{
	char		*new_value;
	t_env_list	*oldpwd_node;

	new_value = ft_strdup(old_value);
	if (!new_value)
		return (minishell_error("cd: set_oldwpd"));
	oldpwd_node = ms_getenv_struct("OLDPWD", env);
	if (!oldpwd_node)
	{
		if (init_new_node(env, "OLDPWD", new_value))
		{
			free(new_value);
			return (minishell_error("cd: set_oldpwd: init_new_node"));
		}
	}
	else
		set_env_value(oldpwd_node, new_value);
	return (0);
}

static int	set_pwd(t_env_list *env)
{
	char		*cwd;
	t_env_list	*pwd_node;

	cwd = ft_calloc(1, PWD_BUFFER_SIZE);
	if (!cwd)
		return (minishell_error("cd: set_pwd"));
	if (!getcwd(cwd, PWD_BUFFER_SIZE))
	{
		free(cwd);
		return (minishell_error("cd: set_pwd"));
	}
	pwd_node = ms_getenv_struct("PWD", env);
	if (!pwd_node)
	{
		if (init_new_node(env, "PWD", cwd))
		{
			free(cwd);
			return (minishell_error("cd: set_pwd: init_new_node"));
		}
	}
	else
		set_env_value(pwd_node, cwd);
	return (0);
}

int	set_env_directories(t_env_list *env, char *oldpwd)
{
	if (set_oldpwd(env, oldpwd) != 0)
		return (1);
	if (set_pwd(env) != 0)
		return (1);
	return (0);
}
