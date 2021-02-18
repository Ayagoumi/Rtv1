/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:27:57 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/18 17:56:40 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** This is tems of cords
**
** equation of a shpere is: x^2 + y^2 + z^2 = R^2
** which means the same distance from the origin of the cam to the hit point to the power of 2 ( name "P" )
** and it will give us P^2 = R^2
**
** But in terms of vectors
** this is the equation of the sphere in vectors
** The hit point is in (P - C)^2 = R^2
** 
*/
