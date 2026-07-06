/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:54:22 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:54:25 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list *head = NULL;
	head = malloc(sizeof(t_list));
	if (!head)
		return 1;
	head->content = "HEAD";
	head->next = NULL;

	// Deuxieme node crée qui viendra se mettre avant la head
	t_list *front = malloc(sizeof(t_list));
	front->content = "FRONT";
	front->next = NULL;

	// On fait le switch
	ft_lstadd_front(&head, front);

	printf("Head content: %s\n", (char *)head->content); // résultat inversé
	printf("Front content: %s\n", (char *)head->next->content);
	t_list *tmp;
	while (head)
	{
		tmp = head->next;
		
		free(head);
		//free(head->content) // Seulement si on a malloc le content avant!!!
		head = tmp;
	}
	if (head == NULL)
		printf("La liste est vide, addresse: %p\n", head);
	return (0);
}
*/
