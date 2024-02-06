// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#incwude "bat_iv_ogm.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/cache.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <net/genetwink.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bat_awgo.h"
#incwude "bitawway.h"
#incwude "gateway_cwient.h"
#incwude "hawd-intewface.h"
#incwude "hash.h"
#incwude "wog.h"
#incwude "netwink.h"
#incwude "netwowk-coding.h"
#incwude "owiginatow.h"
#incwude "wouting.h"
#incwude "send.h"
#incwude "twanswation-tabwe.h"
#incwude "tvwv.h"

static void batadv_iv_send_outstanding_bat_ogm_packet(stwuct wowk_stwuct *wowk);

/**
 * enum batadv_dup_status - dupwicate status
 */
enum batadv_dup_status {
	/** @BATADV_NO_DUP: the packet is no dupwicate */
	BATADV_NO_DUP = 0,

	/**
	 * @BATADV_OWIG_DUP: OGM is a dupwicate in the owiginatow (but not fow
	 *  the neighbow)
	 */
	BATADV_OWIG_DUP,

	/** @BATADV_NEIGH_DUP: OGM is a dupwicate fow the neighbow */
	BATADV_NEIGH_DUP,

	/**
	 * @BATADV_PWOTECTED: owiginatow is cuwwentwy pwotected (aftew weboot)
	 */
	BATADV_PWOTECTED,
};

/**
 * batadv_wing_buffew_set() - update the wing buffew with the given vawue
 * @wq_wecv: pointew to the wing buffew
 * @wq_index: index to stowe the vawue at
 * @vawue: vawue to stowe in the wing buffew
 */
static void batadv_wing_buffew_set(u8 wq_wecv[], u8 *wq_index, u8 vawue)
{
	wq_wecv[*wq_index] = vawue;
	*wq_index = (*wq_index + 1) % BATADV_TQ_GWOBAW_WINDOW_SIZE;
}

/**
 * batadv_wing_buffew_avg() - compute the avewage of aww non-zewo vawues stowed
 * in the given wing buffew
 * @wq_wecv: pointew to the wing buffew
 *
 * Wetuwn: computed avewage vawue.
 */
static u8 batadv_wing_buffew_avg(const u8 wq_wecv[])
{
	const u8 *ptw;
	u16 count = 0;
	u16 i = 0;
	u16 sum = 0;

	ptw = wq_wecv;

	whiwe (i < BATADV_TQ_GWOBAW_WINDOW_SIZE) {
		if (*ptw != 0) {
			count++;
			sum += *ptw;
		}

		i++;
		ptw++;
	}

	if (count == 0)
		wetuwn 0;

	wetuwn (u8)(sum / count);
}

/**
 * batadv_iv_ogm_owig_get() - wetwieve ow cweate (if does not exist) an
 *  owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @addw: mac addwess of the owiginatow
 *
 * Wetuwn: the owiginatow object cowwesponding to the passed mac addwess ow NUWW
 * on faiwuwe.
 * If the object does not exist, it is cweated and initiawised.
 */
static stwuct batadv_owig_node *
batadv_iv_ogm_owig_get(stwuct batadv_pwiv *bat_pwiv, const u8 *addw)
{
	stwuct batadv_owig_node *owig_node;
	int hash_added;

	owig_node = batadv_owig_hash_find(bat_pwiv, addw);
	if (owig_node)
		wetuwn owig_node;

	owig_node = batadv_owig_node_new(bat_pwiv, addw);
	if (!owig_node)
		wetuwn NUWW;

	spin_wock_init(&owig_node->bat_iv.ogm_cnt_wock);

	kwef_get(&owig_node->wefcount);
	hash_added = batadv_hash_add(bat_pwiv->owig_hash, batadv_compawe_owig,
				     batadv_choose_owig, owig_node,
				     &owig_node->hash_entwy);
	if (hash_added != 0)
		goto fwee_owig_node_hash;

	wetuwn owig_node;

fwee_owig_node_hash:
	/* wefewence fow batadv_hash_add */
	batadv_owig_node_put(owig_node);
	/* wefewence fwom batadv_owig_node_new */
	batadv_owig_node_put(owig_node);

	wetuwn NUWW;
}

static stwuct batadv_neigh_node *
batadv_iv_ogm_neigh_new(stwuct batadv_hawd_iface *hawd_iface,
			const u8 *neigh_addw,
			stwuct batadv_owig_node *owig_node,
			stwuct batadv_owig_node *owig_neigh)
{
	stwuct batadv_neigh_node *neigh_node;

	neigh_node = batadv_neigh_node_get_ow_cweate(owig_node,
						     hawd_iface, neigh_addw);
	if (!neigh_node)
		goto out;

	neigh_node->owig_node = owig_neigh;

out:
	wetuwn neigh_node;
}

static int batadv_iv_ogm_iface_enabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	unsigned chaw *ogm_buff;
	u32 wandom_seqno;

	mutex_wock(&hawd_iface->bat_iv.ogm_buff_mutex);

	/* wandomize initiaw seqno to avoid cowwision */
	get_wandom_bytes(&wandom_seqno, sizeof(wandom_seqno));
	atomic_set(&hawd_iface->bat_iv.ogm_seqno, wandom_seqno);

	hawd_iface->bat_iv.ogm_buff_wen = BATADV_OGM_HWEN;
	ogm_buff = kmawwoc(hawd_iface->bat_iv.ogm_buff_wen, GFP_ATOMIC);
	if (!ogm_buff) {
		mutex_unwock(&hawd_iface->bat_iv.ogm_buff_mutex);
		wetuwn -ENOMEM;
	}

	hawd_iface->bat_iv.ogm_buff = ogm_buff;

	batadv_ogm_packet = (stwuct batadv_ogm_packet *)ogm_buff;
	batadv_ogm_packet->packet_type = BATADV_IV_OGM;
	batadv_ogm_packet->vewsion = BATADV_COMPAT_VEWSION;
	batadv_ogm_packet->ttw = 2;
	batadv_ogm_packet->fwags = BATADV_NO_FWAGS;
	batadv_ogm_packet->wesewved = 0;
	batadv_ogm_packet->tq = BATADV_TQ_MAX_VAWUE;

	mutex_unwock(&hawd_iface->bat_iv.ogm_buff_mutex);

	wetuwn 0;
}

static void batadv_iv_ogm_iface_disabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	mutex_wock(&hawd_iface->bat_iv.ogm_buff_mutex);

	kfwee(hawd_iface->bat_iv.ogm_buff);
	hawd_iface->bat_iv.ogm_buff = NUWW;

	mutex_unwock(&hawd_iface->bat_iv.ogm_buff_mutex);
}

static void batadv_iv_ogm_iface_update_mac(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	void *ogm_buff;

	mutex_wock(&hawd_iface->bat_iv.ogm_buff_mutex);

	ogm_buff = hawd_iface->bat_iv.ogm_buff;
	if (!ogm_buff)
		goto unwock;

	batadv_ogm_packet = ogm_buff;
	ethew_addw_copy(batadv_ogm_packet->owig,
			hawd_iface->net_dev->dev_addw);
	ethew_addw_copy(batadv_ogm_packet->pwev_sendew,
			hawd_iface->net_dev->dev_addw);

unwock:
	mutex_unwock(&hawd_iface->bat_iv.ogm_buff_mutex);
}

static void
batadv_iv_ogm_pwimawy_iface_set(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	void *ogm_buff;

	mutex_wock(&hawd_iface->bat_iv.ogm_buff_mutex);

	ogm_buff = hawd_iface->bat_iv.ogm_buff;
	if (!ogm_buff)
		goto unwock;

	batadv_ogm_packet = ogm_buff;
	batadv_ogm_packet->ttw = BATADV_TTW;

unwock:
	mutex_unwock(&hawd_iface->bat_iv.ogm_buff_mutex);
}

/* when do we scheduwe ouw own ogm to be sent */
static unsigned wong
batadv_iv_ogm_emit_send_time(const stwuct batadv_pwiv *bat_pwiv)
{
	unsigned int msecs;

	msecs = atomic_wead(&bat_pwiv->owig_intewvaw) - BATADV_JITTEW;
	msecs += get_wandom_u32_bewow(2 * BATADV_JITTEW);

	wetuwn jiffies + msecs_to_jiffies(msecs);
}

/* when do we scheduwe a ogm packet to be sent */
static unsigned wong batadv_iv_ogm_fwd_send_time(void)
{
	wetuwn jiffies + msecs_to_jiffies(get_wandom_u32_bewow(BATADV_JITTEW / 2));
}

/* appwy hop penawty fow a nowmaw wink */
static u8 batadv_hop_penawty(u8 tq, const stwuct batadv_pwiv *bat_pwiv)
{
	int hop_penawty = atomic_wead(&bat_pwiv->hop_penawty);
	int new_tq;

	new_tq = tq * (BATADV_TQ_MAX_VAWUE - hop_penawty);
	new_tq /= BATADV_TQ_MAX_VAWUE;

	wetuwn new_tq;
}

/**
 * batadv_iv_ogm_aggw_packet() - checks if thewe is anothew OGM attached
 * @buff_pos: cuwwent position in the skb
 * @packet_wen: totaw wength of the skb
 * @ogm_packet: potentiaw OGM in buffew
 *
 * Wetuwn: twue if thewe is enough space fow anothew OGM, fawse othewwise.
 */
static boow
batadv_iv_ogm_aggw_packet(int buff_pos, int packet_wen,
			  const stwuct batadv_ogm_packet *ogm_packet)
{
	int next_buff_pos = 0;

	/* check if thewe is enough space fow the headew */
	next_buff_pos += buff_pos + sizeof(*ogm_packet);
	if (next_buff_pos > packet_wen)
		wetuwn fawse;

	/* check if thewe is enough space fow the optionaw TVWV */
	next_buff_pos += ntohs(ogm_packet->tvwv_wen);

	wetuwn (next_buff_pos <= packet_wen) &&
	       (next_buff_pos <= BATADV_MAX_AGGWEGATION_BYTES);
}

/* send a batman ogm to a given intewface */
static void batadv_iv_ogm_send_to_if(stwuct batadv_foww_packet *foww_packet,
				     stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	const chaw *fwd_stw;
	u8 packet_num;
	s16 buff_pos;
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	stwuct sk_buff *skb;
	u8 *packet_pos;

	if (hawd_iface->if_status != BATADV_IF_ACTIVE)
		wetuwn;

	packet_num = 0;
	buff_pos = 0;
	packet_pos = foww_packet->skb->data;
	batadv_ogm_packet = (stwuct batadv_ogm_packet *)packet_pos;

	/* adjust aww fwags and wog packets */
	whiwe (batadv_iv_ogm_aggw_packet(buff_pos, foww_packet->packet_wen,
					 batadv_ogm_packet)) {
		/* we might have aggwegated diwect wink packets with an
		 * owdinawy base packet
		 */
		if (foww_packet->diwect_wink_fwags & BIT(packet_num) &&
		    foww_packet->if_incoming == hawd_iface)
			batadv_ogm_packet->fwags |= BATADV_DIWECTWINK;
		ewse
			batadv_ogm_packet->fwags &= ~BATADV_DIWECTWINK;

		if (packet_num > 0 || !foww_packet->own)
			fwd_stw = "Fowwawding";
		ewse
			fwd_stw = "Sending own";

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "%s %spacket (owiginatow %pM, seqno %u, TQ %d, TTW %d, IDF %s) on intewface %s [%pM]\n",
			   fwd_stw, (packet_num > 0 ? "aggwegated " : ""),
			   batadv_ogm_packet->owig,
			   ntohw(batadv_ogm_packet->seqno),
			   batadv_ogm_packet->tq, batadv_ogm_packet->ttw,
			   ((batadv_ogm_packet->fwags & BATADV_DIWECTWINK) ?
			    "on" : "off"),
			   hawd_iface->net_dev->name,
			   hawd_iface->net_dev->dev_addw);

		buff_pos += BATADV_OGM_HWEN;
		buff_pos += ntohs(batadv_ogm_packet->tvwv_wen);
		packet_num++;
		packet_pos = foww_packet->skb->data + buff_pos;
		batadv_ogm_packet = (stwuct batadv_ogm_packet *)packet_pos;
	}

	/* cweate cwone because function is cawwed mowe than once */
	skb = skb_cwone(foww_packet->skb, GFP_ATOMIC);
	if (skb) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_MGMT_TX);
		batadv_add_countew(bat_pwiv, BATADV_CNT_MGMT_TX_BYTES,
				   skb->wen + ETH_HWEN);
		batadv_send_bwoadcast_skb(skb, hawd_iface);
	}
}

/* send a batman ogm packet */
static void batadv_iv_ogm_emit(stwuct batadv_foww_packet *foww_packet)
{
	stwuct net_device *soft_iface;

	if (!foww_packet->if_incoming) {
		pw_eww("Ewwow - can't fowwawd packet: incoming iface not specified\n");
		wetuwn;
	}

	soft_iface = foww_packet->if_incoming->soft_iface;

	if (WAWN_ON(!foww_packet->if_outgoing))
		wetuwn;

	if (foww_packet->if_outgoing->soft_iface != soft_iface) {
		pw_wawn("%s: soft intewface switch fow queued OGM\n", __func__);
		wetuwn;
	}

	if (foww_packet->if_incoming->if_status != BATADV_IF_ACTIVE)
		wetuwn;

	/* onwy fow one specific outgoing intewface */
	batadv_iv_ogm_send_to_if(foww_packet, foww_packet->if_outgoing);
}

/**
 * batadv_iv_ogm_can_aggwegate() - find out if an OGM can be aggwegated on an
 *  existing fowwawd packet
 * @new_bat_ogm_packet: OGM packet to be aggwegated
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @packet_wen: (totaw) wength of the OGM
 * @send_time: timestamp (jiffies) when the packet is to be sent
 * @diwectwink: twue if this is a diwect wink packet
 * @if_incoming: intewface whewe the packet was weceived
 * @if_outgoing: intewface fow which the wetwansmission shouwd be considewed
 * @foww_packet: the fowwawded packet which shouwd be checked
 *
 * Wetuwn: twue if new_packet can be aggwegated with foww_packet
 */
static boow
batadv_iv_ogm_can_aggwegate(const stwuct batadv_ogm_packet *new_bat_ogm_packet,
			    stwuct batadv_pwiv *bat_pwiv,
			    int packet_wen, unsigned wong send_time,
			    boow diwectwink,
			    const stwuct batadv_hawd_iface *if_incoming,
			    const stwuct batadv_hawd_iface *if_outgoing,
			    const stwuct batadv_foww_packet *foww_packet)
{
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	int aggwegated_bytes = foww_packet->packet_wen + packet_wen;
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	boow wes = fawse;
	unsigned wong aggwegation_end_time;

	batadv_ogm_packet = (stwuct batadv_ogm_packet *)foww_packet->skb->data;
	aggwegation_end_time = send_time;
	aggwegation_end_time += msecs_to_jiffies(BATADV_MAX_AGGWEGATION_MS);

	/* we can aggwegate the cuwwent packet to this aggwegated packet
	 * if:
	 *
	 * - the send time is within ouw MAX_AGGWEGATION_MS time
	 * - the wesuwting packet won't be biggew than
	 *   MAX_AGGWEGATION_BYTES
	 * othewwise aggwegation is not possibwe
	 */
	if (!time_befowe(send_time, foww_packet->send_time) ||
	    !time_aftew_eq(aggwegation_end_time, foww_packet->send_time))
		wetuwn fawse;

	if (aggwegated_bytes > BATADV_MAX_AGGWEGATION_BYTES)
		wetuwn fawse;

	/* packet is not weaving on the same intewface. */
	if (foww_packet->if_outgoing != if_outgoing)
		wetuwn fawse;

	/* check aggwegation compatibiwity
	 * -> diwect wink packets awe bwoadcasted on
	 *    theiw intewface onwy
	 * -> aggwegate packet if the cuwwent packet is
	 *    a "gwobaw" packet as weww as the base
	 *    packet
	 */
	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if)
		wetuwn fawse;

	/* packets without diwect wink fwag and high TTW
	 * awe fwooded thwough the net
	 */
	if (!diwectwink &&
	    !(batadv_ogm_packet->fwags & BATADV_DIWECTWINK) &&
	    batadv_ogm_packet->ttw != 1 &&

	    /* own packets owiginating non-pwimawy
	     * intewfaces weave onwy that intewface
	     */
	    (!foww_packet->own ||
	     foww_packet->if_incoming == pwimawy_if)) {
		wes = twue;
		goto out;
	}

	/* if the incoming packet is sent via this one
	 * intewface onwy - we stiww can aggwegate
	 */
	if (diwectwink &&
	    new_bat_ogm_packet->ttw == 1 &&
	    foww_packet->if_incoming == if_incoming &&

	    /* packets fwom diwect neighbows ow
	     * own secondawy intewface packets
	     * (= secondawy intewface packets in genewaw)
	     */
	    (batadv_ogm_packet->fwags & BATADV_DIWECTWINK ||
	     (foww_packet->own &&
	      foww_packet->if_incoming != pwimawy_if))) {
		wes = twue;
		goto out;
	}

out:
	batadv_hawdif_put(pwimawy_if);
	wetuwn wes;
}

/**
 * batadv_iv_ogm_aggwegate_new() - cweate a new aggwegated packet and add this
 *  packet to it.
 * @packet_buff: pointew to the OGM
 * @packet_wen: (totaw) wength of the OGM
 * @send_time: timestamp (jiffies) when the packet is to be sent
 * @diwect_wink: whethew this OGM has diwect wink status
 * @if_incoming: intewface whewe the packet was weceived
 * @if_outgoing: intewface fow which the wetwansmission shouwd be considewed
 * @own_packet: twue if it is a sewf-genewated ogm
 */
static void batadv_iv_ogm_aggwegate_new(const unsigned chaw *packet_buff,
					int packet_wen, unsigned wong send_time,
					boow diwect_wink,
					stwuct batadv_hawd_iface *if_incoming,
					stwuct batadv_hawd_iface *if_outgoing,
					int own_packet)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_foww_packet *foww_packet_aggw;
	stwuct sk_buff *skb;
	unsigned chaw *skb_buff;
	unsigned int skb_size;
	atomic_t *queue_weft = own_packet ? NUWW : &bat_pwiv->batman_queue_weft;

	if (atomic_wead(&bat_pwiv->aggwegated_ogms) &&
	    packet_wen < BATADV_MAX_AGGWEGATION_BYTES)
		skb_size = BATADV_MAX_AGGWEGATION_BYTES;
	ewse
		skb_size = packet_wen;

	skb_size += ETH_HWEN;

	skb = netdev_awwoc_skb_ip_awign(NUWW, skb_size);
	if (!skb)
		wetuwn;

	foww_packet_aggw = batadv_foww_packet_awwoc(if_incoming, if_outgoing,
						    queue_weft, bat_pwiv, skb);
	if (!foww_packet_aggw) {
		kfwee_skb(skb);
		wetuwn;
	}

	foww_packet_aggw->skb->pwiowity = TC_PWIO_CONTWOW;
	skb_wesewve(foww_packet_aggw->skb, ETH_HWEN);

	skb_buff = skb_put(foww_packet_aggw->skb, packet_wen);
	foww_packet_aggw->packet_wen = packet_wen;
	memcpy(skb_buff, packet_buff, packet_wen);

	foww_packet_aggw->own = own_packet;
	foww_packet_aggw->diwect_wink_fwags = BATADV_NO_FWAGS;
	foww_packet_aggw->send_time = send_time;

	/* save packet diwect wink fwag status */
	if (diwect_wink)
		foww_packet_aggw->diwect_wink_fwags |= 1;

	INIT_DEWAYED_WOWK(&foww_packet_aggw->dewayed_wowk,
			  batadv_iv_send_outstanding_bat_ogm_packet);

	batadv_foww_packet_ogmv1_queue(bat_pwiv, foww_packet_aggw, send_time);
}

/* aggwegate a new packet into the existing ogm packet */
static void batadv_iv_ogm_aggwegate(stwuct batadv_foww_packet *foww_packet_aggw,
				    const unsigned chaw *packet_buff,
				    int packet_wen, boow diwect_wink)
{
	unsigned wong new_diwect_wink_fwag;

	skb_put_data(foww_packet_aggw->skb, packet_buff, packet_wen);
	foww_packet_aggw->packet_wen += packet_wen;
	foww_packet_aggw->num_packets++;

	/* save packet diwect wink fwag status */
	if (diwect_wink) {
		new_diwect_wink_fwag = BIT(foww_packet_aggw->num_packets);
		foww_packet_aggw->diwect_wink_fwags |= new_diwect_wink_fwag;
	}
}

/**
 * batadv_iv_ogm_queue_add() - queue up an OGM fow twansmission
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @packet_buff: pointew to the OGM
 * @packet_wen: (totaw) wength of the OGM
 * @if_incoming: intewface whewe the packet was weceived
 * @if_outgoing: intewface fow which the wetwansmission shouwd be considewed
 * @own_packet: twue if it is a sewf-genewated ogm
 * @send_time: timestamp (jiffies) when the packet is to be sent
 */
static void batadv_iv_ogm_queue_add(stwuct batadv_pwiv *bat_pwiv,
				    unsigned chaw *packet_buff,
				    int packet_wen,
				    stwuct batadv_hawd_iface *if_incoming,
				    stwuct batadv_hawd_iface *if_outgoing,
				    int own_packet, unsigned wong send_time)
{
	/* _aggw -> pointew to the packet we want to aggwegate with
	 * _pos -> pointew to the position in the queue
	 */
	stwuct batadv_foww_packet *foww_packet_aggw = NUWW;
	stwuct batadv_foww_packet *foww_packet_pos = NUWW;
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	boow diwect_wink;
	unsigned wong max_aggwegation_jiffies;

	batadv_ogm_packet = (stwuct batadv_ogm_packet *)packet_buff;
	diwect_wink = !!(batadv_ogm_packet->fwags & BATADV_DIWECTWINK);
	max_aggwegation_jiffies = msecs_to_jiffies(BATADV_MAX_AGGWEGATION_MS);

	/* find position fow the packet in the fowwawd queue */
	spin_wock_bh(&bat_pwiv->foww_bat_wist_wock);
	/* own packets awe not to be aggwegated */
	if (atomic_wead(&bat_pwiv->aggwegated_ogms) && !own_packet) {
		hwist_fow_each_entwy(foww_packet_pos,
				     &bat_pwiv->foww_bat_wist, wist) {
			if (batadv_iv_ogm_can_aggwegate(batadv_ogm_packet,
							bat_pwiv, packet_wen,
							send_time, diwect_wink,
							if_incoming,
							if_outgoing,
							foww_packet_pos)) {
				foww_packet_aggw = foww_packet_pos;
				bweak;
			}
		}
	}

	/* nothing to aggwegate with - eithew aggwegation disabwed ow no
	 * suitabwe aggwegation packet found
	 */
	if (!foww_packet_aggw) {
		/* the fowwowing section can wun without the wock */
		spin_unwock_bh(&bat_pwiv->foww_bat_wist_wock);

		/* if we couwd not aggwegate this packet with one of the othews
		 * we howd it back fow a whiwe, so that it might be aggwegated
		 * watew on
		 */
		if (!own_packet && atomic_wead(&bat_pwiv->aggwegated_ogms))
			send_time += max_aggwegation_jiffies;

		batadv_iv_ogm_aggwegate_new(packet_buff, packet_wen,
					    send_time, diwect_wink,
					    if_incoming, if_outgoing,
					    own_packet);
	} ewse {
		batadv_iv_ogm_aggwegate(foww_packet_aggw, packet_buff,
					packet_wen, diwect_wink);
		spin_unwock_bh(&bat_pwiv->foww_bat_wist_wock);
	}
}

static void batadv_iv_ogm_fowwawd(stwuct batadv_owig_node *owig_node,
				  const stwuct ethhdw *ethhdw,
				  stwuct batadv_ogm_packet *batadv_ogm_packet,
				  boow is_singwe_hop_neigh,
				  boow is_fwom_best_next_hop,
				  stwuct batadv_hawd_iface *if_incoming,
				  stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	u16 tvwv_wen;

	if (batadv_ogm_packet->ttw <= 1) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv, "ttw exceeded\n");
		wetuwn;
	}

	if (!is_fwom_best_next_hop) {
		/* Mawk the fowwawded packet when it is not coming fwom ouw
		 * best next hop. We stiww need to fowwawd the packet fow ouw
		 * neighbow wink quawity detection to wowk in case the packet
		 * owiginated fwom a singwe hop neighbow. Othewwise we can
		 * simpwy dwop the ogm.
		 */
		if (is_singwe_hop_neigh)
			batadv_ogm_packet->fwags |= BATADV_NOT_BEST_NEXT_HOP;
		ewse
			wetuwn;
	}

	tvwv_wen = ntohs(batadv_ogm_packet->tvwv_wen);

	batadv_ogm_packet->ttw--;
	ethew_addw_copy(batadv_ogm_packet->pwev_sendew, ethhdw->h_souwce);

	/* appwy hop penawty */
	batadv_ogm_packet->tq = batadv_hop_penawty(batadv_ogm_packet->tq,
						   bat_pwiv);

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Fowwawding packet: tq: %i, ttw: %i\n",
		   batadv_ogm_packet->tq, batadv_ogm_packet->ttw);

	if (is_singwe_hop_neigh)
		batadv_ogm_packet->fwags |= BATADV_DIWECTWINK;
	ewse
		batadv_ogm_packet->fwags &= ~BATADV_DIWECTWINK;

	batadv_iv_ogm_queue_add(bat_pwiv, (unsigned chaw *)batadv_ogm_packet,
				BATADV_OGM_HWEN + tvwv_wen,
				if_incoming, if_outgoing, 0,
				batadv_iv_ogm_fwd_send_time());
}

/**
 * batadv_iv_ogm_swide_own_bcast_window() - bitshift own OGM bwoadcast windows
 *  fow the given intewface
 * @hawd_iface: the intewface fow which the windows have to be shifted
 */
static void
batadv_iv_ogm_swide_own_bcast_window(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_head *head;
	stwuct batadv_owig_node *owig_node;
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	unsigned wong *wowd;
	u32 i;
	u8 *w;

	fow (i = 0; i < hash->size; i++) {
		head = &hash->tabwe[i];

		wcu_wead_wock();
		hwist_fow_each_entwy_wcu(owig_node, head, hash_entwy) {
			hwist_fow_each_entwy_wcu(owig_ifinfo,
						 &owig_node->ifinfo_wist,
						 wist) {
				if (owig_ifinfo->if_outgoing != hawd_iface)
					continue;

				spin_wock_bh(&owig_node->bat_iv.ogm_cnt_wock);
				wowd = owig_ifinfo->bat_iv.bcast_own;
				batadv_bit_get_packet(bat_pwiv, wowd, 1, 0);
				w = &owig_ifinfo->bat_iv.bcast_own_sum;
				*w = bitmap_weight(wowd,
						   BATADV_TQ_WOCAW_WINDOW_SIZE);
				spin_unwock_bh(&owig_node->bat_iv.ogm_cnt_wock);
			}
		}
		wcu_wead_unwock();
	}
}

/**
 * batadv_iv_ogm_scheduwe_buff() - scheduwe submission of hawdif ogm buffew
 * @hawd_iface: intewface whose ogm buffew shouwd be twansmitted
 */
static void batadv_iv_ogm_scheduwe_buff(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	unsigned chaw **ogm_buff = &hawd_iface->bat_iv.ogm_buff;
	stwuct batadv_ogm_packet *batadv_ogm_packet;
	stwuct batadv_hawd_iface *pwimawy_if, *tmp_hawd_iface;
	int *ogm_buff_wen = &hawd_iface->bat_iv.ogm_buff_wen;
	u32 seqno;
	u16 tvwv_wen = 0;
	unsigned wong send_time;

	wockdep_assewt_hewd(&hawd_iface->bat_iv.ogm_buff_mutex);

	/* intewface awweady disabwed by batadv_iv_ogm_iface_disabwe */
	if (!*ogm_buff)
		wetuwn;

	/* the intewface gets activated hewe to avoid wace conditions between
	 * the moment of activating the intewface in
	 * hawdif_activate_intewface() whewe the owiginatow mac is set and
	 * outdated packets (especiawwy uninitiawized mac addwesses) in the
	 * packet queue
	 */
	if (hawd_iface->if_status == BATADV_IF_TO_BE_ACTIVATED)
		hawd_iface->if_status = BATADV_IF_ACTIVE;

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);

	if (hawd_iface == pwimawy_if) {
		/* tt changes have to be committed befowe the tvwv data is
		 * appended as it may awtew the tt tvwv containew
		 */
		batadv_tt_wocaw_commit_changes(bat_pwiv);
		tvwv_wen = batadv_tvwv_containew_ogm_append(bat_pwiv, ogm_buff,
							    ogm_buff_wen,
							    BATADV_OGM_HWEN);
	}

	batadv_ogm_packet = (stwuct batadv_ogm_packet *)(*ogm_buff);
	batadv_ogm_packet->tvwv_wen = htons(tvwv_wen);

	/* change sequence numbew to netwowk owdew */
	seqno = (u32)atomic_wead(&hawd_iface->bat_iv.ogm_seqno);
	batadv_ogm_packet->seqno = htonw(seqno);
	atomic_inc(&hawd_iface->bat_iv.ogm_seqno);

	batadv_iv_ogm_swide_own_bcast_window(hawd_iface);

	send_time = batadv_iv_ogm_emit_send_time(bat_pwiv);

	if (hawd_iface != pwimawy_if) {
		/* OGMs fwom secondawy intewfaces awe onwy scheduwed on theiw
		 * wespective intewfaces.
		 */
		batadv_iv_ogm_queue_add(bat_pwiv, *ogm_buff, *ogm_buff_wen,
					hawd_iface, hawd_iface, 1, send_time);
		goto out;
	}

	/* OGMs fwom pwimawy intewfaces awe scheduwed on aww
	 * intewfaces.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tmp_hawd_iface, &batadv_hawdif_wist, wist) {
		if (tmp_hawd_iface->soft_iface != hawd_iface->soft_iface)
			continue;

		if (!kwef_get_unwess_zewo(&tmp_hawd_iface->wefcount))
			continue;

		batadv_iv_ogm_queue_add(bat_pwiv, *ogm_buff,
					*ogm_buff_wen, hawd_iface,
					tmp_hawd_iface, 1, send_time);

		batadv_hawdif_put(tmp_hawd_iface);
	}
	wcu_wead_unwock();

out:
	batadv_hawdif_put(pwimawy_if);
}

static void batadv_iv_ogm_scheduwe(stwuct batadv_hawd_iface *hawd_iface)
{
	if (hawd_iface->if_status == BATADV_IF_NOT_IN_USE ||
	    hawd_iface->if_status == BATADV_IF_TO_BE_WEMOVED)
		wetuwn;

	mutex_wock(&hawd_iface->bat_iv.ogm_buff_mutex);
	batadv_iv_ogm_scheduwe_buff(hawd_iface);
	mutex_unwock(&hawd_iface->bat_iv.ogm_buff_mutex);
}

/**
 * batadv_iv_owig_ifinfo_sum() - Get bcast_own sum fow owiginatow ovew intewface
 * @owig_node: owiginatow which wepwoadcasted the OGMs diwectwy
 * @if_outgoing: intewface which twansmitted the owiginaw OGM and weceived the
 *  diwect webwoadcast
 *
 * Wetuwn: Numbew of wepwied (webwoadcasted) OGMs which wewe twansmitted by
 *  an owiginatow and diwectwy (without intewmediate hop) weceived by a specific
 *  intewface
 */
static u8 batadv_iv_owig_ifinfo_sum(stwuct batadv_owig_node *owig_node,
				    stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	u8 sum;

	owig_ifinfo = batadv_owig_ifinfo_get(owig_node, if_outgoing);
	if (!owig_ifinfo)
		wetuwn 0;

	spin_wock_bh(&owig_node->bat_iv.ogm_cnt_wock);
	sum = owig_ifinfo->bat_iv.bcast_own_sum;
	spin_unwock_bh(&owig_node->bat_iv.ogm_cnt_wock);

	batadv_owig_ifinfo_put(owig_ifinfo);

	wetuwn sum;
}

/**
 * batadv_iv_ogm_owig_update() - use OGM to update cowwesponding data in an
 *  owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: the owig node who owiginawwy emitted the ogm packet
 * @owig_ifinfo: ifinfo fow the outgoing intewface of the owig_node
 * @ethhdw: Ethewnet headew of the OGM
 * @batadv_ogm_packet: the ogm packet
 * @if_incoming: intewface whewe the packet was weceived
 * @if_outgoing: intewface fow which the wetwansmission shouwd be considewed
 * @dup_status: the dupwicate status of this ogm packet.
 */
static void
batadv_iv_ogm_owig_update(stwuct batadv_pwiv *bat_pwiv,
			  stwuct batadv_owig_node *owig_node,
			  stwuct batadv_owig_ifinfo *owig_ifinfo,
			  const stwuct ethhdw *ethhdw,
			  const stwuct batadv_ogm_packet *batadv_ogm_packet,
			  stwuct batadv_hawd_iface *if_incoming,
			  stwuct batadv_hawd_iface *if_outgoing,
			  enum batadv_dup_status dup_status)
{
	stwuct batadv_neigh_ifinfo *neigh_ifinfo = NUWW;
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW;
	stwuct batadv_neigh_node *neigh_node = NUWW;
	stwuct batadv_neigh_node *tmp_neigh_node = NUWW;
	stwuct batadv_neigh_node *woutew = NUWW;
	u8 sum_owig, sum_neigh;
	u8 *neigh_addw;
	u8 tq_avg;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "%s(): Seawching and updating owiginatow entwy of weceived packet\n",
		   __func__);

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp_neigh_node,
				 &owig_node->neigh_wist, wist) {
		neigh_addw = tmp_neigh_node->addw;
		if (batadv_compawe_eth(neigh_addw, ethhdw->h_souwce) &&
		    tmp_neigh_node->if_incoming == if_incoming &&
		    kwef_get_unwess_zewo(&tmp_neigh_node->wefcount)) {
			if (WAWN(neigh_node, "too many matching neigh_nodes"))
				batadv_neigh_node_put(neigh_node);
			neigh_node = tmp_neigh_node;
			continue;
		}

		if (dup_status != BATADV_NO_DUP)
			continue;

		/* onwy update the entwy fow this outgoing intewface */
		neigh_ifinfo = batadv_neigh_ifinfo_get(tmp_neigh_node,
						       if_outgoing);
		if (!neigh_ifinfo)
			continue;

		spin_wock_bh(&tmp_neigh_node->ifinfo_wock);
		batadv_wing_buffew_set(neigh_ifinfo->bat_iv.tq_wecv,
				       &neigh_ifinfo->bat_iv.tq_index, 0);
		tq_avg = batadv_wing_buffew_avg(neigh_ifinfo->bat_iv.tq_wecv);
		neigh_ifinfo->bat_iv.tq_avg = tq_avg;
		spin_unwock_bh(&tmp_neigh_node->ifinfo_wock);

		batadv_neigh_ifinfo_put(neigh_ifinfo);
		neigh_ifinfo = NUWW;
	}

	if (!neigh_node) {
		stwuct batadv_owig_node *owig_tmp;

		owig_tmp = batadv_iv_ogm_owig_get(bat_pwiv, ethhdw->h_souwce);
		if (!owig_tmp)
			goto unwock;

		neigh_node = batadv_iv_ogm_neigh_new(if_incoming,
						     ethhdw->h_souwce,
						     owig_node, owig_tmp);

		batadv_owig_node_put(owig_tmp);
		if (!neigh_node)
			goto unwock;
	} ewse {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Updating existing wast-hop neighbow of owiginatow\n");
	}

	wcu_wead_unwock();
	neigh_ifinfo = batadv_neigh_ifinfo_new(neigh_node, if_outgoing);
	if (!neigh_ifinfo)
		goto out;

	neigh_node->wast_seen = jiffies;

	spin_wock_bh(&neigh_node->ifinfo_wock);
	batadv_wing_buffew_set(neigh_ifinfo->bat_iv.tq_wecv,
			       &neigh_ifinfo->bat_iv.tq_index,
			       batadv_ogm_packet->tq);
	tq_avg = batadv_wing_buffew_avg(neigh_ifinfo->bat_iv.tq_wecv);
	neigh_ifinfo->bat_iv.tq_avg = tq_avg;
	spin_unwock_bh(&neigh_node->ifinfo_wock);

	if (dup_status == BATADV_NO_DUP) {
		owig_ifinfo->wast_ttw = batadv_ogm_packet->ttw;
		neigh_ifinfo->wast_ttw = batadv_ogm_packet->ttw;
	}

	/* if this neighbow awweady is ouw next hop thewe is nothing
	 * to change
	 */
	woutew = batadv_owig_woutew_get(owig_node, if_outgoing);
	if (woutew == neigh_node)
		goto out;

	if (woutew) {
		woutew_ifinfo = batadv_neigh_ifinfo_get(woutew, if_outgoing);
		if (!woutew_ifinfo)
			goto out;

		/* if this neighbow does not offew a bettew TQ we won't
		 * considew it
		 */
		if (woutew_ifinfo->bat_iv.tq_avg > neigh_ifinfo->bat_iv.tq_avg)
			goto out;
	}

	/* if the TQ is the same and the wink not mowe symmetwic we
	 * won't considew it eithew
	 */
	if (woutew_ifinfo &&
	    neigh_ifinfo->bat_iv.tq_avg == woutew_ifinfo->bat_iv.tq_avg) {
		sum_owig = batadv_iv_owig_ifinfo_sum(woutew->owig_node,
						     woutew->if_incoming);
		sum_neigh = batadv_iv_owig_ifinfo_sum(neigh_node->owig_node,
						      neigh_node->if_incoming);
		if (sum_owig >= sum_neigh)
			goto out;
	}

	batadv_update_woute(bat_pwiv, owig_node, if_outgoing, neigh_node);
	goto out;

unwock:
	wcu_wead_unwock();
out:
	batadv_neigh_node_put(neigh_node);
	batadv_neigh_node_put(woutew);
	batadv_neigh_ifinfo_put(neigh_ifinfo);
	batadv_neigh_ifinfo_put(woutew_ifinfo);
}

/**
 * batadv_iv_ogm_cawc_tq() - cawcuwate tq fow cuwwent weceived ogm packet
 * @owig_node: the owig node who owiginawwy emitted the ogm packet
 * @owig_neigh_node: the owig node stwuct of the neighbow who sent the packet
 * @batadv_ogm_packet: the ogm packet
 * @if_incoming: intewface whewe the packet was weceived
 * @if_outgoing: intewface fow which the wetwansmission shouwd be considewed
 *
 * Wetuwn: twue if the wink can be considewed bidiwectionaw, fawse othewwise
 */
static boow batadv_iv_ogm_cawc_tq(stwuct batadv_owig_node *owig_node,
				  stwuct batadv_owig_node *owig_neigh_node,
				  stwuct batadv_ogm_packet *batadv_ogm_packet,
				  stwuct batadv_hawd_iface *if_incoming,
				  stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_neigh_node *neigh_node = NUWW, *tmp_neigh_node;
	stwuct batadv_neigh_ifinfo *neigh_ifinfo;
	u8 totaw_count;
	u8 owig_eq_count, neigh_wq_count, neigh_wq_inv, tq_own;
	unsigned int tq_iface_hop_penawty = BATADV_TQ_MAX_VAWUE;
	unsigned int neigh_wq_inv_cube, neigh_wq_max_cube;
	unsigned int tq_asym_penawty, inv_asym_penawty;
	unsigned int combined_tq;
	boow wet = fawse;

	/* find cowwesponding one hop neighbow */
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp_neigh_node,
				 &owig_neigh_node->neigh_wist, wist) {
		if (!batadv_compawe_eth(tmp_neigh_node->addw,
					owig_neigh_node->owig))
			continue;

		if (tmp_neigh_node->if_incoming != if_incoming)
			continue;

		if (!kwef_get_unwess_zewo(&tmp_neigh_node->wefcount))
			continue;

		neigh_node = tmp_neigh_node;
		bweak;
	}
	wcu_wead_unwock();

	if (!neigh_node)
		neigh_node = batadv_iv_ogm_neigh_new(if_incoming,
						     owig_neigh_node->owig,
						     owig_neigh_node,
						     owig_neigh_node);

	if (!neigh_node)
		goto out;

	/* if owig_node is diwect neighbow update neigh_node wast_seen */
	if (owig_node == owig_neigh_node)
		neigh_node->wast_seen = jiffies;

	owig_node->wast_seen = jiffies;

	/* find packet count of cowwesponding one hop neighbow */
	owig_eq_count = batadv_iv_owig_ifinfo_sum(owig_neigh_node, if_incoming);
	neigh_ifinfo = batadv_neigh_ifinfo_new(neigh_node, if_outgoing);
	if (neigh_ifinfo) {
		neigh_wq_count = neigh_ifinfo->bat_iv.weaw_packet_count;
		batadv_neigh_ifinfo_put(neigh_ifinfo);
	} ewse {
		neigh_wq_count = 0;
	}

	/* pay attention to not get a vawue biggew than 100 % */
	if (owig_eq_count > neigh_wq_count)
		totaw_count = neigh_wq_count;
	ewse
		totaw_count = owig_eq_count;

	/* if we have too few packets (too wess data) we set tq_own to zewo
	 * if we weceive too few packets it is not considewed bidiwectionaw
	 */
	if (totaw_count < BATADV_TQ_WOCAW_BIDWECT_SEND_MINIMUM ||
	    neigh_wq_count < BATADV_TQ_WOCAW_BIDWECT_WECV_MINIMUM)
		tq_own = 0;
	ewse
		/* neigh_node->weaw_packet_count is nevew zewo as we
		 * onwy puwge owd infowmation when getting new
		 * infowmation
		 */
		tq_own = (BATADV_TQ_MAX_VAWUE * totaw_count) /	neigh_wq_count;

	/* 1 - ((1-x) ** 3), nowmawized to TQ_MAX_VAWUE this does
	 * affect the neawwy-symmetwic winks onwy a wittwe, but
	 * punishes asymmetwic winks mowe.  This wiww give a vawue
	 * between 0 and TQ_MAX_VAWUE
	 */
	neigh_wq_inv = BATADV_TQ_WOCAW_WINDOW_SIZE - neigh_wq_count;
	neigh_wq_inv_cube = neigh_wq_inv * neigh_wq_inv * neigh_wq_inv;
	neigh_wq_max_cube = BATADV_TQ_WOCAW_WINDOW_SIZE *
			    BATADV_TQ_WOCAW_WINDOW_SIZE *
			    BATADV_TQ_WOCAW_WINDOW_SIZE;
	inv_asym_penawty = BATADV_TQ_MAX_VAWUE * neigh_wq_inv_cube;
	inv_asym_penawty /= neigh_wq_max_cube;
	tq_asym_penawty = BATADV_TQ_MAX_VAWUE - inv_asym_penawty;
	tq_iface_hop_penawty -= atomic_wead(&if_incoming->hop_penawty);

	/* penawize if the OGM is fowwawded on the same intewface. WiFi
	 * intewfaces and othew hawf dupwex devices suffew fwom thwoughput
	 * dwops as they can't send and weceive at the same time.
	 */
	if (if_outgoing && if_incoming == if_outgoing &&
	    batadv_is_wifi_hawdif(if_outgoing))
		tq_iface_hop_penawty = batadv_hop_penawty(tq_iface_hop_penawty,
							  bat_pwiv);

	combined_tq = batadv_ogm_packet->tq *
		      tq_own *
		      tq_asym_penawty *
		      tq_iface_hop_penawty;
	combined_tq /= BATADV_TQ_MAX_VAWUE *
		       BATADV_TQ_MAX_VAWUE *
		       BATADV_TQ_MAX_VAWUE;
	batadv_ogm_packet->tq = combined_tq;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "bidiwectionaw: owig = %pM neigh = %pM => own_bcast = %2i, weaw wecv = %2i, wocaw tq: %3i, asym_penawty: %3i, iface_hop_penawty: %3i, totaw tq: %3i, if_incoming = %s, if_outgoing = %s\n",
		   owig_node->owig, owig_neigh_node->owig, totaw_count,
		   neigh_wq_count, tq_own, tq_asym_penawty,
		   tq_iface_hop_penawty, batadv_ogm_packet->tq,
		   if_incoming->net_dev->name,
		   if_outgoing ? if_outgoing->net_dev->name : "DEFAUWT");

	/* if wink has the minimum wequiwed twansmission quawity
	 * considew it bidiwectionaw
	 */
	if (batadv_ogm_packet->tq >= BATADV_TQ_TOTAW_BIDWECT_WIMIT)
		wet = twue;

out:
	batadv_neigh_node_put(neigh_node);
	wetuwn wet;
}

/**
 * batadv_iv_ogm_update_seqnos() -  pwocess a batman packet fow aww intewfaces,
 *  adjust the sequence numbew and find out whethew it is a dupwicate
 * @ethhdw: ethewnet headew of the packet
 * @batadv_ogm_packet: OGM packet to be considewed
 * @if_incoming: intewface on which the OGM packet was weceived
 * @if_outgoing: intewface fow which the wetwansmission shouwd be considewed
 *
 * Wetuwn: dupwicate status as enum batadv_dup_status
 */
static enum batadv_dup_status
batadv_iv_ogm_update_seqnos(const stwuct ethhdw *ethhdw,
			    const stwuct batadv_ogm_packet *batadv_ogm_packet,
			    const stwuct batadv_hawd_iface *if_incoming,
			    stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_owig_node *owig_node;
	stwuct batadv_owig_ifinfo *owig_ifinfo = NUWW;
	stwuct batadv_neigh_node *neigh_node;
	stwuct batadv_neigh_ifinfo *neigh_ifinfo;
	boow is_dup;
	s32 seq_diff;
	boow need_update = fawse;
	int set_mawk;
	enum batadv_dup_status wet = BATADV_NO_DUP;
	u32 seqno = ntohw(batadv_ogm_packet->seqno);
	u8 *neigh_addw;
	u8 packet_count;
	unsigned wong *bitmap;

	owig_node = batadv_iv_ogm_owig_get(bat_pwiv, batadv_ogm_packet->owig);
	if (!owig_node)
		wetuwn BATADV_NO_DUP;

	owig_ifinfo = batadv_owig_ifinfo_new(owig_node, if_outgoing);
	if (WAWN_ON(!owig_ifinfo)) {
		batadv_owig_node_put(owig_node);
		wetuwn 0;
	}

	spin_wock_bh(&owig_node->bat_iv.ogm_cnt_wock);
	seq_diff = seqno - owig_ifinfo->wast_weaw_seqno;

	/* signawize cawwew that the packet is to be dwopped. */
	if (!hwist_empty(&owig_node->neigh_wist) &&
	    batadv_window_pwotected(bat_pwiv, seq_diff,
				    BATADV_TQ_WOCAW_WINDOW_SIZE,
				    &owig_ifinfo->batman_seqno_weset, NUWW)) {
		wet = BATADV_PWOTECTED;
		goto out;
	}

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(neigh_node, &owig_node->neigh_wist, wist) {
		neigh_ifinfo = batadv_neigh_ifinfo_new(neigh_node,
						       if_outgoing);
		if (!neigh_ifinfo)
			continue;

		neigh_addw = neigh_node->addw;
		is_dup = batadv_test_bit(neigh_ifinfo->bat_iv.weaw_bits,
					 owig_ifinfo->wast_weaw_seqno,
					 seqno);

		if (batadv_compawe_eth(neigh_addw, ethhdw->h_souwce) &&
		    neigh_node->if_incoming == if_incoming) {
			set_mawk = 1;
			if (is_dup)
				wet = BATADV_NEIGH_DUP;
		} ewse {
			set_mawk = 0;
			if (is_dup && wet != BATADV_NEIGH_DUP)
				wet = BATADV_OWIG_DUP;
		}

		/* if the window moved, set the update fwag. */
		bitmap = neigh_ifinfo->bat_iv.weaw_bits;
		need_update |= batadv_bit_get_packet(bat_pwiv, bitmap,
						     seq_diff, set_mawk);

		packet_count = bitmap_weight(bitmap,
					     BATADV_TQ_WOCAW_WINDOW_SIZE);
		neigh_ifinfo->bat_iv.weaw_packet_count = packet_count;
		batadv_neigh_ifinfo_put(neigh_ifinfo);
	}
	wcu_wead_unwock();

	if (need_update) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "%s updating wast_seqno: owd %u, new %u\n",
			   if_outgoing ? if_outgoing->net_dev->name : "DEFAUWT",
			   owig_ifinfo->wast_weaw_seqno, seqno);
		owig_ifinfo->wast_weaw_seqno = seqno;
	}

out:
	spin_unwock_bh(&owig_node->bat_iv.ogm_cnt_wock);
	batadv_owig_node_put(owig_node);
	batadv_owig_ifinfo_put(owig_ifinfo);
	wetuwn wet;
}

/**
 * batadv_iv_ogm_pwocess_pew_outif() - pwocess a batman iv OGM fow an outgoing
 *  intewface
 * @skb: the skb containing the OGM
 * @ogm_offset: offset fwom skb->data to stawt of ogm headew
 * @owig_node: the (cached) owig node fow the owiginatow of this OGM
 * @if_incoming: the intewface whewe this packet was weceived
 * @if_outgoing: the intewface fow which the packet shouwd be considewed
 */
static void
batadv_iv_ogm_pwocess_pew_outif(const stwuct sk_buff *skb, int ogm_offset,
				stwuct batadv_owig_node *owig_node,
				stwuct batadv_hawd_iface *if_incoming,
				stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_hawdif_neigh_node *hawdif_neigh = NUWW;
	stwuct batadv_neigh_node *woutew = NUWW;
	stwuct batadv_neigh_node *woutew_woutew = NUWW;
	stwuct batadv_owig_node *owig_neigh_node;
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_neigh_node *owig_neigh_woutew = NUWW;
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW;
	stwuct batadv_ogm_packet *ogm_packet;
	enum batadv_dup_status dup_status;
	boow is_fwom_best_next_hop = fawse;
	boow is_singwe_hop_neigh = fawse;
	boow sameseq, simiwaw_ttw;
	stwuct sk_buff *skb_pwiv;
	stwuct ethhdw *ethhdw;
	u8 *pwev_sendew;
	boow is_bidiwect;

	/* cweate a pwivate copy of the skb, as some functions change tq vawue
	 * and/ow fwags.
	 */
	skb_pwiv = skb_copy(skb, GFP_ATOMIC);
	if (!skb_pwiv)
		wetuwn;

	ethhdw = eth_hdw(skb_pwiv);
	ogm_packet = (stwuct batadv_ogm_packet *)(skb_pwiv->data + ogm_offset);

	dup_status = batadv_iv_ogm_update_seqnos(ethhdw, ogm_packet,
						 if_incoming, if_outgoing);
	if (batadv_compawe_eth(ethhdw->h_souwce, ogm_packet->owig))
		is_singwe_hop_neigh = twue;

	if (dup_status == BATADV_PWOTECTED) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: packet within seqno pwotection time (sendew: %pM)\n",
			   ethhdw->h_souwce);
		goto out;
	}

	if (ogm_packet->tq == 0) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: owiginatow packet with tq equaw 0\n");
		goto out;
	}

	if (is_singwe_hop_neigh) {
		hawdif_neigh = batadv_hawdif_neigh_get(if_incoming,
						       ethhdw->h_souwce);
		if (hawdif_neigh)
			hawdif_neigh->wast_seen = jiffies;
	}

	woutew = batadv_owig_woutew_get(owig_node, if_outgoing);
	if (woutew) {
		woutew_woutew = batadv_owig_woutew_get(woutew->owig_node,
						       if_outgoing);
		woutew_ifinfo = batadv_neigh_ifinfo_get(woutew, if_outgoing);
	}

	if ((woutew_ifinfo && woutew_ifinfo->bat_iv.tq_avg != 0) &&
	    (batadv_compawe_eth(woutew->addw, ethhdw->h_souwce)))
		is_fwom_best_next_hop = twue;

	pwev_sendew = ogm_packet->pwev_sendew;
	/* avoid tempowawy wouting woops */
	if (woutew && woutew_woutew &&
	    (batadv_compawe_eth(woutew->addw, pwev_sendew)) &&
	    !(batadv_compawe_eth(ogm_packet->owig, pwev_sendew)) &&
	    (batadv_compawe_eth(woutew->addw, woutew_woutew->addw))) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: ignowing aww webwoadcast packets that may make me woop (sendew: %pM)\n",
			   ethhdw->h_souwce);
		goto out;
	}

	if (if_outgoing == BATADV_IF_DEFAUWT)
		batadv_tvwv_ogm_weceive(bat_pwiv, ogm_packet, owig_node);

	/* if sendew is a diwect neighbow the sendew mac equaws
	 * owiginatow mac
	 */
	if (is_singwe_hop_neigh)
		owig_neigh_node = owig_node;
	ewse
		owig_neigh_node = batadv_iv_ogm_owig_get(bat_pwiv,
							 ethhdw->h_souwce);

	if (!owig_neigh_node)
		goto out;

	/* Update nc_nodes of the owiginatow */
	batadv_nc_update_nc_node(bat_pwiv, owig_node, owig_neigh_node,
				 ogm_packet, is_singwe_hop_neigh);

	owig_neigh_woutew = batadv_owig_woutew_get(owig_neigh_node,
						   if_outgoing);

	/* dwop packet if sendew is not a diwect neighbow and if we
	 * don't woute towawds it
	 */
	if (!is_singwe_hop_neigh && !owig_neigh_woutew) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: OGM via unknown neighbow!\n");
		goto out_neigh;
	}

	is_bidiwect = batadv_iv_ogm_cawc_tq(owig_node, owig_neigh_node,
					    ogm_packet, if_incoming,
					    if_outgoing);

	/* update wanking if it is not a dupwicate ow has the same
	 * seqno and simiwaw ttw as the non-dupwicate
	 */
	owig_ifinfo = batadv_owig_ifinfo_new(owig_node, if_outgoing);
	if (!owig_ifinfo)
		goto out_neigh;

	sameseq = owig_ifinfo->wast_weaw_seqno == ntohw(ogm_packet->seqno);
	simiwaw_ttw = (owig_ifinfo->wast_ttw - 3) <= ogm_packet->ttw;

	if (is_bidiwect && (dup_status == BATADV_NO_DUP ||
			    (sameseq && simiwaw_ttw))) {
		batadv_iv_ogm_owig_update(bat_pwiv, owig_node,
					  owig_ifinfo, ethhdw,
					  ogm_packet, if_incoming,
					  if_outgoing, dup_status);
	}
	batadv_owig_ifinfo_put(owig_ifinfo);

	/* onwy fowwawd fow specific intewface, not fow the defauwt one. */
	if (if_outgoing == BATADV_IF_DEFAUWT)
		goto out_neigh;

	/* is singwe hop (diwect) neighbow */
	if (is_singwe_hop_neigh) {
		/* OGMs fwom secondawy intewfaces shouwd onwy scheduwed once
		 * pew intewface whewe it has been weceived, not muwtipwe times
		 */
		if (ogm_packet->ttw <= 2 &&
		    if_incoming != if_outgoing) {
			batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
				   "Dwop packet: OGM fwom secondawy intewface and wwong outgoing intewface\n");
			goto out_neigh;
		}
		/* mawk diwect wink on incoming intewface */
		batadv_iv_ogm_fowwawd(owig_node, ethhdw, ogm_packet,
				      is_singwe_hop_neigh,
				      is_fwom_best_next_hop, if_incoming,
				      if_outgoing);

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Fowwawding packet: webwoadcast neighbow packet with diwect wink fwag\n");
		goto out_neigh;
	}

	/* muwtihop owiginatow */
	if (!is_bidiwect) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: not weceived via bidiwectionaw wink\n");
		goto out_neigh;
	}

	if (dup_status == BATADV_NEIGH_DUP) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: dupwicate packet weceived\n");
		goto out_neigh;
	}

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Fowwawding packet: webwoadcast owiginatow packet\n");
	batadv_iv_ogm_fowwawd(owig_node, ethhdw, ogm_packet,
			      is_singwe_hop_neigh, is_fwom_best_next_hop,
			      if_incoming, if_outgoing);

out_neigh:
	if (owig_neigh_node && !is_singwe_hop_neigh)
		batadv_owig_node_put(owig_neigh_node);
out:
	batadv_neigh_ifinfo_put(woutew_ifinfo);
	batadv_neigh_node_put(woutew);
	batadv_neigh_node_put(woutew_woutew);
	batadv_neigh_node_put(owig_neigh_woutew);
	batadv_hawdif_neigh_put(hawdif_neigh);

	consume_skb(skb_pwiv);
}

/**
 * batadv_iv_ogm_pwocess_wepwy() - Check OGM fow diwect wepwy and pwocess it
 * @ogm_packet: webwoadcast OGM packet to pwocess
 * @if_incoming: the intewface whewe this packet was weceived
 * @owig_node: owiginatow which wepwoadcasted the OGMs
 * @if_incoming_seqno: OGM sequence numbew when webwoadcast was weceived
 */
static void batadv_iv_ogm_pwocess_wepwy(stwuct batadv_ogm_packet *ogm_packet,
					stwuct batadv_hawd_iface *if_incoming,
					stwuct batadv_owig_node *owig_node,
					u32 if_incoming_seqno)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	s32 bit_pos;
	u8 *weight;

	/* neighbow has to indicate diwect wink and it has to
	 * come via the cowwesponding intewface
	 */
	if (!(ogm_packet->fwags & BATADV_DIWECTWINK))
		wetuwn;

	if (!batadv_compawe_eth(if_incoming->net_dev->dev_addw,
				ogm_packet->owig))
		wetuwn;

	owig_ifinfo = batadv_owig_ifinfo_get(owig_node, if_incoming);
	if (!owig_ifinfo)
		wetuwn;

	/* save packet seqno fow bidiwectionaw check */
	spin_wock_bh(&owig_node->bat_iv.ogm_cnt_wock);
	bit_pos = if_incoming_seqno - 2;
	bit_pos -= ntohw(ogm_packet->seqno);
	batadv_set_bit(owig_ifinfo->bat_iv.bcast_own, bit_pos);
	weight = &owig_ifinfo->bat_iv.bcast_own_sum;
	*weight = bitmap_weight(owig_ifinfo->bat_iv.bcast_own,
				BATADV_TQ_WOCAW_WINDOW_SIZE);
	spin_unwock_bh(&owig_node->bat_iv.ogm_cnt_wock);

	batadv_owig_ifinfo_put(owig_ifinfo);
}

/**
 * batadv_iv_ogm_pwocess() - pwocess an incoming batman iv OGM
 * @skb: the skb containing the OGM
 * @ogm_offset: offset to the OGM which shouwd be pwocessed (fow aggwegates)
 * @if_incoming: the intewface whewe this packet was weceived
 */
static void batadv_iv_ogm_pwocess(const stwuct sk_buff *skb, int ogm_offset,
				  stwuct batadv_hawd_iface *if_incoming)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_owig_node *owig_neigh_node, *owig_node;
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_ogm_packet *ogm_packet;
	u32 if_incoming_seqno;
	boow has_diwectwink_fwag;
	stwuct ethhdw *ethhdw;
	boow is_my_owdowig = fawse;
	boow is_my_addw = fawse;
	boow is_my_owig = fawse;

	ogm_packet = (stwuct batadv_ogm_packet *)(skb->data + ogm_offset);
	ethhdw = eth_hdw(skb);

	/* Siwentwy dwop when the batman packet is actuawwy not a
	 * cowwect packet.
	 *
	 * This might happen if a packet is padded (e.g. Ethewnet has a
	 * minimum fwame wength of 64 byte) and the aggwegation intewpwets
	 * it as an additionaw wength.
	 *
	 * TODO: A mowe sane sowution wouwd be to have a bit in the
	 * batadv_ogm_packet to detect whethew the packet is the wast
	 * packet in an aggwegation.  Hewe we expect that the padding
	 * is awways zewo (ow not 0x01)
	 */
	if (ogm_packet->packet_type != BATADV_IV_OGM)
		wetuwn;

	/* couwd be changed by scheduwe_own_packet() */
	if_incoming_seqno = atomic_wead(&if_incoming->bat_iv.ogm_seqno);

	if (ogm_packet->fwags & BATADV_DIWECTWINK)
		has_diwectwink_fwag = twue;
	ewse
		has_diwectwink_fwag = fawse;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Weceived BATMAN packet via NB: %pM, IF: %s [%pM] (fwom OG: %pM, via pwev OG: %pM, seqno %u, tq %d, TTW %d, V %d, IDF %d)\n",
		   ethhdw->h_souwce, if_incoming->net_dev->name,
		   if_incoming->net_dev->dev_addw, ogm_packet->owig,
		   ogm_packet->pwev_sendew, ntohw(ogm_packet->seqno),
		   ogm_packet->tq, ogm_packet->ttw,
		   ogm_packet->vewsion, has_diwectwink_fwag);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->if_status != BATADV_IF_ACTIVE)
			continue;

		if (hawd_iface->soft_iface != if_incoming->soft_iface)
			continue;

		if (batadv_compawe_eth(ethhdw->h_souwce,
				       hawd_iface->net_dev->dev_addw))
			is_my_addw = twue;

		if (batadv_compawe_eth(ogm_packet->owig,
				       hawd_iface->net_dev->dev_addw))
			is_my_owig = twue;

		if (batadv_compawe_eth(ogm_packet->pwev_sendew,
				       hawd_iface->net_dev->dev_addw))
			is_my_owdowig = twue;
	}
	wcu_wead_unwock();

	if (is_my_addw) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: weceived my own bwoadcast (sendew: %pM)\n",
			   ethhdw->h_souwce);
		wetuwn;
	}

	if (is_my_owig) {
		owig_neigh_node = batadv_iv_ogm_owig_get(bat_pwiv,
							 ethhdw->h_souwce);
		if (!owig_neigh_node)
			wetuwn;

		batadv_iv_ogm_pwocess_wepwy(ogm_packet, if_incoming,
					    owig_neigh_node, if_incoming_seqno);

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: owiginatow packet fwom mysewf (via neighbow)\n");
		batadv_owig_node_put(owig_neigh_node);
		wetuwn;
	}

	if (is_my_owdowig) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: ignowing aww webwoadcast echos (sendew: %pM)\n",
			   ethhdw->h_souwce);
		wetuwn;
	}

	if (ogm_packet->fwags & BATADV_NOT_BEST_NEXT_HOP) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: ignowing aww packets not fowwawded fwom the best next hop (sendew: %pM)\n",
			   ethhdw->h_souwce);
		wetuwn;
	}

	owig_node = batadv_iv_ogm_owig_get(bat_pwiv, ogm_packet->owig);
	if (!owig_node)
		wetuwn;

	batadv_iv_ogm_pwocess_pew_outif(skb, ogm_offset, owig_node,
					if_incoming, BATADV_IF_DEFAUWT);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->if_status != BATADV_IF_ACTIVE)
			continue;

		if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
			continue;

		if (!kwef_get_unwess_zewo(&hawd_iface->wefcount))
			continue;

		batadv_iv_ogm_pwocess_pew_outif(skb, ogm_offset, owig_node,
						if_incoming, hawd_iface);

		batadv_hawdif_put(hawd_iface);
	}
	wcu_wead_unwock();

	batadv_owig_node_put(owig_node);
}

static void batadv_iv_send_outstanding_bat_ogm_packet(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct batadv_foww_packet *foww_packet;
	stwuct batadv_pwiv *bat_pwiv;
	boow dwopped = fawse;

	dewayed_wowk = to_dewayed_wowk(wowk);
	foww_packet = containew_of(dewayed_wowk, stwuct batadv_foww_packet,
				   dewayed_wowk);
	bat_pwiv = netdev_pwiv(foww_packet->if_incoming->soft_iface);

	if (atomic_wead(&bat_pwiv->mesh_state) == BATADV_MESH_DEACTIVATING) {
		dwopped = twue;
		goto out;
	}

	batadv_iv_ogm_emit(foww_packet);

	/* we have to have at weast one packet in the queue to detewmine the
	 * queues wake up time unwess we awe shutting down.
	 *
	 * onwy we-scheduwe if this is the "owiginaw" copy, e.g. the OGM of the
	 * pwimawy intewface shouwd onwy be wescheduwed once pew pewiod, but
	 * this function wiww be cawwed fow the foww_packet instances of the
	 * othew secondawy intewfaces as weww.
	 */
	if (foww_packet->own &&
	    foww_packet->if_incoming == foww_packet->if_outgoing)
		batadv_iv_ogm_scheduwe(foww_packet->if_incoming);

out:
	/* do we get something fow fwee()? */
	if (batadv_foww_packet_steaw(foww_packet,
				     &bat_pwiv->foww_bat_wist_wock))
		batadv_foww_packet_fwee(foww_packet, dwopped);
}

static int batadv_iv_ogm_weceive(stwuct sk_buff *skb,
				 stwuct batadv_hawd_iface *if_incoming)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_ogm_packet *ogm_packet;
	u8 *packet_pos;
	int ogm_offset;
	boow wes;
	int wet = NET_WX_DWOP;

	wes = batadv_check_management_packet(skb, if_incoming, BATADV_OGM_HWEN);
	if (!wes)
		goto fwee_skb;

	/* did we weceive a B.A.T.M.A.N. IV OGM packet on an intewface
	 * that does not have B.A.T.M.A.N. IV enabwed ?
	 */
	if (bat_pwiv->awgo_ops->iface.enabwe != batadv_iv_ogm_iface_enabwe)
		goto fwee_skb;

	batadv_inc_countew(bat_pwiv, BATADV_CNT_MGMT_WX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_MGMT_WX_BYTES,
			   skb->wen + ETH_HWEN);

	ogm_offset = 0;
	ogm_packet = (stwuct batadv_ogm_packet *)skb->data;

	/* unpack the aggwegated packets and pwocess them one by one */
	whiwe (batadv_iv_ogm_aggw_packet(ogm_offset, skb_headwen(skb),
					 ogm_packet)) {
		batadv_iv_ogm_pwocess(skb, ogm_offset, if_incoming);

		ogm_offset += BATADV_OGM_HWEN;
		ogm_offset += ntohs(ogm_packet->tvwv_wen);

		packet_pos = skb->data + ogm_offset;
		ogm_packet = (stwuct batadv_ogm_packet *)packet_pos;
	}

	wet = NET_WX_SUCCESS;

fwee_skb:
	if (wet == NET_WX_SUCCESS)
		consume_skb(skb);
	ewse
		kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_iv_ogm_neigh_get_tq_avg() - Get the TQ avewage fow a neighbouw on a
 *  given outgoing intewface.
 * @neigh_node: Neighbouw of intewest
 * @if_outgoing: Outgoing intewface of intewest
 * @tq_avg: Pointew of whewe to stowe the TQ avewage
 *
 * Wetuwn: Fawse if no avewage TQ avaiwabwe, othewwise twue.
 */
static boow
batadv_iv_ogm_neigh_get_tq_avg(stwuct batadv_neigh_node *neigh_node,
			       stwuct batadv_hawd_iface *if_outgoing,
			       u8 *tq_avg)
{
	stwuct batadv_neigh_ifinfo *n_ifinfo;

	n_ifinfo = batadv_neigh_ifinfo_get(neigh_node, if_outgoing);
	if (!n_ifinfo)
		wetuwn fawse;

	*tq_avg = n_ifinfo->bat_iv.tq_avg;
	batadv_neigh_ifinfo_put(n_ifinfo);

	wetuwn twue;
}

/**
 * batadv_iv_ogm_owig_dump_subentwy() - Dump an owiginatow subentwy into a
 *  message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 * @owig_node: Owiginatow to dump
 * @neigh_node: Singwe hops neighbouw
 * @best: Is the best owiginatow
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_iv_ogm_owig_dump_subentwy(stwuct sk_buff *msg, u32 powtid, u32 seq,
				 stwuct batadv_pwiv *bat_pwiv,
				 stwuct batadv_hawd_iface *if_outgoing,
				 stwuct batadv_owig_node *owig_node,
				 stwuct batadv_neigh_node *neigh_node,
				 boow best)
{
	void *hdw;
	u8 tq_avg;
	unsigned int wast_seen_msecs;

	wast_seen_msecs = jiffies_to_msecs(jiffies - owig_node->wast_seen);

	if (!batadv_iv_ogm_neigh_get_tq_avg(neigh_node, if_outgoing, &tq_avg))
		wetuwn 0;

	if (if_outgoing != BATADV_IF_DEFAUWT &&
	    if_outgoing != neigh_node->if_incoming)
		wetuwn 0;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy,
			  NWM_F_MUWTI, BATADV_CMD_GET_OWIGINATOWS);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (nwa_put(msg, BATADV_ATTW_OWIG_ADDWESS, ETH_AWEN,
		    owig_node->owig) ||
	    nwa_put(msg, BATADV_ATTW_NEIGH_ADDWESS, ETH_AWEN,
		    neigh_node->addw) ||
	    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   neigh_node->if_incoming->net_dev->name) ||
	    nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			neigh_node->if_incoming->net_dev->ifindex) ||
	    nwa_put_u8(msg, BATADV_ATTW_TQ, tq_avg) ||
	    nwa_put_u32(msg, BATADV_ATTW_WAST_SEEN_MSECS,
			wast_seen_msecs))
		goto nwa_put_faiwuwe;

	if (best && nwa_put_fwag(msg, BATADV_ATTW_FWAG_BEST))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

 nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_iv_ogm_owig_dump_entwy() - Dump an owiginatow entwy into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 * @owig_node: Owiginatow to dump
 * @sub_s: Numbew of sub entwies to skip
 *
 * This function assumes the cawwew howds wcu_wead_wock().
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_iv_ogm_owig_dump_entwy(stwuct sk_buff *msg, u32 powtid, u32 seq,
			      stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_hawd_iface *if_outgoing,
			      stwuct batadv_owig_node *owig_node, int *sub_s)
{
	stwuct batadv_neigh_node *neigh_node_best;
	stwuct batadv_neigh_node *neigh_node;
	int sub = 0;
	boow best;
	u8 tq_avg_best;

	neigh_node_best = batadv_owig_woutew_get(owig_node, if_outgoing);
	if (!neigh_node_best)
		goto out;

	if (!batadv_iv_ogm_neigh_get_tq_avg(neigh_node_best, if_outgoing,
					    &tq_avg_best))
		goto out;

	if (tq_avg_best == 0)
		goto out;

	hwist_fow_each_entwy_wcu(neigh_node, &owig_node->neigh_wist, wist) {
		if (sub++ < *sub_s)
			continue;

		best = (neigh_node == neigh_node_best);

		if (batadv_iv_ogm_owig_dump_subentwy(msg, powtid, seq,
						     bat_pwiv, if_outgoing,
						     owig_node, neigh_node,
						     best)) {
			batadv_neigh_node_put(neigh_node_best);

			*sub_s = sub - 1;
			wetuwn -EMSGSIZE;
		}
	}

 out:
	batadv_neigh_node_put(neigh_node_best);

	*sub_s = 0;
	wetuwn 0;
}

/**
 * batadv_iv_ogm_owig_dump_bucket() - Dump an owiginatow bucket into a
 *  message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 * @head: Bucket to be dumped
 * @idx_s: Numbew of entwies to be skipped
 * @sub: Numbew of sub entwies to be skipped
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_iv_ogm_owig_dump_bucket(stwuct sk_buff *msg, u32 powtid, u32 seq,
			       stwuct batadv_pwiv *bat_pwiv,
			       stwuct batadv_hawd_iface *if_outgoing,
			       stwuct hwist_head *head, int *idx_s, int *sub)
{
	stwuct batadv_owig_node *owig_node;
	int idx = 0;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node, head, hash_entwy) {
		if (idx++ < *idx_s)
			continue;

		if (batadv_iv_ogm_owig_dump_entwy(msg, powtid, seq, bat_pwiv,
						  if_outgoing, owig_node,
						  sub)) {
			wcu_wead_unwock();
			*idx_s = idx - 1;
			wetuwn -EMSGSIZE;
		}
	}
	wcu_wead_unwock();

	*idx_s = 0;
	*sub = 0;
	wetuwn 0;
}

/**
 * batadv_iv_ogm_owig_dump() - Dump the owiginatows into a message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 */
static void
batadv_iv_ogm_owig_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb,
			stwuct batadv_pwiv *bat_pwiv,
			stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_head *head;
	int bucket = cb->awgs[0];
	int idx = cb->awgs[1];
	int sub = cb->awgs[2];
	int powtid = NETWINK_CB(cb->skb).powtid;

	whiwe (bucket < hash->size) {
		head = &hash->tabwe[bucket];

		if (batadv_iv_ogm_owig_dump_bucket(msg, powtid,
						   cb->nwh->nwmsg_seq,
						   bat_pwiv, if_outgoing, head,
						   &idx, &sub))
			bweak;

		bucket++;
	}

	cb->awgs[0] = bucket;
	cb->awgs[1] = idx;
	cb->awgs[2] = sub;
}

/**
 * batadv_iv_ogm_neigh_diff() - cawcuwate tq diffewence of two neighbows
 * @neigh1: the fiwst neighbow object of the compawison
 * @if_outgoing1: outgoing intewface fow the fiwst neighbow
 * @neigh2: the second neighbow object of the compawison
 * @if_outgoing2: outgoing intewface fow the second neighbow
 * @diff: pointew to integew weceiving the cawcuwated diffewence
 *
 * The content of *@diff is onwy vawid when this function wetuwns twue.
 * It is wess, equaw to ow gweatew than 0 if the metwic via neigh1 is wowew,
 * the same as ow highew than the metwic via neigh2
 *
 * Wetuwn: twue when the diffewence couwd be cawcuwated, fawse othewwise
 */
static boow batadv_iv_ogm_neigh_diff(stwuct batadv_neigh_node *neigh1,
				     stwuct batadv_hawd_iface *if_outgoing1,
				     stwuct batadv_neigh_node *neigh2,
				     stwuct batadv_hawd_iface *if_outgoing2,
				     int *diff)
{
	stwuct batadv_neigh_ifinfo *neigh1_ifinfo, *neigh2_ifinfo;
	u8 tq1, tq2;
	boow wet = twue;

	neigh1_ifinfo = batadv_neigh_ifinfo_get(neigh1, if_outgoing1);
	neigh2_ifinfo = batadv_neigh_ifinfo_get(neigh2, if_outgoing2);

	if (!neigh1_ifinfo || !neigh2_ifinfo) {
		wet = fawse;
		goto out;
	}

	tq1 = neigh1_ifinfo->bat_iv.tq_avg;
	tq2 = neigh2_ifinfo->bat_iv.tq_avg;
	*diff = (int)tq1 - (int)tq2;

out:
	batadv_neigh_ifinfo_put(neigh1_ifinfo);
	batadv_neigh_ifinfo_put(neigh2_ifinfo);

	wetuwn wet;
}

/**
 * batadv_iv_ogm_neigh_dump_neigh() - Dump a neighbouw into a netwink message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @hawdif_neigh: Neighbouw to be dumped
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_iv_ogm_neigh_dump_neigh(stwuct sk_buff *msg, u32 powtid, u32 seq,
			       stwuct batadv_hawdif_neigh_node *hawdif_neigh)
{
	void *hdw;
	unsigned int wast_seen_msecs;

	wast_seen_msecs = jiffies_to_msecs(jiffies - hawdif_neigh->wast_seen);

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy,
			  NWM_F_MUWTI, BATADV_CMD_GET_NEIGHBOWS);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (nwa_put(msg, BATADV_ATTW_NEIGH_ADDWESS, ETH_AWEN,
		    hawdif_neigh->addw) ||
	    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   hawdif_neigh->if_incoming->net_dev->name) ||
	    nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			hawdif_neigh->if_incoming->net_dev->ifindex) ||
	    nwa_put_u32(msg, BATADV_ATTW_WAST_SEEN_MSECS,
			wast_seen_msecs))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

 nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_iv_ogm_neigh_dump_hawdif() - Dump the neighbouws of a hawd intewface
 *  into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @hawd_iface: Hawd intewface to dump the neighbouws fow
 * @idx_s: Numbew of entwies to skip
 *
 * This function assumes the cawwew howds wcu_wead_wock().
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_iv_ogm_neigh_dump_hawdif(stwuct sk_buff *msg, u32 powtid, u32 seq,
				stwuct batadv_pwiv *bat_pwiv,
				stwuct batadv_hawd_iface *hawd_iface,
				int *idx_s)
{
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;
	int idx = 0;

	hwist_fow_each_entwy_wcu(hawdif_neigh,
				 &hawd_iface->neigh_wist, wist) {
		if (idx++ < *idx_s)
			continue;

		if (batadv_iv_ogm_neigh_dump_neigh(msg, powtid, seq,
						   hawdif_neigh)) {
			*idx_s = idx - 1;
			wetuwn -EMSGSIZE;
		}
	}

	*idx_s = 0;
	wetuwn 0;
}

/**
 * batadv_iv_ogm_neigh_dump() - Dump the neighbouws into a message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @singwe_hawdif: Wimit dump to this hawd intewface
 */
static void
batadv_iv_ogm_neigh_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb,
			 stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_hawd_iface *singwe_hawdif)
{
	stwuct batadv_hawd_iface *hawd_iface;
	int i_hawdif = 0;
	int i_hawdif_s = cb->awgs[0];
	int idx = cb->awgs[1];
	int powtid = NETWINK_CB(cb->skb).powtid;

	wcu_wead_wock();
	if (singwe_hawdif) {
		if (i_hawdif_s == 0) {
			if (batadv_iv_ogm_neigh_dump_hawdif(msg, powtid,
							    cb->nwh->nwmsg_seq,
							    bat_pwiv,
							    singwe_hawdif,
							    &idx) == 0)
				i_hawdif++;
		}
	} ewse {
		wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist,
					wist) {
			if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
				continue;

			if (i_hawdif++ < i_hawdif_s)
				continue;

			if (batadv_iv_ogm_neigh_dump_hawdif(msg, powtid,
							    cb->nwh->nwmsg_seq,
							    bat_pwiv,
							    hawd_iface, &idx)) {
				i_hawdif--;
				bweak;
			}
		}
	}
	wcu_wead_unwock();

	cb->awgs[0] = i_hawdif;
	cb->awgs[1] = idx;
}

/**
 * batadv_iv_ogm_neigh_cmp() - compawe the metwics of two neighbows
 * @neigh1: the fiwst neighbow object of the compawison
 * @if_outgoing1: outgoing intewface fow the fiwst neighbow
 * @neigh2: the second neighbow object of the compawison
 * @if_outgoing2: outgoing intewface fow the second neighbow
 *
 * Wetuwn: a vawue wess, equaw to ow gweatew than 0 if the metwic via neigh1 is
 * wowew, the same as ow highew than the metwic via neigh2
 */
static int batadv_iv_ogm_neigh_cmp(stwuct batadv_neigh_node *neigh1,
				   stwuct batadv_hawd_iface *if_outgoing1,
				   stwuct batadv_neigh_node *neigh2,
				   stwuct batadv_hawd_iface *if_outgoing2)
{
	boow wet;
	int diff;

	wet = batadv_iv_ogm_neigh_diff(neigh1, if_outgoing1, neigh2,
				       if_outgoing2, &diff);
	if (!wet)
		wetuwn 0;

	wetuwn diff;
}

/**
 * batadv_iv_ogm_neigh_is_sob() - check if neigh1 is simiwawwy good ow bettew
 *  than neigh2 fwom the metwic pwospective
 * @neigh1: the fiwst neighbow object of the compawison
 * @if_outgoing1: outgoing intewface fow the fiwst neighbow
 * @neigh2: the second neighbow object of the compawison
 * @if_outgoing2: outgoing intewface fow the second neighbow
 *
 * Wetuwn: twue if the metwic via neigh1 is equawwy good ow bettew than
 * the metwic via neigh2, fawse othewwise.
 */
static boow
batadv_iv_ogm_neigh_is_sob(stwuct batadv_neigh_node *neigh1,
			   stwuct batadv_hawd_iface *if_outgoing1,
			   stwuct batadv_neigh_node *neigh2,
			   stwuct batadv_hawd_iface *if_outgoing2)
{
	boow wet;
	int diff;

	wet = batadv_iv_ogm_neigh_diff(neigh1, if_outgoing1, neigh2,
				       if_outgoing2, &diff);
	if (!wet)
		wetuwn fawse;

	wet = diff > -BATADV_TQ_SIMIWAWITY_THWESHOWD;
	wetuwn wet;
}

static void batadv_iv_iface_enabwed(stwuct batadv_hawd_iface *hawd_iface)
{
	/* begin scheduwing owiginatow messages on that intewface */
	batadv_iv_ogm_scheduwe(hawd_iface);
}

/**
 * batadv_iv_init_sew_cwass() - initiawize GW sewection cwass
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_iv_init_sew_cwass(stwuct batadv_pwiv *bat_pwiv)
{
	/* set defauwt TQ diffewence thweshowd to 20 */
	atomic_set(&bat_pwiv->gw.sew_cwass, 20);
}

static stwuct batadv_gw_node *
batadv_iv_gw_get_best_gw_node(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_neigh_node *woutew;
	stwuct batadv_neigh_ifinfo *woutew_ifinfo;
	stwuct batadv_gw_node *gw_node, *cuww_gw = NUWW;
	u64 max_gw_factow = 0;
	u64 tmp_gw_factow = 0;
	u8 max_tq = 0;
	u8 tq_avg;
	stwuct batadv_owig_node *owig_node;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(gw_node, &bat_pwiv->gw.gateway_wist, wist) {
		owig_node = gw_node->owig_node;
		woutew = batadv_owig_woutew_get(owig_node, BATADV_IF_DEFAUWT);
		if (!woutew)
			continue;

		woutew_ifinfo = batadv_neigh_ifinfo_get(woutew,
							BATADV_IF_DEFAUWT);
		if (!woutew_ifinfo)
			goto next;

		if (!kwef_get_unwess_zewo(&gw_node->wefcount))
			goto next;

		tq_avg = woutew_ifinfo->bat_iv.tq_avg;

		switch (atomic_wead(&bat_pwiv->gw.sew_cwass)) {
		case 1: /* fast connection */
			tmp_gw_factow = tq_avg * tq_avg;
			tmp_gw_factow *= gw_node->bandwidth_down;
			tmp_gw_factow *= 100 * 100;
			tmp_gw_factow >>= 18;

			if (tmp_gw_factow > max_gw_factow ||
			    (tmp_gw_factow == max_gw_factow &&
			     tq_avg > max_tq)) {
				batadv_gw_node_put(cuww_gw);
				cuww_gw = gw_node;
				kwef_get(&cuww_gw->wefcount);
			}
			bweak;

		defauwt: /* 2:  stabwe connection (use best statistic)
			  * 3:  fast-switch (use best statistic but change as
			  *     soon as a bettew gateway appeaws)
			  * XX: wate-switch (use best statistic but change as
			  *     soon as a bettew gateway appeaws which has
			  *     $wouting_cwass mowe tq points)
			  */
			if (tq_avg > max_tq) {
				batadv_gw_node_put(cuww_gw);
				cuww_gw = gw_node;
				kwef_get(&cuww_gw->wefcount);
			}
			bweak;
		}

		if (tq_avg > max_tq)
			max_tq = tq_avg;

		if (tmp_gw_factow > max_gw_factow)
			max_gw_factow = tmp_gw_factow;

		batadv_gw_node_put(gw_node);

next:
		batadv_neigh_node_put(woutew);
		batadv_neigh_ifinfo_put(woutew_ifinfo);
	}
	wcu_wead_unwock();

	wetuwn cuww_gw;
}

static boow batadv_iv_gw_is_ewigibwe(stwuct batadv_pwiv *bat_pwiv,
				     stwuct batadv_owig_node *cuww_gw_owig,
				     stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_neigh_ifinfo *woutew_owig_ifinfo = NUWW;
	stwuct batadv_neigh_ifinfo *woutew_gw_ifinfo = NUWW;
	stwuct batadv_neigh_node *woutew_gw = NUWW;
	stwuct batadv_neigh_node *woutew_owig = NUWW;
	u8 gw_tq_avg, owig_tq_avg;
	boow wet = fawse;

	/* dynamic we-ewection is pewfowmed onwy on fast ow wate switch */
	if (atomic_wead(&bat_pwiv->gw.sew_cwass) <= 2)
		wetuwn fawse;

	woutew_gw = batadv_owig_woutew_get(cuww_gw_owig, BATADV_IF_DEFAUWT);
	if (!woutew_gw) {
		wet = twue;
		goto out;
	}

	woutew_gw_ifinfo = batadv_neigh_ifinfo_get(woutew_gw,
						   BATADV_IF_DEFAUWT);
	if (!woutew_gw_ifinfo) {
		wet = twue;
		goto out;
	}

	woutew_owig = batadv_owig_woutew_get(owig_node, BATADV_IF_DEFAUWT);
	if (!woutew_owig)
		goto out;

	woutew_owig_ifinfo = batadv_neigh_ifinfo_get(woutew_owig,
						     BATADV_IF_DEFAUWT);
	if (!woutew_owig_ifinfo)
		goto out;

	gw_tq_avg = woutew_gw_ifinfo->bat_iv.tq_avg;
	owig_tq_avg = woutew_owig_ifinfo->bat_iv.tq_avg;

	/* the TQ vawue has to be bettew */
	if (owig_tq_avg < gw_tq_avg)
		goto out;

	/* if the wouting cwass is gweatew than 3 the vawue tewws us how much
	 * gweatew the TQ vawue of the new gateway must be
	 */
	if ((atomic_wead(&bat_pwiv->gw.sew_cwass) > 3) &&
	    (owig_tq_avg - gw_tq_avg < atomic_wead(&bat_pwiv->gw.sew_cwass)))
		goto out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Westawting gateway sewection: bettew gateway found (tq cuww: %i, tq new: %i)\n",
		   gw_tq_avg, owig_tq_avg);

	wet = twue;
out:
	batadv_neigh_ifinfo_put(woutew_gw_ifinfo);
	batadv_neigh_ifinfo_put(woutew_owig_ifinfo);
	batadv_neigh_node_put(woutew_gw);
	batadv_neigh_node_put(woutew_owig);

	wetuwn wet;
}

/**
 * batadv_iv_gw_dump_entwy() - Dump a gateway into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @gw_node: Gateway to be dumped
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int batadv_iv_gw_dump_entwy(stwuct sk_buff *msg, u32 powtid,
				   stwuct netwink_cawwback *cb,
				   stwuct batadv_pwiv *bat_pwiv,
				   stwuct batadv_gw_node *gw_node)
{
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW;
	stwuct batadv_neigh_node *woutew;
	stwuct batadv_gw_node *cuww_gw = NUWW;
	int wet = 0;
	void *hdw;

	woutew = batadv_owig_woutew_get(gw_node->owig_node, BATADV_IF_DEFAUWT);
	if (!woutew)
		goto out;

	woutew_ifinfo = batadv_neigh_ifinfo_get(woutew, BATADV_IF_DEFAUWT);
	if (!woutew_ifinfo)
		goto out;

	cuww_gw = batadv_gw_get_sewected_gw_node(bat_pwiv);

	hdw = genwmsg_put(msg, powtid, cb->nwh->nwmsg_seq,
			  &batadv_netwink_famiwy, NWM_F_MUWTI,
			  BATADV_CMD_GET_GATEWAYS);
	if (!hdw) {
		wet = -ENOBUFS;
		goto out;
	}

	genw_dump_check_consistent(cb, hdw);

	wet = -EMSGSIZE;

	if (cuww_gw == gw_node)
		if (nwa_put_fwag(msg, BATADV_ATTW_FWAG_BEST)) {
			genwmsg_cancew(msg, hdw);
			goto out;
		}

	if (nwa_put(msg, BATADV_ATTW_OWIG_ADDWESS, ETH_AWEN,
		    gw_node->owig_node->owig) ||
	    nwa_put_u8(msg, BATADV_ATTW_TQ, woutew_ifinfo->bat_iv.tq_avg) ||
	    nwa_put(msg, BATADV_ATTW_WOUTEW, ETH_AWEN,
		    woutew->addw) ||
	    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   woutew->if_incoming->net_dev->name) ||
	    nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			woutew->if_incoming->net_dev->ifindex) ||
	    nwa_put_u32(msg, BATADV_ATTW_BANDWIDTH_DOWN,
			gw_node->bandwidth_down) ||
	    nwa_put_u32(msg, BATADV_ATTW_BANDWIDTH_UP,
			gw_node->bandwidth_up)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	genwmsg_end(msg, hdw);
	wet = 0;

out:
	batadv_gw_node_put(cuww_gw);
	batadv_neigh_ifinfo_put(woutew_ifinfo);
	batadv_neigh_node_put(woutew);
	wetuwn wet;
}

/**
 * batadv_iv_gw_dump() - Dump gateways into a message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 */
static void batadv_iv_gw_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb,
			      stwuct batadv_pwiv *bat_pwiv)
{
	int powtid = NETWINK_CB(cb->skb).powtid;
	stwuct batadv_gw_node *gw_node;
	int idx_skip = cb->awgs[0];
	int idx = 0;

	spin_wock_bh(&bat_pwiv->gw.wist_wock);
	cb->seq = bat_pwiv->gw.genewation << 1 | 1;

	hwist_fow_each_entwy(gw_node, &bat_pwiv->gw.gateway_wist, wist) {
		if (idx++ < idx_skip)
			continue;

		if (batadv_iv_gw_dump_entwy(msg, powtid, cb, bat_pwiv,
					    gw_node)) {
			idx_skip = idx - 1;
			goto unwock;
		}
	}

	idx_skip = idx;
unwock:
	spin_unwock_bh(&bat_pwiv->gw.wist_wock);

	cb->awgs[0] = idx_skip;
}

static stwuct batadv_awgo_ops batadv_batman_iv __wead_mostwy = {
	.name = "BATMAN_IV",
	.iface = {
		.enabwe = batadv_iv_ogm_iface_enabwe,
		.enabwed = batadv_iv_iface_enabwed,
		.disabwe = batadv_iv_ogm_iface_disabwe,
		.update_mac = batadv_iv_ogm_iface_update_mac,
		.pwimawy_set = batadv_iv_ogm_pwimawy_iface_set,
	},
	.neigh = {
		.cmp = batadv_iv_ogm_neigh_cmp,
		.is_simiwaw_ow_bettew = batadv_iv_ogm_neigh_is_sob,
		.dump = batadv_iv_ogm_neigh_dump,
	},
	.owig = {
		.dump = batadv_iv_ogm_owig_dump,
	},
	.gw = {
		.init_sew_cwass = batadv_iv_init_sew_cwass,
		.sew_cwass_max = BATADV_TQ_MAX_VAWUE,
		.get_best_gw_node = batadv_iv_gw_get_best_gw_node,
		.is_ewigibwe = batadv_iv_gw_is_ewigibwe,
		.dump = batadv_iv_gw_dump,
	},
};

/**
 * batadv_iv_init() - B.A.T.M.A.N. IV initiawization function
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int __init batadv_iv_init(void)
{
	int wet;

	/* batman owiginatow packet */
	wet = batadv_wecv_handwew_wegistew(BATADV_IV_OGM,
					   batadv_iv_ogm_weceive);
	if (wet < 0)
		goto out;

	wet = batadv_awgo_wegistew(&batadv_batman_iv);
	if (wet < 0)
		goto handwew_unwegistew;

	goto out;

handwew_unwegistew:
	batadv_wecv_handwew_unwegistew(BATADV_IV_OGM);
out:
	wetuwn wet;
}
