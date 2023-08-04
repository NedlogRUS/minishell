/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:27:19 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/04 16:43:21 by vtavitia         ###   ########.fr       */
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
	t_token *t;

	t= (*mh)->token;

	while (t && t !=redir)
		t = t->next;
	temp = (t)->next;
	free_token(t);
	t = temp;
	temp = (t)->next;
	free_token(t);
	// free_token(temp);
}


int	dup_out_file(int *outfile, t_mhstruct **mh)
{
	t_token	*t;
	t_token *prev;
	t_token *preprev;
	t_token	*nullthis;
	int count;
	count = 1;
	(void)outfile;
	t = (*mh)->token;
	prev = t;
	preprev = NULL;
	nullthis = NULL;
	if (bad_redirect_syntax((*mh)->token))
	{
		error_msg("Syntax error near unexpected token", 258, *mh);
		return (1);
	}
	while (t)
	{
		if (count >= 4)
			nullthis = preprev;
		if (count >= 3)
			preprev = prev;
		prev = t;
		t = t->next;
		count++;
	}
	if (preprev && preprev->type == GT)
	{
		*outfile = open((preprev)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		delete_outfile_tokens(mh, preprev);
		nullthis->next = NULL;
	}
	else if (preprev && preprev->type == D_GT)
	{
		*outfile = open((preprev)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		delete_outfile_tokens(mh, preprev);
		nullthis->next = NULL;
	}

	// if (ft_tokenlstsize((*mh)->token) > 3)
	// 	printf("found '%s' and pre prev = '%s' and nullthis= '%s\n", preprev->next->data, preprev->data, nullthis->data);
	
	
	print_tokens((*mh)->token);
	return (0);
	// while (t)
	// {
	// 	if (t->type == GT || t->type == D_GT)
	// 	{
	// 		if (do_dups(t, mh))
	// 			return (1);
	// 		delete_redirs(t, mh, prev);
	// 	}
	// }
	// int	i;

	// i = 3;
	// if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	// {
	// 	if (argc < 6)
	// 		error_msg2("Error\nNot enough arguments!");
	// 	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 	do_here_doc(argv[2]);
	// }
	// else
	// {
	// 	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	i = 2;
	// }
	// return (i);
}


// int	launch_pipes(int argc, char **argv, char **envp, t_mhstruct *mh)
// {
// 	int		infile;
// 	int		outfile;
// 	int		i;
// 	int		tempfile;

// 	infile = 0;
// 	outfile = 0;
// 	{
// 		i = setting_out_files(argv, &outfile, argc);
// 		tempfile = setting_in_files(&infile, argv, envp);
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
