/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/26 19:17:31 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

// // //deletethis
void	print_tokens(t_token *token)
{
		printf("Printing tokens\n------\n");
		if (token)
		{
			while (token)
			{
					printf("DATA: -%s- pi is %d\n", token->data, token->pi);
					token = token->next;				
			}
		}
		// if (ft_tokenlstsize(token) == 1 && token)
		// 	printf("DATA: -%s- type is %d\n",
		// 		token->data, token->type);
}

void	cr_temp_mh(t_mhstruct **tmp, t_mhstruct **mh, t_token **curr, int *i)
{
	*tmp = malloc(sizeof(t_mhstruct));
	initializer_temp_mh(*tmp, *mh);
	*curr = (*mh)->token;
	while ((*curr)->pi != *i)
		*curr = (*curr)->next;
	copy_to_tmp(tmp, curr);
}

void	finalise_heredoc_pipes(t_mhstruct *mh, int *hdpipe)
{
	close(hdpipe[1]);
	if (num_of_heredoc(mh->token) >= 2)
	{
		close(hdpipe[0]);
		dup2(mh->in, STDIN_FILENO);
	}
	dup2(hdpipe[0], STDIN_FILENO);
	close(hdpipe[0]);
}

void	do_here_doc_pipes(char *lim, t_mhstruct *mh)
{
	int		hdpipe[2];
	char	*buffer;

	if (pipe(hdpipe) == -1)
		error_msg2("Error\nPipe Creation Failed\n");
	while (1)
	{
		buffer = NULL;
		buffer = readline(">");
		if (buffer != NULL)
		{
			if (!ft_strcmp(buffer, lim))
			{
				free(buffer);
				break ;
			}
			write(hdpipe[1], buffer, ft_strlen(buffer));
			write(hdpipe[1], "\n", 1);
			free(buffer);
		}
		if (buffer == NULL)
			break ;
	}
	finalise_heredoc_pipes(mh, hdpipe);
}

int	act_red_pipes(t_token **tok, t_token **previous, t_mhstruct **mh)
{
	t_token	*start;

	if (check_heredoc(*mh))
	{
		start = *tok;
		while ((*tok)->type != D_LT)
			set_prev(previous, tok);
		if ((*tok)->type == D_LT)
		{
			do_here_doc((*tok)->next->data, *mh);
			do_dups(tok, mh);
			delete_redirs(tok, mh, previous);
			*tok = start;
			return (0);
		}
	}
	else if ((*tok)->next)
		set_prev(previous, tok);
	return (0);
}

void	pipe_heredoc(t_mhstruct **tmp)
{
	t_token	*tok;
	t_token	*previous;

	tok = (*tmp)->token;
	previous = tok;
	if (check_redir_exist((*tmp)->token))
	{
		while (check_redir_exist((*tmp)->token))
			act_red_pipes(&tok, &previous, tmp);
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

int	do_redirects_pipe(t_token **t, t_mhstruct **mh, int x)
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
			mark = act_red(&tok, &previous, mh, x);
			if (mark)
				break ;
		}
	}
	return (mark);
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
			//pipe_heredoc(&tmp);
			do_hd(pipes, i, &tmp);
		//print_tokens(tmp->token);
		set_pipe(pipes, i, lines, 0);
		if (ft_tokenlstsize(tmp->token))
			//do_redirects(tmp->token, tmp, 1);
			do_redirects_pipe(&(tmp->token), &tmp, 0);
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

//check  << a | wc
