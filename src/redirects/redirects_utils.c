/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/26 17:21:33 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"


void	set_prev(t_token **previous, t_token **tok)
{
	if (!(*previous || *tok))
		return ;
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

int	act_red(t_token **tok, t_token **previous, t_mhstruct **mh, int x)
{
	(void) x;
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
			// print_tokens((*))
			// if ((*mh)->token)
			// 	*tok = (*mh)->token;
			return (0);
		}
	}
	if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
	{
		if (do_dups(tok, mh))
			return (1);
		delete_redirs(tok, mh, previous);
		// if ((*mh)->token)
		// 	*tok = (*mh)->token;
	}
	else
		set_prev(previous, tok);
	return (0);
}

// working with pipes but not cat Makefile echo << a > file 
// int	act_red(t_token **tok, t_token **previous, t_mhstruct **mh)
// {
	
// 	if ( ((*tok)->type == GT
// 		|| (*tok)->type == LT || (*tok)->type == D_GT))
// 	{
// 		//printf("Second\n");
// 		if (do_dups(tok, mh))
// 			return (1);
// 		delete_redirs(tok, mh, previous);
// 	}
// 	else if ((*tok)->type == D_LT)
// 	{
// 		//printf("FIRST previous is %s\n", (*previous)->data);
// 		do_here_doc((*tok)->next->data, *mh);
// 		(do_dups(tok, mh));
// 		delete_redirs(tok, mh, previous);
// 		if ((*mh)->token)
// 			*tok = (*mh)->token;
// 		return (0);
// 	}
// 	else
// 		set_prev(previous, tok);
// 	return (0);
// }
int	action_justheredoc(t_token **tok, t_token **previous, t_mhstruct **mh)
{
	if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data, *mh);
		delete_redirs(tok, mh, previous);
	}
	return (0);
}

// cat Makefile echo << a > file working but not piping
// int	act_red(t_token **tok, t_token **previous, t_mhstruct **mh)
// {
// 	if (!check_heredoc(*mh))
// 	{
// 		if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
// 		{
// 			if (do_dups(tok, mh))
// 				return (1);
// 			delete_redirs(tok, mh, previous);
// 			// if ((*mh)->token)
// 			// 	*tok = (*mh)->token;
// 		}
// 	}
// 	else if ((*tok)->type == D_LT && check_heredoc(*mh))
// 	{
// 		do_here_doc((*tok)->next->data, *mh);
// 		// if (!check_heredoc(*mh))
// 			do_dups(tok, mh);
// 		delete_redirs(tok, mh, previous);
// 		// if ((*mh)->token)
// 		// 	*tok = (*mh)->token;
// 		return (0);
// 	}
// 	else
// 		set_prev(previous, tok);
// 	return (0);
// }

int	heredoc_first(t_token **tok, t_token **previous, t_mhstruct **mh)
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
			// print_tokens((*))
			// if ((*mh)->token)
			// 	*tok = (*mh)->token;
			return (0);
		}
	}
	else
		set_prev(previous, tok);
	return (0);
}