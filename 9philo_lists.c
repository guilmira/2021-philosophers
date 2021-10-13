/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9philo_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:01:42 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/13 10:11:49 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/** PURPOSE : clears linked list from first element to last, including content
 * Its important to remember that all elements of content of the
 * list must be allocated. */
void	ft_fullclear(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

/** PURPOSE : adds new node to the enf of the list.
 * 1. Advances list to the last element.
 * 2. Inserts newer element at the back of the list. */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
	}
}

/** PURPOSE : allocates space for a new node with content.
 * 1. Outputs address of the newly created node. */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *) malloc(1 * sizeof(*node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
