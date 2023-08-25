/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:11:04 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 20:12:30 by vtavitia         ###   ########.fr       */
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
