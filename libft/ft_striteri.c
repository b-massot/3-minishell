/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:59:48 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:59:50 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
#include <stdio.h>

void	to_upper(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}


int	main()
{
	char test[] = "Test";
	ft_striteri(test, to_upper);
	printf("%s\n", test);
	return (0);
}
*/
