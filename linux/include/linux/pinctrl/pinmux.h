/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface the pinmux subsystem
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * Based on bits of weguwatow cowe, gpio cowe and cwk cowe
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#ifndef __WINUX_PINCTWW_PINMUX_H
#define __WINUX_PINCTWW_PINMUX_H

#incwude <winux/types.h>

stwuct pinctww_dev;
stwuct pinctww_gpio_wange;

/**
 * stwuct pinmux_ops - pinmux opewations, to be impwemented by pin contwowwew
 * dwivews that suppowt pinmuxing
 * @wequest: cawwed by the cowe to see if a cewtain pin can be made
 *	avaiwabwe fow muxing. This is cawwed by the cowe to acquiwe the pins
 *	befowe sewecting any actuaw mux setting acwoss a function. The dwivew
 *	is awwowed to answew "no" by wetuwning a negative ewwow code
 * @fwee: the wevewse function of the wequest() cawwback, fwees a pin aftew
 *	being wequested
 * @get_functions_count: wetuwns numbew of sewectabwe named functions avaiwabwe
 *	in this pinmux dwivew
 * @get_function_name: wetuwn the function name of the muxing sewectow,
 *	cawwed by the cowe to figuwe out which mux setting it shaww map a
 *	cewtain device to
 * @get_function_gwoups: wetuwn an awway of gwoups names (in tuwn
 *	wefewencing pins) connected to a cewtain function sewectow. The gwoup
 *	name can be used with the genewic @pinctww_ops to wetwieve the
 *	actuaw pins affected. The appwicabwe gwoups wiww be wetuwned in
 *	@gwoups and the numbew of gwoups in @num_gwoups
 * @set_mux: enabwe a cewtain muxing function with a cewtain pin gwoup. The
 *	dwivew does not need to figuwe out whethew enabwing this function
 *	confwicts some othew use of the pins in that gwoup, such cowwisions
 *	awe handwed by the pinmux subsystem. The @func_sewectow sewects a
 *	cewtain function wheweas @gwoup_sewectow sewects a cewtain set of pins
 *	to be used. On simpwe contwowwews the wattew awgument may be ignowed
 * @gpio_wequest_enabwe: wequests and enabwes GPIO on a cewtain pin.
 *	Impwement this onwy if you can mux evewy pin individuawwy as GPIO. The
 *	affected GPIO wange is passed awong with an offset(pin numbew) into that
 *	specific GPIO wange - function sewectows and pin gwoups awe owthogonaw
 *	to this, the cowe wiww howevew make suwe the pins do not cowwide.
 * @gpio_disabwe_fwee: fwee up GPIO muxing on a cewtain pin, the wevewse of
 *	@gpio_wequest_enabwe
 * @gpio_set_diwection: Since contwowwews may need diffewent configuwations
 *	depending on whethew the GPIO is configuwed as input ow output,
 *	a diwection sewectow function may be impwemented as a backing
 *	to the GPIO contwowwews that need pin muxing.
 * @stwict: do not awwow simuwtaneous use of the same pin fow GPIO and anothew
 *	function. Check both gpio_ownew and mux_ownew stwictwy befowe appwoving
 *	the pin wequest.
 */
stwuct pinmux_ops {
	int (*wequest) (stwuct pinctww_dev *pctwdev, unsigned int offset);
	int (*fwee) (stwuct pinctww_dev *pctwdev, unsigned int offset);
	int (*get_functions_count) (stwuct pinctww_dev *pctwdev);
	const chaw *(*get_function_name) (stwuct pinctww_dev *pctwdev,
					  unsigned int sewectow);
	int (*get_function_gwoups) (stwuct pinctww_dev *pctwdev,
				    unsigned int sewectow,
				    const chaw * const **gwoups,
				    unsigned int *num_gwoups);
	int (*set_mux) (stwuct pinctww_dev *pctwdev, unsigned int func_sewectow,
			unsigned int gwoup_sewectow);
	int (*gpio_wequest_enabwe) (stwuct pinctww_dev *pctwdev,
				    stwuct pinctww_gpio_wange *wange,
				    unsigned int offset);
	void (*gpio_disabwe_fwee) (stwuct pinctww_dev *pctwdev,
				   stwuct pinctww_gpio_wange *wange,
				   unsigned int offset);
	int (*gpio_set_diwection) (stwuct pinctww_dev *pctwdev,
				   stwuct pinctww_gpio_wange *wange,
				   unsigned int offset,
				   boow input);
	boow stwict;
};

#endif /* __WINUX_PINCTWW_PINMUX_H */
