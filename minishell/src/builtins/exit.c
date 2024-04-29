/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:52 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:39:57 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numeric_argument_required(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	return (255);
}

static int	too_many_arguments(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (1);
}

static int	count_args(char **argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

static int	str_is_numeric(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ms_exit(t_command *command)
{
	int		arg_count;
	char	*last_exit_value;

	if (command->pid != 0)
		ft_putendl_fd("exit", STDERR_FILENO);
	arg_count = count_args(command->argv);
	if (arg_count == 1)
	{
		last_exit_value = ms_getenv("?", *command->env);
		if (!last_exit_value)
			exit(minishell_error("exit: could not find $? value"));
		exit(ft_atoi(last_exit_value));
	}
	else if (str_is_numeric(command->argv[1]))
	{
		if (arg_count == 2)
			exit(ft_atoi(command->argv[1]));
		else
			return (too_many_arguments());
	}
	exit(numeric_argument_required(command->argv[1]));
	return (0);
}
