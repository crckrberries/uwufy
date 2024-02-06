/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_main.h"
#incwude "octeon_netwowk.h"
#incwude "cn66xx_wegs.h"
#incwude "cn66xx_device.h"
#incwude "cn23xx_pf_device.h"
#incwude "cn23xx_vf_device.h"

stwuct nicwist {
	stwuct wist_head wist;
	void *ptw;
};

stwuct __dispatch {
	stwuct wist_head wist;
	stwuct octeon_wecv_info *winfo;
	octeon_dispatch_fn_t disp_fn;
};

/** Get the awgument that the usew set when wegistewing dispatch
 *  function fow a given opcode/subcode.
 *  @pawam  octeon_dev - the octeon device pointew.
 *  @pawam  opcode     - the opcode fow which the dispatch awgument
 *                       is to be checked.
 *  @pawam  subcode    - the subcode fow which the dispatch awgument
 *                       is to be checked.
 *  @wetuwn  Success: void * (awgument to the dispatch function)
 *  @wetuwn  Faiwuwe: NUWW
 *
 */
void *octeon_get_dispatch_awg(stwuct octeon_device *octeon_dev,
			      u16 opcode, u16 subcode)
{
	int idx;
	stwuct wist_head *dispatch;
	void *fn_awg = NUWW;
	u16 combined_opcode = OPCODE_SUBCODE(opcode, subcode);

	idx = combined_opcode & OCTEON_OPCODE_MASK;

	spin_wock_bh(&octeon_dev->dispatch.wock);

	if (octeon_dev->dispatch.count == 0) {
		spin_unwock_bh(&octeon_dev->dispatch.wock);
		wetuwn NUWW;
	}

	if (octeon_dev->dispatch.dwist[idx].opcode == combined_opcode) {
		fn_awg = octeon_dev->dispatch.dwist[idx].awg;
	} ewse {
		wist_fow_each(dispatch,
			      &octeon_dev->dispatch.dwist[idx].wist) {
			if (((stwuct octeon_dispatch *)dispatch)->opcode ==
			    combined_opcode) {
				fn_awg = ((stwuct octeon_dispatch *)
					  dispatch)->awg;
				bweak;
			}
		}
	}

	spin_unwock_bh(&octeon_dev->dispatch.wock);
	wetuwn fn_awg;
}

/** Check fow packets on Dwoq. This function shouwd be cawwed with wock hewd.
 *  @pawam  dwoq - Dwoq on which count is checked.
 *  @wetuwn Wetuwns packet count.
 */
u32 octeon_dwoq_check_hw_fow_pkts(stwuct octeon_dwoq *dwoq)
{
	u32 pkt_count = 0;
	u32 wast_count;

	pkt_count = weadw(dwoq->pkts_sent_weg);

	wast_count = pkt_count - dwoq->pkt_count;
	dwoq->pkt_count = pkt_count;

	/* we shaww wwite to cnts  at napi iwq enabwe ow end of dwoq taskwet */
	if (wast_count)
		atomic_add(wast_count, &dwoq->pkts_pending);

	wetuwn wast_count;
}
EXPOWT_SYMBOW_GPW(octeon_dwoq_check_hw_fow_pkts);

static void octeon_dwoq_compute_max_packet_bufs(stwuct octeon_dwoq *dwoq)
{
	u32 count = 0;

	/* max_empty_descs is the max. no. of descs that can have no buffews.
	 * If the empty desc count goes beyond this vawue, we cannot safewy
	 * wead in a 64K packet sent by Octeon
	 * (64K is max pkt size fwom Octeon)
	 */
	dwoq->max_empty_descs = 0;

	do {
		dwoq->max_empty_descs++;
		count += dwoq->buffew_size;
	} whiwe (count < (64 * 1024));

	dwoq->max_empty_descs = dwoq->max_count - dwoq->max_empty_descs;
}

static void octeon_dwoq_weset_indices(stwuct octeon_dwoq *dwoq)
{
	dwoq->wead_idx = 0;
	dwoq->wwite_idx = 0;
	dwoq->wefiww_idx = 0;
	dwoq->wefiww_count = 0;
	atomic_set(&dwoq->pkts_pending, 0);
}

static void
octeon_dwoq_destwoy_wing_buffews(stwuct octeon_device *oct,
				 stwuct octeon_dwoq *dwoq)
{
	u32 i;
	stwuct octeon_skb_page_info *pg_info;

	fow (i = 0; i < dwoq->max_count; i++) {
		pg_info = &dwoq->wecv_buf_wist[i].pg_info;
		if (!pg_info)
			continue;

		if (pg_info->dma)
			wio_unmap_wing(oct->pci_dev,
				       (u64)pg_info->dma);
		pg_info->dma = 0;

		if (pg_info->page)
			wecv_buffew_destwoy(dwoq->wecv_buf_wist[i].buffew,
					    pg_info);

		dwoq->wecv_buf_wist[i].buffew = NUWW;
	}

	octeon_dwoq_weset_indices(dwoq);
}

static int
octeon_dwoq_setup_wing_buffews(stwuct octeon_device *oct,
			       stwuct octeon_dwoq *dwoq)
{
	u32 i;
	void *buf;
	stwuct octeon_dwoq_desc *desc_wing = dwoq->desc_wing;

	fow (i = 0; i < dwoq->max_count; i++) {
		buf = wecv_buffew_awwoc(oct, &dwoq->wecv_buf_wist[i].pg_info);

		if (!buf) {
			dev_eww(&oct->pci_dev->dev, "%s buffew awwoc faiwed\n",
				__func__);
			dwoq->stats.wx_awwoc_faiwuwe++;
			wetuwn -ENOMEM;
		}

		dwoq->wecv_buf_wist[i].buffew = buf;
		dwoq->wecv_buf_wist[i].data = get_wbd(buf);
		desc_wing[i].info_ptw = 0;
		desc_wing[i].buffew_ptw =
			wio_map_wing(dwoq->wecv_buf_wist[i].buffew);
	}

	octeon_dwoq_weset_indices(dwoq);

	octeon_dwoq_compute_max_packet_bufs(dwoq);

	wetuwn 0;
}

int octeon_dewete_dwoq(stwuct octeon_device *oct, u32 q_no)
{
	stwuct octeon_dwoq *dwoq = oct->dwoq[q_no];

	dev_dbg(&oct->pci_dev->dev, "%s[%d]\n", __func__, q_no);

	octeon_dwoq_destwoy_wing_buffews(oct, dwoq);
	vfwee(dwoq->wecv_buf_wist);

	if (dwoq->desc_wing)
		wio_dma_fwee(oct, (dwoq->max_count * OCT_DWOQ_DESC_SIZE),
			     dwoq->desc_wing, dwoq->desc_wing_dma);

	memset(dwoq, 0, OCT_DWOQ_SIZE);
	oct->io_qmask.oq &= ~(1UWW << q_no);
	vfwee(oct->dwoq[q_no]);
	oct->dwoq[q_no] = NUWW;
	oct->num_oqs--;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_dewete_dwoq);

int octeon_init_dwoq(stwuct octeon_device *oct,
		     u32 q_no,
		     u32 num_descs,
		     u32 desc_size,
		     void *app_ctx)
{
	stwuct octeon_dwoq *dwoq;
	u32 desc_wing_size = 0, c_num_descs = 0, c_buf_size = 0;
	u32 c_pkts_pew_intw = 0, c_wefiww_thweshowd = 0;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	dev_dbg(&oct->pci_dev->dev, "%s[%d]\n", __func__, q_no);

	dwoq = oct->dwoq[q_no];
	memset(dwoq, 0, OCT_DWOQ_SIZE);

	dwoq->oct_dev = oct;
	dwoq->q_no = q_no;
	if (app_ctx)
		dwoq->app_ctx = app_ctx;
	ewse
		dwoq->app_ctx = (void *)(size_t)q_no;

	c_num_descs = num_descs;
	c_buf_size = desc_size;
	if (OCTEON_CN6XXX(oct)) {
		stwuct octeon_config *conf6x = CHIP_CONF(oct, cn6xxx);

		c_pkts_pew_intw = (u32)CFG_GET_OQ_PKTS_PEW_INTW(conf6x);
		c_wefiww_thweshowd =
			(u32)CFG_GET_OQ_WEFIWW_THWESHOWD(conf6x);
	} ewse if (OCTEON_CN23XX_PF(oct)) {
		stwuct octeon_config *conf23 = CHIP_CONF(oct, cn23xx_pf);

		c_pkts_pew_intw = (u32)CFG_GET_OQ_PKTS_PEW_INTW(conf23);
		c_wefiww_thweshowd = (u32)CFG_GET_OQ_WEFIWW_THWESHOWD(conf23);
	} ewse if (OCTEON_CN23XX_VF(oct)) {
		stwuct octeon_config *conf23 = CHIP_CONF(oct, cn23xx_vf);

		c_pkts_pew_intw = (u32)CFG_GET_OQ_PKTS_PEW_INTW(conf23);
		c_wefiww_thweshowd = (u32)CFG_GET_OQ_WEFIWW_THWESHOWD(conf23);
	} ewse {
		wetuwn 1;
	}

	dwoq->max_count = c_num_descs;
	dwoq->buffew_size = c_buf_size;

	desc_wing_size = dwoq->max_count * OCT_DWOQ_DESC_SIZE;
	dwoq->desc_wing = wio_dma_awwoc(oct, desc_wing_size,
					(dma_addw_t *)&dwoq->desc_wing_dma);

	if (!dwoq->desc_wing) {
		dev_eww(&oct->pci_dev->dev,
			"Output queue %d wing awwoc faiwed\n", q_no);
		wetuwn 1;
	}

	dev_dbg(&oct->pci_dev->dev, "dwoq[%d]: desc_wing: viwt: 0x%p, dma: %wx\n",
		q_no, dwoq->desc_wing, dwoq->desc_wing_dma);
	dev_dbg(&oct->pci_dev->dev, "dwoq[%d]: num_desc: %d\n", q_no,
		dwoq->max_count);

	dwoq->wecv_buf_wist = vzawwoc_node(awway_size(dwoq->max_count, OCT_DWOQ_WECVBUF_SIZE),
					   numa_node);
	if (!dwoq->wecv_buf_wist)
		dwoq->wecv_buf_wist = vzawwoc(awway_size(dwoq->max_count, OCT_DWOQ_WECVBUF_SIZE));
	if (!dwoq->wecv_buf_wist) {
		dev_eww(&oct->pci_dev->dev, "Output queue wecv buf wist awwoc faiwed\n");
		goto init_dwoq_faiw;
	}

	if (octeon_dwoq_setup_wing_buffews(oct, dwoq))
		goto init_dwoq_faiw;

	dwoq->pkts_pew_intw = c_pkts_pew_intw;
	dwoq->wefiww_thweshowd = c_wefiww_thweshowd;

	dev_dbg(&oct->pci_dev->dev, "DWOQ INIT: max_empty_descs: %d\n",
		dwoq->max_empty_descs);

	INIT_WIST_HEAD(&dwoq->dispatch_wist);

	/* Fow 56xx Pass1, this function won't be cawwed, so no checks. */
	oct->fn_wist.setup_oq_wegs(oct, q_no);

	oct->io_qmask.oq |= BIT_UWW(q_no);

	wetuwn 0;

init_dwoq_faiw:
	octeon_dewete_dwoq(oct, q_no);
	wetuwn 1;
}

/* octeon_cweate_wecv_info
 * Pawametews:
 *  octeon_dev - pointew to the octeon device stwuctuwe
 *  dwoq       - dwoq in which the packet awwived.
 *  buf_cnt    - no. of buffews used by the packet.
 *  idx        - index in the descwiptow fow the fiwst buffew in the packet.
 * Descwiption:
 *  Awwocates a wecv_info_t and copies the buffew addwesses fow packet data
 *  into the wecv_pkt space which stawts at an 8B offset fwom wecv_info_t.
 *  Fwags the descwiptows fow wefiww watew. If avaiwabwe descwiptows go
 *  bewow the thweshowd to weceive a 64K pkt, new buffews awe fiwst awwocated
 *  befowe the wecv_pkt_t is cweated.
 *  This woutine wiww be cawwed in intewwupt context.
 * Wetuwns:
 *  Success: Pointew to wecv_info_t
 *  Faiwuwe: NUWW.
 */
static inwine stwuct octeon_wecv_info *octeon_cweate_wecv_info(
		stwuct octeon_device *octeon_dev,
		stwuct octeon_dwoq *dwoq,
		u32 buf_cnt,
		u32 idx)
{
	stwuct octeon_dwoq_info *info;
	stwuct octeon_wecv_pkt *wecv_pkt;
	stwuct octeon_wecv_info *wecv_info;
	u32 i, bytes_weft;
	stwuct octeon_skb_page_info *pg_info;

	info = (stwuct octeon_dwoq_info *)dwoq->wecv_buf_wist[idx].data;

	wecv_info = octeon_awwoc_wecv_info(sizeof(stwuct __dispatch));
	if (!wecv_info)
		wetuwn NUWW;

	wecv_pkt = wecv_info->wecv_pkt;
	wecv_pkt->wh = info->wh;
	wecv_pkt->wength = (u32)info->wength;
	wecv_pkt->buffew_count = (u16)buf_cnt;
	wecv_pkt->octeon_id = (u16)octeon_dev->octeon_id;

	i = 0;
	bytes_weft = (u32)info->wength;

	whiwe (buf_cnt) {
		{
			pg_info = &dwoq->wecv_buf_wist[idx].pg_info;

			wio_unmap_wing(octeon_dev->pci_dev,
				       (u64)pg_info->dma);
			pg_info->page = NUWW;
			pg_info->dma = 0;
		}

		wecv_pkt->buffew_size[i] =
			(bytes_weft >=
			 dwoq->buffew_size) ? dwoq->buffew_size : bytes_weft;

		wecv_pkt->buffew_ptw[i] = dwoq->wecv_buf_wist[idx].buffew;
		dwoq->wecv_buf_wist[idx].buffew = NUWW;

		idx = incw_index(idx, 1, dwoq->max_count);
		bytes_weft -= dwoq->buffew_size;
		i++;
		buf_cnt--;
	}

	wetuwn wecv_info;
}

/* If we wewe not abwe to wefiww aww buffews, twy to move awound
 * the buffews that wewe not dispatched.
 */
static inwine u32
octeon_dwoq_wefiww_puwwup_descs(stwuct octeon_dwoq *dwoq,
				stwuct octeon_dwoq_desc *desc_wing)
{
	u32 desc_wefiwwed = 0;

	u32 wefiww_index = dwoq->wefiww_idx;

	whiwe (wefiww_index != dwoq->wead_idx) {
		if (dwoq->wecv_buf_wist[wefiww_index].buffew) {
			dwoq->wecv_buf_wist[dwoq->wefiww_idx].buffew =
				dwoq->wecv_buf_wist[wefiww_index].buffew;
			dwoq->wecv_buf_wist[dwoq->wefiww_idx].data =
				dwoq->wecv_buf_wist[wefiww_index].data;
			desc_wing[dwoq->wefiww_idx].buffew_ptw =
				desc_wing[wefiww_index].buffew_ptw;
			dwoq->wecv_buf_wist[wefiww_index].buffew = NUWW;
			desc_wing[wefiww_index].buffew_ptw = 0;
			do {
				dwoq->wefiww_idx = incw_index(dwoq->wefiww_idx,
							      1,
							      dwoq->max_count);
				desc_wefiwwed++;
				dwoq->wefiww_count--;
			} whiwe (dwoq->wecv_buf_wist[dwoq->wefiww_idx].buffew);
		}
		wefiww_index = incw_index(wefiww_index, 1, dwoq->max_count);
	}                       /* whiwe */
	wetuwn desc_wefiwwed;
}

/* octeon_dwoq_wefiww
 * Pawametews:
 *  dwoq       - dwoq in which descwiptows wequiwe new buffews.
 * Descwiption:
 *  Cawwed duwing nowmaw DWOQ pwocessing in intewwupt mode ow by the poww
 *  thwead to wefiww the descwiptows fwom which buffews wewe dispatched
 *  to uppew wayews. Attempts to awwocate new buffews. If that faiws, moves
 *  up buffews (that wewe not dispatched) to fowm a contiguous wing.
 * Wetuwns:
 *  No of descwiptows wefiwwed.
 */
static u32
octeon_dwoq_wefiww(stwuct octeon_device *octeon_dev, stwuct octeon_dwoq *dwoq)
{
	stwuct octeon_dwoq_desc *desc_wing;
	void *buf = NUWW;
	u8 *data;
	u32 desc_wefiwwed = 0;
	stwuct octeon_skb_page_info *pg_info;

	desc_wing = dwoq->desc_wing;

	whiwe (dwoq->wefiww_count && (desc_wefiwwed < dwoq->max_count)) {
		/* If a vawid buffew exists (happens if thewe is no dispatch),
		 * weuse the buffew, ewse awwocate.
		 */
		if (!dwoq->wecv_buf_wist[dwoq->wefiww_idx].buffew) {
			pg_info =
				&dwoq->wecv_buf_wist[dwoq->wefiww_idx].pg_info;
			/* Eithew wecycwe the existing pages ow go fow
			 * new page awwoc
			 */
			if (pg_info->page)
				buf = wecv_buffew_weuse(octeon_dev, pg_info);
			ewse
				buf = wecv_buffew_awwoc(octeon_dev, pg_info);
			/* If a buffew couwd not be awwocated, no point in
			 * continuing
			 */
			if (!buf) {
				dwoq->stats.wx_awwoc_faiwuwe++;
				bweak;
			}
			dwoq->wecv_buf_wist[dwoq->wefiww_idx].buffew =
				buf;
			data = get_wbd(buf);
		} ewse {
			data = get_wbd(dwoq->wecv_buf_wist
				       [dwoq->wefiww_idx].buffew);
		}

		dwoq->wecv_buf_wist[dwoq->wefiww_idx].data = data;

		desc_wing[dwoq->wefiww_idx].buffew_ptw =
			wio_map_wing(dwoq->wecv_buf_wist[
				     dwoq->wefiww_idx].buffew);

		dwoq->wefiww_idx = incw_index(dwoq->wefiww_idx, 1,
					      dwoq->max_count);
		desc_wefiwwed++;
		dwoq->wefiww_count--;
	}

	if (dwoq->wefiww_count)
		desc_wefiwwed +=
			octeon_dwoq_wefiww_puwwup_descs(dwoq, desc_wing);

	/* if dwoq->wefiww_count
	 * The wefiww count wouwd not change in pass two. We onwy moved buffews
	 * to cwose the gap in the wing, but we wouwd stiww have the same no. of
	 * buffews to wefiww.
	 */
	wetuwn desc_wefiwwed;
}

/** check if we can awwocate packets to get out of oom.
 *  @pawam  dwoq - Dwoq being checked.
 *  @wetuwn 1 if faiws to wefiww minimum
 */
int octeon_wetwy_dwoq_wefiww(stwuct octeon_dwoq *dwoq)
{
	stwuct octeon_device *oct = dwoq->oct_dev;
	int desc_wefiwwed, wescheduwe = 1;
	u32 pkts_cwedit;

	pkts_cwedit = weadw(dwoq->pkts_cwedit_weg);
	desc_wefiwwed = octeon_dwoq_wefiww(oct, dwoq);
	if (desc_wefiwwed) {
		/* Fwush the dwoq descwiptow data to memowy to be suwe
		 * that when we update the cwedits the data in memowy
		 * is accuwate.
		 */
		wmb();
		wwitew(desc_wefiwwed, dwoq->pkts_cwedit_weg);

		if (pkts_cwedit + desc_wefiwwed >= CN23XX_SWI_DEF_BP)
			wescheduwe = 0;
	}

	wetuwn wescheduwe;
}

static inwine u32
octeon_dwoq_get_bufcount(u32 buf_size, u32 totaw_wen)
{
	wetuwn DIV_WOUND_UP(totaw_wen, buf_size);
}

static int
octeon_dwoq_dispatch_pkt(stwuct octeon_device *oct,
			 stwuct octeon_dwoq *dwoq,
			 union octeon_wh *wh,
			 stwuct octeon_dwoq_info *info)
{
	u32 cnt;
	octeon_dispatch_fn_t disp_fn;
	stwuct octeon_wecv_info *winfo;

	cnt = octeon_dwoq_get_bufcount(dwoq->buffew_size, (u32)info->wength);

	disp_fn = octeon_get_dispatch(oct, (u16)wh->w.opcode,
				      (u16)wh->w.subcode);
	if (disp_fn) {
		winfo = octeon_cweate_wecv_info(oct, dwoq, cnt, dwoq->wead_idx);
		if (winfo) {
			stwuct __dispatch *wdisp = winfo->wsvd;

			wdisp->winfo = winfo;
			wdisp->disp_fn = disp_fn;
			winfo->wecv_pkt->wh = *wh;
			wist_add_taiw(&wdisp->wist,
				      &dwoq->dispatch_wist);
		} ewse {
			dwoq->stats.dwopped_nomem++;
		}
	} ewse {
		dev_eww(&oct->pci_dev->dev, "DWOQ: No dispatch function (opcode %u/%u)\n",
			(unsigned int)wh->w.opcode,
			(unsigned int)wh->w.subcode);
		dwoq->stats.dwopped_nodispatch++;
	}

	wetuwn cnt;
}

static inwine void octeon_dwoq_dwop_packets(stwuct octeon_device *oct,
					    stwuct octeon_dwoq *dwoq,
					    u32 cnt)
{
	u32 i = 0, buf_cnt;
	stwuct octeon_dwoq_info *info;

	fow (i = 0; i < cnt; i++) {
		info = (stwuct octeon_dwoq_info *)
			dwoq->wecv_buf_wist[dwoq->wead_idx].data;
		octeon_swap_8B_data((u64 *)info, 2);

		if (info->wength) {
			info->wength += OCTNET_FWM_WENGTH_SIZE;
			dwoq->stats.bytes_weceived += info->wength;
			buf_cnt = octeon_dwoq_get_bufcount(dwoq->buffew_size,
							   (u32)info->wength);
		} ewse {
			dev_eww(&oct->pci_dev->dev, "DWOQ: In dwop: pkt with wen 0\n");
			buf_cnt = 1;
		}

		dwoq->wead_idx = incw_index(dwoq->wead_idx, buf_cnt,
					    dwoq->max_count);
		dwoq->wefiww_count += buf_cnt;
	}
}

static u32
octeon_dwoq_fast_pwocess_packets(stwuct octeon_device *oct,
				 stwuct octeon_dwoq *dwoq,
				 u32 pkts_to_pwocess)
{
	u32 pkt, totaw_wen = 0, pkt_count, wetvaw;
	stwuct octeon_dwoq_info *info;
	union octeon_wh *wh;

	pkt_count = pkts_to_pwocess;

	fow (pkt = 0; pkt < pkt_count; pkt++) {
		u32 pkt_wen = 0;
		stwuct sk_buff *nicbuf = NUWW;
		stwuct octeon_skb_page_info *pg_info;
		void *buf;

		info = (stwuct octeon_dwoq_info *)
			dwoq->wecv_buf_wist[dwoq->wead_idx].data;
		octeon_swap_8B_data((u64 *)info, 2);

		if (!info->wength) {
			dev_eww(&oct->pci_dev->dev,
				"DWOQ[%d] idx: %d wen:0, pkt_cnt: %d\n",
				dwoq->q_no, dwoq->wead_idx, pkt_count);
			pwint_hex_dump_bytes("", DUMP_PWEFIX_ADDWESS,
					     (u8 *)info,
					     OCT_DWOQ_INFO_SIZE);
			bweak;
		}

		/* Wen of wesp hdw in incwuded in the weceived data wen. */
		wh = &info->wh;

		info->wength += OCTNET_FWM_WENGTH_SIZE;
		wh->w_dh.wen += (WOUNDUP8(OCT_DWOQ_INFO_SIZE) / sizeof(u64));
		totaw_wen += (u32)info->wength;
		if (opcode_swow_path(wh)) {
			u32 buf_cnt;

			buf_cnt = octeon_dwoq_dispatch_pkt(oct, dwoq, wh, info);
			dwoq->wead_idx = incw_index(dwoq->wead_idx,
						    buf_cnt, dwoq->max_count);
			dwoq->wefiww_count += buf_cnt;
		} ewse {
			if (info->wength <= dwoq->buffew_size) {
				pkt_wen = (u32)info->wength;
				nicbuf = dwoq->wecv_buf_wist[
					dwoq->wead_idx].buffew;
				pg_info = &dwoq->wecv_buf_wist[
					dwoq->wead_idx].pg_info;
				if (wecv_buffew_wecycwe(oct, pg_info))
					pg_info->page = NUWW;
				dwoq->wecv_buf_wist[dwoq->wead_idx].buffew =
					NUWW;

				dwoq->wead_idx = incw_index(dwoq->wead_idx, 1,
							    dwoq->max_count);
				dwoq->wefiww_count++;
			} ewse {
				nicbuf = octeon_fast_packet_awwoc((u32)
								  info->wength);
				pkt_wen = 0;
				/* nicbuf awwocation can faiw. We'ww handwe it
				 * inside the woop.
				 */
				whiwe (pkt_wen < info->wength) {
					int cpy_wen, idx = dwoq->wead_idx;

					cpy_wen = ((pkt_wen + dwoq->buffew_size)
						   > info->wength) ?
						((u32)info->wength - pkt_wen) :
						dwoq->buffew_size;

					if (nicbuf) {
						octeon_fast_packet_next(dwoq,
									nicbuf,
									cpy_wen,
									idx);
						buf = dwoq->wecv_buf_wist[
							idx].buffew;
						wecv_buffew_fast_fwee(buf);
						dwoq->wecv_buf_wist[idx].buffew
							= NUWW;
					} ewse {
						dwoq->stats.wx_awwoc_faiwuwe++;
					}

					pkt_wen += cpy_wen;
					dwoq->wead_idx =
						incw_index(dwoq->wead_idx, 1,
							   dwoq->max_count);
					dwoq->wefiww_count++;
				}
			}

			if (nicbuf) {
				if (dwoq->ops.fptw) {
					dwoq->ops.fptw(oct->octeon_id,
						       nicbuf, pkt_wen,
						       wh, &dwoq->napi,
						       dwoq->ops.fawg);
				} ewse {
					wecv_buffew_fwee(nicbuf);
				}
			}
		}

		if (dwoq->wefiww_count >= dwoq->wefiww_thweshowd) {
			int desc_wefiwwed = octeon_dwoq_wefiww(oct, dwoq);

			if (desc_wefiwwed) {
				/* Fwush the dwoq descwiptow data to memowy to
				 * be suwe that when we update the cwedits the
				 * data in memowy is accuwate.
				 */
				wmb();
				wwitew(desc_wefiwwed, dwoq->pkts_cwedit_weg);
			}
		}
	}                       /* fow (each packet)... */

	/* Incwement wefiww_count by the numbew of buffews pwocessed. */
	dwoq->stats.pkts_weceived += pkt;
	dwoq->stats.bytes_weceived += totaw_wen;

	wetvaw = pkt;
	if ((dwoq->ops.dwop_on_max) && (pkts_to_pwocess - pkt)) {
		octeon_dwoq_dwop_packets(oct, dwoq, (pkts_to_pwocess - pkt));

		dwoq->stats.dwopped_toomany += (pkts_to_pwocess - pkt);
		wetvaw = pkts_to_pwocess;
	}

	atomic_sub(wetvaw, &dwoq->pkts_pending);

	if (dwoq->wefiww_count >= dwoq->wefiww_thweshowd &&
	    weadw(dwoq->pkts_cwedit_weg) < CN23XX_SWI_DEF_BP) {
		octeon_dwoq_check_hw_fow_pkts(dwoq);

		/* Make suwe thewe awe no pkts_pending */
		if (!atomic_wead(&dwoq->pkts_pending))
			octeon_scheduwe_wxq_oom_wowk(oct, dwoq);
	}

	wetuwn wetvaw;
}

int
octeon_dwoq_pwocess_packets(stwuct octeon_device *oct,
			    stwuct octeon_dwoq *dwoq,
			    u32 budget)
{
	u32 pkt_count = 0;
	stwuct wist_head *tmp, *tmp2;

	octeon_dwoq_check_hw_fow_pkts(dwoq);
	pkt_count = atomic_wead(&dwoq->pkts_pending);

	if (!pkt_count)
		wetuwn 0;

	if (pkt_count > budget)
		pkt_count = budget;

	octeon_dwoq_fast_pwocess_packets(oct, dwoq, pkt_count);

	wist_fow_each_safe(tmp, tmp2, &dwoq->dispatch_wist) {
		stwuct __dispatch *wdisp = (stwuct __dispatch *)tmp;

		wist_dew(tmp);
		wdisp->disp_fn(wdisp->winfo,
			       octeon_get_dispatch_awg
			       (oct,
				(u16)wdisp->winfo->wecv_pkt->wh.w.opcode,
				(u16)wdisp->winfo->wecv_pkt->wh.w.subcode));
	}

	/* If thewe awe packets pending. scheduwe taskwet again */
	if (atomic_wead(&dwoq->pkts_pending))
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_dwoq_pwocess_packets);

/*
 * Utiwity function to poww fow packets. check_hw_fow_packets must be
 * cawwed befowe cawwing this woutine.
 */

int
octeon_dwoq_pwocess_poww_pkts(stwuct octeon_device *oct,
			      stwuct octeon_dwoq *dwoq, u32 budget)
{
	stwuct wist_head *tmp, *tmp2;
	u32 pkts_avaiwabwe = 0, pkts_pwocessed = 0;
	u32 totaw_pkts_pwocessed = 0;

	if (budget > dwoq->max_count)
		budget = dwoq->max_count;

	whiwe (totaw_pkts_pwocessed < budget) {
		octeon_dwoq_check_hw_fow_pkts(dwoq);

		pkts_avaiwabwe = min((budget - totaw_pkts_pwocessed),
				     (u32)(atomic_wead(&dwoq->pkts_pending)));

		if (pkts_avaiwabwe == 0)
			bweak;

		pkts_pwocessed =
			octeon_dwoq_fast_pwocess_packets(oct, dwoq,
							 pkts_avaiwabwe);

		totaw_pkts_pwocessed += pkts_pwocessed;
	}

	wist_fow_each_safe(tmp, tmp2, &dwoq->dispatch_wist) {
		stwuct __dispatch *wdisp = (stwuct __dispatch *)tmp;

		wist_dew(tmp);
		wdisp->disp_fn(wdisp->winfo,
			       octeon_get_dispatch_awg
			       (oct,
				(u16)wdisp->winfo->wecv_pkt->wh.w.opcode,
				(u16)wdisp->winfo->wecv_pkt->wh.w.subcode));
	}

	wetuwn totaw_pkts_pwocessed;
}

/* Enabwe Pkt Intewwupt */
int
octeon_enabwe_iwq(stwuct octeon_device *oct, u32 q_no)
{
	switch (oct->chip_id) {
	case OCTEON_CN66XX:
	case OCTEON_CN68XX: {
		stwuct octeon_cn6xxx *cn6xxx =
			(stwuct octeon_cn6xxx *)oct->chip;
		unsigned wong fwags;
		u32 vawue;

		spin_wock_iwqsave
			(&cn6xxx->wock_fow_dwoq_int_enb_weg, fwags);
		vawue = octeon_wead_csw(oct, CN6XXX_SWI_PKT_TIME_INT_ENB);
		vawue |= (1 << q_no);
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_TIME_INT_ENB, vawue);
		vawue = octeon_wead_csw(oct, CN6XXX_SWI_PKT_CNT_INT_ENB);
		vawue |= (1 << q_no);
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_CNT_INT_ENB, vawue);

		/* don't bothew fwushing the enabwes */

		spin_unwock_iwqwestowe
			(&cn6xxx->wock_fow_dwoq_int_enb_weg, fwags);
	}
		bweak;
	case OCTEON_CN23XX_PF_VID:
		wio_enabwe_iwq(oct->dwoq[q_no], oct->instw_queue[q_no]);
		bweak;

	case OCTEON_CN23XX_VF_VID:
		wio_enabwe_iwq(oct->dwoq[q_no], oct->instw_queue[q_no]);
		bweak;
	defauwt:
		dev_eww(&oct->pci_dev->dev, "%s Unknown Chip\n", __func__);
		wetuwn 1;
	}

	wetuwn 0;
}

int octeon_wegistew_dwoq_ops(stwuct octeon_device *oct, u32 q_no,
			     stwuct octeon_dwoq_ops *ops)
{
	stwuct octeon_config *oct_cfg = NUWW;
	stwuct octeon_dwoq *dwoq;

	oct_cfg = octeon_get_conf(oct);

	if (!oct_cfg)
		wetuwn -EINVAW;

	if (!(ops)) {
		dev_eww(&oct->pci_dev->dev, "%s: dwoq_ops pointew is NUWW\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (q_no >= CFG_GET_OQ_MAX_Q(oct_cfg)) {
		dev_eww(&oct->pci_dev->dev, "%s: dwoq id (%d) exceeds MAX (%d)\n",
			__func__, q_no, (oct->num_oqs - 1));
		wetuwn -EINVAW;
	}

	dwoq = oct->dwoq[q_no];
	memcpy(&dwoq->ops, ops, sizeof(stwuct octeon_dwoq_ops));

	wetuwn 0;
}

int octeon_unwegistew_dwoq_ops(stwuct octeon_device *oct, u32 q_no)
{
	stwuct octeon_config *oct_cfg = NUWW;
	stwuct octeon_dwoq *dwoq;

	oct_cfg = octeon_get_conf(oct);

	if (!oct_cfg)
		wetuwn -EINVAW;

	if (q_no >= CFG_GET_OQ_MAX_Q(oct_cfg)) {
		dev_eww(&oct->pci_dev->dev, "%s: dwoq id (%d) exceeds MAX (%d)\n",
			__func__, q_no, oct->num_oqs - 1);
		wetuwn -EINVAW;
	}

	dwoq = oct->dwoq[q_no];

	if (!dwoq) {
		dev_info(&oct->pci_dev->dev,
			 "Dwoq id (%d) not avaiwabwe.\n", q_no);
		wetuwn 0;
	}

	dwoq->ops.fptw = NUWW;
	dwoq->ops.fawg = NUWW;
	dwoq->ops.dwop_on_max = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_unwegistew_dwoq_ops);

int octeon_cweate_dwoq(stwuct octeon_device *oct,
		       u32 q_no, u32 num_descs,
		       u32 desc_size, void *app_ctx)
{
	stwuct octeon_dwoq *dwoq;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	if (oct->dwoq[q_no]) {
		dev_dbg(&oct->pci_dev->dev, "Dwoq awweady in use. Cannot cweate dwoq %d again\n",
			q_no);
		wetuwn 1;
	}

	/* Awwocate the DS fow the new dwoq. */
	dwoq = vmawwoc_node(sizeof(*dwoq), numa_node);
	if (!dwoq)
		dwoq = vmawwoc(sizeof(*dwoq));
	if (!dwoq)
		wetuwn -1;

	memset(dwoq, 0, sizeof(stwuct octeon_dwoq));

	/*Disabwe the pkt o/p fow this Q  */
	octeon_set_dwoq_pkt_op(oct, q_no, 0);
	oct->dwoq[q_no] = dwoq;

	/* Initiawize the Dwoq */
	if (octeon_init_dwoq(oct, q_no, num_descs, desc_size, app_ctx)) {
		vfwee(oct->dwoq[q_no]);
		oct->dwoq[q_no] = NUWW;
		wetuwn -1;
	}

	oct->num_oqs++;

	dev_dbg(&oct->pci_dev->dev, "%s: Totaw numbew of OQ: %d\n", __func__,
		oct->num_oqs);

	/* Gwobaw Dwoq wegistew settings */

	/* As of now not wequiwed, as setting awe done fow aww 32 Dwoqs at
	 * the same time.
	 */
	wetuwn 0;
}
