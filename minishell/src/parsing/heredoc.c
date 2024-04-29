/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:03 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 13:44:26 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp(t_expension exp)
{
	if (exp.prefix)
		free(exp.prefix);
	if (exp.suffix)
		free(exp.suffix);
	if (exp.varname)
		free(exp.varname);
}

void	heredoc_expansion(char *str, t_env_list *env, int h_fd)
{
	t_expension		exp;
	char			*iter;
	char			*start;

	iter = ft_strdup(str);
	if (!iter)
		return ;
	while (hd_needexpansion(iter))
	{
		start = iter;
		exp.prefix = hd_getpreffix(&iter);
		exp.varname = hd_getvarname(&iter);
		exp.value = ms_getenv(exp.varname, env);
		exp.suffix = hd_getsuffix(&iter);
		free(start);
		iter = joinpart(exp);
		free_exp(exp);
		if (!iter)
		{
			minishell_error("joinpart");
			return ;
		}
	}
	ft_putendl_fd(iter, h_fd);
	free(iter);
}

int	write_file(char *file_name, t_token_list *list, t_env_list *env)
{
	char	*res;
	int		h_fd;

	h_fd = open(file_name, O_WRONLY, 0600);
	if (h_fd < 0)
		return (minishell_error(file_name));
	res = 0;
	while (1)
	{
		if (res)
			free(res);
		res = readline("> ");
		if (!res || ft_strcmp(list->content, res) == 0)
			break ;
		if (!is_flag(list->flags, IS_QUOTED))
			heredoc_expansion(res, env, h_fd);
		else
			ft_putendl_fd(res, h_fd);
	}
	free(res);
	if (close(h_fd) == -1)
		return (minishell_error(file_name));
	return (0);
}	

static int	set_token(t_token_list *token, char *new_content, int new_flags)
{
	if (!token)
		return (minishell_error("init_heredoc: set_token: no token provided"));
	if (token->content)
		free(token->content);
	token->content = ft_strdup(new_content);
	if (!token->content)
		return (minishell_error("init_heredoc: set_token"));
	token->flags = new_flags;
	return (0);
}

int	init_heredoc(t_token_list **list, t_env_list *env)
{
	t_token_list	*iter;
	char			quote;
	char			*tmp_file;

	iter = *list;
	while (iter)
	{
		quote = '\0';
		if (is_flag(iter->flags, IS_HEREDOC) && iter->next != NULL)
		{
			if (is_flag(iter->next->flags, IS_WORD))
			{
				is_expand(iter->next);
				ft_chk_characters(iter->next->content, "\'\"", &quote);
				ft_rmv_quote_pair(iter->next->content, quote);
				tmp_file = get_new_tmp_file();
				write_file(tmp_file, iter->next, env);
				if (set_token(iter->next, tmp_file, IS_WORD) == 1)
					return (1);
			}
		}
		iter = iter->next;
	}
	return (0);
}
