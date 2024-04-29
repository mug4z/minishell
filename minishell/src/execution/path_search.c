/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:38 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:42:22 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_path(char *path, char *cmd_name)
{
	char	*full_path;
	int		path_len;
	int		cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd_name);
	full_path = ft_calloc(path_len + cmd_len + 2, sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, path_len + 1);
	full_path[path_len] = '/';
	ft_strlcpy(full_path + path_len + 1, cmd_name, cmd_len + 1);
	return (full_path);
}

static char	**get_possible_paths(t_env_list *env)
{
	char	*env_path;
	char	**possible_paths;

	env_path = ms_getenv("PATH", env);
	if (!env_path)
		return (NULL);
	possible_paths = ft_split(env_path, ':');
	if (!possible_paths)
		return (NULL);
	return (possible_paths);
}

int	find_command_path(t_command *command)
{
	char	**possible_paths;
	int		i;

	possible_paths = get_possible_paths(*command->env);
	if (!possible_paths)
		return (-1);
	i = 0;
	while (possible_paths[i])
	{
		command->path = get_full_path(possible_paths[i], command->name);
		if (!command->path)
		{
			ft_free_strarray(possible_paths);
			return (-2);
		}
		if (access(command->path, F_OK) == 0 && !is_dir(command->path))
		{
			ft_free_strarray(possible_paths);
			return (0);
		}
		free(command->path);
		command->path = NULL;
		i++;
	}
	return (ft_free_strarray(possible_paths));
}
