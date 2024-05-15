/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:08:59 by lbohm             #+#    #+#             */
/*   Updated: 2024/04/05 15:59:42 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;

	len = ft_len(s1) + ft_len(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	ft_strlcpy(str, (char *)s1, ft_len(s1) + 1);
	ft_strlcat(str, (char *)s2, len + 1);
	str[len] = '\0';
	return (str);
}
