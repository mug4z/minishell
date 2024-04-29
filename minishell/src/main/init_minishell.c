/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:07 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:26:08 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_signal_handling(t_minishell *ms)
{
	sigemptyset(&ms->sigset);
	sigaddset(&ms->sigset, SIGINT);
	sigaddset(&ms->sigset, SIGQUIT);
	ms->sigactions.sa_handler = signal_handler;
	ms->sigactions.sa_mask = ms->sigset;
	ms->sigactions.sa_flags = 0;
	if (sigaction(SIGINT, &ms->sigactions, NULL) == -1)
		return (minishell_error("set_signal_handling: SIGINT"));
	if (sigaction(SIGQUIT, &ms->sigactions, NULL) == -1)
		return (minishell_error("set_signal_handling: SIGINT"));
	return (0);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_EOF) || RL_ISSTATE(RL_STATE_DONE))
			return ;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		rl_redisplay();
}

static int	set_termios(t_minishell *ms)
{
	if (tcgetattr(STDIN_FILENO, &ms->original_termios))
		return (minishell_error("tcgetattr"));
	ms->updated_termios = ms->original_termios;
	ms->updated_termios.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &ms->updated_termios))
		return (minishell_error("tcsetattr"));
	return (0);
}

void	init_minishell(t_minishell *ms, char **envp)
{
	ft_bzero(ms, sizeof(t_minishell));
	if (set_signal_handling(ms) || set_termios(ms))
		abort_minishell(ms, EXIT_FAILURE);
	if (envp && *envp)
	{
		ms->env = ft_env_lst_init(envp);
		if (!ms->env)
			abort_minishell(ms, EXIT_FAILURE);
	}
	if (!ms_getenv_struct("PATH", ms->env) \
		&& append_literal_env(&ms->env, "PATH", DEFAULT_PATH))
		abort_minishell(ms, EXIT_FAILURE);
	if (update_exit_code(ms))
		abort_minishell(ms, EXIT_FAILURE);
	if (shlvl_init(ms->env))
		abort_minishell(ms, EXIT_FAILURE);
}

int	destroy_minishell(t_minishell *ms)
{
	rl_clear_history();
	if (tcsetattr(STDIN_FILENO, TCSANOW, &ms->original_termios))
		minishell_error("unable to restore terminal attribute");
	if (ms->env)
		del_env_list(&ms->env);
	if (ms->tokens)
		del_token_list(&ms->tokens, free);
	manage_tmp_files(TMP_FILE_REMOVE_ALL, NULL);
	return (ms->exit_code);
}
