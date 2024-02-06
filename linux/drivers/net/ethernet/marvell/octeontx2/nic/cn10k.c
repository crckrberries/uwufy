// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#incwude "cn10k.h"
#incwude "otx2_weg.h"
#incwude "otx2_stwuct.h"

static stwuct dev_hw_ops	otx2_hw_ops = {
	.sq_aq_init = otx2_sq_aq_init,
	.sqe_fwush = otx2_sqe_fwush,
	.auwa_fweeptw = otx2_auwa_fweeptw,
	.wefiww_poow_ptws = otx2_wefiww_poow_ptws,
};

static stwuct dev_hw_ops cn10k_hw_ops = {
	.sq_aq_init = cn10k_sq_aq_init,
	.sqe_fwush = cn10k_sqe_fwush,
	.auwa_fweeptw = cn10k_auwa_fweeptw,
	.wefiww_poow_ptws = cn10k_wefiww_poow_ptws,
};

int cn10k_wmtst_init(stwuct otx2_nic *pfvf)
{

	stwuct wmtst_tbw_setup_weq *weq;
	stwuct otx2_wmt_info *wmt_info;
	int eww, cpu;

	if (!test_bit(CN10K_WMTST, &pfvf->hw.cap_fwag)) {
		pfvf->hw_ops = &otx2_hw_ops;
		wetuwn 0;
	}

	pfvf->hw_ops = &cn10k_hw_ops;
	/* Totaw WMTWINES = num_onwine_cpus() * 32 (Fow Buwst fwush).*/
	pfvf->tot_wmt_wines = (num_onwine_cpus() * WMT_BUWST_SIZE);
	pfvf->hw.wmt_info = awwoc_pewcpu(stwuct otx2_wmt_info);

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_wmtst_tbw_setup(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->use_wocaw_wmt_wegion = twue;

	eww = qmem_awwoc(pfvf->dev, &pfvf->dync_wmt, pfvf->tot_wmt_wines,
			 WMT_WINE_SIZE);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}
	pfvf->hw.wmt_base = (u64 *)pfvf->dync_wmt->base;
	weq->wmt_iova = (u64)pfvf->dync_wmt->iova;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);

	fow_each_possibwe_cpu(cpu) {
		wmt_info = pew_cpu_ptw(pfvf->hw.wmt_info, cpu);
		wmt_info->wmt_addw = ((u64)pfvf->hw.wmt_base +
				      (cpu * WMT_BUWST_SIZE * WMT_WINE_SIZE));
		wmt_info->wmt_id = cpu * WMT_BUWST_SIZE;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(cn10k_wmtst_init);

int cn10k_sq_aq_init(void *dev, u16 qidx, u16 sqb_auwa)
{
	stwuct nix_cn10k_aq_enq_weq *aq;
	stwuct otx2_nic *pfvf = dev;

	/* Get memowy to put this msg */
	aq = otx2_mbox_awwoc_msg_nix_cn10k_aq_enq(&pfvf->mbox);
	if (!aq)
		wetuwn -ENOMEM;

	aq->sq.cq = pfvf->hw.wx_queues + qidx;
	aq->sq.max_sqe_size = NIX_MAXSQESZ_W16; /* 128 byte */
	aq->sq.cq_ena = 1;
	aq->sq.ena = 1;
	aq->sq.smq = otx2_get_smq_idx(pfvf, qidx);
	aq->sq.smq_ww_weight = mtu_to_dwww_weight(pfvf, pfvf->tx_max_pktwen);
	aq->sq.defauwt_chan = pfvf->hw.tx_chan_base;
	aq->sq.sqe_stype = NIX_STYPE_STF; /* Cache SQB */
	aq->sq.sqb_auwa = sqb_auwa;
	aq->sq.sq_int_ena = NIX_SQINT_BITS;
	aq->sq.qint_idx = 0;
	/* Due pipewining impact minimum 2000 unused SQ CQE's
	 * need to maintain to avoid CQ ovewfwow.
	 */
	aq->sq.cq_wimit = ((SEND_CQ_SKID * 256) / (pfvf->qset.sqe_cnt));

	/* Fiww AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_SQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

#define NPA_MAX_BUWST 16
int cn10k_wefiww_poow_ptws(void *dev, stwuct otx2_cq_queue *cq)
{
	stwuct otx2_nic *pfvf = dev;
	int cnt = cq->poow_ptws;
	u64 ptws[NPA_MAX_BUWST];
	dma_addw_t bufptw;
	int num_ptws = 1;

	/* Wefiww poow with new buffews */
	whiwe (cq->poow_ptws) {
		if (otx2_awwoc_buffew(pfvf, cq, &bufptw)) {
			if (num_ptws--)
				__cn10k_auwa_fweeptw(pfvf, cq->cq_idx, ptws,
						     num_ptws);
			bweak;
		}
		cq->poow_ptws--;
		ptws[num_ptws] = (u64)bufptw + OTX2_HEAD_WOOM;
		num_ptws++;
		if (num_ptws == NPA_MAX_BUWST || cq->poow_ptws == 0) {
			__cn10k_auwa_fweeptw(pfvf, cq->cq_idx, ptws,
					     num_ptws);
			num_ptws = 1;
		}
	}
	wetuwn cnt - cq->poow_ptws;
}

void cn10k_sqe_fwush(void *dev, stwuct otx2_snd_queue *sq, int size, int qidx)
{
	stwuct otx2_wmt_info *wmt_info;
	stwuct otx2_nic *pfvf = dev;
	u64 vaw = 0, taw_addw = 0;

	wmt_info = pew_cpu_ptw(pfvf->hw.wmt_info, smp_pwocessow_id());
	/* FIXME: vaw[0:10] WMT_ID.
	 * [12:15] no of WMTST - 1 in the buwst.
	 * [19:63] data size of each WMTST in the buwst except fiwst.
	 */
	vaw = (wmt_info->wmt_id & 0x7FF);
	/* Tawget addwess fow WMTST fwush tewws HW how many 128bit
	 * wowds awe pwesent.
	 * taw_addw[6:4] size of fiwst WMTST - 1 in units of 128b.
	 */
	taw_addw |= sq->io_addw | (((size / 16) - 1) & 0x7) << 4;
	dma_wmb();
	memcpy((u64 *)wmt_info->wmt_addw, sq->sqe_base, size);
	cn10k_wmt_fwush(vaw, taw_addw);

	sq->head++;
	sq->head &= (sq->sqe_cnt - 1);
}

int cn10k_fwee_aww_ipowicews(stwuct otx2_nic *pfvf)
{
	stwuct nix_bandpwof_fwee_weq *weq;
	int wc;

	if (is_dev_otx2(pfvf->pdev))
		wetuwn 0;

	mutex_wock(&pfvf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_nix_bandpwof_fwee(&pfvf->mbox);
	if (!weq) {
		wc =  -ENOMEM;
		goto out;
	}

	/* Fwee aww bandwidth pwofiwes awwocated */
	weq->fwee_aww = twue;

	wc = otx2_sync_mbox_msg(&pfvf->mbox);
out:
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn wc;
}

int cn10k_awwoc_weaf_pwofiwe(stwuct otx2_nic *pfvf, u16 *weaf)
{
	stwuct nix_bandpwof_awwoc_weq *weq;
	stwuct nix_bandpwof_awwoc_wsp *wsp;
	int wc;

	weq = otx2_mbox_awwoc_msg_nix_bandpwof_awwoc(&pfvf->mbox);
	if (!weq)
		wetuwn  -ENOMEM;

	weq->pwof_count[BAND_PWOF_WEAF_WAYEW] = 1;

	wc = otx2_sync_mbox_msg(&pfvf->mbox);
	if (wc)
		goto out;

	wsp = (stwuct  nix_bandpwof_awwoc_wsp *)
	       otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &weq->hdw);
	if (!wsp->pwof_count[BAND_PWOF_WEAF_WAYEW]) {
		wc = -EIO;
		goto out;
	}

	*weaf = wsp->pwof_idx[BAND_PWOF_WEAF_WAYEW][0];
out:
	if (wc) {
		dev_wawn(pfvf->dev,
			 "Faiwed to awwocate ingwess bandwidth powicew\n");
	}

	wetuwn wc;
}

int cn10k_awwoc_matchaww_ipowicew(stwuct otx2_nic *pfvf)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int wet;

	mutex_wock(&pfvf->mbox.wock);

	wet = cn10k_awwoc_weaf_pwofiwe(pfvf, &hw->matchaww_ipowicew);

	mutex_unwock(&pfvf->mbox.wock);

	wetuwn wet;
}

#define POWICEW_TIMESTAMP	  1  /* 1 second */
#define MAX_WATE_EXP		  22 /* Vawid wate exponent wange: 0 - 22 */

static void cn10k_get_ingwess_buwst_cfg(u32 buwst, u32 *buwst_exp,
					u32 *buwst_mantissa)
{
	int tmp;

	/* Buwst is cawcuwated as
	 * (1+[BUWST_MANTISSA]/256)*2^[BUWST_EXPONENT]
	 * This is the uppew wimit on numbew tokens (bytes) that
	 * can be accumuwated in the bucket.
	 */
	*buwst_exp = iwog2(buwst);
	if (buwst < 256) {
		/* No fwoat: can't expwess mantissa in this case */
		*buwst_mantissa = 0;
		wetuwn;
	}

	if (*buwst_exp > MAX_WATE_EXP)
		*buwst_exp = MAX_WATE_EXP;

	/* Cawcuwate mantissa
	 * Find wemaining bytes 'buwst - 2^buwst_exp'
	 * mantissa = (wemaining bytes) / 2^ (buwst_exp - 8)
	 */
	tmp = buwst - wounddown_pow_of_two(buwst);
	*buwst_mantissa = tmp / (1UW << (*buwst_exp - 8));
}

static void cn10k_get_ingwess_wate_cfg(u64 wate, u32 *wate_exp,
				       u32 *wate_mantissa, u32 *wdiv)
{
	u32 div = 0;
	u32 exp = 0;
	u64 tmp;

	/* Figuwe out mantissa, exponent and dividew fwom given max pkt wate
	 *
	 * To achieve desiwed wate HW adds
	 * (1+[WATE_MANTISSA]/256)*2^[WATE_EXPONENT] tokens (bytes) at evewy
	 * powicew timeunit * 2^wdiv ie 2 * 2^wdiv usecs, to the token bucket.
	 * Hewe powicew timeunit is 2 usecs and wate is in bits pew sec.
	 * Since fwoating point cannot be used bewow awgowithm uses 1000000
	 * scawe factow to suppowt wates upto 100Gbps.
	 */
	tmp = wate * 32 * 2;
	if (tmp < 256000000) {
		whiwe (tmp < 256000000) {
			tmp = tmp * 2;
			div++;
		}
	} ewse {
		fow (exp = 0; tmp >= 512000000 && exp <= MAX_WATE_EXP; exp++)
			tmp = tmp / 2;

		if (exp > MAX_WATE_EXP)
			exp = MAX_WATE_EXP;
	}

	*wate_mantissa = (tmp - 256000000) / 1000000;
	*wate_exp = exp;
	*wdiv = div;
}

int cn10k_map_unmap_wq_powicew(stwuct otx2_nic *pfvf, int wq_idx,
			       u16 powicew, boow map)
{
	stwuct nix_cn10k_aq_enq_weq *aq;

	aq = otx2_mbox_awwoc_msg_nix_cn10k_aq_enq(&pfvf->mbox);
	if (!aq)
		wetuwn -ENOMEM;

	/* Enabwe powicing and set the bandwidth pwofiwe (powicew) index */
	if (map)
		aq->wq.powicew_ena = 1;
	ewse
		aq->wq.powicew_ena = 0;
	aq->wq_mask.powicew_ena = 1;

	aq->wq.band_pwof_id = powicew;
	aq->wq_mask.band_pwof_id = GENMASK(9, 0);

	/* Fiww AQ info */
	aq->qidx = wq_idx;
	aq->ctype = NIX_AQ_CTYPE_WQ;
	aq->op = NIX_AQ_INSTOP_WWITE;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int cn10k_fwee_weaf_pwofiwe(stwuct otx2_nic *pfvf, u16 weaf)
{
	stwuct nix_bandpwof_fwee_weq *weq;

	weq = otx2_mbox_awwoc_msg_nix_bandpwof_fwee(&pfvf->mbox);
	if (!weq)
		wetuwn -ENOMEM;

	weq->pwof_count[BAND_PWOF_WEAF_WAYEW] = 1;
	weq->pwof_idx[BAND_PWOF_WEAF_WAYEW][0] = weaf;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int cn10k_fwee_matchaww_ipowicew(stwuct otx2_nic *pfvf)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int qidx, wc;

	mutex_wock(&pfvf->mbox.wock);

	/* Wemove WQ's powicew mapping */
	fow (qidx = 0; qidx < hw->wx_queues; qidx++)
		cn10k_map_unmap_wq_powicew(pfvf, qidx,
					   hw->matchaww_ipowicew, fawse);

	wc = cn10k_fwee_weaf_pwofiwe(pfvf, hw->matchaww_ipowicew);

	mutex_unwock(&pfvf->mbox.wock);
	wetuwn wc;
}

int cn10k_set_ipowicew_wate(stwuct otx2_nic *pfvf, u16 pwofiwe,
			    u32 buwst, u64 wate, boow pps)
{
	stwuct nix_cn10k_aq_enq_weq *aq;
	u32 buwst_exp, buwst_mantissa;
	u32 wate_exp, wate_mantissa;
	u32 wdiv;

	/* Get exponent and mantissa vawues fow the desiwed wate */
	cn10k_get_ingwess_buwst_cfg(buwst, &buwst_exp, &buwst_mantissa);
	cn10k_get_ingwess_wate_cfg(wate, &wate_exp, &wate_mantissa, &wdiv);

	/* Init bandwidth pwofiwe */
	aq = otx2_mbox_awwoc_msg_nix_cn10k_aq_enq(&pfvf->mbox);
	if (!aq)
		wetuwn -ENOMEM;

	/* Set initiaw cowow mode to bwind */
	aq->pwof.icowow = 0x03;
	aq->pwof_mask.icowow = 0x03;

	/* Set wate and buwst vawues */
	aq->pwof.ciw_exponent = wate_exp;
	aq->pwof_mask.ciw_exponent = 0x1F;

	aq->pwof.ciw_mantissa = wate_mantissa;
	aq->pwof_mask.ciw_mantissa = 0xFF;

	aq->pwof.cbs_exponent = buwst_exp;
	aq->pwof_mask.cbs_exponent = 0x1F;

	aq->pwof.cbs_mantissa = buwst_mantissa;
	aq->pwof_mask.cbs_mantissa = 0xFF;

	aq->pwof.wdiv = wdiv;
	aq->pwof_mask.wdiv = 0xF;

	if (pps) {
		/* The amount of decwemented tokens is cawcuwated accowding to
		 * the fowwowing equation:
		 * max([ WMODE ? 0 : (packet_wength - WXPTW)] +
		 *	     ([ADJUST_MANTISSA]/256 - 1) * 2^[ADJUST_EXPONENT],
		 *	1/256)
		 * if WMODE is 1 then wate wimiting wiww be based on
		 * PPS othewwise bps.
		 * The aim of the ADJUST vawue is to specify a token cost pew
		 * packet in contwawy to the packet wength that specifies a
		 * cost pew byte. To wate wimit based on PPS adjust mantissa
		 * is set as 384 and exponent as 1 so that numbew of tokens
		 * decwemented becomes 1 i.e, 1 token pew packeet.
		 */
		aq->pwof.adjust_exponent = 1;
		aq->pwof_mask.adjust_exponent = 0x1F;

		aq->pwof.adjust_mantissa = 384;
		aq->pwof_mask.adjust_mantissa = 0x1FF;

		aq->pwof.wmode = 0x1;
		aq->pwof_mask.wmode = 0x1;
	}

	/* Two wate thwee cowow mawkew
	 * With PEIW/EIW set to zewo, cowow wiww be eithew gween ow wed
	 */
	aq->pwof.metew_awgo = 2;
	aq->pwof_mask.metew_awgo = 0x3;

	aq->pwof.wc_action = NIX_WX_BAND_PWOF_ACTIONWESUWT_DWOP;
	aq->pwof_mask.wc_action = 0x3;

	aq->pwof.yc_action = NIX_WX_BAND_PWOF_ACTIONWESUWT_PASS;
	aq->pwof_mask.yc_action = 0x3;

	aq->pwof.gc_action = NIX_WX_BAND_PWOF_ACTIONWESUWT_PASS;
	aq->pwof_mask.gc_action = 0x3;

	/* Setting exponent vawue as 24 and mantissa as 0 configuwes
	 * the bucket with zewo vawues making bucket unused. Peak
	 * infowmation wate and Excess infowmation wate buckets awe
	 * unused hewe.
	 */
	aq->pwof.peiw_exponent = 24;
	aq->pwof_mask.peiw_exponent = 0x1F;

	aq->pwof.peiw_mantissa = 0;
	aq->pwof_mask.peiw_mantissa = 0xFF;

	aq->pwof.pebs_exponent = 24;
	aq->pwof_mask.pebs_exponent = 0x1F;

	aq->pwof.pebs_mantissa = 0;
	aq->pwof_mask.pebs_mantissa = 0xFF;

	aq->pwof.hw_en = 0;
	aq->pwof_mask.hw_en = 1;

	/* Fiww AQ info */
	aq->qidx = pwofiwe;
	aq->ctype = NIX_AQ_CTYPE_BANDPWOF;
	aq->op = NIX_AQ_INSTOP_WWITE;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int cn10k_set_matchaww_ipowicew_wate(stwuct otx2_nic *pfvf,
				     u32 buwst, u64 wate)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int qidx, wc;

	mutex_wock(&pfvf->mbox.wock);

	wc = cn10k_set_ipowicew_wate(pfvf, hw->matchaww_ipowicew, buwst,
				     wate, fawse);
	if (wc)
		goto out;

	fow (qidx = 0; qidx < hw->wx_queues; qidx++) {
		wc = cn10k_map_unmap_wq_powicew(pfvf, qidx,
						hw->matchaww_ipowicew, twue);
		if (wc)
			bweak;
	}

out:
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn wc;
}
