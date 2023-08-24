/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/24 16:45:49 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"
 int GLOBAL_ERROR = 0;



 void	close_pipes(int pipes[1000][2] , int lines)
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
	i = 0;
	return (out);
}

// void	execution_of_commands_pipe(t_mhstruct *mh, t_token *curr)
// {
// 	if(!ft_strcmp(curr->data, "pwd"))
// 		builtin_pwd(mh);	
// 	else if(!ft_strcmp(mh->token->data, "env"))
// 		builtin_env(mh);
// 	else if(!ft_strcmp(mh->token->data, "export"))
// 		builtin_export(mh);
// 	else if(!ft_strcmp(mh->token->data, "unset"))
// 		builtin_unset(mh);
// 	else if(!ft_strcmp(mh->token->data, "cd"))
// 		builtin_cd(mh);
// 	else if(!ft_strcmp(mh->token->data, "echo"))
// 		builtin_echo(mh);
// 	else if(!ft_strcmp(mh->token->data, "exit"))
// 		builtin_exit(mh);
// 	else
// 		execve_of_commands(mh);	
// 	// {
// 	// 	GLOBAL_ERROR = 127;
// 	// 	printf("minihell: command not found: %s\n", mh->token->data);
// 	// }
// 	return ;

// }


void	execve_commands_pipes(t_token *curr, t_mhstruct *mh, int lines, int pipes[1000][2])
{
	char	**arg;
	char	**env;
	char	*path;
	int		out;

	(void) lines;
(void) pipes;
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
	execve(path, arg, env);
	return ;
}


void	set_pipe(t_token *curr, int pipes[1000][2], int i, int lines, int screen, int hd)
{

	(void) curr;
	(void) screen;
	(void) hd;
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


void	copy_to_tmp(t_mhstruct *tmp, t_token *curr)
{
	t_token	*start;
	t_token *new;
	
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
		{
			tmp->token->next = new;
			tmp->token = tmp->token->next;
		}
		curr = curr->next;
	}
	tmp->token = start;
}


void	initializer_temp_mh( t_mhstruct *tmp, t_mhstruct *mh)
{
	
	int		i;

	i = 0;
	tmp->token = NULL;
	tmp->env = mh->env;
	tmp->er_num = 0;
	mh->mh_pid = (int)getpid();
	add_error_message(tmp);
}

int	check_heredoc(t_mhstruct *mh)
{
	t_token *curr;
	
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

int		do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int	i, int	lines, int screen, char **grid)
{
	int		pid;
	t_token	*curr;
	(void) screen;
	(void) grid;
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
				just_heredoc(tmp->token, tmp, 0);
		}
		set_pipe(curr, pipes, i, lines, screen, hd);
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

void	do_pipes(t_mhstruct **mh, char **grid, int lines)
{
	int	screen = dup(STDOUT_FILENO);
	int	i;
	int	pipes[1000][2];
	(void) grid;
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
		pid[i] = do_pipe_forks(mh, pipes, i, lines, screen, grid);
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
	

//TEST yes | head > 3
//TEST echo hi > 2 | echo test> 3 | echo 4 > 5 | yes | head

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
	create_grid(grid, lines, mh);
	do_pipes(mh, grid, lines);
	free_all(grid);
	return (0);
}

