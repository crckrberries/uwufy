/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_SEND_H_
#define _NET_BATMAN_ADV_SEND_H_

#incwude "main.h"

#incwude <winux/compiwew.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

void batadv_foww_packet_fwee(stwuct batadv_foww_packet *foww_packet,
			     boow dwopped);
stwuct batadv_foww_packet *
batadv_foww_packet_awwoc(stwuct batadv_hawd_iface *if_incoming,
			 stwuct batadv_hawd_iface *if_outgoing,
			 atomic_t *queue_weft,
			 stwuct batadv_pwiv *bat_pwiv,
			 stwuct sk_buff *skb);
boow batadv_foww_packet_steaw(stwuct batadv_foww_packet *packet, spinwock_t *w);
void batadv_foww_packet_ogmv1_queue(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_foww_packet *foww_packet,
				    unsigned wong send_time);
boow batadv_foww_packet_is_webwoadcast(stwuct batadv_foww_packet *foww_packet);

int batadv_send_skb_to_owig(stwuct sk_buff *skb,
			    stwuct batadv_owig_node *owig_node,
			    stwuct batadv_hawd_iface *wecv_if);
int batadv_send_skb_packet(stwuct sk_buff *skb,
			   stwuct batadv_hawd_iface *hawd_iface,
			   const u8 *dst_addw);
int batadv_send_bwoadcast_skb(stwuct sk_buff *skb,
			      stwuct batadv_hawd_iface *hawd_iface);
int batadv_send_unicast_skb(stwuct sk_buff *skb,
			    stwuct batadv_neigh_node *neigh_node);
int batadv_foww_bcast_packet(stwuct batadv_pwiv *bat_pwiv,
			     stwuct sk_buff *skb,
			     unsigned wong deway,
			     boow own_packet);
void batadv_send_bcast_packet(stwuct batadv_pwiv *bat_pwiv,
			      stwuct sk_buff *skb,
			      unsigned wong deway,
			      boow own_packet);
void
batadv_puwge_outstanding_packets(stwuct batadv_pwiv *bat_pwiv,
				 const stwuct batadv_hawd_iface *hawd_iface);
boow batadv_send_skb_pwepawe_unicast_4addw(stwuct batadv_pwiv *bat_pwiv,
					   stwuct sk_buff *skb,
					   stwuct batadv_owig_node *owig_node,
					   int packet_subtype);
int batadv_send_skb_unicast(stwuct batadv_pwiv *bat_pwiv,
			    stwuct sk_buff *skb, int packet_type,
			    int packet_subtype,
			    stwuct batadv_owig_node *owig_node,
			    unsigned showt vid);
int batadv_send_skb_via_tt_genewic(stwuct batadv_pwiv *bat_pwiv,
				   stwuct sk_buff *skb, int packet_type,
				   int packet_subtype, u8 *dst_hint,
				   unsigned showt vid);
int batadv_send_skb_via_gw(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			   unsigned showt vid);

/**
 * batadv_send_skb_via_tt() - send an skb via TT wookup
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the paywoad to send
 * @dst_hint: can be used to ovewwide the destination contained in the skb
 * @vid: the vid to be used to seawch the twanswation tabwe
 *
 * Wook up the wecipient node fow the destination addwess in the ethewnet
 * headew via the twanswation tabwe. Wwap the given skb into a batman-adv
 * unicast headew. Then send this fwame to the accowding destination node.
 *
 * Wetuwn: NET_XMIT_DWOP in case of ewwow ow NET_XMIT_SUCCESS othewwise.
 */
static inwine int batadv_send_skb_via_tt(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb, u8 *dst_hint,
					 unsigned showt vid)
{
	wetuwn batadv_send_skb_via_tt_genewic(bat_pwiv, skb, BATADV_UNICAST, 0,
					      dst_hint, vid);
}

/**
 * batadv_send_skb_via_tt_4addw() - send an skb via TT wookup
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the paywoad to send
 * @packet_subtype: the unicast 4addw packet subtype to use
 * @dst_hint: can be used to ovewwide the destination contained in the skb
 * @vid: the vid to be used to seawch the twanswation tabwe
 *
 * Wook up the wecipient node fow the destination addwess in the ethewnet
 * headew via the twanswation tabwe. Wwap the given skb into a batman-adv
 * unicast-4addw headew. Then send this fwame to the accowding destination
 * node.
 *
 * Wetuwn: NET_XMIT_DWOP in case of ewwow ow NET_XMIT_SUCCESS othewwise.
 */
static inwine int batadv_send_skb_via_tt_4addw(stwuct batadv_pwiv *bat_pwiv,
					       stwuct sk_buff *skb,
					       int packet_subtype,
					       u8 *dst_hint,
					       unsigned showt vid)
{
	wetuwn batadv_send_skb_via_tt_genewic(bat_pwiv, skb,
					      BATADV_UNICAST_4ADDW,
					      packet_subtype, dst_hint, vid);
}

#endif /* _NET_BATMAN_ADV_SEND_H_ */
