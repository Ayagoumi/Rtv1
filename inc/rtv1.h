/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:05:37 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/18 17:54:49 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct	s_vec3
{
	double x;
	double y;
	double z;
}				t_vec3;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}				t_ray;

typedef struct	s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	zoom;
}				t_camera;

typedef struct	s_sphere
{
	t_vec3	pos;
	double	r;
	int		color;
}				t_sphere;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Event			event;
}						t_sdl;

typedef struct			s_rtv1
{
	t_sdl				sdl;
	int					*data;
    int                 still_running;
}						t_rtv1;

int			sdl_init_texture(t_rtv1	*rtv);
int         sdl_init_render(t_rtv1   *rtv);
int			sdl_init_win(t_rtv1	*rtv);

void		process_input(t_rtv1 *rtv);

double		vec_length(t_vec3 vec);
t_vec3		plus(t_vec3 a, t_vec3 b);
t_vec3		minus(t_vec3 a, t_vec3 b);
t_vec3		mult(t_vec3 a, t_vec3 b);
t_vec3		mult2(double t, t_vec3 b);
t_vec3		divide(t_vec3 b, double t);
double		dot(t_vec3    a, t_vec3 b);
t_vec3		cross(t_vec3 a, t_vec3 b);
t_vec3		normalize(t_vec3 vec);

#endif
