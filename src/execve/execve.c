/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:47 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/31 01:42:04 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path2(char **paths, char *argv, char **command_path)
{
	int			j;
	char		*tmp;
	struct stat	s;

	j = 0;
	while (paths[j] != NULL)
	{
		*command_path = ft_strjoin("/", argv);
		tmp = ft_strdup(*command_path);
		free(*command_path);
		*command_path = ft_strjoin(paths[j], tmp);
		free(tmp);
		stat(*command_path, &s);
		if (access(*command_path, R_OK) == 0
			&& S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR))
			return (1);
		else
		{
			free(*command_path);
			*command_path = NULL;
		}
		j++;
	}
	return (0);
}

int	check_path(char *argv, char **envp, char **command_path)
{
	char	**paths;
	int		check;

	check = 0;
	(paths) = NULL;
	if (ft_strchr(argv, '/'))
		return (check);
	path_to_array(&paths, envp);
	if (!(paths))
		return (check);
	check = check_path2(paths, argv, command_path);
	free_all(paths);
	return (check);
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

int	execve_of_commands_2(char *path, char **arg, char **env)
{
	int	pid;
	int	out;

	out = 0;
	pid = fork();
	signal(SIGINT, do_sigint_fork);
	signal(SIGQUIT, do_sigquit);
	if (pid == 0)
	{
		out++;
		execve(path, arg, env);
	}
	else
	{
		waitpid(pid, &out, 0);
		free_all(arg);
		free_all(env);
		free(path);
	}
	return (out);
}

void	execve_of_commands(t_mhstruct *mh)
{
	char		**arg;
	char		**env;
	char		*path;
	struct stat	s;

	path = NULL;
	env = get_env_array(mh);
	arg = get_arg_array(mh);
	if (check_path(arg[0], env, &path) == 0)
	{
		stat(arg[0], &s);
		if (access(arg[0], R_OK) == 0
			&& S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR))
			reassign_path(&path, arg);
		else
		{
			free_all(env);
			pr_err(mh, 127, gemsg(mh->emsg[11], mh->emsg[12], arg[0]));
			free_all(arg);
			return ;
		}
	}
	if (path != NULL)
		g_error = execve_of_commands_2(path, arg, env) / 256;
}
