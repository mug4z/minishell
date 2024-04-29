/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:25 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:26 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_shlvl_exist(t_env_list *list)
{
	t_env_list	*shlvl_node;

	shlvl_node = ms_getenv_struct("SHLVL", list);
	if (!shlvl_node)
		return (0);
	else
		return (1);
}

char	*shlvl_increment(t_env_list *node)
{
	int		increment;
	char	*res;

	if (!node->value)
		res = ft_strdup("1");
	else
	{
		increment = ft_atoi(node->value);
		increment++;
		res = ft_itoa(increment);
	}
	return (res);
}

int	update_shlvl(t_env_list *list)
{
	t_env_list	*node;
	char		*new_value;

	node = ms_getenv_struct("SHLVL", list);
	if (!node)
		return (0);
	new_value = shlvl_increment(node);
	if (!new_value)
		return (0);
	set_env_value(node, new_value);
	return (1);
}

int	shlvl_init(t_env_list *list)
{
	if (!is_shlvl_exist(list))
	{	
		if (append_literal_env(&list, "SHLVL", "1"))
			return (minishell_error("shlvl_init"));
	}
	else
	{
		if (!update_shlvl(list))
			return (minishell_error("could not update the SHLVL variable"));
	}
	return (0);
}

int	append_literal_env(t_env_list **list, char *key, char *value)
{
	t_env_list	*node;
	char		*key_dup;
	char		*value_dup;

	if (!list)
		return (1);
	if (ms_getenv_struct(key, *list))
		return (0);
	key_dup = ft_strdup(key);
	if (key_dup)
	{
		value_dup = ft_strdup(value);
		if (value_dup)
		{
			node = lst_new_env(key_dup, value_dup);
			if (node)
			{
				append_env(list, node);
				return (0);
			}
			free(value_dup);
		}
		free(key_dup);
	}
	return (1);
}
