/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 21:31:39 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	g_error = 0;

// handle error cat < Makefile > | wc

void	set_pipe(int pipes[1000][2], int i, int lines, int hd)
{
	if (i == 0)
	{
		close(pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	else if (i != 0 && i != lines - 1)
	{
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

static void	copy_to_tmp_helper(t_mhstruct **tmp, t_token **new)
{
	(*tmp)->token->next = *new;
	(*tmp)->token = (*tmp)->token->next;
}

void	copy_to_tmp(t_mhstruct *tmp, t_token *curr)
{
	t_token	*start;
	t_token	*new;

	new = NULL;
	tmp->token = NULL;
	while (curr && curr->type != PIPELINE)
	{
		new = init_token("", NULL_VAL);
		new->data = ft_strdup(curr->data);
		new->pi = curr->pi;
		new->type = curr->type;
		if (curr->next == NULL || curr->next->type == PIPELINE)
			new->next = NULL;
		if (tmp->token == NULL)
		{
			tmp->token = new;
			start = tmp->token;
		}
		else
			copy_to_tmp_helper(&tmp, &new);
		curr = curr->next;
	}
	tmp->token = start;
}

void	initializer_temp_mh( t_mhstruct *tmp, t_mhstruct *mh)
{
	tmp->token = NULL;
	tmp->env = mh->env;
	tmp->er_num = 0;
	tmp->mh_pid = mh->mh_pid;
	tmp->emsg = mh->emsg;
	tmp->in = dup(STDIN_FILENO);
	tmp->screen = dup(STDOUT_FILENO);
	tmp->dolmark = 0;
	tmp->t_size = 0;
	tmp->th_i = 0;
}

int	check_heredoc(t_mhstruct *mh)
{
	t_token	*curr;

	if (!mh->token->data)
		return (0);
	curr = mh->token;
	while (curr)
	{
		if (curr->type == D_LT)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int i, int lines, int screen)
{
	int		pid;
	t_token	*curr;
	(void) screen;

	(void) lines;
	(void) pipes;
	t_mhstruct *tmp;
	tmp = NULL;
	tmp = malloc(sizeof(t_mhstruct));
	initializer_temp_mh(tmp, *mh);
	curr = (*mh)->token;	
	while ( curr->pi != i)
		curr = curr->next;

	copy_to_tmp(tmp, curr);
	pid = fork();
	if (pid == 0)
	{
		int hd = check_heredoc(tmp);

		if (hd)
		{
			while ( check_heredoc(tmp))
				just_heredoc(tmp->token, tmp);
		}
		set_pipe(pipes, i, lines, hd);
		if (ft_tokenlstsize(tmp->token))
			do_redirects(tmp->token, tmp, 0);
		close_pipes(pipes, lines);
		if (ft_tokenlstsize(tmp->token))
			execution_of_commands(tmp);
		exit(GLOBAL_ERROR);
	}
	free_token_main(tmp);
	free(tmp);
	return (pid);
}

void	do_pipes(t_mhstruct **mh, int lines)
{
	int	screen = dup(STDOUT_FILENO);
	int	i;
	int	pipes[1000][2];

	int pid[1000];
	i = 0;
	while (i < lines - 1) 
	{
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	while (i < lines)
	{
		pid[i] = do_pipe_forks(mh, pipes, i, lines, screen);
		i++;
	}	
	close_pipes(pipes, lines);
	i = 0;
	while (i < lines)
	{
		if (i == lines - 1)
		{
			waitpid(pid[i], &GLOBAL_ERROR, 0);
			GLOBAL_ERROR /= 256;
		}
		else
			waitpid(pid[i], 0, 0);
		i++;
	}
}
	

int	launch_pipes(t_mhstruct **mh)
{
	int		lines;
	char	**grid = NULL;
	lines = assign_pi(mh);
	if (lines > 250)
	{
		pr_err(*mh, 1, gemsg("", (*mh)->emsg[14], "fork: "));
		return (1);
	}
	grid = (char **)malloc(sizeof(char **) * (lines + 1));
	if (!grid)
		return (1);
	do_pipes(mh, lines);
	return (0);
}

