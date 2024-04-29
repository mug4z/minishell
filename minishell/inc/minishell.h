/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:26 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:26:27 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <limits.h>
# include "libft.h"
# include "utils.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"

// init_minishell
void	init_minishell(t_minishell *ms, char **envp);
void	signal_handler(int signal);
int		destroy_minishell(t_minishell *ms);

#endif