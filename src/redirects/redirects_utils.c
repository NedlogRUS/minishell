/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/26 19:46:29 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	do_gt(t_token **t)
{
	int	fd;

	fd = open((*t)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	dup2(fd, STDOUT_FILENO);
}

void	do_d_gt(t_token **t)
{
	int	fd;

	fd = open((*t)->next->data, O_CREAT | O_APPEND | O_WRONLY, 0644);
	dup2(fd, STDOUT_FILENO);
}

int	act_red(t_token **tok, t_token **previous, t_mhstruct **mh)
{
	t_token	*start;

	if (check_heredoc(*mh))
	{
		start = *tok;
		while ((*tok)->type != D_LT)
			set_prev(previous, tok);
		if ((*tok)->type == D_LT)
		{
			do_here_doc((*tok)->next->data, *mh);
			do_dups(tok, mh);
			delete_redirs(tok, mh, previous);
			*tok = start;
			return (0);
		}
	}
	if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
	{
		if (do_dups(tok, mh))
			return (1);
		delete_redirs(tok, mh, previous);
	}
	else
		set_prev(previous, tok);
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
