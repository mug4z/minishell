/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:07 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:26:07 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_getpreffix(char **str)
{
	int		x;
	char	*res;

	x = 0;
	if (!*str || !str)
		return (NULL);
	while (str[0][x] && str[0][x] != '$')
			x++;
	res = ft_calloc(x + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_memcpy(res, *str, x);
	(*str) += x;
	return (res);
}

char	*hd_getvarname(char **str)
{
	int		len;
	char	*res;
	int		x;

	len = 0;
	x = 0;
	if (!*str || !str)
		return (NULL);
	while (str[0][x] && str[0][x++] != '$')
		;
	(*str) += x;
	len = varnamelen(*str);
	res = ft_calloc(len + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, *str, len);
	(*str) += len;
	return (res);
}

char	*hd_getsuffix(char **str)
{
	char	*res;
	int		x;

	x = 0;
	if (!*str || !str)
		return (NULL);
	res = ft_calloc(ft_strlen(*str) + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_strcpy(res, *str);
	return (res);
}

int	hd_needexpansion(char *str)
{
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

char	*hd_joinpart(t_expension exp)
{
	char	*res;
	char	*temp;

	if (!exp.value && !exp.prefix && !exp.suffix)
		return (ft_strdup(""));
	if (exp.value == NULL && exp.prefix != NULL && exp.suffix != NULL)
	{
		temp = NULL;
		res = ft_strjoin(exp.prefix, exp.value);
	}
	else
	{
		temp = ft_strjoin(exp.prefix, exp.value);
		res = ft_strjoin(temp, exp.suffix);
		free(temp);
	}
	return (res);
}
