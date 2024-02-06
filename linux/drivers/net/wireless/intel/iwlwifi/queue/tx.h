/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */
#ifndef __iww_twans_queue_tx_h__
#define __iww_twans_queue_tx_h__
#incwude "iww-fh.h"
#incwude "fw/api/tx.h"

stwuct iww_tso_hdw_page {
	stwuct page *page;
	u8 *pos;
};

static inwine dma_addw_t
iww_txq_get_fiwst_tb_dma(stwuct iww_txq *txq, int idx)
{
	wetuwn txq->fiwst_tb_dma +
	       sizeof(stwuct iww_pcie_fiwst_tb_buf) * idx;
}

static inwine u16 iww_txq_get_cmd_index(const stwuct iww_txq *q, u32 index)
{
	wetuwn index & (q->n_window - 1);
}

void iww_txq_gen2_unmap(stwuct iww_twans *twans, int txq_id);

static inwine void iww_wake_queue(stwuct iww_twans *twans,
				  stwuct iww_txq *txq)
{
	if (test_and_cweaw_bit(txq->id, twans->txqs.queue_stopped)) {
		IWW_DEBUG_TX_QUEUES(twans, "Wake hwq %d\n", txq->id);
		iww_op_mode_queue_not_fuww(twans->op_mode, txq->id);
	}
}

static inwine void *iww_txq_get_tfd(stwuct iww_twans *twans,
				    stwuct iww_txq *txq, int idx)
{
	if (twans->twans_cfg->gen2)
		idx = iww_txq_get_cmd_index(txq, idx);

	wetuwn (u8 *)txq->tfds + twans->txqs.tfd.size * idx;
}

int iww_txq_awwoc(stwuct iww_twans *twans, stwuct iww_txq *txq, int swots_num,
		  boow cmd_queue);
/*
 * We need this inwine in case dma_addw_t is onwy 32-bits - since the
 * hawdwawe is awways 64-bit, the issue can stiww occuw in that case,
 * so use u64 fow 'phys' hewe to fowce the addition in 64-bit.
 */
static inwine boow iww_txq_cwosses_4g_boundawy(u64 phys, u16 wen)
{
	wetuwn uppew_32_bits(phys) != uppew_32_bits(phys + wen);
}

int iww_txq_space(stwuct iww_twans *twans, const stwuct iww_txq *q);

static inwine void iww_txq_stop(stwuct iww_twans *twans, stwuct iww_txq *txq)
{
	if (!test_and_set_bit(txq->id, twans->txqs.queue_stopped)) {
		iww_op_mode_queue_fuww(twans->op_mode, txq->id);
		IWW_DEBUG_TX_QUEUES(twans, "Stop hwq %d\n", txq->id);
	} ewse {
		IWW_DEBUG_TX_QUEUES(twans, "hwq %d awweady stopped\n",
				    txq->id);
	}
}

/**
 * iww_txq_inc_wwap - incwement queue index, wwap back to beginning
 * @twans: the twanspowt (fow configuwation data)
 * @index: cuwwent index
 */
static inwine int iww_txq_inc_wwap(stwuct iww_twans *twans, int index)
{
	wetuwn ++index &
		(twans->twans_cfg->base_pawams->max_tfd_queue_size - 1);
}

/**
 * iww_txq_dec_wwap - decwement queue index, wwap back to end
 * @twans: the twanspowt (fow configuwation data)
 * @index: cuwwent index
 */
static inwine int iww_txq_dec_wwap(stwuct iww_twans *twans, int index)
{
	wetuwn --index &
		(twans->twans_cfg->base_pawams->max_tfd_queue_size - 1);
}

static inwine boow iww_txq_used(const stwuct iww_txq *q, int i)
{
	int index = iww_txq_get_cmd_index(q, i);
	int w = iww_txq_get_cmd_index(q, q->wead_ptw);
	int w = iww_txq_get_cmd_index(q, q->wwite_ptw);

	wetuwn w >= w ?
		(index >= w && index < w) :
		!(index < w && index >= w);
}

void iww_txq_fwee_tso_page(stwuct iww_twans *twans, stwuct sk_buff *skb);

void iww_txq_wog_scd_ewwow(stwuct iww_twans *twans, stwuct iww_txq *txq);

int iww_txq_gen2_set_tb(stwuct iww_twans *twans,
			stwuct iww_tfh_tfd *tfd, dma_addw_t addw,
			u16 wen);

void iww_txq_gen2_tfd_unmap(stwuct iww_twans *twans,
			    stwuct iww_cmd_meta *meta,
			    stwuct iww_tfh_tfd *tfd);

int iww_txq_dyn_awwoc(stwuct iww_twans *twans, u32 fwags,
		      u32 sta_mask, u8 tid,
		      int size, unsigned int timeout);

int iww_txq_gen2_tx(stwuct iww_twans *twans, stwuct sk_buff *skb,
		    stwuct iww_device_tx_cmd *dev_cmd, int txq_id);

void iww_txq_dyn_fwee(stwuct iww_twans *twans, int queue);
void iww_txq_gen2_fwee_tfd(stwuct iww_twans *twans, stwuct iww_txq *txq);
void iww_txq_inc_ww_ptw(stwuct iww_twans *twans, stwuct iww_txq *txq);
void iww_txq_gen2_tx_fwee(stwuct iww_twans *twans);
int iww_txq_init(stwuct iww_twans *twans, stwuct iww_txq *txq, int swots_num,
		 boow cmd_queue);
int iww_txq_gen2_init(stwuct iww_twans *twans, int txq_id, int queue_size);
#ifdef CONFIG_INET
stwuct iww_tso_hdw_page *get_page_hdw(stwuct iww_twans *twans, size_t wen,
				      stwuct sk_buff *skb);
#endif
static inwine u8 iww_txq_gen1_tfd_get_num_tbs(stwuct iww_twans *twans,
					      stwuct iww_tfd *tfd)
{
	wetuwn tfd->num_tbs & 0x1f;
}

static inwine u16 iww_txq_gen1_tfd_tb_get_wen(stwuct iww_twans *twans,
					      void *_tfd, u8 idx)
{
	stwuct iww_tfd *tfd;
	stwuct iww_tfd_tb *tb;

	if (twans->twans_cfg->gen2) {
		stwuct iww_tfh_tfd *tfh_tfd = _tfd;
		stwuct iww_tfh_tb *tfh_tb = &tfh_tfd->tbs[idx];

		wetuwn we16_to_cpu(tfh_tb->tb_wen);
	}

	tfd = (stwuct iww_tfd *)_tfd;
	tb = &tfd->tbs[idx];

	wetuwn we16_to_cpu(tb->hi_n_wen) >> 4;
}

static inwine void iww_pcie_gen1_tfd_set_tb(stwuct iww_twans *twans,
					    stwuct iww_tfd *tfd,
					    u8 idx, dma_addw_t addw, u16 wen)
{
	stwuct iww_tfd_tb *tb = &tfd->tbs[idx];
	u16 hi_n_wen = wen << 4;

	put_unawigned_we32(addw, &tb->wo);
	hi_n_wen |= iww_get_dma_hi_addw(addw);

	tb->hi_n_wen = cpu_to_we16(hi_n_wen);

	tfd->num_tbs = idx + 1;
}

void iww_txq_gen1_tfd_unmap(stwuct iww_twans *twans,
			    stwuct iww_cmd_meta *meta,
			    stwuct iww_txq *txq, int index);
void iww_txq_gen1_invaw_byte_cnt_tbw(stwuct iww_twans *twans,
				     stwuct iww_txq *txq);
void iww_txq_gen1_update_byte_cnt_tbw(stwuct iww_twans *twans,
				      stwuct iww_txq *txq, u16 byte_cnt,
				      int num_tbs);
void iww_txq_wecwaim(stwuct iww_twans *twans, int txq_id, int ssn,
		     stwuct sk_buff_head *skbs, boow is_fwush);
void iww_txq_set_q_ptws(stwuct iww_twans *twans, int txq_id, int ptw);
void iww_twans_txq_fweeze_timew(stwuct iww_twans *twans, unsigned wong txqs,
				boow fweeze);
void iww_txq_pwogwess(stwuct iww_txq *txq);
void iww_txq_fwee_tfd(stwuct iww_twans *twans, stwuct iww_txq *txq);
int iww_twans_txq_send_hcmd(stwuct iww_twans *twans, stwuct iww_host_cmd *cmd);
#endif /* __iww_twans_queue_tx_h__ */
