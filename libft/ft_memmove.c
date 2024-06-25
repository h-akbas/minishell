/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halilakbas <halilakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:22:12 by hakbas            #+#    #+#             */
/*   Updated: 2023/10/12 19:23:06 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (0);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d < s || d >= s + len)
	{
		while (len--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d += len;
		s += len;
		while (len--)
		{
			*(--d) = *(--s);
		}
	}
	return (dst);
}
