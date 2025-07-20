/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:01:28 by jihoolee          #+#    #+#             */
/*   Updated: 2025/07/20 22:30:44 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

static t_heap	g_heap = {0, };

void	free(void *ptr)
{
	t_block_header	*block;

	if (ptr == NULL)
		return ;
	(void)block;
	block = (t_block_header *)(ptr - sizeof(t_block_header));
}

void	*malloc(size_t size)
{
	enum e_mem_type	type;
	void			*ptr;

	type = __get_mem_type(size);
	if (type == TINY)
		ptr = __allocate_tiny(&g_heap, size);
	else if (type == SMALL)
		ptr = __allocate_small(&g_heap, size);
	else if (type == LARGE)
		ptr = __allocate_large(&g_heap, size);
	else
		ptr = NULL;
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	(void)ptr;
	(void)size;
	new_ptr = NULL;
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	t_pool_header	*pools;

	pools = __sort_pools_by_address(g_heap);

	while (pools)
	{
		if (pools->pool_size == TINY_POOL_SIZE)
			__show_alloc_mem_pool(pools, TINY);
		else if (pools->pool_size == SMALL_POOL_SIZE)
			__show_alloc_mem_pool(pools, SMALL);
		else
			__show_alloc_mem_pool(pools, LARGE);
		pools = pools->next;
	}
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(__get_allocated_bytes(g_heap.tiny_pool)
		+ __get_allocated_bytes(g_heap.small_pool)
		+ __get_allocated_bytes_large(g_heap.large_pool), 1);
	ft_putstr_fd(" bytes\n", 1);
}
