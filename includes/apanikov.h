/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apanikov.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:29:30 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 19:23:21 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APANIKOV_H
# define APANIKOV_H

# include "minishell.h"

typedef struct s_mhstuct	t_mhstruct;
typedef struct s_env		t_env;

void	builtin_pwd(t_mhstruct *mh);
t_env	*create_env_node(const char *name, const char *data);
t_env	*create_env_node2(const char *name, const char *data);
void	insert_env_node(t_env **head, t_env *node);
void	builtin_env(t_mhstruct *mh);
void	builtin_export(t_mhstruct *mh);
void	builtin_unset(t_mhstruct *mh);
void	builtin_cd(t_mhstruct *mh);
void	builtin_echo(t_mhstruct *mh);
void	builtin_exit(t_mhstruct *mh);
void	do_exit(t_mhstruct *mh, int en, char *data);
void	add_oldpwd_node(t_mhstruct *mh);
void	check_oldpwd(t_mhstruct *mh);
void	initializer_mh(char **env, t_mhstruct *mh);
char	**get_env_array(t_mhstruct *mh);
char	*ft_mhjoin(char *s1, char *s2);
char	*gemsg(char *cmndname, char *errmsg, char *data);
void	pr_err(t_mhstruct *mh, int i, char *errmsg);
void	execve_of_commands(t_mhstruct *mh);
void	execution_of_commands(t_mhstruct *mh);
void	do_sigint(int i);
void	do_sigquit(int i);
void	add_error_message(t_mhstruct *mh);
void	free_token_main(t_mhstruct *mh);
void	free_env(t_env *env);
void	do_sigint_fork(int i);
void	reassign_path(char **path, char **arg);
int		get_arg_list_size(t_mhstruct *mh);
void	change_pwd(t_mhstruct *mh);
void	change_oldpwd(t_mhstruct *mh, char *old);
void	error_opendir(t_mhstruct *mh, char *path);
int		do_cd(t_mhstruct *mh, char *path);
void	do_cd_oldpwd(t_mhstruct *mh);
void	exit_num_req(t_mhstruct *mh, const char *data);
int		check_long_min(const char *str);
int		handle_for_export(t_mhstruct *mh, char *tdata);
int		check_env_name(t_env **head, char *name);
void	change_env_data(t_env **head, char *name, char *data);
void	join_env_data(t_env **head, char *name, char *data);
void	join_export_2(t_mhstruct *mh, char *tdata);
void	add_export_2(t_mhstruct *mh, char *tdata);
void	add_export(t_mhstruct *mh, char *tdata);
void	initializer_env(char **env, t_mhstruct *mh, t_env *node, int i);
void	minihell(t_mhstruct *mh, int mark);
void	minihell2(t_mhstruct *mh, int mark);

#endif