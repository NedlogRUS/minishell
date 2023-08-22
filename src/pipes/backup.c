// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   backup.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
// /*   Updated: 2023/08/22 11:53:22 by vtavitia         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "vtavitia.h"
//  int GLOBAL_ERROR = 0;



//  void	close_pipes(int pipes[1000][2] , int lines)
// {
// 	int	i;

// 	i = 0;
// 	while (i < lines - 1)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// }

// int	assign_pi(t_mhstruct **mh)
// {
// 	t_token	*current;
// 	int		idx;

// 	current = (*mh)->token;
// 	idx = 0;
// 	while (current)
// 	{
// 		while (current->type != PIPELINE && current)
// 		{
// 			current->pi = idx;
// 			if (current->next)
// 				current = current->next;
// 			else
// 				break;
// 		}
// 		if (current)
// 			current = current->next;
// 		idx++;
// 	}	
// 	return (idx);
// }

// int	get_args_size_pipes(t_token *tmp)
// {
// 	int		i;

// 	i = 0;
// 	if (!tmp)
// 		return (0);
// 	while (tmp && tmp->type != PIPELINE)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// char	**get_args_pipes(t_token *token, t_mhstruct *mh)
// {
// 	char	**out;
// 	int		i;
// 	(void) mh;

// 	i =get_args_size_pipes(token);
// 	out = (char **)malloc((i + 1) * sizeof(char *));
// 	if (!out)
// 		return (NULL);
// 	i = 0;
// 	while (token && token->type != PIPELINE)
// 	{
// 		out[i] = ft_strdup(token->data);
// 		token = token->next;
// 		i++;
// 	}
// 	out[i] = NULL;
// 	i = 0;
// 	return (out);
// }



// void	execve_commands_pipes(t_token *curr, t_mhstruct *mh, int lines, int pipes[1000][2])
// {
// 	char	**arg;
// 	char	**env;
// 	char	*path;
// 	int		out;
// 	int		pid;
// 	(void) lines;
// (void) pipes;
// 	path = NULL;
// 	out = 0;
// 	env = get_env_array(mh);
// 	arg = get_args_pipes(curr, mh);
// 	if (check_path(arg[0], env, &path) == 0)
// 	{
// 		if (access(arg[0], R_OK) == 0)
// 			path = arg[0];
// 		else
// 		{
// 			free(env);
// 			free(arg);
// 			return (pr_err(mh, 127, gemsg(mh->emsg[11], mh->emsg[12], arg[0])));
// 		}
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close_pipes(pipes, lines);
// 		execve(path, arg, env);
// 		waitpid(pid, &GLOBAL_ERROR, 0);
// 		exit(1);
// 	}

// }


// void	set_pipe(t_token *curr, int pipes[1000][2], int i, int lines, int screen)
// {

// 	(void) curr;
// 	(void) screen;
// 	if (i == 0)
// 	{
// 		close(pipes[i][0]);
// 		dup2(pipes[i][1], STDOUT_FILENO);
// 		close(pipes[i][1]);
	
// 	}
// 	else if (i != 0 && i != lines - 1)
// 	{
// 		dup2(pipes[i - 1][0], STDIN_FILENO);
// 		dup2(pipes[i][1], STDOUT_FILENO);
// 		close(pipes[i - 1][0]);
// 		close(pipes[i][1]);
// 	}
// 	else if (i == lines - 1)
// 	{
// 		close(pipes[i - 1][1]);
// 		dup2(pipes[i - 1][0], STDIN_FILENO);
// 		close(pipes[i - 1][0]);
// 	}
	
// }

// void		do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int	i, int	lines, int screen, char **grid)
// {
// 	int		pid;
// 	t_token	*curr;
// 	(void) screen;
// 	(void) grid;
// 	(void) lines;
// 	(void) pipes;
	
// 	curr = (*mh)->token;
// 	while ( curr->pi != i)
// 		curr = curr->next;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		set_pipe(curr, pipes, i, lines, screen);
// 		close_pipes(pipes, lines);
// 		execve_commands_pipes(curr, *mh, lines, pipes);
// 		exit(1);
// 	}
// }

// void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// {
// 	int	screen = dup(STDOUT_FILENO);
// 	int	i;
// 	int	pipes[1000][2];
// 	(void) grid;
	
// 	i = 0;
// 	printf("lines = %d\n", lines);
// 	while (i < lines - 1) 
// 	{
// 		pipe(pipes[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < lines)
// 	{
// 		do_pipe_forks(mh, pipes, i, lines, screen, grid);
// 		i++;
// 	}
// 	close_pipes(pipes, lines);
// }


// int	launch_pipes(t_mhstruct **mh)
// {
// 	int		lines;
// 	char	**grid = NULL;
	
// 	lines = assign_pi(mh);

// 	grid = (char **)malloc(sizeof(char **) * (lines + 1));
// 	if (!grid)
// 		return (1);
// 	create_grid(grid, lines, mh);
// 	do_pipes(mh, grid, lines);
// 	free_all(grid);
// 	return (0);
// }