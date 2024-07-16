/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:17:21 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 14:10:36 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

static char	*get_var_pos(char *input);
static void	create_first_part(char *first_part, char **input, char *var);
static void	update_input(char **input, char *var, char *second_part);

void	expand_vars(char **input, t_env *ms_env)
{
	char	*var_pos;
	char	*var_name;
	char	*var_value;
	int		size;

	var_pos = get_var_pos(*input);
	if (var_pos)
	{
		size = 0;
		while (is_varname(var_pos[size + 1]))
			size++;
		var_name = ft_substr(var_pos, 1, size);
		*var_pos = '\0';
		var_value = get_env_value(var_name, ms_env);
		update_input(input, var_value, var_pos + size + 1);
		free (var_name);
		expand_vars(input, ms_env);
	}
}

static char	*get_var_pos(char *input)
{
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && is_varname(input[1]))
					return (input);
				input++;
			}
		}
		if (*input == '$' && is_varname(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

static void	create_first_part(char *first_part, char **input, char *var)
{
	if (!*input[0] && !var)
		first_part = ft_strdup("");
	else if (!*input[0] && var)
		first_part = ft_strdup(var);
	else if (!var)
		first_part = ft_strdup(*input);
	else
		first_part = ft_strjoin(*input, var);
}

static void	update_input(char **input, char *var, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	create_first_part(first_part, input, var);
	if (!first_part)
	{
		free (*input);
		*input = NULL;
		return ;
	}
	updated_input = ft_strjoin(first_part, second_part);
	if (!updated_input)
	{
		free(first_part);
		free(*input);
		first_part = NULL;
		*input = NULL;
		return ;
	}
	free(first_part);
	free(*input);
	*input = updated_input;
}
