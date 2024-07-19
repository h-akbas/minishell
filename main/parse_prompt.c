/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:41:55 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:26:20 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*create_prompt_str(t_env *ms_env);

char	*parse_prompt(t_env *ms_env)
{
	char	*input;
	char	*prompt;

	prompt = create_prompt_str(ms_env);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (!input)
		builtin_exit(NULL, &ms_env);
	if (input && *input)
		add_history(input);
	return (input);
}

static char	*create_prompt_str(t_env *ms_env)
{
	char		*user;
	char		*cwd;
	char		*dir;
	static char	prompt[PATH_MAX];

	user = get_env_value("USER", ms_env);
	if (!user)
		user = "unknown_user";
	cwd = get_env_value("PWD", ms_env);
	if (!cwd)
		cwd = "/unknown_dir";
	dir = ft_strrchr(cwd, '/') + 1;
	if (!ft_strncmp(cwd, "/", 2))
		dir = "root";
	ft_bzero(prompt, ft_strlen(prompt));
	ft_strlcat(prompt, "\e[0;32m", PATH_MAX);
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, "\e[0m", PATH_MAX);
	ft_strlcat(prompt, "@", PATH_MAX);
	ft_strlcat(prompt, "\e[0;34m", PATH_MAX);
	ft_strlcat(prompt, dir, PATH_MAX);
	ft_strlcat(prompt, "\e[0m", PATH_MAX);
	ft_strlcat(prompt, " ", PATH_MAX);
	return (prompt);
}
