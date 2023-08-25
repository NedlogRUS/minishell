/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 22:31:32 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	cr_temp_mh(t_mhstruct **tmp, t_mhstruct **mh, t_token **curr, int *i)
{
	*tmp = malloc(sizeof(t_mhstruct));
	initializer_temp_mh(*tmp, *mh);
	*curr = (*mh)->token;
	while ((*curr)->pi != *i)
		*curr = (*curr)->next;
	copy_to_tmp(tmp, curr);
}

int	do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int i, int lines)
{
	int			pid;
	t_token		*curr;
	t_mhstruct	*tmp;
	int			hd;

	tmp = NULL;
	cr_temp_mh(&tmp, mh, &curr, &i);
	pid = fork();
	if (pid == 0)
	{
		hd = check_heredoc(tmp);
		if (hd)
			do_hd(pipes, i, tmp);
		set_pipe(pipes, i, lines, hd);
		if (ft_tokenlstsize(tmp->token))
			do_redirects(tmp->token, tmp, 0);
		close_pipes(pipes, lines);
		if (ft_tokenlstsize(tmp->token))
			execution_of_commands(tmp);
		exit(g_error);
	}
	free_token_main(tmp);
	free(tmp);
	return (pid);
}

void	do_pipes(t_mhstruct **mh, int lines)
{
	int	i;
	int	pipes[1000][2];
	int	pid[1000];

	i = -1;
	while (++i < lines - 1)
		pipe(pipes[i]);
	i = -1;
	while (++i < lines)
		pid[i] = do_pipe_forks(mh, pipes, i, lines);
	close_pipes(pipes, lines);
	i = -1;
	while (++i < lines)
	{
		if (i == lines - 1)
		{
			waitpid(pid[i], &g_error, 0);
			g_error /= 256;
		}
		else
			waitpid(pid[i], 0, 0);
	}
}	

int	launch_pipes(t_mhstruct **mh)
{
	int		lines;

	lines = assign_pi(mh);
	if (lines > 250)
	{
		pr_err(*mh, 1, gemsg("", (*mh)->emsg[14], "fork: "));
		return (1);
	}
	do_pipes(mh, lines);
	return (0);
}
