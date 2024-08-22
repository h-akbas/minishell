/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:27:27 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/22 13:34:23 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

static bool	is_directory(char **args);
static char	*get_cd_path(char **args, t_env *ms_env, t_cd_params *params);
static char	*construct_path(char **args);
static char	*get_home_subdir_path(char **args, t_env *ms_env);

int	cd(char **args, t_env *ms_env)
{
	t_cd_params params;

	params.is_dir_flag = is_directory(args);
	params.home_subdir = args[1] && !ft_strncmp(args[1], "~/", 2);
	params.path = get_cd_path(args, ms_env, &params);
	if (args[1] && args[2] && !params.is_dir_flag)
		return (print_error_msg("cd", "too many arguments"));
	if (params.path == NULL)
	{
		print_error_msg("cd", "Bad address");
		return (EXIT_FAILURE);
	}
	if (chdir(params.path) != 0)
	{
		if (params.is_dir_flag || params.home_subdir)
			free(params.path);
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	if (str_equal(args[1], "-"))
		ft_putendl_fd(params.path, 1);
	if (params.is_dir_flag || params.home_subdir)
		free(params.path);
	update_wd(ms_env);
	return (EXIT_SUCCESS);
}

static bool	is_directory(char **args)
{
	char		*dirname;
	struct stat	statbuf;
	bool		is_dir_flag;

	is_dir_flag = false;
	dirname = construct_path(args);
	if (dirname == NULL)
		return (false);
	if (stat(dirname, &statbuf) == 0)
		is_dir_flag = S_ISDIR(statbuf.st_mode);
	free(dirname);
	return (is_dir_flag);
}

char	*get_cd_path(char **args, t_env *ms_env, t_cd_params *params)
{
	char	*path;

	if (!args[1] || str_equal(args[1], "~"))
		path = get_env_value("HOME", ms_env);
	else if (args[1] && str_equal(args[1], "-"))
		path = get_env_value("OLDPWD", ms_env);
	else if (params->home_subdir)
		path = get_home_subdir_path(args, ms_env);
	else if (params->is_dir_flag)
		path = construct_path(args);
	else
		path = args[1];
	return (path);
}

static char	*construct_path(char **args)
{
	char	*path;
	int		i;

	path = ft_calloc(PATH_MAX, PATH_MAX);
	if (!path)
		return (NULL);
	i = 1;
	while (args[i])
	{
		ft_strlcat(path, args[i], PATH_MAX);
		if (args[i + 1])
			ft_strlcat(path, " ", PATH_MAX);
		i++;
	}
	return (path);
}

static char	*get_home_subdir_path(char **args, t_env *ms_env)
{
	char	*home;
	char	*path;

	home = get_env_value("HOME", ms_env);
	if (!home)
		return (NULL);
	path = ft_calloc(PATH_MAX, sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, home, PATH_MAX);
	ft_strlcat(path, args[1] + 1, PATH_MAX);
	return (path);
}
