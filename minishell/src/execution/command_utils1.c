/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:22 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:42:49 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(t_token_list **tokens, t_env_list **env)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (minishell_error("new_command"), NULL);
	cmd->env = env;
	if (init_command_redirections(tokens, cmd))
		return (minishell_error("init_command_redirections"), NULL);
	if (init_command_args(*tokens, cmd))
		return (minishell_error("init_command_args"), NULL);
	if (cmd->argv)
	{
		cmd->name = cmd->argv[0];
		cmd->builtin = get_builtin(cmd->name);
		if (!cmd->builtin && init_command_path(cmd))
			return (minishell_error("init_command_path"), NULL);
	}
	cmd->input = -1;
	cmd->output = -1;
	cmd->stdin_cpy = -1;
	cmd->stdout_cpy = -1;
	cmd->pid = -1;
	return (cmd);
}

void	destroy_command(t_command *command)
{
	if (!command)
		return ;
	if (command->argv)
		free(command->argv);
	if (command->path)
		free(command->path);
	if (command->redirections)
		del_token_list(&command->redirections, free);
	free(command);
	command = NULL;
}

int	init_command_args(t_token_list *tokens, t_command *cmd)
{
	int				count;
	t_token_list	*current;
	int				i;

	count = token_list_size(tokens);
	if (count <= 0)
		return (0);
	cmd->argv = ft_calloc(count + 1, sizeof(char *));
	if (!cmd->argv)
		return (1);
	current = tokens;
	i = 0;
	while (current && !(current->flags & IS_PIPE))
	{
		cmd->argv[i] = current->content;
		current = current->next;
		i++;
	}
	return (0);
}

int	init_command_path(t_command *command)
{
	if (!command->name)
		return (0);
	if (ft_strchr(command->name, '/'))
	{
		command->path = ft_strdup(command->name);
		if (!command->path)
			return (-1);
		return (0);
	}
	else if (!ms_getenv("PATH", *command->env))
		return (0);
	else
		return (find_command_path(command));
}
