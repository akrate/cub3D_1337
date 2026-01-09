/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:58:38 by aoussama          #+#    #+#             */
/*   Updated: 2026/01/09 11:20:26 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_lst_garbage	*ft_lstnew(void *ptr)
{
	t_lst_garbage	*node;

	node = (t_lst_garbage *)malloc(sizeof(t_lst_garbage));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_garbage(t_lst_garbage **lst, t_lst_garbage *new_node)
{
	t_lst_garbage	*temp;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

void	*ft_malloc(size_t size, t_lst_garbage **head)
{
	void			*p;
	t_lst_garbage	*new;

	p = malloc(size);
	if (!p)
	{
		// ft_putstr_fd("Failed to allocate memory\n", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(2);
	}
	new = ft_lstnew(p);
	if (!new)
	{
		// ft_putstr_fd("Failed to allocate memory\n", 2);
		free(p);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(2);
	}
	ft_lstadd_back_garbage(head, new);
	return (p);
}

void	free_garbage(t_lst_garbage **head)
{
	t_lst_garbage	*current;
	t_lst_garbage	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	*head = NULL;
}

t_data	*set_get_data(void *p)
{
	static t_data	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}