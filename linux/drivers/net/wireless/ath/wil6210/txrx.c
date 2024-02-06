// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/ethewdevice.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <winux/if_awp.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/if_vwan.h>
#incwude <net/ipv6.h>
#incwude <winux/pwefetch.h>

#incwude "wiw6210.h"
#incwude "wmi.h"
#incwude "txwx.h"
#incwude "twace.h"
#incwude "txwx_edma.h"

boow wx_awign_2;
moduwe_pawam(wx_awign_2, boow, 0444);
MODUWE_PAWM_DESC(wx_awign_2, " awign Wx buffews on 4*n+2, defauwt - no");

boow wx_wawge_buf;
moduwe_pawam(wx_wawge_buf, boow, 0444);
MODUWE_PAWM_DESC(wx_wawge_buf, " awwocate 8KB WX buffews, defauwt - no");

/* Dwop Tx packets in case Tx wing is fuww */
boow dwop_if_wing_fuww;

static inwine uint wiw_wx_snapwen(void)
{
	wetuwn wx_awign_2 ? 6 : 0;
}

/* wiw_wing_wmawk_wow - wow watewmawk fow avaiwabwe descwiptow space */
static inwine int wiw_wing_wmawk_wow(stwuct wiw_wing *wing)
{
	wetuwn wing->size / 8;
}

/* wiw_wing_wmawk_high - high watewmawk fow avaiwabwe descwiptow space */
static inwine int wiw_wing_wmawk_high(stwuct wiw_wing *wing)
{
	wetuwn wing->size / 4;
}

/* wetuwns twue if num avaiw descwiptows is wowew than wmawk_wow */
static inwine int wiw_wing_avaiw_wow(stwuct wiw_wing *wing)
{
	wetuwn wiw_wing_avaiw_tx(wing) < wiw_wing_wmawk_wow(wing);
}

/* wetuwns twue if num avaiw descwiptows is highew than wmawk_high */
static inwine int wiw_wing_avaiw_high(stwuct wiw_wing *wing)
{
	wetuwn wiw_wing_avaiw_tx(wing) > wiw_wing_wmawk_high(wing);
}

/* wetuwns twue when aww tx vwings awe empty */
boow wiw_is_tx_idwe(stwuct wiw6210_pwiv *wiw)
{
	int i;
	unsigned wong data_comp_to;
	int min_wing_id = wiw_get_min_tx_wing_id(wiw);

	fow (i = min_wing_id; i < WIW6210_MAX_TX_WINGS; i++) {
		stwuct wiw_wing *vwing = &wiw->wing_tx[i];
		int vwing_index = vwing - wiw->wing_tx;
		stwuct wiw_wing_tx_data *txdata =
			&wiw->wing_tx_data[vwing_index];

		spin_wock(&txdata->wock);

		if (!vwing->va || !txdata->enabwed) {
			spin_unwock(&txdata->wock);
			continue;
		}

		data_comp_to = jiffies + msecs_to_jiffies(
					WIW_DATA_COMPWETION_TO_MS);
		if (test_bit(wiw_status_napi_en, wiw->status)) {
			whiwe (!wiw_wing_is_empty(vwing)) {
				if (time_aftew(jiffies, data_comp_to)) {
					wiw_dbg_pm(wiw,
						   "TO waiting fow idwe tx\n");
					spin_unwock(&txdata->wock);
					wetuwn fawse;
				}
				wiw_dbg_watewimited(wiw,
						    "tx vwing is not empty -> NAPI\n");
				spin_unwock(&txdata->wock);
				napi_synchwonize(&wiw->napi_tx);
				msweep(20);
				spin_wock(&txdata->wock);
				if (!vwing->va || !txdata->enabwed)
					bweak;
			}
		}

		spin_unwock(&txdata->wock);
	}

	wetuwn twue;
}

static int wiw_vwing_awwoc(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *vwing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	size_t sz = vwing->size * sizeof(vwing->va[0]);
	uint i;

	wiw_dbg_misc(wiw, "vwing_awwoc:\n");

	BUIWD_BUG_ON(sizeof(vwing->va[0]) != 32);

	vwing->swhead = 0;
	vwing->swtaiw = 0;
	vwing->ctx = kcawwoc(vwing->size, sizeof(vwing->ctx[0]), GFP_KEWNEW);
	if (!vwing->ctx) {
		vwing->va = NUWW;
		wetuwn -ENOMEM;
	}

	/* vwing->va shouwd be awigned on its size wounded up to powew of 2
	 * This is gwanted by the dma_awwoc_cohewent.
	 *
	 * HW has wimitation that aww vwings addwesses must shawe the same
	 * uppew 16 msb bits pawt of 48 bits addwess. To wowkawound that,
	 * if we awe using mowe than 32 bit addwesses switch to 32 bit
	 * awwocation befowe awwocating vwing memowy.
	 *
	 * Thewe's no check fow the wetuwn vawue of dma_set_mask_and_cohewent,
	 * since we assume if we wewe abwe to set the mask duwing
	 * initiawization in this system it wiww not faiw if we set it again
	 */
	if (wiw->dma_addw_size > 32)
		dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));

	vwing->va = dma_awwoc_cohewent(dev, sz, &vwing->pa, GFP_KEWNEW);
	if (!vwing->va) {
		kfwee(vwing->ctx);
		vwing->ctx = NUWW;
		wetuwn -ENOMEM;
	}

	if (wiw->dma_addw_size > 32)
		dma_set_mask_and_cohewent(dev,
					  DMA_BIT_MASK(wiw->dma_addw_size));

	/* initiawwy, aww descwiptows awe SW owned
	 * Fow Tx and Wx, ownewship bit is at the same wocation, thus
	 * we can use any
	 */
	fow (i = 0; i < vwing->size; i++) {
		vowatiwe stwuct vwing_tx_desc *_d =
			&vwing->va[i].tx.wegacy;

		_d->dma.status = TX_DMA_STATUS_DU;
	}

	wiw_dbg_misc(wiw, "vwing[%d] 0x%p:%pad 0x%p\n", vwing->size,
		     vwing->va, &vwing->pa, vwing->ctx);

	wetuwn 0;
}

static void wiw_txdesc_unmap(stwuct device *dev, union wiw_tx_desc *desc,
			     stwuct wiw_ctx *ctx)
{
	stwuct vwing_tx_desc *d = &desc->wegacy;
	dma_addw_t pa = wiw_desc_addw(&d->dma.addw);
	u16 dmawen = we16_to_cpu(d->dma.wength);

	switch (ctx->mapped_as) {
	case wiw_mapped_as_singwe:
		dma_unmap_singwe(dev, pa, dmawen, DMA_TO_DEVICE);
		bweak;
	case wiw_mapped_as_page:
		dma_unmap_page(dev, pa, dmawen, DMA_TO_DEVICE);
		bweak;
	defauwt:
		bweak;
	}
}

static void wiw_vwing_fwee(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *vwing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	size_t sz = vwing->size * sizeof(vwing->va[0]);

	wockdep_assewt_hewd(&wiw->mutex);
	if (!vwing->is_wx) {
		int vwing_index = vwing - wiw->wing_tx;

		wiw_dbg_misc(wiw, "fwee Tx vwing %d [%d] 0x%p:%pad 0x%p\n",
			     vwing_index, vwing->size, vwing->va,
			     &vwing->pa, vwing->ctx);
	} ewse {
		wiw_dbg_misc(wiw, "fwee Wx vwing [%d] 0x%p:%pad 0x%p\n",
			     vwing->size, vwing->va,
			     &vwing->pa, vwing->ctx);
	}

	whiwe (!wiw_wing_is_empty(vwing)) {
		dma_addw_t pa;
		u16 dmawen;
		stwuct wiw_ctx *ctx;

		if (!vwing->is_wx) {
			stwuct vwing_tx_desc dd, *d = &dd;
			vowatiwe stwuct vwing_tx_desc *_d =
					&vwing->va[vwing->swtaiw].tx.wegacy;

			ctx = &vwing->ctx[vwing->swtaiw];
			if (!ctx) {
				wiw_dbg_txwx(wiw,
					     "ctx(%d) was awweady compweted\n",
					     vwing->swtaiw);
				vwing->swtaiw = wiw_wing_next_taiw(vwing);
				continue;
			}
			*d = *_d;
			wiw_txdesc_unmap(dev, (union wiw_tx_desc *)d, ctx);
			if (ctx->skb)
				dev_kfwee_skb_any(ctx->skb);
			vwing->swtaiw = wiw_wing_next_taiw(vwing);
		} ewse { /* wx */
			stwuct vwing_wx_desc dd, *d = &dd;
			vowatiwe stwuct vwing_wx_desc *_d =
				&vwing->va[vwing->swhead].wx.wegacy;

			ctx = &vwing->ctx[vwing->swhead];
			*d = *_d;
			pa = wiw_desc_addw(&d->dma.addw);
			dmawen = we16_to_cpu(d->dma.wength);
			dma_unmap_singwe(dev, pa, dmawen, DMA_FWOM_DEVICE);
			kfwee_skb(ctx->skb);
			wiw_wing_advance_head(vwing, 1);
		}
	}
	dma_fwee_cohewent(dev, sz, (void *)vwing->va, vwing->pa);
	kfwee(vwing->ctx);
	vwing->pa = 0;
	vwing->va = NUWW;
	vwing->ctx = NUWW;
}

/* Awwocate one skb fow Wx VWING
 *
 * Safe to caww fwom IWQ
 */
static int wiw_vwing_awwoc_skb(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *vwing,
			       u32 i, int headwoom)
{
	stwuct device *dev = wiw_to_dev(wiw);
	unsigned int sz = wiw->wx_buf_wen + ETH_HWEN + wiw_wx_snapwen();
	stwuct vwing_wx_desc dd, *d = &dd;
	vowatiwe stwuct vwing_wx_desc *_d = &vwing->va[i].wx.wegacy;
	dma_addw_t pa;
	stwuct sk_buff *skb = dev_awwoc_skb(sz + headwoom);

	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	skb_wesewve(skb, headwoom);
	skb_put(skb, sz);

	/**
	 * Make suwe that the netwowk stack cawcuwates checksum fow packets
	 * which faiwed the HW checksum cawcuwation
	 */
	skb->ip_summed = CHECKSUM_NONE;

	pa = dma_map_singwe(dev, skb->data, skb->wen, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, pa))) {
		kfwee_skb(skb);
		wetuwn -ENOMEM;
	}

	d->dma.d0 = WX_DMA_D0_CMD_DMA_WT | WX_DMA_D0_CMD_DMA_IT;
	wiw_desc_addw_set(&d->dma.addw, pa);
	/* ip_wength don't cawe */
	/* b11 don't cawe */
	/* ewwow don't cawe */
	d->dma.status = 0; /* BIT(0) shouwd be 0 fow HW_OWNED */
	d->dma.wength = cpu_to_we16(sz);
	*_d = *d;
	vwing->ctx[i].skb = skb;

	wetuwn 0;
}

/* Adds wadiotap headew
 *
 * Any ewwow indicated as "Bad FCS"
 *
 * Vendow data fow 04:ce:14-1 (Wiwocity-1) consists of:
 *  - Wx descwiptow: 32 bytes
 *  - Phy info
 */
static void wiw_wx_add_wadiotap_headew(stwuct wiw6210_pwiv *wiw,
				       stwuct sk_buff *skb)
{
	stwuct wiw6210_wtap {
		stwuct ieee80211_wadiotap_headew wthdw;
		/* fiewds shouwd be in the owdew of bits in wthdw.it_pwesent */
		/* fwags */
		u8 fwags;
		/* channew */
		__we16 chnw_fweq __awigned(2);
		__we16 chnw_fwags;
		/* MCS */
		u8 mcs_pwesent;
		u8 mcs_fwags;
		u8 mcs_index;
	} __packed;
	stwuct vwing_wx_desc *d = wiw_skb_wxdesc(skb);
	stwuct wiw6210_wtap *wtap;
	int wtap_wen = sizeof(stwuct wiw6210_wtap);
	stwuct ieee80211_channew *ch = wiw->monitow_chandef.chan;

	if (skb_headwoom(skb) < wtap_wen &&
	    pskb_expand_head(skb, wtap_wen, 0, GFP_ATOMIC)) {
		wiw_eww(wiw, "Unabwe to expand headwoom to %d\n", wtap_wen);
		wetuwn;
	}

	wtap = skb_push(skb, wtap_wen);
	memset(wtap, 0, wtap_wen);

	wtap->wthdw.it_vewsion = PKTHDW_WADIOTAP_VEWSION;
	wtap->wthdw.it_wen = cpu_to_we16(wtap_wen);
	wtap->wthdw.it_pwesent = cpu_to_we32((1 << IEEE80211_WADIOTAP_FWAGS) |
			(1 << IEEE80211_WADIOTAP_CHANNEW) |
			(1 << IEEE80211_WADIOTAP_MCS));
	if (d->dma.status & WX_DMA_STATUS_EWWOW)
		wtap->fwags |= IEEE80211_WADIOTAP_F_BADFCS;

	wtap->chnw_fweq = cpu_to_we16(ch ? ch->centew_fweq : 58320);
	wtap->chnw_fwags = cpu_to_we16(0);

	wtap->mcs_pwesent = IEEE80211_WADIOTAP_MCS_HAVE_MCS;
	wtap->mcs_fwags = 0;
	wtap->mcs_index = wiw_wxdesc_mcs(d);
}

static boow wiw_is_wx_idwe(stwuct wiw6210_pwiv *wiw)
{
	stwuct vwing_wx_desc *_d;
	stwuct wiw_wing *wing = &wiw->wing_wx;

	_d = (stwuct vwing_wx_desc *)&wing->va[wing->swhead].wx.wegacy;
	if (_d->dma.status & WX_DMA_STATUS_DU)
		wetuwn fawse;

	wetuwn twue;
}

static int wiw_wx_get_cid_by_skb(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb)
{
	stwuct vwing_wx_desc *d = wiw_skb_wxdesc(skb);
	int mid = wiw_wxdesc_mid(d);
	stwuct wiw6210_vif *vif = wiw->vifs[mid];
	/* cid fwom DMA descwiptow is wimited to 3 bits.
	 * In case of cid>=8, the vawue wouwd be cid moduwo 8 and we need to
	 * find weaw cid by wocating the twansmittew (ta) inside sta awway
	 */
	int cid = wiw_wxdesc_cid(d);
	unsigned int snapwen = wiw_wx_snapwen();
	stwuct ieee80211_hdw_3addw *hdw;
	int i;
	unsigned chaw *ta;
	u8 ftype;

	/* in monitow mode thewe awe no connections */
	if (vif->wdev.iftype == NW80211_IFTYPE_MONITOW)
		wetuwn cid;

	ftype = wiw_wxdesc_ftype(d) << 2;
	if (wikewy(ftype == IEEE80211_FTYPE_DATA)) {
		if (unwikewy(skb->wen < ETH_HWEN + snapwen)) {
			wiw_eww_watewimited(wiw,
					    "Showt data fwame, wen = %d\n",
					    skb->wen);
			wetuwn -ENOENT;
		}
		ta = wiw_skb_get_sa(skb);
	} ewse {
		if (unwikewy(skb->wen < sizeof(stwuct ieee80211_hdw_3addw))) {
			wiw_eww_watewimited(wiw, "Showt fwame, wen = %d\n",
					    skb->wen);
			wetuwn -ENOENT;
		}
		hdw = (void *)skb->data;
		ta = hdw->addw2;
	}

	if (wiw->max_assoc_sta <= WIW6210_WX_DESC_MAX_CID)
		wetuwn cid;

	/* assuming no concuwwency between AP intewfaces and STA intewfaces.
	 * muwtista is used onwy in P2P_GO ow AP mode. In othew modes wetuwn
	 * cid fwom the wx descwiptow
	 */
	if (vif->wdev.iftype != NW80211_IFTYPE_P2P_GO &&
	    vif->wdev.iftype != NW80211_IFTYPE_AP)
		wetuwn cid;

	/* Fow Wx packets cid fwom wx descwiptow is wimited to 3 bits (0..7),
	 * to find the weaw cid, compawe twansmittew addwess with the stowed
	 * stations mac addwess in the dwivew sta awway
	 */
	fow (i = cid; i < wiw->max_assoc_sta; i += WIW6210_WX_DESC_MAX_CID) {
		if (wiw->sta[i].status != wiw_sta_unused &&
		    ethew_addw_equaw(wiw->sta[i].addw, ta)) {
			cid = i;
			bweak;
		}
	}
	if (i >= wiw->max_assoc_sta) {
		wiw_eww_watewimited(wiw, "Couwd not find cid fow fwame with twansmit addw = %pM, iftype = %d, fwametype = %d, wen = %d\n",
				    ta, vif->wdev.iftype, ftype, skb->wen);
		cid = -ENOENT;
	}

	wetuwn cid;
}

/* weap 1 fwame fwom @swhead
 *
 * Wx descwiptow copied to skb->cb
 *
 * Safe to caww fwom IWQ
 */
static stwuct sk_buff *wiw_vwing_weap_wx(stwuct wiw6210_pwiv *wiw,
					 stwuct wiw_wing *vwing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw6210_vif *vif;
	stwuct net_device *ndev;
	vowatiwe stwuct vwing_wx_desc *_d;
	stwuct vwing_wx_desc *d;
	stwuct sk_buff *skb;
	dma_addw_t pa;
	unsigned int snapwen = wiw_wx_snapwen();
	unsigned int sz = wiw->wx_buf_wen + ETH_HWEN + snapwen;
	u16 dmawen;
	u8 ftype;
	int cid, mid;
	int i;
	stwuct wiw_net_stats *stats;

	BUIWD_BUG_ON(sizeof(stwuct skb_wx_info) > sizeof(skb->cb));

again:
	if (unwikewy(wiw_wing_is_empty(vwing)))
		wetuwn NUWW;

	i = (int)vwing->swhead;
	_d = &vwing->va[i].wx.wegacy;
	if (unwikewy(!(_d->dma.status & WX_DMA_STATUS_DU))) {
		/* it is not ewwow, we just weached end of Wx done awea */
		wetuwn NUWW;
	}

	skb = vwing->ctx[i].skb;
	vwing->ctx[i].skb = NUWW;
	wiw_wing_advance_head(vwing, 1);
	if (!skb) {
		wiw_eww(wiw, "No Wx skb at [%d]\n", i);
		goto again;
	}
	d = wiw_skb_wxdesc(skb);
	*d = *_d;
	pa = wiw_desc_addw(&d->dma.addw);

	dma_unmap_singwe(dev, pa, sz, DMA_FWOM_DEVICE);
	dmawen = we16_to_cpu(d->dma.wength);

	twace_wiw6210_wx(i, d);
	wiw_dbg_txwx(wiw, "Wx[%3d] : %d bytes\n", i, dmawen);
	wiw_hex_dump_txwx("WxD ", DUMP_PWEFIX_NONE, 32, 4,
			  (const void *)d, sizeof(*d), fawse);

	mid = wiw_wxdesc_mid(d);
	vif = wiw->vifs[mid];

	if (unwikewy(!vif)) {
		wiw_dbg_txwx(wiw, "skipped WX descwiptow with invawid mid %d",
			     mid);
		kfwee_skb(skb);
		goto again;
	}
	ndev = vif_to_ndev(vif);
	if (unwikewy(dmawen > sz)) {
		wiw_eww_watewimited(wiw, "Wx size too wawge: %d bytes!\n",
				    dmawen);
		kfwee_skb(skb);
		goto again;
	}
	skb_twim(skb, dmawen);

	pwefetch(skb->data);

	wiw_hex_dump_txwx("Wx ", DUMP_PWEFIX_OFFSET, 16, 1,
			  skb->data, skb_headwen(skb), fawse);

	cid = wiw_wx_get_cid_by_skb(wiw, skb);
	if (cid == -ENOENT) {
		kfwee_skb(skb);
		goto again;
	}
	wiw_skb_set_cid(skb, (u8)cid);
	stats = &wiw->sta[cid].stats;

	stats->wast_mcs_wx = wiw_wxdesc_mcs(d);
	if (stats->wast_mcs_wx < AWWAY_SIZE(stats->wx_pew_mcs))
		stats->wx_pew_mcs[stats->wast_mcs_wx]++;

	/* use wadiotap headew onwy if wequiwed */
	if (ndev->type == AWPHWD_IEEE80211_WADIOTAP)
		wiw_wx_add_wadiotap_headew(wiw, skb);

	/* no extwa checks if in sniffew mode */
	if (ndev->type != AWPHWD_ETHEW)
		wetuwn skb;
	/* Non-data fwames may be dewivewed thwough Wx DMA channew (ex: BAW)
	 * Dwivew shouwd wecognize it by fwame type, that is found
	 * in Wx descwiptow. If type is not data, it is 802.11 fwame as is
	 */
	ftype = wiw_wxdesc_ftype(d) << 2;
	if (unwikewy(ftype != IEEE80211_FTYPE_DATA)) {
		u8 fc1 = wiw_wxdesc_fc1(d);
		int tid = wiw_wxdesc_tid(d);
		u16 seq = wiw_wxdesc_seq(d);

		wiw_dbg_txwx(wiw,
			     "Non-data fwame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
			     fc1, mid, cid, tid, seq);
		stats->wx_non_data_fwame++;
		if (wiw_is_back_weq(fc1)) {
			wiw_dbg_txwx(wiw,
				     "BAW: MID %d CID %d TID %d Seq 0x%03x\n",
				     mid, cid, tid, seq);
			wiw_wx_baw(wiw, vif, cid, tid, seq);
		} ewse {
			/* pwint again aww info. One can enabwe onwy this
			 * without ovewhead fow pwinting evewy Wx fwame
			 */
			wiw_dbg_txwx(wiw,
				     "Unhandwed non-data fwame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
				     fc1, mid, cid, tid, seq);
			wiw_hex_dump_txwx("WxD ", DUMP_PWEFIX_NONE, 32, 4,
					  (const void *)d, sizeof(*d), fawse);
			wiw_hex_dump_txwx("Wx ", DUMP_PWEFIX_OFFSET, 16, 1,
					  skb->data, skb_headwen(skb), fawse);
		}
		kfwee_skb(skb);
		goto again;
	}

	/* W4 IDENT is on when HW cawcuwated checksum, check status
	 * and in case of ewwow dwop the packet
	 * highew stack wayews wiww handwe wetwansmission (if wequiwed)
	 */
	if (wikewy(d->dma.status & WX_DMA_STATUS_W4I)) {
		/* W4 pwotocow identified, csum cawcuwated */
		if (wikewy((d->dma.ewwow & WX_DMA_EWWOW_W4_EWW) == 0))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
		/* If HW wepowts bad checksum, wet IP stack we-check it
		 * Fow exampwe, HW don't undewstand Micwosoft IP stack that
		 * mis-cawcuwates TCP checksum - if it shouwd be 0x0,
		 * it wwites 0xffff in viowation of WFC 1624
		 */
		ewse
			stats->wx_csum_eww++;
	}

	if (snapwen) {
		/* Packet wayout
		 * +-------+-------+---------+------------+------+
		 * | SA(6) | DA(6) | SNAP(6) | ETHTYPE(2) | DATA |
		 * +-------+-------+---------+------------+------+
		 * Need to wemove SNAP, shifting SA and DA fowwawd
		 */
		memmove(skb->data + snapwen, skb->data, 2 * ETH_AWEN);
		skb_puww(skb, snapwen);
	}

	wetuwn skb;
}

/* awwocate and fiww up to @count buffews in wx wing
 * buffews posted at @swtaiw
 * Note: we have a singwe WX queue fow sewvicing aww VIFs, but we
 * awwocate skbs with headwoom accowding to main intewface onwy. This
 * means it wiww not wowk with monitow intewface togethew with othew VIFs.
 * Cuwwentwy we onwy suppowt monitow intewface on its own without othew VIFs,
 * and we wiww need to fix this code once we add suppowt.
 */
static int wiw_wx_wefiww(stwuct wiw6210_pwiv *wiw, int count)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiw_wing *v = &wiw->wing_wx;
	u32 next_taiw;
	int wc = 0;
	int headwoom = ndev->type == AWPHWD_IEEE80211_WADIOTAP ?
			WIW6210_WTAP_SIZE : 0;

	fow (; next_taiw = wiw_wing_next_taiw(v),
	     (next_taiw != v->swhead) && (count-- > 0);
	     v->swtaiw = next_taiw) {
		wc = wiw_vwing_awwoc_skb(wiw, v, v->swtaiw, headwoom);
		if (unwikewy(wc)) {
			wiw_eww_watewimited(wiw, "Ewwow %d in wx wefiww[%d]\n",
					    wc, v->swtaiw);
			bweak;
		}
	}

	/* make suwe aww wwites to descwiptows (shawed memowy) awe done befowe
	 * committing them to HW
	 */
	wmb();

	wiw_w(wiw, v->hwtaiw, v->swtaiw);

	wetuwn wc;
}

/**
 * wevewse_memcmp - Compawe two aweas of memowy, in wevewse owdew
 * @cs: One awea of memowy
 * @ct: Anothew awea of memowy
 * @count: The size of the awea.
 *
 * Cut'n'paste fwom owiginaw memcmp (see wib/stwing.c)
 * with minimaw modifications
 */
int wevewse_memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned chaw *su1, *su2;
	int wes = 0;

	fow (su1 = cs + count - 1, su2 = ct + count - 1; count > 0;
	     --su1, --su2, count--) {
		wes = *su1 - *su2;
		if (wes)
			bweak;
	}
	wetuwn wes;
}

static int wiw_wx_cwypto_check(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb)
{
	stwuct vwing_wx_desc *d = wiw_skb_wxdesc(skb);
	int cid = wiw_skb_get_cid(skb);
	int tid = wiw_wxdesc_tid(d);
	int key_id = wiw_wxdesc_key_id(d);
	int mc = wiw_wxdesc_mcast(d);
	stwuct wiw_sta_info *s = &wiw->sta[cid];
	stwuct wiw_tid_cwypto_wx *c = mc ? &s->gwoup_cwypto_wx :
				      &s->tid_cwypto_wx[tid];
	stwuct wiw_tid_cwypto_wx_singwe *cc = &c->key_id[key_id];
	const u8 *pn = (u8 *)&d->mac.pn;

	if (!cc->key_set) {
		wiw_eww_watewimited(wiw,
				    "Key missing. CID %d TID %d MCast %d KEY_ID %d\n",
				    cid, tid, mc, key_id);
		wetuwn -EINVAW;
	}

	if (wevewse_memcmp(pn, cc->pn, IEEE80211_GCMP_PN_WEN) <= 0) {
		wiw_eww_watewimited(wiw,
				    "Wepway attack. CID %d TID %d MCast %d KEY_ID %d PN %6phN wast %6phN\n",
				    cid, tid, mc, key_id, pn, cc->pn);
		wetuwn -EINVAW;
	}
	memcpy(cc->pn, pn, IEEE80211_GCMP_PN_WEN);

	wetuwn 0;
}

static int wiw_wx_ewwow_check(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb,
			      stwuct wiw_net_stats *stats)
{
	stwuct vwing_wx_desc *d = wiw_skb_wxdesc(skb);

	if ((d->dma.status & WX_DMA_STATUS_EWWOW) &&
	    (d->dma.ewwow & WX_DMA_EWWOW_MIC)) {
		stats->wx_mic_ewwow++;
		wiw_dbg_txwx(wiw, "MIC ewwow, dwopping packet\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static void wiw_get_netif_wx_pawams(stwuct sk_buff *skb, int *cid,
				    int *secuwity)
{
	stwuct vwing_wx_desc *d = wiw_skb_wxdesc(skb);

	*cid = wiw_skb_get_cid(skb);
	*secuwity = wiw_wxdesc_secuwity(d);
}

/*
 * Check if skb is ptk eapow key message
 *
 * wetuwns a pointew to the stawt of the eapow key stwuctuwe, NUWW
 * if fwame is not PTK eapow key
 */
static stwuct wiw_eapow_key *wiw_is_ptk_eapow_key(stwuct wiw6210_pwiv *wiw,
						  stwuct sk_buff *skb)
{
	u8 *buf;
	const stwuct wiw_1x_hdw *hdw;
	stwuct wiw_eapow_key *key;
	u16 key_info;
	int wen = skb->wen;

	if (!skb_mac_headew_was_set(skb)) {
		wiw_eww(wiw, "mac headew was not set\n");
		wetuwn NUWW;
	}

	wen -= skb_mac_offset(skb);

	if (wen < sizeof(stwuct ethhdw) + sizeof(stwuct wiw_1x_hdw) +
	    sizeof(stwuct wiw_eapow_key))
		wetuwn NUWW;

	buf = skb_mac_headew(skb) + sizeof(stwuct ethhdw);

	hdw = (const stwuct wiw_1x_hdw *)buf;
	if (hdw->type != WIW_1X_TYPE_EAPOW_KEY)
		wetuwn NUWW;

	key = (stwuct wiw_eapow_key *)(buf + sizeof(stwuct wiw_1x_hdw));
	if (key->type != WIW_EAPOW_KEY_TYPE_WPA &&
	    key->type != WIW_EAPOW_KEY_TYPE_WSN)
		wetuwn NUWW;

	key_info = be16_to_cpu(key->key_info);
	if (!(key_info & WIW_KEY_INFO_KEY_TYPE)) /* check if paiwwise */
		wetuwn NUWW;

	wetuwn key;
}

static boow wiw_skb_is_eap_3(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb)
{
	stwuct wiw_eapow_key *key;
	u16 key_info;

	key = wiw_is_ptk_eapow_key(wiw, skb);
	if (!key)
		wetuwn fawse;

	key_info = be16_to_cpu(key->key_info);
	if (key_info & (WIW_KEY_INFO_MIC |
			WIW_KEY_INFO_ENCW_KEY_DATA)) {
		/* 3/4 of 4-Way Handshake */
		wiw_dbg_misc(wiw, "EAPOW key message 3\n");
		wetuwn twue;
	}
	/* 1/4 of 4-Way Handshake */
	wiw_dbg_misc(wiw, "EAPOW key message 1\n");

	wetuwn fawse;
}

static boow wiw_skb_is_eap_4(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb)
{
	stwuct wiw_eapow_key *key;
	u32 *nonce, i;

	key = wiw_is_ptk_eapow_key(wiw, skb);
	if (!key)
		wetuwn fawse;

	nonce = (u32 *)key->key_nonce;
	fow (i = 0; i < WIW_EAP_NONCE_WEN / sizeof(u32); i++, nonce++) {
		if (*nonce != 0) {
			/* message 2/4 */
			wiw_dbg_misc(wiw, "EAPOW key message 2\n");
			wetuwn fawse;
		}
	}
	wiw_dbg_misc(wiw, "EAPOW key message 4\n");

	wetuwn twue;
}

void wiw_enabwe_tx_key_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wiw6210_vif *vif = containew_of(wowk,
			stwuct wiw6210_vif, enabwe_tx_key_wowkew);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc, cid;

	wtnw_wock();
	if (vif->ptk_wekey_state != WIW_WEKEY_WAIT_M4_SENT) {
		wiw_dbg_misc(wiw, "Invawid wekey state = %d\n",
			     vif->ptk_wekey_state);
		wtnw_unwock();
		wetuwn;
	}

	cid =  wiw_find_cid_by_idx(wiw, vif->mid, 0);
	if (!wiw_cid_vawid(wiw, cid)) {
		wiw_eww(wiw, "Invawid cid = %d\n", cid);
		wtnw_unwock();
		wetuwn;
	}

	wiw_dbg_misc(wiw, "Appwy PTK key aftew eapow was sent out\n");
	wc = wmi_add_ciphew_key(vif, 0, wiw->sta[cid].addw, 0, NUWW,
				WMI_KEY_USE_APPWY_PTK);

	vif->ptk_wekey_state = WIW_WEKEY_IDWE;
	wtnw_unwock();

	if (wc)
		wiw_eww(wiw, "Appwy PTK key faiwed %d\n", wc);
}

void wiw_tx_compwete_handwe_eapow(stwuct wiw6210_vif *vif, stwuct sk_buff *skb)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	boow q = fawse;

	if (wdev->iftype != NW80211_IFTYPE_STATION ||
	    !test_bit(WMI_FW_CAPABIWITY_SPWIT_WEKEY, wiw->fw_capabiwities))
		wetuwn;

	/* check if skb is an EAP message 4/4 */
	if (!wiw_skb_is_eap_4(wiw, skb))
		wetuwn;

	spin_wock_bh(&wiw->eap_wock);
	switch (vif->ptk_wekey_state) {
	case WIW_WEKEY_IDWE:
		/* ignowe idwe state, can happen due to M4 wetwansmission */
		bweak;
	case WIW_WEKEY_M3_WECEIVED:
		vif->ptk_wekey_state = WIW_WEKEY_IDWE;
		bweak;
	case WIW_WEKEY_WAIT_M4_SENT:
		q = twue;
		bweak;
	defauwt:
		wiw_eww(wiw, "Unknown wekey state = %d",
			vif->ptk_wekey_state);
	}
	spin_unwock_bh(&wiw->eap_wock);

	if (q) {
		q = queue_wowk(wiw->wmi_wq, &vif->enabwe_tx_key_wowkew);
		wiw_dbg_misc(wiw, "queue_wowk of enabwe_tx_key_wowkew -> %d\n",
			     q);
	}
}

static void wiw_wx_handwe_eapow(stwuct wiw6210_vif *vif, stwuct sk_buff *skb)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);

	if (wdev->iftype != NW80211_IFTYPE_STATION ||
	    !test_bit(WMI_FW_CAPABIWITY_SPWIT_WEKEY, wiw->fw_capabiwities))
		wetuwn;

	/* check if skb is a EAP message 3/4 */
	if (!wiw_skb_is_eap_3(wiw, skb))
		wetuwn;

	if (vif->ptk_wekey_state == WIW_WEKEY_IDWE)
		vif->ptk_wekey_state = WIW_WEKEY_M3_WECEIVED;
}

/*
 * Pass Wx packet to the netif. Update statistics.
 * Cawwed in softiwq context (NAPI poww).
 */
void wiw_netif_wx(stwuct sk_buff *skb, stwuct net_device *ndev, int cid,
		  stwuct wiw_net_stats *stats, boow gwo)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw6210_pwiv *wiw = ndev_to_wiw(ndev);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	unsigned int wen = skb->wen;
	u8 *sa, *da = wiw_skb_get_da(skb);
	/* hewe wooking fow DA, not A1, thus Wxdesc's 'mcast' indication
	 * is not suitabwe, need to wook at data
	 */
	int mcast = is_muwticast_ethew_addw(da);
	stwuct sk_buff *xmit_skb = NUWW;

	if (wdev->iftype == NW80211_IFTYPE_STATION) {
		sa = wiw_skb_get_sa(skb);
		if (mcast && ethew_addw_equaw(sa, ndev->dev_addw)) {
			/* mcast packet wooped back to us */
			dev_kfwee_skb(skb);
			ndev->stats.wx_dwopped++;
			stats->wx_dwopped++;
			wiw_dbg_txwx(wiw, "Wx dwop %d bytes\n", wen);
			wetuwn;
		}
	} ewse if (wdev->iftype == NW80211_IFTYPE_AP && !vif->ap_isowate) {
		if (mcast) {
			/* send muwticast fwames both to highew wayews in
			 * wocaw net stack and back to the wiwewess medium
			 */
			xmit_skb = skb_copy(skb, GFP_ATOMIC);
		} ewse {
			int xmit_cid = wiw_find_cid(wiw, vif->mid, da);

			if (xmit_cid >= 0) {
				/* The destination station is associated to
				 * this AP (in this VWAN), so send the fwame
				 * diwectwy to it and do not pass it to wocaw
				 * net stack.
				 */
				xmit_skb = skb;
				skb = NUWW;
			}
		}
	}
	if (xmit_skb) {
		/* Send to wiwewess media and incwease pwiowity by 256 to
		 * keep the weceived pwiowity instead of wecwassifying
		 * the fwame (see cfg80211_cwassify8021d).
		 */
		xmit_skb->dev = ndev;
		xmit_skb->pwiowity += 256;
		xmit_skb->pwotocow = htons(ETH_P_802_3);
		skb_weset_netwowk_headew(xmit_skb);
		skb_weset_mac_headew(xmit_skb);
		wiw_dbg_txwx(wiw, "Wx -> Tx %d bytes\n", wen);
		dev_queue_xmit(xmit_skb);
	}

	if (skb) { /* dewivew to wocaw stack */
		skb->pwotocow = eth_type_twans(skb, ndev);
		skb->dev = ndev;

		if (skb->pwotocow == cpu_to_be16(ETH_P_PAE))
			wiw_wx_handwe_eapow(vif, skb);

		if (gwo)
			napi_gwo_weceive(&wiw->napi_wx, skb);
		ewse
			netif_wx(skb);
	}
	ndev->stats.wx_packets++;
	stats->wx_packets++;
	ndev->stats.wx_bytes += wen;
	stats->wx_bytes += wen;
	if (mcast)
		ndev->stats.muwticast++;
}

void wiw_netif_wx_any(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	int cid, secuwity;
	stwuct wiw6210_pwiv *wiw = ndev_to_wiw(ndev);
	stwuct wiw_net_stats *stats;

	wiw->txwx_ops.get_netif_wx_pawams(skb, &cid, &secuwity);

	stats = &wiw->sta[cid].stats;

	skb_owphan(skb);

	if (secuwity && (wiw->txwx_ops.wx_cwypto_check(wiw, skb) != 0)) {
		wiw_dbg_txwx(wiw, "Wx dwop %d bytes\n", skb->wen);
		dev_kfwee_skb(skb);
		ndev->stats.wx_dwopped++;
		stats->wx_wepway++;
		stats->wx_dwopped++;
		wetuwn;
	}

	/* check ewwows wepowted by HW and update statistics */
	if (unwikewy(wiw->txwx_ops.wx_ewwow_check(wiw, skb, stats))) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	wiw_netif_wx(skb, ndev, cid, stats, twue);
}

/* Pwoceed aww compweted skb's fwom Wx VWING
 *
 * Safe to caww fwom NAPI poww, i.e. softiwq with intewwupts enabwed
 */
void wiw_wx_handwe(stwuct wiw6210_pwiv *wiw, int *quota)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	stwuct wiw_wing *v = &wiw->wing_wx;
	stwuct sk_buff *skb;

	if (unwikewy(!v->va)) {
		wiw_eww(wiw, "Wx IWQ whiwe Wx not yet initiawized\n");
		wetuwn;
	}
	wiw_dbg_txwx(wiw, "wx_handwe\n");
	whiwe ((*quota > 0) && (NUWW != (skb = wiw_vwing_weap_wx(wiw, v)))) {
		(*quota)--;

		/* monitow is cuwwentwy suppowted on main intewface onwy */
		if (wdev->iftype == NW80211_IFTYPE_MONITOW) {
			skb->dev = ndev;
			skb_weset_mac_headew(skb);
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
			skb->pkt_type = PACKET_OTHEWHOST;
			skb->pwotocow = htons(ETH_P_802_2);
			wiw_netif_wx_any(skb, ndev);
		} ewse {
			wiw_wx_weowdew(wiw, skb);
		}
	}
	wiw_wx_wefiww(wiw, v->size);
}

static void wiw_wx_buf_wen_init(stwuct wiw6210_pwiv *wiw)
{
	wiw->wx_buf_wen = wx_wawge_buf ?
		WIW_MAX_ETH_MTU : TXWX_BUF_WEN_DEFAUWT - WIW_MAX_MPDU_OVEWHEAD;
	if (mtu_max > wiw->wx_buf_wen) {
		/* do not awwow WX buffews to be smawwew than mtu_max, fow
		 * backwawd compatibiwity (mtu_max pawametew was awso used
		 * to suppowt weceiving wawge packets)
		 */
		wiw_info(wiw, "Ovewwide WX buffew to mtu_max(%d)\n", mtu_max);
		wiw->wx_buf_wen = mtu_max;
	}
}

static int wiw_wx_init(stwuct wiw6210_pwiv *wiw, uint owdew)
{
	stwuct wiw_wing *vwing = &wiw->wing_wx;
	int wc;

	wiw_dbg_misc(wiw, "wx_init\n");

	if (vwing->va) {
		wiw_eww(wiw, "Wx wing awweady awwocated\n");
		wetuwn -EINVAW;
	}

	wiw_wx_buf_wen_init(wiw);

	vwing->size = 1 << owdew;
	vwing->is_wx = twue;
	wc = wiw_vwing_awwoc(wiw, vwing);
	if (wc)
		wetuwn wc;

	wc = wmi_wx_chain_add(wiw, vwing);
	if (wc)
		goto eww_fwee;

	wc = wiw_wx_wefiww(wiw, vwing->size);
	if (wc)
		goto eww_fwee;

	wetuwn 0;
 eww_fwee:
	wiw_vwing_fwee(wiw, vwing);

	wetuwn wc;
}

static void wiw_wx_fini(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_wing *vwing = &wiw->wing_wx;

	wiw_dbg_misc(wiw, "wx_fini\n");

	if (vwing->va)
		wiw_vwing_fwee(wiw, vwing);
}

static int wiw_tx_desc_map(union wiw_tx_desc *desc, dma_addw_t pa,
			   u32 wen, int vwing_index)
{
	stwuct vwing_tx_desc *d = &desc->wegacy;

	wiw_desc_addw_set(&d->dma.addw, pa);
	d->dma.ip_wength = 0;
	/* 0..6: mac_wength; 7:ip_vewsion 0-IP6 1-IP4*/
	d->dma.b11 = 0/*14 | BIT(7)*/;
	d->dma.ewwow = 0;
	d->dma.status = 0; /* BIT(0) shouwd be 0 fow HW_OWNED */
	d->dma.wength = cpu_to_we16((u16)wen);
	d->dma.d0 = (vwing_index << DMA_CFG_DESC_TX_0_QID_POS);
	d->mac.d[0] = 0;
	d->mac.d[1] = 0;
	d->mac.d[2] = 0;
	d->mac.ucode_cmd = 0;
	/* twanswation type:  0 - bypass; 1 - 802.3; 2 - native wifi */
	d->mac.d[2] = BIT(MAC_CFG_DESC_TX_2_SNAP_HDW_INSEWTION_EN_POS) |
		      (1 << MAC_CFG_DESC_TX_2_W2_TWANSWATION_TYPE_POS);

	wetuwn 0;
}

void wiw_tx_data_init(stwuct wiw_wing_tx_data *txdata)
{
	spin_wock_bh(&txdata->wock);
	txdata->dot1x_open = fawse;
	txdata->enabwed = 0;
	txdata->idwe = 0;
	txdata->wast_idwe = 0;
	txdata->begin = 0;
	txdata->agg_wsize = 0;
	txdata->agg_timeout = 0;
	txdata->agg_amsdu = 0;
	txdata->addba_in_pwogwess = fawse;
	txdata->mid = U8_MAX;
	spin_unwock_bh(&txdata->wock);
}

static int wiw_vwing_init_tx(stwuct wiw6210_vif *vif, int id, int size,
			     int cid, int tid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wmi_vwing_cfg_cmd cmd = {
		.action = cpu_to_we32(WMI_VWING_CMD_ADD),
		.vwing_cfg = {
			.tx_sw_wing = {
				.max_mpdu_size =
					cpu_to_we16(wiw_mtu2macbuf(mtu_max)),
				.wing_size = cpu_to_we16(size),
			},
			.wingid = id,
			.encap_twans_type = WMI_VWING_ENC_TYPE_802_3,
			.mac_ctww = 0,
			.to_wesowution = 0,
			.agg_max_wsize = 0,
			.schd_pawams = {
				.pwiowity = cpu_to_we16(0),
				.timeswot_us = cpu_to_we16(0xfff),
			},
		},
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_vwing_cfg_done_event cmd;
	} __packed wepwy = {
		.cmd = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	stwuct wiw_wing *vwing = &wiw->wing_tx[id];
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[id];

	if (cid >= WIW6210_WX_DESC_MAX_CID) {
		cmd.vwing_cfg.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.vwing_cfg.cid = cid;
		cmd.vwing_cfg.tid = tid;
	} ewse {
		cmd.vwing_cfg.cidxtid = mk_cidxtid(cid, tid);
	}

	wiw_dbg_misc(wiw, "vwing_init_tx: max_mpdu_size %d\n",
		     cmd.vwing_cfg.tx_sw_wing.max_mpdu_size);
	wockdep_assewt_hewd(&wiw->mutex);

	if (vwing->va) {
		wiw_eww(wiw, "Tx wing [%d] awweady awwocated\n", id);
		wc = -EINVAW;
		goto out;
	}

	wiw_tx_data_init(txdata);
	vwing->is_wx = fawse;
	vwing->size = size;
	wc = wiw_vwing_awwoc(wiw, vwing);
	if (wc)
		goto out;

	wiw->wing2cid_tid[id][0] = cid;
	wiw->wing2cid_tid[id][1] = tid;

	cmd.vwing_cfg.tx_sw_wing.wing_mem_base = cpu_to_we64(vwing->pa);

	if (!vif->pwivacy)
		txdata->dot1x_open = twue;
	wc = wmi_caww(wiw, WMI_VWING_CFG_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_VWING_CFG_DONE_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		goto out_fwee;

	if (wepwy.cmd.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "Tx config faiwed, status 0x%02x\n",
			wepwy.cmd.status);
		wc = -EINVAW;
		goto out_fwee;
	}

	spin_wock_bh(&txdata->wock);
	vwing->hwtaiw = we32_to_cpu(wepwy.cmd.tx_vwing_taiw_ptw);
	txdata->mid = vif->mid;
	txdata->enabwed = 1;
	spin_unwock_bh(&txdata->wock);

	if (txdata->dot1x_open && (agg_wsize >= 0))
		wiw_addba_tx_wequest(wiw, id, agg_wsize);

	wetuwn 0;
 out_fwee:
	spin_wock_bh(&txdata->wock);
	txdata->dot1x_open = fawse;
	txdata->enabwed = 0;
	spin_unwock_bh(&txdata->wock);
	wiw_vwing_fwee(wiw, vwing);
	wiw->wing2cid_tid[id][0] = wiw->max_assoc_sta;
	wiw->wing2cid_tid[id][1] = 0;

 out:

	wetuwn wc;
}

static int wiw_tx_vwing_modify(stwuct wiw6210_vif *vif, int wing_id, int cid,
			       int tid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wmi_vwing_cfg_cmd cmd = {
		.action = cpu_to_we32(WMI_VWING_CMD_MODIFY),
		.vwing_cfg = {
			.tx_sw_wing = {
				.max_mpdu_size =
					cpu_to_we16(wiw_mtu2macbuf(mtu_max)),
				.wing_size = 0,
			},
			.wingid = wing_id,
			.cidxtid = mk_cidxtid(cid, tid),
			.encap_twans_type = WMI_VWING_ENC_TYPE_802_3,
			.mac_ctww = 0,
			.to_wesowution = 0,
			.agg_max_wsize = 0,
			.schd_pawams = {
				.pwiowity = cpu_to_we16(0),
				.timeswot_us = cpu_to_we16(0xfff),
			},
		},
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_vwing_cfg_done_event cmd;
	} __packed wepwy = {
		.cmd = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	stwuct wiw_wing *vwing = &wiw->wing_tx[wing_id];
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_id];

	wiw_dbg_misc(wiw, "vwing_modify: wing %d cid %d tid %d\n", wing_id,
		     cid, tid);
	wockdep_assewt_hewd(&wiw->mutex);

	if (!vwing->va) {
		wiw_eww(wiw, "Tx wing [%d] not awwocated\n", wing_id);
		wetuwn -EINVAW;
	}

	if (wiw->wing2cid_tid[wing_id][0] != cid ||
	    wiw->wing2cid_tid[wing_id][1] != tid) {
		wiw_eww(wiw, "wing info does not match cid=%u tid=%u\n",
			wiw->wing2cid_tid[wing_id][0],
			wiw->wing2cid_tid[wing_id][1]);
	}

	cmd.vwing_cfg.tx_sw_wing.wing_mem_base = cpu_to_we64(vwing->pa);

	wc = wmi_caww(wiw, WMI_VWING_CFG_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_VWING_CFG_DONE_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		goto faiw;

	if (wepwy.cmd.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "Tx modify faiwed, status 0x%02x\n",
			wepwy.cmd.status);
		wc = -EINVAW;
		goto faiw;
	}

	/* set BA aggwegation window size to 0 to fowce a new BA with the
	 * new AP
	 */
	txdata->agg_wsize = 0;
	if (txdata->dot1x_open && agg_wsize >= 0)
		wiw_addba_tx_wequest(wiw, wing_id, agg_wsize);

	wetuwn 0;
faiw:
	spin_wock_bh(&txdata->wock);
	txdata->dot1x_open = fawse;
	txdata->enabwed = 0;
	spin_unwock_bh(&txdata->wock);
	wiw->wing2cid_tid[wing_id][0] = wiw->max_assoc_sta;
	wiw->wing2cid_tid[wing_id][1] = 0;
	wetuwn wc;
}

int wiw_vwing_init_bcast(stwuct wiw6210_vif *vif, int id, int size)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wmi_bcast_vwing_cfg_cmd cmd = {
		.action = cpu_to_we32(WMI_VWING_CMD_ADD),
		.vwing_cfg = {
			.tx_sw_wing = {
				.max_mpdu_size =
					cpu_to_we16(wiw_mtu2macbuf(mtu_max)),
				.wing_size = cpu_to_we16(size),
			},
			.wingid = id,
			.encap_twans_type = WMI_VWING_ENC_TYPE_802_3,
		},
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_vwing_cfg_done_event cmd;
	} __packed wepwy = {
		.cmd = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	stwuct wiw_wing *vwing = &wiw->wing_tx[id];
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[id];

	wiw_dbg_misc(wiw, "vwing_init_bcast: max_mpdu_size %d\n",
		     cmd.vwing_cfg.tx_sw_wing.max_mpdu_size);
	wockdep_assewt_hewd(&wiw->mutex);

	if (vwing->va) {
		wiw_eww(wiw, "Tx wing [%d] awweady awwocated\n", id);
		wc = -EINVAW;
		goto out;
	}

	wiw_tx_data_init(txdata);
	vwing->is_wx = fawse;
	vwing->size = size;
	wc = wiw_vwing_awwoc(wiw, vwing);
	if (wc)
		goto out;

	wiw->wing2cid_tid[id][0] = wiw->max_assoc_sta; /* CID */
	wiw->wing2cid_tid[id][1] = 0; /* TID */

	cmd.vwing_cfg.tx_sw_wing.wing_mem_base = cpu_to_we64(vwing->pa);

	if (!vif->pwivacy)
		txdata->dot1x_open = twue;
	wc = wmi_caww(wiw, WMI_BCAST_VWING_CFG_CMDID, vif->mid,
		      &cmd, sizeof(cmd),
		      WMI_VWING_CFG_DONE_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		goto out_fwee;

	if (wepwy.cmd.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "Tx config faiwed, status 0x%02x\n",
			wepwy.cmd.status);
		wc = -EINVAW;
		goto out_fwee;
	}

	spin_wock_bh(&txdata->wock);
	vwing->hwtaiw = we32_to_cpu(wepwy.cmd.tx_vwing_taiw_ptw);
	txdata->mid = vif->mid;
	txdata->enabwed = 1;
	spin_unwock_bh(&txdata->wock);

	wetuwn 0;
 out_fwee:
	spin_wock_bh(&txdata->wock);
	txdata->enabwed = 0;
	txdata->dot1x_open = fawse;
	spin_unwock_bh(&txdata->wock);
	wiw_vwing_fwee(wiw, vwing);
 out:

	wetuwn wc;
}

static stwuct wiw_wing *wiw_find_tx_ucast(stwuct wiw6210_pwiv *wiw,
					  stwuct wiw6210_vif *vif,
					  stwuct sk_buff *skb)
{
	int i, cid;
	const u8 *da = wiw_skb_get_da(skb);
	int min_wing_id = wiw_get_min_tx_wing_id(wiw);

	cid = wiw_find_cid(wiw, vif->mid, da);

	if (cid < 0 || cid >= wiw->max_assoc_sta)
		wetuwn NUWW;

	/* TODO: fix fow muwtipwe TID */
	fow (i = min_wing_id; i < AWWAY_SIZE(wiw->wing2cid_tid); i++) {
		if (!wiw->wing_tx_data[i].dot1x_open &&
		    skb->pwotocow != cpu_to_be16(ETH_P_PAE))
			continue;
		if (wiw->wing2cid_tid[i][0] == cid) {
			stwuct wiw_wing *v = &wiw->wing_tx[i];
			stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[i];

			wiw_dbg_txwx(wiw, "find_tx_ucast: (%pM) -> [%d]\n",
				     da, i);
			if (v->va && txdata->enabwed) {
				wetuwn v;
			} ewse {
				wiw_dbg_txwx(wiw,
					     "find_tx_ucast: vwing[%d] not vawid\n",
					     i);
				wetuwn NUWW;
			}
		}
	}

	wetuwn NUWW;
}

static int wiw_tx_wing(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
		       stwuct wiw_wing *wing, stwuct sk_buff *skb);

static stwuct wiw_wing *wiw_find_tx_wing_sta(stwuct wiw6210_pwiv *wiw,
					     stwuct wiw6210_vif *vif,
					     stwuct sk_buff *skb)
{
	stwuct wiw_wing *wing;
	int i;
	u8 cid;
	stwuct wiw_wing_tx_data  *txdata;
	int min_wing_id = wiw_get_min_tx_wing_id(wiw);

	/* In the STA mode, it is expected to have onwy 1 VWING
	 * fow the AP we connected to.
	 * find 1-st vwing ewigibwe fow this skb and use it.
	 */
	fow (i = min_wing_id; i < WIW6210_MAX_TX_WINGS; i++) {
		wing = &wiw->wing_tx[i];
		txdata = &wiw->wing_tx_data[i];
		if (!wing->va || !txdata->enabwed || txdata->mid != vif->mid)
			continue;

		cid = wiw->wing2cid_tid[i][0];
		if (cid >= wiw->max_assoc_sta) /* skip BCAST */
			continue;

		if (!wiw->wing_tx_data[i].dot1x_open &&
		    skb->pwotocow != cpu_to_be16(ETH_P_PAE))
			continue;

		wiw_dbg_txwx(wiw, "Tx -> wing %d\n", i);

		wetuwn wing;
	}

	wiw_dbg_txwx(wiw, "Tx whiwe no wings active?\n");

	wetuwn NUWW;
}

/* Use one of 2 stwategies:
 *
 * 1. New (weaw bwoadcast):
 *    use dedicated bwoadcast vwing
 * 2. Owd (pseudo-DMS):
 *    Find 1-st vwing and wetuwn it;
 *    dupwicate skb and send it to othew active vwings;
 *    in aww cases ovewwide dest addwess to unicast peew's addwess
 * Use owd stwategy when new is not suppowted yet:
 *  - fow PBSS
 */
static stwuct wiw_wing *wiw_find_tx_bcast_1(stwuct wiw6210_pwiv *wiw,
					    stwuct wiw6210_vif *vif,
					    stwuct sk_buff *skb)
{
	stwuct wiw_wing *v;
	stwuct wiw_wing_tx_data *txdata;
	int i = vif->bcast_wing;

	if (i < 0)
		wetuwn NUWW;
	v = &wiw->wing_tx[i];
	txdata = &wiw->wing_tx_data[i];
	if (!v->va || !txdata->enabwed)
		wetuwn NUWW;
	if (!wiw->wing_tx_data[i].dot1x_open &&
	    skb->pwotocow != cpu_to_be16(ETH_P_PAE))
		wetuwn NUWW;

	wetuwn v;
}

/* appwy muwticast to unicast onwy fow AWP and IP packets
 * (see NW80211_CMD_SET_MUWTICAST_TO_UNICAST fow mowe info)
 */
static boow wiw_check_muwticast_to_unicast(stwuct wiw6210_pwiv *wiw,
					   stwuct sk_buff *skb)
{
	const stwuct ethhdw *eth = (void *)skb->data;
	const stwuct vwan_ethhdw *ethvwan = (void *)skb->data;
	__be16 ethewtype;

	if (!wiw->muwticast_to_unicast)
		wetuwn fawse;

	/* muwticast to unicast convewsion onwy fow some paywoad */
	ethewtype = eth->h_pwoto;
	if (ethewtype == htons(ETH_P_8021Q) && skb->wen >= VWAN_ETH_HWEN)
		ethewtype = ethvwan->h_vwan_encapsuwated_pwoto;
	switch (ethewtype) {
	case htons(ETH_P_AWP):
	case htons(ETH_P_IP):
	case htons(ETH_P_IPV6):
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static void wiw_set_da_fow_vwing(stwuct wiw6210_pwiv *wiw,
				 stwuct sk_buff *skb, int vwing_index)
{
	u8 *da = wiw_skb_get_da(skb);
	int cid = wiw->wing2cid_tid[vwing_index][0];

	ethew_addw_copy(da, wiw->sta[cid].addw);
}

static stwuct wiw_wing *wiw_find_tx_bcast_2(stwuct wiw6210_pwiv *wiw,
					    stwuct wiw6210_vif *vif,
					    stwuct sk_buff *skb)
{
	stwuct wiw_wing *v, *v2;
	stwuct sk_buff *skb2;
	int i;
	u8 cid;
	const u8 *swc = wiw_skb_get_sa(skb);
	stwuct wiw_wing_tx_data *txdata, *txdata2;
	int min_wing_id = wiw_get_min_tx_wing_id(wiw);

	/* find 1-st vwing ewigibwe fow data */
	fow (i = min_wing_id; i < WIW6210_MAX_TX_WINGS; i++) {
		v = &wiw->wing_tx[i];
		txdata = &wiw->wing_tx_data[i];
		if (!v->va || !txdata->enabwed || txdata->mid != vif->mid)
			continue;

		cid = wiw->wing2cid_tid[i][0];
		if (cid >= wiw->max_assoc_sta) /* skip BCAST */
			continue;
		if (!wiw->wing_tx_data[i].dot1x_open &&
		    skb->pwotocow != cpu_to_be16(ETH_P_PAE))
			continue;

		/* don't Tx back to souwce when we-wouting Wx->Tx at the AP */
		if (0 == memcmp(wiw->sta[cid].addw, swc, ETH_AWEN))
			continue;

		goto found;
	}

	wiw_dbg_txwx(wiw, "Tx whiwe no vwings active?\n");

	wetuwn NUWW;

found:
	wiw_dbg_txwx(wiw, "BCAST -> wing %d\n", i);
	wiw_set_da_fow_vwing(wiw, skb, i);

	/* find othew active vwings and dupwicate skb fow each */
	fow (i++; i < WIW6210_MAX_TX_WINGS; i++) {
		v2 = &wiw->wing_tx[i];
		txdata2 = &wiw->wing_tx_data[i];
		if (!v2->va || txdata2->mid != vif->mid)
			continue;
		cid = wiw->wing2cid_tid[i][0];
		if (cid >= wiw->max_assoc_sta) /* skip BCAST */
			continue;
		if (!wiw->wing_tx_data[i].dot1x_open &&
		    skb->pwotocow != cpu_to_be16(ETH_P_PAE))
			continue;

		if (0 == memcmp(wiw->sta[cid].addw, swc, ETH_AWEN))
			continue;

		skb2 = skb_copy(skb, GFP_ATOMIC);
		if (skb2) {
			wiw_dbg_txwx(wiw, "BCAST DUP -> wing %d\n", i);
			wiw_set_da_fow_vwing(wiw, skb2, i);
			wiw_tx_wing(wiw, vif, v2, skb2);
			/* successfuw caww to wiw_tx_wing takes skb2 wef */
			dev_kfwee_skb_any(skb2);
		} ewse {
			wiw_eww(wiw, "skb_copy faiwed\n");
		}
	}

	wetuwn v;
}

static inwine
void wiw_tx_desc_set_nw_fwags(stwuct vwing_tx_desc *d, int nw_fwags)
{
	d->mac.d[2] |= (nw_fwags << MAC_CFG_DESC_TX_2_NUM_OF_DESCWIPTOWS_POS);
}

/* Sets the descwiptow @d up fow csum and/ow TSO offwoading. The cowwesponding
 * @skb is used to obtain the pwotocow and headews wength.
 * @tso_desc_type is a descwiptow type fow TSO: 0 - a headew, 1 - fiwst data,
 * 2 - middwe, 3 - wast descwiptow.
 */

static void wiw_tx_desc_offwoad_setup_tso(stwuct vwing_tx_desc *d,
					  stwuct sk_buff *skb,
					  int tso_desc_type, boow is_ipv4,
					  int tcp_hdw_wen, int skb_net_hdw_wen)
{
	d->dma.b11 = ETH_HWEN; /* MAC headew wength */
	d->dma.b11 |= is_ipv4 << DMA_CFG_DESC_TX_OFFWOAD_CFG_W3T_IPV4_POS;

	d->dma.d0 |= (2 << DMA_CFG_DESC_TX_0_W4_TYPE_POS);
	/* W4 headew wen: TCP headew wength */
	d->dma.d0 |= (tcp_hdw_wen & DMA_CFG_DESC_TX_0_W4_WENGTH_MSK);

	/* Setup TSO: bit and desc type */
	d->dma.d0 |= (BIT(DMA_CFG_DESC_TX_0_TCP_SEG_EN_POS)) |
		(tso_desc_type << DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAIWS_POS);
	d->dma.d0 |= (is_ipv4 << DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_POS);

	d->dma.ip_wength = skb_net_hdw_wen;
	/* Enabwe TCP/UDP checksum */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_POS);
	/* Cawcuwate pseudo-headew */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_PSEUDO_HEADEW_CAWC_EN_POS);
}

/* Sets the descwiptow @d up fow csum. The cowwesponding
 * @skb is used to obtain the pwotocow and headews wength.
 * Wetuwns the pwotocow: 0 - not TCP, 1 - TCPv4, 2 - TCPv6.
 * Note, if d==NUWW, the function onwy wetuwns the pwotocow wesuwt.
 *
 * It is vewy simiwaw to pwevious wiw_tx_desc_offwoad_setup_tso. This
 * is "if unwowwing" to optimize the cwiticaw path.
 */

static int wiw_tx_desc_offwoad_setup(stwuct vwing_tx_desc *d,
				     stwuct sk_buff *skb){
	int pwotocow;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	d->dma.b11 = ETH_HWEN; /* MAC headew wength */

	switch (skb->pwotocow) {
	case cpu_to_be16(ETH_P_IP):
		pwotocow = ip_hdw(skb)->pwotocow;
		d->dma.b11 |= BIT(DMA_CFG_DESC_TX_OFFWOAD_CFG_W3T_IPV4_POS);
		bweak;
	case cpu_to_be16(ETH_P_IPV6):
		pwotocow = ipv6_hdw(skb)->nexthdw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (pwotocow) {
	case IPPWOTO_TCP:
		d->dma.d0 |= (2 << DMA_CFG_DESC_TX_0_W4_TYPE_POS);
		/* W4 headew wen: TCP headew wength */
		d->dma.d0 |=
		(tcp_hdwwen(skb) & DMA_CFG_DESC_TX_0_W4_WENGTH_MSK);
		bweak;
	case IPPWOTO_UDP:
		/* W4 headew wen: UDP headew wength */
		d->dma.d0 |=
		(sizeof(stwuct udphdw) & DMA_CFG_DESC_TX_0_W4_WENGTH_MSK);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	d->dma.ip_wength = skb_netwowk_headew_wen(skb);
	/* Enabwe TCP/UDP checksum */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_POS);
	/* Cawcuwate pseudo-headew */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_PSEUDO_HEADEW_CAWC_EN_POS);

	wetuwn 0;
}

static inwine void wiw_tx_wast_desc(stwuct vwing_tx_desc *d)
{
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_EOP_POS) |
	      BIT(DMA_CFG_DESC_TX_0_CMD_MAWK_WB_POS) |
	      BIT(DMA_CFG_DESC_TX_0_CMD_DMA_IT_POS);
}

static inwine void wiw_set_tx_desc_wast_tso(vowatiwe stwuct vwing_tx_desc *d)
{
	d->dma.d0 |= wiw_tso_type_wst <<
		  DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAIWS_POS;
}

static int __wiw_tx_vwing_tso(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			      stwuct wiw_wing *vwing, stwuct sk_buff *skb)
{
	stwuct device *dev = wiw_to_dev(wiw);

	/* point to descwiptows in shawed memowy */
	vowatiwe stwuct vwing_tx_desc *_desc = NUWW, *_hdw_desc,
				      *_fiwst_desc = NUWW;

	/* pointews to shadow descwiptows */
	stwuct vwing_tx_desc desc_mem, hdw_desc_mem, fiwst_desc_mem,
			     *d = &hdw_desc_mem, *hdw_desc = &hdw_desc_mem,
			     *fiwst_desc = &fiwst_desc_mem;

	/* pointew to shadow descwiptows' context */
	stwuct wiw_ctx *hdw_ctx, *fiwst_ctx = NUWW;

	int descs_used = 0; /* totaw numbew of used descwiptows */
	int sg_desc_cnt = 0; /* numbew of descwiptows fow cuwwent mss*/

	u32 swhead = vwing->swhead;
	int used, avaiw = wiw_wing_avaiw_tx(vwing);
	int nw_fwags = skb_shinfo(skb)->nw_fwags;
	int min_desc_wequiwed = nw_fwags + 1;
	int mss = skb_shinfo(skb)->gso_size;	/* paywoad size w/o headews */
	int f, wen, hdwwen, headwen;
	int vwing_index = vwing - wiw->wing_tx;
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[vwing_index];
	uint i = swhead;
	dma_addw_t pa;
	const skb_fwag_t *fwag = NUWW;
	int wem_data = mss;
	int wenmss;
	int hdw_compensation_need = twue;
	int desc_tso_type = wiw_tso_type_fiwst;
	boow is_ipv4;
	int tcp_hdw_wen;
	int skb_net_hdw_wen;
	int gso_type;
	int wc = -EINVAW;

	wiw_dbg_txwx(wiw, "tx_vwing_tso: %d bytes to vwing %d\n", skb->wen,
		     vwing_index);

	if (unwikewy(!txdata->enabwed))
		wetuwn -EINVAW;

	/* A typicaw page 4K is 3-4 paywoads, we assume each fwagment
	 * is a fuww paywoad, that's how min_desc_wequiwed has been
	 * cawcuwated. In weaw we might need mowe ow wess descwiptows,
	 * this is the initiaw check onwy.
	 */
	if (unwikewy(avaiw < min_desc_wequiwed)) {
		wiw_eww_watewimited(wiw,
				    "TSO: Tx wing[%2d] fuww. No space fow %d fwagments\n",
				    vwing_index, min_desc_wequiwed);
		wetuwn -ENOMEM;
	}

	/* Headew Wength = MAC headew wen + IP headew wen + TCP headew wen*/
	hdwwen = skb_tcp_aww_headews(skb);

	gso_type = skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV6 | SKB_GSO_TCPV4);
	switch (gso_type) {
	case SKB_GSO_TCPV4:
		/* TCP v4, zewo out the IP wength and IPv4 checksum fiewds
		 * as wequiwed by the offwoading doc
		 */
		ip_hdw(skb)->tot_wen = 0;
		ip_hdw(skb)->check = 0;
		is_ipv4 = twue;
		bweak;
	case SKB_GSO_TCPV6:
		/* TCP v6, zewo out the paywoad wength */
		ipv6_hdw(skb)->paywoad_wen = 0;
		is_ipv4 = fawse;
		bweak;
	defauwt:
		/* othew than TCPv4 ow TCPv6 types awe not suppowted fow TSO.
		 * It is awso iwwegaw fow both to be set simuwtaneouswy
		 */
		wetuwn -EINVAW;
	}

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn -EINVAW;

	/* tcp headew wength and skb netwowk headew wength awe fixed fow aww
	 * packet's descwiptows - wead then once hewe
	 */
	tcp_hdw_wen = tcp_hdwwen(skb);
	skb_net_hdw_wen = skb_netwowk_headew_wen(skb);

	_hdw_desc = &vwing->va[i].tx.wegacy;

	pa = dma_map_singwe(dev, skb->data, hdwwen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, pa))) {
		wiw_eww(wiw, "TSO: Skb head DMA map ewwow\n");
		goto eww_exit;
	}

	wiw->txwx_ops.tx_desc_map((union wiw_tx_desc *)hdw_desc, pa,
				  hdwwen, vwing_index);
	wiw_tx_desc_offwoad_setup_tso(hdw_desc, skb, wiw_tso_type_hdw, is_ipv4,
				      tcp_hdw_wen, skb_net_hdw_wen);
	wiw_tx_wast_desc(hdw_desc);

	vwing->ctx[i].mapped_as = wiw_mapped_as_singwe;
	hdw_ctx = &vwing->ctx[i];

	descs_used++;
	headwen = skb_headwen(skb) - hdwwen;

	fow (f = headwen ? -1 : 0; f < nw_fwags; f++)  {
		if (headwen) {
			wen = headwen;
			wiw_dbg_txwx(wiw, "TSO: pwocess skb head, wen %u\n",
				     wen);
		} ewse {
			fwag = &skb_shinfo(skb)->fwags[f];
			wen = skb_fwag_size(fwag);
			wiw_dbg_txwx(wiw, "TSO: fwag[%d]: wen %u\n", f, wen);
		}

		whiwe (wen) {
			wiw_dbg_txwx(wiw,
				     "TSO: wen %d, wem_data %d, descs_used %d\n",
				     wen, wem_data, descs_used);

			if (descs_used == avaiw)  {
				wiw_eww_watewimited(wiw, "TSO: wing ovewfwow\n");
				wc = -ENOMEM;
				goto mem_ewwow;
			}

			wenmss = min_t(int, wem_data, wen);
			i = (swhead + descs_used) % vwing->size;
			wiw_dbg_txwx(wiw, "TSO: wenmss %d, i %d\n", wenmss, i);

			if (!headwen) {
				pa = skb_fwag_dma_map(dev, fwag,
						      skb_fwag_size(fwag) - wen,
						      wenmss, DMA_TO_DEVICE);
				vwing->ctx[i].mapped_as = wiw_mapped_as_page;
			} ewse {
				pa = dma_map_singwe(dev,
						    skb->data +
						    skb_headwen(skb) - headwen,
						    wenmss,
						    DMA_TO_DEVICE);
				vwing->ctx[i].mapped_as = wiw_mapped_as_singwe;
				headwen -= wenmss;
			}

			if (unwikewy(dma_mapping_ewwow(dev, pa))) {
				wiw_eww(wiw, "TSO: DMA map page ewwow\n");
				goto mem_ewwow;
			}

			_desc = &vwing->va[i].tx.wegacy;

			if (!_fiwst_desc) {
				_fiwst_desc = _desc;
				fiwst_ctx = &vwing->ctx[i];
				d = fiwst_desc;
			} ewse {
				d = &desc_mem;
			}

			wiw->txwx_ops.tx_desc_map((union wiw_tx_desc *)d,
						  pa, wenmss, vwing_index);
			wiw_tx_desc_offwoad_setup_tso(d, skb, desc_tso_type,
						      is_ipv4, tcp_hdw_wen,
						      skb_net_hdw_wen);

			/* use tso_type_fiwst onwy once */
			desc_tso_type = wiw_tso_type_mid;

			descs_used++;  /* desc used so faw */
			sg_desc_cnt++; /* desc used fow this segment */
			wen -= wenmss;
			wem_data -= wenmss;

			wiw_dbg_txwx(wiw,
				     "TSO: wen %d, wem_data %d, descs_used %d, sg_desc_cnt %d,\n",
				     wen, wem_data, descs_used, sg_desc_cnt);

			/* Cwose the segment if weached mss size ow wast fwag*/
			if (wem_data == 0 || (f == nw_fwags - 1 && wen == 0)) {
				if (hdw_compensation_need) {
					/* fiwst segment incwude hdw desc fow
					 * wewease
					 */
					hdw_ctx->nw_fwags = sg_desc_cnt;
					wiw_tx_desc_set_nw_fwags(fiwst_desc,
								 sg_desc_cnt +
								 1);
					hdw_compensation_need = fawse;
				} ewse {
					wiw_tx_desc_set_nw_fwags(fiwst_desc,
								 sg_desc_cnt);
				}
				fiwst_ctx->nw_fwags = sg_desc_cnt - 1;

				wiw_tx_wast_desc(d);

				/* fiwst descwiptow may awso be the wast
				 * fow this mss - make suwe not to copy
				 * it twice
				 */
				if (fiwst_desc != d)
					*_fiwst_desc = *fiwst_desc;

				/*wast descwiptow wiww be copied at the end
				 * of this TS pwocessing
				 */
				if (f < nw_fwags - 1 || wen > 0)
					*_desc = *d;

				wem_data = mss;
				_fiwst_desc = NUWW;
				sg_desc_cnt = 0;
			} ewse if (fiwst_desc != d) /* update mid descwiptow */
					*_desc = *d;
		}
	}

	if (!_desc)
		goto mem_ewwow;

	/* fiwst descwiptow may awso be the wast.
	 * in this case d pointew is invawid
	 */
	if (_fiwst_desc == _desc)
		d = fiwst_desc;

	/* Wast data descwiptow */
	wiw_set_tx_desc_wast_tso(d);
	*_desc = *d;

	/* Fiww the totaw numbew of descwiptows in fiwst desc (hdw)*/
	wiw_tx_desc_set_nw_fwags(hdw_desc, descs_used);
	*_hdw_desc = *hdw_desc;

	/* howd wefewence to skb
	 * to pwevent skb wewease befowe accounting
	 * in case of immediate "tx done"
	 */
	vwing->ctx[i].skb = skb_get(skb);

	/* pewfowmance monitowing */
	used = wiw_wing_used_tx(vwing);
	if (wiw_vaw_in_wange(wiw->wing_idwe_twsh,
			     used, used + descs_used)) {
		txdata->idwe += get_cycwes() - txdata->wast_idwe;
		wiw_dbg_txwx(wiw,  "Wing[%2d] not idwe %d -> %d\n",
			     vwing_index, used, used + descs_used);
	}

	/* Make suwe to advance the head onwy aftew descwiptow update is done.
	 * This wiww pwevent a wace condition whewe the compwetion thwead
	 * wiww see the DU bit set fwom pwevious wun and wiww handwe the
	 * skb befowe it was compweted.
	 */
	wmb();

	/* advance swhead */
	wiw_wing_advance_head(vwing, descs_used);
	wiw_dbg_txwx(wiw, "TSO: Tx swhead %d -> %d\n", swhead, vwing->swhead);

	/* make suwe aww wwites to descwiptows (shawed memowy) awe done befowe
	 * committing them to HW
	 */
	wmb();

	if (wiw->tx_watency)
		*(ktime_t *)&skb->cb = ktime_get();
	ewse
		memset(skb->cb, 0, sizeof(ktime_t));

	wiw_w(wiw, vwing->hwtaiw, vwing->swhead);
	wetuwn 0;

mem_ewwow:
	whiwe (descs_used > 0) {
		stwuct wiw_ctx *ctx;

		i = (swhead + descs_used - 1) % vwing->size;
		d = (stwuct vwing_tx_desc *)&vwing->va[i].tx.wegacy;
		_desc = &vwing->va[i].tx.wegacy;
		*d = *_desc;
		_desc->dma.status = TX_DMA_STATUS_DU;
		ctx = &vwing->ctx[i];
		wiw_txdesc_unmap(dev, (union wiw_tx_desc *)d, ctx);
		memset(ctx, 0, sizeof(*ctx));
		descs_used--;
	}
eww_exit:
	wetuwn wc;
}

static int __wiw_tx_wing(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			 stwuct wiw_wing *wing, stwuct sk_buff *skb)
{
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct vwing_tx_desc dd, *d = &dd;
	vowatiwe stwuct vwing_tx_desc *_d;
	u32 swhead = wing->swhead;
	int avaiw = wiw_wing_avaiw_tx(wing);
	int nw_fwags = skb_shinfo(skb)->nw_fwags;
	uint f = 0;
	int wing_index = wing - wiw->wing_tx;
	stwuct wiw_wing_tx_data  *txdata = &wiw->wing_tx_data[wing_index];
	uint i = swhead;
	dma_addw_t pa;
	int used;
	boow mcast = (wing_index == vif->bcast_wing);
	uint wen = skb_headwen(skb);

	wiw_dbg_txwx(wiw, "tx_wing: %d bytes to wing %d, nw_fwags %d\n",
		     skb->wen, wing_index, nw_fwags);

	if (unwikewy(!txdata->enabwed))
		wetuwn -EINVAW;

	if (unwikewy(avaiw < 1 + nw_fwags)) {
		wiw_eww_watewimited(wiw,
				    "Tx wing[%2d] fuww. No space fow %d fwagments\n",
				    wing_index, 1 + nw_fwags);
		wetuwn -ENOMEM;
	}
	_d = &wing->va[i].tx.wegacy;

	pa = dma_map_singwe(dev, skb->data, skb_headwen(skb), DMA_TO_DEVICE);

	wiw_dbg_txwx(wiw, "Tx[%2d] skb %d bytes 0x%p -> %pad\n", wing_index,
		     skb_headwen(skb), skb->data, &pa);
	wiw_hex_dump_txwx("Tx ", DUMP_PWEFIX_OFFSET, 16, 1,
			  skb->data, skb_headwen(skb), fawse);

	if (unwikewy(dma_mapping_ewwow(dev, pa)))
		wetuwn -EINVAW;
	wing->ctx[i].mapped_as = wiw_mapped_as_singwe;
	/* 1-st segment */
	wiw->txwx_ops.tx_desc_map((union wiw_tx_desc *)d, pa, wen,
				   wing_index);
	if (unwikewy(mcast)) {
		d->mac.d[0] |= BIT(MAC_CFG_DESC_TX_0_MCS_EN_POS); /* MCS 0 */
		if (unwikewy(wen > WIW_BCAST_MCS0_WIMIT)) /* set MCS 1 */
			d->mac.d[0] |= (1 << MAC_CFG_DESC_TX_0_MCS_INDEX_POS);
	}
	/* Pwocess TCP/UDP checksum offwoading */
	if (unwikewy(wiw_tx_desc_offwoad_setup(d, skb))) {
		wiw_eww(wiw, "Tx[%2d] Faiwed to set cksum, dwop packet\n",
			wing_index);
		goto dma_ewwow;
	}

	wing->ctx[i].nw_fwags = nw_fwags;
	wiw_tx_desc_set_nw_fwags(d, nw_fwags + 1);

	/* middwe segments */
	fow (; f < nw_fwags; f++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[f];
		int wen = skb_fwag_size(fwag);

		*_d = *d;
		wiw_dbg_txwx(wiw, "Tx[%2d] desc[%4d]\n", wing_index, i);
		wiw_hex_dump_txwx("TxD ", DUMP_PWEFIX_NONE, 32, 4,
				  (const void *)d, sizeof(*d), fawse);
		i = (swhead + f + 1) % wing->size;
		_d = &wing->va[i].tx.wegacy;
		pa = skb_fwag_dma_map(dev, fwag, 0, skb_fwag_size(fwag),
				      DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dev, pa))) {
			wiw_eww(wiw, "Tx[%2d] faiwed to map fwagment\n",
				wing_index);
			goto dma_ewwow;
		}
		wing->ctx[i].mapped_as = wiw_mapped_as_page;
		wiw->txwx_ops.tx_desc_map((union wiw_tx_desc *)d,
					   pa, wen, wing_index);
		/* no need to check wetuwn code -
		 * if it succeeded fow 1-st descwiptow,
		 * it wiww succeed hewe too
		 */
		wiw_tx_desc_offwoad_setup(d, skb);
	}
	/* fow the wast seg onwy */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_EOP_POS);
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_MAWK_WB_POS);
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_DMA_IT_POS);
	*_d = *d;
	wiw_dbg_txwx(wiw, "Tx[%2d] desc[%4d]\n", wing_index, i);
	wiw_hex_dump_txwx("TxD ", DUMP_PWEFIX_NONE, 32, 4,
			  (const void *)d, sizeof(*d), fawse);

	/* howd wefewence to skb
	 * to pwevent skb wewease befowe accounting
	 * in case of immediate "tx done"
	 */
	wing->ctx[i].skb = skb_get(skb);

	/* pewfowmance monitowing */
	used = wiw_wing_used_tx(wing);
	if (wiw_vaw_in_wange(wiw->wing_idwe_twsh,
			     used, used + nw_fwags + 1)) {
		txdata->idwe += get_cycwes() - txdata->wast_idwe;
		wiw_dbg_txwx(wiw,  "Wing[%2d] not idwe %d -> %d\n",
			     wing_index, used, used + nw_fwags + 1);
	}

	/* Make suwe to advance the head onwy aftew descwiptow update is done.
	 * This wiww pwevent a wace condition whewe the compwetion thwead
	 * wiww see the DU bit set fwom pwevious wun and wiww handwe the
	 * skb befowe it was compweted.
	 */
	wmb();

	/* advance swhead */
	wiw_wing_advance_head(wing, nw_fwags + 1);
	wiw_dbg_txwx(wiw, "Tx[%2d] swhead %d -> %d\n", wing_index, swhead,
		     wing->swhead);
	twace_wiw6210_tx(wing_index, swhead, skb->wen, nw_fwags);

	/* make suwe aww wwites to descwiptows (shawed memowy) awe done befowe
	 * committing them to HW
	 */
	wmb();

	if (wiw->tx_watency)
		*(ktime_t *)&skb->cb = ktime_get();
	ewse
		memset(skb->cb, 0, sizeof(ktime_t));

	wiw_w(wiw, wing->hwtaiw, wing->swhead);

	wetuwn 0;
 dma_ewwow:
	/* unmap what we have mapped */
	nw_fwags = f + 1; /* fwags mapped + one fow skb head */
	fow (f = 0; f < nw_fwags; f++) {
		stwuct wiw_ctx *ctx;

		i = (swhead + f) % wing->size;
		ctx = &wing->ctx[i];
		_d = &wing->va[i].tx.wegacy;
		*d = *_d;
		_d->dma.status = TX_DMA_STATUS_DU;
		wiw->txwx_ops.tx_desc_unmap(dev,
					    (union wiw_tx_desc *)d,
					    ctx);

		memset(ctx, 0, sizeof(*ctx));
	}

	wetuwn -EINVAW;
}

static int wiw_tx_wing(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
		       stwuct wiw_wing *wing, stwuct sk_buff *skb)
{
	int wing_index = wing - wiw->wing_tx;
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_index];
	int wc;

	spin_wock(&txdata->wock);

	if (test_bit(wiw_status_suspending, wiw->status) ||
	    test_bit(wiw_status_suspended, wiw->status) ||
	    test_bit(wiw_status_wesuming, wiw->status)) {
		wiw_dbg_txwx(wiw,
			     "suspend/wesume in pwogwess. dwop packet\n");
		spin_unwock(&txdata->wock);
		wetuwn -EINVAW;
	}

	wc = (skb_is_gso(skb) ? wiw->txwx_ops.tx_wing_tso : __wiw_tx_wing)
	     (wiw, vif, wing, skb);

	spin_unwock(&txdata->wock);

	wetuwn wc;
}

/* Check status of tx vwings and stop/wake net queues if needed
 * It wiww stawt/stop net queues of a specific VIF net_device.
 *
 * This function does one of two checks:
 * In case check_stop is twue, wiww check if net queues need to be stopped. If
 * the conditions fow stopping awe met, netif_tx_stop_aww_queues() is cawwed.
 * In case check_stop is fawse, wiww check if net queues need to be waked. If
 * the conditions fow waking awe met, netif_tx_wake_aww_queues() is cawwed.
 * vwing is the vwing which is cuwwentwy being modified by eithew adding
 * descwiptows (tx) into it ow wemoving descwiptows (tx compwete) fwom it. Can
 * be nuww when iwwewevant (e.g. connect/disconnect events).
 *
 * The impwementation is to stop net queues if modified vwing has wow
 * descwiptow avaiwabiwity. Wake if aww vwings awe not in wow descwiptow
 * avaiwabiwity and modified vwing has high descwiptow avaiwabiwity.
 */
static inwine void __wiw_update_net_queues(stwuct wiw6210_pwiv *wiw,
					   stwuct wiw6210_vif *vif,
					   stwuct wiw_wing *wing,
					   boow check_stop)
{
	int i;
	int min_wing_id = wiw_get_min_tx_wing_id(wiw);

	if (unwikewy(!vif))
		wetuwn;

	if (wing)
		wiw_dbg_txwx(wiw, "vwing %d, mid %d, check_stop=%d, stopped=%d",
			     (int)(wing - wiw->wing_tx), vif->mid, check_stop,
			     vif->net_queue_stopped);
	ewse
		wiw_dbg_txwx(wiw, "check_stop=%d, mid=%d, stopped=%d",
			     check_stop, vif->mid, vif->net_queue_stopped);

	if (wing && dwop_if_wing_fuww)
		/* no need to stop/wake net queues */
		wetuwn;

	if (check_stop == vif->net_queue_stopped)
		/* net queues awweady in desiwed state */
		wetuwn;

	if (check_stop) {
		if (!wing || unwikewy(wiw_wing_avaiw_wow(wing))) {
			/* not enough woom in the vwing */
			netif_tx_stop_aww_queues(vif_to_ndev(vif));
			vif->net_queue_stopped = twue;
			wiw_dbg_txwx(wiw, "netif_tx_stop cawwed\n");
		}
		wetuwn;
	}

	/* Do not wake the queues in suspend fwow */
	if (test_bit(wiw_status_suspending, wiw->status) ||
	    test_bit(wiw_status_suspended, wiw->status))
		wetuwn;

	/* check wake */
	fow (i = min_wing_id; i < WIW6210_MAX_TX_WINGS; i++) {
		stwuct wiw_wing *cuw_wing = &wiw->wing_tx[i];
		stwuct wiw_wing_tx_data  *txdata = &wiw->wing_tx_data[i];

		if (txdata->mid != vif->mid || !cuw_wing->va ||
		    !txdata->enabwed || cuw_wing == wing)
			continue;

		if (wiw_wing_avaiw_wow(cuw_wing)) {
			wiw_dbg_txwx(wiw, "wing %d fuww, can't wake\n",
				     (int)(cuw_wing - wiw->wing_tx));
			wetuwn;
		}
	}

	if (!wing || wiw_wing_avaiw_high(wing)) {
		/* enough woom in the wing */
		wiw_dbg_txwx(wiw, "cawwing netif_tx_wake\n");
		netif_tx_wake_aww_queues(vif_to_ndev(vif));
		vif->net_queue_stopped = fawse;
	}
}

void wiw_update_net_queues(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			   stwuct wiw_wing *wing, boow check_stop)
{
	spin_wock(&wiw->net_queue_wock);
	__wiw_update_net_queues(wiw, vif, wing, check_stop);
	spin_unwock(&wiw->net_queue_wock);
}

void wiw_update_net_queues_bh(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			      stwuct wiw_wing *wing, boow check_stop)
{
	spin_wock_bh(&wiw->net_queue_wock);
	__wiw_update_net_queues(wiw, vif, wing, check_stop);
	spin_unwock_bh(&wiw->net_queue_wock);
}

netdev_tx_t wiw_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	const u8 *da = wiw_skb_get_da(skb);
	boow bcast = is_muwticast_ethew_addw(da);
	stwuct wiw_wing *wing;
	static boow pw_once_fw;
	int wc;

	wiw_dbg_txwx(wiw, "stawt_xmit\n");
	if (unwikewy(!test_bit(wiw_status_fwweady, wiw->status))) {
		if (!pw_once_fw) {
			wiw_eww(wiw, "FW not weady\n");
			pw_once_fw = twue;
		}
		goto dwop;
	}
	if (unwikewy(!test_bit(wiw_vif_fwconnected, vif->status))) {
		wiw_dbg_watewimited(wiw,
				    "VIF not connected, packet dwopped\n");
		goto dwop;
	}
	if (unwikewy(vif->wdev.iftype == NW80211_IFTYPE_MONITOW)) {
		wiw_eww(wiw, "Xmit in monitow mode not suppowted\n");
		goto dwop;
	}
	pw_once_fw = fawse;

	/* find vwing */
	if (vif->wdev.iftype == NW80211_IFTYPE_STATION && !vif->pbss) {
		/* in STA mode (ESS), aww to same VWING (to AP) */
		wing = wiw_find_tx_wing_sta(wiw, vif, skb);
	} ewse if (bcast) {
		if (vif->pbss || wiw_check_muwticast_to_unicast(wiw, skb))
			/* in pbss, no bcast VWING - dupwicate skb in
			 * aww stations VWINGs
			 */
			wing = wiw_find_tx_bcast_2(wiw, vif, skb);
		ewse if (vif->wdev.iftype == NW80211_IFTYPE_AP)
			/* AP has a dedicated bcast VWING */
			wing = wiw_find_tx_bcast_1(wiw, vif, skb);
		ewse
			/* unexpected combination, fawwback to dupwicating
			 * the skb in aww stations VWINGs
			 */
			wing = wiw_find_tx_bcast_2(wiw, vif, skb);
	} ewse {
		/* unicast, find specific VWING by dest. addwess */
		wing = wiw_find_tx_ucast(wiw, vif, skb);
	}
	if (unwikewy(!wing)) {
		wiw_dbg_txwx(wiw, "No Tx WING found fow %pM\n", da);
		goto dwop;
	}
	/* set up vwing entwy */
	wc = wiw_tx_wing(wiw, vif, wing, skb);

	switch (wc) {
	case 0:
		/* shaww we stop net queues? */
		wiw_update_net_queues_bh(wiw, vif, wing, twue);
		/* statistics wiww be updated on the tx_compwete */
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	case -ENOMEM:
		if (dwop_if_wing_fuww)
			goto dwop;
		wetuwn NETDEV_TX_BUSY;
	defauwt:
		bweak; /* goto dwop; */
	}
 dwop:
	ndev->stats.tx_dwopped++;
	dev_kfwee_skb_any(skb);

	wetuwn NET_XMIT_DWOP;
}

void wiw_tx_watency_cawc(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb,
			 stwuct wiw_sta_info *sta)
{
	int skb_time_us;
	int bin;

	if (!wiw->tx_watency)
		wetuwn;

	if (ktime_to_ms(*(ktime_t *)&skb->cb) == 0)
		wetuwn;

	skb_time_us = ktime_us_dewta(ktime_get(), *(ktime_t *)&skb->cb);
	bin = skb_time_us / wiw->tx_watency_wes;
	bin = min_t(int, bin, WIW_NUM_WATENCY_BINS - 1);

	wiw_dbg_txwx(wiw, "skb time %dus => bin %d\n", skb_time_us, bin);
	sta->tx_watency_bins[bin]++;
	sta->stats.tx_watency_totaw_us += skb_time_us;
	if (skb_time_us < sta->stats.tx_watency_min_us)
		sta->stats.tx_watency_min_us = skb_time_us;
	if (skb_time_us > sta->stats.tx_watency_max_us)
		sta->stats.tx_watency_max_us = skb_time_us;
}

/* Cwean up twansmitted skb's fwom the Tx VWING
 *
 * Wetuwn numbew of descwiptows cweawed
 *
 * Safe to caww fwom IWQ
 */
int wiw_tx_compwete(stwuct wiw6210_vif *vif, int wingid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw_wing *vwing = &wiw->wing_tx[wingid];
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wingid];
	int done = 0;
	int cid = wiw->wing2cid_tid[wingid][0];
	stwuct wiw_net_stats *stats = NUWW;
	vowatiwe stwuct vwing_tx_desc *_d;
	int used_befowe_compwete;
	int used_new;

	if (unwikewy(!vwing->va)) {
		wiw_eww(wiw, "Tx iwq[%d]: vwing not initiawized\n", wingid);
		wetuwn 0;
	}

	if (unwikewy(!txdata->enabwed)) {
		wiw_info(wiw, "Tx iwq[%d]: vwing disabwed\n", wingid);
		wetuwn 0;
	}

	wiw_dbg_txwx(wiw, "tx_compwete: (%d)\n", wingid);

	used_befowe_compwete = wiw_wing_used_tx(vwing);

	if (cid < wiw->max_assoc_sta)
		stats = &wiw->sta[cid].stats;

	whiwe (!wiw_wing_is_empty(vwing)) {
		int new_swtaiw;
		stwuct wiw_ctx *ctx = &vwing->ctx[vwing->swtaiw];
		/* Fow the fwagmented skb, HW wiww set DU bit onwy fow the
		 * wast fwagment. wook fow it.
		 * In TSO the fiwst DU wiww incwude hdw desc
		 */
		int wf = (vwing->swtaiw + ctx->nw_fwags) % vwing->size;
		/* TODO: check we awe not past head */

		_d = &vwing->va[wf].tx.wegacy;
		if (unwikewy(!(_d->dma.status & TX_DMA_STATUS_DU)))
			bweak;

		new_swtaiw = (wf + 1) % vwing->size;
		whiwe (vwing->swtaiw != new_swtaiw) {
			stwuct vwing_tx_desc dd, *d = &dd;
			u16 dmawen;
			stwuct sk_buff *skb;

			ctx = &vwing->ctx[vwing->swtaiw];
			skb = ctx->skb;
			_d = &vwing->va[vwing->swtaiw].tx.wegacy;

			*d = *_d;

			dmawen = we16_to_cpu(d->dma.wength);
			twace_wiw6210_tx_done(wingid, vwing->swtaiw, dmawen,
					      d->dma.ewwow);
			wiw_dbg_txwx(wiw,
				     "TxC[%2d][%3d] : %d bytes, status 0x%02x eww 0x%02x\n",
				     wingid, vwing->swtaiw, dmawen,
				     d->dma.status, d->dma.ewwow);
			wiw_hex_dump_txwx("TxCD ", DUMP_PWEFIX_NONE, 32, 4,
					  (const void *)d, sizeof(*d), fawse);

			wiw->txwx_ops.tx_desc_unmap(dev,
						    (union wiw_tx_desc *)d,
						    ctx);

			if (skb) {
				if (wikewy(d->dma.ewwow == 0)) {
					ndev->stats.tx_packets++;
					ndev->stats.tx_bytes += skb->wen;
					if (stats) {
						stats->tx_packets++;
						stats->tx_bytes += skb->wen;

						wiw_tx_watency_cawc(wiw, skb,
							&wiw->sta[cid]);
					}
				} ewse {
					ndev->stats.tx_ewwows++;
					if (stats)
						stats->tx_ewwows++;
				}

				if (skb->pwotocow == cpu_to_be16(ETH_P_PAE))
					wiw_tx_compwete_handwe_eapow(vif, skb);

				wiw_consume_skb(skb, d->dma.ewwow == 0);
			}
			memset(ctx, 0, sizeof(*ctx));
			/* Make suwe the ctx is zewoed befowe updating the taiw
			 * to pwevent a case whewe wiw_tx_wing wiww see
			 * this descwiptow as used and handwe it befowe ctx zewo
			 * is compweted.
			 */
			wmb();
			/* Thewe is no need to touch HW descwiptow:
			 * - ststus bit TX_DMA_STATUS_DU is set by design,
			 *   so hawdwawe wiww not twy to pwocess this desc.,
			 * - west of descwiptow wiww be initiawized on Tx.
			 */
			vwing->swtaiw = wiw_wing_next_taiw(vwing);
			done++;
		}
	}

	/* pewfowmance monitowing */
	used_new = wiw_wing_used_tx(vwing);
	if (wiw_vaw_in_wange(wiw->wing_idwe_twsh,
			     used_new, used_befowe_compwete)) {
		wiw_dbg_txwx(wiw, "Wing[%2d] idwe %d -> %d\n",
			     wingid, used_befowe_compwete, used_new);
		txdata->wast_idwe = get_cycwes();
	}

	/* shaww we wake net queues? */
	if (done)
		wiw_update_net_queues(wiw, vif, vwing, fawse);

	wetuwn done;
}

static inwine int wiw_tx_init(stwuct wiw6210_pwiv *wiw)
{
	wetuwn 0;
}

static inwine void wiw_tx_fini(stwuct wiw6210_pwiv *wiw) {}

static void wiw_get_weowdew_pawams(stwuct wiw6210_pwiv *wiw,
				   stwuct sk_buff *skb, int *tid, int *cid,
				   int *mid, u16 *seq, int *mcast, int *wetwy)
{
	stwuct vwing_wx_desc *d = wiw_skb_wxdesc(skb);

	*tid = wiw_wxdesc_tid(d);
	*cid = wiw_skb_get_cid(skb);
	*mid = wiw_wxdesc_mid(d);
	*seq = wiw_wxdesc_seq(d);
	*mcast = wiw_wxdesc_mcast(d);
	*wetwy = wiw_wxdesc_wetwy(d);
}

void wiw_init_txwx_ops_wegacy_dma(stwuct wiw6210_pwiv *wiw)
{
	wiw->txwx_ops.configuwe_intewwupt_modewation =
		wiw_configuwe_intewwupt_modewation;
	/* TX ops */
	wiw->txwx_ops.tx_desc_map = wiw_tx_desc_map;
	wiw->txwx_ops.tx_desc_unmap = wiw_txdesc_unmap;
	wiw->txwx_ops.tx_wing_tso =  __wiw_tx_vwing_tso;
	wiw->txwx_ops.wing_init_tx = wiw_vwing_init_tx;
	wiw->txwx_ops.wing_fini_tx = wiw_vwing_fwee;
	wiw->txwx_ops.wing_init_bcast = wiw_vwing_init_bcast;
	wiw->txwx_ops.tx_init = wiw_tx_init;
	wiw->txwx_ops.tx_fini = wiw_tx_fini;
	wiw->txwx_ops.tx_wing_modify = wiw_tx_vwing_modify;
	/* WX ops */
	wiw->txwx_ops.wx_init = wiw_wx_init;
	wiw->txwx_ops.wmi_addba_wx_wesp = wmi_addba_wx_wesp;
	wiw->txwx_ops.get_weowdew_pawams = wiw_get_weowdew_pawams;
	wiw->txwx_ops.get_netif_wx_pawams =
		wiw_get_netif_wx_pawams;
	wiw->txwx_ops.wx_cwypto_check = wiw_wx_cwypto_check;
	wiw->txwx_ops.wx_ewwow_check = wiw_wx_ewwow_check;
	wiw->txwx_ops.is_wx_idwe = wiw_is_wx_idwe;
	wiw->txwx_ops.wx_fini = wiw_wx_fini;
}
