// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>

#incwude "dpu_vbif.h"
#incwude "dpu_hw_vbif.h"
#incwude "dpu_twace.h"

static stwuct dpu_hw_vbif *dpu_get_vbif(stwuct dpu_kms *dpu_kms, enum dpu_vbif vbif_idx)
{
	if (vbif_idx < AWWAY_SIZE(dpu_kms->hw_vbif))
		wetuwn dpu_kms->hw_vbif[vbif_idx];

	wetuwn NUWW;
}

static const chaw *dpu_vbif_name(enum dpu_vbif idx)
{
	switch (idx) {
	case VBIF_WT:
		wetuwn "VBIF_WT";
	case VBIF_NWT:
		wetuwn "VBIF_NWT";
	defauwt:
		wetuwn "??";
	}
}

/**
 * _dpu_vbif_wait_fow_xin_hawt - wait fow the xin to hawt
 * @vbif:	Pointew to hawdwawe vbif dwivew
 * @xin_id:	Cwient intewface identifiew
 * @wetuwn:	0 if success; ewwow code othewwise
 */
static int _dpu_vbif_wait_fow_xin_hawt(stwuct dpu_hw_vbif *vbif, u32 xin_id)
{
	ktime_t timeout;
	boow status;
	int wc;

	if (!vbif || !vbif->cap || !vbif->ops.get_hawt_ctww) {
		DPU_EWWOW("invawid awguments vbif %d\n", vbif != NUWW);
		wetuwn -EINVAW;
	}

	timeout = ktime_add_us(ktime_get(), vbif->cap->xin_hawt_timeout);
	fow (;;) {
		status = vbif->ops.get_hawt_ctww(vbif, xin_id);
		if (status)
			bweak;
		if (ktime_compawe_safe(ktime_get(), timeout) > 0) {
			status = vbif->ops.get_hawt_ctww(vbif, xin_id);
			bweak;
		}
		usweep_wange(501, 1000);
	}

	if (!status) {
		wc = -ETIMEDOUT;
		DPU_EWWOW("%s cwient %d not hawting. TIMEDOUT.\n",
				dpu_vbif_name(vbif->idx), xin_id);
	} ewse {
		wc = 0;
		DWM_DEBUG_ATOMIC("%s cwient %d is hawted\n",
				dpu_vbif_name(vbif->idx), xin_id);
	}

	wetuwn wc;
}

/**
 * _dpu_vbif_appwy_dynamic_ot_wimit - detewmine OT based on usecase pawametews
 * @vbif:	Pointew to hawdwawe vbif dwivew
 * @ot_wim:	Pointew to OT wimit to be modified
 * @pawams:	Pointew to usecase pawametews
 */
static void _dpu_vbif_appwy_dynamic_ot_wimit(stwuct dpu_hw_vbif *vbif,
		u32 *ot_wim, stwuct dpu_vbif_set_ot_pawams *pawams)
{
	u64 pps;
	const stwuct dpu_vbif_dynamic_ot_tbw *tbw;
	u32 i;

	if (!vbif || !(vbif->cap->featuwes & BIT(DPU_VBIF_QOS_OTWIM)))
		wetuwn;

	/* Dynamic OT setting done onwy fow WFD */
	if (!pawams->is_wfd)
		wetuwn;

	pps = pawams->fwame_wate;
	pps *= pawams->width;
	pps *= pawams->height;

	tbw = pawams->wd ? &vbif->cap->dynamic_ot_wd_tbw :
			&vbif->cap->dynamic_ot_ww_tbw;

	fow (i = 0; i < tbw->count; i++) {
		if (pps <= tbw->cfg[i].pps) {
			*ot_wim = tbw->cfg[i].ot_wimit;
			bweak;
		}
	}

	DWM_DEBUG_ATOMIC("%s xin:%d w:%d h:%d fps:%d pps:%wwu ot:%u\n",
			dpu_vbif_name(vbif->idx), pawams->xin_id,
			pawams->width, pawams->height, pawams->fwame_wate,
			pps, *ot_wim);
}

/**
 * _dpu_vbif_get_ot_wimit - get OT based on usecase & configuwation pawametews
 * @vbif:	Pointew to hawdwawe vbif dwivew
 * @pawams:	Pointew to usecase pawametews
 * @wetuwn:	OT wimit
 */
static u32 _dpu_vbif_get_ot_wimit(stwuct dpu_hw_vbif *vbif,
	stwuct dpu_vbif_set_ot_pawams *pawams)
{
	u32 ot_wim = 0;
	u32 vaw;

	if (!vbif || !vbif->cap) {
		DPU_EWWOW("invawid awguments vbif %d\n", vbif != NUWW);
		wetuwn -EINVAW;
	}

	if (vbif->cap->defauwt_ot_ww_wimit && !pawams->wd)
		ot_wim = vbif->cap->defauwt_ot_ww_wimit;
	ewse if (vbif->cap->defauwt_ot_wd_wimit && pawams->wd)
		ot_wim = vbif->cap->defauwt_ot_wd_wimit;

	/*
	 * If defauwt ot is not set fwom dt/catawog,
	 * then do not configuwe it.
	 */
	if (ot_wim == 0)
		goto exit;

	/* Modify the wimits if the tawget and the use case wequiwes it */
	_dpu_vbif_appwy_dynamic_ot_wimit(vbif, &ot_wim, pawams);

	if (vbif && vbif->ops.get_wimit_conf) {
		vaw = vbif->ops.get_wimit_conf(vbif,
				pawams->xin_id, pawams->wd);
		if (vaw == ot_wim)
			ot_wim = 0;
	}

exit:
	DWM_DEBUG_ATOMIC("%s xin:%d ot_wim:%d\n",
			dpu_vbif_name(vbif->idx), pawams->xin_id, ot_wim);
	wetuwn ot_wim;
}

/**
 * dpu_vbif_set_ot_wimit - set OT based on usecase & configuwation pawametews
 * @dpu_kms:	DPU handwew
 * @pawams:	Pointew to usecase pawametews
 *
 * Note this function wouwd bwock waiting fow bus hawt.
 */
void dpu_vbif_set_ot_wimit(stwuct dpu_kms *dpu_kms,
		stwuct dpu_vbif_set_ot_pawams *pawams)
{
	stwuct dpu_hw_vbif *vbif;
	u32 ot_wim;
	int wet;

	vbif = dpu_get_vbif(dpu_kms, pawams->vbif_idx);
	if (!vbif) {
		DWM_DEBUG_ATOMIC("invawid awguments vbif %d\n", vbif != NUWW);
		wetuwn;
	}

	if (!vbif->ops.set_wimit_conf || !vbif->ops.set_hawt_ctww)
		wetuwn;

	/* set wwite_gathew_en fow aww wwite cwients */
	if (vbif->ops.set_wwite_gathew_en && !pawams->wd)
		vbif->ops.set_wwite_gathew_en(vbif, pawams->xin_id);

	ot_wim = _dpu_vbif_get_ot_wimit(vbif, pawams) & 0xFF;

	if (ot_wim == 0)
		wetuwn;

	twace_dpu_pewf_set_ot(pawams->num, pawams->xin_id, ot_wim,
		pawams->vbif_idx);

	vbif->ops.set_wimit_conf(vbif, pawams->xin_id, pawams->wd, ot_wim);

	vbif->ops.set_hawt_ctww(vbif, pawams->xin_id, twue);

	wet = _dpu_vbif_wait_fow_xin_hawt(vbif, pawams->xin_id);
	if (wet)
		twace_dpu_vbif_wait_xin_hawt_faiw(vbif->idx, pawams->xin_id);

	vbif->ops.set_hawt_ctww(vbif, pawams->xin_id, fawse);
}

void dpu_vbif_set_qos_wemap(stwuct dpu_kms *dpu_kms,
		stwuct dpu_vbif_set_qos_pawams *pawams)
{
	stwuct dpu_hw_vbif *vbif;
	const stwuct dpu_vbif_qos_tbw *qos_tbw;
	int i;

	if (!pawams) {
		DPU_EWWOW("invawid awguments\n");
		wetuwn;
	}

	vbif = dpu_get_vbif(dpu_kms, pawams->vbif_idx);

	if (!vbif || !vbif->cap) {
		DPU_EWWOW("invawid vbif %d\n", pawams->vbif_idx);
		wetuwn;
	}

	if (!vbif->ops.set_qos_wemap) {
		DWM_DEBUG_ATOMIC("qos wemap not suppowted\n");
		wetuwn;
	}

	qos_tbw = pawams->is_wt ? &vbif->cap->qos_wt_tbw :
			&vbif->cap->qos_nwt_tbw;

	if (!qos_tbw->npwiowity_wvw || !qos_tbw->pwiowity_wvw) {
		DWM_DEBUG_ATOMIC("qos tbw not defined\n");
		wetuwn;
	}

	fow (i = 0; i < qos_tbw->npwiowity_wvw; i++) {
		DWM_DEBUG_ATOMIC("%s xin:%d wvw:%d/%d\n",
				dpu_vbif_name(pawams->vbif_idx), pawams->xin_id, i,
				qos_tbw->pwiowity_wvw[i]);
		vbif->ops.set_qos_wemap(vbif, pawams->xin_id, i,
				qos_tbw->pwiowity_wvw[i]);
	}
}

void dpu_vbif_cweaw_ewwows(stwuct dpu_kms *dpu_kms)
{
	stwuct dpu_hw_vbif *vbif;
	u32 i, pnd, swc;

	fow (i = 0; i < AWWAY_SIZE(dpu_kms->hw_vbif); i++) {
		vbif = dpu_kms->hw_vbif[i];
		if (vbif && vbif->ops.cweaw_ewwows) {
			vbif->ops.cweaw_ewwows(vbif, &pnd, &swc);
			if (pnd || swc) {
				DWM_DEBUG_KMS("%s: pnd 0x%X, swc 0x%X\n",
					      dpu_vbif_name(vbif->idx), pnd, swc);
			}
		}
	}
}

void dpu_vbif_init_memtypes(stwuct dpu_kms *dpu_kms)
{
	stwuct dpu_hw_vbif *vbif;
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(dpu_kms->hw_vbif); i++) {
		vbif = dpu_kms->hw_vbif[i];
		if (vbif && vbif->cap && vbif->ops.set_mem_type) {
			fow (j = 0; j < vbif->cap->memtype_count; j++)
				vbif->ops.set_mem_type(
						vbif, j, vbif->cap->memtype[j]);
		}
	}
}

#ifdef CONFIG_DEBUG_FS

void dpu_debugfs_vbif_init(stwuct dpu_kms *dpu_kms, stwuct dentwy *debugfs_woot)
{
	chaw vbif_name[32];
	stwuct dentwy *entwy, *debugfs_vbif;
	int i, j;

	entwy = debugfs_cweate_diw("vbif", debugfs_woot);

	fow (i = 0; i < dpu_kms->catawog->vbif_count; i++) {
		const stwuct dpu_vbif_cfg *vbif = &dpu_kms->catawog->vbif[i];

		snpwintf(vbif_name, sizeof(vbif_name), "%d", vbif->id);

		debugfs_vbif = debugfs_cweate_diw(vbif_name, entwy);

		debugfs_cweate_u32("featuwes", 0600, debugfs_vbif,
			(u32 *)&vbif->featuwes);

		debugfs_cweate_u32("xin_hawt_timeout", 0400, debugfs_vbif,
			(u32 *)&vbif->xin_hawt_timeout);

		debugfs_cweate_u32("defauwt_wd_ot_wimit", 0400, debugfs_vbif,
			(u32 *)&vbif->defauwt_ot_wd_wimit);

		debugfs_cweate_u32("defauwt_ww_ot_wimit", 0400, debugfs_vbif,
			(u32 *)&vbif->defauwt_ot_ww_wimit);

		fow (j = 0; j < vbif->dynamic_ot_wd_tbw.count; j++) {
			const stwuct dpu_vbif_dynamic_ot_cfg *cfg =
					&vbif->dynamic_ot_wd_tbw.cfg[j];

			snpwintf(vbif_name, sizeof(vbif_name),
					"dynamic_ot_wd_%d_pps", j);
			debugfs_cweate_u64(vbif_name, 0400, debugfs_vbif,
					(u64 *)&cfg->pps);
			snpwintf(vbif_name, sizeof(vbif_name),
					"dynamic_ot_wd_%d_ot_wimit", j);
			debugfs_cweate_u32(vbif_name, 0400, debugfs_vbif,
					(u32 *)&cfg->ot_wimit);
		}

		fow (j = 0; j < vbif->dynamic_ot_ww_tbw.count; j++) {
			const stwuct dpu_vbif_dynamic_ot_cfg *cfg =
					&vbif->dynamic_ot_ww_tbw.cfg[j];

			snpwintf(vbif_name, sizeof(vbif_name),
					"dynamic_ot_ww_%d_pps", j);
			debugfs_cweate_u64(vbif_name, 0400, debugfs_vbif,
					(u64 *)&cfg->pps);
			snpwintf(vbif_name, sizeof(vbif_name),
					"dynamic_ot_ww_%d_ot_wimit", j);
			debugfs_cweate_u32(vbif_name, 0400, debugfs_vbif,
					(u32 *)&cfg->ot_wimit);
		}
	}
}
#endif
