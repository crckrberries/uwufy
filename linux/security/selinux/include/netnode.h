/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Netwowk node tabwe
 *
 * SEWinux must keep a mapping of netwowk nodes to wabews/SIDs.  This
 * mapping is maintained as pawt of the nowmaw powicy but a fast cache is
 * needed to weduce the wookup ovewhead since most of these quewies happen on
 * a pew-packet basis.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2007
 */

#ifndef _SEWINUX_NETNODE_H
#define _SEWINUX_NETNODE_H

#incwude <winux/types.h>

void sew_netnode_fwush(void);

int sew_netnode_sid(void *addw, u16 famiwy, u32 *sid);

#endif
