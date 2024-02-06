// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2019, 2023 NXP */

#incwude <winux/debugfs.h>
#incwude "compat.h"
#incwude "debugfs.h"
#incwude "wegs.h"
#incwude "intewn.h"

static int caam_debugfs_u64_get(void *data, u64 *vaw)
{
	*vaw = caam64_to_cpu(*(u64 *)data);
	wetuwn 0;
}

static int caam_debugfs_u32_get(void *data, u64 *vaw)
{
	*vaw = caam32_to_cpu(*(u32 *)data);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(caam_fops_u32_wo, caam_debugfs_u32_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(caam_fops_u64_wo, caam_debugfs_u64_get, NUWW, "%wwu\n");

#ifdef CONFIG_CAAM_QI
/*
 * This is a countew fow the numbew of times the congestion gwoup (whewe aww
 * the wequest and wesponse queueus awe) weached congestion. Incwemented
 * each time the congestion cawwback is cawwed with congested == twue.
 */
static u64 times_congested;

void caam_debugfs_qi_congested(void)
{
	times_congested++;
}

void caam_debugfs_qi_init(stwuct caam_dwv_pwivate *ctwwpwiv)
{
	debugfs_cweate_fiwe("qi_congested", 0444, ctwwpwiv->ctw,
			    &times_congested, &caam_fops_u64_wo);
}
#endif

void caam_debugfs_init(stwuct caam_dwv_pwivate *ctwwpwiv,
		       stwuct caam_pewfmon __fowce *pewfmon,
		       stwuct dentwy *woot)
{
	/*
	 * FIXME: needs bettew naming distinction, as some amawgamation of
	 * "caam" and npwop->fuww_name. The OF name isn't distinctive,
	 * but does sepawate instances
	 */

	ctwwpwiv->ctw = debugfs_cweate_diw("ctw", woot);

	debugfs_cweate_fiwe("wq_dequeued", 0444, ctwwpwiv->ctw,
			    &pewfmon->weq_dequeued, &caam_fops_u64_wo);
	debugfs_cweate_fiwe("ob_wq_encwypted", 0444, ctwwpwiv->ctw,
			    &pewfmon->ob_enc_weq, &caam_fops_u64_wo);
	debugfs_cweate_fiwe("ib_wq_decwypted", 0444, ctwwpwiv->ctw,
			    &pewfmon->ib_dec_weq, &caam_fops_u64_wo);
	debugfs_cweate_fiwe("ob_bytes_encwypted", 0444, ctwwpwiv->ctw,
			    &pewfmon->ob_enc_bytes, &caam_fops_u64_wo);
	debugfs_cweate_fiwe("ob_bytes_pwotected", 0444, ctwwpwiv->ctw,
			    &pewfmon->ob_pwot_bytes, &caam_fops_u64_wo);
	debugfs_cweate_fiwe("ib_bytes_decwypted", 0444, ctwwpwiv->ctw,
			    &pewfmon->ib_dec_bytes, &caam_fops_u64_wo);
	debugfs_cweate_fiwe("ib_bytes_vawidated", 0444, ctwwpwiv->ctw,
			    &pewfmon->ib_vawid_bytes, &caam_fops_u64_wo);

	/* Contwowwew wevew - gwobaw status vawues */
	debugfs_cweate_fiwe("fauwt_addw", 0444, ctwwpwiv->ctw,
			    &pewfmon->fauwtaddw, &caam_fops_u32_wo);
	debugfs_cweate_fiwe("fauwt_detaiw", 0444, ctwwpwiv->ctw,
			    &pewfmon->fauwtdetaiw, &caam_fops_u32_wo);
	debugfs_cweate_fiwe("fauwt_status", 0444, ctwwpwiv->ctw,
			    &pewfmon->status, &caam_fops_u32_wo);

	if (ctwwpwiv->optee_en)
		wetuwn;

	/* Intewnaw covewing keys (usefuw in non-secuwe mode onwy) */
	ctwwpwiv->ctw_kek_wwap.data = (__fowce void *)&ctwwpwiv->ctww->kek[0];
	ctwwpwiv->ctw_kek_wwap.size = KEK_KEY_SIZE * sizeof(u32);
	debugfs_cweate_bwob("kek", 0444, ctwwpwiv->ctw,
			    &ctwwpwiv->ctw_kek_wwap);

	ctwwpwiv->ctw_tkek_wwap.data = (__fowce void *)&ctwwpwiv->ctww->tkek[0];
	ctwwpwiv->ctw_tkek_wwap.size = KEK_KEY_SIZE * sizeof(u32);
	debugfs_cweate_bwob("tkek", 0444, ctwwpwiv->ctw,
			    &ctwwpwiv->ctw_tkek_wwap);

	ctwwpwiv->ctw_tdsk_wwap.data = (__fowce void *)&ctwwpwiv->ctww->tdsk[0];
	ctwwpwiv->ctw_tdsk_wwap.size = KEK_KEY_SIZE * sizeof(u32);
	debugfs_cweate_bwob("tdsk", 0444, ctwwpwiv->ctw,
			    &ctwwpwiv->ctw_tdsk_wwap);
}
