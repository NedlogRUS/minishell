/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:50:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/14 16:22:10 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static void	do_copy(char *input, t_token **current, int *ip, int count)
{
	int		i;
	int		k;

	i = *ip;
	k = 0;
	while (count-- && input[i] != '\0' && !jw(input, i))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (do_copy_helper(input, &i, &k, current) == 1)
			{
				*ip = i;
				return ;
			}
		}
		else
		{
			(*current)->data[k] = input[i];
			i++;
			k++;
		}
	}
	(*current)->data[k] = '\0';
	*ip = i;
}

static void	tozenize_helper(t_token **current_a, char *input, int *ip, int *jp)
{
	int		count;
	int		i;
	int		j;
	char	c;

	free((*current_a)->data);
	i = *ip;
	j = *jp;
	c = '\0';
	count = 0;
	increment_i(input, &i, &j, c);
	count = i - j;
	(*current_a)->data = (char *)malloc(sizeof(char) * count + 1);
	i = j;
	if (count)
		do_copy(input, current_a, &i, count);
	*ip = i;
	*jp = i;
}

void	tokenize_helper2(t_token **curr, t_token **new_t, char *input, int *i)
{
	int		len;

	len = ft_strlen(input);
	if ((jw(input, *i) || input[*i] == '\0') && *i < len)
	{
		(*curr)->next = NULL;
		return ;
	}
	else if (*i >= len)
	{
		*curr = NULL;
		return ;
	}
	else if (input[*i] != '\0' && *i < len)
	{
		*new_t = init_token("", NULL_VAL);
		free((*new_t)->data);
		(*curr)->next = *new_t;
		*curr = *new_t;
	}
}

void	tokenize( t_mhstruct **mh, char *input)
{
	t_token	*current;
	t_token	*new_t;
	int		i;
	int		j;

	new_t = NULL;
	current = init_token("", NULL_VAL);
	free(current->data);
	(*mh)->token = current;
	i = 0;
	j = 0;
	if (jw(input, i) || input[i] == '\0')
	{
		free((*mh)->token);
		((*mh)->token = NULL);
		return ;
	}
	while (input[i] != '\0' && i < (int)ft_strlen(input))
	{
		tozenize_helper(&current, input, &i, &j);
		tokenize_helper2(&current, &new_t, input, &i);
		if (jw(input, i))
			break ;
	}
}

void	check_and_tokenize(t_mhstruct *mh)
{
	char	c;

	c = '\0';
	if (check_quotes_wrapped(mh->input))
		error_msg("Syntax error -check quotes", 1, mh);
	else if (check_bad_specials(mh->input))
		error_msg("Syntax error - near unexpected token", 1, mh);
	else if (!check_quotes_wrapped(mh->input) && (!check_syntax(mh->input, mh)))
	{
		clean_start(mh, c);
		tokenize(&mh, mh->input);
		if (mh->token && mh->token->data && ft_strlen(mh->token->data))
			handle_dollar(&mh);
		concatenate_tokens(&mh);
		if (ft_tokenlstsize(mh->token) >= 2)
			remove_empty_nodes(mh);
		if (mh->token && ft_tokenlstsize(mh->token))
			classify_tokens(mh);
	}
}

// // //deletethis
void	print_tokens(t_token *token)
{
		printf("Printing tokens\n------\n");
		if (token)
		{
			while (token)
			{
					printf("DATA: -%s- type is %d\n", token->data, token->type);
					token = token->next;				
			}
		}
		// if (ft_tokenlstsize(token) == 1 && token)
		// 	printf("DATA: -%s- type is %d\n",
		// 		token->data, token->type);
}