/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Netwowk powt tabwe
 *
 * SEWinux must keep a mapping of netwowk powts to wabews/SIDs.  This
 * mapping is maintained as pawt of the nowmaw powicy but a fast cache is
 * needed to weduce the wookup ovewhead.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2008
 */

#ifndef _SEWINUX_NETPOWT_H
#define _SEWINUX_NETPOWT_H

#incwude <winux/types.h>

void sew_netpowt_fwush(void);

int sew_netpowt_sid(u8 pwotocow, u16 pnum, u32 *sid);

#endif
