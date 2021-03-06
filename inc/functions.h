/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:15:55 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/05 17:54:01 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "rtv1.h"

int			sdl_init_texture(t_rtv1	*rtv);
int			sdl_init_render(t_rtv1 *rtv);
int			sdl_init_win(t_rtv1	*rtv);
void		process_input(t_rtv1 *rtv);
double		map(int position, int max_wh, double new_min_scope
		, double new_max_scope);
void		cast_rays(t_rtv1 *rtv, char *file);
double		vec_length(t_vec3 vec);
t_vec3		plus(t_vec3 a, t_vec3 b);
t_vec3		minus(t_vec3 a, t_vec3 b);
t_vec3		mult(t_vec3 a, t_vec3 b);
t_vec3		mult2(double t, t_vec3 b);
t_vec3		divide(t_vec3 b, double t);
double		dot(t_vec3 a, t_vec3 b);
t_vec3		cross(t_vec3 a, t_vec3 b);
t_vec3		normalize(t_vec3 vec);
void		ft_cast_rays(t_rtv1 *rtv, t_scene *scene);
t_object	*raycast_object(t_ray r, t_hsno *hsno, t_scene *scene);
double		calc_intersect(t_ray r, t_object *object);
double		intersect_cone(t_ray r, t_object *cone);
double		intersect_cylinder(t_ray r, t_object *cylinder);
double		intersect_plane(t_ray r, t_object *plane);
double		intersect_sphere(t_ray r, t_object *sphere);
int			ft_get_full_color(t_hsno *hsno, t_scene *scene, t_ray *ray);
double		ft_get_specular(t_hsno *hsno, t_light *light);
double		ft_get_diffuse(t_hsno *hsno, t_light *light);
void		calc_surface_normal2(t_ray r, t_object *object, t_hsno *hsno);
void		calc_surface_normal(t_ray r, t_object *object, t_hsno *hsno);
t_vec3		get_ambiant(t_hsno *hsno);
double		ft_get_diffuse(t_hsno *hsno, t_light *light);
double		ft_get_specular(t_hsno *hsno, t_light *light);
int			shadow(t_ray *r, t_hsno *hsno, t_light *l, t_object *objects);
int			rgb_to_int(t_vec3 rgb);
void		declare_camera(t_ray *r, t_scene *scene, t_hsno *hsno, t_point *p);
void		calc_surface_normal(t_ray r, t_object *object, t_hsno *hsno);
void		calc_surface_normal2(t_ray r, t_object *object, t_hsno *hsno);

#endif
