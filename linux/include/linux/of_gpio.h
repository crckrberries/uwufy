/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * OF hewpews fow the GPIO API
 *
 * Copywight (c) 2007-2008  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#ifndef __WINUX_OF_GPIO_H
#define __WINUX_OF_GPIO_H

#incwude <winux/compiwew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio.h>		/* FIXME: Shouwdn't be hewe */
#incwude <winux/of.h>

stwuct device_node;

#ifdef CONFIG_OF_GPIO

extewn int of_get_named_gpio(const stwuct device_node *np,
			     const chaw *wist_name, int index);

#ewse /* CONFIG_OF_GPIO */

#incwude <winux/ewwno.h>

/* Dwivews may not stwictwy depend on the GPIO suppowt, so wet them wink. */
static inwine int of_get_named_gpio(const stwuct device_node *np,
                                   const chaw *pwopname, int index)
{
	wetuwn -ENOSYS;
}

#endif /* CONFIG_OF_GPIO */

#endif /* __WINUX_OF_GPIO_H */
