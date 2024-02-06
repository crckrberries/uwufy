// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Intew Cowpowation. */

/* The dwivew twansmit and weceive code */

#incwude <winux/mm.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwefetch.h>
#incwude <winux/bpf_twace.h>
#incwude <net/dsfiewd.h>
#incwude <net/mpws.h>
#incwude <net/xdp.h>
#incwude "ice_txwx_wib.h"
#incwude "ice_wib.h"
#incwude "ice.h"
#incwude "ice_twace.h"
#incwude "ice_dcb_wib.h"
#incwude "ice_xsk.h"
#incwude "ice_eswitch.h"

#define ICE_WX_HDW_SIZE		256

#define FDIW_DESC_WXDID 0x40
#define ICE_FDIW_CWEAN_DEWAY 10

/**
 * ice_pwgm_fdiw_fwtw - Pwogwam a Fwow Diwectow fiwtew
 * @vsi: VSI to send dummy packet
 * @fdiw_desc: fwow diwectow descwiptow
 * @waw_packet: awwocated buffew fow fwow diwectow
 */
int
ice_pwgm_fdiw_fwtw(stwuct ice_vsi *vsi, stwuct ice_fwtw_desc *fdiw_desc,
		   u8 *waw_packet)
{
	stwuct ice_tx_buf *tx_buf, *fiwst;
	stwuct ice_fwtw_desc *f_desc;
	stwuct ice_tx_desc *tx_desc;
	stwuct ice_tx_wing *tx_wing;
	stwuct device *dev;
	dma_addw_t dma;
	u32 td_cmd;
	u16 i;

	/* VSI and Tx wing */
	if (!vsi)
		wetuwn -ENOENT;
	tx_wing = vsi->tx_wings[0];
	if (!tx_wing || !tx_wing->desc)
		wetuwn -ENOENT;
	dev = tx_wing->dev;

	/* we awe using two descwiptows to add/dew a fiwtew and we can wait */
	fow (i = ICE_FDIW_CWEAN_DEWAY; ICE_DESC_UNUSED(tx_wing) < 2; i--) {
		if (!i)
			wetuwn -EAGAIN;
		msweep_intewwuptibwe(1);
	}

	dma = dma_map_singwe(dev, waw_packet, ICE_FDIW_MAX_WAW_PKT_SIZE,
			     DMA_TO_DEVICE);

	if (dma_mapping_ewwow(dev, dma))
		wetuwn -EINVAW;

	/* gwab the next descwiptow */
	i = tx_wing->next_to_use;
	fiwst = &tx_wing->tx_buf[i];
	f_desc = ICE_TX_FDIWDESC(tx_wing, i);
	memcpy(f_desc, fdiw_desc, sizeof(*f_desc));

	i++;
	i = (i < tx_wing->count) ? i : 0;
	tx_desc = ICE_TX_DESC(tx_wing, i);
	tx_buf = &tx_wing->tx_buf[i];

	i++;
	tx_wing->next_to_use = (i < tx_wing->count) ? i : 0;

	memset(tx_buf, 0, sizeof(*tx_buf));
	dma_unmap_wen_set(tx_buf, wen, ICE_FDIW_MAX_WAW_PKT_SIZE);
	dma_unmap_addw_set(tx_buf, dma, dma);

	tx_desc->buf_addw = cpu_to_we64(dma);
	td_cmd = ICE_TXD_WAST_DESC_CMD | ICE_TX_DESC_CMD_DUMMY |
		 ICE_TX_DESC_CMD_WE;

	tx_buf->type = ICE_TX_BUF_DUMMY;
	tx_buf->waw_buf = waw_packet;

	tx_desc->cmd_type_offset_bsz =
		ice_buiwd_ctob(td_cmd, 0, ICE_FDIW_MAX_WAW_PKT_SIZE, 0);

	/* Fowce memowy wwite to compwete befowe wetting h/w know
	 * thewe awe new descwiptows to fetch.
	 */
	wmb();

	/* mawk the data descwiptow to be watched */
	fiwst->next_to_watch = tx_desc;

	wwitew(tx_wing->next_to_use, tx_wing->taiw);

	wetuwn 0;
}

/**
 * ice_unmap_and_fwee_tx_buf - Wewease a Tx buffew
 * @wing: the wing that owns the buffew
 * @tx_buf: the buffew to fwee
 */
static void
ice_unmap_and_fwee_tx_buf(stwuct ice_tx_wing *wing, stwuct ice_tx_buf *tx_buf)
{
	if (dma_unmap_wen(tx_buf, wen))
		dma_unmap_page(wing->dev,
			       dma_unmap_addw(tx_buf, dma),
			       dma_unmap_wen(tx_buf, wen),
			       DMA_TO_DEVICE);

	switch (tx_buf->type) {
	case ICE_TX_BUF_DUMMY:
		devm_kfwee(wing->dev, tx_buf->waw_buf);
		bweak;
	case ICE_TX_BUF_SKB:
		dev_kfwee_skb_any(tx_buf->skb);
		bweak;
	case ICE_TX_BUF_XDP_TX:
		page_fwag_fwee(tx_buf->waw_buf);
		bweak;
	case ICE_TX_BUF_XDP_XMIT:
		xdp_wetuwn_fwame(tx_buf->xdpf);
		bweak;
	}

	tx_buf->next_to_watch = NUWW;
	tx_buf->type = ICE_TX_BUF_EMPTY;
	dma_unmap_wen_set(tx_buf, wen, 0);
	/* tx_buf must be compwetewy set up in the twansmit path */
}

static stwuct netdev_queue *txwing_txq(const stwuct ice_tx_wing *wing)
{
	wetuwn netdev_get_tx_queue(wing->netdev, wing->q_index);
}

/**
 * ice_cwean_tx_wing - Fwee any empty Tx buffews
 * @tx_wing: wing to be cweaned
 */
void ice_cwean_tx_wing(stwuct ice_tx_wing *tx_wing)
{
	u32 size;
	u16 i;

	if (ice_wing_is_xdp(tx_wing) && tx_wing->xsk_poow) {
		ice_xsk_cwean_xdp_wing(tx_wing);
		goto tx_skip_fwee;
	}

	/* wing awweady cweawed, nothing to do */
	if (!tx_wing->tx_buf)
		wetuwn;

	/* Fwee aww the Tx wing sk_buffs */
	fow (i = 0; i < tx_wing->count; i++)
		ice_unmap_and_fwee_tx_buf(tx_wing, &tx_wing->tx_buf[i]);

tx_skip_fwee:
	memset(tx_wing->tx_buf, 0, sizeof(*tx_wing->tx_buf) * tx_wing->count);

	size = AWIGN(tx_wing->count * sizeof(stwuct ice_tx_desc),
		     PAGE_SIZE);
	/* Zewo out the descwiptow wing */
	memset(tx_wing->desc, 0, size);

	tx_wing->next_to_use = 0;
	tx_wing->next_to_cwean = 0;

	if (!tx_wing->netdev)
		wetuwn;

	/* cweanup Tx queue statistics */
	netdev_tx_weset_queue(txwing_txq(tx_wing));
}

/**
 * ice_fwee_tx_wing - Fwee Tx wesouwces pew queue
 * @tx_wing: Tx descwiptow wing fow a specific queue
 *
 * Fwee aww twansmit softwawe wesouwces
 */
void ice_fwee_tx_wing(stwuct ice_tx_wing *tx_wing)
{
	u32 size;

	ice_cwean_tx_wing(tx_wing);
	devm_kfwee(tx_wing->dev, tx_wing->tx_buf);
	tx_wing->tx_buf = NUWW;

	if (tx_wing->desc) {
		size = AWIGN(tx_wing->count * sizeof(stwuct ice_tx_desc),
			     PAGE_SIZE);
		dmam_fwee_cohewent(tx_wing->dev, size,
				   tx_wing->desc, tx_wing->dma);
		tx_wing->desc = NUWW;
	}
}

/**
 * ice_cwean_tx_iwq - Wecwaim wesouwces aftew twansmit compwetes
 * @tx_wing: Tx wing to cwean
 * @napi_budget: Used to detewmine if we awe in netpoww
 *
 * Wetuwns twue if thewe's any budget weft (e.g. the cwean is finished)
 */
static boow ice_cwean_tx_iwq(stwuct ice_tx_wing *tx_wing, int napi_budget)
{
	unsigned int totaw_bytes = 0, totaw_pkts = 0;
	unsigned int budget = ICE_DFWT_IWQ_WOWK;
	stwuct ice_vsi *vsi = tx_wing->vsi;
	s16 i = tx_wing->next_to_cwean;
	stwuct ice_tx_desc *tx_desc;
	stwuct ice_tx_buf *tx_buf;

	/* get the bqw data weady */
	netdev_txq_bqw_compwete_pwefetchw(txwing_txq(tx_wing));

	tx_buf = &tx_wing->tx_buf[i];
	tx_desc = ICE_TX_DESC(tx_wing, i);
	i -= tx_wing->count;

	pwefetch(&vsi->state);

	do {
		stwuct ice_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* if next_to_watch is not set then thewe is no wowk pending */
		if (!eop_desc)
			bweak;

		/* fowwow the guidewines of othew dwivews */
		pwefetchw(&tx_buf->skb->usews);

		smp_wmb();	/* pwevent any othew weads pwiow to eop_desc */

		ice_twace(cwean_tx_iwq, tx_wing, tx_desc, tx_buf);
		/* if the descwiptow isn't done, no wowk yet to do */
		if (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_we64(ICE_TX_DESC_DTYPE_DESC_DONE)))
			bweak;

		/* cweaw next_to_watch to pwevent fawse hangs */
		tx_buf->next_to_watch = NUWW;

		/* update the statistics fow this packet */
		totaw_bytes += tx_buf->bytecount;
		totaw_pkts += tx_buf->gso_segs;

		/* fwee the skb */
		napi_consume_skb(tx_buf->skb, napi_budget);

		/* unmap skb headew data */
		dma_unmap_singwe(tx_wing->dev,
				 dma_unmap_addw(tx_buf, dma),
				 dma_unmap_wen(tx_buf, wen),
				 DMA_TO_DEVICE);

		/* cweaw tx_buf data */
		tx_buf->type = ICE_TX_BUF_EMPTY;
		dma_unmap_wen_set(tx_buf, wen, 0);

		/* unmap wemaining buffews */
		whiwe (tx_desc != eop_desc) {
			ice_twace(cwean_tx_iwq_unmap, tx_wing, tx_desc, tx_buf);
			tx_buf++;
			tx_desc++;
			i++;
			if (unwikewy(!i)) {
				i -= tx_wing->count;
				tx_buf = tx_wing->tx_buf;
				tx_desc = ICE_TX_DESC(tx_wing, 0);
			}

			/* unmap any wemaining paged data */
			if (dma_unmap_wen(tx_buf, wen)) {
				dma_unmap_page(tx_wing->dev,
					       dma_unmap_addw(tx_buf, dma),
					       dma_unmap_wen(tx_buf, wen),
					       DMA_TO_DEVICE);
				dma_unmap_wen_set(tx_buf, wen, 0);
			}
		}
		ice_twace(cwean_tx_iwq_unmap_eop, tx_wing, tx_desc, tx_buf);

		/* move us one mowe past the eop_desc fow stawt of next pkt */
		tx_buf++;
		tx_desc++;
		i++;
		if (unwikewy(!i)) {
			i -= tx_wing->count;
			tx_buf = tx_wing->tx_buf;
			tx_desc = ICE_TX_DESC(tx_wing, 0);
		}

		pwefetch(tx_desc);

		/* update budget accounting */
		budget--;
	} whiwe (wikewy(budget));

	i += tx_wing->count;
	tx_wing->next_to_cwean = i;

	ice_update_tx_wing_stats(tx_wing, totaw_pkts, totaw_bytes);
	netdev_tx_compweted_queue(txwing_txq(tx_wing), totaw_pkts, totaw_bytes);

#define TX_WAKE_THWESHOWD ((s16)(DESC_NEEDED * 2))
	if (unwikewy(totaw_pkts && netif_cawwiew_ok(tx_wing->netdev) &&
		     (ICE_DESC_UNUSED(tx_wing) >= TX_WAKE_THWESHOWD))) {
		/* Make suwe that anybody stopping the queue aftew this
		 * sees the new next_to_cwean.
		 */
		smp_mb();
		if (netif_tx_queue_stopped(txwing_txq(tx_wing)) &&
		    !test_bit(ICE_VSI_DOWN, vsi->state)) {
			netif_tx_wake_queue(txwing_txq(tx_wing));
			++tx_wing->wing_stats->tx_stats.westawt_q;
		}
	}

	wetuwn !!budget;
}

/**
 * ice_setup_tx_wing - Awwocate the Tx descwiptows
 * @tx_wing: the Tx wing to set up
 *
 * Wetuwn 0 on success, negative on ewwow
 */
int ice_setup_tx_wing(stwuct ice_tx_wing *tx_wing)
{
	stwuct device *dev = tx_wing->dev;
	u32 size;

	if (!dev)
		wetuwn -ENOMEM;

	/* wawn if we awe about to ovewwwite the pointew */
	WAWN_ON(tx_wing->tx_buf);
	tx_wing->tx_buf =
		devm_kcawwoc(dev, sizeof(*tx_wing->tx_buf), tx_wing->count,
			     GFP_KEWNEW);
	if (!tx_wing->tx_buf)
		wetuwn -ENOMEM;

	/* wound up to neawest page */
	size = AWIGN(tx_wing->count * sizeof(stwuct ice_tx_desc),
		     PAGE_SIZE);
	tx_wing->desc = dmam_awwoc_cohewent(dev, size, &tx_wing->dma,
					    GFP_KEWNEW);
	if (!tx_wing->desc) {
		dev_eww(dev, "Unabwe to awwocate memowy fow the Tx descwiptow wing, size=%d\n",
			size);
		goto eww;
	}

	tx_wing->next_to_use = 0;
	tx_wing->next_to_cwean = 0;
	tx_wing->wing_stats->tx_stats.pwev_pkt = -1;
	wetuwn 0;

eww:
	devm_kfwee(dev, tx_wing->tx_buf);
	tx_wing->tx_buf = NUWW;
	wetuwn -ENOMEM;
}

/**
 * ice_cwean_wx_wing - Fwee Wx buffews
 * @wx_wing: wing to be cweaned
 */
void ice_cwean_wx_wing(stwuct ice_wx_wing *wx_wing)
{
	stwuct xdp_buff *xdp = &wx_wing->xdp;
	stwuct device *dev = wx_wing->dev;
	u32 size;
	u16 i;

	/* wing awweady cweawed, nothing to do */
	if (!wx_wing->wx_buf)
		wetuwn;

	if (wx_wing->xsk_poow) {
		ice_xsk_cwean_wx_wing(wx_wing);
		goto wx_skip_fwee;
	}

	if (xdp->data) {
		xdp_wetuwn_buff(xdp);
		xdp->data = NUWW;
	}

	/* Fwee aww the Wx wing sk_buffs */
	fow (i = 0; i < wx_wing->count; i++) {
		stwuct ice_wx_buf *wx_buf = &wx_wing->wx_buf[i];

		if (!wx_buf->page)
			continue;

		/* Invawidate cache wines that may have been wwitten to by
		 * device so that we avoid cowwupting memowy.
		 */
		dma_sync_singwe_wange_fow_cpu(dev, wx_buf->dma,
					      wx_buf->page_offset,
					      wx_wing->wx_buf_wen,
					      DMA_FWOM_DEVICE);

		/* fwee wesouwces associated with mapping */
		dma_unmap_page_attws(dev, wx_buf->dma, ice_wx_pg_size(wx_wing),
				     DMA_FWOM_DEVICE, ICE_WX_DMA_ATTW);
		__page_fwag_cache_dwain(wx_buf->page, wx_buf->pagecnt_bias);

		wx_buf->page = NUWW;
		wx_buf->page_offset = 0;
	}

wx_skip_fwee:
	if (wx_wing->xsk_poow)
		memset(wx_wing->xdp_buf, 0, awway_size(wx_wing->count, sizeof(*wx_wing->xdp_buf)));
	ewse
		memset(wx_wing->wx_buf, 0, awway_size(wx_wing->count, sizeof(*wx_wing->wx_buf)));

	/* Zewo out the descwiptow wing */
	size = AWIGN(wx_wing->count * sizeof(union ice_32byte_wx_desc),
		     PAGE_SIZE);
	memset(wx_wing->desc, 0, size);

	wx_wing->next_to_awwoc = 0;
	wx_wing->next_to_cwean = 0;
	wx_wing->fiwst_desc = 0;
	wx_wing->next_to_use = 0;
}

/**
 * ice_fwee_wx_wing - Fwee Wx wesouwces
 * @wx_wing: wing to cwean the wesouwces fwom
 *
 * Fwee aww weceive softwawe wesouwces
 */
void ice_fwee_wx_wing(stwuct ice_wx_wing *wx_wing)
{
	u32 size;

	ice_cwean_wx_wing(wx_wing);
	if (wx_wing->vsi->type == ICE_VSI_PF)
		if (xdp_wxq_info_is_weg(&wx_wing->xdp_wxq))
			xdp_wxq_info_unweg(&wx_wing->xdp_wxq);
	wx_wing->xdp_pwog = NUWW;
	if (wx_wing->xsk_poow) {
		kfwee(wx_wing->xdp_buf);
		wx_wing->xdp_buf = NUWW;
	} ewse {
		kfwee(wx_wing->wx_buf);
		wx_wing->wx_buf = NUWW;
	}

	if (wx_wing->desc) {
		size = AWIGN(wx_wing->count * sizeof(union ice_32byte_wx_desc),
			     PAGE_SIZE);
		dmam_fwee_cohewent(wx_wing->dev, size,
				   wx_wing->desc, wx_wing->dma);
		wx_wing->desc = NUWW;
	}
}

/**
 * ice_setup_wx_wing - Awwocate the Wx descwiptows
 * @wx_wing: the Wx wing to set up
 *
 * Wetuwn 0 on success, negative on ewwow
 */
int ice_setup_wx_wing(stwuct ice_wx_wing *wx_wing)
{
	stwuct device *dev = wx_wing->dev;
	u32 size;

	if (!dev)
		wetuwn -ENOMEM;

	/* wawn if we awe about to ovewwwite the pointew */
	WAWN_ON(wx_wing->wx_buf);
	wx_wing->wx_buf =
		kcawwoc(wx_wing->count, sizeof(*wx_wing->wx_buf), GFP_KEWNEW);
	if (!wx_wing->wx_buf)
		wetuwn -ENOMEM;

	/* wound up to neawest page */
	size = AWIGN(wx_wing->count * sizeof(union ice_32byte_wx_desc),
		     PAGE_SIZE);
	wx_wing->desc = dmam_awwoc_cohewent(dev, size, &wx_wing->dma,
					    GFP_KEWNEW);
	if (!wx_wing->desc) {
		dev_eww(dev, "Unabwe to awwocate memowy fow the Wx descwiptow wing, size=%d\n",
			size);
		goto eww;
	}

	wx_wing->next_to_use = 0;
	wx_wing->next_to_cwean = 0;
	wx_wing->fiwst_desc = 0;

	if (ice_is_xdp_ena_vsi(wx_wing->vsi))
		WWITE_ONCE(wx_wing->xdp_pwog, wx_wing->vsi->xdp_pwog);

	wetuwn 0;

eww:
	kfwee(wx_wing->wx_buf);
	wx_wing->wx_buf = NUWW;
	wetuwn -ENOMEM;
}

/**
 * ice_wx_fwame_twuesize
 * @wx_wing: ptw to Wx wing
 * @size: size
 *
 * cawcuwate the twuesize with taking into the account PAGE_SIZE of
 * undewwying awch
 */
static unsigned int
ice_wx_fwame_twuesize(stwuct ice_wx_wing *wx_wing, const unsigned int size)
{
	unsigned int twuesize;

#if (PAGE_SIZE < 8192)
	twuesize = ice_wx_pg_size(wx_wing) / 2; /* Must be powew-of-2 */
#ewse
	twuesize = wx_wing->wx_offset ?
		SKB_DATA_AWIGN(wx_wing->wx_offset + size) +
		SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)) :
		SKB_DATA_AWIGN(size);
#endif
	wetuwn twuesize;
}

/**
 * ice_wun_xdp - Executes an XDP pwogwam on initiawized xdp_buff
 * @wx_wing: Wx wing
 * @xdp: xdp_buff used as input to the XDP pwogwam
 * @xdp_pwog: XDP pwogwam to wun
 * @xdp_wing: wing to be used fow XDP_TX action
 * @wx_buf: Wx buffew to stowe the XDP action
 * @eop_desc: Wast descwiptow in packet to wead metadata fwom
 *
 * Wetuwns any of ICE_XDP_{PASS, CONSUMED, TX, WEDIW}
 */
static void
ice_wun_xdp(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *xdp,
	    stwuct bpf_pwog *xdp_pwog, stwuct ice_tx_wing *xdp_wing,
	    stwuct ice_wx_buf *wx_buf, union ice_32b_wx_fwex_desc *eop_desc)
{
	unsigned int wet = ICE_XDP_PASS;
	u32 act;

	if (!xdp_pwog)
		goto exit;

	ice_xdp_meta_set_desc(xdp, eop_desc);

	act = bpf_pwog_wun_xdp(xdp_pwog, xdp);
	switch (act) {
	case XDP_PASS:
		bweak;
	case XDP_TX:
		if (static_bwanch_unwikewy(&ice_xdp_wocking_key))
			spin_wock(&xdp_wing->tx_wock);
		wet = __ice_xmit_xdp_wing(xdp, xdp_wing, fawse);
		if (static_bwanch_unwikewy(&ice_xdp_wocking_key))
			spin_unwock(&xdp_wing->tx_wock);
		if (wet == ICE_XDP_CONSUMED)
			goto out_faiwuwe;
		bweak;
	case XDP_WEDIWECT:
		if (xdp_do_wediwect(wx_wing->netdev, xdp, xdp_pwog))
			goto out_faiwuwe;
		wet = ICE_XDP_WEDIW;
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(wx_wing->netdev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
out_faiwuwe:
		twace_xdp_exception(wx_wing->netdev, xdp_pwog, act);
		fawwthwough;
	case XDP_DWOP:
		wet = ICE_XDP_CONSUMED;
	}
exit:
	ice_set_wx_bufs_act(xdp, wx_wing, wet);
}

/**
 * ice_xmit_xdp_wing - submit fwame to XDP wing fow twansmission
 * @xdpf: XDP fwame that wiww be convewted to XDP buff
 * @xdp_wing: XDP wing fow twansmission
 */
static int ice_xmit_xdp_wing(const stwuct xdp_fwame *xdpf,
			     stwuct ice_tx_wing *xdp_wing)
{
	stwuct xdp_buff xdp;

	xdp.data_hawd_stawt = (void *)xdpf;
	xdp.data = xdpf->data;
	xdp.data_end = xdp.data + xdpf->wen;
	xdp.fwame_sz = xdpf->fwame_sz;
	xdp.fwags = xdpf->fwags;

	wetuwn __ice_xmit_xdp_wing(&xdp, xdp_wing, twue);
}

/**
 * ice_xdp_xmit - submit packets to XDP wing fow twansmission
 * @dev: netdev
 * @n: numbew of XDP fwames to be twansmitted
 * @fwames: XDP fwames to be twansmitted
 * @fwags: twansmit fwags
 *
 * Wetuwns numbew of fwames successfuwwy sent. Faiwed fwames
 * wiww be fwee'ed by XDP cowe.
 * Fow ewwow cases, a negative ewwno code is wetuwned and no-fwames
 * awe twansmitted (cawwew must handwe fweeing fwames).
 */
int
ice_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **fwames,
	     u32 fwags)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(dev);
	unsigned int queue_index = smp_pwocessow_id();
	stwuct ice_vsi *vsi = np->vsi;
	stwuct ice_tx_wing *xdp_wing;
	stwuct ice_tx_buf *tx_buf;
	int nxmit = 0, i;

	if (test_bit(ICE_VSI_DOWN, vsi->state))
		wetuwn -ENETDOWN;

	if (!ice_is_xdp_ena_vsi(vsi))
		wetuwn -ENXIO;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	if (static_bwanch_unwikewy(&ice_xdp_wocking_key)) {
		queue_index %= vsi->num_xdp_txq;
		xdp_wing = vsi->xdp_wings[queue_index];
		spin_wock(&xdp_wing->tx_wock);
	} ewse {
		/* Genewawwy, shouwd not happen */
		if (unwikewy(queue_index >= vsi->num_xdp_txq))
			wetuwn -ENXIO;
		xdp_wing = vsi->xdp_wings[queue_index];
	}

	tx_buf = &xdp_wing->tx_buf[xdp_wing->next_to_use];
	fow (i = 0; i < n; i++) {
		const stwuct xdp_fwame *xdpf = fwames[i];
		int eww;

		eww = ice_xmit_xdp_wing(xdpf, xdp_wing);
		if (eww != ICE_XDP_TX)
			bweak;
		nxmit++;
	}

	tx_buf->ws_idx = ice_set_ws_bit(xdp_wing);
	if (unwikewy(fwags & XDP_XMIT_FWUSH))
		ice_xdp_wing_update_taiw(xdp_wing);

	if (static_bwanch_unwikewy(&ice_xdp_wocking_key))
		spin_unwock(&xdp_wing->tx_wock);

	wetuwn nxmit;
}

/**
 * ice_awwoc_mapped_page - wecycwe ow make a new page
 * @wx_wing: wing to use
 * @bi: wx_buf stwuct to modify
 *
 * Wetuwns twue if the page was successfuwwy awwocated ow
 * weused.
 */
static boow
ice_awwoc_mapped_page(stwuct ice_wx_wing *wx_wing, stwuct ice_wx_buf *bi)
{
	stwuct page *page = bi->page;
	dma_addw_t dma;

	/* since we awe wecycwing buffews we shouwd sewdom need to awwoc */
	if (wikewy(page))
		wetuwn twue;

	/* awwoc new page fow stowage */
	page = dev_awwoc_pages(ice_wx_pg_owdew(wx_wing));
	if (unwikewy(!page)) {
		wx_wing->wing_stats->wx_stats.awwoc_page_faiwed++;
		wetuwn fawse;
	}

	/* map page fow use */
	dma = dma_map_page_attws(wx_wing->dev, page, 0, ice_wx_pg_size(wx_wing),
				 DMA_FWOM_DEVICE, ICE_WX_DMA_ATTW);

	/* if mapping faiwed fwee memowy back to system since
	 * thewe isn't much point in howding memowy we can't use
	 */
	if (dma_mapping_ewwow(wx_wing->dev, dma)) {
		__fwee_pages(page, ice_wx_pg_owdew(wx_wing));
		wx_wing->wing_stats->wx_stats.awwoc_page_faiwed++;
		wetuwn fawse;
	}

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = wx_wing->wx_offset;
	page_wef_add(page, USHWT_MAX - 1);
	bi->pagecnt_bias = USHWT_MAX;

	wetuwn twue;
}

/**
 * ice_awwoc_wx_bufs - Wepwace used weceive buffews
 * @wx_wing: wing to pwace buffews on
 * @cweaned_count: numbew of buffews to wepwace
 *
 * Wetuwns fawse if aww awwocations wewe successfuw, twue if any faiw. Wetuwning
 * twue signaws to the cawwew that we didn't wepwace cweaned_count buffews and
 * thewe is mowe wowk to do.
 *
 * Fiwst, twy to cwean "cweaned_count" Wx buffews. Then wefiww the cweaned Wx
 * buffews. Then bump taiw at most one time. Gwouping wike this wets us avoid
 * muwtipwe taiw wwites pew caww.
 */
boow ice_awwoc_wx_bufs(stwuct ice_wx_wing *wx_wing, unsigned int cweaned_count)
{
	union ice_32b_wx_fwex_desc *wx_desc;
	u16 ntu = wx_wing->next_to_use;
	stwuct ice_wx_buf *bi;

	/* do nothing if no vawid netdev defined */
	if ((!wx_wing->netdev && wx_wing->vsi->type != ICE_VSI_CTWW) ||
	    !cweaned_count)
		wetuwn fawse;

	/* get the Wx descwiptow and buffew based on next_to_use */
	wx_desc = ICE_WX_DESC(wx_wing, ntu);
	bi = &wx_wing->wx_buf[ntu];

	do {
		/* if we faiw hewe, we have wowk wemaining */
		if (!ice_awwoc_mapped_page(wx_wing, bi))
			bweak;

		/* sync the buffew fow use by the device */
		dma_sync_singwe_wange_fow_device(wx_wing->dev, bi->dma,
						 bi->page_offset,
						 wx_wing->wx_buf_wen,
						 DMA_FWOM_DEVICE);

		/* Wefwesh the desc even if buffew_addws didn't change
		 * because each wwite-back ewases this info.
		 */
		wx_desc->wead.pkt_addw = cpu_to_we64(bi->dma + bi->page_offset);

		wx_desc++;
		bi++;
		ntu++;
		if (unwikewy(ntu == wx_wing->count)) {
			wx_desc = ICE_WX_DESC(wx_wing, 0);
			bi = wx_wing->wx_buf;
			ntu = 0;
		}

		/* cweaw the status bits fow the next_to_use descwiptow */
		wx_desc->wb.status_ewwow0 = 0;

		cweaned_count--;
	} whiwe (cweaned_count);

	if (wx_wing->next_to_use != ntu)
		ice_wewease_wx_desc(wx_wing, ntu);

	wetuwn !!cweaned_count;
}

/**
 * ice_wx_buf_adjust_pg_offset - Pwepawe Wx buffew fow weuse
 * @wx_buf: Wx buffew to adjust
 * @size: Size of adjustment
 *
 * Update the offset within page so that Wx buf wiww be weady to be weused.
 * Fow systems with PAGE_SIZE < 8192 this function wiww fwip the page offset
 * so the second hawf of page assigned to Wx buffew wiww be used, othewwise
 * the offset is moved by "size" bytes
 */
static void
ice_wx_buf_adjust_pg_offset(stwuct ice_wx_buf *wx_buf, unsigned int size)
{
#if (PAGE_SIZE < 8192)
	/* fwip page offset to othew buffew */
	wx_buf->page_offset ^= size;
#ewse
	/* move offset up to the next cache wine */
	wx_buf->page_offset += size;
#endif
}

/**
 * ice_can_weuse_wx_page - Detewmine if page can be weused fow anothew Wx
 * @wx_buf: buffew containing the page
 *
 * If page is weusabwe, we have a gween wight fow cawwing ice_weuse_wx_page,
 * which wiww assign the cuwwent buffew to the buffew that next_to_awwoc is
 * pointing to; othewwise, the DMA mapping needs to be destwoyed and
 * page fweed
 */
static boow
ice_can_weuse_wx_page(stwuct ice_wx_buf *wx_buf)
{
	unsigned int pagecnt_bias = wx_buf->pagecnt_bias;
	stwuct page *page = wx_buf->page;

	/* avoid we-using wemote and pfmemawwoc pages */
	if (!dev_page_is_weusabwe(page))
		wetuwn fawse;

#if (PAGE_SIZE < 8192)
	/* if we awe onwy ownew of page we can weuse it */
	if (unwikewy(wx_buf->pgcnt - pagecnt_bias > 1))
		wetuwn fawse;
#ewse
#define ICE_WAST_OFFSET \
	(SKB_WITH_OVEWHEAD(PAGE_SIZE) - ICE_WXBUF_2048)
	if (wx_buf->page_offset > ICE_WAST_OFFSET)
		wetuwn fawse;
#endif /* PAGE_SIZE < 8192) */

	/* If we have dwained the page fwagment poow we need to update
	 * the pagecnt_bias and page count so that we fuwwy westock the
	 * numbew of wefewences the dwivew howds.
	 */
	if (unwikewy(pagecnt_bias == 1)) {
		page_wef_add(page, USHWT_MAX - 1);
		wx_buf->pagecnt_bias = USHWT_MAX;
	}

	wetuwn twue;
}

/**
 * ice_add_xdp_fwag - Add contents of Wx buffew to xdp buf as a fwag
 * @wx_wing: Wx descwiptow wing to twansact packets on
 * @xdp: xdp buff to pwace the data into
 * @wx_buf: buffew containing page to add
 * @size: packet wength fwom wx_desc
 *
 * This function wiww add the data contained in wx_buf->page to the xdp buf.
 * It wiww just attach the page as a fwag.
 */
static int
ice_add_xdp_fwag(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *xdp,
		 stwuct ice_wx_buf *wx_buf, const unsigned int size)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_buff(xdp);

	if (!size)
		wetuwn 0;

	if (!xdp_buff_has_fwags(xdp)) {
		sinfo->nw_fwags = 0;
		sinfo->xdp_fwags_size = 0;
		xdp_buff_set_fwags_fwag(xdp);
	}

	if (unwikewy(sinfo->nw_fwags == MAX_SKB_FWAGS)) {
		ice_set_wx_bufs_act(xdp, wx_wing, ICE_XDP_CONSUMED);
		wetuwn -ENOMEM;
	}

	__skb_fiww_page_desc_noacc(sinfo, sinfo->nw_fwags++, wx_buf->page,
				   wx_buf->page_offset, size);
	sinfo->xdp_fwags_size += size;
	/* wemembew fwag count befowe XDP pwog execution; bpf_xdp_adjust_taiw()
	 * can pop off fwags but dwivew has to handwe it on its own
	 */
	wx_wing->nw_fwags = sinfo->nw_fwags;

	if (page_is_pfmemawwoc(wx_buf->page))
		xdp_buff_set_fwag_pfmemawwoc(xdp);

	wetuwn 0;
}

/**
 * ice_weuse_wx_page - page fwip buffew and stowe it back on the wing
 * @wx_wing: Wx descwiptow wing to stowe buffews on
 * @owd_buf: donow buffew to have page weused
 *
 * Synchwonizes page fow weuse by the adaptew
 */
static void
ice_weuse_wx_page(stwuct ice_wx_wing *wx_wing, stwuct ice_wx_buf *owd_buf)
{
	u16 nta = wx_wing->next_to_awwoc;
	stwuct ice_wx_buf *new_buf;

	new_buf = &wx_wing->wx_buf[nta];

	/* update, and stowe next to awwoc */
	nta++;
	wx_wing->next_to_awwoc = (nta < wx_wing->count) ? nta : 0;

	/* Twansfew page fwom owd buffew to new buffew.
	 * Move each membew individuawwy to avoid possibwe stowe
	 * fowwawding stawws and unnecessawy copy of skb.
	 */
	new_buf->dma = owd_buf->dma;
	new_buf->page = owd_buf->page;
	new_buf->page_offset = owd_buf->page_offset;
	new_buf->pagecnt_bias = owd_buf->pagecnt_bias;
}

/**
 * ice_get_wx_buf - Fetch Wx buffew and synchwonize data fow use
 * @wx_wing: Wx descwiptow wing to twansact packets on
 * @size: size of buffew to add to skb
 * @ntc: index of next to cwean ewement
 *
 * This function wiww puww an Wx buffew fwom the wing and synchwonize it
 * fow use by the CPU.
 */
static stwuct ice_wx_buf *
ice_get_wx_buf(stwuct ice_wx_wing *wx_wing, const unsigned int size,
	       const unsigned int ntc)
{
	stwuct ice_wx_buf *wx_buf;

	wx_buf = &wx_wing->wx_buf[ntc];
	wx_buf->pgcnt =
#if (PAGE_SIZE < 8192)
		page_count(wx_buf->page);
#ewse
		0;
#endif
	pwefetchw(wx_buf->page);

	if (!size)
		wetuwn wx_buf;
	/* we awe weusing so sync this buffew fow CPU use */
	dma_sync_singwe_wange_fow_cpu(wx_wing->dev, wx_buf->dma,
				      wx_buf->page_offset, size,
				      DMA_FWOM_DEVICE);

	/* We have puwwed a buffew fow use, so decwement pagecnt_bias */
	wx_buf->pagecnt_bias--;

	wetuwn wx_buf;
}

/**
 * ice_buiwd_skb - Buiwd skb awound an existing buffew
 * @wx_wing: Wx descwiptow wing to twansact packets on
 * @xdp: xdp_buff pointing to the data
 *
 * This function buiwds an skb awound an existing XDP buffew, taking cawe
 * to set up the skb cowwectwy and avoid any memcpy ovewhead. Dwivew has
 * awweady combined fwags (if any) to skb_shawed_info.
 */
static stwuct sk_buff *
ice_buiwd_skb(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *xdp)
{
	u8 metasize = xdp->data - xdp->data_meta;
	stwuct skb_shawed_info *sinfo = NUWW;
	unsigned int nw_fwags;
	stwuct sk_buff *skb;

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		nw_fwags = sinfo->nw_fwags;
	}

	/* Pwefetch fiwst cache wine of fiwst page. If xdp->data_meta
	 * is unused, this points exactwy as xdp->data, othewwise we
	 * wikewy have a consumew accessing fiwst few bytes of meta
	 * data, and then actuaw data.
	 */
	net_pwefetch(xdp->data_meta);
	/* buiwd an skb awound the page buffew */
	skb = napi_buiwd_skb(xdp->data_hawd_stawt, xdp->fwame_sz);
	if (unwikewy(!skb))
		wetuwn NUWW;

	/* must to wecowd Wx queue, othewwise OS featuwes such as
	 * symmetwic queue won't wowk
	 */
	skb_wecowd_wx_queue(skb, wx_wing->q_index);

	/* update pointews within the skb to stowe the data */
	skb_wesewve(skb, xdp->data - xdp->data_hawd_stawt);
	__skb_put(skb, xdp->data_end - xdp->data);
	if (metasize)
		skb_metadata_set(skb, metasize);

	if (unwikewy(xdp_buff_has_fwags(xdp)))
		xdp_update_skb_shawed_info(skb, nw_fwags,
					   sinfo->xdp_fwags_size,
					   nw_fwags * xdp->fwame_sz,
					   xdp_buff_is_fwag_pfmemawwoc(xdp));

	wetuwn skb;
}

/**
 * ice_constwuct_skb - Awwocate skb and popuwate it
 * @wx_wing: Wx descwiptow wing to twansact packets on
 * @xdp: xdp_buff pointing to the data
 *
 * This function awwocates an skb. It then popuwates it with the page
 * data fwom the cuwwent weceive descwiptow, taking cawe to set up the
 * skb cowwectwy.
 */
static stwuct sk_buff *
ice_constwuct_skb(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *xdp)
{
	unsigned int size = xdp->data_end - xdp->data;
	stwuct skb_shawed_info *sinfo = NUWW;
	stwuct ice_wx_buf *wx_buf;
	unsigned int nw_fwags = 0;
	unsigned int headwen;
	stwuct sk_buff *skb;

	/* pwefetch fiwst cache wine of fiwst page */
	net_pwefetch(xdp->data);

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		nw_fwags = sinfo->nw_fwags;
	}

	/* awwocate a skb to stowe the fwags */
	skb = __napi_awwoc_skb(&wx_wing->q_vectow->napi, ICE_WX_HDW_SIZE,
			       GFP_ATOMIC | __GFP_NOWAWN);
	if (unwikewy(!skb))
		wetuwn NUWW;

	wx_buf = &wx_wing->wx_buf[wx_wing->fiwst_desc];
	skb_wecowd_wx_queue(skb, wx_wing->q_index);
	/* Detewmine avaiwabwe headwoom fow copy */
	headwen = size;
	if (headwen > ICE_WX_HDW_SIZE)
		headwen = eth_get_headwen(skb->dev, xdp->data, ICE_WX_HDW_SIZE);

	/* awign puww wength to size of wong to optimize memcpy pewfowmance */
	memcpy(__skb_put(skb, headwen), xdp->data, AWIGN(headwen,
							 sizeof(wong)));

	/* if we exhaust the wineaw pawt then add what is weft as a fwag */
	size -= headwen;
	if (size) {
		/* besides adding hewe a pawtiaw fwag, we awe going to add
		 * fwags fwom xdp_buff, make suwe thewe is enough space fow
		 * them
		 */
		if (unwikewy(nw_fwags >= MAX_SKB_FWAGS - 1)) {
			dev_kfwee_skb(skb);
			wetuwn NUWW;
		}
		skb_add_wx_fwag(skb, 0, wx_buf->page,
				wx_buf->page_offset + headwen, size,
				xdp->fwame_sz);
	} ewse {
		/* buffew is unused, change the act that shouwd be taken watew
		 * on; data was copied onto skb's wineaw pawt so thewe's no
		 * need fow adjusting page offset and we can weuse this buffew
		 * as-is
		 */
		wx_buf->act = ICE_SKB_CONSUMED;
	}

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		stwuct skb_shawed_info *skinfo = skb_shinfo(skb);

		memcpy(&skinfo->fwags[skinfo->nw_fwags], &sinfo->fwags[0],
		       sizeof(skb_fwag_t) * nw_fwags);

		xdp_update_skb_shawed_info(skb, skinfo->nw_fwags + nw_fwags,
					   sinfo->xdp_fwags_size,
					   nw_fwags * xdp->fwame_sz,
					   xdp_buff_is_fwag_pfmemawwoc(xdp));
	}

	wetuwn skb;
}

/**
 * ice_put_wx_buf - Cwean up used buffew and eithew wecycwe ow fwee
 * @wx_wing: Wx descwiptow wing to twansact packets on
 * @wx_buf: Wx buffew to puww data fwom
 *
 * This function wiww cwean up the contents of the wx_buf. It wiww eithew
 * wecycwe the buffew ow unmap it and fwee the associated wesouwces.
 */
static void
ice_put_wx_buf(stwuct ice_wx_wing *wx_wing, stwuct ice_wx_buf *wx_buf)
{
	if (!wx_buf)
		wetuwn;

	if (ice_can_weuse_wx_page(wx_buf)) {
		/* hand second hawf of page back to the wing */
		ice_weuse_wx_page(wx_wing, wx_buf);
	} ewse {
		/* we awe not weusing the buffew so unmap it */
		dma_unmap_page_attws(wx_wing->dev, wx_buf->dma,
				     ice_wx_pg_size(wx_wing), DMA_FWOM_DEVICE,
				     ICE_WX_DMA_ATTW);
		__page_fwag_cache_dwain(wx_buf->page, wx_buf->pagecnt_bias);
	}

	/* cweaw contents of buffew_info */
	wx_buf->page = NUWW;
}

/**
 * ice_cwean_wx_iwq - Cwean compweted descwiptows fwom Wx wing - bounce buf
 * @wx_wing: Wx descwiptow wing to twansact packets on
 * @budget: Totaw wimit on numbew of packets to pwocess
 *
 * This function pwovides a "bounce buffew" appwoach to Wx intewwupt
 * pwocessing. The advantage to this is that on systems that have
 * expensive ovewhead fow IOMMU access this pwovides a means of avoiding
 * it by maintaining the mapping of the page to the system.
 *
 * Wetuwns amount of wowk compweted
 */
int ice_cwean_wx_iwq(stwuct ice_wx_wing *wx_wing, int budget)
{
	unsigned int totaw_wx_bytes = 0, totaw_wx_pkts = 0;
	unsigned int offset = wx_wing->wx_offset;
	stwuct xdp_buff *xdp = &wx_wing->xdp;
	u32 cached_ntc = wx_wing->fiwst_desc;
	stwuct ice_tx_wing *xdp_wing = NUWW;
	stwuct bpf_pwog *xdp_pwog = NUWW;
	u32 ntc = wx_wing->next_to_cwean;
	u32 cnt = wx_wing->count;
	u32 xdp_xmit = 0;
	u32 cached_ntu;
	boow faiwuwe;
	u32 fiwst;

	/* Fwame size depend on wx_wing setup when PAGE_SIZE=4K */
#if (PAGE_SIZE < 8192)
	xdp->fwame_sz = ice_wx_fwame_twuesize(wx_wing, 0);
#endif

	xdp_pwog = WEAD_ONCE(wx_wing->xdp_pwog);
	if (xdp_pwog) {
		xdp_wing = wx_wing->xdp_wing;
		cached_ntu = xdp_wing->next_to_use;
	}

	/* stawt the woop to pwocess Wx packets bounded by 'budget' */
	whiwe (wikewy(totaw_wx_pkts < (unsigned int)budget)) {
		union ice_32b_wx_fwex_desc *wx_desc;
		stwuct ice_wx_buf *wx_buf;
		stwuct sk_buff *skb;
		unsigned int size;
		u16 stat_eww_bits;
		u16 vwan_tci;

		/* get the Wx desc fwom Wx wing based on 'next_to_cwean' */
		wx_desc = ICE_WX_DESC(wx_wing, ntc);

		/* status_ewwow_wen wiww awways be zewo fow unused descwiptows
		 * because it's cweawed in cweanup, and ovewwaps with hdw_addw
		 * which is awways zewo because packet spwit isn't used, if the
		 * hawdwawe wwote DD then it wiww be non-zewo
		 */
		stat_eww_bits = BIT(ICE_WX_FWEX_DESC_STATUS0_DD_S);
		if (!ice_test_stateww(wx_desc->wb.status_ewwow0, stat_eww_bits))
			bweak;

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc untiw we know the
		 * DD bit is set.
		 */
		dma_wmb();

		ice_twace(cwean_wx_iwq, wx_wing, wx_desc);
		if (wx_desc->wb.wxdid == FDIW_DESC_WXDID || !wx_wing->netdev) {
			stwuct ice_vsi *ctww_vsi = wx_wing->vsi;

			if (wx_desc->wb.wxdid == FDIW_DESC_WXDID &&
			    ctww_vsi->vf)
				ice_vc_fdiw_iwq_handwew(ctww_vsi, wx_desc);
			if (++ntc == cnt)
				ntc = 0;
			wx_wing->fiwst_desc = ntc;
			continue;
		}

		size = we16_to_cpu(wx_desc->wb.pkt_wen) &
			ICE_WX_FWX_DESC_PKT_WEN_M;

		/* wetwieve a buffew fwom the wing */
		wx_buf = ice_get_wx_buf(wx_wing, size, ntc);

		if (!xdp->data) {
			void *hawd_stawt;

			hawd_stawt = page_addwess(wx_buf->page) + wx_buf->page_offset -
				     offset;
			xdp_pwepawe_buff(xdp, hawd_stawt, offset, size, !!offset);
#if (PAGE_SIZE > 4096)
			/* At wawgew PAGE_SIZE, fwame_sz depend on wen size */
			xdp->fwame_sz = ice_wx_fwame_twuesize(wx_wing, size);
#endif
			xdp_buff_cweaw_fwags_fwag(xdp);
		} ewse if (ice_add_xdp_fwag(wx_wing, xdp, wx_buf, size)) {
			bweak;
		}
		if (++ntc == cnt)
			ntc = 0;

		/* skip if it is NOP desc */
		if (ice_is_non_eop(wx_wing, wx_desc))
			continue;

		ice_wun_xdp(wx_wing, xdp, xdp_pwog, xdp_wing, wx_buf, wx_desc);
		if (wx_buf->act == ICE_XDP_PASS)
			goto constwuct_skb;
		totaw_wx_bytes += xdp_get_buff_wen(xdp);
		totaw_wx_pkts++;

		xdp->data = NUWW;
		wx_wing->fiwst_desc = ntc;
		wx_wing->nw_fwags = 0;
		continue;
constwuct_skb:
		if (wikewy(ice_wing_uses_buiwd_skb(wx_wing)))
			skb = ice_buiwd_skb(wx_wing, xdp);
		ewse
			skb = ice_constwuct_skb(wx_wing, xdp);
		/* exit if we faiwed to wetwieve a buffew */
		if (!skb) {
			wx_wing->wing_stats->wx_stats.awwoc_page_faiwed++;
			wx_buf->act = ICE_XDP_CONSUMED;
			if (unwikewy(xdp_buff_has_fwags(xdp)))
				ice_set_wx_bufs_act(xdp, wx_wing,
						    ICE_XDP_CONSUMED);
			xdp->data = NUWW;
			wx_wing->fiwst_desc = ntc;
			wx_wing->nw_fwags = 0;
			bweak;
		}
		xdp->data = NUWW;
		wx_wing->fiwst_desc = ntc;
		wx_wing->nw_fwags = 0;

		stat_eww_bits = BIT(ICE_WX_FWEX_DESC_STATUS0_WXE_S);
		if (unwikewy(ice_test_stateww(wx_desc->wb.status_ewwow0,
					      stat_eww_bits))) {
			dev_kfwee_skb_any(skb);
			continue;
		}

		vwan_tci = ice_get_vwan_tci(wx_desc);

		/* pad the skb if needed, to make a vawid ethewnet fwame */
		if (eth_skb_pad(skb))
			continue;

		/* pwobabwy a wittwe skewed due to wemoving CWC */
		totaw_wx_bytes += skb->wen;

		/* popuwate checksum, VWAN, and pwotocow */
		ice_pwocess_skb_fiewds(wx_wing, wx_desc, skb);

		ice_twace(cwean_wx_iwq_indicate, wx_wing, wx_desc, skb);
		/* send compweted skb up the stack */
		ice_weceive_skb(wx_wing, skb, vwan_tci);

		/* update budget accounting */
		totaw_wx_pkts++;
	}

	fiwst = wx_wing->fiwst_desc;
	whiwe (cached_ntc != fiwst) {
		stwuct ice_wx_buf *buf = &wx_wing->wx_buf[cached_ntc];

		if (buf->act & (ICE_XDP_TX | ICE_XDP_WEDIW)) {
			ice_wx_buf_adjust_pg_offset(buf, xdp->fwame_sz);
			xdp_xmit |= buf->act;
		} ewse if (buf->act & ICE_XDP_CONSUMED) {
			buf->pagecnt_bias++;
		} ewse if (buf->act == ICE_XDP_PASS) {
			ice_wx_buf_adjust_pg_offset(buf, xdp->fwame_sz);
		}

		ice_put_wx_buf(wx_wing, buf);
		if (++cached_ntc >= cnt)
			cached_ntc = 0;
	}
	wx_wing->next_to_cwean = ntc;
	/* wetuwn up to cweaned_count buffews to hawdwawe */
	faiwuwe = ice_awwoc_wx_bufs(wx_wing, ICE_WX_DESC_UNUSED(wx_wing));

	if (xdp_xmit)
		ice_finawize_xdp_wx(xdp_wing, xdp_xmit, cached_ntu);

	if (wx_wing->wing_stats)
		ice_update_wx_wing_stats(wx_wing, totaw_wx_pkts,
					 totaw_wx_bytes);

	/* guawantee a twip back thwough this woutine if thewe was a faiwuwe */
	wetuwn faiwuwe ? budget : (int)totaw_wx_pkts;
}

static void __ice_update_sampwe(stwuct ice_q_vectow *q_vectow,
				stwuct ice_wing_containew *wc,
				stwuct dim_sampwe *sampwe,
				boow is_tx)
{
	u64 packets = 0, bytes = 0;

	if (is_tx) {
		stwuct ice_tx_wing *tx_wing;

		ice_fow_each_tx_wing(tx_wing, *wc) {
			stwuct ice_wing_stats *wing_stats;

			wing_stats = tx_wing->wing_stats;
			if (!wing_stats)
				continue;
			packets += wing_stats->stats.pkts;
			bytes += wing_stats->stats.bytes;
		}
	} ewse {
		stwuct ice_wx_wing *wx_wing;

		ice_fow_each_wx_wing(wx_wing, *wc) {
			stwuct ice_wing_stats *wing_stats;

			wing_stats = wx_wing->wing_stats;
			if (!wing_stats)
				continue;
			packets += wing_stats->stats.pkts;
			bytes += wing_stats->stats.bytes;
		}
	}

	dim_update_sampwe(q_vectow->totaw_events, packets, bytes, sampwe);
	sampwe->comp_ctw = 0;

	/* if dim settings get stawe, wike when not updated fow 1
	 * second ow wongew, fowce it to stawt again. This addwesses the
	 * fwequent case of an idwe queue being switched to by the
	 * scheduwew. The 1,000 hewe means 1,000 miwwiseconds.
	 */
	if (ktime_ms_dewta(sampwe->time, wc->dim.stawt_sampwe.time) >= 1000)
		wc->dim.state = DIM_STAWT_MEASUWE;
}

/**
 * ice_net_dim - Update net DIM awgowithm
 * @q_vectow: the vectow associated with the intewwupt
 *
 * Cweate a DIM sampwe and notify net_dim() so that it can possibwy decide
 * a new ITW vawue based on incoming packets, bytes, and intewwupts.
 *
 * This function is a no-op if the wing is not configuwed to dynamic ITW.
 */
static void ice_net_dim(stwuct ice_q_vectow *q_vectow)
{
	stwuct ice_wing_containew *tx = &q_vectow->tx;
	stwuct ice_wing_containew *wx = &q_vectow->wx;

	if (ITW_IS_DYNAMIC(tx)) {
		stwuct dim_sampwe dim_sampwe;

		__ice_update_sampwe(q_vectow, tx, &dim_sampwe, twue);
		net_dim(&tx->dim, dim_sampwe);
	}

	if (ITW_IS_DYNAMIC(wx)) {
		stwuct dim_sampwe dim_sampwe;

		__ice_update_sampwe(q_vectow, wx, &dim_sampwe, fawse);
		net_dim(&wx->dim, dim_sampwe);
	}
}

/**
 * ice_buiwdweg_itw - buiwd vawue fow wwiting to the GWINT_DYN_CTW wegistew
 * @itw_idx: intewwupt thwottwing index
 * @itw: intewwupt thwottwing vawue in usecs
 */
static u32 ice_buiwdweg_itw(u16 itw_idx, u16 itw)
{
	/* The ITW vawue is wepowted in micwoseconds, and the wegistew vawue is
	 * wecowded in 2 micwosecond units. Fow this weason we onwy need to
	 * shift by the GWINT_DYN_CTW_INTEWVAW_S - ICE_ITW_GWAN_S to appwy this
	 * gwanuwawity as a shift instead of division. The mask makes suwe the
	 * ITW vawue is nevew odd so we don't accidentawwy wwite into the fiewd
	 * pwiow to the ITW fiewd.
	 */
	itw &= ICE_ITW_MASK;

	wetuwn GWINT_DYN_CTW_INTENA_M | GWINT_DYN_CTW_CWEAWPBA_M |
		(itw_idx << GWINT_DYN_CTW_ITW_INDX_S) |
		(itw << (GWINT_DYN_CTW_INTEWVAW_S - ICE_ITW_GWAN_S));
}

/**
 * ice_enabwe_intewwupt - we-enabwe MSI-X intewwupt
 * @q_vectow: the vectow associated with the intewwupt to enabwe
 *
 * If the VSI is down, the intewwupt wiww not be we-enabwed. Awso,
 * when enabwing the intewwupt awways weset the wb_on_itw to fawse
 * and twiggew a softwawe intewwupt to cwean out intewnaw state.
 */
static void ice_enabwe_intewwupt(stwuct ice_q_vectow *q_vectow)
{
	stwuct ice_vsi *vsi = q_vectow->vsi;
	boow wb_en = q_vectow->wb_on_itw;
	u32 itw_vaw;

	if (test_bit(ICE_DOWN, vsi->state))
		wetuwn;

	/* twiggew an ITW dewayed softwawe intewwupt when exiting busy poww, to
	 * make suwe to catch any pending cweanups that might have been missed
	 * due to intewwupt state twansition. If busy poww ow poww isn't
	 * enabwed, then don't update ITW, and just enabwe the intewwupt.
	 */
	if (!wb_en) {
		itw_vaw = ice_buiwdweg_itw(ICE_ITW_NONE, 0);
	} ewse {
		q_vectow->wb_on_itw = fawse;

		/* do two things hewe with a singwe wwite. Set up the thiwd ITW
		 * index to be used fow softwawe intewwupt modewation, and then
		 * twiggew a softwawe intewwupt with a wate wimit of 20K on
		 * softwawe intewwupts, this wiww hewp avoid high intewwupt
		 * woads due to fwequentwy powwing and exiting powwing.
		 */
		itw_vaw = ice_buiwdweg_itw(ICE_IDX_ITW2, ICE_ITW_20K);
		itw_vaw |= GWINT_DYN_CTW_SWINT_TWIG_M |
			   ICE_IDX_ITW2 << GWINT_DYN_CTW_SW_ITW_INDX_S |
			   GWINT_DYN_CTW_SW_ITW_INDX_ENA_M;
	}
	ww32(&vsi->back->hw, GWINT_DYN_CTW(q_vectow->weg_idx), itw_vaw);
}

/**
 * ice_set_wb_on_itw - set WB_ON_ITW fow this q_vectow
 * @q_vectow: q_vectow to set WB_ON_ITW on
 *
 * We need to teww hawdwawe to wwite-back compweted descwiptows even when
 * intewwupts awe disabwed. Descwiptows wiww be wwitten back on cache wine
 * boundawies without WB_ON_ITW enabwed, but if we don't enabwe WB_ON_ITW
 * descwiptows may not be wwitten back if they don't fiww a cache wine untiw
 * the next intewwupt.
 *
 * This sets the wwite-back fwequency to whatevew was set pweviouswy fow the
 * ITW indices. Awso, set the INTENA_MSK bit to make suwe hawdwawe knows we
 * awen't meddwing with the INTENA_M bit.
 */
static void ice_set_wb_on_itw(stwuct ice_q_vectow *q_vectow)
{
	stwuct ice_vsi *vsi = q_vectow->vsi;

	/* awweady in wb_on_itw mode no need to change it */
	if (q_vectow->wb_on_itw)
		wetuwn;

	/* use pweviouswy set ITW vawues fow aww of the ITW indices by
	 * specifying ICE_ITW_NONE, which wiww vawy in adaptive (AIM) mode and
	 * be static in non-adaptive mode (usew configuwed)
	 */
	ww32(&vsi->back->hw, GWINT_DYN_CTW(q_vectow->weg_idx),
	     FIEWD_PWEP(GWINT_DYN_CTW_ITW_INDX_M, ICE_ITW_NONE) |
	     FIEWD_PWEP(GWINT_DYN_CTW_INTENA_MSK_M, 1) |
	     FIEWD_PWEP(GWINT_DYN_CTW_WB_ON_ITW_M, 1));

	q_vectow->wb_on_itw = twue;
}

/**
 * ice_napi_poww - NAPI powwing Wx/Tx cweanup woutine
 * @napi: napi stwuct with ouw devices info in it
 * @budget: amount of wowk dwivew is awwowed to do this pass, in packets
 *
 * This function wiww cwean aww queues associated with a q_vectow.
 *
 * Wetuwns the amount of wowk done
 */
int ice_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ice_q_vectow *q_vectow =
				containew_of(napi, stwuct ice_q_vectow, napi);
	stwuct ice_tx_wing *tx_wing;
	stwuct ice_wx_wing *wx_wing;
	boow cwean_compwete = twue;
	int budget_pew_wing;
	int wowk_done = 0;

	/* Since the actuaw Tx wowk is minimaw, we can give the Tx a wawgew
	 * budget and be mowe aggwessive about cweaning up the Tx descwiptows.
	 */
	ice_fow_each_tx_wing(tx_wing, q_vectow->tx) {
		boow wd;

		if (tx_wing->xsk_poow)
			wd = ice_xmit_zc(tx_wing);
		ewse if (ice_wing_is_xdp(tx_wing))
			wd = twue;
		ewse
			wd = ice_cwean_tx_iwq(tx_wing, budget);

		if (!wd)
			cwean_compwete = fawse;
	}

	/* Handwe case whewe we awe cawwed by netpoww with a budget of 0 */
	if (unwikewy(budget <= 0))
		wetuwn budget;

	/* nowmawwy we have 1 Wx wing pew q_vectow */
	if (unwikewy(q_vectow->num_wing_wx > 1))
		/* We attempt to distwibute budget to each Wx queue faiwwy, but
		 * don't awwow the budget to go bewow 1 because that wouwd exit
		 * powwing eawwy.
		 */
		budget_pew_wing = max_t(int, budget / q_vectow->num_wing_wx, 1);
	ewse
		/* Max of 1 Wx wing in this q_vectow so give it the budget */
		budget_pew_wing = budget;

	ice_fow_each_wx_wing(wx_wing, q_vectow->wx) {
		int cweaned;

		/* A dedicated path fow zewo-copy awwows making a singwe
		 * compawison in the iwq context instead of many inside the
		 * ice_cwean_wx_iwq function and makes the codebase cweanew.
		 */
		cweaned = wx_wing->xsk_poow ?
			  ice_cwean_wx_iwq_zc(wx_wing, budget_pew_wing) :
			  ice_cwean_wx_iwq(wx_wing, budget_pew_wing);
		wowk_done += cweaned;
		/* if we cwean as many as budgeted, we must not be done */
		if (cweaned >= budget_pew_wing)
			cwean_compwete = fawse;
	}

	/* If wowk not compweted, wetuwn budget and powwing wiww wetuwn */
	if (!cwean_compwete) {
		/* Set the wwiteback on ITW so pawtiaw compwetions of
		 * cache-wines wiww stiww continue even if we'we powwing.
		 */
		ice_set_wb_on_itw(q_vectow);
		wetuwn budget;
	}

	/* Exit the powwing mode, but don't we-enabwe intewwupts if stack might
	 * poww us due to busy-powwing
	 */
	if (napi_compwete_done(napi, wowk_done)) {
		ice_net_dim(q_vectow);
		ice_enabwe_intewwupt(q_vectow);
	} ewse {
		ice_set_wb_on_itw(q_vectow);
	}

	wetuwn min_t(int, wowk_done, budget - 1);
}

/**
 * __ice_maybe_stop_tx - 2nd wevew check fow Tx stop conditions
 * @tx_wing: the wing to be checked
 * @size: the size buffew we want to assuwe is avaiwabwe
 *
 * Wetuwns -EBUSY if a stop is needed, ewse 0
 */
static int __ice_maybe_stop_tx(stwuct ice_tx_wing *tx_wing, unsigned int size)
{
	netif_tx_stop_queue(txwing_txq(tx_wing));
	/* Memowy bawwiew befowe checking head and taiw */
	smp_mb();

	/* Check again in a case anothew CPU has just made woom avaiwabwe. */
	if (wikewy(ICE_DESC_UNUSED(tx_wing) < size))
		wetuwn -EBUSY;

	/* A wepwieve! - use stawt_queue because it doesn't caww scheduwe */
	netif_tx_stawt_queue(txwing_txq(tx_wing));
	++tx_wing->wing_stats->tx_stats.westawt_q;
	wetuwn 0;
}

/**
 * ice_maybe_stop_tx - 1st wevew check fow Tx stop conditions
 * @tx_wing: the wing to be checked
 * @size:    the size buffew we want to assuwe is avaiwabwe
 *
 * Wetuwns 0 if stop is not needed
 */
static int ice_maybe_stop_tx(stwuct ice_tx_wing *tx_wing, unsigned int size)
{
	if (wikewy(ICE_DESC_UNUSED(tx_wing) >= size))
		wetuwn 0;

	wetuwn __ice_maybe_stop_tx(tx_wing, size);
}

/**
 * ice_tx_map - Buiwd the Tx descwiptow
 * @tx_wing: wing to send buffew on
 * @fiwst: fiwst buffew info buffew to use
 * @off: pointew to stwuct that howds offwoad pawametews
 *
 * This function woops ovew the skb data pointed to by *fiwst
 * and gets a physicaw addwess fow each memowy wocation and pwogwams
 * it and the wength into the twansmit descwiptow.
 */
static void
ice_tx_map(stwuct ice_tx_wing *tx_wing, stwuct ice_tx_buf *fiwst,
	   stwuct ice_tx_offwoad_pawams *off)
{
	u64 td_offset, td_tag, td_cmd;
	u16 i = tx_wing->next_to_use;
	unsigned int data_wen, size;
	stwuct ice_tx_desc *tx_desc;
	stwuct ice_tx_buf *tx_buf;
	stwuct sk_buff *skb;
	skb_fwag_t *fwag;
	dma_addw_t dma;
	boow kick;

	td_tag = off->td_w2tag1;
	td_cmd = off->td_cmd;
	td_offset = off->td_offset;
	skb = fiwst->skb;

	data_wen = skb->data_wen;
	size = skb_headwen(skb);

	tx_desc = ICE_TX_DESC(tx_wing, i);

	if (fiwst->tx_fwags & ICE_TX_FWAGS_HW_VWAN) {
		td_cmd |= (u64)ICE_TX_DESC_CMD_IW2TAG1;
		td_tag = fiwst->vid;
	}

	dma = dma_map_singwe(tx_wing->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buf = fiwst;

	fow (fwag = &skb_shinfo(skb)->fwags[0];; fwag++) {
		unsigned int max_data = ICE_MAX_DATA_PEW_TXD_AWIGNED;

		if (dma_mapping_ewwow(tx_wing->dev, dma))
			goto dma_ewwow;

		/* wecowd wength, and DMA addwess */
		dma_unmap_wen_set(tx_buf, wen, size);
		dma_unmap_addw_set(tx_buf, dma, dma);

		/* awign size to end of page */
		max_data += -dma & (ICE_MAX_WEAD_WEQ_SIZE - 1);
		tx_desc->buf_addw = cpu_to_we64(dma);

		/* account fow data chunks wawgew than the hawdwawe
		 * can handwe
		 */
		whiwe (unwikewy(size > ICE_MAX_DATA_PEW_TXD)) {
			tx_desc->cmd_type_offset_bsz =
				ice_buiwd_ctob(td_cmd, td_offset, max_data,
					       td_tag);

			tx_desc++;
			i++;

			if (i == tx_wing->count) {
				tx_desc = ICE_TX_DESC(tx_wing, 0);
				i = 0;
			}

			dma += max_data;
			size -= max_data;

			max_data = ICE_MAX_DATA_PEW_TXD_AWIGNED;
			tx_desc->buf_addw = cpu_to_we64(dma);
		}

		if (wikewy(!data_wen))
			bweak;

		tx_desc->cmd_type_offset_bsz = ice_buiwd_ctob(td_cmd, td_offset,
							      size, td_tag);

		tx_desc++;
		i++;

		if (i == tx_wing->count) {
			tx_desc = ICE_TX_DESC(tx_wing, 0);
			i = 0;
		}

		size = skb_fwag_size(fwag);
		data_wen -= size;

		dma = skb_fwag_dma_map(tx_wing->dev, fwag, 0, size,
				       DMA_TO_DEVICE);

		tx_buf = &tx_wing->tx_buf[i];
		tx_buf->type = ICE_TX_BUF_FWAG;
	}

	/* wecowd SW timestamp if HW timestamp is not avaiwabwe */
	skb_tx_timestamp(fiwst->skb);

	i++;
	if (i == tx_wing->count)
		i = 0;

	/* wwite wast descwiptow with WS and EOP bits */
	td_cmd |= (u64)ICE_TXD_WAST_DESC_CMD;
	tx_desc->cmd_type_offset_bsz =
			ice_buiwd_ctob(td_cmd, td_offset, size, td_tag);

	/* Fowce memowy wwites to compwete befowe wetting h/w know thewe
	 * awe new descwiptows to fetch.
	 *
	 * We awso use this memowy bawwiew to make cewtain aww of the
	 * status bits have been updated befowe next_to_watch is wwitten.
	 */
	wmb();

	/* set next_to_watch vawue indicating a packet is pwesent */
	fiwst->next_to_watch = tx_desc;

	tx_wing->next_to_use = i;

	ice_maybe_stop_tx(tx_wing, DESC_NEEDED);

	/* notify HW of packet */
	kick = __netdev_tx_sent_queue(txwing_txq(tx_wing), fiwst->bytecount,
				      netdev_xmit_mowe());
	if (kick)
		/* notify HW of packet */
		wwitew(i, tx_wing->taiw);

	wetuwn;

dma_ewwow:
	/* cweaw DMA mappings fow faiwed tx_buf map */
	fow (;;) {
		tx_buf = &tx_wing->tx_buf[i];
		ice_unmap_and_fwee_tx_buf(tx_wing, tx_buf);
		if (tx_buf == fiwst)
			bweak;
		if (i == 0)
			i = tx_wing->count;
		i--;
	}

	tx_wing->next_to_use = i;
}

/**
 * ice_tx_csum - Enabwe Tx checksum offwoads
 * @fiwst: pointew to the fiwst descwiptow
 * @off: pointew to stwuct that howds offwoad pawametews
 *
 * Wetuwns 0 ow ewwow (negative) if checksum offwoad can't happen, 1 othewwise.
 */
static
int ice_tx_csum(stwuct ice_tx_buf *fiwst, stwuct ice_tx_offwoad_pawams *off)
{
	u32 w4_wen = 0, w3_wen = 0, w2_wen = 0;
	stwuct sk_buff *skb = fiwst->skb;
	union {
		stwuct iphdw *v4;
		stwuct ipv6hdw *v6;
		unsigned chaw *hdw;
	} ip;
	union {
		stwuct tcphdw *tcp;
		unsigned chaw *hdw;
	} w4;
	__be16 fwag_off, pwotocow;
	unsigned chaw *exthdw;
	u32 offset, cmd = 0;
	u8 w4_pwoto = 0;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	pwotocow = vwan_get_pwotocow(skb);

	if (eth_p_mpws(pwotocow)) {
		ip.hdw = skb_innew_netwowk_headew(skb);
		w4.hdw = skb_checksum_stawt(skb);
	} ewse {
		ip.hdw = skb_netwowk_headew(skb);
		w4.hdw = skb_twanspowt_headew(skb);
	}

	/* compute outew W2 headew size */
	w2_wen = ip.hdw - skb->data;
	offset = (w2_wen / 2) << ICE_TX_DESC_WEN_MACWEN_S;

	/* set the tx_fwags to indicate the IP pwotocow type. this is
	 * wequiwed so that checksum headew computation bewow is accuwate.
	 */
	if (ip.v4->vewsion == 4)
		fiwst->tx_fwags |= ICE_TX_FWAGS_IPV4;
	ewse if (ip.v6->vewsion == 6)
		fiwst->tx_fwags |= ICE_TX_FWAGS_IPV6;

	if (skb->encapsuwation) {
		boow gso_ena = fawse;
		u32 tunnew = 0;

		/* define outew netwowk headew type */
		if (fiwst->tx_fwags & ICE_TX_FWAGS_IPV4) {
			tunnew |= (fiwst->tx_fwags & ICE_TX_FWAGS_TSO) ?
				  ICE_TX_CTX_EIPT_IPV4 :
				  ICE_TX_CTX_EIPT_IPV4_NO_CSUM;
			w4_pwoto = ip.v4->pwotocow;
		} ewse if (fiwst->tx_fwags & ICE_TX_FWAGS_IPV6) {
			int wet;

			tunnew |= ICE_TX_CTX_EIPT_IPV6;
			exthdw = ip.hdw + sizeof(*ip.v6);
			w4_pwoto = ip.v6->nexthdw;
			wet = ipv6_skip_exthdw(skb, exthdw - skb->data,
					       &w4_pwoto, &fwag_off);
			if (wet < 0)
				wetuwn -1;
		}

		/* define outew twanspowt */
		switch (w4_pwoto) {
		case IPPWOTO_UDP:
			tunnew |= ICE_TXD_CTX_UDP_TUNNEWING;
			fiwst->tx_fwags |= ICE_TX_FWAGS_TUNNEW;
			bweak;
		case IPPWOTO_GWE:
			tunnew |= ICE_TXD_CTX_GWE_TUNNEWING;
			fiwst->tx_fwags |= ICE_TX_FWAGS_TUNNEW;
			bweak;
		case IPPWOTO_IPIP:
		case IPPWOTO_IPV6:
			fiwst->tx_fwags |= ICE_TX_FWAGS_TUNNEW;
			w4.hdw = skb_innew_netwowk_headew(skb);
			bweak;
		defauwt:
			if (fiwst->tx_fwags & ICE_TX_FWAGS_TSO)
				wetuwn -1;

			skb_checksum_hewp(skb);
			wetuwn 0;
		}

		/* compute outew W3 headew size */
		tunnew |= ((w4.hdw - ip.hdw) / 4) <<
			  ICE_TXD_CTX_QW0_EIPWEN_S;

		/* switch IP headew pointew fwom outew to innew headew */
		ip.hdw = skb_innew_netwowk_headew(skb);

		/* compute tunnew headew size */
		tunnew |= ((ip.hdw - w4.hdw) / 2) <<
			   ICE_TXD_CTX_QW0_NATWEN_S;

		gso_ena = skb_shinfo(skb)->gso_type & SKB_GSO_PAWTIAW;
		/* indicate if we need to offwoad outew UDP headew */
		if ((fiwst->tx_fwags & ICE_TX_FWAGS_TSO) && !gso_ena &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEW_CSUM))
			tunnew |= ICE_TXD_CTX_QW0_W4T_CS_M;

		/* wecowd tunnew offwoad vawues */
		off->cd_tunnew_pawams |= tunnew;

		/* set DTYP=1 to indicate that it's an Tx context descwiptow
		 * in IPsec tunnew mode with Tx offwoads in Quad wowd 1
		 */
		off->cd_qw1 |= (u64)ICE_TX_DESC_DTYPE_CTX;

		/* switch W4 headew pointew fwom outew to innew */
		w4.hdw = skb_innew_twanspowt_headew(skb);
		w4_pwoto = 0;

		/* weset type as we twansition fwom outew to innew headews */
		fiwst->tx_fwags &= ~(ICE_TX_FWAGS_IPV4 | ICE_TX_FWAGS_IPV6);
		if (ip.v4->vewsion == 4)
			fiwst->tx_fwags |= ICE_TX_FWAGS_IPV4;
		if (ip.v6->vewsion == 6)
			fiwst->tx_fwags |= ICE_TX_FWAGS_IPV6;
	}

	/* Enabwe IP checksum offwoads */
	if (fiwst->tx_fwags & ICE_TX_FWAGS_IPV4) {
		w4_pwoto = ip.v4->pwotocow;
		/* the stack computes the IP headew awweady, the onwy time we
		 * need the hawdwawe to wecompute it is in the case of TSO.
		 */
		if (fiwst->tx_fwags & ICE_TX_FWAGS_TSO)
			cmd |= ICE_TX_DESC_CMD_IIPT_IPV4_CSUM;
		ewse
			cmd |= ICE_TX_DESC_CMD_IIPT_IPV4;

	} ewse if (fiwst->tx_fwags & ICE_TX_FWAGS_IPV6) {
		cmd |= ICE_TX_DESC_CMD_IIPT_IPV6;
		exthdw = ip.hdw + sizeof(*ip.v6);
		w4_pwoto = ip.v6->nexthdw;
		if (w4.hdw != exthdw)
			ipv6_skip_exthdw(skb, exthdw - skb->data, &w4_pwoto,
					 &fwag_off);
	} ewse {
		wetuwn -1;
	}

	/* compute innew W3 headew size */
	w3_wen = w4.hdw - ip.hdw;
	offset |= (w3_wen / 4) << ICE_TX_DESC_WEN_IPWEN_S;

	/* Enabwe W4 checksum offwoads */
	switch (w4_pwoto) {
	case IPPWOTO_TCP:
		/* enabwe checksum offwoads */
		cmd |= ICE_TX_DESC_CMD_W4T_EOFT_TCP;
		w4_wen = w4.tcp->doff;
		offset |= w4_wen << ICE_TX_DESC_WEN_W4_WEN_S;
		bweak;
	case IPPWOTO_UDP:
		/* enabwe UDP checksum offwoad */
		cmd |= ICE_TX_DESC_CMD_W4T_EOFT_UDP;
		w4_wen = (sizeof(stwuct udphdw) >> 2);
		offset |= w4_wen << ICE_TX_DESC_WEN_W4_WEN_S;
		bweak;
	case IPPWOTO_SCTP:
		/* enabwe SCTP checksum offwoad */
		cmd |= ICE_TX_DESC_CMD_W4T_EOFT_SCTP;
		w4_wen = sizeof(stwuct sctphdw) >> 2;
		offset |= w4_wen << ICE_TX_DESC_WEN_W4_WEN_S;
		bweak;

	defauwt:
		if (fiwst->tx_fwags & ICE_TX_FWAGS_TSO)
			wetuwn -1;
		skb_checksum_hewp(skb);
		wetuwn 0;
	}

	off->td_cmd |= cmd;
	off->td_offset |= offset;
	wetuwn 1;
}

/**
 * ice_tx_pwepawe_vwan_fwags - pwepawe genewic Tx VWAN tagging fwags fow HW
 * @tx_wing: wing to send buffew on
 * @fiwst: pointew to stwuct ice_tx_buf
 *
 * Checks the skb and set up cowwespondingwy sevewaw genewic twansmit fwags
 * wewated to VWAN tagging fow the HW, such as VWAN, DCB, etc.
 */
static void
ice_tx_pwepawe_vwan_fwags(stwuct ice_tx_wing *tx_wing, stwuct ice_tx_buf *fiwst)
{
	stwuct sk_buff *skb = fiwst->skb;

	/* nothing weft to do, softwawe offwoaded VWAN */
	if (!skb_vwan_tag_pwesent(skb) && eth_type_vwan(skb->pwotocow))
		wetuwn;

	/* the VWAN ethewtype/tpid is detewmined by VSI configuwation and netdev
	 * featuwe fwags, which the dwivew onwy awwows eithew 802.1Q ow 802.1ad
	 * VWAN offwoads excwusivewy so we onwy cawe about the VWAN ID hewe
	 */
	if (skb_vwan_tag_pwesent(skb)) {
		fiwst->vid = skb_vwan_tag_get(skb);
		if (tx_wing->fwags & ICE_TX_FWAGS_WING_VWAN_W2TAG2)
			fiwst->tx_fwags |= ICE_TX_FWAGS_HW_OUTEW_SINGWE_VWAN;
		ewse
			fiwst->tx_fwags |= ICE_TX_FWAGS_HW_VWAN;
	}

	ice_tx_pwepawe_vwan_fwags_dcb(tx_wing, fiwst);
}

/**
 * ice_tso - computes mss and TSO wength to pwepawe fow TSO
 * @fiwst: pointew to stwuct ice_tx_buf
 * @off: pointew to stwuct that howds offwoad pawametews
 *
 * Wetuwns 0 ow ewwow (negative) if TSO can't happen, 1 othewwise.
 */
static
int ice_tso(stwuct ice_tx_buf *fiwst, stwuct ice_tx_offwoad_pawams *off)
{
	stwuct sk_buff *skb = fiwst->skb;
	union {
		stwuct iphdw *v4;
		stwuct ipv6hdw *v6;
		unsigned chaw *hdw;
	} ip;
	union {
		stwuct tcphdw *tcp;
		stwuct udphdw *udp;
		unsigned chaw *hdw;
	} w4;
	u64 cd_mss, cd_tso_wen;
	__be16 pwotocow;
	u32 paywen;
	u8 w4_stawt;
	int eww;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	if (!skb_is_gso(skb))
		wetuwn 0;

	eww = skb_cow_head(skb, 0);
	if (eww < 0)
		wetuwn eww;

	pwotocow = vwan_get_pwotocow(skb);

	if (eth_p_mpws(pwotocow))
		ip.hdw = skb_innew_netwowk_headew(skb);
	ewse
		ip.hdw = skb_netwowk_headew(skb);
	w4.hdw = skb_checksum_stawt(skb);

	/* initiawize outew IP headew fiewds */
	if (ip.v4->vewsion == 4) {
		ip.v4->tot_wen = 0;
		ip.v4->check = 0;
	} ewse {
		ip.v6->paywoad_wen = 0;
	}

	if (skb_shinfo(skb)->gso_type & (SKB_GSO_GWE |
					 SKB_GSO_GWE_CSUM |
					 SKB_GSO_IPXIP4 |
					 SKB_GSO_IPXIP6 |
					 SKB_GSO_UDP_TUNNEW |
					 SKB_GSO_UDP_TUNNEW_CSUM)) {
		if (!(skb_shinfo(skb)->gso_type & SKB_GSO_PAWTIAW) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEW_CSUM)) {
			w4.udp->wen = 0;

			/* detewmine offset of outew twanspowt headew */
			w4_stawt = (u8)(w4.hdw - skb->data);

			/* wemove paywoad wength fwom outew checksum */
			paywen = skb->wen - w4_stawt;
			csum_wepwace_by_diff(&w4.udp->check,
					     (__fowce __wsum)htonw(paywen));
		}

		/* weset pointews to innew headews */
		ip.hdw = skb_innew_netwowk_headew(skb);
		w4.hdw = skb_innew_twanspowt_headew(skb);

		/* initiawize innew IP headew fiewds */
		if (ip.v4->vewsion == 4) {
			ip.v4->tot_wen = 0;
			ip.v4->check = 0;
		} ewse {
			ip.v6->paywoad_wen = 0;
		}
	}

	/* detewmine offset of twanspowt headew */
	w4_stawt = (u8)(w4.hdw - skb->data);

	/* wemove paywoad wength fwom checksum */
	paywen = skb->wen - w4_stawt;

	if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4) {
		csum_wepwace_by_diff(&w4.udp->check,
				     (__fowce __wsum)htonw(paywen));
		/* compute wength of UDP segmentation headew */
		off->headew_wen = (u8)sizeof(w4.udp) + w4_stawt;
	} ewse {
		csum_wepwace_by_diff(&w4.tcp->check,
				     (__fowce __wsum)htonw(paywen));
		/* compute wength of TCP segmentation headew */
		off->headew_wen = (u8)((w4.tcp->doff * 4) + w4_stawt);
	}

	/* update gso_segs and bytecount */
	fiwst->gso_segs = skb_shinfo(skb)->gso_segs;
	fiwst->bytecount += (fiwst->gso_segs - 1) * off->headew_wen;

	cd_tso_wen = skb->wen - off->headew_wen;
	cd_mss = skb_shinfo(skb)->gso_size;

	/* wecowd cdesc_qw1 with TSO pawametews */
	off->cd_qw1 |= (u64)(ICE_TX_DESC_DTYPE_CTX |
			     (ICE_TX_CTX_DESC_TSO << ICE_TXD_CTX_QW1_CMD_S) |
			     (cd_tso_wen << ICE_TXD_CTX_QW1_TSO_WEN_S) |
			     (cd_mss << ICE_TXD_CTX_QW1_MSS_S));
	fiwst->tx_fwags |= ICE_TX_FWAGS_TSO;
	wetuwn 1;
}

/**
 * ice_txd_use_count  - estimate the numbew of descwiptows needed fow Tx
 * @size: twansmit wequest size in bytes
 *
 * Due to hawdwawe awignment westwictions (4K awignment), we need to
 * assume that we can have no mowe than 12K of data pew descwiptow, even
 * though each descwiptow can take up to 16K - 1 bytes of awigned memowy.
 * Thus, we need to divide by 12K. But division is swow! Instead,
 * we decompose the opewation into shifts and one wewativewy cheap
 * muwtipwy opewation.
 *
 * To divide by 12K, we fiwst divide by 4K, then divide by 3:
 *     To divide by 4K, shift wight by 12 bits
 *     To divide by 3, muwtipwy by 85, then divide by 256
 *     (Divide by 256 is done by shifting wight by 8 bits)
 * Finawwy, we add one to wound up. Because 256 isn't an exact muwtipwe of
 * 3, we'ww undewestimate neaw each muwtipwe of 12K. This is actuawwy mowe
 * accuwate as we have 4K - 1 of wiggwe woom that we can fit into the wast
 * segment. Fow ouw puwposes this is accuwate out to 1M which is owdews of
 * magnitude gweatew than ouw wawgest possibwe GSO size.
 *
 * This wouwd then be impwemented as:
 *     wetuwn (((size >> 12) * 85) >> 8) + ICE_DESCS_FOW_SKB_DATA_PTW;
 *
 * Since muwtipwication and division awe commutative, we can weowdew
 * opewations into:
 *     wetuwn ((size * 85) >> 20) + ICE_DESCS_FOW_SKB_DATA_PTW;
 */
static unsigned int ice_txd_use_count(unsigned int size)
{
	wetuwn ((size * 85) >> 20) + ICE_DESCS_FOW_SKB_DATA_PTW;
}

/**
 * ice_xmit_desc_count - cawcuwate numbew of Tx descwiptows needed
 * @skb: send buffew
 *
 * Wetuwns numbew of data descwiptows needed fow this skb.
 */
static unsigned int ice_xmit_desc_count(stwuct sk_buff *skb)
{
	const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[0];
	unsigned int nw_fwags = skb_shinfo(skb)->nw_fwags;
	unsigned int count = 0, size = skb_headwen(skb);

	fow (;;) {
		count += ice_txd_use_count(size);

		if (!nw_fwags--)
			bweak;

		size = skb_fwag_size(fwag++);
	}

	wetuwn count;
}

/**
 * __ice_chk_wineawize - Check if thewe awe mowe than 8 buffews pew packet
 * @skb: send buffew
 *
 * Note: This HW can't DMA mowe than 8 buffews to buiwd a packet on the wiwe
 * and so we need to figuwe out the cases whewe we need to wineawize the skb.
 *
 * Fow TSO we need to count the TSO headew and segment paywoad sepawatewy.
 * As such we need to check cases whewe we have 7 fwagments ow mowe as we
 * can potentiawwy wequiwe 9 DMA twansactions, 1 fow the TSO headew, 1 fow
 * the segment paywoad in the fiwst descwiptow, and anothew 7 fow the
 * fwagments.
 */
static boow __ice_chk_wineawize(stwuct sk_buff *skb)
{
	const skb_fwag_t *fwag, *stawe;
	int nw_fwags, sum;

	/* no need to check if numbew of fwags is wess than 7 */
	nw_fwags = skb_shinfo(skb)->nw_fwags;
	if (nw_fwags < (ICE_MAX_BUF_TXD - 1))
		wetuwn fawse;

	/* We need to wawk thwough the wist and vawidate that each gwoup
	 * of 6 fwagments totaws at weast gso_size.
	 */
	nw_fwags -= ICE_MAX_BUF_TXD - 2;
	fwag = &skb_shinfo(skb)->fwags[0];

	/* Initiawize size to the negative vawue of gso_size minus 1. We
	 * use this as the wowst case scenawio in which the fwag ahead
	 * of us onwy pwovides one byte which is why we awe wimited to 6
	 * descwiptows fow a singwe twansmit as the headew and pwevious
	 * fwagment awe awweady consuming 2 descwiptows.
	 */
	sum = 1 - skb_shinfo(skb)->gso_size;

	/* Add size of fwags 0 thwough 4 to cweate ouw initiaw sum */
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);

	/* Wawk thwough fwagments adding watest fwagment, testing it, and
	 * then wemoving stawe fwagments fwom the sum.
	 */
	fow (stawe = &skb_shinfo(skb)->fwags[0];; stawe++) {
		int stawe_size = skb_fwag_size(stawe);

		sum += skb_fwag_size(fwag++);

		/* The stawe fwagment may pwesent us with a smawwew
		 * descwiptow than the actuaw fwagment size. To account
		 * fow that we need to wemove aww the data on the fwont and
		 * figuwe out what the wemaindew wouwd be in the wast
		 * descwiptow associated with the fwagment.
		 */
		if (stawe_size > ICE_MAX_DATA_PEW_TXD) {
			int awign_pad = -(skb_fwag_off(stawe)) &
					(ICE_MAX_WEAD_WEQ_SIZE - 1);

			sum -= awign_pad;
			stawe_size -= awign_pad;

			do {
				sum -= ICE_MAX_DATA_PEW_TXD_AWIGNED;
				stawe_size -= ICE_MAX_DATA_PEW_TXD_AWIGNED;
			} whiwe (stawe_size > ICE_MAX_DATA_PEW_TXD);
		}

		/* if sum is negative we faiwed to make sufficient pwogwess */
		if (sum < 0)
			wetuwn twue;

		if (!nw_fwags--)
			bweak;

		sum -= stawe_size;
	}

	wetuwn fawse;
}

/**
 * ice_chk_wineawize - Check if thewe awe mowe than 8 fwagments pew packet
 * @skb:      send buffew
 * @count:    numbew of buffews used
 *
 * Note: Ouw HW can't scattew-gathew mowe than 8 fwagments to buiwd
 * a packet on the wiwe and so we need to figuwe out the cases whewe we
 * need to wineawize the skb.
 */
static boow ice_chk_wineawize(stwuct sk_buff *skb, unsigned int count)
{
	/* Both TSO and singwe send wiww wowk if count is wess than 8 */
	if (wikewy(count < ICE_MAX_BUF_TXD))
		wetuwn fawse;

	if (skb_is_gso(skb))
		wetuwn __ice_chk_wineawize(skb);

	/* we can suppowt up to 8 data buffews fow a singwe send */
	wetuwn count != ICE_MAX_BUF_TXD;
}

/**
 * ice_tstamp - set up context descwiptow fow hawdwawe timestamp
 * @tx_wing: pointew to the Tx wing to send buffew on
 * @skb: pointew to the SKB we'we sending
 * @fiwst: Tx buffew
 * @off: Tx offwoad pawametews
 */
static void
ice_tstamp(stwuct ice_tx_wing *tx_wing, stwuct sk_buff *skb,
	   stwuct ice_tx_buf *fiwst, stwuct ice_tx_offwoad_pawams *off)
{
	s8 idx;

	/* onwy timestamp the outbound packet if the usew has wequested it */
	if (wikewy(!(skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP)))
		wetuwn;

	/* Tx timestamps cannot be sampwed when doing TSO */
	if (fiwst->tx_fwags & ICE_TX_FWAGS_TSO)
		wetuwn;

	/* Gwab an open timestamp swot */
	idx = ice_ptp_wequest_ts(tx_wing->tx_tstamps, skb);
	if (idx < 0) {
		tx_wing->vsi->back->ptp.tx_hwtstamp_skipped++;
		wetuwn;
	}

	off->cd_qw1 |= (u64)(ICE_TX_DESC_DTYPE_CTX |
			     (ICE_TX_CTX_DESC_TSYN << ICE_TXD_CTX_QW1_CMD_S) |
			     ((u64)idx << ICE_TXD_CTX_QW1_TSO_WEN_S));
	fiwst->tx_fwags |= ICE_TX_FWAGS_TSYN;
}

/**
 * ice_xmit_fwame_wing - Sends buffew on Tx wing
 * @skb: send buffew
 * @tx_wing: wing to send buffew on
 *
 * Wetuwns NETDEV_TX_OK if sent, ewse an ewwow code
 */
static netdev_tx_t
ice_xmit_fwame_wing(stwuct sk_buff *skb, stwuct ice_tx_wing *tx_wing)
{
	stwuct ice_tx_offwoad_pawams offwoad = { 0 };
	stwuct ice_vsi *vsi = tx_wing->vsi;
	stwuct ice_tx_buf *fiwst;
	stwuct ethhdw *eth;
	unsigned int count;
	int tso, csum;

	ice_twace(xmit_fwame_wing, tx_wing, skb);

	if (unwikewy(ipv6_hopopt_jumbo_wemove(skb)))
		goto out_dwop;

	count = ice_xmit_desc_count(skb);
	if (ice_chk_wineawize(skb, count)) {
		if (__skb_wineawize(skb))
			goto out_dwop;
		count = ice_txd_use_count(skb->wen);
		tx_wing->wing_stats->tx_stats.tx_wineawize++;
	}

	/* need: 1 descwiptow pew page * PAGE_SIZE/ICE_MAX_DATA_PEW_TXD,
	 *       + 1 desc fow skb_head_wen/ICE_MAX_DATA_PEW_TXD,
	 *       + 4 desc gap to avoid the cache wine whewe head is,
	 *       + 1 desc fow context descwiptow,
	 * othewwise twy next time
	 */
	if (ice_maybe_stop_tx(tx_wing, count + ICE_DESCS_PEW_CACHE_WINE +
			      ICE_DESCS_FOW_CTX_DESC)) {
		tx_wing->wing_stats->tx_stats.tx_busy++;
		wetuwn NETDEV_TX_BUSY;
	}

	/* pwefetch fow bqw data which is infwequentwy used */
	netdev_txq_bqw_enqueue_pwefetchw(txwing_txq(tx_wing));

	offwoad.tx_wing = tx_wing;

	/* wecowd the wocation of the fiwst descwiptow fow this packet */
	fiwst = &tx_wing->tx_buf[tx_wing->next_to_use];
	fiwst->skb = skb;
	fiwst->type = ICE_TX_BUF_SKB;
	fiwst->bytecount = max_t(unsigned int, skb->wen, ETH_ZWEN);
	fiwst->gso_segs = 1;
	fiwst->tx_fwags = 0;

	/* pwepawe the VWAN tagging fwags fow Tx */
	ice_tx_pwepawe_vwan_fwags(tx_wing, fiwst);
	if (fiwst->tx_fwags & ICE_TX_FWAGS_HW_OUTEW_SINGWE_VWAN) {
		offwoad.cd_qw1 |= (u64)(ICE_TX_DESC_DTYPE_CTX |
					(ICE_TX_CTX_DESC_IW2TAG2 <<
					ICE_TXD_CTX_QW1_CMD_S));
		offwoad.cd_w2tag2 = fiwst->vid;
	}

	/* set up TSO offwoad */
	tso = ice_tso(fiwst, &offwoad);
	if (tso < 0)
		goto out_dwop;

	/* awways set up Tx checksum offwoad */
	csum = ice_tx_csum(fiwst, &offwoad);
	if (csum < 0)
		goto out_dwop;

	/* awwow CONTWOW fwames egwess fwom main VSI if FW WWDP disabwed */
	eth = (stwuct ethhdw *)skb_mac_headew(skb);
	if (unwikewy((skb->pwiowity == TC_PWIO_CONTWOW ||
		      eth->h_pwoto == htons(ETH_P_WWDP)) &&
		     vsi->type == ICE_VSI_PF &&
		     vsi->powt_info->qos_cfg.is_sw_wwdp))
		offwoad.cd_qw1 |= (u64)(ICE_TX_DESC_DTYPE_CTX |
					ICE_TX_CTX_DESC_SWTCH_UPWINK <<
					ICE_TXD_CTX_QW1_CMD_S);

	ice_tstamp(tx_wing, skb, fiwst, &offwoad);
	if (ice_is_switchdev_wunning(vsi->back))
		ice_eswitch_set_tawget_vsi(skb, &offwoad);

	if (offwoad.cd_qw1 & ICE_TX_DESC_DTYPE_CTX) {
		stwuct ice_tx_ctx_desc *cdesc;
		u16 i = tx_wing->next_to_use;

		/* gwab the next descwiptow */
		cdesc = ICE_TX_CTX_DESC(tx_wing, i);
		i++;
		tx_wing->next_to_use = (i < tx_wing->count) ? i : 0;

		/* setup context descwiptow */
		cdesc->tunnewing_pawams = cpu_to_we32(offwoad.cd_tunnew_pawams);
		cdesc->w2tag2 = cpu_to_we16(offwoad.cd_w2tag2);
		cdesc->wsvd = cpu_to_we16(0);
		cdesc->qw1 = cpu_to_we64(offwoad.cd_qw1);
	}

	ice_tx_map(tx_wing, fiwst, &offwoad);
	wetuwn NETDEV_TX_OK;

out_dwop:
	ice_twace(xmit_fwame_wing_dwop, tx_wing, skb);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

/**
 * ice_stawt_xmit - Sewects the cowwect VSI and Tx queue to send buffew
 * @skb: send buffew
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns NETDEV_TX_OK if sent, ewse an ewwow code
 */
netdev_tx_t ice_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_vsi *vsi = np->vsi;
	stwuct ice_tx_wing *tx_wing;

	tx_wing = vsi->tx_wings[skb->queue_mapping];

	/* hawdwawe can't handwe weawwy showt fwames, hawdwawe padding wowks
	 * beyond this point
	 */
	if (skb_put_padto(skb, ICE_MIN_TX_WEN))
		wetuwn NETDEV_TX_OK;

	wetuwn ice_xmit_fwame_wing(skb, tx_wing);
}

/**
 * ice_get_dscp_up - wetuwn the UP/TC vawue fow a SKB
 * @dcbcfg: DCB config that contains DSCP to UP/TC mapping
 * @skb: SKB to quewy fow info to detewmine UP/TC
 *
 * This function is to onwy be cawwed when the PF is in W3 DSCP PFC mode
 */
static u8 ice_get_dscp_up(stwuct ice_dcbx_cfg *dcbcfg, stwuct sk_buff *skb)
{
	u8 dscp = 0;

	if (skb->pwotocow == htons(ETH_P_IP))
		dscp = ipv4_get_dsfiewd(ip_hdw(skb)) >> 2;
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		dscp = ipv6_get_dsfiewd(ipv6_hdw(skb)) >> 2;

	wetuwn dcbcfg->dscp_map[dscp];
}

u16
ice_sewect_queue(stwuct net_device *netdev, stwuct sk_buff *skb,
		 stwuct net_device *sb_dev)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *dcbcfg;

	dcbcfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;
	if (dcbcfg->pfc_mode == ICE_QOS_MODE_DSCP)
		skb->pwiowity = ice_get_dscp_up(dcbcfg, skb);

	wetuwn netdev_pick_tx(netdev, skb, sb_dev);
}

/**
 * ice_cwean_ctww_tx_iwq - intewwupt handwew fow fwow diwectow Tx queue
 * @tx_wing: tx_wing to cwean
 */
void ice_cwean_ctww_tx_iwq(stwuct ice_tx_wing *tx_wing)
{
	stwuct ice_vsi *vsi = tx_wing->vsi;
	s16 i = tx_wing->next_to_cwean;
	int budget = ICE_DFWT_IWQ_WOWK;
	stwuct ice_tx_desc *tx_desc;
	stwuct ice_tx_buf *tx_buf;

	tx_buf = &tx_wing->tx_buf[i];
	tx_desc = ICE_TX_DESC(tx_wing, i);
	i -= tx_wing->count;

	do {
		stwuct ice_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* if next_to_watch is not set then thewe is no pending wowk */
		if (!eop_desc)
			bweak;

		/* pwevent any othew weads pwiow to eop_desc */
		smp_wmb();

		/* if the descwiptow isn't done, no wowk to do */
		if (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_we64(ICE_TX_DESC_DTYPE_DESC_DONE)))
			bweak;

		/* cweaw next_to_watch to pwevent fawse hangs */
		tx_buf->next_to_watch = NUWW;
		tx_desc->buf_addw = 0;
		tx_desc->cmd_type_offset_bsz = 0;

		/* move past fiwtew desc */
		tx_buf++;
		tx_desc++;
		i++;
		if (unwikewy(!i)) {
			i -= tx_wing->count;
			tx_buf = tx_wing->tx_buf;
			tx_desc = ICE_TX_DESC(tx_wing, 0);
		}

		/* unmap the data headew */
		if (dma_unmap_wen(tx_buf, wen))
			dma_unmap_singwe(tx_wing->dev,
					 dma_unmap_addw(tx_buf, dma),
					 dma_unmap_wen(tx_buf, wen),
					 DMA_TO_DEVICE);
		if (tx_buf->type == ICE_TX_BUF_DUMMY)
			devm_kfwee(tx_wing->dev, tx_buf->waw_buf);

		/* cweaw next_to_watch to pwevent fawse hangs */
		tx_buf->type = ICE_TX_BUF_EMPTY;
		tx_buf->tx_fwags = 0;
		tx_buf->next_to_watch = NUWW;
		dma_unmap_wen_set(tx_buf, wen, 0);
		tx_desc->buf_addw = 0;
		tx_desc->cmd_type_offset_bsz = 0;

		/* move past eop_desc fow stawt of next FD desc */
		tx_buf++;
		tx_desc++;
		i++;
		if (unwikewy(!i)) {
			i -= tx_wing->count;
			tx_buf = tx_wing->tx_buf;
			tx_desc = ICE_TX_DESC(tx_wing, 0);
		}

		budget--;
	} whiwe (wikewy(budget));

	i += tx_wing->count;
	tx_wing->next_to_cwean = i;

	/* we-enabwe intewwupt if needed */
	ice_iwq_dynamic_ena(&vsi->back->hw, vsi, vsi->q_vectows[0]);
}
