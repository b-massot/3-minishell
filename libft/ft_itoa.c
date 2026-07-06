/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:53:43 by bmassot           #+#    #+#             */
/*   Updated: 2026/03/18 09:07:10 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_size(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*new;
	long	nb;
	int		len;
	int		is_negative;

	nb = (long)n;
	len = int_size(nb);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	is_negative = 0;
	if (nb < 0)
	{
		is_negative = 1;
		nb = -nb;
		new[0] = '-';
	}
	while (len > is_negative)
	{
		new[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (new);
}
/*
#include <stdio.h>
int	main()
{
	int test = -1234;
	int test2 = 0;
	printf("%s\n", ft_itoa(test));
	printf("%s\n", ft_itoa(test2));

	return (0);
}
*/
