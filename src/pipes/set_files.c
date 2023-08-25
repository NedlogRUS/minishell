/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:25:48 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/24 16:42:19 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	set_outfile(int *outfile, char **argv, int argc)
{
	int	i;

	i = 3;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error_msg2("Error\nNot enough arguments!");
		*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		// do_here_doc(argv[2]);
	}
	else
	{
		*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		i = 2;
	}
	return (i);
}

int	setting_in_files(int *infile, char **argv, char **envp)
{
	int	result;
	int	check;

	result = 0;
	check = check_command(argv[2], envp);
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
	{
		if (check)
		{
			*infile = open(argv[1], O_RDONLY, 0644);
			if (*infile == -1)
				write(1, "No such file or directory\n", 26);
		}
		else if (check_command(argv[2], envp) == 0 || *infile == -1)
		{
			*infile = open("TEMPORARYFILETODELETE", O_RDONLY | O_CREAT, 0644);
			if (*infile == -1)
				error_msg2("Error\nInput file opening error/not found");
			result = 1;
		}
	}
	return (result);
}

int	setting_out_files(char **argv, int *outfile, int argc)
{
	int	i;

	i = set_outfile(outfile, argv, argc);
	return (i);
}
