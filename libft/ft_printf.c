/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:02:48 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/22 10:02:51 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_format prend un pointeur sur va_list (va_list *args). On passe un pointeur
** pour éviter de copier va_list par valeur (sans va_copy) — cela prévient
** les comportements non-portables(ex: macOS/arm64).
*/
int	ft_format(va_list *args, const char spec)
{
	if (spec == 'c')
		return (ft_print_chr(va_arg(*args, int)));
	else if (spec == 's')
		return (ft_print_str(va_arg(*args, char *)));
	else if (spec == 'p')
		return (ft_print_ptr(va_arg(*args, void *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_print_num(va_arg(*args, int)));
	else if (spec == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int)));
	else if (spec == 'x' || spec == 'X')
		return (ft_print_hex(va_arg(*args, unsigned int), spec));
	else if (spec == '%')
		return (ft_print_chr('%'));
	return (0);
}

int	ft_printf(const char *spec, ...)
{
	size_t		i;
	va_list		args;
	int			length;

	if (!spec)
		return (-1);
	i = 0;
	length = 0;
	va_start(args, spec);
	while (spec[i])
	{
		if (spec[i] == '%')
		{
			length += ft_format(&args, spec[i + 1]);
			i++;
		}
		else
			length += ft_print_chr(spec[i]);
		i++;
	}
	va_end(args);
	return (length);
}
