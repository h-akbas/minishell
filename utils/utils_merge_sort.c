/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_merge_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:30:46 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/31 19:37:48 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

static t_env	*merge(t_env *a, t_env *b);
static void		split_list(t_env *src, t_env **front_ref, t_env **back_ref);

void	merge_sort(t_env **head_ref)
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

static void	split_list(t_env *src, t_env **front_ref, t_env **back_ref)
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
