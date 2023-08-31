/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/31 14:05:23 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	do_redirects_pipe(t_token **t, t_mhstruct **mh)
{
	t_token	*tok;
	t_token	*previous;
	int		mark;

	tok = (*mh)->token;
	previous = tok;
	mark = 0;
	if (bad_redirect_syntax(*t))
	{
		error_msg("Syntax error near unexpected token", 258, *mh);
		return (258);
	}
	if (check_redir_exist((*mh)->token))
	{
		while (check_redir_exist((*mh)->token))
		{
			mark = act_red(&tok, &previous, mh);
			if (mark)
				break ;
		}
	}
	return (mark);
}

void	close_reset_dups(t_mhstruct **mh, int pipes[1000][2], int lines)
{
	close_pipes(pipes, lines);
	dup2((*mh)->in, STDIN_FILENO);
	dup2((*mh)->screen, STDOUT_FILENO);
	exit(g_error);
}

int	do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int i, int lines)
{
	int			pid;
	t_token		*curr;
	t_mhstruct	*tmp;

	tmp = NULL;
	cr_temp_mh(&tmp, mh, &curr, &i);
	pid = fork();
	if (pid == 0)
	{
		if (check_heredoc(tmp))
			do_hd(pipes, i, &tmp);
		set_pipe(pipes, i, lines, 0);
		if (ft_tokenlstsize(tmp->token))
		{
			if (do_redirects_pipe(&(tmp->token), &tmp))
				close_reset_dups(mh, pipes, lines);
		}
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
	if (bad_redirect_syntax((*mh)->token) || bad_redirect_syntax2((*mh)->token))
	{
		pr_err((*mh), 258, gemsg("", (*mh)->emsg[15], ""));
		return (1);
	}
	else
		do_pipes(mh, lines);
	return (0);
}
