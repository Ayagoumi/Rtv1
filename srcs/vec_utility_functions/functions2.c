/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:13:52 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/04 16:14:32 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

double		vec_length(t_vec3 vec)
{
	double	length;

	length = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (length);
}

double		dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3		cross(t_vec3 a, t_vec3 b)
{
	t_vec3		res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_vec3		normalize(t_vec3 vec)
{
	return (divide(vec, vec_length(vec)));
}
