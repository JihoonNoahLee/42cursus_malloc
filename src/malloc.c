/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:01:28 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/13 18:31:21 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

static t_heap	g_heap = {0, };

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
	if (g_heap.tiny_pool)
		__show_alloc_mem_pool(g_heap.tiny_pool, "TINY");
	if (g_heap.small_pool)
		__show_alloc_mem_pool(g_heap.small_pool, "SMALL");
	if (g_heap.large_pool)
		__show_alloc_mem_pool(g_heap.large_pool, "LARGE");
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(__get_total_allocated_bytes(g_heap.tiny_pool)
		+ __get_total_allocated_bytes(g_heap.small_pool)
		+ __get_total_allocated_bytes(g_heap.large_pool), 1);
	ft_putstr_fd(" bytes\n", 1);
}
