/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:45 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:24:46 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ms_echo(t_command *command)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 1;
	while (command->argv[++i])
	{
		if (is_n_flag(command->argv[i]))
			new_line = 0;
		else
			break ;
	}
	while (command->argv[i])
	{
		ft_putstr_fd(command->argv[i++], STDOUT_FILENO);
		if (command->argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
