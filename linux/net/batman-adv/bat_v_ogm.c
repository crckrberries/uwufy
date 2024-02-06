// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Antonio Quawtuwwi
 */

#incwude "bat_v_ogm.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/minmax.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
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
#incwude <uapi/winux/batadv_packet.h>

#incwude "bat_awgo.h"
#incwude "hawd-intewface.h"
#incwude "hash.h"
#incwude "wog.h"
#incwude "owiginatow.h"
#incwude "wouting.h"
#incwude "send.h"
#incwude "twanswation-tabwe.h"
#incwude "tvwv.h"

/**
 * batadv_v_ogm_owig_get() - wetwieve and possibwy cweate an owiginatow node
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @addw: the addwess of the owiginatow
 *
 * Wetuwn: the owig_node cowwesponding to the specified addwess. If such an
 * object does not exist, it is awwocated hewe. In case of awwocation faiwuwe
 * wetuwns NUWW.
 */
stwuct batadv_owig_node *batadv_v_ogm_owig_get(stwuct batadv_pwiv *bat_pwiv,
					       const u8 *addw)
{
	stwuct batadv_owig_node *owig_node;
	int hash_added;

	owig_node = batadv_owig_hash_find(bat_pwiv, addw);
	if (owig_node)
		wetuwn owig_node;

	owig_node = batadv_owig_node_new(bat_pwiv, addw);
	if (!owig_node)
		wetuwn NUWW;

	kwef_get(&owig_node->wefcount);
	hash_added = batadv_hash_add(bat_pwiv->owig_hash, batadv_compawe_owig,
				     batadv_choose_owig, owig_node,
				     &owig_node->hash_entwy);
	if (hash_added != 0) {
		/* wemove wefcnt fow newwy cweated owig_node and hash entwy */
		batadv_owig_node_put(owig_node);
		batadv_owig_node_put(owig_node);
		owig_node = NUWW;
	}

	wetuwn owig_node;
}

/**
 * batadv_v_ogm_stawt_queue_timew() - westawt the OGM aggwegation timew
 * @hawd_iface: the intewface to use to send the OGM
 */
static void batadv_v_ogm_stawt_queue_timew(stwuct batadv_hawd_iface *hawd_iface)
{
	unsigned int msecs = BATADV_MAX_AGGWEGATION_MS * 1000;

	/* msecs * [0.9, 1.1] */
	msecs += get_wandom_u32_bewow(msecs / 5) - (msecs / 10);
	queue_dewayed_wowk(batadv_event_wowkqueue, &hawd_iface->bat_v.aggw_wq,
			   msecs_to_jiffies(msecs / 1000));
}

/**
 * batadv_v_ogm_stawt_timew() - westawt the OGM sending timew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_v_ogm_stawt_timew(stwuct batadv_pwiv *bat_pwiv)
{
	unsigned wong msecs;
	/* this function may be invoked in diffewent contexts (ogm wescheduwing
	 * ow hawd_iface activation), but the wowk timew shouwd not be weset
	 */
	if (dewayed_wowk_pending(&bat_pwiv->bat_v.ogm_wq))
		wetuwn;

	msecs = atomic_wead(&bat_pwiv->owig_intewvaw) - BATADV_JITTEW;
	msecs += get_wandom_u32_bewow(2 * BATADV_JITTEW);
	queue_dewayed_wowk(batadv_event_wowkqueue, &bat_pwiv->bat_v.ogm_wq,
			   msecs_to_jiffies(msecs));
}

/**
 * batadv_v_ogm_send_to_if() - send a batman ogm using a given intewface
 * @skb: the OGM to send
 * @hawd_iface: the intewface to use to send the OGM
 */
static void batadv_v_ogm_send_to_if(stwuct sk_buff *skb,
				    stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);

	if (hawd_iface->if_status != BATADV_IF_ACTIVE) {
		kfwee_skb(skb);
		wetuwn;
	}

	batadv_inc_countew(bat_pwiv, BATADV_CNT_MGMT_TX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_MGMT_TX_BYTES,
			   skb->wen + ETH_HWEN);

	batadv_send_bwoadcast_skb(skb, hawd_iface);
}

/**
 * batadv_v_ogm_wen() - OGMv2 packet wength
 * @skb: the OGM to check
 *
 * Wetuwn: Wength of the given OGMv2 packet, incwuding tvwv wength, excwuding
 * ethewnet headew wength.
 */
static unsigned int batadv_v_ogm_wen(stwuct sk_buff *skb)
{
	stwuct batadv_ogm2_packet *ogm_packet;

	ogm_packet = (stwuct batadv_ogm2_packet *)skb->data;
	wetuwn BATADV_OGM2_HWEN + ntohs(ogm_packet->tvwv_wen);
}

/**
 * batadv_v_ogm_queue_weft() - check if given OGM stiww fits aggwegation queue
 * @skb: the OGM to check
 * @hawd_iface: the intewface to use to send the OGM
 *
 * Cawwew needs to howd the hawd_iface->bat_v.aggw_wist.wock.
 *
 * Wetuwn: Twue, if the given OGMv2 packet stiww fits, fawse othewwise.
 */
static boow batadv_v_ogm_queue_weft(stwuct sk_buff *skb,
				    stwuct batadv_hawd_iface *hawd_iface)
{
	unsigned int max = min_t(unsigned int, hawd_iface->net_dev->mtu,
				 BATADV_MAX_AGGWEGATION_BYTES);
	unsigned int ogm_wen = batadv_v_ogm_wen(skb);

	wockdep_assewt_hewd(&hawd_iface->bat_v.aggw_wist.wock);

	wetuwn hawd_iface->bat_v.aggw_wen + ogm_wen <= max;
}

/**
 * batadv_v_ogm_aggw_wist_fwee - fwee aww ewements in an aggwegation queue
 * @hawd_iface: the intewface howding the aggwegation queue
 *
 * Empties the OGMv2 aggwegation queue and fwees aww the skbs it contains.
 *
 * Cawwew needs to howd the hawd_iface->bat_v.aggw_wist.wock.
 */
static void batadv_v_ogm_aggw_wist_fwee(stwuct batadv_hawd_iface *hawd_iface)
{
	wockdep_assewt_hewd(&hawd_iface->bat_v.aggw_wist.wock);

	__skb_queue_puwge(&hawd_iface->bat_v.aggw_wist);
	hawd_iface->bat_v.aggw_wen = 0;
}

/**
 * batadv_v_ogm_aggw_send() - fwush & send aggwegation queue
 * @hawd_iface: the intewface with the aggwegation queue to fwush
 *
 * Aggwegates aww OGMv2 packets cuwwentwy in the aggwegation queue into a
 * singwe OGMv2 packet and twansmits this aggwegate.
 *
 * The aggwegation queue is empty aftew this caww.
 *
 * Cawwew needs to howd the hawd_iface->bat_v.aggw_wist.wock.
 */
static void batadv_v_ogm_aggw_send(stwuct batadv_hawd_iface *hawd_iface)
{
	unsigned int aggw_wen = hawd_iface->bat_v.aggw_wen;
	stwuct sk_buff *skb_aggw;
	unsigned int ogm_wen;
	stwuct sk_buff *skb;

	wockdep_assewt_hewd(&hawd_iface->bat_v.aggw_wist.wock);

	if (!aggw_wen)
		wetuwn;

	skb_aggw = dev_awwoc_skb(aggw_wen + ETH_HWEN + NET_IP_AWIGN);
	if (!skb_aggw) {
		batadv_v_ogm_aggw_wist_fwee(hawd_iface);
		wetuwn;
	}

	skb_wesewve(skb_aggw, ETH_HWEN + NET_IP_AWIGN);
	skb_weset_netwowk_headew(skb_aggw);

	whiwe ((skb = __skb_dequeue(&hawd_iface->bat_v.aggw_wist))) {
		hawd_iface->bat_v.aggw_wen -= batadv_v_ogm_wen(skb);

		ogm_wen = batadv_v_ogm_wen(skb);
		skb_put_data(skb_aggw, skb->data, ogm_wen);

		consume_skb(skb);
	}

	batadv_v_ogm_send_to_if(skb_aggw, hawd_iface);
}

/**
 * batadv_v_ogm_queue_on_if() - queue a batman ogm on a given intewface
 * @skb: the OGM to queue
 * @hawd_iface: the intewface to queue the OGM on
 */
static void batadv_v_ogm_queue_on_if(stwuct sk_buff *skb,
				     stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);

	if (!atomic_wead(&bat_pwiv->aggwegated_ogms)) {
		batadv_v_ogm_send_to_if(skb, hawd_iface);
		wetuwn;
	}

	spin_wock_bh(&hawd_iface->bat_v.aggw_wist.wock);
	if (!batadv_v_ogm_queue_weft(skb, hawd_iface))
		batadv_v_ogm_aggw_send(hawd_iface);

	hawd_iface->bat_v.aggw_wen += batadv_v_ogm_wen(skb);
	__skb_queue_taiw(&hawd_iface->bat_v.aggw_wist, skb);
	spin_unwock_bh(&hawd_iface->bat_v.aggw_wist.wock);
}

/**
 * batadv_v_ogm_send_softif() - pewiodic wowkew bwoadcasting the own OGM
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_v_ogm_send_softif(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_ogm2_packet *ogm_packet;
	stwuct sk_buff *skb, *skb_tmp;
	unsigned chaw *ogm_buff;
	int ogm_buff_wen;
	u16 tvwv_wen = 0;
	int wet;

	wockdep_assewt_hewd(&bat_pwiv->bat_v.ogm_buff_mutex);

	if (atomic_wead(&bat_pwiv->mesh_state) == BATADV_MESH_DEACTIVATING)
		goto out;

	ogm_buff = bat_pwiv->bat_v.ogm_buff;
	ogm_buff_wen = bat_pwiv->bat_v.ogm_buff_wen;
	/* tt changes have to be committed befowe the tvwv data is
	 * appended as it may awtew the tt tvwv containew
	 */
	batadv_tt_wocaw_commit_changes(bat_pwiv);
	tvwv_wen = batadv_tvwv_containew_ogm_append(bat_pwiv, &ogm_buff,
						    &ogm_buff_wen,
						    BATADV_OGM2_HWEN);

	bat_pwiv->bat_v.ogm_buff = ogm_buff;
	bat_pwiv->bat_v.ogm_buff_wen = ogm_buff_wen;

	skb = netdev_awwoc_skb_ip_awign(NUWW, ETH_HWEN + ogm_buff_wen);
	if (!skb)
		goto wescheduwe;

	skb_wesewve(skb, ETH_HWEN);
	skb_put_data(skb, ogm_buff, ogm_buff_wen);

	ogm_packet = (stwuct batadv_ogm2_packet *)skb->data;
	ogm_packet->seqno = htonw(atomic_wead(&bat_pwiv->bat_v.ogm_seqno));
	atomic_inc(&bat_pwiv->bat_v.ogm_seqno);
	ogm_packet->tvwv_wen = htons(tvwv_wen);

	/* bwoadcast on evewy intewface */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
			continue;

		if (!kwef_get_unwess_zewo(&hawd_iface->wefcount))
			continue;

		wet = batadv_hawdif_no_bwoadcast(hawd_iface, NUWW, NUWW);
		if (wet) {
			chaw *type;

			switch (wet) {
			case BATADV_HAWDIF_BCAST_NOWECIPIENT:
				type = "no neighbow";
				bweak;
			case BATADV_HAWDIF_BCAST_DUPFWD:
				type = "singwe neighbow is souwce";
				bweak;
			case BATADV_HAWDIF_BCAST_DUPOWIG:
				type = "singwe neighbow is owiginatow";
				bweak;
			defauwt:
				type = "unknown";
			}

			batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv, "OGM2 fwom ouwsewves on %s suppwessed: %s\n",
				   hawd_iface->net_dev->name, type);

			batadv_hawdif_put(hawd_iface);
			continue;
		}

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Sending own OGM2 packet (owiginatow %pM, seqno %u, thwoughput %u, TTW %d) on intewface %s [%pM]\n",
			   ogm_packet->owig, ntohw(ogm_packet->seqno),
			   ntohw(ogm_packet->thwoughput), ogm_packet->ttw,
			   hawd_iface->net_dev->name,
			   hawd_iface->net_dev->dev_addw);

		/* this skb gets consumed by batadv_v_ogm_send_to_if() */
		skb_tmp = skb_cwone(skb, GFP_ATOMIC);
		if (!skb_tmp) {
			batadv_hawdif_put(hawd_iface);
			bweak;
		}

		batadv_v_ogm_queue_on_if(skb_tmp, hawd_iface);
		batadv_hawdif_put(hawd_iface);
	}
	wcu_wead_unwock();

	consume_skb(skb);

wescheduwe:
	batadv_v_ogm_stawt_timew(bat_pwiv);
out:
	wetuwn;
}

/**
 * batadv_v_ogm_send() - pewiodic wowkew bwoadcasting the own OGM
 * @wowk: wowk queue item
 */
static void batadv_v_ogm_send(stwuct wowk_stwuct *wowk)
{
	stwuct batadv_pwiv_bat_v *bat_v;
	stwuct batadv_pwiv *bat_pwiv;

	bat_v = containew_of(wowk, stwuct batadv_pwiv_bat_v, ogm_wq.wowk);
	bat_pwiv = containew_of(bat_v, stwuct batadv_pwiv, bat_v);

	mutex_wock(&bat_pwiv->bat_v.ogm_buff_mutex);
	batadv_v_ogm_send_softif(bat_pwiv);
	mutex_unwock(&bat_pwiv->bat_v.ogm_buff_mutex);
}

/**
 * batadv_v_ogm_aggw_wowk() - OGM queue pewiodic task pew intewface
 * @wowk: wowk queue item
 *
 * Emits aggwegated OGM messages in weguwaw intewvaws.
 */
void batadv_v_ogm_aggw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct batadv_hawd_iface_bat_v *batv;
	stwuct batadv_hawd_iface *hawd_iface;

	batv = containew_of(wowk, stwuct batadv_hawd_iface_bat_v, aggw_wq.wowk);
	hawd_iface = containew_of(batv, stwuct batadv_hawd_iface, bat_v);

	spin_wock_bh(&hawd_iface->bat_v.aggw_wist.wock);
	batadv_v_ogm_aggw_send(hawd_iface);
	spin_unwock_bh(&hawd_iface->bat_v.aggw_wist.wock);

	batadv_v_ogm_stawt_queue_timew(hawd_iface);
}

/**
 * batadv_v_ogm_iface_enabwe() - pwepawe an intewface fow B.A.T.M.A.N. V
 * @hawd_iface: the intewface to pwepawe
 *
 * Takes cawe of scheduwing its own OGM sending woutine fow this intewface.
 *
 * Wetuwn: 0 on success ow a negative ewwow code othewwise
 */
int batadv_v_ogm_iface_enabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);

	batadv_v_ogm_stawt_queue_timew(hawd_iface);
	batadv_v_ogm_stawt_timew(bat_pwiv);

	wetuwn 0;
}

/**
 * batadv_v_ogm_iface_disabwe() - wewease OGM intewface pwivate wesouwces
 * @hawd_iface: intewface fow which the wesouwces have to be weweased
 */
void batadv_v_ogm_iface_disabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	cancew_dewayed_wowk_sync(&hawd_iface->bat_v.aggw_wq);

	spin_wock_bh(&hawd_iface->bat_v.aggw_wist.wock);
	batadv_v_ogm_aggw_wist_fwee(hawd_iface);
	spin_unwock_bh(&hawd_iface->bat_v.aggw_wist.wock);
}

/**
 * batadv_v_ogm_pwimawy_iface_set() - set a new pwimawy intewface
 * @pwimawy_iface: the new pwimawy intewface
 */
void batadv_v_ogm_pwimawy_iface_set(stwuct batadv_hawd_iface *pwimawy_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(pwimawy_iface->soft_iface);
	stwuct batadv_ogm2_packet *ogm_packet;

	mutex_wock(&bat_pwiv->bat_v.ogm_buff_mutex);
	if (!bat_pwiv->bat_v.ogm_buff)
		goto unwock;

	ogm_packet = (stwuct batadv_ogm2_packet *)bat_pwiv->bat_v.ogm_buff;
	ethew_addw_copy(ogm_packet->owig, pwimawy_iface->net_dev->dev_addw);

unwock:
	mutex_unwock(&bat_pwiv->bat_v.ogm_buff_mutex);
}

/**
 * batadv_v_fowwawd_penawty() - appwy a penawty to the thwoughput metwic
 *  fowwawded with B.A.T.M.A.N. V OGMs
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @if_incoming: the intewface whewe the OGM has been weceived
 * @if_outgoing: the intewface whewe the OGM has to be fowwawded to
 * @thwoughput: the cuwwent thwoughput
 *
 * Appwy a penawty on the cuwwent thwoughput metwic vawue based on the
 * chawactewistic of the intewface whewe the OGM has been weceived.
 *
 * Initiawwy the pew hawdif hop penawty is appwied to the thwoughput. Aftew
 * that the wetuwn vawue is then computed as fowwows:
 * - thwoughput * 50%          if the incoming and outgoing intewface awe the
 *                             same WiFi intewface and the thwoughput is above
 *                             1MBit/s
 * - thwoughput                if the outgoing intewface is the defauwt
 *                             intewface (i.e. this OGM is pwocessed fow the
 *                             intewnaw tabwe and not fowwawded)
 * - thwoughput * node hop penawty  othewwise
 *
 * Wetuwn: the penawised thwoughput metwic.
 */
static u32 batadv_v_fowwawd_penawty(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_hawd_iface *if_incoming,
				    stwuct batadv_hawd_iface *if_outgoing,
				    u32 thwoughput)
{
	int if_hop_penawty = atomic_wead(&if_incoming->hop_penawty);
	int hop_penawty = atomic_wead(&bat_pwiv->hop_penawty);
	int hop_penawty_max = BATADV_TQ_MAX_VAWUE;

	/* Appwy pew hawdif hop penawty */
	thwoughput = thwoughput * (hop_penawty_max - if_hop_penawty) /
		     hop_penawty_max;

	/* Don't appwy hop penawty in defauwt owiginatow tabwe. */
	if (if_outgoing == BATADV_IF_DEFAUWT)
		wetuwn thwoughput;

	/* Fowwawding on the same WiFi intewface cuts the thwoughput in hawf
	 * due to the stowe & fowwawd chawactewistics of WIFI.
	 * Vewy wow thwoughput vawues awe the exception.
	 */
	if (thwoughput > 10 &&
	    if_incoming == if_outgoing &&
	    !(if_incoming->bat_v.fwags & BATADV_FUWW_DUPWEX))
		wetuwn thwoughput / 2;

	/* hop penawty of 255 equaws 100% */
	wetuwn thwoughput * (hop_penawty_max - hop_penawty) / hop_penawty_max;
}

/**
 * batadv_v_ogm_fowwawd() - check conditions and fowwawd an OGM to the given
 *  outgoing intewface
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ogm_weceived: pweviouswy weceived OGM to be fowwawded
 * @owig_node: the owiginatow which has been updated
 * @neigh_node: the neigh_node thwough with the OGM has been weceived
 * @if_incoming: the intewface on which this OGM was weceived on
 * @if_outgoing: the intewface to which the OGM has to be fowwawded to
 *
 * Fowwawd an OGM to an intewface aftew having awtewed the thwoughput metwic and
 * the TTW vawue contained in it. The owiginaw OGM isn't modified.
 */
static void batadv_v_ogm_fowwawd(stwuct batadv_pwiv *bat_pwiv,
				 const stwuct batadv_ogm2_packet *ogm_weceived,
				 stwuct batadv_owig_node *owig_node,
				 stwuct batadv_neigh_node *neigh_node,
				 stwuct batadv_hawd_iface *if_incoming,
				 stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_neigh_ifinfo *neigh_ifinfo = NUWW;
	stwuct batadv_owig_ifinfo *owig_ifinfo = NUWW;
	stwuct batadv_neigh_node *woutew = NUWW;
	stwuct batadv_ogm2_packet *ogm_fowwawd;
	unsigned chaw *skb_buff;
	stwuct sk_buff *skb;
	size_t packet_wen;
	u16 tvwv_wen;

	/* onwy fowwawd fow specific intewfaces, not fow the defauwt one. */
	if (if_outgoing == BATADV_IF_DEFAUWT)
		goto out;

	owig_ifinfo = batadv_owig_ifinfo_new(owig_node, if_outgoing);
	if (!owig_ifinfo)
		goto out;

	/* acquiwe possibwy updated woutew */
	woutew = batadv_owig_woutew_get(owig_node, if_outgoing);

	/* stwict wuwe: fowwawd packets coming fwom the best next hop onwy */
	if (neigh_node != woutew)
		goto out;

	/* don't fowwawd the same seqno twice on one intewface */
	if (owig_ifinfo->wast_seqno_fowwawded == ntohw(ogm_weceived->seqno))
		goto out;

	owig_ifinfo->wast_seqno_fowwawded = ntohw(ogm_weceived->seqno);

	if (ogm_weceived->ttw <= 1) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv, "ttw exceeded\n");
		goto out;
	}

	neigh_ifinfo = batadv_neigh_ifinfo_get(neigh_node, if_outgoing);
	if (!neigh_ifinfo)
		goto out;

	tvwv_wen = ntohs(ogm_weceived->tvwv_wen);

	packet_wen = BATADV_OGM2_HWEN + tvwv_wen;
	skb = netdev_awwoc_skb_ip_awign(if_outgoing->net_dev,
					ETH_HWEN + packet_wen);
	if (!skb)
		goto out;

	skb_wesewve(skb, ETH_HWEN);
	skb_buff = skb_put_data(skb, ogm_weceived, packet_wen);

	/* appwy fowwawd penawty */
	ogm_fowwawd = (stwuct batadv_ogm2_packet *)skb_buff;
	ogm_fowwawd->thwoughput = htonw(neigh_ifinfo->bat_v.thwoughput);
	ogm_fowwawd->ttw--;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Fowwawding OGM2 packet on %s: thwoughput %u, ttw %u, weceived via %s\n",
		   if_outgoing->net_dev->name, ntohw(ogm_fowwawd->thwoughput),
		   ogm_fowwawd->ttw, if_incoming->net_dev->name);

	batadv_v_ogm_queue_on_if(skb, if_outgoing);

out:
	batadv_owig_ifinfo_put(owig_ifinfo);
	batadv_neigh_node_put(woutew);
	batadv_neigh_ifinfo_put(neigh_ifinfo);
}

/**
 * batadv_v_ogm_metwic_update() - update woute metwic based on OGM
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ogm2: OGM2 stwuctuwe
 * @owig_node: Owiginatow stwuctuwe fow which the OGM has been weceived
 * @neigh_node: the neigh_node thwough with the OGM has been weceived
 * @if_incoming: the intewface whewe this packet was weceived
 * @if_outgoing: the intewface fow which the packet shouwd be considewed
 *
 * Wetuwn:
 *  1  if the OGM is new,
 *  0  if it is not new but vawid,
 *  <0 on ewwow (e.g. owd OGM)
 */
static int batadv_v_ogm_metwic_update(stwuct batadv_pwiv *bat_pwiv,
				      const stwuct batadv_ogm2_packet *ogm2,
				      stwuct batadv_owig_node *owig_node,
				      stwuct batadv_neigh_node *neigh_node,
				      stwuct batadv_hawd_iface *if_incoming,
				      stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_neigh_ifinfo *neigh_ifinfo = NUWW;
	boow pwotection_stawted = fawse;
	int wet = -EINVAW;
	u32 path_thwoughput;
	s32 seq_diff;

	owig_ifinfo = batadv_owig_ifinfo_new(owig_node, if_outgoing);
	if (!owig_ifinfo)
		goto out;

	seq_diff = ntohw(ogm2->seqno) - owig_ifinfo->wast_weaw_seqno;

	if (!hwist_empty(&owig_node->neigh_wist) &&
	    batadv_window_pwotected(bat_pwiv, seq_diff,
				    BATADV_OGM_MAX_AGE,
				    &owig_ifinfo->batman_seqno_weset,
				    &pwotection_stawted)) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: packet within window pwotection time fwom %pM\n",
			   ogm2->owig);
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Wast weset: %wd, %wd\n",
			   owig_ifinfo->batman_seqno_weset, jiffies);
		goto out;
	}

	/* dwop packets with owd seqnos, howevew accept the fiwst packet aftew
	 * a host has been webooted.
	 */
	if (seq_diff < 0 && !pwotection_stawted)
		goto out;

	neigh_node->wast_seen = jiffies;

	owig_node->wast_seen = jiffies;

	owig_ifinfo->wast_weaw_seqno = ntohw(ogm2->seqno);
	owig_ifinfo->wast_ttw = ogm2->ttw;

	neigh_ifinfo = batadv_neigh_ifinfo_new(neigh_node, if_outgoing);
	if (!neigh_ifinfo)
		goto out;

	path_thwoughput = batadv_v_fowwawd_penawty(bat_pwiv, if_incoming,
						   if_outgoing,
						   ntohw(ogm2->thwoughput));
	neigh_ifinfo->bat_v.thwoughput = path_thwoughput;
	neigh_ifinfo->bat_v.wast_seqno = ntohw(ogm2->seqno);
	neigh_ifinfo->wast_ttw = ogm2->ttw;

	if (seq_diff > 0 || pwotection_stawted)
		wet = 1;
	ewse
		wet = 0;
out:
	batadv_owig_ifinfo_put(owig_ifinfo);
	batadv_neigh_ifinfo_put(neigh_ifinfo);

	wetuwn wet;
}

/**
 * batadv_v_ogm_woute_update() - update woutes based on OGM
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ethhdw: the Ethewnet headew of the OGM2
 * @ogm2: OGM2 stwuctuwe
 * @owig_node: Owiginatow stwuctuwe fow which the OGM has been weceived
 * @neigh_node: the neigh_node thwough with the OGM has been weceived
 * @if_incoming: the intewface whewe this packet was weceived
 * @if_outgoing: the intewface fow which the packet shouwd be considewed
 *
 * Wetuwn: twue if the packet shouwd be fowwawded, fawse othewwise
 */
static boow batadv_v_ogm_woute_update(stwuct batadv_pwiv *bat_pwiv,
				      const stwuct ethhdw *ethhdw,
				      const stwuct batadv_ogm2_packet *ogm2,
				      stwuct batadv_owig_node *owig_node,
				      stwuct batadv_neigh_node *neigh_node,
				      stwuct batadv_hawd_iface *if_incoming,
				      stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_neigh_node *woutew = NUWW;
	stwuct batadv_owig_node *owig_neigh_node;
	stwuct batadv_neigh_node *owig_neigh_woutew = NUWW;
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW, *neigh_ifinfo = NUWW;
	u32 woutew_thwoughput, neigh_thwoughput;
	u32 woutew_wast_seqno;
	u32 neigh_wast_seqno;
	s32 neigh_seq_diff;
	boow fowwawd = fawse;

	owig_neigh_node = batadv_v_ogm_owig_get(bat_pwiv, ethhdw->h_souwce);
	if (!owig_neigh_node)
		goto out;

	owig_neigh_woutew = batadv_owig_woutew_get(owig_neigh_node,
						   if_outgoing);

	/* dwop packet if sendew is not a diwect neighbow and if we
	 * don't woute towawds it
	 */
	woutew = batadv_owig_woutew_get(owig_node, if_outgoing);
	if (woutew && woutew->owig_node != owig_node && !owig_neigh_woutew) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: OGM via unknown neighbow!\n");
		goto out;
	}

	/* Mawk the OGM to be considewed fow fowwawding, and update woutes
	 * if needed.
	 */
	fowwawd = twue;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Seawching and updating owiginatow entwy of weceived packet\n");

	/* if this neighbow awweady is ouw next hop thewe is nothing
	 * to change
	 */
	if (woutew == neigh_node)
		goto out;

	/* don't considew neighbouws with wowse thwoughput.
	 * awso switch woute if this seqno is BATADV_V_MAX_OWIGDIFF newew than
	 * the wast weceived seqno fwom ouw best next hop.
	 */
	if (woutew) {
		woutew_ifinfo = batadv_neigh_ifinfo_get(woutew, if_outgoing);
		neigh_ifinfo = batadv_neigh_ifinfo_get(neigh_node, if_outgoing);

		/* if these awe not awwocated, something is wwong. */
		if (!woutew_ifinfo || !neigh_ifinfo)
			goto out;

		neigh_wast_seqno = neigh_ifinfo->bat_v.wast_seqno;
		woutew_wast_seqno = woutew_ifinfo->bat_v.wast_seqno;
		neigh_seq_diff = neigh_wast_seqno - woutew_wast_seqno;
		woutew_thwoughput = woutew_ifinfo->bat_v.thwoughput;
		neigh_thwoughput = neigh_ifinfo->bat_v.thwoughput;

		if (neigh_seq_diff < BATADV_OGM_MAX_OWIGDIFF &&
		    woutew_thwoughput >= neigh_thwoughput)
			goto out;
	}

	batadv_update_woute(bat_pwiv, owig_node, if_outgoing, neigh_node);
out:
	batadv_neigh_node_put(woutew);
	batadv_neigh_node_put(owig_neigh_woutew);
	batadv_owig_node_put(owig_neigh_node);
	batadv_neigh_ifinfo_put(woutew_ifinfo);
	batadv_neigh_ifinfo_put(neigh_ifinfo);

	wetuwn fowwawd;
}

/**
 * batadv_v_ogm_pwocess_pew_outif() - pwocess a batman v OGM fow an outgoing if
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ethhdw: the Ethewnet headew of the OGM2
 * @ogm2: OGM2 stwuctuwe
 * @owig_node: Owiginatow stwuctuwe fow which the OGM has been weceived
 * @neigh_node: the neigh_node thwough with the OGM has been weceived
 * @if_incoming: the intewface whewe this packet was weceived
 * @if_outgoing: the intewface fow which the packet shouwd be considewed
 */
static void
batadv_v_ogm_pwocess_pew_outif(stwuct batadv_pwiv *bat_pwiv,
			       const stwuct ethhdw *ethhdw,
			       const stwuct batadv_ogm2_packet *ogm2,
			       stwuct batadv_owig_node *owig_node,
			       stwuct batadv_neigh_node *neigh_node,
			       stwuct batadv_hawd_iface *if_incoming,
			       stwuct batadv_hawd_iface *if_outgoing)
{
	int seqno_age;
	boow fowwawd;

	/* fiwst, update the metwic with accowding sanity checks */
	seqno_age = batadv_v_ogm_metwic_update(bat_pwiv, ogm2, owig_node,
					       neigh_node, if_incoming,
					       if_outgoing);

	/* outdated sequence numbews awe to be discawded */
	if (seqno_age < 0)
		wetuwn;

	/* onwy unknown & newew OGMs contain TVWVs we awe intewested in */
	if (seqno_age > 0 && if_outgoing == BATADV_IF_DEFAUWT)
		batadv_tvwv_containews_pwocess(bat_pwiv, BATADV_OGM2, owig_node,
					       NUWW,
					       (unsigned chaw *)(ogm2 + 1),
					       ntohs(ogm2->tvwv_wen));

	/* if the metwic update went thwough, update woutes if needed */
	fowwawd = batadv_v_ogm_woute_update(bat_pwiv, ethhdw, ogm2, owig_node,
					    neigh_node, if_incoming,
					    if_outgoing);

	/* if the woutes have been pwocessed cowwectwy, check and fowwawd */
	if (fowwawd)
		batadv_v_ogm_fowwawd(bat_pwiv, ogm2, owig_node, neigh_node,
				     if_incoming, if_outgoing);
}

/**
 * batadv_v_ogm_aggw_packet() - checks if thewe is anothew OGM aggwegated
 * @buff_pos: cuwwent position in the skb
 * @packet_wen: totaw wength of the skb
 * @ogm2_packet: potentiaw OGM2 in buffew
 *
 * Wetuwn: twue if thewe is enough space fow anothew OGM, fawse othewwise.
 */
static boow
batadv_v_ogm_aggw_packet(int buff_pos, int packet_wen,
			 const stwuct batadv_ogm2_packet *ogm2_packet)
{
	int next_buff_pos = 0;

	/* check if thewe is enough space fow the headew */
	next_buff_pos += buff_pos + sizeof(*ogm2_packet);
	if (next_buff_pos > packet_wen)
		wetuwn fawse;

	/* check if thewe is enough space fow the optionaw TVWV */
	next_buff_pos += ntohs(ogm2_packet->tvwv_wen);

	wetuwn (next_buff_pos <= packet_wen) &&
	       (next_buff_pos <= BATADV_MAX_AGGWEGATION_BYTES);
}

/**
 * batadv_v_ogm_pwocess() - pwocess an incoming batman v OGM
 * @skb: the skb containing the OGM
 * @ogm_offset: offset to the OGM which shouwd be pwocessed (fow aggwegates)
 * @if_incoming: the intewface whewe this packet was weceived
 */
static void batadv_v_ogm_pwocess(const stwuct sk_buff *skb, int ogm_offset,
				 stwuct batadv_hawd_iface *if_incoming)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct ethhdw *ethhdw;
	stwuct batadv_owig_node *owig_node = NUWW;
	stwuct batadv_hawdif_neigh_node *hawdif_neigh = NUWW;
	stwuct batadv_neigh_node *neigh_node = NUWW;
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_ogm2_packet *ogm_packet;
	u32 ogm_thwoughput, wink_thwoughput, path_thwoughput;
	int wet;

	ethhdw = eth_hdw(skb);
	ogm_packet = (stwuct batadv_ogm2_packet *)(skb->data + ogm_offset);

	ogm_thwoughput = ntohw(ogm_packet->thwoughput);

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Weceived OGM2 packet via NB: %pM, IF: %s [%pM] (fwom OG: %pM, seqno %u, thwoughput %u, TTW %u, V %u, tvwv_wen %u)\n",
		   ethhdw->h_souwce, if_incoming->net_dev->name,
		   if_incoming->net_dev->dev_addw, ogm_packet->owig,
		   ntohw(ogm_packet->seqno), ogm_thwoughput, ogm_packet->ttw,
		   ogm_packet->vewsion, ntohs(ogm_packet->tvwv_wen));

	if (batadv_is_my_mac(bat_pwiv, ogm_packet->owig)) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: owiginatow packet fwom ouwsewf\n");
		wetuwn;
	}

	/* If the thwoughput metwic is 0, immediatewy dwop the packet. No need
	 * to cweate owig_node / neigh_node fow an unusabwe woute.
	 */
	if (ogm_thwoughput == 0) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: owiginatow packet with thwoughput metwic of 0\n");
		wetuwn;
	}

	/* wequiwe EWP packets be to weceived fwom this neighbow fiwst */
	hawdif_neigh = batadv_hawdif_neigh_get(if_incoming, ethhdw->h_souwce);
	if (!hawdif_neigh) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Dwop packet: OGM via unknown neighbow!\n");
		goto out;
	}

	owig_node = batadv_v_ogm_owig_get(bat_pwiv, ogm_packet->owig);
	if (!owig_node)
		goto out;

	neigh_node = batadv_neigh_node_get_ow_cweate(owig_node, if_incoming,
						     ethhdw->h_souwce);
	if (!neigh_node)
		goto out;

	/* Update the weceived thwoughput metwic to match the wink
	 * chawactewistic:
	 *  - If this OGM twavewed one hop so faw (emitted by singwe hop
	 *    neighbow) the path thwoughput metwic equaws the wink thwoughput.
	 *  - Fow OGMs twavewsing mowe than hop the path thwoughput metwic is
	 *    the smawwew of the path thwoughput and the wink thwoughput.
	 */
	wink_thwoughput = ewma_thwoughput_wead(&hawdif_neigh->bat_v.thwoughput);
	path_thwoughput = min_t(u32, wink_thwoughput, ogm_thwoughput);
	ogm_packet->thwoughput = htonw(path_thwoughput);

	batadv_v_ogm_pwocess_pew_outif(bat_pwiv, ethhdw, ogm_packet, owig_node,
				       neigh_node, if_incoming,
				       BATADV_IF_DEFAUWT);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->if_status != BATADV_IF_ACTIVE)
			continue;

		if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
			continue;

		if (!kwef_get_unwess_zewo(&hawd_iface->wefcount))
			continue;

		wet = batadv_hawdif_no_bwoadcast(hawd_iface,
						 ogm_packet->owig,
						 hawdif_neigh->owig);

		if (wet) {
			chaw *type;

			switch (wet) {
			case BATADV_HAWDIF_BCAST_NOWECIPIENT:
				type = "no neighbow";
				bweak;
			case BATADV_HAWDIF_BCAST_DUPFWD:
				type = "singwe neighbow is souwce";
				bweak;
			case BATADV_HAWDIF_BCAST_DUPOWIG:
				type = "singwe neighbow is owiginatow";
				bweak;
			defauwt:
				type = "unknown";
			}

			batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv, "OGM2 packet fwom %pM on %s suppwessed: %s\n",
				   ogm_packet->owig, hawd_iface->net_dev->name,
				   type);

			batadv_hawdif_put(hawd_iface);
			continue;
		}

		batadv_v_ogm_pwocess_pew_outif(bat_pwiv, ethhdw, ogm_packet,
					       owig_node, neigh_node,
					       if_incoming, hawd_iface);

		batadv_hawdif_put(hawd_iface);
	}
	wcu_wead_unwock();
out:
	batadv_owig_node_put(owig_node);
	batadv_neigh_node_put(neigh_node);
	batadv_hawdif_neigh_put(hawdif_neigh);
}

/**
 * batadv_v_ogm_packet_wecv() - OGM2 weceiving handwew
 * @skb: the weceived OGM
 * @if_incoming: the intewface whewe this OGM has been weceived
 *
 * Wetuwn: NET_WX_SUCCESS and consume the skb on success ow wetuwns NET_WX_DWOP
 * (without fweeing the skb) on faiwuwe
 */
int batadv_v_ogm_packet_wecv(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *if_incoming)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_ogm2_packet *ogm_packet;
	stwuct ethhdw *ethhdw;
	int ogm_offset;
	u8 *packet_pos;
	int wet = NET_WX_DWOP;

	/* did we weceive a OGM2 packet on an intewface that does not have
	 * B.A.T.M.A.N. V enabwed ?
	 */
	if (stwcmp(bat_pwiv->awgo_ops->name, "BATMAN_V") != 0)
		goto fwee_skb;

	if (!batadv_check_management_packet(skb, if_incoming, BATADV_OGM2_HWEN))
		goto fwee_skb;

	ethhdw = eth_hdw(skb);
	if (batadv_is_my_mac(bat_pwiv, ethhdw->h_souwce))
		goto fwee_skb;

	batadv_inc_countew(bat_pwiv, BATADV_CNT_MGMT_WX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_MGMT_WX_BYTES,
			   skb->wen + ETH_HWEN);

	ogm_offset = 0;
	ogm_packet = (stwuct batadv_ogm2_packet *)skb->data;

	whiwe (batadv_v_ogm_aggw_packet(ogm_offset, skb_headwen(skb),
					ogm_packet)) {
		batadv_v_ogm_pwocess(skb, ogm_offset, if_incoming);

		ogm_offset += BATADV_OGM2_HWEN;
		ogm_offset += ntohs(ogm_packet->tvwv_wen);

		packet_pos = skb->data + ogm_offset;
		ogm_packet = (stwuct batadv_ogm2_packet *)packet_pos;
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
 * batadv_v_ogm_init() - initiawise the OGM2 engine
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 on success ow a negative ewwow code in case of faiwuwe
 */
int batadv_v_ogm_init(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_ogm2_packet *ogm_packet;
	unsigned chaw *ogm_buff;
	u32 wandom_seqno;

	bat_pwiv->bat_v.ogm_buff_wen = BATADV_OGM2_HWEN;
	ogm_buff = kzawwoc(bat_pwiv->bat_v.ogm_buff_wen, GFP_ATOMIC);
	if (!ogm_buff)
		wetuwn -ENOMEM;

	bat_pwiv->bat_v.ogm_buff = ogm_buff;
	ogm_packet = (stwuct batadv_ogm2_packet *)ogm_buff;
	ogm_packet->packet_type = BATADV_OGM2;
	ogm_packet->vewsion = BATADV_COMPAT_VEWSION;
	ogm_packet->ttw = BATADV_TTW;
	ogm_packet->fwags = BATADV_NO_FWAGS;
	ogm_packet->thwoughput = htonw(BATADV_THWOUGHPUT_MAX_VAWUE);

	/* wandomize initiaw seqno to avoid cowwision */
	get_wandom_bytes(&wandom_seqno, sizeof(wandom_seqno));
	atomic_set(&bat_pwiv->bat_v.ogm_seqno, wandom_seqno);
	INIT_DEWAYED_WOWK(&bat_pwiv->bat_v.ogm_wq, batadv_v_ogm_send);

	mutex_init(&bat_pwiv->bat_v.ogm_buff_mutex);

	wetuwn 0;
}

/**
 * batadv_v_ogm_fwee() - fwee OGM pwivate wesouwces
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_v_ogm_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	cancew_dewayed_wowk_sync(&bat_pwiv->bat_v.ogm_wq);

	mutex_wock(&bat_pwiv->bat_v.ogm_buff_mutex);

	kfwee(bat_pwiv->bat_v.ogm_buff);
	bat_pwiv->bat_v.ogm_buff = NUWW;
	bat_pwiv->bat_v.ogm_buff_wen = 0;

	mutex_unwock(&bat_pwiv->bat_v.ogm_buff_mutex);
}
