/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/21 16:22:25 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"
 int GLOBAL_ERROR = 0;

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
				break;
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

char	**get_args_pipes(t_token *token, t_mhstruct *mh)
{
	char	**out;
	int		i;
	(void) mh;

	i =get_args_size_pipes(token);
	out = (char **)malloc((i + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (token && token->type != PIPELINE)
	{
		out[i] = ft_strdup(token->data);
		token = token->next;
		i++;
	}
	out[i] = NULL;
	return (out);
}


void	execve_commands_pipes(t_token *curr, t_mhstruct *mh)
{
	char	**arg;
	char	**env;
	char	*path;
	int		out;
	int		pid;

	path = NULL;
	out = 0;
	env = get_env_array(mh);
	arg = get_args_pipes(curr, mh);
	if (check_path(arg[0], env, &path) == 0)
	{
		if (access(arg[0], R_OK) == 0)
			path = arg[0];
		else
		{
			free(env);
			free(arg);
			return (pr_err(mh, 127, gemsg(mh->emsg[11], mh->emsg[12], arg[0])));
		}
	}
	
	// if (path != NULL)
	// 	out = execve_of_commands_2(path, arg, env);
	pid = fork();
	if (pid == 0)
	{
		//  printf("EXECUTING curr is %s path is %s\n", curr->data, path);
		execve(path, arg, env);
		exit(1);
	}
	else
	{
		waitpid(pid, &GLOBAL_ERROR, 0);
		// printf("WAITED for %s\n\n\n", curr->data);
		free(env);
		free(arg);
		return ;
	}
}


void	set_pipe(t_token *curr, int pipes[1000][2], int i, int lines, int screen)
{

	(void) curr;
	(void) screen;
	if (i == 0)
	{
		close(pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
	
	}
	else if (i != 0 && i != lines - 1)
	{
		close(pipes[i - 1][1]);
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else if (i == lines - 1)
	{
		close(pipes[i - 1][1]);
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		//dup2(screen, STDOUT_FILENO);
		// c_pipes(pipes, lines);
	}
	
}

void close_unused_pipes(int pipes[1000][2], int current, int lines)
{
	int	i;

	i = 0;

	while (i < lines)
	{
        if (i - 1 != current)
        {
            close(pipes[i][0]); 
            close(pipes[i][1]); 
        }
    }
}

void	do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int	i, int	lines, int screen)
{
	int		pid;
	t_token	*curr;
	//int screen = dup(STDOUT_FILENO);
	
	(void)pipes;
	(void)lines;
	curr = (*mh)->token;
	while (curr && curr->pi != i)
		curr = curr->next;
	pid = fork();
	if (pid == 0)
	{
		set_pipe(curr, pipes, i, lines, screen);
		c_pipes(pipes, lines - 1);
		//close_unused_pipes(pipes, i, lines);
		execve_commands_pipes(curr, *mh);
		exit(1);
	}
	else
    {
    //    if (i == lines - 1)
	//    	waitpid(pid, NULL, 0); 
	   return ;
    }
	
	
}



void	do_pipes(t_mhstruct **mh, char **grid, int lines)
{
	 int	screen = dup(STDOUT_FILENO);
	 int	in = dup(STDIN_FILENO);
	int	i;
	int	pipes[1000][2];
	(void) grid;
	i = 0;
	while (i < lines - 1)
	{
		pipe(pipes[i]);
		i++;
	}
	// printf("i is %d lines is %d\n", i, lines);
	i = 0;
	while (i < lines)
	{
		do_pipe_forks(mh, pipes, i, lines, screen);
		i++;
	}
	printf("completed\n");
	c_pipes(pipes, lines - 1);
	//  close_unused_pipes(pipes, i, lines);
	dup2(in, STDIN_FILENO);
}


int	launch_pipes(t_mhstruct **mh)
{
	int		lines;
	char	**grid;
	
	lines = assign_pi(mh);
	grid = (char **)malloc(sizeof(char **) * (lines + 1));
	if (!grid)
		return (1);
	create_grid(grid, lines, mh);
	do_pipes(mh, grid, lines);
	free_all(grid);
	return (0);
}