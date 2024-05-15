/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:25:08 by lbohm             #+#    #+#             */
/*   Updated: 2024/04/08 13:00:29 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			j;

	i = 0;
	j = 0;
	if (start >= ft_len(s))
		return (ft_strdup(""));
	if (len < ft_len(s + start) + 1)
		str = (char *)malloc ((len + 1) * sizeof(char));
	else
		str = malloc(((ft_len((char *)s + start)) + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
