/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtavitia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:39:20 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/02 14:27:24 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VTAVITIA_H
# define VTAVITIA_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "minishell.h"

typedef struct s_mhstuct	t_mhstruct;

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
	char			*data_for_redir;
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
void	concatenate_tokens(t_mhstruct *mh);
int		is_special(char c);
int		check_syntax(char *input, t_mhstruct *mh);
void	handle_dollar(t_mhstruct **mh);
int		check_term_exists(char *term, t_env *env_lst);
void	get_search_term(int *i, int *qty, t_token *current, char **search_term);
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

// redirects
void	do_redirects(t_token *t, t_mhstruct *mh);


//delete this
void	print_tokens(t_token *token);
#endif
