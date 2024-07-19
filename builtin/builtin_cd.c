/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:27:27 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:26:20 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <readline/chardefs.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

static bool	is_dir(char **args);
static char	*get_cd_path(char **args, t_env *ms_env, bool home_subdir, \
				bool is_dir_flag);
static char	*parse_dir_name(char **args);
static char	*parse_home_subdir(char **args, t_env *ms_env);

int	cd(char **args, t_env *ms_env)
{
	char	*path;
	bool	home_subdir;
	bool	is_dir_flag;

	is_dir_flag = is_dir(args);
	home_subdir = args[1] && !ft_strncmp(args[1], "~/", 2);
	path = get_cd_path(args, ms_env, home_subdir, is_dir_flag);
	if (args[1] && args[2] && !is_dir_flag)
	{
		free(path);
		return (print_error_msg("cd", "too many arguments"));
	}
	if (chdir(path) != 0)
	{
		if (is_dir_flag || home_subdir)
			free(path);
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	if (is_dir_flag || home_subdir)
		free(path);
	update_wd(ms_env);
	return (EXIT_SUCCESS);
}

static bool	is_dir(char **args)
{
	char		*dirname;
	struct stat	statbuf;

	dirname = parse_dir_name(args);
	if (!dirname)
		return (false);
	if (stat(dirname, &statbuf) != 0)
	{
		free(dirname);
		return (false);
	}
	free(dirname);
	return (S_ISDIR(statbuf.st_mode));
}

char	*get_cd_path(char **args, t_env *ms_env, bool home_subdir, \
			bool is_dir_flag)
{
	char	*path;

	if (!args[1] || str_equal(args[1], "~"))
	{
		path = get_env_value("HOME", ms_env);
		if (!path)
			path = get_env_value("__HOME", ms_env);
	}
	else if (args[1] && str_equal(args[1], "-"))
		path = get_env_value("OLDPWD", ms_env);
	else if (home_subdir)
		path = parse_home_subdir(args, ms_env);
	else if (is_dir_flag)
		path = parse_dir_name(args);
	else
		path = args[1];
	return (path);
}

static char	*parse_dir_name(char **args)
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

static char	*parse_home_subdir(char **args, t_env *ms_env)
{
	char	*home;
	char	*path;

	home = get_env_value("HOME", ms_env);
	if (!home)
	{
		home = get_env_value("__HOME", ms_env);
		if (!home)
			return (NULL);
	}
	path = ft_calloc(PATH_MAX, PATH_MAX);
	if (!path)
		return (NULL);
	ft_strlcpy(path, home, PATH_MAX);
	ft_strlcat(path, args[1] + 1, PATH_MAX);
	return (path);
}
