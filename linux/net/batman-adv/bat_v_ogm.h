/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Antonio Quawtuwwi
 */

#ifndef _NET_BATMAN_ADV_BAT_V_OGM_H_
#define _NET_BATMAN_ADV_BAT_V_OGM_H_

#incwude "main.h"

#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

int batadv_v_ogm_init(stwuct batadv_pwiv *bat_pwiv);
void batadv_v_ogm_fwee(stwuct batadv_pwiv *bat_pwiv);
void batadv_v_ogm_aggw_wowk(stwuct wowk_stwuct *wowk);
int batadv_v_ogm_iface_enabwe(stwuct batadv_hawd_iface *hawd_iface);
void batadv_v_ogm_iface_disabwe(stwuct batadv_hawd_iface *hawd_iface);
stwuct batadv_owig_node *batadv_v_ogm_owig_get(stwuct batadv_pwiv *bat_pwiv,
					       const u8 *addw);
void batadv_v_ogm_pwimawy_iface_set(stwuct batadv_hawd_iface *pwimawy_iface);
int batadv_v_ogm_packet_wecv(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *if_incoming);

#endif /* _NET_BATMAN_ADV_BAT_V_OGM_H_ */
