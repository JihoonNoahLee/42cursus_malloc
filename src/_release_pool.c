/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _release_pool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:18:48 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 23:50:10 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

void	__remove_pool_from_heap(t_pool_header *pool,
								t_pool_header **p_pool_head)
{
	t_pool_header	**current;

	current = p_pool_head;
	while (*current)
	{
		if (*current == pool)
		{
			*current = (*current)->next;
			munmap(pool, pool->pool_size);
			return ;
		}
		current = &((*current)->next);
	}
}

void	_release_pool(t_pool_header *pool, t_heap *const p_heap)
{
	t_pool_header	*pool_head;

	if (pool->pool_size == TINY_POOL_SIZE)
		__remove_pool_from_heap(pool, &p_heap->tiny_pool);
	else if (pool->pool_size == SMALL_POOL_SIZE)
		__remove_pool_from_heap(pool, &p_heap->small_pool);
	else
		__remove_pool_from_heap(pool, &p_heap->large_pool);
}
