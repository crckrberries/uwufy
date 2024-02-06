/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#ifndef __WW1251_PS_H__
#define __WW1251_PS_H__

#incwude "ww1251.h"
#incwude "acx.h"

int ww1251_ps_set_mode(stwuct ww1251 *ww, enum ww1251_station_mode mode);
void ww1251_ps_ewp_sweep(stwuct ww1251 *ww);
int ww1251_ps_ewp_wakeup(stwuct ww1251 *ww);
void ww1251_ewp_wowk(stwuct wowk_stwuct *wowk);


#endif /* __WW1251_PS_H__ */
