/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_tokens3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:23:49 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/28 17:22:51 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	parse_start(t_mhstruct *mh)
{
	t_token	*current;
	t_token	*token;

	token = mh->token;
	if ((!ft_strlen(token->data) && token)
		|| (ft_strlen(token->data) == 1 && token->data[0] == ' '))
	{
		while ((!ft_strlen(token->data) && token)
			|| (ft_strlen(token->data) == 1 && token->data[0] == ' '))
		{
			current = token;
			if (token->next)
			{
				token = token->next;
				free_token(current);
				mh->token = token;
			}
			else
				break ;
		}
	}
}

void	count_chars_helper(t_token **token, int *count, int *start)
{
	while (*count < *start)
	{
		if ((*token)->next)
			*token = (*token)->next;
		(*count)++;
	}
}

int	count_chars(t_mhstruct *mh, int start, int nodes, int lst_size)
{
	int		count;
	int		i;
	int		chars;
	t_token	*token;

	(void) lst_size;
	count = 1;
	i = 0;
	chars = 0;
	token = mh->token;
	count_chars_helper(&token, &count, &start);
	while (nodes--)
	{
		while (token->data[i])
		{
			chars++;
			i++;
		}
		if (token->next)
			token = token->next;
		i = 0;
	}
	return (chars);
}
