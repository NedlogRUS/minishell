/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/01 15:34:41 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
		mh->er_num = 127;
		printf("minihell: command not found: %s\n", mh->token->data);
	}
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	// (void)env;
	t_mhstruct *mh;
	mh = malloc(sizeof(t_mhstruct));
	initializer_mh(env, mh);
	while(1)
	{
		mh->input = readline("$> ");
		
		check_and_tokenize(mh);
		execution_of_commands(mh);
		// free_token(mh);
		add_history(mh->input);
	
	}
		// system("leaks minishell");
	return 0;
}