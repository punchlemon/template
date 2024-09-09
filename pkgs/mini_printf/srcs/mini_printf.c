/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:32:14 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/04 11:32:15 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_printf.h"

int	put(char *src)
{
	if (!src)
		return (write(1, "(null)", 6));
	return (write(1, src, ft_strlen(src)));
}

int	put_char(char c)
{
	return (write(1, &c, 1));
}

int	print_count(int res, int *count)
{
	if (!count)
		return (-1);
	if (res == -1)
		return (*count = -1, *count);
	else
		return (*count += res, *count);
}

int	put_arg(char *s, size_t *i, va_list *args)
{
	(*i)++;
	if (s[*i] == '%')
		return (put_char('%'));
	else if (s[*i] == 'c')
		return (put_char((char)va_arg(*args, int)));
	else if (s[*i] == 's')
		return (put((char *)va_arg(*args, char *)));
	else if (s[*i] == 'u')
		return (put_u((uint32_t)va_arg(*args, uint32_t)));
	else if (s[*i] == 'd')
		return (put_d((int32_t)va_arg(*args, int32_t)));
	else if (s[*i] == 'l' && (s[*i + 1] == 'u' || s[*i + 1] == 'd'))
	{
		(*i)++;
		if (s[*i] == 'u')
			return (put_lu((uint64_t)va_arg(*args, uint64_t)));
		else if (s[*i] == 'd')
			return (put_ld((int64_t)va_arg(*args, int64_t)));
	}
	else
		(*i)--;
	return (0);
}

int	mini_printf(char *s, ...)
{
	va_list	args;
	int		count;
	size_t	i;

	va_start(args, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
			print_count(put_arg(s, &i, &args), &count);
		else
			print_count(put_char(s[i]), &count);
		if (count == -1)
			break ;
		i++;
	}
	va_end(args);
	return (count);
}
