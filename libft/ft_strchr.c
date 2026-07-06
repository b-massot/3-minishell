/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:59:17 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:59:19 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i] && ptr[i] != (unsigned char)c)
		i++;
	if (ptr[i] == (unsigned char)c)
		return (&ptr[i]);
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char *test = "Hello comment";
	char *test1 = ft_strchr(test, 'c');
	printf("%s\n", test1);
    return (0);
}
*/
