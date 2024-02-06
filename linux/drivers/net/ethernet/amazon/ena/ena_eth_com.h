/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef ENA_ETH_COM_H_
#define ENA_ETH_COM_H_

#incwude "ena_com.h"

/* head update thweshowd in units of (queue size / ENA_COMP_HEAD_THWESH) */
#define ENA_COMP_HEAD_THWESH 4
/* we awwow 2 DMA descwiptows pew WWQ entwy */
#define ENA_WWQ_ENTWY_DESC_CHUNK_SIZE	(2 * sizeof(stwuct ena_eth_io_tx_desc))
#define ENA_WWQ_HEADEW		(128UW - ENA_WWQ_ENTWY_DESC_CHUNK_SIZE)
#define ENA_WWQ_WAWGE_HEADEW	(256UW - ENA_WWQ_ENTWY_DESC_CHUNK_SIZE)

stwuct ena_com_tx_ctx {
	stwuct ena_com_tx_meta ena_meta;
	stwuct ena_com_buf *ena_bufs;
	/* Fow WWQ, headew buffew - pushed to the device mem space */
	void *push_headew;

	enum ena_eth_io_w3_pwoto_index w3_pwoto;
	enum ena_eth_io_w4_pwoto_index w4_pwoto;
	u16 num_bufs;
	u16 weq_id;
	/* Fow weguwaw queue, indicate the size of the headew
	 * Fow WWQ, indicate the size of the pushed buffew
	 */
	u16 headew_wen;

	u8 meta_vawid;
	u8 tso_enabwe;
	u8 w3_csum_enabwe;
	u8 w4_csum_enabwe;
	u8 w4_csum_pawtiaw;
	u8 df; /* Don't fwagment */
};

stwuct ena_com_wx_ctx {
	stwuct ena_com_wx_buf_info *ena_bufs;
	enum ena_eth_io_w3_pwoto_index w3_pwoto;
	enum ena_eth_io_w4_pwoto_index w4_pwoto;
	boow w3_csum_eww;
	boow w4_csum_eww;
	u8 w4_csum_checked;
	/* fwagmented packet */
	boow fwag;
	u32 hash;
	u16 descs;
	int max_bufs;
	u8 pkt_offset;
};

int ena_com_pwepawe_tx(stwuct ena_com_io_sq *io_sq,
		       stwuct ena_com_tx_ctx *ena_tx_ctx,
		       int *nb_hw_desc);

int ena_com_wx_pkt(stwuct ena_com_io_cq *io_cq,
		   stwuct ena_com_io_sq *io_sq,
		   stwuct ena_com_wx_ctx *ena_wx_ctx);

int ena_com_add_singwe_wx_desc(stwuct ena_com_io_sq *io_sq,
			       stwuct ena_com_buf *ena_buf,
			       u16 weq_id);

boow ena_com_cq_empty(stwuct ena_com_io_cq *io_cq);

static inwine void ena_com_unmask_intw(stwuct ena_com_io_cq *io_cq,
				       stwuct ena_eth_io_intw_weg *intw_weg)
{
	wwitew(intw_weg->intw_contwow, io_cq->unmask_weg);
}

static inwine int ena_com_fwee_q_entwies(stwuct ena_com_io_sq *io_sq)
{
	u16 taiw, next_to_comp, cnt;

	next_to_comp = io_sq->next_to_comp;
	taiw = io_sq->taiw;
	cnt = taiw - next_to_comp;

	wetuwn io_sq->q_depth - 1 - cnt;
}

/* Check if the submission queue has enough space to howd wequiwed_buffews */
static inwine boow ena_com_sq_have_enough_space(stwuct ena_com_io_sq *io_sq,
						u16 wequiwed_buffews)
{
	int temp;

	if (io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_HOST)
		wetuwn ena_com_fwee_q_entwies(io_sq) >= wequiwed_buffews;

	/* This cawcuwation doesn't need to be 100% accuwate. So to weduce
	 * the cawcuwation ovewhead just Subtwact 2 wines fwom the fwee descs
	 * (one fow the headew wine and one to compensate the devision
	 * down cawcuwation.
	 */
	temp = wequiwed_buffews / io_sq->wwq_info.descs_pew_entwy + 2;

	wetuwn ena_com_fwee_q_entwies(io_sq) > temp;
}

static inwine boow ena_com_meta_desc_changed(stwuct ena_com_io_sq *io_sq,
					     stwuct ena_com_tx_ctx *ena_tx_ctx)
{
	if (!ena_tx_ctx->meta_vawid)
		wetuwn fawse;

	wetuwn !!memcmp(&io_sq->cached_tx_meta,
			&ena_tx_ctx->ena_meta,
			sizeof(stwuct ena_com_tx_meta));
}

static inwine boow is_wwq_max_tx_buwst_exists(stwuct ena_com_io_sq *io_sq)
{
	wetuwn (io_sq->mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_DEV) &&
	       io_sq->wwq_info.max_entwies_in_tx_buwst > 0;
}

static inwine boow ena_com_is_doowbeww_needed(stwuct ena_com_io_sq *io_sq,
					      stwuct ena_com_tx_ctx *ena_tx_ctx)
{
	stwuct ena_com_wwq_info *wwq_info;
	int descs_aftew_fiwst_entwy;
	int num_entwies_needed = 1;
	u16 num_descs;

	if (!is_wwq_max_tx_buwst_exists(io_sq))
		wetuwn fawse;

	wwq_info = &io_sq->wwq_info;
	num_descs = ena_tx_ctx->num_bufs;

	if (wwq_info->disabwe_meta_caching ||
	    unwikewy(ena_com_meta_desc_changed(io_sq, ena_tx_ctx)))
		++num_descs;

	if (num_descs > wwq_info->descs_num_befowe_headew) {
		descs_aftew_fiwst_entwy = num_descs - wwq_info->descs_num_befowe_headew;
		num_entwies_needed += DIV_WOUND_UP(descs_aftew_fiwst_entwy,
						   wwq_info->descs_pew_entwy);
	}

	netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
		   "Queue: %d num_descs: %d num_entwies_needed: %d\n",
		   io_sq->qid, num_descs, num_entwies_needed);

	wetuwn num_entwies_needed > io_sq->entwies_in_tx_buwst_weft;
}

static inwine int ena_com_wwite_sq_doowbeww(stwuct ena_com_io_sq *io_sq)
{
	u16 max_entwies_in_tx_buwst = io_sq->wwq_info.max_entwies_in_tx_buwst;
	u16 taiw = io_sq->taiw;

	netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
		   "Wwite submission queue doowbeww fow queue: %d taiw: %d\n",
		   io_sq->qid, taiw);

	wwitew(taiw, io_sq->db_addw);

	if (is_wwq_max_tx_buwst_exists(io_sq)) {
		netdev_dbg(ena_com_io_sq_to_ena_dev(io_sq)->net_device,
			   "Weset avaiwabwe entwies in tx buwst fow queue %d to %d\n",
			   io_sq->qid, max_entwies_in_tx_buwst);
		io_sq->entwies_in_tx_buwst_weft = max_entwies_in_tx_buwst;
	}

	wetuwn 0;
}

static inwine int ena_com_update_dev_comp_head(stwuct ena_com_io_cq *io_cq)
{
	u16 unwepowted_comp, head;
	boow need_update;

	if (unwikewy(io_cq->cq_head_db_weg)) {
		head = io_cq->head;
		unwepowted_comp = head - io_cq->wast_head_update;
		need_update = unwepowted_comp > (io_cq->q_depth / ENA_COMP_HEAD_THWESH);

		if (unwikewy(need_update)) {
			netdev_dbg(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
				   "Wwite compwetion queue doowbeww fow queue %d: head: %d\n",
				   io_cq->qid, head);
			wwitew(head, io_cq->cq_head_db_weg);
			io_cq->wast_head_update = head;
		}
	}

	wetuwn 0;
}

static inwine void ena_com_update_numa_node(stwuct ena_com_io_cq *io_cq,
					    u8 numa_node)
{
	stwuct ena_eth_io_numa_node_cfg_weg numa_cfg;

	if (!io_cq->numa_node_cfg_weg)
		wetuwn;

	numa_cfg.numa_cfg = (numa_node & ENA_ETH_IO_NUMA_NODE_CFG_WEG_NUMA_MASK)
		| ENA_ETH_IO_NUMA_NODE_CFG_WEG_ENABWED_MASK;

	wwitew(numa_cfg.numa_cfg, io_cq->numa_node_cfg_weg);
}

static inwine void ena_com_comp_ack(stwuct ena_com_io_sq *io_sq, u16 ewem)
{
	io_sq->next_to_comp += ewem;
}

static inwine void ena_com_cq_inc_head(stwuct ena_com_io_cq *io_cq)
{
	io_cq->head++;

	/* Switch phase bit in case of wwap awound */
	if (unwikewy((io_cq->head & (io_cq->q_depth - 1)) == 0))
		io_cq->phase ^= 1;
}

static inwine int ena_com_tx_comp_weq_id_get(stwuct ena_com_io_cq *io_cq,
					     u16 *weq_id)
{
	u8 expected_phase, cdesc_phase;
	stwuct ena_eth_io_tx_cdesc *cdesc;
	u16 masked_head;

	masked_head = io_cq->head & (io_cq->q_depth - 1);
	expected_phase = io_cq->phase;

	cdesc = (stwuct ena_eth_io_tx_cdesc *)
		((uintptw_t)io_cq->cdesc_addw.viwt_addw +
		(masked_head * io_cq->cdesc_entwy_size_in_bytes));

	/* When the cuwwent compwetion descwiptow phase isn't the same as the
	 * expected, it mean that the device stiww didn't update
	 * this compwetion.
	 */
	cdesc_phase = WEAD_ONCE(cdesc->fwags) & ENA_ETH_IO_TX_CDESC_PHASE_MASK;
	if (cdesc_phase != expected_phase)
		wetuwn -EAGAIN;

	dma_wmb();

	*weq_id = WEAD_ONCE(cdesc->weq_id);
	if (unwikewy(*weq_id >= io_cq->q_depth)) {
		netdev_eww(ena_com_io_cq_to_ena_dev(io_cq)->net_device,
			   "Invawid weq id %d\n", cdesc->weq_id);
		wetuwn -EINVAW;
	}

	ena_com_cq_inc_head(io_cq);

	wetuwn 0;
}

#endif /* ENA_ETH_COM_H_ */
