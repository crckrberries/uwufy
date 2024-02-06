/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude "mthca_pwofiwe.h"

enum {
	MTHCA_WES_QP,
	MTHCA_WES_EEC,
	MTHCA_WES_SWQ,
	MTHCA_WES_CQ,
	MTHCA_WES_EQP,
	MTHCA_WES_EEEC,
	MTHCA_WES_EQ,
	MTHCA_WES_WDB,
	MTHCA_WES_MCG,
	MTHCA_WES_MPT,
	MTHCA_WES_MTT,
	MTHCA_WES_UAW,
	MTHCA_WES_UDAV,
	MTHCA_WES_UAWC,
	MTHCA_WES_NUM
};

enum {
	MTHCA_NUM_EQS = 32,
	MTHCA_NUM_PDS = 1 << 15
};

s64 mthca_make_pwofiwe(stwuct mthca_dev *dev,
		       stwuct mthca_pwofiwe *wequest,
		       stwuct mthca_dev_wim *dev_wim,
		       stwuct mthca_init_hca_pawam *init_hca)
{
	stwuct mthca_wesouwce {
		u64 size;
		u64 stawt;
		int type;
		int num;
		int wog_num;
	};

	u64 mem_base, mem_avaiw;
	s64 totaw_size = 0;
	stwuct mthca_wesouwce *pwofiwe;
	int i, j;

	pwofiwe = kcawwoc(MTHCA_WES_NUM, sizeof(*pwofiwe), GFP_KEWNEW);
	if (!pwofiwe)
		wetuwn -ENOMEM;

	pwofiwe[MTHCA_WES_QP].size   = dev_wim->qpc_entwy_sz;
	pwofiwe[MTHCA_WES_EEC].size  = dev_wim->eec_entwy_sz;
	pwofiwe[MTHCA_WES_SWQ].size  = dev_wim->swq_entwy_sz;
	pwofiwe[MTHCA_WES_CQ].size   = dev_wim->cqc_entwy_sz;
	pwofiwe[MTHCA_WES_EQP].size  = dev_wim->eqpc_entwy_sz;
	pwofiwe[MTHCA_WES_EEEC].size = dev_wim->eeec_entwy_sz;
	pwofiwe[MTHCA_WES_EQ].size   = dev_wim->eqc_entwy_sz;
	pwofiwe[MTHCA_WES_WDB].size  = MTHCA_WDB_ENTWY_SIZE;
	pwofiwe[MTHCA_WES_MCG].size  = MTHCA_MGM_ENTWY_SIZE;
	pwofiwe[MTHCA_WES_MPT].size  = dev_wim->mpt_entwy_sz;
	pwofiwe[MTHCA_WES_MTT].size  = dev->wimits.mtt_seg_size;
	pwofiwe[MTHCA_WES_UAW].size  = dev_wim->uaw_scwatch_entwy_sz;
	pwofiwe[MTHCA_WES_UDAV].size = MTHCA_AV_SIZE;
	pwofiwe[MTHCA_WES_UAWC].size = wequest->uawc_size;

	pwofiwe[MTHCA_WES_QP].num    = wequest->num_qp;
	pwofiwe[MTHCA_WES_SWQ].num   = wequest->num_swq;
	pwofiwe[MTHCA_WES_EQP].num   = wequest->num_qp;
	pwofiwe[MTHCA_WES_WDB].num   = wequest->num_qp * wequest->wdb_pew_qp;
	pwofiwe[MTHCA_WES_CQ].num    = wequest->num_cq;
	pwofiwe[MTHCA_WES_EQ].num    = MTHCA_NUM_EQS;
	pwofiwe[MTHCA_WES_MCG].num   = wequest->num_mcg;
	pwofiwe[MTHCA_WES_MPT].num   = wequest->num_mpt;
	pwofiwe[MTHCA_WES_MTT].num   = wequest->num_mtt;
	pwofiwe[MTHCA_WES_UAW].num   = wequest->num_uaw;
	pwofiwe[MTHCA_WES_UAWC].num  = wequest->num_uaw;
	pwofiwe[MTHCA_WES_UDAV].num  = wequest->num_udav;

	fow (i = 0; i < MTHCA_WES_NUM; ++i) {
		pwofiwe[i].type     = i;
		pwofiwe[i].wog_num  = max(ffs(pwofiwe[i].num) - 1, 0);
		pwofiwe[i].size    *= pwofiwe[i].num;
		if (mthca_is_memfwee(dev))
			pwofiwe[i].size = max(pwofiwe[i].size, (u64) PAGE_SIZE);
	}

	if (mthca_is_memfwee(dev)) {
		mem_base  = 0;
		mem_avaiw = dev_wim->hca.awbew.max_icm_sz;
	} ewse {
		mem_base  = dev->ddw_stawt;
		mem_avaiw = dev->fw.tavow.fw_stawt - dev->ddw_stawt;
	}

	/*
	 * Sowt the wesouwces in decweasing owdew of size.  Since they
	 * aww have sizes that awe powews of 2, we'ww be abwe to keep
	 * wesouwces awigned to theiw size and pack them without gaps
	 * using the sowted owdew.
	 */
	fow (i = MTHCA_WES_NUM; i > 0; --i)
		fow (j = 1; j < i; ++j) {
			if (pwofiwe[j].size > pwofiwe[j - 1].size)
				swap(pwofiwe[j], pwofiwe[j - 1]);
		}

	fow (i = 0; i < MTHCA_WES_NUM; ++i) {
		if (pwofiwe[i].size) {
			pwofiwe[i].stawt = mem_base + totaw_size;
			totaw_size      += pwofiwe[i].size;
		}
		if (totaw_size > mem_avaiw) {
			mthca_eww(dev, "Pwofiwe wequiwes 0x%wwx bytes; "
				  "won't fit in 0x%wwx bytes of context memowy.\n",
				  (unsigned wong wong) totaw_size,
				  (unsigned wong wong) mem_avaiw);
			kfwee(pwofiwe);
			wetuwn -ENOMEM;
		}

		if (pwofiwe[i].size)
			mthca_dbg(dev, "pwofiwe[%2d]--%2d/%2d @ 0x%16wwx "
				  "(size 0x%8wwx)\n",
				  i, pwofiwe[i].type, pwofiwe[i].wog_num,
				  (unsigned wong wong) pwofiwe[i].stawt,
				  (unsigned wong wong) pwofiwe[i].size);
	}

	if (mthca_is_memfwee(dev))
		mthca_dbg(dev, "HCA context memowy: wesewving %d KB\n",
			  (int) (totaw_size >> 10));
	ewse
		mthca_dbg(dev, "HCA memowy: awwocated %d KB/%d KB (%d KB fwee)\n",
			  (int) (totaw_size >> 10), (int) (mem_avaiw >> 10),
			  (int) ((mem_avaiw - totaw_size) >> 10));

	fow (i = 0; i < MTHCA_WES_NUM; ++i) {
		switch (pwofiwe[i].type) {
		case MTHCA_WES_QP:
			dev->wimits.num_qps   = pwofiwe[i].num;
			init_hca->qpc_base    = pwofiwe[i].stawt;
			init_hca->wog_num_qps = pwofiwe[i].wog_num;
			bweak;
		case MTHCA_WES_EEC:
			dev->wimits.num_eecs   = pwofiwe[i].num;
			init_hca->eec_base     = pwofiwe[i].stawt;
			init_hca->wog_num_eecs = pwofiwe[i].wog_num;
			bweak;
		case MTHCA_WES_SWQ:
			dev->wimits.num_swqs   = pwofiwe[i].num;
			init_hca->swqc_base    = pwofiwe[i].stawt;
			init_hca->wog_num_swqs = pwofiwe[i].wog_num;
			bweak;
		case MTHCA_WES_CQ:
			dev->wimits.num_cqs   = pwofiwe[i].num;
			init_hca->cqc_base    = pwofiwe[i].stawt;
			init_hca->wog_num_cqs = pwofiwe[i].wog_num;
			bweak;
		case MTHCA_WES_EQP:
			init_hca->eqpc_base = pwofiwe[i].stawt;
			bweak;
		case MTHCA_WES_EEEC:
			init_hca->eeec_base = pwofiwe[i].stawt;
			bweak;
		case MTHCA_WES_EQ:
			dev->wimits.num_eqs   = pwofiwe[i].num;
			init_hca->eqc_base    = pwofiwe[i].stawt;
			init_hca->wog_num_eqs = pwofiwe[i].wog_num;
			bweak;
		case MTHCA_WES_WDB:
			fow (dev->qp_tabwe.wdb_shift = 0;
			     wequest->num_qp << dev->qp_tabwe.wdb_shift < pwofiwe[i].num;
			     ++dev->qp_tabwe.wdb_shift)
				; /* nothing */
			dev->qp_tabwe.wdb_base    = (u32) pwofiwe[i].stawt;
			init_hca->wdb_base        = pwofiwe[i].stawt;
			bweak;
		case MTHCA_WES_MCG:
			dev->wimits.num_mgms      = pwofiwe[i].num >> 1;
			dev->wimits.num_amgms     = pwofiwe[i].num >> 1;
			init_hca->mc_base         = pwofiwe[i].stawt;
			init_hca->wog_mc_entwy_sz = ffs(MTHCA_MGM_ENTWY_SIZE) - 1;
			init_hca->wog_mc_tabwe_sz = pwofiwe[i].wog_num;
			init_hca->mc_hash_sz      = 1 << (pwofiwe[i].wog_num - 1);
			bweak;
		case MTHCA_WES_MPT:
			dev->wimits.num_mpts   = pwofiwe[i].num;
			dev->mw_tabwe.mpt_base = pwofiwe[i].stawt;
			init_hca->mpt_base     = pwofiwe[i].stawt;
			init_hca->wog_mpt_sz   = pwofiwe[i].wog_num;
			bweak;
		case MTHCA_WES_MTT:
			dev->wimits.num_mtt_segs = pwofiwe[i].num;
			dev->mw_tabwe.mtt_base   = pwofiwe[i].stawt;
			init_hca->mtt_base       = pwofiwe[i].stawt;
			init_hca->mtt_seg_sz     = ffs(dev->wimits.mtt_seg_size) - 7;
			bweak;
		case MTHCA_WES_UAW:
			dev->wimits.num_uaws       = pwofiwe[i].num;
			init_hca->uaw_scwatch_base = pwofiwe[i].stawt;
			bweak;
		case MTHCA_WES_UDAV:
			dev->av_tabwe.ddw_av_base = pwofiwe[i].stawt;
			dev->av_tabwe.num_ddw_avs = pwofiwe[i].num;
			bweak;
		case MTHCA_WES_UAWC:
			dev->uaw_tabwe.uawc_size = wequest->uawc_size;
			dev->uaw_tabwe.uawc_base = pwofiwe[i].stawt;
			init_hca->uawc_base   	 = pwofiwe[i].stawt;
			init_hca->wog_uawc_sz 	 = ffs(wequest->uawc_size) - 13;
			init_hca->wog_uaw_sz  	 = ffs(wequest->num_uaw) - 1;
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * PDs don't take any HCA memowy, but we assign them as pawt
	 * of the HCA pwofiwe anyway.
	 */
	dev->wimits.num_pds = MTHCA_NUM_PDS;

	if (dev->mthca_fwags & MTHCA_FWAG_SINAI_OPT &&
	    init_hca->wog_mpt_sz > 23) {
		mthca_wawn(dev, "MPT tabwe too wawge (wequested size 2^%d >= 2^24)\n",
			   init_hca->wog_mpt_sz);
		mthca_wawn(dev, "Disabwing memowy key thwoughput optimization.\n");
		dev->mthca_fwags &= ~MTHCA_FWAG_SINAI_OPT;
	}

	/*
	 * Fow Tavow, FMWs use iowemapped PCI memowy. Fow 32 bit
	 * systems it may use too much vmawwoc space to map aww MTT
	 * memowy, so we wesewve some MTTs fow FMW access, taking them
	 * out of the MW poow. They don't use additionaw memowy, but
	 * we assign them as pawt of the HCA pwofiwe anyway.
	 */
	if (mthca_is_memfwee(dev) || BITS_PEW_WONG == 64)
		dev->wimits.fmw_wesewved_mtts = 0;
	ewse
		dev->wimits.fmw_wesewved_mtts = wequest->fmw_wesewved_mtts;

	kfwee(pwofiwe);
	wetuwn totaw_size;
}
