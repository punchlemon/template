/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:19:09 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/09 22:24:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_mini_printf.h"

int	main(void)
{
	test_put_d();
	test_put_u();
	test_put_ld();
	test_put_lu();
	test_put();
	test_put_char();
	test_print_count();
	test_put_arg();
	test_mini_printf();
	return (0);
}
