// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   backup.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/12 16:27:19 by vtavitia          #+#    #+#             */
// /*   Updated: 2023/08/14 17:11:55 by vtavitia         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "vtavitia.h"

// // static void	run_pipe_helper(char *argv, int argc, char **envp, int *pipes)
// // {
// // 	char	buffer[1024];
// // 	char	**argsread;
// // 	(void)	argc;

// // 	close(pipes[0]);
// // 	find_path(argv, envp, buffer);
// // 	argsread = ft_split(&(*argv), ' ');
// // 	dup2(pipes[1], STDOUT_FILENO);
// // 	execve(buffer, argsread, envp);
// // }

// // static void	run_pipe(char **argv, int argc, char **envp, int i)
// // {
// // 	int		pipes[2];
// // 	int		pid;
// // 	(void)	argc;

// // 	if (pipe(pipes) == -1)
// // 		return ;
// // 	if (check_command(argv[i], envp, argc) == 0)
// // 		write(1, "command not found:\n", 19);
// // 	else
// // 	{
// // 		pid = fork();
// // 		{
// // 			if (pid == 0)
// // 				run_pipe_helper(argv[i], argc, envp, pipes);
// // 			else
// // 			{	
// // 				close(pipes[1]);
// // 				dup2(pipes[0], STDIN_FILENO);
// // 				close(pipes[0]);
// // 				unlink("TEMPORARYFILETODELETE");
// // 				waitpid(pid, NULL, 0);
// // 			}
// // 		}
// // 	}
// // }

// void	execute_last(char **argv, char **envp, int i)
// {
// 	char	buffer[1024];
// 	char	**argsread;

// 	find_path(argv[i], envp, buffer);
// 	argsread = ft_split(argv[i], ' ');
// 	execve(buffer, argsread, envp);
// }

// void	delete_outfile_tokens(t_mhstruct **mh, t_token *redir)
// {
// 	t_token	*temp;
// 	t_token	*t;

// 	t = (*mh)->token;
// 	while (t && t != redir)
// 		t = t->next;
// 	temp = (t)->next;
// 	free_token(t);
// 	t = temp;
// 	temp = (t)->next;
// 	free_token(t);
// }

// void	checkred(t_token **pre, t_token **nullthis, t_mhstruct **mh, int *out)
// {
// 	if (*pre && (*pre)->type == GT)
// 	{
// 		*out = open((*pre)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		delete_outfile_tokens(mh, *pre);
// 		(*nullthis)->next = NULL;
// 	}
// 	else if (*pre && (*pre)->type == D_GT)
// 	{
// 		*out = open((*pre)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		delete_outfile_tokens(mh, *pre);
// 		(*nullthis)->next = NULL;
// 	}
// }

// void	ct_check(int count, t_token **last, t_token **preprev, t_token **prev)
// {
// 	if (count >= 4)
// 		*last = *preprev;
// 	if (count >= 3)
// 		*preprev = *prev;
// }

// // void test(t_mhstruct **mh)
// // {
// // 	char **envarray = get_env_array(*mh);
// // 	char *command_path;
// // 	char *argv = "cat";
	
// // 	command_path = NULL;
// // 	check_path_exists(argv, envarray, &command_path);
// // 	if (command_path)
// // 		printf("found >%s<", command_path);
// // }

// int	dup_out_file(int *outfile, t_mhstruct **mh)
// {
// 	t_token	*t;
// 	t_token *prev;
// 	t_token *preprev;
// 	t_token	*nullthis;
// 	int count;
// 	count = 1;
// 	t = (*mh)->token;
// 	prev = t;
// 	preprev = NULL;
// 	nullthis = NULL;
	

// 	while (t)
// 	{
// 		ct_check(count, &nullthis, &preprev, &prev);
// 		prev = t;
// 		t = t->next;
// 		count++;
// 	}
// 	checkred(&preprev, &nullthis, mh, outfile);
// 	return (0);
// }

// int	check_redir_exist_pipe(t_token *t)
// {
// 	while (t->next->type != PIPELINE)
// 	{
// 		if (t->type == GT || t->type == LT
// 			|| t->type == D_GT || t->type == D_LT)
// 			return (1);
// 		t = t->next;
// 	}
// 	if (t->type == GT || t->type == LT || t->type == D_GT || t->type == D_LT)
// 		return (1);
// 	return (0);
// }

// void	check_pipe_redirs(t_token **current, t_token **previous, t_mhstruct **mh, int screen)
// {
// 	if (*current)
// 	{
// 		while (*current && (*current)->type != PIPELINE)
// 		{
// 					printf("check pipe redirs");
// 		//	print_tokens(*current);
// 			if (check_redir_exist_pipe(((*mh)->token)))
// 				action_redirect(current, previous, mh, screen);
// 			else
// 				set_prev(previous, current);
// 		}
// 	}
// }

// int	get_arg_list_size_pipes(t_mhstruct *mh)
// {
// 	int		i;
// 	t_token	*tmp;

// 	tmp = mh->token;
// 	i = 0;
// 	if (!mh->token)
// 		return (0);
// 	while (tmp && tmp->type != PIPELINE)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }
// char	**get_arg_array_pipes(t_mhstruct *mh)
// {
// 	char	**out;
// 	int		i;
// 	t_token	*token;

// 	token = mh->token;
// 	i = get_arg_list_size_pipes(mh);
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
// 	return (out);
// }

// void	execve_of_commands_pipes(t_mhstruct *mh)
// {
// 	char	**arg;
// 	char	**env;
// 	char	*path;
// 	int		out;

// 	path = NULL;
// 	out = 0;
// 	env = get_env_array(mh);
// 	arg = get_arg_array_pipes(mh);
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
// 	// if (path != NULL)
// 	// 	out = execve_of_commands_2(path, arg, env);
// 	execve(path, arg, env);
// 	mh->er_num = out / 256;
// 	free(env);
// 	free(arg);
// }

// void	clean_pipes(t_mhstruct **mh)
// {
// 	t_token	*current;
// 	t_token *tmp;
	
// 	printf("clean pipes\n");
// 	current = (*mh)->token;
// 	while (current && current->type != PIPELINE)
// 	{
// 		tmp = current->next;
// 		free(current->data);
// 		current = tmp;
// 	}
// 	if (current->type == PIPELINE)
// 	{
// 		tmp = current->next;
// 		free(current->data);
// 		current = tmp;
// 		(*mh)->token = current;
// 	}
// 	else if (current == NULL)
// 	{
// 		tmp = current->next;
// 		free(current->data);
// 		current = tmp;
// 	}
// }

// int	count_segs(t_token *token)
// {
// 	int	count;

// 	count = 0;
// 	while (token)
// 	{
// 		if (token->type == PIPELINE)
// 			count++;
// 		token = token->next;	
// 	}
// 	return (count);
// }

// void	run_pipe(t_mhstruct **mh, int in, int screen)
// {
// 	int	pid;
// 	int	pipes[2];
	
	
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		//print_tokens((*mh)->token);
// 		//check_pipe_redirs(&current, &previous, mh, screen);
// 		dup2(pipes[1], screen);
// 		execve_of_commands_pipes(*mh);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(pipes[1]);
// 		if (check_pipe_exists((*mh)->token))
// 			clean_pipes(mh);
// 		dup2( pipes[0], in);
// 				close(pipes[0]);
// 	}
// }

// int	launch_pipes(t_mhstruct **mh)
// {
// 	int		outfile;
// 	t_token	*current;
// 	t_token	*previous;

// 	current = (*mh)->token;
// 	previous = current;
// 	outfile = 0;
// 	int screen = dup(STDOUT_FILENO);
// 	int	in = dup(STDIN_FILENO);	
// 	int pid;
	
// 	if (pipe(pipes) == -1)
// 		return (-1) ;
// 	if (bad_redirect_syntax((*mh)->token) || bad_redirect_syntax2((*mh)->token))
// 	{
// 		error_msg("Syntax error near unexpected token", 258, *mh);
// 		return (1);
// 	}
// 	// printf("PIPELINE = %d\n", check_redir_exist_pipe(((*mh)->token)));
// 	int	count = count_segs((*mh)->token);
// 		printf("counts is = %d\n", count);
// 	while (count--) 
// 	{
// 	// 	pid = fork();
// 	// 	if (pid == 0)
// 	// 	{
// 	// 		//print_tokens((*mh)->token);
// 	// 		//check_pipe_redirs(&current, &previous, mh, screen);
// 	// 		dup2(pipes[1], screen);
// 	// 		execve_of_commands_pipes(*mh);
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		wait(NULL);
// 	// 		close(pipes[1]);
// 	// 		if (check_pipe_exists((*mh)->token))
// 	// 			clean_pipes(mh);
// 	// // ÷
// 	// 		// break; 
// 	// 		dup2( pipes[0], in);
// 	// 				close(pipes[0]);
// 	// 	}
// 	}
// 	//check_pipe_redirs(&current, &previous, mh, screen);
// 	dup2(pipes[1], screen);
// 	execve_of_commands_pipes(*mh);

// 	print_tokens(((*mh)->token));
// 	//dup_out_file(&outfile, mh);
// 	// printf("outfile is %d\n", outfile);

	
// 	// {
// 	// 	i = setting_out_files(argv, &outfile, argc);
// 	// 	tempfile = setting_in_files(&infile, argv, envp);
// 	// 	dup2(infile, STDIN_FILENO);
// 	// 	while (i < (argc - 2))
// 	// 		run_pipe(argv, argc, envp, i++);
// 	// 	if (tempfile == 1)
// 	// 		unlink("TEMPORARYFILETODELETE");
// 	// 	if (check_command(argv[i], envp, argc) == 0)
// 	// 		error_msg("command not found:");
// 	// 	dup2(outfile, STDOUT_FILENO);
// 	// 	execute_last(argc, argv, envp, i);
// 	// }
// 	return (0);
// }





// // int	main(int argc, char **argv, char **envp)
// // {
// // 	int		infile;
// // 	int		outfile;
// // 	int		i;
// // 	int		tempfile;

// // 	infile = 0;
// // 	outfile = 0;
// // 	if (argc < 5)
// // 		error_msg("Error\nInvalid number of arguments!");
// // 	if (argc >= 5)
// // 	{
// // 		i = setting_out_files(argv, &outfile, argc);
// // 		tempfile = setting_in_files(&infile, argv, envp, argc);
// // 		dup2(infile, STDIN_FILENO);
// // 		while (i < (argc - 2))
// // 			run_pipe(argv, argc, envp, i++);
// // 		if (tempfile == 1)
// // 			unlink("TEMPORARYFILETODELETE");
// // 		if (check_command(argv[i], envp, argc) == 0)
// // 			error_msg("command not found:");
// // 		dup2(outfile, STDOUT_FILENO);
// // 		execute_last(argc, argv, envp, i);
// // 	}
// // 	return (0);
// // }


//20aug
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/20 14:06:30 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vtavitia.h"


// int	c_w(t_mhstruct **mh, int i)
// {
// 	t_token	*current;
// 	int		words;

// 	words = 0;
// 	current = (*mh)->token;
// 	while (current && current->pi != i)
// 		current = current->next;
// 	while (current && current->pi == i)
// 	{
// 		words++;
// 		current = current->next;
// 	}
// 	return (words);
// }

// int	c_ch(t_mhstruct **mh, int i)
// {
// 	t_token	*current;
// 	int		j;
// 	int		count;

// 	j = 0;
// 	count = 0;
// 	current = (*mh)->token;
// 	while (current && current->pi != i)
// 		current = current->next;
// 	while (current && current->pi == i)
// 	{
// 		while (current->data[j])
// 		{
// 			count++;
// 			j++;
// 		}
// 		j = 0;
// 		current = current->next;
// 	}
// 	return (count);
// }

// void	copy_to_grid(t_mhstruct **mh, int i, char **grid)
// {
// 	t_token	*current;
// 	int		j;
// 	int		k;
	
// 	current = (*mh)->token;
// 	k = 0;
// 	j = 0;
// 	while (current && current->pi != i)
// 		current = current->next;
// 	while (current && current->pi == i)
// 	{
// 		while (current->data[j])
// 		{
// 			grid[i][k] = current->data[j];
// 			j++;
// 			k++;
// 		}
// 		if (current->next && current->next->pi == i)
// 		{
// 			grid[i][k] = ' ';
// 			k++;
// 		}
// 		j = 0;
// 		current = current->next;
// 	}
// 	grid[i][k] = '\0';
// //	printf("copied for i = %d >%s<\n", i, grid[i]);
// }

// void	create_grid(char **grid, int lines, t_mhstruct **mh)
// {
// 	int	i;
// 	// int	count;
// 	// int	words;
// 	i = 0;
// 	// count = 0;
// 		// printf("lines are %d\n", lines);
// 	while (i < lines)
// 	{
// 		grid[i] = (char *)malloc(sizeof(char) * (c_ch(mh, i) +  c_w(mh, i) + 1));
// 		if (!grid)
// 			return ;
// 		copy_to_grid(mh, i, grid);
// 		// count = c_ch(mh, i);
// 		// words =  c_w(mh, i);
// 		// printf("count for i = %d is %d words = %d\n", i, count, words);
// 		i++;
// 	}
// 	grid[lines] = NULL;
// 	// printf("copied for i = %d >%s<\n", i, grid[0]);
// 	// printf("copied for i = %d >%s<\n", i, grid[1]);
// 	// printf("copied for i = %d >%s<\n", i, grid[2]);
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
// 	// t_token	*tmp;

// 	// tmp = mh->token;
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
// 	// t_token	*token;

// 	// token = mh->token;
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
// 	return (out);
// }


// void	execve_commands_pipes(t_token *curr, t_mhstruct *mh)
// {
// 	char	**arg;
// 	char	**env;
// 	char	*path;
// 	int		out;

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
// 	// if (path != NULL)
// 	// 	out = execve_of_commands_2(path, arg, env);
// 	execve(path, arg, env);
// 	mh->er_num = out / 256;
// 	free(env);
// 	free(arg);
// }


// void	do_pipe_forks(t_mhstruct **mh, int **pipes, int	i)
// {
// 	int	pid;
// 	t_token	*current;
// 	// int	screen = dup(STDOUT_FILENO);
// //printf("ENTERED FORK and i is %d!\n", i);
// 	current = (*mh)->token;
// 	while (current != NULL & current->pi != i)
// 		current = current->next;
// 	(void)mh;
// 	if (pipe(pipes[i]) == -1)
// 		return ;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		//printf("Executing FORK! i is %d\n\n\n", i);
// 		close(pipes[i][0]);
// 		dup2(pipes[i][1], STDOUT_FILENO);
	
// 		//printf("DoNE! i is %d and pid is %d\n\n\n", i, pid);
// 		execve_commands_pipes(current, *mh);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(pipes[i][1]);
// 		dup2(pipes[i][0], STDIN_FILENO);
// 			// dup2(screen, STDOUT_FILENO);
// 		close(pipes[i][0]);
// 		//printf(" COMPLETED fork %d\n\n\n", i);
// 	}
// }


// void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// {
// 	int	i;
// 	int	**pipes;
// 	int	mainp[2];
// 	(void) grid;
// 	int	screen = dup(STDOUT_FILENO);
// 	i = 0;
// 	pipe(mainp);
// 	pipes = (int **)malloc(sizeof(int *) * lines);
// 	int	proc = fork();
// 	if (proc == 0)
// 	{
// 		dup2(mainp[1], STDOUT_FILENO);
// 		while (i < lines)
// 		{
// 			//printf("NOW i is %d \n\n\n", i);
// 			pipes[i] = (int *)malloc(sizeof(int) * 2);
// 			do_pipe_forks(mh, pipes, i);
// 			//printf("DONNEE i is %d lines is %d \n\n\n", i, lines);
// 			i++;
	
// 			// free(pipes[i][0]);
// 			// free(pipes[i][1]);
// 		}
// 			//printf("LOOP COMPLETED \n\n\n");
// 		dup2(screen, STDOUT_FILENO);
// 		exit(1);
// 	}
// 	else
// 	{
// 		waitpid(proc, NULL, 0);
// 		close(mainp[1]);
// 		dup2(mainp[0], STDIN_FILENO);
// 		// dup2(screen, mainp[0]);
// 		dup2(screen, STDOUT_FILENO);
// 		printf("!FINISHED!\n");
// 			close(mainp[0]);
// 		free(pipes);
// 	}
// 	// system("leaks minishell");
// }



// // void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// // {
// // 	int	i;
// // 	int	**pipes;
// // 	int	proc;
// // 	(void) grid;
// // 	i = 0;
// // 	pipes = (int **)malloc(sizeof(int *) * lines);
// // 	while (i < lines)
// // 	{
// // 		proc = fork();
// // 		if (proc == 0)
// // 		{
// // 			pipes[i] = (int *)malloc(sizeof(int) * 2);
// // 			do_pipe_forks(mh, pipes, i);
// // 			exit(1);
			
// // 		}
// // 		else
// // 		{
// // 			wait(NULL);
// // 			i++;
// // 	//	free(pipes[i][0]);
// // 	//	free(pipes[i][1]);
	
// // 		}
// // 	}
// // 	//free(pipes);
// // 	// system("leaks minishell");
// // }


// void	run_seq(t_mhstruct **mh)
// {
// 	int		lines;
// 	char	**grid;
	
// 	lines = assign_pi(mh);
// 	//  printf("lines are %d\n", lines);
// 	grid = (char **)malloc(sizeof(char **) * (lines + 1));
// 	if (!grid)
// 		return ;
// 	create_grid(grid, lines, mh);
// 	do_pipes(mh, grid, lines);
	
// }


// int	launch_pipes(t_mhstruct **mh)
// {
// 	run_seq(mh);
// 	return (0);
// }

//aug21
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:37:53 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/21 13:31:44 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vtavitia.h"
//  int GLOBAL_ERROR = 0;

// int	c_w(t_mhstruct **mh, int i)
// {
// 	t_token	*current;
// 	int		words;

// 	words = 0;
// 	current = (*mh)->token;
// 	while (current && current->pi != i)
// 		current = current->next;
// 	while (current && current->pi == i)
// 	{
// 		words++;
// 		current = current->next;
// 	}
// 	return (words);
// }

// int	c_ch(t_mhstruct **mh, int i)
// {
// 	t_token	*current;
// 	int		j;
// 	int		count;

// 	j = 0;
// 	count = 0;
// 	current = (*mh)->token;
// 	while (current && current->pi != i)
// 		current = current->next;
// 	while (current && current->pi == i)
// 	{
// 		while (current->data[j])
// 		{
// 			count++;
// 			j++;
// 		}
// 		j = 0;
// 		current = current->next;
// 	}
// 	return (count);
// }

// void	copy_to_grid(t_mhstruct **mh, int i, char **grid)
// {
// 	t_token	*current;
// 	int		j;
// 	int		k;
	
// 	current = (*mh)->token;
// 	k = 0;
// 	j = 0;
// 	while (current && current->pi != i)
// 		current = current->next;
// 	while (current && current->pi == i)
// 	{
// 		while (current->data[j])
// 		{
// 			grid[i][k] = current->data[j];
// 			j++;
// 			k++;
// 		}
// 		if (current->next && current->next->pi == i)
// 		{
// 			grid[i][k] = ' ';
// 			k++;
// 		}
// 		j = 0;
// 		current = current->next;
// 	}
// 	grid[i][k] = '\0';
// }

// void	create_grid(char **grid, int lines, t_mhstruct **mh)
// {
// 	int	i;

// 	i = 0;
// 	while (i < lines)
// 	{
// 		grid[i] = (char *)malloc(sizeof(char) * (c_ch(mh, i) +  c_w(mh, i) + 1));
// 		if (!grid)
// 			return ;
// 		copy_to_grid(mh, i, grid);
// 		i++;
// 	}
// 	grid[lines] = NULL;
// 	// free grid
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
// 	return (out);
// }


// void	execve_commands_pipes(t_token *curr, t_mhstruct *mh)
// {
// 	char	**arg;
// 	char	**env;
// 	char	*path;
// 	int		out;
// 	int		pid;

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
// 	// if (path != NULL)
// 	// 	out = execve_of_commands_2(path, arg, env);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(path, arg, env);
// 		waitpid(pid, &GLOBAL_ERROR, 0);
// 		return ;
// 	}
// 	// else
// 	// {
		
// 	// 	// wait(NULL);
// 	// 	// mh->er_num = out / 256;
// 	// 	// free(env);
// 	// 	// free(arg);
// 	// }

// }

// int	check_redir_exist_pipe(t_token *t)
// {
// 	while (t && t->next->type != PIPELINE)
// 	{
// 		if (t->type == GT || t->type == LT
// 			|| t->type == D_GT || t->type == D_LT)
// 			return (1);
// 		t = t->next;
// 	}
// 	// if (t->type == GT || t->type == LT || t->type == D_GT || t->type == D_LT)
// 	// 	return (1);
// 	return (0);
// }

// // void	do_last_fork(t_mhstruct **mh, int *mainp, int lines, int screen)
// // {
// // 	int pid;
// // 	t_token	*current;

// // 	current = (*mh)->token;

// // 	while (current != NULL && current->pi != lines - 1)
// // 		current = current->next;
// // 	(void) screen;
// // 	pid = fork();
// // 	if (pid == 0)
// // 	{
// // 		dup2(mainp[0], STDIN_FILENO);
// // 		//dup2(mainp[1], STDOUT_FILENO);
// // 			//dup2(mainp[0], screen);
// // 		execve_commands_pipes(current, *mh);
// // 	}
// // 	else
// // 	{
// // 		wait(NULL);
// // 		close(mainp[1]);
// // 		// dup2(mainp[0], screen);
// // 		close(mainp[0]);
// // 	}
	
	
	
// // }

// // void	do_pipe_forks(t_mhstruct **mh, int **pipes, int	i, int screen)
// // {
// // 	int	pid;
// // 	t_token	*current;
// // 	t_token *previous;
// // 	t_token *mark;
// // 	current = (*mh)->token;
// // 	mark = current;
// // 	previous = current;
// // 	while (current != NULL & current->pi != i)
// // 		current = current->next;
// // 	(void)mh;
// // 	(void)screen;
// // 	if (pipe(pipes[i]) == -1)
// // 		return ;
// // 	pid = fork();
// // 	if (pid == 0)
// // 	{
// // 		// if (check_redir_exist_pipe(current))
// // 		// {
// // 		// 	while (current && (current)->type != PIPELINE)
// // 		// 	{
// // 		// 		if ((current)->type == GT || (current)->type == LT|| (current)->type == D_GT || (current)->type == D_LT)
// // 		// 			action_redirect(&current, &previous, mh, pipes[i][1]);
// // 		// 		else
// // 		// 		{
// // 		// 			previous = current;
// // 		// 			current = (current)->next;
// // 		// 		}
// // 		// 	}
// // 		// 	current = mark;
// // 		// }
// // 		//printf("Executing FORK! i is %d\xn\n\n", i);
// // 		close(pipes[i][0]);
// // 		dup2(pipes[i][1], STDOUT_FILENO);
	
// // 		//printf("DoNE! i is %d and pid is %d\n\n\n", i, pid);
// // 		execve_commands_pipes(current, *mh);
// // 	}
// // 	else
// // 	{
// // 		wait(NULL);
// // 		close(pipes[i][1]);
// // 		dup2(pipes[i][0], STDIN_FILENO);
// // 		// dup2(screen,pipes[i][0]);
// // 		//close(pipes[i][0]);
// // 		//printf(" COMPLETED fork %d\n\n\n", i);
// // 	}
// // }

// void	set_pipe(t_token *curr, int pipes[1000][2], int i, int lines, int screen)
// {
// 	(void)screen;
// 	(void) curr;
// 	if (i == 0)
// 	{
// 		dup2(pipes[i][1], STDOUT_FILENO);
// 		close(pipes[i][1]);
// 	}
// 	else if (i != 0 && i != lines - 1)
// 	{
// 		dup2(pipes[i - 1][0], STDIN_FILENO);
// 		close(pipes[i - 1][0]);
// 		dup2(pipes[i][1], STDOUT_FILENO);
// 		close(pipes[i][1]);
// 	}
// 	else if (i == lines - 1)
// 	{
// 		dup2(pipes[i - 1][0], STDIN_FILENO);
// 		close(pipes[i - 1][0]);
// 		dup2(screen, STDOUT_FILENO);
	
// 	}
	
// }

// // void	set_pipe(t_token *pipe_token, int fd_array[1000][2],
// // 				int i, int heredocced, int screen)
// // {
// // 	heredocced = 0;
// // 	screen = 0;
// // 	if (pipe_token->pi == 0)
// // 	{
// // 		dup2(fd_array[i][1], STDOUT_FILENO);
// // 		close(fd_array[i][1]);
// // 	}
// // 	// else if (pipe_token->middle_pipe)
// // 	// {
// // 	// 	if (!heredocced)
// // 	// 		dup2(fd_array[i - 1][0], STDIN_FILENO);
// // 	// 	dup2(fd_array[i][1], STDOUT_FILENO);
// // 	// 	close(fd_array[i - 1][0]);
// // 	// 	close(fd_array[i][1]);
// // 	// }
// // 	else if (pipe_token->pi == 1)
// // 	{
// // 		if (!heredocced)
// // 			dup2(fd_array[i - 1][0], STDIN_FILENO);
// // 		close(fd_array[i - 1][0]);
// // 	}
// // }


// void	c_pipes(int pipes[1000][2] , int lines)
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

// void	do_pipe_forks(t_mhstruct **mh, int pipes[1000][2], int	i, int	lines)
// {
// 	int		pid;
// 	t_token	*curr;
// 	//int screen = dup(STDOUT_FILENO);
// (void)pipes;
// (void)lines;
// 	curr = (*mh)->token;
// 	while (curr && curr->pi != i)
// 		curr = curr->next;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		//printf("curr %s - pi %d\n", curr->data, curr->pi);
// 		//set_pipe(curr, pipes, i, lines, screen);
// 		//c_pipes(pipes, lines - 1);
	
// 		execve_commands_pipes(curr, *mh);
// 		exit(1);
// 	}

	
// }



// void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// {
// 	int	i;
// 	int	pipes[1000][2];
// 	(void) grid;
// 	// int	screen = dup(STDOUT_FILENO);
// 	i = 0;
// 	while (i < lines -1)
// 	{
// 		pipe(pipes[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < lines)
// 	{
// 		do_pipe_forks(mh, pipes, i, lines);
// 		i++;
// 	}

	
// }
// 	// else
// 	// {
// 	// 	waitpid(proc, NULL, 0);
// 	// 	close(mainp[1]);
// 	// 	do_last_fork(mh, mainp, lines, screen);
// 	// 	close(mainp[0]);
// 	// 	// dup2(screen, STDOUT_FILENO);
// 	// 	printf("!FINISHED!\n");
// 	// 	free(pipes);
// 	// }
	 







// // void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// // {
// // 	int	i;
// // 	int	**pipes;
// // 	(void) grid;
// // 	int	screen = dup(STDOUT_FILENO);
// // 	int mainp[2];
// // 	pipe(mainp);
// // 	i = 0;
// // 	pipes = (int **)malloc(sizeof(int *) * lines);
// // 	int	proc = fork();
// // 	if (proc == 0)
// // 	{
// // 		while (i < lines -1)
// // 		{
// // 			//printf("NOW i is %d \n\n\n", i);
// // 			pipes[i] = (int *)malloc(sizeof(int) * 2);
// // 			do_pipe_forks(mh, pipes, i, screen);
// // 			//printf("DONNEE i is %d lines is %d \n\n\n", i, lines);
// // 			// dup2(mainp[1], pipes[i][0]);
// // 			i++;
// // 		}
// // 		mainp[1] = dup(pipes[i - 1][0]);
// // 		// dup2(mainp[1], pipes[i - 1][0]);
// // 		close(mainp[1]);
// // 		// dup2(screen, mainp[0]);
// // 		//printf("!DONEEEE!\n");
// // 		exit(1);
// // 	}
// // 	else
// // 	{
// // 		waitpid(proc, NULL, 0);
// // 		close(mainp[1]);
// // 		do_last_fork(mh, mainp, lines, screen);
// // 		close(mainp[0]);
// // 		// dup2(screen, STDOUT_FILENO);
// // 		printf("!FINISHED!\n");
// // 		free(pipes);
// // 	}
	 
// // }



// // void	do_pipes(t_mhstruct **mh, char **grid, int lines)
// // {
// // 	int	i;
// // 	int	**pipes;
// // 	int	proc;
// // 	(void) grid;
// // 	i = 0;
// // 	pipes = (int **)malloc(sizeof(int *) * lines);
// // 	while (i < lines)
// // 	{
// // 		proc = fork();
// // 		if (proc == 0)
// // 		{
// // 			pipes[i] = (int *)malloc(sizeof(int) * 2);
// // 			do_pipe_forks(mh, pipes, i);
// // 			exit(1);
			
// // 		}
// // 		else
// // 		{
// // 			wait(NULL);
// // 			i++;
// // 	//	free(pipes[i][0]);
// // 	//	free(pipes[i][1]);
	
// // 		}
// // 	}
// // 	//free(pipes);
// // 	// system("leaks minishell");
// // }


// void	run_seq(t_mhstruct **mh)
// {
// 	int		lines;
// 	char	**grid;
	
// 	lines = assign_pi(mh);
// 	//  printf("lines are %d\n", lines);
// 	grid = (char **)malloc(sizeof(char **) * (lines + 1));
// 	if (!grid)
// 		return ;
// 	create_grid(grid, lines, mh);
// 	do_pipes(mh, grid, lines);
// 	free_all(grid);
// //	system("leaks minishell");
	
// }


// int	launch_pipes(t_mhstruct **mh)
// {
// 	run_seq(mh);
// 	return (0);
// }

