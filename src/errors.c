/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:13:58 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/15 22:09:46 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	check_line_length(char *line, t_cache *data)
{
	int	in_number;
	int	i;
	int	line_length;

	line_length = 0;
	i = 0;
	in_number = 0;
	while (line[i])
	{
		if (line[i] == ',')
			i += 9;
		if (ft_isdigit(line[i]) && !in_number)
		{
			in_number = 1;
			line_length++;
		}
		else
			in_number = 0;
		i++;
	}
	if (line_length > 500)
		line_length = 500;
	if (line_length != data->width)
		return (-1);
	return (0);
}
