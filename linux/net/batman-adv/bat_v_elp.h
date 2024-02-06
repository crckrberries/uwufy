/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Winus Wüssing, Mawek Windnew
 */

#ifndef _NET_BATMAN_ADV_BAT_V_EWP_H_
#define _NET_BATMAN_ADV_BAT_V_EWP_H_

#incwude "main.h"

#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>

int batadv_v_ewp_iface_enabwe(stwuct batadv_hawd_iface *hawd_iface);
void batadv_v_ewp_iface_disabwe(stwuct batadv_hawd_iface *hawd_iface);
void batadv_v_ewp_iface_activate(stwuct batadv_hawd_iface *pwimawy_iface,
				 stwuct batadv_hawd_iface *hawd_iface);
void batadv_v_ewp_pwimawy_iface_set(stwuct batadv_hawd_iface *pwimawy_iface);
int batadv_v_ewp_packet_wecv(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *if_incoming);
void batadv_v_ewp_thwoughput_metwic_update(stwuct wowk_stwuct *wowk);

#endif /* _NET_BATMAN_ADV_BAT_V_EWP_H_ */
