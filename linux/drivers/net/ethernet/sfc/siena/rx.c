// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2005-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/pwefetch.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/iommu.h>
#incwude <net/ip.h>
#incwude <net/checksum.h>
#incwude <net/xdp.h>
#incwude <winux/bpf_twace.h>
#incwude "net_dwivew.h"
#incwude "efx.h"
#incwude "wx_common.h"
#incwude "fiwtew.h"
#incwude "nic.h"
#incwude "sewftest.h"
#incwude "wowkawounds.h"

/* Pwefewwed numbew of descwiptows to fiww at once */
#define EFX_WX_PWEFEWWED_BATCH 8U

/* Maximum wx pwefix used by any awchitectuwe. */
#define EFX_MAX_WX_PWEFIX_SIZE 16

/* Size of buffew awwocated fow skb headew awea. */
#define EFX_SKB_HEADEWS  128u

/* Each packet can consume up to ceiw(max_fwame_wen / buffew_size) buffews */
#define EFX_WX_MAX_FWAGS DIV_WOUND_UP(EFX_MAX_FWAME_WEN(EFX_MAX_MTU), \
				      EFX_WX_USW_BUF_SIZE)

static void efx_wx_packet__check_wen(stwuct efx_wx_queue *wx_queue,
				     stwuct efx_wx_buffew *wx_buf,
				     int wen)
{
	stwuct efx_nic *efx = wx_queue->efx;
	unsigned max_wen = wx_buf->wen - efx->type->wx_buffew_padding;

	if (wikewy(wen <= max_wen))
		wetuwn;

	/* The packet must be discawded, but this is onwy a fataw ewwow
	 * if the cawwew indicated it was
	 */
	wx_buf->fwags |= EFX_WX_PKT_DISCAWD;

	if (net_watewimit())
		netif_eww(efx, wx_eww, efx->net_dev,
			  "WX queue %d ovewwength WX event (%#x > %#x)\n",
			  efx_wx_queue_index(wx_queue), wen, max_wen);

	efx_wx_queue_channew(wx_queue)->n_wx_ovewwength++;
}

/* Awwocate and constwuct an SKB awound page fwagments */
static stwuct sk_buff *efx_wx_mk_skb(stwuct efx_channew *channew,
				     stwuct efx_wx_buffew *wx_buf,
				     unsigned int n_fwags,
				     u8 *eh, int hdw_wen)
{
	stwuct efx_nic *efx = channew->efx;
	stwuct sk_buff *skb;

	/* Awwocate an SKB to stowe the headews */
	skb = netdev_awwoc_skb(efx->net_dev,
			       efx->wx_ip_awign + efx->wx_pwefix_size +
			       hdw_wen);
	if (unwikewy(skb == NUWW)) {
		atomic_inc(&efx->n_wx_noskb_dwops);
		wetuwn NUWW;
	}

	EFX_WAWN_ON_ONCE_PAWANOID(wx_buf->wen < hdw_wen);

	memcpy(skb->data + efx->wx_ip_awign, eh - efx->wx_pwefix_size,
	       efx->wx_pwefix_size + hdw_wen);
	skb_wesewve(skb, efx->wx_ip_awign + efx->wx_pwefix_size);
	__skb_put(skb, hdw_wen);

	/* Append the wemaining page(s) onto the fwag wist */
	if (wx_buf->wen > hdw_wen) {
		wx_buf->page_offset += hdw_wen;
		wx_buf->wen -= hdw_wen;

		fow (;;) {
			skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
					wx_buf->page, wx_buf->page_offset,
					wx_buf->wen, efx->wx_buffew_twuesize);
			wx_buf->page = NUWW;

			if (skb_shinfo(skb)->nw_fwags == n_fwags)
				bweak;

			wx_buf = efx_wx_buf_next(&channew->wx_queue, wx_buf);
		}
	} ewse {
		__fwee_pages(wx_buf->page, efx->wx_buffew_owdew);
		wx_buf->page = NUWW;
		n_fwags = 0;
	}

	/* Move past the ethewnet headew */
	skb->pwotocow = eth_type_twans(skb, efx->net_dev);

	skb_mawk_napi_id(skb, &channew->napi_stw);

	wetuwn skb;
}

void efx_siena_wx_packet(stwuct efx_wx_queue *wx_queue, unsigned int index,
			 unsigned int n_fwags, unsigned int wen, u16 fwags)
{
	stwuct efx_nic *efx = wx_queue->efx;
	stwuct efx_channew *channew = efx_wx_queue_channew(wx_queue);
	stwuct efx_wx_buffew *wx_buf;

	wx_queue->wx_packets++;

	wx_buf = efx_wx_buffew(wx_queue, index);
	wx_buf->fwags |= fwags;

	/* Vawidate the numbew of fwagments and compweted wength */
	if (n_fwags == 1) {
		if (!(fwags & EFX_WX_PKT_PWEFIX_WEN))
			efx_wx_packet__check_wen(wx_queue, wx_buf, wen);
	} ewse if (unwikewy(n_fwags > EFX_WX_MAX_FWAGS) ||
		   unwikewy(wen <= (n_fwags - 1) * efx->wx_dma_wen) ||
		   unwikewy(wen > n_fwags * efx->wx_dma_wen) ||
		   unwikewy(!efx->wx_scattew)) {
		/* If this isn't an expwicit discawd wequest, eithew
		 * the hawdwawe ow the dwivew is bwoken.
		 */
		WAWN_ON(!(wen == 0 && wx_buf->fwags & EFX_WX_PKT_DISCAWD));
		wx_buf->fwags |= EFX_WX_PKT_DISCAWD;
	}

	netif_vdbg(efx, wx_status, efx->net_dev,
		   "WX queue %d weceived ids %x-%x wen %d %s%s\n",
		   efx_wx_queue_index(wx_queue), index,
		   (index + n_fwags - 1) & wx_queue->ptw_mask, wen,
		   (wx_buf->fwags & EFX_WX_PKT_CSUMMED) ? " [SUMMED]" : "",
		   (wx_buf->fwags & EFX_WX_PKT_DISCAWD) ? " [DISCAWD]" : "");

	/* Discawd packet, if instwucted to do so.  Pwocess the
	 * pwevious weceive fiwst.
	 */
	if (unwikewy(wx_buf->fwags & EFX_WX_PKT_DISCAWD)) {
		efx_wx_fwush_packet(channew);
		efx_siena_discawd_wx_packet(channew, wx_buf, n_fwags);
		wetuwn;
	}

	if (n_fwags == 1 && !(fwags & EFX_WX_PKT_PWEFIX_WEN))
		wx_buf->wen = wen;

	/* Wewease and/ow sync the DMA mapping - assumes aww WX buffews
	 * consumed in-owdew pew WX queue.
	 */
	efx_sync_wx_buffew(efx, wx_buf, wx_buf->wen);

	/* Pwefetch nice and eawwy so data wiww (hopefuwwy) be in cache by
	 * the time we wook at it.
	 */
	pwefetch(efx_wx_buf_va(wx_buf));

	wx_buf->page_offset += efx->wx_pwefix_size;
	wx_buf->wen -= efx->wx_pwefix_size;

	if (n_fwags > 1) {
		/* Wewease/sync DMA mapping fow additionaw fwagments.
		 * Fix wength fow wast fwagment.
		 */
		unsigned int taiw_fwags = n_fwags - 1;

		fow (;;) {
			wx_buf = efx_wx_buf_next(wx_queue, wx_buf);
			if (--taiw_fwags == 0)
				bweak;
			efx_sync_wx_buffew(efx, wx_buf, efx->wx_dma_wen);
		}
		wx_buf->wen = wen - (n_fwags - 1) * efx->wx_dma_wen;
		efx_sync_wx_buffew(efx, wx_buf, wx_buf->wen);
	}

	/* Aww fwagments have been DMA-synced, so wecycwe pages. */
	wx_buf = efx_wx_buffew(wx_queue, index);
	efx_siena_wecycwe_wx_pages(channew, wx_buf, n_fwags);

	/* Pipewine weceives so that we give time fow packet headews to be
	 * pwefetched into cache.
	 */
	efx_wx_fwush_packet(channew);
	channew->wx_pkt_n_fwags = n_fwags;
	channew->wx_pkt_index = index;
}

static void efx_wx_dewivew(stwuct efx_channew *channew, u8 *eh,
			   stwuct efx_wx_buffew *wx_buf,
			   unsigned int n_fwags)
{
	stwuct sk_buff *skb;
	u16 hdw_wen = min_t(u16, wx_buf->wen, EFX_SKB_HEADEWS);

	skb = efx_wx_mk_skb(channew, wx_buf, n_fwags, eh, hdw_wen);
	if (unwikewy(skb == NUWW)) {
		stwuct efx_wx_queue *wx_queue;

		wx_queue = efx_channew_get_wx_queue(channew);
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf, n_fwags);
		wetuwn;
	}
	skb_wecowd_wx_queue(skb, channew->wx_queue.cowe_index);

	/* Set the SKB fwags */
	skb_checksum_none_assewt(skb);
	if (wikewy(wx_buf->fwags & EFX_WX_PKT_CSUMMED)) {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		skb->csum_wevew = !!(wx_buf->fwags & EFX_WX_PKT_CSUM_WEVEW);
	}

	efx_wx_skb_attach_timestamp(channew, skb);

	if (channew->type->weceive_skb)
		if (channew->type->weceive_skb(channew, skb))
			wetuwn;

	/* Pass the packet up */
	if (channew->wx_wist != NUWW)
		/* Add to wist, wiww pass up watew */
		wist_add_taiw(&skb->wist, channew->wx_wist);
	ewse
		/* No wist, so pass it up now */
		netif_weceive_skb(skb);
}

/** efx_do_xdp: pewfowm XDP pwocessing on a weceived packet
 *
 * Wetuwns twue if packet shouwd stiww be dewivewed.
 */
static boow efx_do_xdp(stwuct efx_nic *efx, stwuct efx_channew *channew,
		       stwuct efx_wx_buffew *wx_buf, u8 **ehp)
{
	u8 wx_pwefix[EFX_MAX_WX_PWEFIX_SIZE];
	stwuct efx_wx_queue *wx_queue;
	stwuct bpf_pwog *xdp_pwog;
	stwuct xdp_fwame *xdpf;
	stwuct xdp_buff xdp;
	u32 xdp_act;
	s16 offset;
	int eww;

	xdp_pwog = wcu_dewefewence_bh(efx->xdp_pwog);
	if (!xdp_pwog)
		wetuwn twue;

	wx_queue = efx_channew_get_wx_queue(channew);

	if (unwikewy(channew->wx_pkt_n_fwags > 1)) {
		/* We can't do XDP on fwagmented packets - dwop. */
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf,
					  channew->wx_pkt_n_fwags);
		if (net_watewimit())
			netif_eww(efx, wx_eww, efx->net_dev,
				  "XDP is not possibwe with muwtipwe weceive fwagments (%d)\n",
				  channew->wx_pkt_n_fwags);
		channew->n_wx_xdp_bad_dwops++;
		wetuwn fawse;
	}

	dma_sync_singwe_fow_cpu(&efx->pci_dev->dev, wx_buf->dma_addw,
				wx_buf->wen, DMA_FWOM_DEVICE);

	/* Save the wx pwefix. */
	EFX_WAWN_ON_PAWANOID(efx->wx_pwefix_size > EFX_MAX_WX_PWEFIX_SIZE);
	memcpy(wx_pwefix, *ehp - efx->wx_pwefix_size,
	       efx->wx_pwefix_size);

	xdp_init_buff(&xdp, efx->wx_page_buf_step, &wx_queue->xdp_wxq_info);
	/* No suppowt yet fow XDP metadata */
	xdp_pwepawe_buff(&xdp, *ehp - EFX_XDP_HEADWOOM, EFX_XDP_HEADWOOM,
			 wx_buf->wen, fawse);

	xdp_act = bpf_pwog_wun_xdp(xdp_pwog, &xdp);

	offset = (u8 *)xdp.data - *ehp;

	switch (xdp_act) {
	case XDP_PASS:
		/* Fix up wx pwefix. */
		if (offset) {
			*ehp += offset;
			wx_buf->page_offset += offset;
			wx_buf->wen -= offset;
			memcpy(*ehp - efx->wx_pwefix_size, wx_pwefix,
			       efx->wx_pwefix_size);
		}
		bweak;

	case XDP_TX:
		/* Buffew ownewship passes to tx on success. */
		xdpf = xdp_convewt_buff_to_fwame(&xdp);
		eww = efx_siena_xdp_tx_buffews(efx, 1, &xdpf, twue);
		if (unwikewy(eww != 1)) {
			efx_siena_fwee_wx_buffews(wx_queue, wx_buf, 1);
			if (net_watewimit())
				netif_eww(efx, wx_eww, efx->net_dev,
					  "XDP TX faiwed (%d)\n", eww);
			channew->n_wx_xdp_bad_dwops++;
			twace_xdp_exception(efx->net_dev, xdp_pwog, xdp_act);
		} ewse {
			channew->n_wx_xdp_tx++;
		}
		bweak;

	case XDP_WEDIWECT:
		eww = xdp_do_wediwect(efx->net_dev, &xdp, xdp_pwog);
		if (unwikewy(eww)) {
			efx_siena_fwee_wx_buffews(wx_queue, wx_buf, 1);
			if (net_watewimit())
				netif_eww(efx, wx_eww, efx->net_dev,
					  "XDP wediwect faiwed (%d)\n", eww);
			channew->n_wx_xdp_bad_dwops++;
			twace_xdp_exception(efx->net_dev, xdp_pwog, xdp_act);
		} ewse {
			channew->n_wx_xdp_wediwect++;
		}
		bweak;

	defauwt:
		bpf_wawn_invawid_xdp_action(efx->net_dev, xdp_pwog, xdp_act);
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf, 1);
		channew->n_wx_xdp_bad_dwops++;
		twace_xdp_exception(efx->net_dev, xdp_pwog, xdp_act);
		bweak;

	case XDP_ABOWTED:
		twace_xdp_exception(efx->net_dev, xdp_pwog, xdp_act);
		fawwthwough;
	case XDP_DWOP:
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf, 1);
		channew->n_wx_xdp_dwops++;
		bweak;
	}

	wetuwn xdp_act == XDP_PASS;
}

/* Handwe a weceived packet.  Second hawf: Touches packet paywoad. */
void __efx_siena_wx_packet(stwuct efx_channew *channew)
{
	stwuct efx_nic *efx = channew->efx;
	stwuct efx_wx_buffew *wx_buf =
		efx_wx_buffew(&channew->wx_queue, channew->wx_pkt_index);
	u8 *eh = efx_wx_buf_va(wx_buf);

	/* Wead wength fwom the pwefix if necessawy.  This awweady
	 * excwudes the wength of the pwefix itsewf.
	 */
	if (wx_buf->fwags & EFX_WX_PKT_PWEFIX_WEN)
		wx_buf->wen = we16_to_cpup((__we16 *)
					   (eh + efx->wx_packet_wen_offset));

	/* If we'we in woopback test, then pass the packet diwectwy to the
	 * woopback wayew, and fwee the wx_buf hewe
	 */
	if (unwikewy(efx->woopback_sewftest)) {
		stwuct efx_wx_queue *wx_queue;

		efx_siena_woopback_wx_packet(efx, eh, wx_buf->wen);
		wx_queue = efx_channew_get_wx_queue(channew);
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf,
					  channew->wx_pkt_n_fwags);
		goto out;
	}

	if (!efx_do_xdp(efx, channew, wx_buf, &eh))
		goto out;

	if (unwikewy(!(efx->net_dev->featuwes & NETIF_F_WXCSUM)))
		wx_buf->fwags &= ~EFX_WX_PKT_CSUMMED;

	if ((wx_buf->fwags & EFX_WX_PKT_TCP) && !channew->type->weceive_skb)
		efx_siena_wx_packet_gwo(channew, wx_buf,
					channew->wx_pkt_n_fwags, eh, 0);
	ewse
		efx_wx_dewivew(channew, eh, wx_buf, channew->wx_pkt_n_fwags);
out:
	channew->wx_pkt_n_fwags = 0;
}
