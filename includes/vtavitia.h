/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtavitia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:39:20 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/18 13:16:46 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VTAVITIA_H
# define VTAVITIA_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "minishell.h"

typedef struct s_mhstuct	t_mhstruct;

typedef enum s_token_type
{
	STRING,
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
int		just_whitespace(char *input, int i);
void	skip_all_whitespace(char *input, int *ip, int *jp);
void	increment_i(char *input, int *ip, int *jp, char c);
int		check_quotes_wrapped(char *str);
void	error_msg(char *str, int err_num);
void	check_and_tokenize(t_mhstruct *mh);
void	concatenate_tokens(t_mhstruct *mh);
int		is_special(char c);
int		check_syntax(char *input);
void	handle_dollar(t_mhstruct **mh);

#endif