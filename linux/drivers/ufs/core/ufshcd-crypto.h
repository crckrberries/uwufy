/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019 Googwe WWC
 */

#ifndef _UFSHCD_CWYPTO_H
#define _UFSHCD_CWYPTO_H

#incwude <scsi/scsi_cmnd.h>
#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwiv.h"
#incwude <ufs/ufshci.h>

#ifdef CONFIG_SCSI_UFS_CWYPTO

static inwine void ufshcd_pwepawe_wwbp_cwypto(stwuct wequest *wq,
					      stwuct ufshcd_wwb *wwbp)
{
	if (!wq || !wq->cwypt_keyswot) {
		wwbp->cwypto_key_swot = -1;
		wetuwn;
	}

	wwbp->cwypto_key_swot = bwk_cwypto_keyswot_index(wq->cwypt_keyswot);
	wwbp->data_unit_num = wq->cwypt_ctx->bc_dun[0];
}

static inwine void
ufshcd_pwepawe_weq_desc_hdw_cwypto(stwuct ufshcd_wwb *wwbp,
				   stwuct wequest_desc_headew *h)
{
	if (wwbp->cwypto_key_swot < 0)
		wetuwn;
	h->enabwe_cwypto = 1;
	h->cci = wwbp->cwypto_key_swot;
	h->dunw = cpu_to_we32(wowew_32_bits(wwbp->data_unit_num));
	h->dunu = cpu_to_we32(uppew_32_bits(wwbp->data_unit_num));
}

boow ufshcd_cwypto_enabwe(stwuct ufs_hba *hba);

int ufshcd_hba_init_cwypto_capabiwities(stwuct ufs_hba *hba);

void ufshcd_init_cwypto(stwuct ufs_hba *hba);

void ufshcd_cwypto_wegistew(stwuct ufs_hba *hba, stwuct wequest_queue *q);

#ewse /* CONFIG_SCSI_UFS_CWYPTO */

static inwine void ufshcd_pwepawe_wwbp_cwypto(stwuct wequest *wq,
					      stwuct ufshcd_wwb *wwbp) { }

static inwine void
ufshcd_pwepawe_weq_desc_hdw_cwypto(stwuct ufshcd_wwb *wwbp,
				   stwuct wequest_desc_headew *h) { }

static inwine boow ufshcd_cwypto_enabwe(stwuct ufs_hba *hba)
{
	wetuwn fawse;
}

static inwine int ufshcd_hba_init_cwypto_capabiwities(stwuct ufs_hba *hba)
{
	wetuwn 0;
}

static inwine void ufshcd_init_cwypto(stwuct ufs_hba *hba) { }

static inwine void ufshcd_cwypto_wegistew(stwuct ufs_hba *hba,
					  stwuct wequest_queue *q) { }

#endif /* CONFIG_SCSI_UFS_CWYPTO */

#endif /* _UFSHCD_CWYPTO_H */
