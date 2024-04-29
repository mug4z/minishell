/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:11 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:26:12 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	init_minishell(&ms, envp);
	while (1)
	{
		while (!ms.tokens)
			if (ft_readline(&ms))
				return (destroy_minishell(&ms));
		ms.exit_code = execute_command_line(&ms);
		update_exit_code(&ms);
		del_token_list(&ms.tokens, free);
	}
	return (destroy_minishell(&ms));
}
