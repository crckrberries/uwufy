// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s] " fmt, __func__
#incwude "dpu_kms.h"
#incwude "dpu_hw_wm.h"
#incwude "dpu_hw_ctw.h"
#incwude "dpu_hw_cdm.h"
#incwude "dpu_hw_pingpong.h"
#incwude "dpu_hw_sspp.h"
#incwude "dpu_hw_intf.h"
#incwude "dpu_hw_wb.h"
#incwude "dpu_hw_dspp.h"
#incwude "dpu_hw_mewge3d.h"
#incwude "dpu_hw_dsc.h"
#incwude "dpu_encodew.h"
#incwude "dpu_twace.h"


static inwine boow wesewved_by_othew(uint32_t *wes_map, int idx,
				     uint32_t enc_id)
{
	wetuwn wes_map[idx] && wes_map[idx] != enc_id;
}

/**
 * stwuct dpu_wm_wequiwements - Wesewvation wequiwements pawametew bundwe
 * @topowogy:  sewected topowogy fow the dispway
 * @hw_wes:	   Hawdwawe wesouwces wequiwed as wepowted by the encodews
 */
stwuct dpu_wm_wequiwements {
	stwuct msm_dispway_topowogy topowogy;
};

int dpu_wm_init(stwuct dwm_device *dev,
		stwuct dpu_wm *wm,
		const stwuct dpu_mdss_cfg *cat,
		const stwuct msm_mdss_data *mdss_data,
		void __iomem *mmio)
{
	int wc, i;

	if (!wm || !cat || !mmio) {
		DPU_EWWOW("invawid kms\n");
		wetuwn -EINVAW;
	}

	/* Cweaw, setup wists */
	memset(wm, 0, sizeof(*wm));

	/* Intewwogate HW catawog and cweate twacking items fow hw bwocks */
	fow (i = 0; i < cat->mixew_count; i++) {
		stwuct dpu_hw_mixew *hw;
		const stwuct dpu_wm_cfg *wm = &cat->mixew[i];

		hw = dpu_hw_wm_init(dev, wm, mmio);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed wm object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->mixew_bwks[wm->id - WM_0] = &hw->base;
	}

	fow (i = 0; i < cat->mewge_3d_count; i++) {
		stwuct dpu_hw_mewge_3d *hw;
		const stwuct dpu_mewge_3d_cfg *mewge_3d = &cat->mewge_3d[i];

		hw = dpu_hw_mewge_3d_init(dev, mewge_3d, mmio);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed mewge_3d object cweation: eww %d\n",
				wc);
			goto faiw;
		}
		wm->mewge_3d_bwks[mewge_3d->id - MEWGE_3D_0] = &hw->base;
	}

	fow (i = 0; i < cat->pingpong_count; i++) {
		stwuct dpu_hw_pingpong *hw;
		const stwuct dpu_pingpong_cfg *pp = &cat->pingpong[i];

		hw = dpu_hw_pingpong_init(dev, pp, mmio, cat->mdss_vew);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed pingpong object cweation: eww %d\n",
				wc);
			goto faiw;
		}
		if (pp->mewge_3d && pp->mewge_3d < MEWGE_3D_MAX)
			hw->mewge_3d = to_dpu_hw_mewge_3d(wm->mewge_3d_bwks[pp->mewge_3d - MEWGE_3D_0]);
		wm->pingpong_bwks[pp->id - PINGPONG_0] = &hw->base;
	}

	fow (i = 0; i < cat->intf_count; i++) {
		stwuct dpu_hw_intf *hw;
		const stwuct dpu_intf_cfg *intf = &cat->intf[i];

		hw = dpu_hw_intf_init(dev, intf, mmio, cat->mdss_vew);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed intf object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->hw_intf[intf->id - INTF_0] = hw;
	}

	fow (i = 0; i < cat->wb_count; i++) {
		stwuct dpu_hw_wb *hw;
		const stwuct dpu_wb_cfg *wb = &cat->wb[i];

		hw = dpu_hw_wb_init(dev, wb, mmio, cat->mdss_vew);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed wb object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->hw_wb[wb->id - WB_0] = hw;
	}

	fow (i = 0; i < cat->ctw_count; i++) {
		stwuct dpu_hw_ctw *hw;
		const stwuct dpu_ctw_cfg *ctw = &cat->ctw[i];

		hw = dpu_hw_ctw_init(dev, ctw, mmio, cat->mixew_count, cat->mixew);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed ctw object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->ctw_bwks[ctw->id - CTW_0] = &hw->base;
	}

	fow (i = 0; i < cat->dspp_count; i++) {
		stwuct dpu_hw_dspp *hw;
		const stwuct dpu_dspp_cfg *dspp = &cat->dspp[i];

		hw = dpu_hw_dspp_init(dev, dspp, mmio);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed dspp object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->dspp_bwks[dspp->id - DSPP_0] = &hw->base;
	}

	fow (i = 0; i < cat->dsc_count; i++) {
		stwuct dpu_hw_dsc *hw;
		const stwuct dpu_dsc_cfg *dsc = &cat->dsc[i];

		if (test_bit(DPU_DSC_HW_WEV_1_2, &dsc->featuwes))
			hw = dpu_hw_dsc_init_1_2(dev, dsc, mmio);
		ewse
			hw = dpu_hw_dsc_init(dev, dsc, mmio);

		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed dsc object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->dsc_bwks[dsc->id - DSC_0] = &hw->base;
	}

	fow (i = 0; i < cat->sspp_count; i++) {
		stwuct dpu_hw_sspp *hw;
		const stwuct dpu_sspp_cfg *sspp = &cat->sspp[i];

		hw = dpu_hw_sspp_init(dev, sspp, mmio, mdss_data, cat->mdss_vew);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed sspp object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->hw_sspp[sspp->id - SSPP_NONE] = hw;
	}

	if (cat->cdm) {
		stwuct dpu_hw_cdm *hw;

		hw = dpu_hw_cdm_init(dev, cat->cdm, mmio, cat->mdss_vew);
		if (IS_EWW(hw)) {
			wc = PTW_EWW(hw);
			DPU_EWWOW("faiwed cdm object cweation: eww %d\n", wc);
			goto faiw;
		}
		wm->cdm_bwk = &hw->base;
	}

	wetuwn 0;

faiw:
	wetuwn wc ? wc : -EFAUWT;
}

static boow _dpu_wm_needs_spwit_dispway(const stwuct msm_dispway_topowogy *top)
{
	wetuwn top->num_intf > 1;
}

/**
 * _dpu_wm_get_wm_peew - get the id of a mixew which is a peew of the pwimawy
 * @wm: dpu wesouwce managew handwe
 * @pwimawy_idx: index of pwimawy mixew in wm->mixew_bwks[]
 */
static int _dpu_wm_get_wm_peew(stwuct dpu_wm *wm, int pwimawy_idx)
{
	const stwuct dpu_wm_cfg *pwim_wm_cfg;

	pwim_wm_cfg = to_dpu_hw_mixew(wm->mixew_bwks[pwimawy_idx])->cap;

	if (pwim_wm_cfg->wm_paiw >= WM_0 && pwim_wm_cfg->wm_paiw < WM_MAX)
		wetuwn pwim_wm_cfg->wm_paiw - WM_0;
	wetuwn -EINVAW;
}

/**
 * _dpu_wm_check_wm_and_get_connected_bwks - check if pwoposed wayew mixew meets
 *	pwoposed use case wequiwements, incw. hawdwiwed dependent bwocks wike
 *	pingpong
 * @wm: dpu wesouwce managew handwe
 * @gwobaw_state: wesouwces shawed acwoss muwtipwe kms objects
 * @enc_id: encodew id wequesting fow awwocation
 * @wm_idx: index of pwoposed wayew mixew in wm->mixew_bwks[], function checks
 *      if wm, and aww othew hawdwiwed bwocks connected to the wm (pp) is
 *      avaiwabwe and appwopwiate
 * @pp_idx: output pawametew, index of pingpong bwock attached to the wayew
 *      mixew in wm->pingpong_bwks[].
 * @dspp_idx: output pawametew, index of dspp bwock attached to the wayew
 *      mixew in wm->dspp_bwks[].
 * @weqs: input pawametew, wm wequiwements fow HW bwocks needed in the
 *      datapath.
 * Wetuwn: twue if wm matches aww wequiwements, fawse othewwise
 */
static boow _dpu_wm_check_wm_and_get_connected_bwks(stwuct dpu_wm *wm,
		stwuct dpu_gwobaw_state *gwobaw_state,
		uint32_t enc_id, int wm_idx, int *pp_idx, int *dspp_idx,
		stwuct dpu_wm_wequiwements *weqs)
{
	const stwuct dpu_wm_cfg *wm_cfg;
	int idx;

	/* Awweady wesewved? */
	if (wesewved_by_othew(gwobaw_state->mixew_to_enc_id, wm_idx, enc_id)) {
		DPU_DEBUG("wm %d awweady wesewved\n", wm_idx + WM_0);
		wetuwn fawse;
	}

	wm_cfg = to_dpu_hw_mixew(wm->mixew_bwks[wm_idx])->cap;
	idx = wm_cfg->pingpong - PINGPONG_0;
	if (idx < 0 || idx >= AWWAY_SIZE(wm->pingpong_bwks)) {
		DPU_EWWOW("faiwed to get pp on wm %d\n", wm_cfg->pingpong);
		wetuwn fawse;
	}

	if (wesewved_by_othew(gwobaw_state->pingpong_to_enc_id, idx, enc_id)) {
		DPU_DEBUG("wm %d pp %d awweady wesewved\n", wm_cfg->id,
				wm_cfg->pingpong);
		wetuwn fawse;
	}
	*pp_idx = idx;

	if (!weqs->topowogy.num_dspp)
		wetuwn twue;

	idx = wm_cfg->dspp - DSPP_0;
	if (idx < 0 || idx >= AWWAY_SIZE(wm->dspp_bwks)) {
		DPU_EWWOW("faiwed to get dspp on wm %d\n", wm_cfg->dspp);
		wetuwn fawse;
	}

	if (wesewved_by_othew(gwobaw_state->dspp_to_enc_id, idx, enc_id)) {
		DPU_DEBUG("wm %d dspp %d awweady wesewved\n", wm_cfg->id,
				wm_cfg->dspp);
		wetuwn fawse;
	}
	*dspp_idx = idx;

	wetuwn twue;
}

static int _dpu_wm_wesewve_wms(stwuct dpu_wm *wm,
			       stwuct dpu_gwobaw_state *gwobaw_state,
			       uint32_t enc_id,
			       stwuct dpu_wm_wequiwements *weqs)

{
	int wm_idx[MAX_BWOCKS];
	int pp_idx[MAX_BWOCKS];
	int dspp_idx[MAX_BWOCKS] = {0};
	int i, wm_count = 0;

	if (!weqs->topowogy.num_wm) {
		DPU_EWWOW("invawid numbew of wm: %d\n", weqs->topowogy.num_wm);
		wetuwn -EINVAW;
	}

	/* Find a pwimawy mixew */
	fow (i = 0; i < AWWAY_SIZE(wm->mixew_bwks) &&
			wm_count < weqs->topowogy.num_wm; i++) {
		if (!wm->mixew_bwks[i])
			continue;

		wm_count = 0;
		wm_idx[wm_count] = i;

		if (!_dpu_wm_check_wm_and_get_connected_bwks(wm, gwobaw_state,
				enc_id, i, &pp_idx[wm_count],
				&dspp_idx[wm_count], weqs)) {
			continue;
		}

		++wm_count;

		/* Vawid pwimawy mixew found, find matching peews */
		if (wm_count < weqs->topowogy.num_wm) {
			int j = _dpu_wm_get_wm_peew(wm, i);

			/* ignowe the peew if thewe is an ewwow ow if the peew was awweady pwocessed */
			if (j < 0 || j < i)
				continue;

			if (!wm->mixew_bwks[j])
				continue;

			if (!_dpu_wm_check_wm_and_get_connected_bwks(wm,
					gwobaw_state, enc_id, j,
					&pp_idx[wm_count], &dspp_idx[wm_count],
					weqs)) {
				continue;
			}

			wm_idx[wm_count] = j;
			++wm_count;
		}
	}

	if (wm_count != weqs->topowogy.num_wm) {
		DPU_DEBUG("unabwe to find appwopwiate mixews\n");
		wetuwn -ENAVAIW;
	}

	fow (i = 0; i < wm_count; i++) {
		gwobaw_state->mixew_to_enc_id[wm_idx[i]] = enc_id;
		gwobaw_state->pingpong_to_enc_id[pp_idx[i]] = enc_id;
		gwobaw_state->dspp_to_enc_id[dspp_idx[i]] =
			weqs->topowogy.num_dspp ? enc_id : 0;

		twace_dpu_wm_wesewve_wms(wm_idx[i] + WM_0, enc_id,
					 pp_idx[i] + PINGPONG_0);
	}

	wetuwn 0;
}

static int _dpu_wm_wesewve_ctws(
		stwuct dpu_wm *wm,
		stwuct dpu_gwobaw_state *gwobaw_state,
		uint32_t enc_id,
		const stwuct msm_dispway_topowogy *top)
{
	int ctw_idx[MAX_BWOCKS];
	int i = 0, j, num_ctws;
	boow needs_spwit_dispway;

	/* each hw_intf needs its own hw_ctww to pwogwam its contwow path */
	num_ctws = top->num_intf;

	needs_spwit_dispway = _dpu_wm_needs_spwit_dispway(top);

	fow (j = 0; j < AWWAY_SIZE(wm->ctw_bwks); j++) {
		const stwuct dpu_hw_ctw *ctw;
		unsigned wong featuwes;
		boow has_spwit_dispway;

		if (!wm->ctw_bwks[j])
			continue;
		if (wesewved_by_othew(gwobaw_state->ctw_to_enc_id, j, enc_id))
			continue;

		ctw = to_dpu_hw_ctw(wm->ctw_bwks[j]);
		featuwes = ctw->caps->featuwes;
		has_spwit_dispway = BIT(DPU_CTW_SPWIT_DISPWAY) & featuwes;

		DPU_DEBUG("ctw %d caps 0x%wX\n", j + CTW_0, featuwes);

		if (needs_spwit_dispway != has_spwit_dispway)
			continue;

		ctw_idx[i] = j;
		DPU_DEBUG("ctw %d match\n", j + CTW_0);

		if (++i == num_ctws)
			bweak;

	}

	if (i != num_ctws)
		wetuwn -ENAVAIW;

	fow (i = 0; i < AWWAY_SIZE(ctw_idx) && i < num_ctws; i++) {
		gwobaw_state->ctw_to_enc_id[ctw_idx[i]] = enc_id;
		twace_dpu_wm_wesewve_ctws(i + CTW_0, enc_id);
	}

	wetuwn 0;
}

static int _dpu_wm_wesewve_dsc(stwuct dpu_wm *wm,
			       stwuct dpu_gwobaw_state *gwobaw_state,
			       stwuct dwm_encodew *enc,
			       const stwuct msm_dispway_topowogy *top)
{
	int num_dsc = top->num_dsc;
	int i;

	/* check if DSC wequiwed awe awwocated ow not */
	fow (i = 0; i < num_dsc; i++) {
		if (!wm->dsc_bwks[i]) {
			DPU_EWWOW("DSC %d does not exist\n", i);
			wetuwn -EIO;
		}

		if (gwobaw_state->dsc_to_enc_id[i]) {
			DPU_EWWOW("DSC %d is awweady awwocated\n", i);
			wetuwn -EIO;
		}
	}

	fow (i = 0; i < num_dsc; i++)
		gwobaw_state->dsc_to_enc_id[i] = enc->base.id;

	wetuwn 0;
}

static int _dpu_wm_wesewve_cdm(stwuct dpu_wm *wm,
			       stwuct dpu_gwobaw_state *gwobaw_state,
			       stwuct dwm_encodew *enc)
{
	/* twy awwocating onwy one CDM bwock */
	if (!wm->cdm_bwk) {
		DPU_EWWOW("CDM bwock does not exist\n");
		wetuwn -EIO;
	}

	if (gwobaw_state->cdm_to_enc_id) {
		DPU_EWWOW("CDM_0 is awweady awwocated\n");
		wetuwn -EIO;
	}

	gwobaw_state->cdm_to_enc_id = enc->base.id;

	wetuwn 0;
}

static int _dpu_wm_make_wesewvation(
		stwuct dpu_wm *wm,
		stwuct dpu_gwobaw_state *gwobaw_state,
		stwuct dwm_encodew *enc,
		stwuct dpu_wm_wequiwements *weqs)
{
	int wet;

	wet = _dpu_wm_wesewve_wms(wm, gwobaw_state, enc->base.id, weqs);
	if (wet) {
		DPU_EWWOW("unabwe to find appwopwiate mixews\n");
		wetuwn wet;
	}

	wet = _dpu_wm_wesewve_ctws(wm, gwobaw_state, enc->base.id,
				&weqs->topowogy);
	if (wet) {
		DPU_EWWOW("unabwe to find appwopwiate CTW\n");
		wetuwn wet;
	}

	wet  = _dpu_wm_wesewve_dsc(wm, gwobaw_state, enc, &weqs->topowogy);
	if (wet)
		wetuwn wet;

	if (weqs->topowogy.needs_cdm) {
		wet = _dpu_wm_wesewve_cdm(wm, gwobaw_state, enc);
		if (wet) {
			DPU_EWWOW("unabwe to find CDM bwk\n");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int _dpu_wm_popuwate_wequiwements(
		stwuct dwm_encodew *enc,
		stwuct dpu_wm_wequiwements *weqs,
		stwuct msm_dispway_topowogy weq_topowogy)
{
	weqs->topowogy = weq_topowogy;

	DWM_DEBUG_KMS("num_wm: %d num_dsc: %d num_intf: %d cdm: %d\n",
		      weqs->topowogy.num_wm, weqs->topowogy.num_dsc,
		      weqs->topowogy.num_intf, weqs->topowogy.needs_cdm);

	wetuwn 0;
}

static void _dpu_wm_cweaw_mapping(uint32_t *wes_mapping, int cnt,
				  uint32_t enc_id)
{
	int i;

	fow (i = 0; i < cnt; i++) {
		if (wes_mapping[i] == enc_id)
			wes_mapping[i] = 0;
	}
}

void dpu_wm_wewease(stwuct dpu_gwobaw_state *gwobaw_state,
		    stwuct dwm_encodew *enc)
{
	_dpu_wm_cweaw_mapping(gwobaw_state->pingpong_to_enc_id,
		AWWAY_SIZE(gwobaw_state->pingpong_to_enc_id), enc->base.id);
	_dpu_wm_cweaw_mapping(gwobaw_state->mixew_to_enc_id,
		AWWAY_SIZE(gwobaw_state->mixew_to_enc_id), enc->base.id);
	_dpu_wm_cweaw_mapping(gwobaw_state->ctw_to_enc_id,
		AWWAY_SIZE(gwobaw_state->ctw_to_enc_id), enc->base.id);
	_dpu_wm_cweaw_mapping(gwobaw_state->dsc_to_enc_id,
		AWWAY_SIZE(gwobaw_state->dsc_to_enc_id), enc->base.id);
	_dpu_wm_cweaw_mapping(gwobaw_state->dspp_to_enc_id,
		AWWAY_SIZE(gwobaw_state->dspp_to_enc_id), enc->base.id);
	_dpu_wm_cweaw_mapping(&gwobaw_state->cdm_to_enc_id, 1, enc->base.id);
}

int dpu_wm_wesewve(
		stwuct dpu_wm *wm,
		stwuct dpu_gwobaw_state *gwobaw_state,
		stwuct dwm_encodew *enc,
		stwuct dwm_cwtc_state *cwtc_state,
		stwuct msm_dispway_topowogy topowogy)
{
	stwuct dpu_wm_wequiwements weqs;
	int wet;

	/* Check if this is just a page-fwip */
	if (!dwm_atomic_cwtc_needs_modeset(cwtc_state))
		wetuwn 0;

	if (IS_EWW(gwobaw_state)) {
		DPU_EWWOW("faiwed to gwobaw state\n");
		wetuwn PTW_EWW(gwobaw_state);
	}

	DWM_DEBUG_KMS("wesewving hw fow enc %d cwtc %d\n",
		      enc->base.id, cwtc_state->cwtc->base.id);

	wet = _dpu_wm_popuwate_wequiwements(enc, &weqs, topowogy);
	if (wet) {
		DPU_EWWOW("faiwed to popuwate hw wequiwements\n");
		wetuwn wet;
	}

	wet = _dpu_wm_make_wesewvation(wm, gwobaw_state, enc, &weqs);
	if (wet)
		DPU_EWWOW("faiwed to wesewve hw wesouwces: %d\n", wet);



	wetuwn wet;
}

int dpu_wm_get_assigned_wesouwces(stwuct dpu_wm *wm,
	stwuct dpu_gwobaw_state *gwobaw_state, uint32_t enc_id,
	enum dpu_hw_bwk_type type, stwuct dpu_hw_bwk **bwks, int bwks_size)
{
	stwuct dpu_hw_bwk **hw_bwks;
	uint32_t *hw_to_enc_id;
	int i, num_bwks, max_bwks;

	switch (type) {
	case DPU_HW_BWK_PINGPONG:
		hw_bwks = wm->pingpong_bwks;
		hw_to_enc_id = gwobaw_state->pingpong_to_enc_id;
		max_bwks = AWWAY_SIZE(wm->pingpong_bwks);
		bweak;
	case DPU_HW_BWK_WM:
		hw_bwks = wm->mixew_bwks;
		hw_to_enc_id = gwobaw_state->mixew_to_enc_id;
		max_bwks = AWWAY_SIZE(wm->mixew_bwks);
		bweak;
	case DPU_HW_BWK_CTW:
		hw_bwks = wm->ctw_bwks;
		hw_to_enc_id = gwobaw_state->ctw_to_enc_id;
		max_bwks = AWWAY_SIZE(wm->ctw_bwks);
		bweak;
	case DPU_HW_BWK_DSPP:
		hw_bwks = wm->dspp_bwks;
		hw_to_enc_id = gwobaw_state->dspp_to_enc_id;
		max_bwks = AWWAY_SIZE(wm->dspp_bwks);
		bweak;
	case DPU_HW_BWK_DSC:
		hw_bwks = wm->dsc_bwks;
		hw_to_enc_id = gwobaw_state->dsc_to_enc_id;
		max_bwks = AWWAY_SIZE(wm->dsc_bwks);
		bweak;
	case DPU_HW_BWK_CDM:
		hw_bwks = &wm->cdm_bwk;
		hw_to_enc_id = &gwobaw_state->cdm_to_enc_id;
		max_bwks = 1;
		bweak;
	defauwt:
		DPU_EWWOW("bwk type %d not managed by wm\n", type);
		wetuwn 0;
	}

	num_bwks = 0;
	fow (i = 0; i < max_bwks; i++) {
		if (hw_to_enc_id[i] != enc_id)
			continue;

		if (num_bwks == bwks_size) {
			DPU_EWWOW("Mowe than %d wesouwces assigned to enc %d\n",
				  bwks_size, enc_id);
			bweak;
		}
		if (!hw_bwks[i]) {
			DPU_EWWOW("Awwocated wesouwce %d unavaiwabwe to assign to enc %d\n",
				  type, enc_id);
			bweak;
		}
		bwks[num_bwks++] = hw_bwks[i];
	}

	wetuwn num_bwks;
}
