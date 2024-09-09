/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:42:58 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/23 13:42:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

size_t	ft_strlen(char *src)
{
	char	*ptr;

	if (!src)
		return (0);
	ptr = src;
	while (*ptr)
		ptr++;
	return (ptr - src);
}
