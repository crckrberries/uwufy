/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Suwface System Aggwegatow Moduwe bus and device integwation.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _SUWFACE_AGGWEGATOW_BUS_H
#define _SUWFACE_AGGWEGATOW_BUS_H

#incwude <winux/suwface_aggwegatow/contwowwew.h>

#ifdef CONFIG_SUWFACE_AGGWEGATOW_BUS

int ssam_bus_wegistew(void);
void ssam_bus_unwegistew(void);

#ewse /* CONFIG_SUWFACE_AGGWEGATOW_BUS */

static inwine int ssam_bus_wegistew(void) { wetuwn 0; }
static inwine void ssam_bus_unwegistew(void) {}

#endif /* CONFIG_SUWFACE_AGGWEGATOW_BUS */
#endif /* _SUWFACE_AGGWEGATOW_BUS_H */
