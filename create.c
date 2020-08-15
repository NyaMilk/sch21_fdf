/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrass <mgrass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:21:20 by mgrass            #+#    #+#             */
/*   Updated: 2019/11/19 17:15:08 by mgrass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_background(t_fdf *fdf)
{
	int		i;

	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (i % WIDTH < MENU_WIDTH)
			(fdf->img_data)[i] = 0x272727;
		else
			(fdf->img_data)[i] = 0x323232;
		i++;
	}
}

void		create_color_map(char *tmp, t_fdf *fdf, int x, int y)
{
	char	**ptr;

	ptr = ft_strsplit(tmp, ',');
	if (ptr[1])
	{
		fdf->color[y][x] = ft_atoi_base(ptr[1] + 2, 16);
		free(ptr[1]);
	}
	else
		fdf->color[y][x] = 1;
	free(ptr[0]);
	free(ptr);
}

void		create_map(t_fdf *fdf)
{
	char	*line;
	char	**tmp;
	int		x;
	int		y;

	y = 0;
	while ((get_next_line(fdf->fd, &line)) == 1)
	{
		x = 0;
		tmp = ft_strsplit(line, ' ');
		fdf->map[y] = ft_memalloc(sizeof(int) * fdf->cols);
		fdf->color[y] = ft_memalloc(sizeof(int) * fdf->cols);
		while (tmp[x])
		{
			create_color_map(tmp[x], fdf, x, y);
			fdf->map[y][x] = ft_atoi(tmp[x]);
			check_maxmin(fdf, x, y);
			free(tmp[x++]);
		}
		free(line);
		free(tmp);
		y++;
	}
	create_color(fdf);
}

void		init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF");
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->img_data = (int *)mlx_get_data_addr(fdf->img_ptr, &(fdf->bpp),
		&(fdf->size_line), &(fdf->endian));
	fdf->resize = 1;
	fdf->step = find_step(fdf);
	fdf->x_start = ((WIDTH - (fdf->cols * fdf->step * fdf->resize)
		+ MENU_WIDTH) / 2);
	fdf->y_start = ((HEIGHT - (fdf->rows * fdf->step * fdf->resize)) / 2);
	if (!(fdf->map = ft_memalloc(sizeof(int *) * fdf->rows)))
		error_out();
	if (!(fdf->color = ft_memalloc(sizeof(int *) * fdf->rows)))
		error_out();
	fdf->z_coeff = 0;
}

t_fdf		*read_file(char *s)
{
	t_fdf	*fdf;
	char	*line;

	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		error_out();
	fdf->cols = 0;
	fdf->rows = 0;
	fdf->z_max = 0;
	fdf->z_min = 0;
	fdf->step = 0;
	fdf->name = s;
	fdf->dimension = 'n';
	fdf->x_offset = 0;
	fdf->y_offset = 0;
	if ((fdf->fd = open(s, O_RDONLY)) < 0)
		error_out();
	while ((get_next_line(fdf->fd, &line)) == 1)
	{
		if (!(check_size(fdf, line)))
			error_out();
	}
	init_fdf(fdf);
	close(fdf->fd);
	fdf->fd = open(fdf->name, O_RDONLY);
	return (fdf);
}
