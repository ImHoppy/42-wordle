/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:08:07 by wluong            #+#    #+#             */
/*   Updated: 2022/05/15 17:09:12 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

# include <iostream>

enum Colors : uint32_t {
	BG			= 0x181818FF,
	BORDER		= 0x696969FF,
	INCORRECT	= 0x939598FF,
	GREEN		= 0x538D4EFF,
	YELLOW		= 0xB59F3BFF
};

#endif