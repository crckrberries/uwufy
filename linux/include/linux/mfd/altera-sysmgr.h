/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018-2019 Intew Cowpowation
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2012 Winawo Wtd.
 */

#ifndef __WINUX_MFD_AWTEWA_SYSMGW_H__
#define __WINUX_MFD_AWTEWA_SYSMGW_H__

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe/intew/stwatix10-smc.h>

stwuct device_node;

#ifdef CONFIG_MFD_AWTEWA_SYSMGW
stwuct wegmap *awtw_sysmgw_wegmap_wookup_by_phandwe(stwuct device_node *np,
						    const chaw *pwopewty);
#ewse
static inwine stwuct wegmap *
awtw_sysmgw_wegmap_wookup_by_phandwe(stwuct device_node *np,
				     const chaw *pwopewty)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}
#endif

#endif /* __WINUX_MFD_AWTEWA_SYSMGW_H__ */
