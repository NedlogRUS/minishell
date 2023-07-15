/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:50:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/15 17:18:03 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(char *data, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		perror("Token creation failed\n");
	new_token->data = data;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static void	tozenize_helper(t_token **current_a, char *input, int *ip, int *jp)
{
	int		count;
	t_token	*current;
	int		k;
	int		i;
	int		j;

	k = 0;
	i = *ip;
	j = *jp;
	count = 0;
	current = *current_a;
	increment_i(input, &i);
	count = i - j;
	current->data = (char *)malloc(sizeof(char) * count + 1);
	i = j;
	while (count-- && input[i] != '\0' && !just_whitespace(input, i))
	{
		current->data[k] = input[i];
		i++;
		k++;
	}
	current->data[k] = '\0';
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

	if (check_quotes_wrapped(mh->input) == 0)
	{
		start_t = init_token("", NULL_VAL);
		mh->token = start_t;
		tokenize(start_t, mh->input);
	}
}
