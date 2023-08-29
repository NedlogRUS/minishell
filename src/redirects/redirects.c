/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:40:51 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 22:05:54 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	set_prev(t_token **previous, t_token **tok)
{
	if (!(*previous || *tok))
		return ;
	*previous = *tok;
	//	printf("here\n");
	if ((*tok) && (*tok)->next)
		*tok = (*tok)->next;
	else
		*tok = *previous;
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

void	delete_redirs(t_token **t, t_mhstruct **mh, t_token **p, t_token **s)
{
	t_token	*tmp;
(void)s;
	// if ((*t == *s && *t == (*mh)->token && (*t)->next->next))
	// 	*s = (*t)->next->next;
	if (*t == (*mh)->token)
	{
		(*mh)->token = (*mh)->token->next->next;
		*p = (*mh)->token;
	}
	else
		(*p)->next = (*t)->next->next;
	tmp = (*t);
	(*t) = (*t)->next;
	free(tmp->data);
	free(tmp);
	tmp = (*t);
	(*t) = (*t)->next;
	free(tmp->data);
	free(tmp);
}

int	do_redirects(t_token *t, t_mhstruct *mh)
{
	t_token	*tok;
	t_token	*previous;
	int		mark;

	tok = mh->token;
	previous = tok;
	mark = 0;
	if (bad_redirect_syntax(t))
	{
		pr_err(mh, 2, gemsg("", mh->emsg[15], ""));
		return (258);
	}
	if (check_redir_exist(mh->token))
	{
		while (check_redir_exist(mh->token))
		{
		//	printf("tok is %s previous is %s\n", (tok)->data, (previous)->data);
			mark = act_red(&tok, &previous, &mh);
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

	tok = (*mh)->token;
	previous = tok;
	if (bad_redirect_syntax(*t))
		return pr_err(*mh, 2, gemsg("", (*mh)->emsg[15], ""));
	while (tok && tok->type != D_LT)
	{
		previous = tok;
		tok = tok->next;
	}
	action_justheredoc(&tok, &previous, mh);
}
