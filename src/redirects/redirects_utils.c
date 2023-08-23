/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/14 18:18:55 by vtavitia         ###   ########.fr       */
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

int	action_redirect(t_token **tok, t_token **previous, t_mhstruct **mh, int screen)
{
	if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
	{
		if (do_dups(tok, mh, screen))
			return (1);
		delete_redirs(tok, mh, previous);
	}
	else if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data);
		delete_redirs(tok, mh, previous);
	}
	else
		set_prev(previous, tok);
	return (0);
}

void	run_comms(t_mhstruct *mh, int mark, int in, int screen)
{
	if (mh->token && !mark)
		execution_of_commands(mh);
	dup2(screen, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}
