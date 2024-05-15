/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:08:52 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/08 17:33:43 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;

	str = malloc((ft_len(s) + 1) * sizeof(char));
	if (!(str))
		return (0);
	ft_strlcpy(str, s, ft_len(s) + 1);
	return (str);
}
