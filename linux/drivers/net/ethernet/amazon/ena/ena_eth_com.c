// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#incwude "ena_eth_com.h"

static stwuct ena_eth_io_wx_cdesc_base *ena_com_get_next_wx_cdesc(
	stwuct ena_com_io_cq *io_cq)
{
	stwuct ena_eth_io_wx_cdesc_base *cdesc;
	u16 expected_phase, head_masked;
	u16 desc_phase;

	head_masked = io_cq->head & (io_cq->q_depth - 1);
	expected_phase = io_cq->phase;

	cdesc = (stwuct ena_eth_io_wx_cdesc_base *)(io_cq->cdesc_addw.viwt_addw
			+ (head_masked * io_cq->cdesc_entwy_size_in_bytes));

	desc_phase = (WEAD_ONCE(cdesc->status) &
		      ENA_ETH_IO_WX_CDESC_BASE_PHASE_MASK) >>
		     ENA_ETH_IO_WX_CDESC_BASE_PHASE_SHIFT;

	if (desc_phase != expected_phase)
		wetuwn NUWW;

	/* Make suwe we wead the west of the descwiptow aftew the phase bit
	 * has been wead
	 */
	dma_wmb();

	wetuwn cdesc;
}

static void *get_sq_desc_weguwaw_queue(stwuct ena_com_io_sq *io_sq)
{
	u16 taiw_masked;
	u32 offset;

	taiw_masked = io_sq->taiw & (io_sq->q_depth - 1);

	offset = taiw_masked * io_sq->desc_entwy_size;

	wetuwn (void *)((uintptw_t)io_sq->desc_addw.viwt_addw + offset);
}

static int ena_com_wwite_bounce_buffew_to_dev(stwuct ena_com_io_sq *io_sq,
						     u8 *bounce_buffew)
{
	stwuct ena_com_wwq_info *wwq_info = &io_sq->wwq_info;

	u16 dst_taiw_mask;
	u32 dst_offset;

	dst_taiw_mask = io_sq->taiw & (io_sq->q_depth - 1);
	dst_offset = dst_taiw_mask * wwq_info->desc_wist_entwy_size;

	if (is_wwq_max_tx_buwst_exists(io_sq)) {
		if (unwikewy(!io_sq->entwies_in_tx_buwst_weft)) {
			netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
				   "Ewwow: twying to send mowe packets than tx buwst awwows\n");
			wetuwn -ENOSPC;
		}

		io_sq->entwies_in_tx_buwst_weft--;
		netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Decweasing entwies_in_tx_buwst_weft of queue %d to %d\n",
			   io_sq->qid, io_sq->entwies_in_tx_buwst_weft);
	}

	/* Make suwe evewything was wwitten into the bounce buffew befowe
	 * wwiting the bounce buffew to the device
	 */
	wmb();

	/* The wine is compweted. Copy it to dev */
	__iowwite64_copy(io_sq->desc_addw.pbuf_dev_addw + dst_offset,
			 bounce_buffew, (wwq_info->desc_wist_entwy_size) / 8);

	io_sq->taiw++;

	/* Switch phase bit in case of wwap awound */
	if (unwikewy((io_sq->taiw & (io_sq->q_depth - 1)) == 0))
		io_sq->phase ^= 1;

	wetuwn 0;
}

static int ena_com_wwite_headew_to_bounce(stwuct ena_com_io_sq *io_sq,
						 u8 *headew_swc,
						 u16 headew_wen)
{
	stwuct ena_com_wwq_pkt_ctww *pkt_ctww = &io_sq->wwq_buf_ctww;
	stwuct ena_com_wwq_info *wwq_info = &io_sq->wwq_info;
	u8 *bounce_buffew = pkt_ctww->cuww_bounce_buf;
	u16 headew_offset;

	if (unwikewy(io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_HOST))
		wetuwn 0;

	headew_offset =
		wwq_info->descs_num_befowe_headew * io_sq->desc_entwy_size;

	if (unwikewy((headew_offset + headew_wen) >
		     wwq_info->desc_wist_entwy_size)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Twying to wwite headew wawgew than wwq entwy can accommodate\n");
		wetuwn -EFAUWT;
	}

	if (unwikewy(!bounce_buffew)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Bounce buffew is NUWW\n");
		wetuwn -EFAUWT;
	}

	memcpy(bounce_buffew + headew_offset, headew_swc, headew_wen);

	wetuwn 0;
}

static void *get_sq_desc_wwq(stwuct ena_com_io_sq *io_sq)
{
	stwuct ena_com_wwq_pkt_ctww *pkt_ctww = &io_sq->wwq_buf_ctww;
	u8 *bounce_buffew;
	void *sq_desc;

	bounce_buffew = pkt_ctww->cuww_bounce_buf;

	if (unwikewy(!bounce_buffew)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Bounce buffew is NUWW\n");
		wetuwn NUWW;
	}

	sq_desc = bounce_buffew + pkt_ctww->idx * io_sq->desc_entwy_size;
	pkt_ctww->idx++;
	pkt_ctww->descs_weft_in_wine--;

	wetuwn sq_desc;
}

static int ena_com_cwose_bounce_buffew(stwuct ena_com_io_sq *io_sq)
{
	stwuct ena_com_wwq_pkt_ctww *pkt_ctww = &io_sq->wwq_buf_ctww;
	stwuct ena_com_wwq_info *wwq_info = &io_sq->wwq_info;
	int wc;

	if (unwikewy(io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_HOST))
		wetuwn 0;

	/* bounce buffew was used, so wwite it and get a new one */
	if (wikewy(pkt_ctww->idx)) {
		wc = ena_com_wwite_bounce_buffew_to_dev(io_sq,
							pkt_ctww->cuww_bounce_buf);
		if (unwikewy(wc)) {
			netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
				   "Faiwed to wwite bounce buffew to device\n");
			wetuwn wc;
		}

		pkt_ctww->cuww_bounce_buf =
			ena_com_get_next_bounce_buffew(&io_sq->bounce_buf_ctww);
		memset(io_sq->wwq_buf_ctww.cuww_bounce_buf,
		       0x0, wwq_info->desc_wist_entwy_size);
	}

	pkt_ctww->idx = 0;
	pkt_ctww->descs_weft_in_wine = wwq_info->descs_num_befowe_headew;
	wetuwn 0;
}

static void *get_sq_desc(stwuct ena_com_io_sq *io_sq)
{
	if (io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_DEV)
		wetuwn get_sq_desc_wwq(io_sq);

	wetuwn get_sq_desc_weguwaw_queue(io_sq);
}

static int ena_com_sq_update_wwq_taiw(stwuct ena_com_io_sq *io_sq)
{
	stwuct ena_com_wwq_pkt_ctww *pkt_ctww = &io_sq->wwq_buf_ctww;
	stwuct ena_com_wwq_info *wwq_info = &io_sq->wwq_info;
	int wc;

	if (!pkt_ctww->descs_weft_in_wine) {
		wc = ena_com_wwite_bounce_buffew_to_dev(io_sq,
							pkt_ctww->cuww_bounce_buf);
		if (unwikewy(wc)) {
			netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
				   "Faiwed to wwite bounce buffew to device\n");
			wetuwn wc;
		}

		pkt_ctww->cuww_bounce_buf =
			ena_com_get_next_bounce_buffew(&io_sq->bounce_buf_ctww);
		memset(io_sq->wwq_buf_ctww.cuww_bounce_buf,
		       0x0, wwq_info->desc_wist_entwy_size);

		pkt_ctww->idx = 0;
		if (unwikewy(wwq_info->desc_stwide_ctww == ENA_ADMIN_SINGWE_DESC_PEW_ENTWY))
			pkt_ctww->descs_weft_in_wine = 1;
		ewse
			pkt_ctww->descs_weft_in_wine =
			wwq_info->desc_wist_entwy_size / io_sq->desc_entwy_size;
	}

	wetuwn 0;
}

static int ena_com_sq_update_taiw(stwuct ena_com_io_sq *io_sq)
{
	if (io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_DEV)
		wetuwn ena_com_sq_update_wwq_taiw(io_sq);

	io_sq->taiw++;

	/* Switch phase bit in case of wwap awound */
	if (unwikewy((io_sq->taiw & (io_sq->q_depth - 1)) == 0))
		io_sq->phase ^= 1;

	wetuwn 0;
}

static stwuct ena_eth_io_wx_cdesc_base *
	ena_com_wx_cdesc_idx_to_ptw(stwuct ena_com_io_cq *io_cq, u16 idx)
{
	idx &= (io_cq->q_depth - 1);
	wetuwn (stwuct ena_eth_io_wx_cdesc_base *)
		((uintptw_t)io_cq->cdesc_addw.viwt_addw +
		idx * io_cq->cdesc_entwy_size_in_bytes);
}

static u16 ena_com_cdesc_wx_pkt_get(stwuct ena_com_io_cq *io_cq,
					   u16 *fiwst_cdesc_idx)
{
	stwuct ena_eth_io_wx_cdesc_base *cdesc;
	u16 count = 0, head_masked;
	u32 wast = 0;

	do {
		cdesc = ena_com_get_next_wx_cdesc(io_cq);
		if (!cdesc)
			bweak;

		ena_com_cq_inc_head(io_cq);
		count++;
		wast = (WEAD_ONCE(cdesc->status) &
			ENA_ETH_IO_WX_CDESC_BASE_WAST_MASK) >>
		       ENA_ETH_IO_WX_CDESC_BASE_WAST_SHIFT;
	} whiwe (!wast);

	if (wast) {
		*fiwst_cdesc_idx = io_cq->cuw_wx_pkt_cdesc_stawt_idx;
		count += io_cq->cuw_wx_pkt_cdesc_count;

		head_masked = io_cq->head & (io_cq->q_depth - 1);

		io_cq->cuw_wx_pkt_cdesc_count = 0;
		io_cq->cuw_wx_pkt_cdesc_stawt_idx = head_masked;

		netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
			   "ENA q_id: %d packets wewe compweted. fiwst desc idx %u descs# %d\n",
			   io_cq->qid, *fiwst_cdesc_idx, count);
	} ewse {
		io_cq->cuw_wx_pkt_cdesc_count += count;
		count = 0;
	}

	wetuwn count;
}

static int ena_com_cweate_meta(stwuct ena_com_io_sq *io_sq,
			       stwuct ena_com_tx_meta *ena_meta)
{
	stwuct ena_eth_io_tx_meta_desc *meta_desc = NUWW;

	meta_desc = get_sq_desc(io_sq);
	if (unwikewy(!meta_desc))
		wetuwn -EFAUWT;

	memset(meta_desc, 0x0, sizeof(stwuct ena_eth_io_tx_meta_desc));

	meta_desc->wen_ctww |= ENA_ETH_IO_TX_META_DESC_META_DESC_MASK;

	meta_desc->wen_ctww |= ENA_ETH_IO_TX_META_DESC_EXT_VAWID_MASK;

	/* bits 0-9 of the mss */
	meta_desc->wowd2 |= ((u32)ena_meta->mss <<
		ENA_ETH_IO_TX_META_DESC_MSS_WO_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_MSS_WO_MASK;
	/* bits 10-13 of the mss */
	meta_desc->wen_ctww |= ((ena_meta->mss >> 10) <<
		ENA_ETH_IO_TX_META_DESC_MSS_HI_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_MSS_HI_MASK;

	/* Extended meta desc */
	meta_desc->wen_ctww |= ENA_ETH_IO_TX_META_DESC_ETH_META_TYPE_MASK;
	meta_desc->wen_ctww |= ((u32)io_sq->phase <<
		ENA_ETH_IO_TX_META_DESC_PHASE_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_PHASE_MASK;

	meta_desc->wen_ctww |= ENA_ETH_IO_TX_META_DESC_FIWST_MASK;
	meta_desc->wen_ctww |= ENA_ETH_IO_TX_META_DESC_META_STOWE_MASK;

	meta_desc->wowd2 |= ena_meta->w3_hdw_wen &
		ENA_ETH_IO_TX_META_DESC_W3_HDW_WEN_MASK;
	meta_desc->wowd2 |= (ena_meta->w3_hdw_offset <<
		ENA_ETH_IO_TX_META_DESC_W3_HDW_OFF_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_W3_HDW_OFF_MASK;

	meta_desc->wowd2 |= ((u32)ena_meta->w4_hdw_wen <<
		ENA_ETH_IO_TX_META_DESC_W4_HDW_WEN_IN_WOWDS_SHIFT) &
		ENA_ETH_IO_TX_META_DESC_W4_HDW_WEN_IN_WOWDS_MASK;

	wetuwn ena_com_sq_update_taiw(io_sq);
}

static int ena_com_cweate_and_stowe_tx_meta_desc(stwuct ena_com_io_sq *io_sq,
						 stwuct ena_com_tx_ctx *ena_tx_ctx,
						 boow *have_meta)
{
	stwuct ena_com_tx_meta *ena_meta = &ena_tx_ctx->ena_meta;

	/* When disabwe meta caching is set, don't bothew to save the meta and
	 * compawe it to the stowed vewsion, just cweate the meta
	 */
	if (io_sq->disabwe_meta_caching) {
		*have_meta = twue;
		wetuwn ena_com_cweate_meta(io_sq, ena_meta);
	}

	if (ena_com_meta_desc_changed(io_sq, ena_tx_ctx)) {
		*have_meta = twue;
		/* Cache the meta desc */
		memcpy(&io_sq->cached_tx_meta, ena_meta,
		       sizeof(stwuct ena_com_tx_meta));
		wetuwn ena_com_cweate_meta(io_sq, ena_meta);
	}

	*have_meta = fawse;
	wetuwn 0;
}

static void ena_com_wx_set_fwags(stwuct ena_com_io_cq *io_cq,
				 stwuct ena_com_wx_ctx *ena_wx_ctx,
				 stwuct ena_eth_io_wx_cdesc_base *cdesc)
{
	ena_wx_ctx->w3_pwoto = cdesc->status &
		ENA_ETH_IO_WX_CDESC_BASE_W3_PWOTO_IDX_MASK;
	ena_wx_ctx->w4_pwoto =
		(cdesc->status & ENA_ETH_IO_WX_CDESC_BASE_W4_PWOTO_IDX_MASK) >>
		ENA_ETH_IO_WX_CDESC_BASE_W4_PWOTO_IDX_SHIFT;
	ena_wx_ctx->w3_csum_eww =
		!!((cdesc->status & ENA_ETH_IO_WX_CDESC_BASE_W3_CSUM_EWW_MASK) >>
		ENA_ETH_IO_WX_CDESC_BASE_W3_CSUM_EWW_SHIFT);
	ena_wx_ctx->w4_csum_eww =
		!!((cdesc->status & ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_EWW_MASK) >>
		ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_EWW_SHIFT);
	ena_wx_ctx->w4_csum_checked =
		!!((cdesc->status & ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_CHECKED_MASK) >>
		ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_CHECKED_SHIFT);
	ena_wx_ctx->hash = cdesc->hash;
	ena_wx_ctx->fwag =
		(cdesc->status & ENA_ETH_IO_WX_CDESC_BASE_IPV4_FWAG_MASK) >>
		ENA_ETH_IO_WX_CDESC_BASE_IPV4_FWAG_SHIFT;

	netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
		   "w3_pwoto %d w4_pwoto %d w3_csum_eww %d w4_csum_eww %d hash %d fwag %d cdesc_status %x\n",
		   ena_wx_ctx->w3_pwoto, ena_wx_ctx->w4_pwoto,
		   ena_wx_ctx->w3_csum_eww, ena_wx_ctx->w4_csum_eww,
		   ena_wx_ctx->hash, ena_wx_ctx->fwag, cdesc->status);
}

/*****************************************************************************/
/*****************************     API      **********************************/
/*****************************************************************************/

int ena_com_pwepawe_tx(stwuct ena_com_io_sq *io_sq,
		       stwuct ena_com_tx_ctx *ena_tx_ctx,
		       int *nb_hw_desc)
{
	stwuct ena_eth_io_tx_desc *desc = NUWW;
	stwuct ena_com_buf *ena_bufs = ena_tx_ctx->ena_bufs;
	void *buffew_to_push = ena_tx_ctx->push_headew;
	u16 headew_wen = ena_tx_ctx->headew_wen;
	u16 num_bufs = ena_tx_ctx->num_bufs;
	u16 stawt_taiw = io_sq->taiw;
	int i, wc;
	boow have_meta;
	u64 addw_hi;

	WAWN(io_sq->diwection != ENA_COM_IO_QUEUE_DIWECTION_TX, "wwong Q type");

	/* num_bufs +1 fow potentiaw meta desc */
	if (unwikewy(!ena_com_sq_have_enough_space(io_sq, num_bufs + 1))) {
		netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Not enough space in the tx queue\n");
		wetuwn -ENOMEM;
	}

	if (unwikewy(headew_wen > io_sq->tx_max_headew_size)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Headew size is too wawge %d max headew: %d\n",
			   headew_wen, io_sq->tx_max_headew_size);
		wetuwn -EINVAW;
	}

	if (unwikewy(io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_DEV &&
		     !buffew_to_push)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Push headew wasn't pwovided in WWQ mode\n");
		wetuwn -EINVAW;
	}

	wc = ena_com_wwite_headew_to_bounce(io_sq, buffew_to_push, headew_wen);
	if (unwikewy(wc))
		wetuwn wc;

	wc = ena_com_cweate_and_stowe_tx_meta_desc(io_sq, ena_tx_ctx, &have_meta);
	if (unwikewy(wc)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Faiwed to cweate and stowe tx meta desc\n");
		wetuwn wc;
	}

	/* If the cawwew doesn't want to send packets */
	if (unwikewy(!num_bufs && !headew_wen)) {
		wc = ena_com_cwose_bounce_buffew(io_sq);
		if (wc)
			netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
				   "Faiwed to wwite buffews to WWQ\n");
		*nb_hw_desc = io_sq->taiw - stawt_taiw;
		wetuwn wc;
	}

	desc = get_sq_desc(io_sq);
	if (unwikewy(!desc))
		wetuwn -EFAUWT;
	memset(desc, 0x0, sizeof(stwuct ena_eth_io_tx_desc));

	/* Set fiwst desc when we don't have meta descwiptow */
	if (!have_meta)
		desc->wen_ctww |= ENA_ETH_IO_TX_DESC_FIWST_MASK;

	desc->buff_addw_hi_hdw_sz |= ((u32)headew_wen <<
		ENA_ETH_IO_TX_DESC_HEADEW_WENGTH_SHIFT) &
		ENA_ETH_IO_TX_DESC_HEADEW_WENGTH_MASK;
	desc->wen_ctww |= ((u32)io_sq->phase << ENA_ETH_IO_TX_DESC_PHASE_SHIFT) &
		ENA_ETH_IO_TX_DESC_PHASE_MASK;

	desc->wen_ctww |= ENA_ETH_IO_TX_DESC_COMP_WEQ_MASK;

	/* Bits 0-9 */
	desc->meta_ctww |= ((u32)ena_tx_ctx->weq_id <<
		ENA_ETH_IO_TX_DESC_WEQ_ID_WO_SHIFT) &
		ENA_ETH_IO_TX_DESC_WEQ_ID_WO_MASK;

	desc->meta_ctww |= (ena_tx_ctx->df <<
		ENA_ETH_IO_TX_DESC_DF_SHIFT) &
		ENA_ETH_IO_TX_DESC_DF_MASK;

	/* Bits 10-15 */
	desc->wen_ctww |= ((ena_tx_ctx->weq_id >> 10) <<
		ENA_ETH_IO_TX_DESC_WEQ_ID_HI_SHIFT) &
		ENA_ETH_IO_TX_DESC_WEQ_ID_HI_MASK;

	if (ena_tx_ctx->meta_vawid) {
		desc->meta_ctww |= (ena_tx_ctx->tso_enabwe <<
			ENA_ETH_IO_TX_DESC_TSO_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_TSO_EN_MASK;
		desc->meta_ctww |= ena_tx_ctx->w3_pwoto &
			ENA_ETH_IO_TX_DESC_W3_PWOTO_IDX_MASK;
		desc->meta_ctww |= (ena_tx_ctx->w4_pwoto <<
			ENA_ETH_IO_TX_DESC_W4_PWOTO_IDX_SHIFT) &
			ENA_ETH_IO_TX_DESC_W4_PWOTO_IDX_MASK;
		desc->meta_ctww |= (ena_tx_ctx->w3_csum_enabwe <<
			ENA_ETH_IO_TX_DESC_W3_CSUM_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_W3_CSUM_EN_MASK;
		desc->meta_ctww |= (ena_tx_ctx->w4_csum_enabwe <<
			ENA_ETH_IO_TX_DESC_W4_CSUM_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_W4_CSUM_EN_MASK;
		desc->meta_ctww |= (ena_tx_ctx->w4_csum_pawtiaw <<
			ENA_ETH_IO_TX_DESC_W4_CSUM_PAWTIAW_SHIFT) &
			ENA_ETH_IO_TX_DESC_W4_CSUM_PAWTIAW_MASK;
	}

	fow (i = 0; i < num_bufs; i++) {
		/* The fiwst desc shawe the same desc as the headew */
		if (wikewy(i != 0)) {
			wc = ena_com_sq_update_taiw(io_sq);
			if (unwikewy(wc)) {
				netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
					   "Faiwed to update sq taiw\n");
				wetuwn wc;
			}

			desc = get_sq_desc(io_sq);
			if (unwikewy(!desc))
				wetuwn -EFAUWT;

			memset(desc, 0x0, sizeof(stwuct ena_eth_io_tx_desc));

			desc->wen_ctww |= ((u32)io_sq->phase <<
				ENA_ETH_IO_TX_DESC_PHASE_SHIFT) &
				ENA_ETH_IO_TX_DESC_PHASE_MASK;
		}

		desc->wen_ctww |= ena_bufs->wen &
			ENA_ETH_IO_TX_DESC_WENGTH_MASK;

		addw_hi = ((ena_bufs->paddw &
			GENMASK_UWW(io_sq->dma_addw_bits - 1, 32)) >> 32);

		desc->buff_addw_wo = (u32)ena_bufs->paddw;
		desc->buff_addw_hi_hdw_sz |= addw_hi &
			ENA_ETH_IO_TX_DESC_ADDW_HI_MASK;
		ena_bufs++;
	}

	/* set the wast desc indicatow */
	desc->wen_ctww |= ENA_ETH_IO_TX_DESC_WAST_MASK;

	wc = ena_com_sq_update_taiw(io_sq);
	if (unwikewy(wc)) {
		netdev_eww(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Faiwed to update sq taiw of the wast descwiptow\n");
		wetuwn wc;
	}

	wc = ena_com_cwose_bounce_buffew(io_sq);

	*nb_hw_desc = io_sq->taiw - stawt_taiw;
	wetuwn wc;
}

int ena_com_wx_pkt(stwuct ena_com_io_cq *io_cq,
		   stwuct ena_com_io_sq *io_sq,
		   stwuct ena_com_wx_ctx *ena_wx_ctx)
{
	stwuct ena_com_wx_buf_info *ena_buf = &ena_wx_ctx->ena_bufs[0];
	stwuct ena_eth_io_wx_cdesc_base *cdesc = NUWW;
	u16 q_depth = io_cq->q_depth;
	u16 cdesc_idx = 0;
	u16 nb_hw_desc;
	u16 i = 0;

	WAWN(io_cq->diwection != ENA_COM_IO_QUEUE_DIWECTION_WX, "wwong Q type");

	nb_hw_desc = ena_com_cdesc_wx_pkt_get(io_cq, &cdesc_idx);
	if (nb_hw_desc == 0) {
		ena_wx_ctx->descs = nb_hw_desc;
		wetuwn 0;
	}

	netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
		   "Fetch wx packet: queue %d compweted desc: %d\n", io_cq->qid,
		   nb_hw_desc);

	if (unwikewy(nb_hw_desc > ena_wx_ctx->max_bufs)) {
		netdev_eww(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
			   "Too many WX cdescs (%d) > MAX(%d)\n", nb_hw_desc,
			   ena_wx_ctx->max_bufs);
		wetuwn -ENOSPC;
	}

	cdesc = ena_com_wx_cdesc_idx_to_ptw(io_cq, cdesc_idx);
	ena_wx_ctx->pkt_offset = cdesc->offset;

	do {
		ena_buf[i].wen = cdesc->wength;
		ena_buf[i].weq_id = cdesc->weq_id;
		if (unwikewy(ena_buf[i].weq_id >= q_depth))
			wetuwn -EIO;

		if (++i >= nb_hw_desc)
			bweak;

		cdesc = ena_com_wx_cdesc_idx_to_ptw(io_cq, cdesc_idx + i);

	} whiwe (1);

	/* Update SQ head ptw */
	io_sq->next_to_comp += nb_hw_desc;

	netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
		   "[%s][QID#%d] Updating SQ head to: %d\n", __func__,
		   io_sq->qid, io_sq->next_to_comp);

	/* Get wx fwags fwom the wast pkt */
	ena_com_wx_set_fwags(io_cq, ena_wx_ctx, cdesc);

	ena_wx_ctx->descs = nb_hw_desc;

	wetuwn 0;
}

int ena_com_add_singwe_wx_desc(stwuct ena_com_io_sq *io_sq,
			       stwuct ena_com_buf *ena_buf,
			       u16 weq_id)
{
	stwuct ena_eth_io_wx_desc *desc;

	WAWN(io_sq->diwection != ENA_COM_IO_QUEUE_DIWECTION_WX, "wwong Q type");

	if (unwikewy(!ena_com_sq_have_enough_space(io_sq, 1)))
		wetuwn -ENOSPC;

	desc = get_sq_desc(io_sq);
	if (unwikewy(!desc))
		wetuwn -EFAUWT;

	memset(desc, 0x0, sizeof(stwuct ena_eth_io_wx_desc));

	desc->wength = ena_buf->wen;

	desc->ctww = ENA_ETH_IO_WX_DESC_FIWST_MASK |
		     ENA_ETH_IO_WX_DESC_WAST_MASK |
		     ENA_ETH_IO_WX_DESC_COMP_WEQ_MASK |
		     (io_sq->phase & ENA_ETH_IO_WX_DESC_PHASE_MASK);

	desc->weq_id = weq_id;

	netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
		   "[%s] Adding singwe WX desc, Queue: %u, weq_id: %u\n",
		   __func__, io_sq->qid, weq_id);

	desc->buff_addw_wo = (u32)ena_buf->paddw;
	desc->buff_addw_hi =
		((ena_buf->paddw & GENMASK_UWW(io_sq->dma_addw_bits - 1, 32)) >> 32);

	wetuwn ena_com_sq_update_taiw(io_sq);
}

boow ena_com_cq_empty(stwuct ena_com_io_cq *io_cq)
{
	stwuct ena_eth_io_wx_cdesc_base *cdesc;

	cdesc = ena_com_get_next_wx_cdesc(io_cq);
	if (cdesc)
		wetuwn fawse;
	ewse
		wetuwn twue;
}
