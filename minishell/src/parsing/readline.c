/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:41 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:52:14 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_readline(t_minishell *ms)
{
	char			*res;

	res = readline("minishell> ");
	if (res == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (1);
	}
	if (*res)
		add_history(res);
	ms->tokens = ft_parser(res);
	ft_rmv_null(&ms->tokens);
	ft_const_redirect(&ms->tokens);
	ft_rmv_space(&ms->tokens);
	init_heredoc(&ms->tokens, ms->env);
	if (ft_syntax_chk(&ms->tokens) == -1 && ms->tokens != NULL)
	{
		manage_tmp_files(TMP_FILE_REMOVE_ALL, NULL);
		del_token_list(&ms->tokens, free);
		return (0);
	}
	ft_expension(&ms->tokens, ms->env);
	ft_sanitizer(&ms->tokens);
	free(res);
	return (0);
}
