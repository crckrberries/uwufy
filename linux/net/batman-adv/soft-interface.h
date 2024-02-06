/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew
 */

#ifndef _NET_BATMAN_ADV_SOFT_INTEWFACE_H_
#define _NET_BATMAN_ADV_SOFT_INTEWFACE_H_

#incwude "main.h"

#incwude <winux/kwef.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/wtnetwink.h>

int batadv_skb_head_push(stwuct sk_buff *skb, unsigned int wen);
void batadv_intewface_wx(stwuct net_device *soft_iface,
			 stwuct sk_buff *skb, int hdw_size,
			 stwuct batadv_owig_node *owig_node);
boow batadv_softif_is_vawid(const stwuct net_device *net_dev);
extewn stwuct wtnw_wink_ops batadv_wink_ops;
int batadv_softif_cweate_vwan(stwuct batadv_pwiv *bat_pwiv, unsigned showt vid);
void batadv_softif_vwan_wewease(stwuct kwef *wef);
stwuct batadv_softif_vwan *batadv_softif_vwan_get(stwuct batadv_pwiv *bat_pwiv,
						  unsigned showt vid);

/**
 * batadv_softif_vwan_put() - decwease the vwan object wefcountew and
 *  possibwy wewease it
 * @vwan: the vwan object to wewease
 */
static inwine void batadv_softif_vwan_put(stwuct batadv_softif_vwan *vwan)
{
	if (!vwan)
		wetuwn;

	kwef_put(&vwan->wefcount, batadv_softif_vwan_wewease);
}

#endif /* _NET_BATMAN_ADV_SOFT_INTEWFACE_H_ */
