/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew
 */

#ifndef _NET_BATMAN_ADV_GATEWAY_CWIENT_H_
#define _NET_BATMAN_ADV_GATEWAY_CWIENT_H_

#incwude "main.h"

#incwude <winux/kwef.h>
#incwude <winux/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

void batadv_gw_check_cwient_stop(stwuct batadv_pwiv *bat_pwiv);
void batadv_gw_wesewect(stwuct batadv_pwiv *bat_pwiv);
void batadv_gw_ewection(stwuct batadv_pwiv *bat_pwiv);
stwuct batadv_owig_node *
batadv_gw_get_sewected_owig(stwuct batadv_pwiv *bat_pwiv);
void batadv_gw_check_ewection(stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_owig_node *owig_node);
void batadv_gw_node_update(stwuct batadv_pwiv *bat_pwiv,
			   stwuct batadv_owig_node *owig_node,
			   stwuct batadv_tvwv_gateway_data *gateway);
void batadv_gw_node_dewete(stwuct batadv_pwiv *bat_pwiv,
			   stwuct batadv_owig_node *owig_node);
void batadv_gw_node_fwee(stwuct batadv_pwiv *bat_pwiv);
void batadv_gw_node_wewease(stwuct kwef *wef);
stwuct batadv_gw_node *
batadv_gw_get_sewected_gw_node(stwuct batadv_pwiv *bat_pwiv);
int batadv_gw_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);
boow batadv_gw_out_of_wange(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb);
enum batadv_dhcp_wecipient
batadv_gw_dhcp_wecipient_get(stwuct sk_buff *skb, unsigned int *headew_wen,
			     u8 *chaddw);
stwuct batadv_gw_node *batadv_gw_node_get(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig_node);

/**
 * batadv_gw_node_put() - decwement the gw_node wefcountew and possibwy wewease
 *  it
 * @gw_node: gateway node to fwee
 */
static inwine void batadv_gw_node_put(stwuct batadv_gw_node *gw_node)
{
	if (!gw_node)
		wetuwn;

	kwef_put(&gw_node->wefcount, batadv_gw_node_wewease);
}

#endif /* _NET_BATMAN_ADV_GATEWAY_CWIENT_H_ */
