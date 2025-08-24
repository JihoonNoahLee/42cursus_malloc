/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:01:28 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 20:11:22 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

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

	type = _get_mem_type(size);
	if (type == TINY)
		ptr = _allocate_tiny(&g_heap, size);
	else if (type == SMALL)
		ptr = _allocate_small(&g_heap, size);
	else if (type == LARGE)
		ptr = _allocate_large(&g_heap, size);
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

// TODO - malloc이 된 적 없을때 에러 없는지 검토 & large malloc에 아마 충돌 있을거임
void	show_alloc_mem(void)
{
	const t_pool_header	*minimum_pool;
	const t_pool_header	*last_pool;
	size_t				allocated_bytes;

	allocated_bytes = 0;
	minimum_pool = _get_next_min_pool(g_heap, NULL);
	last_pool = _get_last_pool_in_heap(g_heap);
	while (1)
	{
		if (minimum_pool == NULL || last_pool == NULL)
			break ;
		if (minimum_pool->pool_size == TINY_POOL_SIZE)
			_show_alloc_mem_pool(minimum_pool, TINY);
		else if (minimum_pool->pool_size == SMALL_POOL_SIZE)
			_show_alloc_mem_pool(minimum_pool, SMALL);
		else
			_show_alloc_mem_pool(minimum_pool, LARGE);
		allocated_bytes += _get_allocated_bytes(minimum_pool);
		if (minimum_pool == last_pool)
			break ;
		minimum_pool = _get_next_min_pool(g_heap, minimum_pool);
	}
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(allocated_bytes, 1);
	ft_putstr_fd(" bytes\n", 1);
}
