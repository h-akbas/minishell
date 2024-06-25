/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <halilakbas1992@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:24:19 by hakbas            #+#    #+#             */
/*   Updated: 2023/10/12 21:57:52 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(src);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, len + 1);
	dst[len] = '\0';
	return (dst);
}
