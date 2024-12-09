/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:30:54 by lumarque          #+#    #+#             */
/*   Updated: 2024/12/06 06:21:33 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	int				i;

	if (!n)
		return (s);
	i = -1;
	p = s;
	while (n-- > 0)
		p[++i] = (unsigned char) c;
	return (s);
}
