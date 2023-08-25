/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/24 16:40:21 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	set_prev(t_token **previous, t_token **tok)
{
	*previous = *tok;
	*tok = (*tok)->next;
}

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

int	action_redirect(t_token **tok, t_token **previous, t_mhstruct **mh, int screen, int in)
{
	(void)in;
	if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
	{
		if (do_dups(tok, mh, screen))
			return (1);
		delete_redirs(tok, mh, previous);
	}
	else if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data, *mh);	
		delete_redirs(tok, mh, previous);
		return (0);
	}
	else
		set_prev(previous, tok);
	return (0);
}

int	action_redirect_pipe(t_token **tok, t_token **previous, t_mhstruct **mh, int screen)
{
	if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
	{
		if (do_dups(tok, mh, screen))
			return (1);
		delete_redirs(tok, mh, previous);
	}
	else
		set_prev(previous, tok);
	return (0);
}

int	action_justheredoc(t_token **tok, t_token **previous, t_mhstruct **mh, int screen)
{
	(void) screen;
	if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data, *mh);
		delete_redirs(tok, mh, previous);
	}
	return (0);
}

void	run_comms(t_mhstruct *mh, int mark, int in, int screen)
{
	(void)in;
	(void)screen;
	if (mh->token && !mark)
		execution_of_commands(mh);
	dup2(screen, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}
