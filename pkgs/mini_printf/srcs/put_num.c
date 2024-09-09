/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:42:58 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/04 11:33:10 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_printf.h"

int	put_d(int32_t num)
{
	char	buffer[INT32_BUF_LEN];
	char	*ptr;
	int		is_negative;

	if (num == INT32_MIN)
		return (write(1, INT32_MIN_STR, INT32_BUF_LEN));
	ptr = buffer + INT32_BUF_LEN;
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
	return (write(1, ptr, buffer + INT32_BUF_LEN - ptr));
}

int	put_u(uint32_t num)
{
	char	buffer[UINT32_BUF_LEN];
	char	*ptr;

	ptr = buffer + UINT32_BUF_LEN;
	while (1)
	{
		*(--ptr) = '0' + (num % 10);
		num /= 10;
		if (num == 0)
			break ;
	}
	return (write(1, ptr, buffer + UINT32_BUF_LEN - ptr));
}

int	put_ld(int64_t num)
{
	char	buffer[INT64_BUF_LEN];
	char	*ptr;
	int		is_negative;

	if (num == INT64_MIN)
		return (write(1, INT64_MIN_STR, INT64_BUF_LEN));
	ptr = buffer + INT64_BUF_LEN;
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
	return (write(1, ptr, buffer + INT64_BUF_LEN - ptr));
}

int	put_lu(uint64_t num)
{
	char	buffer[UINT64_BUF_LEN];
	char	*ptr;

	ptr = buffer + UINT64_BUF_LEN;
	while (1)
	{
		*(--ptr) = '0' + (num % 10);
		num /= 10;
		if (num == 0)
			break ;
	}
	return (write(1, ptr, buffer + UINT64_BUF_LEN - ptr));
}
