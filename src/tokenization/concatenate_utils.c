/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:37:15 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/10 17:30:23 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	isbreak(char c)
{
	char	*special;
	int		i;

	special = "|<>; ";
	i = 0;
	while (special[i] != '\0')
	{
		if (special[i] == c || special[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_tokenlstsize(t_token *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	free_token(t_token *token)
{
	if (token->data && ft_strlen(token->data))
		free(token->data);
	token = NULL;
}

void	move_current(t_token *current, t_token *previous, t_mhstruct **mh)
{
	if (current != (*mh)->token)
		previous->next = current;
	previous = current;
	current = current->next;
}
