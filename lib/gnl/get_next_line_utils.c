/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enbuyuk <enbuyuk@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:48:31 by enbuyuk           #+#    #+#             */
/*   Updated: 2025/01/08 04:12:16 by enbuyuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*ft_gnl_lstnew(char *content)
{
	t_line	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->length = 0;
	new_node->next = NULL;
	return (new_node);
}

t_line	*ft_gnl_lstlast(t_line *lst)
{
	t_line	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_gnl_lstadd_back(t_line **lst, t_line *new)
{
	t_line	*tmp;

	tmp = ft_gnl_lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

void	ft_gnl_lstclear(t_line **lst, void (*del)(void *))
{
	t_line	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp->content);
		free(temp);
	}
	*lst = NULL;
}

void	*ft_gnl_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			alloc_size;
	size_t			i;

	alloc_size = nmemb * size;
	ptr = malloc(alloc_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < alloc_size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
