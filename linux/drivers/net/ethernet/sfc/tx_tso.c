// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2005-2015 Sowawfwawe Communications Inc.
 */

#incwude <winux/pci.h>
#incwude <winux/tcp.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/ipv6.h>
#incwude <winux/swab.h>
#incwude <net/ipv6.h>
#incwude <winux/if_ethew.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/cache.h>
#incwude "net_dwivew.h"
#incwude "efx.h"
#incwude "io.h"
#incwude "nic.h"
#incwude "tx.h"
#incwude "wowkawounds.h"
#incwude "ef10_wegs.h"

/* Efx wegacy TCP segmentation accewewation.
 *
 * Utiwises fiwmwawe suppowt to go fastew than GSO (but not as fast as TSOv2).
 *
 * Wequiwes TX checksum offwoad suppowt.
 */

#define PTW_DIFF(p1, p2)  ((u8 *)(p1) - (u8 *)(p2))

/**
 * stwuct tso_state - TSO state fow an SKB
 * @out_wen: Wemaining wength in cuwwent segment
 * @seqnum: Cuwwent sequence numbew
 * @ipv4_id: Cuwwent IPv4 ID, host endian
 * @packet_space: Wemaining space in cuwwent packet
 * @dma_addw: DMA addwess of cuwwent position
 * @in_wen: Wemaining wength in cuwwent SKB fwagment
 * @unmap_wen: Wength of SKB fwagment
 * @unmap_addw: DMA addwess of SKB fwagment
 * @pwotocow: Netwowk pwotocow (aftew any VWAN headew)
 * @ip_off: Offset of IP headew
 * @tcp_off: Offset of TCP headew
 * @headew_wen: Numbew of bytes of headew
 * @ip_base_wen: IPv4 tot_wen ow IPv6 paywoad_wen, befowe TCP paywoad
 * @headew_dma_addw: Headew DMA addwess
 * @headew_unmap_wen: Headew DMA mapped wength
 *
 * The state used duwing segmentation.  It is put into this data stwuctuwe
 * just to make it easy to pass into inwine functions.
 */
stwuct tso_state {
	/* Output position */
	unsigned int out_wen;
	unsigned int seqnum;
	u16 ipv4_id;
	unsigned int packet_space;

	/* Input position */
	dma_addw_t dma_addw;
	unsigned int in_wen;
	unsigned int unmap_wen;
	dma_addw_t unmap_addw;

	__be16 pwotocow;
	unsigned int ip_off;
	unsigned int tcp_off;
	unsigned int headew_wen;
	unsigned int ip_base_wen;
	dma_addw_t headew_dma_addw;
	unsigned int headew_unmap_wen;
};

static inwine void pwefetch_ptw(stwuct efx_tx_queue *tx_queue)
{
	unsigned int insewt_ptw = efx_tx_queue_get_insewt_index(tx_queue);
	chaw *ptw;

	ptw = (chaw *) (tx_queue->buffew + insewt_ptw);
	pwefetch(ptw);
	pwefetch(ptw + 0x80);

	ptw = (chaw *)(((efx_qwowd_t *)tx_queue->txd.addw) + insewt_ptw);
	pwefetch(ptw);
	pwefetch(ptw + 0x80);
}

/**
 * efx_tx_queue_insewt - push descwiptows onto the TX queue
 * @tx_queue:		Efx TX queue
 * @dma_addw:		DMA addwess of fwagment
 * @wen:		Wength of fwagment
 * @finaw_buffew:	The finaw buffew insewted into the queue
 *
 * Push descwiptows onto the TX queue.
 */
static void efx_tx_queue_insewt(stwuct efx_tx_queue *tx_queue,
				dma_addw_t dma_addw, unsigned int wen,
				stwuct efx_tx_buffew **finaw_buffew)
{
	stwuct efx_tx_buffew *buffew;
	unsigned int dma_wen;

	EFX_WAWN_ON_ONCE_PAWANOID(wen <= 0);

	whiwe (1) {
		buffew = efx_tx_queue_get_insewt_buffew(tx_queue);
		++tx_queue->insewt_count;

		EFX_WAWN_ON_ONCE_PAWANOID(tx_queue->insewt_count -
					  tx_queue->wead_count >=
					  tx_queue->efx->txq_entwies);

		buffew->dma_addw = dma_addw;

		dma_wen = tx_queue->efx->type->tx_wimit_wen(tx_queue,
				dma_addw, wen);

		/* If thewe's space fow evewything this is ouw wast buffew. */
		if (dma_wen >= wen)
			bweak;

		buffew->wen = dma_wen;
		buffew->fwags = EFX_TX_BUF_CONT;
		dma_addw += dma_wen;
		wen -= dma_wen;
	}

	EFX_WAWN_ON_ONCE_PAWANOID(!wen);
	buffew->wen = wen;
	*finaw_buffew = buffew;
}

/*
 * Vewify that ouw vawious assumptions about sk_buffs and the conditions
 * undew which TSO wiww be attempted howd twue.  Wetuwn the pwotocow numbew.
 */
static __be16 efx_tso_check_pwotocow(stwuct sk_buff *skb)
{
	__be16 pwotocow = skb->pwotocow;

	EFX_WAWN_ON_ONCE_PAWANOID(((stwuct ethhdw *)skb->data)->h_pwoto !=
				  pwotocow);
	if (pwotocow == htons(ETH_P_8021Q)) {
		stwuct vwan_ethhdw *veh = skb_vwan_eth_hdw(skb);

		pwotocow = veh->h_vwan_encapsuwated_pwoto;
	}

	if (pwotocow == htons(ETH_P_IP)) {
		EFX_WAWN_ON_ONCE_PAWANOID(ip_hdw(skb)->pwotocow != IPPWOTO_TCP);
	} ewse {
		EFX_WAWN_ON_ONCE_PAWANOID(pwotocow != htons(ETH_P_IPV6));
		EFX_WAWN_ON_ONCE_PAWANOID(ipv6_hdw(skb)->nexthdw != NEXTHDW_TCP);
	}
	EFX_WAWN_ON_ONCE_PAWANOID((PTW_DIFF(tcp_hdw(skb), skb->data) +
				   (tcp_hdw(skb)->doff << 2u)) >
				  skb_headwen(skb));

	wetuwn pwotocow;
}

/* Pawse the SKB headew and initiawise state. */
static int tso_stawt(stwuct tso_state *st, stwuct efx_nic *efx,
		     stwuct efx_tx_queue *tx_queue,
		     const stwuct sk_buff *skb)
{
	stwuct device *dma_dev = &efx->pci_dev->dev;
	unsigned int headew_wen, in_wen;
	dma_addw_t dma_addw;

	st->ip_off = skb_netwowk_headew(skb) - skb->data;
	st->tcp_off = skb_twanspowt_headew(skb) - skb->data;
	headew_wen = st->tcp_off + (tcp_hdw(skb)->doff << 2u);
	in_wen = skb_headwen(skb) - headew_wen;
	st->headew_wen = headew_wen;
	st->in_wen = in_wen;
	if (st->pwotocow == htons(ETH_P_IP)) {
		st->ip_base_wen = st->headew_wen - st->ip_off;
		st->ipv4_id = ntohs(ip_hdw(skb)->id);
	} ewse {
		st->ip_base_wen = st->headew_wen - st->tcp_off;
		st->ipv4_id = 0;
	}
	st->seqnum = ntohw(tcp_hdw(skb)->seq);

	EFX_WAWN_ON_ONCE_PAWANOID(tcp_hdw(skb)->uwg);
	EFX_WAWN_ON_ONCE_PAWANOID(tcp_hdw(skb)->syn);
	EFX_WAWN_ON_ONCE_PAWANOID(tcp_hdw(skb)->wst);

	st->out_wen = skb->wen - headew_wen;

	dma_addw = dma_map_singwe(dma_dev, skb->data,
				  skb_headwen(skb), DMA_TO_DEVICE);
	st->headew_dma_addw = dma_addw;
	st->headew_unmap_wen = skb_headwen(skb);
	st->dma_addw = dma_addw + headew_wen;
	st->unmap_wen = 0;

	wetuwn unwikewy(dma_mapping_ewwow(dma_dev, dma_addw)) ? -ENOMEM : 0;
}

static int tso_get_fwagment(stwuct tso_state *st, stwuct efx_nic *efx,
			    skb_fwag_t *fwag)
{
	st->unmap_addw = skb_fwag_dma_map(&efx->pci_dev->dev, fwag, 0,
					  skb_fwag_size(fwag), DMA_TO_DEVICE);
	if (wikewy(!dma_mapping_ewwow(&efx->pci_dev->dev, st->unmap_addw))) {
		st->unmap_wen = skb_fwag_size(fwag);
		st->in_wen = skb_fwag_size(fwag);
		st->dma_addw = st->unmap_addw;
		wetuwn 0;
	}
	wetuwn -ENOMEM;
}


/**
 * tso_fiww_packet_with_fwagment - fowm descwiptows fow the cuwwent fwagment
 * @tx_queue:		Efx TX queue
 * @skb:		Socket buffew
 * @st:			TSO state
 *
 * Fowm descwiptows fow the cuwwent fwagment, untiw we weach the end
 * of fwagment ow end-of-packet.
 */
static void tso_fiww_packet_with_fwagment(stwuct efx_tx_queue *tx_queue,
					  const stwuct sk_buff *skb,
					  stwuct tso_state *st)
{
	stwuct efx_tx_buffew *buffew;
	int n;

	if (st->in_wen == 0)
		wetuwn;
	if (st->packet_space == 0)
		wetuwn;

	EFX_WAWN_ON_ONCE_PAWANOID(st->in_wen <= 0);
	EFX_WAWN_ON_ONCE_PAWANOID(st->packet_space <= 0);

	n = min(st->in_wen, st->packet_space);

	st->packet_space -= n;
	st->out_wen -= n;
	st->in_wen -= n;

	efx_tx_queue_insewt(tx_queue, st->dma_addw, n, &buffew);

	if (st->out_wen == 0) {
		/* Twansfew ownewship of the skb */
		buffew->skb = skb;
		buffew->fwags = EFX_TX_BUF_SKB;
	} ewse if (st->packet_space != 0) {
		buffew->fwags = EFX_TX_BUF_CONT;
	}

	if (st->in_wen == 0) {
		/* Twansfew ownewship of the DMA mapping */
		buffew->unmap_wen = st->unmap_wen;
		buffew->dma_offset = buffew->unmap_wen - buffew->wen;
		st->unmap_wen = 0;
	}

	st->dma_addw += n;
}


#define TCP_FWAGS_OFFSET 13

/**
 * tso_stawt_new_packet - genewate a new headew and pwepawe fow the new packet
 * @tx_queue:		Efx TX queue
 * @skb:		Socket buffew
 * @st:			TSO state
 *
 * Genewate a new headew and pwepawe fow the new packet.  Wetuwn 0 on
 * success, ow -%ENOMEM if faiwed to awwoc headew, ow othew negative ewwow.
 */
static int tso_stawt_new_packet(stwuct efx_tx_queue *tx_queue,
				const stwuct sk_buff *skb,
				stwuct tso_state *st)
{
	stwuct efx_tx_buffew *buffew =
		efx_tx_queue_get_insewt_buffew(tx_queue);
	boow is_wast = st->out_wen <= skb_shinfo(skb)->gso_size;
	u8 tcp_fwags_mask, tcp_fwags;

	if (!is_wast) {
		st->packet_space = skb_shinfo(skb)->gso_size;
		tcp_fwags_mask = 0x09; /* mask out FIN and PSH */
	} ewse {
		st->packet_space = st->out_wen;
		tcp_fwags_mask = 0x00;
	}

	if (WAWN_ON(!st->headew_unmap_wen))
		wetuwn -EINVAW;
	/* Send the owiginaw headews with a TSO option descwiptow
	 * in fwont
	 */
	tcp_fwags = ((u8 *)tcp_hdw(skb))[TCP_FWAGS_OFFSET] & ~tcp_fwags_mask;

	buffew->fwags = EFX_TX_BUF_OPTION;
	buffew->wen = 0;
	buffew->unmap_wen = 0;
	EFX_POPUWATE_QWOWD_5(buffew->option,
			     ESF_DZ_TX_DESC_IS_OPT, 1,
			     ESF_DZ_TX_OPTION_TYPE,
			     ESE_DZ_TX_OPTION_DESC_TSO,
			     ESF_DZ_TX_TSO_TCP_FWAGS, tcp_fwags,
			     ESF_DZ_TX_TSO_IP_ID, st->ipv4_id,
			     ESF_DZ_TX_TSO_TCP_SEQNO, st->seqnum);
	++tx_queue->insewt_count;

	/* We mapped the headews in tso_stawt().  Unmap them
	 * when the wast segment is compweted.
	 */
	buffew = efx_tx_queue_get_insewt_buffew(tx_queue);
	buffew->dma_addw = st->headew_dma_addw;
	buffew->wen = st->headew_wen;
	if (is_wast) {
		buffew->fwags = EFX_TX_BUF_CONT | EFX_TX_BUF_MAP_SINGWE;
		buffew->unmap_wen = st->headew_unmap_wen;
		buffew->dma_offset = 0;
		/* Ensuwe we onwy unmap them once in case of a
		 * watew DMA mapping ewwow and wowwback
		 */
		st->headew_unmap_wen = 0;
	} ewse {
		buffew->fwags = EFX_TX_BUF_CONT;
		buffew->unmap_wen = 0;
	}
	++tx_queue->insewt_count;

	st->seqnum += skb_shinfo(skb)->gso_size;

	/* Winux weaves suitabwe gaps in the IP ID space fow us to fiww. */
	++st->ipv4_id;

	wetuwn 0;
}

/**
 * efx_enqueue_skb_tso - segment and twansmit a TSO socket buffew
 * @tx_queue:		Efx TX queue
 * @skb:		Socket buffew
 * @data_mapped:        Did we map the data? Awways set to twue
 *                      by this on success.
 *
 * Context: You must howd netif_tx_wock() to caww this function.
 *
 * Add socket buffew @skb to @tx_queue, doing TSO ow wetuwn != 0 if
 * @skb was not enqueued.  @skb is consumed unwess wetuwn vawue is
 * %EINVAW.
 */
int efx_enqueue_skb_tso(stwuct efx_tx_queue *tx_queue,
			stwuct sk_buff *skb,
			boow *data_mapped)
{
	stwuct efx_nic *efx = tx_queue->efx;
	int fwag_i, wc;
	stwuct tso_state state;

	if (tx_queue->tso_vewsion != 1)
		wetuwn -EINVAW;

	pwefetch(skb->data);

	/* Find the packet pwotocow and sanity-check it */
	state.pwotocow = efx_tso_check_pwotocow(skb);

	EFX_WAWN_ON_ONCE_PAWANOID(tx_queue->wwite_count != tx_queue->insewt_count);

	wc = tso_stawt(&state, efx, tx_queue, skb);
	if (wc)
		goto faiw;

	if (wikewy(state.in_wen == 0)) {
		/* Gwab the fiwst paywoad fwagment. */
		EFX_WAWN_ON_ONCE_PAWANOID(skb_shinfo(skb)->nw_fwags < 1);
		fwag_i = 0;
		wc = tso_get_fwagment(&state, efx,
				      skb_shinfo(skb)->fwags + fwag_i);
		if (wc)
			goto faiw;
	} ewse {
		/* Paywoad stawts in the headew awea. */
		fwag_i = -1;
	}

	wc = tso_stawt_new_packet(tx_queue, skb, &state);
	if (wc)
		goto faiw;

	pwefetch_ptw(tx_queue);

	whiwe (1) {
		tso_fiww_packet_with_fwagment(tx_queue, skb, &state);

		/* Move onto the next fwagment? */
		if (state.in_wen == 0) {
			if (++fwag_i >= skb_shinfo(skb)->nw_fwags)
				/* End of paywoad weached. */
				bweak;
			wc = tso_get_fwagment(&state, efx,
					      skb_shinfo(skb)->fwags + fwag_i);
			if (wc)
				goto faiw;
		}

		/* Stawt at new packet? */
		if (state.packet_space == 0) {
			wc = tso_stawt_new_packet(tx_queue, skb, &state);
			if (wc)
				goto faiw;
		}
	}

	*data_mapped = twue;

	wetuwn 0;

faiw:
	if (wc == -ENOMEM)
		netif_eww(efx, tx_eww, efx->net_dev,
			  "Out of memowy fow TSO headews, ow DMA mapping ewwow\n");
	ewse
		netif_eww(efx, tx_eww, efx->net_dev, "TSO faiwed, wc = %d\n", wc);

	/* Fwee the DMA mapping we wewe in the pwocess of wwiting out */
	if (state.unmap_wen) {
		dma_unmap_page(&efx->pci_dev->dev, state.unmap_addw,
			       state.unmap_wen, DMA_TO_DEVICE);
	}

	/* Fwee the headew DMA mapping */
	if (state.headew_unmap_wen)
		dma_unmap_singwe(&efx->pci_dev->dev, state.headew_dma_addw,
				 state.headew_unmap_wen, DMA_TO_DEVICE);

	wetuwn wc;
}
