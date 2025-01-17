/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:02:10 by rhvidste          #+#    #+#             */
/*   Updated: 2025/01/17 17:49:33 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_error(char *argv, bool flag)
{
	if (flag == true)
	{
		write(2, "pipex: ", 8);
		perror(argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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
	free_array(mypaths);
	return (0);
}

void	cmd_exec(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	if (ft_strchr(command[0], '/'))
		path = command[0];
	else
		path = path_parsing(command[0], envp);
	if (execve(path, command, envp) == -1)
	{
		free_array(command);
		ft_error(argv, true);
	}
}
