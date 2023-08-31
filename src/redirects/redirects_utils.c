/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/31 13:39:28 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	set_start(t_token **s, t_token **t, t_token **previous, t_mhstruct **mh)
{
	*s = (*mh)->token;
	while ((*t)->type != D_LT)
		set_prev(previous, t);
}

int	act_red_helper(t_token **t, t_token **p, t_token **start, t_mhstruct **mh)
{
	if ((*t) && ((*t)->type == GT || (*t)->type == LT || (*t)->type == D_GT))
	{
		if (do_dups(t, mh))
		{
			delete_redirs(t, mh, p, start);
			return (1);
		}
		delete_redirs(t, mh, p, start);
	}
	else
		set_prev(p, t);
	return (0);
}

int	act_red(t_token **t, t_token **previous, t_mhstruct **mh)
{
	t_token	*start;

	start = NULL;
	if (check_heredoc(*mh))
	{
		set_start(&start, t, previous, mh);
		if ((*t)->type == D_LT)
		{
			do_here_doc((*t)->next->data, *mh);
			if (do_dups(t, mh))
				return (1);
			delete_redirs(t, mh, previous, &start);
			if (start)
			{
				(*mh)->token = start;
				*t = start;
				*previous = start;
			}
			return (0);
		}
	}
	if (act_red_helper(t, previous, &start, mh))
		return (1);
	return (0);
}

void	delete_here_doc_redirs(t_token **t, t_mhstruct **mh, t_token **previous)
{
	t_token	*tmp;

	if (*t == (*mh)->token)
	{
		(*mh)->token = (*mh)->token->next->next;
		*previous = (*mh)->token;
	}
	else
		(*previous)->next = (*t)->next->next;
	tmp = (*t);
	(*t) = (*t)->next;
	free(tmp->data);
	free(tmp);
	tmp = (*t);
	(*t) = (*t)->next;
	free(tmp->data);
	free(tmp);
}

int	action_justheredoc(t_token **tok, t_token **previous, t_mhstruct **mh)
{
	if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data, *mh);
		delete_here_doc_redirs(tok, mh, previous);
	}
	return (0);
}
