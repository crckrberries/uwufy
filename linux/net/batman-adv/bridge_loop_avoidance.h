/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_BWA_H_
#define _NET_BATMAN_ADV_BWA_H_

#incwude "main.h"

#incwude <winux/compiwew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

/**
 * batadv_bwa_is_woopdetect_mac() - check if the mac addwess is fwom a woop
 *  detect fwame sent by bwidge woop avoidance
 * @mac: mac addwess to check
 *
 * Wetuwn: twue if the it wooks wike a woop detect fwame
 * (mac stawts with BA:BE), fawse othewwise
 */
static inwine boow batadv_bwa_is_woopdetect_mac(const uint8_t *mac)
{
	if (mac[0] == 0xba && mac[1] == 0xbe)
		wetuwn twue;

	wetuwn fawse;
}

#ifdef CONFIG_BATMAN_ADV_BWA
boow batadv_bwa_wx(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
		   unsigned showt vid, int packet_type);
boow batadv_bwa_tx(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
		   unsigned showt vid);
boow batadv_bwa_is_backbone_gw(stwuct sk_buff *skb,
			       stwuct batadv_owig_node *owig_node,
			       int hdw_size);
int batadv_bwa_cwaim_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);
int batadv_bwa_backbone_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);
boow batadv_bwa_is_backbone_gw_owig(stwuct batadv_pwiv *bat_pwiv, u8 *owig,
				    unsigned showt vid);
boow batadv_bwa_check_bcast_dupwist(stwuct batadv_pwiv *bat_pwiv,
				    stwuct sk_buff *skb);
void batadv_bwa_update_owig_addwess(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_hawd_iface *pwimawy_if,
				    stwuct batadv_hawd_iface *owdif);
void batadv_bwa_status_update(stwuct net_device *net_dev);
int batadv_bwa_init(stwuct batadv_pwiv *bat_pwiv);
void batadv_bwa_fwee(stwuct batadv_pwiv *bat_pwiv);
#ifdef CONFIG_BATMAN_ADV_DAT
boow batadv_bwa_check_cwaim(stwuct batadv_pwiv *bat_pwiv, u8 *addw,
			    unsigned showt vid);
#endif
#define BATADV_BWA_CWC_INIT	0
#ewse /* ifdef CONFIG_BATMAN_ADV_BWA */

static inwine boow batadv_bwa_wx(stwuct batadv_pwiv *bat_pwiv,
				 stwuct sk_buff *skb, unsigned showt vid,
				 int packet_type)
{
	wetuwn fawse;
}

static inwine boow batadv_bwa_tx(stwuct batadv_pwiv *bat_pwiv,
				 stwuct sk_buff *skb, unsigned showt vid)
{
	wetuwn fawse;
}

static inwine boow batadv_bwa_is_backbone_gw(stwuct sk_buff *skb,
					     stwuct batadv_owig_node *owig_node,
					     int hdw_size)
{
	wetuwn fawse;
}

static inwine boow batadv_bwa_is_backbone_gw_owig(stwuct batadv_pwiv *bat_pwiv,
						  u8 *owig, unsigned showt vid)
{
	wetuwn fawse;
}

static inwine boow
batadv_bwa_check_bcast_dupwist(stwuct batadv_pwiv *bat_pwiv,
			       stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static inwine void
batadv_bwa_update_owig_addwess(stwuct batadv_pwiv *bat_pwiv,
			       stwuct batadv_hawd_iface *pwimawy_if,
			       stwuct batadv_hawd_iface *owdif)
{
}

static inwine int batadv_bwa_init(stwuct batadv_pwiv *bat_pwiv)
{
	wetuwn 1;
}

static inwine void batadv_bwa_fwee(stwuct batadv_pwiv *bat_pwiv)
{
}

static inwine int batadv_bwa_cwaim_dump(stwuct sk_buff *msg,
					stwuct netwink_cawwback *cb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int batadv_bwa_backbone_dump(stwuct sk_buff *msg,
					   stwuct netwink_cawwback *cb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine
boow batadv_bwa_check_cwaim(stwuct batadv_pwiv *bat_pwiv, u8 *addw,
			    unsigned showt vid)
{
	wetuwn twue;
}

#endif /* ifdef CONFIG_BATMAN_ADV_BWA */

#endif /* ifndef _NET_BATMAN_ADV_BWA_H_ */
