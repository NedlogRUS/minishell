/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:11:30 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/05 19:01:25 by vatche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbreak(char c)
{
	char	*special;
	int		i;

	special = "|<>; ";
	i = 0;
	while (special[i] != '\0')
	{
		if (special[i] == c || special[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	find_range(t_mhstruct *mh, int *start, int *nodes)
{
	t_token	*token;

	token = mh->token;
	while (token && !(*nodes))
	{
		(*start)++;
		if (token->next)
		{
			if ((!isbreak(token->data[0]) || (token->s_quote || token->d_quote))
				&& (!isbreak(token->next->data[0])
					|| (token->next->s_quote || token->next->d_quote)))
				(*nodes)++;
			while ((token->next) && ((!isbreak(token->data[0])
						|| (token->s_quote || token->d_quote))
					&& (!isbreak(token->next->data[0])
						|| (token->next->s_quote || token->next->d_quote))))
			{
				(*nodes)++;
				token = token->next;
			}
		}
		token = token->next;
	}
	return (*nodes);
}

void	begin_cat_helper(t_token *token, t_token *new_t, int nodes)
{
	int		i;
	int		k;
	int		sq;
	int		dq;

	i = 0;
	k = 0;
	sq = token->s_quote;
	dq = token->d_quote;
	while (nodes--)
	{	
		while (token->data[i])
		{
			new_t->data[k] = token->data[i];
			i++;
			k++;
		}
		token = token->next;
		i = 0;
	}
	if (sq || dq)
		assign_quotes(&new_t, sq, dq);
	new_t->data[k] = '\0';
}

void	begin_cat(t_mhstruct *mh, int start, int nodes, int lst_size)
{
	int		count;
	t_token	*new_t;
	t_token	*token;

	count = count_chars(mh, start, nodes, lst_size);
	token = mh->token;
	new_t = init_token("", NULL_VAL);
	new_t->data = (char *)malloc(sizeof(char) * count + 1);
	if (!new_t->data)
		error_msg("Concatenation Failed\n", 1, mh);
	count = 0;
	while (count++ < start - 1 && count < lst_size)
		token = token->next;
	begin_cat_helper(token, new_t, nodes);
	replace_token(mh, new_t, start, nodes);
	//free(token->data);
}

void	concatenate_tokens(t_mhstruct *mh)
{
	int		lst_size;
	int		start;
	int		nodes;

	start = 0;
	nodes = 0;
	parse_start(mh);
	lst_size = ft_tokenlstsize(mh->token);
	while (find_range(mh, &start, &nodes))
	{
		find_range(mh, &start, &nodes);
		if (nodes)
			begin_cat(mh, start, nodes, lst_size);
		start = 0;
		nodes = 0;
	}
}
