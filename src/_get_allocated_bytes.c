/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_allocated_bytes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:19:56 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 20:08:34 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

size_t	_get_allocated_bytes(const t_pool_header *pool)
{
	t_block_header	*block_header;
	size_t			size;
	size_t			allocated_bytes;

	allocated_bytes = 0;
	block_header = (t_block_header *)(pool + 1);
	while ((void *)block_header < (void *)pool + pool->pool_size)
	{
		size = block_header->header & BLOCK_SIZE_MASK;
		if (block_header->header & BLOCK_USED_FLAG)
			allocated_bytes += size;
		block_header = (t_block_header *)(
				(void *)block_header + sizeof(t_block_header) + size);
	}
	return (allocated_bytes);
}
