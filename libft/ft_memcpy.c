/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halilakbas <halilakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:10:28 by hakbas            #+#    #+#             */
/*   Updated: 2023/10/12 19:22:43 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (0);
	d = (char *)dst;
	s = (const char *)src;
	while (n)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dst);
}
