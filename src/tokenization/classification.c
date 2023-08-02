/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:43:32 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/31 14:40:36 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static int	check_builtin(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "export"))
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
	else if (!(ft_strcmp(t->data, "<")))
		t->type = LT;
	else if (!(ft_strcmp(t->data, "<<")))
		t->type = D_LT;
	else if (!(ft_strcmp(t->data, ">")))
		t->type = GT;
	else if (!(ft_strcmp(t->data, ">>")))
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

	// STRING, 0 
	// BUILTIN, 1
	// PIPELINE, 2
	// GT, 3 
	// LT, 4
	// D_GT, 5
	// D_LT, 6
	// SEMICOL, 7
	// NULL_VAL 8