/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:22:57 by mzutter           #+#    #+#             */
/*   Updated: 2025/08/31 17:30:05 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(float degrees)
{
	return (degrees * M_PI / 180);
}

float	rad_to_deg(float rad)
{
	return (rad * 180 / M_PI);
}
