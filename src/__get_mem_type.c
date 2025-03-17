/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __get_mem_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:52:47 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/17 16:24:47 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

enum e_mem_type	__get_mem_type(size_t payload_size)
{
	if (payload_size + sizeof(t_block_header) <= MAX_TINY_BLOCK_SIZE)
		return (TINY);
	else if (payload_size + sizeof(t_block_header) <= MAX_SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}
