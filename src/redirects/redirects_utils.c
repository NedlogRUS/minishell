/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 22:13:18 by vtavitia         ###   ########.fr       */
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

int	act_red(t_token **t, t_token **previous, t_mhstruct **mh)
{
	t_token	*start;

	start = NULL;
	if (check_heredoc(*mh))
	{
		start = (*mh)->token;
		while ((*t)->type != D_LT)
			set_prev(previous, t);
		if ((*t)->type == D_LT)
		{
			do_here_doc((*t)->next->data, *mh);
			do_dups(t, mh);
			delete_redirs(t, mh, previous, &start);
			return (0);
		}
	}
	//(*t) = start;
	printf("tok is %s previous is %s\n", (*t)->data, (*previous)->data);
	exit(1);
	if ((*t) && ((*t)->type == GT || (*t)->type == LT || (*t)->type == D_GT))
	{
		printf("here1\n");
		if (do_dups(t, mh))
			return (1);
		delete_redirs(t, mh, previous, &start);
	}
	else
	{
		printf("here2 %s\n", (*t)->data);
		set_prev(previous, t);
	}
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
