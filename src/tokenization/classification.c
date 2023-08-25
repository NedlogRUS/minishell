/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:43:32 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 23:26:49 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static int	check_builtin(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	else if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "export"))
		|| !(ft_strcmp(str, "cd")) || !(ft_strcmp(str, "unset"))
		|| !(ft_strcmp(str, "env")) || !(ft_strcmp(str, "exit"))
		|| !(ft_strcmp(str, "pwd")))
		return (1);
	return (0);
}

static void	assign_type(t_token *t)
{
	if (check_builtin(t->data))
			t->type = BUILTIN;
	else if (!(ft_strcmp(t->data, "<")) && !(t->s_quote || t->d_quote))
		t->type = LT;
	else if (!(ft_strcmp(t->data, "<<")) && !(t->s_quote || t->d_quote))
		t->type = D_LT;
	else if (!(ft_strcmp(t->data, ">")) && !(t->s_quote || t->d_quote))
		t->type = GT;
	else if (!(ft_strcmp(t->data, ">>")) && !(t->s_quote || t->d_quote))
		t->type = D_GT;
	else if (!(ft_strcmp(t->data, "|")) && !(t->s_quote || t->d_quote))
		t->type = PIPELINE;
	else
		t->type = STRING;
}

void	classify_tokens(t_mhstruct *mh)
{
	t_token	*t;

	t = mh->token;
	while (t->next)
	{
		assign_type(t);
		t = t->next;
	}
	assign_type(t);
}

int	check_last_type(t_mhstruct *mh)
{
	if (!mh->token)
		return (1);
	while (mh->token->next != NULL)
		mh->token = mh->token->next;
	if (mh->token)
	{
		if (mh->token->type == LT || mh->token->type == D_LT
			|| mh->token->type == GT || mh->token->type == D_GT
			|| mh->token->type == PIPELINE)
			return (1);
	}
	return (0);
}
