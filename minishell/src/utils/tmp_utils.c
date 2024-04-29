/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:44 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:26:45 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_wrapper(void *path)
{
	if (access((const char *)path, F_OK) == 0)
		unlink((const char *)path);
}

t_list	*manage_tmp_files(enum e_tmp_mode mode, char *new_file)
{
	static t_list	*tmp_files = NULL;
	t_list			*node;
	char			*cpy;

	if (mode >= TMP_FILE_MODE_COUNT)
		return (minishell_error("manage_tmp_files: invalid mode"), NULL);
	else if (mode == TMP_FILE_APPEND)
	{
		cpy = ft_strdup(new_file);
		if (!cpy)
			return (minishell_error("manage_tmp_files"), NULL);
		node = ft_lstnew(cpy);
		if (!node)
			return (minishell_error("manage_tmp_files"), NULL);
		ft_lstadd_back(&tmp_files, node);
	}
	else if (mode == TMP_FILE_REMOVE_ALL && tmp_files)
	{
		ft_lstiter(tmp_files, unlink_wrapper);
		ft_lstclear(&tmp_files, free);
	}
	return (tmp_files);
}
