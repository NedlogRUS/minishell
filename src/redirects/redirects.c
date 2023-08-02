/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:40:51 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/02 14:22:31 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	check_redirects(t_mhstruct *mh)
{
	t_token	*t;

	t = mh->token;
	while (t->next)
	{
		if (t->type == LT || t->type == GT || t->type == D_GT)
			return (1);
		t = t->next;
	}
	if (t->type == LT || t->type == GT || t->type == D_GT)
		return (1);
	return (0);
}

void	check_symbol(t_token *tok, t_token **symbol)
{
	//printf("HERE checking %s\n", tok->data);
	if (tok->type == GT)
		*symbol = tok;
	else if (tok->type == LT)
		*symbol = tok;
	else if (tok->type == D_GT)
		*symbol = tok;
	//printf("HERE now %s\n", (*symbol)->data);
}

void	execute_redirect(t_token *t, t_token *symbol)
{
	(void) t;
	int		fd;
	
	fd = 0;
	if (!(ft_strcmp(symbol->data, "<")))
	{
		fd = open(symbol->next->data, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (!(ft_strcmp(symbol->data, ">")))
	{
		fd = open(symbol->next->data, O_RDONLY);
		dup2(fd, STDOUT_FILENO);
	}
	
}

int		bad_redirect_syntax(t_token *t)
{
	printf("here!!");
	while (t->next)
		t = t->next;
	if (t->type == GT || t->type == LT || t->type == D_GT)
		return (1);
	return (0);
}

void	do_redirects(t_token *t, t_mhstruct *mh)
{
	t_token	*symbol;
	t_token	*tok;

	tok = t;
	symbol = NULL;
	
	if (bad_redirect_syntax(t))
		error_msg("Syntax error near unexpected token", 258, mh);
	else
	{
		while (tok->next && !symbol)
		{
			check_symbol(tok, &symbol);
			tok = tok->next;
		}
		check_symbol(tok, &symbol);
		if (symbol)
		{
			printf("Redirect found %s\n", symbol->data);
			execute_redirect(t, symbol);
		}
	}
}