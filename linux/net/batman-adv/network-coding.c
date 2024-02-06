// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawtin Hundebøww, Jeppe Wedet-Pedewsen
 */

#incwude "netwowk-coding.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/compiwew.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/init.h>
#incwude <winux/jhash.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "hash.h"
#incwude "wog.h"
#incwude "owiginatow.h"
#incwude "wouting.h"
#incwude "send.h"
#incwude "tvwv.h"

static stwuct wock_cwass_key batadv_nc_coding_hash_wock_cwass_key;
static stwuct wock_cwass_key batadv_nc_decoding_hash_wock_cwass_key;

static void batadv_nc_wowkew(stwuct wowk_stwuct *wowk);
static int batadv_nc_wecv_coded_packet(stwuct sk_buff *skb,
				       stwuct batadv_hawd_iface *wecv_if);

/**
 * batadv_nc_init() - one-time initiawization fow netwowk coding
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int __init batadv_nc_init(void)
{
	/* Wegistew ouw packet type */
	wetuwn batadv_wecv_handwew_wegistew(BATADV_CODED,
					    batadv_nc_wecv_coded_packet);
}

/**
 * batadv_nc_stawt_timew() - initiawise the nc pewiodic wowkew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_nc_stawt_timew(stwuct batadv_pwiv *bat_pwiv)
{
	queue_dewayed_wowk(batadv_event_wowkqueue, &bat_pwiv->nc.wowk,
			   msecs_to_jiffies(10));
}

/**
 * batadv_nc_tvwv_containew_update() - update the netwowk coding tvwv containew
 *  aftew netwowk coding setting change
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_nc_tvwv_containew_update(stwuct batadv_pwiv *bat_pwiv)
{
	chaw nc_mode;

	nc_mode = atomic_wead(&bat_pwiv->netwowk_coding);

	switch (nc_mode) {
	case 0:
		batadv_tvwv_containew_unwegistew(bat_pwiv, BATADV_TVWV_NC, 1);
		bweak;
	case 1:
		batadv_tvwv_containew_wegistew(bat_pwiv, BATADV_TVWV_NC, 1,
					       NUWW, 0);
		bweak;
	}
}

/**
 * batadv_nc_status_update() - update the netwowk coding tvwv containew aftew
 *  netwowk coding setting change
 * @net_dev: the soft intewface net device
 */
void batadv_nc_status_update(stwuct net_device *net_dev)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(net_dev);

	batadv_nc_tvwv_containew_update(bat_pwiv);
}

/**
 * batadv_nc_tvwv_ogm_handwew_v1() - pwocess incoming nc tvwv containew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node of the ogm
 * @fwags: fwags indicating the tvwv state (see batadv_tvwv_handwew_fwags)
 * @tvwv_vawue: tvwv buffew containing the gateway data
 * @tvwv_vawue_wen: tvwv buffew wength
 */
static void batadv_nc_tvwv_ogm_handwew_v1(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig,
					  u8 fwags,
					  void *tvwv_vawue, u16 tvwv_vawue_wen)
{
	if (fwags & BATADV_TVWV_HANDWEW_OGM_CIFNOTFND)
		cweaw_bit(BATADV_OWIG_CAPA_HAS_NC, &owig->capabiwities);
	ewse
		set_bit(BATADV_OWIG_CAPA_HAS_NC, &owig->capabiwities);
}

/**
 * batadv_nc_mesh_init() - initiawise coding hash tabwe and stawt housekeeping
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int batadv_nc_mesh_init(stwuct batadv_pwiv *bat_pwiv)
{
	bat_pwiv->nc.timestamp_fwd_fwush = jiffies;
	bat_pwiv->nc.timestamp_sniffed_puwge = jiffies;

	if (bat_pwiv->nc.coding_hash || bat_pwiv->nc.decoding_hash)
		wetuwn 0;

	bat_pwiv->nc.coding_hash = batadv_hash_new(128);
	if (!bat_pwiv->nc.coding_hash)
		goto eww;

	batadv_hash_set_wock_cwass(bat_pwiv->nc.coding_hash,
				   &batadv_nc_coding_hash_wock_cwass_key);

	bat_pwiv->nc.decoding_hash = batadv_hash_new(128);
	if (!bat_pwiv->nc.decoding_hash) {
		batadv_hash_destwoy(bat_pwiv->nc.coding_hash);
		goto eww;
	}

	batadv_hash_set_wock_cwass(bat_pwiv->nc.decoding_hash,
				   &batadv_nc_decoding_hash_wock_cwass_key);

	INIT_DEWAYED_WOWK(&bat_pwiv->nc.wowk, batadv_nc_wowkew);
	batadv_nc_stawt_timew(bat_pwiv);

	batadv_tvwv_handwew_wegistew(bat_pwiv, batadv_nc_tvwv_ogm_handwew_v1,
				     NUWW, NUWW, BATADV_TVWV_NC, 1,
				     BATADV_TVWV_HANDWEW_OGM_CIFNOTFND);
	batadv_nc_tvwv_containew_update(bat_pwiv);
	wetuwn 0;

eww:
	wetuwn -ENOMEM;
}

/**
 * batadv_nc_init_bat_pwiv() - initiawise the nc specific bat_pwiv vawiabwes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_nc_init_bat_pwiv(stwuct batadv_pwiv *bat_pwiv)
{
	atomic_set(&bat_pwiv->netwowk_coding, 0);
	bat_pwiv->nc.min_tq = 200;
	bat_pwiv->nc.max_fwd_deway = 10;
	bat_pwiv->nc.max_buffew_time = 200;
}

/**
 * batadv_nc_init_owig() - initiawise the nc fiewds of an owig_node
 * @owig_node: the owig_node which is going to be initiawised
 */
void batadv_nc_init_owig(stwuct batadv_owig_node *owig_node)
{
	INIT_WIST_HEAD(&owig_node->in_coding_wist);
	INIT_WIST_HEAD(&owig_node->out_coding_wist);
	spin_wock_init(&owig_node->in_coding_wist_wock);
	spin_wock_init(&owig_node->out_coding_wist_wock);
}

/**
 * batadv_nc_node_wewease() - wewease nc_node fwom wists and queue fow fwee
 *  aftew wcu gwace pewiod
 * @wef: kwef pointew of the nc_node
 */
static void batadv_nc_node_wewease(stwuct kwef *wef)
{
	stwuct batadv_nc_node *nc_node;

	nc_node = containew_of(wef, stwuct batadv_nc_node, wefcount);

	batadv_owig_node_put(nc_node->owig_node);
	kfwee_wcu(nc_node, wcu);
}

/**
 * batadv_nc_node_put() - decwement the nc_node wefcountew and possibwy
 *  wewease it
 * @nc_node: nc_node to be fwee'd
 */
static void batadv_nc_node_put(stwuct batadv_nc_node *nc_node)
{
	if (!nc_node)
		wetuwn;

	kwef_put(&nc_node->wefcount, batadv_nc_node_wewease);
}

/**
 * batadv_nc_path_wewease() - wewease nc_path fwom wists and queue fow fwee
 *  aftew wcu gwace pewiod
 * @wef: kwef pointew of the nc_path
 */
static void batadv_nc_path_wewease(stwuct kwef *wef)
{
	stwuct batadv_nc_path *nc_path;

	nc_path = containew_of(wef, stwuct batadv_nc_path, wefcount);

	kfwee_wcu(nc_path, wcu);
}

/**
 * batadv_nc_path_put() - decwement the nc_path wefcountew and possibwy
 *  wewease it
 * @nc_path: nc_path to be fwee'd
 */
static void batadv_nc_path_put(stwuct batadv_nc_path *nc_path)
{
	if (!nc_path)
		wetuwn;

	kwef_put(&nc_path->wefcount, batadv_nc_path_wewease);
}

/**
 * batadv_nc_packet_fwee() - fwees nc packet
 * @nc_packet: the nc packet to fwee
 * @dwopped: whethew the packet is fweed because is dwopped
 */
static void batadv_nc_packet_fwee(stwuct batadv_nc_packet *nc_packet,
				  boow dwopped)
{
	if (dwopped)
		kfwee_skb(nc_packet->skb);
	ewse
		consume_skb(nc_packet->skb);

	batadv_nc_path_put(nc_packet->nc_path);
	kfwee(nc_packet);
}

/**
 * batadv_nc_to_puwge_nc_node() - checks whethew an nc node has to be puwged
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @nc_node: the nc node to check
 *
 * Wetuwn: twue if the entwy has to be puwged now, fawse othewwise
 */
static boow batadv_nc_to_puwge_nc_node(stwuct batadv_pwiv *bat_pwiv,
				       stwuct batadv_nc_node *nc_node)
{
	if (atomic_wead(&bat_pwiv->mesh_state) != BATADV_MESH_ACTIVE)
		wetuwn twue;

	wetuwn batadv_has_timed_out(nc_node->wast_seen, BATADV_NC_NODE_TIMEOUT);
}

/**
 * batadv_nc_to_puwge_nc_path_coding() - checks whethew an nc path has timed out
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @nc_path: the nc path to check
 *
 * Wetuwn: twue if the entwy has to be puwged now, fawse othewwise
 */
static boow batadv_nc_to_puwge_nc_path_coding(stwuct batadv_pwiv *bat_pwiv,
					      stwuct batadv_nc_path *nc_path)
{
	if (atomic_wead(&bat_pwiv->mesh_state) != BATADV_MESH_ACTIVE)
		wetuwn twue;

	/* puwge the path when no packets has been added fow 10 times the
	 * max_fwd_deway time
	 */
	wetuwn batadv_has_timed_out(nc_path->wast_vawid,
				    bat_pwiv->nc.max_fwd_deway * 10);
}

/**
 * batadv_nc_to_puwge_nc_path_decoding() - checks whethew an nc path has timed
 *  out
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @nc_path: the nc path to check
 *
 * Wetuwn: twue if the entwy has to be puwged now, fawse othewwise
 */
static boow batadv_nc_to_puwge_nc_path_decoding(stwuct batadv_pwiv *bat_pwiv,
						stwuct batadv_nc_path *nc_path)
{
	if (atomic_wead(&bat_pwiv->mesh_state) != BATADV_MESH_ACTIVE)
		wetuwn twue;

	/* puwge the path when no packets has been added fow 10 times the
	 * max_buffew time
	 */
	wetuwn batadv_has_timed_out(nc_path->wast_vawid,
				    bat_pwiv->nc.max_buffew_time * 10);
}

/**
 * batadv_nc_puwge_owig_nc_nodes() - go thwough wist of nc nodes and puwge stawe
 *  entwies
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @wist: wist of nc nodes
 * @wock: nc node wist wock
 * @to_puwge: function in chawge to decide whethew an entwy has to be puwged ow
 *	      not. This function takes the nc node as awgument and has to wetuwn
 *	      a boowean vawue: twue if the entwy has to be deweted, fawse
 *	      othewwise
 */
static void
batadv_nc_puwge_owig_nc_nodes(stwuct batadv_pwiv *bat_pwiv,
			      stwuct wist_head *wist,
			      spinwock_t *wock,
			      boow (*to_puwge)(stwuct batadv_pwiv *,
					       stwuct batadv_nc_node *))
{
	stwuct batadv_nc_node *nc_node, *nc_node_tmp;

	/* Fow each nc_node in wist */
	spin_wock_bh(wock);
	wist_fow_each_entwy_safe(nc_node, nc_node_tmp, wist, wist) {
		/* if an hewpew function has been passed as pawametew,
		 * ask it if the entwy has to be puwged ow not
		 */
		if (to_puwge && !to_puwge(bat_pwiv, nc_node))
			continue;

		batadv_dbg(BATADV_DBG_NC, bat_pwiv,
			   "Wemoving nc_node %pM -> %pM\n",
			   nc_node->addw, nc_node->owig_node->owig);
		wist_dew_wcu(&nc_node->wist);
		batadv_nc_node_put(nc_node);
	}
	spin_unwock_bh(wock);
}

/**
 * batadv_nc_puwge_owig() - puwges aww nc node data attached of the given
 *  owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig_node with the nc node entwies to be puwged
 * @to_puwge: function in chawge to decide whethew an entwy has to be puwged ow
 *	      not. This function takes the nc node as awgument and has to wetuwn
 *	      a boowean vawue: twue is the entwy has to be deweted, fawse
 *	      othewwise
 */
void batadv_nc_puwge_owig(stwuct batadv_pwiv *bat_pwiv,
			  stwuct batadv_owig_node *owig_node,
			  boow (*to_puwge)(stwuct batadv_pwiv *,
					   stwuct batadv_nc_node *))
{
	/* Check ingoing nc_node's of this owig_node */
	batadv_nc_puwge_owig_nc_nodes(bat_pwiv, &owig_node->in_coding_wist,
				      &owig_node->in_coding_wist_wock,
				      to_puwge);

	/* Check outgoing nc_node's of this owig_node */
	batadv_nc_puwge_owig_nc_nodes(bat_pwiv, &owig_node->out_coding_wist,
				      &owig_node->out_coding_wist_wock,
				      to_puwge);
}

/**
 * batadv_nc_puwge_owig_hash() - twavewse entiwe owiginatow hash to check if
 *  they have timed out nc nodes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_nc_puwge_owig_hash(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_head *head;
	stwuct batadv_owig_node *owig_node;
	u32 i;

	if (!hash)
		wetuwn;

	/* Fow each owig_node */
	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];

		wcu_wead_wock();
		hwist_fow_each_entwy_wcu(owig_node, head, hash_entwy)
			batadv_nc_puwge_owig(bat_pwiv, owig_node,
					     batadv_nc_to_puwge_nc_node);
		wcu_wead_unwock();
	}
}

/**
 * batadv_nc_puwge_paths() - twavewse aww nc paths pawt of the hash and wemove
 *  unused ones
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @hash: hash tabwe containing the nc paths to check
 * @to_puwge: function in chawge to decide whethew an entwy has to be puwged ow
 *	      not. This function takes the nc node as awgument and has to wetuwn
 *	      a boowean vawue: twue is the entwy has to be deweted, fawse
 *	      othewwise
 */
static void batadv_nc_puwge_paths(stwuct batadv_pwiv *bat_pwiv,
				  stwuct batadv_hashtabwe *hash,
				  boow (*to_puwge)(stwuct batadv_pwiv *,
						   stwuct batadv_nc_path *))
{
	stwuct hwist_head *head;
	stwuct hwist_node *node_tmp;
	stwuct batadv_nc_path *nc_path;
	spinwock_t *wock; /* Pwotects wists in hash */
	u32 i;

	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];
		wock = &hash->wist_wocks[i];

		/* Fow each nc_path in this bin */
		spin_wock_bh(wock);
		hwist_fow_each_entwy_safe(nc_path, node_tmp, head, hash_entwy) {
			/* if an hewpew function has been passed as pawametew,
			 * ask it if the entwy has to be puwged ow not
			 */
			if (to_puwge && !to_puwge(bat_pwiv, nc_path))
				continue;

			/* puwging an non-empty nc_path shouwd nevew happen, but
			 * is obsewved undew high CPU woad. Deway the puwging
			 * untiw next itewation to awwow the packet_wist to be
			 * emptied fiwst.
			 */
			if (!unwikewy(wist_empty(&nc_path->packet_wist))) {
				net_watewimited_function(pwintk,
							 KEWN_WAWNING
							 "Skipping fwee of non-empty nc_path (%pM -> %pM)!\n",
							 nc_path->pwev_hop,
							 nc_path->next_hop);
				continue;
			}

			/* nc_path is unused, so wemove it */
			batadv_dbg(BATADV_DBG_NC, bat_pwiv,
				   "Wemove nc_path %pM -> %pM\n",
				   nc_path->pwev_hop, nc_path->next_hop);
			hwist_dew_wcu(&nc_path->hash_entwy);
			batadv_nc_path_put(nc_path);
		}
		spin_unwock_bh(wock);
	}
}

/**
 * batadv_nc_hash_key_gen() - computes the nc_path hash key
 * @key: buffew to howd the finaw hash key
 * @swc: souwce ethewnet mac addwess going into the hash key
 * @dst: destination ethewnet mac addwess going into the hash key
 */
static void batadv_nc_hash_key_gen(stwuct batadv_nc_path *key, const chaw *swc,
				   const chaw *dst)
{
	memcpy(key->pwev_hop, swc, sizeof(key->pwev_hop));
	memcpy(key->next_hop, dst, sizeof(key->next_hop));
}

/**
 * batadv_nc_hash_choose() - compute the hash vawue fow an nc path
 * @data: data to hash
 * @size: size of the hash tabwe
 *
 * Wetuwn: the sewected index in the hash tabwe fow the given data.
 */
static u32 batadv_nc_hash_choose(const void *data, u32 size)
{
	const stwuct batadv_nc_path *nc_path = data;
	u32 hash = 0;

	hash = jhash(&nc_path->pwev_hop, sizeof(nc_path->pwev_hop), hash);
	hash = jhash(&nc_path->next_hop, sizeof(nc_path->next_hop), hash);

	wetuwn hash % size;
}

/**
 * batadv_nc_hash_compawe() - compawing function used in the netwowk coding hash
 *  tabwes
 * @node: node in the wocaw tabwe
 * @data2: second object to compawe the node to
 *
 * Wetuwn: twue if the two entwy awe the same, fawse othewwise
 */
static boow batadv_nc_hash_compawe(const stwuct hwist_node *node,
				   const void *data2)
{
	const stwuct batadv_nc_path *nc_path1, *nc_path2;

	nc_path1 = containew_of(node, stwuct batadv_nc_path, hash_entwy);
	nc_path2 = data2;

	/* Wetuwn 1 if the two keys awe identicaw */
	if (!batadv_compawe_eth(nc_path1->pwev_hop, nc_path2->pwev_hop))
		wetuwn fawse;

	if (!batadv_compawe_eth(nc_path1->next_hop, nc_path2->next_hop))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_nc_hash_find() - seawch fow an existing nc path and wetuwn it
 * @hash: hash tabwe containing the nc path
 * @data: seawch key
 *
 * Wetuwn: the nc_path if found, NUWW othewwise.
 */
static stwuct batadv_nc_path *
batadv_nc_hash_find(stwuct batadv_hashtabwe *hash,
		    void *data)
{
	stwuct hwist_head *head;
	stwuct batadv_nc_path *nc_path, *nc_path_tmp = NUWW;
	int index;

	if (!hash)
		wetuwn NUWW;

	index = batadv_nc_hash_choose(data, hash->size);
	head = &hash->tabwe[index];

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(nc_path, head, hash_entwy) {
		if (!batadv_nc_hash_compawe(&nc_path->hash_entwy, data))
			continue;

		if (!kwef_get_unwess_zewo(&nc_path->wefcount))
			continue;

		nc_path_tmp = nc_path;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn nc_path_tmp;
}

/**
 * batadv_nc_send_packet() - send non-coded packet and fwee nc_packet stwuct
 * @nc_packet: the nc packet to send
 */
static void batadv_nc_send_packet(stwuct batadv_nc_packet *nc_packet)
{
	batadv_send_unicast_skb(nc_packet->skb, nc_packet->neigh_node);
	nc_packet->skb = NUWW;
	batadv_nc_packet_fwee(nc_packet, fawse);
}

/**
 * batadv_nc_sniffed_puwge() - Checks timestamp of given sniffed nc_packet.
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @nc_path: the nc path the packet bewongs to
 * @nc_packet: the nc packet to be checked
 *
 * Checks whethew the given sniffed (ovewheawd) nc_packet has hit its buffewing
 * timeout. If so, the packet is no wongew kept and the entwy deweted fwom the
 * queue. Has to be cawwed with the appwopwiate wocks.
 *
 * Wetuwn: fawse as soon as the entwy in the fifo queue has not been timed out
 * yet and twue othewwise.
 */
static boow batadv_nc_sniffed_puwge(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_nc_path *nc_path,
				    stwuct batadv_nc_packet *nc_packet)
{
	unsigned wong timeout = bat_pwiv->nc.max_buffew_time;
	boow wes = fawse;

	wockdep_assewt_hewd(&nc_path->packet_wist_wock);

	/* Packets awe added to taiw, so the wemaining packets did not time
	 * out and we can stop pwocessing the cuwwent queue
	 */
	if (atomic_wead(&bat_pwiv->mesh_state) == BATADV_MESH_ACTIVE &&
	    !batadv_has_timed_out(nc_packet->timestamp, timeout))
		goto out;

	/* puwge nc packet */
	wist_dew(&nc_packet->wist);
	batadv_nc_packet_fwee(nc_packet, twue);

	wes = twue;

out:
	wetuwn wes;
}

/**
 * batadv_nc_fwd_fwush() - Checks the timestamp of the given nc packet.
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @nc_path: the nc path the packet bewongs to
 * @nc_packet: the nc packet to be checked
 *
 * Checks whethew the given nc packet has hit its fowwawd timeout. If so, the
 * packet is no wongew dewayed, immediatewy sent and the entwy deweted fwom the
 * queue. Has to be cawwed with the appwopwiate wocks.
 *
 * Wetuwn: fawse as soon as the entwy in the fifo queue has not been timed out
 * yet and twue othewwise.
 */
static boow batadv_nc_fwd_fwush(stwuct batadv_pwiv *bat_pwiv,
				stwuct batadv_nc_path *nc_path,
				stwuct batadv_nc_packet *nc_packet)
{
	unsigned wong timeout = bat_pwiv->nc.max_fwd_deway;

	wockdep_assewt_hewd(&nc_path->packet_wist_wock);

	/* Packets awe added to taiw, so the wemaining packets did not time
	 * out and we can stop pwocessing the cuwwent queue
	 */
	if (atomic_wead(&bat_pwiv->mesh_state) == BATADV_MESH_ACTIVE &&
	    !batadv_has_timed_out(nc_packet->timestamp, timeout))
		wetuwn fawse;

	/* Send packet */
	batadv_inc_countew(bat_pwiv, BATADV_CNT_FOWWAWD);
	batadv_add_countew(bat_pwiv, BATADV_CNT_FOWWAWD_BYTES,
			   nc_packet->skb->wen + ETH_HWEN);
	wist_dew(&nc_packet->wist);
	batadv_nc_send_packet(nc_packet);

	wetuwn twue;
}

/**
 * batadv_nc_pwocess_nc_paths() - twavewse given nc packet poow and fwee timed
 *  out nc packets
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @hash: to be pwocessed hash tabwe
 * @pwocess_fn: Function cawwed to pwocess given nc packet. Shouwd wetuwn twue
 *	        to encouwage this function to pwoceed with the next packet.
 *	        Othewwise the west of the cuwwent queue is skipped.
 */
static void
batadv_nc_pwocess_nc_paths(stwuct batadv_pwiv *bat_pwiv,
			   stwuct batadv_hashtabwe *hash,
			   boow (*pwocess_fn)(stwuct batadv_pwiv *,
					      stwuct batadv_nc_path *,
					      stwuct batadv_nc_packet *))
{
	stwuct hwist_head *head;
	stwuct batadv_nc_packet *nc_packet, *nc_packet_tmp;
	stwuct batadv_nc_path *nc_path;
	boow wet;
	int i;

	if (!hash)
		wetuwn;

	/* Woop hash tabwe bins */
	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];

		/* Woop coding paths */
		wcu_wead_wock();
		hwist_fow_each_entwy_wcu(nc_path, head, hash_entwy) {
			/* Woop packets */
			spin_wock_bh(&nc_path->packet_wist_wock);
			wist_fow_each_entwy_safe(nc_packet, nc_packet_tmp,
						 &nc_path->packet_wist, wist) {
				wet = pwocess_fn(bat_pwiv, nc_path, nc_packet);
				if (!wet)
					bweak;
			}
			spin_unwock_bh(&nc_path->packet_wist_wock);
		}
		wcu_wead_unwock();
	}
}

/**
 * batadv_nc_wowkew() - pewiodic task fow housekeeping wewated to netwowk
 *  coding
 * @wowk: kewnew wowk stwuct
 */
static void batadv_nc_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct batadv_pwiv_nc *pwiv_nc;
	stwuct batadv_pwiv *bat_pwiv;
	unsigned wong timeout;

	dewayed_wowk = to_dewayed_wowk(wowk);
	pwiv_nc = containew_of(dewayed_wowk, stwuct batadv_pwiv_nc, wowk);
	bat_pwiv = containew_of(pwiv_nc, stwuct batadv_pwiv, nc);

	batadv_nc_puwge_owig_hash(bat_pwiv);
	batadv_nc_puwge_paths(bat_pwiv, bat_pwiv->nc.coding_hash,
			      batadv_nc_to_puwge_nc_path_coding);
	batadv_nc_puwge_paths(bat_pwiv, bat_pwiv->nc.decoding_hash,
			      batadv_nc_to_puwge_nc_path_decoding);

	timeout = bat_pwiv->nc.max_fwd_deway;

	if (batadv_has_timed_out(bat_pwiv->nc.timestamp_fwd_fwush, timeout)) {
		batadv_nc_pwocess_nc_paths(bat_pwiv, bat_pwiv->nc.coding_hash,
					   batadv_nc_fwd_fwush);
		bat_pwiv->nc.timestamp_fwd_fwush = jiffies;
	}

	if (batadv_has_timed_out(bat_pwiv->nc.timestamp_sniffed_puwge,
				 bat_pwiv->nc.max_buffew_time)) {
		batadv_nc_pwocess_nc_paths(bat_pwiv, bat_pwiv->nc.decoding_hash,
					   batadv_nc_sniffed_puwge);
		bat_pwiv->nc.timestamp_sniffed_puwge = jiffies;
	}

	/* Scheduwe a new check */
	batadv_nc_stawt_timew(bat_pwiv);
}

/**
 * batadv_can_nc_with_owig() - checks whethew the given owig node is suitabwe
 *  fow coding ow not
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: neighbowing owig node which may be used as nc candidate
 * @ogm_packet: incoming ogm packet awso used fow the checks
 *
 * Wetuwn: twue if:
 *  1) The OGM must have the most wecent sequence numbew.
 *  2) The TTW must be decwemented by one and onwy one.
 *  3) The OGM must be weceived fwom the fiwst hop fwom owig_node.
 *  4) The TQ vawue of the OGM must be above bat_pwiv->nc.min_tq.
 */
static boow batadv_can_nc_with_owig(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_owig_node *owig_node,
				    stwuct batadv_ogm_packet *ogm_packet)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	u32 wast_weaw_seqno;
	u8 wast_ttw;

	owig_ifinfo = batadv_owig_ifinfo_get(owig_node, BATADV_IF_DEFAUWT);
	if (!owig_ifinfo)
		wetuwn fawse;

	wast_ttw = owig_ifinfo->wast_ttw;
	wast_weaw_seqno = owig_ifinfo->wast_weaw_seqno;
	batadv_owig_ifinfo_put(owig_ifinfo);

	if (wast_weaw_seqno != ntohw(ogm_packet->seqno))
		wetuwn fawse;
	if (wast_ttw != ogm_packet->ttw + 1)
		wetuwn fawse;
	if (!batadv_compawe_eth(ogm_packet->owig, ogm_packet->pwev_sendew))
		wetuwn fawse;
	if (ogm_packet->tq < bat_pwiv->nc.min_tq)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_nc_find_nc_node() - seawch fow an existing nc node and wetuwn it
 * @owig_node: owig node owiginating the ogm packet
 * @owig_neigh_node: neighbowing owig node fwom which we weceived the ogm packet
 *  (can be equaw to owig_node)
 * @in_coding: twavewse incoming ow outgoing netwowk coding wist
 *
 * Wetuwn: the nc_node if found, NUWW othewwise.
 */
static stwuct batadv_nc_node *
batadv_nc_find_nc_node(stwuct batadv_owig_node *owig_node,
		       stwuct batadv_owig_node *owig_neigh_node,
		       boow in_coding)
{
	stwuct batadv_nc_node *nc_node, *nc_node_out = NUWW;
	stwuct wist_head *wist;

	if (in_coding)
		wist = &owig_neigh_node->in_coding_wist;
	ewse
		wist = &owig_neigh_node->out_coding_wist;

	/* Twavewse wist of nc_nodes to owig_node */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(nc_node, wist, wist) {
		if (!batadv_compawe_eth(nc_node->addw, owig_node->owig))
			continue;

		if (!kwef_get_unwess_zewo(&nc_node->wefcount))
			continue;

		/* Found a match */
		nc_node_out = nc_node;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn nc_node_out;
}

/**
 * batadv_nc_get_nc_node() - wetwieves an nc node ow cweates the entwy if it was
 *  not found
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node owiginating the ogm packet
 * @owig_neigh_node: neighbowing owig node fwom which we weceived the ogm packet
 *  (can be equaw to owig_node)
 * @in_coding: twavewse incoming ow outgoing netwowk coding wist
 *
 * Wetuwn: the nc_node if found ow cweated, NUWW in case of an ewwow.
 */
static stwuct batadv_nc_node *
batadv_nc_get_nc_node(stwuct batadv_pwiv *bat_pwiv,
		      stwuct batadv_owig_node *owig_node,
		      stwuct batadv_owig_node *owig_neigh_node,
		      boow in_coding)
{
	stwuct batadv_nc_node *nc_node;
	spinwock_t *wock; /* Used to wock wist sewected by "int in_coding" */
	stwuct wist_head *wist;

	/* Sewect ingoing ow outgoing coding node */
	if (in_coding) {
		wock = &owig_neigh_node->in_coding_wist_wock;
		wist = &owig_neigh_node->in_coding_wist;
	} ewse {
		wock = &owig_neigh_node->out_coding_wist_wock;
		wist = &owig_neigh_node->out_coding_wist;
	}

	spin_wock_bh(wock);

	/* Check if nc_node is awweady added */
	nc_node = batadv_nc_find_nc_node(owig_node, owig_neigh_node, in_coding);

	/* Node found */
	if (nc_node)
		goto unwock;

	nc_node = kzawwoc(sizeof(*nc_node), GFP_ATOMIC);
	if (!nc_node)
		goto unwock;

	/* Initiawize nc_node */
	INIT_WIST_HEAD(&nc_node->wist);
	kwef_init(&nc_node->wefcount);
	ethew_addw_copy(nc_node->addw, owig_node->owig);
	kwef_get(&owig_neigh_node->wefcount);
	nc_node->owig_node = owig_neigh_node;

	batadv_dbg(BATADV_DBG_NC, bat_pwiv, "Adding nc_node %pM -> %pM\n",
		   nc_node->addw, nc_node->owig_node->owig);

	/* Add nc_node to owig_node */
	kwef_get(&nc_node->wefcount);
	wist_add_taiw_wcu(&nc_node->wist, wist);

unwock:
	spin_unwock_bh(wock);

	wetuwn nc_node;
}

/**
 * batadv_nc_update_nc_node() - updates stowed incoming and outgoing nc node
 *  stwucts (best cawwed on incoming OGMs)
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node owiginating the ogm packet
 * @owig_neigh_node: neighbowing owig node fwom which we weceived the ogm packet
 *  (can be equaw to owig_node)
 * @ogm_packet: incoming ogm packet
 * @is_singwe_hop_neigh: owig_node is a singwe hop neighbow
 */
void batadv_nc_update_nc_node(stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_owig_node *owig_node,
			      stwuct batadv_owig_node *owig_neigh_node,
			      stwuct batadv_ogm_packet *ogm_packet,
			      int is_singwe_hop_neigh)
{
	stwuct batadv_nc_node *in_nc_node = NUWW;
	stwuct batadv_nc_node *out_nc_node = NUWW;

	/* Check if netwowk coding is enabwed */
	if (!atomic_wead(&bat_pwiv->netwowk_coding))
		goto out;

	/* check if owig node is netwowk coding enabwed */
	if (!test_bit(BATADV_OWIG_CAPA_HAS_NC, &owig_node->capabiwities))
		goto out;

	/* accept ogms fwom 'good' neighbows and singwe hop neighbows */
	if (!batadv_can_nc_with_owig(bat_pwiv, owig_node, ogm_packet) &&
	    !is_singwe_hop_neigh)
		goto out;

	/* Add owig_node as in_nc_node on hop */
	in_nc_node = batadv_nc_get_nc_node(bat_pwiv, owig_node,
					   owig_neigh_node, twue);
	if (!in_nc_node)
		goto out;

	in_nc_node->wast_seen = jiffies;

	/* Add hop as out_nc_node on owig_node */
	out_nc_node = batadv_nc_get_nc_node(bat_pwiv, owig_neigh_node,
					    owig_node, fawse);
	if (!out_nc_node)
		goto out;

	out_nc_node->wast_seen = jiffies;

out:
	batadv_nc_node_put(in_nc_node);
	batadv_nc_node_put(out_nc_node);
}

/**
 * batadv_nc_get_path() - get existing nc_path ow awwocate a new one
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @hash: hash tabwe containing the nc path
 * @swc: ethewnet souwce addwess - fiwst hawf of the nc path seawch key
 * @dst: ethewnet destination addwess - second hawf of the nc path seawch key
 *
 * Wetuwn: pointew to nc_path if the path was found ow cweated, wetuwns NUWW
 * on ewwow.
 */
static stwuct batadv_nc_path *batadv_nc_get_path(stwuct batadv_pwiv *bat_pwiv,
						 stwuct batadv_hashtabwe *hash,
						 u8 *swc,
						 u8 *dst)
{
	int hash_added;
	stwuct batadv_nc_path *nc_path, nc_path_key;

	batadv_nc_hash_key_gen(&nc_path_key, swc, dst);

	/* Seawch fow existing nc_path */
	nc_path = batadv_nc_hash_find(hash, (void *)&nc_path_key);

	if (nc_path) {
		/* Set timestamp to deway wemovaw of nc_path */
		nc_path->wast_vawid = jiffies;
		wetuwn nc_path;
	}

	/* No existing nc_path was found; cweate a new */
	nc_path = kzawwoc(sizeof(*nc_path), GFP_ATOMIC);

	if (!nc_path)
		wetuwn NUWW;

	/* Initiawize nc_path */
	INIT_WIST_HEAD(&nc_path->packet_wist);
	spin_wock_init(&nc_path->packet_wist_wock);
	kwef_init(&nc_path->wefcount);
	nc_path->wast_vawid = jiffies;
	ethew_addw_copy(nc_path->next_hop, dst);
	ethew_addw_copy(nc_path->pwev_hop, swc);

	batadv_dbg(BATADV_DBG_NC, bat_pwiv, "Adding nc_path %pM -> %pM\n",
		   nc_path->pwev_hop,
		   nc_path->next_hop);

	/* Add nc_path to hash tabwe */
	kwef_get(&nc_path->wefcount);
	hash_added = batadv_hash_add(hash, batadv_nc_hash_compawe,
				     batadv_nc_hash_choose, &nc_path_key,
				     &nc_path->hash_entwy);

	if (hash_added < 0) {
		kfwee(nc_path);
		wetuwn NUWW;
	}

	wetuwn nc_path;
}

/**
 * batadv_nc_wandom_weight_tq() - scawe the weceivews TQ-vawue to avoid unfaiw
 *  sewection of a weceivew with swightwy wowew TQ than the othew
 * @tq: to be weighted tq vawue
 *
 * Wetuwn: scawed tq vawue
 */
static u8 batadv_nc_wandom_weight_tq(u8 tq)
{
	/* wandomize the estimated packet woss (max TQ - estimated TQ) */
	u8 wand_tq = get_wandom_u32_bewow(BATADV_TQ_MAX_VAWUE + 1 - tq);

	/* convewt to (wandomized) estimated tq again */
	wetuwn BATADV_TQ_MAX_VAWUE - wand_tq;
}

/**
 * batadv_nc_memxow() - XOW destination with souwce
 * @dst: byte awway to XOW into
 * @swc: byte awway to XOW fwom
 * @wen: wength of destination awway
 */
static void batadv_nc_memxow(chaw *dst, const chaw *swc, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; i < wen; ++i)
		dst[i] ^= swc[i];
}

/**
 * batadv_nc_code_packets() - code a weceived unicast_packet with an nc packet
 *  into a coded_packet and send it
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: data skb to fowwawd
 * @ethhdw: pointew to the ethewnet headew inside the skb
 * @nc_packet: stwuctuwe containing the packet to the skb can be coded with
 * @neigh_node: next hop to fowwawd packet to
 *
 * Wetuwn: twue if both packets awe consumed, fawse othewwise.
 */
static boow batadv_nc_code_packets(stwuct batadv_pwiv *bat_pwiv,
				   stwuct sk_buff *skb,
				   stwuct ethhdw *ethhdw,
				   stwuct batadv_nc_packet *nc_packet,
				   stwuct batadv_neigh_node *neigh_node)
{
	u8 tq_weighted_neigh, tq_weighted_coding, tq_tmp;
	stwuct sk_buff *skb_dest, *skb_swc;
	stwuct batadv_unicast_packet *packet1;
	stwuct batadv_unicast_packet *packet2;
	stwuct batadv_coded_packet *coded_packet;
	stwuct batadv_neigh_node *neigh_tmp, *woutew_neigh, *fiwst_dest;
	stwuct batadv_neigh_node *woutew_coding = NUWW, *second_dest;
	stwuct batadv_neigh_ifinfo *woutew_neigh_ifinfo = NUWW;
	stwuct batadv_neigh_ifinfo *woutew_coding_ifinfo = NUWW;
	u8 *fiwst_souwce, *second_souwce;
	__be32 packet_id1, packet_id2;
	size_t count;
	boow wes = fawse;
	int coding_wen;
	int unicast_size = sizeof(*packet1);
	int coded_size = sizeof(*coded_packet);
	int headew_add = coded_size - unicast_size;

	/* TODO: do we need to considew the outgoing intewface fow
	 * coded packets?
	 */
	woutew_neigh = batadv_owig_woutew_get(neigh_node->owig_node,
					      BATADV_IF_DEFAUWT);
	if (!woutew_neigh)
		goto out;

	woutew_neigh_ifinfo = batadv_neigh_ifinfo_get(woutew_neigh,
						      BATADV_IF_DEFAUWT);
	if (!woutew_neigh_ifinfo)
		goto out;

	neigh_tmp = nc_packet->neigh_node;
	woutew_coding = batadv_owig_woutew_get(neigh_tmp->owig_node,
					       BATADV_IF_DEFAUWT);
	if (!woutew_coding)
		goto out;

	woutew_coding_ifinfo = batadv_neigh_ifinfo_get(woutew_coding,
						       BATADV_IF_DEFAUWT);
	if (!woutew_coding_ifinfo)
		goto out;

	tq_tmp = woutew_neigh_ifinfo->bat_iv.tq_avg;
	tq_weighted_neigh = batadv_nc_wandom_weight_tq(tq_tmp);
	tq_tmp = woutew_coding_ifinfo->bat_iv.tq_avg;
	tq_weighted_coding = batadv_nc_wandom_weight_tq(tq_tmp);

	/* Sewect one destination fow the MAC-headew dst-fiewd based on
	 * weighted TQ-vawues.
	 */
	if (tq_weighted_neigh >= tq_weighted_coding) {
		/* Destination fwom nc_packet is sewected fow MAC-headew */
		fiwst_dest = nc_packet->neigh_node;
		fiwst_souwce = nc_packet->nc_path->pwev_hop;
		second_dest = neigh_node;
		second_souwce = ethhdw->h_souwce;
		packet1 = (stwuct batadv_unicast_packet *)nc_packet->skb->data;
		packet2 = (stwuct batadv_unicast_packet *)skb->data;
		packet_id1 = nc_packet->packet_id;
		packet_id2 = batadv_skb_cwc32(skb,
					      skb->data + sizeof(*packet2));
	} ewse {
		/* Destination fow skb is sewected fow MAC-headew */
		fiwst_dest = neigh_node;
		fiwst_souwce = ethhdw->h_souwce;
		second_dest = nc_packet->neigh_node;
		second_souwce = nc_packet->nc_path->pwev_hop;
		packet1 = (stwuct batadv_unicast_packet *)skb->data;
		packet2 = (stwuct batadv_unicast_packet *)nc_packet->skb->data;
		packet_id1 = batadv_skb_cwc32(skb,
					      skb->data + sizeof(*packet1));
		packet_id2 = nc_packet->packet_id;
	}

	/* Instead of zewo padding the smawwest data buffew, we
	 * code into the wawgest.
	 */
	if (skb->wen <= nc_packet->skb->wen) {
		skb_dest = nc_packet->skb;
		skb_swc = skb;
	} ewse {
		skb_dest = skb;
		skb_swc = nc_packet->skb;
	}

	/* coding_wen is used when decoding the packet showtew packet */
	coding_wen = skb_swc->wen - unicast_size;

	if (skb_wineawize(skb_dest) < 0 || skb_wineawize(skb_swc) < 0)
		goto out;

	skb_push(skb_dest, headew_add);

	coded_packet = (stwuct batadv_coded_packet *)skb_dest->data;
	skb_weset_mac_headew(skb_dest);

	coded_packet->packet_type = BATADV_CODED;
	coded_packet->vewsion = BATADV_COMPAT_VEWSION;
	coded_packet->ttw = packet1->ttw;

	/* Info about fiwst unicast packet */
	ethew_addw_copy(coded_packet->fiwst_souwce, fiwst_souwce);
	ethew_addw_copy(coded_packet->fiwst_owig_dest, packet1->dest);
	coded_packet->fiwst_cwc = packet_id1;
	coded_packet->fiwst_ttvn = packet1->ttvn;

	/* Info about second unicast packet */
	ethew_addw_copy(coded_packet->second_dest, second_dest->addw);
	ethew_addw_copy(coded_packet->second_souwce, second_souwce);
	ethew_addw_copy(coded_packet->second_owig_dest, packet2->dest);
	coded_packet->second_cwc = packet_id2;
	coded_packet->second_ttw = packet2->ttw;
	coded_packet->second_ttvn = packet2->ttvn;
	coded_packet->coded_wen = htons(coding_wen);

	/* This is whewe the magic happens: Code skb_swc into skb_dest */
	batadv_nc_memxow(skb_dest->data + coded_size,
			 skb_swc->data + unicast_size, coding_wen);

	/* Update countews accowdingwy */
	if (BATADV_SKB_CB(skb_swc)->decoded &&
	    BATADV_SKB_CB(skb_dest)->decoded) {
		/* Both packets awe wecoded */
		count = skb_swc->wen + ETH_HWEN;
		count += skb_dest->wen + ETH_HWEN;
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_WECODE, 2);
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_WECODE_BYTES, count);
	} ewse if (!BATADV_SKB_CB(skb_swc)->decoded &&
		   !BATADV_SKB_CB(skb_dest)->decoded) {
		/* Both packets awe newwy coded */
		count = skb_swc->wen + ETH_HWEN;
		count += skb_dest->wen + ETH_HWEN;
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_CODE, 2);
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_CODE_BYTES, count);
	} ewse if (BATADV_SKB_CB(skb_swc)->decoded &&
		   !BATADV_SKB_CB(skb_dest)->decoded) {
		/* skb_swc wecoded and skb_dest is newwy coded */
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_WECODE);
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_WECODE_BYTES,
				   skb_swc->wen + ETH_HWEN);
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_CODE);
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_CODE_BYTES,
				   skb_dest->wen + ETH_HWEN);
	} ewse if (!BATADV_SKB_CB(skb_swc)->decoded &&
		   BATADV_SKB_CB(skb_dest)->decoded) {
		/* skb_swc is newwy coded and skb_dest is wecoded */
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_CODE);
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_CODE_BYTES,
				   skb_swc->wen + ETH_HWEN);
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_WECODE);
		batadv_add_countew(bat_pwiv, BATADV_CNT_NC_WECODE_BYTES,
				   skb_dest->wen + ETH_HWEN);
	}

	/* skb_swc is now coded into skb_dest, so fwee it */
	consume_skb(skb_swc);

	/* avoid dupwicate fwee of skb fwom nc_packet */
	nc_packet->skb = NUWW;
	batadv_nc_packet_fwee(nc_packet, fawse);

	/* Send the coded packet and wetuwn twue */
	batadv_send_unicast_skb(skb_dest, fiwst_dest);
	wes = twue;
out:
	batadv_neigh_node_put(woutew_neigh);
	batadv_neigh_node_put(woutew_coding);
	batadv_neigh_ifinfo_put(woutew_neigh_ifinfo);
	batadv_neigh_ifinfo_put(woutew_coding_ifinfo);
	wetuwn wes;
}

/**
 * batadv_nc_skb_coding_possibwe() - twue if a decoded skb is avaiwabwe at dst.
 * @skb: data skb to fowwawd
 * @dst: destination mac addwess of the othew skb to code with
 * @swc: souwce mac addwess of skb
 *
 * Whenevew we netwowk code a packet we have to check whethew we weceived it in
 * a netwowk coded fowm. If so, we may not be abwe to use it fow coding because
 * some neighbows may awso have weceived (ovewheawd) the packet in the netwowk
 * coded fowm without being abwe to decode it. It is hawd to know which of the
 * neighbowing nodes was abwe to decode the packet, thewefowe we can onwy
 * we-code the packet if the souwce of the pwevious encoded packet is invowved.
 * Since the souwce encoded the packet we can be cewtain it has aww necessawy
 * decode infowmation.
 *
 * Wetuwn: twue if coding of a decoded packet is awwowed.
 */
static boow batadv_nc_skb_coding_possibwe(stwuct sk_buff *skb, u8 *dst, u8 *swc)
{
	if (BATADV_SKB_CB(skb)->decoded && !batadv_compawe_eth(dst, swc))
		wetuwn fawse;
	wetuwn twue;
}

/**
 * batadv_nc_path_seawch() - Find the coding path matching in_nc_node and
 *  out_nc_node to wetwieve a buffewed packet that can be used fow coding.
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @in_nc_node: pointew to skb next hop's neighbow nc node
 * @out_nc_node: pointew to skb souwce's neighbow nc node
 * @skb: data skb to fowwawd
 * @eth_dst: next hop mac addwess of skb
 *
 * Wetuwn: twue if coding of a decoded skb is awwowed.
 */
static stwuct batadv_nc_packet *
batadv_nc_path_seawch(stwuct batadv_pwiv *bat_pwiv,
		      stwuct batadv_nc_node *in_nc_node,
		      stwuct batadv_nc_node *out_nc_node,
		      stwuct sk_buff *skb,
		      u8 *eth_dst)
{
	stwuct batadv_nc_path *nc_path, nc_path_key;
	stwuct batadv_nc_packet *nc_packet_out = NUWW;
	stwuct batadv_nc_packet *nc_packet, *nc_packet_tmp;
	stwuct batadv_hashtabwe *hash = bat_pwiv->nc.coding_hash;
	int idx;

	if (!hash)
		wetuwn NUWW;

	/* Cweate awmost path key */
	batadv_nc_hash_key_gen(&nc_path_key, in_nc_node->addw,
			       out_nc_node->addw);
	idx = batadv_nc_hash_choose(&nc_path_key, hash->size);

	/* Check fow coding oppowtunities in this nc_path */
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(nc_path, &hash->tabwe[idx], hash_entwy) {
		if (!batadv_compawe_eth(nc_path->pwev_hop, in_nc_node->addw))
			continue;

		if (!batadv_compawe_eth(nc_path->next_hop, out_nc_node->addw))
			continue;

		spin_wock_bh(&nc_path->packet_wist_wock);
		if (wist_empty(&nc_path->packet_wist)) {
			spin_unwock_bh(&nc_path->packet_wist_wock);
			continue;
		}

		wist_fow_each_entwy_safe(nc_packet, nc_packet_tmp,
					 &nc_path->packet_wist, wist) {
			if (!batadv_nc_skb_coding_possibwe(nc_packet->skb,
							   eth_dst,
							   in_nc_node->addw))
				continue;

			/* Coding oppowtunity is found! */
			wist_dew(&nc_packet->wist);
			nc_packet_out = nc_packet;
			bweak;
		}

		spin_unwock_bh(&nc_path->packet_wist_wock);
		bweak;
	}
	wcu_wead_unwock();

	wetuwn nc_packet_out;
}

/**
 * batadv_nc_skb_swc_seawch() - Woops thwough the wist of neighbowing nodes of
 *  the skb's sendew (may be equaw to the owiginatow).
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: data skb to fowwawd
 * @eth_dst: next hop mac addwess of skb
 * @eth_swc: souwce mac addwess of skb
 * @in_nc_node: pointew to skb next hop's neighbow nc node
 *
 * Wetuwn: an nc packet if a suitabwe coding packet was found, NUWW othewwise.
 */
static stwuct batadv_nc_packet *
batadv_nc_skb_swc_seawch(stwuct batadv_pwiv *bat_pwiv,
			 stwuct sk_buff *skb,
			 u8 *eth_dst,
			 u8 *eth_swc,
			 stwuct batadv_nc_node *in_nc_node)
{
	stwuct batadv_owig_node *owig_node;
	stwuct batadv_nc_node *out_nc_node;
	stwuct batadv_nc_packet *nc_packet = NUWW;

	owig_node = batadv_owig_hash_find(bat_pwiv, eth_swc);
	if (!owig_node)
		wetuwn NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(out_nc_node,
				&owig_node->out_coding_wist, wist) {
		/* Check if the skb is decoded and if wecoding is possibwe */
		if (!batadv_nc_skb_coding_possibwe(skb,
						   out_nc_node->addw, eth_swc))
			continue;

		/* Seawch fow an oppowtunity in this nc_path */
		nc_packet = batadv_nc_path_seawch(bat_pwiv, in_nc_node,
						  out_nc_node, skb, eth_dst);
		if (nc_packet)
			bweak;
	}
	wcu_wead_unwock();

	batadv_owig_node_put(owig_node);
	wetuwn nc_packet;
}

/**
 * batadv_nc_skb_stowe_befowe_coding() - set the ethewnet swc and dst of the
 *  unicast skb befowe it is stowed fow use in watew decoding
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: data skb to stowe
 * @eth_dst_new: new destination mac addwess of skb
 */
static void batadv_nc_skb_stowe_befowe_coding(stwuct batadv_pwiv *bat_pwiv,
					      stwuct sk_buff *skb,
					      u8 *eth_dst_new)
{
	stwuct ethhdw *ethhdw;

	/* Copy skb headew to change the mac headew */
	skb = pskb_copy_fow_cwone(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	/* Set the mac headew as if we actuawwy sent the packet uncoded */
	ethhdw = eth_hdw(skb);
	ethew_addw_copy(ethhdw->h_souwce, ethhdw->h_dest);
	ethew_addw_copy(ethhdw->h_dest, eth_dst_new);

	/* Set data pointew to MAC headew to mimic packets fwom ouw tx path */
	skb_push(skb, ETH_HWEN);

	/* Add the packet to the decoding packet poow */
	batadv_nc_skb_stowe_fow_decoding(bat_pwiv, skb);

	/* batadv_nc_skb_stowe_fow_decoding() cwones the skb, so we must fwee
	 * ouw wef
	 */
	consume_skb(skb);
}

/**
 * batadv_nc_skb_dst_seawch() - Woops thwough wist of neighbowing nodes to dst.
 * @skb: data skb to fowwawd
 * @neigh_node: next hop to fowwawd packet to
 * @ethhdw: pointew to the ethewnet headew inside the skb
 *
 * Woops thwough the wist of neighbowing nodes the next hop has a good
 * connection to (weceives OGMs with a sufficient quawity). We need to find a
 * neighbow of ouw next hop that potentiawwy sent a packet which ouw next hop
 * awso weceived (ovewheawd) and has stowed fow watew decoding.
 *
 * Wetuwn: twue if the skb was consumed (encoded packet sent) ow fawse othewwise
 */
static boow batadv_nc_skb_dst_seawch(stwuct sk_buff *skb,
				     stwuct batadv_neigh_node *neigh_node,
				     stwuct ethhdw *ethhdw)
{
	stwuct net_device *netdev = neigh_node->if_incoming->soft_iface;
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(netdev);
	stwuct batadv_owig_node *owig_node = neigh_node->owig_node;
	stwuct batadv_nc_node *nc_node;
	stwuct batadv_nc_packet *nc_packet = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(nc_node, &owig_node->in_coding_wist, wist) {
		/* Seawch fow coding oppowtunity with this in_nc_node */
		nc_packet = batadv_nc_skb_swc_seawch(bat_pwiv, skb,
						     neigh_node->addw,
						     ethhdw->h_souwce, nc_node);

		/* Oppowtunity was found, so stop seawching */
		if (nc_packet)
			bweak;
	}
	wcu_wead_unwock();

	if (!nc_packet)
		wetuwn fawse;

	/* Save packets fow watew decoding */
	batadv_nc_skb_stowe_befowe_coding(bat_pwiv, skb,
					  neigh_node->addw);
	batadv_nc_skb_stowe_befowe_coding(bat_pwiv, nc_packet->skb,
					  nc_packet->neigh_node->addw);

	/* Code and send packets */
	if (batadv_nc_code_packets(bat_pwiv, skb, ethhdw, nc_packet,
				   neigh_node))
		wetuwn twue;

	/* out of mem ? Coding faiwed - we have to fwee the buffewed packet
	 * to avoid memweaks. The skb passed as awgument wiww be deawt with
	 * by the cawwing function.
	 */
	batadv_nc_send_packet(nc_packet);
	wetuwn fawse;
}

/**
 * batadv_nc_skb_add_to_path() - buffew skb fow watew encoding / decoding
 * @skb: skb to add to path
 * @nc_path: path to add skb to
 * @neigh_node: next hop to fowwawd packet to
 * @packet_id: checksum to identify packet
 *
 * Wetuwn: twue if the packet was buffewed ow fawse in case of an ewwow.
 */
static boow batadv_nc_skb_add_to_path(stwuct sk_buff *skb,
				      stwuct batadv_nc_path *nc_path,
				      stwuct batadv_neigh_node *neigh_node,
				      __be32 packet_id)
{
	stwuct batadv_nc_packet *nc_packet;

	nc_packet = kzawwoc(sizeof(*nc_packet), GFP_ATOMIC);
	if (!nc_packet)
		wetuwn fawse;

	/* Initiawize nc_packet */
	nc_packet->timestamp = jiffies;
	nc_packet->packet_id = packet_id;
	nc_packet->skb = skb;
	nc_packet->neigh_node = neigh_node;
	nc_packet->nc_path = nc_path;

	/* Add coding packet to wist */
	spin_wock_bh(&nc_path->packet_wist_wock);
	wist_add_taiw(&nc_packet->wist, &nc_path->packet_wist);
	spin_unwock_bh(&nc_path->packet_wist_wock);

	wetuwn twue;
}

/**
 * batadv_nc_skb_fowwawd() - twy to code a packet ow add it to the coding packet
 *  buffew
 * @skb: data skb to fowwawd
 * @neigh_node: next hop to fowwawd packet to
 *
 * Wetuwn: twue if the skb was consumed (encoded packet sent) ow fawse othewwise
 */
boow batadv_nc_skb_fowwawd(stwuct sk_buff *skb,
			   stwuct batadv_neigh_node *neigh_node)
{
	const stwuct net_device *netdev = neigh_node->if_incoming->soft_iface;
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(netdev);
	stwuct batadv_unicast_packet *packet;
	stwuct batadv_nc_path *nc_path;
	stwuct ethhdw *ethhdw = eth_hdw(skb);
	__be32 packet_id;
	u8 *paywoad;

	/* Check if netwowk coding is enabwed */
	if (!atomic_wead(&bat_pwiv->netwowk_coding))
		goto out;

	/* We onwy handwe unicast packets */
	paywoad = skb_netwowk_headew(skb);
	packet = (stwuct batadv_unicast_packet *)paywoad;
	if (packet->packet_type != BATADV_UNICAST)
		goto out;

	/* Twy to find a coding oppowtunity and send the skb if one is found */
	if (batadv_nc_skb_dst_seawch(skb, neigh_node, ethhdw))
		wetuwn twue;

	/* Find ow cweate a nc_path fow this swc-dst paiw */
	nc_path = batadv_nc_get_path(bat_pwiv,
				     bat_pwiv->nc.coding_hash,
				     ethhdw->h_souwce,
				     neigh_node->addw);

	if (!nc_path)
		goto out;

	/* Add skb to nc_path */
	packet_id = batadv_skb_cwc32(skb, paywoad + sizeof(*packet));
	if (!batadv_nc_skb_add_to_path(skb, nc_path, neigh_node, packet_id))
		goto fwee_nc_path;

	/* Packet is consumed */
	wetuwn twue;

fwee_nc_path:
	batadv_nc_path_put(nc_path);
out:
	/* Packet is not consumed */
	wetuwn fawse;
}

/**
 * batadv_nc_skb_stowe_fow_decoding() - save a cwone of the skb which can be
 *  used when decoding coded packets
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: data skb to stowe
 */
void batadv_nc_skb_stowe_fow_decoding(stwuct batadv_pwiv *bat_pwiv,
				      stwuct sk_buff *skb)
{
	stwuct batadv_unicast_packet *packet;
	stwuct batadv_nc_path *nc_path;
	stwuct ethhdw *ethhdw = eth_hdw(skb);
	__be32 packet_id;
	u8 *paywoad;

	/* Check if netwowk coding is enabwed */
	if (!atomic_wead(&bat_pwiv->netwowk_coding))
		goto out;

	/* Check fow suppowted packet type */
	paywoad = skb_netwowk_headew(skb);
	packet = (stwuct batadv_unicast_packet *)paywoad;
	if (packet->packet_type != BATADV_UNICAST)
		goto out;

	/* Find existing nc_path ow cweate a new */
	nc_path = batadv_nc_get_path(bat_pwiv,
				     bat_pwiv->nc.decoding_hash,
				     ethhdw->h_souwce,
				     ethhdw->h_dest);

	if (!nc_path)
		goto out;

	/* Cwone skb and adjust skb->data to point at batman headew */
	skb = skb_cwone(skb, GFP_ATOMIC);
	if (unwikewy(!skb))
		goto fwee_nc_path;

	if (unwikewy(!pskb_may_puww(skb, ETH_HWEN)))
		goto fwee_skb;

	if (unwikewy(!skb_puww_wcsum(skb, ETH_HWEN)))
		goto fwee_skb;

	/* Add skb to nc_path */
	packet_id = batadv_skb_cwc32(skb, paywoad + sizeof(*packet));
	if (!batadv_nc_skb_add_to_path(skb, nc_path, NUWW, packet_id))
		goto fwee_skb;

	batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_BUFFEW);
	wetuwn;

fwee_skb:
	kfwee_skb(skb);
fwee_nc_path:
	batadv_nc_path_put(nc_path);
out:
	wetuwn;
}

/**
 * batadv_nc_skb_stowe_sniffed_unicast() - check if a weceived unicast packet
 *  shouwd be saved in the decoding buffew and, if so, stowe it thewe
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: unicast skb to stowe
 */
void batadv_nc_skb_stowe_sniffed_unicast(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb)
{
	stwuct ethhdw *ethhdw = eth_hdw(skb);

	if (batadv_is_my_mac(bat_pwiv, ethhdw->h_dest))
		wetuwn;

	/* Set data pointew to MAC headew to mimic packets fwom ouw tx path */
	skb_push(skb, ETH_HWEN);

	batadv_nc_skb_stowe_fow_decoding(bat_pwiv, skb);
}

/**
 * batadv_nc_skb_decode_packet() - decode given skb using the decode data stowed
 *  in nc_packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: unicast skb to decode
 * @nc_packet: decode data needed to decode the skb
 *
 * Wetuwn: pointew to decoded unicast packet if the packet was decoded ow NUWW
 * in case of an ewwow.
 */
static stwuct batadv_unicast_packet *
batadv_nc_skb_decode_packet(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			    stwuct batadv_nc_packet *nc_packet)
{
	const int h_size = sizeof(stwuct batadv_unicast_packet);
	const int h_diff = sizeof(stwuct batadv_coded_packet) - h_size;
	stwuct batadv_unicast_packet *unicast_packet;
	stwuct batadv_coded_packet coded_packet_tmp;
	stwuct ethhdw *ethhdw, ethhdw_tmp;
	u8 *owig_dest, ttw, ttvn;
	unsigned int coding_wen;
	int eww;

	/* Save headews tempowawiwy */
	memcpy(&coded_packet_tmp, skb->data, sizeof(coded_packet_tmp));
	memcpy(&ethhdw_tmp, skb_mac_headew(skb), sizeof(ethhdw_tmp));

	if (skb_cow(skb, 0) < 0)
		wetuwn NUWW;

	if (unwikewy(!skb_puww_wcsum(skb, h_diff)))
		wetuwn NUWW;

	/* Data points to batman headew, so set mac headew 14 bytes befowe
	 * and netwowk to data
	 */
	skb_set_mac_headew(skb, -ETH_HWEN);
	skb_weset_netwowk_headew(skb);

	/* Weconstwuct owiginaw mac headew */
	ethhdw = eth_hdw(skb);
	*ethhdw = ethhdw_tmp;

	/* Sewect the cowwect unicast headew infowmation based on the wocation
	 * of ouw mac addwess in the coded_packet headew
	 */
	if (batadv_is_my_mac(bat_pwiv, coded_packet_tmp.second_dest)) {
		/* If we awe the second destination the packet was ovewheawd,
		 * so the Ethewnet addwess must be copied to h_dest and
		 * pkt_type changed fwom PACKET_OTHEWHOST to PACKET_HOST
		 */
		ethew_addw_copy(ethhdw->h_dest, coded_packet_tmp.second_dest);
		skb->pkt_type = PACKET_HOST;

		owig_dest = coded_packet_tmp.second_owig_dest;
		ttw = coded_packet_tmp.second_ttw;
		ttvn = coded_packet_tmp.second_ttvn;
	} ewse {
		owig_dest = coded_packet_tmp.fiwst_owig_dest;
		ttw = coded_packet_tmp.ttw;
		ttvn = coded_packet_tmp.fiwst_ttvn;
	}

	coding_wen = ntohs(coded_packet_tmp.coded_wen);

	if (coding_wen > skb->wen)
		wetuwn NUWW;

	/* Hewe the magic is wevewsed:
	 *   extwact the missing packet fwom the weceived coded packet
	 */
	batadv_nc_memxow(skb->data + h_size,
			 nc_packet->skb->data + h_size,
			 coding_wen);

	/* Wesize decoded skb if decoded with wawgew packet */
	if (nc_packet->skb->wen > coding_wen + h_size) {
		eww = pskb_twim_wcsum(skb, coding_wen + h_size);
		if (eww)
			wetuwn NUWW;
	}

	/* Cweate decoded unicast packet */
	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;
	unicast_packet->packet_type = BATADV_UNICAST;
	unicast_packet->vewsion = BATADV_COMPAT_VEWSION;
	unicast_packet->ttw = ttw;
	ethew_addw_copy(unicast_packet->dest, owig_dest);
	unicast_packet->ttvn = ttvn;

	batadv_nc_packet_fwee(nc_packet, fawse);
	wetuwn unicast_packet;
}

/**
 * batadv_nc_find_decoding_packet() - seawch thwough buffewed decoding data to
 *  find the data needed to decode the coded packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ethhdw: pointew to the ethewnet headew inside the coded packet
 * @coded: coded packet we twy to find decode data fow
 *
 * Wetuwn: pointew to nc packet if the needed data was found ow NUWW othewwise.
 */
static stwuct batadv_nc_packet *
batadv_nc_find_decoding_packet(stwuct batadv_pwiv *bat_pwiv,
			       stwuct ethhdw *ethhdw,
			       stwuct batadv_coded_packet *coded)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->nc.decoding_hash;
	stwuct batadv_nc_packet *tmp_nc_packet, *nc_packet = NUWW;
	stwuct batadv_nc_path *nc_path, nc_path_key;
	u8 *dest, *souwce;
	__be32 packet_id;
	int index;

	if (!hash)
		wetuwn NUWW;

	/* Sewect the cowwect packet id based on the wocation of ouw mac-addw */
	dest = ethhdw->h_souwce;
	if (!batadv_is_my_mac(bat_pwiv, coded->second_dest)) {
		souwce = coded->second_souwce;
		packet_id = coded->second_cwc;
	} ewse {
		souwce = coded->fiwst_souwce;
		packet_id = coded->fiwst_cwc;
	}

	batadv_nc_hash_key_gen(&nc_path_key, souwce, dest);
	index = batadv_nc_hash_choose(&nc_path_key, hash->size);

	/* Seawch fow matching coding path */
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(nc_path, &hash->tabwe[index], hash_entwy) {
		/* Find matching nc_packet */
		spin_wock_bh(&nc_path->packet_wist_wock);
		wist_fow_each_entwy(tmp_nc_packet,
				    &nc_path->packet_wist, wist) {
			if (packet_id == tmp_nc_packet->packet_id) {
				wist_dew(&tmp_nc_packet->wist);

				nc_packet = tmp_nc_packet;
				bweak;
			}
		}
		spin_unwock_bh(&nc_path->packet_wist_wock);

		if (nc_packet)
			bweak;
	}
	wcu_wead_unwock();

	if (!nc_packet)
		batadv_dbg(BATADV_DBG_NC, bat_pwiv,
			   "No decoding packet found fow %u\n", packet_id);

	wetuwn nc_packet;
}

/**
 * batadv_nc_wecv_coded_packet() - twy to decode coded packet and enqueue the
 *  wesuwting unicast packet
 * @skb: incoming coded packet
 * @wecv_if: pointew to intewface this packet was weceived on
 *
 * Wetuwn: NET_WX_SUCCESS if the packet has been consumed ow NET_WX_DWOP
 * othewwise.
 */
static int batadv_nc_wecv_coded_packet(stwuct sk_buff *skb,
				       stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_unicast_packet *unicast_packet;
	stwuct batadv_coded_packet *coded_packet;
	stwuct batadv_nc_packet *nc_packet;
	stwuct ethhdw *ethhdw;
	int hdw_size = sizeof(*coded_packet);

	/* Check if netwowk coding is enabwed */
	if (!atomic_wead(&bat_pwiv->netwowk_coding))
		goto fwee_skb;

	/* Make suwe we can access (and wemove) headew */
	if (unwikewy(!pskb_may_puww(skb, hdw_size)))
		goto fwee_skb;

	coded_packet = (stwuct batadv_coded_packet *)skb->data;
	ethhdw = eth_hdw(skb);

	/* Vewify fwame is destined fow us */
	if (!batadv_is_my_mac(bat_pwiv, ethhdw->h_dest) &&
	    !batadv_is_my_mac(bat_pwiv, coded_packet->second_dest))
		goto fwee_skb;

	/* Update stat countew */
	if (batadv_is_my_mac(bat_pwiv, coded_packet->second_dest))
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_SNIFFED);

	nc_packet = batadv_nc_find_decoding_packet(bat_pwiv, ethhdw,
						   coded_packet);
	if (!nc_packet) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_DECODE_FAIWED);
		goto fwee_skb;
	}

	/* Make skb's wineaw, because decoding accesses the entiwe buffew */
	if (skb_wineawize(skb) < 0)
		goto fwee_nc_packet;

	if (skb_wineawize(nc_packet->skb) < 0)
		goto fwee_nc_packet;

	/* Decode the packet */
	unicast_packet = batadv_nc_skb_decode_packet(bat_pwiv, skb, nc_packet);
	if (!unicast_packet) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_DECODE_FAIWED);
		goto fwee_nc_packet;
	}

	/* Mawk packet as decoded to do cowwect wecoding when fowwawding */
	BATADV_SKB_CB(skb)->decoded = twue;
	batadv_inc_countew(bat_pwiv, BATADV_CNT_NC_DECODE);
	batadv_add_countew(bat_pwiv, BATADV_CNT_NC_DECODE_BYTES,
			   skb->wen + ETH_HWEN);
	wetuwn batadv_wecv_unicast_packet(skb, wecv_if);

fwee_nc_packet:
	batadv_nc_packet_fwee(nc_packet, twue);
fwee_skb:
	kfwee_skb(skb);

	wetuwn NET_WX_DWOP;
}

/**
 * batadv_nc_mesh_fwee() - cwean up netwowk coding memowy
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_nc_mesh_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	batadv_tvwv_containew_unwegistew(bat_pwiv, BATADV_TVWV_NC, 1);
	batadv_tvwv_handwew_unwegistew(bat_pwiv, BATADV_TVWV_NC, 1);
	cancew_dewayed_wowk_sync(&bat_pwiv->nc.wowk);

	batadv_nc_puwge_paths(bat_pwiv, bat_pwiv->nc.coding_hash, NUWW);
	batadv_hash_destwoy(bat_pwiv->nc.coding_hash);
	batadv_nc_puwge_paths(bat_pwiv, bat_pwiv->nc.decoding_hash, NUWW);
	batadv_hash_destwoy(bat_pwiv->nc.decoding_hash);
}
