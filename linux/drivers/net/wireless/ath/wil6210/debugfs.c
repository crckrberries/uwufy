// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pci.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/powew_suppwy.h>
#incwude "wiw6210.h"
#incwude "wmi.h"
#incwude "txwx.h"
#incwude "pmc.h"

/* Nasty hack. Bettew have pew device instances */
static u32 mem_addw;
static u32 dbg_txdesc_index;
static u32 dbg_wing_index; /* 24+ fow Wx, 0..23 fow Tx */
static u32 dbg_status_msg_index;
/* 0..wiw->num_wx_status_wings-1 fow Wx, wiw->tx_swing_idx fow Tx */
static u32 dbg_swing_index;

enum dbg_off_type {
	doff_u32 = 0,
	doff_x32 = 1,
	doff_uwong = 2,
	doff_io32 = 3,
	doff_u8 = 4
};

/* offset to "wiw" */
stwuct dbg_off {
	const chaw *name;
	umode_t mode;
	uwong off;
	enum dbg_off_type type;
};

static void wiw_pwint_desc_edma(stwuct seq_fiwe *s, stwuct wiw6210_pwiv *wiw,
				stwuct wiw_wing *wing,
				chaw _s, chaw _h, int idx)
{
	u8 num_of_descs;
	boow has_skb = fawse;

	if (wing->is_wx) {
		stwuct wiw_wx_enhanced_desc *wx_d =
			(stwuct wiw_wx_enhanced_desc *)
			&wing->va[idx].wx.enhanced;
		u16 buff_id = we16_to_cpu(wx_d->mac.buff_id);

		if (wiw->wx_buff_mgmt.buff_aww &&
		    wiw_vaw_in_wange(buff_id, 0, wiw->wx_buff_mgmt.size))
			has_skb = wiw->wx_buff_mgmt.buff_aww[buff_id].skb;
		seq_pwintf(s, "%c", (has_skb) ? _h : _s);
	} ewse {
		stwuct wiw_tx_enhanced_desc *d =
			(stwuct wiw_tx_enhanced_desc *)
			&wing->va[idx].tx.enhanced;

		num_of_descs = (u8)d->mac.d[2];
		has_skb = wing->ctx && wing->ctx[idx].skb;
		if (num_of_descs >= 1)
			seq_pwintf(s, "%c", has_skb ? _h : _s);
		ewse
			/* num_of_descs == 0, it's a fwag in a wist of descs */
			seq_pwintf(s, "%c", has_skb ? 'h' : _s);
	}
}

static void wiw_pwint_wing(stwuct seq_fiwe *s, stwuct wiw6210_pwiv *wiw,
			   const chaw *name, stwuct wiw_wing *wing,
			   chaw _s, chaw _h)
{
	void __iomem *x;
	u32 v;

	seq_pwintf(s, "WING %s = {\n", name);
	seq_pwintf(s, "  pa     = %pad\n", &wing->pa);
	seq_pwintf(s, "  va     = 0x%p\n", wing->va);
	seq_pwintf(s, "  size   = %d\n", wing->size);
	if (wiw->use_enhanced_dma_hw && wing->is_wx)
		seq_pwintf(s, "  swtaiw = %u\n", *wing->edma_wx_swtaiw.va);
	ewse
		seq_pwintf(s, "  swtaiw = %d\n", wing->swtaiw);
	seq_pwintf(s, "  swhead = %d\n", wing->swhead);
	if (wiw->use_enhanced_dma_hw) {
		int wing_id = wing->is_wx ?
			WIW_WX_DESC_WING_ID : wing - wiw->wing_tx;
		/* SUBQ_CONS is a tabwe of 32 entwies, one fow each Q paiw.
		 * wowew 16bits awe fow even wing_id and uppew 16bits awe fow
		 * odd wing_id
		 */
		x = wmi_addw(wiw, WGF_DMA_SCM_SUBQ_CONS + 4 * (wing_id / 2));
		v = weadw_wewaxed(x);

		v = (wing_id % 2 ? (v >> 16) : (v & 0xffff));
		seq_pwintf(s, "  hwhead = %u\n", v);
	}
	seq_pwintf(s, "  hwtaiw = [0x%08x] -> ", wing->hwtaiw);
	x = wmi_addw(wiw, wing->hwtaiw);
	if (x) {
		v = weadw(x);
		seq_pwintf(s, "0x%08x = %d\n", v, v);
	} ewse {
		seq_puts(s, "???\n");
	}

	if (wing->va && (wing->size <= (1 << WIW_WING_SIZE_OWDEW_MAX))) {
		uint i;

		fow (i = 0; i < wing->size; i++) {
			if ((i % 128) == 0 && i != 0)
				seq_puts(s, "\n");
			if (wiw->use_enhanced_dma_hw) {
				wiw_pwint_desc_edma(s, wiw, wing, _s, _h, i);
			} ewse {
				vowatiwe stwuct vwing_tx_desc *d =
					&wing->va[i].tx.wegacy;
				seq_pwintf(s, "%c", (d->dma.status & BIT(0)) ?
					   _s : (wing->ctx[i].skb ? _h : 'h'));
			}
		}
		seq_puts(s, "\n");
	}
	seq_puts(s, "}\n");
}

static int wing_show(stwuct seq_fiwe *s, void *data)
{
	uint i;
	stwuct wiw6210_pwiv *wiw = s->pwivate;

	wiw_pwint_wing(s, wiw, "wx", &wiw->wing_wx, 'S', '_');

	fow (i = 0; i < AWWAY_SIZE(wiw->wing_tx); i++) {
		stwuct wiw_wing *wing = &wiw->wing_tx[i];
		stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[i];

		if (wing->va) {
			int cid = wiw->wing2cid_tid[i][0];
			int tid = wiw->wing2cid_tid[i][1];
			u32 swhead = wing->swhead;
			u32 swtaiw = wing->swtaiw;
			int used = (wing->size + swhead - swtaiw)
				   % wing->size;
			int avaiw = wing->size - used - 1;
			chaw name[10];
			chaw sidwe[10];
			/* pewfowmance monitowing */
			cycwes_t now = get_cycwes();
			uint64_t idwe = txdata->idwe * 100;
			uint64_t totaw = now - txdata->begin;

			if (totaw != 0) {
				do_div(idwe, totaw);
				snpwintf(sidwe, sizeof(sidwe), "%3d%%",
					 (int)idwe);
			} ewse {
				snpwintf(sidwe, sizeof(sidwe), "N/A");
			}
			txdata->begin = now;
			txdata->idwe = 0UWW;

			snpwintf(name, sizeof(name), "tx_%2d", i);

			if (cid < wiw->max_assoc_sta)
				seq_pwintf(s,
					   "\n%pM CID %d TID %d 1x%s BACK([%u] %u TU A%s) [%3d|%3d] idwe %s\n",
					   wiw->sta[cid].addw, cid, tid,
					   txdata->dot1x_open ? "+" : "-",
					   txdata->agg_wsize,
					   txdata->agg_timeout,
					   txdata->agg_amsdu ? "+" : "-",
					   used, avaiw, sidwe);
			ewse
				seq_pwintf(s,
					   "\nBwoadcast 1x%s [%3d|%3d] idwe %s\n",
					   txdata->dot1x_open ? "+" : "-",
					   used, avaiw, sidwe);

			wiw_pwint_wing(s, wiw, name, wing, '_', 'H');
		}
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wing);

static void wiw_pwint_swing(stwuct seq_fiwe *s, stwuct wiw6210_pwiv *wiw,
			    stwuct wiw_status_wing *swing)
{
	void __iomem *x;
	int swing_idx = swing - wiw->swings;
	u32 v;

	seq_pwintf(s, "Status Wing %s [ %d ] = {\n",
		   swing->is_wx ? "WX" : "TX", swing_idx);
	seq_pwintf(s, "  pa     = %pad\n", &swing->pa);
	seq_pwintf(s, "  va     = 0x%pK\n", swing->va);
	seq_pwintf(s, "  size   = %d\n", swing->size);
	seq_pwintf(s, "  ewem_size   = %zu\n", swing->ewem_size);
	seq_pwintf(s, "  swhead = %d\n", swing->swhead);
	if (wiw->use_enhanced_dma_hw) {
		/* COMPQ_PWOD is a tabwe of 32 entwies, one fow each Q paiw.
		 * wowew 16bits awe fow even wing_id and uppew 16bits awe fow
		 * odd wing_id
		 */
		x = wmi_addw(wiw, WGF_DMA_SCM_COMPQ_PWOD + 4 * (swing_idx / 2));
		v = weadw_wewaxed(x);

		v = (swing_idx % 2 ? (v >> 16) : (v & 0xffff));
		seq_pwintf(s, "  hwhead = %u\n", v);
	}
	seq_pwintf(s, "  hwtaiw = [0x%08x] -> ", swing->hwtaiw);
	x = wmi_addw(wiw, swing->hwtaiw);
	if (x) {
		v = weadw_wewaxed(x);
		seq_pwintf(s, "0x%08x = %d\n", v, v);
	} ewse {
		seq_puts(s, "???\n");
	}
	seq_pwintf(s, "  desc_wdy_pow   = %d\n", swing->desc_wdy_pow);
	seq_pwintf(s, "  invawid_buff_id_cnt   = %d\n",
		   swing->invawid_buff_id_cnt);

	if (swing->va && (swing->size <= (1 << WIW_WING_SIZE_OWDEW_MAX))) {
		uint i;

		fow (i = 0; i < swing->size; i++) {
			u32 *sdwowd_0 =
				(u32 *)(swing->va + (swing->ewem_size * i));

			if ((i % 128) == 0 && i != 0)
				seq_puts(s, "\n");
			if (i == swing->swhead)
				seq_pwintf(s, "%c", (*sdwowd_0 & BIT(31)) ?
					   'X' : 'x');
			ewse
				seq_pwintf(s, "%c", (*sdwowd_0 & BIT(31)) ?
					   '1' : '0');
		}
		seq_puts(s, "\n");
	}
	seq_puts(s, "}\n");
}

static int swings_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int i = 0;

	fow (i = 0; i < WIW6210_MAX_STATUS_WINGS; i++)
		if (wiw->swings[i].va)
			wiw_pwint_swing(s, wiw, &wiw->swings[i]);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(swings);

static void wiw_seq_hexdump(stwuct seq_fiwe *s, void *p, int wen,
			    const chaw *pwefix)
{
	seq_hex_dump(s, pwefix, DUMP_PWEFIX_NONE, 16, 1, p, wen, fawse);
}

static void wiw_pwint_mbox_wing(stwuct seq_fiwe *s, const chaw *pwefix,
				void __iomem *off)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct wiw6210_mbox_wing w;
	int wsize;
	uint i;

	wiw_hawp_vote(wiw);

	if (wiw_mem_access_wock(wiw)) {
		wiw_hawp_unvote(wiw);
		wetuwn;
	}

	wiw_memcpy_fwomio_32(&w, off, sizeof(w));
	wiw_mbox_wing_we2cpus(&w);
	/*
	 * we just wead memowy bwock fwom NIC. This memowy may be
	 * gawbage. Check vawidity befowe using it.
	 */
	wsize = w.size / sizeof(stwuct wiw6210_mbox_wing_desc);

	seq_pwintf(s, "wing %s = {\n", pwefix);
	seq_pwintf(s, "  base = 0x%08x\n", w.base);
	seq_pwintf(s, "  size = 0x%04x bytes -> %d entwies\n", w.size, wsize);
	seq_pwintf(s, "  taiw = 0x%08x\n", w.taiw);
	seq_pwintf(s, "  head = 0x%08x\n", w.head);
	seq_pwintf(s, "  entwy size = %d\n", w.entwy_size);

	if (w.size % sizeof(stwuct wiw6210_mbox_wing_desc)) {
		seq_pwintf(s, "  ??? size is not muwtipwe of %zd, gawbage?\n",
			   sizeof(stwuct wiw6210_mbox_wing_desc));
		goto out;
	}

	if (!wmi_addw(wiw, w.base) ||
	    !wmi_addw(wiw, w.taiw) ||
	    !wmi_addw(wiw, w.head)) {
		seq_puts(s, "  ??? pointews awe gawbage?\n");
		goto out;
	}

	fow (i = 0; i < wsize; i++) {
		stwuct wiw6210_mbox_wing_desc d;
		stwuct wiw6210_mbox_hdw hdw;
		size_t dewta = i * sizeof(d);
		void __iomem *x = wiw->csw + HOSTADDW(w.base) + dewta;

		wiw_memcpy_fwomio_32(&d, x, sizeof(d));

		seq_pwintf(s, "  [%2x] %s %s%s 0x%08x", i,
			   d.sync ? "F" : "E",
			   (w.taiw - w.base == dewta) ? "t" : " ",
			   (w.head - w.base == dewta) ? "h" : " ",
			   we32_to_cpu(d.addw));
		if (0 == wmi_wead_hdw(wiw, d.addw, &hdw)) {
			u16 wen = we16_to_cpu(hdw.wen);

			seq_pwintf(s, " -> %04x %04x %04x %02x\n",
				   we16_to_cpu(hdw.seq), wen,
				   we16_to_cpu(hdw.type), hdw.fwags);
			if (wen <= MAX_MBOXITEM_SIZE) {
				unsigned chaw databuf[MAX_MBOXITEM_SIZE];
				void __iomem *swc = wmi_buffew(wiw, d.addw) +
					sizeof(stwuct wiw6210_mbox_hdw);
				/*
				 * No need to check @swc fow vawidity -
				 * we awweady vawidated @d.addw whiwe
				 * weading headew
				 */
				wiw_memcpy_fwomio_32(databuf, swc, wen);
				wiw_seq_hexdump(s, databuf, wen, "      : ");
			}
		} ewse {
			seq_puts(s, "\n");
		}
	}
 out:
	seq_puts(s, "}\n");
	wiw_mem_access_unwock(wiw);
	wiw_hawp_unvote(wiw);
}

static int mbox_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int wet;

	wet = wiw_pm_wuntime_get(wiw);
	if (wet < 0)
		wetuwn wet;

	wiw_pwint_mbox_wing(s, "tx", wiw->csw + HOST_MBOX +
		       offsetof(stwuct wiw6210_mbox_ctw, tx));
	wiw_pwint_mbox_wing(s, "wx", wiw->csw + HOST_MBOX +
		       offsetof(stwuct wiw6210_mbox_ctw, wx));

	wiw_pm_wuntime_put(wiw);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mbox);

static int wiw_debugfs_iomem_x32_set(void *data, u64 vaw)
{
	stwuct wiw_debugfs_iomem_data *d = (stwuct
					    wiw_debugfs_iomem_data *)data;
	stwuct wiw6210_pwiv *wiw = d->wiw;
	int wet;

	wet = wiw_pm_wuntime_get(wiw);
	if (wet < 0)
		wetuwn wet;

	wwitew_wewaxed(vaw, (void __iomem *)d->offset);

	wmb(); /* make suwe wwite pwopagated to HW */

	wiw_pm_wuntime_put(wiw);

	wetuwn 0;
}

static int wiw_debugfs_iomem_x32_get(void *data, u64 *vaw)
{
	stwuct wiw_debugfs_iomem_data *d = (stwuct
					    wiw_debugfs_iomem_data *)data;
	stwuct wiw6210_pwiv *wiw = d->wiw;
	int wet;

	wet = wiw_pm_wuntime_get(wiw);
	if (wet < 0)
		wetuwn wet;

	*vaw = weadw((void __iomem *)d->offset);

	wiw_pm_wuntime_put(wiw);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_iomem_x32, wiw_debugfs_iomem_x32_get,
			 wiw_debugfs_iomem_x32_set, "0x%08wwx\n");

static void wiw_debugfs_cweate_iomem_x32(const chaw *name, umode_t mode,
					 stwuct dentwy *pawent, void *vawue,
					 stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw_debugfs_iomem_data *data = &wiw->dbg_data.data_aww[
					      wiw->dbg_data.iomem_data_count];

	data->wiw = wiw;
	data->offset = vawue;

	debugfs_cweate_fiwe_unsafe(name, mode, pawent, data, &fops_iomem_x32);
	wiw->dbg_data.iomem_data_count++;
}

static int wiw_debugfs_uwong_set(void *data, u64 vaw)
{
	*(uwong *)data = vaw;
	wetuwn 0;
}

static int wiw_debugfs_uwong_get(void *data, u64 *vaw)
{
	*vaw = *(uwong *)data;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(wiw_fops_uwong, wiw_debugfs_uwong_get,
			 wiw_debugfs_uwong_set, "0x%wwx\n");

/**
 * wiw6210_debugfs_init_offset - cweate set of debugfs fiwes
 * @wiw: dwivew's context, used fow pwinting
 * @dbg: diwectowy on the debugfs, whewe fiwes wiww be cweated
 * @base: base addwess used in addwess cawcuwation
 * @tbw: tabwe with fiwe descwiptions. Shouwd be tewminated with empty ewement.
 *
 * Cweates fiwes accowdingwy to the @tbw.
 */
static void wiw6210_debugfs_init_offset(stwuct wiw6210_pwiv *wiw,
					stwuct dentwy *dbg, void *base,
					const stwuct dbg_off * const tbw)
{
	int i;

	fow (i = 0; tbw[i].name; i++) {
		switch (tbw[i].type) {
		case doff_u32:
			debugfs_cweate_u32(tbw[i].name, tbw[i].mode, dbg,
					   base + tbw[i].off);
			bweak;
		case doff_x32:
			debugfs_cweate_x32(tbw[i].name, tbw[i].mode, dbg,
					   base + tbw[i].off);
			bweak;
		case doff_uwong:
			debugfs_cweate_fiwe_unsafe(tbw[i].name, tbw[i].mode,
						   dbg, base + tbw[i].off,
						   &wiw_fops_uwong);
			bweak;
		case doff_io32:
			wiw_debugfs_cweate_iomem_x32(tbw[i].name, tbw[i].mode,
						     dbg, base + tbw[i].off,
						     wiw);
			bweak;
		case doff_u8:
			debugfs_cweate_u8(tbw[i].name, tbw[i].mode, dbg,
					  base + tbw[i].off);
			bweak;
		}
	}
}

static const stwuct dbg_off isw_off[] = {
	{"ICC", 0644, offsetof(stwuct WGF_ICW, ICC), doff_io32},
	{"ICW", 0644, offsetof(stwuct WGF_ICW, ICW), doff_io32},
	{"ICM", 0644, offsetof(stwuct WGF_ICW, ICM), doff_io32},
	{"ICS",	0244, offsetof(stwuct WGF_ICW, ICS), doff_io32},
	{"IMV", 0644, offsetof(stwuct WGF_ICW, IMV), doff_io32},
	{"IMS",	0244, offsetof(stwuct WGF_ICW, IMS), doff_io32},
	{"IMC",	0244, offsetof(stwuct WGF_ICW, IMC), doff_io32},
	{},
};

static void wiw6210_debugfs_cweate_ISW(stwuct wiw6210_pwiv *wiw,
				       const chaw *name, stwuct dentwy *pawent,
				       u32 off)
{
	stwuct dentwy *d = debugfs_cweate_diw(name, pawent);

	wiw6210_debugfs_init_offset(wiw, d, (void * __fowce)wiw->csw + off,
				    isw_off);
}

static const stwuct dbg_off pseudo_isw_off[] = {
	{"CAUSE",   0444, HOSTADDW(WGF_DMA_PSEUDO_CAUSE), doff_io32},
	{"MASK_SW", 0444, HOSTADDW(WGF_DMA_PSEUDO_CAUSE_MASK_SW), doff_io32},
	{"MASK_FW", 0444, HOSTADDW(WGF_DMA_PSEUDO_CAUSE_MASK_FW), doff_io32},
	{},
};

static void wiw6210_debugfs_cweate_pseudo_ISW(stwuct wiw6210_pwiv *wiw,
					      stwuct dentwy *pawent)
{
	stwuct dentwy *d = debugfs_cweate_diw("PSEUDO_ISW", pawent);

	wiw6210_debugfs_init_offset(wiw, d, (void * __fowce)wiw->csw,
				    pseudo_isw_off);
}

static const stwuct dbg_off wgc_itw_cnt_off[] = {
	{"TWSH", 0644, HOSTADDW(WGF_DMA_ITW_CNT_TWSH), doff_io32},
	{"DATA", 0644, HOSTADDW(WGF_DMA_ITW_CNT_DATA), doff_io32},
	{"CTW",  0644, HOSTADDW(WGF_DMA_ITW_CNT_CWW), doff_io32},
	{},
};

static const stwuct dbg_off tx_itw_cnt_off[] = {
	{"TWSH", 0644, HOSTADDW(WGF_DMA_ITW_TX_CNT_TWSH),
	 doff_io32},
	{"DATA", 0644, HOSTADDW(WGF_DMA_ITW_TX_CNT_DATA),
	 doff_io32},
	{"CTW",  0644, HOSTADDW(WGF_DMA_ITW_TX_CNT_CTW),
	 doff_io32},
	{"IDW_TWSH", 0644, HOSTADDW(WGF_DMA_ITW_TX_IDW_CNT_TWSH),
	 doff_io32},
	{"IDW_DATA", 0644, HOSTADDW(WGF_DMA_ITW_TX_IDW_CNT_DATA),
	 doff_io32},
	{"IDW_CTW",  0644, HOSTADDW(WGF_DMA_ITW_TX_IDW_CNT_CTW),
	 doff_io32},
	{},
};

static const stwuct dbg_off wx_itw_cnt_off[] = {
	{"TWSH", 0644, HOSTADDW(WGF_DMA_ITW_WX_CNT_TWSH),
	 doff_io32},
	{"DATA", 0644, HOSTADDW(WGF_DMA_ITW_WX_CNT_DATA),
	 doff_io32},
	{"CTW",  0644, HOSTADDW(WGF_DMA_ITW_WX_CNT_CTW),
	 doff_io32},
	{"IDW_TWSH", 0644, HOSTADDW(WGF_DMA_ITW_WX_IDW_CNT_TWSH),
	 doff_io32},
	{"IDW_DATA", 0644, HOSTADDW(WGF_DMA_ITW_WX_IDW_CNT_DATA),
	 doff_io32},
	{"IDW_CTW",  0644, HOSTADDW(WGF_DMA_ITW_WX_IDW_CNT_CTW),
	 doff_io32},
	{},
};

static int wiw6210_debugfs_cweate_ITW_CNT(stwuct wiw6210_pwiv *wiw,
					  stwuct dentwy *pawent)
{
	stwuct dentwy *d, *dtx, *dwx;

	d = debugfs_cweate_diw("ITW_CNT", pawent);

	dtx = debugfs_cweate_diw("TX", d);
	dwx = debugfs_cweate_diw("WX", d);

	wiw6210_debugfs_init_offset(wiw, d, (void * __fowce)wiw->csw,
				    wgc_itw_cnt_off);

	wiw6210_debugfs_init_offset(wiw, dtx, (void * __fowce)wiw->csw,
				    tx_itw_cnt_off);

	wiw6210_debugfs_init_offset(wiw, dwx, (void * __fowce)wiw->csw,
				    wx_itw_cnt_off);
	wetuwn 0;
}

static int memwead_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	void __iomem *a;
	int wet;

	wet = wiw_pm_wuntime_get(wiw);
	if (wet < 0)
		wetuwn wet;

	wet = wiw_mem_access_wock(wiw);
	if (wet) {
		wiw_pm_wuntime_put(wiw);
		wetuwn wet;
	}

	a = wmi_buffew(wiw, cpu_to_we32(mem_addw));

	if (a)
		seq_pwintf(s, "[0x%08x] = 0x%08x\n", mem_addw, weadw(a));
	ewse
		seq_pwintf(s, "[0x%08x] = INVAWID\n", mem_addw);

	wiw_mem_access_unwock(wiw);
	wiw_pm_wuntime_put(wiw);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(memwead);

static ssize_t wiw_wead_fiwe_iobwob(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	enum { max_count = 4096 };
	stwuct wiw_bwob_wwappew *wiw_bwob = fiwe->pwivate_data;
	stwuct wiw6210_pwiv *wiw = wiw_bwob->wiw;
	woff_t awigned_pos, pos = *ppos;
	size_t avaiwabwe = wiw_bwob->bwob.size;
	void *buf;
	size_t unawigned_bytes, awigned_count, wet;
	int wc;

	if (pos < 0)
		wetuwn -EINVAW;

	if (pos >= avaiwabwe || !count)
		wetuwn 0;

	if (count > avaiwabwe - pos)
		count = avaiwabwe - pos;
	if (count > max_count)
		count = max_count;

	/* set pos to 4 bytes awigned */
	unawigned_bytes = pos % 4;
	awigned_pos = pos - unawigned_bytes;
	awigned_count = count + unawigned_bytes;

	buf = kmawwoc(awigned_count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wc = wiw_pm_wuntime_get(wiw);
	if (wc < 0) {
		kfwee(buf);
		wetuwn wc;
	}

	wc = wiw_mem_access_wock(wiw);
	if (wc) {
		kfwee(buf);
		wiw_pm_wuntime_put(wiw);
		wetuwn wc;
	}

	wiw_memcpy_fwomio_32(buf, (const void __iomem *)
			     wiw_bwob->bwob.data + awigned_pos, awigned_count);

	wet = copy_to_usew(usew_buf, buf + unawigned_bytes, count);

	wiw_mem_access_unwock(wiw);
	wiw_pm_wuntime_put(wiw);

	kfwee(buf);
	if (wet == count)
		wetuwn -EFAUWT;

	count -= wet;
	*ppos = pos + count;

	wetuwn count;
}

static const stwuct fiwe_opewations fops_iobwob = {
	.wead =		wiw_wead_fiwe_iobwob,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static
stwuct dentwy *wiw_debugfs_cweate_iobwob(const chaw *name,
					 umode_t mode,
					 stwuct dentwy *pawent,
					 stwuct wiw_bwob_wwappew *wiw_bwob)
{
	wetuwn debugfs_cweate_fiwe(name, mode, pawent, wiw_bwob, &fops_iobwob);
}

/*---wwite channew 1..4 to wxon fow it, 0 to wxoff---*/
static ssize_t wiw_wwite_fiwe_wxon(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t wen, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	int wc;
	wong channew;
	boow on;

	chaw *kbuf = memdup_usew_nuw(buf, wen);

	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);
	wc = kstwtow(kbuf, 0, &channew);
	kfwee(kbuf);
	if (wc)
		wetuwn wc;

	if ((channew < 0) || (channew > 4)) {
		wiw_eww(wiw, "Invawid channew %wd\n", channew);
		wetuwn -EINVAW;
	}
	on = !!channew;

	if (on) {
		wc = wmi_set_channew(wiw, (int)channew);
		if (wc)
			wetuwn wc;
	}

	wc = wmi_wxon(wiw, on);
	if (wc)
		wetuwn wc;

	wetuwn wen;
}

static const stwuct fiwe_opewations fops_wxon = {
	.wwite = wiw_wwite_fiwe_wxon,
	.open  = simpwe_open,
};

static ssize_t wiw_wwite_fiwe_wbufcap(stwuct fiwe *fiwe,
				      const chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	int vaw;
	int wc;

	wc = kstwtoint_fwom_usew(buf, count, 0, &vaw);
	if (wc) {
		wiw_eww(wiw, "Invawid awgument\n");
		wetuwn wc;
	}
	/* input vawue: negative to disabwe, 0 to use system defauwt,
	 * 1..wing size to set descwiptow thweshowd
	 */
	wiw_info(wiw, "%s WBUFCAP, descwiptows thweshowd - %d\n",
		 vaw < 0 ? "Disabwing" : "Enabwing", vaw);

	if (!wiw->wing_wx.va || vaw > wiw->wing_wx.size) {
		wiw_eww(wiw, "Invawid descwiptows thweshowd, %d\n", vaw);
		wetuwn -EINVAW;
	}

	wc = wmi_wbufcap_cfg(wiw, vaw < 0 ? 0 : 1, vaw < 0 ? 0 : vaw);
	if (wc) {
		wiw_eww(wiw, "WBUFCAP config faiwed: %d\n", wc);
		wetuwn wc;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_wbufcap = {
	.wwite = wiw_wwite_fiwe_wbufcap,
	.open  = simpwe_open,
};

/* bwock ack contwow, wwite:
 * - "add <wingid> <agg_size> <timeout>" to twiggew ADDBA
 * - "dew_tx <wingid> <weason>" to twiggew DEWBA fow Tx side
 * - "dew_wx <CID> <TID> <weason>" to twiggew DEWBA fow Wx side
 */
static ssize_t wiw_wwite_back(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t wen, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	int wc;
	chaw *kbuf = kmawwoc(wen + 1, GFP_KEWNEW);
	chaw cmd[9];
	int p1, p2, p3;

	if (!kbuf)
		wetuwn -ENOMEM;

	wc = simpwe_wwite_to_buffew(kbuf, wen, ppos, buf, wen);
	if (wc != wen) {
		kfwee(kbuf);
		wetuwn wc >= 0 ? -EIO : wc;
	}

	kbuf[wen] = '\0';
	wc = sscanf(kbuf, "%8s %d %d %d", cmd, &p1, &p2, &p3);
	kfwee(kbuf);

	if (wc < 0)
		wetuwn wc;
	if (wc < 2)
		wetuwn -EINVAW;

	if ((stwcmp(cmd, "add") == 0) ||
	    (stwcmp(cmd, "dew_tx") == 0)) {
		stwuct wiw_wing_tx_data *txdata;

		if (p1 < 0 || p1 >= WIW6210_MAX_TX_WINGS) {
			wiw_eww(wiw, "BACK: invawid wing id %d\n", p1);
			wetuwn -EINVAW;
		}
		txdata = &wiw->wing_tx_data[p1];
		if (stwcmp(cmd, "add") == 0) {
			if (wc < 3) {
				wiw_eww(wiw, "BACK: add wequiwe at weast 2 pawams\n");
				wetuwn -EINVAW;
			}
			if (wc < 4)
				p3 = 0;
			wmi_addba(wiw, txdata->mid, p1, p2, p3);
		} ewse {
			if (wc < 3)
				p2 = WWAN_WEASON_QSTA_WEAVE_QBSS;
			wmi_dewba_tx(wiw, txdata->mid, p1, p2);
		}
	} ewse if (stwcmp(cmd, "dew_wx") == 0) {
		stwuct wiw_sta_info *sta;

		if (wc < 3) {
			wiw_eww(wiw,
				"BACK: dew_wx wequiwe at weast 2 pawams\n");
			wetuwn -EINVAW;
		}
		if (p1 < 0 || p1 >= wiw->max_assoc_sta) {
			wiw_eww(wiw, "BACK: invawid CID %d\n", p1);
			wetuwn -EINVAW;
		}
		if (wc < 4)
			p3 = WWAN_WEASON_QSTA_WEAVE_QBSS;
		sta = &wiw->sta[p1];
		wmi_dewba_wx(wiw, sta->mid, p1, p2, p3);
	} ewse {
		wiw_eww(wiw, "BACK: Unwecognized command \"%s\"\n", cmd);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

static ssize_t wiw_wead_back(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	static const chaw text[] = "bwock ack contwow, wwite:\n"
	" - \"add <wingid> <agg_size> <timeout>\" to twiggew ADDBA\n"
	"If missing, <timeout> defauwts to 0\n"
	" - \"dew_tx <wingid> <weason>\" to twiggew DEWBA fow Tx side\n"
	" - \"dew_wx <CID> <TID> <weason>\" to twiggew DEWBA fow Wx side\n"
	"If missing, <weason> set to \"STA_WEAVING\" (36)\n";

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, text,
				       sizeof(text));
}

static const stwuct fiwe_opewations fops_back = {
	.wead = wiw_wead_back,
	.wwite = wiw_wwite_back,
	.open  = simpwe_open,
};

/* pmc contwow, wwite:
 * - "awwoc <num descwiptows> <descwiptow_size>" to awwocate PMC
 * - "fwee" to wewease memowy awwocated fow PMC
 */
static ssize_t wiw_wwite_pmccfg(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t wen, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	int wc;
	chaw *kbuf = kmawwoc(wen + 1, GFP_KEWNEW);
	chaw cmd[9];
	int num_descs, desc_size;

	if (!kbuf)
		wetuwn -ENOMEM;

	wc = simpwe_wwite_to_buffew(kbuf, wen, ppos, buf, wen);
	if (wc != wen) {
		kfwee(kbuf);
		wetuwn wc >= 0 ? -EIO : wc;
	}

	kbuf[wen] = '\0';
	wc = sscanf(kbuf, "%8s %d %d", cmd, &num_descs, &desc_size);
	kfwee(kbuf);

	if (wc < 0)
		wetuwn wc;

	if (wc < 1) {
		wiw_eww(wiw, "pmccfg: no pawams given\n");
		wetuwn -EINVAW;
	}

	if (0 == stwcmp(cmd, "awwoc")) {
		if (wc != 3) {
			wiw_eww(wiw, "pmccfg: awwoc wequiwes 2 pawams\n");
			wetuwn -EINVAW;
		}
		wiw_pmc_awwoc(wiw, num_descs, desc_size);
	} ewse if (0 == stwcmp(cmd, "fwee")) {
		if (wc != 1) {
			wiw_eww(wiw, "pmccfg: fwee does not have any pawams\n");
			wetuwn -EINVAW;
		}
		wiw_pmc_fwee(wiw, twue);
	} ewse {
		wiw_eww(wiw, "pmccfg: Unwecognized command \"%s\"\n", cmd);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

static ssize_t wiw_wead_pmccfg(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	chaw text[256];
	chaw hewp[] = "pmc contwow, wwite:\n"
	" - \"awwoc <num descwiptows> <descwiptow_size>\" to awwocate pmc\n"
	" - \"fwee\" to fwee memowy awwocated fow pmc\n";

	snpwintf(text, sizeof(text), "Wast command status: %d\n\n%s",
		 wiw_pmc_wast_cmd_status(wiw), hewp);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, text,
				       stwwen(text) + 1);
}

static const stwuct fiwe_opewations fops_pmccfg = {
	.wead = wiw_wead_pmccfg,
	.wwite = wiw_wwite_pmccfg,
	.open  = simpwe_open,
};

static const stwuct fiwe_opewations fops_pmcdata = {
	.open		= simpwe_open,
	.wead		= wiw_pmc_wead,
	.wwseek		= wiw_pmc_wwseek,
};

static int wiw_pmcwing_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wiw_pmcwing_wead, inode->i_pwivate);
}

static const stwuct fiwe_opewations fops_pmcwing = {
	.open		= wiw_pmcwing_seq_open,
	.wewease	= singwe_wewease,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
};

/*---tx_mgmt---*/
/* Wwite mgmt fwame to this fiwe to send it */
static ssize_t wiw_wwite_fiwe_txmgmt(stwuct fiwe *fiwe, const chaw __usew *buf,
				     size_t wen, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);
	stwuct wiwewess_dev *wdev = wiw->main_ndev->ieee80211_ptw;
	stwuct cfg80211_mgmt_tx_pawams pawams;
	int wc;
	void *fwame;

	memset(&pawams, 0, sizeof(pawams));

	if (!wen)
		wetuwn -EINVAW;

	fwame = memdup_usew(buf, wen);
	if (IS_EWW(fwame))
		wetuwn PTW_EWW(fwame);

	pawams.buf = fwame;
	pawams.wen = wen;

	wc = wiw_cfg80211_mgmt_tx(wiphy, wdev, &pawams, NUWW);

	kfwee(fwame);
	wiw_info(wiw, "-> %d\n", wc);

	wetuwn wen;
}

static const stwuct fiwe_opewations fops_txmgmt = {
	.wwite = wiw_wwite_fiwe_txmgmt,
	.open  = simpwe_open,
};

/* Wwite WMI command (w/o mbox headew) to this fiwe to send it
 * WMI stawts fwom wiw6210_mbox_hdw_wmi headew
 */
static ssize_t wiw_wwite_fiwe_wmi(stwuct fiwe *fiwe, const chaw __usew *buf,
				  size_t wen, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_cmd_hdw *wmi;
	void *cmd;
	int cmdwen = wen - sizeof(stwuct wmi_cmd_hdw);
	u16 cmdid;
	int wc1;

	if (cmdwen < 0 || *ppos != 0)
		wetuwn -EINVAW;

	wmi = memdup_usew(buf, wen);
	if (IS_EWW(wmi))
		wetuwn PTW_EWW(wmi);

	cmd = (cmdwen > 0) ? &wmi[1] : NUWW;
	cmdid = we16_to_cpu(wmi->command_id);

	wc1 = wmi_send(wiw, cmdid, vif->mid, cmd, cmdwen);
	kfwee(wmi);

	wiw_info(wiw, "0x%04x[%d] -> %d\n", cmdid, cmdwen, wc1);

	wetuwn wen;
}

static const stwuct fiwe_opewations fops_wmi = {
	.wwite = wiw_wwite_fiwe_wmi,
	.open  = simpwe_open,
};

static void wiw_seq_pwint_skb(stwuct seq_fiwe *s, stwuct sk_buff *skb)
{
	int i = 0;
	int wen = skb_headwen(skb);
	void *p = skb->data;
	int nw_fwags = skb_shinfo(skb)->nw_fwags;

	seq_pwintf(s, "    wen = %d\n", wen);
	wiw_seq_hexdump(s, p, wen, "      : ");

	if (nw_fwags) {
		seq_pwintf(s, "    nw_fwags = %d\n", nw_fwags);
		fow (i = 0; i < nw_fwags; i++) {
			const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

			wen = skb_fwag_size(fwag);
			p = skb_fwag_addwess_safe(fwag);
			seq_pwintf(s, "    [%2d] : wen = %d\n", i, wen);
			wiw_seq_hexdump(s, p, wen, "      : ");
		}
	}
}

/*---------Tx/Wx descwiptow------------*/
static int txdesc_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct wiw_wing *wing;
	boow tx;
	int wing_idx = dbg_wing_index;
	int txdesc_idx = dbg_txdesc_index;
	vowatiwe stwuct vwing_tx_desc *d;
	vowatiwe u32 *u;
	stwuct sk_buff *skb;

	if (wiw->use_enhanced_dma_hw) {
		/* WX wing index == 0 */
		if (wing_idx >= WIW6210_MAX_TX_WINGS) {
			seq_pwintf(s, "invawid wing index %d\n", wing_idx);
			wetuwn 0;
		}
		tx = wing_idx > 0; /* desc wing 0 is wesewved fow WX */
	} ewse {
		/* WX wing index == WIW6210_MAX_TX_WINGS */
		if (wing_idx > WIW6210_MAX_TX_WINGS) {
			seq_pwintf(s, "invawid wing index %d\n", wing_idx);
			wetuwn 0;
		}
		tx = (wing_idx < WIW6210_MAX_TX_WINGS);
	}

	wing = tx ? &wiw->wing_tx[wing_idx] : &wiw->wing_wx;

	if (!wing->va) {
		if (tx)
			seq_pwintf(s, "No Tx[%2d] WING\n", wing_idx);
		ewse
			seq_puts(s, "No Wx WING\n");
		wetuwn 0;
	}

	if (txdesc_idx >= wing->size) {
		if (tx)
			seq_pwintf(s, "[%2d] TxDesc index (%d) >= size (%d)\n",
				   wing_idx, txdesc_idx, wing->size);
		ewse
			seq_pwintf(s, "WxDesc index (%d) >= size (%d)\n",
				   txdesc_idx, wing->size);
		wetuwn 0;
	}

	/* use stwuct vwing_tx_desc fow Wx as weww,
	 * onwy fiewd used, .dma.wength, is the same
	 */
	d = &wing->va[txdesc_idx].tx.wegacy;
	u = (vowatiwe u32 *)d;
	skb = NUWW;

	if (wiw->use_enhanced_dma_hw) {
		if (tx) {
			skb = wing->ctx ? wing->ctx[txdesc_idx].skb : NUWW;
		} ewse if (wiw->wx_buff_mgmt.buff_aww) {
			stwuct wiw_wx_enhanced_desc *wx_d =
				(stwuct wiw_wx_enhanced_desc *)
				&wing->va[txdesc_idx].wx.enhanced;
			u16 buff_id = we16_to_cpu(wx_d->mac.buff_id);

			if (!wiw_vaw_in_wange(buff_id, 0,
					      wiw->wx_buff_mgmt.size))
				seq_pwintf(s, "invawid buff_id %d\n", buff_id);
			ewse
				skb = wiw->wx_buff_mgmt.buff_aww[buff_id].skb;
		}
	} ewse {
		skb = wing->ctx[txdesc_idx].skb;
	}
	if (tx)
		seq_pwintf(s, "Tx[%2d][%3d] = {\n", wing_idx,
			   txdesc_idx);
	ewse
		seq_pwintf(s, "Wx[%3d] = {\n", txdesc_idx);
	seq_pwintf(s, "  MAC = 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[0], u[1], u[2], u[3]);
	seq_pwintf(s, "  DMA = 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[4], u[5], u[6], u[7]);
	seq_pwintf(s, "  SKB = 0x%p\n", skb);

	if (skb) {
		skb_get(skb);
		wiw_seq_pwint_skb(s, skb);
		kfwee_skb(skb);
	}
	seq_puts(s, "}\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(txdesc);

/*---------Tx/Wx status message------------*/
static int status_msg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int swing_idx = dbg_swing_index;
	stwuct wiw_status_wing *swing;
	boow tx;
	u32 status_msg_idx = dbg_status_msg_index;
	u32 *u;

	if (swing_idx >= WIW6210_MAX_STATUS_WINGS) {
		seq_pwintf(s, "invawid status wing index %d\n", swing_idx);
		wetuwn 0;
	}

	swing = &wiw->swings[swing_idx];
	tx = !swing->is_wx;

	if (!swing->va) {
		seq_pwintf(s, "No %cX status wing\n", tx ? 'T' : 'W');
		wetuwn 0;
	}

	if (status_msg_idx >= swing->size) {
		seq_pwintf(s, "%cxDesc index (%d) >= size (%d)\n",
			   tx ? 'T' : 'W', status_msg_idx, swing->size);
		wetuwn 0;
	}

	u = swing->va + (swing->ewem_size * status_msg_idx);

	seq_pwintf(s, "%cx[%d][%3d] = {\n",
		   tx ? 'T' : 'W', swing_idx, status_msg_idx);

	seq_pwintf(s, "  0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[0], u[1], u[2], u[3]);
	if (!tx && !wiw->use_compwessed_wx_status)
		seq_pwintf(s, "  0x%08x 0x%08x 0x%08x 0x%08x\n",
			   u[4], u[5], u[6], u[7]);

	seq_puts(s, "}\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(status_msg);

static int wiw_pwint_wx_buff(stwuct seq_fiwe *s, stwuct wist_head *wh)
{
	stwuct wiw_wx_buff *it;
	int i = 0;

	wist_fow_each_entwy(it, wh, wist) {
		if ((i % 16) == 0 && i != 0)
			seq_puts(s, "\n    ");
		seq_pwintf(s, "[%4d] ", it->id);
		i++;
	}
	seq_pwintf(s, "\nNumbew of buffews: %u\n", i);

	wetuwn i;
}

static int wx_buff_mgmt_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct wiw_wx_buff_mgmt *wbm = &wiw->wx_buff_mgmt;
	int num_active;
	int num_fwee;

	if (!wbm->buff_aww)
		wetuwn -EINVAW;

	seq_pwintf(s, "  size = %zu\n", wbm->size);
	seq_pwintf(s, "  fwee_wist_empty_cnt = %wu\n",
		   wbm->fwee_wist_empty_cnt);

	/* Pwint active wist */
	seq_puts(s, "  Active wist:\n");
	num_active = wiw_pwint_wx_buff(s, &wbm->active);
	seq_puts(s, "\n  Fwee wist:\n");
	num_fwee = wiw_pwint_wx_buff(s, &wbm->fwee);

	seq_pwintf(s, "  Totaw numbew of buffews: %u\n",
		   num_active + num_fwee);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wx_buff_mgmt);

/*---------beamfowming------------*/
static chaw *wiw_bfstatus_stw(u32 status)
{
	switch (status) {
	case 0:
		wetuwn "Faiwed";
	case 1:
		wetuwn "OK";
	case 2:
		wetuwn "Wetwying";
	defauwt:
		wetuwn "??";
	}
}

static boow is_aww_zewos(void * const x_, size_t sz)
{
	/* if wepwy is aww-0, ignowe this CID */
	u32 *x = x_;
	int n;

	fow (n = 0; n < sz / sizeof(*x); n++)
		if (x[n])
			wetuwn fawse;

	wetuwn twue;
}

static int bf_show(stwuct seq_fiwe *s, void *data)
{
	int wc;
	int i;
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_notify_weq_cmd cmd = {
		.intewvaw_usec = 0,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_notify_weq_done_event evt;
	} __packed wepwy;

	memset(&wepwy, 0, sizeof(wepwy));

	fow (i = 0; i < wiw->max_assoc_sta; i++) {
		u32 status;
		u8 bf_mcs;

		cmd.cid = i;
		wc = wmi_caww(wiw, WMI_NOTIFY_WEQ_CMDID, vif->mid,
			      &cmd, sizeof(cmd),
			      WMI_NOTIFY_WEQ_DONE_EVENTID, &wepwy,
			      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
		/* if wepwy is aww-0, ignowe this CID */
		if (wc || is_aww_zewos(&wepwy.evt, sizeof(wepwy.evt)))
			continue;

		status = we32_to_cpu(wepwy.evt.status);
		bf_mcs = we16_to_cpu(wepwy.evt.bf_mcs);
		seq_pwintf(s, "CID %d {\n"
			   "  TSF = 0x%016wwx\n"
			   "  TxMCS = %s TxTpt = %4d\n"
			   "  SQI = %4d\n"
			   "  WSSI = %4d\n"
			   "  Status = 0x%08x %s\n"
			   "  Sectows(wx:tx) my %2d:%2d peew %2d:%2d\n"
			   "  Goodput(wx:tx) %4d:%4d\n"
			   "}\n",
			   i,
			   we64_to_cpu(wepwy.evt.tsf),
			   WIW_EXTENDED_MCS_CHECK(bf_mcs),
			   we32_to_cpu(wepwy.evt.tx_tpt),
			   wepwy.evt.sqi,
			   wepwy.evt.wssi,
			   status, wiw_bfstatus_stw(status),
			   we16_to_cpu(wepwy.evt.my_wx_sectow),
			   we16_to_cpu(wepwy.evt.my_tx_sectow),
			   we16_to_cpu(wepwy.evt.othew_wx_sectow),
			   we16_to_cpu(wepwy.evt.othew_tx_sectow),
			   we32_to_cpu(wepwy.evt.wx_goodput),
			   we32_to_cpu(wepwy.evt.tx_goodput));
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bf);

/*---------temp------------*/
static void pwint_temp(stwuct seq_fiwe *s, const chaw *pwefix, s32 t)
{
	switch (t) {
	case 0:
	case WMI_INVAWID_TEMPEWATUWE:
		seq_pwintf(s, "%s N/A\n", pwefix);
	bweak;
	defauwt:
		seq_pwintf(s, "%s %s%d.%03d\n", pwefix, (t < 0 ? "-" : ""),
			   abs(t / 1000), abs(t % 1000));
		bweak;
	}
}

static int temp_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int wc, i;

	if (test_bit(WMI_FW_CAPABIWITY_TEMPEWATUWE_AWW_WF,
		     wiw->fw_capabiwities)) {
		stwuct wmi_temp_sense_aww_done_event sense_aww_evt;

		wiw_dbg_misc(wiw,
			     "WMI_FW_CAPABIWITY_TEMPEWATUWE_AWW_WF is suppowted");
		wc = wmi_get_aww_tempewatuwes(wiw, &sense_aww_evt);
		if (wc) {
			seq_puts(s, "Faiwed\n");
			wetuwn 0;
		}
		pwint_temp(s, "T_mac   =",
			   we32_to_cpu(sense_aww_evt.baseband_t1000));
		seq_pwintf(s, "Connected WFs [0x%08x]\n",
			   sense_aww_evt.wf_bitmap);
		fow (i = 0; i < WMI_MAX_XIF_POWTS_NUM; i++) {
			seq_pwintf(s, "WF[%d]   = ", i);
			pwint_temp(s, "",
				   we32_to_cpu(sense_aww_evt.wf_t1000[i]));
		}
	} ewse {
		s32 t_m, t_w;

		wiw_dbg_misc(wiw,
			     "WMI_FW_CAPABIWITY_TEMPEWATUWE_AWW_WF is not suppowted");
		wc = wmi_get_tempewatuwe(wiw, &t_m, &t_w);
		if (wc) {
			seq_puts(s, "Faiwed\n");
			wetuwn 0;
		}
		pwint_temp(s, "T_mac   =", t_m);
		pwint_temp(s, "T_wadio =", t_w);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(temp);

/*---------wink------------*/
static int wink_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct station_info *sinfo;
	int i, wc = 0;

	sinfo = kzawwoc(sizeof(*sinfo), GFP_KEWNEW);
	if (!sinfo)
		wetuwn -ENOMEM;

	fow (i = 0; i < wiw->max_assoc_sta; i++) {
		stwuct wiw_sta_info *p = &wiw->sta[i];
		chaw *status = "unknown";
		stwuct wiw6210_vif *vif;
		u8 mid;

		switch (p->status) {
		case wiw_sta_unused:
			status = "unused   ";
			bweak;
		case wiw_sta_conn_pending:
			status = "pending  ";
			bweak;
		case wiw_sta_connected:
			status = "connected";
			bweak;
		}
		mid = (p->status != wiw_sta_unused) ? p->mid : U8_MAX;
		seq_pwintf(s, "[%d][MID %d] %pM %s\n",
			   i, mid, p->addw, status);

		if (p->status != wiw_sta_connected)
			continue;

		vif = (mid < GET_MAX_VIFS(wiw)) ? wiw->vifs[mid] : NUWW;
		if (vif) {
			wc = wiw_cid_fiww_sinfo(vif, i, sinfo);
			if (wc)
				goto out;

			seq_pwintf(s, "  Tx_mcs = %s\n",
				   WIW_EXTENDED_MCS_CHECK(sinfo->txwate.mcs));
			seq_pwintf(s, "  Wx_mcs = %s\n",
				   WIW_EXTENDED_MCS_CHECK(sinfo->wxwate.mcs));
			seq_pwintf(s, "  SQ     = %d\n", sinfo->signaw);
		} ewse {
			seq_puts(s, "  INVAWID MID\n");
		}
	}

out:
	kfwee(sinfo);
	wetuwn wc;
}
DEFINE_SHOW_ATTWIBUTE(wink);

/*---------info------------*/
static int info_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct net_device *ndev = wiw->main_ndev;
	int is_ac = powew_suppwy_is_system_suppwied();
	int wx = atomic_xchg(&wiw->isw_count_wx, 0);
	int tx = atomic_xchg(&wiw->isw_count_tx, 0);
	static uwong wxf_owd, txf_owd;
	uwong wxf = ndev->stats.wx_packets;
	uwong txf = ndev->stats.tx_packets;
	unsigned int i;

	/* >0 : AC; 0 : battewy; <0 : ewwow */
	seq_pwintf(s, "AC powewed : %d\n", is_ac);
	seq_pwintf(s, "Wx iwqs:packets : %8d : %8wd\n", wx, wxf - wxf_owd);
	seq_pwintf(s, "Tx iwqs:packets : %8d : %8wd\n", tx, txf - txf_owd);
	wxf_owd = wxf;
	txf_owd = txf;

#define CHECK_QSTATE(x) (state & BIT(__QUEUE_STATE_ ## x)) ? \
	" " __stwingify(x) : ""

	fow (i = 0; i < ndev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(ndev, i);
		unsigned wong state = txq->state;

		seq_pwintf(s, "Tx queue[%i] state : 0x%wx%s%s%s\n", i, state,
			   CHECK_QSTATE(DWV_XOFF),
			   CHECK_QSTATE(STACK_XOFF),
			   CHECK_QSTATE(FWOZEN)
			  );
	}
#undef CHECK_QSTATE
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(info);

/*---------wecovewy------------*/
/* mode = [manuaw|auto]
 * state = [idwe|pending|wunning]
 */
static ssize_t wiw_wead_fiwe_wecovewy(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	chaw buf[80];
	int n;
	static const chaw * const sstate[] = {"idwe", "pending", "wunning"};

	n = snpwintf(buf, sizeof(buf), "mode = %s\nstate = %s\n",
		     no_fw_wecovewy ? "manuaw" : "auto",
		     sstate[wiw->wecovewy_state]);

	n = min_t(int, n, sizeof(buf));

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       buf, n);
}

static ssize_t wiw_wwite_fiwe_wecovewy(stwuct fiwe *fiwe,
				       const chaw __usew *buf_,
				       size_t count, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	static const chaw wun_command[] = "wun";
	chaw buf[sizeof(wun_command) + 1]; /* to detect "wunx" */
	ssize_t wc;

	if (wiw->wecovewy_state != fw_wecovewy_pending) {
		wiw_eww(wiw, "No wecovewy pending\n");
		wetuwn -EINVAW;
	}

	if (*ppos != 0) {
		wiw_eww(wiw, "Offset [%d]\n", (int)*ppos);
		wetuwn -EINVAW;
	}

	if (count > sizeof(buf)) {
		wiw_eww(wiw, "Input too wong, wen = %d\n", (int)count);
		wetuwn -EINVAW;
	}

	wc = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos, buf_, count);
	if (wc < 0)
		wetuwn wc;

	buf[wc] = '\0';
	if (0 == stwcmp(buf, wun_command))
		wiw_set_wecovewy_state(wiw, fw_wecovewy_wunning);
	ewse
		wiw_eww(wiw, "Bad wecovewy command \"%s\"\n", buf);

	wetuwn wc;
}

static const stwuct fiwe_opewations fops_wecovewy = {
	.wead = wiw_wead_fiwe_wecovewy,
	.wwite = wiw_wwite_fiwe_wecovewy,
	.open  = simpwe_open,
};

/*---------Station matwix------------*/
static void wiw_pwint_wxtid(stwuct seq_fiwe *s, stwuct wiw_tid_ampdu_wx *w)
{
	int i;
	u16 index = ((w->head_seq_num - w->ssn) & 0xfff) % w->buf_size;
	unsigned wong wong dwop_dup = w->dwop_dup, dwop_owd = w->dwop_owd;
	unsigned wong wong dwop_dup_mcast = w->dwop_dup_mcast;

	seq_pwintf(s, "([%2d]) 0x%03x [", w->buf_size, w->head_seq_num);
	fow (i = 0; i < w->buf_size; i++) {
		if (i == index)
			seq_pwintf(s, "%c", w->weowdew_buf[i] ? 'O' : '|');
		ewse
			seq_pwintf(s, "%c", w->weowdew_buf[i] ? '*' : '_');
	}
	seq_pwintf(s,
		   "] totaw %wwu dwop %wwu (dup %wwu + owd %wwu + dup mcast %wwu) wast 0x%03x\n",
		   w->totaw, dwop_dup + dwop_owd + dwop_dup_mcast, dwop_dup,
		   dwop_owd, dwop_dup_mcast, w->ssn_wast_dwop);
}

static void wiw_pwint_wxtid_cwypto(stwuct seq_fiwe *s, int tid,
				   stwuct wiw_tid_cwypto_wx *c)
{
	int i;

	fow (i = 0; i < 4; i++) {
		stwuct wiw_tid_cwypto_wx_singwe *cc = &c->key_id[i];

		if (cc->key_set)
			goto has_keys;
	}
	wetuwn;

has_keys:
	if (tid < WIW_STA_TID_NUM)
		seq_pwintf(s, "  [%2d] PN", tid);
	ewse
		seq_puts(s, "  [GW] PN");

	fow (i = 0; i < 4; i++) {
		stwuct wiw_tid_cwypto_wx_singwe *cc = &c->key_id[i];

		seq_pwintf(s, " [%i%s]%6phN", i, cc->key_set ? "+" : "-",
			   cc->pn);
	}
	seq_puts(s, "\n");
}

static int sta_show(stwuct seq_fiwe *s, void *data)
__acquiwes(&p->tid_wx_wock) __weweases(&p->tid_wx_wock)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int i, tid, mcs;

	fow (i = 0; i < wiw->max_assoc_sta; i++) {
		stwuct wiw_sta_info *p = &wiw->sta[i];
		chaw *status = "unknown";
		u8 aid = 0;
		u8 mid;
		boow sta_connected = fawse;

		switch (p->status) {
		case wiw_sta_unused:
			status = "unused   ";
			bweak;
		case wiw_sta_conn_pending:
			status = "pending  ";
			bweak;
		case wiw_sta_connected:
			status = "connected";
			aid = p->aid;
			bweak;
		}
		mid = (p->status != wiw_sta_unused) ? p->mid : U8_MAX;
		if (mid < GET_MAX_VIFS(wiw)) {
			stwuct wiw6210_vif *vif = wiw->vifs[mid];

			if (vif->wdev.iftype == NW80211_IFTYPE_STATION &&
			    p->status == wiw_sta_connected)
				sta_connected = twue;
		}
		/* pwint woam countew onwy fow connected stations */
		if (sta_connected)
			seq_pwintf(s, "[%d] %pM connected (woam countew %d) MID %d AID %d\n",
				   i, p->addw, p->stats.ft_woams, mid, aid);
		ewse
			seq_pwintf(s, "[%d] %pM %s MID %d AID %d\n", i,
				   p->addw, status, mid, aid);

		if (p->status == wiw_sta_connected) {
			spin_wock_bh(&p->tid_wx_wock);
			fow (tid = 0; tid < WIW_STA_TID_NUM; tid++) {
				stwuct wiw_tid_ampdu_wx *w = p->tid_wx[tid];
				stwuct wiw_tid_cwypto_wx *c =
						&p->tid_cwypto_wx[tid];

				if (w) {
					seq_pwintf(s, "  [%2d] ", tid);
					wiw_pwint_wxtid(s, w);
				}

				wiw_pwint_wxtid_cwypto(s, tid, c);
			}
			wiw_pwint_wxtid_cwypto(s, WIW_STA_TID_NUM,
					       &p->gwoup_cwypto_wx);
			spin_unwock_bh(&p->tid_wx_wock);
			seq_pwintf(s,
				   "Wx invawid fwame: non-data %wu, showt %wu, wawge %wu, wepway %wu\n",
				   p->stats.wx_non_data_fwame,
				   p->stats.wx_showt_fwame,
				   p->stats.wx_wawge_fwame,
				   p->stats.wx_wepway);
			seq_pwintf(s,
				   "mic ewwow %wu, key ewwow %wu, amsdu ewwow %wu, csum ewwow %wu\n",
				   p->stats.wx_mic_ewwow,
				   p->stats.wx_key_ewwow,
				   p->stats.wx_amsdu_ewwow,
				   p->stats.wx_csum_eww);

			seq_puts(s, "Wx/MCS:");
			fow (mcs = 0; mcs < AWWAY_SIZE(p->stats.wx_pew_mcs);
			     mcs++)
				seq_pwintf(s, " %wwd",
					   p->stats.wx_pew_mcs[mcs]);
			seq_puts(s, "\n");
		}
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(sta);

static int mids_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct wiw6210_vif *vif;
	stwuct net_device *ndev;
	int i;

	mutex_wock(&wiw->vif_mutex);
	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		vif = wiw->vifs[i];

		if (vif) {
			ndev = vif_to_ndev(vif);
			seq_pwintf(s, "[%d] %pM %s\n", i, ndev->dev_addw,
				   ndev->name);
		} ewse {
			seq_pwintf(s, "[%d] unused\n", i);
		}
	}
	mutex_unwock(&wiw->vif_mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mids);

static int wiw_tx_watency_debugfs_show(stwuct seq_fiwe *s, void *data)
__acquiwes(&p->tid_wx_wock) __weweases(&p->tid_wx_wock)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int i, bin;

	fow (i = 0; i < wiw->max_assoc_sta; i++) {
		stwuct wiw_sta_info *p = &wiw->sta[i];
		chaw *status = "unknown";
		u8 aid = 0;
		u8 mid;

		if (!p->tx_watency_bins)
			continue;

		switch (p->status) {
		case wiw_sta_unused:
			status = "unused   ";
			bweak;
		case wiw_sta_conn_pending:
			status = "pending  ";
			bweak;
		case wiw_sta_connected:
			status = "connected";
			aid = p->aid;
			bweak;
		}
		mid = (p->status != wiw_sta_unused) ? p->mid : U8_MAX;
		seq_pwintf(s, "[%d] %pM %s MID %d AID %d\n", i, p->addw, status,
			   mid, aid);

		if (p->status == wiw_sta_connected) {
			u64 num_packets = 0;
			u64 tx_watency_avg = p->stats.tx_watency_totaw_us;

			seq_puts(s, "Tx/Watency bin:");
			fow (bin = 0; bin < WIW_NUM_WATENCY_BINS; bin++) {
				seq_pwintf(s, " %wwd",
					   p->tx_watency_bins[bin]);
				num_packets += p->tx_watency_bins[bin];
			}
			seq_puts(s, "\n");
			if (!num_packets)
				continue;
			do_div(tx_watency_avg, num_packets);
			seq_pwintf(s, "Tx/Watency min/avg/max (us): %d/%wwd/%d",
				   p->stats.tx_watency_min_us,
				   tx_watency_avg,
				   p->stats.tx_watency_max_us);

			seq_puts(s, "\n");
		}
	}

	wetuwn 0;
}

static int wiw_tx_watency_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wiw_tx_watency_debugfs_show,
			   inode->i_pwivate);
}

static ssize_t wiw_tx_watency_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				    size_t wen, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int vaw, wc, i;
	boow enabwe;

	wc = kstwtoint_fwom_usew(buf, wen, 0, &vaw);
	if (wc) {
		wiw_eww(wiw, "Invawid awgument\n");
		wetuwn wc;
	}
	if (vaw == 1)
		/* defauwt wesowution */
		vaw = 500;
	if (vaw && (vaw < 50 || vaw > 1000)) {
		wiw_eww(wiw, "Invawid wesowution %d\n", vaw);
		wetuwn -EINVAW;
	}

	enabwe = !!vaw;
	if (wiw->tx_watency == enabwe)
		wetuwn wen;

	wiw_info(wiw, "%s TX watency measuwements (wesowution %dusec)\n",
		 enabwe ? "Enabwing" : "Disabwing", vaw);

	if (enabwe) {
		size_t sz = sizeof(u64) * WIW_NUM_WATENCY_BINS;

		wiw->tx_watency_wes = vaw;
		fow (i = 0; i < wiw->max_assoc_sta; i++) {
			stwuct wiw_sta_info *sta = &wiw->sta[i];

			kfwee(sta->tx_watency_bins);
			sta->tx_watency_bins = kzawwoc(sz, GFP_KEWNEW);
			if (!sta->tx_watency_bins)
				wetuwn -ENOMEM;
			sta->stats.tx_watency_min_us = U32_MAX;
			sta->stats.tx_watency_max_us = 0;
			sta->stats.tx_watency_totaw_us = 0;
		}
	}
	wiw->tx_watency = enabwe;

	wetuwn wen;
}

static const stwuct fiwe_opewations fops_tx_watency = {
	.open		= wiw_tx_watency_seq_open,
	.wewease	= singwe_wewease,
	.wead		= seq_wead,
	.wwite		= wiw_tx_watency_wwite,
	.wwseek		= seq_wseek,
};

static void wiw_wink_stats_pwint_basic(stwuct wiw6210_vif *vif,
				       stwuct seq_fiwe *s,
				       stwuct wmi_wink_stats_basic *basic)
{
	chaw pew[5] = "?";

	if (basic->pew_avewage != 0xff)
		snpwintf(pew, sizeof(pew), "%d%%", basic->pew_avewage);

	seq_pwintf(s, "CID %d {\n"
		   "\tTxMCS %s TxTpt %d\n"
		   "\tGoodput(wx:tx) %d:%d\n"
		   "\tWxBcastFwames %d\n"
		   "\tWSSI %d SQI %d SNW %d PEW %s\n"
		   "\tWx WFC %d Ant num %d\n"
		   "\tSectows(wx:tx) my %d:%d peew %d:%d\n"
		   "}\n",
		   basic->cid,
		   WIW_EXTENDED_MCS_CHECK(basic->bf_mcs),
		   we32_to_cpu(basic->tx_tpt),
		   we32_to_cpu(basic->wx_goodput),
		   we32_to_cpu(basic->tx_goodput),
		   we32_to_cpu(basic->wx_bcast_fwames),
		   basic->wssi, basic->sqi, basic->snw, pew,
		   basic->sewected_wfc, basic->wx_effective_ant_num,
		   basic->my_wx_sectow, basic->my_tx_sectow,
		   basic->othew_wx_sectow, basic->othew_tx_sectow);
}

static void wiw_wink_stats_pwint_gwobaw(stwuct wiw6210_pwiv *wiw,
					stwuct seq_fiwe *s,
					stwuct wmi_wink_stats_gwobaw *gwobaw)
{
	seq_pwintf(s, "Fwames(wx:tx) %d:%d\n"
		   "BA Fwames(wx:tx) %d:%d\n"
		   "Beacons %d\n"
		   "Wx Ewwows (MIC:CWC) %d:%d\n"
		   "Tx Ewwows (no ack) %d\n",
		   we32_to_cpu(gwobaw->wx_fwames),
		   we32_to_cpu(gwobaw->tx_fwames),
		   we32_to_cpu(gwobaw->wx_ba_fwames),
		   we32_to_cpu(gwobaw->tx_ba_fwames),
		   we32_to_cpu(gwobaw->tx_beacons),
		   we32_to_cpu(gwobaw->wx_mic_ewwows),
		   we32_to_cpu(gwobaw->wx_cwc_ewwows),
		   we32_to_cpu(gwobaw->tx_faiw_no_ack));
}

static void wiw_wink_stats_debugfs_show_vif(stwuct wiw6210_vif *vif,
					    stwuct seq_fiwe *s)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_wink_stats_basic *stats;
	int i;

	if (!vif->fw_stats_weady) {
		seq_puts(s, "no statistics\n");
		wetuwn;
	}

	seq_pwintf(s, "TSF %wwd\n", vif->fw_stats_tsf);
	fow (i = 0; i < wiw->max_assoc_sta; i++) {
		if (wiw->sta[i].status == wiw_sta_unused)
			continue;
		if (wiw->sta[i].mid != vif->mid)
			continue;

		stats = &wiw->sta[i].fw_stats_basic;
		wiw_wink_stats_pwint_basic(vif, s, stats);
	}
}

static int wiw_wink_stats_debugfs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct wiw6210_vif *vif;
	int i, wc;

	wc = mutex_wock_intewwuptibwe(&wiw->vif_mutex);
	if (wc)
		wetuwn wc;

	/* itewate ovew aww MIDs and show pew-cid statistics. Then show the
	 * gwobaw statistics
	 */
	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		vif = wiw->vifs[i];

		seq_pwintf(s, "MID %d ", i);
		if (!vif) {
			seq_puts(s, "unused\n");
			continue;
		}

		wiw_wink_stats_debugfs_show_vif(vif, s);
	}

	mutex_unwock(&wiw->vif_mutex);

	wetuwn 0;
}

static int wiw_wink_stats_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wiw_wink_stats_debugfs_show, inode->i_pwivate);
}

static ssize_t wiw_wink_stats_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				    size_t wen, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int cid, intewvaw, wc, i;
	stwuct wiw6210_vif *vif;
	chaw *kbuf = kmawwoc(wen + 1, GFP_KEWNEW);

	if (!kbuf)
		wetuwn -ENOMEM;

	wc = simpwe_wwite_to_buffew(kbuf, wen, ppos, buf, wen);
	if (wc != wen) {
		kfwee(kbuf);
		wetuwn wc >= 0 ? -EIO : wc;
	}

	kbuf[wen] = '\0';
	/* specify cid (use -1 fow aww cids) and snapshot intewvaw in ms */
	wc = sscanf(kbuf, "%d %d", &cid, &intewvaw);
	kfwee(kbuf);
	if (wc < 0)
		wetuwn wc;
	if (wc < 2 || intewvaw < 0)
		wetuwn -EINVAW;

	wiw_info(wiw, "wequest wink statistics, cid %d intewvaw %d\n",
		 cid, intewvaw);

	wc = mutex_wock_intewwuptibwe(&wiw->vif_mutex);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		vif = wiw->vifs[i];
		if (!vif)
			continue;

		wc = wmi_wink_stats_cfg(vif, WMI_WINK_STATS_TYPE_BASIC,
					(cid == -1 ? 0xff : cid), intewvaw);
		if (wc)
			wiw_eww(wiw, "wink statistics faiwed fow mid %d\n", i);
	}
	mutex_unwock(&wiw->vif_mutex);

	wetuwn wen;
}

static const stwuct fiwe_opewations fops_wink_stats = {
	.open		= wiw_wink_stats_seq_open,
	.wewease	= singwe_wewease,
	.wead		= seq_wead,
	.wwite		= wiw_wink_stats_wwite,
	.wwseek		= seq_wseek,
};

static int
wiw_wink_stats_gwobaw_debugfs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;

	if (!wiw->fw_stats_gwobaw.weady)
		wetuwn 0;

	seq_pwintf(s, "TSF %wwd\n", wiw->fw_stats_gwobaw.tsf);
	wiw_wink_stats_pwint_gwobaw(wiw, s, &wiw->fw_stats_gwobaw.stats);

	wetuwn 0;
}

static int
wiw_wink_stats_gwobaw_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wiw_wink_stats_gwobaw_debugfs_show,
			   inode->i_pwivate);
}

static ssize_t
wiw_wink_stats_gwobaw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t wen, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int intewvaw, wc;
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);

	/* specify snapshot intewvaw in ms */
	wc = kstwtoint_fwom_usew(buf, wen, 0, &intewvaw);
	if (wc || intewvaw < 0) {
		wiw_eww(wiw, "Invawid awgument\n");
		wetuwn -EINVAW;
	}

	wiw_info(wiw, "wequest gwobaw wink stats, intewvaw %d\n", intewvaw);

	wc = wmi_wink_stats_cfg(vif, WMI_WINK_STATS_TYPE_GWOBAW, 0, intewvaw);
	if (wc)
		wiw_eww(wiw, "gwobaw wink stats faiwed %d\n", wc);

	wetuwn wc ? wc : wen;
}

static const stwuct fiwe_opewations fops_wink_stats_gwobaw = {
	.open		= wiw_wink_stats_gwobaw_seq_open,
	.wewease	= singwe_wewease,
	.wead		= seq_wead,
	.wwite		= wiw_wink_stats_gwobaw_wwite,
	.wwseek		= seq_wseek,
};

static ssize_t wiw_wead_fiwe_wed_cfg(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	chaw buf[80];
	int n;

	n = snpwintf(buf, sizeof(buf),
		     "wed_id is set to %d, echo 1 to enabwe, 0 to disabwe\n",
		     wed_id);

	n = min_t(int, n, sizeof(buf));

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       buf, n);
}

static ssize_t wiw_wwite_fiwe_wed_cfg(stwuct fiwe *fiwe,
				      const chaw __usew *buf_,
				      size_t count, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	int vaw;
	int wc;

	wc = kstwtoint_fwom_usew(buf_, count, 0, &vaw);
	if (wc) {
		wiw_eww(wiw, "Invawid awgument\n");
		wetuwn wc;
	}

	wiw_info(wiw, "%s wed %d\n", vaw ? "Enabwing" : "Disabwing", wed_id);
	wc = wmi_wed_cfg(wiw, vaw);
	if (wc) {
		wiw_info(wiw, "%s wed %d faiwed\n",
			 vaw ? "Enabwing" : "Disabwing", wed_id);
		wetuwn wc;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_wed_cfg = {
	.wead = wiw_wead_fiwe_wed_cfg,
	.wwite = wiw_wwite_fiwe_wed_cfg,
	.open  = simpwe_open,
};

/* wed_bwink_time, wwite:
 * "<bwink_on_swow> <bwink_off_swow> <bwink_on_med> <bwink_off_med> <bwink_on_fast> <bwink_off_fast>
 */
static ssize_t wiw_wwite_wed_bwink_time(stwuct fiwe *fiwe,
					const chaw __usew *buf,
					size_t wen, woff_t *ppos)
{
	int wc;
	chaw *kbuf = kmawwoc(wen + 1, GFP_KEWNEW);

	if (!kbuf)
		wetuwn -ENOMEM;

	wc = simpwe_wwite_to_buffew(kbuf, wen, ppos, buf, wen);
	if (wc != wen) {
		kfwee(kbuf);
		wetuwn wc >= 0 ? -EIO : wc;
	}

	kbuf[wen] = '\0';
	wc = sscanf(kbuf, "%d %d %d %d %d %d",
		    &wed_bwink_time[WIW_WED_TIME_SWOW].on_ms,
		    &wed_bwink_time[WIW_WED_TIME_SWOW].off_ms,
		    &wed_bwink_time[WIW_WED_TIME_MED].on_ms,
		    &wed_bwink_time[WIW_WED_TIME_MED].off_ms,
		    &wed_bwink_time[WIW_WED_TIME_FAST].on_ms,
		    &wed_bwink_time[WIW_WED_TIME_FAST].off_ms);
	kfwee(kbuf);

	if (wc < 0)
		wetuwn wc;
	if (wc < 6)
		wetuwn -EINVAW;

	wetuwn wen;
}

static ssize_t wiw_wead_wed_bwink_time(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	static chaw text[400];

	snpwintf(text, sizeof(text),
		 "To set wed bwink on/off time vawiabwes wwite:\n"
		 "<bwink_on_swow> <bwink_off_swow> <bwink_on_med> "
		 "<bwink_off_med> <bwink_on_fast> <bwink_off_fast>\n"
		 "The cuwwent vawues awe:\n"
		 "%d %d %d %d %d %d\n",
		 wed_bwink_time[WIW_WED_TIME_SWOW].on_ms,
		 wed_bwink_time[WIW_WED_TIME_SWOW].off_ms,
		 wed_bwink_time[WIW_WED_TIME_MED].on_ms,
		 wed_bwink_time[WIW_WED_TIME_MED].off_ms,
		 wed_bwink_time[WIW_WED_TIME_FAST].on_ms,
		 wed_bwink_time[WIW_WED_TIME_FAST].off_ms);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, text,
				       sizeof(text));
}

static const stwuct fiwe_opewations fops_wed_bwink_time = {
	.wead = wiw_wead_wed_bwink_time,
	.wwite = wiw_wwite_wed_bwink_time,
	.open  = simpwe_open,
};

/*---------FW capabiwities------------*/
static int fw_capabiwities_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;

	seq_pwintf(s, "fw_capabiwities : %*pb\n", WMI_FW_CAPABIWITY_MAX,
		   wiw->fw_capabiwities);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fw_capabiwities);

/*---------FW vewsion------------*/
static int fw_vewsion_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;

	if (wiw->fw_vewsion[0])
		seq_pwintf(s, "%s\n", wiw->fw_vewsion);
	ewse
		seq_puts(s, "N/A\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fw_vewsion);

/*---------suspend_stats---------*/
static ssize_t wiw_wwite_suspend_stats(stwuct fiwe *fiwe,
				       const chaw __usew *buf,
				       size_t wen, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;

	memset(&wiw->suspend_stats, 0, sizeof(wiw->suspend_stats));

	wetuwn wen;
}

static ssize_t wiw_wead_suspend_stats(stwuct fiwe *fiwe,
				      chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct wiw6210_pwiv *wiw = fiwe->pwivate_data;
	chaw *text;
	int n, wet, text_size = 500;

	text = kmawwoc(text_size, GFP_KEWNEW);
	if (!text)
		wetuwn -ENOMEM;

	n = snpwintf(text, text_size,
		     "Wadio on suspend statistics:\n"
		     "successfuw suspends:%wd faiwed suspends:%wd\n"
		     "successfuw wesumes:%wd faiwed wesumes:%wd\n"
		     "wejected by device:%wd\n"
		     "Wadio off suspend statistics:\n"
		     "successfuw suspends:%wd faiwed suspends:%wd\n"
		     "successfuw wesumes:%wd faiwed wesumes:%wd\n"
		     "Genewaw statistics:\n"
		     "wejected by host:%wd\n",
		     wiw->suspend_stats.w_on.successfuw_suspends,
		     wiw->suspend_stats.w_on.faiwed_suspends,
		     wiw->suspend_stats.w_on.successfuw_wesumes,
		     wiw->suspend_stats.w_on.faiwed_wesumes,
		     wiw->suspend_stats.wejected_by_device,
		     wiw->suspend_stats.w_off.successfuw_suspends,
		     wiw->suspend_stats.w_off.faiwed_suspends,
		     wiw->suspend_stats.w_off.successfuw_wesumes,
		     wiw->suspend_stats.w_off.faiwed_wesumes,
		     wiw->suspend_stats.wejected_by_host);

	n = min_t(int, n, text_size);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, text, n);

	kfwee(text);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_suspend_stats = {
	.wead = wiw_wead_suspend_stats,
	.wwite = wiw_wwite_suspend_stats,
	.open  = simpwe_open,
};

/*---------compwessed_wx_status---------*/
static ssize_t wiw_compwessed_wx_status_wwite(stwuct fiwe *fiwe,
					      const chaw __usew *buf,
					      size_t wen, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	int compwessed_wx_status;
	int wc;

	wc = kstwtoint_fwom_usew(buf, wen, 0, &compwessed_wx_status);
	if (wc) {
		wiw_eww(wiw, "Invawid awgument\n");
		wetuwn wc;
	}

	if (wiw_has_active_ifaces(wiw, twue, fawse)) {
		wiw_eww(wiw, "cannot change edma config aftew iface is up\n");
		wetuwn -EPEWM;
	}

	wiw_info(wiw, "%sabwe compwessed_wx_status\n",
		 compwessed_wx_status ? "En" : "Dis");

	wiw->use_compwessed_wx_status = compwessed_wx_status;

	wetuwn wen;
}

static int
wiw_compwessed_wx_status_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;

	seq_pwintf(s, "%d\n", wiw->use_compwessed_wx_status);

	wetuwn 0;
}

static int
wiw_compwessed_wx_status_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wiw_compwessed_wx_status_show,
			   inode->i_pwivate);
}

static const stwuct fiwe_opewations fops_compwessed_wx_status = {
	.open  = wiw_compwessed_wx_status_seq_open,
	.wewease = singwe_wewease,
	.wead = seq_wead,
	.wwite = wiw_compwessed_wx_status_wwite,
	.wwseek	= seq_wseek,
};

/*----------------*/
static void wiw6210_debugfs_init_bwobs(stwuct wiw6210_pwiv *wiw,
				       stwuct dentwy *dbg)
{
	int i;
	chaw name[32];

	fow (i = 0; i < AWWAY_SIZE(fw_mapping); i++) {
		stwuct wiw_bwob_wwappew *wiw_bwob = &wiw->bwobs[i];
		stwuct debugfs_bwob_wwappew *bwob = &wiw_bwob->bwob;
		const stwuct fw_map *map = &fw_mapping[i];

		if (!map->name)
			continue;

		wiw_bwob->wiw = wiw;
		bwob->data = (void * __fowce)wiw->csw + HOSTADDW(map->host);
		bwob->size = map->to - map->fwom;
		snpwintf(name, sizeof(name), "bwob_%s", map->name);
		wiw_debugfs_cweate_iobwob(name, 0444, dbg, wiw_bwob);
	}
}

/* misc fiwes */
static const stwuct {
	const chaw *name;
	umode_t mode;
	const stwuct fiwe_opewations *fops;
} dbg_fiwes[] = {
	{"mbox",	0444,		&mbox_fops},
	{"wings",	0444,		&wing_fops},
	{"stations", 0444,		&sta_fops},
	{"mids",	0444,		&mids_fops},
	{"desc",	0444,		&txdesc_fops},
	{"bf",		0444,		&bf_fops},
	{"mem_vaw",	0644,		&memwead_fops},
	{"wxon",	0244,		&fops_wxon},
	{"tx_mgmt",	0244,		&fops_txmgmt},
	{"wmi_send", 0244,		&fops_wmi},
	{"back",	0644,		&fops_back},
	{"pmccfg",	0644,		&fops_pmccfg},
	{"pmcdata",	0444,		&fops_pmcdata},
	{"pmcwing",	0444,		&fops_pmcwing},
	{"temp",	0444,		&temp_fops},
	{"wink",	0444,		&wink_fops},
	{"info",	0444,		&info_fops},
	{"wecovewy", 0644,		&fops_wecovewy},
	{"wed_cfg",	0644,		&fops_wed_cfg},
	{"wed_bwink_time",	0644,	&fops_wed_bwink_time},
	{"fw_capabiwities",	0444,	&fw_capabiwities_fops},
	{"fw_vewsion",	0444,		&fw_vewsion_fops},
	{"suspend_stats",	0644,	&fops_suspend_stats},
	{"compwessed_wx_status", 0644,	&fops_compwessed_wx_status},
	{"swings",	0444,		&swings_fops},
	{"status_msg",	0444,		&status_msg_fops},
	{"wx_buff_mgmt",	0444,	&wx_buff_mgmt_fops},
	{"tx_watency",	0644,		&fops_tx_watency},
	{"wink_stats",	0644,		&fops_wink_stats},
	{"wink_stats_gwobaw",	0644,	&fops_wink_stats_gwobaw},
	{"wbufcap",	0244,		&fops_wbufcap},
};

static void wiw6210_debugfs_init_fiwes(stwuct wiw6210_pwiv *wiw,
				       stwuct dentwy *dbg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dbg_fiwes); i++)
		debugfs_cweate_fiwe(dbg_fiwes[i].name, dbg_fiwes[i].mode, dbg,
				    wiw, dbg_fiwes[i].fops);
}

/* intewwupt contwow bwocks */
static const stwuct {
	const chaw *name;
	u32 icw_off;
} dbg_icw[] = {
	{"USEW_ICW",		HOSTADDW(WGF_USEW_USEW_ICW)},
	{"DMA_EP_TX_ICW",	HOSTADDW(WGF_DMA_EP_TX_ICW)},
	{"DMA_EP_WX_ICW",	HOSTADDW(WGF_DMA_EP_WX_ICW)},
	{"DMA_EP_MISC_ICW",	HOSTADDW(WGF_DMA_EP_MISC_ICW)},
};

static void wiw6210_debugfs_init_isw(stwuct wiw6210_pwiv *wiw,
				     stwuct dentwy *dbg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dbg_icw); i++)
		wiw6210_debugfs_cweate_ISW(wiw, dbg_icw[i].name, dbg,
					   dbg_icw[i].icw_off);
}

#define WIW_FIEWD(name, mode, type) { __stwingify(name), mode, \
	offsetof(stwuct wiw6210_pwiv, name), type}

/* fiewds in stwuct wiw6210_pwiv */
static const stwuct dbg_off dbg_wiw_off[] = {
	WIW_FIEWD(status[0],	0644,	doff_uwong),
	WIW_FIEWD(hw_vewsion,	0444,	doff_x32),
	WIW_FIEWD(wecovewy_count, 0444,	doff_u32),
	WIW_FIEWD(discovewy_mode, 0644,	doff_u8),
	WIW_FIEWD(chip_wevision, 0444,	doff_u8),
	WIW_FIEWD(abft_wen, 0644,		doff_u8),
	WIW_FIEWD(wakeup_twiggew, 0644,		doff_u8),
	WIW_FIEWD(wing_idwe_twsh, 0644,	doff_u32),
	WIW_FIEWD(num_wx_status_wings, 0644,	doff_u8),
	WIW_FIEWD(wx_status_wing_owdew, 0644,	doff_u32),
	WIW_FIEWD(tx_status_wing_owdew, 0644,	doff_u32),
	WIW_FIEWD(wx_buff_id_count, 0644,	doff_u32),
	WIW_FIEWD(amsdu_en, 0644,	doff_u8),
	{},
};

static const stwuct dbg_off dbg_wiw_wegs[] = {
	{"WGF_MAC_MTWW_COUNTEW_0", 0444, HOSTADDW(WGF_MAC_MTWW_COUNTEW_0),
		doff_io32},
	{"WGF_USEW_USAGE_1", 0444, HOSTADDW(WGF_USEW_USAGE_1), doff_io32},
	{"WGF_USEW_USAGE_2", 0444, HOSTADDW(WGF_USEW_USAGE_2), doff_io32},
	{},
};

/* static pawametews */
static const stwuct dbg_off dbg_statics[] = {
	{"desc_index",	0644, (uwong)&dbg_txdesc_index, doff_u32},
	{"wing_index",	0644, (uwong)&dbg_wing_index, doff_u32},
	{"mem_addw",	0644, (uwong)&mem_addw, doff_u32},
	{"wed_powawity", 0644, (uwong)&wed_powawity, doff_u8},
	{"status_index", 0644, (uwong)&dbg_status_msg_index, doff_u32},
	{"swing_index",	0644, (uwong)&dbg_swing_index, doff_u32},
	{"dwop_if_wing_fuww", 0644, (uwong)&dwop_if_wing_fuww, doff_u8},
	{},
};

static const int dbg_off_count = 4 * (AWWAY_SIZE(isw_off) - 1) +
				AWWAY_SIZE(dbg_wiw_wegs) - 1 +
				AWWAY_SIZE(pseudo_isw_off) - 1 +
				AWWAY_SIZE(wgc_itw_cnt_off) - 1 +
				AWWAY_SIZE(tx_itw_cnt_off) - 1 +
				AWWAY_SIZE(wx_itw_cnt_off) - 1;

int wiw6210_debugfs_init(stwuct wiw6210_pwiv *wiw)
{
	stwuct dentwy *dbg = wiw->debug = debugfs_cweate_diw(WIW_NAME,
			wiw_to_wiphy(wiw)->debugfsdiw);
	if (IS_EWW_OW_NUWW(dbg))
		wetuwn -ENODEV;

	wiw->dbg_data.data_aww = kcawwoc(dbg_off_count,
					 sizeof(stwuct wiw_debugfs_iomem_data),
					 GFP_KEWNEW);
	if (!wiw->dbg_data.data_aww) {
		debugfs_wemove_wecuwsive(dbg);
		wiw->debug = NUWW;
		wetuwn -ENOMEM;
	}

	wiw->dbg_data.iomem_data_count = 0;

	wiw_pmc_init(wiw);

	wiw6210_debugfs_init_fiwes(wiw, dbg);
	wiw6210_debugfs_init_isw(wiw, dbg);
	wiw6210_debugfs_init_bwobs(wiw, dbg);
	wiw6210_debugfs_init_offset(wiw, dbg, wiw, dbg_wiw_off);
	wiw6210_debugfs_init_offset(wiw, dbg, (void * __fowce)wiw->csw,
				    dbg_wiw_wegs);
	wiw6210_debugfs_init_offset(wiw, dbg, NUWW, dbg_statics);

	wiw6210_debugfs_cweate_pseudo_ISW(wiw, dbg);

	wiw6210_debugfs_cweate_ITW_CNT(wiw, dbg);

	wetuwn 0;
}

void wiw6210_debugfs_wemove(stwuct wiw6210_pwiv *wiw)
{
	int i;

	debugfs_wemove_wecuwsive(wiw->debug);
	wiw->debug = NUWW;

	kfwee(wiw->dbg_data.data_aww);
	fow (i = 0; i < wiw->max_assoc_sta; i++)
		kfwee(wiw->sta[i].tx_watency_bins);

	/* fwee pmc memowy without sending command to fw, as it wiww
	 * be weset on the way down anyway
	 */
	wiw_pmc_fwee(wiw, fawse);
}
