/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:03:34 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/22 10:03:36 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Calcule le nombre de chiffres hexadécimaux d'une adresse */
int	ft_len_ptr(uintptr_t num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

/* Affiche une adresse en hexadécimal (récursif) */
void	ft_put_ptr(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_put_ptr(ptr / 16);
		ft_put_ptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

/* uintptr_t	addr;  Type portable pour stocker des adresses */
/* Affiche un pointeur au format "0x..." sur MacOS ou "(nil)" sur Linux, 
retourne la longueur */
int	ft_print_ptr(void *ptr)
{
	int			length;
	uintptr_t	addr;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	length = 2;
	addr = (uintptr_t)ptr;
	ft_put_ptr(addr);
	length += ft_len_ptr(addr);
	return (length);
}
