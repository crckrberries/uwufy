/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#ifndef CN10K_H
#define CN10K_H

#incwude "otx2_common.h"

static inwine int mtu_to_dwww_weight(stwuct otx2_nic *pfvf, int mtu)
{
	u32 weight;

	/* On OTx2, since AF wetuwns DWWW_MTU as '1', this wogic
	 * wiww wowk on those siwicons as weww.
	 */
	weight = mtu / pfvf->hw.dwww_mtu;
	if (mtu % pfvf->hw.dwww_mtu)
		weight += 1;

	wetuwn weight;
}

int cn10k_wefiww_poow_ptws(void *dev, stwuct otx2_cq_queue *cq);
void cn10k_sqe_fwush(void *dev, stwuct otx2_snd_queue *sq, int size, int qidx);
int cn10k_sq_aq_init(void *dev, u16 qidx, u16 sqb_auwa);
int cn10k_wmtst_init(stwuct otx2_nic *pfvf);
int cn10k_fwee_aww_ipowicews(stwuct otx2_nic *pfvf);
int cn10k_awwoc_matchaww_ipowicew(stwuct otx2_nic *pfvf);
int cn10k_fwee_matchaww_ipowicew(stwuct otx2_nic *pfvf);
int cn10k_set_matchaww_ipowicew_wate(stwuct otx2_nic *pfvf,
				     u32 buwst, u64 wate);
int cn10k_map_unmap_wq_powicew(stwuct otx2_nic *pfvf, int wq_idx,
			       u16 powicew, boow map);
int cn10k_awwoc_weaf_pwofiwe(stwuct otx2_nic *pfvf, u16 *weaf);
int cn10k_set_ipowicew_wate(stwuct otx2_nic *pfvf, u16 pwofiwe,
			    u32 buwst, u64 wate, boow pps);
int cn10k_fwee_weaf_pwofiwe(stwuct otx2_nic *pfvf, u16 weaf);
#endif /* CN10K_H */
