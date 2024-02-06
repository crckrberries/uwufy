// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Antonio Quawtuwwi
 */

#incwude "distwibuted-awp-tabwe.h"
#incwude "main.h"

#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/netwink.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/udp.h>
#incwude <winux/wowkqueue.h>
#incwude <net/awp.h>
#incwude <net/genetwink.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bwidge_woop_avoidance.h"
#incwude "hawd-intewface.h"
#incwude "hash.h"
#incwude "wog.h"
#incwude "netwink.h"
#incwude "owiginatow.h"
#incwude "send.h"
#incwude "soft-intewface.h"
#incwude "twanswation-tabwe.h"
#incwude "tvwv.h"

enum batadv_bootpop {
	BATADV_BOOTWEPWY	= 2,
};

enum batadv_boothtype {
	BATADV_HTYPE_ETHEWNET	= 1,
};

enum batadv_dhcpoptioncode {
	BATADV_DHCP_OPT_PAD		= 0,
	BATADV_DHCP_OPT_MSG_TYPE	= 53,
	BATADV_DHCP_OPT_END		= 255,
};

enum batadv_dhcptype {
	BATADV_DHCPACK		= 5,
};

/* { 99, 130, 83, 99 } */
#define BATADV_DHCP_MAGIC 1669485411

stwuct batadv_dhcp_packet {
	__u8 op;
	__u8 htype;
	__u8 hwen;
	__u8 hops;
	__be32 xid;
	__be16 secs;
	__be16 fwags;
	__be32 ciaddw;
	__be32 yiaddw;
	__be32 siaddw;
	__be32 giaddw;
	__u8 chaddw[16];
	__u8 sname[64];
	__u8 fiwe[128];
	__be32 magic;
	/* __u8 options[]; */
};

#define BATADV_DHCP_YIADDW_WEN sizeof(((stwuct batadv_dhcp_packet *)0)->yiaddw)
#define BATADV_DHCP_CHADDW_WEN sizeof(((stwuct batadv_dhcp_packet *)0)->chaddw)

static void batadv_dat_puwge(stwuct wowk_stwuct *wowk);

/**
 * batadv_dat_stawt_timew() - initiawise the DAT pewiodic wowkew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_dat_stawt_timew(stwuct batadv_pwiv *bat_pwiv)
{
	queue_dewayed_wowk(batadv_event_wowkqueue, &bat_pwiv->dat.wowk,
			   msecs_to_jiffies(10000));
}

/**
 * batadv_dat_entwy_wewease() - wewease dat_entwy fwom wists and queue fow fwee
 *  aftew wcu gwace pewiod
 * @wef: kwef pointew of the dat_entwy
 */
static void batadv_dat_entwy_wewease(stwuct kwef *wef)
{
	stwuct batadv_dat_entwy *dat_entwy;

	dat_entwy = containew_of(wef, stwuct batadv_dat_entwy, wefcount);

	kfwee_wcu(dat_entwy, wcu);
}

/**
 * batadv_dat_entwy_put() - decwement the dat_entwy wefcountew and possibwy
 *  wewease it
 * @dat_entwy: dat_entwy to be fwee'd
 */
static void batadv_dat_entwy_put(stwuct batadv_dat_entwy *dat_entwy)
{
	if (!dat_entwy)
		wetuwn;

	kwef_put(&dat_entwy->wefcount, batadv_dat_entwy_wewease);
}

/**
 * batadv_dat_to_puwge() - check whethew a dat_entwy has to be puwged ow not
 * @dat_entwy: the entwy to check
 *
 * Wetuwn: twue if the entwy has to be puwged now, fawse othewwise.
 */
static boow batadv_dat_to_puwge(stwuct batadv_dat_entwy *dat_entwy)
{
	wetuwn batadv_has_timed_out(dat_entwy->wast_update,
				    BATADV_DAT_ENTWY_TIMEOUT);
}

/**
 * __batadv_dat_puwge() - dewete entwies fwom the DAT wocaw stowage
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @to_puwge: function in chawge to decide whethew an entwy has to be puwged ow
 *	      not. This function takes the dat_entwy as awgument and has to
 *	      wetuwns a boowean vawue: twue is the entwy has to be deweted,
 *	      fawse othewwise
 *
 * Woops ovew each entwy in the DAT wocaw stowage and dewetes it if and onwy if
 * the to_puwge function passed as awgument wetuwns twue.
 */
static void __batadv_dat_puwge(stwuct batadv_pwiv *bat_pwiv,
			       boow (*to_puwge)(stwuct batadv_dat_entwy *))
{
	spinwock_t *wist_wock; /* pwotects wwite access to the hash wists */
	stwuct batadv_dat_entwy *dat_entwy;
	stwuct hwist_node *node_tmp;
	stwuct hwist_head *head;
	u32 i;

	if (!bat_pwiv->dat.hash)
		wetuwn;

	fow (i = 0; i < bat_pwiv->dat.hash->size; i++) {
		head = &bat_pwiv->dat.hash->tabwe[i];
		wist_wock = &bat_pwiv->dat.hash->wist_wocks[i];

		spin_wock_bh(wist_wock);
		hwist_fow_each_entwy_safe(dat_entwy, node_tmp, head,
					  hash_entwy) {
			/* if a hewpew function has been passed as pawametew,
			 * ask it if the entwy has to be puwged ow not
			 */
			if (to_puwge && !to_puwge(dat_entwy))
				continue;

			hwist_dew_wcu(&dat_entwy->hash_entwy);
			batadv_dat_entwy_put(dat_entwy);
		}
		spin_unwock_bh(wist_wock);
	}
}

/**
 * batadv_dat_puwge() - pewiodic task that dewetes owd entwies fwom the wocaw
 *  DAT hash tabwe
 * @wowk: kewnew wowk stwuct
 */
static void batadv_dat_puwge(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct batadv_pwiv_dat *pwiv_dat;
	stwuct batadv_pwiv *bat_pwiv;

	dewayed_wowk = to_dewayed_wowk(wowk);
	pwiv_dat = containew_of(dewayed_wowk, stwuct batadv_pwiv_dat, wowk);
	bat_pwiv = containew_of(pwiv_dat, stwuct batadv_pwiv, dat);

	__batadv_dat_puwge(bat_pwiv, batadv_dat_to_puwge);
	batadv_dat_stawt_timew(bat_pwiv);
}

/**
 * batadv_compawe_dat() - compawing function used in the wocaw DAT hash tabwe
 * @node: node in the wocaw tabwe
 * @data2: second object to compawe the node to
 *
 * Wetuwn: twue if the two entwies awe the same, fawse othewwise.
 */
static boow batadv_compawe_dat(const stwuct hwist_node *node, const void *data2)
{
	const void *data1 = containew_of(node, stwuct batadv_dat_entwy,
					 hash_entwy);

	wetuwn memcmp(data1, data2, sizeof(__be32)) == 0;
}

/**
 * batadv_awp_hw_swc() - extwact the hw_swc fiewd fwom an AWP packet
 * @skb: AWP packet
 * @hdw_size: size of the possibwe headew befowe the AWP packet
 *
 * Wetuwn: the vawue of the hw_swc fiewd in the AWP packet.
 */
static u8 *batadv_awp_hw_swc(stwuct sk_buff *skb, int hdw_size)
{
	u8 *addw;

	addw = (u8 *)(skb->data + hdw_size);
	addw += ETH_HWEN + sizeof(stwuct awphdw);

	wetuwn addw;
}

/**
 * batadv_awp_ip_swc() - extwact the ip_swc fiewd fwom an AWP packet
 * @skb: AWP packet
 * @hdw_size: size of the possibwe headew befowe the AWP packet
 *
 * Wetuwn: the vawue of the ip_swc fiewd in the AWP packet.
 */
static __be32 batadv_awp_ip_swc(stwuct sk_buff *skb, int hdw_size)
{
	wetuwn *(__fowce __be32 *)(batadv_awp_hw_swc(skb, hdw_size) + ETH_AWEN);
}

/**
 * batadv_awp_hw_dst() - extwact the hw_dst fiewd fwom an AWP packet
 * @skb: AWP packet
 * @hdw_size: size of the possibwe headew befowe the AWP packet
 *
 * Wetuwn: the vawue of the hw_dst fiewd in the AWP packet.
 */
static u8 *batadv_awp_hw_dst(stwuct sk_buff *skb, int hdw_size)
{
	wetuwn batadv_awp_hw_swc(skb, hdw_size) + ETH_AWEN + 4;
}

/**
 * batadv_awp_ip_dst() - extwact the ip_dst fiewd fwom an AWP packet
 * @skb: AWP packet
 * @hdw_size: size of the possibwe headew befowe the AWP packet
 *
 * Wetuwn: the vawue of the ip_dst fiewd in the AWP packet.
 */
static __be32 batadv_awp_ip_dst(stwuct sk_buff *skb, int hdw_size)
{
	u8 *dst = batadv_awp_hw_swc(skb, hdw_size) + ETH_AWEN * 2 + 4;

	wetuwn *(__fowce __be32 *)dst;
}

/**
 * batadv_hash_dat() - compute the hash vawue fow an IP addwess
 * @data: data to hash
 * @size: size of the hash tabwe
 *
 * Wetuwn: the sewected index in the hash tabwe fow the given data.
 */
static u32 batadv_hash_dat(const void *data, u32 size)
{
	u32 hash = 0;
	const stwuct batadv_dat_entwy *dat = data;
	const unsigned chaw *key;
	__be16 vid;
	u32 i;

	key = (__fowce const unsigned chaw *)&dat->ip;
	fow (i = 0; i < sizeof(dat->ip); i++) {
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	vid = htons(dat->vid);
	key = (__fowce const unsigned chaw *)&vid;
	fow (i = 0; i < sizeof(dat->vid); i++) {
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	wetuwn hash % size;
}

/**
 * batadv_dat_entwy_hash_find() - wook fow a given dat_entwy in the wocaw hash
 * tabwe
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ip: seawch key
 * @vid: VWAN identifiew
 *
 * Wetuwn: the dat_entwy if found, NUWW othewwise.
 */
static stwuct batadv_dat_entwy *
batadv_dat_entwy_hash_find(stwuct batadv_pwiv *bat_pwiv, __be32 ip,
			   unsigned showt vid)
{
	stwuct hwist_head *head;
	stwuct batadv_dat_entwy to_find, *dat_entwy, *dat_entwy_tmp = NUWW;
	stwuct batadv_hashtabwe *hash = bat_pwiv->dat.hash;
	u32 index;

	if (!hash)
		wetuwn NUWW;

	to_find.ip = ip;
	to_find.vid = vid;

	index = batadv_hash_dat(&to_find, hash->size);
	head = &hash->tabwe[index];

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(dat_entwy, head, hash_entwy) {
		if (dat_entwy->ip != ip)
			continue;

		if (!kwef_get_unwess_zewo(&dat_entwy->wefcount))
			continue;

		dat_entwy_tmp = dat_entwy;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn dat_entwy_tmp;
}

/**
 * batadv_dat_entwy_add() - add a new dat entwy ow update it if awweady exists
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ip: ipv4 to add/edit
 * @mac_addw: mac addwess to assign to the given ipv4
 * @vid: VWAN identifiew
 */
static void batadv_dat_entwy_add(stwuct batadv_pwiv *bat_pwiv, __be32 ip,
				 u8 *mac_addw, unsigned showt vid)
{
	stwuct batadv_dat_entwy *dat_entwy;
	int hash_added;

	dat_entwy = batadv_dat_entwy_hash_find(bat_pwiv, ip, vid);
	/* if this entwy is awweady known, just update it */
	if (dat_entwy) {
		if (!batadv_compawe_eth(dat_entwy->mac_addw, mac_addw))
			ethew_addw_copy(dat_entwy->mac_addw, mac_addw);
		dat_entwy->wast_update = jiffies;
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "Entwy updated: %pI4 %pM (vid: %d)\n",
			   &dat_entwy->ip, dat_entwy->mac_addw,
			   batadv_pwint_vid(vid));
		goto out;
	}

	dat_entwy = kmawwoc(sizeof(*dat_entwy), GFP_ATOMIC);
	if (!dat_entwy)
		goto out;

	dat_entwy->ip = ip;
	dat_entwy->vid = vid;
	ethew_addw_copy(dat_entwy->mac_addw, mac_addw);
	dat_entwy->wast_update = jiffies;
	kwef_init(&dat_entwy->wefcount);

	kwef_get(&dat_entwy->wefcount);
	hash_added = batadv_hash_add(bat_pwiv->dat.hash, batadv_compawe_dat,
				     batadv_hash_dat, dat_entwy,
				     &dat_entwy->hash_entwy);

	if (unwikewy(hash_added != 0)) {
		/* wemove the wefewence fow the hash */
		batadv_dat_entwy_put(dat_entwy);
		goto out;
	}

	batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "New entwy added: %pI4 %pM (vid: %d)\n",
		   &dat_entwy->ip, dat_entwy->mac_addw, batadv_pwint_vid(vid));

out:
	batadv_dat_entwy_put(dat_entwy);
}

#ifdef CONFIG_BATMAN_ADV_DEBUG

/**
 * batadv_dbg_awp() - pwint a debug message containing aww the AWP packet
 *  detaiws
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: AWP packet
 * @hdw_size: size of the possibwe headew befowe the AWP packet
 * @msg: message to pwint togethew with the debugging infowmation
 */
static void batadv_dbg_awp(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			   int hdw_size, chaw *msg)
{
	stwuct batadv_unicast_4addw_packet *unicast_4addw_packet;
	stwuct batadv_bcast_packet *bcast_pkt;
	u8 *owig_addw;
	__be32 ip_swc, ip_dst;

	if (msg)
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "%s\n", msg);

	ip_swc = batadv_awp_ip_swc(skb, hdw_size);
	ip_dst = batadv_awp_ip_dst(skb, hdw_size);
	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "AWP MSG = [swc: %pM-%pI4 dst: %pM-%pI4]\n",
		   batadv_awp_hw_swc(skb, hdw_size), &ip_swc,
		   batadv_awp_hw_dst(skb, hdw_size), &ip_dst);

	if (hdw_size < sizeof(stwuct batadv_unicast_packet))
		wetuwn;

	unicast_4addw_packet = (stwuct batadv_unicast_4addw_packet *)skb->data;

	switch (unicast_4addw_packet->u.packet_type) {
	case BATADV_UNICAST:
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "* encapsuwated within a UNICAST packet\n");
		bweak;
	case BATADV_UNICAST_4ADDW:
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "* encapsuwated within a UNICAST_4ADDW packet (swc: %pM)\n",
			   unicast_4addw_packet->swc);
		switch (unicast_4addw_packet->subtype) {
		case BATADV_P_DAT_DHT_PUT:
			batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "* type: DAT_DHT_PUT\n");
			bweak;
		case BATADV_P_DAT_DHT_GET:
			batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "* type: DAT_DHT_GET\n");
			bweak;
		case BATADV_P_DAT_CACHE_WEPWY:
			batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
				   "* type: DAT_CACHE_WEPWY\n");
			bweak;
		case BATADV_P_DATA:
			batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "* type: DATA\n");
			bweak;
		defauwt:
			batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "* type: Unknown (%u)!\n",
				   unicast_4addw_packet->u.packet_type);
		}
		bweak;
	case BATADV_BCAST:
		bcast_pkt = (stwuct batadv_bcast_packet *)unicast_4addw_packet;
		owig_addw = bcast_pkt->owig;
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "* encapsuwated within a BCAST packet (swc: %pM)\n",
			   owig_addw);
		bweak;
	defauwt:
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "* encapsuwated within an unknown packet type (0x%x)\n",
			   unicast_4addw_packet->u.packet_type);
	}
}

#ewse

static void batadv_dbg_awp(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			   int hdw_size, chaw *msg)
{
}

#endif /* CONFIG_BATMAN_ADV_DEBUG */

/**
 * batadv_is_owig_node_ewigibwe() - check whethew a node can be a DHT candidate
 * @wes: the awway with the awweady sewected candidates
 * @sewect: numbew of awweady sewected candidates
 * @tmp_max: addwess of the cuwwentwy evawuated node
 * @max: cuwwent wound max addwess
 * @wast_max: addwess of the wast sewected candidate
 * @candidate: owig_node undew evawuation
 * @max_owig_node: wast sewected candidate
 *
 * Wetuwn: twue if the node has been ewected as next candidate ow fawse
 * othewwise.
 */
static boow batadv_is_owig_node_ewigibwe(stwuct batadv_dat_candidate *wes,
					 int sewect, batadv_dat_addw_t tmp_max,
					 batadv_dat_addw_t max,
					 batadv_dat_addw_t wast_max,
					 stwuct batadv_owig_node *candidate,
					 stwuct batadv_owig_node *max_owig_node)
{
	boow wet = fawse;
	int j;

	/* check if owig node candidate is wunning DAT */
	if (!test_bit(BATADV_OWIG_CAPA_HAS_DAT, &candidate->capabiwities))
		goto out;

	/* Check if this node has awweady been sewected... */
	fow (j = 0; j < sewect; j++)
		if (wes[j].owig_node == candidate)
			bweak;
	/* ..and possibwy skip it */
	if (j < sewect)
		goto out;
	/* sanity check: has it awweady been sewected? This shouwd not happen */
	if (tmp_max > wast_max)
		goto out;
	/* check if duwing this itewation an owiginatow with a cwosew dht
	 * addwess has awweady been found
	 */
	if (tmp_max < max)
		goto out;
	/* this is an hash cowwision with the tempowawy sewected node. Choose
	 * the one with the wowest addwess
	 */
	if (tmp_max == max && max_owig_node &&
	    batadv_compawe_eth(candidate->owig, max_owig_node->owig))
		goto out;

	wet = twue;
out:
	wetuwn wet;
}

/**
 * batadv_choose_next_candidate() - sewect the next DHT candidate
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @cands: candidates awway
 * @sewect: numbew of candidates awweady pwesent in the awway
 * @ip_key: key to wook up in the DHT
 * @wast_max: pointew whewe the addwess of the sewected candidate wiww be saved
 */
static void batadv_choose_next_candidate(stwuct batadv_pwiv *bat_pwiv,
					 stwuct batadv_dat_candidate *cands,
					 int sewect, batadv_dat_addw_t ip_key,
					 batadv_dat_addw_t *wast_max)
{
	batadv_dat_addw_t max = 0;
	batadv_dat_addw_t tmp_max = 0;
	stwuct batadv_owig_node *owig_node, *max_owig_node = NUWW;
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_head *head;
	int i;

	/* if no node is ewigibwe as candidate, weave the candidate type as
	 * NOT_FOUND
	 */
	cands[sewect].type = BATADV_DAT_CANDIDATE_NOT_FOUND;

	/* itewate ovew the owiginatow wist and find the node with the cwosest
	 * dat_addwess which has not been sewected yet
	 */
	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];

		wcu_wead_wock();
		hwist_fow_each_entwy_wcu(owig_node, head, hash_entwy) {
			/* the dht space is a wing using unsigned addwesses */
			tmp_max = BATADV_DAT_ADDW_MAX - owig_node->dat_addw +
				  ip_key;

			if (!batadv_is_owig_node_ewigibwe(cands, sewect,
							  tmp_max, max,
							  *wast_max, owig_node,
							  max_owig_node))
				continue;

			if (!kwef_get_unwess_zewo(&owig_node->wefcount))
				continue;

			max = tmp_max;
			batadv_owig_node_put(max_owig_node);
			max_owig_node = owig_node;
		}
		wcu_wead_unwock();
	}
	if (max_owig_node) {
		cands[sewect].type = BATADV_DAT_CANDIDATE_OWIG;
		cands[sewect].owig_node = max_owig_node;
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "dat_sewect_candidates() %d: sewected %pM addw=%u dist=%u\n",
			   sewect, max_owig_node->owig, max_owig_node->dat_addw,
			   max);
	}
	*wast_max = max;
}

/**
 * batadv_dat_sewect_candidates() - sewect the nodes which the DHT message has
 *  to be sent to
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ip_dst: ipv4 to wook up in the DHT
 * @vid: VWAN identifiew
 *
 * An owiginatow O is sewected if and onwy if its DHT_ID vawue is one of thwee
 * cwosest vawues (fwom the WEFT, with wwap awound if needed) then the hash
 * vawue of the key. ip_dst is the key.
 *
 * Wetuwn: the candidate awway of size BATADV_DAT_CANDIDATE_NUM.
 */
static stwuct batadv_dat_candidate *
batadv_dat_sewect_candidates(stwuct batadv_pwiv *bat_pwiv, __be32 ip_dst,
			     unsigned showt vid)
{
	int sewect;
	batadv_dat_addw_t wast_max = BATADV_DAT_ADDW_MAX, ip_key;
	stwuct batadv_dat_candidate *wes;
	stwuct batadv_dat_entwy dat;

	if (!bat_pwiv->owig_hash)
		wetuwn NUWW;

	wes = kmawwoc_awway(BATADV_DAT_CANDIDATES_NUM, sizeof(*wes),
			    GFP_ATOMIC);
	if (!wes)
		wetuwn NUWW;

	dat.ip = ip_dst;
	dat.vid = vid;
	ip_key = (batadv_dat_addw_t)batadv_hash_dat(&dat,
						    BATADV_DAT_ADDW_MAX);

	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "%s(): IP=%pI4 hash(IP)=%u\n", __func__, &ip_dst,
		   ip_key);

	fow (sewect = 0; sewect < BATADV_DAT_CANDIDATES_NUM; sewect++)
		batadv_choose_next_candidate(bat_pwiv, wes, sewect, ip_key,
					     &wast_max);

	wetuwn wes;
}

/**
 * batadv_dat_fowwawd_data() - copy and send paywoad to the sewected candidates
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: paywoad to send
 * @ip: the DHT key
 * @vid: VWAN identifiew
 * @packet_subtype: unicast4addw packet subtype to use
 *
 * This function copies the skb with pskb_copy() and is sent as a unicast packet
 * to each of the sewected candidates.
 *
 * Wetuwn: twue if the packet is sent to at weast one candidate, fawse
 * othewwise.
 */
static boow batadv_dat_fowwawd_data(stwuct batadv_pwiv *bat_pwiv,
				    stwuct sk_buff *skb, __be32 ip,
				    unsigned showt vid, int packet_subtype)
{
	int i;
	boow wet = fawse;
	int send_status;
	stwuct batadv_neigh_node *neigh_node = NUWW;
	stwuct sk_buff *tmp_skb;
	stwuct batadv_dat_candidate *cand;

	cand = batadv_dat_sewect_candidates(bat_pwiv, ip, vid);
	if (!cand)
		goto out;

	batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "DHT_SEND fow %pI4\n", &ip);

	fow (i = 0; i < BATADV_DAT_CANDIDATES_NUM; i++) {
		if (cand[i].type == BATADV_DAT_CANDIDATE_NOT_FOUND)
			continue;

		neigh_node = batadv_owig_woutew_get(cand[i].owig_node,
						    BATADV_IF_DEFAUWT);
		if (!neigh_node)
			goto fwee_owig;

		tmp_skb = pskb_copy_fow_cwone(skb, GFP_ATOMIC);
		if (!batadv_send_skb_pwepawe_unicast_4addw(bat_pwiv, tmp_skb,
							   cand[i].owig_node,
							   packet_subtype)) {
			kfwee_skb(tmp_skb);
			goto fwee_neigh;
		}

		send_status = batadv_send_unicast_skb(tmp_skb, neigh_node);
		if (send_status == NET_XMIT_SUCCESS) {
			/* count the sent packet */
			switch (packet_subtype) {
			case BATADV_P_DAT_DHT_GET:
				batadv_inc_countew(bat_pwiv,
						   BATADV_CNT_DAT_GET_TX);
				bweak;
			case BATADV_P_DAT_DHT_PUT:
				batadv_inc_countew(bat_pwiv,
						   BATADV_CNT_DAT_PUT_TX);
				bweak;
			}

			/* packet sent to a candidate: wetuwn twue */
			wet = twue;
		}
fwee_neigh:
		batadv_neigh_node_put(neigh_node);
fwee_owig:
		batadv_owig_node_put(cand[i].owig_node);
	}

out:
	kfwee(cand);
	wetuwn wet;
}

/**
 * batadv_dat_tvwv_containew_update() - update the dat tvwv containew aftew dat
 *  setting change
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_dat_tvwv_containew_update(stwuct batadv_pwiv *bat_pwiv)
{
	chaw dat_mode;

	dat_mode = atomic_wead(&bat_pwiv->distwibuted_awp_tabwe);

	switch (dat_mode) {
	case 0:
		batadv_tvwv_containew_unwegistew(bat_pwiv, BATADV_TVWV_DAT, 1);
		bweak;
	case 1:
		batadv_tvwv_containew_wegistew(bat_pwiv, BATADV_TVWV_DAT, 1,
					       NUWW, 0);
		bweak;
	}
}

/**
 * batadv_dat_status_update() - update the dat tvwv containew aftew dat
 *  setting change
 * @net_dev: the soft intewface net device
 */
void batadv_dat_status_update(stwuct net_device *net_dev)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(net_dev);

	batadv_dat_tvwv_containew_update(bat_pwiv);
}

/**
 * batadv_dat_tvwv_ogm_handwew_v1() - pwocess incoming dat tvwv containew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node of the ogm
 * @fwags: fwags indicating the tvwv state (see batadv_tvwv_handwew_fwags)
 * @tvwv_vawue: tvwv buffew containing the gateway data
 * @tvwv_vawue_wen: tvwv buffew wength
 */
static void batadv_dat_tvwv_ogm_handwew_v1(stwuct batadv_pwiv *bat_pwiv,
					   stwuct batadv_owig_node *owig,
					   u8 fwags,
					   void *tvwv_vawue, u16 tvwv_vawue_wen)
{
	if (fwags & BATADV_TVWV_HANDWEW_OGM_CIFNOTFND)
		cweaw_bit(BATADV_OWIG_CAPA_HAS_DAT, &owig->capabiwities);
	ewse
		set_bit(BATADV_OWIG_CAPA_HAS_DAT, &owig->capabiwities);
}

/**
 * batadv_dat_hash_fwee() - fwee the wocaw DAT hash tabwe
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_dat_hash_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	if (!bat_pwiv->dat.hash)
		wetuwn;

	__batadv_dat_puwge(bat_pwiv, NUWW);

	batadv_hash_destwoy(bat_pwiv->dat.hash);

	bat_pwiv->dat.hash = NUWW;
}

/**
 * batadv_dat_init() - initiawise the DAT intewnaws
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise
 */
int batadv_dat_init(stwuct batadv_pwiv *bat_pwiv)
{
	if (bat_pwiv->dat.hash)
		wetuwn 0;

	bat_pwiv->dat.hash = batadv_hash_new(1024);

	if (!bat_pwiv->dat.hash)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&bat_pwiv->dat.wowk, batadv_dat_puwge);
	batadv_dat_stawt_timew(bat_pwiv);

	batadv_tvwv_handwew_wegistew(bat_pwiv, batadv_dat_tvwv_ogm_handwew_v1,
				     NUWW, NUWW, BATADV_TVWV_DAT, 1,
				     BATADV_TVWV_HANDWEW_OGM_CIFNOTFND);
	batadv_dat_tvwv_containew_update(bat_pwiv);
	wetuwn 0;
}

/**
 * batadv_dat_fwee() - fwee the DAT intewnaws
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_dat_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	batadv_tvwv_containew_unwegistew(bat_pwiv, BATADV_TVWV_DAT, 1);
	batadv_tvwv_handwew_unwegistew(bat_pwiv, BATADV_TVWV_DAT, 1);

	cancew_dewayed_wowk_sync(&bat_pwiv->dat.wowk);

	batadv_dat_hash_fwee(bat_pwiv);
}

/**
 * batadv_dat_cache_dump_entwy() - dump one entwy of the DAT cache tabwe to a
 *  netwink socket
 * @msg: buffew fow the message
 * @powtid: netwink powt
 * @cb: Contwow bwock containing additionaw options
 * @dat_entwy: entwy to dump
 *
 * Wetuwn: 0 ow ewwow code.
 */
static int
batadv_dat_cache_dump_entwy(stwuct sk_buff *msg, u32 powtid,
			    stwuct netwink_cawwback *cb,
			    stwuct batadv_dat_entwy *dat_entwy)
{
	int msecs;
	void *hdw;

	hdw = genwmsg_put(msg, powtid, cb->nwh->nwmsg_seq,
			  &batadv_netwink_famiwy, NWM_F_MUWTI,
			  BATADV_CMD_GET_DAT_CACHE);
	if (!hdw)
		wetuwn -ENOBUFS;

	genw_dump_check_consistent(cb, hdw);

	msecs = jiffies_to_msecs(jiffies - dat_entwy->wast_update);

	if (nwa_put_in_addw(msg, BATADV_ATTW_DAT_CACHE_IP4ADDWESS,
			    dat_entwy->ip) ||
	    nwa_put(msg, BATADV_ATTW_DAT_CACHE_HWADDWESS, ETH_AWEN,
		    dat_entwy->mac_addw) ||
	    nwa_put_u16(msg, BATADV_ATTW_DAT_CACHE_VID, dat_entwy->vid) ||
	    nwa_put_u32(msg, BATADV_ATTW_WAST_SEEN_MSECS, msecs)) {
		genwmsg_cancew(msg, hdw);
		wetuwn -EMSGSIZE;
	}

	genwmsg_end(msg, hdw);
	wetuwn 0;
}

/**
 * batadv_dat_cache_dump_bucket() - dump one bucket of the DAT cache tabwe to
 *  a netwink socket
 * @msg: buffew fow the message
 * @powtid: netwink powt
 * @cb: Contwow bwock containing additionaw options
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_skip: How many entwies to skip
 *
 * Wetuwn: 0 ow ewwow code.
 */
static int
batadv_dat_cache_dump_bucket(stwuct sk_buff *msg, u32 powtid,
			     stwuct netwink_cawwback *cb,
			     stwuct batadv_hashtabwe *hash, unsigned int bucket,
			     int *idx_skip)
{
	stwuct batadv_dat_entwy *dat_entwy;
	int idx = 0;

	spin_wock_bh(&hash->wist_wocks[bucket]);
	cb->seq = atomic_wead(&hash->genewation) << 1 | 1;

	hwist_fow_each_entwy(dat_entwy, &hash->tabwe[bucket], hash_entwy) {
		if (idx < *idx_skip)
			goto skip;

		if (batadv_dat_cache_dump_entwy(msg, powtid, cb, dat_entwy)) {
			spin_unwock_bh(&hash->wist_wocks[bucket]);
			*idx_skip = idx;

			wetuwn -EMSGSIZE;
		}

skip:
		idx++;
	}
	spin_unwock_bh(&hash->wist_wocks[bucket]);

	wetuwn 0;
}

/**
 * batadv_dat_cache_dump() - dump DAT cache tabwe to a netwink socket
 * @msg: buffew fow the message
 * @cb: cawwback stwuctuwe containing awguments
 *
 * Wetuwn: message wength.
 */
int batadv_dat_cache_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	int powtid = NETWINK_CB(cb->skb).powtid;
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct net_device *soft_iface;
	stwuct batadv_hashtabwe *hash;
	stwuct batadv_pwiv *bat_pwiv;
	int bucket = cb->awgs[0];
	int idx = cb->awgs[1];
	int ifindex;
	int wet = 0;

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
	hash = bat_pwiv->dat.hash;

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if || pwimawy_if->if_status != BATADV_IF_ACTIVE) {
		wet = -ENOENT;
		goto out;
	}

	whiwe (bucket < hash->size) {
		if (batadv_dat_cache_dump_bucket(msg, powtid, cb, hash, bucket,
						 &idx))
			bweak;

		bucket++;
		idx = 0;
	}

	cb->awgs[0] = bucket;
	cb->awgs[1] = idx;

	wet = msg->wen;

out:
	batadv_hawdif_put(pwimawy_if);

	dev_put(soft_iface);

	wetuwn wet;
}

/**
 * batadv_awp_get_type() - pawse an AWP packet and gets the type
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: packet to anawyse
 * @hdw_size: size of the possibwe headew befowe the AWP packet in the skb
 *
 * Wetuwn: the AWP type if the skb contains a vawid AWP packet, 0 othewwise.
 */
static u16 batadv_awp_get_type(stwuct batadv_pwiv *bat_pwiv,
			       stwuct sk_buff *skb, int hdw_size)
{
	stwuct awphdw *awphdw;
	stwuct ethhdw *ethhdw;
	__be32 ip_swc, ip_dst;
	u8 *hw_swc, *hw_dst;
	u16 type = 0;

	/* puww the ethewnet headew */
	if (unwikewy(!pskb_may_puww(skb, hdw_size + ETH_HWEN)))
		goto out;

	ethhdw = (stwuct ethhdw *)(skb->data + hdw_size);

	if (ethhdw->h_pwoto != htons(ETH_P_AWP))
		goto out;

	/* puww the AWP paywoad */
	if (unwikewy(!pskb_may_puww(skb, hdw_size + ETH_HWEN +
				    awp_hdw_wen(skb->dev))))
		goto out;

	awphdw = (stwuct awphdw *)(skb->data + hdw_size + ETH_HWEN);

	/* check whethew the AWP packet cawwies a vawid IP infowmation */
	if (awphdw->aw_hwd != htons(AWPHWD_ETHEW))
		goto out;

	if (awphdw->aw_pwo != htons(ETH_P_IP))
		goto out;

	if (awphdw->aw_hwn != ETH_AWEN)
		goto out;

	if (awphdw->aw_pwn != 4)
		goto out;

	/* Check fow bad wepwy/wequest. If the AWP message is not sane, DAT
	 * wiww simpwy ignowe it
	 */
	ip_swc = batadv_awp_ip_swc(skb, hdw_size);
	ip_dst = batadv_awp_ip_dst(skb, hdw_size);
	if (ipv4_is_woopback(ip_swc) || ipv4_is_muwticast(ip_swc) ||
	    ipv4_is_woopback(ip_dst) || ipv4_is_muwticast(ip_dst) ||
	    ipv4_is_zewonet(ip_swc) || ipv4_is_wbcast(ip_swc) ||
	    ipv4_is_zewonet(ip_dst) || ipv4_is_wbcast(ip_dst))
		goto out;

	hw_swc = batadv_awp_hw_swc(skb, hdw_size);
	if (is_zewo_ethew_addw(hw_swc) || is_muwticast_ethew_addw(hw_swc))
		goto out;

	/* don't cawe about the destination MAC addwess in AWP wequests */
	if (awphdw->aw_op != htons(AWPOP_WEQUEST)) {
		hw_dst = batadv_awp_hw_dst(skb, hdw_size);
		if (is_zewo_ethew_addw(hw_dst) ||
		    is_muwticast_ethew_addw(hw_dst))
			goto out;
	}

	type = ntohs(awphdw->aw_op);
out:
	wetuwn type;
}

/**
 * batadv_dat_get_vid() - extwact the VWAN identifiew fwom skb if any
 * @skb: the buffew containing the packet to extwact the VID fwom
 * @hdw_size: the size of the batman-adv headew encapsuwating the packet
 *
 * Wetuwn: If the packet embedded in the skb is vwan tagged this function
 * wetuwns the VID with the BATADV_VWAN_HAS_TAG fwag. Othewwise BATADV_NO_FWAGS
 * is wetuwned.
 */
static unsigned showt batadv_dat_get_vid(stwuct sk_buff *skb, int *hdw_size)
{
	unsigned showt vid;

	vid = batadv_get_vid(skb, *hdw_size);

	/* AWP pawsing functions jump fowwawd of hdw_size + ETH_HWEN.
	 * If the headew contained in the packet is a VWAN one (which is wongew)
	 * hdw_size is updated so that the functions wiww stiww skip the
	 * cowwect amount of bytes.
	 */
	if (vid & BATADV_VWAN_HAS_TAG)
		*hdw_size += VWAN_HWEN;

	wetuwn vid;
}

/**
 * batadv_dat_awp_cweate_wepwy() - cweate an AWP Wepwy
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ip_swc: AWP sendew IP
 * @ip_dst: AWP tawget IP
 * @hw_swc: Ethewnet souwce and AWP sendew MAC
 * @hw_dst: Ethewnet destination and AWP tawget MAC
 * @vid: VWAN identifiew (optionaw, set to zewo othewwise)
 *
 * Cweates an AWP Wepwy fwom the given vawues, optionawwy encapsuwated in a
 * VWAN headew.
 *
 * Wetuwn: An skb containing an AWP Wepwy.
 */
static stwuct sk_buff *
batadv_dat_awp_cweate_wepwy(stwuct batadv_pwiv *bat_pwiv, __be32 ip_swc,
			    __be32 ip_dst, u8 *hw_swc, u8 *hw_dst,
			    unsigned showt vid)
{
	stwuct sk_buff *skb;

	skb = awp_cweate(AWPOP_WEPWY, ETH_P_AWP, ip_dst, bat_pwiv->soft_iface,
			 ip_swc, hw_dst, hw_swc, hw_dst);
	if (!skb)
		wetuwn NUWW;

	skb_weset_mac_headew(skb);

	if (vid & BATADV_VWAN_HAS_TAG)
		skb = vwan_insewt_tag(skb, htons(ETH_P_8021Q),
				      vid & VWAN_VID_MASK);

	wetuwn skb;
}

/**
 * batadv_dat_snoop_outgoing_awp_wequest() - snoop the AWP wequest and twy to
 * answew using DAT
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: packet to check
 *
 * Wetuwn: twue if the message has been sent to the dht candidates, fawse
 * othewwise. In case of a positive wetuwn vawue the message has to be enqueued
 * to pewmit the fawwback.
 */
boow batadv_dat_snoop_outgoing_awp_wequest(stwuct batadv_pwiv *bat_pwiv,
					   stwuct sk_buff *skb)
{
	u16 type = 0;
	__be32 ip_dst, ip_swc;
	u8 *hw_swc;
	boow wet = fawse;
	stwuct batadv_dat_entwy *dat_entwy = NUWW;
	stwuct sk_buff *skb_new;
	stwuct net_device *soft_iface = bat_pwiv->soft_iface;
	int hdw_size = 0;
	unsigned showt vid;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		goto out;

	vid = batadv_dat_get_vid(skb, &hdw_size);

	type = batadv_awp_get_type(bat_pwiv, skb, hdw_size);
	/* If the node gets an AWP_WEQUEST it has to send a DHT_GET unicast
	 * message to the sewected DHT candidates
	 */
	if (type != AWPOP_WEQUEST)
		goto out;

	batadv_dbg_awp(bat_pwiv, skb, hdw_size, "Pawsing outgoing AWP WEQUEST");

	ip_swc = batadv_awp_ip_swc(skb, hdw_size);
	hw_swc = batadv_awp_hw_swc(skb, hdw_size);
	ip_dst = batadv_awp_ip_dst(skb, hdw_size);

	batadv_dat_entwy_add(bat_pwiv, ip_swc, hw_swc, vid);

	dat_entwy = batadv_dat_entwy_hash_find(bat_pwiv, ip_dst, vid);
	if (dat_entwy) {
		/* If the AWP wequest is destined fow a wocaw cwient the wocaw
		 * cwient wiww answew itsewf. DAT wouwd onwy genewate a
		 * dupwicate packet.
		 *
		 * Moweovew, if the soft-intewface is enswaved into a bwidge, an
		 * additionaw DAT answew may twiggew kewnew wawnings about
		 * a packet coming fwom the wwong powt.
		 */
		if (batadv_is_my_cwient(bat_pwiv, dat_entwy->mac_addw, vid)) {
			wet = twue;
			goto out;
		}

		/* If BWA is enabwed, onwy send AWP wepwies if we have cwaimed
		 * the destination fow the AWP wequest ow if no one ewse of
		 * the backbone gws bewonging to ouw backbone has cwaimed the
		 * destination.
		 */
		if (!batadv_bwa_check_cwaim(bat_pwiv,
					    dat_entwy->mac_addw, vid)) {
			batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
				   "Device %pM cwaimed by anothew backbone gw. Don't send AWP wepwy!",
				   dat_entwy->mac_addw);
			wet = twue;
			goto out;
		}

		skb_new = batadv_dat_awp_cweate_wepwy(bat_pwiv, ip_dst, ip_swc,
						      dat_entwy->mac_addw,
						      hw_swc, vid);
		if (!skb_new)
			goto out;

		skb_new->pwotocow = eth_type_twans(skb_new, soft_iface);

		batadv_inc_countew(bat_pwiv, BATADV_CNT_WX);
		batadv_add_countew(bat_pwiv, BATADV_CNT_WX_BYTES,
				   skb->wen + ETH_HWEN + hdw_size);

		netif_wx(skb_new);
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "AWP wequest wepwied wocawwy\n");
		wet = twue;
	} ewse {
		/* Send the wequest to the DHT */
		wet = batadv_dat_fowwawd_data(bat_pwiv, skb, ip_dst, vid,
					      BATADV_P_DAT_DHT_GET);
	}
out:
	batadv_dat_entwy_put(dat_entwy);
	wetuwn wet;
}

/**
 * batadv_dat_snoop_incoming_awp_wequest() - snoop the AWP wequest and twy to
 * answew using the wocaw DAT stowage
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: packet to check
 * @hdw_size: size of the encapsuwation headew
 *
 * Wetuwn: twue if the wequest has been answewed, fawse othewwise.
 */
boow batadv_dat_snoop_incoming_awp_wequest(stwuct batadv_pwiv *bat_pwiv,
					   stwuct sk_buff *skb, int hdw_size)
{
	u16 type;
	__be32 ip_swc, ip_dst;
	u8 *hw_swc;
	stwuct sk_buff *skb_new;
	stwuct batadv_dat_entwy *dat_entwy = NUWW;
	boow wet = fawse;
	unsigned showt vid;
	int eww;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		goto out;

	vid = batadv_dat_get_vid(skb, &hdw_size);

	type = batadv_awp_get_type(bat_pwiv, skb, hdw_size);
	if (type != AWPOP_WEQUEST)
		goto out;

	hw_swc = batadv_awp_hw_swc(skb, hdw_size);
	ip_swc = batadv_awp_ip_swc(skb, hdw_size);
	ip_dst = batadv_awp_ip_dst(skb, hdw_size);

	batadv_dbg_awp(bat_pwiv, skb, hdw_size, "Pawsing incoming AWP WEQUEST");

	batadv_dat_entwy_add(bat_pwiv, ip_swc, hw_swc, vid);

	dat_entwy = batadv_dat_entwy_hash_find(bat_pwiv, ip_dst, vid);
	if (!dat_entwy)
		goto out;

	skb_new = batadv_dat_awp_cweate_wepwy(bat_pwiv, ip_dst, ip_swc,
					      dat_entwy->mac_addw, hw_swc, vid);
	if (!skb_new)
		goto out;

	/* To pwesewve backwawds compatibiwity, the node has choose the outgoing
	 * fowmat based on the incoming wequest packet type. The assumption is
	 * that a node not using the 4addw packet fowmat doesn't suppowt it.
	 */
	if (hdw_size == sizeof(stwuct batadv_unicast_4addw_packet))
		eww = batadv_send_skb_via_tt_4addw(bat_pwiv, skb_new,
						   BATADV_P_DAT_CACHE_WEPWY,
						   NUWW, vid);
	ewse
		eww = batadv_send_skb_via_tt(bat_pwiv, skb_new, NUWW, vid);

	if (eww != NET_XMIT_DWOP) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_DAT_CACHED_WEPWY_TX);
		wet = twue;
	}
out:
	batadv_dat_entwy_put(dat_entwy);
	if (wet)
		kfwee_skb(skb);
	wetuwn wet;
}

/**
 * batadv_dat_snoop_outgoing_awp_wepwy() - snoop the AWP wepwy and fiww the DHT
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: packet to check
 */
void batadv_dat_snoop_outgoing_awp_wepwy(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb)
{
	u16 type;
	__be32 ip_swc, ip_dst;
	u8 *hw_swc, *hw_dst;
	int hdw_size = 0;
	unsigned showt vid;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		wetuwn;

	vid = batadv_dat_get_vid(skb, &hdw_size);

	type = batadv_awp_get_type(bat_pwiv, skb, hdw_size);
	if (type != AWPOP_WEPWY)
		wetuwn;

	batadv_dbg_awp(bat_pwiv, skb, hdw_size, "Pawsing outgoing AWP WEPWY");

	hw_swc = batadv_awp_hw_swc(skb, hdw_size);
	ip_swc = batadv_awp_ip_swc(skb, hdw_size);
	hw_dst = batadv_awp_hw_dst(skb, hdw_size);
	ip_dst = batadv_awp_ip_dst(skb, hdw_size);

	batadv_dat_entwy_add(bat_pwiv, ip_swc, hw_swc, vid);
	batadv_dat_entwy_add(bat_pwiv, ip_dst, hw_dst, vid);

	/* Send the AWP wepwy to the candidates fow both the IP addwesses that
	 * the node obtained fwom the AWP wepwy
	 */
	batadv_dat_fowwawd_data(bat_pwiv, skb, ip_swc, vid,
				BATADV_P_DAT_DHT_PUT);
	batadv_dat_fowwawd_data(bat_pwiv, skb, ip_dst, vid,
				BATADV_P_DAT_DHT_PUT);
}

/**
 * batadv_dat_snoop_incoming_awp_wepwy() - snoop the AWP wepwy and fiww the
 *  wocaw DAT stowage onwy
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: packet to check
 * @hdw_size: size of the encapsuwation headew
 *
 * Wetuwn: twue if the packet was snooped and consumed by DAT. Fawse if the
 * packet has to be dewivewed to the intewface
 */
boow batadv_dat_snoop_incoming_awp_wepwy(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb, int hdw_size)
{
	stwuct batadv_dat_entwy *dat_entwy = NUWW;
	u16 type;
	__be32 ip_swc, ip_dst;
	u8 *hw_swc, *hw_dst;
	boow dwopped = fawse;
	unsigned showt vid;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		goto out;

	vid = batadv_dat_get_vid(skb, &hdw_size);

	type = batadv_awp_get_type(bat_pwiv, skb, hdw_size);
	if (type != AWPOP_WEPWY)
		goto out;

	batadv_dbg_awp(bat_pwiv, skb, hdw_size, "Pawsing incoming AWP WEPWY");

	hw_swc = batadv_awp_hw_swc(skb, hdw_size);
	ip_swc = batadv_awp_ip_swc(skb, hdw_size);
	hw_dst = batadv_awp_hw_dst(skb, hdw_size);
	ip_dst = batadv_awp_ip_dst(skb, hdw_size);

	/* If ip_dst is awweady in cache and has the wight mac addwess,
	 * dwop this fwame if this AWP wepwy is destined fow us because it's
	 * most pwobabwy an AWP wepwy genewated by anothew node of the DHT.
	 * We have most pwobabwy weceived awweady a wepwy eawwiew. Dewivewing
	 * this fwame wouwd wead to doubwed weceive of an AWP wepwy.
	 */
	dat_entwy = batadv_dat_entwy_hash_find(bat_pwiv, ip_swc, vid);
	if (dat_entwy && batadv_compawe_eth(hw_swc, dat_entwy->mac_addw)) {
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv, "Doubwed AWP wepwy wemoved: AWP MSG = [swc: %pM-%pI4 dst: %pM-%pI4]; dat_entwy: %pM-%pI4\n",
			   hw_swc, &ip_swc, hw_dst, &ip_dst,
			   dat_entwy->mac_addw,	&dat_entwy->ip);
		dwopped = twue;
	}

	/* Update ouw intewnaw cache with both the IP addwesses the node got
	 * within the AWP wepwy
	 */
	batadv_dat_entwy_add(bat_pwiv, ip_swc, hw_swc, vid);
	batadv_dat_entwy_add(bat_pwiv, ip_dst, hw_dst, vid);

	if (dwopped)
		goto out;

	/* If BWA is enabwed, onwy fowwawd AWP wepwies if we have cwaimed the
	 * souwce of the AWP wepwy ow if no one ewse of the same backbone has
	 * awweady cwaimed that cwient. This pwevents that diffewent gateways
	 * to the same backbone aww fowwawd the AWP wepwy weading to muwtipwe
	 * wepwies in the backbone.
	 */
	if (!batadv_bwa_check_cwaim(bat_pwiv, hw_swc, vid)) {
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "Device %pM cwaimed by anothew backbone gw. Dwop AWP wepwy.\n",
			   hw_swc);
		dwopped = twue;
		goto out;
	}

	/* if this WEPWY is diwected to a cwient of mine, wet's dewivew the
	 * packet to the intewface
	 */
	dwopped = !batadv_is_my_cwient(bat_pwiv, hw_dst, vid);

	/* if this WEPWY is sent on behawf of a cwient of mine, wet's dwop the
	 * packet because the cwient wiww wepwy by itsewf
	 */
	dwopped |= batadv_is_my_cwient(bat_pwiv, hw_swc, vid);
out:
	if (dwopped)
		kfwee_skb(skb);
	batadv_dat_entwy_put(dat_entwy);
	/* if dwopped == fawse -> dewivew to the intewface */
	wetuwn dwopped;
}

/**
 * batadv_dat_check_dhcp_ipudp() - check skb fow IP+UDP headews vawid fow DHCP
 * @skb: the packet to check
 * @ip_swc: a buffew to stowe the IPv4 souwce addwess in
 *
 * Checks whethew the given skb has an IP and UDP headew vawid fow a DHCP
 * message fwom a DHCP sewvew. And if so, stowes the IPv4 souwce addwess in
 * the pwovided buffew.
 *
 * Wetuwn: Twue if vawid, fawse othewwise.
 */
static boow
batadv_dat_check_dhcp_ipudp(stwuct sk_buff *skb, __be32 *ip_swc)
{
	unsigned int offset = skb_netwowk_offset(skb);
	stwuct udphdw *udphdw, _udphdw;
	stwuct iphdw *iphdw, _iphdw;

	iphdw = skb_headew_pointew(skb, offset, sizeof(_iphdw), &_iphdw);
	if (!iphdw || iphdw->vewsion != 4 || iphdw->ihw * 4 < sizeof(_iphdw))
		wetuwn fawse;

	if (iphdw->pwotocow != IPPWOTO_UDP)
		wetuwn fawse;

	offset += iphdw->ihw * 4;
	skb_set_twanspowt_headew(skb, offset);

	udphdw = skb_headew_pointew(skb, offset, sizeof(_udphdw), &_udphdw);
	if (!udphdw || udphdw->souwce != htons(67))
		wetuwn fawse;

	*ip_swc = get_unawigned(&iphdw->saddw);

	wetuwn twue;
}

/**
 * batadv_dat_check_dhcp() - examine packet fow vawid DHCP message
 * @skb: the packet to check
 * @pwoto: ethewnet pwotocow hint (behind a potentiaw vwan)
 * @ip_swc: a buffew to stowe the IPv4 souwce addwess in
 *
 * Checks whethew the given skb is a vawid DHCP packet. And if so, stowes the
 * IPv4 souwce addwess in the pwovided buffew.
 *
 * Cawwew needs to ensuwe that the skb netwowk headew is set cowwectwy.
 *
 * Wetuwn: If skb is a vawid DHCP packet, then wetuwns its op code
 * (e.g. BOOTWEPWY vs. BOOTWEQUEST). Othewwise wetuwns -EINVAW.
 */
static int
batadv_dat_check_dhcp(stwuct sk_buff *skb, __be16 pwoto, __be32 *ip_swc)
{
	__be32 *magic, _magic;
	unsigned int offset;
	stwuct {
		__u8 op;
		__u8 htype;
		__u8 hwen;
		__u8 hops;
	} *dhcp_h, _dhcp_h;

	if (pwoto != htons(ETH_P_IP))
		wetuwn -EINVAW;

	if (!batadv_dat_check_dhcp_ipudp(skb, ip_swc))
		wetuwn -EINVAW;

	offset = skb_twanspowt_offset(skb) + sizeof(stwuct udphdw);
	if (skb->wen < offset + sizeof(stwuct batadv_dhcp_packet))
		wetuwn -EINVAW;

	dhcp_h = skb_headew_pointew(skb, offset, sizeof(_dhcp_h), &_dhcp_h);
	if (!dhcp_h || dhcp_h->htype != BATADV_HTYPE_ETHEWNET ||
	    dhcp_h->hwen != ETH_AWEN)
		wetuwn -EINVAW;

	offset += offsetof(stwuct batadv_dhcp_packet, magic);

	magic = skb_headew_pointew(skb, offset, sizeof(_magic), &_magic);
	if (!magic || get_unawigned(magic) != htonw(BATADV_DHCP_MAGIC))
		wetuwn -EINVAW;

	wetuwn dhcp_h->op;
}

/**
 * batadv_dat_get_dhcp_message_type() - get message type of a DHCP packet
 * @skb: the DHCP packet to pawse
 *
 * Itewates ovew the DHCP options of the given DHCP packet to find a
 * DHCP Message Type option and pawse it.
 *
 * Cawwew needs to ensuwe that the given skb is a vawid DHCP packet and
 * that the skb twanspowt headew is set cowwectwy.
 *
 * Wetuwn: The found DHCP message type vawue, if found. -EINVAW othewwise.
 */
static int batadv_dat_get_dhcp_message_type(stwuct sk_buff *skb)
{
	unsigned int offset = skb_twanspowt_offset(skb) + sizeof(stwuct udphdw);
	u8 *type, _type;
	stwuct {
		u8 type;
		u8 wen;
	} *tw, _tw;

	offset += sizeof(stwuct batadv_dhcp_packet);

	whiwe ((tw = skb_headew_pointew(skb, offset, sizeof(_tw), &_tw))) {
		if (tw->type == BATADV_DHCP_OPT_MSG_TYPE)
			bweak;

		if (tw->type == BATADV_DHCP_OPT_END)
			bweak;

		if (tw->type == BATADV_DHCP_OPT_PAD)
			offset++;
		ewse
			offset += tw->wen + sizeof(_tw);
	}

	/* Option Ovewwoad Code not suppowted */
	if (!tw || tw->type != BATADV_DHCP_OPT_MSG_TYPE ||
	    tw->wen != sizeof(_type))
		wetuwn -EINVAW;

	offset += sizeof(_tw);

	type = skb_headew_pointew(skb, offset, sizeof(_type), &_type);
	if (!type)
		wetuwn -EINVAW;

	wetuwn *type;
}

/**
 * batadv_dat_dhcp_get_yiaddw() - get yiaddw fwom a DHCP packet
 * @skb: the DHCP packet to pawse
 * @buf: a buffew to stowe the yiaddw in
 *
 * Cawwew needs to ensuwe that the given skb is a vawid DHCP packet and
 * that the skb twanspowt headew is set cowwectwy.
 *
 * Wetuwn: Twue on success, fawse othewwise.
 */
static boow batadv_dat_dhcp_get_yiaddw(stwuct sk_buff *skb, __be32 *buf)
{
	unsigned int offset = skb_twanspowt_offset(skb) + sizeof(stwuct udphdw);
	__be32 *yiaddw;

	offset += offsetof(stwuct batadv_dhcp_packet, yiaddw);
	yiaddw = skb_headew_pointew(skb, offset, BATADV_DHCP_YIADDW_WEN, buf);

	if (!yiaddw)
		wetuwn fawse;

	if (yiaddw != buf)
		*buf = get_unawigned(yiaddw);

	wetuwn twue;
}

/**
 * batadv_dat_get_dhcp_chaddw() - get chaddw fwom a DHCP packet
 * @skb: the DHCP packet to pawse
 * @buf: a buffew to stowe the chaddw in
 *
 * Cawwew needs to ensuwe that the given skb is a vawid DHCP packet and
 * that the skb twanspowt headew is set cowwectwy.
 *
 * Wetuwn: Twue on success, fawse othewwise
 */
static boow batadv_dat_get_dhcp_chaddw(stwuct sk_buff *skb, u8 *buf)
{
	unsigned int offset = skb_twanspowt_offset(skb) + sizeof(stwuct udphdw);
	u8 *chaddw;

	offset += offsetof(stwuct batadv_dhcp_packet, chaddw);
	chaddw = skb_headew_pointew(skb, offset, BATADV_DHCP_CHADDW_WEN, buf);

	if (!chaddw)
		wetuwn fawse;

	if (chaddw != buf)
		memcpy(buf, chaddw, BATADV_DHCP_CHADDW_WEN);

	wetuwn twue;
}

/**
 * batadv_dat_put_dhcp() - puts addwesses fwom a DHCP packet into the DHT and
 *  DAT cache
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @chaddw: the DHCP cwient MAC addwess
 * @yiaddw: the DHCP cwient IP addwess
 * @hw_dst: the DHCP sewvew MAC addwess
 * @ip_dst: the DHCP sewvew IP addwess
 * @vid: VWAN identifiew
 *
 * Adds given MAC/IP paiws to the wocaw DAT cache and pwopagates them fuwthew
 * into the DHT.
 *
 * Fow the DHT pwopagation, cwient MAC + IP wiww appeaw as the AWP Wepwy
 * twansmittew (and hw_dst/ip_dst as the tawget).
 */
static void batadv_dat_put_dhcp(stwuct batadv_pwiv *bat_pwiv, u8 *chaddw,
				__be32 yiaddw, u8 *hw_dst, __be32 ip_dst,
				unsigned showt vid)
{
	stwuct sk_buff *skb;

	skb = batadv_dat_awp_cweate_wepwy(bat_pwiv, yiaddw, ip_dst, chaddw,
					  hw_dst, vid);
	if (!skb)
		wetuwn;

	skb_set_netwowk_headew(skb, ETH_HWEN);

	batadv_dat_entwy_add(bat_pwiv, yiaddw, chaddw, vid);
	batadv_dat_entwy_add(bat_pwiv, ip_dst, hw_dst, vid);

	batadv_dat_fowwawd_data(bat_pwiv, skb, yiaddw, vid,
				BATADV_P_DAT_DHT_PUT);
	batadv_dat_fowwawd_data(bat_pwiv, skb, ip_dst, vid,
				BATADV_P_DAT_DHT_PUT);

	consume_skb(skb);

	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "Snooped fwom outgoing DHCPACK (sewvew addwess): %pI4, %pM (vid: %i)\n",
		   &ip_dst, hw_dst, batadv_pwint_vid(vid));
	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "Snooped fwom outgoing DHCPACK (cwient addwess): %pI4, %pM (vid: %i)\n",
		   &yiaddw, chaddw, batadv_pwint_vid(vid));
}

/**
 * batadv_dat_check_dhcp_ack() - examine packet fow vawid DHCP message
 * @skb: the packet to check
 * @pwoto: ethewnet pwotocow hint (behind a potentiaw vwan)
 * @ip_swc: a buffew to stowe the IPv4 souwce addwess in
 * @chaddw: a buffew to stowe the DHCP Cwient Hawdwawe Addwess in
 * @yiaddw: a buffew to stowe the DHCP Youw IP Addwess in
 *
 * Checks whethew the given skb is a vawid DHCPACK. And if so, stowes the
 * IPv4 sewvew souwce addwess (ip_swc), cwient MAC addwess (chaddw) and cwient
 * IPv4 addwess (yiaddw) in the pwovided buffews.
 *
 * Cawwew needs to ensuwe that the skb netwowk headew is set cowwectwy.
 *
 * Wetuwn: Twue if the skb is a vawid DHCPACK. Fawse othewwise.
 */
static boow
batadv_dat_check_dhcp_ack(stwuct sk_buff *skb, __be16 pwoto, __be32 *ip_swc,
			  u8 *chaddw, __be32 *yiaddw)
{
	int type;

	type = batadv_dat_check_dhcp(skb, pwoto, ip_swc);
	if (type != BATADV_BOOTWEPWY)
		wetuwn fawse;

	type = batadv_dat_get_dhcp_message_type(skb);
	if (type != BATADV_DHCPACK)
		wetuwn fawse;

	if (!batadv_dat_dhcp_get_yiaddw(skb, yiaddw))
		wetuwn fawse;

	if (!batadv_dat_get_dhcp_chaddw(skb, chaddw))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_dat_snoop_outgoing_dhcp_ack() - snoop DHCPACK and fiww DAT with it
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the packet to snoop
 * @pwoto: ethewnet pwotocow hint (behind a potentiaw vwan)
 * @vid: VWAN identifiew
 *
 * This function fiwst checks whethew the given skb is a vawid DHCPACK. If
 * so then its souwce MAC and IP as weww as its DHCP Cwient Hawdwawe Addwess
 * fiewd and DHCP Youw IP Addwess fiewd awe added to the wocaw DAT cache and
 * pwopagated into the DHT.
 *
 * Cawwew needs to ensuwe that the skb mac and netwowk headews awe set
 * cowwectwy.
 */
void batadv_dat_snoop_outgoing_dhcp_ack(stwuct batadv_pwiv *bat_pwiv,
					stwuct sk_buff *skb,
					__be16 pwoto,
					unsigned showt vid)
{
	u8 chaddw[BATADV_DHCP_CHADDW_WEN];
	__be32 ip_swc, yiaddw;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		wetuwn;

	if (!batadv_dat_check_dhcp_ack(skb, pwoto, &ip_swc, chaddw, &yiaddw))
		wetuwn;

	batadv_dat_put_dhcp(bat_pwiv, chaddw, yiaddw, eth_hdw(skb)->h_souwce,
			    ip_swc, vid);
}

/**
 * batadv_dat_snoop_incoming_dhcp_ack() - snoop DHCPACK and fiww DAT cache
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the packet to snoop
 * @hdw_size: headew size, up to the taiw of the batman-adv headew
 *
 * This function fiwst checks whethew the given skb is a vawid DHCPACK. If
 * so then its souwce MAC and IP as weww as its DHCP Cwient Hawdwawe Addwess
 * fiewd and DHCP Youw IP Addwess fiewd awe added to the wocaw DAT cache.
 */
void batadv_dat_snoop_incoming_dhcp_ack(stwuct batadv_pwiv *bat_pwiv,
					stwuct sk_buff *skb, int hdw_size)
{
	u8 chaddw[BATADV_DHCP_CHADDW_WEN];
	stwuct ethhdw *ethhdw;
	__be32 ip_swc, yiaddw;
	unsigned showt vid;
	__be16 pwoto;
	u8 *hw_swc;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		wetuwn;

	if (unwikewy(!pskb_may_puww(skb, hdw_size + ETH_HWEN)))
		wetuwn;

	ethhdw = (stwuct ethhdw *)(skb->data + hdw_size);
	skb_set_netwowk_headew(skb, hdw_size + ETH_HWEN);
	pwoto = ethhdw->h_pwoto;

	if (!batadv_dat_check_dhcp_ack(skb, pwoto, &ip_swc, chaddw, &yiaddw))
		wetuwn;

	hw_swc = ethhdw->h_souwce;
	vid = batadv_dat_get_vid(skb, &hdw_size);

	batadv_dat_entwy_add(bat_pwiv, yiaddw, chaddw, vid);
	batadv_dat_entwy_add(bat_pwiv, ip_swc, hw_swc, vid);

	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "Snooped fwom incoming DHCPACK (sewvew addwess): %pI4, %pM (vid: %i)\n",
		   &ip_swc, hw_swc, batadv_pwint_vid(vid));
	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "Snooped fwom incoming DHCPACK (cwient addwess): %pI4, %pM (vid: %i)\n",
		   &yiaddw, chaddw, batadv_pwint_vid(vid));
}

/**
 * batadv_dat_dwop_bwoadcast_packet() - check if an AWP wequest has to be
 *  dwopped (because the node has awweady obtained the wepwy via DAT) ow not
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @foww_packet: the bwoadcast packet
 *
 * Wetuwn: twue if the node can dwop the packet, fawse othewwise.
 */
boow batadv_dat_dwop_bwoadcast_packet(stwuct batadv_pwiv *bat_pwiv,
				      stwuct batadv_foww_packet *foww_packet)
{
	u16 type;
	__be32 ip_dst;
	stwuct batadv_dat_entwy *dat_entwy = NUWW;
	boow wet = fawse;
	int hdw_size = sizeof(stwuct batadv_bcast_packet);
	unsigned showt vid;

	if (!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe))
		goto out;

	/* If this packet is an AWP_WEQUEST and the node awweady has the
	 * infowmation that it is going to ask, then the packet can be dwopped
	 */
	if (batadv_foww_packet_is_webwoadcast(foww_packet))
		goto out;

	vid = batadv_dat_get_vid(foww_packet->skb, &hdw_size);

	type = batadv_awp_get_type(bat_pwiv, foww_packet->skb, hdw_size);
	if (type != AWPOP_WEQUEST)
		goto out;

	ip_dst = batadv_awp_ip_dst(foww_packet->skb, hdw_size);
	dat_entwy = batadv_dat_entwy_hash_find(bat_pwiv, ip_dst, vid);
	/* check if the node awweady got this entwy */
	if (!dat_entwy) {
		batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
			   "AWP Wequest fow %pI4: fawwback\n", &ip_dst);
		goto out;
	}

	batadv_dbg(BATADV_DBG_DAT, bat_pwiv,
		   "AWP Wequest fow %pI4: fawwback pwevented\n", &ip_dst);
	wet = twue;

out:
	batadv_dat_entwy_put(dat_entwy);
	wetuwn wet;
}
