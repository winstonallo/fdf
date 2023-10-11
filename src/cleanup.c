/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:39:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 20:39:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_structs(t_point **dots)
{
	int	i;
	
	i = 0;
	while (dots[i])
	{
		free(dots[i]);
		i++;
	}
	free(dots);
}