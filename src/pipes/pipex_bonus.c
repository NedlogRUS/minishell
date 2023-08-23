/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:27:19 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/22 18:26:25 by vtavitia         ###   ########.fr       */
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

// int	check_pipe_redirs(t_mhstruct **mh, int screen)
// {
// 	t_token *current;

// 	current = (*mh)->token;
// 	while (current && current->type!= PIPELINE)
// 	{
// 		if (check_redir_exist_pipe(((*mh)->token)))
// 			action_redirect(current, previous, mh, screen);
// 		else
// 			set_prev(previous, current);
// 	}
// 	}
// }

int	get_arg_list_size_pipes(t_mhstruct *mh)
{
	int		i;
	t_token	*tmp;

	tmp = mh->token;
	i = 0;
	if (!mh->token)
		return (0);
	while (tmp && tmp->type != PIPELINE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
char	**get_arg_array_pipes(t_mhstruct *mh)
{
	char	**out;
	int		i;
	t_token	*token;

	token = mh->token;
	i = get_arg_list_size_pipes(mh);
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

void	execve_of_commands_pipes(t_mhstruct *mh)
{
	char	**arg;
	char	**env;
	char	*path;
	int		out;

	path = NULL;
	out = 0;
	env = get_env_array(mh);
	arg = get_arg_array_pipes(mh);
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
	GLOBAL_ERROR = out / 256;
	free(env);
	free(arg);
}

void	clean_pipes(t_mhstruct **mh)
{
	t_token	*current;
	t_token *tmp;
	
	current = (*mh)->token;
	while (current && current->type != PIPELINE)
	{
		tmp = current->next;
		free(current->data);
		current = tmp;
	}
	if (current->type == PIPELINE)
	{
		tmp = current->next;
		free(current->data);
		current = tmp;
		(*mh)->token = current;
	}
	else if (current == NULL)
	{
		tmp = current->next;
		free(current->data);
		current = tmp;
	}
}

int	count_segs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPELINE)
			count++;
		token = token->next;	
	}
	return (count);
}

int	action_pipe_redirect(t_token **tok, t_token **previous, t_mhstruct **mh, int screen)
{
	if ((*tok)->type == GT || (*tok)->type == LT || (*tok)->type == D_GT)
	{
		if (do_dups(tok, mh, screen))
			return (1);
		delete_redirs(tok, mh, previous);
	}
	else if ((*tok)->type == D_LT)
	{
		do_here_doc((*tok)->next->data);
		delete_redirs(tok, mh, previous);
	}
	else
		set_prev(previous, tok);
	return (0);
}

void	run_pipe(t_mhstruct **mh, int *pipes)
{
	int	pid;
	
	t_token	**current;
	t_token	**previous;

	current = &(*mh)->token;
	previous = current;

	
	pid = fork();
	if (pid == 0)
	{
		close(pipes[0]);
		if (check_redir_exist_pipe((*mh)->token))
		{
			while (*current && (*current)->type != PIPELINE)
			{
				if ((*current)->type == GT || (*current)->type == LT|| (*current)->type == D_GT || (*current)->type == D_LT)
					action_redirect(current, previous, mh, pipes[1]);
				else
				{
					previous = current;
					current = &(*current)->next;
				}
			}
		}
		else
			dup2(pipes[1], STDOUT_FILENO);
		execve_of_commands_pipes(*mh);
	}
	else
	{
		wait(NULL);
		close(pipes[1]);
		if (check_pipe_exists((*mh)->token))
			clean_pipes(mh);
		dup2( pipes[0], STDIN_FILENO);
		close(pipes[0]);
	}
}


// int	launch_pipes(t_mhstruct **mh)
// {
// 	int		outfile = dup(STDOUT_FILENO);
// 	int		in = dup(STDIN_FILENO);
// 		int	pipes[2];
// 		if (pipe(pipes) == -1)
// 		return (1);
// 	//dup_out_file(&outfile, mh);
// 	if (bad_redirect_syntax((*mh)->token) || bad_redirect_syntax2((*mh)->token))
// 	{
// 		error_msg("Syntax error near unexpected token", 258, *mh);
// 		return (1);
// 	}
	
// 	int	count = count_segs((*mh)->token);
// 	while (count--) 
// 		run_pipe(mh, pipes);
// 	// close(pipes[0]);
// 	// close(pipes[1]);
// 	dup2(outfile, STDOUT_FILENO);
// 	do_redirects((*mh)->token, *mh, 1);
// 	dup2(in, STDIN_FILENO);
// 	return (0);
// }
