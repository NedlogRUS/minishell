/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_tokens2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:13:42 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/28 17:10:33 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	ft_tokenlstsize(t_token *lst)
{
	int		i;

	i = 0;
	if (!lst || lst->data[0] == '\0')
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	free_token(t_token *token)
{
	free(token->data);
	free(token);
}

void	move_and_free(t_token **token, t_token **tmp)
{
	*token = *tmp;
	*tmp = (*tmp)->next;
	free_token(*token);
}

static void	reassign_start(t_mhstruct *mh, t_token *new_t, int *nodes)
{
	mh->token = new_t;
	(*nodes)--;
}

void	replace_token(t_mhstruct *mh, t_token *new_t, int start, int nodes)
{
	int		count;
	t_token	*token;
	t_token	*previous;
	t_token	*tmp;

	count = 1;
	token = mh->token;
	previous = mh->token;
	while (count <= start && count < ft_tokenlstsize(mh->token))
	{
		if (count == start - 1 || start == 1)
		{
			previous = token;
			tmp = token->next;
			previous->next = new_t;
			if (start == 1)
				reassign_start(mh, new_t, &nodes);
			while (nodes-- > 1)
				move_and_free(&token, &tmp);
			new_t->next = tmp->next;
			break ;
		}
		token = token->next;
		count++;
	}
}
