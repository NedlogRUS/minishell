/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ms_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:10:29 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 20:53:52 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	c_w(t_mhstruct **mh, int i)
{
	t_token	*current;
	int		words;

	words = 0;
	current = (*mh)->token;
	while (current && current->pi != i)
		current = current->next;
	while (current && current->pi == i)
	{
		words++;
		current = current->next;
	}
	return (words);
}

int	c_ch(t_mhstruct **mh, int i)
{
	t_token	*current;
	int		j;
	int		count;

	j = 0;
	count = 0;
	current = (*mh)->token;
	while (current && current->pi != i)
		current = current->next;
	while (current && current->pi == i)
	{
		while (current->data[j])
		{
			count++;
			j++;
		}
		j = 0;
		current = current->next;
	}
	return (count);
}

void	close_pipes(int pipes[1000][2], int lines)
{
	int	i;

	i = 0;
	while (i < lines - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	assign_pi(t_mhstruct **mh)
{
	t_token	*current;
	int		idx;

	current = (*mh)->token;
	idx = 0;
	while (current)
	{
		while (current->type != PIPELINE && current)
		{
			current->pi = idx;
			if (current->next)
				current = current->next;
			else
				break ;
		}
		if (current)
			current = current->next;
		idx++;
	}	
	return (idx);
}

int	get_args_size_pipes(t_token *tmp)
{
	int		i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp && tmp->type != PIPELINE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
