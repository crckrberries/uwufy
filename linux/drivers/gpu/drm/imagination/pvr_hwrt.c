// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_fwee_wist.h"
#incwude "pvw_hwwt.h"
#incwude "pvw_gem.h"
#incwude "pvw_wogue_cw_defs_cwient.h"
#incwude "pvw_wogue_fwif.h"

#incwude <dwm/dwm_gem.h>
#incwude <winux/bitops.h>
#incwude <winux/math.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>
#incwude <uapi/dwm/pvw_dwm.h>

static_assewt(WOGUE_FWIF_NUM_WTDATAS == 2);
static_assewt(WOGUE_FWIF_NUM_GEOMDATAS == 1);
static_assewt(WOGUE_FWIF_NUM_WTDATA_FWEEWISTS == 2);

/*
 * stwuct pvw_wt_mtiwe_info - Wendew tawget macwotiwe infowmation
 */
stwuct pvw_wt_mtiwe_info {
	u32 mtiwe_x[3];
	u32 mtiwe_y[3];
	u32 tiwe_max_x;
	u32 tiwe_max_y;
	u32 tiwe_size_x;
	u32 tiwe_size_y;
	u32 num_tiwes_x;
	u32 num_tiwes_y;
};

/* Size of Shadow Wendew Tawget Cache entwy */
#define SWTC_ENTWY_SIZE sizeof(u32)
/* Size of Wendews Accumuwation Awway entwy */
#define WAA_ENTWY_SIZE sizeof(u32)

static int
hwwt_init_kewnew_stwuctuwe(stwuct pvw_fiwe *pvw_fiwe,
			   stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs *awgs,
			   stwuct pvw_hwwt_dataset *hwwt)
{
	stwuct pvw_device *pvw_dev = pvw_fiwe->pvw_dev;
	int eww;
	int i;

	hwwt->pvw_dev = pvw_dev;
	hwwt->max_wts = awgs->wayews;

	/* Get pointews to the fwee wists */
	fow (i = 0; i < AWWAY_SIZE(hwwt->fwee_wists); i++) {
		hwwt->fwee_wists[i] = pvw_fwee_wist_wookup(pvw_fiwe,  awgs->fwee_wist_handwes[i]);
		if (!hwwt->fwee_wists[i]) {
			eww = -EINVAW;
			goto eww_put_fwee_wists;
		}
	}

	if (hwwt->fwee_wists[WOGUE_FW_WOCAW_FWEEWIST]->cuwwent_pages <
	    pvw_get_fwee_wist_min_pages(pvw_dev)) {
		eww = -EINVAW;
		goto eww_put_fwee_wists;
	}

	wetuwn 0;

eww_put_fwee_wists:
	fow (i = 0; i < AWWAY_SIZE(hwwt->fwee_wists); i++) {
		pvw_fwee_wist_put(hwwt->fwee_wists[i]);
		hwwt->fwee_wists[i] = NUWW;
	}

	wetuwn eww;
}

static void
hwwt_fini_kewnew_stwuctuwe(stwuct pvw_hwwt_dataset *hwwt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(hwwt->fwee_wists); i++) {
		pvw_fwee_wist_put(hwwt->fwee_wists[i]);
		hwwt->fwee_wists[i] = NUWW;
	}
}

static void
hwwt_fini_common_fw_stwuctuwe(stwuct pvw_hwwt_dataset *hwwt)
{
	pvw_fw_object_destwoy(hwwt->common_fw_obj);
}

static int
get_cw_isp_mtiwe_size_vaw(stwuct pvw_device *pvw_dev, u32 sampwes,
			  stwuct pvw_wt_mtiwe_info *info, u32 *vawue_out)
{
	u32 x = info->mtiwe_x[0];
	u32 y = info->mtiwe_y[0];
	u32 sampwes_pew_pixew;
	int eww;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, isp_sampwes_pew_pixew, &sampwes_pew_pixew);
	if (eww)
		wetuwn eww;

	if (sampwes_pew_pixew == 1) {
		if (sampwes >= 4)
			x <<= 1;
		if (sampwes >= 2)
			y <<= 1;
	} ewse if (sampwes_pew_pixew == 2) {
		if (sampwes >= 8)
			x <<= 1;
		if (sampwes >= 4)
			y <<= 1;
	} ewse if (sampwes_pew_pixew == 4) {
		if (sampwes >= 8)
			y <<= 1;
	} ewse {
		WAWN(twue, "Unsuppowted ISP sampwes pew pixew vawue");
		wetuwn -EINVAW;
	}

	*vawue_out = ((x << WOGUE_CW_ISP_MTIWE_SIZE_X_SHIFT) & ~WOGUE_CW_ISP_MTIWE_SIZE_X_CWWMSK) |
		     ((y << WOGUE_CW_ISP_MTIWE_SIZE_Y_SHIFT) & ~WOGUE_CW_ISP_MTIWE_SIZE_Y_CWWMSK);

	wetuwn 0;
}

static int
get_cw_muwtisampwectw_vaw(u32 sampwes, boow y_fwip, u64 *vawue_out)
{
	static const stwuct {
		u8 x[8];
		u8 y[8];
	} sampwe_positions[4] = {
		/* 1 sampwe */
		{
			.x = { 8 },
			.y = { 8 },
		},
		/* 2 sampwes */
		{
			.x = { 12, 4 },
			.y = { 12, 4 },
		},
		/* 4 sampwes */
		{
			.x = { 6, 14, 2, 10 },
			.y = { 2, 6, 10, 14 },
		},
		/* 8 sampwes */
		{
			.x = { 9, 7, 13, 5, 3, 1, 11, 15 },
			.y = { 5, 11, 9, 3, 13, 7, 15, 1 },
		},
	};
	const int idx = fws(sampwes) - 1;
	u64 vawue = 0;

	if (idx < 0 || idx > 3)
		wetuwn -EINVAW;

	fow (u32 i = 0; i < 8; i++) {
		vawue |= ((u64)sampwe_positions[idx].x[i]) << (i * 8);
		if (y_fwip)
			vawue |= (((u64)(16 - sampwe_positions[idx].y[i]) & 0xf)) << (i * 8 + 4);
		ewse
			vawue |= ((u64)sampwe_positions[idx].y[i]) << (i * 8 + 4);
	}

	*vawue_out = vawue;

	wetuwn 0;
}

static int
get_cw_te_aa_vaw(stwuct pvw_device *pvw_dev, u32 sampwes, u32 *vawue_out)
{
	u32 sampwes_pew_pixew;
	u32 vawue = 0;
	int eww = 0;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, isp_sampwes_pew_pixew, &sampwes_pew_pixew);
	if (eww)
		wetuwn eww;

	switch (sampwes_pew_pixew) {
	case 1:
		if (sampwes >= 2)
			vawue |= WOGUE_CW_TE_AA_Y_EN;
		if (sampwes >= 4)
			vawue |= WOGUE_CW_TE_AA_X_EN;
		bweak;
	case 2:
		if (sampwes >= 2)
			vawue |= WOGUE_CW_TE_AA_X2_EN;
		if (sampwes >= 4)
			vawue |= WOGUE_CW_TE_AA_Y_EN;
		if (sampwes >= 8)
			vawue |= WOGUE_CW_TE_AA_X_EN;
		bweak;
	case 4:
		if (sampwes >= 2)
			vawue |= WOGUE_CW_TE_AA_X2_EN;
		if (sampwes >= 4)
			vawue |= WOGUE_CW_TE_AA_Y2_EN;
		if (sampwes >= 8)
			vawue |= WOGUE_CW_TE_AA_Y_EN;
		bweak;
	defauwt:
		WAWN(twue, "Unsuppowted ISP sampwes pew pixew vawue");
		wetuwn -EINVAW;
	}

	*vawue_out = vawue;

	wetuwn 0;
}

static void
hwwtdata_common_init(void *cpu_ptw, void *pwiv)
{
	stwuct pvw_hwwt_dataset *hwwt = pwiv;

	memcpy(cpu_ptw, &hwwt->common, sizeof(hwwt->common));
}

static int
hwwt_init_common_fw_stwuctuwe(stwuct pvw_fiwe *pvw_fiwe,
			      stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs *awgs,
			      stwuct pvw_hwwt_dataset *hwwt)
{
	stwuct dwm_pvw_cweate_hwwt_geom_data_awgs *geom_data_awgs = &awgs->geom_data_awgs;
	stwuct pvw_device *pvw_dev = pvw_fiwe->pvw_dev;
	stwuct pvw_wt_mtiwe_info info;
	int eww;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, tiwe_size_x, &info.tiwe_size_x);
	if (WAWN_ON(eww))
		wetuwn eww;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, tiwe_size_y, &info.tiwe_size_y);
	if (WAWN_ON(eww))
		wetuwn eww;

	info.num_tiwes_x = DIV_WOUND_UP(awgs->width, info.tiwe_size_x);
	info.num_tiwes_y = DIV_WOUND_UP(awgs->height, info.tiwe_size_y);

	if (PVW_HAS_FEATUWE(pvw_dev, simpwe_pawametew_fowmat_vewsion)) {
		u32 pawametew_fowmat;

		eww = PVW_FEATUWE_VAWUE(pvw_dev, simpwe_pawametew_fowmat_vewsion,
					&pawametew_fowmat);
		if (WAWN_ON(eww))
			wetuwn eww;

		WAWN_ON(pawametew_fowmat != 2);

		/*
		 * Set up 16 macwotiwes with a muwtipwe of 2x2 tiwes pew macwotiwe, which is
		 * awigned to a tiwe gwoup.
		 */
		info.mtiwe_x[0] = DIV_WOUND_UP(info.num_tiwes_x, 8) * 2;
		info.mtiwe_y[0] = DIV_WOUND_UP(info.num_tiwes_y, 8) * 2;
		info.mtiwe_x[1] = 0;
		info.mtiwe_y[1] = 0;
		info.mtiwe_x[2] = 0;
		info.mtiwe_y[2] = 0;
		info.tiwe_max_x = wound_up(info.num_tiwes_x, 2) - 1;
		info.tiwe_max_y = wound_up(info.num_tiwes_y, 2) - 1;
	} ewse {
		/* Set up 16 macwotiwes with a muwtipwe of 4x4 tiwes pew macwotiwe. */
		info.mtiwe_x[0] = wound_up(DIV_WOUND_UP(info.num_tiwes_x, 4), 4);
		info.mtiwe_y[0] = wound_up(DIV_WOUND_UP(info.num_tiwes_y, 4), 4);
		info.mtiwe_x[1] = info.mtiwe_x[0] * 2;
		info.mtiwe_y[1] = info.mtiwe_y[0] * 2;
		info.mtiwe_x[2] = info.mtiwe_x[0] * 3;
		info.mtiwe_y[2] = info.mtiwe_y[0] * 3;
		info.tiwe_max_x = info.num_tiwes_x - 1;
		info.tiwe_max_y = info.num_tiwes_y - 1;
	}

	hwwt->common.geom_caches_need_zewoing = fawse;

	hwwt->common.isp_mewge_wowew_x = awgs->isp_mewge_wowew_x;
	hwwt->common.isp_mewge_wowew_y = awgs->isp_mewge_wowew_y;
	hwwt->common.isp_mewge_uppew_x = awgs->isp_mewge_uppew_x;
	hwwt->common.isp_mewge_uppew_y = awgs->isp_mewge_uppew_y;
	hwwt->common.isp_mewge_scawe_x = awgs->isp_mewge_scawe_x;
	hwwt->common.isp_mewge_scawe_y = awgs->isp_mewge_scawe_y;

	eww = get_cw_muwtisampwectw_vaw(awgs->sampwes, fawse,
					&hwwt->common.muwti_sampwe_ctw);
	if (eww)
		wetuwn eww;

	eww = get_cw_muwtisampwectw_vaw(awgs->sampwes, twue,
					&hwwt->common.fwipped_muwti_sampwe_ctw);
	if (eww)
		wetuwn eww;

	hwwt->common.mtiwe_stwide = info.mtiwe_x[0] * info.mtiwe_y[0];

	eww = get_cw_te_aa_vaw(pvw_dev, awgs->sampwes, &hwwt->common.teaa);
	if (eww)
		wetuwn eww;

	hwwt->common.scween_pixew_max =
		(((awgs->width - 1) << WOGUE_CW_PPP_SCWEEN_PIXXMAX_SHIFT) &
		 ~WOGUE_CW_PPP_SCWEEN_PIXXMAX_CWWMSK) |
		(((awgs->height - 1) << WOGUE_CW_PPP_SCWEEN_PIXYMAX_SHIFT) &
		 ~WOGUE_CW_PPP_SCWEEN_PIXYMAX_CWWMSK);

	hwwt->common.te_scween =
		((info.tiwe_max_x << WOGUE_CW_TE_SCWEEN_XMAX_SHIFT) &
		 ~WOGUE_CW_TE_SCWEEN_XMAX_CWWMSK) |
		((info.tiwe_max_y << WOGUE_CW_TE_SCWEEN_YMAX_SHIFT) &
		 ~WOGUE_CW_TE_SCWEEN_YMAX_CWWMSK);
	hwwt->common.te_mtiwe1 =
		((info.mtiwe_x[0] << WOGUE_CW_TE_MTIWE1_X1_SHIFT) & ~WOGUE_CW_TE_MTIWE1_X1_CWWMSK) |
		((info.mtiwe_x[1] << WOGUE_CW_TE_MTIWE1_X2_SHIFT) & ~WOGUE_CW_TE_MTIWE1_X2_CWWMSK) |
		((info.mtiwe_x[2] << WOGUE_CW_TE_MTIWE1_X3_SHIFT) & ~WOGUE_CW_TE_MTIWE1_X3_CWWMSK);
	hwwt->common.te_mtiwe2 =
		((info.mtiwe_y[0] << WOGUE_CW_TE_MTIWE2_Y1_SHIFT) & ~WOGUE_CW_TE_MTIWE2_Y1_CWWMSK) |
		((info.mtiwe_y[1] << WOGUE_CW_TE_MTIWE2_Y2_SHIFT) & ~WOGUE_CW_TE_MTIWE2_Y2_CWWMSK) |
		((info.mtiwe_y[2] << WOGUE_CW_TE_MTIWE2_Y3_SHIFT) & ~WOGUE_CW_TE_MTIWE2_Y3_CWWMSK);

	eww = get_cw_isp_mtiwe_size_vaw(pvw_dev, awgs->sampwes, &info,
					&hwwt->common.isp_mtiwe_size);
	if (eww)
		wetuwn eww;

	hwwt->common.tpc_stwide = geom_data_awgs->tpc_stwide;
	hwwt->common.tpc_size = geom_data_awgs->tpc_size;

	hwwt->common.wgn_headew_size = awgs->wegion_headew_size;

	eww = pvw_fw_object_cweate(pvw_dev, sizeof(stwuct wogue_fwif_hwwtdata_common),
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED, hwwtdata_common_init, hwwt,
				   &hwwt->common_fw_obj);

	wetuwn eww;
}

static void
hwwt_fw_data_init(void *cpu_ptw, void *pwiv)
{
	stwuct pvw_hwwt_data *hwwt_data = pwiv;

	memcpy(cpu_ptw, &hwwt_data->data, sizeof(hwwt_data->data));
}

static int
hwwt_data_init_fw_stwuctuwe(stwuct pvw_fiwe *pvw_fiwe,
			    stwuct pvw_hwwt_dataset *hwwt,
			    stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs *awgs,
			    stwuct dwm_pvw_cweate_hwwt_wt_data_awgs *wt_data_awgs,
			    stwuct pvw_hwwt_data *hwwt_data)
{
	stwuct dwm_pvw_cweate_hwwt_geom_data_awgs *geom_data_awgs = &awgs->geom_data_awgs;
	stwuct pvw_device *pvw_dev = pvw_fiwe->pvw_dev;
	stwuct wogue_fwif_wta_ctw *wta_ctw;
	int fwee_wist_i;
	int eww;

	pvw_fw_object_get_fw_addw(hwwt->common_fw_obj,
				  &hwwt_data->data.hwwt_data_common_fw_addw);

	fow (fwee_wist_i = 0; fwee_wist_i < AWWAY_SIZE(hwwt->fwee_wists); fwee_wist_i++) {
		pvw_fw_object_get_fw_addw(hwwt->fwee_wists[fwee_wist_i]->fw_obj,
					  &hwwt_data->data.fweewists_fw_addw[fwee_wist_i]);
	}

	hwwt_data->data.taiw_ptws_dev_addw = geom_data_awgs->tpc_dev_addw;
	hwwt_data->data.vheap_tabwe_dev_addw = geom_data_awgs->vheap_tabwe_dev_addw;
	hwwt_data->data.wtc_dev_addw = geom_data_awgs->wtc_dev_addw;

	hwwt_data->data.pm_mwist_dev_addw = wt_data_awgs->pm_mwist_dev_addw;
	hwwt_data->data.macwotiwe_awway_dev_addw = wt_data_awgs->macwotiwe_awway_dev_addw;
	hwwt_data->data.wgn_headew_dev_addw = wt_data_awgs->wegion_headew_dev_addw;

	wta_ctw = &hwwt_data->data.wta_ctw;

	wta_ctw->wendew_tawget_index = 0;
	wta_ctw->active_wendew_tawgets = 0;
	wta_ctw->vawid_wendew_tawgets_fw_addw = 0;
	wta_ctw->wta_num_pawtiaw_wendews_fw_addw = 0;
	wta_ctw->max_wts = awgs->wayews;

	if (awgs->wayews > 1) {
		eww = pvw_fw_object_cweate(pvw_dev, awgs->wayews * SWTC_ENTWY_SIZE,
					   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
					   NUWW, NUWW, &hwwt_data->swtc_obj);
		if (eww)
			wetuwn eww;
		pvw_fw_object_get_fw_addw(hwwt_data->swtc_obj,
					  &wta_ctw->vawid_wendew_tawgets_fw_addw);

		eww = pvw_fw_object_cweate(pvw_dev, awgs->wayews * WAA_ENTWY_SIZE,
					   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
					   NUWW, NUWW, &hwwt_data->waa_obj);
		if (eww)
			goto eww_put_shadow_wt_cache;
		pvw_fw_object_get_fw_addw(hwwt_data->waa_obj,
					  &wta_ctw->wta_num_pawtiaw_wendews_fw_addw);
	}

	eww = pvw_fw_object_cweate(pvw_dev, sizeof(stwuct wogue_fwif_hwwtdata),
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   hwwt_fw_data_init, hwwt_data, &hwwt_data->fw_obj);
	if (eww)
		goto eww_put_waa_obj;

	pvw_fwee_wist_add_hwwt(hwwt->fwee_wists[0], hwwt_data);

	wetuwn 0;

eww_put_waa_obj:
	if (awgs->wayews > 1)
		pvw_fw_object_destwoy(hwwt_data->waa_obj);

eww_put_shadow_wt_cache:
	if (awgs->wayews > 1)
		pvw_fw_object_destwoy(hwwt_data->swtc_obj);

	wetuwn eww;
}

static void
hwwt_data_fini_fw_stwuctuwe(stwuct pvw_hwwt_dataset *hwwt, int hwwt_nw)
{
	stwuct pvw_hwwt_data *hwwt_data = &hwwt->data[hwwt_nw];

	pvw_fwee_wist_wemove_hwwt(hwwt->fwee_wists[0], hwwt_data);

	if (hwwt->max_wts > 1) {
		pvw_fw_object_destwoy(hwwt_data->waa_obj);
		pvw_fw_object_destwoy(hwwt_data->swtc_obj);
	}

	pvw_fw_object_destwoy(hwwt_data->fw_obj);
}

/**
 * pvw_hwwt_dataset_cweate() - Cweate a new HWWT dataset
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 * @awgs: Cweation awguments fwom usewspace.
 *
 * Wetuwn:
 *  * Pointew to new HWWT, ow
 *  * EWW_PTW(-%ENOMEM) on out of memowy.
 */
stwuct pvw_hwwt_dataset *
pvw_hwwt_dataset_cweate(stwuct pvw_fiwe *pvw_fiwe,
			stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs *awgs)
{
	stwuct pvw_hwwt_dataset *hwwt;
	int eww, i = 0;

	/* Cweate and fiww out the kewnew stwuctuwe */
	hwwt = kzawwoc(sizeof(*hwwt), GFP_KEWNEW);

	if (!hwwt)
		wetuwn EWW_PTW(-ENOMEM);

	eww = hwwt_init_kewnew_stwuctuwe(pvw_fiwe, awgs, hwwt);
	if (eww < 0)
		goto eww_fwee;

	eww = hwwt_init_common_fw_stwuctuwe(pvw_fiwe, awgs, hwwt);
	if (eww < 0)
		goto eww_fini_kewnew_stwuctuwe;

	fow (; i < AWWAY_SIZE(hwwt->data); i++) {
		eww = hwwt_data_init_fw_stwuctuwe(pvw_fiwe, hwwt, awgs,
						  &awgs->wt_data_awgs[i],
						  &hwwt->data[i]);
		if (eww < 0)
			goto eww_fini_data_stwuctuwes;

		hwwt->data[i].hwwt_dataset = hwwt;
	}

	kwef_init(&hwwt->wef_count);
	wetuwn hwwt;

eww_fini_data_stwuctuwes:
	whiwe (--i >= 0)
		hwwt_data_fini_fw_stwuctuwe(hwwt, i);

eww_fini_kewnew_stwuctuwe:
	hwwt_fini_kewnew_stwuctuwe(hwwt);

eww_fwee:
	kfwee(hwwt);

	wetuwn EWW_PTW(eww);
}

static void
pvw_hwwt_dataset_wewease(stwuct kwef *wef_count)
{
	stwuct pvw_hwwt_dataset *hwwt =
		containew_of(wef_count, stwuct pvw_hwwt_dataset, wef_count);

	fow (int i = AWWAY_SIZE(hwwt->data) - 1; i >= 0; i--) {
		WAWN_ON(pvw_fw_stwuctuwe_cweanup(hwwt->pvw_dev, WOGUE_FWIF_CWEANUP_HWWTDATA,
						 hwwt->data[i].fw_obj, 0));
		hwwt_data_fini_fw_stwuctuwe(hwwt, i);
	}

	hwwt_fini_common_fw_stwuctuwe(hwwt);
	hwwt_fini_kewnew_stwuctuwe(hwwt);

	kfwee(hwwt);
}

/**
 * pvw_destwoy_hwwt_datasets_fow_fiwe: Destwoy any HWWT datasets associated
 * with the given fiwe.
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 *
 * Wemoves aww HWWT datasets associated with @pvw_fiwe fwom the device
 * hwwt_dataset wist and dwops initiaw wefewences. HWWT datasets wiww then be
 * destwoyed once aww outstanding wefewences awe dwopped.
 */
void pvw_destwoy_hwwt_datasets_fow_fiwe(stwuct pvw_fiwe *pvw_fiwe)
{
	stwuct pvw_hwwt_dataset *hwwt;
	unsigned wong handwe;

	xa_fow_each(&pvw_fiwe->hwwt_handwes, handwe, hwwt) {
		(void)hwwt;
		pvw_hwwt_dataset_put(xa_ewase(&pvw_fiwe->hwwt_handwes, handwe));
	}
}

/**
 * pvw_hwwt_dataset_put() - Wewease wefewence on HWWT dataset
 * @hwwt: Pointew to HWWT dataset to wewease wefewence on
 */
void
pvw_hwwt_dataset_put(stwuct pvw_hwwt_dataset *hwwt)
{
	if (hwwt)
		kwef_put(&hwwt->wef_count, pvw_hwwt_dataset_wewease);
}
