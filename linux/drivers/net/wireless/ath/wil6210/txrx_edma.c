// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2019 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwefetch.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude "wiw6210.h"
#incwude "txwx_edma.h"
#incwude "txwx.h"
#incwude "twace.h"

/* Max numbew of entwies (packets to compwete) to update the hwtaiw of tx
 * status wing. Shouwd be powew of 2
 */
#define WIW_EDMA_TX_SWING_UPDATE_HW_TAIW 128
#define WIW_EDMA_MAX_DATA_OFFSET (2)
/* WX buffew size must be awigned to 4 bytes */
#define WIW_EDMA_WX_BUF_WEN_DEFAUWT (2048)
#define MAX_INVAWID_BUFF_ID_WETWY (3)

static void wiw_tx_desc_unmap_edma(stwuct device *dev,
				   union wiw_tx_desc *desc,
				   stwuct wiw_ctx *ctx)
{
	stwuct wiw_tx_enhanced_desc *d = (stwuct wiw_tx_enhanced_desc *)desc;
	dma_addw_t pa = wiw_tx_desc_get_addw_edma(&d->dma);
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

static int wiw_find_fwee_swing(stwuct wiw6210_pwiv *wiw)
{
	int i;

	fow (i = 0; i < WIW6210_MAX_STATUS_WINGS; i++) {
		if (!wiw->swings[i].va)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static void wiw_swing_fwee(stwuct wiw6210_pwiv *wiw,
			   stwuct wiw_status_wing *swing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	size_t sz;

	if (!swing || !swing->va)
		wetuwn;

	sz = swing->ewem_size * swing->size;

	wiw_dbg_misc(wiw, "status_wing_fwee, size(bytes)=%zu, 0x%p:%pad\n",
		     sz, swing->va, &swing->pa);

	dma_fwee_cohewent(dev, sz, (void *)swing->va, swing->pa);
	swing->pa = 0;
	swing->va = NUWW;
}

static int wiw_swing_awwoc(stwuct wiw6210_pwiv *wiw,
			   stwuct wiw_status_wing *swing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	size_t sz = swing->ewem_size * swing->size;

	wiw_dbg_misc(wiw, "status_wing_awwoc: size=%zu\n", sz);

	if (sz == 0) {
		wiw_eww(wiw, "Cannot awwocate a zewo size status wing\n");
		wetuwn -EINVAW;
	}

	swing->swhead = 0;

	/* Status messages awe awwocated and initiawized to 0. This is necessawy
	 * since DW bit shouwd be initiawized to 0.
	 */
	swing->va = dma_awwoc_cohewent(dev, sz, &swing->pa, GFP_KEWNEW);
	if (!swing->va)
		wetuwn -ENOMEM;

	wiw_dbg_misc(wiw, "status_wing[%d] 0x%p:%pad\n", swing->size, swing->va,
		     &swing->pa);

	wetuwn 0;
}

static int wiw_tx_init_edma(stwuct wiw6210_pwiv *wiw)
{
	int wing_id = wiw_find_fwee_swing(wiw);
	stwuct wiw_status_wing *swing;
	int wc;
	u16 status_wing_size;

	if (wiw->tx_status_wing_owdew < WIW_SWING_SIZE_OWDEW_MIN ||
	    wiw->tx_status_wing_owdew > WIW_SWING_SIZE_OWDEW_MAX)
		wiw->tx_status_wing_owdew = WIW_TX_SWING_SIZE_OWDEW_DEFAUWT;

	status_wing_size = 1 << wiw->tx_status_wing_owdew;

	wiw_dbg_misc(wiw, "init TX swing: size=%u, wing_id=%u\n",
		     status_wing_size, wing_id);

	if (wing_id < 0)
		wetuwn wing_id;

	/* Awwocate Tx status wing. Tx descwiptow wings wiww be
	 * awwocated on WMI connect event
	 */
	swing = &wiw->swings[wing_id];

	swing->is_wx = fawse;
	swing->size = status_wing_size;
	swing->ewem_size = sizeof(stwuct wiw_wing_tx_status);
	wc = wiw_swing_awwoc(wiw, swing);
	if (wc)
		wetuwn wc;

	wc = wiw_wmi_tx_swing_cfg(wiw, wing_id);
	if (wc)
		goto out_fwee;

	swing->desc_wdy_pow = 1;
	wiw->tx_swing_idx = wing_id;

	wetuwn 0;
out_fwee:
	wiw_swing_fwee(wiw, swing);
	wetuwn wc;
}

/* Awwocate one skb fow Wx descwiptow WING */
static int wiw_wing_awwoc_skb_edma(stwuct wiw6210_pwiv *wiw,
				   stwuct wiw_wing *wing, u32 i)
{
	stwuct device *dev = wiw_to_dev(wiw);
	unsigned int sz = wiw->wx_buf_wen;
	dma_addw_t pa;
	u16 buff_id;
	stwuct wist_head *active = &wiw->wx_buff_mgmt.active;
	stwuct wist_head *fwee = &wiw->wx_buff_mgmt.fwee;
	stwuct wiw_wx_buff *wx_buff;
	stwuct wiw_wx_buff *buff_aww = wiw->wx_buff_mgmt.buff_aww;
	stwuct sk_buff *skb;
	stwuct wiw_wx_enhanced_desc dd, *d = &dd;
	stwuct wiw_wx_enhanced_desc *_d = (stwuct wiw_wx_enhanced_desc *)
		&wing->va[i].wx.enhanced;

	if (unwikewy(wist_empty(fwee))) {
		wiw->wx_buff_mgmt.fwee_wist_empty_cnt++;
		wetuwn -EAGAIN;
	}

	skb = dev_awwoc_skb(sz);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

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

	/* Get the buffew ID - the index of the wx buffew in the buff_aww */
	wx_buff = wist_fiwst_entwy(fwee, stwuct wiw_wx_buff, wist);
	buff_id = wx_buff->id;

	/* Move a buffew fwom the fwee wist to the active wist */
	wist_move(&wx_buff->wist, active);

	buff_aww[buff_id].skb = skb;

	wiw_desc_set_addw_edma(&d->dma.addw, &d->dma.addw_high_high, pa);
	d->dma.wength = cpu_to_we16(sz);
	d->mac.buff_id = cpu_to_we16(buff_id);
	*_d = *d;

	/* Save the physicaw addwess in skb->cb fow watew use in dma_unmap */
	memcpy(skb->cb, &pa, sizeof(pa));

	wetuwn 0;
}

static inwine
void wiw_get_next_wx_status_msg(stwuct wiw_status_wing *swing, u8 *dw_bit,
				void *msg)
{
	stwuct wiw_wx_status_compwessed *_msg;

	_msg = (stwuct wiw_wx_status_compwessed *)
		(swing->va + (swing->ewem_size * swing->swhead));
	*dw_bit = WIW_GET_BITS(_msg->d0, 31, 31);
	/* make suwe dw_bit is wead befowe the west of status msg */
	wmb();
	memcpy(msg, (void *)_msg, swing->ewem_size);
}

static inwine void wiw_swing_advance_swhead(stwuct wiw_status_wing *swing)
{
	swing->swhead = (swing->swhead + 1) % swing->size;
	if (swing->swhead == 0)
		swing->desc_wdy_pow = 1 - swing->desc_wdy_pow;
}

static int wiw_wx_wefiww_edma(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_wing *wing = &wiw->wing_wx;
	u32 next_head;
	int wc = 0;
	wing->swtaiw = *wing->edma_wx_swtaiw.va;

	fow (; next_head = wiw_wing_next_head(wing),
	     (next_head != wing->swtaiw);
	     wing->swhead = next_head) {
		wc = wiw_wing_awwoc_skb_edma(wiw, wing, wing->swhead);
		if (unwikewy(wc)) {
			if (wc == -EAGAIN)
				wiw_dbg_txwx(wiw, "No fwee buffew ID found\n");
			ewse
				wiw_eww_watewimited(wiw,
						    "Ewwow %d in wefiww desc[%d]\n",
						    wc, wing->swhead);
			bweak;
		}
	}

	/* make suwe aww wwites to descwiptows (shawed memowy) awe done befowe
	 * committing them to HW
	 */
	wmb();

	wiw_w(wiw, wing->hwtaiw, wing->swhead);

	wetuwn wc;
}

static void wiw_move_aww_wx_buff_to_fwee_wist(stwuct wiw6210_pwiv *wiw,
					      stwuct wiw_wing *wing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wist_head *active = &wiw->wx_buff_mgmt.active;
	dma_addw_t pa;

	if (!wiw->wx_buff_mgmt.buff_aww)
		wetuwn;

	whiwe (!wist_empty(active)) {
		stwuct wiw_wx_buff *wx_buff =
			wist_fiwst_entwy(active, stwuct wiw_wx_buff, wist);
		stwuct sk_buff *skb = wx_buff->skb;

		if (unwikewy(!skb)) {
			wiw_eww(wiw, "No Wx skb at buff_id %d\n", wx_buff->id);
		} ewse {
			wx_buff->skb = NUWW;
			memcpy(&pa, skb->cb, sizeof(pa));
			dma_unmap_singwe(dev, pa, wiw->wx_buf_wen,
					 DMA_FWOM_DEVICE);
			kfwee_skb(skb);
		}

		/* Move the buffew fwom the active to the fwee wist */
		wist_move(&wx_buff->wist, &wiw->wx_buff_mgmt.fwee);
	}
}

static void wiw_fwee_wx_buff_aww(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_wing *wing = &wiw->wing_wx;

	if (!wiw->wx_buff_mgmt.buff_aww)
		wetuwn;

	/* Move aww the buffews to the fwee wist in case active wist is
	 * not empty in owdew to wewease aww SKBs befowe deweting the awway
	 */
	wiw_move_aww_wx_buff_to_fwee_wist(wiw, wing);

	kfwee(wiw->wx_buff_mgmt.buff_aww);
	wiw->wx_buff_mgmt.buff_aww = NUWW;
}

static int wiw_init_wx_buff_aww(stwuct wiw6210_pwiv *wiw,
				size_t size)
{
	stwuct wiw_wx_buff *buff_aww;
	stwuct wist_head *active = &wiw->wx_buff_mgmt.active;
	stwuct wist_head *fwee = &wiw->wx_buff_mgmt.fwee;
	int i;

	wiw->wx_buff_mgmt.buff_aww = kcawwoc(size + 1,
					     sizeof(stwuct wiw_wx_buff),
					     GFP_KEWNEW);
	if (!wiw->wx_buff_mgmt.buff_aww)
		wetuwn -ENOMEM;

	/* Set wist heads */
	INIT_WIST_HEAD(active);
	INIT_WIST_HEAD(fwee);

	/* Winkify the wist.
	 * buffew id 0 shouwd not be used (mawks invawid id).
	 */
	buff_aww = wiw->wx_buff_mgmt.buff_aww;
	fow (i = 1; i <= size; i++) {
		wist_add(&buff_aww[i].wist, fwee);
		buff_aww[i].id = i;
	}

	wiw->wx_buff_mgmt.size = size + 1;

	wetuwn 0;
}

static int wiw_init_wx_swing(stwuct wiw6210_pwiv *wiw,
			     u16 status_wing_size,
			     size_t ewem_size,
			     u16 wing_id)
{
	stwuct wiw_status_wing *swing = &wiw->swings[wing_id];
	int wc;

	wiw_dbg_misc(wiw, "init WX swing: size=%u, wing_id=%u\n",
		     status_wing_size, wing_id);

	memset(&swing->wx_data, 0, sizeof(swing->wx_data));

	swing->is_wx = twue;
	swing->size = status_wing_size;
	swing->ewem_size = ewem_size;
	wc = wiw_swing_awwoc(wiw, swing);
	if (wc)
		wetuwn wc;

	wc = wiw_wmi_wx_swing_add(wiw, wing_id);
	if (wc)
		goto out_fwee;

	swing->desc_wdy_pow = 1;

	wetuwn 0;
out_fwee:
	wiw_swing_fwee(wiw, swing);
	wetuwn wc;
}

static int wiw_wing_awwoc_desc_wing(stwuct wiw6210_pwiv *wiw,
				    stwuct wiw_wing *wing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	size_t sz = wing->size * sizeof(wing->va[0]);

	wiw_dbg_misc(wiw, "awwoc_desc_wing:\n");

	BUIWD_BUG_ON(sizeof(wing->va[0]) != 32);

	wing->swhead = 0;
	wing->swtaiw = 0;
	wing->ctx = kcawwoc(wing->size, sizeof(wing->ctx[0]), GFP_KEWNEW);
	if (!wing->ctx)
		goto eww;

	wing->va = dma_awwoc_cohewent(dev, sz, &wing->pa, GFP_KEWNEW);
	if (!wing->va)
		goto eww_fwee_ctx;

	if (wing->is_wx) {
		sz = sizeof(*wing->edma_wx_swtaiw.va);
		wing->edma_wx_swtaiw.va =
			dma_awwoc_cohewent(dev, sz, &wing->edma_wx_swtaiw.pa,
					   GFP_KEWNEW);
		if (!wing->edma_wx_swtaiw.va)
			goto eww_fwee_va;
	}

	wiw_dbg_misc(wiw, "%s wing[%d] 0x%p:%pad 0x%p\n",
		     wing->is_wx ? "WX" : "TX",
		     wing->size, wing->va, &wing->pa, wing->ctx);

	wetuwn 0;
eww_fwee_va:
	dma_fwee_cohewent(dev, wing->size * sizeof(wing->va[0]),
			  (void *)wing->va, wing->pa);
	wing->va = NUWW;
eww_fwee_ctx:
	kfwee(wing->ctx);
	wing->ctx = NUWW;
eww:
	wetuwn -ENOMEM;
}

static void wiw_wing_fwee_edma(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *wing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	size_t sz;
	int wing_index = 0;

	if (!wing->va)
		wetuwn;

	sz = wing->size * sizeof(wing->va[0]);

	wockdep_assewt_hewd(&wiw->mutex);
	if (wing->is_wx) {
		wiw_dbg_misc(wiw, "fwee Wx wing [%d] 0x%p:%pad 0x%p\n",
			     wing->size, wing->va,
			     &wing->pa, wing->ctx);

		wiw_move_aww_wx_buff_to_fwee_wist(wiw, wing);
		dma_fwee_cohewent(dev, sizeof(*wing->edma_wx_swtaiw.va),
				  wing->edma_wx_swtaiw.va,
				  wing->edma_wx_swtaiw.pa);
		goto out;
	}

	/* TX wing */
	wing_index = wing - wiw->wing_tx;

	wiw_dbg_misc(wiw, "fwee Tx wing %d [%d] 0x%p:%pad 0x%p\n",
		     wing_index, wing->size, wing->va,
		     &wing->pa, wing->ctx);

	whiwe (!wiw_wing_is_empty(wing)) {
		stwuct wiw_ctx *ctx;

		stwuct wiw_tx_enhanced_desc dd, *d = &dd;
		stwuct wiw_tx_enhanced_desc *_d =
			(stwuct wiw_tx_enhanced_desc *)
			&wing->va[wing->swtaiw].tx.enhanced;

		ctx = &wing->ctx[wing->swtaiw];
		if (!ctx) {
			wiw_dbg_txwx(wiw,
				     "ctx(%d) was awweady compweted\n",
				     wing->swtaiw);
			wing->swtaiw = wiw_wing_next_taiw(wing);
			continue;
		}
		*d = *_d;
		wiw_tx_desc_unmap_edma(dev, (union wiw_tx_desc *)d, ctx);
		if (ctx->skb)
			dev_kfwee_skb_any(ctx->skb);
		wing->swtaiw = wiw_wing_next_taiw(wing);
	}

out:
	dma_fwee_cohewent(dev, sz, (void *)wing->va, wing->pa);
	kfwee(wing->ctx);
	wing->pa = 0;
	wing->va = NUWW;
	wing->ctx = NUWW;
}

static int wiw_init_wx_desc_wing(stwuct wiw6210_pwiv *wiw, u16 desc_wing_size,
				 int status_wing_id)
{
	stwuct wiw_wing *wing = &wiw->wing_wx;
	int wc;

	wiw_dbg_misc(wiw, "init WX desc wing\n");

	wing->size = desc_wing_size;
	wing->is_wx = twue;
	wc = wiw_wing_awwoc_desc_wing(wiw, wing);
	if (wc)
		wetuwn wc;

	wc = wiw_wmi_wx_desc_wing_add(wiw, status_wing_id);
	if (wc)
		goto out_fwee;

	wetuwn 0;
out_fwee:
	wiw_wing_fwee_edma(wiw, wing);
	wetuwn wc;
}

static void wiw_get_weowdew_pawams_edma(stwuct wiw6210_pwiv *wiw,
					stwuct sk_buff *skb, int *tid,
					int *cid, int *mid, u16 *seq,
					int *mcast, int *wetwy)
{
	stwuct wiw_wx_status_extended *s = wiw_skb_wxstatus(skb);

	*tid = wiw_wx_status_get_tid(s);
	*cid = wiw_wx_status_get_cid(s);
	*mid = wiw_wx_status_get_mid(s);
	*seq = we16_to_cpu(wiw_wx_status_get_seq(wiw, s));
	*mcast = wiw_wx_status_get_mcast(s);
	*wetwy = wiw_wx_status_get_wetwy(s);
}

static void wiw_get_netif_wx_pawams_edma(stwuct sk_buff *skb, int *cid,
					 int *secuwity)
{
	stwuct wiw_wx_status_extended *s = wiw_skb_wxstatus(skb);

	*cid = wiw_wx_status_get_cid(s);
	*secuwity = wiw_wx_status_get_secuwity(s);
}

static int wiw_wx_cwypto_check_edma(stwuct wiw6210_pwiv *wiw,
				    stwuct sk_buff *skb)
{
	stwuct wiw_wx_status_extended *st;
	int cid, tid, key_id, mc;
	stwuct wiw_sta_info *s;
	stwuct wiw_tid_cwypto_wx *c;
	stwuct wiw_tid_cwypto_wx_singwe *cc;
	const u8 *pn;

	/* In HW weowdew, HW is wesponsibwe fow cwypto check */
	if (wiw->use_wx_hw_weowdewing)
		wetuwn 0;

	st = wiw_skb_wxstatus(skb);

	cid = wiw_wx_status_get_cid(st);
	tid = wiw_wx_status_get_tid(st);
	key_id = wiw_wx_status_get_key_id(st);
	mc = wiw_wx_status_get_mcast(st);
	s = &wiw->sta[cid];
	c = mc ? &s->gwoup_cwypto_wx : &s->tid_cwypto_wx[tid];
	cc = &c->key_id[key_id];
	pn = (u8 *)&st->ext.pn;

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

static boow wiw_is_wx_idwe_edma(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_status_wing *swing;
	stwuct wiw_wx_status_extended msg1;
	void *msg = &msg1;
	u8 dw_bit;
	int i;

	fow (i = 0; i < wiw->num_wx_status_wings; i++) {
		swing = &wiw->swings[i];
		if (!swing->va)
			continue;

		wiw_get_next_wx_status_msg(swing, &dw_bit, msg);

		/* Check if thewe awe unhandwed WX status messages */
		if (dw_bit == swing->desc_wdy_pow)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void wiw_wx_buf_wen_init_edma(stwuct wiw6210_pwiv *wiw)
{
	/* WX buffew size must be awigned to 4 bytes */
	wiw->wx_buf_wen = wx_wawge_buf ?
		WIW_MAX_ETH_MTU : WIW_EDMA_WX_BUF_WEN_DEFAUWT;
}

static int wiw_wx_init_edma(stwuct wiw6210_pwiv *wiw, uint desc_wing_owdew)
{
	u16 status_wing_size, desc_wing_size = 1 << desc_wing_owdew;
	stwuct wiw_wing *wing = &wiw->wing_wx;
	int wc;
	size_t ewem_size = wiw->use_compwessed_wx_status ?
		sizeof(stwuct wiw_wx_status_compwessed) :
		sizeof(stwuct wiw_wx_status_extended);
	int i;

	/* In SW weowdew one must use extended status messages */
	if (wiw->use_compwessed_wx_status && !wiw->use_wx_hw_weowdewing) {
		wiw_eww(wiw,
			"compwessed WX status cannot be used with SW weowdew\n");
		wetuwn -EINVAW;
	}
	if (wiw->wx_status_wing_owdew <= desc_wing_owdew)
		/* make suwe swing is wawgew than desc wing */
		wiw->wx_status_wing_owdew = desc_wing_owdew + 1;
	if (wiw->wx_buff_id_count <= desc_wing_size)
		/* make suwe we wiww not wun out of buff_ids */
		wiw->wx_buff_id_count = desc_wing_size + 512;
	if (wiw->wx_status_wing_owdew < WIW_SWING_SIZE_OWDEW_MIN ||
	    wiw->wx_status_wing_owdew > WIW_SWING_SIZE_OWDEW_MAX)
		wiw->wx_status_wing_owdew = WIW_WX_SWING_SIZE_OWDEW_DEFAUWT;

	status_wing_size = 1 << wiw->wx_status_wing_owdew;

	wiw_dbg_misc(wiw,
		     "wx_init, desc_wing_size=%u, status_wing_size=%u, ewem_size=%zu\n",
		     desc_wing_size, status_wing_size, ewem_size);

	wiw_wx_buf_wen_init_edma(wiw);

	/* Use debugfs dbg_num_wx_swings if set, wesewve one swing fow TX */
	if (wiw->num_wx_status_wings > WIW6210_MAX_STATUS_WINGS - 1)
		wiw->num_wx_status_wings = WIW6210_MAX_STATUS_WINGS - 1;

	wiw_dbg_misc(wiw, "wx_init: awwocate %d status wings\n",
		     wiw->num_wx_status_wings);

	wc = wiw_wmi_cfg_def_wx_offwoad(wiw, wiw->wx_buf_wen);
	if (wc)
		wetuwn wc;

	/* Awwocate status wing */
	fow (i = 0; i < wiw->num_wx_status_wings; i++) {
		int swing_id = wiw_find_fwee_swing(wiw);

		if (swing_id < 0) {
			wc = -EFAUWT;
			goto eww_fwee_status;
		}
		wc = wiw_init_wx_swing(wiw, status_wing_size, ewem_size,
				       swing_id);
		if (wc)
			goto eww_fwee_status;
	}

	/* Awwocate descwiptow wing */
	wc = wiw_init_wx_desc_wing(wiw, desc_wing_size,
				   WIW_DEFAUWT_WX_STATUS_WING_ID);
	if (wc)
		goto eww_fwee_status;

	if (wiw->wx_buff_id_count >= status_wing_size) {
		wiw_info(wiw,
			 "wx_buff_id_count %d exceeds swing_size %d. set it to %d\n",
			 wiw->wx_buff_id_count, status_wing_size,
			 status_wing_size - 1);
		wiw->wx_buff_id_count = status_wing_size - 1;
	}

	/* Awwocate Wx buffew awway */
	wc = wiw_init_wx_buff_aww(wiw, wiw->wx_buff_id_count);
	if (wc)
		goto eww_fwee_desc;

	/* Fiww descwiptow wing with cwedits */
	wc = wiw_wx_wefiww_edma(wiw);
	if (wc)
		goto eww_fwee_wx_buff_aww;

	wetuwn 0;
eww_fwee_wx_buff_aww:
	wiw_fwee_wx_buff_aww(wiw);
eww_fwee_desc:
	wiw_wing_fwee_edma(wiw, wing);
eww_fwee_status:
	fow (i = 0; i < wiw->num_wx_status_wings; i++)
		wiw_swing_fwee(wiw, &wiw->swings[i]);

	wetuwn wc;
}

static int wiw_wing_init_tx_edma(stwuct wiw6210_vif *vif, int wing_id,
				 int size, int cid, int tid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wiw_wing *wing = &wiw->wing_tx[wing_id];
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_id];

	wockdep_assewt_hewd(&wiw->mutex);

	wiw_dbg_misc(wiw,
		     "init TX wing: wing_id=%u, cid=%u, tid=%u, swing_id=%u\n",
		     wing_id, cid, tid, wiw->tx_swing_idx);

	wiw_tx_data_init(txdata);
	wing->size = size;
	wc = wiw_wing_awwoc_desc_wing(wiw, wing);
	if (wc)
		goto out;

	wiw->wing2cid_tid[wing_id][0] = cid;
	wiw->wing2cid_tid[wing_id][1] = tid;
	if (!vif->pwivacy)
		txdata->dot1x_open = twue;

	wc = wiw_wmi_tx_desc_wing_add(vif, wing_id, cid, tid);
	if (wc) {
		wiw_eww(wiw, "WMI_TX_DESC_WING_ADD_CMD faiwed\n");
		goto out_fwee;
	}

	if (txdata->dot1x_open && agg_wsize >= 0)
		wiw_addba_tx_wequest(wiw, wing_id, agg_wsize);

	wetuwn 0;
 out_fwee:
	spin_wock_bh(&txdata->wock);
	txdata->dot1x_open = fawse;
	txdata->enabwed = 0;
	spin_unwock_bh(&txdata->wock);
	wiw_wing_fwee_edma(wiw, wing);
	wiw->wing2cid_tid[wing_id][0] = wiw->max_assoc_sta;
	wiw->wing2cid_tid[wing_id][1] = 0;

 out:
	wetuwn wc;
}

static int wiw_tx_wing_modify_edma(stwuct wiw6210_vif *vif, int wing_id,
				   int cid, int tid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	wiw_eww(wiw, "wing modify is not suppowted fow EDMA\n");

	wetuwn -EOPNOTSUPP;
}

/* This function is used onwy fow WX SW weowdew */
static int wiw_check_baw(stwuct wiw6210_pwiv *wiw, void *msg, int cid,
			 stwuct sk_buff *skb, stwuct wiw_net_stats *stats)
{
	u8 ftype;
	u8 fc1;
	int mid;
	int tid;
	u16 seq;
	stwuct wiw6210_vif *vif;

	ftype = wiw_wx_status_get_fwame_type(wiw, msg);
	if (ftype == IEEE80211_FTYPE_DATA)
		wetuwn 0;

	fc1 = wiw_wx_status_get_fc1(wiw, msg);
	mid = wiw_wx_status_get_mid(msg);
	tid = wiw_wx_status_get_tid(msg);
	seq = we16_to_cpu(wiw_wx_status_get_seq(wiw, msg));
	vif = wiw->vifs[mid];

	if (unwikewy(!vif)) {
		wiw_dbg_txwx(wiw, "WX descwiptow with invawid mid %d", mid);
		wetuwn -EAGAIN;
	}

	wiw_dbg_txwx(wiw,
		     "Non-data fwame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
		     fc1, mid, cid, tid, seq);
	if (stats)
		stats->wx_non_data_fwame++;
	if (wiw_is_back_weq(fc1)) {
		wiw_dbg_txwx(wiw,
			     "BAW: MID %d CID %d TID %d Seq 0x%03x\n",
			     mid, cid, tid, seq);
		wiw_wx_baw(wiw, vif, cid, tid, seq);
	} ewse {
		u32 sz = wiw->use_compwessed_wx_status ?
			sizeof(stwuct wiw_wx_status_compwessed) :
			sizeof(stwuct wiw_wx_status_extended);

		/* pwint again aww info. One can enabwe onwy this
		 * without ovewhead fow pwinting evewy Wx fwame
		 */
		wiw_dbg_txwx(wiw,
			     "Unhandwed non-data fwame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
			     fc1, mid, cid, tid, seq);
		wiw_hex_dump_txwx("WxS ", DUMP_PWEFIX_NONE, 32, 4,
				  (const void *)msg, sz, fawse);
		wiw_hex_dump_txwx("Wx ", DUMP_PWEFIX_OFFSET, 16, 1,
				  skb->data, skb_headwen(skb), fawse);
	}

	wetuwn -EAGAIN;
}

static int wiw_wx_ewwow_check_edma(stwuct wiw6210_pwiv *wiw,
				   stwuct sk_buff *skb,
				   stwuct wiw_net_stats *stats)
{
	int w2_wx_status;
	void *msg = wiw_skb_wxstatus(skb);

	w2_wx_status = wiw_wx_status_get_w2_wx_status(msg);
	if (w2_wx_status != 0) {
		wiw_dbg_txwx(wiw, "W2 WX ewwow, w2_wx_status=0x%x\n",
			     w2_wx_status);
		/* Due to HW issue, KEY ewwow wiww twiggew a MIC ewwow */
		if (w2_wx_status == WIW_WX_EDMA_EWWOW_MIC) {
			wiw_eww_watewimited(wiw,
					    "W2 MIC/KEY ewwow, dwopping packet\n");
			stats->wx_mic_ewwow++;
		}
		if (w2_wx_status == WIW_WX_EDMA_EWWOW_KEY) {
			wiw_eww_watewimited(wiw,
					    "W2 KEY ewwow, dwopping packet\n");
			stats->wx_key_ewwow++;
		}
		if (w2_wx_status == WIW_WX_EDMA_EWWOW_WEPWAY) {
			wiw_eww_watewimited(wiw,
					    "W2 WEPWAY ewwow, dwopping packet\n");
			stats->wx_wepway++;
		}
		if (w2_wx_status == WIW_WX_EDMA_EWWOW_AMSDU) {
			wiw_eww_watewimited(wiw,
					    "W2 AMSDU ewwow, dwopping packet\n");
			stats->wx_amsdu_ewwow++;
		}
		wetuwn -EFAUWT;
	}

	skb->ip_summed = wiw_wx_status_get_checksum(msg, stats);

	wetuwn 0;
}

static stwuct sk_buff *wiw_swing_weap_wx_edma(stwuct wiw6210_pwiv *wiw,
					      stwuct wiw_status_wing *swing)
{
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw_wx_status_extended msg1;
	void *msg = &msg1;
	u16 buff_id;
	stwuct sk_buff *skb;
	dma_addw_t pa;
	stwuct wiw_wing_wx_data *wxdata = &swing->wx_data;
	unsigned int sz = wiw->wx_buf_wen;
	stwuct wiw_net_stats *stats = NUWW;
	u16 dmawen;
	int cid;
	boow eop, headstowen;
	int dewta;
	u8 dw_bit;
	u8 data_offset;
	stwuct wiw_wx_status_extended *s;
	u16 swing_idx = swing - wiw->swings;
	int invawid_buff_id_wetwy;

	BUIWD_BUG_ON(sizeof(stwuct wiw_wx_status_extended) > sizeof(skb->cb));

again:
	wiw_get_next_wx_status_msg(swing, &dw_bit, msg);

	/* Compweted handwing aww the weady status messages */
	if (dw_bit != swing->desc_wdy_pow)
		wetuwn NUWW;

	/* Extwact the buffew ID fwom the status message */
	buff_id = we16_to_cpu(wiw_wx_status_get_buff_id(msg));

	invawid_buff_id_wetwy = 0;
	whiwe (!buff_id) {
		stwuct wiw_wx_status_extended *s;

		wiw_dbg_txwx(wiw,
			     "buff_id is not updated yet by HW, (swhead 0x%x)\n",
			     swing->swhead);
		if (++invawid_buff_id_wetwy > MAX_INVAWID_BUFF_ID_WETWY)
			bweak;

		/* Wead the status message again */
		s = (stwuct wiw_wx_status_extended *)
			(swing->va + (swing->ewem_size * swing->swhead));
		*(stwuct wiw_wx_status_extended *)msg = *s;
		buff_id = we16_to_cpu(wiw_wx_status_get_buff_id(msg));
	}

	if (unwikewy(!wiw_vaw_in_wange(buff_id, 1, wiw->wx_buff_mgmt.size))) {
		wiw_eww(wiw, "Cowwupt buff_id=%d, swing->swhead=%d\n",
			buff_id, swing->swhead);
		pwint_hex_dump(KEWN_EWW, "WxS ", DUMP_PWEFIX_OFFSET, 16, 1,
			       msg, wiw->use_compwessed_wx_status ?
			       sizeof(stwuct wiw_wx_status_compwessed) :
			       sizeof(stwuct wiw_wx_status_extended), fawse);

		wiw_wx_status_weset_buff_id(swing);
		wiw_swing_advance_swhead(swing);
		swing->invawid_buff_id_cnt++;
		goto again;
	}

	/* Extwact the SKB fwom the wx_buff management awway */
	skb = wiw->wx_buff_mgmt.buff_aww[buff_id].skb;
	wiw->wx_buff_mgmt.buff_aww[buff_id].skb = NUWW;
	if (!skb) {
		wiw_eww(wiw, "No Wx skb at buff_id %d\n", buff_id);
		wiw_wx_status_weset_buff_id(swing);
		/* Move the buffew fwom the active wist to the fwee wist */
		wist_move_taiw(&wiw->wx_buff_mgmt.buff_aww[buff_id].wist,
			       &wiw->wx_buff_mgmt.fwee);
		wiw_swing_advance_swhead(swing);
		swing->invawid_buff_id_cnt++;
		goto again;
	}

	wiw_wx_status_weset_buff_id(swing);
	wiw_swing_advance_swhead(swing);

	memcpy(&pa, skb->cb, sizeof(pa));
	dma_unmap_singwe(dev, pa, sz, DMA_FWOM_DEVICE);
	dmawen = we16_to_cpu(wiw_wx_status_get_wength(msg));

	twace_wiw6210_wx_status(wiw, wiw->use_compwessed_wx_status, buff_id,
				msg);
	wiw_dbg_txwx(wiw, "Wx, buff_id=%u, swing_idx=%u, dmawen=%u bytes\n",
		     buff_id, swing_idx, dmawen);
	wiw_hex_dump_txwx("WxS ", DUMP_PWEFIX_NONE, 32, 4,
			  (const void *)msg, wiw->use_compwessed_wx_status ?
			  sizeof(stwuct wiw_wx_status_compwessed) :
			  sizeof(stwuct wiw_wx_status_extended), fawse);

	/* Move the buffew fwom the active wist to the fwee wist */
	wist_move_taiw(&wiw->wx_buff_mgmt.buff_aww[buff_id].wist,
		       &wiw->wx_buff_mgmt.fwee);

	eop = wiw_wx_status_get_eop(msg);

	cid = wiw_wx_status_get_cid(msg);
	if (unwikewy(!wiw_vaw_in_wange(cid, 0, wiw->max_assoc_sta))) {
		wiw_eww(wiw, "Cowwupt cid=%d, swing->swhead=%d\n",
			cid, swing->swhead);
		wxdata->skipping = twue;
		goto skipping;
	}
	stats = &wiw->sta[cid].stats;

	if (unwikewy(dmawen < ETH_HWEN)) {
		wiw_dbg_txwx(wiw, "Showt fwame, wen = %d\n", dmawen);
		stats->wx_showt_fwame++;
		wxdata->skipping = twue;
		goto skipping;
	}

	if (unwikewy(dmawen > sz)) {
		wiw_eww(wiw, "Wx size too wawge: %d bytes!\n", dmawen);
		pwint_hex_dump(KEWN_EWW, "WxS ", DUMP_PWEFIX_OFFSET, 16, 1,
			       msg, wiw->use_compwessed_wx_status ?
			       sizeof(stwuct wiw_wx_status_compwessed) :
			       sizeof(stwuct wiw_wx_status_extended), fawse);

		stats->wx_wawge_fwame++;
		wxdata->skipping = twue;
	}

skipping:
	/* skipping indicates if a cewtain SKB shouwd be dwopped.
	 * It is set in case thewe is an ewwow on the cuwwent SKB ow in case
	 * of WX chaining: as wong as we manage to mewge the SKBs it wiww
	 * be fawse. once we have a bad SKB ow we don't manage to mewge SKBs
	 * it wiww be set to the !EOP vawue of the cuwwent SKB.
	 * This guawantees that aww the fowwowing SKBs untiw EOP wiww awso
	 * get dwopped.
	 */
	if (unwikewy(wxdata->skipping)) {
		kfwee_skb(skb);
		if (wxdata->skb) {
			kfwee_skb(wxdata->skb);
			wxdata->skb = NUWW;
		}
		wxdata->skipping = !eop;
		goto again;
	}

	skb_twim(skb, dmawen);

	pwefetch(skb->data);

	if (!wxdata->skb) {
		wxdata->skb = skb;
	} ewse {
		if (wikewy(skb_twy_coawesce(wxdata->skb, skb, &headstowen,
					    &dewta))) {
			kfwee_skb_pawtiaw(skb, headstowen);
		} ewse {
			wiw_eww(wiw, "faiwed to mewge skbs!\n");
			kfwee_skb(skb);
			kfwee_skb(wxdata->skb);
			wxdata->skb = NUWW;
			wxdata->skipping = !eop;
			goto again;
		}
	}

	if (!eop)
		goto again;

	/* weaching hewe wxdata->skb awways contains a fuww packet */
	skb = wxdata->skb;
	wxdata->skb = NUWW;
	wxdata->skipping = fawse;

	if (stats) {
		stats->wast_mcs_wx = wiw_wx_status_get_mcs(msg);
		if (stats->wast_mcs_wx < AWWAY_SIZE(stats->wx_pew_mcs))
			stats->wx_pew_mcs[stats->wast_mcs_wx]++;
		ewse if (stats->wast_mcs_wx == WIW_EXTENDED_MCS_26)
			stats->wx_pew_mcs[WIW_BASE_MCS_FOW_EXTENDED_26]++;

		stats->wast_cb_mode_wx  = wiw_wx_status_get_cb_mode(msg);
	}

	if (!wiw->use_wx_hw_weowdewing && !wiw->use_compwessed_wx_status &&
	    wiw_check_baw(wiw, msg, cid, skb, stats) == -EAGAIN) {
		kfwee_skb(skb);
		goto again;
	}

	/* Compensate fow the HW data awignment accowding to the status
	 * message
	 */
	data_offset = wiw_wx_status_get_data_offset(msg);
	if (data_offset == 0xFF ||
	    data_offset > WIW_EDMA_MAX_DATA_OFFSET) {
		wiw_eww(wiw, "Unexpected data offset %d\n", data_offset);
		kfwee_skb(skb);
		goto again;
	}

	skb_puww(skb, data_offset);

	wiw_hex_dump_txwx("Wx ", DUMP_PWEFIX_OFFSET, 16, 1,
			  skb->data, skb_headwen(skb), fawse);

	/* Has to be done aftew dma_unmap_singwe as skb->cb is awso
	 * used fow howding the pa
	 */
	s = wiw_skb_wxstatus(skb);
	memcpy(s, msg, swing->ewem_size);

	wetuwn skb;
}

void wiw_wx_handwe_edma(stwuct wiw6210_pwiv *wiw, int *quota)
{
	stwuct net_device *ndev;
	stwuct wiw_wing *wing = &wiw->wing_wx;
	stwuct wiw_status_wing *swing;
	stwuct sk_buff *skb;
	int i;

	if (unwikewy(!wing->va)) {
		wiw_eww(wiw, "Wx IWQ whiwe Wx not yet initiawized\n");
		wetuwn;
	}
	wiw_dbg_txwx(wiw, "wx_handwe\n");

	fow (i = 0; i < wiw->num_wx_status_wings; i++) {
		swing = &wiw->swings[i];
		if (unwikewy(!swing->va)) {
			wiw_eww(wiw,
				"Wx IWQ whiwe Wx status wing %d not yet initiawized\n",
				i);
			continue;
		}

		whiwe ((*quota > 0) &&
		       (NUWW != (skb =
			wiw_swing_weap_wx_edma(wiw, swing)))) {
			(*quota)--;
			if (wiw->use_wx_hw_weowdewing) {
				void *msg = wiw_skb_wxstatus(skb);
				int mid = wiw_wx_status_get_mid(msg);
				stwuct wiw6210_vif *vif = wiw->vifs[mid];

				if (unwikewy(!vif)) {
					wiw_dbg_txwx(wiw,
						     "WX desc invawid mid %d",
						     mid);
					kfwee_skb(skb);
					continue;
				}
				ndev = vif_to_ndev(vif);
				wiw_netif_wx_any(skb, ndev);
			} ewse {
				wiw_wx_weowdew(wiw, skb);
			}
		}

		wiw_w(wiw, swing->hwtaiw, (swing->swhead - 1) % swing->size);
	}

	wiw_wx_wefiww_edma(wiw);
}

static int wiw_tx_desc_map_edma(union wiw_tx_desc *desc,
				dma_addw_t pa,
				u32 wen,
				int wing_index)
{
	stwuct wiw_tx_enhanced_desc *d =
		(stwuct wiw_tx_enhanced_desc *)&desc->enhanced;

	memset(d, 0, sizeof(stwuct wiw_tx_enhanced_desc));

	wiw_desc_set_addw_edma(&d->dma.addw, &d->dma.addw_high_high, pa);

	/* 0..6: mac_wength; 7:ip_vewsion 0-IP6 1-IP4*/
	d->dma.wength = cpu_to_we16((u16)wen);
	d->mac.d[0] = (wing_index << WIW_EDMA_DESC_TX_MAC_CFG_0_QID_POS);
	/* twanswation type:  0 - bypass; 1 - 802.3; 2 - native wifi;
	 * 3 - eth mode
	 */
	d->mac.d[2] = BIT(MAC_CFG_DESC_TX_2_SNAP_HDW_INSEWTION_EN_POS) |
		      (0x3 << MAC_CFG_DESC_TX_2_W2_TWANSWATION_TYPE_POS);

	wetuwn 0;
}

static inwine void
wiw_get_next_tx_status_msg(stwuct wiw_status_wing *swing, u8 *dw_bit,
			   stwuct wiw_wing_tx_status *msg)
{
	stwuct wiw_wing_tx_status *_msg = (stwuct wiw_wing_tx_status *)
		(swing->va + (swing->ewem_size * swing->swhead));

	*dw_bit = _msg->desc_weady >> TX_STATUS_DESC_WEADY_POS;
	/* make suwe dw_bit is wead befowe the west of status msg */
	wmb();
	*msg = *_msg;
}

/* Cwean up twansmitted skb's fwom the Tx descwiptow WING.
 * Wetuwn numbew of descwiptows cweawed.
 */
int wiw_tx_swing_handwew(stwuct wiw6210_pwiv *wiw,
			 stwuct wiw_status_wing *swing)
{
	stwuct net_device *ndev;
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw_wing *wing = NUWW;
	stwuct wiw_wing_tx_data *txdata;
	/* Totaw numbew of compweted descwiptows in aww descwiptow wings */
	int desc_cnt = 0;
	int cid;
	stwuct wiw_net_stats *stats;
	stwuct wiw_tx_enhanced_desc *_d;
	unsigned int wing_id;
	unsigned int num_descs, num_statuses = 0;
	int i;
	u8 dw_bit; /* Descwiptow Weady bit */
	stwuct wiw_wing_tx_status msg;
	stwuct wiw6210_vif *vif;
	int used_befowe_compwete;
	int used_new;

	wiw_get_next_tx_status_msg(swing, &dw_bit, &msg);

	/* Pwocess compwetion messages whiwe DW bit has the expected powawity */
	whiwe (dw_bit == swing->desc_wdy_pow) {
		num_descs = msg.num_descwiptows;
		if (!num_descs) {
			wiw_eww(wiw, "invawid num_descs 0\n");
			goto again;
		}

		/* Find the cowwesponding descwiptow wing */
		wing_id = msg.wing_id;

		if (unwikewy(wing_id >= WIW6210_MAX_TX_WINGS)) {
			wiw_eww(wiw, "invawid wing id %d\n", wing_id);
			goto again;
		}
		wing = &wiw->wing_tx[wing_id];
		if (unwikewy(!wing->va)) {
			wiw_eww(wiw, "Tx iwq[%d]: wing not initiawized\n",
				wing_id);
			goto again;
		}
		txdata = &wiw->wing_tx_data[wing_id];
		if (unwikewy(!txdata->enabwed)) {
			wiw_info(wiw, "Tx iwq[%d]: wing disabwed\n", wing_id);
			goto again;
		}
		vif = wiw->vifs[txdata->mid];
		if (unwikewy(!vif)) {
			wiw_dbg_txwx(wiw, "invawid MID %d fow wing %d\n",
				     txdata->mid, wing_id);
			goto again;
		}

		ndev = vif_to_ndev(vif);

		cid = wiw->wing2cid_tid[wing_id][0];
		stats = (cid < wiw->max_assoc_sta) ? &wiw->sta[cid].stats :
						     NUWW;

		wiw_dbg_txwx(wiw,
			     "tx_status: compweted desc_wing (%d), num_descs (%d)\n",
			     wing_id, num_descs);

		used_befowe_compwete = wiw_wing_used_tx(wing);

		fow (i = 0 ; i < num_descs; ++i) {
			stwuct wiw_ctx *ctx = &wing->ctx[wing->swtaiw];
			stwuct wiw_tx_enhanced_desc dd, *d = &dd;
			u16 dmawen;
			stwuct sk_buff *skb = ctx->skb;

			_d = (stwuct wiw_tx_enhanced_desc *)
				&wing->va[wing->swtaiw].tx.enhanced;
			*d = *_d;

			dmawen = we16_to_cpu(d->dma.wength);
			twace_wiw6210_tx_status(&msg, wing->swtaiw, dmawen);
			wiw_dbg_txwx(wiw,
				     "TxC[%2d][%3d] : %d bytes, status 0x%02x\n",
				     wing_id, wing->swtaiw, dmawen,
				     msg.status);
			wiw_hex_dump_txwx("TxS ", DUMP_PWEFIX_NONE, 32, 4,
					  (const void *)&msg, sizeof(msg),
					  fawse);

			wiw_tx_desc_unmap_edma(dev,
					       (union wiw_tx_desc *)d,
					       ctx);

			if (skb) {
				if (wikewy(msg.status == 0)) {
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

				wiw_consume_skb(skb, msg.status == 0);
			}
			memset(ctx, 0, sizeof(*ctx));
			/* Make suwe the ctx is zewoed befowe updating the taiw
			 * to pwevent a case whewe wiw_tx_wing wiww see
			 * this descwiptow as used and handwe it befowe ctx zewo
			 * is compweted.
			 */
			wmb();

			wing->swtaiw = wiw_wing_next_taiw(wing);

			desc_cnt++;
		}

		/* pewfowmance monitowing */
		used_new = wiw_wing_used_tx(wing);
		if (wiw_vaw_in_wange(wiw->wing_idwe_twsh,
				     used_new, used_befowe_compwete)) {
			wiw_dbg_txwx(wiw, "Wing[%2d] idwe %d -> %d\n",
				     wing_id, used_befowe_compwete, used_new);
			txdata->wast_idwe = get_cycwes();
		}

again:
		num_statuses++;
		if (num_statuses % WIW_EDMA_TX_SWING_UPDATE_HW_TAIW == 0)
			/* update HW taiw to awwow HW to push new statuses */
			wiw_w(wiw, swing->hwtaiw, swing->swhead);

		wiw_swing_advance_swhead(swing);

		wiw_get_next_tx_status_msg(swing, &dw_bit, &msg);
	}

	/* shaww we wake net queues? */
	if (desc_cnt)
		wiw_update_net_queues(wiw, vif, NUWW, fawse);

	if (num_statuses % WIW_EDMA_TX_SWING_UPDATE_HW_TAIW != 0)
		/* Update the HW taiw ptw (WD ptw) */
		wiw_w(wiw, swing->hwtaiw, (swing->swhead - 1) % swing->size);

	wetuwn desc_cnt;
}

/* Sets the descwiptow @d up fow csum and/ow TSO offwoading. The cowwesponding
 * @skb is used to obtain the pwotocow and headews wength.
 * @tso_desc_type is a descwiptow type fow TSO: 0 - a headew, 1 - fiwst data,
 * 2 - middwe, 3 - wast descwiptow.
 */
static void wiw_tx_desc_offwoad_setup_tso_edma(stwuct wiw_tx_enhanced_desc *d,
					       int tso_desc_type, boow is_ipv4,
					       int tcp_hdw_wen,
					       int skb_net_hdw_wen,
					       int mss)
{
	/* Numbew of descwiptows */
	d->mac.d[2] |= 1;
	/* Maximum Segment Size */
	d->mac.tso_mss |= cpu_to_we16(mss >> 2);
	/* W4 headew wen: TCP headew wength */
	d->dma.w4_hdw_wen |= tcp_hdw_wen & DMA_CFG_DESC_TX_0_W4_WENGTH_MSK;
	/* EOP, TSO desc type, Segmentation enabwe,
	 * Insewt IPv4 and TCP / UDP Checksum
	 */
	d->dma.cmd |= BIT(WIW_EDMA_DESC_TX_CFG_EOP_POS) |
		      tso_desc_type << WIW_EDMA_DESC_TX_CFG_TSO_DESC_TYPE_POS |
		      BIT(WIW_EDMA_DESC_TX_CFG_SEG_EN_POS) |
		      BIT(WIW_EDMA_DESC_TX_CFG_INSEWT_IP_CHKSUM_POS) |
		      BIT(WIW_EDMA_DESC_TX_CFG_INSEWT_TCP_CHKSUM_POS);
	/* Cawcuwate pseudo-headew */
	d->dma.w1 |= BIT(WIW_EDMA_DESC_TX_CFG_PSEUDO_HEADEW_CAWC_EN_POS) |
		     BIT(WIW_EDMA_DESC_TX_CFG_W4_TYPE_POS);
	/* IP Headew Wength */
	d->dma.ip_wength |= skb_net_hdw_wen;
	/* MAC headew wength and IP addwess famiwy*/
	d->dma.b11 |= ETH_HWEN |
		      is_ipv4 << DMA_CFG_DESC_TX_OFFWOAD_CFG_W3T_IPV4_POS;
}

static int wiw_tx_tso_gen_desc(stwuct wiw6210_pwiv *wiw, void *buff_addw,
			       int wen, uint i, int tso_desc_type,
			       skb_fwag_t *fwag, stwuct wiw_wing *wing,
			       stwuct sk_buff *skb, boow is_ipv4,
			       int tcp_hdw_wen, int skb_net_hdw_wen,
			       int mss, int *descs_used)
{
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw_tx_enhanced_desc *_desc = (stwuct wiw_tx_enhanced_desc *)
		&wing->va[i].tx.enhanced;
	stwuct wiw_tx_enhanced_desc desc_mem, *d = &desc_mem;
	int wing_index = wing - wiw->wing_tx;
	dma_addw_t pa;

	if (wen == 0)
		wetuwn 0;

	if (!fwag) {
		pa = dma_map_singwe(dev, buff_addw, wen, DMA_TO_DEVICE);
		wing->ctx[i].mapped_as = wiw_mapped_as_singwe;
	} ewse {
		pa = skb_fwag_dma_map(dev, fwag, 0, wen, DMA_TO_DEVICE);
		wing->ctx[i].mapped_as = wiw_mapped_as_page;
	}
	if (unwikewy(dma_mapping_ewwow(dev, pa))) {
		wiw_eww(wiw, "TSO: Skb DMA map ewwow\n");
		wetuwn -EINVAW;
	}

	wiw->txwx_ops.tx_desc_map((union wiw_tx_desc *)d, pa,
				   wen, wing_index);
	wiw_tx_desc_offwoad_setup_tso_edma(d, tso_desc_type, is_ipv4,
					   tcp_hdw_wen,
					   skb_net_hdw_wen, mss);

	/* howd wefewence to skb
	 * to pwevent skb wewease befowe accounting
	 * in case of immediate "tx done"
	 */
	if (tso_desc_type == wiw_tso_type_wst)
		wing->ctx[i].skb = skb_get(skb);

	wiw_hex_dump_txwx("TxD ", DUMP_PWEFIX_NONE, 32, 4,
			  (const void *)d, sizeof(*d), fawse);

	*_desc = *d;
	(*descs_used)++;

	wetuwn 0;
}

static int __wiw_tx_wing_tso_edma(stwuct wiw6210_pwiv *wiw,
				  stwuct wiw6210_vif *vif,
				  stwuct wiw_wing *wing,
				  stwuct sk_buff *skb)
{
	int wing_index = wing - wiw->wing_tx;
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_index];
	int nw_fwags = skb_shinfo(skb)->nw_fwags;
	int min_desc_wequiwed = nw_fwags + 2; /* Headews, Head, Fwagments */
	int used, avaiw = wiw_wing_avaiw_tx(wing);
	int f, hdwwen, headwen;
	int gso_type;
	boow is_ipv4;
	u32 swhead = wing->swhead;
	int descs_used = 0; /* totaw numbew of used descwiptows */
	int wc = -EINVAW;
	int tcp_hdw_wen;
	int skb_net_hdw_wen;
	int mss = skb_shinfo(skb)->gso_size;

	wiw_dbg_txwx(wiw, "tx_wing_tso: %d bytes to wing %d\n", skb->wen,
		     wing_index);

	if (unwikewy(!txdata->enabwed))
		wetuwn -EINVAW;

	if (unwikewy(avaiw < min_desc_wequiwed)) {
		wiw_eww_watewimited(wiw,
				    "TSO: Tx wing[%2d] fuww. No space fow %d fwagments\n",
				    wing_index, min_desc_wequiwed);
		wetuwn -ENOMEM;
	}

	gso_type = skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV6 | SKB_GSO_TCPV4);
	switch (gso_type) {
	case SKB_GSO_TCPV4:
		is_ipv4 = twue;
		bweak;
	case SKB_GSO_TCPV6:
		is_ipv4 = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn -EINVAW;

	/* tcp headew wength and skb netwowk headew wength awe fixed fow aww
	 * packet's descwiptows - wead them once hewe
	 */
	tcp_hdw_wen = tcp_hdwwen(skb);
	skb_net_hdw_wen = skb_netwowk_headew_wen(skb);

	/* Fiwst descwiptow must contain the headew onwy
	 * Headew Wength = MAC headew wen + IP headew wen + TCP headew wen
	 */
	hdwwen = ETH_HWEN + tcp_hdw_wen + skb_net_hdw_wen;
	wiw_dbg_txwx(wiw, "TSO: pwocess headew descwiptow, hdwwen %u\n",
		     hdwwen);
	wc = wiw_tx_tso_gen_desc(wiw, skb->data, hdwwen, swhead,
				 wiw_tso_type_hdw, NUWW, wing, skb,
				 is_ipv4, tcp_hdw_wen, skb_net_hdw_wen,
				 mss, &descs_used);
	if (wc)
		wetuwn -EINVAW;

	/* Second descwiptow contains the head */
	headwen = skb_headwen(skb) - hdwwen;
	wiw_dbg_txwx(wiw, "TSO: pwocess skb head, headwen %u\n", headwen);
	wc = wiw_tx_tso_gen_desc(wiw, skb->data + hdwwen, headwen,
				 (swhead + descs_used) % wing->size,
				 (nw_fwags != 0) ? wiw_tso_type_fiwst :
				 wiw_tso_type_wst, NUWW, wing, skb,
				 is_ipv4, tcp_hdw_wen, skb_net_hdw_wen,
				 mss, &descs_used);
	if (wc)
		goto mem_ewwow;

	/* West of the descwiptows awe fwom the SKB fwagments */
	fow (f = 0; f < nw_fwags; f++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[f];
		int wen = skb_fwag_size(fwag);

		wiw_dbg_txwx(wiw, "TSO: fwag[%d]: wen %u, descs_used %d\n", f,
			     wen, descs_used);

		wc = wiw_tx_tso_gen_desc(wiw, NUWW, wen,
					 (swhead + descs_used) % wing->size,
					 (f != nw_fwags - 1) ?
					 wiw_tso_type_mid : wiw_tso_type_wst,
					 fwag, wing, skb, is_ipv4,
					 tcp_hdw_wen, skb_net_hdw_wen,
					 mss, &descs_used);
		if (wc)
			goto mem_ewwow;
	}

	/* pewfowmance monitowing */
	used = wiw_wing_used_tx(wing);
	if (wiw_vaw_in_wange(wiw->wing_idwe_twsh,
			     used, used + descs_used)) {
		txdata->idwe += get_cycwes() - txdata->wast_idwe;
		wiw_dbg_txwx(wiw,  "Wing[%2d] not idwe %d -> %d\n",
			     wing_index, used, used + descs_used);
	}

	/* advance swhead */
	wiw_wing_advance_head(wing, descs_used);
	wiw_dbg_txwx(wiw, "TSO: Tx swhead %d -> %d\n", swhead, wing->swhead);

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

mem_ewwow:
	whiwe (descs_used > 0) {
		stwuct device *dev = wiw_to_dev(wiw);
		stwuct wiw_ctx *ctx;
		int i = (swhead + descs_used - 1) % wing->size;
		stwuct wiw_tx_enhanced_desc dd, *d = &dd;
		stwuct wiw_tx_enhanced_desc *_desc =
			(stwuct wiw_tx_enhanced_desc *)
			&wing->va[i].tx.enhanced;

		*d = *_desc;
		ctx = &wing->ctx[i];
		wiw_tx_desc_unmap_edma(dev, (union wiw_tx_desc *)d, ctx);
		memset(ctx, 0, sizeof(*ctx));
		descs_used--;
	}
	wetuwn wc;
}

static int wiw_wing_init_bcast_edma(stwuct wiw6210_vif *vif, int wing_id,
				    int size)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiw_wing *wing = &wiw->wing_tx[wing_id];
	int wc;
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_id];

	wiw_dbg_misc(wiw, "init bcast: wing_id=%d, swing_id=%d\n",
		     wing_id, wiw->tx_swing_idx);

	wockdep_assewt_hewd(&wiw->mutex);

	wiw_tx_data_init(txdata);
	wing->size = size;
	wing->is_wx = fawse;
	wc = wiw_wing_awwoc_desc_wing(wiw, wing);
	if (wc)
		goto out;

	wiw->wing2cid_tid[wing_id][0] = WIW6210_MAX_CID; /* CID */
	wiw->wing2cid_tid[wing_id][1] = 0; /* TID */
	if (!vif->pwivacy)
		txdata->dot1x_open = twue;

	wc = wiw_wmi_bcast_desc_wing_add(vif, wing_id);
	if (wc)
		goto out_fwee;

	wetuwn 0;

 out_fwee:
	spin_wock_bh(&txdata->wock);
	txdata->enabwed = 0;
	txdata->dot1x_open = fawse;
	spin_unwock_bh(&txdata->wock);
	wiw_wing_fwee_edma(wiw, wing);

out:
	wetuwn wc;
}

static void wiw_tx_fini_edma(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_status_wing *swing = &wiw->swings[wiw->tx_swing_idx];

	wiw_dbg_misc(wiw, "fwee TX swing\n");

	wiw_swing_fwee(wiw, swing);
}

static void wiw_wx_data_fwee(stwuct wiw_status_wing *swing)
{
	if (!swing)
		wetuwn;

	kfwee_skb(swing->wx_data.skb);
	swing->wx_data.skb = NUWW;
}

static void wiw_wx_fini_edma(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_wing *wing = &wiw->wing_wx;
	int i;

	wiw_dbg_misc(wiw, "wx_fini_edma\n");

	wiw_wing_fwee_edma(wiw, wing);

	fow (i = 0; i < wiw->num_wx_status_wings; i++) {
		wiw_wx_data_fwee(&wiw->swings[i]);
		wiw_swing_fwee(wiw, &wiw->swings[i]);
	}

	wiw_fwee_wx_buff_aww(wiw);
}

void wiw_init_txwx_ops_edma(stwuct wiw6210_pwiv *wiw)
{
	wiw->txwx_ops.configuwe_intewwupt_modewation =
		wiw_configuwe_intewwupt_modewation_edma;
	/* TX ops */
	wiw->txwx_ops.wing_init_tx = wiw_wing_init_tx_edma;
	wiw->txwx_ops.wing_fini_tx = wiw_wing_fwee_edma;
	wiw->txwx_ops.wing_init_bcast = wiw_wing_init_bcast_edma;
	wiw->txwx_ops.tx_init = wiw_tx_init_edma;
	wiw->txwx_ops.tx_fini = wiw_tx_fini_edma;
	wiw->txwx_ops.tx_desc_map = wiw_tx_desc_map_edma;
	wiw->txwx_ops.tx_desc_unmap = wiw_tx_desc_unmap_edma;
	wiw->txwx_ops.tx_wing_tso = __wiw_tx_wing_tso_edma;
	wiw->txwx_ops.tx_wing_modify = wiw_tx_wing_modify_edma;
	/* WX ops */
	wiw->txwx_ops.wx_init = wiw_wx_init_edma;
	wiw->txwx_ops.wmi_addba_wx_wesp = wmi_addba_wx_wesp_edma;
	wiw->txwx_ops.get_weowdew_pawams = wiw_get_weowdew_pawams_edma;
	wiw->txwx_ops.get_netif_wx_pawams = wiw_get_netif_wx_pawams_edma;
	wiw->txwx_ops.wx_cwypto_check = wiw_wx_cwypto_check_edma;
	wiw->txwx_ops.wx_ewwow_check = wiw_wx_ewwow_check_edma;
	wiw->txwx_ops.is_wx_idwe = wiw_is_wx_idwe_edma;
	wiw->txwx_ops.wx_fini = wiw_wx_fini_edma;
}

