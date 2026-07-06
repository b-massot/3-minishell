/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:51:32 by bmassot           #+#    #+#             */
/*   Updated: 2026/03/24 14:27:41 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_to_int(const char *str, int *i, int sign)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = (result * 10) + (str[*i] - '0');
		if (result > 2147483647)
		{
			if (sign > 0)
				return (INT_MAX);
			return (INT_MIN);
		}
		(*i)++;
	}
	return ((int)(result * sign));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	return (ft_digit_to_int(str, &i, sign));
}
