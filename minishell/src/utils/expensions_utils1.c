/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expensions_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:53 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:25:54 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinpart(t_expension exp)
{
	char	*res;
	char	*temp;

	if (!exp.value && !exp.prefix && !exp.suffix)
		return (ft_strdup(""));
	if (exp.value == NULL && exp.prefix != NULL && exp.suffix != NULL)
	{
		temp = NULL;
		res = ft_strjoin(exp.prefix, exp.suffix);
	}
	else
	{
		temp = ft_strjoin(exp.prefix, exp.value);
		res = ft_strjoin(temp, exp.suffix);
		if (temp)
			free(temp);
	}
	return (res);
}

void	exp_replace_token(t_token_list *current, t_expension exp)
{
	char	*res;

	res = joinpart(exp);
	free(exp.prefix);
	free(exp.suffix);
	free(exp.varname);
	free(current->content);
	current->content = res;
}

int	indexcalc(t_expension exp)
{
	int	len_pre;
	int	len_value;

	if (exp.value == NULL)
		return (0);
	len_pre = ft_strlen(exp.prefix);
	len_value = ft_strlen(exp.value);
	*(exp.index) = len_pre + len_value;
	return (len_pre + len_value);
}

// Should take into account the simple quotes.
	// echo $HOME'$HOME' -> /usr/../..$HOME
// Should check what is directly after $
	// If number 0-9 ->copy emptystring + the rest of the string.
	// If non alphanum ignore it.
int	needexpansion(char *str, t_expension exp)
{
	if (exp.prefix == NULL || exp.suffix == NULL)
	{	
		minishell_error("unable to perform expansion");
		return (0);
	}
	str += *(exp.index);
	if (*str)
	{
		while (*str && *str++ != '$')
			;
		if (*str)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
