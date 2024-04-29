/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:44 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 12:35:41 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define CMD_INPUT (0)
# define CMD_OUTPUT (1)

# define DEFAULT_PATH "/usr/local/bin:/usr/local/sbin:\
/usr/bin:/usr/sbin:/bin:/sbin"

typedef struct s_command
{
	t_env_list			**env;
	char				**argv;
	char				*name;
	int					(*builtin)(struct s_command *);
	char				*path;
	int					input;
	int					output;
	int					stdin_cpy;
	int					stdout_cpy;
	t_token_list		*redirections;
	pid_t				pid;
	struct s_command	*next;
}						t_command;

typedef struct s_pipe
{
	int	read;
	int	write;
}		t_pipe_fd;

typedef struct s_pipeline
{
	t_env_list		*env;
	t_pipe_fd		*pipe_fd;
	int				pipe_count;
	t_token_list	**token_lists;
	t_command		*command;
	int				command_count;
	int				*command_pid;
}				t_pipeline;

// execution
int				execute_command_line(t_minishell *ms);
int				execute_pipeline(t_pipeline *pipeline);
int				execute_command(t_command *command);
int				execute_system_command(t_command *command);
int				execute_child_system_command(t_command *command);
// exec_utils
int				ft_free_strarray(char **array);
int				is_dir(char *path);
int				wait_for_children(t_pipeline *pipeline);
// command_utils1
t_command		*new_command(t_token_list **tokens, t_env_list **env);
void			destroy_command(t_command *command);
int				init_command_args(t_token_list *tokens, t_command *command);
int				init_command_path(t_command *command);
// command_utils2
int				init_pipeline_cmds(t_pipeline *pipeline, t_token_list **tok);
void			append_command(t_command **list, t_command *new);
t_command		*get_last_command(t_command *list);
t_token_list	*get_next_command(t_token_list *tokens);
t_token_list	*extract_command(t_token_list **list);
// path_search
int				find_command_path(t_command *command);
// pipe_utils1
int				init_pipeline(t_pipeline *pipeline, t_token_list **tok, \
													t_env_list **env);
int				count_pipes(t_token_list *tokens);
int				init_pipes(t_pipeline *pipeline);
int				create_pipe(t_pipe_fd *pipe_fd);
int				apply_pipe_redirects(t_pipeline *pipeline, t_command *command);
// pipe_utils2
void			close_pipe(t_pipe_fd *pipe_fd);
void			close_all_pipes(t_pipeline *pipeline);
void			destroy_pipes(t_pipeline *pipeline);
void			close_unused_pipes(t_pipeline *p, int read_fd, int write_fd);
void			destroy_pipeline(t_pipeline *pipeline);
//	redirect
int				init_command_redirections(t_token_list **list, t_command *cmd);
int				duplicate_standard_fds(t_command *command);
int				apply_redirections(t_command *cmd);
int				restore_standard_fds(t_command *command);
// redirect_utils
int				open_redirect(t_token_list *redirect);
int				redirect_input(t_command *command, t_token_list *redirect);
int				redirect_output(t_command *command, t_token_list *redirect);

#endif