/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:37:54 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/28 19:03:02 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static int	check_qual(t_token *c)
{
	if ((jw(c->data, 0) && !(c->s_quote || c->d_quote))
		|| ft_strlen(c->data) == 0)
		return (1);
	return (0);
}

static void	change_current(t_token **current, t_token **previous)
{
	*previous = *current;
	*current = (*current)->next;
}

void	remove_empty_nodes(t_mhstruct *mh)
{
	t_token	*token;
	t_token	*c;
	t_token	*previous;

	token = mh->token;
	c = mh->token;
	previous = c;
	while (c->next)
	{
		if (check_qual(c))
		{
			previous->next = c->next;
			token = c->next;
			//free_token(c);
			if (token)
				c = token;
		}
		else
			change_current(&c, &previous);
	}
}

// void	adjust_first(t_mhstruct *mh, t_token *current, t_token *token, t_token *previous)
// {
// 	if ((jw(current->data, 0) && !(token->s_quote || token->d_quote))
// 	|| ft_strlen(current->data) == 0)
// 	{
// 		mh->token = current->next;
// 			free_token(current);
// 		current = mh->token;
// 		token = current;
// 		previous = current;
// 	}
// 	else
// 	{
// 		previous = current;
// 		current = current->next;
// 	}
// }