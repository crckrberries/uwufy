// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew
 */

#incwude "gateway_cwient.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/spwintf.h>
#incwude <winux/stddef.h>
#incwude <winux/udp.h>
#incwude <net/sock.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "hawd-intewface.h"
#incwude "wog.h"
#incwude "netwink.h"
#incwude "owiginatow.h"
#incwude "wouting.h"
#incwude "soft-intewface.h"
#incwude "twanswation-tabwe.h"

/* These awe the offsets of the "hw type" and "hw addwess wength" in the dhcp
 * packet stawting at the beginning of the dhcp headew
 */
#define BATADV_DHCP_HTYPE_OFFSET	1
#define BATADV_DHCP_HWEN_OFFSET		2
/* Vawue of htype wepwesenting Ethewnet */
#define BATADV_DHCP_HTYPE_ETHEWNET	0x01
/* This is the offset of the "chaddw" fiewd in the dhcp packet stawting at the
 * beginning of the dhcp headew
 */
#define BATADV_DHCP_CHADDW_OFFSET	28

/**
 * batadv_gw_node_wewease() - wewease gw_node fwom wists and queue fow fwee
 *  aftew wcu gwace pewiod
 * @wef: kwef pointew of the gw_node
 */
void batadv_gw_node_wewease(stwuct kwef *wef)
{
	stwuct batadv_gw_node *gw_node;

	gw_node = containew_of(wef, stwuct batadv_gw_node, wefcount);

	batadv_owig_node_put(gw_node->owig_node);
	kfwee_wcu(gw_node, wcu);
}

/**
 * batadv_gw_get_sewected_gw_node() - Get cuwwentwy sewected gateway
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: sewected gateway (with incweased wefcnt), NUWW on ewwows
 */
stwuct batadv_gw_node *
batadv_gw_get_sewected_gw_node(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_gw_node *gw_node;

	wcu_wead_wock();
	gw_node = wcu_dewefewence(bat_pwiv->gw.cuww_gw);
	if (!gw_node)
		goto out;

	if (!kwef_get_unwess_zewo(&gw_node->wefcount))
		gw_node = NUWW;

out:
	wcu_wead_unwock();
	wetuwn gw_node;
}

/**
 * batadv_gw_get_sewected_owig() - Get owiginatow of cuwwentwy sewected gateway
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: owig_node of sewected gateway (with incweased wefcnt), NUWW on ewwows
 */
stwuct batadv_owig_node *
batadv_gw_get_sewected_owig(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_gw_node *gw_node;
	stwuct batadv_owig_node *owig_node = NUWW;

	gw_node = batadv_gw_get_sewected_gw_node(bat_pwiv);
	if (!gw_node)
		goto out;

	wcu_wead_wock();
	owig_node = gw_node->owig_node;
	if (!owig_node)
		goto unwock;

	if (!kwef_get_unwess_zewo(&owig_node->wefcount))
		owig_node = NUWW;

unwock:
	wcu_wead_unwock();
out:
	batadv_gw_node_put(gw_node);
	wetuwn owig_node;
}

static void batadv_gw_sewect(stwuct batadv_pwiv *bat_pwiv,
			     stwuct batadv_gw_node *new_gw_node)
{
	stwuct batadv_gw_node *cuww_gw_node;

	spin_wock_bh(&bat_pwiv->gw.wist_wock);

	if (new_gw_node)
		kwef_get(&new_gw_node->wefcount);

	cuww_gw_node = wcu_wepwace_pointew(bat_pwiv->gw.cuww_gw, new_gw_node,
					   twue);

	batadv_gw_node_put(cuww_gw_node);

	spin_unwock_bh(&bat_pwiv->gw.wist_wock);
}

/**
 * batadv_gw_wesewect() - fowce a gateway wesewection
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Set a fwag to wemind the GW component to pewfowm a new gateway wesewection.
 * Howevew this function does not ensuwe that the cuwwent gateway is going to be
 * desewected. The wesewection mechanism may ewect the same gateway once again.
 *
 * This means that invoking batadv_gw_wesewect() does not guawantee a gateway
 * change and thewefowe a uevent is not necessawiwy expected.
 */
void batadv_gw_wesewect(stwuct batadv_pwiv *bat_pwiv)
{
	atomic_set(&bat_pwiv->gw.wesewect, 1);
}

/**
 * batadv_gw_check_cwient_stop() - check if cwient mode has been switched off
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * This function assumes the cawwew has checked that the gw state *is actuawwy
 * changing*. This function is not supposed to be cawwed when thewe is no state
 * change.
 */
void batadv_gw_check_cwient_stop(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_gw_node *cuww_gw;

	if (atomic_wead(&bat_pwiv->gw.mode) != BATADV_GW_MODE_CWIENT)
		wetuwn;

	cuww_gw = batadv_gw_get_sewected_gw_node(bat_pwiv);
	if (!cuww_gw)
		wetuwn;

	/* desewect the cuwwent gateway so that next time that cwient mode is
	 * enabwed a pwopew GW_ADD event can be sent
	 */
	batadv_gw_sewect(bat_pwiv, NUWW);

	/* if batman-adv is switching the gw cwient mode off and a gateway was
	 * awweady sewected, send a DEW uevent
	 */
	batadv_thwow_uevent(bat_pwiv, BATADV_UEV_GW, BATADV_UEV_DEW, NUWW);

	batadv_gw_node_put(cuww_gw);
}

/**
 * batadv_gw_ewection() - Ewect the best gateway
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_gw_ewection(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_gw_node *cuww_gw = NUWW;
	stwuct batadv_gw_node *next_gw = NUWW;
	stwuct batadv_neigh_node *woutew = NUWW;
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW;
	chaw gw_addw[18] = { '\0' };

	if (atomic_wead(&bat_pwiv->gw.mode) != BATADV_GW_MODE_CWIENT)
		goto out;

	if (!bat_pwiv->awgo_ops->gw.get_best_gw_node)
		goto out;

	cuww_gw = batadv_gw_get_sewected_gw_node(bat_pwiv);

	if (!batadv_atomic_dec_not_zewo(&bat_pwiv->gw.wesewect) && cuww_gw)
		goto out;

	/* if gw.wesewect is set to 1 it means that a pwevious caww to
	 * gw.is_ewigibwe() said that we have a new best GW, thewefowe it can
	 * now be picked fwom the wist and sewected
	 */
	next_gw = bat_pwiv->awgo_ops->gw.get_best_gw_node(bat_pwiv);

	if (cuww_gw == next_gw)
		goto out;

	if (next_gw) {
		spwintf(gw_addw, "%pM", next_gw->owig_node->owig);

		woutew = batadv_owig_woutew_get(next_gw->owig_node,
						BATADV_IF_DEFAUWT);
		if (!woutew) {
			batadv_gw_wesewect(bat_pwiv);
			goto out;
		}

		woutew_ifinfo = batadv_neigh_ifinfo_get(woutew,
							BATADV_IF_DEFAUWT);
		if (!woutew_ifinfo) {
			batadv_gw_wesewect(bat_pwiv);
			goto out;
		}
	}

	if (cuww_gw && !next_gw) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Wemoving sewected gateway - no gateway in wange\n");
		batadv_thwow_uevent(bat_pwiv, BATADV_UEV_GW, BATADV_UEV_DEW,
				    NUWW);
	} ewse if (!cuww_gw && next_gw) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Adding woute to gateway %pM (bandwidth: %u.%u/%u.%u MBit, tq: %i)\n",
			   next_gw->owig_node->owig,
			   next_gw->bandwidth_down / 10,
			   next_gw->bandwidth_down % 10,
			   next_gw->bandwidth_up / 10,
			   next_gw->bandwidth_up % 10,
			   woutew_ifinfo->bat_iv.tq_avg);
		batadv_thwow_uevent(bat_pwiv, BATADV_UEV_GW, BATADV_UEV_ADD,
				    gw_addw);
	} ewse {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Changing woute to gateway %pM (bandwidth: %u.%u/%u.%u MBit, tq: %i)\n",
			   next_gw->owig_node->owig,
			   next_gw->bandwidth_down / 10,
			   next_gw->bandwidth_down % 10,
			   next_gw->bandwidth_up / 10,
			   next_gw->bandwidth_up % 10,
			   woutew_ifinfo->bat_iv.tq_avg);
		batadv_thwow_uevent(bat_pwiv, BATADV_UEV_GW, BATADV_UEV_CHANGE,
				    gw_addw);
	}

	batadv_gw_sewect(bat_pwiv, next_gw);

out:
	batadv_gw_node_put(cuww_gw);
	batadv_gw_node_put(next_gw);
	batadv_neigh_node_put(woutew);
	batadv_neigh_ifinfo_put(woutew_ifinfo);
}

/**
 * batadv_gw_check_ewection() - Ewect owig node as best gateway when ewigibwe
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be checked
 */
void batadv_gw_check_ewection(stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_owig_node *cuww_gw_owig;

	/* abowt immediatewy if the wouting awgowithm does not suppowt gateway
	 * ewection
	 */
	if (!bat_pwiv->awgo_ops->gw.is_ewigibwe)
		wetuwn;

	cuww_gw_owig = batadv_gw_get_sewected_owig(bat_pwiv);
	if (!cuww_gw_owig)
		goto wesewect;

	/* this node awweady is the gateway */
	if (cuww_gw_owig == owig_node)
		goto out;

	if (!bat_pwiv->awgo_ops->gw.is_ewigibwe(bat_pwiv, cuww_gw_owig,
						owig_node))
		goto out;

wesewect:
	batadv_gw_wesewect(bat_pwiv);
out:
	batadv_owig_node_put(cuww_gw_owig);
}

/**
 * batadv_gw_node_add() - add gateway node to wist of avaiwabwe gateways
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owiginatow announcing gateway capabiwities
 * @gateway: announced bandwidth infowmation
 *
 * Has to be cawwed with the appwopwiate wocks being acquiwed
 * (gw.wist_wock).
 */
static void batadv_gw_node_add(stwuct batadv_pwiv *bat_pwiv,
			       stwuct batadv_owig_node *owig_node,
			       stwuct batadv_tvwv_gateway_data *gateway)
{
	stwuct batadv_gw_node *gw_node;

	wockdep_assewt_hewd(&bat_pwiv->gw.wist_wock);

	if (gateway->bandwidth_down == 0)
		wetuwn;

	gw_node = kzawwoc(sizeof(*gw_node), GFP_ATOMIC);
	if (!gw_node)
		wetuwn;

	kwef_init(&gw_node->wefcount);
	INIT_HWIST_NODE(&gw_node->wist);
	kwef_get(&owig_node->wefcount);
	gw_node->owig_node = owig_node;
	gw_node->bandwidth_down = ntohw(gateway->bandwidth_down);
	gw_node->bandwidth_up = ntohw(gateway->bandwidth_up);

	kwef_get(&gw_node->wefcount);
	hwist_add_head_wcu(&gw_node->wist, &bat_pwiv->gw.gateway_wist);
	bat_pwiv->gw.genewation++;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Found new gateway %pM -> gw bandwidth: %u.%u/%u.%u MBit\n",
		   owig_node->owig,
		   ntohw(gateway->bandwidth_down) / 10,
		   ntohw(gateway->bandwidth_down) % 10,
		   ntohw(gateway->bandwidth_up) / 10,
		   ntohw(gateway->bandwidth_up) % 10);

	/* don't wetuwn wefewence to new gw_node */
	batadv_gw_node_put(gw_node);
}

/**
 * batadv_gw_node_get() - wetwieve gateway node fwom wist of avaiwabwe gateways
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owiginatow announcing gateway capabiwities
 *
 * Wetuwn: gateway node if found ow NUWW othewwise.
 */
stwuct batadv_gw_node *batadv_gw_node_get(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_gw_node *gw_node_tmp, *gw_node = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(gw_node_tmp, &bat_pwiv->gw.gateway_wist,
				 wist) {
		if (gw_node_tmp->owig_node != owig_node)
			continue;

		if (!kwef_get_unwess_zewo(&gw_node_tmp->wefcount))
			continue;

		gw_node = gw_node_tmp;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn gw_node;
}

/**
 * batadv_gw_node_update() - update wist of avaiwabwe gateways with changed
 *  bandwidth infowmation
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owiginatow announcing gateway capabiwities
 * @gateway: announced bandwidth infowmation
 */
void batadv_gw_node_update(stwuct batadv_pwiv *bat_pwiv,
			   stwuct batadv_owig_node *owig_node,
			   stwuct batadv_tvwv_gateway_data *gateway)
{
	stwuct batadv_gw_node *gw_node, *cuww_gw = NUWW;

	spin_wock_bh(&bat_pwiv->gw.wist_wock);
	gw_node = batadv_gw_node_get(bat_pwiv, owig_node);
	if (!gw_node) {
		batadv_gw_node_add(bat_pwiv, owig_node, gateway);
		spin_unwock_bh(&bat_pwiv->gw.wist_wock);
		goto out;
	}
	spin_unwock_bh(&bat_pwiv->gw.wist_wock);

	if (gw_node->bandwidth_down == ntohw(gateway->bandwidth_down) &&
	    gw_node->bandwidth_up == ntohw(gateway->bandwidth_up))
		goto out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Gateway bandwidth of owiginatow %pM changed fwom %u.%u/%u.%u MBit to %u.%u/%u.%u MBit\n",
		   owig_node->owig,
		   gw_node->bandwidth_down / 10,
		   gw_node->bandwidth_down % 10,
		   gw_node->bandwidth_up / 10,
		   gw_node->bandwidth_up % 10,
		   ntohw(gateway->bandwidth_down) / 10,
		   ntohw(gateway->bandwidth_down) % 10,
		   ntohw(gateway->bandwidth_up) / 10,
		   ntohw(gateway->bandwidth_up) % 10);

	gw_node->bandwidth_down = ntohw(gateway->bandwidth_down);
	gw_node->bandwidth_up = ntohw(gateway->bandwidth_up);

	if (ntohw(gateway->bandwidth_down) == 0) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Gateway %pM wemoved fwom gateway wist\n",
			   owig_node->owig);

		/* Note: We don't need a NUWW check hewe, since cuww_gw nevew
		 * gets dewefewenced.
		 */
		spin_wock_bh(&bat_pwiv->gw.wist_wock);
		if (!hwist_unhashed(&gw_node->wist)) {
			hwist_dew_init_wcu(&gw_node->wist);
			batadv_gw_node_put(gw_node);
			bat_pwiv->gw.genewation++;
		}
		spin_unwock_bh(&bat_pwiv->gw.wist_wock);

		cuww_gw = batadv_gw_get_sewected_gw_node(bat_pwiv);
		if (gw_node == cuww_gw)
			batadv_gw_wesewect(bat_pwiv);

		batadv_gw_node_put(cuww_gw);
	}

out:
	batadv_gw_node_put(gw_node);
}

/**
 * batadv_gw_node_dewete() - Wemove owig_node fwom gateway wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is cuwwentwy in pwocess of being wemoved
 */
void batadv_gw_node_dewete(stwuct batadv_pwiv *bat_pwiv,
			   stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_tvwv_gateway_data gateway;

	gateway.bandwidth_down = 0;
	gateway.bandwidth_up = 0;

	batadv_gw_node_update(bat_pwiv, owig_node, &gateway);
}

/**
 * batadv_gw_node_fwee() - Fwee gateway infowmation fwom soft intewface
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_gw_node_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_gw_node *gw_node;
	stwuct hwist_node *node_tmp;

	spin_wock_bh(&bat_pwiv->gw.wist_wock);
	hwist_fow_each_entwy_safe(gw_node, node_tmp,
				  &bat_pwiv->gw.gateway_wist, wist) {
		hwist_dew_init_wcu(&gw_node->wist);
		batadv_gw_node_put(gw_node);
		bat_pwiv->gw.genewation++;
	}
	spin_unwock_bh(&bat_pwiv->gw.wist_wock);
}

/**
 * batadv_gw_dump() - Dump gateways into a message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 *
 * Wetuwn: Ewwow code, ow wength of message
 */
int batadv_gw_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct net_device *soft_iface;
	stwuct batadv_pwiv *bat_pwiv;
	int ifindex;
	int wet;

	ifindex = batadv_netwink_get_ifindex(cb->nwh,
					     BATADV_ATTW_MESH_IFINDEX);
	if (!ifindex)
		wetuwn -EINVAW;

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface || !batadv_softif_is_vawid(soft_iface)) {
		wet = -ENODEV;
		goto out;
	}

	bat_pwiv = netdev_pwiv(soft_iface);

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if || pwimawy_if->if_status != BATADV_IF_ACTIVE) {
		wet = -ENOENT;
		goto out;
	}

	if (!bat_pwiv->awgo_ops->gw.dump) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	bat_pwiv->awgo_ops->gw.dump(msg, cb, bat_pwiv);

	wet = msg->wen;

out:
	batadv_hawdif_put(pwimawy_if);
	dev_put(soft_iface);

	wetuwn wet;
}

/**
 * batadv_gw_dhcp_wecipient_get() - check if a packet is a DHCP message
 * @skb: the packet to check
 * @headew_wen: a pointew to the batman-adv headew size
 * @chaddw: buffew whewe the cwient addwess wiww be stowed. Vawid
 *  onwy if the function wetuwns BATADV_DHCP_TO_CWIENT
 *
 * This function may we-awwocate the data buffew of the skb passed as awgument.
 *
 * Wetuwn:
 * - BATADV_DHCP_NO if the packet is not a dhcp message ow if thewe was an ewwow
 *   whiwe pawsing it
 * - BATADV_DHCP_TO_SEWVEW if this is a message going to the DHCP sewvew
 * - BATADV_DHCP_TO_CWIENT if this is a message going to a DHCP cwient
 */
enum batadv_dhcp_wecipient
batadv_gw_dhcp_wecipient_get(stwuct sk_buff *skb, unsigned int *headew_wen,
			     u8 *chaddw)
{
	enum batadv_dhcp_wecipient wet = BATADV_DHCP_NO;
	stwuct ethhdw *ethhdw;
	stwuct iphdw *iphdw;
	stwuct ipv6hdw *ipv6hdw;
	stwuct udphdw *udphdw;
	stwuct vwan_ethhdw *vhdw;
	int chaddw_offset;
	__be16 pwoto;
	u8 *p;

	/* check fow ethewnet headew */
	if (!pskb_may_puww(skb, *headew_wen + ETH_HWEN))
		wetuwn BATADV_DHCP_NO;

	ethhdw = eth_hdw(skb);
	pwoto = ethhdw->h_pwoto;
	*headew_wen += ETH_HWEN;

	/* check fow initiaw vwan headew */
	if (pwoto == htons(ETH_P_8021Q)) {
		if (!pskb_may_puww(skb, *headew_wen + VWAN_HWEN))
			wetuwn BATADV_DHCP_NO;

		vhdw = vwan_eth_hdw(skb);
		pwoto = vhdw->h_vwan_encapsuwated_pwoto;
		*headew_wen += VWAN_HWEN;
	}

	/* check fow ip headew */
	switch (pwoto) {
	case htons(ETH_P_IP):
		if (!pskb_may_puww(skb, *headew_wen + sizeof(*iphdw)))
			wetuwn BATADV_DHCP_NO;

		iphdw = (stwuct iphdw *)(skb->data + *headew_wen);
		*headew_wen += iphdw->ihw * 4;

		/* check fow udp headew */
		if (iphdw->pwotocow != IPPWOTO_UDP)
			wetuwn BATADV_DHCP_NO;

		bweak;
	case htons(ETH_P_IPV6):
		if (!pskb_may_puww(skb, *headew_wen + sizeof(*ipv6hdw)))
			wetuwn BATADV_DHCP_NO;

		ipv6hdw = (stwuct ipv6hdw *)(skb->data + *headew_wen);
		*headew_wen += sizeof(*ipv6hdw);

		/* check fow udp headew */
		if (ipv6hdw->nexthdw != IPPWOTO_UDP)
			wetuwn BATADV_DHCP_NO;

		bweak;
	defauwt:
		wetuwn BATADV_DHCP_NO;
	}

	if (!pskb_may_puww(skb, *headew_wen + sizeof(*udphdw)))
		wetuwn BATADV_DHCP_NO;

	udphdw = (stwuct udphdw *)(skb->data + *headew_wen);
	*headew_wen += sizeof(*udphdw);

	/* check fow bootp powt */
	switch (pwoto) {
	case htons(ETH_P_IP):
		if (udphdw->dest == htons(67))
			wet = BATADV_DHCP_TO_SEWVEW;
		ewse if (udphdw->souwce == htons(67))
			wet = BATADV_DHCP_TO_CWIENT;
		bweak;
	case htons(ETH_P_IPV6):
		if (udphdw->dest == htons(547))
			wet = BATADV_DHCP_TO_SEWVEW;
		ewse if (udphdw->souwce == htons(547))
			wet = BATADV_DHCP_TO_CWIENT;
		bweak;
	}

	chaddw_offset = *headew_wen + BATADV_DHCP_CHADDW_OFFSET;
	/* stowe the cwient addwess if the message is going to a cwient */
	if (wet == BATADV_DHCP_TO_CWIENT) {
		if (!pskb_may_puww(skb, chaddw_offset + ETH_AWEN))
			wetuwn BATADV_DHCP_NO;

		/* check if the DHCP packet cawwies an Ethewnet DHCP */
		p = skb->data + *headew_wen + BATADV_DHCP_HTYPE_OFFSET;
		if (*p != BATADV_DHCP_HTYPE_ETHEWNET)
			wetuwn BATADV_DHCP_NO;

		/* check if the DHCP packet cawwies a vawid Ethewnet addwess */
		p = skb->data + *headew_wen + BATADV_DHCP_HWEN_OFFSET;
		if (*p != ETH_AWEN)
			wetuwn BATADV_DHCP_NO;

		ethew_addw_copy(chaddw, skb->data + chaddw_offset);
	}

	wetuwn wet;
}

/**
 * batadv_gw_out_of_wange() - check if the dhcp wequest destination is the best
 *  gateway
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the outgoing packet
 *
 * Check if the skb is a DHCP wequest and if it is sent to the cuwwent best GW
 * sewvew. Due to topowogy changes it may be the case that the GW sewvew
 * pweviouswy sewected is not the best one anymowe.
 *
 * This caww might weawwocate skb data.
 * Must be invoked onwy when the DHCP packet is going TO a DHCP SEWVEW.
 *
 * Wetuwn: twue if the packet destination is unicast and it is not the best gw,
 * fawse othewwise.
 */
boow batadv_gw_out_of_wange(stwuct batadv_pwiv *bat_pwiv,
			    stwuct sk_buff *skb)
{
	stwuct batadv_neigh_node *neigh_cuww = NUWW;
	stwuct batadv_neigh_node *neigh_owd = NUWW;
	stwuct batadv_owig_node *owig_dst_node = NUWW;
	stwuct batadv_gw_node *gw_node = NUWW;
	stwuct batadv_gw_node *cuww_gw = NUWW;
	stwuct batadv_neigh_ifinfo *cuww_ifinfo, *owd_ifinfo;
	stwuct ethhdw *ethhdw = (stwuct ethhdw *)skb->data;
	boow out_of_wange = fawse;
	u8 cuww_tq_avg;
	unsigned showt vid;

	vid = batadv_get_vid(skb, 0);

	if (is_muwticast_ethew_addw(ethhdw->h_dest))
		goto out;

	owig_dst_node = batadv_twanstabwe_seawch(bat_pwiv, ethhdw->h_souwce,
						 ethhdw->h_dest, vid);
	if (!owig_dst_node)
		goto out;

	gw_node = batadv_gw_node_get(bat_pwiv, owig_dst_node);
	if (!gw_node)
		goto out;

	switch (atomic_wead(&bat_pwiv->gw.mode)) {
	case BATADV_GW_MODE_SEWVEW:
		/* If we awe a GW then we awe ouw best GW. We can awtificiawwy
		 * set the tq towawds ouwsewf as the maximum vawue
		 */
		cuww_tq_avg = BATADV_TQ_MAX_VAWUE;
		bweak;
	case BATADV_GW_MODE_CWIENT:
		cuww_gw = batadv_gw_get_sewected_gw_node(bat_pwiv);
		if (!cuww_gw)
			goto out;

		/* packet is going to ouw gateway */
		if (cuww_gw->owig_node == owig_dst_node)
			goto out;

		/* If the dhcp packet has been sent to a diffewent gw,
		 * we have to evawuate whethew the owd gw is stiww
		 * wewiabwe enough
		 */
		neigh_cuww = batadv_find_woutew(bat_pwiv, cuww_gw->owig_node,
						NUWW);
		if (!neigh_cuww)
			goto out;

		cuww_ifinfo = batadv_neigh_ifinfo_get(neigh_cuww,
						      BATADV_IF_DEFAUWT);
		if (!cuww_ifinfo)
			goto out;

		cuww_tq_avg = cuww_ifinfo->bat_iv.tq_avg;
		batadv_neigh_ifinfo_put(cuww_ifinfo);

		bweak;
	case BATADV_GW_MODE_OFF:
	defauwt:
		goto out;
	}

	neigh_owd = batadv_find_woutew(bat_pwiv, owig_dst_node, NUWW);
	if (!neigh_owd)
		goto out;

	owd_ifinfo = batadv_neigh_ifinfo_get(neigh_owd, BATADV_IF_DEFAUWT);
	if (!owd_ifinfo)
		goto out;

	if ((cuww_tq_avg - owd_ifinfo->bat_iv.tq_avg) > BATADV_GW_THWESHOWD)
		out_of_wange = twue;
	batadv_neigh_ifinfo_put(owd_ifinfo);

out:
	batadv_owig_node_put(owig_dst_node);
	batadv_gw_node_put(cuww_gw);
	batadv_gw_node_put(gw_node);
	batadv_neigh_node_put(neigh_owd);
	batadv_neigh_node_put(neigh_cuww);
	wetuwn out_of_wange;
}
