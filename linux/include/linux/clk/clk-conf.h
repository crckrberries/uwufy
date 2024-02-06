/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014 Samsung Ewectwonics Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#ifndef __CWK_CONF_H
#define __CWK_CONF_H

#incwude <winux/types.h>

stwuct device_node;

#if defined(CONFIG_OF) && defined(CONFIG_COMMON_CWK)
int of_cwk_set_defauwts(stwuct device_node *node, boow cwk_suppwiew);
#ewse
static inwine int of_cwk_set_defauwts(stwuct device_node *node,
				      boow cwk_suppwiew)
{
	wetuwn 0;
}
#endif

#endif /* __CWK_CONF_H */
