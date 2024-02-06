/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __OSDEP_INTF_H_
#define __OSDEP_INTF_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

#define WND4(x)	(((x >> 2) + ((x & 3) != 0)) << 2)

stwuct intf_pwiv {
	u8 *intf_dev;
	/* when in USB, IO is thwough intewwupt in/out endpoints */
	stwuct usb_device *udev;
	stwuct uwb *pioww_uwb;
	stwuct compwetion io_wetevt_comp;
};

int w871x_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);

#endif	/*_OSDEP_INTF_H_*/
