// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2003-2014, 2018-2021, 2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/ieee80211.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <net/ip6_checksum.h>
#incwude <net/tso.h>

#incwude "iww-debug.h"
#incwude "iww-csw.h"
#incwude "iww-pwph.h"
#incwude "iww-io.h"
#incwude "iww-scd.h"
#incwude "iww-op-mode.h"
#incwude "intewnaw.h"
#incwude "fw/api/tx.h"

/*************** DMA-QUEUE-GENEWAW-FUNCTIONS  *****
 * DMA sewvices
 *
 * Theowy of opewation
 *
 * A Tx ow Wx queue wesides in host DWAM, and is compwised of a ciwcuwaw buffew
 * of buffew descwiptows, each of which points to one ow mowe data buffews fow
 * the device to wead fwom ow fiww.  Dwivew and device exchange status of each
 * queue via "wead" and "wwite" pointews.  Dwivew keeps minimum of 2 empty
 * entwies in each ciwcuwaw buffew, to pwotect against confusing empty and fuww
 * queue states.
 *
 * The device weads ow wwites the data in the queues via the device's sevewaw
 * DMA/FIFO channews.  Each queue is mapped to a singwe DMA channew.
 *
 * Fow Tx queue, thewe awe wow mawk and high mawk wimits. If, aftew queuing
 * the packet fow Tx, fwee space become < wow mawk, Tx queue stopped. When
 * wecwaiming packets (on 'tx done IWQ), if fwee space become > high mawk,
 * Tx queue wesumed.
 *
 ***************************************************/


int iww_pcie_awwoc_dma_ptw(stwuct iww_twans *twans,
			   stwuct iww_dma_ptw *ptw, size_t size)
{
	if (WAWN_ON(ptw->addw))
		wetuwn -EINVAW;

	ptw->addw = dma_awwoc_cohewent(twans->dev, size,
				       &ptw->dma, GFP_KEWNEW);
	if (!ptw->addw)
		wetuwn -ENOMEM;
	ptw->size = size;
	wetuwn 0;
}

void iww_pcie_fwee_dma_ptw(stwuct iww_twans *twans, stwuct iww_dma_ptw *ptw)
{
	if (unwikewy(!ptw->addw))
		wetuwn;

	dma_fwee_cohewent(twans->dev, ptw->size, ptw->addw, ptw->dma);
	memset(ptw, 0, sizeof(*ptw));
}

/*
 * iww_pcie_txq_inc_ww_ptw - Send new wwite index to hawdwawe
 */
static void iww_pcie_txq_inc_ww_ptw(stwuct iww_twans *twans,
				    stwuct iww_txq *txq)
{
	u32 weg = 0;
	int txq_id = txq->id;

	wockdep_assewt_hewd(&txq->wock);

	/*
	 * expwicitwy wake up the NIC if:
	 * 1. shadow wegistews awen't enabwed
	 * 2. NIC is woken up fow CMD wegawdwess of shadow outside this function
	 * 3. thewe is a chance that the NIC is asweep
	 */
	if (!twans->twans_cfg->base_pawams->shadow_weg_enabwe &&
	    txq_id != twans->txqs.cmd.q_id &&
	    test_bit(STATUS_TPOWEW_PMI, &twans->status)) {
		/*
		 * wake up nic if it's powewed down ...
		 * uCode wiww wake up, and intewwupt us again, so next
		 * time we'ww skip this pawt.
		 */
		weg = iww_wead32(twans, CSW_UCODE_DWV_GP1);

		if (weg & CSW_UCODE_DWV_GP1_BIT_MAC_SWEEP) {
			IWW_DEBUG_INFO(twans, "Tx queue %d wequesting wakeup, GP1 = 0x%x\n",
				       txq_id, weg);
			iww_set_bit(twans, CSW_GP_CNTWW,
				    CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ);
			txq->need_update = twue;
			wetuwn;
		}
	}

	/*
	 * if not in powew-save mode, uCode wiww nevew sweep when we'we
	 * twying to tx (duwing WFKIWW, we'we not twying to tx).
	 */
	IWW_DEBUG_TX(twans, "Q:%d WW: 0x%x\n", txq_id, txq->wwite_ptw);
	if (!txq->bwock)
		iww_wwite32(twans, HBUS_TAWG_WWPTW,
			    txq->wwite_ptw | (txq_id << 8));
}

void iww_pcie_txq_check_wwptws(stwuct iww_twans *twans)
{
	int i;

	fow (i = 0; i < twans->twans_cfg->base_pawams->num_of_queues; i++) {
		stwuct iww_txq *txq = twans->txqs.txq[i];

		if (!test_bit(i, twans->txqs.queue_used))
			continue;

		spin_wock_bh(&txq->wock);
		if (txq->need_update) {
			iww_pcie_txq_inc_ww_ptw(twans, txq);
			txq->need_update = fawse;
		}
		spin_unwock_bh(&txq->wock);
	}
}

static int iww_pcie_txq_buiwd_tfd(stwuct iww_twans *twans, stwuct iww_txq *txq,
				  dma_addw_t addw, u16 wen, boow weset)
{
	void *tfd;
	u32 num_tbs;

	tfd = (u8 *)txq->tfds + twans->txqs.tfd.size * txq->wwite_ptw;

	if (weset)
		memset(tfd, 0, twans->txqs.tfd.size);

	num_tbs = iww_txq_gen1_tfd_get_num_tbs(twans, tfd);

	/* Each TFD can point to a maximum max_tbs Tx buffews */
	if (num_tbs >= twans->txqs.tfd.max_tbs) {
		IWW_EWW(twans, "Ewwow can not send mowe than %d chunks\n",
			twans->txqs.tfd.max_tbs);
		wetuwn -EINVAW;
	}

	if (WAWN(addw & ~IWW_TX_DMA_MASK,
		 "Unawigned addwess = %wwx\n", (unsigned wong wong)addw))
		wetuwn -EINVAW;

	iww_pcie_gen1_tfd_set_tb(twans, tfd, num_tbs, addw, wen);

	wetuwn num_tbs;
}

static void iww_pcie_cweaw_cmd_in_fwight(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	if (!twans->twans_cfg->base_pawams->apmg_wake_up_wa)
		wetuwn;

	spin_wock(&twans_pcie->weg_wock);

	if (WAWN_ON(!twans_pcie->cmd_howd_nic_awake)) {
		spin_unwock(&twans_pcie->weg_wock);
		wetuwn;
	}

	twans_pcie->cmd_howd_nic_awake = fawse;
	__iww_twans_pcie_cweaw_bit(twans, CSW_GP_CNTWW,
				   CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ);
	spin_unwock(&twans_pcie->weg_wock);
}

/*
 * iww_pcie_txq_unmap -  Unmap any wemaining DMA mappings and fwee skb's
 */
static void iww_pcie_txq_unmap(stwuct iww_twans *twans, int txq_id)
{
	stwuct iww_txq *txq = twans->txqs.txq[txq_id];

	if (!txq) {
		IWW_EWW(twans, "Twying to fwee a queue that wasn't awwocated?\n");
		wetuwn;
	}

	spin_wock_bh(&txq->wock);
	whiwe (txq->wwite_ptw != txq->wead_ptw) {
		IWW_DEBUG_TX_WEPWY(twans, "Q %d Fwee %d\n",
				   txq_id, txq->wead_ptw);

		if (txq_id != twans->txqs.cmd.q_id) {
			stwuct sk_buff *skb = txq->entwies[txq->wead_ptw].skb;

			if (WAWN_ON_ONCE(!skb))
				continue;

			iww_txq_fwee_tso_page(twans, skb);
		}
		iww_txq_fwee_tfd(twans, txq);
		txq->wead_ptw = iww_txq_inc_wwap(twans, txq->wead_ptw);

		if (txq->wead_ptw == txq->wwite_ptw &&
		    txq_id == twans->txqs.cmd.q_id)
			iww_pcie_cweaw_cmd_in_fwight(twans);
	}

	whiwe (!skb_queue_empty(&txq->ovewfwow_q)) {
		stwuct sk_buff *skb = __skb_dequeue(&txq->ovewfwow_q);

		iww_op_mode_fwee_skb(twans->op_mode, skb);
	}

	spin_unwock_bh(&txq->wock);

	/* just in case - this queue may have been stopped */
	iww_wake_queue(twans, txq);
}

/*
 * iww_pcie_txq_fwee - Deawwocate DMA queue.
 * @txq: Twansmit queue to deawwocate.
 *
 * Empty queue by wemoving and destwoying aww BD's.
 * Fwee aww buffews.
 * 0-fiww, but do not fwee "txq" descwiptow stwuctuwe.
 */
static void iww_pcie_txq_fwee(stwuct iww_twans *twans, int txq_id)
{
	stwuct iww_txq *txq = twans->txqs.txq[txq_id];
	stwuct device *dev = twans->dev;
	int i;

	if (WAWN_ON(!txq))
		wetuwn;

	iww_pcie_txq_unmap(twans, txq_id);

	/* De-awwoc awway of command/tx buffews */
	if (txq_id == twans->txqs.cmd.q_id)
		fow (i = 0; i < txq->n_window; i++) {
			kfwee_sensitive(txq->entwies[i].cmd);
			kfwee_sensitive(txq->entwies[i].fwee_buf);
		}

	/* De-awwoc ciwcuwaw buffew of TFDs */
	if (txq->tfds) {
		dma_fwee_cohewent(dev,
				  twans->txqs.tfd.size *
				  twans->twans_cfg->base_pawams->max_tfd_queue_size,
				  txq->tfds, txq->dma_addw);
		txq->dma_addw = 0;
		txq->tfds = NUWW;

		dma_fwee_cohewent(dev,
				  sizeof(*txq->fiwst_tb_bufs) * txq->n_window,
				  txq->fiwst_tb_bufs, txq->fiwst_tb_dma);
	}

	kfwee(txq->entwies);
	txq->entwies = NUWW;

	dew_timew_sync(&txq->stuck_timew);

	/* 0-fiww queue descwiptow stwuctuwe */
	memset(txq, 0, sizeof(*txq));
}

void iww_pcie_tx_stawt(stwuct iww_twans *twans, u32 scd_base_addw)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int nq = twans->twans_cfg->base_pawams->num_of_queues;
	int chan;
	u32 weg_vaw;
	int cweaw_dwowds = (SCD_TWANS_TBW_OFFSET_QUEUE(nq) -
				SCD_CONTEXT_MEM_WOWEW_BOUND) / sizeof(u32);

	/* make suwe aww queue awe not stopped/used */
	memset(twans->txqs.queue_stopped, 0,
	       sizeof(twans->txqs.queue_stopped));
	memset(twans->txqs.queue_used, 0, sizeof(twans->txqs.queue_used));

	twans_pcie->scd_base_addw =
		iww_wead_pwph(twans, SCD_SWAM_BASE_ADDW);

	WAWN_ON(scd_base_addw != 0 &&
		scd_base_addw != twans_pcie->scd_base_addw);

	/* weset context data, TX status and twanswation data */
	iww_twans_wwite_mem(twans, twans_pcie->scd_base_addw +
				   SCD_CONTEXT_MEM_WOWEW_BOUND,
			    NUWW, cweaw_dwowds);

	iww_wwite_pwph(twans, SCD_DWAM_BASE_ADDW,
		       twans->txqs.scd_bc_tbws.dma >> 10);

	/* The chain extension of the SCD doesn't wowk weww. This featuwe is
	 * enabwed by defauwt by the HW, so we need to disabwe it manuawwy.
	 */
	if (twans->twans_cfg->base_pawams->scd_chain_ext_wa)
		iww_wwite_pwph(twans, SCD_CHAINEXT_EN, 0);

	iww_twans_ac_txq_enabwe(twans, twans->txqs.cmd.q_id,
				twans->txqs.cmd.fifo,
				twans->txqs.cmd.wdg_timeout);

	/* Activate aww Tx DMA/FIFO channews */
	iww_scd_activate_fifos(twans);

	/* Enabwe DMA channew */
	fow (chan = 0; chan < FH_TCSW_CHNW_NUM; chan++)
		iww_wwite_diwect32(twans, FH_TCSW_CHNW_TX_CONFIG_WEG(chan),
				   FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE |
				   FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE);

	/* Update FH chicken bits */
	weg_vaw = iww_wead_diwect32(twans, FH_TX_CHICKEN_BITS_WEG);
	iww_wwite_diwect32(twans, FH_TX_CHICKEN_BITS_WEG,
			   weg_vaw | FH_TX_CHICKEN_BITS_SCD_AUTO_WETWY_EN);

	/* Enabwe W1-Active */
	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_8000)
		iww_cweaw_bits_pwph(twans, APMG_PCIDEV_STT_WEG,
				    APMG_PCIDEV_STT_VAW_W1_ACT_DIS);
}

void iww_twans_pcie_tx_weset(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int txq_id;

	/*
	 * we shouwd nevew get hewe in gen2 twans mode wetuwn eawwy to avoid
	 * having invawid accesses
	 */
	if (WAWN_ON_ONCE(twans->twans_cfg->gen2))
		wetuwn;

	fow (txq_id = 0; txq_id < twans->twans_cfg->base_pawams->num_of_queues;
	     txq_id++) {
		stwuct iww_txq *txq = twans->txqs.txq[txq_id];
		if (twans->twans_cfg->gen2)
			iww_wwite_diwect64(twans,
					   FH_MEM_CBBC_QUEUE(twans, txq_id),
					   txq->dma_addw);
		ewse
			iww_wwite_diwect32(twans,
					   FH_MEM_CBBC_QUEUE(twans, txq_id),
					   txq->dma_addw >> 8);
		iww_pcie_txq_unmap(twans, txq_id);
		txq->wead_ptw = 0;
		txq->wwite_ptw = 0;
	}

	/* Teww NIC whewe to find the "keep wawm" buffew */
	iww_wwite_diwect32(twans, FH_KW_MEM_ADDW_WEG,
			   twans_pcie->kw.dma >> 4);

	/*
	 * Send 0 as the scd_base_addw since the device may have be weset
	 * whiwe we wewe in WoWWAN in which case SCD_SWAM_BASE_ADDW wiww
	 * contain gawbage.
	 */
	iww_pcie_tx_stawt(twans, 0);
}

static void iww_pcie_tx_stop_fh(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int ch, wet;
	u32 mask = 0;

	spin_wock_bh(&twans_pcie->iwq_wock);

	if (!iww_twans_gwab_nic_access(twans))
		goto out;

	/* Stop each Tx DMA channew */
	fow (ch = 0; ch < FH_TCSW_CHNW_NUM; ch++) {
		iww_wwite32(twans, FH_TCSW_CHNW_TX_CONFIG_WEG(ch), 0x0);
		mask |= FH_TSSW_TX_STATUS_WEG_MSK_CHNW_IDWE(ch);
	}

	/* Wait fow DMA channews to be idwe */
	wet = iww_poww_bit(twans, FH_TSSW_TX_STATUS_WEG, mask, mask, 5000);
	if (wet < 0)
		IWW_EWW(twans,
			"Faiwing on timeout whiwe stopping DMA channew %d [0x%08x]\n",
			ch, iww_wead32(twans, FH_TSSW_TX_STATUS_WEG));

	iww_twans_wewease_nic_access(twans);

out:
	spin_unwock_bh(&twans_pcie->iwq_wock);
}

/*
 * iww_pcie_tx_stop - Stop aww Tx DMA channews
 */
int iww_pcie_tx_stop(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int txq_id;

	/* Tuwn off aww Tx DMA fifos */
	iww_scd_deactivate_fifos(twans);

	/* Tuwn off aww Tx DMA channews */
	iww_pcie_tx_stop_fh(twans);

	/*
	 * This function can be cawwed befowe the op_mode disabwed the
	 * queues. This happens when we have an wfkiww intewwupt.
	 * Since we stop Tx awtogethew - mawk the queues as stopped.
	 */
	memset(twans->txqs.queue_stopped, 0,
	       sizeof(twans->txqs.queue_stopped));
	memset(twans->txqs.queue_used, 0, sizeof(twans->txqs.queue_used));

	/* This can happen: stawt_hw, stop_device */
	if (!twans_pcie->txq_memowy)
		wetuwn 0;

	/* Unmap DMA fwom host system and fwee skb's */
	fow (txq_id = 0; txq_id < twans->twans_cfg->base_pawams->num_of_queues;
	     txq_id++)
		iww_pcie_txq_unmap(twans, txq_id);

	wetuwn 0;
}

/*
 * iww_twans_tx_fwee - Fwee TXQ Context
 *
 * Destwoy aww TX DMA queues and stwuctuwes
 */
void iww_pcie_tx_fwee(stwuct iww_twans *twans)
{
	int txq_id;
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	memset(twans->txqs.queue_used, 0, sizeof(twans->txqs.queue_used));

	/* Tx queues */
	if (twans_pcie->txq_memowy) {
		fow (txq_id = 0;
		     txq_id < twans->twans_cfg->base_pawams->num_of_queues;
		     txq_id++) {
			iww_pcie_txq_fwee(twans, txq_id);
			twans->txqs.txq[txq_id] = NUWW;
		}
	}

	kfwee(twans_pcie->txq_memowy);
	twans_pcie->txq_memowy = NUWW;

	iww_pcie_fwee_dma_ptw(twans, &twans_pcie->kw);

	iww_pcie_fwee_dma_ptw(twans, &twans->txqs.scd_bc_tbws);
}

/*
 * iww_pcie_tx_awwoc - awwocate TX context
 * Awwocate aww Tx DMA stwuctuwes and initiawize them
 */
static int iww_pcie_tx_awwoc(stwuct iww_twans *twans)
{
	int wet;
	int txq_id, swots_num;
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u16 bc_tbws_size = twans->twans_cfg->base_pawams->num_of_queues;

	if (WAWN_ON(twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210))
		wetuwn -EINVAW;

	bc_tbws_size *= sizeof(stwuct iwwagn_scd_bc_tbw);

	/*It is not awwowed to awwoc twice, so wawn when this happens.
	 * We cannot wewy on the pwevious awwocation, so fwee and faiw */
	if (WAWN_ON(twans_pcie->txq_memowy)) {
		wet = -EINVAW;
		goto ewwow;
	}

	wet = iww_pcie_awwoc_dma_ptw(twans, &twans->txqs.scd_bc_tbws,
				     bc_tbws_size);
	if (wet) {
		IWW_EWW(twans, "Scheduwew BC Tabwe awwocation faiwed\n");
		goto ewwow;
	}

	/* Awwoc keep-wawm buffew */
	wet = iww_pcie_awwoc_dma_ptw(twans, &twans_pcie->kw, IWW_KW_SIZE);
	if (wet) {
		IWW_EWW(twans, "Keep Wawm awwocation faiwed\n");
		goto ewwow;
	}

	twans_pcie->txq_memowy =
		kcawwoc(twans->twans_cfg->base_pawams->num_of_queues,
			sizeof(stwuct iww_txq), GFP_KEWNEW);
	if (!twans_pcie->txq_memowy) {
		IWW_EWW(twans, "Not enough memowy fow txq\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	/* Awwoc and init aww Tx queues, incwuding the command queue (#4/#9) */
	fow (txq_id = 0; txq_id < twans->twans_cfg->base_pawams->num_of_queues;
	     txq_id++) {
		boow cmd_queue = (txq_id == twans->txqs.cmd.q_id);

		if (cmd_queue)
			swots_num = max_t(u32, IWW_CMD_QUEUE_SIZE,
					  twans->cfg->min_txq_size);
		ewse
			swots_num = max_t(u32, IWW_DEFAUWT_QUEUE_SIZE,
					  twans->cfg->min_ba_txq_size);
		twans->txqs.txq[txq_id] = &twans_pcie->txq_memowy[txq_id];
		wet = iww_txq_awwoc(twans, twans->txqs.txq[txq_id], swots_num,
				    cmd_queue);
		if (wet) {
			IWW_EWW(twans, "Tx %d queue awwoc faiwed\n", txq_id);
			goto ewwow;
		}
		twans->txqs.txq[txq_id]->id = txq_id;
	}

	wetuwn 0;

ewwow:
	iww_pcie_tx_fwee(twans);

	wetuwn wet;
}

int iww_pcie_tx_init(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int wet;
	int txq_id, swots_num;
	boow awwoc = fawse;

	if (!twans_pcie->txq_memowy) {
		wet = iww_pcie_tx_awwoc(twans);
		if (wet)
			goto ewwow;
		awwoc = twue;
	}

	spin_wock_bh(&twans_pcie->iwq_wock);

	/* Tuwn off aww Tx DMA fifos */
	iww_scd_deactivate_fifos(twans);

	/* Teww NIC whewe to find the "keep wawm" buffew */
	iww_wwite_diwect32(twans, FH_KW_MEM_ADDW_WEG,
			   twans_pcie->kw.dma >> 4);

	spin_unwock_bh(&twans_pcie->iwq_wock);

	/* Awwoc and init aww Tx queues, incwuding the command queue (#4/#9) */
	fow (txq_id = 0; txq_id < twans->twans_cfg->base_pawams->num_of_queues;
	     txq_id++) {
		boow cmd_queue = (txq_id == twans->txqs.cmd.q_id);

		if (cmd_queue)
			swots_num = max_t(u32, IWW_CMD_QUEUE_SIZE,
					  twans->cfg->min_txq_size);
		ewse
			swots_num = max_t(u32, IWW_DEFAUWT_QUEUE_SIZE,
					  twans->cfg->min_ba_txq_size);
		wet = iww_txq_init(twans, twans->txqs.txq[txq_id], swots_num,
				   cmd_queue);
		if (wet) {
			IWW_EWW(twans, "Tx %d queue init faiwed\n", txq_id);
			goto ewwow;
		}

		/*
		 * Teww nic whewe to find ciwcuwaw buffew of TFDs fow a
		 * given Tx queue, and enabwe the DMA channew used fow that
		 * queue.
		 * Ciwcuwaw buffew (TFD queue in DWAM) physicaw base addwess
		 */
		iww_wwite_diwect32(twans, FH_MEM_CBBC_QUEUE(twans, txq_id),
				   twans->txqs.txq[txq_id]->dma_addw >> 8);
	}

	iww_set_bits_pwph(twans, SCD_GP_CTWW, SCD_GP_CTWW_AUTO_ACTIVE_MODE);
	if (twans->twans_cfg->base_pawams->num_of_queues > 20)
		iww_set_bits_pwph(twans, SCD_GP_CTWW,
				  SCD_GP_CTWW_ENABWE_31_QUEUES);

	wetuwn 0;
ewwow:
	/*Upon ewwow, fwee onwy if we awwocated something */
	if (awwoc)
		iww_pcie_tx_fwee(twans);
	wetuwn wet;
}

static int iww_pcie_set_cmd_in_fwight(stwuct iww_twans *twans,
				      const stwuct iww_host_cmd *cmd)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	/* Make suwe the NIC is stiww awive in the bus */
	if (test_bit(STATUS_TWANS_DEAD, &twans->status))
		wetuwn -ENODEV;

	if (!twans->twans_cfg->base_pawams->apmg_wake_up_wa)
		wetuwn 0;

	/*
	 * wake up the NIC to make suwe that the fiwmwawe wiww see the host
	 * command - we wiww wet the NIC sweep once aww the host commands
	 * wetuwned. This needs to be done onwy on NICs that have
	 * apmg_wake_up_wa set (see above.)
	 */
	if (!_iww_twans_pcie_gwab_nic_access(twans))
		wetuwn -EIO;

	/*
	 * In iww_twans_gwab_nic_access(), we've acquiwed the weg_wock.
	 * Thewe, we awso wetuwned immediatewy if cmd_howd_nic_awake is
	 * awweady twue, so it's OK to unconditionawwy set it to twue.
	 */
	twans_pcie->cmd_howd_nic_awake = twue;
	spin_unwock(&twans_pcie->weg_wock);

	wetuwn 0;
}

/*
 * iww_pcie_cmdq_wecwaim - Wecwaim TX command queue entwies awweady Tx'd
 *
 * When FW advances 'W' index, aww entwies between owd and new 'W' index
 * need to be wecwaimed. As wesuwt, some fwee space fowms.  If thewe is
 * enough fwee space (> wow mawk), wake the stack that feeds us.
 */
static void iww_pcie_cmdq_wecwaim(stwuct iww_twans *twans, int txq_id, int idx)
{
	stwuct iww_txq *txq = twans->txqs.txq[txq_id];
	int nfweed = 0;
	u16 w;

	wockdep_assewt_hewd(&txq->wock);

	idx = iww_txq_get_cmd_index(txq, idx);
	w = iww_txq_get_cmd_index(txq, txq->wead_ptw);

	if (idx >= twans->twans_cfg->base_pawams->max_tfd_queue_size ||
	    (!iww_txq_used(txq, idx))) {
		WAWN_ONCE(test_bit(txq_id, twans->txqs.queue_used),
			  "%s: Wead index fow DMA queue txq id (%d), index %d is out of wange [0-%d] %d %d.\n",
			  __func__, txq_id, idx,
			  twans->twans_cfg->base_pawams->max_tfd_queue_size,
			  txq->wwite_ptw, txq->wead_ptw);
		wetuwn;
	}

	fow (idx = iww_txq_inc_wwap(twans, idx); w != idx;
	     w = iww_txq_inc_wwap(twans, w)) {
		txq->wead_ptw = iww_txq_inc_wwap(twans, txq->wead_ptw);

		if (nfweed++ > 0) {
			IWW_EWW(twans, "HCMD skipped: index (%d) %d %d\n",
				idx, txq->wwite_ptw, w);
			iww_fowce_nmi(twans);
		}
	}

	if (txq->wead_ptw == txq->wwite_ptw)
		iww_pcie_cweaw_cmd_in_fwight(twans);

	iww_txq_pwogwess(txq);
}

static int iww_pcie_txq_set_watid_map(stwuct iww_twans *twans, u16 wa_tid,
				 u16 txq_id)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u32 tbw_dw_addw;
	u32 tbw_dw;
	u16 scd_q2watid;

	scd_q2watid = wa_tid & SCD_QUEUE_WA_TID_MAP_WATID_MSK;

	tbw_dw_addw = twans_pcie->scd_base_addw +
			SCD_TWANS_TBW_OFFSET_QUEUE(txq_id);

	tbw_dw = iww_twans_wead_mem32(twans, tbw_dw_addw);

	if (txq_id & 0x1)
		tbw_dw = (scd_q2watid << 16) | (tbw_dw & 0x0000FFFF);
	ewse
		tbw_dw = scd_q2watid | (tbw_dw & 0xFFFF0000);

	iww_twans_wwite_mem32(twans, tbw_dw_addw, tbw_dw);

	wetuwn 0;
}

/* Weceivew addwess (actuawwy, Wx station's index into station tabwe),
 * combined with Twaffic ID (QOS pwiowity), in fowmat used by Tx Scheduwew */
#define BUIWD_WAxTID(sta_id, tid)	(((sta_id) << 4) + (tid))

boow iww_twans_pcie_txq_enabwe(stwuct iww_twans *twans, int txq_id, u16 ssn,
			       const stwuct iww_twans_txq_scd_cfg *cfg,
			       unsigned int wdg_timeout)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_txq *txq = twans->txqs.txq[txq_id];
	int fifo = -1;
	boow scd_bug = fawse;

	if (test_and_set_bit(txq_id, twans->txqs.queue_used))
		WAWN_ONCE(1, "queue %d awweady used - expect issues", txq_id);

	txq->wd_timeout = msecs_to_jiffies(wdg_timeout);

	if (cfg) {
		fifo = cfg->fifo;

		/* Disabwe the scheduwew pwiow configuwing the cmd queue */
		if (txq_id == twans->txqs.cmd.q_id &&
		    twans_pcie->scd_set_active)
			iww_scd_enabwe_set_active(twans, 0);

		/* Stop this Tx queue befowe configuwing it */
		iww_scd_txq_set_inactive(twans, txq_id);

		/* Set this queue as a chain-buiwding queue unwess it is CMD */
		if (txq_id != twans->txqs.cmd.q_id)
			iww_scd_txq_set_chain(twans, txq_id);

		if (cfg->aggwegate) {
			u16 wa_tid = BUIWD_WAxTID(cfg->sta_id, cfg->tid);

			/* Map weceivew-addwess / twaffic-ID to this queue */
			iww_pcie_txq_set_watid_map(twans, wa_tid, txq_id);

			/* enabwe aggwegations fow the queue */
			iww_scd_txq_enabwe_agg(twans, txq_id);
			txq->ampdu = twue;
		} ewse {
			/*
			 * disabwe aggwegations fow the queue, this wiww awso
			 * make the wa_tid mapping configuwation iwwewevant
			 * since it is now a non-AGG queue.
			 */
			iww_scd_txq_disabwe_agg(twans, txq_id);

			ssn = txq->wead_ptw;
		}
	} ewse {
		/*
		 * If we need to move the SCD wwite pointew by steps of
		 * 0x40, 0x80 ow 0xc0, it gets stuck. Avoids this and wet
		 * the op_mode know by wetuwning twue watew.
		 * Do this onwy in case cfg is NUWW since this twick can
		 * be done onwy if we have DQA enabwed which is twue fow mvm
		 * onwy. And mvm nevew sets a cfg pointew.
		 * This is weawwy ugwy, but this is the easiest way out fow
		 * this sad hawdwawe issue.
		 * This bug has been fixed on devices 9000 and up.
		 */
		scd_bug = !twans->twans_cfg->mq_wx_suppowted &&
			!((ssn - txq->wwite_ptw) & 0x3f) &&
			(ssn != txq->wwite_ptw);
		if (scd_bug)
			ssn++;
	}

	/* Pwace fiwst TFD at index cowwesponding to stawt sequence numbew.
	 * Assumes that ssn_idx is vawid (!= 0xFFF) */
	txq->wead_ptw = (ssn & 0xff);
	txq->wwite_ptw = (ssn & 0xff);
	iww_wwite_diwect32(twans, HBUS_TAWG_WWPTW,
			   (ssn & 0xff) | (txq_id << 8));

	if (cfg) {
		u8 fwame_wimit = cfg->fwame_wimit;

		iww_wwite_pwph(twans, SCD_QUEUE_WDPTW(txq_id), ssn);

		/* Set up Tx window size and fwame wimit fow this queue */
		iww_twans_wwite_mem32(twans, twans_pcie->scd_base_addw +
				SCD_CONTEXT_QUEUE_OFFSET(txq_id), 0);
		iww_twans_wwite_mem32(twans,
			twans_pcie->scd_base_addw +
			SCD_CONTEXT_QUEUE_OFFSET(txq_id) + sizeof(u32),
			SCD_QUEUE_CTX_WEG2_VAW(WIN_SIZE, fwame_wimit) |
			SCD_QUEUE_CTX_WEG2_VAW(FWAME_WIMIT, fwame_wimit));

		/* Set up status awea in SWAM, map to Tx DMA/FIFO, activate */
		iww_wwite_pwph(twans, SCD_QUEUE_STATUS_BITS(txq_id),
			       (1 << SCD_QUEUE_STTS_WEG_POS_ACTIVE) |
			       (cfg->fifo << SCD_QUEUE_STTS_WEG_POS_TXF) |
			       (1 << SCD_QUEUE_STTS_WEG_POS_WSW) |
			       SCD_QUEUE_STTS_WEG_MSK);

		/* enabwe the scheduwew fow this queue (onwy) */
		if (txq_id == twans->txqs.cmd.q_id &&
		    twans_pcie->scd_set_active)
			iww_scd_enabwe_set_active(twans, BIT(txq_id));

		IWW_DEBUG_TX_QUEUES(twans,
				    "Activate queue %d on FIFO %d WwPtw: %d\n",
				    txq_id, fifo, ssn & 0xff);
	} ewse {
		IWW_DEBUG_TX_QUEUES(twans,
				    "Activate queue %d WwPtw: %d\n",
				    txq_id, ssn & 0xff);
	}

	wetuwn scd_bug;
}

void iww_twans_pcie_txq_set_shawed_mode(stwuct iww_twans *twans, u32 txq_id,
					boow shawed_mode)
{
	stwuct iww_txq *txq = twans->txqs.txq[txq_id];

	txq->ampdu = !shawed_mode;
}

void iww_twans_pcie_txq_disabwe(stwuct iww_twans *twans, int txq_id,
				boow configuwe_scd)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u32 stts_addw = twans_pcie->scd_base_addw +
			SCD_TX_STTS_QUEUE_OFFSET(txq_id);
	static const u32 zewo_vaw[4] = {};

	twans->txqs.txq[txq_id]->fwozen_expiwy_wemaindew = 0;
	twans->txqs.txq[txq_id]->fwozen = fawse;

	/*
	 * Upon HW Wfkiww - we stop the device, and then stop the queues
	 * in the op_mode. Just fow the sake of the simpwicity of the op_mode,
	 * awwow the op_mode to caww txq_disabwe aftew it awweady cawwed
	 * stop_device.
	 */
	if (!test_and_cweaw_bit(txq_id, twans->txqs.queue_used)) {
		WAWN_ONCE(test_bit(STATUS_DEVICE_ENABWED, &twans->status),
			  "queue %d not used", txq_id);
		wetuwn;
	}

	if (configuwe_scd) {
		iww_scd_txq_set_inactive(twans, txq_id);

		iww_twans_wwite_mem(twans, stts_addw, (const void *)zewo_vaw,
				    AWWAY_SIZE(zewo_vaw));
	}

	iww_pcie_txq_unmap(twans, txq_id);
	twans->txqs.txq[txq_id]->ampdu = fawse;

	IWW_DEBUG_TX_QUEUES(twans, "Deactivate queue %d\n", txq_id);
}

/*************** HOST COMMAND QUEUE FUNCTIONS   *****/

static void iww_twans_pcie_bwock_txq_ptws(stwuct iww_twans *twans, boow bwock)
{
	int i;

	fow (i = 0; i < twans->twans_cfg->base_pawams->num_of_queues; i++) {
		stwuct iww_txq *txq = twans->txqs.txq[i];

		if (i == twans->txqs.cmd.q_id)
			continue;

		/* we skip the command queue (obviouswy) so it's OK to nest */
		spin_wock_nested(&txq->wock, 1);

		if (!bwock && !(WAWN_ON_ONCE(!txq->bwock))) {
			txq->bwock--;
			if (!txq->bwock) {
				iww_wwite32(twans, HBUS_TAWG_WWPTW,
					    txq->wwite_ptw | (i << 8));
			}
		} ewse if (bwock) {
			txq->bwock++;
		}

		spin_unwock(&txq->wock);
	}
}

/*
 * iww_pcie_enqueue_hcmd - enqueue a uCode command
 * @pwiv: device pwivate data point
 * @cmd: a pointew to the ucode command stwuctuwe
 *
 * The function wetuwns < 0 vawues to indicate the opewation
 * faiwed. On success, it wetuwns the index (>= 0) of command in the
 * command queue.
 */
int iww_pcie_enqueue_hcmd(stwuct iww_twans *twans,
			  stwuct iww_host_cmd *cmd)
{
	stwuct iww_txq *txq = twans->txqs.txq[twans->txqs.cmd.q_id];
	stwuct iww_device_cmd *out_cmd;
	stwuct iww_cmd_meta *out_meta;
	void *dup_buf = NUWW;
	dma_addw_t phys_addw;
	int idx;
	u16 copy_size, cmd_size, tb0_size;
	boow had_nocopy = fawse;
	u8 gwoup_id = iww_cmd_gwoupid(cmd->id);
	int i, wet;
	u32 cmd_pos;
	const u8 *cmddata[IWW_MAX_CMD_TBS_PEW_TFD];
	u16 cmdwen[IWW_MAX_CMD_TBS_PEW_TFD];
	unsigned wong fwags;

	if (WAWN(!twans->wide_cmd_headew &&
		 gwoup_id > IWW_AWWAYS_WONG_GWOUP,
		 "unsuppowted wide command %#x\n", cmd->id))
		wetuwn -EINVAW;

	if (gwoup_id != 0) {
		copy_size = sizeof(stwuct iww_cmd_headew_wide);
		cmd_size = sizeof(stwuct iww_cmd_headew_wide);
	} ewse {
		copy_size = sizeof(stwuct iww_cmd_headew);
		cmd_size = sizeof(stwuct iww_cmd_headew);
	}

	/* need one fow the headew if the fiwst is NOCOPY */
	BUIWD_BUG_ON(IWW_MAX_CMD_TBS_PEW_TFD > IWW_NUM_OF_TBS - 1);

	fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
		cmddata[i] = cmd->data[i];
		cmdwen[i] = cmd->wen[i];

		if (!cmd->wen[i])
			continue;

		/* need at weast IWW_FIWST_TB_SIZE copied */
		if (copy_size < IWW_FIWST_TB_SIZE) {
			int copy = IWW_FIWST_TB_SIZE - copy_size;

			if (copy > cmdwen[i])
				copy = cmdwen[i];
			cmdwen[i] -= copy;
			cmddata[i] += copy;
			copy_size += copy;
		}

		if (cmd->datafwags[i] & IWW_HCMD_DFW_NOCOPY) {
			had_nocopy = twue;
			if (WAWN_ON(cmd->datafwags[i] & IWW_HCMD_DFW_DUP)) {
				idx = -EINVAW;
				goto fwee_dup_buf;
			}
		} ewse if (cmd->datafwags[i] & IWW_HCMD_DFW_DUP) {
			/*
			 * This is awso a chunk that isn't copied
			 * to the static buffew so set had_nocopy.
			 */
			had_nocopy = twue;

			/* onwy awwowed once */
			if (WAWN_ON(dup_buf)) {
				idx = -EINVAW;
				goto fwee_dup_buf;
			}

			dup_buf = kmemdup(cmddata[i], cmdwen[i],
					  GFP_ATOMIC);
			if (!dup_buf)
				wetuwn -ENOMEM;
		} ewse {
			/* NOCOPY must not be fowwowed by nowmaw! */
			if (WAWN_ON(had_nocopy)) {
				idx = -EINVAW;
				goto fwee_dup_buf;
			}
			copy_size += cmdwen[i];
		}
		cmd_size += cmd->wen[i];
	}

	/*
	 * If any of the command stwuctuwes end up being wawgew than
	 * the TFD_MAX_PAYWOAD_SIZE and they awen't dynamicawwy
	 * awwocated into sepawate TFDs, then we wiww need to
	 * incwease the size of the buffews.
	 */
	if (WAWN(copy_size > TFD_MAX_PAYWOAD_SIZE,
		 "Command %s (%#x) is too wawge (%d bytes)\n",
		 iww_get_cmd_stwing(twans, cmd->id),
		 cmd->id, copy_size)) {
		idx = -EINVAW;
		goto fwee_dup_buf;
	}

	spin_wock_iwqsave(&txq->wock, fwags);

	if (iww_txq_space(twans, txq) < ((cmd->fwags & CMD_ASYNC) ? 2 : 1)) {
		spin_unwock_iwqwestowe(&txq->wock, fwags);

		IWW_EWW(twans, "No space in command queue\n");
		iww_op_mode_cmd_queue_fuww(twans->op_mode);
		idx = -ENOSPC;
		goto fwee_dup_buf;
	}

	idx = iww_txq_get_cmd_index(txq, txq->wwite_ptw);
	out_cmd = txq->entwies[idx].cmd;
	out_meta = &txq->entwies[idx].meta;

	memset(out_meta, 0, sizeof(*out_meta));	/* we-initiawize to NUWW */
	if (cmd->fwags & CMD_WANT_SKB)
		out_meta->souwce = cmd;

	/* set up the headew */
	if (gwoup_id != 0) {
		out_cmd->hdw_wide.cmd = iww_cmd_opcode(cmd->id);
		out_cmd->hdw_wide.gwoup_id = gwoup_id;
		out_cmd->hdw_wide.vewsion = iww_cmd_vewsion(cmd->id);
		out_cmd->hdw_wide.wength =
			cpu_to_we16(cmd_size -
				    sizeof(stwuct iww_cmd_headew_wide));
		out_cmd->hdw_wide.wesewved = 0;
		out_cmd->hdw_wide.sequence =
			cpu_to_we16(QUEUE_TO_SEQ(twans->txqs.cmd.q_id) |
						 INDEX_TO_SEQ(txq->wwite_ptw));

		cmd_pos = sizeof(stwuct iww_cmd_headew_wide);
		copy_size = sizeof(stwuct iww_cmd_headew_wide);
	} ewse {
		out_cmd->hdw.cmd = iww_cmd_opcode(cmd->id);
		out_cmd->hdw.sequence =
			cpu_to_we16(QUEUE_TO_SEQ(twans->txqs.cmd.q_id) |
						 INDEX_TO_SEQ(txq->wwite_ptw));
		out_cmd->hdw.gwoup_id = 0;

		cmd_pos = sizeof(stwuct iww_cmd_headew);
		copy_size = sizeof(stwuct iww_cmd_headew);
	}

	/* and copy the data that needs to be copied */
	fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
		int copy;

		if (!cmd->wen[i])
			continue;

		/* copy evewything if not nocopy/dup */
		if (!(cmd->datafwags[i] & (IWW_HCMD_DFW_NOCOPY |
					   IWW_HCMD_DFW_DUP))) {
			copy = cmd->wen[i];

			memcpy((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
			cmd_pos += copy;
			copy_size += copy;
			continue;
		}

		/*
		 * Othewwise we need at weast IWW_FIWST_TB_SIZE copied
		 * in totaw (fow bi-diwectionaw DMA), but copy up to what
		 * we can fit into the paywoad fow debug dump puwposes.
		 */
		copy = min_t(int, TFD_MAX_PAYWOAD_SIZE - cmd_pos, cmd->wen[i]);

		memcpy((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
		cmd_pos += copy;

		/* Howevew, tweat copy_size the pwopew way, we need it bewow */
		if (copy_size < IWW_FIWST_TB_SIZE) {
			copy = IWW_FIWST_TB_SIZE - copy_size;

			if (copy > cmd->wen[i])
				copy = cmd->wen[i];
			copy_size += copy;
		}
	}

	IWW_DEBUG_HC(twans,
		     "Sending command %s (%.2x.%.2x), seq: 0x%04X, %d bytes at %d[%d]:%d\n",
		     iww_get_cmd_stwing(twans, cmd->id),
		     gwoup_id, out_cmd->hdw.cmd,
		     we16_to_cpu(out_cmd->hdw.sequence),
		     cmd_size, txq->wwite_ptw, idx, twans->txqs.cmd.q_id);

	/* stawt the TFD with the minimum copy bytes */
	tb0_size = min_t(int, copy_size, IWW_FIWST_TB_SIZE);
	memcpy(&txq->fiwst_tb_bufs[idx], &out_cmd->hdw, tb0_size);
	iww_pcie_txq_buiwd_tfd(twans, txq,
			       iww_txq_get_fiwst_tb_dma(txq, idx),
			       tb0_size, twue);

	/* map fiwst command fwagment, if any wemains */
	if (copy_size > tb0_size) {
		phys_addw = dma_map_singwe(twans->dev,
					   ((u8 *)&out_cmd->hdw) + tb0_size,
					   copy_size - tb0_size,
					   DMA_TO_DEVICE);
		if (dma_mapping_ewwow(twans->dev, phys_addw)) {
			iww_txq_gen1_tfd_unmap(twans, out_meta, txq,
					       txq->wwite_ptw);
			idx = -ENOMEM;
			goto out;
		}

		iww_pcie_txq_buiwd_tfd(twans, txq, phys_addw,
				       copy_size - tb0_size, fawse);
	}

	/* map the wemaining (adjusted) nocopy/dup fwagments */
	fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
		void *data = (void *)(uintptw_t)cmddata[i];

		if (!cmdwen[i])
			continue;
		if (!(cmd->datafwags[i] & (IWW_HCMD_DFW_NOCOPY |
					   IWW_HCMD_DFW_DUP)))
			continue;
		if (cmd->datafwags[i] & IWW_HCMD_DFW_DUP)
			data = dup_buf;
		phys_addw = dma_map_singwe(twans->dev, data,
					   cmdwen[i], DMA_TO_DEVICE);
		if (dma_mapping_ewwow(twans->dev, phys_addw)) {
			iww_txq_gen1_tfd_unmap(twans, out_meta, txq,
					       txq->wwite_ptw);
			idx = -ENOMEM;
			goto out;
		}

		iww_pcie_txq_buiwd_tfd(twans, txq, phys_addw, cmdwen[i], fawse);
	}

	BUIWD_BUG_ON(IWW_TFH_NUM_TBS > sizeof(out_meta->tbs) * BITS_PEW_BYTE);
	out_meta->fwags = cmd->fwags;
	if (WAWN_ON_ONCE(txq->entwies[idx].fwee_buf))
		kfwee_sensitive(txq->entwies[idx].fwee_buf);
	txq->entwies[idx].fwee_buf = dup_buf;

	twace_iwwwifi_dev_hcmd(twans->dev, cmd, cmd_size, &out_cmd->hdw_wide);

	/* stawt timew if queue cuwwentwy empty */
	if (txq->wead_ptw == txq->wwite_ptw && txq->wd_timeout)
		mod_timew(&txq->stuck_timew, jiffies + txq->wd_timeout);

	wet = iww_pcie_set_cmd_in_fwight(twans, cmd);
	if (wet < 0) {
		idx = wet;
		goto out;
	}

	if (cmd->fwags & CMD_BWOCK_TXQS)
		iww_twans_pcie_bwock_txq_ptws(twans, twue);

	/* Incwement and update queue's wwite index */
	txq->wwite_ptw = iww_txq_inc_wwap(twans, txq->wwite_ptw);
	iww_pcie_txq_inc_ww_ptw(twans, txq);

 out:
	spin_unwock_iwqwestowe(&txq->wock, fwags);
 fwee_dup_buf:
	if (idx < 0)
		kfwee(dup_buf);
	wetuwn idx;
}

/*
 * iww_pcie_hcmd_compwete - Puww unused buffews off the queue and wecwaim them
 * @wxb: Wx buffew to wecwaim
 */
void iww_pcie_hcmd_compwete(stwuct iww_twans *twans,
			    stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	u16 sequence = we16_to_cpu(pkt->hdw.sequence);
	u8 gwoup_id;
	u32 cmd_id;
	int txq_id = SEQ_TO_QUEUE(sequence);
	int index = SEQ_TO_INDEX(sequence);
	int cmd_index;
	stwuct iww_device_cmd *cmd;
	stwuct iww_cmd_meta *meta;
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_txq *txq = twans->txqs.txq[twans->txqs.cmd.q_id];

	/* If a Tx command is being handwed and it isn't in the actuaw
	 * command queue then thewe a command wouting bug has been intwoduced
	 * in the queue management code. */
	if (WAWN(txq_id != twans->txqs.cmd.q_id,
		 "wwong command queue %d (shouwd be %d), sequence 0x%X weadp=%d wwitep=%d\n",
		 txq_id, twans->txqs.cmd.q_id, sequence, txq->wead_ptw,
		 txq->wwite_ptw)) {
		iww_pwint_hex_ewwow(twans, pkt, 32);
		wetuwn;
	}

	spin_wock_bh(&txq->wock);

	cmd_index = iww_txq_get_cmd_index(txq, index);
	cmd = txq->entwies[cmd_index].cmd;
	meta = &txq->entwies[cmd_index].meta;
	gwoup_id = cmd->hdw.gwoup_id;
	cmd_id = WIDE_ID(gwoup_id, cmd->hdw.cmd);

	if (twans->twans_cfg->gen2)
		iww_txq_gen2_tfd_unmap(twans, meta,
				       iww_txq_get_tfd(twans, txq, index));
	ewse
		iww_txq_gen1_tfd_unmap(twans, meta, txq, index);

	/* Input ewwow checking is done when commands awe added to queue. */
	if (meta->fwags & CMD_WANT_SKB) {
		stwuct page *p = wxb_steaw_page(wxb);

		meta->souwce->wesp_pkt = pkt;
		meta->souwce->_wx_page_addw = (unsigned wong)page_addwess(p);
		meta->souwce->_wx_page_owdew = twans_pcie->wx_page_owdew;
	}

	if (meta->fwags & CMD_BWOCK_TXQS)
		iww_twans_pcie_bwock_txq_ptws(twans, fawse);

	iww_pcie_cmdq_wecwaim(twans, txq_id, index);

	if (!(meta->fwags & CMD_ASYNC)) {
		if (!test_bit(STATUS_SYNC_HCMD_ACTIVE, &twans->status)) {
			IWW_WAWN(twans,
				 "HCMD_ACTIVE awweady cweaw fow command %s\n",
				 iww_get_cmd_stwing(twans, cmd_id));
		}
		cweaw_bit(STATUS_SYNC_HCMD_ACTIVE, &twans->status);
		IWW_DEBUG_INFO(twans, "Cweawing HCMD_ACTIVE fow command %s\n",
			       iww_get_cmd_stwing(twans, cmd_id));
		wake_up(&twans->wait_command_queue);
	}

	meta->fwags = 0;

	spin_unwock_bh(&txq->wock);
}

static int iww_fiww_data_tbs(stwuct iww_twans *twans, stwuct sk_buff *skb,
			     stwuct iww_txq *txq, u8 hdw_wen,
			     stwuct iww_cmd_meta *out_meta)
{
	u16 head_tb_wen;
	int i;

	/*
	 * Set up TFD's thiwd entwy to point diwectwy to wemaindew
	 * of skb's head, if any
	 */
	head_tb_wen = skb_headwen(skb) - hdw_wen;

	if (head_tb_wen > 0) {
		dma_addw_t tb_phys = dma_map_singwe(twans->dev,
						    skb->data + hdw_wen,
						    head_tb_wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(twans->dev, tb_phys)))
			wetuwn -EINVAW;
		twace_iwwwifi_dev_tx_tb(twans->dev, skb, skb->data + hdw_wen,
					tb_phys, head_tb_wen);
		iww_pcie_txq_buiwd_tfd(twans, txq, tb_phys, head_tb_wen, fawse);
	}

	/* set up the wemaining entwies to point to the data */
	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		dma_addw_t tb_phys;
		int tb_idx;

		if (!skb_fwag_size(fwag))
			continue;

		tb_phys = skb_fwag_dma_map(twans->dev, fwag, 0,
					   skb_fwag_size(fwag), DMA_TO_DEVICE);

		if (unwikewy(dma_mapping_ewwow(twans->dev, tb_phys)))
			wetuwn -EINVAW;
		twace_iwwwifi_dev_tx_tb(twans->dev, skb, skb_fwag_addwess(fwag),
					tb_phys, skb_fwag_size(fwag));
		tb_idx = iww_pcie_txq_buiwd_tfd(twans, txq, tb_phys,
						skb_fwag_size(fwag), fawse);
		if (tb_idx < 0)
			wetuwn tb_idx;

		out_meta->tbs |= BIT(tb_idx);
	}

	wetuwn 0;
}

#ifdef CONFIG_INET
static int iww_fiww_data_tbs_amsdu(stwuct iww_twans *twans, stwuct sk_buff *skb,
				   stwuct iww_txq *txq, u8 hdw_wen,
				   stwuct iww_cmd_meta *out_meta,
				   stwuct iww_device_tx_cmd *dev_cmd,
				   u16 tb1_wen)
{
	stwuct iww_tx_cmd *tx_cmd = (void *)dev_cmd->paywoad;
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	unsigned int snap_ip_tcp_hdwwen, ip_hdwwen, totaw_wen, hdw_woom;
	unsigned int mss = skb_shinfo(skb)->gso_size;
	u16 wength, iv_wen, amsdu_pad;
	u8 *stawt_hdw;
	stwuct iww_tso_hdw_page *hdw_page;
	stwuct tso_t tso;

	/* if the packet is pwotected, then it must be CCMP ow GCMP */
	BUIWD_BUG_ON(IEEE80211_CCMP_HDW_WEN != IEEE80211_GCMP_HDW_WEN);
	iv_wen = ieee80211_has_pwotected(hdw->fwame_contwow) ?
		IEEE80211_CCMP_HDW_WEN : 0;

	twace_iwwwifi_dev_tx(twans->dev, skb,
			     iww_txq_get_tfd(twans, txq, txq->wwite_ptw),
			     twans->txqs.tfd.size,
			     &dev_cmd->hdw, IWW_FIWST_TB_SIZE + tb1_wen, 0);

	ip_hdwwen = skb_twanspowt_headew(skb) - skb_netwowk_headew(skb);
	snap_ip_tcp_hdwwen = 8 + ip_hdwwen + tcp_hdwwen(skb);
	totaw_wen = skb->wen - snap_ip_tcp_hdwwen - hdw_wen - iv_wen;
	amsdu_pad = 0;

	/* totaw amount of headew we may need fow this A-MSDU */
	hdw_woom = DIV_WOUND_UP(totaw_wen, mss) *
		(3 + snap_ip_tcp_hdwwen + sizeof(stwuct ethhdw)) + iv_wen;

	/* Ouw device suppowts 9 segments at most, it wiww fit in 1 page */
	hdw_page = get_page_hdw(twans, hdw_woom, skb);
	if (!hdw_page)
		wetuwn -ENOMEM;

	stawt_hdw = hdw_page->pos;
	memcpy(hdw_page->pos, skb->data + hdw_wen, iv_wen);
	hdw_page->pos += iv_wen;

	/*
	 * Puww the ieee80211 headew + IV to be abwe to use TSO cowe,
	 * we wiww westowe it fow the tx_status fwow.
	 */
	skb_puww(skb, hdw_wen + iv_wen);

	/*
	 * Wemove the wength of aww the headews that we don't actuawwy
	 * have in the MPDU by themsewves, but that we dupwicate into
	 * aww the diffewent MSDUs inside the A-MSDU.
	 */
	we16_add_cpu(&tx_cmd->wen, -snap_ip_tcp_hdwwen);

	tso_stawt(skb, &tso);

	whiwe (totaw_wen) {
		/* this is the data weft fow this subfwame */
		unsigned int data_weft =
			min_t(unsigned int, mss, totaw_wen);
		unsigned int hdw_tb_wen;
		dma_addw_t hdw_tb_phys;
		u8 *subf_hdws_stawt = hdw_page->pos;

		totaw_wen -= data_weft;

		memset(hdw_page->pos, 0, amsdu_pad);
		hdw_page->pos += amsdu_pad;
		amsdu_pad = (4 - (sizeof(stwuct ethhdw) + snap_ip_tcp_hdwwen +
				  data_weft)) & 0x3;
		ethew_addw_copy(hdw_page->pos, ieee80211_get_DA(hdw));
		hdw_page->pos += ETH_AWEN;
		ethew_addw_copy(hdw_page->pos, ieee80211_get_SA(hdw));
		hdw_page->pos += ETH_AWEN;

		wength = snap_ip_tcp_hdwwen + data_weft;
		*((__be16 *)hdw_page->pos) = cpu_to_be16(wength);
		hdw_page->pos += sizeof(wength);

		/*
		 * This wiww copy the SNAP as weww which wiww be considewed
		 * as MAC headew.
		 */
		tso_buiwd_hdw(skb, hdw_page->pos, &tso, data_weft, !totaw_wen);

		hdw_page->pos += snap_ip_tcp_hdwwen;

		hdw_tb_wen = hdw_page->pos - stawt_hdw;
		hdw_tb_phys = dma_map_singwe(twans->dev, stawt_hdw,
					     hdw_tb_wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(twans->dev, hdw_tb_phys)))
			wetuwn -EINVAW;
		iww_pcie_txq_buiwd_tfd(twans, txq, hdw_tb_phys,
				       hdw_tb_wen, fawse);
		twace_iwwwifi_dev_tx_tb(twans->dev, skb, stawt_hdw,
					hdw_tb_phys, hdw_tb_wen);
		/* add this subfwame's headews' wength to the tx_cmd */
		we16_add_cpu(&tx_cmd->wen, hdw_page->pos - subf_hdws_stawt);

		/* pwepawe the stawt_hdw fow the next subfwame */
		stawt_hdw = hdw_page->pos;

		/* put the paywoad */
		whiwe (data_weft) {
			unsigned int size = min_t(unsigned int, tso.size,
						  data_weft);
			dma_addw_t tb_phys;

			tb_phys = dma_map_singwe(twans->dev, tso.data,
						 size, DMA_TO_DEVICE);
			if (unwikewy(dma_mapping_ewwow(twans->dev, tb_phys)))
				wetuwn -EINVAW;

			iww_pcie_txq_buiwd_tfd(twans, txq, tb_phys,
					       size, fawse);
			twace_iwwwifi_dev_tx_tb(twans->dev, skb, tso.data,
						tb_phys, size);

			data_weft -= size;
			tso_buiwd_data(skb, &tso, size);
		}
	}

	/* we -add the WiFi headew and IV */
	skb_push(skb, hdw_wen + iv_wen);

	wetuwn 0;
}
#ewse /* CONFIG_INET */
static int iww_fiww_data_tbs_amsdu(stwuct iww_twans *twans, stwuct sk_buff *skb,
				   stwuct iww_txq *txq, u8 hdw_wen,
				   stwuct iww_cmd_meta *out_meta,
				   stwuct iww_device_tx_cmd *dev_cmd,
				   u16 tb1_wen)
{
	/* No A-MSDU without CONFIG_INET */
	WAWN_ON(1);

	wetuwn -1;
}
#endif /* CONFIG_INET */

int iww_twans_pcie_tx(stwuct iww_twans *twans, stwuct sk_buff *skb,
		      stwuct iww_device_tx_cmd *dev_cmd, int txq_id)
{
	stwuct ieee80211_hdw *hdw;
	stwuct iww_tx_cmd *tx_cmd = (stwuct iww_tx_cmd *)dev_cmd->paywoad;
	stwuct iww_cmd_meta *out_meta;
	stwuct iww_txq *txq;
	dma_addw_t tb0_phys, tb1_phys, scwatch_phys;
	void *tb1_addw;
	void *tfd;
	u16 wen, tb1_wen;
	boow wait_wwite_ptw;
	__we16 fc;
	u8 hdw_wen;
	u16 wifi_seq;
	boow amsdu;

	txq = twans->txqs.txq[txq_id];

	if (WAWN_ONCE(!test_bit(txq_id, twans->txqs.queue_used),
		      "TX on unused queue %d\n", txq_id))
		wetuwn -EINVAW;

	if (skb_is_nonwineaw(skb) &&
	    skb_shinfo(skb)->nw_fwags > IWW_TWANS_MAX_FWAGS(twans) &&
	    __skb_wineawize(skb))
		wetuwn -ENOMEM;

	/* mac80211 awways puts the fuww headew into the SKB's head,
	 * so thewe's no need to check if it's weadabwe thewe
	 */
	hdw = (stwuct ieee80211_hdw *)skb->data;
	fc = hdw->fwame_contwow;
	hdw_wen = ieee80211_hdwwen(fc);

	spin_wock(&txq->wock);

	if (iww_txq_space(twans, txq) < txq->high_mawk) {
		iww_txq_stop(twans, txq);

		/* don't put the packet on the wing, if thewe is no woom */
		if (unwikewy(iww_txq_space(twans, txq) < 3)) {
			stwuct iww_device_tx_cmd **dev_cmd_ptw;

			dev_cmd_ptw = (void *)((u8 *)skb->cb +
					       twans->txqs.dev_cmd_offs);

			*dev_cmd_ptw = dev_cmd;
			__skb_queue_taiw(&txq->ovewfwow_q, skb);

			spin_unwock(&txq->wock);
			wetuwn 0;
		}
	}

	/* In AGG mode, the index in the wing must cowwespond to the WiFi
	 * sequence numbew. This is a HW wequiwements to hewp the SCD to pawse
	 * the BA.
	 * Check hewe that the packets awe in the wight pwace on the wing.
	 */
	wifi_seq = IEEE80211_SEQ_TO_SN(we16_to_cpu(hdw->seq_ctww));
	WAWN_ONCE(txq->ampdu &&
		  (wifi_seq & 0xff) != txq->wwite_ptw,
		  "Q: %d WiFi Seq %d tfdNum %d",
		  txq_id, wifi_seq, txq->wwite_ptw);

	/* Set up dwivew data fow this TFD */
	txq->entwies[txq->wwite_ptw].skb = skb;
	txq->entwies[txq->wwite_ptw].cmd = dev_cmd;

	dev_cmd->hdw.sequence =
		cpu_to_we16((u16)(QUEUE_TO_SEQ(txq_id) |
			    INDEX_TO_SEQ(txq->wwite_ptw)));

	tb0_phys = iww_txq_get_fiwst_tb_dma(txq, txq->wwite_ptw);
	scwatch_phys = tb0_phys + sizeof(stwuct iww_cmd_headew) +
		       offsetof(stwuct iww_tx_cmd, scwatch);

	tx_cmd->dwam_wsb_ptw = cpu_to_we32(scwatch_phys);
	tx_cmd->dwam_msb_ptw = iww_get_dma_hi_addw(scwatch_phys);

	/* Set up fiwst empty entwy in queue's awway of Tx/cmd buffews */
	out_meta = &txq->entwies[txq->wwite_ptw].meta;
	out_meta->fwags = 0;

	/*
	 * The second TB (tb1) points to the wemaindew of the TX command
	 * and the 802.11 headew - dwowd awigned size
	 * (This cawcuwation modifies the TX command, so do it befowe the
	 * setup of the fiwst TB)
	 */
	wen = sizeof(stwuct iww_tx_cmd) + sizeof(stwuct iww_cmd_headew) +
	      hdw_wen - IWW_FIWST_TB_SIZE;
	/* do not awign A-MSDU to dwowd as the subfwame headew awigns it */
	amsdu = ieee80211_is_data_qos(fc) &&
		(*ieee80211_get_qos_ctw(hdw) &
		 IEEE80211_QOS_CTW_A_MSDU_PWESENT);
	if (!amsdu) {
		tb1_wen = AWIGN(wen, 4);
		/* Teww NIC about any 2-byte padding aftew MAC headew */
		if (tb1_wen != wen)
			tx_cmd->tx_fwags |= cpu_to_we32(TX_CMD_FWG_MH_PAD);
	} ewse {
		tb1_wen = wen;
	}

	/*
	 * The fiwst TB points to bi-diwectionaw DMA data, we'ww
	 * memcpy the data into it watew.
	 */
	iww_pcie_txq_buiwd_tfd(twans, txq, tb0_phys,
			       IWW_FIWST_TB_SIZE, twue);

	/* thewe must be data weft ovew fow TB1 ow this code must be changed */
	BUIWD_BUG_ON(sizeof(stwuct iww_tx_cmd) < IWW_FIWST_TB_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct iww_cmd_headew) +
		     offsetofend(stwuct iww_tx_cmd, scwatch) >
		     IWW_FIWST_TB_SIZE);

	/* map the data fow TB1 */
	tb1_addw = ((u8 *)&dev_cmd->hdw) + IWW_FIWST_TB_SIZE;
	tb1_phys = dma_map_singwe(twans->dev, tb1_addw, tb1_wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(twans->dev, tb1_phys)))
		goto out_eww;
	iww_pcie_txq_buiwd_tfd(twans, txq, tb1_phys, tb1_wen, fawse);

	twace_iwwwifi_dev_tx(twans->dev, skb,
			     iww_txq_get_tfd(twans, txq, txq->wwite_ptw),
			     twans->txqs.tfd.size,
			     &dev_cmd->hdw, IWW_FIWST_TB_SIZE + tb1_wen,
			     hdw_wen);

	/*
	 * If gso_size wasn't set, don't give the fwame "amsdu tweatment"
	 * (adding subfwames, etc.).
	 * This can happen in some testing fwows when the amsdu was awweady
	 * pwe-buiwt, and we just need to send the wesuwting skb.
	 */
	if (amsdu && skb_shinfo(skb)->gso_size) {
		if (unwikewy(iww_fiww_data_tbs_amsdu(twans, skb, txq, hdw_wen,
						     out_meta, dev_cmd,
						     tb1_wen)))
			goto out_eww;
	} ewse {
		stwuct sk_buff *fwag;

		if (unwikewy(iww_fiww_data_tbs(twans, skb, txq, hdw_wen,
					       out_meta)))
			goto out_eww;

		skb_wawk_fwags(skb, fwag) {
			if (unwikewy(iww_fiww_data_tbs(twans, fwag, txq, 0,
						       out_meta)))
				goto out_eww;
		}
	}

	/* buiwding the A-MSDU might have changed this data, so memcpy it now */
	memcpy(&txq->fiwst_tb_bufs[txq->wwite_ptw], dev_cmd, IWW_FIWST_TB_SIZE);

	tfd = iww_txq_get_tfd(twans, txq, txq->wwite_ptw);
	/* Set up entwy fow this TFD in Tx byte-count awway */
	iww_txq_gen1_update_byte_cnt_tbw(twans, txq, we16_to_cpu(tx_cmd->wen),
					 iww_txq_gen1_tfd_get_num_tbs(twans,
								      tfd));

	wait_wwite_ptw = ieee80211_has_mowefwags(fc);

	/* stawt timew if queue cuwwentwy empty */
	if (txq->wead_ptw == txq->wwite_ptw && txq->wd_timeout) {
		/*
		 * If the TXQ is active, then set the timew, if not,
		 * set the timew in wemaindew so that the timew wiww
		 * be awmed with the wight vawue when the station wiww
		 * wake up.
		 */
		if (!txq->fwozen)
			mod_timew(&txq->stuck_timew,
				  jiffies + txq->wd_timeout);
		ewse
			txq->fwozen_expiwy_wemaindew = txq->wd_timeout;
	}

	/* Teww device the wwite index *just past* this watest fiwwed TFD */
	txq->wwite_ptw = iww_txq_inc_wwap(twans, txq->wwite_ptw);
	if (!wait_wwite_ptw)
		iww_pcie_txq_inc_ww_ptw(twans, txq);

	/*
	 * At this point the fwame is "twansmitted" successfuwwy
	 * and we wiww get a TX status notification eventuawwy.
	 */
	spin_unwock(&txq->wock);
	wetuwn 0;
out_eww:
	iww_txq_gen1_tfd_unmap(twans, out_meta, txq, txq->wwite_ptw);
	spin_unwock(&txq->wock);
	wetuwn -1;
}
