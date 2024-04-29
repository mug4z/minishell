/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:48 by bgolding          #+#    #+#             */
/*   Updated: 2024/04/29 11:26:49 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define PWD_BUFFER_SIZE (4096)

typedef int	(*t_builtin)(t_command *);

// builtins
t_builtin	get_builtin(char *command);
int			execute_builtin(t_command *command);
// echo
int			ms_echo(t_command *command);
// cd
int			ms_cd(t_command *command);
// cd_utils
int			set_env_directories(t_env_list *env, char *oldpwd);
// pwd
int			ms_pwd(t_command *command);
// export
int			ms_export(t_command *command);
int			valid_identifier(const char *str);
int			invalid_identifier(char *str);
void		set_env_value(t_env_list *node, char *value);
// export_print
int			print_export_list(t_env_list *env);
//unset
int			ms_unset(t_command *command);
// env
int			ms_env(t_command *command);
// exit
int			ms_exit(t_command *command);

#endif