/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:40:51 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/04 15:36:19 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	check_redir_exist(t_token *t)
{
	while (t->next)
	{
		if (t->type == GT || t->type == LT
			|| t->type == D_GT || t->type == D_LT)
			return (1);
		t = t->next;
	}
	if (t->type == GT || t->type == LT || t->type == D_GT || t->type == D_LT)
		return (1);
	return (0);
}

int	bad_redirect_syntax(t_token *t)
{
	if (t->type == PIPELINE)
		return (1);
	while (t->next)
		t = t->next;
	if (t->type == GT || t->type == LT || t->type == D_GT || t->type == D_LT
		|| t->type == PIPELINE)
		return (1);
	return (0);
}

int	do_dups(t_token **t, t_mhstruct **mh)
{
	int	fd;

	if ((*t)->type == GT)
		do_gt(t);
	else if ((*t)->type == D_GT)
		do_d_gt(t);
	else if ((*t)->type == LT)
	{
		if (!access(((*t)->next->data), R_OK))
		{
			fd = open((*t)->next->data, O_RDONLY, 0644);
			dup2(fd, STDIN_FILENO);
		}
		else
		{
			error_msg("No such file or directory", 1, *mh);
			return (1);
		}
	}
	return (0);
}

void	delete_redirs(t_token **t, t_mhstruct **mh, t_token **previous)
{
	t_token	*temp;

	if (*t == (*mh)->token)
	{
		(*mh)->token = (*mh)->token->next->next;
		*previous = (*mh)->token;
	}
	else
		(*previous)->next = (*t)->next->next;
	temp = (*t)->next;
	free_token(*t);
	*t = temp;
	temp = (*t)->next;
	free_token(*t);
	*t = temp;
}

void	do_redirects(t_token *t, t_mhstruct *mh)
{
	t_token	*tok;
	t_token	*previous;
	int		screen;
	int		in;
	int		mark;

	tok = mh->token;
	previous = tok;
	screen = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
	mark = 0;
	if (bad_redirect_syntax(t))
		return (error_msg("Syntax error near unexpected token", 258, mh));
	if (check_redir_exist(mh->token))
	{
		while (tok)
		{
			mark = action_redirect(&tok, &previous, &mh);
			if (mark)
				break ;
		}
	}
	run_comms(mh, mark, in, screen);
}
