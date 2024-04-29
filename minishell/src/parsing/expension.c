/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:23:25 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:29:28 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varnamelen(char *str)
{
	int	x;

	x = 0;
	if (!*str || !str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
	{
		if (*str == '?')
			;
		else
			return (0);
	}
	x++;
	str++;
	while (ft_isalnum(*str) || *str == '?')
	{
		x++;
		str++;
	}
	return (x);
}

// ADD A CHECK THAT IF A ' is found
// no expansion should be performed.
char	*getvarname(char *str, t_expension exp)
{
	int		len;
	char	*res;

	len = 0;
	if (!*str || !str)
		return (NULL);
	str += *(exp.index);
	while (*str && *str++ != '$')
		;
	len = varnamelen(str);
	res = ft_calloc(len + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, str, len);
	return (res);
}

// TEST with echo $HOME 
// TEST with echo $HOME$PWD 
// EDGE case if I have echo $PWD'$PWD'

char	*getpreffix(char *str, t_expension exp)
{
	int		x;
	char	*res;

	x = 0;
	if (!*str || !str)
		return (NULL);
	advance(str, exp);
	x += *(exp.index);
	while (str[x] && str[x] != '$')
			x++;
	res = ft_calloc(x + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_memcpy(res, str, x);
	return (res);
}

char	*getsuffix(char *str, t_expension exp)
{
	int		len;
	char	*res;

	if (!*str || !str)
		return (NULL);
	advance(str, exp);
	str += *(exp.index);
	while (*str && *str++ != '$')
		;
	len = varnamelen(str);
	str += len;
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_strcpy(res, str);
	return (res);
}

void	ft_expension(t_token_list **list, t_env_list *env)
{
	t_token_list	*iter;
	t_expension		exp;
	int				index;

	iter = *list;
	while (iter)
	{
		index = 0;
		exp.index = &index;
		exp.quoted = 0;
		if ((iter->flags & IS_EXPANDABLE) == IS_EXPANDABLE)
		{
			while (needexpansion(iter->content, exp))
			{
				exp.prefix = getpreffix(iter->content, exp);
				exp.suffix = getsuffix(iter->content, exp);
				exp.varname = getvarname(iter->content, exp);
				exp.value = ms_getenv(exp.varname, env);
				indexcalc(exp);
				exp_replace_token(iter, exp);
			}
		}
		iter = iter->next;
	}
}
