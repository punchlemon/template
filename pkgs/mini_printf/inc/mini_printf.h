/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:10:07 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/04 11:33:49 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PRINTF_H
# define MINI_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include "common.h"
# define INT32_BUF_LEN 11
# define UINT32_BUF_LEN 10
# define INT32_MIN_STR "-2147483648"
# define INT64_BUF_LEN 20
# define UINT64_BUF_LEN 20
# define INT64_MIN_STR "-9223372036854775808"

// function
int	put_d(int32_t num);
int	put_u(uint32_t num);
int	put_ld(int64_t num);
int	put_lu(uint64_t num);
int	put(char *src);
int	put_char(char c);
int	print_count(int res, int *count);
int	put_arg(char *s, size_t *i, va_list *args);
int	mini_printf(char *s, ...);

#endif
