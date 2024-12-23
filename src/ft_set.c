/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:13:56 by bgoron            #+#    #+#             */
/*   Updated: 2024/11/28 19:34:55 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fract_ol.h"
#include <string.h>

void	set_values(int x, int y, int choice, t_fractol *f)
{
	double	s;

	s = (double)W / (double)H;
	if (choice == 1)
	{
		f->s->c_r = map_fract_x(x / f->m->zoom + f->m->movx, -2.5 * s, 1.5 * s);
		f->s->c_i = map_fract_y(y / f->m->zoom + f->m->movy, -2, 2);
		f->s->z_r = 0;
		f->s->z_i = 0;
	}
	else if (choice == 2)
	{
		f->s->z_r = map_fract_x(x / f->m->zoom + f->m->movx, -2 * s, 2 * s);
		f->s->z_i = map_fract_y(y / f->m->zoom + f->m->movy, -2, 2);
	}
	if (choice == 3)
	{
		f->s->c_r = map_fract_x(x / f->m->zoom + f->m->movx, -2.5 * s, 1.5 * s);
		f->s->c_i = map_fract_y(y / f->m->zoom + f->m->movy, -2.5, 1.5);
		f->s->z_r = 0;
		f->s->z_i = 0;
	}
}

void	ft_allocator(t_fractol **f)
{
	*f = malloc(sizeof(t_fractol));
	if (!*f)
		return ;
	memset(*f, 0, sizeof(t_fractol));

	(*f)->s = malloc(sizeof(t_set));
	if (!(*f)->s)
		return ;
	memset((*f)->s, 0, sizeof(t_set));

	(*f)->m = malloc(sizeof(t_move));
	if (!(*f)->m)
		return ;
	memset((*f)->m, 0, sizeof(t_move));

	(*f)->c = malloc(sizeof(t_color));
	if (!(*f)->c)
		return ;
	memset((*f)->c, 0, sizeof(t_color));
}

t_fractol *init_fractol(int ac, char **av, t_fractol **f)
{
    ft_allocator(f);
    if (!*f)
        return (NULL);

    (*f)->iter = 100;
    (*f)->m->zoom = 1;
    (*f)->m->pix = 1;
    (*f)->leftclick = 0;
    (*f)->rightclick = 0;
    (*f)->s->av = choose_fractal(av);
    set_values(0, 0, (*f)->s->av, *f);

    if (ac >= 2)
    {
        if (ac == 4)
        {
            (*f)->s->c_r = ft_atof(av[2]);
            (*f)->s->c_i = ft_atof(av[3]);
        }
        (*f)->mlx = mlx_init();
        (*f)->win = mlx_new_window((*f)->mlx, W, H, "Fract.ol");
        (*f)->img = mlx_new_image((*f)->mlx, W, H);
    }
    return (*f);
}

unsigned int	mandelbrot_julia(t_fractol *f)
{
	int		i;
	double	tmp;
	double	z_r;
	double	z_i;

	i = 0;
	z_r = f->s->z_r;
	z_i = f->s->z_i;
	while (((z_r * z_r) + (z_i * z_i) < 4 && i < f->iter))
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + f->s->c_r;
		z_i = 2 * tmp * z_i + f->s->c_i;
		i++;
	}
	if (i == f->iter)
		return (0);
	return (get_color(i, f));
}

unsigned int	burning_ship(t_fractol *f)
{
	int		i;
	double	tmp;
	double	z_r;
	double	z_i;

	i = 0;
	z_r = f->s->z_r;
	z_i = f->s->z_i;
	while (((z_r * z_r) + (z_i * z_i) < 4 && i < f->iter))
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + f->s->c_r;
		z_i = 2 * fabs(tmp * z_i) + f->s->c_i;
		i++;
	}
	if (i == f->iter)
		return (0);
	return (get_color(i, f));
}
