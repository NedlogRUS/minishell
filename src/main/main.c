/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:50 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_mhstruct *mh;
	mh = malloc(sizeof(t_mhstruct));
	
	initializer_mh(env, mh);
	while(1)
	{
		mh->input = readline("$> ");
		printf("%s\n", mh->input);
		check_and_tokenize(mh);
		if(!ft_strcmp(mh->input, "pwd"))
			builtin_pwd(mh);
		else if(!ft_strcmp(mh->input, "env"))
			builtin_env(mh);
		else if(!ft_strcmp(mh->input, "export"))
			builtin_export(mh);
		else
			printf("minihell: command not found: %s\n", mh->input);
		add_history(mh->input);
	}
	return 0;
}
