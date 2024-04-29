/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:07 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:08 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_command *command)
{
	char	buffer[PWD_BUFFER_SIZE];
	char	*str;

	(void)command;
	str = getcwd(buffer, PWD_BUFFER_SIZE);
	if (!str)
	{
		minishell_error("pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(str, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
