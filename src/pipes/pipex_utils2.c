/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:12:24 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/31 13:45:10 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	close_upto_i(int pipes[1000][2], int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(pipes[j][1]);
		close(pipes[j][0]);
		j++;
	}
}

void	set_pipe(int pipes[1000][2], int i, int lines, int hd)
{
	if (i == 0)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	else if (i != 0 && i != lines - 1)
	{
		if (!hd)
			dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i - 1][0]);
		close(pipes[i][1]);
	}
	else if (i == lines - 1)
	{
		close(pipes[i - 1][1]);
		if (!hd)
			dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
}
