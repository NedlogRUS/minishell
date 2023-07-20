/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/20 19:16:38 by apanikov         ###   ########.fr       */
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
	else
		printf("minihell: command not found: %s\n", mh->token->data);	
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_mhstruct *mh;
	mh = malloc(sizeof(t_mhstruct));
	(void)env;
	initializer_mh(env, mh);
	mh->afex = ft_strdup("LOGNAME=777");
	while(1)
	{
		mh->input = readline("$> ");
		check_and_tokenize(mh);
		execution_of_commands(mh);
		// free_token(mh);
		// if(!ft_strcmp(mh->input, "pwd"))
		// 	builtin_pwd(mh);
		// else if(!ft_strcmp(mh->input, "env"))
		// 	builtin_env(mh);
		// else if(!ft_strcmp(mh->input, "export"))
		// 	builtin_export(mh);
		// else
		// 	printf("minihell: command not found: %s\n", mh->input);
		add_history(mh->input);
		//break ;
	}
	//system("leaks minishell");
	return 0;
}