/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:42:58 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/23 13:42:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

int	put(char *src)
{
	if (!src)
		return (write(1, "(null)", 6));
	return (write(1, src, ft_strlen(src)));
}

int	put_num(int64_t num)
{
	char	buffer[20];
	char	*ptr;
	int		is_negative;

	if (num == INT64_MIN)
		return (write(1, INTMIN_ADDR, 20));
	ptr = buffer + 20;
	is_negative = num < 0;
	if (is_negative)
		num = -num;
	while (1)
	{
		*(--ptr) = '0' + (num % 10);
		num /= 10;
		if (num == 0)
			break ;
	}
	if (is_negative)
		*(--ptr) = '-';
	return (write(1, ptr, buffer + 20 - ptr));
}
