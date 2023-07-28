/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:53:52 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/28 18:11:15 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static void	check_and_inc(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
		(*i)++;
	if (input[*i] == '<' && input[*i + 1] == '<')
		(*i)++;
}

static void	do_special_inc(char *input, int *ip, char c)
{
	int	open;
	int	i;

	open = 0;
	i = *ip;
	if (input[i] == '\'' || input[i] == '"')
	{
		c = input[i];
		open = 1;
		while (open && input[i])
		{
			i++;
			if (input[i] == c)
			{
				i++;
				open = 0;
			}
		}
	}
	else
	{
		check_and_inc(input, &i);
		i++;
	}
	*ip = i;
}

void	increment_i(char *input, int *ip, int *jp, char c)
{
	int		i;
	int		j;

	i = *ip;
	j = *jp;
	if (is_special(input[i]))
		do_special_inc(input, &i, c);
	else
	{
		while (!is_special(input[i]) && input[i])
			i++;
	}
	*ip = i;
	*jp = j;
}

t_token	*init_token(char *data, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		perror("Token creation failed\n");
	new_token->data = data;
	new_token->type = type;
	new_token->s_quote = 0;
	new_token->d_quote = 0;
	new_token->next = NULL;
	return (new_token);
}

void	assign_quotes(t_token **new_t, int sq, int dq)
{
	if (sq)
		(*new_t)->s_quote = sq;
	if (dq)
		(*new_t)->d_quote = dq;
}
