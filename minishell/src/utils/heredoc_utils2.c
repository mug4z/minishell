/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:12 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:29:06 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	increment_filename(char *file_name)
{
	int	index;

	index = TMP_NAME_LENGTH - 1;
	while (file_name[index] != '_')
	{
		if (file_name[index] < 'z')
		{
			file_name[index]++;
			return (0);
		}
		else
		{
			file_name[index] = 'a';
			index--;
		}
	}
	return (perror("increment_filename"), 1);
}

char	*get_new_tmp_file(void)
{
	static char	file_name[TMP_NAME_LENGTH + 1] = TMP_NAME_PREFIX;
	int			fd;

	while (1)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd != -1)
			break ;
		else if (errno == EEXIST)
		{
			if (increment_filename(file_name) != 0)
				return (NULL);
		}
		else
			return (perror("get_new_tmp_file (open)"), NULL);
	}
	if (close(fd) == -1)
		perror("get_new_tmp_file (close)");
	manage_tmp_files(TMP_FILE_APPEND, file_name);
	return (file_name);
}

int	is_quote(char *str)
{
	char	char_f;

	if (ft_chk_characters(str, "\'\"", &char_f))
		return (1);
	else
		return (0);
}

int	is_expand(t_token_list *list)
{
	if (is_quote(list->content))
	{
		list->flags = IS_QUOTED;
		return (1);
	}
	else
		return (0);
}
