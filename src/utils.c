/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:02:10 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/17 15:48:26 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_error(char *argv, bool flag)
{
	if (flag == true)
	{
		//write(2, "1\n", 2);
		//ft_printf("pipex :");
		write(2, "pipex: ", 8);
		//write(2, argv, ft_strlen(argv));
		if (errno != ENOENT)
		        errno = ENOENT;  // Force "No such file or directory" error
		write(2, "pipex: ", 8);
		perror(argv);
		//write(2, ": Is a directory\n", 15);
		exit(EXIT_FAILURE);
	}
	else
	{
		//write(2, "2\n", 2);
		perror("error");
		exit(EXIT_FAILURE);
	}
}

char	*path_parsing(char *command, char **envp)
{
	char	**mypaths;
	char	*onepath;
	char	*fullpath;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	mypaths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (mypaths[i])
	{
		onepath = ft_strjoin(mypaths[i], "/");
		fullpath = ft_strjoin(onepath, command);
		free(onepath);
		if (access(fullpath, F_OK) == 0)
			return (fullpath);
		i++;
	}
	return (0);
}

void	cmd_exec(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	path = path_parsing(command[0], envp);
	if (execve(path, command, envp) == -1)
	{
		//write(2, "exec fail\n", 10);
		ft_error(argv, true);
	}
}
