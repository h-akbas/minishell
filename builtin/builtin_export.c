/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:51:26 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/20 13:48:17 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	declare_env(t_env *ms_env);
static t_env	*merge(t_env *a, t_env *b);
static void		split_list(t_env *src, t_env **front_ref, t_env **back_ref);
static void		merge_sort(t_env **head_ref);

int	builtin_export(char **args, t_env **ms_env)
{
	char	*key_pair;
	char	*varname;
	int		exit_stat;

	args++;
	exit_stat = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*ms_env));
	while (*args)
	{
		key_pair = *args;
		varname = get_name_only(key_pair);
		if (!valid_varname(varname) || str_equal(key_pair, "="))
		{
			print_varname_error("export", key_pair);
			exit_stat = EXIT_FAILURE;
		}
		else if (get_env_node(varname, *ms_env))
			update_env_var(varname, get_value_only(key_pair), *ms_env);
		else
			append_list(key_pair, ms_env);
		free(varname);
		args++;
	}
	exit(exit_stat);
}

static int	declare_env(t_env *ms_env)
{
	t_env	*tmp;

	merge_sort(&ms_env);
	tmp = ms_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(get_name_only(tmp->key_pair), STDOUT_FILENO);
		if (ft_strchr(tmp->key_pair, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(get_value_only(tmp->key_pair), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

static t_env	*merge(t_env *a, t_env *b)
{
	t_env	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strncmp(a->key_pair, b->key_pair, ft_strlen(a->key_pair)) <= 0)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return (result);
}

static void		split_list(t_env *src, t_env **front_ref, t_env **back_ref)
{
	t_env	*fast;
	t_env	*slow;

	if (src == NULL || src->next == NULL)
	{
		*front_ref = src;
		*back_ref = NULL;
		return ;
	}
	slow = src;
	fast = src->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = src;
	*back_ref = slow->next;
	slow->next = NULL;
	return ;
}

static void		merge_sort(t_env **head_ref)
{
	t_env	*head;
	t_env	*a;
	t_env	*b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = merge(a, b);
}
