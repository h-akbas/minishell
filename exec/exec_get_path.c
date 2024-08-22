/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:49:21 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/22 14:01:39 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdbool.h>
#include <unistd.h>

static void	create_path(char *dst, const char *part1, const char *part2, \
						const char *part3);
static bool	is_relative_or_absolute_path(const char *cmd);
static char	*resolve_local_path(char *cmd, t_env *ms_env);
static char	*search_in_path(const char *cmd, char **paths);

char	*get_path(char *cmd, t_env *ms_env)
{
	char	*path_env;
	char	**paths;
	char	*resolved_path;

	if (is_relative_or_absolute_path(cmd))
		return (resolve_local_path(cmd, ms_env));
	path_env = get_env_value("PATH", ms_env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	resolved_path = search_in_path(cmd, paths);
	free_array(paths);
	return (resolved_path);
}

static void	create_path(char *dst, const char *part1, const char *part2, \
						const char *part3)
{
	*dst = '\0';
	ft_strlcat(dst, part1, PATH_MAX);
	ft_strlcat(dst, part2, PATH_MAX);
	ft_strlcat(dst, part3, PATH_MAX);
}

static bool	is_relative_or_absolute_path(const char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
		return (true);
	if (cmd[0] == '/')
		return (true);
	return (false);
}

static char	*resolve_local_path(char *cmd, t_env *ms_env)
{
	char	full_path[PATH_MAX];

	if (*cmd == '/')
		return (ft_strdup(cmd));
	full_path[0] = '\0';
	create_path(full_path, get_env_value("PWD", ms_env), "/", cmd);
	return (ft_strdup(full_path));
}

static char	*search_in_path(const char *cmd, char **paths)
{
	char	current_path[PATH_MAX];

	while (*paths)
	{
		create_path(current_path, *paths, "/", cmd);
		if (access(current_path, F_OK) == 0)
			return (ft_strdup(current_path));
		paths++;
	}
	return (NULL);
}