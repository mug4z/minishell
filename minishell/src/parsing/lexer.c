/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:10 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:24:10 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*ft_lexer(char *str)
{
	char	char_f;

	char_f = 0;
	if (ft_strcmp("|", str) == 0)
		return (lst_new_token(str, IS_OPERATOR | IS_PIPE));
	else if (ft_strcmp("<", str) == 0)
		return (lst_new_token(str, IS_OPERATOR | IS_REDIRECT | IS_INPUT));
	else if (ft_strcmp(">", str) == 0)
		return (lst_new_token(str, IS_OPERATOR | IS_REDIRECT | IS_OUTPUT));
	else if (ft_chk_characters(str, "$", &char_f) == 1 && ft_strcmp(str, "$"))
		return (lst_new_token(str, IS_WORD | IS_EXPANDABLE));
	else
		return (lst_new_token(str, IS_WORD));
}
