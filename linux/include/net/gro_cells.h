/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_GWO_CEWWS_H
#define _NET_GWO_CEWWS_H

#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>

stwuct gwo_ceww;

stwuct gwo_cewws {
	stwuct gwo_ceww __pewcpu	*cewws;
};

int gwo_cewws_weceive(stwuct gwo_cewws *gcewws, stwuct sk_buff *skb);
int gwo_cewws_init(stwuct gwo_cewws *gcewws, stwuct net_device *dev);
void gwo_cewws_destwoy(stwuct gwo_cewws *gcewws);

#endif
