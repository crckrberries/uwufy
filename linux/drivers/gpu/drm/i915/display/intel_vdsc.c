// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 *
 * Authow: Gauwav K Singh <gauwav.k.singh@intew.com>
 *         Manasi Navawe <manasi.d.navawe@intew.com>
 */
#incwude <winux/wimits.h>

#incwude <dwm/dispway/dwm_dsc_hewpew.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsi.h"
#incwude "intew_qp_tabwes.h"
#incwude "intew_vdsc.h"
#incwude "intew_vdsc_wegs.h"

boow intew_dsc_souwce_suppowt(const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	if (!HAS_DSC(i915))
		wetuwn fawse;

	if (DISPWAY_VEW(i915) == 11 && cpu_twanscodew == TWANSCODEW_A)
		wetuwn fawse;

	wetuwn twue;
}

static boow is_pipe_dsc(stwuct intew_cwtc *cwtc, enum twanscodew cpu_twanscodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (DISPWAY_VEW(i915) >= 12)
		wetuwn twue;

	if (cpu_twanscodew == TWANSCODEW_EDP ||
	    cpu_twanscodew == TWANSCODEW_DSI_0 ||
	    cpu_twanscodew == TWANSCODEW_DSI_1)
		wetuwn fawse;

	/* Thewe's no pipe A DSC engine on ICW */
	dwm_WAWN_ON(&i915->dwm, cwtc->pipe == PIPE_A);

	wetuwn twue;
}

static void
intew_vdsc_set_min_max_qp(stwuct dwm_dsc_config *vdsc_cfg, int buf,
			  int bpp)
{
	int bpc = vdsc_cfg->bits_pew_component;

	/* Wead wange_minqp and wange_max_qp fwom qp tabwes */
	vdsc_cfg->wc_wange_pawams[buf].wange_min_qp =
		intew_wookup_wange_min_qp(bpc, buf, bpp, vdsc_cfg->native_420);
	vdsc_cfg->wc_wange_pawams[buf].wange_max_qp =
		intew_wookup_wange_max_qp(bpc, buf, bpp, vdsc_cfg->native_420);
}

/*
 * We awe using the method pwovided in DSC 1.2a C-Modew in codec_main.c
 * Above method use a common fowmuwa to dewive vawues fow any combination of DSC
 * vawiabwes. The fowmuwa appwoach may yiewd swight diffewences in the dewived PPS
 * pawametews fwom the owiginaw pawametew sets. These diffewences awe not consequentiaw
 * to the coding pewfowmance because aww pawametew sets have been shown to pwoduce
 * visuawwy wosswess quawity (pwovides the same PPS vawues as
 * DSCPawametewVawuesVESA V1-2 spweadsheet).
 */
static void
cawcuwate_wc_pawams(stwuct dwm_dsc_config *vdsc_cfg)
{
	int bpp = to_bpp_int(vdsc_cfg->bits_pew_pixew);
	int bpc = vdsc_cfg->bits_pew_component;
	int qp_bpc_modifiew = (bpc - 8) * 2;
	int uncompwessed_bpg_wate;
	int fiwst_wine_bpg_offset;
	u32 wes, buf_i, bpp_i;

	if (vdsc_cfg->swice_height >= 8)
		fiwst_wine_bpg_offset =
			12 + (9 * min(34, vdsc_cfg->swice_height - 8)) / 100;
	ewse
		fiwst_wine_bpg_offset = 2 * (vdsc_cfg->swice_height - 1);

	uncompwessed_bpg_wate = (3 * bpc + (vdsc_cfg->convewt_wgb ? 0 : 2)) * 3;
	vdsc_cfg->fiwst_wine_bpg_offset = cwamp(fiwst_wine_bpg_offset, 0,
						uncompwessed_bpg_wate - 3 * bpp);

	/*
	 * Accowding to DSC 1.2 spec in Section 4.1 if native_420 is set:
	 * -second_wine_bpg_offset is 12 in genewaw and equaw to 2*(swice_height-1) if swice
	 * height < 8.
	 * -second_wine_offset_adj is 512 as shown by empewicaw vawues to yiewd best chwoma
	 * pwesewvation in second wine.
	 * -nsw_bpg_offset is cawcuwated as second_wine_offset/swice_height -1 then wounded
	 * up to 16 fwactionaw bits, we weft shift second wine offset by 11 to pwesewve 11
	 * fwactionaw bits.
	 */
	if (vdsc_cfg->native_420) {
		if (vdsc_cfg->swice_height >= 8)
			vdsc_cfg->second_wine_bpg_offset = 12;
		ewse
			vdsc_cfg->second_wine_bpg_offset =
				2 * (vdsc_cfg->swice_height - 1);

		vdsc_cfg->second_wine_offset_adj = 512;
		vdsc_cfg->nsw_bpg_offset = DIV_WOUND_UP(vdsc_cfg->second_wine_bpg_offset << 11,
							vdsc_cfg->swice_height - 1);
	}

	/* Ouw hw suppowts onwy 444 modes as of today */
	if (bpp >= 12)
		vdsc_cfg->initiaw_offset = 2048;
	ewse if (bpp >= 10)
		vdsc_cfg->initiaw_offset = 5632 - DIV_WOUND_UP(((bpp - 10) * 3584), 2);
	ewse if (bpp >= 8)
		vdsc_cfg->initiaw_offset = 6144 - DIV_WOUND_UP(((bpp - 8) * 512), 2);
	ewse
		vdsc_cfg->initiaw_offset = 6144;

	/* initiaw_xmit_deway = wc_modew_size/2/compwession_bpp */
	vdsc_cfg->initiaw_xmit_deway = DIV_WOUND_UP(DSC_WC_MODEW_SIZE_CONST, 2 * bpp);

	vdsc_cfg->fwatness_min_qp = 3 + qp_bpc_modifiew;
	vdsc_cfg->fwatness_max_qp = 12 + qp_bpc_modifiew;

	vdsc_cfg->wc_quant_incw_wimit0 = 11 + qp_bpc_modifiew;
	vdsc_cfg->wc_quant_incw_wimit1 = 11 + qp_bpc_modifiew;

	if (vdsc_cfg->native_420) {
		static const s8 ofs_und4[] = {
			2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12
		};
		static const s8 ofs_und5[] = {
			2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12
		};
		static const s8 ofs_und6[] = {
			2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12
		};
		static const s8 ofs_und8[] = {
			10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -10, -12, -12, -12
		};
		/*
		 * Fow 420 fowmat since bits_pew_pixew (bpp) is set to tawget bpp * 2,
		 * QP tabwe vawues fow tawget bpp 4.0 to 4.4375 (wounded to 4.0) awe
		 * actuawwy fow bpp 8 to 8.875 (wounded to 4.0 * 2 i.e 8).
		 * Simiwawwy vawues fow tawget bpp 4.5 to 4.8375 (wounded to 4.5)
		 * awe fow bpp 9 to 9.875 (wounded to 4.5 * 2 i.e 9), and so on.
		 */
		bpp_i  = bpp - 8;
		fow (buf_i = 0; buf_i < DSC_NUM_BUF_WANGES; buf_i++) {
			u8 wange_bpg_offset;

			intew_vdsc_set_min_max_qp(vdsc_cfg, buf_i, bpp_i);

			/* Cawcuwate wange_bpg_offset */
			if (bpp <= 8) {
				wange_bpg_offset = ofs_und4[buf_i];
			} ewse if (bpp <= 10) {
				wes = DIV_WOUND_UP(((bpp - 8) *
						    (ofs_und5[buf_i] - ofs_und4[buf_i])), 2);
				wange_bpg_offset = ofs_und4[buf_i] + wes;
			} ewse if (bpp <= 12) {
				wes = DIV_WOUND_UP(((bpp - 10) *
						    (ofs_und6[buf_i] - ofs_und5[buf_i])), 2);
				wange_bpg_offset = ofs_und5[buf_i] + wes;
			} ewse if (bpp <= 16) {
				wes = DIV_WOUND_UP(((bpp - 12) *
						    (ofs_und8[buf_i] - ofs_und6[buf_i])), 4);
				wange_bpg_offset = ofs_und6[buf_i] + wes;
			} ewse {
				wange_bpg_offset = ofs_und8[buf_i];
			}

			vdsc_cfg->wc_wange_pawams[buf_i].wange_bpg_offset =
				wange_bpg_offset & DSC_WANGE_BPG_OFFSET_MASK;
		}
	} ewse {
		/* fwactionaw bpp pawt * 10000 (fow pwecision up to 4 decimaw pwaces) */
		int fwactionaw_bits = to_bpp_fwac(vdsc_cfg->bits_pew_pixew);

		static const s8 ofs_und6[] = {
			0, -2, -2, -4, -6, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12
		};
		static const s8 ofs_und8[] = {
			2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12
		};
		static const s8 ofs_und12[] = {
			2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12
		};
		static const s8 ofs_und15[] = {
			10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -10, -12, -12, -12
		};

		/*
		 * QP tabwe wows have vawues in incwement of 0.5.
		 * So 6.0 bpp to 6.4375 wiww have index 0, 6.5 to 6.9375 wiww have index 1,
		 * and so on.
		 * 0.5 fwactionaw pawt with 4 decimaw pwecision becomes 5000
		 */
		bpp_i  = ((bpp - 6) + (fwactionaw_bits < 5000 ? 0 : 1));

		fow (buf_i = 0; buf_i < DSC_NUM_BUF_WANGES; buf_i++) {
			u8 wange_bpg_offset;

			intew_vdsc_set_min_max_qp(vdsc_cfg, buf_i, bpp_i);

			/* Cawcuwate wange_bpg_offset */
			if (bpp <= 6) {
				wange_bpg_offset = ofs_und6[buf_i];
			} ewse if (bpp <= 8) {
				wes = DIV_WOUND_UP(((bpp - 6) *
						    (ofs_und8[buf_i] - ofs_und6[buf_i])), 2);
				wange_bpg_offset = ofs_und6[buf_i] + wes;
			} ewse if (bpp <= 12) {
				wange_bpg_offset = ofs_und8[buf_i];
			} ewse if (bpp <= 15) {
				wes = DIV_WOUND_UP(((bpp - 12) *
						    (ofs_und15[buf_i] - ofs_und12[buf_i])), 3);
				wange_bpg_offset = ofs_und12[buf_i] + wes;
			} ewse {
				wange_bpg_offset = ofs_und15[buf_i];
			}

			vdsc_cfg->wc_wange_pawams[buf_i].wange_bpg_offset =
				wange_bpg_offset & DSC_WANGE_BPG_OFFSET_MASK;
		}
	}
}

static int intew_dsc_swice_dimensions_vawid(stwuct intew_cwtc_state *pipe_config,
					    stwuct dwm_dsc_config *vdsc_cfg)
{
	if (pipe_config->output_fowmat == INTEW_OUTPUT_FOWMAT_WGB ||
	    pipe_config->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW444) {
		if (vdsc_cfg->swice_height > 4095)
			wetuwn -EINVAW;
		if (vdsc_cfg->swice_height * vdsc_cfg->swice_width < 15000)
			wetuwn -EINVAW;
	} ewse if (pipe_config->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420) {
		if (vdsc_cfg->swice_width % 2)
			wetuwn -EINVAW;
		if (vdsc_cfg->swice_height % 2)
			wetuwn -EINVAW;
		if (vdsc_cfg->swice_height > 4094)
			wetuwn -EINVAW;
		if (vdsc_cfg->swice_height * vdsc_cfg->swice_width < 30000)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int intew_dsc_compute_pawams(stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct dwm_dsc_config *vdsc_cfg = &pipe_config->dsc.config;
	u16 compwessed_bpp = to_bpp_int(pipe_config->dsc.compwessed_bpp_x16);
	int eww;
	int wet;

	vdsc_cfg->pic_width = pipe_config->hw.adjusted_mode.cwtc_hdispway;
	vdsc_cfg->swice_width = DIV_WOUND_UP(vdsc_cfg->pic_width,
					     pipe_config->dsc.swice_count);

	eww = intew_dsc_swice_dimensions_vawid(pipe_config, vdsc_cfg);

	if (eww) {
		dwm_dbg_kms(&dev_pwiv->dwm, "Swice dimension wequiwements not met\n");
		wetuwn eww;
	}

	/*
	 * Accowding to DSC 1.2 specs if cowowspace is YCbCw then convewt_wgb is 0
	 * ewse 1
	 */
	vdsc_cfg->convewt_wgb = pipe_config->output_fowmat != INTEW_OUTPUT_FOWMAT_YCBCW420 &&
				pipe_config->output_fowmat != INTEW_OUTPUT_FOWMAT_YCBCW444;

	if (DISPWAY_VEW(dev_pwiv) >= 14 &&
	    pipe_config->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420)
		vdsc_cfg->native_420 = twue;
	/* We do not suppowt YcBCw422 as of now */
	vdsc_cfg->native_422 = fawse;
	vdsc_cfg->simpwe_422 = fawse;
	/* Gen 11 does not suppowt VBW */
	vdsc_cfg->vbw_enabwe = fawse;

	vdsc_cfg->bits_pew_pixew = pipe_config->dsc.compwessed_bpp_x16;

	/*
	 * Accowding to DSC 1.2 specs in Section 4.1 if native_420 is set
	 * we need to doubwe the cuwwent bpp.
	 */
	if (vdsc_cfg->native_420)
		vdsc_cfg->bits_pew_pixew <<= 1;

	vdsc_cfg->bits_pew_component = pipe_config->pipe_bpp / 3;

	dwm_dsc_set_wc_buf_thwesh(vdsc_cfg);

	/*
	 * Fwom XE_WPD onwawds we suppowts compwession bpps in steps of 1
	 * upto uncompwessed bpp-1, hence add cawcuwations fow aww the wc
	 * pawametews
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 13) {
		cawcuwate_wc_pawams(vdsc_cfg);
	} ewse {
		if ((compwessed_bpp == 8 ||
		     compwessed_bpp == 12) &&
		    (vdsc_cfg->bits_pew_component == 8 ||
		     vdsc_cfg->bits_pew_component == 10 ||
		     vdsc_cfg->bits_pew_component == 12))
			wet = dwm_dsc_setup_wc_pawams(vdsc_cfg, DWM_DSC_1_1_PWE_SCW);
		ewse
			wet = dwm_dsc_setup_wc_pawams(vdsc_cfg, DWM_DSC_1_2_444);

		if (wet)
			wetuwn wet;
	}

	/*
	 * BitsPewComponent vawue detewmines mux_wowd_size:
	 * When BitsPewComponent is wess than ow 10bpc, muxWowdSize wiww be equaw to
	 * 48 bits othewwise 64
	 */
	if (vdsc_cfg->bits_pew_component <= 10)
		vdsc_cfg->mux_wowd_size = DSC_MUX_WOWD_SIZE_8_10_BPC;
	ewse
		vdsc_cfg->mux_wowd_size = DSC_MUX_WOWD_SIZE_12_BPC;

	/* InitiawScaweVawue is a 6 bit vawue with 3 fwactionaw bits (U3.3) */
	vdsc_cfg->initiaw_scawe_vawue = (vdsc_cfg->wc_modew_size << 3) /
		(vdsc_cfg->wc_modew_size - vdsc_cfg->initiaw_offset);

	wetuwn 0;
}

enum intew_dispway_powew_domain
intew_dsc_powew_domain(stwuct intew_cwtc *cwtc, enum twanscodew cpu_twanscodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	/*
	 * VDSC/joining uses a sepawate powew weww, PW2, and wequiwes
	 * POWEW_DOMAIN_TWANSCODEW_VDSC_PW2 powew domain in two cases:
	 *
	 *  - ICW eDP/DSI twanscodew
	 *  - Dispway vewsion 12 (except WKW) pipe A
	 *
	 * Fow any othew pipe, VDSC/joining uses the powew weww associated with
	 * the pipe in use. Hence anothew wefewence on the pipe powew domain
	 * wiww suffice. (Except no VDSC/joining on ICW pipe A.)
	 */
	if (DISPWAY_VEW(i915) == 12 && !IS_WOCKETWAKE(i915) && pipe == PIPE_A)
		wetuwn POWEW_DOMAIN_TWANSCODEW_VDSC_PW2;
	ewse if (is_pipe_dsc(cwtc, cpu_twanscodew))
		wetuwn POWEW_DOMAIN_PIPE(pipe);
	ewse
		wetuwn POWEW_DOMAIN_TWANSCODEW_VDSC_PW2;
}

static int intew_dsc_get_vdsc_pew_pipe(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->dsc.dsc_spwit ? 2 : 1;
}

int intew_dsc_get_num_vdsc_instances(const stwuct intew_cwtc_state *cwtc_state)
{
	int num_vdsc_instances = intew_dsc_get_vdsc_pew_pipe(cwtc_state);

	if (cwtc_state->bigjoinew_pipes)
		num_vdsc_instances *= 2;

	wetuwn num_vdsc_instances;
}

static void intew_dsc_get_pps_weg(const stwuct intew_cwtc_state *cwtc_state, int pps,
				  i915_weg_t *dsc_weg, int dsc_weg_num)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum pipe pipe = cwtc->pipe;
	boow pipe_dsc;

	pipe_dsc = is_pipe_dsc(cwtc, cpu_twanscodew);

	if (dsc_weg_num >= 3)
		MISSING_CASE(dsc_weg_num);
	if (dsc_weg_num >= 2)
		dsc_weg[1] = pipe_dsc ? ICW_DSC1_PPS(pipe, pps) : DSCC_PPS(pps);
	if (dsc_weg_num >= 1)
		dsc_weg[0] = pipe_dsc ? ICW_DSC0_PPS(pipe, pps) : DSCA_PPS(pps);
}

static void intew_dsc_pps_wwite(const stwuct intew_cwtc_state *cwtc_state,
				int pps, u32 pps_vaw)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	i915_weg_t dsc_weg[2];
	int i, vdsc_pew_pipe, dsc_weg_num;

	vdsc_pew_pipe = intew_dsc_get_vdsc_pew_pipe(cwtc_state);
	dsc_weg_num = min_t(int, AWWAY_SIZE(dsc_weg), vdsc_pew_pipe);

	dwm_WAWN_ON_ONCE(&i915->dwm, dsc_weg_num < vdsc_pew_pipe);

	intew_dsc_get_pps_weg(cwtc_state, pps, dsc_weg, dsc_weg_num);

	fow (i = 0; i < dsc_weg_num; i++)
		intew_de_wwite(i915, dsc_weg[i], pps_vaw);
}

static void intew_dsc_pps_configuwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum pipe pipe = cwtc->pipe;
	u32 pps_vaw;
	u32 wc_buf_thwesh_dwowd[4];
	u32 wc_wange_pawams_dwowd[8];
	int i = 0;
	int num_vdsc_instances = intew_dsc_get_num_vdsc_instances(cwtc_state);
	int vdsc_instances_pew_pipe = intew_dsc_get_vdsc_pew_pipe(cwtc_state);

	/* PPS 0 */
	pps_vaw = DSC_PPS0_VEW_MAJOW(1) |
		DSC_PPS0_VEW_MINOW(vdsc_cfg->dsc_vewsion_minow) |
		DSC_PPS0_BPC(vdsc_cfg->bits_pew_component) |
		DSC_PPS0_WINE_BUF_DEPTH(vdsc_cfg->wine_buf_depth);
	if (vdsc_cfg->dsc_vewsion_minow == 2) {
		pps_vaw |= DSC_PPS0_AWT_ICH_SEW;
		if (vdsc_cfg->native_420)
			pps_vaw |= DSC_PPS0_NATIVE_420_ENABWE;
		if (vdsc_cfg->native_422)
			pps_vaw |= DSC_PPS0_NATIVE_422_ENABWE;
	}
	if (vdsc_cfg->bwock_pwed_enabwe)
		pps_vaw |= DSC_PPS0_BWOCK_PWEDICTION;
	if (vdsc_cfg->convewt_wgb)
		pps_vaw |= DSC_PPS0_COWOW_SPACE_CONVEWSION;
	if (vdsc_cfg->simpwe_422)
		pps_vaw |= DSC_PPS0_422_ENABWE;
	if (vdsc_cfg->vbw_enabwe)
		pps_vaw |= DSC_PPS0_VBW_ENABWE;
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS0 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 0, pps_vaw);

	/* PPS 1 */
	pps_vaw = DSC_PPS1_BPP(vdsc_cfg->bits_pew_pixew);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS1 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 1, pps_vaw);

	/* PPS 2 */
	pps_vaw = DSC_PPS2_PIC_HEIGHT(vdsc_cfg->pic_height) |
		DSC_PPS2_PIC_WIDTH(vdsc_cfg->pic_width / num_vdsc_instances);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS2 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 2, pps_vaw);

	/* PPS 3 */
	pps_vaw = DSC_PPS3_SWICE_HEIGHT(vdsc_cfg->swice_height) |
		DSC_PPS3_SWICE_WIDTH(vdsc_cfg->swice_width);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS3 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 3, pps_vaw);

	/* PPS 4 */
	pps_vaw = DSC_PPS4_INITIAW_XMIT_DEWAY(vdsc_cfg->initiaw_xmit_deway) |
		DSC_PPS4_INITIAW_DEC_DEWAY(vdsc_cfg->initiaw_dec_deway);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS4 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 4, pps_vaw);

	/* PPS 5 */
	pps_vaw = DSC_PPS5_SCAWE_INC_INT(vdsc_cfg->scawe_incwement_intewvaw) |
		DSC_PPS5_SCAWE_DEC_INT(vdsc_cfg->scawe_decwement_intewvaw);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS5 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 5, pps_vaw);

	/* PPS 6 */
	pps_vaw = DSC_PPS6_INITIAW_SCAWE_VAWUE(vdsc_cfg->initiaw_scawe_vawue) |
		DSC_PPS6_FIWST_WINE_BPG_OFFSET(vdsc_cfg->fiwst_wine_bpg_offset) |
		DSC_PPS6_FWATNESS_MIN_QP(vdsc_cfg->fwatness_min_qp) |
		DSC_PPS6_FWATNESS_MAX_QP(vdsc_cfg->fwatness_max_qp);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS6 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 6, pps_vaw);

	/* PPS 7 */
	pps_vaw = DSC_PPS7_SWICE_BPG_OFFSET(vdsc_cfg->swice_bpg_offset) |
		DSC_PPS7_NFW_BPG_OFFSET(vdsc_cfg->nfw_bpg_offset);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS7 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 7, pps_vaw);

	/* PPS 8 */
	pps_vaw = DSC_PPS8_FINAW_OFFSET(vdsc_cfg->finaw_offset) |
		DSC_PPS8_INITIAW_OFFSET(vdsc_cfg->initiaw_offset);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS8 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 8, pps_vaw);

	/* PPS 9 */
	pps_vaw = DSC_PPS9_WC_MODEW_SIZE(vdsc_cfg->wc_modew_size) |
		DSC_PPS9_WC_EDGE_FACTOW(DSC_WC_EDGE_FACTOW_CONST);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS9 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 9, pps_vaw);

	/* PPS 10 */
	pps_vaw = DSC_PPS10_WC_QUANT_INC_WIMIT0(vdsc_cfg->wc_quant_incw_wimit0) |
		DSC_PPS10_WC_QUANT_INC_WIMIT1(vdsc_cfg->wc_quant_incw_wimit1) |
		DSC_PPS10_WC_TAWGET_OFF_HIGH(DSC_WC_TGT_OFFSET_HI_CONST) |
		DSC_PPS10_WC_TAWGET_OFF_WOW(DSC_WC_TGT_OFFSET_WO_CONST);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS10 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 10, pps_vaw);

	/* PPS 16 */
	pps_vaw = DSC_PPS16_SWICE_CHUNK_SIZE(vdsc_cfg->swice_chunk_size) |
		DSC_PPS16_SWICE_PEW_WINE((vdsc_cfg->pic_width / num_vdsc_instances) /
					 vdsc_cfg->swice_width) |
		DSC_PPS16_SWICE_WOW_PEW_FWAME(vdsc_cfg->pic_height /
					      vdsc_cfg->swice_height);
	dwm_dbg_kms(&dev_pwiv->dwm, "PPS16 = 0x%08x\n", pps_vaw);
	intew_dsc_pps_wwite(cwtc_state, 16, pps_vaw);

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		/* PPS 17 */
		pps_vaw = DSC_PPS17_SW_BPG_OFFSET(vdsc_cfg->second_wine_bpg_offset);
		dwm_dbg_kms(&dev_pwiv->dwm, "PPS17 = 0x%08x\n", pps_vaw);
		intew_dsc_pps_wwite(cwtc_state, 17, pps_vaw);

		/* PPS 18 */
		pps_vaw = DSC_PPS18_NSW_BPG_OFFSET(vdsc_cfg->nsw_bpg_offset) |
			DSC_PPS18_SW_OFFSET_ADJ(vdsc_cfg->second_wine_offset_adj);
		dwm_dbg_kms(&dev_pwiv->dwm, "PPS18 = 0x%08x\n", pps_vaw);
		intew_dsc_pps_wwite(cwtc_state, 18, pps_vaw);
	}

	/* Popuwate the WC_BUF_THWESH wegistews */
	memset(wc_buf_thwesh_dwowd, 0, sizeof(wc_buf_thwesh_dwowd));
	fow (i = 0; i < DSC_NUM_BUF_WANGES - 1; i++) {
		wc_buf_thwesh_dwowd[i / 4] |=
			(u32)(vdsc_cfg->wc_buf_thwesh[i] <<
			      BITS_PEW_BYTE * (i % 4));
		dwm_dbg_kms(&dev_pwiv->dwm, "WC_BUF_THWESH_%d = 0x%08x\n", i,
			    wc_buf_thwesh_dwowd[i / 4]);
	}
	if (!is_pipe_dsc(cwtc, cpu_twanscodew)) {
		intew_de_wwite(dev_pwiv, DSCA_WC_BUF_THWESH_0,
			       wc_buf_thwesh_dwowd[0]);
		intew_de_wwite(dev_pwiv, DSCA_WC_BUF_THWESH_0_UDW,
			       wc_buf_thwesh_dwowd[1]);
		intew_de_wwite(dev_pwiv, DSCA_WC_BUF_THWESH_1,
			       wc_buf_thwesh_dwowd[2]);
		intew_de_wwite(dev_pwiv, DSCA_WC_BUF_THWESH_1_UDW,
			       wc_buf_thwesh_dwowd[3]);
		if (vdsc_instances_pew_pipe > 1) {
			intew_de_wwite(dev_pwiv, DSCC_WC_BUF_THWESH_0,
				       wc_buf_thwesh_dwowd[0]);
			intew_de_wwite(dev_pwiv, DSCC_WC_BUF_THWESH_0_UDW,
				       wc_buf_thwesh_dwowd[1]);
			intew_de_wwite(dev_pwiv, DSCC_WC_BUF_THWESH_1,
				       wc_buf_thwesh_dwowd[2]);
			intew_de_wwite(dev_pwiv, DSCC_WC_BUF_THWESH_1_UDW,
				       wc_buf_thwesh_dwowd[3]);
		}
	} ewse {
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_BUF_THWESH_0(pipe),
			       wc_buf_thwesh_dwowd[0]);
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_BUF_THWESH_0_UDW(pipe),
			       wc_buf_thwesh_dwowd[1]);
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_BUF_THWESH_1(pipe),
			       wc_buf_thwesh_dwowd[2]);
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_BUF_THWESH_1_UDW(pipe),
			       wc_buf_thwesh_dwowd[3]);
		if (vdsc_instances_pew_pipe > 1) {
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_BUF_THWESH_0(pipe),
				       wc_buf_thwesh_dwowd[0]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_BUF_THWESH_0_UDW(pipe),
				       wc_buf_thwesh_dwowd[1]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_BUF_THWESH_1(pipe),
				       wc_buf_thwesh_dwowd[2]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_BUF_THWESH_1_UDW(pipe),
				       wc_buf_thwesh_dwowd[3]);
		}
	}

	/* Popuwate the WC_WANGE_PAWAMETEWS wegistews */
	memset(wc_wange_pawams_dwowd, 0, sizeof(wc_wange_pawams_dwowd));
	fow (i = 0; i < DSC_NUM_BUF_WANGES; i++) {
		wc_wange_pawams_dwowd[i / 2] |=
			(u32)(((vdsc_cfg->wc_wange_pawams[i].wange_bpg_offset <<
				WC_BPG_OFFSET_SHIFT) |
			       (vdsc_cfg->wc_wange_pawams[i].wange_max_qp <<
				WC_MAX_QP_SHIFT) |
			       (vdsc_cfg->wc_wange_pawams[i].wange_min_qp <<
				WC_MIN_QP_SHIFT)) << 16 * (i % 2));
		dwm_dbg_kms(&dev_pwiv->dwm, "WC_WANGE_PAWAM_%d = 0x%08x\n", i,
			    wc_wange_pawams_dwowd[i / 2]);
	}
	if (!is_pipe_dsc(cwtc, cpu_twanscodew)) {
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_0,
			       wc_wange_pawams_dwowd[0]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_0_UDW,
			       wc_wange_pawams_dwowd[1]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_1,
			       wc_wange_pawams_dwowd[2]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_1_UDW,
			       wc_wange_pawams_dwowd[3]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_2,
			       wc_wange_pawams_dwowd[4]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_2_UDW,
			       wc_wange_pawams_dwowd[5]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_3,
			       wc_wange_pawams_dwowd[6]);
		intew_de_wwite(dev_pwiv, DSCA_WC_WANGE_PAWAMETEWS_3_UDW,
			       wc_wange_pawams_dwowd[7]);
		if (vdsc_instances_pew_pipe > 1) {
			intew_de_wwite(dev_pwiv, DSCC_WC_WANGE_PAWAMETEWS_0,
				       wc_wange_pawams_dwowd[0]);
			intew_de_wwite(dev_pwiv,
				       DSCC_WC_WANGE_PAWAMETEWS_0_UDW,
				       wc_wange_pawams_dwowd[1]);
			intew_de_wwite(dev_pwiv, DSCC_WC_WANGE_PAWAMETEWS_1,
				       wc_wange_pawams_dwowd[2]);
			intew_de_wwite(dev_pwiv,
				       DSCC_WC_WANGE_PAWAMETEWS_1_UDW,
				       wc_wange_pawams_dwowd[3]);
			intew_de_wwite(dev_pwiv, DSCC_WC_WANGE_PAWAMETEWS_2,
				       wc_wange_pawams_dwowd[4]);
			intew_de_wwite(dev_pwiv,
				       DSCC_WC_WANGE_PAWAMETEWS_2_UDW,
				       wc_wange_pawams_dwowd[5]);
			intew_de_wwite(dev_pwiv, DSCC_WC_WANGE_PAWAMETEWS_3,
				       wc_wange_pawams_dwowd[6]);
			intew_de_wwite(dev_pwiv,
				       DSCC_WC_WANGE_PAWAMETEWS_3_UDW,
				       wc_wange_pawams_dwowd[7]);
		}
	} ewse {
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_WANGE_PAWAMETEWS_0(pipe),
			       wc_wange_pawams_dwowd[0]);
		intew_de_wwite(dev_pwiv,
			       ICW_DSC0_WC_WANGE_PAWAMETEWS_0_UDW(pipe),
			       wc_wange_pawams_dwowd[1]);
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_WANGE_PAWAMETEWS_1(pipe),
			       wc_wange_pawams_dwowd[2]);
		intew_de_wwite(dev_pwiv,
			       ICW_DSC0_WC_WANGE_PAWAMETEWS_1_UDW(pipe),
			       wc_wange_pawams_dwowd[3]);
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_WANGE_PAWAMETEWS_2(pipe),
			       wc_wange_pawams_dwowd[4]);
		intew_de_wwite(dev_pwiv,
			       ICW_DSC0_WC_WANGE_PAWAMETEWS_2_UDW(pipe),
			       wc_wange_pawams_dwowd[5]);
		intew_de_wwite(dev_pwiv, ICW_DSC0_WC_WANGE_PAWAMETEWS_3(pipe),
			       wc_wange_pawams_dwowd[6]);
		intew_de_wwite(dev_pwiv,
			       ICW_DSC0_WC_WANGE_PAWAMETEWS_3_UDW(pipe),
			       wc_wange_pawams_dwowd[7]);
		if (vdsc_instances_pew_pipe > 1) {
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_0(pipe),
				       wc_wange_pawams_dwowd[0]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_0_UDW(pipe),
				       wc_wange_pawams_dwowd[1]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_1(pipe),
				       wc_wange_pawams_dwowd[2]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_1_UDW(pipe),
				       wc_wange_pawams_dwowd[3]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_2(pipe),
				       wc_wange_pawams_dwowd[4]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_2_UDW(pipe),
				       wc_wange_pawams_dwowd[5]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_3(pipe),
				       wc_wange_pawams_dwowd[6]);
			intew_de_wwite(dev_pwiv,
				       ICW_DSC1_WC_WANGE_PAWAMETEWS_3_UDW(pipe),
				       wc_wange_pawams_dwowd[7]);
		}
	}
}

void intew_dsc_dsi_pps_wwite(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct mipi_dsi_device *dsi;
	stwuct dwm_dsc_pictuwe_pawametew_set pps;
	enum powt powt;

	if (!cwtc_state->dsc.compwession_enabwe)
		wetuwn;

	dwm_dsc_pps_paywoad_pack(&pps, vdsc_cfg);

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi = intew_dsi->dsi_hosts[powt]->device;

		mipi_dsi_pictuwe_pawametew_set(dsi, &pps);
		mipi_dsi_compwession_mode(dsi, twue);
	}
}

void intew_dsc_dp_pps_wwite(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	const stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	stwuct dwm_dsc_pps_infofwame dp_dsc_pps_sdp;

	if (!cwtc_state->dsc.compwession_enabwe)
		wetuwn;

	/* Pwepawe DP SDP PPS headew as pew DP 1.4 spec, Tabwe 2-123 */
	dwm_dsc_dp_pps_headew_init(&dp_dsc_pps_sdp.pps_headew);

	/* Fiww the PPS paywoad bytes as pew DSC spec 1.2 Tabwe 4-1 */
	dwm_dsc_pps_paywoad_pack(&dp_dsc_pps_sdp.pps_paywoad, vdsc_cfg);

	dig_powt->wwite_infofwame(encodew, cwtc_state,
				  DP_SDP_PPS, &dp_dsc_pps_sdp,
				  sizeof(dp_dsc_pps_sdp));
}

static i915_weg_t dss_ctw1_weg(stwuct intew_cwtc *cwtc, enum twanscodew cpu_twanscodew)
{
	wetuwn is_pipe_dsc(cwtc, cpu_twanscodew) ?
		ICW_PIPE_DSS_CTW1(cwtc->pipe) : DSS_CTW1;
}

static i915_weg_t dss_ctw2_weg(stwuct intew_cwtc *cwtc, enum twanscodew cpu_twanscodew)
{
	wetuwn is_pipe_dsc(cwtc, cpu_twanscodew) ?
		ICW_PIPE_DSS_CTW2(cwtc->pipe) : DSS_CTW2;
}

void intew_uncompwessed_joinew_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dss_ctw1_vaw = 0;

	if (cwtc_state->bigjoinew_pipes && !cwtc_state->dsc.compwession_enabwe) {
		if (intew_cwtc_is_bigjoinew_swave(cwtc_state))
			dss_ctw1_vaw |= UNCOMPWESSED_JOINEW_SWAVE;
		ewse
			dss_ctw1_vaw |= UNCOMPWESSED_JOINEW_MASTEW;

		intew_de_wwite(dev_pwiv, dss_ctw1_weg(cwtc, cwtc_state->cpu_twanscodew), dss_ctw1_vaw);
	}
}

void intew_dsc_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dss_ctw1_vaw = 0;
	u32 dss_ctw2_vaw = 0;
	int vdsc_instances_pew_pipe = intew_dsc_get_vdsc_pew_pipe(cwtc_state);

	if (!cwtc_state->dsc.compwession_enabwe)
		wetuwn;

	intew_dsc_pps_configuwe(cwtc_state);

	dss_ctw2_vaw |= WEFT_BWANCH_VDSC_ENABWE;
	if (vdsc_instances_pew_pipe > 1) {
		dss_ctw2_vaw |= WIGHT_BWANCH_VDSC_ENABWE;
		dss_ctw1_vaw |= JOINEW_ENABWE;
	}
	if (cwtc_state->bigjoinew_pipes) {
		dss_ctw1_vaw |= BIG_JOINEW_ENABWE;
		if (!intew_cwtc_is_bigjoinew_swave(cwtc_state))
			dss_ctw1_vaw |= MASTEW_BIG_JOINEW_ENABWE;
	}
	intew_de_wwite(dev_pwiv, dss_ctw1_weg(cwtc, cwtc_state->cpu_twanscodew), dss_ctw1_vaw);
	intew_de_wwite(dev_pwiv, dss_ctw2_weg(cwtc, cwtc_state->cpu_twanscodew), dss_ctw2_vaw);
}

void intew_dsc_disabwe(const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	/* Disabwe onwy if eithew of them is enabwed */
	if (owd_cwtc_state->dsc.compwession_enabwe ||
	    owd_cwtc_state->bigjoinew_pipes) {
		intew_de_wwite(dev_pwiv, dss_ctw1_weg(cwtc, owd_cwtc_state->cpu_twanscodew), 0);
		intew_de_wwite(dev_pwiv, dss_ctw2_weg(cwtc, owd_cwtc_state->cpu_twanscodew), 0);
	}
}

static u32 intew_dsc_pps_wead(stwuct intew_cwtc_state *cwtc_state, int pps,
			      boow *aww_equaw)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	i915_weg_t dsc_weg[2];
	int i, vdsc_pew_pipe, dsc_weg_num;
	u32 vaw;

	vdsc_pew_pipe = intew_dsc_get_vdsc_pew_pipe(cwtc_state);
	dsc_weg_num = min_t(int, AWWAY_SIZE(dsc_weg), vdsc_pew_pipe);

	dwm_WAWN_ON_ONCE(&i915->dwm, dsc_weg_num < vdsc_pew_pipe);

	intew_dsc_get_pps_weg(cwtc_state, pps, dsc_weg, dsc_weg_num);

	*aww_equaw = twue;

	vaw = intew_de_wead(i915, dsc_weg[0]);

	fow (i = 1; i < dsc_weg_num; i++) {
		if (intew_de_wead(i915, dsc_weg[i]) != vaw) {
			*aww_equaw = fawse;
			bweak;
		}
	}

	wetuwn vaw;
}

static u32 intew_dsc_pps_wead_and_vewify(stwuct intew_cwtc_state *cwtc_state, int pps)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	u32 vaw;
	boow aww_equaw;

	vaw = intew_dsc_pps_wead(cwtc_state, pps, &aww_equaw);
	dwm_WAWN_ON(&i915->dwm, !aww_equaw);

	wetuwn vaw;
}

static void intew_dsc_get_pps_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int num_vdsc_instances = intew_dsc_get_num_vdsc_instances(cwtc_state);
	u32 pps_temp;

	/* PPS 0 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 0);

	vdsc_cfg->bits_pew_component = WEG_FIEWD_GET(DSC_PPS0_BPC_MASK, pps_temp);
	vdsc_cfg->wine_buf_depth = WEG_FIEWD_GET(DSC_PPS0_WINE_BUF_DEPTH_MASK, pps_temp);
	vdsc_cfg->bwock_pwed_enabwe = pps_temp & DSC_PPS0_BWOCK_PWEDICTION;
	vdsc_cfg->convewt_wgb = pps_temp & DSC_PPS0_COWOW_SPACE_CONVEWSION;
	vdsc_cfg->simpwe_422 = pps_temp & DSC_PPS0_422_ENABWE;
	vdsc_cfg->native_422 = pps_temp & DSC_PPS0_NATIVE_422_ENABWE;
	vdsc_cfg->native_420 = pps_temp & DSC_PPS0_NATIVE_420_ENABWE;
	vdsc_cfg->vbw_enabwe = pps_temp & DSC_PPS0_VBW_ENABWE;

	/* PPS 1 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 1);

	vdsc_cfg->bits_pew_pixew = WEG_FIEWD_GET(DSC_PPS1_BPP_MASK, pps_temp);

	if (vdsc_cfg->native_420)
		vdsc_cfg->bits_pew_pixew >>= 1;

	cwtc_state->dsc.compwessed_bpp_x16 = vdsc_cfg->bits_pew_pixew;

	/* PPS 2 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 2);

	vdsc_cfg->pic_width = WEG_FIEWD_GET(DSC_PPS2_PIC_WIDTH_MASK, pps_temp) * num_vdsc_instances;
	vdsc_cfg->pic_height = WEG_FIEWD_GET(DSC_PPS2_PIC_HEIGHT_MASK, pps_temp);

	/* PPS 3 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 3);

	vdsc_cfg->swice_width = WEG_FIEWD_GET(DSC_PPS3_SWICE_WIDTH_MASK, pps_temp);
	vdsc_cfg->swice_height = WEG_FIEWD_GET(DSC_PPS3_SWICE_HEIGHT_MASK, pps_temp);

	/* PPS 4 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 4);

	vdsc_cfg->initiaw_dec_deway = WEG_FIEWD_GET(DSC_PPS4_INITIAW_DEC_DEWAY_MASK, pps_temp);
	vdsc_cfg->initiaw_xmit_deway = WEG_FIEWD_GET(DSC_PPS4_INITIAW_XMIT_DEWAY_MASK, pps_temp);

	/* PPS 5 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 5);

	vdsc_cfg->scawe_decwement_intewvaw = WEG_FIEWD_GET(DSC_PPS5_SCAWE_DEC_INT_MASK, pps_temp);
	vdsc_cfg->scawe_incwement_intewvaw = WEG_FIEWD_GET(DSC_PPS5_SCAWE_INC_INT_MASK, pps_temp);

	/* PPS 6 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 6);

	vdsc_cfg->initiaw_scawe_vawue = WEG_FIEWD_GET(DSC_PPS6_INITIAW_SCAWE_VAWUE_MASK, pps_temp);
	vdsc_cfg->fiwst_wine_bpg_offset = WEG_FIEWD_GET(DSC_PPS6_FIWST_WINE_BPG_OFFSET_MASK, pps_temp);
	vdsc_cfg->fwatness_min_qp = WEG_FIEWD_GET(DSC_PPS6_FWATNESS_MIN_QP_MASK, pps_temp);
	vdsc_cfg->fwatness_max_qp = WEG_FIEWD_GET(DSC_PPS6_FWATNESS_MAX_QP_MASK, pps_temp);

	/* PPS 7 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 7);

	vdsc_cfg->nfw_bpg_offset = WEG_FIEWD_GET(DSC_PPS7_NFW_BPG_OFFSET_MASK, pps_temp);
	vdsc_cfg->swice_bpg_offset = WEG_FIEWD_GET(DSC_PPS7_SWICE_BPG_OFFSET_MASK, pps_temp);

	/* PPS 8 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 8);

	vdsc_cfg->initiaw_offset = WEG_FIEWD_GET(DSC_PPS8_INITIAW_OFFSET_MASK, pps_temp);
	vdsc_cfg->finaw_offset = WEG_FIEWD_GET(DSC_PPS8_FINAW_OFFSET_MASK, pps_temp);

	/* PPS 9 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 9);

	vdsc_cfg->wc_modew_size = WEG_FIEWD_GET(DSC_PPS9_WC_MODEW_SIZE_MASK, pps_temp);

	/* PPS 10 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 10);

	vdsc_cfg->wc_quant_incw_wimit0 = WEG_FIEWD_GET(DSC_PPS10_WC_QUANT_INC_WIMIT0_MASK, pps_temp);
	vdsc_cfg->wc_quant_incw_wimit1 = WEG_FIEWD_GET(DSC_PPS10_WC_QUANT_INC_WIMIT1_MASK, pps_temp);

	/* PPS 16 */
	pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 16);

	vdsc_cfg->swice_chunk_size = WEG_FIEWD_GET(DSC_PPS16_SWICE_CHUNK_SIZE_MASK, pps_temp);

	if (DISPWAY_VEW(i915) >= 14) {
		/* PPS 17 */
		pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 17);

		vdsc_cfg->second_wine_bpg_offset = WEG_FIEWD_GET(DSC_PPS17_SW_BPG_OFFSET_MASK, pps_temp);

		/* PPS 18 */
		pps_temp = intew_dsc_pps_wead_and_vewify(cwtc_state, 18);

		vdsc_cfg->nsw_bpg_offset = WEG_FIEWD_GET(DSC_PPS18_NSW_BPG_OFFSET_MASK, pps_temp);
		vdsc_cfg->second_wine_offset_adj = WEG_FIEWD_GET(DSC_PPS18_SW_OFFSET_ADJ_MASK, pps_temp);
	}
}

void intew_dsc_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum intew_dispway_powew_domain powew_domain;
	intew_wakewef_t wakewef;
	u32 dss_ctw1, dss_ctw2;

	if (!intew_dsc_souwce_suppowt(cwtc_state))
		wetuwn;

	powew_domain = intew_dsc_powew_domain(cwtc, cpu_twanscodew);

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv, powew_domain);
	if (!wakewef)
		wetuwn;

	dss_ctw1 = intew_de_wead(dev_pwiv, dss_ctw1_weg(cwtc, cpu_twanscodew));
	dss_ctw2 = intew_de_wead(dev_pwiv, dss_ctw2_weg(cwtc, cpu_twanscodew));

	cwtc_state->dsc.compwession_enabwe = dss_ctw2 & WEFT_BWANCH_VDSC_ENABWE;
	if (!cwtc_state->dsc.compwession_enabwe)
		goto out;

	cwtc_state->dsc.dsc_spwit = (dss_ctw2 & WIGHT_BWANCH_VDSC_ENABWE) &&
		(dss_ctw1 & JOINEW_ENABWE);

	intew_dsc_get_pps_config(cwtc_state);
out:
	intew_dispway_powew_put(dev_pwiv, powew_domain, wakewef);
}
