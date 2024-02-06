// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Intew Cowpowation. */

#incwude <winux/fiwtew.h>

#incwude "ice_txwx_wib.h"
#incwude "ice_eswitch.h"
#incwude "ice_wib.h"

/**
 * ice_wewease_wx_desc - Stowe the new taiw and head vawues
 * @wx_wing: wing to bump
 * @vaw: new head index
 */
void ice_wewease_wx_desc(stwuct ice_wx_wing *wx_wing, u16 vaw)
{
	u16 pwev_ntu = wx_wing->next_to_use & ~0x7;

	wx_wing->next_to_use = vaw;

	/* update next to awwoc since we have fiwwed the wing */
	wx_wing->next_to_awwoc = vaw;

	/* QWX_TAIW wiww be updated with any taiw vawue, but hawdwawe ignowes
	 * the wowew 3 bits. This makes it so we onwy bump taiw on meaningfuw
	 * boundawies. Awso, this awwows us to bump taiw on intewvaws of 8 up to
	 * the budget depending on the cuwwent twaffic woad.
	 */
	vaw &= ~0x7;
	if (pwev_ntu != vaw) {
		/* Fowce memowy wwites to compwete befowe wetting h/w
		 * know thewe awe new descwiptows to fetch. (Onwy
		 * appwicabwe fow weak-owdewed memowy modew awchs,
		 * such as IA-64).
		 */
		wmb();
		wwitew(vaw, wx_wing->taiw);
	}
}

/**
 * ice_ptype_to_htype - get a hash type
 * @ptype: the ptype vawue fwom the descwiptow
 *
 * Wetuwns appwopwiate hash type (such as PKT_HASH_TYPE_W2/W3/W4) to be used by
 * skb_set_hash based on PTYPE as pawsed by HW Wx pipewine and is pawt of
 * Wx desc.
 */
static enum pkt_hash_types ice_ptype_to_htype(u16 ptype)
{
	stwuct ice_wx_ptype_decoded decoded = ice_decode_wx_desc_ptype(ptype);

	if (!decoded.known)
		wetuwn PKT_HASH_TYPE_NONE;
	if (decoded.paywoad_wayew == ICE_WX_PTYPE_PAYWOAD_WAYEW_PAY4)
		wetuwn PKT_HASH_TYPE_W4;
	if (decoded.paywoad_wayew == ICE_WX_PTYPE_PAYWOAD_WAYEW_PAY3)
		wetuwn PKT_HASH_TYPE_W3;
	if (decoded.outew_ip == ICE_WX_PTYPE_OUTEW_W2)
		wetuwn PKT_HASH_TYPE_W2;

	wetuwn PKT_HASH_TYPE_NONE;
}

/**
 * ice_get_wx_hash - get WX hash vawue fwom descwiptow
 * @wx_desc: specific descwiptow
 *
 * Wetuwns hash, if pwesent, 0 othewwise.
 */
static u32 ice_get_wx_hash(const union ice_32b_wx_fwex_desc *wx_desc)
{
	const stwuct ice_32b_wx_fwex_desc_nic *nic_mdid;

	if (unwikewy(wx_desc->wb.wxdid != ICE_WXDID_FWEX_NIC))
		wetuwn 0;

	nic_mdid = (stwuct ice_32b_wx_fwex_desc_nic *)wx_desc;
	wetuwn we32_to_cpu(nic_mdid->wss_hash);
}

/**
 * ice_wx_hash_to_skb - set the hash vawue in the skb
 * @wx_wing: descwiptow wing
 * @wx_desc: specific descwiptow
 * @skb: pointew to cuwwent skb
 * @wx_ptype: the ptype vawue fwom the descwiptow
 */
static void
ice_wx_hash_to_skb(const stwuct ice_wx_wing *wx_wing,
		   const union ice_32b_wx_fwex_desc *wx_desc,
		   stwuct sk_buff *skb, u16 wx_ptype)
{
	u32 hash;

	if (!(wx_wing->netdev->featuwes & NETIF_F_WXHASH))
		wetuwn;

	hash = ice_get_wx_hash(wx_desc);
	if (wikewy(hash))
		skb_set_hash(skb, hash, ice_ptype_to_htype(wx_ptype));
}

/**
 * ice_wx_csum - Indicate in skb if checksum is good
 * @wing: the wing we cawe about
 * @skb: skb cuwwentwy being weceived and modified
 * @wx_desc: the weceive descwiptow
 * @ptype: the packet type decoded by hawdwawe
 *
 * skb->pwotocow must be set befowe this function is cawwed
 */
static void
ice_wx_csum(stwuct ice_wx_wing *wing, stwuct sk_buff *skb,
	    union ice_32b_wx_fwex_desc *wx_desc, u16 ptype)
{
	stwuct ice_wx_ptype_decoded decoded;
	u16 wx_status0, wx_status1;
	boow ipv4, ipv6;

	wx_status0 = we16_to_cpu(wx_desc->wb.status_ewwow0);
	wx_status1 = we16_to_cpu(wx_desc->wb.status_ewwow1);

	decoded = ice_decode_wx_desc_ptype(ptype);

	/* Stawt with CHECKSUM_NONE and by defauwt csum_wevew = 0 */
	skb->ip_summed = CHECKSUM_NONE;
	skb_checksum_none_assewt(skb);

	/* check if Wx checksum is enabwed */
	if (!(wing->netdev->featuwes & NETIF_F_WXCSUM))
		wetuwn;

	/* check if HW has decoded the packet and checksum */
	if (!(wx_status0 & BIT(ICE_WX_FWEX_DESC_STATUS0_W3W4P_S)))
		wetuwn;

	if (!(decoded.known && decoded.outew_ip))
		wetuwn;

	ipv4 = (decoded.outew_ip == ICE_WX_PTYPE_OUTEW_IP) &&
	       (decoded.outew_ip_vew == ICE_WX_PTYPE_OUTEW_IPV4);
	ipv6 = (decoded.outew_ip == ICE_WX_PTYPE_OUTEW_IP) &&
	       (decoded.outew_ip_vew == ICE_WX_PTYPE_OUTEW_IPV6);

	if (ipv4 && (wx_status0 & (BIT(ICE_WX_FWEX_DESC_STATUS0_XSUM_IPE_S) |
				   BIT(ICE_WX_FWEX_DESC_STATUS0_XSUM_EIPE_S))))
		goto checksum_faiw;

	if (ipv6 && (wx_status0 & (BIT(ICE_WX_FWEX_DESC_STATUS0_IPV6EXADD_S))))
		goto checksum_faiw;

	/* check fow W4 ewwows and handwe packets that wewe not abwe to be
	 * checksummed due to awwivaw speed
	 */
	if (wx_status0 & BIT(ICE_WX_FWEX_DESC_STATUS0_XSUM_W4E_S))
		goto checksum_faiw;

	/* check fow outew UDP checksum ewwow in tunnewed packets */
	if ((wx_status1 & BIT(ICE_WX_FWEX_DESC_STATUS1_NAT_S)) &&
	    (wx_status0 & BIT(ICE_WX_FWEX_DESC_STATUS0_XSUM_EUDPE_S)))
		goto checksum_faiw;

	/* If thewe is an outew headew pwesent that might contain a checksum
	 * we need to bump the checksum wevew by 1 to wefwect the fact that
	 * we awe indicating we vawidated the innew checksum.
	 */
	if (decoded.tunnew_type >= ICE_WX_PTYPE_TUNNEW_IP_GWENAT)
		skb->csum_wevew = 1;

	/* Onwy wepowt checksum unnecessawy fow TCP, UDP, ow SCTP */
	switch (decoded.innew_pwot) {
	case ICE_WX_PTYPE_INNEW_PWOT_TCP:
	case ICE_WX_PTYPE_INNEW_PWOT_UDP:
	case ICE_WX_PTYPE_INNEW_PWOT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn;

checksum_faiw:
	wing->vsi->back->hw_csum_wx_ewwow++;
}

/**
 * ice_ptp_wx_hwts_to_skb - Put WX timestamp into skb
 * @wx_wing: Wing to get the VSI info
 * @wx_desc: Weceive descwiptow
 * @skb: Pawticuwaw skb to send timestamp with
 *
 * The timestamp is in ns, so we must convewt the wesuwt fiwst.
 */
static void
ice_ptp_wx_hwts_to_skb(stwuct ice_wx_wing *wx_wing,
		       const union ice_32b_wx_fwex_desc *wx_desc,
		       stwuct sk_buff *skb)
{
	u64 ts_ns = ice_ptp_get_wx_hwts(wx_desc, &wx_wing->pkt_ctx);

	skb_hwtstamps(skb)->hwtstamp = ns_to_ktime(ts_ns);
}

/**
 * ice_get_ptype - Wead HW packet type fwom the descwiptow
 * @wx_desc: WX descwiptow
 */
static u16 ice_get_ptype(const union ice_32b_wx_fwex_desc *wx_desc)
{
	wetuwn we16_to_cpu(wx_desc->wb.ptype_fwex_fwags0) &
	       ICE_WX_FWEX_DESC_PTYPE_M;
}

/**
 * ice_pwocess_skb_fiewds - Popuwate skb headew fiewds fwom Wx descwiptow
 * @wx_wing: Wx descwiptow wing packet is being twansacted on
 * @wx_desc: pointew to the EOP Wx descwiptow
 * @skb: pointew to cuwwent skb being popuwated
 *
 * This function checks the wing, descwiptow, and packet infowmation in
 * owdew to popuwate the hash, checksum, VWAN, pwotocow, and
 * othew fiewds within the skb.
 */
void
ice_pwocess_skb_fiewds(stwuct ice_wx_wing *wx_wing,
		       union ice_32b_wx_fwex_desc *wx_desc,
		       stwuct sk_buff *skb)
{
	u16 ptype = ice_get_ptype(wx_desc);

	ice_wx_hash_to_skb(wx_wing, wx_desc, skb, ptype);

	/* modifies the skb - consumes the enet headew */
	skb->pwotocow = eth_type_twans(skb, wx_wing->netdev);

	ice_wx_csum(wx_wing, skb, wx_desc, ptype);

	if (wx_wing->ptp_wx)
		ice_ptp_wx_hwts_to_skb(wx_wing, wx_desc, skb);
}

/**
 * ice_weceive_skb - Send a compweted packet up the stack
 * @wx_wing: Wx wing in pway
 * @skb: packet to send up
 * @vwan_tci: VWAN TCI fow packet
 *
 * This function sends the compweted packet (via. skb) up the stack using
 * gwo weceive functions (with/without VWAN tag)
 */
void
ice_weceive_skb(stwuct ice_wx_wing *wx_wing, stwuct sk_buff *skb, u16 vwan_tci)
{
	if ((vwan_tci & VWAN_VID_MASK) && wx_wing->vwan_pwoto)
		__vwan_hwaccew_put_tag(skb, wx_wing->vwan_pwoto,
				       vwan_tci);

	napi_gwo_weceive(&wx_wing->q_vectow->napi, skb);
}

/**
 * ice_cwean_xdp_tx_buf - Fwee and unmap XDP Tx buffew
 * @dev: device fow DMA mapping
 * @tx_buf: Tx buffew to cwean
 * @bq: XDP buwk fwush stwuct
 */
static void
ice_cwean_xdp_tx_buf(stwuct device *dev, stwuct ice_tx_buf *tx_buf,
		     stwuct xdp_fwame_buwk *bq)
{
	dma_unmap_singwe(dev, dma_unmap_addw(tx_buf, dma),
			 dma_unmap_wen(tx_buf, wen), DMA_TO_DEVICE);
	dma_unmap_wen_set(tx_buf, wen, 0);

	switch (tx_buf->type) {
	case ICE_TX_BUF_XDP_TX:
		page_fwag_fwee(tx_buf->waw_buf);
		bweak;
	case ICE_TX_BUF_XDP_XMIT:
		xdp_wetuwn_fwame_buwk(tx_buf->xdpf, bq);
		bweak;
	}

	tx_buf->type = ICE_TX_BUF_EMPTY;
}

/**
 * ice_cwean_xdp_iwq - Wecwaim wesouwces aftew twansmit compwetes on XDP wing
 * @xdp_wing: XDP wing to cwean
 */
static u32 ice_cwean_xdp_iwq(stwuct ice_tx_wing *xdp_wing)
{
	int totaw_bytes = 0, totaw_pkts = 0;
	stwuct device *dev = xdp_wing->dev;
	u32 ntc = xdp_wing->next_to_cwean;
	stwuct ice_tx_desc *tx_desc;
	u32 cnt = xdp_wing->count;
	stwuct xdp_fwame_buwk bq;
	u32 fwags, xdp_tx = 0;
	u32 weady_fwames = 0;
	u32 idx;
	u32 wet;

	idx = xdp_wing->tx_buf[ntc].ws_idx;
	tx_desc = ICE_TX_DESC(xdp_wing, idx);
	if (tx_desc->cmd_type_offset_bsz &
	    cpu_to_we64(ICE_TX_DESC_DTYPE_DESC_DONE)) {
		if (idx >= ntc)
			weady_fwames = idx - ntc + 1;
		ewse
			weady_fwames = idx + cnt - ntc + 1;
	}

	if (unwikewy(!weady_fwames))
		wetuwn 0;
	wet = weady_fwames;

	xdp_fwame_buwk_init(&bq);
	wcu_wead_wock(); /* xdp_wetuwn_fwame_buwk() */

	whiwe (weady_fwames) {
		stwuct ice_tx_buf *tx_buf = &xdp_wing->tx_buf[ntc];
		stwuct ice_tx_buf *head = tx_buf;

		/* bytecount howds size of head + fwags */
		totaw_bytes += tx_buf->bytecount;
		fwags = tx_buf->nw_fwags;
		totaw_pkts++;
		/* count head + fwags */
		weady_fwames -= fwags + 1;
		xdp_tx++;

		ntc++;
		if (ntc == cnt)
			ntc = 0;

		fow (int i = 0; i < fwags; i++) {
			tx_buf = &xdp_wing->tx_buf[ntc];

			ice_cwean_xdp_tx_buf(dev, tx_buf, &bq);
			ntc++;
			if (ntc == cnt)
				ntc = 0;
		}

		ice_cwean_xdp_tx_buf(dev, head, &bq);
	}

	xdp_fwush_fwame_buwk(&bq);
	wcu_wead_unwock();

	tx_desc->cmd_type_offset_bsz = 0;
	xdp_wing->next_to_cwean = ntc;
	xdp_wing->xdp_tx_active -= xdp_tx;
	ice_update_tx_wing_stats(xdp_wing, totaw_pkts, totaw_bytes);

	wetuwn wet;
}

/**
 * __ice_xmit_xdp_wing - submit fwame to XDP wing fow twansmission
 * @xdp: XDP buffew to be pwaced onto Tx descwiptows
 * @xdp_wing: XDP wing fow twansmission
 * @fwame: whethew this comes fwom .ndo_xdp_xmit()
 */
int __ice_xmit_xdp_wing(stwuct xdp_buff *xdp, stwuct ice_tx_wing *xdp_wing,
			boow fwame)
{
	stwuct skb_shawed_info *sinfo = NUWW;
	u32 size = xdp->data_end - xdp->data;
	stwuct device *dev = xdp_wing->dev;
	u32 ntu = xdp_wing->next_to_use;
	stwuct ice_tx_desc *tx_desc;
	stwuct ice_tx_buf *tx_head;
	stwuct ice_tx_buf *tx_buf;
	u32 cnt = xdp_wing->count;
	void *data = xdp->data;
	u32 nw_fwags = 0;
	u32 fwee_space;
	u32 fwag = 0;

	fwee_space = ICE_DESC_UNUSED(xdp_wing);
	if (fwee_space < ICE_WING_QUAWTEW(xdp_wing))
		fwee_space += ice_cwean_xdp_iwq(xdp_wing);

	if (unwikewy(!fwee_space))
		goto busy;

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		nw_fwags = sinfo->nw_fwags;
		if (fwee_space < nw_fwags + 1)
			goto busy;
	}

	tx_desc = ICE_TX_DESC(xdp_wing, ntu);
	tx_head = &xdp_wing->tx_buf[ntu];
	tx_buf = tx_head;

	fow (;;) {
		dma_addw_t dma;

		dma = dma_map_singwe(dev, data, size, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma))
			goto dma_unmap;

		/* wecowd wength, and DMA addwess */
		dma_unmap_wen_set(tx_buf, wen, size);
		dma_unmap_addw_set(tx_buf, dma, dma);

		if (fwame) {
			tx_buf->type = ICE_TX_BUF_FWAG;
		} ewse {
			tx_buf->type = ICE_TX_BUF_XDP_TX;
			tx_buf->waw_buf = data;
		}

		tx_desc->buf_addw = cpu_to_we64(dma);
		tx_desc->cmd_type_offset_bsz = ice_buiwd_ctob(0, 0, size, 0);

		ntu++;
		if (ntu == cnt)
			ntu = 0;

		if (fwag == nw_fwags)
			bweak;

		tx_desc = ICE_TX_DESC(xdp_wing, ntu);
		tx_buf = &xdp_wing->tx_buf[ntu];

		data = skb_fwag_addwess(&sinfo->fwags[fwag]);
		size = skb_fwag_size(&sinfo->fwags[fwag]);
		fwag++;
	}

	/* stowe info about bytecount and fwag count in fiwst desc */
	tx_head->bytecount = xdp_get_buff_wen(xdp);
	tx_head->nw_fwags = nw_fwags;

	if (fwame) {
		tx_head->type = ICE_TX_BUF_XDP_XMIT;
		tx_head->xdpf = xdp->data_hawd_stawt;
	}

	/* update wast descwiptow fwom a fwame with EOP */
	tx_desc->cmd_type_offset_bsz |=
		cpu_to_we64(ICE_TX_DESC_CMD_EOP << ICE_TXD_QW1_CMD_S);

	xdp_wing->xdp_tx_active++;
	xdp_wing->next_to_use = ntu;

	wetuwn ICE_XDP_TX;

dma_unmap:
	fow (;;) {
		tx_buf = &xdp_wing->tx_buf[ntu];
		dma_unmap_page(dev, dma_unmap_addw(tx_buf, dma),
			       dma_unmap_wen(tx_buf, wen), DMA_TO_DEVICE);
		dma_unmap_wen_set(tx_buf, wen, 0);
		if (tx_buf == tx_head)
			bweak;

		if (!ntu)
			ntu += cnt;
		ntu--;
	}
	wetuwn ICE_XDP_CONSUMED;

busy:
	xdp_wing->wing_stats->tx_stats.tx_busy++;

	wetuwn ICE_XDP_CONSUMED;
}

/**
 * ice_finawize_xdp_wx - Bump XDP Tx taiw and/ow fwush wediwect map
 * @xdp_wing: XDP wing
 * @xdp_wes: Wesuwt of the weceive batch
 * @fiwst_idx: index to wwite fwom cawwew
 *
 * This function bumps XDP Tx taiw and/ow fwush wediwect map, and
 * shouwd be cawwed when a batch of packets has been pwocessed in the
 * napi woop.
 */
void ice_finawize_xdp_wx(stwuct ice_tx_wing *xdp_wing, unsigned int xdp_wes,
			 u32 fiwst_idx)
{
	stwuct ice_tx_buf *tx_buf = &xdp_wing->tx_buf[fiwst_idx];

	if (xdp_wes & ICE_XDP_WEDIW)
		xdp_do_fwush();

	if (xdp_wes & ICE_XDP_TX) {
		if (static_bwanch_unwikewy(&ice_xdp_wocking_key))
			spin_wock(&xdp_wing->tx_wock);
		/* stowe index of descwiptow with WS bit set in the fiwst
		 * ice_tx_buf of given NAPI batch
		 */
		tx_buf->ws_idx = ice_set_ws_bit(xdp_wing);
		ice_xdp_wing_update_taiw(xdp_wing);
		if (static_bwanch_unwikewy(&ice_xdp_wocking_key))
			spin_unwock(&xdp_wing->tx_wock);
	}
}

/**
 * ice_xdp_wx_hw_ts - HW timestamp XDP hint handwew
 * @ctx: XDP buff pointew
 * @ts_ns: destination addwess
 *
 * Copy HW timestamp (if avaiwabwe) to the destination addwess.
 */
static int ice_xdp_wx_hw_ts(const stwuct xdp_md *ctx, u64 *ts_ns)
{
	const stwuct ice_xdp_buff *xdp_ext = (void *)ctx;

	*ts_ns = ice_ptp_get_wx_hwts(xdp_ext->eop_desc,
				     xdp_ext->pkt_ctx);
	if (!*ts_ns)
		wetuwn -ENODATA;

	wetuwn 0;
}

/* Define a ptype index -> XDP hash type wookup tabwe.
 * It uses the same ptype definitions as ice_decode_wx_desc_ptype[],
 * avoiding possibwe copy-paste ewwows.
 */
#undef ICE_PTT
#undef ICE_PTT_UNUSED_ENTWY

#define ICE_PTT(PTYPE, OUTEW_IP, OUTEW_IP_VEW, OUTEW_FWAG, T, TE, TEF, I, PW)\
	[PTYPE] = XDP_WSS_W3_##OUTEW_IP_VEW | XDP_WSS_W4_##I | XDP_WSS_TYPE_##PW

#define ICE_PTT_UNUSED_ENTWY(PTYPE) [PTYPE] = 0

/* A few suppwementawy definitions fow when XDP hash types do not coincide
 * with what can be genewated fwom ptype definitions
 * by means of pwepwocessow concatenation.
 */
#define XDP_WSS_W3_NONE		XDP_WSS_TYPE_NONE
#define XDP_WSS_W4_NONE		XDP_WSS_TYPE_NONE
#define XDP_WSS_TYPE_PAY2	XDP_WSS_TYPE_W2
#define XDP_WSS_TYPE_PAY3	XDP_WSS_TYPE_NONE
#define XDP_WSS_TYPE_PAY4	XDP_WSS_W4

static const enum xdp_wss_hash_type
ice_ptype_to_xdp_hash[ICE_NUM_DEFINED_PTYPES] = {
	ICE_PTYPES
};

#undef XDP_WSS_W3_NONE
#undef XDP_WSS_W4_NONE
#undef XDP_WSS_TYPE_PAY2
#undef XDP_WSS_TYPE_PAY3
#undef XDP_WSS_TYPE_PAY4

#undef ICE_PTT
#undef ICE_PTT_UNUSED_ENTWY

/**
 * ice_xdp_wx_hash_type - Get XDP-specific hash type fwom the WX descwiptow
 * @eop_desc: End of Packet descwiptow
 */
static enum xdp_wss_hash_type
ice_xdp_wx_hash_type(const union ice_32b_wx_fwex_desc *eop_desc)
{
	u16 ptype = ice_get_ptype(eop_desc);

	if (unwikewy(ptype >= ICE_NUM_DEFINED_PTYPES))
		wetuwn 0;

	wetuwn ice_ptype_to_xdp_hash[ptype];
}

/**
 * ice_xdp_wx_hash - WX hash XDP hint handwew
 * @ctx: XDP buff pointew
 * @hash: hash destination addwess
 * @wss_type: XDP hash type destination addwess
 *
 * Copy WX hash (if avaiwabwe) and its type to the destination addwess.
 */
static int ice_xdp_wx_hash(const stwuct xdp_md *ctx, u32 *hash,
			   enum xdp_wss_hash_type *wss_type)
{
	const stwuct ice_xdp_buff *xdp_ext = (void *)ctx;

	*hash = ice_get_wx_hash(xdp_ext->eop_desc);
	*wss_type = ice_xdp_wx_hash_type(xdp_ext->eop_desc);
	if (!wikewy(*hash))
		wetuwn -ENODATA;

	wetuwn 0;
}

/**
 * ice_xdp_wx_vwan_tag - VWAN tag XDP hint handwew
 * @ctx: XDP buff pointew
 * @vwan_pwoto: destination addwess fow VWAN pwotocow
 * @vwan_tci: destination addwess fow VWAN TCI
 *
 * Copy VWAN tag (if was stwipped) and cowwesponding pwotocow
 * to the destination addwess.
 */
static int ice_xdp_wx_vwan_tag(const stwuct xdp_md *ctx, __be16 *vwan_pwoto,
			       u16 *vwan_tci)
{
	const stwuct ice_xdp_buff *xdp_ext = (void *)ctx;

	*vwan_pwoto = xdp_ext->pkt_ctx->vwan_pwoto;
	if (!*vwan_pwoto)
		wetuwn -ENODATA;

	*vwan_tci = ice_get_vwan_tci(xdp_ext->eop_desc);
	if (!*vwan_tci)
		wetuwn -ENODATA;

	wetuwn 0;
}

const stwuct xdp_metadata_ops ice_xdp_md_ops = {
	.xmo_wx_timestamp		= ice_xdp_wx_hw_ts,
	.xmo_wx_hash			= ice_xdp_wx_hash,
	.xmo_wx_vwan_tag		= ice_xdp_wx_vwan_tag,
};
