/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:39:00 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/26 19:20:06 by vtavitia         ###   ########.fr       */
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

void	delete_here_doc_redirs(t_token **t, t_mhstruct **mh, t_token **previous)
{
	t_token	*tmp;
// printf("\n MH is %s \n", (*mh)->token->data);
// 	printf("\n previous is %s and current is %s\n", (*previous)->data, (*t)->data);
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
	// printf("\n MH is %s \n", (*mh)->token->data);
	// printf("\n here previous is %s and current is %s\n", (*previous)->data, (*tok)->data);
	if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data, *mh);
		delete_here_doc_redirs(tok, mh, previous);
	}
	// print_tokens((*mh)->token);
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