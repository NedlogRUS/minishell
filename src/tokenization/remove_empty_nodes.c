/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:37:54 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/12 17:30:00 by vtavitia         ###   ########.fr       */
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
	t_token	*c;
	t_token	*previous;
	t_token	*tmp;

	c = mh->token;
	tmp = c;
	previous = NULL;
	while (c)
	{
		if (check_qual(c))
		{
			tmp = c;
			c = c->next;
			if (previous)
				previous->next = c;
			else
				mh->token = c;
			free(tmp->data);
			free(tmp);
		}
		else
			change_current(&c, &previous);
	}
}
