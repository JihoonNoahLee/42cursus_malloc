/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pool_traversal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:47:35 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/04 02:11:54 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "__malloc_core.h"

// TODO - understand this with wrong logic differnece
// static const t_pool_header	*__get_next_min_addr_pool(
// 	const t_pool_header *prev_min,
// 	const t_pool_header *pool)
// {
// 	const t_pool_header	*next_min;

// 	next_min = pool;
// 	while (pool)
// 	{
// 		if (pool > prev_min && pool < next_min)
// 			next_min = pool;
// 		pool = pool->next;
// 	}
// 	return (next_min);
// }

static const t_pool_header	*__get_next_min_addr_pool(
	const t_pool_header *prev_min,
	const t_pool_header *pool)
{
	const t_pool_header	*next_min;

	next_min = NULL;
	while (pool)
	{
		if (pool > prev_min && (next_min == NULL || pool < next_min))
			next_min = pool;
		pool = pool->next;
	}
	return (next_min);
}

const t_pool_header	*_get_next_min_pool(const t_heap g_heap,
										const t_pool_header *current_min)
{
	const t_pool_header	*next_tiny;
	const t_pool_header	*next_small;
	const t_pool_header	*next_large;
	const t_pool_header	*result;

	next_tiny = __get_next_min_addr_pool(current_min, g_heap.tiny_pool);
	next_small = __get_next_min_addr_pool(current_min, g_heap.small_pool);
	next_large = __get_next_min_addr_pool(current_min, g_heap.large_pool);
	result = NULL;
	printf("next_tiny: %p, next_small: %p, next_large: %p\n", next_tiny, next_small, next_large);
	if (next_tiny != NULL && (result == NULL || next_tiny < result))
		result = next_tiny;
	if (next_small != NULL && (result == NULL || next_small < result))
		result = next_small;
	if (next_large != NULL && (result == NULL || next_large < result))
		result = next_large;
	printf("current: %p, result: %p\n", current_min, result);
	return (result);
}

static const t_pool_header	*__get_max_addr_pool(const t_pool_header *pool)
{
	const t_pool_header	*max;

	max = pool;
	while (pool)
	{
		if (pool > max)
			max = pool;
		pool = pool->next;
	}
	return (max);
}

const t_pool_header	*_get_last_pool_in_heap(const t_heap g_heap)
{
	const t_pool_header	*tiny_last;
	const t_pool_header	*small_last;
	const t_pool_header	*large_last;

	tiny_last = __get_max_addr_pool(g_heap.tiny_pool);
	small_last = __get_max_addr_pool(g_heap.small_pool);
	large_last = __get_max_addr_pool(g_heap.large_pool);
	if (tiny_last > small_last && tiny_last > large_last)
		return (tiny_last);
	else if (small_last > tiny_last && small_last > large_last)
		return (small_last);
	else
		return (large_last);
}
