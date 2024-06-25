/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <halilakbas1992@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:19:01 by hakbas            #+#    #+#             */
/*   Updated: 2023/10/12 21:19:07 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;
	char	ch;

	last_occurrence = 0;
	ch = (char)c;
	while (1)
	{
		if (*s == ch)
			last_occurrence = (char *)s;
		if (*s == '\0')
			return (last_occurrence);
		s++;
	}
	return (0);
}
