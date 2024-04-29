/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:36 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:38:17 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_to_old_pwd(t_env_list *env, char *cwd)
{
	char	*oldpwd;

	oldpwd = ms_getenv("OLDPWD", env);
	if (!oldpwd)
		return (minishell_error("cd: OLDPWD not set"));
	if (chdir(oldpwd))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(oldpwd);
		return (EXIT_FAILURE);
	}
	ms_pwd(NULL);
	return (set_env_directories(env, cwd));
}

static int	change_to_new_dir(t_env_list *env, char *new_dir, char *cwd)
{
	if (*new_dir && chdir(new_dir))
		return (minishell_error("cd"));
	return (set_env_directories(env, cwd));
}

static int	change_to_home_dir(t_env_list *env, char *cwd)
{
	char		*home;

	home = ms_getenv("HOME", env);
	if (!home)
		return (minishell_error("cd: HOME not set"));
	if (*home && chdir(home))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(home);
		return (EXIT_FAILURE);
	}
	return (set_env_directories(env, cwd));
}

int	ms_cd(t_command *command)
{
	char	cwd[PWD_BUFFER_SIZE];

	if (!getcwd(cwd, PWD_BUFFER_SIZE))
		return (minishell_error("cd"));
	if (command->argv[1])
	{
		if (command->argv[1][0] == '-')
		{
			if (ft_strcmp(command->argv[1], "-") == 0)
				return (change_to_old_pwd(*command->env, cwd));
			else
				return (minishell_error("cd: options not supported"));
		}
		else
			return (change_to_new_dir(*command->env, command->argv[1], cwd));
	}
	return (change_to_home_dir(*command->env, cwd));
}
