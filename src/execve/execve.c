/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:47 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/05 15:25:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path2(char **paths, char *argv, char **command_path)
{
	int		i;
	int		j;
	char	*tmp;
	int		check;

	i = 2;
	j = 0;
	check = 0;
	argv = cut_argv(argv);
	while (paths[j] != NULL)
	{
		*command_path = ft_strjoin("/", argv);
		tmp = *command_path;
		*command_path = ft_strjoin(paths[j], tmp);
		if (access(*command_path, R_OK) == 0)
			return (1);
			// return (check++);
		else
			*command_path = NULL;
		j++;
		free(tmp);
	}
	// free(argv);
	return (check);
}

int	check_path(char *argv, char **envp, char **command_path)
{
	int		i;
	char	**paths;
	int		check;

	check = 0;
	path_to_array(&paths, envp);
	if (!(paths))
		return (check);
	i = 2;
	check = check_path2(paths, argv, command_path);
	free_all(paths);
	return (check);
}

int	get_arg_list_size(t_mhstruct *mh)
{
	int		i;
	t_token	*tmp;

	tmp = mh->token;
	i = 0;
	if (!mh->token)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_arg_array(t_mhstruct *mh)
{
	char	**out;
	int		i;
	t_token	*token;

	token = mh->token;
	i = get_arg_list_size(mh);
	out = (char **)malloc((i + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (token != NULL)
	{
		out[i] = ft_strdup(token->data);	
		token = token->next;
		i++;
	}
	out[i] = NULL;
	return (out);
}

void	execve_of_commands(t_mhstruct *mh)
{
	int		pid;
	char	**arg;
	char	**env;
	char	*path = NULL;
	int 	out;
	
	out = 0;
	env = get_env_array(mh); //don,t forget to free env
	arg = get_arg_array(mh); //don,t forget to free env
	if (check_path(arg[0], env, &path) == 0)
	{
		if(access(arg[0], R_OK) == 0)
			path = arg[0];
		else
		{
		free(env);
		free(arg);
		return (pr_err(mh, 127, gemsg(mh->emsg[11], mh->emsg[12], arg[0])));
		}
	}
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			out++;
			execve(path, arg, env);
		}
		else
			waitpid(pid, &out, 0);
	}
	mh->er_num = out / 256;
	free(env);
	free(arg);
	return ;
}

// bash-3.2$ ./minishell 
// $> unset PATH
// $> ls
// Segmentation fault: 11
// bash-3.2$ 