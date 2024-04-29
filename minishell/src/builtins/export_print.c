/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:56 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:24:57 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(t_env_list **env, int env_count)
{
	int	i;

	i = 0;
	while (i < env_count)
	{
		if (env[i]->key && ft_strcmp(env[i]->key, "_") \
			&& ft_strcmp(env[i]->key, "?"))
		{
			printf("declare -x %s", env[i]->key);
			if (env[i]->value)
				printf("=\"%s\"\n", env[i]->value);
			else
				printf("\n");
		}
		i++;
	}
}

static void	ft_sort_env_array(t_env_list **env, int env_count)
{
	t_env_list	*tmp;
	int			n;
	int			unsorted;

	n = 0;
	unsorted = 1;
	tmp = *env;
	while (unsorted)
	{
		while (n < env_count - 1)
		{
			if (ft_strcmp(env[n]->key, env[n + 1]->key) > 0)
			{
				tmp = env[n];
				env[n] = env[n + 1];
				env[n + 1] = tmp;
				unsorted ++;
			}
			n ++;
		}
		n = 0;
		unsorted --;
	}
}

static int	count_env_size(t_env_list *env)
{
	int			count;
	t_env_list	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	print_export_list(t_env_list *env)
{
	int			env_count;
	t_env_list	*current;
	t_env_list	**env_array;
	int			i;

	env_count = count_env_size(env);
	env_array = ft_calloc(env_count, sizeof(t_env_list *));
	if (!env_array)
		return (1);
	current = env;
	i = 0;
	while (i < env_count)
	{
		env_array[i++] = current;
		current = current->next;
	}
	ft_sort_env_array(env_array, env_count);
	print_export(env_array, env_count);
	free(env_array);
	return (0);
}
