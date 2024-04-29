/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:16 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:19 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the value of an environment variable from the
 * internal environment linked list.
 * 
 * @param name The name of the environment variable.
 * @param list The linked list of environment variables.
 * @return If a value is found returns it as a pointer. If the list is NULL
 * or the value is not found returns NULL.
 */
char	*ms_getenv(char *name, t_env_list *list)
{
	t_env_list	*current;

	if (!list)
		return (NULL);
	current = list;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*ft_set_key(char **stringp)
{
	int			y;
	char		*res;

	y = 0;
	while ((*stringp)[y] && (*stringp)[y] != '=')
		y++;
	res = ft_calloc(y + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_memcpy(res, *stringp, y);
	if ((*stringp)[y] == '=')
		(*stringp)[y++] = '\0';
	*stringp += y;
	return (res);
}

static char	*ft_set_value(char *stringp)
{
	char	*res;

	res = ft_calloc(ft_strlen(stringp) + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_strcpy(res, stringp);
	return (res);
}

t_env_list	*ft_env_sep(char *stringp)
{
	char		*key;
	char		*value;
	t_env_list	*res;

	res = NULL;
	value = NULL;
	if (stringp == NULL)
		return (NULL);
	key = ft_set_key(&stringp);
	if (key == NULL)
		return (NULL);
	if (stringp)
	{
		value = ft_set_value(stringp);
		if (value == NULL)
			return (free(key), NULL);
	}
	res = lst_new_env(key, value);
	if (res == NULL)
	{
		free(key);
		free(value);
	}
	return (res);
}

t_env_list	*ft_env_lst_init(char **envp)
{
	t_env_list	*node;
	t_env_list	*list;
	char		*line;

	if (envp == NULL)
		return (NULL);
	list = NULL;
	node = NULL;
	while (*envp)
	{
		line = ft_strdup(*envp);
		if (line == NULL)
			return (del_env_list(&list), NULL);
		node = ft_env_sep(line);
		if (node == NULL)
		{
			free(line);
			return (del_env_list(&list), NULL);
		}
		append_env(&list, node);
		free(line);
		envp++;
	}
	return (list);
}
