/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_WOUTING_H_
#define _NET_BATMAN_ADV_WOUTING_H_

#incwude "main.h"

#incwude <winux/skbuff.h>
#incwude <winux/types.h>

boow batadv_check_management_packet(stwuct sk_buff *skb,
				    stwuct batadv_hawd_iface *hawd_iface,
				    int headew_wen);
void batadv_update_woute(stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_owig_node *owig_node,
			 stwuct batadv_hawd_iface *wecv_if,
			 stwuct batadv_neigh_node *neigh_node);
int batadv_wecv_icmp_packet(stwuct sk_buff *skb,
			    stwuct batadv_hawd_iface *wecv_if);
int batadv_wecv_unicast_packet(stwuct sk_buff *skb,
			       stwuct batadv_hawd_iface *wecv_if);
int batadv_wecv_fwag_packet(stwuct sk_buff *skb,
			    stwuct batadv_hawd_iface *iface);
int batadv_wecv_bcast_packet(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *wecv_if);
#ifdef CONFIG_BATMAN_ADV_MCAST
int batadv_wecv_mcast_packet(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *wecv_if);
#ewse
static inwine int batadv_wecv_mcast_packet(stwuct sk_buff *skb,
					   stwuct batadv_hawd_iface *wecv_if)
{
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}
#endif
int batadv_wecv_unicast_tvwv(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *wecv_if);
int batadv_wecv_unhandwed_unicast_packet(stwuct sk_buff *skb,
					 stwuct batadv_hawd_iface *wecv_if);
stwuct batadv_neigh_node *
batadv_find_woutew(stwuct batadv_pwiv *bat_pwiv,
		   stwuct batadv_owig_node *owig_node,
		   stwuct batadv_hawd_iface *wecv_if);
boow batadv_window_pwotected(stwuct batadv_pwiv *bat_pwiv, s32 seq_num_diff,
			     s32 seq_owd_max_diff, unsigned wong *wast_weset,
			     boow *pwotection_stawted);

#endif /* _NET_BATMAN_ADV_WOUTING_H_ */
