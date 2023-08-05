/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:27:19 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/04 19:37:40 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

// static void	run_pipe_helper(char *argv, int argc, char **envp, int *pipes)
// {
// 	char	buffer[1024];
// 	char	**argsread;
// 	(void)	argc;

// 	close(pipes[0]);
// 	find_path(argv, envp, buffer);
// 	argsread = ft_split(&(*argv), ' ');
// 	dup2(pipes[1], STDOUT_FILENO);
// 	execve(buffer, argsread, envp);
// }

// static void	run_pipe(char **argv, int argc, char **envp, int i)
// {
// 	int		pipes[2];
// 	int		pid;
// 	(void)	argc;

// 	if (pipe(pipes) == -1)
// 		return ;
// 	if (check_command(argv[i], envp, argc) == 0)
// 		write(1, "command not found:\n", 19);
// 	else
// 	{
// 		pid = fork();
// 		{
// 			if (pid == 0)
// 				run_pipe_helper(argv[i], argc, envp, pipes);
// 			else
// 			{	
// 				close(pipes[1]);
// 				dup2(pipes[0], STDIN_FILENO);
// 				close(pipes[0]);
// 				unlink("TEMPORARYFILETODELETE");
// 				waitpid(pid, NULL, 0);
// 			}
// 		}
// 	}
// }

void	execute_last(char **argv, char **envp, int i)
{
	char	buffer[1024];
	char	**argsread;

	find_path(argv[i], envp, buffer);
	argsread = ft_split(argv[i], ' ');
	execve(buffer, argsread, envp);
}

void	delete_outfile_tokens(t_mhstruct **mh, t_token *redir)
{
	t_token	*temp;
	t_token	*t;

	t = (*mh)->token;
	while (t && t != redir)
		t = t->next;
	temp = (t)->next;
	free_token(t);
	t = temp;
	temp = (t)->next;
	free_token(t);
}

void	checkred(t_token **pre, t_token **nullthis, t_mhstruct **mh, int *out)
{
	if (*pre && (*pre)->type == GT)
	{
		*out = open((*pre)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		delete_outfile_tokens(mh, *pre);
		(*nullthis)->next = NULL;
	}
	else if (*pre && (*pre)->type == D_GT)
	{
		*out = open((*pre)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		delete_outfile_tokens(mh, *pre);
		(*nullthis)->next = NULL;
	}
}

void	ct_check(int count, t_token **last, t_token **preprev, t_token **prev)
{
	if (count >= 4)
		*last = *preprev;
	if (count >= 3)
		*preprev = *prev;
}

// void test(t_mhstruct **mh)
// {
// 	char **envarray = get_env_array(*mh);
// 	char *command_path;
// 	char *argv = "cat";
	
// 	command_path = NULL;
// 	check_path_exists(argv, envarray, &command_path);
// 	if (command_path)
// 		printf("found >%s<", command_path);
// }

int	dup_out_file(int *outfile, t_mhstruct **mh)
{
	t_token	*t;
	t_token *prev;
	t_token *preprev;
	t_token	*nullthis;
	int count;
	count = 1;
	t = (*mh)->token;
	prev = t;
	preprev = NULL;
	nullthis = NULL;
	

	while (t)
	{
		ct_check(count, &nullthis, &preprev, &prev);
		prev = t;
		t = t->next;
		count++;
	}
	checkred(&preprev, &nullthis, mh, outfile);
	return (0);
}


int	launch_pipes(t_mhstruct **mh)
{
	int		outfile;
	
	outfile = 0;

	if (bad_redirect_syntax((*mh)->token) || bad_redirect_syntax2((*mh)->token))
	{
		error_msg("Syntax error near unexpected token", 258, *mh);
		return (1);
	}
	dup_out_file(&outfile, mh);
	// printf("outfile is %d\n", outfile);
	// 	print_tokens((*mh)->token);

	
	// {
	// 	i = setting_out_files(argv, &outfile, argc);
	// 	tempfile = setting_in_files(&infile, argv, envp);
	// 	dup2(infile, STDIN_FILENO);
	// 	while (i < (argc - 2))
	// 		run_pipe(argv, argc, envp, i++);
	// 	if (tempfile == 1)
	// 		unlink("TEMPORARYFILETODELETE");
	// 	if (check_command(argv[i], envp, argc) == 0)
	// 		error_msg("command not found:");
	// 	dup2(outfile, STDOUT_FILENO);
	// 	execute_last(argc, argv, envp, i);
	// }
	return (0);
}





// int	main(int argc, char **argv, char **envp)
// {
// 	int		infile;
// 	int		outfile;
// 	int		i;
// 	int		tempfile;

// 	infile = 0;
// 	outfile = 0;
// 	if (argc < 5)
// 		error_msg("Error\nInvalid number of arguments!");
// 	if (argc >= 5)
// 	{
// 		i = setting_out_files(argv, &outfile, argc);
// 		tempfile = setting_in_files(&infile, argv, envp, argc);
// 		dup2(infile, STDIN_FILENO);
// 		while (i < (argc - 2))
// 			run_pipe(argv, argc, envp, i++);
// 		if (tempfile == 1)
// 			unlink("TEMPORARYFILETODELETE");
// 		if (check_command(argv[i], envp, argc) == 0)
// 			error_msg("command not found:");
// 		dup2(outfile, STDOUT_FILENO);
// 		execute_last(argc, argv, envp, i);
// 	}
// 	return (0);
// }
