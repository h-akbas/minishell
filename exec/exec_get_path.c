/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:49:21 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:26:20 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdbool.h>
#include <unistd.h>

static void	create_path(char base[], char *part1, char *part2, char *part3);
static bool	is_path(char *cmd);
static char	*get_local_path(char *cmd, t_env *ms_env);

char	*get_path(char *cmd, t_env *ms_env)
{
	char	*path_env;
	char	**paths;
	char	current_path[PATH_MAX];
	char	**paths_start;

	if (is_path(cmd))
		return (get_local_path(cmd, ms_env));
	path_env = get_env_value("PATH", ms_env);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	paths_start = paths;
	while (paths && *paths)
	{
		create_path(current_path, *paths, "/", cmd);
		if (access(current_path, F_OK) == 0)
		{
			free_array(paths_start);
			return (ft_strdup(current_path));
		}
		paths++;
	}
	free_array(paths_start);
	return (NULL);
}

static void	create_path(char base[], char *part1, char *part2, char *part3)
{
	*base = '\0';
	ft_strlcat(base, part1, PATH_MAX);
	ft_strlcat(base, part2, PATH_MAX);
	ft_strlcat(base, part3, PATH_MAX);
}

static bool	is_path(char *cmd)
{
	if (*cmd == '.')
		cmd++;
	if (*cmd == '.')
		cmd++;
	return (*cmd == '/');
}

static char	*get_local_path(char *cmd, t_env *ms_env)
{
	char	full_path[PATH_MAX];

	if (*cmd == '/')
		return (ft_strdup(cmd));
	full_path[0] = '\0';
	create_path(full_path, get_env_value("PWD", ms_env), "/", cmd);
	return (ft_strdup(full_path));
}
