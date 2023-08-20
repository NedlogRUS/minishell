/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/20 15:21:55 by vtavitia         ###   ########.fr       */
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
	execve(path, arg, env);
	mh->er_num = out / 256;
	free(env);
	free(arg);
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

void	do_last_fork(t_mhstruct **mh, int *mainp, int lines, int screen)
{
	int pid;
	t_token	*current;

	current = (*mh)->token;

	while (current != NULL && current->pi != lines - 1)
		current = current->next;
	(void) screen;
	pid = fork();
	if (pid == 0)
	{
		dup2(mainp[0], STDIN_FILENO);
		//dup2(mainp[1], STDOUT_FILENO);
			//dup2(mainp[0], screen);
		execve_commands_pipes(current, *mh);
	}
	else
	{
		wait(NULL);
		close(mainp[1]);
		// dup2(mainp[0], screen);
		close(mainp[0]);
	}
	
	
	
}

void	do_pipe_forks(t_mhstruct **mh, int **pipes, int	i, int screen)
{
	int	pid;
	t_token	*current;
	t_token *previous;
	t_token *mark;
	current = (*mh)->token;
	mark = current;
	previous = current;
	while (current != NULL & current->pi != i)
		current = current->next;
	(void)mh;
	(void)screen;
	if (pipe(pipes[i]) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		// if (check_redir_exist_pipe(current))
		// {
		// 	while (current && (current)->type != PIPELINE)
		// 	{
		// 		if ((current)->type == GT || (current)->type == LT|| (current)->type == D_GT || (current)->type == D_LT)
		// 			action_redirect(&current, &previous, mh, pipes[i][1]);
		// 		else
		// 		{
		// 			previous = current;
		// 			current = (current)->next;
		// 		}
		// 	}
		// 	current = mark;
		// }
		//printf("Executing FORK! i is %d\xn\n\n", i);
		close(pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
	
		//printf("DoNE! i is %d and pid is %d\n\n\n", i, pid);
		execve_commands_pipes(current, *mh);
	}
	else
	{
		wait(NULL);
		close(pipes[i][1]);
		dup2(pipes[i][0], STDIN_FILENO);
		// dup2(screen,pipes[i][0]);
		//close(pipes[i][0]);
		//printf(" COMPLETED fork %d\n\n\n", i);
	}
}


void	do_pipes(t_mhstruct **mh, char **grid, int lines)
{
	int	i;
	int	**pipes;
	(void) grid;
	int	screen = dup(STDOUT_FILENO);
	int mainp[2];
	pipe(mainp);
	i = 0;
	pipes = (int **)malloc(sizeof(int *) * lines);
	int	proc = fork();
	if (proc == 0)
	{
		while (i < lines -1)
		{
			//printf("NOW i is %d \n\n\n", i);
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			do_pipe_forks(mh, pipes, i, screen);
			//printf("DONNEE i is %d lines is %d \n\n\n", i, lines);
			// dup2(mainp[1], pipes[i][0]);
			i++;
		}
		mainp[1] = dup(pipes[i - 1][0]);
		// dup2(mainp[1], pipes[i - 1][0]);
		close(mainp[1]);
		// dup2(screen, mainp[0]);
		//printf("!DONEEEE!\n");
		exit(1);
	}
	else
	{
		waitpid(proc, NULL, 0);
		close(mainp[1]);
		do_last_fork(mh, mainp, lines, screen);
		close(mainp[0]);
		// dup2(screen, STDOUT_FILENO);
		printf("!FINISHED!\n");
		free(pipes);
	}
	 
}



// void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// {
// 	int	i;
// 	int	**pipes;
// 	int	proc;
// 	(void) grid;
// 	i = 0;
// 	pipes = (int **)malloc(sizeof(int *) * lines);
// 	while (i < lines)
// 	{
// 		proc = fork();
// 		if (proc == 0)
// 		{
// 			pipes[i] = (int *)malloc(sizeof(int) * 2);
// 			do_pipe_forks(mh, pipes, i);
// 			exit(1);
			
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			i++;
// 	//	free(pipes[i][0]);
// 	//	free(pipes[i][1]);
	
// 		}
// 	}
// 	//free(pipes);
// 	// system("leaks minishell");
// }


void	run_seq(t_mhstruct **mh)
{
	int		lines;
	char	**grid;
	
	lines = assign_pi(mh);
	//  printf("lines are %d\n", lines);
	grid = (char **)malloc(sizeof(char **) * (lines + 1));
	if (!grid)
		return ;
	create_grid(grid, lines, mh);
	do_pipes(mh, grid, lines);
	free_all(grid);
//	system("leaks minishell");
	
}


int	launch_pipes(t_mhstruct **mh)
{
	run_seq(mh);
	return (0);
}