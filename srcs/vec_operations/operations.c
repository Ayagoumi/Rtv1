/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:58:02 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/04 16:14:49 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_vec3		plus(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = (a.x + b.x);
	res.y = (a.y + b.y);
	res.z = (a.z + b.z);
	return (res);
}

t_vec3		minus(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = (a.x - b.x);
	res.y = (a.y - b.y);
	res.z = (a.z - b.z);
	return (res);
}

t_vec3		mult2(double t, t_vec3 b)
{
	t_vec3	res;

	res.x = (t * b.x);
	res.y = (t * b.y);
	res.z = (t * b.z);
	return (res);
}

t_vec3		mult(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = (a.x * b.x);
	res.y = (a.y * b.y);
	res.z = (a.z * b.z);
	return (res);
}

t_vec3		divide(t_vec3 b, double t)
{
	return (mult2((1 / t), b));
}
