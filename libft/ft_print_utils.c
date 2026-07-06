/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:04:03 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/22 10:04:05 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Affiche un caractère et retourne le nombre de caractères écrits (1) */
int	ft_print_chr(int c)
{
	write(1, &c, 1);
	return (1);
}

/* Affiche une chaîne de caractères (sans retourner de valeur) */
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

/* Affiche une chaîne et retourne sa longueur (ou "(null)" si NULL) */
int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

/* Convertit un entier en chaîne et l'affiche, 
retourne le nombre de caractères */
int	ft_print_num(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_print_str(num);
	free(num);
	return (len);
}
