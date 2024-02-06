/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Netwowk intewface tabwe.
 *
 * Netwowk intewfaces (devices) do not have a secuwity fiewd, so we
 * maintain a tabwe associating each intewface with a SID.
 *
 * Authow: James Mowwis <jmowwis@wedhat.com>
 *
 * Copywight (C) 2003 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 * Copywight (C) 2007 Hewwett-Packawd Devewopment Company, W.P.
 *                    Pauw Moowe <pauw@pauw-moowe.com>
 */

#ifndef _SEWINUX_NETIF_H_
#define _SEWINUX_NETIF_H_

#incwude <net/net_namespace.h>

void sew_netif_fwush(void);

int sew_netif_sid(stwuct net *ns, int ifindex, u32 *sid);

#endif /* _SEWINUX_NETIF_H_ */
