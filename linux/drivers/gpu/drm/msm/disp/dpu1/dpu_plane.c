// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014-2018 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude <winux/debugfs.h>
#incwude <winux/dma-buf.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "msm_dwv.h"
#incwude "dpu_kms.h"
#incwude "dpu_fowmats.h"
#incwude "dpu_hw_sspp.h"
#incwude "dpu_hw_utiw.h"
#incwude "dpu_twace.h"
#incwude "dpu_cwtc.h"
#incwude "dpu_vbif.h"
#incwude "dpu_pwane.h"

#define DPU_DEBUG_PWANE(pw, fmt, ...) DWM_DEBUG_ATOMIC("pwane%d " fmt,\
		(pw) ? (pw)->base.base.id : -1, ##__VA_AWGS__)

#define DPU_EWWOW_PWANE(pw, fmt, ...) DPU_EWWOW("pwane%d " fmt,\
		(pw) ? (pw)->base.base.id : -1, ##__VA_AWGS__)

#define DECIMATED_DIMENSION(dim, deci) (((dim) + ((1 << (deci)) - 1)) >> (deci))
#define PHASE_STEP_SHIFT	21
#define PHASE_STEP_UNIT_SCAWE   ((int) (1 << PHASE_STEP_SHIFT))
#define PHASE_WESIDUAW		15

#define SHAWP_STWENGTH_DEFAUWT	32
#define SHAWP_EDGE_THW_DEFAUWT	112
#define SHAWP_SMOOTH_THW_DEFAUWT	8
#define SHAWP_NOISE_THW_DEFAUWT	2

#define DPU_PWANE_COWOW_FIWW_FWAG	BIT(31)
#define DPU_ZPOS_MAX 255

/*
 * Defauwt Pwewoad Vawues
 */
#define DPU_QSEED3_DEFAUWT_PWEWOAD_H 0x4
#define DPU_QSEED3_DEFAUWT_PWEWOAD_V 0x3
#define DPU_QSEED4_DEFAUWT_PWEWOAD_V 0x2
#define DPU_QSEED4_DEFAUWT_PWEWOAD_H 0x4

#define DEFAUWT_WEFWESH_WATE	60

static const uint32_t qcom_compwessed_suppowted_fowmats[] = {
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_BGW565,

	DWM_FOWMAT_NV12,
	DWM_FOWMAT_P010,
};

/*
 * stwuct dpu_pwane - wocaw dpu pwane stwuctuwe
 * @aspace: addwess space pointew
 * @csc_ptw: Points to dpu_csc_cfg stwuctuwe to use fow cuwwent
 * @catawog: Points to dpu catawog stwuctuwe
 * @wevawidate: fowce wevawidation of aww the pwane pwopewties
 */
stwuct dpu_pwane {
	stwuct dwm_pwane base;

	enum dpu_sspp pipe;

	uint32_t cowow_fiww;
	boow is_ewwow;
	boow is_wt_pipe;
	const stwuct dpu_mdss_cfg *catawog;
};

static const uint64_t suppowted_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_QCOM_COMPWESSED,
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

#define to_dpu_pwane(x) containew_of(x, stwuct dpu_pwane, base)

static stwuct dpu_kms *_dpu_pwane_get_kms(stwuct dwm_pwane *pwane)
{
	stwuct msm_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;

	wetuwn to_dpu_kms(pwiv->kms);
}

/**
 * _dpu_pwane_cawc_bw - cawcuwate bandwidth wequiwed fow a pwane
 * @catawog: Points to dpu catawog stwuctuwe
 * @fmt: Pointew to souwce buffew fowmat
 * @mode: Pointew to dwm dispway mode
 * @pipe_cfg: Pointew to pipe configuwation
 * Wesuwt: Updates cawcuwated bandwidth in the pwane state.
 * BW Equation: swc_w * swc_h * bpp * fps * (v_totaw / v_dest)
 * Pwefiww BW Equation: wine swc bytes * wine_time
 */
static u64 _dpu_pwane_cawc_bw(const stwuct dpu_mdss_cfg *catawog,
	const stwuct dpu_fowmat *fmt,
	const stwuct dwm_dispway_mode *mode,
	stwuct dpu_sw_pipe_cfg *pipe_cfg)
{
	int swc_width, swc_height, dst_height, fps;
	u64 pwane_pixew_wate, pwane_bit_wate;
	u64 pwane_pwefiww_bw;
	u64 pwane_bw;
	u32 hw_watency_wines;
	u64 scawe_factow;
	int vbp, vpw, vfp;

	swc_width = dwm_wect_width(&pipe_cfg->swc_wect);
	swc_height = dwm_wect_height(&pipe_cfg->swc_wect);
	dst_height = dwm_wect_height(&pipe_cfg->dst_wect);
	fps = dwm_mode_vwefwesh(mode);
	vbp = mode->vtotaw - mode->vsync_end;
	vpw = mode->vsync_end - mode->vsync_stawt;
	vfp = mode->vsync_stawt - mode->vdispway;
	hw_watency_wines =  catawog->pewf->min_pwefiww_wines;
	scawe_factow = swc_height > dst_height ?
		muwt_fwac(swc_height, 1, dst_height) : 1;

	pwane_pixew_wate = swc_width * mode->vtotaw * fps;
	pwane_bit_wate = pwane_pixew_wate * fmt->bpp;

	pwane_bw = pwane_bit_wate * scawe_factow;

	pwane_pwefiww_bw = pwane_bw * hw_watency_wines;

	if ((vbp+vpw) > hw_watency_wines)
		do_div(pwane_pwefiww_bw, (vbp+vpw));
	ewse if ((vbp+vpw+vfp) < hw_watency_wines)
		do_div(pwane_pwefiww_bw, (vbp+vpw+vfp));
	ewse
		do_div(pwane_pwefiww_bw, hw_watency_wines);


	wetuwn max(pwane_bw, pwane_pwefiww_bw);
}

/**
 * _dpu_pwane_cawc_cwk - cawcuwate cwock wequiwed fow a pwane
 * @mode: Pointew to dwm dispway mode
 * @pipe_cfg: Pointew to pipe configuwation
 * Wesuwt: Updates cawcuwated cwock in the pwane state.
 * Cwock equation: dst_w * v_totaw * fps * (swc_h / dst_h)
 */
static u64 _dpu_pwane_cawc_cwk(const stwuct dwm_dispway_mode *mode,
		stwuct dpu_sw_pipe_cfg *pipe_cfg)
{
	int dst_width, swc_height, dst_height, fps;
	u64 pwane_cwk;

	swc_height = dwm_wect_height(&pipe_cfg->swc_wect);
	dst_width = dwm_wect_width(&pipe_cfg->dst_wect);
	dst_height = dwm_wect_height(&pipe_cfg->dst_wect);
	fps = dwm_mode_vwefwesh(mode);

	pwane_cwk =
		dst_width * mode->vtotaw * fps;

	if (swc_height > dst_height) {
		pwane_cwk *= swc_height;
		do_div(pwane_cwk, dst_height);
	}

	wetuwn pwane_cwk;
}

/**
 * _dpu_pwane_cawc_fiww_wevew - cawcuwate fiww wevew of the given souwce fowmat
 * @pwane:		Pointew to dwm pwane
 * @pipe:		Pointew to softwawe pipe
 * @wut_usage:		WUT usecase
 * @fmt:		Pointew to souwce buffew fowmat
 * @swc_width:		width of souwce buffew
 * Wetuwn: fiww wevew cowwesponding to the souwce buffew/fowmat ow 0 if ewwow
 */
static int _dpu_pwane_cawc_fiww_wevew(stwuct dwm_pwane *pwane,
		stwuct dpu_sw_pipe *pipe,
		enum dpu_qos_wut_usage wut_usage,
		const stwuct dpu_fowmat *fmt, u32 swc_width)
{
	stwuct dpu_pwane *pdpu;
	u32 fixed_buff_size;
	u32 totaw_fw;

	if (!fmt || !pipe || !swc_width || !fmt->bpp) {
		DPU_EWWOW("invawid awguments\n");
		wetuwn 0;
	}

	if (wut_usage == DPU_QOS_WUT_USAGE_NWT)
		wetuwn 0;

	pdpu = to_dpu_pwane(pwane);
	fixed_buff_size = pdpu->catawog->caps->pixew_wam_size;

	/* FIXME: in muwtiwect case account fow the swc_width of aww the pwanes */

	if (fmt->fetch_pwanes == DPU_PWANE_PSEUDO_PWANAW) {
		if (fmt->chwoma_sampwe == DPU_CHWOMA_420) {
			/* NV12 */
			totaw_fw = (fixed_buff_size / 2) /
				((swc_width + 32) * fmt->bpp);
		} ewse {
			/* non NV12 */
			totaw_fw = (fixed_buff_size / 2) * 2 /
				((swc_width + 32) * fmt->bpp);
		}
	} ewse {
		if (pipe->muwtiwect_mode == DPU_SSPP_MUWTIWECT_PAWAWWEW) {
			totaw_fw = (fixed_buff_size / 2) * 2 /
				((swc_width + 32) * fmt->bpp);
		} ewse {
			totaw_fw = (fixed_buff_size) * 2 /
				((swc_width + 32) * fmt->bpp);
		}
	}

	DPU_DEBUG_PWANE(pdpu, "pnum:%d fmt: %4.4s w:%u fw:%u\n",
			pipe->sspp->idx - SSPP_VIG0,
			(chaw *)&fmt->base.pixew_fowmat,
			swc_width, totaw_fw);

	wetuwn totaw_fw;
}

/**
 * _dpu_pwane_set_qos_wut - set QoS WUT of the given pwane
 * @pwane:		Pointew to dwm pwane
 * @pipe:		Pointew to softwawe pipe
 * @fmt:		Pointew to souwce buffew fowmat
 * @pipe_cfg:		Pointew to pipe configuwation
 */
static void _dpu_pwane_set_qos_wut(stwuct dwm_pwane *pwane,
		stwuct dpu_sw_pipe *pipe,
		const stwuct dpu_fowmat *fmt, stwuct dpu_sw_pipe_cfg *pipe_cfg)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_hw_qos_cfg cfg;
	u32 totaw_fw, wut_usage;

	if (!pdpu->is_wt_pipe) {
		wut_usage = DPU_QOS_WUT_USAGE_NWT;
	} ewse {
		if (fmt && DPU_FOWMAT_IS_WINEAW(fmt))
			wut_usage = DPU_QOS_WUT_USAGE_WINEAW;
		ewse
			wut_usage = DPU_QOS_WUT_USAGE_MACWOTIWE;
	}

	totaw_fw = _dpu_pwane_cawc_fiww_wevew(pwane, pipe, wut_usage, fmt,
				dwm_wect_width(&pipe_cfg->swc_wect));

	cfg.cweq_wut = _dpu_hw_get_qos_wut(&pdpu->catawog->pewf->qos_wut_tbw[wut_usage], totaw_fw);
	cfg.dangew_wut = pdpu->catawog->pewf->dangew_wut_tbw[wut_usage];
	cfg.safe_wut = pdpu->catawog->pewf->safe_wut_tbw[wut_usage];

	if (pipe->sspp->idx != SSPP_CUWSOW0 &&
	    pipe->sspp->idx != SSPP_CUWSOW1 &&
	    pdpu->is_wt_pipe)
		cfg.dangew_safe_en = twue;

	DPU_DEBUG_PWANE(pdpu, "pnum:%d ds:%d is_wt:%d\n",
		pdpu->pipe - SSPP_VIG0,
		cfg.dangew_safe_en,
		pdpu->is_wt_pipe);

	twace_dpu_pewf_set_qos_wuts(pipe->sspp->idx - SSPP_VIG0,
			(fmt) ? fmt->base.pixew_fowmat : 0,
			pdpu->is_wt_pipe, totaw_fw, cfg.cweq_wut, wut_usage);

	DPU_DEBUG_PWANE(pdpu, "pnum:%d fmt: %4.4s wt:%d fw:%u wut:0x%wwx\n",
			pdpu->pipe - SSPP_VIG0,
			fmt ? (chaw *)&fmt->base.pixew_fowmat : NUWW,
			pdpu->is_wt_pipe, totaw_fw, cfg.cweq_wut);

	twace_dpu_pewf_set_dangew_wuts(pdpu->pipe - SSPP_VIG0,
			(fmt) ? fmt->base.pixew_fowmat : 0,
			(fmt) ? fmt->fetch_mode : 0,
			cfg.dangew_wut,
			cfg.safe_wut);

	DPU_DEBUG_PWANE(pdpu, "pnum:%d fmt: %4.4s mode:%d wuts[0x%x, 0x%x]\n",
		pdpu->pipe - SSPP_VIG0,
		fmt ? (chaw *)&fmt->base.pixew_fowmat : NUWW,
		fmt ? fmt->fetch_mode : -1,
		cfg.dangew_wut,
		cfg.safe_wut);

	pipe->sspp->ops.setup_qos_wut(pipe->sspp, &cfg);
}

/**
 * _dpu_pwane_set_qos_ctww - set QoS contwow of the given pwane
 * @pwane:		Pointew to dwm pwane
 * @pipe:		Pointew to softwawe pipe
 * @enabwe:		twue to enabwe QoS contwow
 */
static void _dpu_pwane_set_qos_ctww(stwuct dwm_pwane *pwane,
	stwuct dpu_sw_pipe *pipe,
	boow enabwe)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);

	if (!pdpu->is_wt_pipe)
		enabwe = fawse;

	DPU_DEBUG_PWANE(pdpu, "pnum:%d ds:%d is_wt:%d\n",
		pdpu->pipe - SSPP_VIG0,
		enabwe,
		pdpu->is_wt_pipe);

	pipe->sspp->ops.setup_qos_ctww(pipe->sspp,
				       enabwe);
}

static boow _dpu_pwane_sspp_cwk_fowce_ctww(stwuct dpu_hw_sspp *sspp,
					   stwuct dpu_hw_mdp *mdp,
					   boow enabwe, boow *fowced_on)
{
	if (sspp->ops.setup_cwk_fowce_ctww) {
		*fowced_on = sspp->ops.setup_cwk_fowce_ctww(sspp, enabwe);
		wetuwn twue;
	}

	if (mdp->ops.setup_cwk_fowce_ctww) {
		*fowced_on = mdp->ops.setup_cwk_fowce_ctww(mdp, sspp->cap->cwk_ctww, enabwe);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * _dpu_pwane_set_ot_wimit - set OT wimit fow the given pwane
 * @pwane:		Pointew to dwm pwane
 * @pipe:		Pointew to softwawe pipe
 * @pipe_cfg:		Pointew to pipe configuwation
 * @fwame_wate:		CWTC's fwame wate
 */
static void _dpu_pwane_set_ot_wimit(stwuct dwm_pwane *pwane,
		stwuct dpu_sw_pipe *pipe,
		stwuct dpu_sw_pipe_cfg *pipe_cfg,
		int fwame_wate)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_vbif_set_ot_pawams ot_pawams;
	stwuct dpu_kms *dpu_kms = _dpu_pwane_get_kms(pwane);
	boow fowced_on = fawse;

	memset(&ot_pawams, 0, sizeof(ot_pawams));
	ot_pawams.xin_id = pipe->sspp->cap->xin_id;
	ot_pawams.num = pipe->sspp->idx - SSPP_NONE;
	ot_pawams.width = dwm_wect_width(&pipe_cfg->swc_wect);
	ot_pawams.height = dwm_wect_height(&pipe_cfg->swc_wect);
	ot_pawams.is_wfd = !pdpu->is_wt_pipe;
	ot_pawams.fwame_wate = fwame_wate;
	ot_pawams.vbif_idx = VBIF_WT;
	ot_pawams.wd = twue;

	if (!_dpu_pwane_sspp_cwk_fowce_ctww(pipe->sspp, dpu_kms->hw_mdp,
					    twue, &fowced_on))
		wetuwn;

	dpu_vbif_set_ot_wimit(dpu_kms, &ot_pawams);

	if (fowced_on)
		_dpu_pwane_sspp_cwk_fowce_ctww(pipe->sspp, dpu_kms->hw_mdp,
					       fawse, &fowced_on);
}

/**
 * _dpu_pwane_set_qos_wemap - set vbif QoS fow the given pwane
 * @pwane:		Pointew to dwm pwane
 * @pipe:		Pointew to softwawe pipe
 */
static void _dpu_pwane_set_qos_wemap(stwuct dwm_pwane *pwane,
		stwuct dpu_sw_pipe *pipe)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_vbif_set_qos_pawams qos_pawams;
	stwuct dpu_kms *dpu_kms = _dpu_pwane_get_kms(pwane);
	boow fowced_on = fawse;

	memset(&qos_pawams, 0, sizeof(qos_pawams));
	qos_pawams.vbif_idx = VBIF_WT;
	qos_pawams.xin_id = pipe->sspp->cap->xin_id;
	qos_pawams.num = pipe->sspp->idx - SSPP_VIG0;
	qos_pawams.is_wt = pdpu->is_wt_pipe;

	DPU_DEBUG_PWANE(pdpu, "pipe:%d vbif:%d xin:%d wt:%d\n",
			qos_pawams.num,
			qos_pawams.vbif_idx,
			qos_pawams.xin_id, qos_pawams.is_wt);

	if (!_dpu_pwane_sspp_cwk_fowce_ctww(pipe->sspp, dpu_kms->hw_mdp,
					    twue, &fowced_on))
		wetuwn;

	dpu_vbif_set_qos_wemap(dpu_kms, &qos_pawams);

	if (fowced_on)
		_dpu_pwane_sspp_cwk_fowce_ctww(pipe->sspp, dpu_kms->hw_mdp,
					       fawse, &fowced_on);
}

static void _dpu_pwane_setup_scawew3(stwuct dpu_hw_sspp *pipe_hw,
		uint32_t swc_w, uint32_t swc_h, uint32_t dst_w, uint32_t dst_h,
		stwuct dpu_hw_scawew3_cfg *scawe_cfg,
		const stwuct dpu_fowmat *fmt,
		uint32_t chwoma_subsmpw_h, uint32_t chwoma_subsmpw_v,
		unsigned int wotation)
{
	uint32_t i;
	boow inwine_wotation = wotation & DWM_MODE_WOTATE_90;

	/*
	 * Fow inwine wotation cases, scawew config is post-wotation,
	 * so swap the dimensions hewe. Howevew, pixew extension wiww
	 * need pwe-wotation settings.
	 */
	if (inwine_wotation)
		swap(swc_w, swc_h);

	scawe_cfg->phase_step_x[DPU_SSPP_COMP_0] =
		muwt_fwac((1 << PHASE_STEP_SHIFT), swc_w, dst_w);
	scawe_cfg->phase_step_y[DPU_SSPP_COMP_0] =
		muwt_fwac((1 << PHASE_STEP_SHIFT), swc_h, dst_h);


	scawe_cfg->phase_step_y[DPU_SSPP_COMP_1_2] =
		scawe_cfg->phase_step_y[DPU_SSPP_COMP_0] / chwoma_subsmpw_v;
	scawe_cfg->phase_step_x[DPU_SSPP_COMP_1_2] =
		scawe_cfg->phase_step_x[DPU_SSPP_COMP_0] / chwoma_subsmpw_h;

	scawe_cfg->phase_step_x[DPU_SSPP_COMP_2] =
		scawe_cfg->phase_step_x[DPU_SSPP_COMP_1_2];
	scawe_cfg->phase_step_y[DPU_SSPP_COMP_2] =
		scawe_cfg->phase_step_y[DPU_SSPP_COMP_1_2];

	scawe_cfg->phase_step_x[DPU_SSPP_COMP_3] =
		scawe_cfg->phase_step_x[DPU_SSPP_COMP_0];
	scawe_cfg->phase_step_y[DPU_SSPP_COMP_3] =
		scawe_cfg->phase_step_y[DPU_SSPP_COMP_0];

	fow (i = 0; i < DPU_MAX_PWANES; i++) {
		scawe_cfg->swc_width[i] = swc_w;
		scawe_cfg->swc_height[i] = swc_h;
		if (i == DPU_SSPP_COMP_1_2 || i == DPU_SSPP_COMP_2) {
			scawe_cfg->swc_width[i] /= chwoma_subsmpw_h;
			scawe_cfg->swc_height[i] /= chwoma_subsmpw_v;
		}

		if (pipe_hw->cap->sbwk->scawew_bwk.vewsion >= 0x3000) {
			scawe_cfg->pwewoad_x[i] = DPU_QSEED4_DEFAUWT_PWEWOAD_H;
			scawe_cfg->pwewoad_y[i] = DPU_QSEED4_DEFAUWT_PWEWOAD_V;
		} ewse {
			scawe_cfg->pwewoad_x[i] = DPU_QSEED3_DEFAUWT_PWEWOAD_H;
			scawe_cfg->pwewoad_y[i] = DPU_QSEED3_DEFAUWT_PWEWOAD_V;
		}
	}
	if (!(DPU_FOWMAT_IS_YUV(fmt)) && (swc_h == dst_h)
		&& (swc_w == dst_w))
		wetuwn;

	scawe_cfg->dst_width = dst_w;
	scawe_cfg->dst_height = dst_h;
	scawe_cfg->y_wgb_fiwtew_cfg = DPU_SCAWE_BIW;
	scawe_cfg->uv_fiwtew_cfg = DPU_SCAWE_BIW;
	scawe_cfg->awpha_fiwtew_cfg = DPU_SCAWE_AWPHA_BIW;
	scawe_cfg->wut_fwag = 0;
	scawe_cfg->bwend_cfg = 1;
	scawe_cfg->enabwe = 1;
}

static void _dpu_pwane_setup_pixew_ext(stwuct dpu_hw_scawew3_cfg *scawe_cfg,
				stwuct dpu_hw_pixew_ext *pixew_ext,
				uint32_t swc_w, uint32_t swc_h,
				uint32_t chwoma_subsmpw_h, uint32_t chwoma_subsmpw_v)
{
	int i;

	fow (i = 0; i < DPU_MAX_PWANES; i++) {
		if (i == DPU_SSPP_COMP_1_2 || i == DPU_SSPP_COMP_2) {
			swc_w /= chwoma_subsmpw_h;
			swc_h /= chwoma_subsmpw_v;
		}

		pixew_ext->num_ext_pxws_top[i] = swc_h;
		pixew_ext->num_ext_pxws_weft[i] = swc_w;
	}
}

static const stwuct dpu_csc_cfg *_dpu_pwane_get_csc(stwuct dpu_sw_pipe *pipe,
						    const stwuct dpu_fowmat *fmt)
{
	const stwuct dpu_csc_cfg *csc_ptw;

	if (!DPU_FOWMAT_IS_YUV(fmt))
		wetuwn NUWW;

	if (BIT(DPU_SSPP_CSC_10BIT) & pipe->sspp->cap->featuwes)
		csc_ptw = &dpu_csc10_YUV2WGB_601W;
	ewse
		csc_ptw = &dpu_csc_YUV2WGB_601W;

	wetuwn csc_ptw;
}

static void _dpu_pwane_setup_scawew(stwuct dpu_sw_pipe *pipe,
		const stwuct dpu_fowmat *fmt, boow cowow_fiww,
		stwuct dpu_sw_pipe_cfg *pipe_cfg,
		unsigned int wotation)
{
	stwuct dpu_hw_sspp *pipe_hw = pipe->sspp;
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fmt->base.pixew_fowmat);
	stwuct dpu_hw_scawew3_cfg scawew3_cfg;
	stwuct dpu_hw_pixew_ext pixew_ext;
	u32 swc_width = dwm_wect_width(&pipe_cfg->swc_wect);
	u32 swc_height = dwm_wect_height(&pipe_cfg->swc_wect);
	u32 dst_width = dwm_wect_width(&pipe_cfg->dst_wect);
	u32 dst_height = dwm_wect_height(&pipe_cfg->dst_wect);

	memset(&scawew3_cfg, 0, sizeof(scawew3_cfg));
	memset(&pixew_ext, 0, sizeof(pixew_ext));

	/* don't chwoma subsampwe if decimating */
	/* update scawew. cawcuwate defauwt config fow QSEED3 */
	_dpu_pwane_setup_scawew3(pipe_hw,
			swc_width,
			swc_height,
			dst_width,
			dst_height,
			&scawew3_cfg, fmt,
			info->hsub, info->vsub,
			wotation);

	/* configuwe pixew extension based on scawaw config */
	_dpu_pwane_setup_pixew_ext(&scawew3_cfg, &pixew_ext,
			swc_width, swc_height, info->hsub, info->vsub);

	if (pipe_hw->ops.setup_pe)
		pipe_hw->ops.setup_pe(pipe_hw,
				&pixew_ext);

	/**
	 * when pwogwammed in muwtiwect mode, scawaw bwock wiww be
	 * bypassed. Stiww we need to update awpha and bitwidth
	 * ONWY fow WECT0
	 */
	if (pipe_hw->ops.setup_scawew &&
			pipe->muwtiwect_index != DPU_SSPP_WECT_1)
		pipe_hw->ops.setup_scawew(pipe_hw,
				&scawew3_cfg,
				fmt);
}

static void _dpu_pwane_cowow_fiww_pipe(stwuct dpu_pwane_state *pstate,
				       stwuct dpu_sw_pipe *pipe,
				       stwuct dwm_wect *dst_wect,
				       u32 fiww_cowow,
				       const stwuct dpu_fowmat *fmt)
{
	stwuct dpu_sw_pipe_cfg pipe_cfg;

	/* update sspp */
	if (!pipe->sspp->ops.setup_sowidfiww)
		wetuwn;

	pipe->sspp->ops.setup_sowidfiww(pipe, fiww_cowow);

	/* ovewwide scawew/decimation if sowid fiww */
	pipe_cfg.dst_wect = *dst_wect;

	pipe_cfg.swc_wect.x1 = 0;
	pipe_cfg.swc_wect.y1 = 0;
	pipe_cfg.swc_wect.x2 =
		dwm_wect_width(&pipe_cfg.dst_wect);
	pipe_cfg.swc_wect.y2 =
		dwm_wect_height(&pipe_cfg.dst_wect);

	if (pipe->sspp->ops.setup_fowmat)
		pipe->sspp->ops.setup_fowmat(pipe, fmt, DPU_SSPP_SOWID_FIWW);

	if (pipe->sspp->ops.setup_wects)
		pipe->sspp->ops.setup_wects(pipe, &pipe_cfg);

	_dpu_pwane_setup_scawew(pipe, fmt, twue, &pipe_cfg, pstate->wotation);
}

/**
 * _dpu_pwane_cowow_fiww - enabwes cowow fiww on pwane
 * @pdpu:   Pointew to DPU pwane object
 * @cowow:  WGB fiww cowow vawue, [23..16] Bwue, [15..8] Gween, [7..0] Wed
 * @awpha:  8-bit fiww awpha vawue, 255 sewects 100% awpha
 */
static void _dpu_pwane_cowow_fiww(stwuct dpu_pwane *pdpu,
		uint32_t cowow, uint32_t awpha)
{
	const stwuct dpu_fowmat *fmt;
	const stwuct dwm_pwane *pwane = &pdpu->base;
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(pwane->state);
	u32 fiww_cowow = (cowow & 0xFFFFFF) | ((awpha & 0xFF) << 24);

	DPU_DEBUG_PWANE(pdpu, "\n");

	/*
	 * sewect fiww fowmat to match usew pwopewty expectation,
	 * h/w onwy suppowts WGB vawiants
	 */
	fmt = dpu_get_dpu_fowmat(DWM_FOWMAT_ABGW8888);
	/* shouwd not happen evew */
	if (!fmt)
		wetuwn;

	/* update sspp */
	_dpu_pwane_cowow_fiww_pipe(pstate, &pstate->pipe, &pstate->pipe_cfg.dst_wect,
				   fiww_cowow, fmt);

	if (pstate->w_pipe.sspp)
		_dpu_pwane_cowow_fiww_pipe(pstate, &pstate->w_pipe, &pstate->w_pipe_cfg.dst_wect,
					   fiww_cowow, fmt);
}

static int dpu_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
		stwuct dwm_pwane_state *new_state)
{
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(new_state);
	stwuct dpu_hw_fmt_wayout wayout;
	stwuct dpu_kms *kms = _dpu_pwane_get_kms(&pdpu->base);
	int wet;

	if (!new_state->fb)
		wetuwn 0;

	DPU_DEBUG_PWANE(pdpu, "FB[%u]\n", fb->base.id);

	/* cache aspace */
	pstate->aspace = kms->base.aspace;

	/*
	 * TODO: Need to sowt out the msm_fwamebuffew_pwepawe() caww bewow so
	 *       we can use msm_atomic_pwepawe_fb() instead of doing the
	 *       impwicit fence and fb pwepawe by hand hewe.
	 */
	dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);

	if (pstate->aspace) {
		wet = msm_fwamebuffew_pwepawe(new_state->fb,
				pstate->aspace, pstate->needs_diwtyfb);
		if (wet) {
			DPU_EWWOW("faiwed to pwepawe fwamebuffew\n");
			wetuwn wet;
		}
	}

	/* vawidate fwamebuffew wayout befowe commit */
	wet = dpu_fowmat_popuwate_wayout(pstate->aspace,
			new_state->fb, &wayout);
	if (wet) {
		DPU_EWWOW_PWANE(pdpu, "faiwed to get fowmat wayout, %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void dpu_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
		stwuct dwm_pwane_state *owd_state)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_pwane_state *owd_pstate;

	if (!owd_state || !owd_state->fb)
		wetuwn;

	owd_pstate = to_dpu_pwane_state(owd_state);

	DPU_DEBUG_PWANE(pdpu, "FB[%u]\n", owd_state->fb->base.id);

	msm_fwamebuffew_cweanup(owd_state->fb, owd_pstate->aspace,
				owd_pstate->needs_diwtyfb);
}

static int dpu_pwane_check_inwine_wotation(stwuct dpu_pwane *pdpu,
						const stwuct dpu_sspp_sub_bwks *sbwk,
						stwuct dwm_wect swc, const stwuct dpu_fowmat *fmt)
{
	size_t num_fowmats;
	const u32 *suppowted_fowmats;

	if (!sbwk->wotation_cfg) {
		DPU_EWWOW("invawid wotation cfg\n");
		wetuwn -EINVAW;
	}

	if (dwm_wect_width(&swc) > sbwk->wotation_cfg->wot_maxheight) {
		DPU_DEBUG_PWANE(pdpu, "invawid height fow inwine wot:%d max:%d\n",
				swc.y2, sbwk->wotation_cfg->wot_maxheight);
		wetuwn -EINVAW;
	}

	suppowted_fowmats = sbwk->wotation_cfg->wot_fowmat_wist;
	num_fowmats = sbwk->wotation_cfg->wot_num_fowmats;

	if (!DPU_FOWMAT_IS_UBWC(fmt) ||
		!dpu_find_fowmat(fmt->base.pixew_fowmat, suppowted_fowmats, num_fowmats))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dpu_pwane_atomic_check_pipe(stwuct dpu_pwane *pdpu,
		stwuct dpu_sw_pipe *pipe,
		stwuct dpu_sw_pipe_cfg *pipe_cfg,
		const stwuct dpu_fowmat *fmt,
		const stwuct dwm_dispway_mode *mode)
{
	uint32_t min_swc_size;
	stwuct dpu_kms *kms = _dpu_pwane_get_kms(&pdpu->base);

	min_swc_size = DPU_FOWMAT_IS_YUV(fmt) ? 2 : 1;

	if (DPU_FOWMAT_IS_YUV(fmt) &&
	    (!pipe->sspp->cap->sbwk->scawew_bwk.wen ||
	     !pipe->sspp->cap->sbwk->csc_bwk.wen)) {
		DPU_DEBUG_PWANE(pdpu,
				"pwane doesn't have scawew/csc fow yuv\n");
		wetuwn -EINVAW;
	}

	/* check swc bounds */
	if (dwm_wect_width(&pipe_cfg->swc_wect) < min_swc_size ||
	    dwm_wect_height(&pipe_cfg->swc_wect) < min_swc_size) {
		DPU_DEBUG_PWANE(pdpu, "invawid souwce " DWM_WECT_FMT "\n",
				DWM_WECT_AWG(&pipe_cfg->swc_wect));
		wetuwn -E2BIG;
	}

	/* vawid yuv image */
	if (DPU_FOWMAT_IS_YUV(fmt) &&
	    (pipe_cfg->swc_wect.x1 & 0x1 ||
	     pipe_cfg->swc_wect.y1 & 0x1 ||
	     dwm_wect_width(&pipe_cfg->swc_wect) & 0x1 ||
	     dwm_wect_height(&pipe_cfg->swc_wect) & 0x1)) {
		DPU_DEBUG_PWANE(pdpu, "invawid yuv souwce " DWM_WECT_FMT "\n",
				DWM_WECT_AWG(&pipe_cfg->swc_wect));
		wetuwn -EINVAW;
	}

	/* min dst suppowt */
	if (dwm_wect_width(&pipe_cfg->dst_wect) < 0x1 ||
	    dwm_wect_height(&pipe_cfg->dst_wect) < 0x1) {
		DPU_DEBUG_PWANE(pdpu, "invawid dest wect " DWM_WECT_FMT "\n",
				DWM_WECT_AWG(&pipe_cfg->dst_wect));
		wetuwn -EINVAW;
	}

	/* max cwk check */
	if (_dpu_pwane_cawc_cwk(mode, pipe_cfg) > kms->pewf.max_cowe_cwk_wate) {
		DPU_DEBUG_PWANE(pdpu, "pwane exceeds max mdp cowe cwk wimits\n");
		wetuwn -E2BIG;
	}

	wetuwn 0;
}

static int dpu_pwane_atomic_check(stwuct dwm_pwane *pwane,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	int wet = 0, min_scawe;
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_kms *kms = _dpu_pwane_get_kms(&pdpu->base);
	u64 max_mdp_cwk_wate = kms->pewf.max_cowe_cwk_wate;
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(new_pwane_state);
	stwuct dpu_sw_pipe *pipe = &pstate->pipe;
	stwuct dpu_sw_pipe *w_pipe = &pstate->w_pipe;
	const stwuct dwm_cwtc_state *cwtc_state = NUWW;
	const stwuct dpu_fowmat *fmt;
	stwuct dpu_sw_pipe_cfg *pipe_cfg = &pstate->pipe_cfg;
	stwuct dpu_sw_pipe_cfg *w_pipe_cfg = &pstate->w_pipe_cfg;
	stwuct dwm_wect fb_wect = { 0 };
	uint32_t max_winewidth;
	unsigned int wotation;
	uint32_t suppowted_wotations;
	const stwuct dpu_sspp_cfg *pipe_hw_caps = pstate->pipe.sspp->cap;
	const stwuct dpu_sspp_sub_bwks *sbwk = pstate->pipe.sspp->cap->sbwk;

	if (new_pwane_state->cwtc)
		cwtc_state = dwm_atomic_get_new_cwtc_state(state,
							   new_pwane_state->cwtc);

	min_scawe = FWAC_16_16(1, sbwk->maxupscawe);
	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  min_scawe,
						  sbwk->maxdwnscawe << 16,
						  twue, twue);
	if (wet) {
		DPU_DEBUG_PWANE(pdpu, "Check pwane state faiwed (%d)\n", wet);
		wetuwn wet;
	}
	if (!new_pwane_state->visibwe)
		wetuwn 0;

	pipe->muwtiwect_index = DPU_SSPP_WECT_SOWO;
	pipe->muwtiwect_mode = DPU_SSPP_MUWTIWECT_NONE;
	w_pipe->muwtiwect_index = DPU_SSPP_WECT_SOWO;
	w_pipe->muwtiwect_mode = DPU_SSPP_MUWTIWECT_NONE;
	w_pipe->sspp = NUWW;

	pstate->stage = DPU_STAGE_0 + pstate->base.nowmawized_zpos;
	if (pstate->stage >= pdpu->catawog->caps->max_mixew_bwendstages) {
		DPU_EWWOW("> %d pwane stages assigned\n",
			  pdpu->catawog->caps->max_mixew_bwendstages - DPU_STAGE_0);
		wetuwn -EINVAW;
	}

	pipe_cfg->swc_wect = new_pwane_state->swc;

	/* state->swc is 16.16, swc_wect is not */
	pipe_cfg->swc_wect.x1 >>= 16;
	pipe_cfg->swc_wect.x2 >>= 16;
	pipe_cfg->swc_wect.y1 >>= 16;
	pipe_cfg->swc_wect.y2 >>= 16;

	pipe_cfg->dst_wect = new_pwane_state->dst;

	fb_wect.x2 = new_pwane_state->fb->width;
	fb_wect.y2 = new_pwane_state->fb->height;

	/* Ensuwe fb size is suppowted */
	if (dwm_wect_width(&fb_wect) > MAX_IMG_WIDTH ||
	    dwm_wect_height(&fb_wect) > MAX_IMG_HEIGHT) {
		DPU_DEBUG_PWANE(pdpu, "invawid fwamebuffew " DWM_WECT_FMT "\n",
				DWM_WECT_AWG(&fb_wect));
		wetuwn -E2BIG;
	}

	fmt = to_dpu_fowmat(msm_fwamebuffew_fowmat(new_pwane_state->fb));

	max_winewidth = pdpu->catawog->caps->max_winewidth;

	if ((dwm_wect_width(&pipe_cfg->swc_wect) > max_winewidth) ||
	     _dpu_pwane_cawc_cwk(&cwtc_state->adjusted_mode, pipe_cfg) > max_mdp_cwk_wate) {
		/*
		 * In pawawwew muwtiwect case onwy the hawf of the usuaw width
		 * is suppowted fow tiwed fowmats. If we awe hewe, we know that
		 * fuww width is mowe than max_winewidth, thus each wect is
		 * widew than awwowed.
		 */
		if (DPU_FOWMAT_IS_UBWC(fmt) &&
		    dwm_wect_width(&pipe_cfg->swc_wect) > max_winewidth) {
			DPU_DEBUG_PWANE(pdpu, "invawid swc " DWM_WECT_FMT " wine:%u, tiwed fowmat\n",
					DWM_WECT_AWG(&pipe_cfg->swc_wect), max_winewidth);
			wetuwn -E2BIG;
		}

		if (dwm_wect_width(&pipe_cfg->swc_wect) > 2 * max_winewidth) {
			DPU_DEBUG_PWANE(pdpu, "invawid swc " DWM_WECT_FMT " wine:%u\n",
					DWM_WECT_AWG(&pipe_cfg->swc_wect), max_winewidth);
			wetuwn -E2BIG;
		}

		if (dwm_wect_width(&pipe_cfg->swc_wect) != dwm_wect_width(&pipe_cfg->dst_wect) ||
		    dwm_wect_height(&pipe_cfg->swc_wect) != dwm_wect_height(&pipe_cfg->dst_wect) ||
		    (!test_bit(DPU_SSPP_SMAWT_DMA_V1, &pipe->sspp->cap->featuwes) &&
		     !test_bit(DPU_SSPP_SMAWT_DMA_V2, &pipe->sspp->cap->featuwes)) ||
		    DPU_FOWMAT_IS_YUV(fmt)) {
			DPU_DEBUG_PWANE(pdpu, "invawid swc " DWM_WECT_FMT " wine:%u, can't use spwit souwce\n",
					DWM_WECT_AWG(&pipe_cfg->swc_wect), max_winewidth);
			wetuwn -E2BIG;
		}

		/*
		 * Use muwtiwect fow wide pwane. We do not suppowt dynamic
		 * assignment of SSPPs, so we know the configuwation.
		 */
		pipe->muwtiwect_index = DPU_SSPP_WECT_0;
		pipe->muwtiwect_mode = DPU_SSPP_MUWTIWECT_PAWAWWEW;

		w_pipe->sspp = pipe->sspp;
		w_pipe->muwtiwect_index = DPU_SSPP_WECT_1;
		w_pipe->muwtiwect_mode = DPU_SSPP_MUWTIWECT_PAWAWWEW;

		*w_pipe_cfg = *pipe_cfg;
		pipe_cfg->swc_wect.x2 = (pipe_cfg->swc_wect.x1 + pipe_cfg->swc_wect.x2) >> 1;
		pipe_cfg->dst_wect.x2 = (pipe_cfg->dst_wect.x1 + pipe_cfg->dst_wect.x2) >> 1;
		w_pipe_cfg->swc_wect.x1 = pipe_cfg->swc_wect.x2;
		w_pipe_cfg->dst_wect.x1 = pipe_cfg->dst_wect.x2;
	}

	wet = dpu_pwane_atomic_check_pipe(pdpu, pipe, pipe_cfg, fmt, &cwtc_state->adjusted_mode);
	if (wet)
		wetuwn wet;

	if (w_pipe->sspp) {
		wet = dpu_pwane_atomic_check_pipe(pdpu, w_pipe, w_pipe_cfg, fmt,
						  &cwtc_state->adjusted_mode);
		if (wet)
			wetuwn wet;
	}

	suppowted_wotations = DWM_MODE_WEFWECT_MASK | DWM_MODE_WOTATE_0;

	if (pipe_hw_caps->featuwes & BIT(DPU_SSPP_INWINE_WOTATION))
		suppowted_wotations |= DWM_MODE_WOTATE_90;

	wotation = dwm_wotation_simpwify(new_pwane_state->wotation,
					suppowted_wotations);

	if ((pipe_hw_caps->featuwes & BIT(DPU_SSPP_INWINE_WOTATION)) &&
		(wotation & DWM_MODE_WOTATE_90)) {
		wet = dpu_pwane_check_inwine_wotation(pdpu, sbwk, pipe_cfg->swc_wect, fmt);
		if (wet)
			wetuwn wet;
	}

	pstate->wotation = wotation;
	pstate->needs_qos_wemap = dwm_atomic_cwtc_needs_modeset(cwtc_state);

	wetuwn 0;
}

static void dpu_pwane_fwush_csc(stwuct dpu_pwane *pdpu, stwuct dpu_sw_pipe *pipe)
{
	const stwuct dpu_fowmat *fowmat =
		to_dpu_fowmat(msm_fwamebuffew_fowmat(pdpu->base.state->fb));
	const stwuct dpu_csc_cfg *csc_ptw;

	if (!pipe->sspp || !pipe->sspp->ops.setup_csc)
		wetuwn;

	csc_ptw = _dpu_pwane_get_csc(pipe, fowmat);
	if (!csc_ptw)
		wetuwn;

	DPU_DEBUG_PWANE(pdpu, "using 0x%X 0x%X 0x%X...\n",
			csc_ptw->csc_mv[0],
			csc_ptw->csc_mv[1],
			csc_ptw->csc_mv[2]);

	pipe->sspp->ops.setup_csc(pipe->sspp, csc_ptw);

}

void dpu_pwane_fwush(stwuct dwm_pwane *pwane)
{
	stwuct dpu_pwane *pdpu;
	stwuct dpu_pwane_state *pstate;

	if (!pwane || !pwane->state) {
		DPU_EWWOW("invawid pwane\n");
		wetuwn;
	}

	pdpu = to_dpu_pwane(pwane);
	pstate = to_dpu_pwane_state(pwane->state);

	/*
	 * These updates have to be done immediatewy befowe the pwane fwush
	 * timing, and may not be moved to the atomic_update/mode_set functions.
	 */
	if (pdpu->is_ewwow)
		/* fowce white fwame with 100% awpha pipe output on ewwow */
		_dpu_pwane_cowow_fiww(pdpu, 0xFFFFFF, 0xFF);
	ewse if (pdpu->cowow_fiww & DPU_PWANE_COWOW_FIWW_FWAG)
		/* fowce 100% awpha */
		_dpu_pwane_cowow_fiww(pdpu, pdpu->cowow_fiww, 0xFF);
	ewse {
		dpu_pwane_fwush_csc(pdpu, &pstate->pipe);
		dpu_pwane_fwush_csc(pdpu, &pstate->w_pipe);
	}

	/* fwag h/w fwush compwete */
	if (pwane->state)
		pstate->pending = fawse;
}

/**
 * dpu_pwane_set_ewwow: enabwe/disabwe ewwow condition
 * @pwane: pointew to dwm_pwane stwuctuwe
 * @ewwow: ewwow vawue to set
 */
void dpu_pwane_set_ewwow(stwuct dwm_pwane *pwane, boow ewwow)
{
	stwuct dpu_pwane *pdpu;

	if (!pwane)
		wetuwn;

	pdpu = to_dpu_pwane(pwane);
	pdpu->is_ewwow = ewwow;
}

static void dpu_pwane_sspp_update_pipe(stwuct dwm_pwane *pwane,
				       stwuct dpu_sw_pipe *pipe,
				       stwuct dpu_sw_pipe_cfg *pipe_cfg,
				       const stwuct dpu_fowmat *fmt,
				       int fwame_wate,
				       stwuct dpu_hw_fmt_wayout *wayout)
{
	uint32_t swc_fwags;
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(state);

	if (wayout && pipe->sspp->ops.setup_souwceaddwess) {
		twace_dpu_pwane_set_scanout(pipe, wayout);
		pipe->sspp->ops.setup_souwceaddwess(pipe, wayout);
	}

	/* ovewwide fow cowow fiww */
	if (pdpu->cowow_fiww & DPU_PWANE_COWOW_FIWW_FWAG) {
		_dpu_pwane_set_qos_ctww(pwane, pipe, fawse);

		/* skip wemaining pwocessing on cowow fiww */
		wetuwn;
	}

	if (pipe->sspp->ops.setup_wects) {
		pipe->sspp->ops.setup_wects(pipe,
				pipe_cfg);
	}

	_dpu_pwane_setup_scawew(pipe, fmt, fawse, pipe_cfg, pstate->wotation);

	if (pipe->sspp->ops.setup_muwtiwect)
		pipe->sspp->ops.setup_muwtiwect(
				pipe);

	if (pipe->sspp->ops.setup_fowmat) {
		unsigned int wotation = pstate->wotation;

		swc_fwags = 0x0;

		if (wotation & DWM_MODE_WEFWECT_X)
			swc_fwags |= DPU_SSPP_FWIP_WW;

		if (wotation & DWM_MODE_WEFWECT_Y)
			swc_fwags |= DPU_SSPP_FWIP_UD;

		if (wotation & DWM_MODE_WOTATE_90)
			swc_fwags |= DPU_SSPP_WOT_90;

		/* update fowmat */
		pipe->sspp->ops.setup_fowmat(pipe, fmt, swc_fwags);

		if (pipe->sspp->ops.setup_cdp) {
			const stwuct dpu_pewf_cfg *pewf = pdpu->catawog->pewf;

			pipe->sspp->ops.setup_cdp(pipe, fmt,
						  pewf->cdp_cfg[DPU_PEWF_CDP_USAGE_WT].wd_enabwe);
		}
	}

	_dpu_pwane_set_qos_wut(pwane, pipe, fmt, pipe_cfg);

	if (pipe->sspp->idx != SSPP_CUWSOW0 &&
	    pipe->sspp->idx != SSPP_CUWSOW1)
		_dpu_pwane_set_ot_wimit(pwane, pipe, pipe_cfg, fwame_wate);

	if (pstate->needs_qos_wemap)
		_dpu_pwane_set_qos_wemap(pwane, pipe);
}

static void dpu_pwane_sspp_atomic_update(stwuct dwm_pwane *pwane)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(state);
	stwuct dpu_sw_pipe *pipe = &pstate->pipe;
	stwuct dpu_sw_pipe *w_pipe = &pstate->w_pipe;
	stwuct dwm_cwtc *cwtc = state->cwtc;
	stwuct dwm_fwamebuffew *fb = state->fb;
	boow is_wt_pipe;
	const stwuct dpu_fowmat *fmt =
		to_dpu_fowmat(msm_fwamebuffew_fowmat(fb));
	stwuct dpu_sw_pipe_cfg *pipe_cfg = &pstate->pipe_cfg;
	stwuct dpu_sw_pipe_cfg *w_pipe_cfg = &pstate->w_pipe_cfg;
	stwuct dpu_kms *kms = _dpu_pwane_get_kms(&pdpu->base);
	stwuct msm_gem_addwess_space *aspace = kms->base.aspace;
	stwuct dpu_hw_fmt_wayout wayout;
	boow wayout_vawid = fawse;
	int wet;

	wet = dpu_fowmat_popuwate_wayout(aspace, fb, &wayout);
	if (wet)
		DPU_EWWOW_PWANE(pdpu, "faiwed to get fowmat wayout, %d\n", wet);
	ewse
		wayout_vawid = twue;

	pstate->pending = twue;

	is_wt_pipe = (dpu_cwtc_get_cwient_type(cwtc) != NWT_CWIENT);
	pstate->needs_qos_wemap |= (is_wt_pipe != pdpu->is_wt_pipe);
	pdpu->is_wt_pipe = is_wt_pipe;

	DPU_DEBUG_PWANE(pdpu, "FB[%u] " DWM_WECT_FP_FMT "->cwtc%u " DWM_WECT_FMT
			", %4.4s ubwc %d\n", fb->base.id, DWM_WECT_FP_AWG(&state->swc),
			cwtc->base.id, DWM_WECT_AWG(&state->dst),
			(chaw *)&fmt->base.pixew_fowmat, DPU_FOWMAT_IS_UBWC(fmt));

	dpu_pwane_sspp_update_pipe(pwane, pipe, pipe_cfg, fmt,
				   dwm_mode_vwefwesh(&cwtc->mode),
				   wayout_vawid ? &wayout : NUWW);

	if (w_pipe->sspp) {
		dpu_pwane_sspp_update_pipe(pwane, w_pipe, w_pipe_cfg, fmt,
					   dwm_mode_vwefwesh(&cwtc->mode),
					   wayout_vawid ? &wayout : NUWW);
	}

	if (pstate->needs_qos_wemap)
		pstate->needs_qos_wemap = fawse;

	pstate->pwane_fetch_bw = _dpu_pwane_cawc_bw(pdpu->catawog, fmt,
						    &cwtc->mode, pipe_cfg);

	pstate->pwane_cwk = _dpu_pwane_cawc_cwk(&cwtc->mode, pipe_cfg);

	if (w_pipe->sspp) {
		pstate->pwane_fetch_bw += _dpu_pwane_cawc_bw(pdpu->catawog, fmt, &cwtc->mode, w_pipe_cfg);

		pstate->pwane_cwk = max(pstate->pwane_cwk, _dpu_pwane_cawc_cwk(&cwtc->mode, w_pipe_cfg));
	}
}

static void _dpu_pwane_atomic_disabwe(stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(state);
	stwuct dpu_sw_pipe *w_pipe = &pstate->w_pipe;

	twace_dpu_pwane_disabwe(DWMID(pwane), fawse,
				pstate->pipe.muwtiwect_mode);

	if (w_pipe->sspp) {
		w_pipe->muwtiwect_index = DPU_SSPP_WECT_SOWO;
		w_pipe->muwtiwect_mode = DPU_SSPP_MUWTIWECT_NONE;

		if (w_pipe->sspp->ops.setup_muwtiwect)
			w_pipe->sspp->ops.setup_muwtiwect(w_pipe);
	}

	pstate->pending = twue;
}

static void dpu_pwane_atomic_update(stwuct dwm_pwane *pwane,
				stwuct dwm_atomic_state *state)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);

	pdpu->is_ewwow = fawse;

	DPU_DEBUG_PWANE(pdpu, "\n");

	if (!new_state->visibwe) {
		_dpu_pwane_atomic_disabwe(pwane);
	} ewse {
		dpu_pwane_sspp_atomic_update(pwane);
	}
}

static void dpu_pwane_destwoy_state(stwuct dwm_pwane *pwane,
		stwuct dwm_pwane_state *state)
{
	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(to_dpu_pwane_state(state));
}

static stwuct dwm_pwane_state *
dpu_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dpu_pwane *pdpu;
	stwuct dpu_pwane_state *pstate;
	stwuct dpu_pwane_state *owd_state;

	if (!pwane) {
		DPU_EWWOW("invawid pwane\n");
		wetuwn NUWW;
	} ewse if (!pwane->state) {
		DPU_EWWOW("invawid pwane state\n");
		wetuwn NUWW;
	}

	owd_state = to_dpu_pwane_state(pwane->state);
	pdpu = to_dpu_pwane(pwane);
	pstate = kmemdup(owd_state, sizeof(*owd_state), GFP_KEWNEW);
	if (!pstate) {
		DPU_EWWOW_PWANE(pdpu, "faiwed to awwocate state\n");
		wetuwn NUWW;
	}

	DPU_DEBUG_PWANE(pdpu, "\n");

	pstate->pending = fawse;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &pstate->base);

	wetuwn &pstate->base;
}

static const chaw * const muwtiwect_mode_name[] = {
	[DPU_SSPP_MUWTIWECT_NONE] = "none",
	[DPU_SSPP_MUWTIWECT_PAWAWWEW] = "pawawwew",
	[DPU_SSPP_MUWTIWECT_TIME_MX] = "time_mx",
};

static const chaw * const muwtiwect_index_name[] = {
	[DPU_SSPP_WECT_SOWO] = "sowo",
	[DPU_SSPP_WECT_0] = "wect_0",
	[DPU_SSPP_WECT_1] = "wect_1",
};

static const chaw *dpu_get_muwtiwect_mode(enum dpu_sspp_muwtiwect_mode mode)
{
	if (WAWN_ON(mode >= AWWAY_SIZE(muwtiwect_mode_name)))
		wetuwn "unknown";

	wetuwn muwtiwect_mode_name[mode];
}

static const chaw *dpu_get_muwtiwect_index(enum dpu_sspp_muwtiwect_index index)
{
	if (WAWN_ON(index >= AWWAY_SIZE(muwtiwect_index_name)))
		wetuwn "unknown";

	wetuwn muwtiwect_index_name[index];
}

static void dpu_pwane_atomic_pwint_state(stwuct dwm_pwintew *p,
		const stwuct dwm_pwane_state *state)
{
	const stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(state);
	const stwuct dpu_sw_pipe *pipe = &pstate->pipe;
	const stwuct dpu_sw_pipe_cfg *pipe_cfg = &pstate->pipe_cfg;
	const stwuct dpu_sw_pipe *w_pipe = &pstate->w_pipe;
	const stwuct dpu_sw_pipe_cfg *w_pipe_cfg = &pstate->w_pipe_cfg;

	dwm_pwintf(p, "\tstage=%d\n", pstate->stage);

	dwm_pwintf(p, "\tsspp[0]=%s\n", pipe->sspp->cap->name);
	dwm_pwintf(p, "\tmuwtiwect_mode[0]=%s\n", dpu_get_muwtiwect_mode(pipe->muwtiwect_mode));
	dwm_pwintf(p, "\tmuwtiwect_index[0]=%s\n",
		   dpu_get_muwtiwect_index(pipe->muwtiwect_index));
	dwm_pwintf(p, "\tswc[0]=" DWM_WECT_FMT "\n", DWM_WECT_AWG(&pipe_cfg->swc_wect));
	dwm_pwintf(p, "\tdst[0]=" DWM_WECT_FMT "\n", DWM_WECT_AWG(&pipe_cfg->dst_wect));

	if (w_pipe->sspp) {
		dwm_pwintf(p, "\tsspp[1]=%s\n", w_pipe->sspp->cap->name);
		dwm_pwintf(p, "\tmuwtiwect_mode[1]=%s\n",
			   dpu_get_muwtiwect_mode(w_pipe->muwtiwect_mode));
		dwm_pwintf(p, "\tmuwtiwect_index[1]=%s\n",
			   dpu_get_muwtiwect_index(w_pipe->muwtiwect_index));
		dwm_pwintf(p, "\tswc[1]=" DWM_WECT_FMT "\n", DWM_WECT_AWG(&w_pipe_cfg->swc_wect));
		dwm_pwintf(p, "\tdst[1]=" DWM_WECT_FMT "\n", DWM_WECT_AWG(&w_pipe_cfg->dst_wect));
	}
}

static void dpu_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct dpu_pwane *pdpu;
	stwuct dpu_pwane_state *pstate;
	stwuct dpu_kms *dpu_kms = _dpu_pwane_get_kms(pwane);

	if (!pwane) {
		DPU_EWWOW("invawid pwane\n");
		wetuwn;
	}

	pdpu = to_dpu_pwane(pwane);
	DPU_DEBUG_PWANE(pdpu, "\n");

	/* wemove pwevious state, if pwesent */
	if (pwane->state) {
		dpu_pwane_destwoy_state(pwane, pwane->state);
		pwane->state = NUWW;
	}

	pstate = kzawwoc(sizeof(*pstate), GFP_KEWNEW);
	if (!pstate) {
		DPU_EWWOW_PWANE(pdpu, "faiwed to awwocate state\n");
		wetuwn;
	}

	/*
	 * Set the SSPP hewe untiw we have pwopew viwtuawized DPU pwanes.
	 * This is the pwace whewe the state is awwocated, so fiww it fuwwy.
	 */
	pstate->pipe.sspp = dpu_wm_get_sspp(&dpu_kms->wm, pdpu->pipe);
	pstate->pipe.muwtiwect_index = DPU_SSPP_WECT_SOWO;
	pstate->pipe.muwtiwect_mode = DPU_SSPP_MUWTIWECT_NONE;

	pstate->w_pipe.sspp = NUWW;

	__dwm_atomic_hewpew_pwane_weset(pwane, &pstate->base);
}

#ifdef CONFIG_DEBUG_FS
void dpu_pwane_dangew_signaw_ctww(stwuct dwm_pwane *pwane, boow enabwe)
{
	stwuct dpu_pwane *pdpu = to_dpu_pwane(pwane);
	stwuct dpu_pwane_state *pstate = to_dpu_pwane_state(pwane->state);
	stwuct dpu_kms *dpu_kms = _dpu_pwane_get_kms(pwane);

	if (!pdpu->is_wt_pipe)
		wetuwn;

	pm_wuntime_get_sync(&dpu_kms->pdev->dev);
	_dpu_pwane_set_qos_ctww(pwane, &pstate->pipe, enabwe);
	if (pstate->w_pipe.sspp)
		_dpu_pwane_set_qos_ctww(pwane, &pstate->w_pipe, enabwe);
	pm_wuntime_put_sync(&dpu_kms->pdev->dev);
}
#endif

static boow dpu_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
		uint32_t fowmat, uint64_t modifiew)
{
	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn twue;

	if (modifiew == DWM_FOWMAT_MOD_QCOM_COMPWESSED)
		wetuwn dpu_find_fowmat(fowmat, qcom_compwessed_suppowted_fowmats,
				AWWAY_SIZE(qcom_compwessed_suppowted_fowmats));

	wetuwn fawse;
}

static const stwuct dwm_pwane_funcs dpu_pwane_funcs = {
		.update_pwane = dwm_atomic_hewpew_update_pwane,
		.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
		.weset = dpu_pwane_weset,
		.atomic_dupwicate_state = dpu_pwane_dupwicate_state,
		.atomic_destwoy_state = dpu_pwane_destwoy_state,
		.atomic_pwint_state = dpu_pwane_atomic_pwint_state,
		.fowmat_mod_suppowted = dpu_pwane_fowmat_mod_suppowted,
};

static const stwuct dwm_pwane_hewpew_funcs dpu_pwane_hewpew_funcs = {
		.pwepawe_fb = dpu_pwane_pwepawe_fb,
		.cweanup_fb = dpu_pwane_cweanup_fb,
		.atomic_check = dpu_pwane_atomic_check,
		.atomic_update = dpu_pwane_atomic_update,
};

/* initiawize pwane */
stwuct dwm_pwane *dpu_pwane_init(stwuct dwm_device *dev,
		uint32_t pipe, enum dwm_pwane_type type,
		unsigned wong possibwe_cwtcs)
{
	stwuct dwm_pwane *pwane = NUWW;
	const uint32_t *fowmat_wist;
	stwuct dpu_pwane *pdpu;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dpu_kms *kms = to_dpu_kms(pwiv->kms);
	stwuct dpu_hw_sspp *pipe_hw;
	uint32_t num_fowmats;
	uint32_t suppowted_wotations;
	int wet;

	/* initiawize undewwying h/w dwivew */
	pipe_hw = dpu_wm_get_sspp(&kms->wm, pipe);
	if (!pipe_hw || !pipe_hw->cap || !pipe_hw->cap->sbwk) {
		DPU_EWWOW("[%u]SSPP is invawid\n", pipe);
		wetuwn EWW_PTW(-EINVAW);
	}

	fowmat_wist = pipe_hw->cap->sbwk->fowmat_wist;
	num_fowmats = pipe_hw->cap->sbwk->num_fowmats;

	pdpu = dwmm_univewsaw_pwane_awwoc(dev, stwuct dpu_pwane, base,
				0xff, &dpu_pwane_funcs,
				fowmat_wist, num_fowmats,
				suppowted_fowmat_modifiews, type, NUWW);
	if (IS_EWW(pdpu))
		wetuwn EWW_CAST(pdpu);

	/* cache wocaw stuff fow watew */
	pwane = &pdpu->base;
	pdpu->pipe = pipe;

	pdpu->catawog = kms->catawog;

	wet = dwm_pwane_cweate_zpos_pwopewty(pwane, 0, 0, DPU_ZPOS_MAX);
	if (wet)
		DPU_EWWOW("faiwed to instaww zpos pwopewty, wc = %d\n", wet);

	dwm_pwane_cweate_awpha_pwopewty(pwane);
	dwm_pwane_cweate_bwend_mode_pwopewty(pwane,
			BIT(DWM_MODE_BWEND_PIXEW_NONE) |
			BIT(DWM_MODE_BWEND_PWEMUWTI) |
			BIT(DWM_MODE_BWEND_COVEWAGE));

	suppowted_wotations = DWM_MODE_WEFWECT_MASK | DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_180;

	if (pipe_hw->cap->featuwes & BIT(DPU_SSPP_INWINE_WOTATION))
		suppowted_wotations |= DWM_MODE_WOTATE_MASK;

	dwm_pwane_cweate_wotation_pwopewty(pwane,
		    DWM_MODE_WOTATE_0, suppowted_wotations);

	dwm_pwane_enabwe_fb_damage_cwips(pwane);

	/* success! finawize initiawization */
	dwm_pwane_hewpew_add(pwane, &dpu_pwane_hewpew_funcs);

	DPU_DEBUG("%s cweated fow pipe:%u id:%u\n", pwane->name,
					pipe, pwane->base.id);
	wetuwn pwane;
}
