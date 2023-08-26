/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:40:51 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/26 19:27:19 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

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
	// else
	// {
	// 	dup2((*mh)->in, STDIN_FILENO);
	// 	dup2((*mh)->screen, STDOUT_FILENO);
	// }
	return (0);
}

void	delete_redirs(t_token **t, t_mhstruct **mh, t_token **previous)
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

int	do_redirects(t_token *t, t_mhstruct *mh, int x)
{
	t_token	*tok;
	t_token	*previous;
	int		mark;


	tok = mh->token;
	previous = tok;
	mark = 0;
	if (bad_redirect_syntax(t))
	{
		error_msg("Syntax error near unexpected token", 258, mh);
		return (258);
	}
	if (check_redir_exist(mh->token))
	{
		while (check_redir_exist(mh->token))
		{
			mark = act_red(&tok, &previous, &mh, x);
			// dup2(mh->in, STDIN_FILENO);
			// dup2(mh->screen, STDOUT_FILENO);
			if (mark)
				break ;
		}
	}
	return (mark);
}


void	just_heredoc(t_token **t, t_mhstruct **mh)
{
	t_token	*tok;
	t_token	*previous;
	t_token	*start;
	start = (*mh)->token;
	// print_tokens(start);
	tok = (*mh)->token;
	previous = tok;
	if (bad_redirect_syntax(*t))
		return (error_msg("Syntax error near unexpected token", 258, *mh));
	while (tok && tok->type != D_LT)
	{
		previous = tok;
		tok = tok->next;
	}
	action_justheredoc(&tok, &previous, mh);
	//(*mh)->token = start;
		// print_tokens((*mh)->token);
		// exit(1);
}
