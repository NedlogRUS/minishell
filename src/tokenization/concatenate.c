/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:55:40 by vatche            #+#    #+#             */
/*   Updated: 2023/08/28 14:30:59 by vatche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	conc_check(t_token *current)
{
	if (current->next != NULL && (((!(isbreak(current->next->data[0])))
				|| (current->next->s_quote || current->next->d_quote))
			&& ((!(isbreak(current->data[0])))
				|| (current->s_quote || current->d_quote))))
		return (1);
	else
		return (0);
}

int	conc_while_check(t_token *current)
{
	if (current && current->next && (!isbreak(current->data[0])
			|| (current->s_quote || current->d_quote))
		&& (!isbreak(current->next->data[0])
			|| (current->next->s_quote || current->next->d_quote)))
		return (1);
	else
		return (0);
}

void	copy_over(t_token *current, t_token *new, t_token *tmp)
{
	tmp = current->next;
	free(current->data);
	current->data = ft_strdup(new->data);
	current->next = new->next;
	current->s_quote = new->s_quote;
	current->d_quote = new->d_quote;
	free(new->data);
	free(tmp->data);
	free(tmp);
	free(new);
}

void	do_concatenation(t_token *current, t_mhstruct **mh)
{
	t_token	*tmp;
	t_token	*new;
	int		mark;

	tmp = NULL;
	new = NULL;
	mark = 0;
	new = init_token("", NULL_VAL);
	new->data = ft_strjoin(current->data, current->next->data);
	if (current == (*mh)->token)
				mark = 1;
	if (current->s_quote || current->next->s_quote)
		new->s_quote = 1;
	if (current->d_quote || current->next->d_quote)
		new->d_quote = 1;
	if (current->next->next)
		new->next = current->next->next;
	else
		new->next = NULL;
	copy_over(current, new, tmp);
	if (current == NULL)
		return ;
	if (mark)
		(*mh)->token = current;
}

void	concatenate_tokens(t_mhstruct **mh)
{
	t_token	*current;
	t_token	*previous;

	current = (*mh)->token;
	previous = current;
	while (current)
	{
		if (conc_check(current))
		{
			while (conc_while_check(current))
				do_concatenation(current, mh);
			if (current->next)
				move_current(&current, &previous, mh);
		}
		else
		{
			if (previous != current)
				previous->next = current;
			previous = current;
			current = current->next;
		}
	}
}
