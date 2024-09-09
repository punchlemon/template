/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mini_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:32:44 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/09 22:22:19 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_mini_printf.h"

void	test_put(void)
{
	put(NULL);
	put("\n");
	put("Hello world!");
	put("\n");
	put("");
	put("\n");
}

void	test_put_char(void)
{
	put_char('a');
	put_char('\n');
	put_char('b');
	put_char('\n');
	put_char('c');
	put_char('\n');
}

void	test_print_count(void)
{
	int	count;

	put_d(print_count(5, NULL));
	put("\n");
	count = 2;
	put_d(count);
	put("\n");
	put_d(print_count(-1, &count));
	put("\n");
	count = 2;
	put_d(count);
	put("\n");
	put_d(print_count(0, &count));
	put("\n");
	count = 2;
	put_d(count);
	put("\n");
	put_d(print_count(5, &count));
	put("\n");
}

void	test_put_arg(void)
{
}

void	test_mini_printf(void)
{
	mini_printf("test%s%d\n", "hello", 42);
	mini_printf("%ld%d%d%ctest%a", 9223372036854775806, 42, 43, 'a');
	mini_printf("%");
	mini_printf("\n");
}
