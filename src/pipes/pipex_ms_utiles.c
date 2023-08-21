/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ms_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:10:29 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/21 15:11:35 by vtavitia         ###   ########.fr       */
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

void	copy_to_grid(t_mhstruct **mh, int i, char **grid)
{
	t_token	*current;
	int		j;
	int		k;
	
	current = (*mh)->token;
	k = 0;
	j = 0;
	while (current && current->pi != i)
		current = current->next;
	while (current && current->pi == i)
	{
		while (current->data[j])
		{
			grid[i][k] = current->data[j];
			j++;
			k++;
		}
		if (current->next && current->next->pi == i)
		{
			grid[i][k] = ' ';
			k++;
		}
		j = 0;
		current = current->next;
	}
	grid[i][k] = '\0';
}

void	create_grid(char **grid, int lines, t_mhstruct **mh)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		grid[i] = (char *)malloc(sizeof(char) * (c_ch(mh, i) +  c_w(mh, i) + 1));
		if (!grid)
			return ;
		copy_to_grid(mh, i, grid);
		i++;
	}
	grid[lines] = NULL;
	// free grid
}


void	c_pipes(int pipes[1000][2] , int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}


int	check_redir_exist_pipe(t_token *t)
{
	while (t && t->next->type != PIPELINE)
	{
		if (t->type == GT || t->type == LT
			|| t->type == D_GT || t->type == D_LT)
			return (1);
		t = t->next;
	}
	// if (t->type == GT || t->type == LT || t->type == D_GT || t->type == D_LT)
	// 	return (1);
	return (0);
}