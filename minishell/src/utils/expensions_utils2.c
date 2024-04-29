/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expensions_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:00 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:26:01 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	advance(char *str, t_expension exp)
{
	char	endquote;

	str += *(exp.index);
	while (*str)
	{
		exp.quoted = ft_isquoted(*str, &endquote, exp.quoted);
		if (exp.quoted == 1 && endquote == '\"')
			break ;
		else if (*str == '$' && exp.quoted == 0)
			break ;
		else if (endquote == '\'')
		{
			str++;
			*(exp.index) += 1;
		}
		else
			str++;
	}
}
