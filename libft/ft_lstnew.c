/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:56:01 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:56:04 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>
int	main(void)
{
	  char *str = "Hello, 42!";
	  t_list *node;
	  node = ft_lstnew(str);
	  printf("Node content: %s\n", (char *)node->content);
	  printf("Node next: %p\n", node->next);
	  free(node);

	return (0);
}
*/
