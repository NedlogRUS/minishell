/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:50:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/24 13:51:41 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//deletethis
void	print_tokens(t_token *token)
{
	while (token->next != NULL)
	{
		//printf("ADDRESS: %p\tDATA: %s Type: %d Next: %p\n",
			// token, token->data, token->type, (char *)token->next);
			printf("DATA: -%s-  next is %p\n",
			token->data ,  token->next);
		token = token->next;
	}
	// printf("ADDRESS: %p\tDATA: %s Type: %d Next: %p\n",
	// 	token, token->data, token->type, (char *)token->next);
	// 	if (token !=NULL)
			printf("DATA: -%s-\n",
			token->data );
}
/////

static int	do_copy_helper(char *input, int *ip, int *kp, t_token **current)
{
	int		open;
	char	c;

	c = input[*ip];
	open = 1;
	if (c == '\'')
		(*current)->s_quote = 1;
	else if (c == '"')
		(*current)->d_quote = 1;
	(*ip)++;
	while (open)
	{
		if (input[*ip] == c)
		{
			open = 0;
			(*current)->data[*kp] = '\0';
			(*ip)++;
			return (1);
		}
		(*current)->data[*kp] = input[*ip];
		(*ip)++;
		(*kp)++;
	}
	return (0);
}

static void	do_copy(char *input, t_token **current, int *ip, int count)
{
	int		i;
	int		k;

	i = *ip;
	k = 0;
	while (count-- && input[i] != '\0' && !just_whitespace(input, i))
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
	t_token	*current;
	int		i;
	int		j;
	char	c;

	i = *ip;
	j = *jp;
	c = '\0';
	count = 0;
	current = *current_a;
	increment_i(input, &i, &j, c);
	count = i - j;
	current->data = (char *)malloc(sizeof(char) * count + 1);
	i = j;
	do_copy(input, current_a, &i, count);
	*ip = i;
	*jp = i;
}

void	tokenize(t_token *current, char *input)
{
	t_token	*new_t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	skip_all_whitespace(input, &i, &j);
	while (input[i] != '\0')
	{
		tozenize_helper(&current, input, &i, &j);
		if (just_whitespace(input, i) || input[i] == '\0')
		{
			current->next = NULL;
			break ;
		}
		else if (input[i] != '\0')
		{
			new_t = init_token("", NULL_VAL);
			current->next = new_t;
			current = new_t;
		}
	}
}

void	check_and_tokenize(t_mhstruct *mh)
{
	t_token	*start_t;

	if (!check_quotes_wrapped(mh->input) && !check_syntax(mh->input))
	{
		start_t = init_token("", NULL_VAL);
		mh->token = start_t;
		tokenize(start_t, mh->input);
		handle_dollar(&mh);
	//	concatenate_tokens(mh);
		print_tokens(mh->token);
	}
}
