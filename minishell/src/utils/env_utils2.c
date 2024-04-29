/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:10 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:11 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ms_getenv_struct(char *key, t_env_list *list)
{
	t_env_list	*current;

	if (!list)
		return (NULL);
	current = list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	pop_env(t_env_list **list, t_env_list *node)
{
	t_env_list	*prev;
	t_env_list	*current;

	prev = NULL;
	if (!list || !(*list) || !node)
		return ;
	current = *list;
	while (current && current != node)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (!prev)
		*list = current->next;
	else
		prev->next = current->next;
	del_env(node);
}

int	env_list_size(t_env_list *list)
{
	int	n;

	n = 0;
	while (list)
	{
		list = list->next;
		n++;
	}
	return (n);
}

char	*cat_env(t_env_list *env)
{
	int		key_len;
	int		value_len;
	char	*str;

	key_len = ft_strlen(env->key);
	value_len = ft_strlen(env->value);
	str = ft_calloc(key_len + 1 + value_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy(str, env->key);
	str[key_len] = '=';
	ft_strcpy(str + key_len + 1, env->value);
	return (str);
}

char	**convert_envp(t_env_list *env_list)
{
	char	**envp;
	int		size;
	int		i;

	if (!env_list)
		return (NULL);
	size = env_list_size(env_list);
	envp = ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envp[i] = cat_env(env_list);
		if (!envp[i])
		{
			ft_free_strarray(envp);
			return (NULL);
		}
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
