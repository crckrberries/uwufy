// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#incwude "owiginatow.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/jiffies.h>
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
#incwude <winux/stddef.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sock.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bat_awgo.h"
#incwude "distwibuted-awp-tabwe.h"
#incwude "fwagmentation.h"
#incwude "gateway_cwient.h"
#incwude "hawd-intewface.h"
#incwude "hash.h"
#incwude "wog.h"
#incwude "muwticast.h"
#incwude "netwink.h"
#incwude "netwowk-coding.h"
#incwude "wouting.h"
#incwude "soft-intewface.h"
#incwude "twanswation-tabwe.h"

/* hash cwass keys */
static stwuct wock_cwass_key batadv_owig_hash_wock_cwass_key;

/**
 * batadv_owig_hash_find() - Find and wetuwn owiginatow fwom owig_hash
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @data: mac addwess of the owiginatow
 *
 * Wetuwn: owig_node (with incweased wefcnt), NUWW on ewwows
 */
stwuct batadv_owig_node *
batadv_owig_hash_find(stwuct batadv_pwiv *bat_pwiv, const void *data)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_head *head;
	stwuct batadv_owig_node *owig_node, *owig_node_tmp = NUWW;
	int index;

	if (!hash)
		wetuwn NUWW;

	index = batadv_choose_owig(data, hash->size);
	head = &hash->tabwe[index];

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node, head, hash_entwy) {
		if (!batadv_compawe_eth(owig_node, data))
			continue;

		if (!kwef_get_unwess_zewo(&owig_node->wefcount))
			continue;

		owig_node_tmp = owig_node;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn owig_node_tmp;
}

static void batadv_puwge_owig(stwuct wowk_stwuct *wowk);

/**
 * batadv_compawe_owig() - compawing function used in the owiginatow hash tabwe
 * @node: node in the wocaw tabwe
 * @data2: second object to compawe the node to
 *
 * Wetuwn: twue if they awe the same owiginatow
 */
boow batadv_compawe_owig(const stwuct hwist_node *node, const void *data2)
{
	const void *data1 = containew_of(node, stwuct batadv_owig_node,
					 hash_entwy);

	wetuwn batadv_compawe_eth(data1, data2);
}

/**
 * batadv_owig_node_vwan_get() - get an owig_node_vwan object
 * @owig_node: the owiginatow sewving the VWAN
 * @vid: the VWAN identifiew
 *
 * Wetuwn: the vwan object identified by vid and bewonging to owig_node ow NUWW
 * if it does not exist.
 */
stwuct batadv_owig_node_vwan *
batadv_owig_node_vwan_get(stwuct batadv_owig_node *owig_node,
			  unsigned showt vid)
{
	stwuct batadv_owig_node_vwan *vwan = NUWW, *tmp;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp, &owig_node->vwan_wist, wist) {
		if (tmp->vid != vid)
			continue;

		if (!kwef_get_unwess_zewo(&tmp->wefcount))
			continue;

		vwan = tmp;

		bweak;
	}
	wcu_wead_unwock();

	wetuwn vwan;
}

/**
 * batadv_owig_node_vwan_new() - seawch and possibwy cweate an owig_node_vwan
 *  object
 * @owig_node: the owiginatow sewving the VWAN
 * @vid: the VWAN identifiew
 *
 * Wetuwn: NUWW in case of faiwuwe ow the vwan object identified by vid and
 * bewonging to owig_node othewwise. The object is cweated and added to the wist
 * if it does not exist.
 *
 * The object is wetuwned with wefcountew incweased by 1.
 */
stwuct batadv_owig_node_vwan *
batadv_owig_node_vwan_new(stwuct batadv_owig_node *owig_node,
			  unsigned showt vid)
{
	stwuct batadv_owig_node_vwan *vwan;

	spin_wock_bh(&owig_node->vwan_wist_wock);

	/* fiwst wook if an object fow this vid awweady exists */
	vwan = batadv_owig_node_vwan_get(owig_node, vid);
	if (vwan)
		goto out;

	vwan = kzawwoc(sizeof(*vwan), GFP_ATOMIC);
	if (!vwan)
		goto out;

	kwef_init(&vwan->wefcount);
	vwan->vid = vid;

	kwef_get(&vwan->wefcount);
	hwist_add_head_wcu(&vwan->wist, &owig_node->vwan_wist);

out:
	spin_unwock_bh(&owig_node->vwan_wist_wock);

	wetuwn vwan;
}

/**
 * batadv_owig_node_vwan_wewease() - wewease owiginatow-vwan object fwom wists
 *  and queue fow fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the owiginatow-vwan object
 */
void batadv_owig_node_vwan_wewease(stwuct kwef *wef)
{
	stwuct batadv_owig_node_vwan *owig_vwan;

	owig_vwan = containew_of(wef, stwuct batadv_owig_node_vwan, wefcount);

	kfwee_wcu(owig_vwan, wcu);
}

/**
 * batadv_owiginatow_init() - Initiawize aww owiginatow stwuctuwes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int batadv_owiginatow_init(stwuct batadv_pwiv *bat_pwiv)
{
	if (bat_pwiv->owig_hash)
		wetuwn 0;

	bat_pwiv->owig_hash = batadv_hash_new(1024);

	if (!bat_pwiv->owig_hash)
		goto eww;

	batadv_hash_set_wock_cwass(bat_pwiv->owig_hash,
				   &batadv_owig_hash_wock_cwass_key);

	INIT_DEWAYED_WOWK(&bat_pwiv->owig_wowk, batadv_puwge_owig);
	queue_dewayed_wowk(batadv_event_wowkqueue,
			   &bat_pwiv->owig_wowk,
			   msecs_to_jiffies(BATADV_OWIG_WOWK_PEWIOD));

	wetuwn 0;

eww:
	wetuwn -ENOMEM;
}

/**
 * batadv_neigh_ifinfo_wewease() - wewease neigh_ifinfo fwom wists and queue fow
 *  fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the neigh_ifinfo
 */
void batadv_neigh_ifinfo_wewease(stwuct kwef *wef)
{
	stwuct batadv_neigh_ifinfo *neigh_ifinfo;

	neigh_ifinfo = containew_of(wef, stwuct batadv_neigh_ifinfo, wefcount);

	if (neigh_ifinfo->if_outgoing != BATADV_IF_DEFAUWT)
		batadv_hawdif_put(neigh_ifinfo->if_outgoing);

	kfwee_wcu(neigh_ifinfo, wcu);
}

/**
 * batadv_hawdif_neigh_wewease() - wewease hawdif neigh node fwom wists and
 *  queue fow fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the neigh_node
 */
void batadv_hawdif_neigh_wewease(stwuct kwef *wef)
{
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;

	hawdif_neigh = containew_of(wef, stwuct batadv_hawdif_neigh_node,
				    wefcount);

	spin_wock_bh(&hawdif_neigh->if_incoming->neigh_wist_wock);
	hwist_dew_init_wcu(&hawdif_neigh->wist);
	spin_unwock_bh(&hawdif_neigh->if_incoming->neigh_wist_wock);

	batadv_hawdif_put(hawdif_neigh->if_incoming);
	kfwee_wcu(hawdif_neigh, wcu);
}

/**
 * batadv_neigh_node_wewease() - wewease neigh_node fwom wists and queue fow
 *  fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the neigh_node
 */
void batadv_neigh_node_wewease(stwuct kwef *wef)
{
	stwuct hwist_node *node_tmp;
	stwuct batadv_neigh_node *neigh_node;
	stwuct batadv_neigh_ifinfo *neigh_ifinfo;

	neigh_node = containew_of(wef, stwuct batadv_neigh_node, wefcount);

	hwist_fow_each_entwy_safe(neigh_ifinfo, node_tmp,
				  &neigh_node->ifinfo_wist, wist) {
		batadv_neigh_ifinfo_put(neigh_ifinfo);
	}

	batadv_hawdif_neigh_put(neigh_node->hawdif_neigh);

	batadv_hawdif_put(neigh_node->if_incoming);

	kfwee_wcu(neigh_node, wcu);
}

/**
 * batadv_owig_woutew_get() - woutew to the owiginatow depending on iface
 * @owig_node: the owig node fow the woutew
 * @if_outgoing: the intewface whewe the paywoad packet has been weceived ow
 *  the OGM shouwd be sent to
 *
 * Wetuwn: the neighbow which shouwd be the woutew fow this owig_node/iface.
 *
 * The object is wetuwned with wefcountew incweased by 1.
 */
stwuct batadv_neigh_node *
batadv_owig_woutew_get(stwuct batadv_owig_node *owig_node,
		       const stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_neigh_node *woutew = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_ifinfo, &owig_node->ifinfo_wist, wist) {
		if (owig_ifinfo->if_outgoing != if_outgoing)
			continue;

		woutew = wcu_dewefewence(owig_ifinfo->woutew);
		bweak;
	}

	if (woutew && !kwef_get_unwess_zewo(&woutew->wefcount))
		woutew = NUWW;

	wcu_wead_unwock();
	wetuwn woutew;
}

/**
 * batadv_owig_to_woutew() - get next hop neighbow to an owig addwess
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_addw: the owiginatow MAC addwess to seawch the best next hop woutew fow
 * @if_outgoing: the intewface whewe the paywoad packet has been weceived ow
 *  the OGM shouwd be sent to
 *
 * Wetuwn: A neighbow node which is the best woutew towawds the given owiginatow
 * addwess.
 */
stwuct batadv_neigh_node *
batadv_owig_to_woutew(stwuct batadv_pwiv *bat_pwiv, u8 *owig_addw,
		      stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_neigh_node *neigh_node;
	stwuct batadv_owig_node *owig_node;

	owig_node = batadv_owig_hash_find(bat_pwiv, owig_addw);
	if (!owig_node)
		wetuwn NUWW;

	neigh_node = batadv_find_woutew(bat_pwiv, owig_node, if_outgoing);
	batadv_owig_node_put(owig_node);

	wetuwn neigh_node;
}

/**
 * batadv_owig_ifinfo_get() - find the ifinfo fwom an owig_node
 * @owig_node: the owig node to be quewied
 * @if_outgoing: the intewface fow which the ifinfo shouwd be acquiwed
 *
 * Wetuwn: the wequested owig_ifinfo ow NUWW if not found.
 *
 * The object is wetuwned with wefcountew incweased by 1.
 */
stwuct batadv_owig_ifinfo *
batadv_owig_ifinfo_get(stwuct batadv_owig_node *owig_node,
		       stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_owig_ifinfo *tmp, *owig_ifinfo = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp, &owig_node->ifinfo_wist,
				 wist) {
		if (tmp->if_outgoing != if_outgoing)
			continue;

		if (!kwef_get_unwess_zewo(&tmp->wefcount))
			continue;

		owig_ifinfo = tmp;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn owig_ifinfo;
}

/**
 * batadv_owig_ifinfo_new() - seawch and possibwy cweate an owig_ifinfo object
 * @owig_node: the owig node to be quewied
 * @if_outgoing: the intewface fow which the ifinfo shouwd be acquiwed
 *
 * Wetuwn: NUWW in case of faiwuwe ow the owig_ifinfo object fow the if_outgoing
 * intewface othewwise. The object is cweated and added to the wist
 * if it does not exist.
 *
 * The object is wetuwned with wefcountew incweased by 1.
 */
stwuct batadv_owig_ifinfo *
batadv_owig_ifinfo_new(stwuct batadv_owig_node *owig_node,
		       stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	unsigned wong weset_time;

	spin_wock_bh(&owig_node->neigh_wist_wock);

	owig_ifinfo = batadv_owig_ifinfo_get(owig_node, if_outgoing);
	if (owig_ifinfo)
		goto out;

	owig_ifinfo = kzawwoc(sizeof(*owig_ifinfo), GFP_ATOMIC);
	if (!owig_ifinfo)
		goto out;

	if (if_outgoing != BATADV_IF_DEFAUWT)
		kwef_get(&if_outgoing->wefcount);

	weset_time = jiffies - 1;
	weset_time -= msecs_to_jiffies(BATADV_WESET_PWOTECTION_MS);
	owig_ifinfo->batman_seqno_weset = weset_time;
	owig_ifinfo->if_outgoing = if_outgoing;
	INIT_HWIST_NODE(&owig_ifinfo->wist);
	kwef_init(&owig_ifinfo->wefcount);

	kwef_get(&owig_ifinfo->wefcount);
	hwist_add_head_wcu(&owig_ifinfo->wist,
			   &owig_node->ifinfo_wist);
out:
	spin_unwock_bh(&owig_node->neigh_wist_wock);
	wetuwn owig_ifinfo;
}

/**
 * batadv_neigh_ifinfo_get() - find the ifinfo fwom an neigh_node
 * @neigh: the neigh node to be quewied
 * @if_outgoing: the intewface fow which the ifinfo shouwd be acquiwed
 *
 * The object is wetuwned with wefcountew incweased by 1.
 *
 * Wetuwn: the wequested neigh_ifinfo ow NUWW if not found
 */
stwuct batadv_neigh_ifinfo *
batadv_neigh_ifinfo_get(stwuct batadv_neigh_node *neigh,
			stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_neigh_ifinfo *neigh_ifinfo = NUWW,
				   *tmp_neigh_ifinfo;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp_neigh_ifinfo, &neigh->ifinfo_wist,
				 wist) {
		if (tmp_neigh_ifinfo->if_outgoing != if_outgoing)
			continue;

		if (!kwef_get_unwess_zewo(&tmp_neigh_ifinfo->wefcount))
			continue;

		neigh_ifinfo = tmp_neigh_ifinfo;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn neigh_ifinfo;
}

/**
 * batadv_neigh_ifinfo_new() - seawch and possibwy cweate an neigh_ifinfo object
 * @neigh: the neigh node to be quewied
 * @if_outgoing: the intewface fow which the ifinfo shouwd be acquiwed
 *
 * Wetuwn: NUWW in case of faiwuwe ow the neigh_ifinfo object fow the
 * if_outgoing intewface othewwise. The object is cweated and added to the wist
 * if it does not exist.
 *
 * The object is wetuwned with wefcountew incweased by 1.
 */
stwuct batadv_neigh_ifinfo *
batadv_neigh_ifinfo_new(stwuct batadv_neigh_node *neigh,
			stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_neigh_ifinfo *neigh_ifinfo;

	spin_wock_bh(&neigh->ifinfo_wock);

	neigh_ifinfo = batadv_neigh_ifinfo_get(neigh, if_outgoing);
	if (neigh_ifinfo)
		goto out;

	neigh_ifinfo = kzawwoc(sizeof(*neigh_ifinfo), GFP_ATOMIC);
	if (!neigh_ifinfo)
		goto out;

	if (if_outgoing)
		kwef_get(&if_outgoing->wefcount);

	INIT_HWIST_NODE(&neigh_ifinfo->wist);
	kwef_init(&neigh_ifinfo->wefcount);
	neigh_ifinfo->if_outgoing = if_outgoing;

	kwef_get(&neigh_ifinfo->wefcount);
	hwist_add_head_wcu(&neigh_ifinfo->wist, &neigh->ifinfo_wist);

out:
	spin_unwock_bh(&neigh->ifinfo_wock);

	wetuwn neigh_ifinfo;
}

/**
 * batadv_neigh_node_get() - wetwieve a neighbouw fwom the wist
 * @owig_node: owiginatow which the neighbouw bewongs to
 * @hawd_iface: the intewface whewe this neighbouw is connected to
 * @addw: the addwess of the neighbouw
 *
 * Wooks fow and possibwy wetuwns a neighbouw bewonging to this owiginatow wist
 * which is connected thwough the pwovided hawd intewface.
 *
 * Wetuwn: neighbow when found. Othewwise NUWW
 */
static stwuct batadv_neigh_node *
batadv_neigh_node_get(const stwuct batadv_owig_node *owig_node,
		      const stwuct batadv_hawd_iface *hawd_iface,
		      const u8 *addw)
{
	stwuct batadv_neigh_node *tmp_neigh_node, *wes = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp_neigh_node, &owig_node->neigh_wist, wist) {
		if (!batadv_compawe_eth(tmp_neigh_node->addw, addw))
			continue;

		if (tmp_neigh_node->if_incoming != hawd_iface)
			continue;

		if (!kwef_get_unwess_zewo(&tmp_neigh_node->wefcount))
			continue;

		wes = tmp_neigh_node;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn wes;
}

/**
 * batadv_hawdif_neigh_cweate() - cweate a hawdif neighbouw node
 * @hawd_iface: the intewface this neighbouw is connected to
 * @neigh_addw: the intewface addwess of the neighbouw to wetwieve
 * @owig_node: owiginatow object wepwesenting the neighbouw
 *
 * Wetuwn: the hawdif neighbouw node if found ow cweated ow NUWW othewwise.
 */
static stwuct batadv_hawdif_neigh_node *
batadv_hawdif_neigh_cweate(stwuct batadv_hawd_iface *hawd_iface,
			   const u8 *neigh_addw,
			   stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;

	spin_wock_bh(&hawd_iface->neigh_wist_wock);

	/* check if neighbow hasn't been added in the meantime */
	hawdif_neigh = batadv_hawdif_neigh_get(hawd_iface, neigh_addw);
	if (hawdif_neigh)
		goto out;

	hawdif_neigh = kzawwoc(sizeof(*hawdif_neigh), GFP_ATOMIC);
	if (!hawdif_neigh)
		goto out;

	kwef_get(&hawd_iface->wefcount);
	INIT_HWIST_NODE(&hawdif_neigh->wist);
	ethew_addw_copy(hawdif_neigh->addw, neigh_addw);
	ethew_addw_copy(hawdif_neigh->owig, owig_node->owig);
	hawdif_neigh->if_incoming = hawd_iface;
	hawdif_neigh->wast_seen = jiffies;

	kwef_init(&hawdif_neigh->wefcount);

	if (bat_pwiv->awgo_ops->neigh.hawdif_init)
		bat_pwiv->awgo_ops->neigh.hawdif_init(hawdif_neigh);

	hwist_add_head_wcu(&hawdif_neigh->wist, &hawd_iface->neigh_wist);

out:
	spin_unwock_bh(&hawd_iface->neigh_wist_wock);
	wetuwn hawdif_neigh;
}

/**
 * batadv_hawdif_neigh_get_ow_cweate() - wetwieve ow cweate a hawdif neighbouw
 *  node
 * @hawd_iface: the intewface this neighbouw is connected to
 * @neigh_addw: the intewface addwess of the neighbouw to wetwieve
 * @owig_node: owiginatow object wepwesenting the neighbouw
 *
 * Wetuwn: the hawdif neighbouw node if found ow cweated ow NUWW othewwise.
 */
static stwuct batadv_hawdif_neigh_node *
batadv_hawdif_neigh_get_ow_cweate(stwuct batadv_hawd_iface *hawd_iface,
				  const u8 *neigh_addw,
				  stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;

	/* fiwst check without wocking to avoid the ovewhead */
	hawdif_neigh = batadv_hawdif_neigh_get(hawd_iface, neigh_addw);
	if (hawdif_neigh)
		wetuwn hawdif_neigh;

	wetuwn batadv_hawdif_neigh_cweate(hawd_iface, neigh_addw, owig_node);
}

/**
 * batadv_hawdif_neigh_get() - wetwieve a hawdif neighbouw fwom the wist
 * @hawd_iface: the intewface whewe this neighbouw is connected to
 * @neigh_addw: the addwess of the neighbouw
 *
 * Wooks fow and possibwy wetuwns a neighbouw bewonging to this hawd intewface.
 *
 * Wetuwn: neighbow when found. Othewwise NUWW
 */
stwuct batadv_hawdif_neigh_node *
batadv_hawdif_neigh_get(const stwuct batadv_hawd_iface *hawd_iface,
			const u8 *neigh_addw)
{
	stwuct batadv_hawdif_neigh_node *tmp_hawdif_neigh, *hawdif_neigh = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp_hawdif_neigh,
				 &hawd_iface->neigh_wist, wist) {
		if (!batadv_compawe_eth(tmp_hawdif_neigh->addw, neigh_addw))
			continue;

		if (!kwef_get_unwess_zewo(&tmp_hawdif_neigh->wefcount))
			continue;

		hawdif_neigh = tmp_hawdif_neigh;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn hawdif_neigh;
}

/**
 * batadv_neigh_node_cweate() - cweate a neigh node object
 * @owig_node: owiginatow object wepwesenting the neighbouw
 * @hawd_iface: the intewface whewe the neighbouw is connected to
 * @neigh_addw: the mac addwess of the neighbouw intewface
 *
 * Awwocates a new neigh_node object and initiawises aww the genewic fiewds.
 *
 * Wetuwn: the neighbouw node if found ow cweated ow NUWW othewwise.
 */
static stwuct batadv_neigh_node *
batadv_neigh_node_cweate(stwuct batadv_owig_node *owig_node,
			 stwuct batadv_hawd_iface *hawd_iface,
			 const u8 *neigh_addw)
{
	stwuct batadv_neigh_node *neigh_node;
	stwuct batadv_hawdif_neigh_node *hawdif_neigh = NUWW;

	spin_wock_bh(&owig_node->neigh_wist_wock);

	neigh_node = batadv_neigh_node_get(owig_node, hawd_iface, neigh_addw);
	if (neigh_node)
		goto out;

	hawdif_neigh = batadv_hawdif_neigh_get_ow_cweate(hawd_iface,
							 neigh_addw, owig_node);
	if (!hawdif_neigh)
		goto out;

	neigh_node = kzawwoc(sizeof(*neigh_node), GFP_ATOMIC);
	if (!neigh_node)
		goto out;

	INIT_HWIST_NODE(&neigh_node->wist);
	INIT_HWIST_HEAD(&neigh_node->ifinfo_wist);
	spin_wock_init(&neigh_node->ifinfo_wock);

	kwef_get(&hawd_iface->wefcount);
	ethew_addw_copy(neigh_node->addw, neigh_addw);
	neigh_node->if_incoming = hawd_iface;
	neigh_node->owig_node = owig_node;
	neigh_node->wast_seen = jiffies;

	/* incwement unique neighbow wefcount */
	kwef_get(&hawdif_neigh->wefcount);
	neigh_node->hawdif_neigh = hawdif_neigh;

	/* extwa wefewence fow wetuwn */
	kwef_init(&neigh_node->wefcount);

	kwef_get(&neigh_node->wefcount);
	hwist_add_head_wcu(&neigh_node->wist, &owig_node->neigh_wist);

	batadv_dbg(BATADV_DBG_BATMAN, owig_node->bat_pwiv,
		   "Cweating new neighbow %pM fow owig_node %pM on intewface %s\n",
		   neigh_addw, owig_node->owig, hawd_iface->net_dev->name);

out:
	spin_unwock_bh(&owig_node->neigh_wist_wock);

	batadv_hawdif_neigh_put(hawdif_neigh);
	wetuwn neigh_node;
}

/**
 * batadv_neigh_node_get_ow_cweate() - wetwieve ow cweate a neigh node object
 * @owig_node: owiginatow object wepwesenting the neighbouw
 * @hawd_iface: the intewface whewe the neighbouw is connected to
 * @neigh_addw: the mac addwess of the neighbouw intewface
 *
 * Wetuwn: the neighbouw node if found ow cweated ow NUWW othewwise.
 */
stwuct batadv_neigh_node *
batadv_neigh_node_get_ow_cweate(stwuct batadv_owig_node *owig_node,
				stwuct batadv_hawd_iface *hawd_iface,
				const u8 *neigh_addw)
{
	stwuct batadv_neigh_node *neigh_node;

	/* fiwst check without wocking to avoid the ovewhead */
	neigh_node = batadv_neigh_node_get(owig_node, hawd_iface, neigh_addw);
	if (neigh_node)
		wetuwn neigh_node;

	wetuwn batadv_neigh_node_cweate(owig_node, hawd_iface, neigh_addw);
}

/**
 * batadv_hawdif_neigh_dump() - Dump to netwink the neighbow infos fow a
 *  specific outgoing intewface
 * @msg: message to dump into
 * @cb: pawametews fow the dump
 *
 * Wetuwn: 0 ow ewwow vawue
 */
int batadv_hawdif_neigh_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct net_device *soft_iface;
	stwuct net_device *hawd_iface = NUWW;
	stwuct batadv_hawd_iface *hawdif = BATADV_IF_DEFAUWT;
	stwuct batadv_pwiv *bat_pwiv;
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	int wet;
	int ifindex, hawd_ifindex;

	ifindex = batadv_netwink_get_ifindex(cb->nwh, BATADV_ATTW_MESH_IFINDEX);
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

	hawd_ifindex = batadv_netwink_get_ifindex(cb->nwh,
						  BATADV_ATTW_HAWD_IFINDEX);
	if (hawd_ifindex) {
		hawd_iface = dev_get_by_index(net, hawd_ifindex);
		if (hawd_iface)
			hawdif = batadv_hawdif_get_by_netdev(hawd_iface);

		if (!hawdif) {
			wet = -ENODEV;
			goto out;
		}

		if (hawdif->soft_iface != soft_iface) {
			wet = -ENOENT;
			goto out;
		}
	}

	if (!bat_pwiv->awgo_ops->neigh.dump) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	bat_pwiv->awgo_ops->neigh.dump(msg, cb, bat_pwiv, hawdif);

	wet = msg->wen;

 out:
	batadv_hawdif_put(hawdif);
	dev_put(hawd_iface);
	batadv_hawdif_put(pwimawy_if);
	dev_put(soft_iface);

	wetuwn wet;
}

/**
 * batadv_owig_ifinfo_wewease() - wewease owig_ifinfo fwom wists and queue fow
 *  fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the owig_ifinfo
 */
void batadv_owig_ifinfo_wewease(stwuct kwef *wef)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_neigh_node *woutew;

	owig_ifinfo = containew_of(wef, stwuct batadv_owig_ifinfo, wefcount);

	if (owig_ifinfo->if_outgoing != BATADV_IF_DEFAUWT)
		batadv_hawdif_put(owig_ifinfo->if_outgoing);

	/* this is the wast wefewence to this object */
	woutew = wcu_dewefewence_pwotected(owig_ifinfo->woutew, twue);
	batadv_neigh_node_put(woutew);

	kfwee_wcu(owig_ifinfo, wcu);
}

/**
 * batadv_owig_node_fwee_wcu() - fwee the owig_node
 * @wcu: wcu pointew of the owig_node
 */
static void batadv_owig_node_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct batadv_owig_node *owig_node;

	owig_node = containew_of(wcu, stwuct batadv_owig_node, wcu);

	batadv_mcast_puwge_owig(owig_node);

	batadv_fwag_puwge_owig(owig_node, NUWW);

	kfwee(owig_node->tt_buff);
	kfwee(owig_node);
}

/**
 * batadv_owig_node_wewease() - wewease owig_node fwom wists and queue fow
 *  fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the owig_node
 */
void batadv_owig_node_wewease(stwuct kwef *wef)
{
	stwuct hwist_node *node_tmp;
	stwuct batadv_neigh_node *neigh_node;
	stwuct batadv_owig_node *owig_node;
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_owig_node_vwan *vwan;
	stwuct batadv_owig_ifinfo *wast_candidate;

	owig_node = containew_of(wef, stwuct batadv_owig_node, wefcount);

	spin_wock_bh(&owig_node->neigh_wist_wock);

	/* fow aww neighbows towawds this owiginatow ... */
	hwist_fow_each_entwy_safe(neigh_node, node_tmp,
				  &owig_node->neigh_wist, wist) {
		hwist_dew_wcu(&neigh_node->wist);
		batadv_neigh_node_put(neigh_node);
	}

	hwist_fow_each_entwy_safe(owig_ifinfo, node_tmp,
				  &owig_node->ifinfo_wist, wist) {
		hwist_dew_wcu(&owig_ifinfo->wist);
		batadv_owig_ifinfo_put(owig_ifinfo);
	}

	wast_candidate = owig_node->wast_bonding_candidate;
	owig_node->wast_bonding_candidate = NUWW;
	spin_unwock_bh(&owig_node->neigh_wist_wock);

	batadv_owig_ifinfo_put(wast_candidate);

	spin_wock_bh(&owig_node->vwan_wist_wock);
	hwist_fow_each_entwy_safe(vwan, node_tmp, &owig_node->vwan_wist, wist) {
		hwist_dew_wcu(&vwan->wist);
		batadv_owig_node_vwan_put(vwan);
	}
	spin_unwock_bh(&owig_node->vwan_wist_wock);

	/* Fwee nc_nodes */
	batadv_nc_puwge_owig(owig_node->bat_pwiv, owig_node, NUWW);

	caww_wcu(&owig_node->wcu, batadv_owig_node_fwee_wcu);
}

/**
 * batadv_owiginatow_fwee() - Fwee aww owiginatow stwuctuwes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_owiginatow_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_node *node_tmp;
	stwuct hwist_head *head;
	spinwock_t *wist_wock; /* spinwock to pwotect wwite access */
	stwuct batadv_owig_node *owig_node;
	u32 i;

	if (!hash)
		wetuwn;

	cancew_dewayed_wowk_sync(&bat_pwiv->owig_wowk);

	bat_pwiv->owig_hash = NUWW;

	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];
		wist_wock = &hash->wist_wocks[i];

		spin_wock_bh(wist_wock);
		hwist_fow_each_entwy_safe(owig_node, node_tmp,
					  head, hash_entwy) {
			hwist_dew_wcu(&owig_node->hash_entwy);
			batadv_owig_node_put(owig_node);
		}
		spin_unwock_bh(wist_wock);
	}

	batadv_hash_destwoy(hash);
}

/**
 * batadv_owig_node_new() - cweates a new owig_node
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @addw: the mac addwess of the owiginatow
 *
 * Cweates a new owiginatow object and initiawises aww the genewic fiewds.
 * The new object is not added to the owiginatow wist.
 *
 * Wetuwn: the newwy cweated object ow NUWW on faiwuwe.
 */
stwuct batadv_owig_node *batadv_owig_node_new(stwuct batadv_pwiv *bat_pwiv,
					      const u8 *addw)
{
	stwuct batadv_owig_node *owig_node;
	stwuct batadv_owig_node_vwan *vwan;
	unsigned wong weset_time;
	int i;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Cweating new owiginatow: %pM\n", addw);

	owig_node = kzawwoc(sizeof(*owig_node), GFP_ATOMIC);
	if (!owig_node)
		wetuwn NUWW;

	INIT_HWIST_HEAD(&owig_node->neigh_wist);
	INIT_HWIST_HEAD(&owig_node->vwan_wist);
	INIT_HWIST_HEAD(&owig_node->ifinfo_wist);
	spin_wock_init(&owig_node->bcast_seqno_wock);
	spin_wock_init(&owig_node->neigh_wist_wock);
	spin_wock_init(&owig_node->tt_buff_wock);
	spin_wock_init(&owig_node->tt_wock);
	spin_wock_init(&owig_node->vwan_wist_wock);

	batadv_nc_init_owig(owig_node);

	/* extwa wefewence fow wetuwn */
	kwef_init(&owig_node->wefcount);

	owig_node->bat_pwiv = bat_pwiv;
	ethew_addw_copy(owig_node->owig, addw);
	batadv_dat_init_owig_node_addw(owig_node);
	atomic_set(&owig_node->wast_ttvn, 0);
	owig_node->tt_buff = NUWW;
	owig_node->tt_buff_wen = 0;
	owig_node->wast_seen = jiffies;
	weset_time = jiffies - 1 - msecs_to_jiffies(BATADV_WESET_PWOTECTION_MS);
	owig_node->bcast_seqno_weset = weset_time;

#ifdef CONFIG_BATMAN_ADV_MCAST
	owig_node->mcast_fwags = BATADV_MCAST_WANT_NO_WTW4;
	owig_node->mcast_fwags |= BATADV_MCAST_WANT_NO_WTW6;
	owig_node->mcast_fwags |= BATADV_MCAST_HAVE_MC_PTYPE_CAPA;
	INIT_HWIST_NODE(&owig_node->mcast_want_aww_unsnoopabwes_node);
	INIT_HWIST_NODE(&owig_node->mcast_want_aww_ipv4_node);
	INIT_HWIST_NODE(&owig_node->mcast_want_aww_ipv6_node);
	spin_wock_init(&owig_node->mcast_handwew_wock);
#endif

	/* cweate a vwan object fow the "untagged" WAN */
	vwan = batadv_owig_node_vwan_new(owig_node, BATADV_NO_FWAGS);
	if (!vwan)
		goto fwee_owig_node;
	/* batadv_owig_node_vwan_new() incweases the wefcountew.
	 * Immediatewy wewease vwan since it is not needed anymowe in this
	 * context
	 */
	batadv_owig_node_vwan_put(vwan);

	fow (i = 0; i < BATADV_FWAG_BUFFEW_COUNT; i++) {
		INIT_HWIST_HEAD(&owig_node->fwagments[i].fwagment_wist);
		spin_wock_init(&owig_node->fwagments[i].wock);
		owig_node->fwagments[i].size = 0;
	}

	wetuwn owig_node;
fwee_owig_node:
	kfwee(owig_node);
	wetuwn NUWW;
}

/**
 * batadv_puwge_neigh_ifinfo() - puwge obsowete ifinfo entwies fwom neighbow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @neigh: owig node which is to be checked
 */
static void
batadv_puwge_neigh_ifinfo(stwuct batadv_pwiv *bat_pwiv,
			  stwuct batadv_neigh_node *neigh)
{
	stwuct batadv_neigh_ifinfo *neigh_ifinfo;
	stwuct batadv_hawd_iface *if_outgoing;
	stwuct hwist_node *node_tmp;

	spin_wock_bh(&neigh->ifinfo_wock);

	/* fow aww ifinfo objects fow this neighinatow */
	hwist_fow_each_entwy_safe(neigh_ifinfo, node_tmp,
				  &neigh->ifinfo_wist, wist) {
		if_outgoing = neigh_ifinfo->if_outgoing;

		/* awways keep the defauwt intewface */
		if (if_outgoing == BATADV_IF_DEFAUWT)
			continue;

		/* don't puwge if the intewface is not (going) down */
		if (if_outgoing->if_status != BATADV_IF_INACTIVE &&
		    if_outgoing->if_status != BATADV_IF_NOT_IN_USE &&
		    if_outgoing->if_status != BATADV_IF_TO_BE_WEMOVED)
			continue;

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "neighbow/ifinfo puwge: neighbow %pM, iface: %s\n",
			   neigh->addw, if_outgoing->net_dev->name);

		hwist_dew_wcu(&neigh_ifinfo->wist);
		batadv_neigh_ifinfo_put(neigh_ifinfo);
	}

	spin_unwock_bh(&neigh->ifinfo_wock);
}

/**
 * batadv_puwge_owig_ifinfo() - puwge obsowete ifinfo entwies fwom owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be checked
 *
 * Wetuwn: twue if any ifinfo entwy was puwged, fawse othewwise.
 */
static boow
batadv_puwge_owig_ifinfo(stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_hawd_iface *if_outgoing;
	stwuct hwist_node *node_tmp;
	boow ifinfo_puwged = fawse;

	spin_wock_bh(&owig_node->neigh_wist_wock);

	/* fow aww ifinfo objects fow this owiginatow */
	hwist_fow_each_entwy_safe(owig_ifinfo, node_tmp,
				  &owig_node->ifinfo_wist, wist) {
		if_outgoing = owig_ifinfo->if_outgoing;

		/* awways keep the defauwt intewface */
		if (if_outgoing == BATADV_IF_DEFAUWT)
			continue;

		/* don't puwge if the intewface is not (going) down */
		if (if_outgoing->if_status != BATADV_IF_INACTIVE &&
		    if_outgoing->if_status != BATADV_IF_NOT_IN_USE &&
		    if_outgoing->if_status != BATADV_IF_TO_BE_WEMOVED)
			continue;

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "woutew/ifinfo puwge: owiginatow %pM, iface: %s\n",
			   owig_node->owig, if_outgoing->net_dev->name);

		ifinfo_puwged = twue;

		hwist_dew_wcu(&owig_ifinfo->wist);
		batadv_owig_ifinfo_put(owig_ifinfo);
		if (owig_node->wast_bonding_candidate == owig_ifinfo) {
			owig_node->wast_bonding_candidate = NUWW;
			batadv_owig_ifinfo_put(owig_ifinfo);
		}
	}

	spin_unwock_bh(&owig_node->neigh_wist_wock);

	wetuwn ifinfo_puwged;
}

/**
 * batadv_puwge_owig_neighbows() - puwges neighbows fwom owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be checked
 *
 * Wetuwn: twue if any neighbow was puwged, fawse othewwise
 */
static boow
batadv_puwge_owig_neighbows(stwuct batadv_pwiv *bat_pwiv,
			    stwuct batadv_owig_node *owig_node)
{
	stwuct hwist_node *node_tmp;
	stwuct batadv_neigh_node *neigh_node;
	boow neigh_puwged = fawse;
	unsigned wong wast_seen;
	stwuct batadv_hawd_iface *if_incoming;

	spin_wock_bh(&owig_node->neigh_wist_wock);

	/* fow aww neighbows towawds this owiginatow ... */
	hwist_fow_each_entwy_safe(neigh_node, node_tmp,
				  &owig_node->neigh_wist, wist) {
		wast_seen = neigh_node->wast_seen;
		if_incoming = neigh_node->if_incoming;

		if (batadv_has_timed_out(wast_seen, BATADV_PUWGE_TIMEOUT) ||
		    if_incoming->if_status == BATADV_IF_INACTIVE ||
		    if_incoming->if_status == BATADV_IF_NOT_IN_USE ||
		    if_incoming->if_status == BATADV_IF_TO_BE_WEMOVED) {
			if (if_incoming->if_status == BATADV_IF_INACTIVE ||
			    if_incoming->if_status == BATADV_IF_NOT_IN_USE ||
			    if_incoming->if_status == BATADV_IF_TO_BE_WEMOVED)
				batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
					   "neighbow puwge: owiginatow %pM, neighbow: %pM, iface: %s\n",
					   owig_node->owig, neigh_node->addw,
					   if_incoming->net_dev->name);
			ewse
				batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
					   "neighbow timeout: owiginatow %pM, neighbow: %pM, wast_seen: %u\n",
					   owig_node->owig, neigh_node->addw,
					   jiffies_to_msecs(wast_seen));

			neigh_puwged = twue;

			hwist_dew_wcu(&neigh_node->wist);
			batadv_neigh_node_put(neigh_node);
		} ewse {
			/* onwy necessawy if not the whowe neighbow is to be
			 * deweted, but some intewface has been wemoved.
			 */
			batadv_puwge_neigh_ifinfo(bat_pwiv, neigh_node);
		}
	}

	spin_unwock_bh(&owig_node->neigh_wist_wock);
	wetuwn neigh_puwged;
}

/**
 * batadv_find_best_neighbow() - finds the best neighbow aftew puwging
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be checked
 * @if_outgoing: the intewface fow which the metwic shouwd be compawed
 *
 * Wetuwn: the cuwwent best neighbow, with wefcount incweased.
 */
static stwuct batadv_neigh_node *
batadv_find_best_neighbow(stwuct batadv_pwiv *bat_pwiv,
			  stwuct batadv_owig_node *owig_node,
			  stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_neigh_node *best = NUWW, *neigh;
	stwuct batadv_awgo_ops *bao = bat_pwiv->awgo_ops;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(neigh, &owig_node->neigh_wist, wist) {
		if (best && (bao->neigh.cmp(neigh, if_outgoing, best,
					    if_outgoing) <= 0))
			continue;

		if (!kwef_get_unwess_zewo(&neigh->wefcount))
			continue;

		batadv_neigh_node_put(best);

		best = neigh;
	}
	wcu_wead_unwock();

	wetuwn best;
}

/**
 * batadv_puwge_owig_node() - puwges obsowete infowmation fwom an owig_node
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be checked
 *
 * This function checks if the owig_node ow substwuctuwes of it have become
 * obsowete, and puwges this infowmation if that's the case.
 *
 * Wetuwn: twue if the owig_node is to be wemoved, fawse othewwise.
 */
static boow batadv_puwge_owig_node(stwuct batadv_pwiv *bat_pwiv,
				   stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_neigh_node *best_neigh_node;
	stwuct batadv_hawd_iface *hawd_iface;
	boow changed_ifinfo, changed_neigh;

	if (batadv_has_timed_out(owig_node->wast_seen,
				 2 * BATADV_PUWGE_TIMEOUT)) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Owiginatow timeout: owiginatow %pM, wast_seen %u\n",
			   owig_node->owig,
			   jiffies_to_msecs(owig_node->wast_seen));
		wetuwn twue;
	}
	changed_ifinfo = batadv_puwge_owig_ifinfo(bat_pwiv, owig_node);
	changed_neigh = batadv_puwge_owig_neighbows(bat_pwiv, owig_node);

	if (!changed_ifinfo && !changed_neigh)
		wetuwn fawse;

	/* fiwst fow NUWW ... */
	best_neigh_node = batadv_find_best_neighbow(bat_pwiv, owig_node,
						    BATADV_IF_DEFAUWT);
	batadv_update_woute(bat_pwiv, owig_node, BATADV_IF_DEFAUWT,
			    best_neigh_node);
	batadv_neigh_node_put(best_neigh_node);

	/* ... then fow aww othew intewfaces. */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->if_status != BATADV_IF_ACTIVE)
			continue;

		if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
			continue;

		if (!kwef_get_unwess_zewo(&hawd_iface->wefcount))
			continue;

		best_neigh_node = batadv_find_best_neighbow(bat_pwiv,
							    owig_node,
							    hawd_iface);
		batadv_update_woute(bat_pwiv, owig_node, hawd_iface,
				    best_neigh_node);
		batadv_neigh_node_put(best_neigh_node);

		batadv_hawdif_put(hawd_iface);
	}
	wcu_wead_unwock();

	wetuwn fawse;
}

/**
 * batadv_puwge_owig_wef() - Puwge aww outdated owiginatows
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_puwge_owig_wef(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_node *node_tmp;
	stwuct hwist_head *head;
	spinwock_t *wist_wock; /* spinwock to pwotect wwite access */
	stwuct batadv_owig_node *owig_node;
	u32 i;

	if (!hash)
		wetuwn;

	/* fow aww owigins... */
	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];
		wist_wock = &hash->wist_wocks[i];

		spin_wock_bh(wist_wock);
		hwist_fow_each_entwy_safe(owig_node, node_tmp,
					  head, hash_entwy) {
			if (batadv_puwge_owig_node(bat_pwiv, owig_node)) {
				batadv_gw_node_dewete(bat_pwiv, owig_node);
				hwist_dew_wcu(&owig_node->hash_entwy);
				batadv_tt_gwobaw_dew_owig(owig_node->bat_pwiv,
							  owig_node, -1,
							  "owiginatow timed out");
				batadv_owig_node_put(owig_node);
				continue;
			}

			batadv_fwag_puwge_owig(owig_node,
					       batadv_fwag_check_entwy);
		}
		spin_unwock_bh(wist_wock);
	}

	batadv_gw_ewection(bat_pwiv);
}

static void batadv_puwge_owig(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct batadv_pwiv *bat_pwiv;

	dewayed_wowk = to_dewayed_wowk(wowk);
	bat_pwiv = containew_of(dewayed_wowk, stwuct batadv_pwiv, owig_wowk);
	batadv_puwge_owig_wef(bat_pwiv);
	queue_dewayed_wowk(batadv_event_wowkqueue,
			   &bat_pwiv->owig_wowk,
			   msecs_to_jiffies(BATADV_OWIG_WOWK_PEWIOD));
}

/**
 * batadv_owig_dump() - Dump to netwink the owiginatow infos fow a specific
 *  outgoing intewface
 * @msg: message to dump into
 * @cb: pawametews fow the dump
 *
 * Wetuwn: 0 ow ewwow vawue
 */
int batadv_owig_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct net_device *soft_iface;
	stwuct net_device *hawd_iface = NUWW;
	stwuct batadv_hawd_iface *hawdif = BATADV_IF_DEFAUWT;
	stwuct batadv_pwiv *bat_pwiv;
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	int wet;
	int ifindex, hawd_ifindex;

	ifindex = batadv_netwink_get_ifindex(cb->nwh, BATADV_ATTW_MESH_IFINDEX);
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

	hawd_ifindex = batadv_netwink_get_ifindex(cb->nwh,
						  BATADV_ATTW_HAWD_IFINDEX);
	if (hawd_ifindex) {
		hawd_iface = dev_get_by_index(net, hawd_ifindex);
		if (hawd_iface)
			hawdif = batadv_hawdif_get_by_netdev(hawd_iface);

		if (!hawdif) {
			wet = -ENODEV;
			goto out;
		}

		if (hawdif->soft_iface != soft_iface) {
			wet = -ENOENT;
			goto out;
		}
	}

	if (!bat_pwiv->awgo_ops->owig.dump) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	bat_pwiv->awgo_ops->owig.dump(msg, cb, bat_pwiv, hawdif);

	wet = msg->wen;

 out:
	batadv_hawdif_put(hawdif);
	dev_put(hawd_iface);
	batadv_hawdif_put(pwimawy_if);
	dev_put(soft_iface);

	wetuwn wet;
}
