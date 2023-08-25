/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:40:51 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 11:45:18 by vatche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	check_redir_exist(t_token *t)
{
	if (!t)
		return (0);
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

int	num_of_heredoc(t_token *t)
{
	int	count;

	count = 0;
	if (!t)
		return (0);
	while (t->next)
	{
		if (t->type == D_LT)
			count++;
		t = t->next;
	}
	if (t->type == D_LT)
			count++;
	return (count);
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
int	bad_redirect_syntax2(t_token *t)
{
	while (t->next)
	{
		if (t->type == PIPELINE && t->next->type == PIPELINE)
			return (1);
		t = t->next;
	}
	return (0);
}

int	do_dups(t_token **t, t_mhstruct **mh, int screen)
{
	int	fd;
	(void) screen;
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
			// dup2(screen, STDOUT_FILENO);
			// printf("here dup!!!!!\n");
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


// write rull for < Makefile
int	do_redirects(t_token *t, t_mhstruct *mh, int x)
{
	t_token	*tok;
	t_token	*previous;
	int		screen;
	int		in;
	int		mark;
	(void) x;
	tok = mh->token;
	previous = tok;
	screen = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
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
			// printf("entered\n");
			// print_tokens(mh->token);
			mark = action_redirect(&tok, &previous, &mh, screen, in);
			if (mark)
				break ;
		}
	}
	return (mark);
}

void	do_redirects_pipes(t_token *t, t_mhstruct *mh, int x)
{
	t_token	*tok;
	t_token	*previous;
	int		screen;
	int		in;
	int		mark;
	(void) x;
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
			mark = action_redirect(&tok, &previous, &mh, screen, in);
			if (mark)
				break ;
		}
	}
		
}


void	just_heredoc(t_token *t, t_mhstruct *mh, int x)
{
	t_token	*tok;
	t_token	*previous;
	int		screen;
	// int		in;
	(void) x;
	tok = mh->token;
	previous = tok;
	screen = dup(STDOUT_FILENO);
	// in = dup(STDIN_FILENO);
	if (bad_redirect_syntax(t))
		return (error_msg("Syntax error near unexpected token", 258, mh));

	while(tok && tok->type != D_LT)
		tok = tok->next;
	action_justheredoc(&tok, &previous, &mh, screen);
}

