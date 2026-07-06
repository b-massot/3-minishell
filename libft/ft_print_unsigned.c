/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:03:49 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/22 10:03:51 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Calcule le nombre de chiffres d'un unsigned int */
int	ft_num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/* Convertit un unsigned int en chaîne de caractères */
char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

/* Affiche un unsigned int et retourne le nombre de caractères écrits */
int	ft_print_unsigned(unsigned int n)
{
	int		length;
	char	*num;

	length = 0;
	if (n == 0)
		length += write(1, "0", 1);
	else
	{
		num = ft_uitoa(n);
		length += ft_print_str(num);
		free(num);
	}
	return (length);
}
