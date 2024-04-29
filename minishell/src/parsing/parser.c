/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:31 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:29:17 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compare a string, to a list of characters to determine
 * 		  if the characters are present in the line
 *
 * @param line A string.
 * @param characters List of characters.
 * @param char_f The first character found in line based on characters.
 * @return int return 0 if characters not present in line and 1 if it is.
 */
int	ft_chk_characters(char *line, char *characters, char *char_f)
{
	int	x;
	int	y;

	x = 0;
	while (line[x])
	{
		y = 0;
		while (characters[y])
		{
			if (line[x] == characters[y])
			{
				*char_f = characters[y];
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_isquoted(char c, char *endquote, int quoted)
{
	if ((c == '\"' || c == '\'' ) && quoted == 0)
	{
		quoted = 1;
		*endquote = c;
	}
	else if (*endquote == c && quoted == 1)
		return (0);
	return (quoted);
}

char	*ft_strsep_iter(char **stringp, char *delim, char *tok,
t_context *context)
{
	int		y;
	char	endquote;

	context->quoted = 0;
	endquote = 0;
	while (**stringp)
	{
		y = 0;
		context->quoted = ft_isquoted(**stringp, &endquote, context->quoted);
		while (delim[y] && context->quoted == 0)
		{
			if (**stringp == delim[y])
			{
				context->delim = delim[y];
				**stringp = '\0';
				(*stringp)++;
				return (tok);
			}
			y++;
		}
		(*stringp)++;
	}
	return (NULL);
}

/**
 * @brief
 *
 * @param stringp Reference to the string to parse.
 * @param delim   Delimiter's string.
 * @return char*  Return the pointer to the token.
 */
char	*ft_strsep(char **stringp, char *delim, t_context *context)
{
	char	*tok;

	if (*stringp == NULL)
		return (NULL);
	tok = *stringp;
	context->delim = '\0';
	if (ft_strsep_iter(stringp, delim, tok, context))
		return (tok);
	else
	{
		*stringp = NULL;
		return (tok);
	}
}

/**
 * @brief Function to parse the line given in arguments.
 *
 * @param line A user's input.
 * @return t_token_list Return the t_token_list linked list that contains
 * 		   different token with different flags.
 */
t_token_list	*ft_parser(char *line)
{
	char			*token;
	t_token_list	*delim;
	t_token_list	*list;
	t_token_list	*node;
	t_context		context;

	list = NULL;
	while (line != NULL)
	{
		token = ft_strdup(ft_strsep(&line, META_SEP, &context));
		if (token == NULL)
			return (del_token_list(&list, free), NULL);
		node = ft_lexer(token);
		delim = ft_lexer(ft_strdup(&context.delim));
		if (node == NULL || delim == NULL || delim->content == NULL)
			return (del_token_list(&list, free), NULL);
		append_token(&list, node);
		append_token(&list, delim);
	}
	if (context.quoted == 1)
	{
		minishell_error("Unclosed quotes ");
		return (del_token_list(&list, free), NULL);
	}
	return (list);
}
