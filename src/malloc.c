/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:01:28 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/09 20:26:26 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

static t_heap	g_heap;

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
}

// TODO - switch  case?
void	*malloc(size_t size)
{
	enum e_mem_type	type;
	void			*ptr;

	type = __get_mem_type(size);
	if (type == TINY)
		ptr = __allocate_tiny(&g_heap, size);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	return ;
}
