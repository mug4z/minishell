/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:27:57 by tfrily            #+#    #+#             */
/*   Updated: 2024/04/29 11:27:58 by tfrily           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define TMP_NAME_LENGTH (12)
# define TMP_NAME_PREFIX "ms_hdtmp_aaa"
# define META_SEP " \\\t|<>;&()*"

typedef struct s_context
{
	int			quoted;
	char		delim;
}				t_context;

typedef struct s_expension
{
	char		*prefix;
	char		*suffix;
	char		*value;
	char		*varname;
	int			*index;
	int			quoted;
}				t_expension;

// Readline
int				ft_readline(t_minishell *ms);
// PARSER
t_token_list	*ft_parser(char *line);
int				ft_chk_characters(char *line, char *characters, char *char_f);
int				ft_isquoted(char c, char *endquote, int quoted);
// Parser utils
int				is_flag(int flags, int flag);
// Lexer
t_token_list	*ft_lexer(char *str);
// UTILS TEST
void			ft_print_tok_lst(t_token_list **list);
// Sanitizer
void			ft_sanitizer(t_token_list **list);
void			ft_rmv_space(t_token_list **list);
void			ft_rmv_quote_pair(char *line, char quote);
// Expansion
int				varnamelen(char *str);
char			*getvarname(char *str, t_expension exp);
char			*getpreffix(char *str, t_expension exp);
char			*getsuffix(char *str, t_expension exp);
void			ft_expension(t_token_list **list, t_env_list *env);

// Expansion_utils
void			exp_replace_token(t_token_list *current, t_expension exp);
int				needexpansion(char *str, t_expension exp);
int				indexcalc(t_expension exp);
void			advance(char *str, t_expension exp);
char			*joinpart(t_expension exp);
// heredoc
int				init_heredoc(t_token_list **list, t_env_list *env);
// heredoc_utils1
char			*hd_getpreffix(char **str);
char			*hd_getvarname(char **str);
char			*hd_getsuffix(char **str);
int				hd_needexpansion(char *str);
//heredoc_utils2
char			*get_new_tmp_file(void);
int				is_quote(char *str);
int				is_expand(t_token_list *list);
#endif