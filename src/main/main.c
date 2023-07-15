/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/15 20:17:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pwd(t_mhstruct *mh) 
{
    char cwd[PATH_MAX];

	if (!ft_strcmp("pwd", mh->input))
	{
    	if (getcwd(cwd, sizeof(cwd)) != NULL) 
		{
    	    printf("%s\n", cwd);
    	} 
		else 
        	return 1;
	}
	else
		return 1;
    return 0;
}

//void start_builtin()

int main(int ac, char **av, char **env)
{
	(void) env;
	(void) ac;
	(void) av;
	t_mhstruct *mh;
	mh = malloc(sizeof(t_mhstruct));
	
	while(1)
	{
		mh->input = readline("$> ");
		if(pwd(mh) != 0)
			printf("minihell: command not found: %s\n", mh->input);
		add_history(mh->input);
	}
	return 0;
}
