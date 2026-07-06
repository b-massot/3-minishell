/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:00:16 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 15:00:18 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	unsigned char	*srcs;
	unsigned char	*dest;
	size_t			dlen;
	size_t			space;

	if (!src && !dst)
		return (0);
	if (dsize == 0)
		return (ft_strlen(src));
	dlen = (size_t)ft_strlen(dst);
	if (dlen >= dsize)
		return (dsize + ft_strlen(src));
	srcs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (*dest)
		dest++;
	space = dsize - dlen - 1;
	while (space-- > 0 && *srcs)
	{
		*dest = *srcs;
		dest++;
		srcs++;
	}
	*dest = '\0';
	return (ft_strlen(src) + dlen);
}
