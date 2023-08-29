/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtavitia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:39:20 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 19:25:27 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VTAVITIA_H
# define VTAVITIA_H

# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_mhstuct	t_mhstruct;

int							g_error;

typedef enum s_token_type
{
	STRING,
	BUILTIN,
	PIPELINE,
	GT,
	LT,
	D_GT,
	D_LT,
	SEMICOL,
	NULL_VAL
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	int				s_quote;
	int				d_quote;
	int				pi;
	struct s_token	*next;
}	t_token;

// tokens
t_token	*init_token(char *data, t_token_type type);
int		is_special(char c);
int		jw(char *input, int i);
void	increment_i(char *input, int *ip, int *jp, char c);
int		check_quotes_wrapped(char *str);
void	error_msg(char *str, int err_num, t_mhstruct *mh);
void	check_and_tokenize(t_mhstruct *mh);
int		check_syntax(char *input, t_mhstruct *mh);
int		check_term_exists(char *term, t_env *env_lst);
char	*get_term(int *i, int *qty, t_token *current, char **search_term);
int		is_there_dollar(char *str);
int		num_of_dollars(char *str);
int		ft_strnstr_mod(const char *haystack, const char *needle, size_t len);
int		do_copy_inject(int *i, int termlen, t_token **new_term, t_token **curr);
int		inject_helper( int *k, int loc, t_token **curr, t_token **new_term);
int		get_location(char *search, t_token **curr);
int		inject_wo_dollar(int *k, int size, t_env **env_term, t_token **new_t);
int		inject_pid(int	*k, int size, t_token **new_t, t_mhstruct **mh);
void	copy_remaining(int *i, int *k, t_token **curr, t_token **new_term);
int		get_size(char *term, t_env *env_lst, t_env **env_term, t_mhstruct *mh);
void	finalise_newterm(t_token *new_t, t_token **curr, t_mhstruct *mh, int k);
int		inject_exit_msg(int	*k, int size, t_token **new_t, t_mhstruct **mh);
int		ft_tokenlstsize(t_token *lst);
void	remove_empty_nodes(t_mhstruct *mh);
void	classify_tokens(t_mhstruct *mh);
int		check_bad_specials(char *input);
int		check_gt(char *input, int i, int count, int open);
int		check_lt(char *input, int i, int count, int open);
void	handle_dollar(t_mhstruct **mh);
int		isbreak(char c);
void	concatenate_tokens(t_mhstruct **mh);
void	move_current(t_token **urrent, t_token **previous, t_mhstruct **mh);
void	clean_start(t_mhstruct *mh, char c);
int		do_copy_helper(char *input, int *ip, int *kp, t_token **current);
int		found_dollar(t_mhstruct *mh);
int		found_err_num(t_mhstruct *mh);
void	slice_term(t_token **x, t_mhstruct *mh, int i, int termlen);
void	term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t);
void	check_helper(char *input, char c, int *i, int *open);
int		check_bad_pipes(char *input, int i, int count, int open);
void	update_cur(t_token **prev, t_token **curr);
void	convert_dollars(t_token **current, t_mhstruct *mh);
int		check_bad_specials(char *input);
int		check_last_type(t_mhstruct *mh);

// redirects
int		do_redirects(t_token *t, t_mhstruct *mh);
int		check_redir_exist(t_token *t);
void	do_gt(t_token **t);
void	do_d_gt(t_token **t);
int		do_dups(t_token **t, t_mhstruct **mh);
void	delete_redirs(t_token **t, t_mhstruct **mh, t_token **previous);
int		bad_redirect_syntax(t_token *t);
int		act_red(t_token **tok, t_token **previous, t_mhstruct **mh);

//pipes
void	do_here_doc(char *lim, t_mhstruct *mh);
void	error_msg2(char *msg);
void	path_to_array(char ***paths, char **envp);
int		join_commands(char **paths, char *argv);
void	free_all(char **array);
int		check_pipe_exists(t_token *t);
char	*cut_argv(char *argv);
int		launch_pipes(t_mhstruct **mh);
int		action_justheredoc(t_token **tok, t_token **previous, t_mhstruct **mh);
void	just_heredoc(t_token **t, t_mhstruct **mh);
void	close_pipes(int pipes[1000][2], int lines);
int		assign_pi(t_mhstruct **mh);
int		check_heredoc(t_mhstruct *mh);
void	do_hd(int pipes[1000][2], int i, t_mhstruct **tmp);
void	close_upto_i(int pipes[1000][2], int i);
int		num_of_heredoc(t_token *t);
void	copy_to_tmp(t_mhstruct **tmp, t_token **curr);
void	set_pipe(int pipes[1000][2], int i, int lines, int hd);
void	initializer_temp_mh( t_mhstruct *tmp, t_mhstruct *mh);
int		check_redir_pipe_syntax(t_mhstruct *mh);
void	finalise_heredoc(t_mhstruct *mh, int *hdpipe);
void	do_here_doc_pipes(char *lim, t_mhstruct *mh);
void	set_prev(t_token **previous, t_token **tok);

#endif
