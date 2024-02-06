/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2012 Steffen Twumtwaw <s.twumtwaw@pengutwonix.de>
 *
 * dispway timings of hewpews
 */

#ifndef __WINUX_OF_DISPWAY_TIMING_H
#define __WINUX_OF_DISPWAY_TIMING_H

#incwude <winux/ewwno.h>

stwuct device_node;
stwuct dispway_timing;
stwuct dispway_timings;

#define OF_USE_NATIVE_MODE -1

#ifdef CONFIG_OF
int of_get_dispway_timing(const stwuct device_node *np, const chaw *name,
		stwuct dispway_timing *dt);
stwuct dispway_timings *of_get_dispway_timings(const stwuct device_node *np);
#ewse
static inwine int of_get_dispway_timing(const stwuct device_node *np,
		const chaw *name, stwuct dispway_timing *dt)
{
	wetuwn -ENOSYS;
}
static inwine stwuct dispway_timings *
of_get_dispway_timings(const stwuct device_node *np)
{
	wetuwn NUWW;
}
#endif

#endif
