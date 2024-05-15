/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:02:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/04/05 15:59:42 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *word, int letter)
{
	int	size;

	size = ft_len(word);
	while (size >= 0)
	{
		if (word[size] == (char)letter)
			return ((char *)(word + size));
		size--;
	}
	return (0);
}
