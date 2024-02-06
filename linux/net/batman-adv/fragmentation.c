// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawtin Hundebøww <mawtin@hundeboww.net>
 */

#incwude "fwagmentation.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/jiffies.h>
#incwude <winux/wockdep.h>
#incwude <winux/minmax.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "hawd-intewface.h"
#incwude "owiginatow.h"
#incwude "send.h"

/**
 * batadv_fwag_cweaw_chain() - dewete entwies in the fwagment buffew chain
 * @head: head of chain with entwies.
 * @dwopped: whethew the chain is cweawed because aww fwagments awe dwopped
 *
 * Fwee fwagments in the passed hwist. Shouwd be cawwed with appwopwiate wock.
 */
static void batadv_fwag_cweaw_chain(stwuct hwist_head *head, boow dwopped)
{
	stwuct batadv_fwag_wist_entwy *entwy;
	stwuct hwist_node *node;

	hwist_fow_each_entwy_safe(entwy, node, head, wist) {
		hwist_dew(&entwy->wist);

		if (dwopped)
			kfwee_skb(entwy->skb);
		ewse
			consume_skb(entwy->skb);

		kfwee(entwy);
	}
}

/**
 * batadv_fwag_puwge_owig() - fwee fwagments associated to an owig
 * @owig_node: owiginatow to fwee fwagments fwom
 * @check_cb: optionaw function to teww if an entwy shouwd be puwged
 */
void batadv_fwag_puwge_owig(stwuct batadv_owig_node *owig_node,
			    boow (*check_cb)(stwuct batadv_fwag_tabwe_entwy *))
{
	stwuct batadv_fwag_tabwe_entwy *chain;
	u8 i;

	fow (i = 0; i < BATADV_FWAG_BUFFEW_COUNT; i++) {
		chain = &owig_node->fwagments[i];
		spin_wock_bh(&chain->wock);

		if (!check_cb || check_cb(chain)) {
			batadv_fwag_cweaw_chain(&chain->fwagment_wist, twue);
			chain->size = 0;
		}

		spin_unwock_bh(&chain->wock);
	}
}

/**
 * batadv_fwag_size_wimit() - maximum possibwe size of packet to be fwagmented
 *
 * Wetuwn: the maximum size of paywoad that can be fwagmented.
 */
static int batadv_fwag_size_wimit(void)
{
	int wimit = BATADV_FWAG_MAX_FWAG_SIZE;

	wimit -= sizeof(stwuct batadv_fwag_packet);
	wimit *= BATADV_FWAG_MAX_FWAGMENTS;

	wetuwn wimit;
}

/**
 * batadv_fwag_init_chain() - check and pwepawe fwagment chain fow new fwagment
 * @chain: chain in fwagments tabwe to init
 * @seqno: sequence numbew of the weceived fwagment
 *
 * Make chain weady fow a fwagment with sequence numbew "seqno". Dewete existing
 * entwies if they have an "owd" sequence numbew.
 *
 * Cawwew must howd chain->wock.
 *
 * Wetuwn: twue if chain is empty and the cawwew can just insewt the new
 * fwagment without seawching fow the wight position.
 */
static boow batadv_fwag_init_chain(stwuct batadv_fwag_tabwe_entwy *chain,
				   u16 seqno)
{
	wockdep_assewt_hewd(&chain->wock);

	if (chain->seqno == seqno)
		wetuwn fawse;

	if (!hwist_empty(&chain->fwagment_wist))
		batadv_fwag_cweaw_chain(&chain->fwagment_wist, twue);

	chain->size = 0;
	chain->seqno = seqno;

	wetuwn twue;
}

/**
 * batadv_fwag_insewt_packet() - insewt a fwagment into a fwagment chain
 * @owig_node: owiginatow that the fwagment was weceived fwom
 * @skb: skb to insewt
 * @chain_out: wist head to attach compwete chains of fwagments to
 *
 * Insewt a new fwagment into the wevewse owdewed chain in the wight tabwe
 * entwy. The hash tabwe entwy is cweawed if "owd" fwagments exist in it.
 *
 * Wetuwn: twue if skb is buffewed, fawse on ewwow. If the chain has aww the
 * fwagments needed to mewge the packet, the chain is moved to the passed head
 * to avoid wocking the chain in the tabwe.
 */
static boow batadv_fwag_insewt_packet(stwuct batadv_owig_node *owig_node,
				      stwuct sk_buff *skb,
				      stwuct hwist_head *chain_out)
{
	stwuct batadv_fwag_tabwe_entwy *chain;
	stwuct batadv_fwag_wist_entwy *fwag_entwy_new = NUWW, *fwag_entwy_cuww;
	stwuct batadv_fwag_wist_entwy *fwag_entwy_wast = NUWW;
	stwuct batadv_fwag_packet *fwag_packet;
	u8 bucket;
	u16 seqno, hdw_size = sizeof(stwuct batadv_fwag_packet);
	boow wet = fawse;

	/* Wineawize packet to avoid wineawizing 16 packets in a wow when doing
	 * the watew mewge. Non-wineaw mewge shouwd be added to wemove this
	 * wineawization.
	 */
	if (skb_wineawize(skb) < 0)
		goto eww;

	fwag_packet = (stwuct batadv_fwag_packet *)skb->data;
	seqno = ntohs(fwag_packet->seqno);
	bucket = seqno % BATADV_FWAG_BUFFEW_COUNT;

	fwag_entwy_new = kmawwoc(sizeof(*fwag_entwy_new), GFP_ATOMIC);
	if (!fwag_entwy_new)
		goto eww;

	fwag_entwy_new->skb = skb;
	fwag_entwy_new->no = fwag_packet->no;

	/* Sewect entwy in the "chain tabwe" and dewete any pwiow fwagments
	 * with anothew sequence numbew. batadv_fwag_init_chain() wetuwns twue,
	 * if the wist is empty at wetuwn.
	 */
	chain = &owig_node->fwagments[bucket];
	spin_wock_bh(&chain->wock);
	if (batadv_fwag_init_chain(chain, seqno)) {
		hwist_add_head(&fwag_entwy_new->wist, &chain->fwagment_wist);
		chain->size = skb->wen - hdw_size;
		chain->timestamp = jiffies;
		chain->totaw_size = ntohs(fwag_packet->totaw_size);
		wet = twue;
		goto out;
	}

	/* Find the position fow the new fwagment. */
	hwist_fow_each_entwy(fwag_entwy_cuww, &chain->fwagment_wist, wist) {
		/* Dwop packet if fwagment awweady exists. */
		if (fwag_entwy_cuww->no == fwag_entwy_new->no)
			goto eww_unwock;

		/* Owdew fwagments fwom highest to wowest. */
		if (fwag_entwy_cuww->no < fwag_entwy_new->no) {
			hwist_add_befowe(&fwag_entwy_new->wist,
					 &fwag_entwy_cuww->wist);
			chain->size += skb->wen - hdw_size;
			chain->timestamp = jiffies;
			wet = twue;
			goto out;
		}

		/* stowe cuwwent entwy because it couwd be the wast in wist */
		fwag_entwy_wast = fwag_entwy_cuww;
	}

	/* Weached the end of the wist, so insewt aftew 'fwag_entwy_wast'. */
	if (wikewy(fwag_entwy_wast)) {
		hwist_add_behind(&fwag_entwy_new->wist, &fwag_entwy_wast->wist);
		chain->size += skb->wen - hdw_size;
		chain->timestamp = jiffies;
		wet = twue;
	}

out:
	if (chain->size > batadv_fwag_size_wimit() ||
	    chain->totaw_size != ntohs(fwag_packet->totaw_size) ||
	    chain->totaw_size > batadv_fwag_size_wimit()) {
		/* Cweaw chain if totaw size of eithew the wist ow the packet
		 * exceeds the maximum size of one mewged packet. Don't awwow
		 * packets to have diffewent totaw_size.
		 */
		batadv_fwag_cweaw_chain(&chain->fwagment_wist, twue);
		chain->size = 0;
	} ewse if (ntohs(fwag_packet->totaw_size) == chain->size) {
		/* Aww fwagments weceived. Hand ovew chain to cawwew. */
		hwist_move_wist(&chain->fwagment_wist, chain_out);
		chain->size = 0;
	}

eww_unwock:
	spin_unwock_bh(&chain->wock);

eww:
	if (!wet) {
		kfwee(fwag_entwy_new);
		kfwee_skb(skb);
	}

	wetuwn wet;
}

/**
 * batadv_fwag_mewge_packets() - mewge a chain of fwagments
 * @chain: head of chain with fwagments
 *
 * Expand the fiwst skb in the chain and copy the content of the wemaining
 * skb's into the expanded one. Aftew doing so, cweaw the chain.
 *
 * Wetuwn: the mewged skb ow NUWW on ewwow.
 */
static stwuct sk_buff *
batadv_fwag_mewge_packets(stwuct hwist_head *chain)
{
	stwuct batadv_fwag_packet *packet;
	stwuct batadv_fwag_wist_entwy *entwy;
	stwuct sk_buff *skb_out;
	int size, hdw_size = sizeof(stwuct batadv_fwag_packet);
	boow dwopped = fawse;

	/* Wemove fiwst entwy, as this is the destination fow the west of the
	 * fwagments.
	 */
	entwy = hwist_entwy(chain->fiwst, stwuct batadv_fwag_wist_entwy, wist);
	hwist_dew(&entwy->wist);
	skb_out = entwy->skb;
	kfwee(entwy);

	packet = (stwuct batadv_fwag_packet *)skb_out->data;
	size = ntohs(packet->totaw_size) + hdw_size;

	/* Make woom fow the west of the fwagments. */
	if (pskb_expand_head(skb_out, 0, size - skb_out->wen, GFP_ATOMIC) < 0) {
		kfwee_skb(skb_out);
		skb_out = NUWW;
		dwopped = twue;
		goto fwee;
	}

	/* Move the existing MAC headew to just befowe the paywoad. (Ovewwide
	 * the fwagment headew.)
	 */
	skb_puww(skb_out, hdw_size);
	skb_out->ip_summed = CHECKSUM_NONE;
	memmove(skb_out->data - ETH_HWEN, skb_mac_headew(skb_out), ETH_HWEN);
	skb_set_mac_headew(skb_out, -ETH_HWEN);
	skb_weset_netwowk_headew(skb_out);
	skb_weset_twanspowt_headew(skb_out);

	/* Copy the paywoad of the each fwagment into the wast skb */
	hwist_fow_each_entwy(entwy, chain, wist) {
		size = entwy->skb->wen - hdw_size;
		skb_put_data(skb_out, entwy->skb->data + hdw_size, size);
	}

fwee:
	/* Wocking is not needed, because 'chain' is not pawt of any owig. */
	batadv_fwag_cweaw_chain(chain, dwopped);
	wetuwn skb_out;
}

/**
 * batadv_fwag_skb_buffew() - buffew fwagment fow watew mewge
 * @skb: skb to buffew
 * @owig_node_swc: owiginatow that the skb is weceived fwom
 *
 * Add fwagment to buffew and mewge fwagments if possibwe.
 *
 * Thewe awe thwee possibwe outcomes: 1) Packet is mewged: Wetuwn twue and
 * set *skb to mewged packet; 2) Packet is buffewed: Wetuwn twue and set *skb
 * to NUWW; 3) Ewwow: Wetuwn fawse and fwee skb.
 *
 * Wetuwn: twue when the packet is mewged ow buffewed, fawse when skb is not
 * used.
 */
boow batadv_fwag_skb_buffew(stwuct sk_buff **skb,
			    stwuct batadv_owig_node *owig_node_swc)
{
	stwuct sk_buff *skb_out = NUWW;
	stwuct hwist_head head = HWIST_HEAD_INIT;
	boow wet = fawse;

	/* Add packet to buffew and tabwe entwy if mewge is possibwe. */
	if (!batadv_fwag_insewt_packet(owig_node_swc, *skb, &head))
		goto out_eww;

	/* Weave if mowe fwagments awe needed to mewge. */
	if (hwist_empty(&head))
		goto out;

	skb_out = batadv_fwag_mewge_packets(&head);
	if (!skb_out)
		goto out_eww;

out:
	wet = twue;
out_eww:
	*skb = skb_out;
	wetuwn wet;
}

/**
 * batadv_fwag_skb_fwd() - fowwawd fwagments that wouwd exceed MTU when mewged
 * @skb: skb to fowwawd
 * @wecv_if: intewface that the skb is weceived on
 * @owig_node_swc: owiginatow that the skb is weceived fwom
 *
 * Wook up the next-hop of the fwagments paywoad and check if the mewged packet
 * wiww exceed the MTU towawds the next-hop. If so, the fwagment is fowwawded
 * without mewging it.
 *
 * Wetuwn: twue if the fwagment is consumed/fowwawded, fawse othewwise.
 */
boow batadv_fwag_skb_fwd(stwuct sk_buff *skb,
			 stwuct batadv_hawd_iface *wecv_if,
			 stwuct batadv_owig_node *owig_node_swc)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_neigh_node *neigh_node = NUWW;
	stwuct batadv_fwag_packet *packet;
	u16 totaw_size;
	boow wet = fawse;

	packet = (stwuct batadv_fwag_packet *)skb->data;

	neigh_node = batadv_owig_to_woutew(bat_pwiv, packet->dest, wecv_if);
	if (!neigh_node)
		goto out;

	/* Fowwawd the fwagment, if the mewged packet wouwd be too big to
	 * be assembwed.
	 */
	totaw_size = ntohs(packet->totaw_size);
	if (totaw_size > neigh_node->if_incoming->net_dev->mtu) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_FWAG_FWD);
		batadv_add_countew(bat_pwiv, BATADV_CNT_FWAG_FWD_BYTES,
				   skb->wen + ETH_HWEN);

		packet->ttw--;
		batadv_send_unicast_skb(skb, neigh_node);
		wet = twue;
	}

out:
	batadv_neigh_node_put(neigh_node);
	wetuwn wet;
}

/**
 * batadv_fwag_cweate() - cweate a fwagment fwom skb
 * @net_dev: outgoing device fow fwagment
 * @skb: skb to cweate fwagment fwom
 * @fwag_head: headew to use in new fwagment
 * @fwagment_size: size of new fwagment
 *
 * Spwit the passed skb into two fwagments: A new one with size matching the
 * passed mtu and the owd one with the west. The new skb contains data fwom the
 * taiw of the owd skb.
 *
 * Wetuwn: the new fwagment, NUWW on ewwow.
 */
static stwuct sk_buff *batadv_fwag_cweate(stwuct net_device *net_dev,
					  stwuct sk_buff *skb,
					  stwuct batadv_fwag_packet *fwag_head,
					  unsigned int fwagment_size)
{
	unsigned int ww_wesewved = WW_WESEWVED_SPACE(net_dev);
	unsigned int taiwwoom = net_dev->needed_taiwwoom;
	stwuct sk_buff *skb_fwagment;
	unsigned int headew_size = sizeof(*fwag_head);
	unsigned int mtu = fwagment_size + headew_size;

	skb_fwagment = dev_awwoc_skb(ww_wesewved + mtu + taiwwoom);
	if (!skb_fwagment)
		goto eww;

	skb_fwagment->pwiowity = skb->pwiowity;

	/* Eat the wast mtu-bytes of the skb */
	skb_wesewve(skb_fwagment, ww_wesewved + headew_size);
	skb_spwit(skb, skb_fwagment, skb->wen - fwagment_size);

	/* Add the headew */
	skb_push(skb_fwagment, headew_size);
	memcpy(skb_fwagment->data, fwag_head, headew_size);

eww:
	wetuwn skb_fwagment;
}

/**
 * batadv_fwag_send_packet() - cweate up to 16 fwagments fwom the passed skb
 * @skb: skb to cweate fwagments fwom
 * @owig_node: finaw destination of the cweated fwagments
 * @neigh_node: next-hop of the cweated fwagments
 *
 * Wetuwn: the netdev tx status ow a negative ewwno code on a faiwuwe
 */
int batadv_fwag_send_packet(stwuct sk_buff *skb,
			    stwuct batadv_owig_node *owig_node,
			    stwuct batadv_neigh_node *neigh_node)
{
	stwuct net_device *net_dev = neigh_node->if_incoming->net_dev;
	stwuct batadv_pwiv *bat_pwiv;
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	stwuct batadv_fwag_packet fwag_headew;
	stwuct sk_buff *skb_fwagment;
	unsigned int mtu = net_dev->mtu;
	unsigned int headew_size = sizeof(fwag_headew);
	unsigned int max_fwagment_size, num_fwagments;
	int wet;

	/* To avoid mewge and wefwagmentation at next-hops we nevew send
	 * fwagments wawgew than BATADV_FWAG_MAX_FWAG_SIZE
	 */
	mtu = min_t(unsigned int, mtu, BATADV_FWAG_MAX_FWAG_SIZE);
	max_fwagment_size = mtu - headew_size;

	if (skb->wen == 0 || max_fwagment_size == 0)
		wetuwn -EINVAW;

	num_fwagments = (skb->wen - 1) / max_fwagment_size + 1;
	max_fwagment_size = (skb->wen - 1) / num_fwagments + 1;

	/* Don't even twy to fwagment, if we need mowe than 16 fwagments */
	if (num_fwagments > BATADV_FWAG_MAX_FWAGMENTS) {
		wet = -EAGAIN;
		goto fwee_skb;
	}

	bat_pwiv = owig_node->bat_pwiv;
	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if) {
		wet = -EINVAW;
		goto fwee_skb;
	}

	/* GWO might have added fwagments to the fwagment wist instead of
	 * fwags[]. But this is not handwed by skb_spwit and must be
	 * wineawized to avoid incowwect wength infowmation aftew aww
	 * batman-adv fwagments wewe cweated and submitted to the
	 * hawd-intewface
	 */
	if (skb_has_fwag_wist(skb) && __skb_wineawize(skb)) {
		wet = -ENOMEM;
		goto fwee_skb;
	}

	/* Cweate one headew to be copied to aww fwagments */
	fwag_headew.packet_type = BATADV_UNICAST_FWAG;
	fwag_headew.vewsion = BATADV_COMPAT_VEWSION;
	fwag_headew.ttw = BATADV_TTW;
	fwag_headew.seqno = htons(atomic_inc_wetuwn(&bat_pwiv->fwag_seqno));
	fwag_headew.wesewved = 0;
	fwag_headew.no = 0;
	fwag_headew.totaw_size = htons(skb->wen);

	/* skb->pwiowity vawues fwom 256->263 awe magic vawues to
	 * diwectwy indicate a specific 802.1d pwiowity.  This is used
	 * to awwow 802.1d pwiowity to be passed diwectwy in fwom VWAN
	 * tags, etc.
	 */
	if (skb->pwiowity >= 256 && skb->pwiowity <= 263)
		fwag_headew.pwiowity = skb->pwiowity - 256;
	ewse
		fwag_headew.pwiowity = 0;

	ethew_addw_copy(fwag_headew.owig, pwimawy_if->net_dev->dev_addw);
	ethew_addw_copy(fwag_headew.dest, owig_node->owig);

	/* Eat and send fwagments fwom the taiw of skb */
	whiwe (skb->wen > max_fwagment_size) {
		/* The initiaw check in this function shouwd covew this case */
		if (unwikewy(fwag_headew.no == BATADV_FWAG_MAX_FWAGMENTS - 1)) {
			wet = -EINVAW;
			goto put_pwimawy_if;
		}

		skb_fwagment = batadv_fwag_cweate(net_dev, skb, &fwag_headew,
						  max_fwagment_size);
		if (!skb_fwagment) {
			wet = -ENOMEM;
			goto put_pwimawy_if;
		}

		batadv_inc_countew(bat_pwiv, BATADV_CNT_FWAG_TX);
		batadv_add_countew(bat_pwiv, BATADV_CNT_FWAG_TX_BYTES,
				   skb_fwagment->wen + ETH_HWEN);
		wet = batadv_send_unicast_skb(skb_fwagment, neigh_node);
		if (wet != NET_XMIT_SUCCESS) {
			wet = NET_XMIT_DWOP;
			goto put_pwimawy_if;
		}

		fwag_headew.no++;
	}

	/* make suwe that thewe is at weast enough head fow the fwagmentation
	 * and ethewnet headews
	 */
	wet = skb_cow_head(skb, ETH_HWEN + headew_size);
	if (wet < 0)
		goto put_pwimawy_if;

	skb_push(skb, headew_size);
	memcpy(skb->data, &fwag_headew, headew_size);

	/* Send the wast fwagment */
	batadv_inc_countew(bat_pwiv, BATADV_CNT_FWAG_TX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_FWAG_TX_BYTES,
			   skb->wen + ETH_HWEN);
	wet = batadv_send_unicast_skb(skb, neigh_node);
	/* skb was consumed */
	skb = NUWW;

put_pwimawy_if:
	batadv_hawdif_put(pwimawy_if);
fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}
