/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __PS_H__
#define __PS_H__

#incwude "wwcowe.h"
#incwude "acx.h"

int ww1271_ps_set_mode(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       enum ww1271_cmd_ps_mode mode);
void ww12xx_ps_wink_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  u8 hwid, boow cwean_queues);
void ww12xx_ps_wink_end(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 hwid);

#define WW1271_PS_COMPWETE_TIMEOUT 500

#endif /* __WW1271_PS_H__ */
