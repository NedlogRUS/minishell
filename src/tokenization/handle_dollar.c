/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:40:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 19:56:08 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	handle_dollar_helper2(t_token **prev, t_token **curr)
{
	if ((*curr)->next)
	{
		*curr = (*curr)->next;
		*prev = *curr;
	}
	else if ((*curr)->next == NULL)
	{
		free((*curr)->data);
		free(*curr);
		*curr = NULL;
		(*prev)->next = *curr;
	}
}

void	hd_helper(t_mhstruct **mh, t_token **p, t_token **c, t_token **t)
{
	if (*p == *c && (*mh)->dolmark && ((*c)->next == NULL))
	{
		free((*c)->data);
		free(*c);
		(*mh)->token = NULL;
		return ;
	}
	else if (*p == *c && (*mh)->dolmark && ((*c)->next != NULL))
	{
		*t = (*c)->next;
		free((*c)->data);
		free((*mh)->token);
		*c = *t;
		*p = *c;
		(*mh)->token = *c;
		(*mh)->dolmark = 0;
	}
	else
		handle_dollar_helper2(p, c);
}

void	handle_dollar(t_mhstruct **mh)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*tmp;

	tmp = NULL;
	(*mh)->dolmark = is_there_dollar((*mh)->token->data);
	curr = (*mh)->token;
	prev = curr;
	while (curr)
	{
		if (curr == (*mh)->token)
		(*mh)->dolmark = is_there_dollar((*mh)->token->data);
		if (is_there_dollar(curr->data) && !(curr->s_quote))
		{
			convert_dollars(&curr, *mh);
			if (!ft_strlen(curr->data) && !(curr->s_quote || curr->d_quote))
				hd_helper(mh, &prev, &curr, &tmp);
			else if (curr->next)
				update_car(&prev, &curr);
		}
		else
			update_car(&prev, &curr);
	}
}
