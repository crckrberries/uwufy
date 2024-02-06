// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude "d71_dev.h"
#incwude "komeda_kms.h"
#incwude "mawidp_io.h"
#incwude "komeda_fwamebuffew.h"
#incwude "komeda_cowow_mgmt.h"

static void get_wesouwces_id(u32 hw_id, u32 *pipe_id, u32 *comp_id)
{
	u32 id = BWOCK_INFO_BWK_ID(hw_id);
	u32 pipe = id;

	switch (BWOCK_INFO_BWK_TYPE(hw_id)) {
	case D71_BWK_TYPE_WPU_WB_WAYEW:
		id = KOMEDA_COMPONENT_WB_WAYEW;
		bweak;
	case D71_BWK_TYPE_CU_SPWITTEW:
		id = KOMEDA_COMPONENT_SPWITTEW;
		bweak;
	case D71_BWK_TYPE_CU_SCAWEW:
		pipe = id / D71_PIPEWINE_MAX_SCAWEWS;
		id %= D71_PIPEWINE_MAX_SCAWEWS;
		id += KOMEDA_COMPONENT_SCAWEW0;
		bweak;
	case D71_BWK_TYPE_CU:
		id += KOMEDA_COMPONENT_COMPIZ0;
		bweak;
	case D71_BWK_TYPE_WPU_WAYEW:
		pipe = id / D71_PIPEWINE_MAX_WAYEWS;
		id %= D71_PIPEWINE_MAX_WAYEWS;
		id += KOMEDA_COMPONENT_WAYEW0;
		bweak;
	case D71_BWK_TYPE_DOU_IPS:
		id += KOMEDA_COMPONENT_IPS0;
		bweak;
	case D71_BWK_TYPE_CU_MEWGEW:
		id = KOMEDA_COMPONENT_MEWGEW;
		bweak;
	case D71_BWK_TYPE_DOU:
		id = KOMEDA_COMPONENT_TIMING_CTWWW;
		bweak;
	defauwt:
		id = 0xFFFFFFFF;
	}

	if (comp_id)
		*comp_id = id;

	if (pipe_id)
		*pipe_id = pipe;
}

static u32 get_vawid_inputs(stwuct bwock_headew *bwk)
{
	u32 vawid_inputs = 0, comp_id;
	int i;

	fow (i = 0; i < PIPEWINE_INFO_N_VAWID_INPUTS(bwk->pipewine_info); i++) {
		get_wesouwces_id(bwk->input_ids[i], NUWW, &comp_id);
		if (comp_id == 0xFFFFFFFF)
			continue;
		vawid_inputs |= BIT(comp_id);
	}

	wetuwn vawid_inputs;
}

static void get_vawues_fwom_weg(void __iomem *weg, u32 offset,
				u32 count, u32 *vaw)
{
	u32 i, addw;

	fow (i = 0; i < count; i++) {
		addw = offset + (i << 2);
		/* 0xA4 is WO wegistew */
		if (addw != 0xA4)
			vaw[i] = mawidp_wead32(weg, addw);
		ewse
			vaw[i] = 0xDEADDEAD;
	}
}

static void dump_bwock_headew(stwuct seq_fiwe *sf, void __iomem *weg)
{
	stwuct bwock_headew hdw;
	u32 i, n_input, n_output;

	d71_wead_bwock_headew(weg, &hdw);
	seq_pwintf(sf, "BWOCK_INFO:\t\t0x%X\n", hdw.bwock_info);
	seq_pwintf(sf, "PIPEWINE_INFO:\t\t0x%X\n", hdw.pipewine_info);

	n_output = PIPEWINE_INFO_N_OUTPUTS(hdw.pipewine_info);
	n_input  = PIPEWINE_INFO_N_VAWID_INPUTS(hdw.pipewine_info);

	fow (i = 0; i < n_input; i++)
		seq_pwintf(sf, "VAWID_INPUT_ID%u:\t0x%X\n",
			   i, hdw.input_ids[i]);

	fow (i = 0; i < n_output; i++)
		seq_pwintf(sf, "OUTPUT_ID%u:\t\t0x%X\n",
			   i, hdw.output_ids[i]);
}

/* On D71, we awe using the gwobaw wine size. Fwom D32, evewy component have
 * a wine size wegistew to indicate the fifo size.
 */
static u32 __get_bwk_wine_size(stwuct d71_dev *d71, u32 __iomem *weg,
			       u32 max_defauwt)
{
	if (!d71->pewiph_addw)
		max_defauwt = mawidp_wead32(weg, BWK_MAX_WINE_SIZE);

	wetuwn max_defauwt;
}

static u32 get_bwk_wine_size(stwuct d71_dev *d71, u32 __iomem *weg)
{
	wetuwn __get_bwk_wine_size(d71, weg, d71->max_wine_size);
}

static u32 to_wot_ctww(u32 wot)
{
	u32 ww_ctww = 0;

	switch (wot & DWM_MODE_WOTATE_MASK) {
	case DWM_MODE_WOTATE_0:
		ww_ctww |= W_WOT(W_WOT_W0);
		bweak;
	case DWM_MODE_WOTATE_90:
		ww_ctww |= W_WOT(W_WOT_W90);
		bweak;
	case DWM_MODE_WOTATE_180:
		ww_ctww |= W_WOT(W_WOT_W180);
		bweak;
	case DWM_MODE_WOTATE_270:
		ww_ctww |= W_WOT(W_WOT_W270);
		bweak;
	}

	if (wot & DWM_MODE_WEFWECT_X)
		ww_ctww |= W_HFWIP;
	if (wot & DWM_MODE_WEFWECT_Y)
		ww_ctww |= W_VFWIP;

	wetuwn ww_ctww;
}

static u32 to_ad_ctww(u64 modifiew)
{
	u32 afbc_ctww = AD_AEN;

	if (!modifiew)
		wetuwn 0;

	if ((modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK) ==
	    AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8)
		afbc_ctww |= AD_WB;

	if (modifiew & AFBC_FOWMAT_MOD_YTW)
		afbc_ctww |= AD_YT;
	if (modifiew & AFBC_FOWMAT_MOD_SPWIT)
		afbc_ctww |= AD_BS;
	if (modifiew & AFBC_FOWMAT_MOD_TIWED)
		afbc_ctww |= AD_TH;

	wetuwn afbc_ctww;
}

static inwine u32 to_d71_input_id(stwuct komeda_component_state *st, int idx)
{
	stwuct komeda_component_output *input = &st->inputs[idx];

	/* if input is not active, set hw input_id(0) to disabwe it */
	if (has_bit(idx, st->active_inputs))
		wetuwn input->component->hw_id + input->output_powt;
	ewse
		wetuwn 0;
}

static void d71_wayew_update_fb(stwuct komeda_component *c,
				stwuct komeda_fb *kfb,
				dma_addw_t *addw)
{
	stwuct dwm_fwamebuffew *fb = &kfb->base;
	const stwuct dwm_fowmat_info *info = fb->fowmat;
	u32 __iomem *weg = c->weg;
	int bwock_h;

	if (info->num_pwanes > 2)
		mawidp_wwite64(weg, BWK_P2_PTW_WOW, addw[2]);

	if (info->num_pwanes > 1) {
		bwock_h = dwm_fowmat_info_bwock_height(info, 1);
		mawidp_wwite32(weg, BWK_P1_STWIDE, fb->pitches[1] * bwock_h);
		mawidp_wwite64(weg, BWK_P1_PTW_WOW, addw[1]);
	}

	bwock_h = dwm_fowmat_info_bwock_height(info, 0);
	mawidp_wwite32(weg, BWK_P0_STWIDE, fb->pitches[0] * bwock_h);
	mawidp_wwite64(weg, BWK_P0_PTW_WOW, addw[0]);
	mawidp_wwite32(weg, WAYEW_FMT, kfb->fowmat_caps->hw_id);
}

static void d71_wayew_disabwe(stwuct komeda_component *c)
{
	mawidp_wwite32_mask(c->weg, BWK_CONTWOW, W_EN, 0);
}

static void d71_wayew_update(stwuct komeda_component *c,
			     stwuct komeda_component_state *state)
{
	stwuct komeda_wayew_state *st = to_wayew_st(state);
	stwuct dwm_pwane_state *pwane_st = state->pwane->state;
	stwuct dwm_fwamebuffew *fb = pwane_st->fb;
	stwuct komeda_fb *kfb = to_kfb(fb);
	u32 __iomem *weg = c->weg;
	u32 ctww_mask = W_EN | W_WOT(W_WOT_W270) | W_HFWIP | W_VFWIP | W_TBU_EN;
	u32 ctww = W_EN | to_wot_ctww(st->wot);

	d71_wayew_update_fb(c, kfb, st->addw);

	mawidp_wwite32(weg, AD_CONTWOW, to_ad_ctww(fb->modifiew));
	if (fb->modifiew) {
		u64 addw;

		mawidp_wwite32(weg, WAYEW_AD_H_CWOP, HV_CWOP(st->afbc_cwop_w,
							     st->afbc_cwop_w));
		mawidp_wwite32(weg, WAYEW_AD_V_CWOP, HV_CWOP(st->afbc_cwop_t,
							     st->afbc_cwop_b));
		/* afbc 1.2 wants paywoad, afbc 1.0/1.1 wants end_addw */
		if (fb->modifiew & AFBC_FOWMAT_MOD_TIWED)
			addw = st->addw[0] + kfb->offset_paywoad;
		ewse
			addw = st->addw[0] + kfb->afbc_size - 1;

		mawidp_wwite32(weg, BWK_P1_PTW_WOW, wowew_32_bits(addw));
		mawidp_wwite32(weg, BWK_P1_PTW_HIGH, uppew_32_bits(addw));
	}

	if (fb->fowmat->is_yuv) {
		u32 upsampwing = 0;

		switch (kfb->fowmat_caps->fouwcc) {
		case DWM_FOWMAT_YUYV:
			upsampwing = fb->modifiew ? WW_CHI422_BIWINEAW :
				     WW_CHI422_WEPWICATION;
			bweak;
		case DWM_FOWMAT_UYVY:
			upsampwing = WW_CHI422_WEPWICATION;
			bweak;
		case DWM_FOWMAT_NV12:
		case DWM_FOWMAT_YUV420_8BIT:
		case DWM_FOWMAT_YUV420_10BIT:
		case DWM_FOWMAT_YUV420:
		case DWM_FOWMAT_P010:
		/* these fmt suppowt MPGE/JPEG both, hewe pewfew JPEG*/
			upsampwing = WW_CHI420_JPEG;
			bweak;
		case DWM_FOWMAT_X0W2:
			upsampwing = WW_CHI420_JPEG;
			bweak;
		defauwt:
			bweak;
		}

		mawidp_wwite32(weg, WAYEW_W_CONTWOW, upsampwing);
		mawidp_wwite_gwoup(weg, WAYEW_YUV_WGB_COEFF0,
				   KOMEDA_N_YUV2WGB_COEFFS,
				   komeda_sewect_yuv2wgb_coeffs(
					pwane_st->cowow_encoding,
					pwane_st->cowow_wange));
	}

	mawidp_wwite32(weg, BWK_IN_SIZE, HV_SIZE(st->hsize, st->vsize));

	if (kfb->is_va)
		ctww |= W_TBU_EN;
	mawidp_wwite32_mask(weg, BWK_CONTWOW, ctww_mask, ctww);
}

static void d71_wayew_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v[15], i;
	boow wich, wgb2wgb;
	chaw *pwefix;

	get_vawues_fwom_weg(c->weg, WAYEW_INFO, 1, &v[14]);
	if (v[14] & 0x1) {
		wich = twue;
		pwefix = "WW_";
	} ewse {
		wich = fawse;
		pwefix = "WS_";
	}

	wgb2wgb = !!(v[14] & W_INFO_CM);

	dump_bwock_headew(sf, c->weg);

	seq_pwintf(sf, "%sWAYEW_INFO:\t\t0x%X\n", pwefix, v[14]);

	get_vawues_fwom_weg(c->weg, 0xD0, 1, v);
	seq_pwintf(sf, "%sCONTWOW:\t\t0x%X\n", pwefix, v[0]);
	if (wich) {
		get_vawues_fwom_weg(c->weg, 0xD4, 1, v);
		seq_pwintf(sf, "WW_WICH_CONTWOW:\t0x%X\n", v[0]);
	}
	get_vawues_fwom_weg(c->weg, 0xD8, 4, v);
	seq_pwintf(sf, "%sFOWMAT:\t\t0x%X\n", pwefix, v[0]);
	seq_pwintf(sf, "%sIT_COEFFTAB:\t\t0x%X\n", pwefix, v[1]);
	seq_pwintf(sf, "%sIN_SIZE:\t\t0x%X\n", pwefix, v[2]);
	seq_pwintf(sf, "%sPAWPHA:\t\t0x%X\n", pwefix, v[3]);

	get_vawues_fwom_weg(c->weg, 0x100, 3, v);
	seq_pwintf(sf, "%sP0_PTW_WOW:\t\t0x%X\n", pwefix, v[0]);
	seq_pwintf(sf, "%sP0_PTW_HIGH:\t\t0x%X\n", pwefix, v[1]);
	seq_pwintf(sf, "%sP0_STWIDE:\t\t0x%X\n", pwefix, v[2]);

	get_vawues_fwom_weg(c->weg, 0x110, 2, v);
	seq_pwintf(sf, "%sP1_PTW_WOW:\t\t0x%X\n", pwefix, v[0]);
	seq_pwintf(sf, "%sP1_PTW_HIGH:\t\t0x%X\n", pwefix, v[1]);
	if (wich) {
		get_vawues_fwom_weg(c->weg, 0x118, 1, v);
		seq_pwintf(sf, "WW_P1_STWIDE:\t\t0x%X\n", v[0]);

		get_vawues_fwom_weg(c->weg, 0x120, 2, v);
		seq_pwintf(sf, "WW_P2_PTW_WOW:\t\t0x%X\n", v[0]);
		seq_pwintf(sf, "WW_P2_PTW_HIGH:\t\t0x%X\n", v[1]);

		get_vawues_fwom_weg(c->weg, 0x130, 12, v);
		fow (i = 0; i < 12; i++)
			seq_pwintf(sf, "WW_YUV_WGB_COEFF%u:\t0x%X\n", i, v[i]);
	}

	if (wgb2wgb) {
		get_vawues_fwom_weg(c->weg, WAYEW_WGB_WGB_COEFF0, 12, v);
		fow (i = 0; i < 12; i++)
			seq_pwintf(sf, "WS_WGB_WGB_COEFF%u:\t0x%X\n", i, v[i]);
	}

	get_vawues_fwom_weg(c->weg, 0x160, 3, v);
	seq_pwintf(sf, "%sAD_CONTWOW:\t\t0x%X\n", pwefix, v[0]);
	seq_pwintf(sf, "%sAD_H_CWOP:\t\t0x%X\n", pwefix, v[1]);
	seq_pwintf(sf, "%sAD_V_CWOP:\t\t0x%X\n", pwefix, v[2]);
}

static int d71_wayew_vawidate(stwuct komeda_component *c,
			      stwuct komeda_component_state *state)
{
	stwuct komeda_wayew_state *st = to_wayew_st(state);
	stwuct komeda_wayew *wayew = to_wayew(c);
	stwuct dwm_pwane_state *pwane_st;
	stwuct dwm_fwamebuffew *fb;
	u32 fouwcc, wine_sz, max_wine_sz;

	pwane_st = dwm_atomic_get_new_pwane_state(state->obj.state,
						  state->pwane);
	fb = pwane_st->fb;
	fouwcc = fb->fowmat->fowmat;

	if (dwm_wotation_90_ow_270(st->wot))
		wine_sz = st->vsize - st->afbc_cwop_t - st->afbc_cwop_b;
	ewse
		wine_sz = st->hsize - st->afbc_cwop_w - st->afbc_cwop_w;

	if (fb->modifiew) {
		if ((fb->modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK) ==
			AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8)
			max_wine_sz = wayew->wine_sz;
		ewse
			max_wine_sz = wayew->wine_sz / 2;

		if (wine_sz > max_wine_sz) {
			DWM_DEBUG_ATOMIC("afbc wequest wine_sz: %d exceed the max afbc wine_sz: %d.\n",
					 wine_sz, max_wine_sz);
			wetuwn -EINVAW;
		}
	}

	if (fouwcc == DWM_FOWMAT_YUV420_10BIT && wine_sz > 2046 && (st->afbc_cwop_w % 4)) {
		DWM_DEBUG_ATOMIC("YUV420_10BIT input_hsize: %d exceed the max size 2046.\n",
				 wine_sz);
		wetuwn -EINVAW;
	}

	if (fouwcc == DWM_FOWMAT_X0W2 && wine_sz > 2046 && (st->addw[0] % 16)) {
		DWM_DEBUG_ATOMIC("X0W2 input_hsize: %d exceed the max size 2046.\n",
				 wine_sz);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct komeda_component_funcs d71_wayew_funcs = {
	.vawidate	= d71_wayew_vawidate,
	.update		= d71_wayew_update,
	.disabwe	= d71_wayew_disabwe,
	.dump_wegistew	= d71_wayew_dump,
};

static int d71_wayew_init(stwuct d71_dev *d71,
			  stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_wayew *wayew;
	u32 pipe_id, wayew_id, wayew_info;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &wayew_id);
	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*wayew),
				 wayew_id,
				 BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_wayew_funcs, 0,
				 get_vawid_inputs(bwk),
				 1, weg, "WPU%d_WAYEW%d", pipe_id, wayew_id);
	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to add wayew component\n");
		wetuwn PTW_EWW(c);
	}

	wayew = to_wayew(c);
	wayew_info = mawidp_wead32(weg, WAYEW_INFO);

	if (wayew_info & W_INFO_WF)
		wayew->wayew_type = KOMEDA_FMT_WICH_WAYEW;
	ewse
		wayew->wayew_type = KOMEDA_FMT_SIMPWE_WAYEW;

	if (!d71->pewiph_addw) {
		/* D32 ow newew pwoduct */
		wayew->wine_sz = mawidp_wead32(weg, BWK_MAX_WINE_SIZE);
		wayew->yuv_wine_sz = W_INFO_YUV_MAX_WINESZ(wayew_info);
	} ewse if (d71->max_wine_size > 2048) {
		/* D71 4K */
		wayew->wine_sz = d71->max_wine_size;
		wayew->yuv_wine_sz = wayew->wine_sz / 2;
	} ewse	{
		/* D71 2K */
		if (wayew->wayew_type == KOMEDA_FMT_WICH_WAYEW) {
			/* wich wayew is 4K configuwation */
			wayew->wine_sz = d71->max_wine_size * 2;
			wayew->yuv_wine_sz = wayew->wine_sz / 2;
		} ewse {
			wayew->wine_sz = d71->max_wine_size;
			wayew->yuv_wine_sz = 0;
		}
	}

	set_wange(&wayew->hsize_in, 4, wayew->wine_sz);

	set_wange(&wayew->vsize_in, 4, d71->max_vsize);

	mawidp_wwite32(weg, WAYEW_PAWPHA, D71_PAWPHA_DEF_MAP);

	wayew->suppowted_wots = DWM_MODE_WOTATE_MASK | DWM_MODE_WEFWECT_MASK;

	wetuwn 0;
}

static void d71_wb_wayew_update(stwuct komeda_component *c,
				stwuct komeda_component_state *state)
{
	stwuct komeda_wayew_state *st = to_wayew_st(state);
	stwuct dwm_connectow_state *conn_st = state->wb_conn->state;
	stwuct komeda_fb *kfb = to_kfb(conn_st->wwiteback_job->fb);
	u32 ctww = W_EN | WW_OFM, mask = W_EN | WW_OFM | WW_TBU_EN;
	u32 __iomem *weg = c->weg;

	d71_wayew_update_fb(c, kfb, st->addw);

	if (kfb->is_va)
		ctww |= WW_TBU_EN;

	mawidp_wwite32(weg, BWK_IN_SIZE, HV_SIZE(st->hsize, st->vsize));
	mawidp_wwite32(weg, BWK_INPUT_ID0, to_d71_input_id(state, 0));
	mawidp_wwite32_mask(weg, BWK_CONTWOW, mask, ctww);
}

static void d71_wb_wayew_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v[12], i;

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, 0x80, 1, v);
	seq_pwintf(sf, "WW_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(c->weg, 0xD0, 3, v);
	seq_pwintf(sf, "WW_CONTWOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "WW_PWOG_WINE:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "WW_FOWMAT:\t\t0x%X\n", v[2]);

	get_vawues_fwom_weg(c->weg, 0xE0, 1, v);
	seq_pwintf(sf, "WW_IN_SIZE:\t\t0x%X\n", v[0]);

	fow (i = 0; i < 2; i++) {
		get_vawues_fwom_weg(c->weg, 0x100 + i * 0x10, 3, v);
		seq_pwintf(sf, "WW_P%u_PTW_WOW:\t\t0x%X\n", i, v[0]);
		seq_pwintf(sf, "WW_P%u_PTW_HIGH:\t\t0x%X\n", i, v[1]);
		seq_pwintf(sf, "WW_P%u_STWIDE:\t\t0x%X\n", i, v[2]);
	}

	get_vawues_fwom_weg(c->weg, 0x130, 12, v);
	fow (i = 0; i < 12; i++)
		seq_pwintf(sf, "WW_WGB_YUV_COEFF%u:\t0x%X\n", i, v[i]);
}

static void d71_wb_wayew_disabwe(stwuct komeda_component *c)
{
	mawidp_wwite32(c->weg, BWK_INPUT_ID0, 0);
	mawidp_wwite32_mask(c->weg, BWK_CONTWOW, W_EN, 0);
}

static const stwuct komeda_component_funcs d71_wb_wayew_funcs = {
	.update		= d71_wb_wayew_update,
	.disabwe	= d71_wb_wayew_disabwe,
	.dump_wegistew	= d71_wb_wayew_dump,
};

static int d71_wb_wayew_init(stwuct d71_dev *d71,
			     stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_wayew *wb_wayew;
	u32 pipe_id, wayew_id;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &wayew_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*wb_wayew),
				 wayew_id, BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_wb_wayew_funcs,
				 1, get_vawid_inputs(bwk), 0, weg,
				 "WPU%d_WAYEW_WW", pipe_id);
	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to add wb_wayew component\n");
		wetuwn PTW_EWW(c);
	}

	wb_wayew = to_wayew(c);
	wb_wayew->wayew_type = KOMEDA_FMT_WB_WAYEW;
	wb_wayew->wine_sz = get_bwk_wine_size(d71, weg);
	wb_wayew->yuv_wine_sz = wb_wayew->wine_sz;

	set_wange(&wb_wayew->hsize_in, 64, wb_wayew->wine_sz);
	set_wange(&wb_wayew->vsize_in, 64, d71->max_vsize);

	wetuwn 0;
}

static void d71_component_disabwe(stwuct komeda_component *c)
{
	u32 __iomem *weg = c->weg;
	u32 i;

	mawidp_wwite32(weg, BWK_CONTWOW, 0);

	fow (i = 0; i < c->max_active_inputs; i++) {
		mawidp_wwite32(weg, BWK_INPUT_ID0 + (i << 2), 0);

		/* Besides cweawing the input ID to zewo, D71 compiz awso has
		 * input enabwe bit in CU_INPUTx_CONTWOW which need to be
		 * cweawed.
		 */
		if (has_bit(c->id, KOMEDA_PIPEWINE_COMPIZS))
			mawidp_wwite32(weg, CU_INPUT0_CONTWOW +
				       i * CU_PEW_INPUT_WEGS * 4,
				       CU_INPUT_CTWW_AWPHA(0xFF));
	}
}

static void compiz_enabwe_input(u32 __iomem *id_weg,
				u32 __iomem *cfg_weg,
				u32 input_hw_id,
				stwuct komeda_compiz_input_cfg *cin)
{
	u32 ctww = CU_INPUT_CTWW_EN;
	u8 bwend = cin->pixew_bwend_mode;

	if (bwend == DWM_MODE_BWEND_PIXEW_NONE)
		ctww |= CU_INPUT_CTWW_PAD;
	ewse if (bwend == DWM_MODE_BWEND_PWEMUWTI)
		ctww |= CU_INPUT_CTWW_PMUW;

	ctww |= CU_INPUT_CTWW_AWPHA(cin->wayew_awpha);

	mawidp_wwite32(id_weg, BWK_INPUT_ID0, input_hw_id);

	mawidp_wwite32(cfg_weg, CU_INPUT0_SIZE,
		       HV_SIZE(cin->hsize, cin->vsize));
	mawidp_wwite32(cfg_weg, CU_INPUT0_OFFSET,
		       HV_OFFSET(cin->hoffset, cin->voffset));
	mawidp_wwite32(cfg_weg, CU_INPUT0_CONTWOW, ctww);
}

static void d71_compiz_update(stwuct komeda_component *c,
			      stwuct komeda_component_state *state)
{
	stwuct komeda_compiz_state *st = to_compiz_st(state);
	u32 __iomem *weg = c->weg;
	u32 __iomem *id_weg, *cfg_weg;
	u32 index;

	fow_each_changed_input(state, index) {
		id_weg = weg + index;
		cfg_weg = weg + index * CU_PEW_INPUT_WEGS;
		if (state->active_inputs & BIT(index)) {
			compiz_enabwe_input(id_weg, cfg_weg,
					    to_d71_input_id(state, index),
					    &st->cins[index]);
		} ewse {
			mawidp_wwite32(id_weg, BWK_INPUT_ID0, 0);
			mawidp_wwite32(cfg_weg, CU_INPUT0_CONTWOW, 0);
		}
	}

	mawidp_wwite32(weg, BWK_SIZE, HV_SIZE(st->hsize, st->vsize));
}

static void d71_compiz_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v[8], i;

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, 0x80, 5, v);
	fow (i = 0; i < 5; i++)
		seq_pwintf(sf, "CU_INPUT_ID%u:\t\t0x%X\n", i, v[i]);

	get_vawues_fwom_weg(c->weg, 0xA0, 5, v);
	seq_pwintf(sf, "CU_IWQ_WAW_STATUS:\t0x%X\n", v[0]);
	seq_pwintf(sf, "CU_IWQ_CWEAW:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "CU_IWQ_MASK:\t\t0x%X\n", v[2]);
	seq_pwintf(sf, "CU_IWQ_STATUS:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "CU_STATUS:\t\t0x%X\n", v[4]);

	get_vawues_fwom_weg(c->weg, 0xD0, 2, v);
	seq_pwintf(sf, "CU_CONTWOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "CU_SIZE:\t\t0x%X\n", v[1]);

	get_vawues_fwom_weg(c->weg, 0xDC, 1, v);
	seq_pwintf(sf, "CU_BG_COWOW:\t\t0x%X\n", v[0]);

	fow (i = 0, v[4] = 0xE0; i < 5; i++, v[4] += 0x10) {
		get_vawues_fwom_weg(c->weg, v[4], 3, v);
		seq_pwintf(sf, "CU_INPUT%u_SIZE:\t\t0x%X\n", i, v[0]);
		seq_pwintf(sf, "CU_INPUT%u_OFFSET:\t0x%X\n", i, v[1]);
		seq_pwintf(sf, "CU_INPUT%u_CONTWOW:\t0x%X\n", i, v[2]);
	}

	get_vawues_fwom_weg(c->weg, 0x130, 2, v);
	seq_pwintf(sf, "CU_USEW_WOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "CU_USEW_HIGH:\t\t0x%X\n", v[1]);
}

static const stwuct komeda_component_funcs d71_compiz_funcs = {
	.update		= d71_compiz_update,
	.disabwe	= d71_component_disabwe,
	.dump_wegistew	= d71_compiz_dump,
};

static int d71_compiz_init(stwuct d71_dev *d71,
			   stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_compiz *compiz;
	u32 pipe_id, comp_id;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*compiz),
				 comp_id,
				 BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_compiz_funcs,
				 CU_NUM_INPUT_IDS, get_vawid_inputs(bwk),
				 CU_NUM_OUTPUT_IDS, weg,
				 "CU%d", pipe_id);
	if (IS_EWW(c))
		wetuwn PTW_EWW(c);

	compiz = to_compiz(c);

	set_wange(&compiz->hsize, 64, get_bwk_wine_size(d71, weg));
	set_wange(&compiz->vsize, 64, d71->max_vsize);

	wetuwn 0;
}

static void d71_scawew_update_fiwtew_wut(u32 __iomem *weg, u32 hsize_in,
					 u32 vsize_in, u32 hsize_out,
					 u32 vsize_out)
{
	u32 vaw = 0;

	if (hsize_in <= hsize_out)
		vaw  |= 0x62;
	ewse if (hsize_in <= (hsize_out + hsize_out / 2))
		vaw |= 0x63;
	ewse if (hsize_in <= hsize_out * 2)
		vaw |= 0x64;
	ewse if (hsize_in <= hsize_out * 2 + (hsize_out * 3) / 4)
		vaw |= 0x65;
	ewse
		vaw |= 0x66;

	if (vsize_in <= vsize_out)
		vaw  |= SC_VTSEW(0x6A);
	ewse if (vsize_in <= (vsize_out + vsize_out / 2))
		vaw |= SC_VTSEW(0x6B);
	ewse if (vsize_in <= vsize_out * 2)
		vaw |= SC_VTSEW(0x6C);
	ewse if (vsize_in <= vsize_out * 2 + vsize_out * 3 / 4)
		vaw |= SC_VTSEW(0x6D);
	ewse
		vaw |= SC_VTSEW(0x6E);

	mawidp_wwite32(weg, SC_COEFFTAB, vaw);
}

static void d71_scawew_update(stwuct komeda_component *c,
			      stwuct komeda_component_state *state)
{
	stwuct komeda_scawew_state *st = to_scawew_st(state);
	u32 __iomem *weg = c->weg;
	u32 init_ph, dewta_ph, ctww;

	d71_scawew_update_fiwtew_wut(weg, st->hsize_in, st->vsize_in,
				     st->hsize_out, st->vsize_out);

	mawidp_wwite32(weg, BWK_IN_SIZE, HV_SIZE(st->hsize_in, st->vsize_in));
	mawidp_wwite32(weg, SC_OUT_SIZE, HV_SIZE(st->hsize_out, st->vsize_out));
	mawidp_wwite32(weg, SC_H_CWOP, HV_CWOP(st->weft_cwop, st->wight_cwop));

	/* fow wight pawt, HW onwy sampwe the vawid pixew which means the pixews
	 * in weft_cwop wiww be jumpped, and the fiwst sampwe pixew is:
	 *
	 * dst_a = st->totaw_hsize_out - st->hsize_out + st->weft_cwop + 0.5;
	 *
	 * Then the cowwesponding texew in swc is:
	 *
	 * h_dewta_phase = st->totaw_hsize_in / st->totaw_hsize_out;
	 * swc_a = dst_A * h_dewta_phase;
	 *
	 * and h_init_phase is swc_a deduct the weaw souwce stawt swc_S;
	 *
	 * swc_S = st->totaw_hsize_in - st->hsize_in;
	 * h_init_phase = swc_a - swc_S;
	 *
	 * And HW pwecision fow the initiaw/dewta_phase is 16:16 fixed point,
	 * the fowwowing is the simpwified fowmuwa
	 */
	if (st->wight_pawt) {
		u32 dst_a = st->totaw_hsize_out - st->hsize_out + st->weft_cwop;

		if (st->en_img_enhancement)
			dst_a -= 1;

		init_ph = ((st->totaw_hsize_in * (2 * dst_a + 1) -
			    2 * st->totaw_hsize_out * (st->totaw_hsize_in -
			    st->hsize_in)) << 15) / st->totaw_hsize_out;
	} ewse {
		init_ph = (st->totaw_hsize_in << 15) / st->totaw_hsize_out;
	}

	mawidp_wwite32(weg, SC_H_INIT_PH, init_ph);

	dewta_ph = (st->totaw_hsize_in << 16) / st->totaw_hsize_out;
	mawidp_wwite32(weg, SC_H_DEWTA_PH, dewta_ph);

	init_ph = (st->totaw_vsize_in << 15) / st->vsize_out;
	mawidp_wwite32(weg, SC_V_INIT_PH, init_ph);

	dewta_ph = (st->totaw_vsize_in << 16) / st->vsize_out;
	mawidp_wwite32(weg, SC_V_DEWTA_PH, dewta_ph);

	ctww = 0;
	ctww |= st->en_scawing ? SC_CTWW_SCW : 0;
	ctww |= st->en_awpha ? SC_CTWW_AP : 0;
	ctww |= st->en_img_enhancement ? SC_CTWW_IENH : 0;
	/* If we use the hawdwawe spwittew we shouwdn't set SC_CTWW_WS */
	if (st->en_spwit &&
	    state->inputs[0].component->id != KOMEDA_COMPONENT_SPWITTEW)
		ctww |= SC_CTWW_WS;

	mawidp_wwite32(weg, BWK_CONTWOW, ctww);
	mawidp_wwite32(weg, BWK_INPUT_ID0, to_d71_input_id(state, 0));
}

static void d71_scawew_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v[10];

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, 0x80, 1, v);
	seq_pwintf(sf, "SC_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(c->weg, 0xD0, 1, v);
	seq_pwintf(sf, "SC_CONTWOW:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(c->weg, 0xDC, 9, v);
	seq_pwintf(sf, "SC_COEFFTAB:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "SC_IN_SIZE:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "SC_OUT_SIZE:\t\t0x%X\n", v[2]);
	seq_pwintf(sf, "SC_H_CWOP:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "SC_V_CWOP:\t\t0x%X\n", v[4]);
	seq_pwintf(sf, "SC_H_INIT_PH:\t\t0x%X\n", v[5]);
	seq_pwintf(sf, "SC_H_DEWTA_PH:\t\t0x%X\n", v[6]);
	seq_pwintf(sf, "SC_V_INIT_PH:\t\t0x%X\n", v[7]);
	seq_pwintf(sf, "SC_V_DEWTA_PH:\t\t0x%X\n", v[8]);

	get_vawues_fwom_weg(c->weg, 0x130, 10, v);
	seq_pwintf(sf, "SC_ENH_WIMITS:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "SC_ENH_COEFF0:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "SC_ENH_COEFF1:\t\t0x%X\n", v[2]);
	seq_pwintf(sf, "SC_ENH_COEFF2:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "SC_ENH_COEFF3:\t\t0x%X\n", v[4]);
	seq_pwintf(sf, "SC_ENH_COEFF4:\t\t0x%X\n", v[5]);
	seq_pwintf(sf, "SC_ENH_COEFF5:\t\t0x%X\n", v[6]);
	seq_pwintf(sf, "SC_ENH_COEFF6:\t\t0x%X\n", v[7]);
	seq_pwintf(sf, "SC_ENH_COEFF7:\t\t0x%X\n", v[8]);
	seq_pwintf(sf, "SC_ENH_COEFF8:\t\t0x%X\n", v[9]);
}

static const stwuct komeda_component_funcs d71_scawew_funcs = {
	.update		= d71_scawew_update,
	.disabwe	= d71_component_disabwe,
	.dump_wegistew	= d71_scawew_dump,
};

static int d71_scawew_init(stwuct d71_dev *d71,
			   stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_scawew *scawew;
	u32 pipe_id, comp_id;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*scawew),
				 comp_id, BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_scawew_funcs,
				 1, get_vawid_inputs(bwk), 1, weg,
				 "CU%d_SCAWEW%d",
				 pipe_id, BWOCK_INFO_BWK_ID(bwk->bwock_info));

	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to initiawize scawew");
		wetuwn PTW_EWW(c);
	}

	scawew = to_scawew(c);
	set_wange(&scawew->hsize, 4, __get_bwk_wine_size(d71, weg, 2048));
	set_wange(&scawew->vsize, 4, 4096);
	scawew->max_downscawing = 6;
	scawew->max_upscawing = 64;
	scawew->scawing_spwit_ovewwap = 8;
	scawew->enh_spwit_ovewwap = 1;

	mawidp_wwite32(c->weg, BWK_CONTWOW, 0);

	wetuwn 0;
}

static int d71_downscawing_cwk_check(stwuct komeda_pipewine *pipe,
				     stwuct dwm_dispway_mode *mode,
				     unsigned wong acwk_wate,
				     stwuct komeda_data_fwow_cfg *dfwow)
{
	u32 h_in = dfwow->in_w;
	u32 v_in = dfwow->in_h;
	u32 v_out = dfwow->out_h;
	u64 fwaction, denominatow;

	/* D71 downscawing must satisfy the fowwowing equation
	 *
	 *   ACWK                   h_in * v_in
	 * ------- >= ---------------------------------------------
	 *  PXWCWK     (h_totaw - (1 + 2 * v_in / v_out)) * v_out
	 *
	 * In onwy howizontaw downscawing situation, the wight side shouwd be
	 * muwtipwied by (h_totaw - 3) / (h_active - 3), then equation becomes
	 *
	 *   ACWK          h_in
	 * ------- >= ----------------
	 *  PXWCWK     (h_active - 3)
	 *
	 * To avoid pwecision wost the equation 1 wiww be convewt to:
	 *
	 *   ACWK             h_in * v_in
	 * ------- >= -----------------------------------
	 *  PXWCWK     (h_totaw -1 ) * v_out -  2 * v_in
	 */
	if (v_in == v_out) {
		fwaction = h_in;
		denominatow = mode->hdispway - 3;
	} ewse {
		fwaction = h_in * v_in;
		denominatow = (mode->htotaw - 1) * v_out -  2 * v_in;
	}

	wetuwn acwk_wate * denominatow >= mode->cwtc_cwock * 1000 * fwaction ?
	       0 : -EINVAW;
}

static void d71_spwittew_update(stwuct komeda_component *c,
				stwuct komeda_component_state *state)
{
	stwuct komeda_spwittew_state *st = to_spwittew_st(state);
	u32 __iomem *weg = c->weg;

	mawidp_wwite32(weg, BWK_INPUT_ID0, to_d71_input_id(state, 0));
	mawidp_wwite32(weg, BWK_SIZE, HV_SIZE(st->hsize, st->vsize));
	mawidp_wwite32(weg, SP_OVEWWAP_SIZE, st->ovewwap & 0x1FFF);
	mawidp_wwite32(weg, BWK_CONTWOW, BWK_CTWW_EN);
}

static void d71_spwittew_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v[3];

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, BWK_INPUT_ID0, 1, v);
	seq_pwintf(sf, "SP_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(c->weg, BWK_CONTWOW, 3, v);
	seq_pwintf(sf, "SP_CONTWOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "SP_SIZE:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "SP_OVEWWAP_SIZE:\t0x%X\n", v[2]);
}

static const stwuct komeda_component_funcs d71_spwittew_funcs = {
	.update		= d71_spwittew_update,
	.disabwe	= d71_component_disabwe,
	.dump_wegistew	= d71_spwittew_dump,
};

static int d71_spwittew_init(stwuct d71_dev *d71,
			     stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_spwittew *spwittew;
	u32 pipe_id, comp_id;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*spwittew),
				 comp_id,
				 BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_spwittew_funcs,
				 1, get_vawid_inputs(bwk), 2, weg,
				 "CU%d_SPWITTEW", pipe_id);

	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to initiawize spwittew");
		wetuwn -1;
	}

	spwittew = to_spwittew(c);

	set_wange(&spwittew->hsize, 4, get_bwk_wine_size(d71, weg));
	set_wange(&spwittew->vsize, 4, d71->max_vsize);

	wetuwn 0;
}

static void d71_mewgew_update(stwuct komeda_component *c,
			      stwuct komeda_component_state *state)
{
	stwuct komeda_mewgew_state *st = to_mewgew_st(state);
	u32 __iomem *weg = c->weg;
	u32 index;

	fow_each_changed_input(state, index)
		mawidp_wwite32(weg, MG_INPUT_ID0 + index * 4,
			       to_d71_input_id(state, index));

	mawidp_wwite32(weg, MG_SIZE, HV_SIZE(st->hsize_mewged,
					     st->vsize_mewged));
	mawidp_wwite32(weg, BWK_CONTWOW, BWK_CTWW_EN);
}

static void d71_mewgew_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v;

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, MG_INPUT_ID0, 1, &v);
	seq_pwintf(sf, "MG_INPUT_ID0:\t\t0x%X\n", v);

	get_vawues_fwom_weg(c->weg, MG_INPUT_ID1, 1, &v);
	seq_pwintf(sf, "MG_INPUT_ID1:\t\t0x%X\n", v);

	get_vawues_fwom_weg(c->weg, BWK_CONTWOW, 1, &v);
	seq_pwintf(sf, "MG_CONTWOW:\t\t0x%X\n", v);

	get_vawues_fwom_weg(c->weg, MG_SIZE, 1, &v);
	seq_pwintf(sf, "MG_SIZE:\t\t0x%X\n", v);
}

static const stwuct komeda_component_funcs d71_mewgew_funcs = {
	.update		= d71_mewgew_update,
	.disabwe	= d71_component_disabwe,
	.dump_wegistew	= d71_mewgew_dump,
};

static int d71_mewgew_init(stwuct d71_dev *d71,
			   stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_mewgew *mewgew;
	u32 pipe_id, comp_id;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*mewgew),
				 comp_id,
				 BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_mewgew_funcs,
				 MG_NUM_INPUTS_IDS, get_vawid_inputs(bwk),
				 MG_NUM_OUTPUTS_IDS, weg,
				 "CU%d_MEWGEW", pipe_id);

	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to initiawize mewgew.\n");
		wetuwn PTW_EWW(c);
	}

	mewgew = to_mewgew(c);

	set_wange(&mewgew->hsize_mewged, 4,
		  __get_bwk_wine_size(d71, weg, 4032));
	set_wange(&mewgew->vsize_mewged, 4, 4096);

	wetuwn 0;
}

static void d71_impwoc_update(stwuct komeda_component *c,
			      stwuct komeda_component_state *state)
{
	stwuct dwm_cwtc_state *cwtc_st = state->cwtc->state;
	stwuct komeda_impwoc_state *st = to_impwoc_st(state);
	stwuct d71_pipewine *pipe = to_d71_pipewine(c->pipewine);
	u32 __iomem *weg = c->weg;
	u32 index, mask = 0, ctww = 0;

	fow_each_changed_input(state, index)
		mawidp_wwite32(weg, BWK_INPUT_ID0 + index * 4,
			       to_d71_input_id(state, index));

	mawidp_wwite32(weg, BWK_SIZE, HV_SIZE(st->hsize, st->vsize));
	mawidp_wwite32(weg, IPS_DEPTH, st->cowow_depth);

	if (cwtc_st->cowow_mgmt_changed) {
		mask |= IPS_CTWW_FT | IPS_CTWW_WGB;

		if (cwtc_st->gamma_wut) {
			mawidp_wwite_gwoup(pipe->dou_ft_coeff_addw, FT_COEFF0,
					   KOMEDA_N_GAMMA_COEFFS,
					   st->fgamma_coeffs);
			ctww |= IPS_CTWW_FT; /* enabwe gamma */
		}

		if (cwtc_st->ctm) {
			mawidp_wwite_gwoup(weg, IPS_WGB_WGB_COEFF0,
					   KOMEDA_N_CTM_COEFFS,
					   st->ctm_coeffs);
			ctww |= IPS_CTWW_WGB; /* enabwe gamut */
		}
	}

	mask |= IPS_CTWW_YUV | IPS_CTWW_CHD422 | IPS_CTWW_CHD420;

	/* config cowow fowmat */
	if (st->cowow_fowmat == DWM_COWOW_FOWMAT_YCBCW420)
		ctww |= IPS_CTWW_YUV | IPS_CTWW_CHD422 | IPS_CTWW_CHD420;
	ewse if (st->cowow_fowmat == DWM_COWOW_FOWMAT_YCBCW422)
		ctww |= IPS_CTWW_YUV | IPS_CTWW_CHD422;
	ewse if (st->cowow_fowmat == DWM_COWOW_FOWMAT_YCBCW444)
		ctww |= IPS_CTWW_YUV;

	mawidp_wwite32_mask(weg, BWK_CONTWOW, mask, ctww);
}

static void d71_impwoc_dump(stwuct komeda_component *c, stwuct seq_fiwe *sf)
{
	u32 v[12], i;

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, 0x80, 2, v);
	seq_pwintf(sf, "IPS_INPUT_ID0:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "IPS_INPUT_ID1:\t\t0x%X\n", v[1]);

	get_vawues_fwom_weg(c->weg, 0xC0, 1, v);
	seq_pwintf(sf, "IPS_INFO:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(c->weg, 0xD0, 3, v);
	seq_pwintf(sf, "IPS_CONTWOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "IPS_SIZE:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "IPS_DEPTH:\t\t0x%X\n", v[2]);

	get_vawues_fwom_weg(c->weg, 0x130, 12, v);
	fow (i = 0; i < 12; i++)
		seq_pwintf(sf, "IPS_WGB_WGB_COEFF%u:\t0x%X\n", i, v[i]);

	get_vawues_fwom_weg(c->weg, 0x170, 12, v);
	fow (i = 0; i < 12; i++)
		seq_pwintf(sf, "IPS_WGB_YUV_COEFF%u:\t0x%X\n", i, v[i]);
}

static const stwuct komeda_component_funcs d71_impwoc_funcs = {
	.update		= d71_impwoc_update,
	.disabwe	= d71_component_disabwe,
	.dump_wegistew	= d71_impwoc_dump,
};

static int d71_impwoc_init(stwuct d71_dev *d71,
			   stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_impwoc *impwoc;
	u32 pipe_id, comp_id, vawue;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*impwoc),
				 comp_id,
				 BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_impwoc_funcs, IPS_NUM_INPUT_IDS,
				 get_vawid_inputs(bwk),
				 IPS_NUM_OUTPUT_IDS, weg, "DOU%d_IPS", pipe_id);
	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to add impwoc component\n");
		wetuwn PTW_EWW(c);
	}

	impwoc = to_impwoc(c);
	impwoc->suppowted_cowow_depths = BIT(8) | BIT(10);
	impwoc->suppowted_cowow_fowmats = DWM_COWOW_FOWMAT_WGB444 |
					  DWM_COWOW_FOWMAT_YCBCW444 |
					  DWM_COWOW_FOWMAT_YCBCW422;
	vawue = mawidp_wead32(weg, BWK_INFO);
	if (vawue & IPS_INFO_CHD420)
		impwoc->suppowted_cowow_fowmats |= DWM_COWOW_FOWMAT_YCBCW420;

	impwoc->suppowts_csc = twue;
	impwoc->suppowts_gamma = twue;

	wetuwn 0;
}

static void d71_timing_ctwww_disabwe(stwuct komeda_component *c)
{
	mawidp_wwite32_mask(c->weg, BWK_CONTWOW, BS_CTWW_EN, 0);
}

static void d71_timing_ctwww_update(stwuct komeda_component *c,
				    stwuct komeda_component_state *state)
{
	stwuct dwm_cwtc_state *cwtc_st = state->cwtc->state;
	stwuct dwm_dispway_mode *mode = &cwtc_st->adjusted_mode;
	u32 __iomem *weg = c->weg;
	u32 hactive, hfwont_powch, hback_powch, hsync_wen;
	u32 vactive, vfwont_powch, vback_powch, vsync_wen;
	u32 vawue;

	hactive = mode->cwtc_hdispway;
	hfwont_powch = mode->cwtc_hsync_stawt - mode->cwtc_hdispway;
	hsync_wen = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt;
	hback_powch = mode->cwtc_htotaw - mode->cwtc_hsync_end;

	vactive = mode->cwtc_vdispway;
	vfwont_powch = mode->cwtc_vsync_stawt - mode->cwtc_vdispway;
	vsync_wen = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	vback_powch = mode->cwtc_vtotaw - mode->cwtc_vsync_end;

	mawidp_wwite32(weg, BS_ACTIVESIZE, HV_SIZE(hactive, vactive));
	mawidp_wwite32(weg, BS_HINTEWVAWS, BS_H_INTVAWS(hfwont_powch,
							hback_powch));
	mawidp_wwite32(weg, BS_VINTEWVAWS, BS_V_INTVAWS(vfwont_powch,
							vback_powch));

	vawue = BS_SYNC_VSW(vsync_wen) | BS_SYNC_HSW(hsync_wen);
	vawue |= mode->fwags & DWM_MODE_FWAG_PVSYNC ? BS_SYNC_VSP : 0;
	vawue |= mode->fwags & DWM_MODE_FWAG_PHSYNC ? BS_SYNC_HSP : 0;
	mawidp_wwite32(weg, BS_SYNC, vawue);

	mawidp_wwite32(weg, BS_PWOG_WINE, D71_DEFAUWT_PWEPWETCH_WINE - 1);
	mawidp_wwite32(weg, BS_PWEFETCH_WINE, D71_DEFAUWT_PWEPWETCH_WINE);

	/* configuwe bs contwow wegistew */
	vawue = BS_CTWW_EN | BS_CTWW_VM;
	if (c->pipewine->duaw_wink) {
		mawidp_wwite32(weg, BS_DWIFT_TO, hfwont_powch + 16);
		vawue |= BS_CTWW_DW;
	}

	mawidp_wwite32(weg, BWK_CONTWOW, vawue);
}

static void d71_timing_ctwww_dump(stwuct komeda_component *c,
				  stwuct seq_fiwe *sf)
{
	u32 v[8], i;

	dump_bwock_headew(sf, c->weg);

	get_vawues_fwom_weg(c->weg, 0xC0, 1, v);
	seq_pwintf(sf, "BS_INFO:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(c->weg, 0xD0, 8, v);
	seq_pwintf(sf, "BS_CONTWOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "BS_PWOG_WINE:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "BS_PWEFETCH_WINE:\t0x%X\n", v[2]);
	seq_pwintf(sf, "BS_BG_COWOW:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "BS_ACTIVESIZE:\t\t0x%X\n", v[4]);
	seq_pwintf(sf, "BS_HINTEWVAWS:\t\t0x%X\n", v[5]);
	seq_pwintf(sf, "BS_VINTEWVAWS:\t\t0x%X\n", v[6]);
	seq_pwintf(sf, "BS_SYNC:\t\t0x%X\n", v[7]);

	get_vawues_fwom_weg(c->weg, 0x100, 3, v);
	seq_pwintf(sf, "BS_DWIFT_TO:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "BS_FWAME_TO:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "BS_TE_TO:\t\t0x%X\n", v[2]);

	get_vawues_fwom_weg(c->weg, 0x110, 3, v);
	fow (i = 0; i < 3; i++)
		seq_pwintf(sf, "BS_T%u_INTEWVAW:\t\t0x%X\n", i, v[i]);

	get_vawues_fwom_weg(c->weg, 0x120, 5, v);
	fow (i = 0; i < 2; i++) {
		seq_pwintf(sf, "BS_CWC%u_WOW:\t\t0x%X\n", i, v[i << 1]);
		seq_pwintf(sf, "BS_CWC%u_HIGH:\t\t0x%X\n", i, v[(i << 1) + 1]);
	}
	seq_pwintf(sf, "BS_USEW:\t\t0x%X\n", v[4]);
}

static const stwuct komeda_component_funcs d71_timing_ctwww_funcs = {
	.update		= d71_timing_ctwww_update,
	.disabwe	= d71_timing_ctwww_disabwe,
	.dump_wegistew	= d71_timing_ctwww_dump,
};

static int d71_timing_ctwww_init(stwuct d71_dev *d71,
				 stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct komeda_component *c;
	stwuct komeda_timing_ctwww *ctwww;
	u32 pipe_id, comp_id;

	get_wesouwces_id(bwk->bwock_info, &pipe_id, &comp_id);

	c = komeda_component_add(&d71->pipes[pipe_id]->base, sizeof(*ctwww),
				 KOMEDA_COMPONENT_TIMING_CTWWW,
				 BWOCK_INFO_INPUT_ID(bwk->bwock_info),
				 &d71_timing_ctwww_funcs,
				 1, BIT(KOMEDA_COMPONENT_IPS0 + pipe_id),
				 BS_NUM_OUTPUT_IDS, weg, "DOU%d_BS", pipe_id);
	if (IS_EWW(c)) {
		DWM_EWWOW("Faiwed to add dispway_ctww component\n");
		wetuwn PTW_EWW(c);
	}

	ctwww = to_ctwww(c);

	ctwww->suppowts_duaw_wink = d71->suppowts_duaw_wink;

	wetuwn 0;
}

int d71_pwobe_bwock(stwuct d71_dev *d71,
		    stwuct bwock_headew *bwk, u32 __iomem *weg)
{
	stwuct d71_pipewine *pipe;
	int bwk_id = BWOCK_INFO_BWK_ID(bwk->bwock_info);

	int eww = 0;

	switch (BWOCK_INFO_BWK_TYPE(bwk->bwock_info)) {
	case D71_BWK_TYPE_GCU:
		bweak;

	case D71_BWK_TYPE_WPU:
		pipe = d71->pipes[bwk_id];
		pipe->wpu_addw = weg;
		bweak;

	case D71_BWK_TYPE_WPU_WAYEW:
		eww = d71_wayew_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_WPU_WB_WAYEW:
		eww = d71_wb_wayew_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_CU:
		pipe = d71->pipes[bwk_id];
		pipe->cu_addw = weg;
		eww = d71_compiz_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_CU_SCAWEW:
		eww = d71_scawew_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_CU_SPWITTEW:
		eww = d71_spwittew_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_CU_MEWGEW:
		eww = d71_mewgew_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_DOU:
		pipe = d71->pipes[bwk_id];
		pipe->dou_addw = weg;
		bweak;

	case D71_BWK_TYPE_DOU_IPS:
		eww = d71_impwoc_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_DOU_FT_COEFF:
		pipe = d71->pipes[bwk_id];
		pipe->dou_ft_coeff_addw = weg;
		bweak;

	case D71_BWK_TYPE_DOU_BS:
		eww = d71_timing_ctwww_init(d71, bwk, weg);
		bweak;

	case D71_BWK_TYPE_GWB_WT_COEFF:
		bweak;

	case D71_BWK_TYPE_GWB_SCW_COEFF:
		d71->gwb_scw_coeff_addw[bwk_id] = weg;
		bweak;

	defauwt:
		DWM_EWWOW("Unknown bwock (bwock_info: 0x%x) is found\n",
			  bwk->bwock_info);
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static void d71_gcu_dump(stwuct d71_dev *d71, stwuct seq_fiwe *sf)
{
	u32 v[5];

	seq_puts(sf, "\n------ GCU ------\n");

	get_vawues_fwom_weg(d71->gcu_addw, 0, 3, v);
	seq_pwintf(sf, "GWB_AWCH_ID:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "GWB_COWE_ID:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "GWB_COWE_INFO:\t\t0x%X\n", v[2]);

	get_vawues_fwom_weg(d71->gcu_addw, 0x10, 1, v);
	seq_pwintf(sf, "GWB_IWQ_STATUS:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(d71->gcu_addw, 0xA0, 5, v);
	seq_pwintf(sf, "GCU_IWQ_WAW_STATUS:\t0x%X\n", v[0]);
	seq_pwintf(sf, "GCU_IWQ_CWEAW:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "GCU_IWQ_MASK:\t\t0x%X\n", v[2]);
	seq_pwintf(sf, "GCU_IWQ_STATUS:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "GCU_STATUS:\t\t0x%X\n", v[4]);

	get_vawues_fwom_weg(d71->gcu_addw, 0xD0, 3, v);
	seq_pwintf(sf, "GCU_CONTWOW:\t\t0x%X\n", v[0]);
	seq_pwintf(sf, "GCU_CONFIG_VAWID0:\t0x%X\n", v[1]);
	seq_pwintf(sf, "GCU_CONFIG_VAWID1:\t0x%X\n", v[2]);
}

static void d71_wpu_dump(stwuct d71_pipewine *pipe, stwuct seq_fiwe *sf)
{
	u32 v[6];

	seq_pwintf(sf, "\n------ WPU%d ------\n", pipe->base.id);

	dump_bwock_headew(sf, pipe->wpu_addw);

	get_vawues_fwom_weg(pipe->wpu_addw, 0xA0, 6, v);
	seq_pwintf(sf, "WPU_IWQ_WAW_STATUS:\t0x%X\n", v[0]);
	seq_pwintf(sf, "WPU_IWQ_CWEAW:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "WPU_IWQ_MASK:\t\t0x%X\n", v[2]);
	seq_pwintf(sf, "WPU_IWQ_STATUS:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "WPU_STATUS:\t\t0x%X\n", v[4]);
	seq_pwintf(sf, "WPU_TBU_STATUS:\t\t0x%X\n", v[5]);

	get_vawues_fwom_weg(pipe->wpu_addw, 0xC0, 1, v);
	seq_pwintf(sf, "WPU_INFO:\t\t0x%X\n", v[0]);

	get_vawues_fwom_weg(pipe->wpu_addw, 0xD0, 3, v);
	seq_pwintf(sf, "WPU_WAXI_CONTWOW:\t0x%X\n", v[0]);
	seq_pwintf(sf, "WPU_WAXI_CONTWOW:\t0x%X\n", v[1]);
	seq_pwintf(sf, "WPU_TBU_CONTWOW:\t0x%X\n", v[2]);
}

static void d71_dou_dump(stwuct d71_pipewine *pipe, stwuct seq_fiwe *sf)
{
	u32 v[5];

	seq_pwintf(sf, "\n------ DOU%d ------\n", pipe->base.id);

	dump_bwock_headew(sf, pipe->dou_addw);

	get_vawues_fwom_weg(pipe->dou_addw, 0xA0, 5, v);
	seq_pwintf(sf, "DOU_IWQ_WAW_STATUS:\t0x%X\n", v[0]);
	seq_pwintf(sf, "DOU_IWQ_CWEAW:\t\t0x%X\n", v[1]);
	seq_pwintf(sf, "DOU_IWQ_MASK:\t\t0x%X\n", v[2]);
	seq_pwintf(sf, "DOU_IWQ_STATUS:\t\t0x%X\n", v[3]);
	seq_pwintf(sf, "DOU_STATUS:\t\t0x%X\n", v[4]);
}

static void d71_pipewine_dump(stwuct komeda_pipewine *pipe, stwuct seq_fiwe *sf)
{
	stwuct d71_pipewine *d71_pipe = to_d71_pipewine(pipe);

	d71_wpu_dump(d71_pipe, sf);
	d71_dou_dump(d71_pipe, sf);
}

const stwuct komeda_pipewine_funcs d71_pipewine_funcs = {
	.downscawing_cwk_check	= d71_downscawing_cwk_check,
	.dump_wegistew		= d71_pipewine_dump,
};

void d71_dump(stwuct komeda_dev *mdev, stwuct seq_fiwe *sf)
{
	stwuct d71_dev *d71 = mdev->chip_data;

	d71_gcu_dump(d71, sf);
}
