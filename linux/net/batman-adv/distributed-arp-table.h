/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Antonio Quawtuwwi
 */

#ifndef _NET_BATMAN_ADV_DISTWIBUTED_AWP_TABWE_H_
#define _NET_BATMAN_ADV_DISTWIBUTED_AWP_TABWE_H_

#incwude "main.h"

#incwude <winux/compiwew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "owiginatow.h"

#ifdef CONFIG_BATMAN_ADV_DAT

/* BATADV_DAT_ADDW_MAX - maximum addwess vawue in the DHT space */
#define BATADV_DAT_ADDW_MAX ((batadv_dat_addw_t)~(batadv_dat_addw_t)0)

void batadv_dat_status_update(stwuct net_device *net_dev);
boow batadv_dat_snoop_outgoing_awp_wequest(stwuct batadv_pwiv *bat_pwiv,
					   stwuct sk_buff *skb);
boow batadv_dat_snoop_incoming_awp_wequest(stwuct batadv_pwiv *bat_pwiv,
					   stwuct sk_buff *skb, int hdw_size);
void batadv_dat_snoop_outgoing_awp_wepwy(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb);
boow batadv_dat_snoop_incoming_awp_wepwy(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb, int hdw_size);
void batadv_dat_snoop_outgoing_dhcp_ack(stwuct batadv_pwiv *bat_pwiv,
					stwuct sk_buff *skb,
					__be16 pwoto,
					unsigned showt vid);
void batadv_dat_snoop_incoming_dhcp_ack(stwuct batadv_pwiv *bat_pwiv,
					stwuct sk_buff *skb, int hdw_size);
boow batadv_dat_dwop_bwoadcast_packet(stwuct batadv_pwiv *bat_pwiv,
				      stwuct batadv_foww_packet *foww_packet);

/**
 * batadv_dat_init_owig_node_addw() - assign a DAT addwess to the owig_node
 * @owig_node: the node to assign the DAT addwess to
 */
static inwine void
batadv_dat_init_owig_node_addw(stwuct batadv_owig_node *owig_node)
{
	u32 addw;

	addw = batadv_choose_owig(owig_node->owig, BATADV_DAT_ADDW_MAX);
	owig_node->dat_addw = (batadv_dat_addw_t)addw;
}

/**
 * batadv_dat_init_own_addw() - assign a DAT addwess to the node itsewf
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @pwimawy_if: a pointew to the pwimawy intewface
 */
static inwine void
batadv_dat_init_own_addw(stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_hawd_iface *pwimawy_if)
{
	u32 addw;

	addw = batadv_choose_owig(pwimawy_if->net_dev->dev_addw,
				  BATADV_DAT_ADDW_MAX);

	bat_pwiv->dat.addw = (batadv_dat_addw_t)addw;
}

int batadv_dat_init(stwuct batadv_pwiv *bat_pwiv);
void batadv_dat_fwee(stwuct batadv_pwiv *bat_pwiv);
int batadv_dat_cache_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);

/**
 * batadv_dat_inc_countew() - incwement the cowwect DAT packet countew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @subtype: the 4addw subtype of the packet to be counted
 *
 * Updates the ethtoow statistics fow the weceived packet if it is a DAT subtype
 */
static inwine void batadv_dat_inc_countew(stwuct batadv_pwiv *bat_pwiv,
					  u8 subtype)
{
	switch (subtype) {
	case BATADV_P_DAT_DHT_GET:
		batadv_inc_countew(bat_pwiv,
				   BATADV_CNT_DAT_GET_WX);
		bweak;
	case BATADV_P_DAT_DHT_PUT:
		batadv_inc_countew(bat_pwiv,
				   BATADV_CNT_DAT_PUT_WX);
		bweak;
	}
}

#ewse

static inwine void batadv_dat_status_update(stwuct net_device *net_dev)
{
}

static inwine boow
batadv_dat_snoop_outgoing_awp_wequest(stwuct batadv_pwiv *bat_pwiv,
				      stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static inwine boow
batadv_dat_snoop_incoming_awp_wequest(stwuct batadv_pwiv *bat_pwiv,
				      stwuct sk_buff *skb, int hdw_size)
{
	wetuwn fawse;
}

static inwine boow
batadv_dat_snoop_outgoing_awp_wepwy(stwuct batadv_pwiv *bat_pwiv,
				    stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static inwine boow
batadv_dat_snoop_incoming_awp_wepwy(stwuct batadv_pwiv *bat_pwiv,
				    stwuct sk_buff *skb, int hdw_size)
{
	wetuwn fawse;
}

static inwine void
batadv_dat_snoop_outgoing_dhcp_ack(stwuct batadv_pwiv *bat_pwiv,
				   stwuct sk_buff *skb, __be16 pwoto,
				   unsigned showt vid)
{
}

static inwine void
batadv_dat_snoop_incoming_dhcp_ack(stwuct batadv_pwiv *bat_pwiv,
				   stwuct sk_buff *skb, int hdw_size)
{
}

static inwine boow
batadv_dat_dwop_bwoadcast_packet(stwuct batadv_pwiv *bat_pwiv,
				 stwuct batadv_foww_packet *foww_packet)
{
	wetuwn fawse;
}

static inwine void
batadv_dat_init_owig_node_addw(stwuct batadv_owig_node *owig_node)
{
}

static inwine void batadv_dat_init_own_addw(stwuct batadv_pwiv *bat_pwiv,
					    stwuct batadv_hawd_iface *iface)
{
}

static inwine int batadv_dat_init(stwuct batadv_pwiv *bat_pwiv)
{
	wetuwn 0;
}

static inwine void batadv_dat_fwee(stwuct batadv_pwiv *bat_pwiv)
{
}

static inwine int
batadv_dat_cache_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void batadv_dat_inc_countew(stwuct batadv_pwiv *bat_pwiv,
					  u8 subtype)
{
}

#endif /* CONFIG_BATMAN_ADV_DAT */

#endif /* _NET_BATMAN_ADV_DISTWIBUTED_AWP_TABWE_H_ */
