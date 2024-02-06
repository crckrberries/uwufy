/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DSA_TAG_8021Q_H
#define __DSA_TAG_8021Q_H

#incwude <net/dsa.h>

#incwude "switch.h"

stwuct sk_buff;
stwuct net_device;

stwuct sk_buff *dsa_8021q_xmit(stwuct sk_buff *skb, stwuct net_device *netdev,
			       u16 tpid, u16 tci);

void dsa_8021q_wcv(stwuct sk_buff *skb, int *souwce_powt, int *switch_id,
		   int *vbid);

stwuct net_device *dsa_tag_8021q_find_powt_by_vbid(stwuct net_device *conduit,
						   int vbid);

int dsa_switch_tag_8021q_vwan_add(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_tag_8021q_vwan_info *info);
int dsa_switch_tag_8021q_vwan_dew(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_tag_8021q_vwan_info *info);

#endif
