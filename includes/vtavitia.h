/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtavitia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:39:20 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 20:54:24 by vtavitia         ###   ########.fr       */
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

int GLOBAL_ERROR;

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

t_token	*init_token(char *data, t_token_type type);
int		is_special(char c);
int		jw(char *input, int i);
void	skip_all_whitespace(char *input, int *ip, int *jp);
void	increment_i(char *input, int *ip, int *jp, char c);
int		check_quotes_wrapped(char *str);
void	error_msg(char *str, int err_num, t_mhstruct *mh);
void	check_and_tokenize(t_mhstruct *mh);
int		is_special(char c);
int		check_syntax(char *input, t_mhstruct *mh);
int		check_term_exists(char *term, t_env *env_lst);
char*	get_search_term(int *i, int *qty, t_token *current, char **search_term);
int		is_there_dollar(char *str);
int		num_of_dollars(char *str);
int		ft_strnstr_mod(const char *haystack, const char *needle, size_t len);
int		do_copy_inject(int *i, int termlen, t_token **new_term, t_token **curr);
int		inject_helper( int *k, int location, t_token **curr, t_token **new_term);
int		get_location(char *search, t_token **curr);
int		inject_without_dollar(int *k, int size, t_env **env_term, t_token **new_t);
int		inject_pid(int	*k, int size, t_token **new_t, t_mhstruct **mh);
void	copy_remaining(int *i, int *k, t_token **curr, t_token **new_term);
int		get_size(char *term, t_env *env_lst, t_env **env_term, t_mhstruct *mh);
void	finalise_newterm(t_token *new_t, t_token **curr, t_mhstruct *mh, int k);
int		inject_exit_msg(int	*k, int size, t_token **new_t, t_mhstruct **mh);
void	replace_token(t_mhstruct *mh, t_token *new_t, int start, int nodes);
int		ft_tokenlstsize(t_token *lst);
void	free_token(t_token *token);
void	move_and_free(t_token **token, t_token **tmp);
void	remove_empty_nodes(t_mhstruct *mh);
int		check_bad_specials(char *input);
void	parse_start(t_mhstruct *mh);
int		count_chars(t_mhstruct *mh, int start, int nodes, int lst_size);
void	assign_quotes(t_token **new_t, int sq, int dq);
void	classify_tokens(t_mhstruct *mh);
int		check_bad_specials(char *input);
int		check_gt(char *input, int i, int count, int open);
int		check_lt(char *input, int i, int count, int open);
void	handle_dollar(t_mhstruct **mh);
int		isbreak(char c);
void	concatenate_tokens(t_mhstruct **mh);
void	move_current(t_token *current, t_token *previous, t_mhstruct **mh);
void	clean_start(t_mhstruct *mh, char c);
int		do_copy_helper(char *input, int *ip, int *kp, t_token **current);
int		found_dollar(t_mhstruct *mh);
int		found_err_num(t_mhstruct *mh);
void	slice_term(t_token **x, t_mhstruct *mh, int i, int termlen);
void	inject_term(char *search, t_token **curr, t_mhstruct *mh);
void	shift_i(t_token **current, int *i);
void	term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t);
void	check_helper(char *input, char c, int *i, int *open);
int		check_bad_pipes(char *input, int i, int count, int open);
void	update_car(t_token **prev, t_token **curr);
void	convert_dollars(t_token **current, t_mhstruct *mh);
void	term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t);

// redirects
int		do_redirects(t_token *t, t_mhstruct *mh, int x);
void	execution_of_commands(t_mhstruct *mh);
int		check_redir_exist(t_token *t);
void	set_prev(t_token **previous, t_token **tok);
void	do_gt(t_token **t);
void	do_d_gt(t_token **t);
int	do_dups(t_token **t, t_mhstruct **mh);
void	delete_redirs(t_token **t, t_mhstruct **mh, t_token **previous);
void	run_comms(t_mhstruct *mh, int mark, int in, int screen);
int		bad_redirect_syntax(t_token *t);
int		act_red(t_token **tok, t_token **previous, t_mhstruct **mh);

//pipes
void	do_here_doc(char *lim, t_mhstruct *mh);
int		setting_out_files(char **argv, int *outfile, int argc);
int		setting_in_files(int *infile, char **argv, char **envp);
int		check_command(char *argv, char **envp);
int		setting_files(int *i, int argc, char **argv, char **envp);
char	*find_path(char *comm, char **envp, char *buffer);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	error_msg2(char *msg);
int		check_commands(char **argv, char **envp, int argc);
int		check_first_comm(char *argv, char **envp);
void	path_to_array(char ***paths, char **envp);
int		join_commands(char **paths, char *argv);
int		set_infile(int *infile, char **argv, int argc, char **envp);
void	free_all(char **array);
int		dup_out_file(int *outfile, t_mhstruct **mh);
int		check_pipe_exists(t_token *t);
int		check_path_exists(char *argv, char **envp, char **command_path);
char	*cut_argv(char *argv);
int		bad_redirect_syntax2(t_token *t);
int		launch_pipes(t_mhstruct **mh);
char	**get_arg_array(t_mhstruct *mh);
int		check_path(char *argv, char **envp, char **command_path);
int		execve_of_commands_2(char *path, char **arg, char **env);
void	execve_commands_pipes(t_token *curr, t_mhstruct *mh, int lines, int pipes[1000][2]);
int		check_redir_exist_pipe(t_token *t);
int		action_justheredoc(t_token **tok, t_token **previous, t_mhstruct **mh);
void	just_heredoc(t_token *t, t_mhstruct *mh);
int		action_redirect_pipe(t_token **tok, t_token **previous, t_mhstruct **mh, int screen);
void	do_redirects_pipes(t_token *t, t_mhstruct *mh, int x);
void	close_pipes(int pipes[1000][2], int lines);
int		assign_pi(t_mhstruct **mh);

int		c_w(t_mhstruct **mh, int i);
int		c_ch(t_mhstruct **mh, int i);
void	copy_to_grid(t_mhstruct **mh, int i, char **grid);
void	create_grid(char **grid, int lines, t_mhstruct **mh);
void	c_pipes(int pipes[1000][2] , int lines);
int		check_redir_exist_pipe(t_token *t);
int		num_of_heredoc(t_token *t);

//delete this
void	print_tokens(t_token *token);
void	dell(t_token **t);
#endif
