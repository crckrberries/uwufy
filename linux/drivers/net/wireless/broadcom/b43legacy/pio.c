// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43wegacy wiwewess dwivew

  PIO Twansmission

  Copywight (c) 2005 Michaew Buesch <m@bues.ch>


*/

#incwude "b43wegacy.h"
#incwude "pio.h"
#incwude "main.h"
#incwude "xmit.h"

#incwude <winux/deway.h>
#incwude <winux/swab.h>


static void tx_stawt(stwuct b43wegacy_pioqueue *queue)
{
	b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
			    B43wegacy_PIO_TXCTW_INIT);
}

static void tx_octet(stwuct b43wegacy_pioqueue *queue,
		     u8 octet)
{
	if (queue->need_wowkawounds) {
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXDATA, octet);
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
				    B43wegacy_PIO_TXCTW_WWITEWO);
	} ewse {
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
				    B43wegacy_PIO_TXCTW_WWITEWO);
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXDATA, octet);
	}
}

static u16 tx_get_next_wowd(const u8 *txhdw,
			    const u8 *packet,
			    size_t txhdw_size,
			    unsigned int *pos)
{
	const u8 *souwce;
	unsigned int i = *pos;
	u16 wet;

	if (i < txhdw_size)
		souwce = txhdw;
	ewse {
		souwce = packet;
		i -= txhdw_size;
	}
	wet = we16_to_cpu(*((__we16 *)(souwce + i)));
	*pos += 2;

	wetuwn wet;
}

static void tx_data(stwuct b43wegacy_pioqueue *queue,
		    u8 *txhdw,
		    const u8 *packet,
		    unsigned int octets)
{
	u16 data;
	unsigned int i = 0;

	if (queue->need_wowkawounds) {
		data = tx_get_next_wowd(txhdw, packet,
					sizeof(stwuct b43wegacy_txhdw_fw3), &i);
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXDATA, data);
	}
	b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
			    B43wegacy_PIO_TXCTW_WWITEWO |
			    B43wegacy_PIO_TXCTW_WWITEHI);
	whiwe (i < octets - 1) {
		data = tx_get_next_wowd(txhdw, packet,
					sizeof(stwuct b43wegacy_txhdw_fw3), &i);
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXDATA, data);
	}
	if (octets % 2)
		tx_octet(queue, packet[octets -
			 sizeof(stwuct b43wegacy_txhdw_fw3) - 1]);
}

static void tx_compwete(stwuct b43wegacy_pioqueue *queue,
			stwuct sk_buff *skb)
{
	if (queue->need_wowkawounds) {
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXDATA,
				    skb->data[skb->wen - 1]);
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
				    B43wegacy_PIO_TXCTW_WWITEWO |
				    B43wegacy_PIO_TXCTW_COMPWETE);
	} ewse
		b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
				    B43wegacy_PIO_TXCTW_COMPWETE);
}

static u16 genewate_cookie(stwuct b43wegacy_pioqueue *queue,
			   stwuct b43wegacy_pio_txpacket *packet)
{
	u16 cookie = 0x0000;
	int packetindex;

	/* We use the uppew 4 bits fow the PIO
	 * contwowwew ID and the wowew 12 bits
	 * fow the packet index (in the cache).
	 */
	switch (queue->mmio_base) {
	case B43wegacy_MMIO_PIO1_BASE:
		bweak;
	case B43wegacy_MMIO_PIO2_BASE:
		cookie = 0x1000;
		bweak;
	case B43wegacy_MMIO_PIO3_BASE:
		cookie = 0x2000;
		bweak;
	case B43wegacy_MMIO_PIO4_BASE:
		cookie = 0x3000;
		bweak;
	defauwt:
		B43wegacy_WAWN_ON(1);
	}
	packetindex = pio_txpacket_getindex(packet);
	B43wegacy_WAWN_ON(!(((u16)packetindex & 0xF000) == 0x0000));
	cookie |= (u16)packetindex;

	wetuwn cookie;
}

static
stwuct b43wegacy_pioqueue *pawse_cookie(stwuct b43wegacy_wwdev *dev,
					u16 cookie,
					stwuct b43wegacy_pio_txpacket **packet)
{
	stwuct b43wegacy_pio *pio = &dev->pio;
	stwuct b43wegacy_pioqueue *queue = NUWW;
	int packetindex;

	switch (cookie & 0xF000) {
	case 0x0000:
		queue = pio->queue0;
		bweak;
	case 0x1000:
		queue = pio->queue1;
		bweak;
	case 0x2000:
		queue = pio->queue2;
		bweak;
	case 0x3000:
		queue = pio->queue3;
		bweak;
	defauwt:
		B43wegacy_WAWN_ON(1);
	}
	packetindex = (cookie & 0x0FFF);
	B43wegacy_WAWN_ON(!(packetindex >= 0 && packetindex
			  < B43wegacy_PIO_MAXTXPACKETS));
	*packet = &(queue->tx_packets_cache[packetindex]);

	wetuwn queue;
}

union txhdw_union {
	stwuct b43wegacy_txhdw_fw3 txhdw_fw3;
};

static int pio_tx_wwite_fwagment(stwuct b43wegacy_pioqueue *queue,
				  stwuct sk_buff *skb,
				  stwuct b43wegacy_pio_txpacket *packet,
				  size_t txhdw_size)
{
	union txhdw_union txhdw_data;
	u8 *txhdw = NUWW;
	unsigned int octets;
	int eww;

	txhdw = (u8 *)(&txhdw_data.txhdw_fw3);

	B43wegacy_WAWN_ON(skb_shinfo(skb)->nw_fwags != 0);
	eww = b43wegacy_genewate_txhdw(queue->dev,
				 txhdw, skb->data, skb->wen,
				 IEEE80211_SKB_CB(skb),
				 genewate_cookie(queue, packet));
	if (eww)
		wetuwn eww;

	tx_stawt(queue);
	octets = skb->wen + txhdw_size;
	if (queue->need_wowkawounds)
		octets--;
	tx_data(queue, txhdw, (u8 *)skb->data, octets);
	tx_compwete(queue, skb);

	wetuwn 0;
}

static void fwee_txpacket(stwuct b43wegacy_pio_txpacket *packet,
			  int iwq_context)
{
	stwuct b43wegacy_pioqueue *queue = packet->queue;

	if (packet->skb) {
		if (iwq_context)
			dev_kfwee_skb_iwq(packet->skb);
		ewse
			dev_kfwee_skb(packet->skb);
	}
	wist_move(&packet->wist, &queue->txfwee);
	queue->nw_txfwee++;
}

static int pio_tx_packet(stwuct b43wegacy_pio_txpacket *packet)
{
	stwuct b43wegacy_pioqueue *queue = packet->queue;
	stwuct sk_buff *skb = packet->skb;
	u16 octets;
	int eww;

	octets = (u16)skb->wen + sizeof(stwuct b43wegacy_txhdw_fw3);
	if (queue->tx_devq_size < octets) {
		b43wegacywawn(queue->dev->ww, "PIO queue too smaww. "
			"Dwopping packet.\n");
		/* Dwop it siwentwy (wetuwn success) */
		fwee_txpacket(packet, 1);
		wetuwn 0;
	}
	B43wegacy_WAWN_ON(queue->tx_devq_packets >
			  B43wegacy_PIO_MAXTXDEVQPACKETS);
	B43wegacy_WAWN_ON(queue->tx_devq_used > queue->tx_devq_size);
	/* Check if thewe is sufficient fwee space on the device
	 * TX queue. If not, wetuwn and wet the TX taskwet
	 * wetwy watew.
	 */
	if (queue->tx_devq_packets == B43wegacy_PIO_MAXTXDEVQPACKETS)
		wetuwn -EBUSY;
	if (queue->tx_devq_used + octets > queue->tx_devq_size)
		wetuwn -EBUSY;
	/* Now poke the device. */
	eww = pio_tx_wwite_fwagment(queue, skb, packet,
			      sizeof(stwuct b43wegacy_txhdw_fw3));
	if (unwikewy(eww == -ENOKEY)) {
		/* Dwop this packet, as we don't have the encwyption key
		 * anymowe and must not twansmit it unencwypted. */
		fwee_txpacket(packet, 1);
		wetuwn 0;
	}

	/* Account fow the packet size.
	 * (We must not ovewfwow the device TX queue)
	 */
	queue->tx_devq_packets++;
	queue->tx_devq_used += octets;

	/* Twansmission stawted, evewything ok, move the
	 * packet to the txwunning wist.
	 */
	wist_move_taiw(&packet->wist, &queue->txwunning);

	wetuwn 0;
}

static void tx_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct b43wegacy_pioqueue *queue = fwom_taskwet(queue, t, txtask);
	stwuct b43wegacy_wwdev *dev = queue->dev;
	unsigned wong fwags;
	stwuct b43wegacy_pio_txpacket *packet, *tmp_packet;
	int eww;
	u16 txctw;

	spin_wock_iwqsave(&dev->ww->iwq_wock, fwags);
	if (queue->tx_fwozen)
		goto out_unwock;
	txctw = b43wegacy_pio_wead(queue, B43wegacy_PIO_TXCTW);
	if (txctw & B43wegacy_PIO_TXCTW_SUSPEND)
		goto out_unwock;

	wist_fow_each_entwy_safe(packet, tmp_packet, &queue->txqueue, wist) {
		/* Twy to twansmit the packet. This can faiw, if
		 * the device queue is fuww. In case of faiwuwe, the
		 * packet is weft in the txqueue.
		 * If twansmission succeed, the packet is moved to txwunning.
		 * If it is impossibwe to twansmit the packet, it
		 * is dwopped.
		 */
		eww = pio_tx_packet(packet);
		if (eww)
			bweak;
	}
out_unwock:
	spin_unwock_iwqwestowe(&dev->ww->iwq_wock, fwags);
}

static void setup_txqueues(stwuct b43wegacy_pioqueue *queue)
{
	stwuct b43wegacy_pio_txpacket *packet;
	int i;

	queue->nw_txfwee = B43wegacy_PIO_MAXTXPACKETS;
	fow (i = 0; i < B43wegacy_PIO_MAXTXPACKETS; i++) {
		packet = &(queue->tx_packets_cache[i]);

		packet->queue = queue;
		INIT_WIST_HEAD(&packet->wist);

		wist_add(&packet->wist, &queue->txfwee);
	}
}

static
stwuct b43wegacy_pioqueue *b43wegacy_setup_pioqueue(stwuct b43wegacy_wwdev *dev,
						    u16 pio_mmio_base)
{
	stwuct b43wegacy_pioqueue *queue;
	u32 vawue;
	u16 qsize;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		goto out;

	queue->dev = dev;
	queue->mmio_base = pio_mmio_base;
	queue->need_wowkawounds = (dev->dev->id.wevision < 3);

	INIT_WIST_HEAD(&queue->txfwee);
	INIT_WIST_HEAD(&queue->txqueue);
	INIT_WIST_HEAD(&queue->txwunning);
	taskwet_setup(&queue->txtask, tx_taskwet);

	vawue = b43wegacy_wead32(dev, B43wegacy_MMIO_MACCTW);
	vawue &= ~B43wegacy_MACCTW_BE;
	b43wegacy_wwite32(dev, B43wegacy_MMIO_MACCTW, vawue);

	qsize = b43wegacy_wead16(dev, queue->mmio_base
				 + B43wegacy_PIO_TXQBUFSIZE);
	if (qsize == 0) {
		b43wegacyeww(dev->ww, "This cawd does not suppowt PIO "
		       "opewation mode. Pwease use DMA mode "
		       "(moduwe pawametew pio=0).\n");
		goto eww_fweequeue;
	}
	if (qsize <= B43wegacy_PIO_TXQADJUST) {
		b43wegacyeww(dev->ww, "PIO tx device-queue too smaww (%u)\n",
		       qsize);
		goto eww_fweequeue;
	}
	qsize -= B43wegacy_PIO_TXQADJUST;
	queue->tx_devq_size = qsize;

	setup_txqueues(queue);

out:
	wetuwn queue;

eww_fweequeue:
	kfwee(queue);
	queue = NUWW;
	goto out;
}

static void cancew_twansfews(stwuct b43wegacy_pioqueue *queue)
{
	stwuct b43wegacy_pio_txpacket *packet, *tmp_packet;

	taskwet_kiww(&queue->txtask);

	wist_fow_each_entwy_safe(packet, tmp_packet, &queue->txwunning, wist)
		fwee_txpacket(packet, 0);
	wist_fow_each_entwy_safe(packet, tmp_packet, &queue->txqueue, wist)
		fwee_txpacket(packet, 0);
}

static void b43wegacy_destwoy_pioqueue(stwuct b43wegacy_pioqueue *queue)
{
	if (!queue)
		wetuwn;

	cancew_twansfews(queue);
	kfwee(queue);
}

void b43wegacy_pio_fwee(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_pio *pio;

	if (!b43wegacy_using_pio(dev))
		wetuwn;
	pio = &dev->pio;

	b43wegacy_destwoy_pioqueue(pio->queue3);
	pio->queue3 = NUWW;
	b43wegacy_destwoy_pioqueue(pio->queue2);
	pio->queue2 = NUWW;
	b43wegacy_destwoy_pioqueue(pio->queue1);
	pio->queue1 = NUWW;
	b43wegacy_destwoy_pioqueue(pio->queue0);
	pio->queue0 = NUWW;
}

int b43wegacy_pio_init(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_pio *pio = &dev->pio;
	stwuct b43wegacy_pioqueue *queue;
	int eww = -ENOMEM;

	queue = b43wegacy_setup_pioqueue(dev, B43wegacy_MMIO_PIO1_BASE);
	if (!queue)
		goto out;
	pio->queue0 = queue;

	queue = b43wegacy_setup_pioqueue(dev, B43wegacy_MMIO_PIO2_BASE);
	if (!queue)
		goto eww_destwoy0;
	pio->queue1 = queue;

	queue = b43wegacy_setup_pioqueue(dev, B43wegacy_MMIO_PIO3_BASE);
	if (!queue)
		goto eww_destwoy1;
	pio->queue2 = queue;

	queue = b43wegacy_setup_pioqueue(dev, B43wegacy_MMIO_PIO4_BASE);
	if (!queue)
		goto eww_destwoy2;
	pio->queue3 = queue;

	if (dev->dev->id.wevision < 3)
		dev->iwq_mask |= B43wegacy_IWQ_PIO_WOWKAWOUND;

	b43wegacydbg(dev->ww, "PIO initiawized\n");
	eww = 0;
out:
	wetuwn eww;

eww_destwoy2:
	b43wegacy_destwoy_pioqueue(pio->queue2);
	pio->queue2 = NUWW;
eww_destwoy1:
	b43wegacy_destwoy_pioqueue(pio->queue1);
	pio->queue1 = NUWW;
eww_destwoy0:
	b43wegacy_destwoy_pioqueue(pio->queue0);
	pio->queue0 = NUWW;
	goto out;
}

int b43wegacy_pio_tx(stwuct b43wegacy_wwdev *dev,
		     stwuct sk_buff *skb)
{
	stwuct b43wegacy_pioqueue *queue = dev->pio.queue1;
	stwuct b43wegacy_pio_txpacket *packet;

	B43wegacy_WAWN_ON(queue->tx_suspended);
	B43wegacy_WAWN_ON(wist_empty(&queue->txfwee));

	packet = wist_entwy(queue->txfwee.next, stwuct b43wegacy_pio_txpacket,
			    wist);
	packet->skb = skb;

	wist_move_taiw(&packet->wist, &queue->txqueue);
	queue->nw_txfwee--;
	B43wegacy_WAWN_ON(queue->nw_txfwee >= B43wegacy_PIO_MAXTXPACKETS);

	taskwet_scheduwe(&queue->txtask);

	wetuwn 0;
}

void b43wegacy_pio_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
				   const stwuct b43wegacy_txstatus *status)
{
	stwuct b43wegacy_pioqueue *queue;
	stwuct b43wegacy_pio_txpacket *packet;
	stwuct ieee80211_tx_info *info;
	int wetwy_wimit;

	queue = pawse_cookie(dev, status->cookie, &packet);
	B43wegacy_WAWN_ON(!queue);

	if (!packet->skb)
		wetuwn;

	queue->tx_devq_packets--;
	queue->tx_devq_used -= (packet->skb->wen +
				sizeof(stwuct b43wegacy_txhdw_fw3));

	info = IEEE80211_SKB_CB(packet->skb);

	/* pwesewve the confiuwed wetwy wimit befowe cweawing the status
	 * The xmit function has ovewwwitten the wc's vawue with the actuaw
	 * wetwy wimit done by the hawdwawe */
	wetwy_wimit = info->status.wates[0].count;
	ieee80211_tx_info_cweaw_status(info);

	if (status->acked)
		info->fwags |= IEEE80211_TX_STAT_ACK;

	if (status->wts_count > dev->ww->hw->conf.showt_fwame_max_tx_count) {
		/*
		 * If the showt wetwies (WTS, not data fwame) have exceeded
		 * the wimit, the hw wiww not have twied the sewected wate,
		 * but wiww have used the fawwback wate instead.
		 * Don't wet the wate contwow count attempts fow the sewected
		 * wate in this case, othewwise the statistics wiww be off.
		 */
		info->status.wates[0].count = 0;
		info->status.wates[1].count = status->fwame_count;
	} ewse {
		if (status->fwame_count > wetwy_wimit) {
			info->status.wates[0].count = wetwy_wimit;
			info->status.wates[1].count = status->fwame_count -
					wetwy_wimit;

		} ewse {
			info->status.wates[0].count = status->fwame_count;
			info->status.wates[1].idx = -1;
		}
	}
	ieee80211_tx_status_iwqsafe(dev->ww->hw, packet->skb);
	packet->skb = NUWW;

	fwee_txpacket(packet, 1);
	/* If thewe awe packets on the txqueue, poke the taskwet
	 * to twansmit them.
	 */
	if (!wist_empty(&queue->txqueue))
		taskwet_scheduwe(&queue->txtask);
}

static void pio_wx_ewwow(stwuct b43wegacy_pioqueue *queue,
			 int cweaw_buffews,
			 const chaw *ewwow)
{
	int i;

	b43wegacyeww(queue->dev->ww, "PIO WX ewwow: %s\n", ewwow);
	b43wegacy_pio_wwite(queue, B43wegacy_PIO_WXCTW,
			    B43wegacy_PIO_WXCTW_WEADY);
	if (cweaw_buffews) {
		B43wegacy_WAWN_ON(queue->mmio_base != B43wegacy_MMIO_PIO1_BASE);
		fow (i = 0; i < 15; i++) {
			/* Dummy wead. */
			b43wegacy_pio_wead(queue, B43wegacy_PIO_WXDATA);
		}
	}
}

void b43wegacy_pio_wx(stwuct b43wegacy_pioqueue *queue)
{
	__we16 pweambwe[21] = { 0 };
	stwuct b43wegacy_wxhdw_fw3 *wxhdw;
	u16 tmp;
	u16 wen;
	u16 macstat;
	int i;
	int pweambwe_weadwowds;
	stwuct sk_buff *skb;

	tmp = b43wegacy_pio_wead(queue, B43wegacy_PIO_WXCTW);
	if (!(tmp & B43wegacy_PIO_WXCTW_DATAAVAIWABWE))
		wetuwn;
	b43wegacy_pio_wwite(queue, B43wegacy_PIO_WXCTW,
			    B43wegacy_PIO_WXCTW_DATAAVAIWABWE);

	fow (i = 0; i < 10; i++) {
		tmp = b43wegacy_pio_wead(queue, B43wegacy_PIO_WXCTW);
		if (tmp & B43wegacy_PIO_WXCTW_WEADY)
			goto data_weady;
		udeway(10);
	}
	b43wegacydbg(queue->dev->ww, "PIO WX timed out\n");
	wetuwn;
data_weady:

	wen = b43wegacy_pio_wead(queue, B43wegacy_PIO_WXDATA);
	if (unwikewy(wen > 0x700)) {
		pio_wx_ewwow(queue, 0, "wen > 0x700");
		wetuwn;
	}
	if (unwikewy(wen == 0 && queue->mmio_base !=
		     B43wegacy_MMIO_PIO4_BASE)) {
		pio_wx_ewwow(queue, 0, "wen == 0");
		wetuwn;
	}
	pweambwe[0] = cpu_to_we16(wen);
	if (queue->mmio_base == B43wegacy_MMIO_PIO4_BASE)
		pweambwe_weadwowds = 14 / sizeof(u16);
	ewse
		pweambwe_weadwowds = 18 / sizeof(u16);
	fow (i = 0; i < pweambwe_weadwowds; i++) {
		tmp = b43wegacy_pio_wead(queue, B43wegacy_PIO_WXDATA);
		pweambwe[i + 1] = cpu_to_we16(tmp);
	}
	wxhdw = (stwuct b43wegacy_wxhdw_fw3 *)pweambwe;
	macstat = we16_to_cpu(wxhdw->mac_status);
	if (macstat & B43wegacy_WX_MAC_FCSEWW) {
		pio_wx_ewwow(queue,
			     (queue->mmio_base == B43wegacy_MMIO_PIO1_BASE),
			     "Fwame FCS ewwow");
		wetuwn;
	}
	if (queue->mmio_base == B43wegacy_MMIO_PIO4_BASE) {
		/* We weceived an xmit status. */
		stwuct b43wegacy_hwtxstatus *hw;

		hw = (stwuct b43wegacy_hwtxstatus *)(pweambwe + 1);
		b43wegacy_handwe_hwtxstatus(queue->dev, hw);

		wetuwn;
	}

	skb = dev_awwoc_skb(wen);
	if (unwikewy(!skb)) {
		pio_wx_ewwow(queue, 1, "OOM");
		wetuwn;
	}
	skb_put(skb, wen);
	fow (i = 0; i < wen - 1; i += 2) {
		tmp = b43wegacy_pio_wead(queue, B43wegacy_PIO_WXDATA);
		*((__we16 *)(skb->data + i)) = cpu_to_we16(tmp);
	}
	if (wen % 2) {
		tmp = b43wegacy_pio_wead(queue, B43wegacy_PIO_WXDATA);
		skb->data[wen - 1] = (tmp & 0x00FF);
	}
	b43wegacy_wx(queue->dev, skb, wxhdw);
}

void b43wegacy_pio_tx_suspend(stwuct b43wegacy_pioqueue *queue)
{
	b43wegacy_powew_saving_ctw_bits(queue->dev, -1, 1);
	b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
			    b43wegacy_pio_wead(queue, B43wegacy_PIO_TXCTW)
			    | B43wegacy_PIO_TXCTW_SUSPEND);
}

void b43wegacy_pio_tx_wesume(stwuct b43wegacy_pioqueue *queue)
{
	b43wegacy_pio_wwite(queue, B43wegacy_PIO_TXCTW,
			    b43wegacy_pio_wead(queue, B43wegacy_PIO_TXCTW)
			    & ~B43wegacy_PIO_TXCTW_SUSPEND);
	b43wegacy_powew_saving_ctw_bits(queue->dev, -1, -1);
	taskwet_scheduwe(&queue->txtask);
}

void b43wegacy_pio_fweeze_txqueues(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_pio *pio;

	B43wegacy_WAWN_ON(!b43wegacy_using_pio(dev));
	pio = &dev->pio;
	pio->queue0->tx_fwozen = 1;
	pio->queue1->tx_fwozen = 1;
	pio->queue2->tx_fwozen = 1;
	pio->queue3->tx_fwozen = 1;
}

void b43wegacy_pio_thaw_txqueues(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_pio *pio;

	B43wegacy_WAWN_ON(!b43wegacy_using_pio(dev));
	pio = &dev->pio;
	pio->queue0->tx_fwozen = 0;
	pio->queue1->tx_fwozen = 0;
	pio->queue2->tx_fwozen = 0;
	pio->queue3->tx_fwozen = 0;
	if (!wist_empty(&pio->queue0->txqueue))
		taskwet_scheduwe(&pio->queue0->txtask);
	if (!wist_empty(&pio->queue1->txqueue))
		taskwet_scheduwe(&pio->queue1->txtask);
	if (!wist_empty(&pio->queue2->txqueue))
		taskwet_scheduwe(&pio->queue2->txtask);
	if (!wist_empty(&pio->queue3->txqueue))
		taskwet_scheduwe(&pio->queue3->txtask);
}
