/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM gpio

#if !defined(_TWACE_GPIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_GPIO_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(gpio_diwection,

	TP_PWOTO(unsigned gpio, int in, int eww),

	TP_AWGS(gpio, in, eww),

	TP_STWUCT__entwy(
		__fiewd(unsigned, gpio)
		__fiewd(int, in)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->gpio = gpio;
		__entwy->in = in;
		__entwy->eww = eww;
	),

	TP_pwintk("%u %3s (%d)", __entwy->gpio,
		__entwy->in ? "in" : "out", __entwy->eww)
);

TWACE_EVENT(gpio_vawue,

	TP_PWOTO(unsigned gpio, int get, int vawue),

	TP_AWGS(gpio, get, vawue),

	TP_STWUCT__entwy(
		__fiewd(unsigned, gpio)
		__fiewd(int, get)
		__fiewd(int, vawue)
	),

	TP_fast_assign(
		__entwy->gpio = gpio;
		__entwy->get = get;
		__entwy->vawue = vawue;
	),

	TP_pwintk("%u %3s %d", __entwy->gpio,
		__entwy->get ? "get" : "set", __entwy->vawue)
);

#endif /* if !defined(_TWACE_GPIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
