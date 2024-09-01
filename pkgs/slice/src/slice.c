/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:42:58 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/23 13:42:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slice.h"

t_slice	*create_byte_slice(uint64_t len)
{
	t_slice	*res;

	res = malloc(sizeof(t_slice));
	if (!res)
		return (NULL);
	res->p = malloc(len);
	if (!res)
		return (free(res), NULL);
	res->l = len;
	res->c = len;
	return (res);
}
