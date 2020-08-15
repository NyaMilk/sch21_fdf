/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrass <mgrass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:18:12 by mgrass            #+#    #+#             */
/*   Updated: 2019/11/19 12:25:56 by mgrass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			check_color(char *line)
{
	int		count;

	count = 0;
	line++;
	if (*line && *line != '0')
		error_out();
	line++;
	if (*line && *line != 'x')
		error_out();
	line++;
	count += 2;
	while (*line && *line != ' ')
	{
		if ((*line < 'A' || *line > 'F') && (*line < 'a' || *line > 'f') &&
		(*line < '0' || *line > '9'))
			error_out();
		line++;
		count++;
	}
	if (count != 8 && count != 6 && count != 4)
		error_out();
	return (count);
}

void		check_line(char *line)
{
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (*line == '-')
			line++;
		if (*line < '0' || *line > '9')
			error_out();
		while (*line != '\0' && *line >= '0' && *line <= '9')
			line++;
		if (*line == ',')
			line += check_color(line) + 1;
		if (*line && *line != ' ')
			error_out();
		while (*line && *line == ' ')
			line++;
	}
}

int			check_size(t_fdf *fdf, char *line)
{
	char	**tmp;
	int		x;

	x = 0;
	check_line(line);
	tmp = ft_strsplit(line, ' ');
	while (tmp[x])
		free(tmp[x++]);
	if (fdf->rows == 0)
		fdf->cols = x;
	else
	{
		if (x != fdf->cols)
			return (0);
	}
	free(line);
	free(tmp);
	fdf->rows++;
	return (1);
}
