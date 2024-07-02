/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:41:55 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/02 13:59:46 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*fetch_prompt_str(t_env *ms_env);

char	*parse_prompt(t_env *ms_env)
{
	char	*input;
	char	*prompt;

	prompt = fetch_prompt_str(ms_env);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (!input)
		exit_builtin(NULL, &ms_env);
	if (input && *input)
		add_history(input);
	return (input);
}

static char	*fetch_prompt_str(t_env *ms_env)
{
	char			*user;
	char			*cwd;
	char			*dir;
	static	char	prompt[PATH_MAX];

	user = get_env_value("USER", ms_env);
	if (!user)
		user = "UNKNOWN";
	cwd	= get_env_value("CWD", ms_env);
	if (!cwd)
		cwd = "/UNKNOWN";
	dir = ft_strrchr(cwd, '/') + 1;
	if (!ft_strncmp(cwd, "/", 2))
		dir = "ROOT";
	ft_bzero(prompt, ft_strlen(prompt));
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, "@", PATH_MAX);
	ft_strlcat(prompt, dir, PATH_MAX);
	return (prompt);
}
