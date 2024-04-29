/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:28:05 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:28:08 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

enum e_tmp_mode
{
	TMP_FILE_APPEND,
	TMP_FILE_REMOVE_ALL,
	TMP_FILE_MODE_COUNT
};

typedef enum e_word_flags
{
	IS_WORD			= 1 << 0,
	IS_EXPANDABLE	= 1 << 1,
	IS_OPERATOR		= 1 << 2,
	IS_PIPE			= 1 << 3,
	IS_REDIRECT		= 1 << 4,
	IS_INPUT		= 1 << 5,
	IS_OUTPUT		= 1 << 6,
	IS_HEREDOC		= 1 << 7,
	IS_APPEND		= 1 << 8,
	IS_QUOTED		= 1 << 9,
	IS_SGL_QUOTED	= 1 << 10,
}	t_word_flags;

typedef struct s_token_list
{
	struct s_token_list	*next;
	char				*content;
	int					flags;
}						t_token_list;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_minishell
{
	struct s_env_list	*env;
	struct s_token_list	*tokens;
	struct sigaction	sigactions;
	sigset_t			sigset;
	struct termios		original_termios;
	struct termios		updated_termios;
	int					exit_code;
}						t_minishell;

// error_utils
int				minishell_error(char *str);
void			abort_minishell(t_minishell *ms, int exit_code);
void			handle_execution_failure(char *command);
int				command_not_found(char *command);
// token_utils1
t_token_list	*lst_new_token(char *content, int flags);
void			add_token(t_token_list **list, t_token_list *new);
void			append_token(t_token_list **list, t_token_list *new);
t_token_list	*get_last_token(t_token_list *list);
void			token_lst_iter(t_token_list *list, void (*f)(char *));
// token_utils2
void			del_token(t_token_list *list, void (*del)(void *));
void			del_token_list(t_token_list **list, void (*del)(void *));
void			pop_token(t_token_list **list, t_token_list *token);
int				token_list_size(t_token_list *list);
t_token_list	*copy_token(char *content, int flags);
// Syntax check
int				ft_syntax_chk(t_token_list **list);
// env_utils1
t_env_list		*lst_new_env(char *key, char *value);
t_env_list		*get_last_env(t_env_list *list);
void			append_env(t_env_list **list, t_env_list *new);
void			del_env(t_env_list *node);
void			del_env_list(t_env_list **list);
// env_utils2
t_env_list		*ms_getenv_struct(char *name, t_env_list *list);
void			pop_env(t_env_list **list, t_env_list *node);
int				env_list_size(t_env_list *list);
char			*cat_env(t_env_list *env);
char			**convert_envp(t_env_list *env_list);
// env_utils3
t_env_list		*ft_env_lst_init(char **envp);
t_env_list		*ft_env_sep(char *stringp);
char			*ms_getenv(char *name, t_env_list *list);
//env_utils4
int				shlvl_init(t_env_list *list);
int				append_literal_env(t_env_list **list, char *key, char *value);
//sanitizer_utils
void			ft_rmv_null(t_token_list **list);

//parser_utils1
void			ft_const_redirect(t_token_list **list);
// exit_code_utils
int				update_exit_code(t_minishell *ms);
// tmp_utils
t_list			*manage_tmp_files(enum e_tmp_mode mode, char *new_file);
#endif