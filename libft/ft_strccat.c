/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:51:11 by elemarch          #+#    #+#             */
/*   Updated: 2014/11/06 15:03:56 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strccat(char *dest, const char *src)
{
	char	*nstr;
	int		i;

	i = 0;
	nstr = ft_strnew(ft_strlen(src) + ft_strlen(dest) + 2);
	while (dest && dest[i])
	{
		nstr[i] = dest[i];
		i++;
	}
	i = 0;
	while (src && src[i])
	{
		nstr[ft_strlen(dest) + i] = src[i];
		i++;
	}
	return (nstr);
}
