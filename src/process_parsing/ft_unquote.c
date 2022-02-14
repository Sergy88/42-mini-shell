//
// Created by sergey on 14.02.2022.
//

#include "minishell.h"

static int cpy_unquote(char *src, char *dst)
{
	int quotes[2];
	int count;
	int i;
	int j;

	i = 0;
	j = 0;
	quotes[1] = 0;
	quotes[0] = 0;
	while (src[i])
	{
		if (((src[i] == '\'') && quotes[1]) || ((src[i] == '\"') && quotes[0]) ||
			((src[i] != '\"') && (src[i] != '\"')))
		{
			change_quote_flags(quotes, src + i);
			dst[j] = src[i];
			i++;
			j++;
		}else
		{
			change_quote_flags(quotes, src + i);
			i++;
		}
	}
	return (0);
}

static int count_len(char *str)
{
	int quotes[2];
	int count;

	count = 0;
	quotes[1] = 0;
	quotes[0] = 0;
	while (*str)
	{
		if (((*str == '\'') && quotes[1]) || ((*str == '\"') && quotes[0]) ||
			((*str != '\"') && (*str != '\"')))
		{
			count++;
		}
		change_quote_flags(quotes, str);
		str++;
	}
	return (count);
}

void ft_unquote(char **str_p)
{
	int len;
	char *s;
	char *result;

	s = *str_p;
	len = count_len(s);
	result = (char *)malloc(sizeof(len) + 1);
	result[len] = '\0';
	cpy_unquote(s, result);
	free(*str_p);
	*str_p = result;
}