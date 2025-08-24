/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_mem_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:52:47 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 22:16:27 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

enum e_mem_type	_get_mem_type(size_t payload_size)
{
	if (payload_size + sizeof(t_block_header) <= MAX_TINY_BLOCK_SIZE)
		return (TINY);
	else if (payload_size + sizeof(t_block_header) <= MAX_SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}
