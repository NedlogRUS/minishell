/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/22 18:40:24 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void do_sigint(int i)
{
	(void)i;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void do_sigquit(int i)
{
	(void)i;
	rl_redisplay();
}

void	execution_of_commands(t_mhstruct *mh)
{
	if(!ft_strcmp(mh->token->data, "pwd"))
		builtin_pwd(mh);	
	else if(!ft_strcmp(mh->token->data, "env"))
		builtin_env(mh);
	else if(!ft_strcmp(mh->token->data, "export"))
		builtin_export(mh);
	else if(!ft_strcmp(mh->token->data, "unset"))
		builtin_unset(mh);
	else if(!ft_strcmp(mh->token->data, "cd"))
		builtin_cd(mh);
	else if(!ft_strcmp(mh->token->data, "echo"))
		builtin_echo(mh);
	else if(!ft_strcmp(mh->token->data, "exit"))
		builtin_exit(mh);
	else
		execve_of_commands(mh);	
	// {
	// 	GLOBAL_ERROR = 127;
	// 	printf("minihell: command not found: %s\n", mh->token->data);
	// }
	return ;

}

void	free_token_main(t_mhstruct *mh)
{
	if(mh->token == NULL)
		return ;
    t_token	*curr = mh->token;
	t_token *tmp;
    while (curr != NULL) 
	{
		tmp = curr;
        curr = curr->next;
		if(tmp->data != NULL)
        	free(tmp->data);
		if(tmp != NULL)
        	free(tmp);
    }
	mh->token = NULL;
}

int main(int ac, char **av, char **env)
{
	t_mhstruct *mh;

	
	(void) av;

	if(ac > 1)
		exit (1);
	rl_catch_signals = 0;
	mh = malloc(sizeof(t_mhstruct));
	mh->token = NULL;
	initializer_mh(env, mh);
	while(1)
	{
		signal(SIGINT, do_sigint);
		signal(SIGQUIT, do_sigquit);
		mh->input = readline("$> ");
		if(mh->input == NULL)
		{
			free(mh->input);
			printf("\x1b[1A\x1b[3Cexit\n");
			exit(GLOBAL_ERROR);
		}
		if (ft_strlen(mh->input))
		{
			add_history(mh->input);
			check_and_tokenize(mh);
			free(mh->input);
			if (mh->token)
			{
				if (check_redir_exist(mh->token) && !(check_pipe_exists(mh->token)))
					do_redirects(mh->token, mh, 1);
				else if (ft_strlen(mh->token->data) && mh->token && !(check_pipe_exists(mh->token)))
					execution_of_commands(mh);
				else if (check_pipe_exists(mh->token))
					launch_pipes(&mh);
				free_token_main(mh);
				free(mh->token);
			}
			else
			{
				free_token_main(mh);
				free(mh->token);
			}
		}
		else
			free(mh->input);
	// system("leaks minishell");
	}
	return 0;
}

// bash-3.2$ ./minishell 
// $> test
// $> echo $?
// 1
// $> echo $?
// 0
// $> echo ><
// Syntax error near unexpected token: Undefined error: 0
// > <
// $> echo $?
// 0
// $> <
// Syntax error - near unexpected token: Undefined error: 0
// Segmentation fault: 11