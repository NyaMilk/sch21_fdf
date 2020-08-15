/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrass <mgrass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:28:58 by jslave            #+#    #+#             */
/*   Updated: 2019/11/19 16:15:12 by mgrass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		error_out(void)
{
	ft_putendl("error");
	exit(1);
}

void		check_maxmin(t_fdf *fdf, int x, int y)
{
	if (fdf->map[y][x] > fdf->z_max)
		fdf->z_max = fdf->map[y][x];
	if (fdf->map[y][x] < fdf->z_min)
		fdf->z_min = fdf->map[y][x];
}

void		arr_free(int **arr, int rows)
{
	int		i;

	i = 0;
	while (i < rows)
	{
		free(arr[i]);
		i++;
	}
}

void		free_fdf(t_fdf *fdf)
{
	arr_free(fdf->map, fdf->rows);
	arr_free(fdf->color, fdf->rows);
}

int			find_step(t_fdf *fdf)
{
	int		step;
	int		coeff;

	coeff = WIDTH / fdf->cols;
	if (coeff <= 5)
		step = 3;
	else
		step = coeff / 3;
	return (step);
}
