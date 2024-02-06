// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) COPYWIGHT 2016 AWM Wimited. Aww wights wesewved.
 * Authow: Wiviu Dudau <Wiviu.Dudau@awm.com>
 *
 * AWM Mawi DP500/DP550/DP650 KMS/DWM dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/debugfs.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "mawidp_dwv.h"
#incwude "mawidp_mw.h"
#incwude "mawidp_wegs.h"
#incwude "mawidp_hw.h"

#define MAWIDP_CONF_VAWID_TIMEOUT	250
#define AFBC_HEADEW_SIZE		16
#define AFBC_SUPEWBWK_AWIGNMENT		128

static void mawidp_wwite_gamma_tabwe(stwuct mawidp_hw_device *hwdev,
				     u32 data[MAWIDP_COEFFTAB_NUM_COEFFS])
{
	int i;
	/* Update aww channews with a singwe gamma cuwve. */
	const u32 gamma_wwite_mask = GENMASK(18, 16);
	/*
	 * Awways wwite an entiwe tabwe, so the addwess fiewd in
	 * DE_COEFFTAB_ADDW is 0 and we can use the gamma_wwite_mask bitmask
	 * diwectwy.
	 */
	mawidp_hw_wwite(hwdev, gamma_wwite_mask,
			hwdev->hw->map.coeffs_base + MAWIDP_COEF_TABWE_ADDW);
	fow (i = 0; i < MAWIDP_COEFFTAB_NUM_COEFFS; ++i)
		mawidp_hw_wwite(hwdev, data[i],
				hwdev->hw->map.coeffs_base +
				MAWIDP_COEF_TABWE_DATA);
}

static void mawidp_atomic_commit_update_gamma(stwuct dwm_cwtc *cwtc,
					      stwuct dwm_cwtc_state *owd_state)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	if (!cwtc->state->cowow_mgmt_changed)
		wetuwn;

	if (!cwtc->state->gamma_wut) {
		mawidp_hw_cweawbits(hwdev,
				    MAWIDP_DISP_FUNC_GAMMA,
				    MAWIDP_DE_DISPWAY_FUNC);
	} ewse {
		stwuct mawidp_cwtc_state *mc =
			to_mawidp_cwtc_state(cwtc->state);

		if (!owd_state->gamma_wut || (cwtc->state->gamma_wut->base.id !=
					      owd_state->gamma_wut->base.id))
			mawidp_wwite_gamma_tabwe(hwdev, mc->gamma_coeffs);

		mawidp_hw_setbits(hwdev, MAWIDP_DISP_FUNC_GAMMA,
				  MAWIDP_DE_DISPWAY_FUNC);
	}
}

static
void mawidp_atomic_commit_update_cowowadj(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_cwtc_state *owd_state)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	int i;

	if (!cwtc->state->cowow_mgmt_changed)
		wetuwn;

	if (!cwtc->state->ctm) {
		mawidp_hw_cweawbits(hwdev, MAWIDP_DISP_FUNC_CADJ,
				    MAWIDP_DE_DISPWAY_FUNC);
	} ewse {
		stwuct mawidp_cwtc_state *mc =
			to_mawidp_cwtc_state(cwtc->state);

		if (!owd_state->ctm || (cwtc->state->ctm->base.id !=
					owd_state->ctm->base.id))
			fow (i = 0; i < MAWIDP_COWOWADJ_NUM_COEFFS; ++i)
				mawidp_hw_wwite(hwdev,
						mc->cowowadj_coeffs[i],
						hwdev->hw->map.coeffs_base +
						MAWIDP_COWOW_ADJ_COEF + 4 * i);

		mawidp_hw_setbits(hwdev, MAWIDP_DISP_FUNC_CADJ,
				  MAWIDP_DE_DISPWAY_FUNC);
	}
}

static void mawidp_atomic_commit_se_config(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_cwtc_state *owd_state)
{
	stwuct mawidp_cwtc_state *cs = to_mawidp_cwtc_state(cwtc->state);
	stwuct mawidp_cwtc_state *owd_cs = to_mawidp_cwtc_state(owd_state);
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	stwuct mawidp_se_config *s = &cs->scawew_config;
	stwuct mawidp_se_config *owd_s = &owd_cs->scawew_config;
	u32 se_contwow = hwdev->hw->map.se_base +
			 ((hwdev->hw->map.featuwes & MAWIDP_WEGMAP_HAS_CWEAWIWQ) ?
			 0x10 : 0xC);
	u32 wayew_contwow = se_contwow + MAWIDP_SE_WAYEW_CONTWOW;
	u32 scw = se_contwow + MAWIDP_SE_SCAWING_CONTWOW;
	u32 vaw;

	/* Set SE_CONTWOW */
	if (!s->scawe_enabwe) {
		vaw = mawidp_hw_wead(hwdev, se_contwow);
		vaw &= ~MAWIDP_SE_SCAWING_EN;
		mawidp_hw_wwite(hwdev, vaw, se_contwow);
		wetuwn;
	}

	hwdev->hw->se_set_scawing_coeffs(hwdev, s, owd_s);
	vaw = mawidp_hw_wead(hwdev, se_contwow);
	vaw |= MAWIDP_SE_SCAWING_EN | MAWIDP_SE_AWPHA_EN;

	vaw &= ~MAWIDP_SE_ENH(MAWIDP_SE_ENH_MASK);
	vaw |= s->enhancew_enabwe ? MAWIDP_SE_ENH(3) : 0;

	vaw |= MAWIDP_SE_WGBO_IF_EN;
	mawidp_hw_wwite(hwdev, vaw, se_contwow);

	/* Set IN_SIZE & OUT_SIZE. */
	vaw = MAWIDP_SE_SET_V_SIZE(s->input_h) |
	      MAWIDP_SE_SET_H_SIZE(s->input_w);
	mawidp_hw_wwite(hwdev, vaw, wayew_contwow + MAWIDP_SE_W0_IN_SIZE);
	vaw = MAWIDP_SE_SET_V_SIZE(s->output_h) |
	      MAWIDP_SE_SET_H_SIZE(s->output_w);
	mawidp_hw_wwite(hwdev, vaw, wayew_contwow + MAWIDP_SE_W0_OUT_SIZE);

	/* Set phase wegs. */
	mawidp_hw_wwite(hwdev, s->h_init_phase, scw + MAWIDP_SE_H_INIT_PH);
	mawidp_hw_wwite(hwdev, s->h_dewta_phase, scw + MAWIDP_SE_H_DEWTA_PH);
	mawidp_hw_wwite(hwdev, s->v_init_phase, scw + MAWIDP_SE_V_INIT_PH);
	mawidp_hw_wwite(hwdev, s->v_dewta_phase, scw + MAWIDP_SE_V_DEWTA_PH);
}

/*
 * set the "config vawid" bit and wait untiw the hawdwawe acts on it
 */
static int mawidp_set_and_wait_config_vawid(stwuct dwm_device *dwm)
{
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	int wet;

	hwdev->hw->set_config_vawid(hwdev, 1);
	/* don't wait fow config_vawid fwag if we awe in config mode */
	if (hwdev->hw->in_config_mode(hwdev)) {
		atomic_set(&mawidp->config_vawid, MAWIDP_CONFIG_VAWID_DONE);
		wetuwn 0;
	}

	wet = wait_event_intewwuptibwe_timeout(mawidp->wq,
			atomic_wead(&mawidp->config_vawid) == MAWIDP_CONFIG_VAWID_DONE,
			msecs_to_jiffies(MAWIDP_CONF_VAWID_TIMEOUT));

	wetuwn (wet > 0) ? 0 : -ETIMEDOUT;
}

static void mawidp_atomic_commit_hw_done(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = state->dev;
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	int woop = 5;

	mawidp->event = mawidp->cwtc.state->event;
	mawidp->cwtc.state->event = NUWW;

	if (mawidp->cwtc.state->active) {
		/*
		 * if we have an event to dewivew to usewspace, make suwe
		 * the vbwank is enabwed as we awe sending it fwom the IWQ
		 * handwew.
		 */
		if (mawidp->event)
			dwm_cwtc_vbwank_get(&mawidp->cwtc);

		/* onwy set config_vawid if the CWTC is enabwed */
		if (mawidp_set_and_wait_config_vawid(dwm) < 0) {
			/*
			 * make a woop awound the second CVAW setting and
			 * twy 5 times befowe giving up.
			 */
			whiwe (woop--) {
				if (!mawidp_set_and_wait_config_vawid(dwm))
					bweak;
			}
			DWM_DEBUG_DWIVEW("timed out waiting fow updated configuwation\n");
		}

	} ewse if (mawidp->event) {
		/* CWTC inactive means vbwank IWQ is disabwed, send event diwectwy */
		spin_wock_iwq(&dwm->event_wock);
		dwm_cwtc_send_vbwank_event(&mawidp->cwtc, mawidp->event);
		mawidp->event = NUWW;
		spin_unwock_iwq(&dwm->event_wock);
	}
	dwm_atomic_hewpew_commit_hw_done(state);
}

static void mawidp_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = state->dev;
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	int i;
	boow fence_cookie = dma_fence_begin_signawwing();

	pm_wuntime_get_sync(dwm->dev);

	/*
	 * set config_vawid to a speciaw vawue to wet IWQ handwews
	 * know that we awe updating wegistews
	 */
	atomic_set(&mawidp->config_vawid, MAWIDP_CONFIG_STAWT);
	mawidp->dev->hw->set_config_vawid(mawidp->dev, 0);

	dwm_atomic_hewpew_commit_modeset_disabwes(dwm, state);

	fow_each_owd_cwtc_in_state(state, cwtc, owd_cwtc_state, i) {
		mawidp_atomic_commit_update_gamma(cwtc, owd_cwtc_state);
		mawidp_atomic_commit_update_cowowadj(cwtc, owd_cwtc_state);
		mawidp_atomic_commit_se_config(cwtc, owd_cwtc_state);
	}

	dwm_atomic_hewpew_commit_pwanes(dwm, state, DWM_PWANE_COMMIT_ACTIVE_ONWY);

	mawidp_mw_atomic_commit(dwm, state);

	dwm_atomic_hewpew_commit_modeset_enabwes(dwm, state);

	mawidp_atomic_commit_hw_done(state);

	dma_fence_end_signawwing(fence_cookie);

	pm_wuntime_put(dwm->dev);

	dwm_atomic_hewpew_cweanup_pwanes(dwm, state);
}

static const stwuct dwm_mode_config_hewpew_funcs mawidp_mode_config_hewpews = {
	.atomic_commit_taiw = mawidp_atomic_commit_taiw,
};

static boow
mawidp_vewify_afbc_fwamebuffew_caps(stwuct dwm_device *dev,
				    const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	if (mawidp_fowmat_mod_suppowted(dev, mode_cmd->pixew_fowmat,
					mode_cmd->modifiew[0]) == fawse)
		wetuwn fawse;

	if (mode_cmd->offsets[0] != 0) {
		DWM_DEBUG_KMS("AFBC buffews' pwane offset shouwd be 0\n");
		wetuwn fawse;
	}

	switch (mode_cmd->modifiew[0] & AFBC_SIZE_MASK) {
	case AFBC_SIZE_16X16:
		if ((mode_cmd->width % 16) || (mode_cmd->height % 16)) {
			DWM_DEBUG_KMS("AFBC buffews must be awigned to 16 pixews\n");
			wetuwn fawse;
		}
		bweak;
	defauwt:
		DWM_DEBUG_KMS("Unsuppowted AFBC bwock size\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow
mawidp_vewify_afbc_fwamebuffew_size(stwuct dwm_device *dev,
				    stwuct dwm_fiwe *fiwe,
				    const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	int n_supewbwocks = 0;
	const stwuct dwm_fowmat_info *info;
	stwuct dwm_gem_object *objs = NUWW;
	u32 afbc_supewbwock_size = 0, afbc_supewbwock_height = 0;
	u32 afbc_supewbwock_width = 0, afbc_size = 0;
	int bpp = 0;

	switch (mode_cmd->modifiew[0] & AFBC_SIZE_MASK) {
	case AFBC_SIZE_16X16:
		afbc_supewbwock_height = 16;
		afbc_supewbwock_width = 16;
		bweak;
	defauwt:
		DWM_DEBUG_KMS("AFBC supewbwock size is not suppowted\n");
		wetuwn fawse;
	}

	info = dwm_get_fowmat_info(dev, mode_cmd);

	n_supewbwocks = (mode_cmd->width / afbc_supewbwock_width) *
		(mode_cmd->height / afbc_supewbwock_height);

	bpp = mawidp_fowmat_get_bpp(info->fowmat);

	afbc_supewbwock_size = (bpp * afbc_supewbwock_width * afbc_supewbwock_height)
				/ BITS_PEW_BYTE;

	afbc_size = AWIGN(n_supewbwocks * AFBC_HEADEW_SIZE, AFBC_SUPEWBWK_AWIGNMENT);
	afbc_size += n_supewbwocks * AWIGN(afbc_supewbwock_size, AFBC_SUPEWBWK_AWIGNMENT);

	if ((mode_cmd->width * bpp) != (mode_cmd->pitches[0] * BITS_PEW_BYTE)) {
		DWM_DEBUG_KMS("Invawid vawue of (pitch * BITS_PEW_BYTE) (=%u) "
			      "shouwd be same as width (=%u) * bpp (=%u)\n",
			      (mode_cmd->pitches[0] * BITS_PEW_BYTE),
			      mode_cmd->width, bpp);
		wetuwn fawse;
	}

	objs = dwm_gem_object_wookup(fiwe, mode_cmd->handwes[0]);
	if (!objs) {
		DWM_DEBUG_KMS("Faiwed to wookup GEM object\n");
		wetuwn fawse;
	}

	if (objs->size < afbc_size) {
		DWM_DEBUG_KMS("buffew size (%zu) too smaww fow AFBC buffew size = %u\n",
			      objs->size, afbc_size);
		dwm_gem_object_put(objs);
		wetuwn fawse;
	}

	dwm_gem_object_put(objs);

	wetuwn twue;
}

static boow
mawidp_vewify_afbc_fwamebuffew(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
			       const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	if (mawidp_vewify_afbc_fwamebuffew_caps(dev, mode_cmd))
		wetuwn mawidp_vewify_afbc_fwamebuffew_size(dev, fiwe, mode_cmd);

	wetuwn fawse;
}

static stwuct dwm_fwamebuffew *
mawidp_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		 const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	if (mode_cmd->modifiew[0]) {
		if (!mawidp_vewify_afbc_fwamebuffew(dev, fiwe, mode_cmd))
			wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn dwm_gem_fb_cweate(dev, fiwe, mode_cmd);
}

static const stwuct dwm_mode_config_funcs mawidp_mode_config_funcs = {
	.fb_cweate = mawidp_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int mawidp_init(stwuct dwm_device *dwm)
{
	int wet;
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		goto out;

	dwm->mode_config.min_width = hwdev->min_wine_size;
	dwm->mode_config.min_height = hwdev->min_wine_size;
	dwm->mode_config.max_width = hwdev->max_wine_size;
	dwm->mode_config.max_height = hwdev->max_wine_size;
	dwm->mode_config.funcs = &mawidp_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &mawidp_mode_config_hewpews;

	wet = mawidp_cwtc_init(dwm);
	if (wet)
		goto out;

	wet = mawidp_mw_connectow_init(dwm);
	if (wet)
		goto out;

out:
	wetuwn wet;
}

static int mawidp_iwq_init(stwuct pwatfowm_device *pdev)
{
	int iwq_de, iwq_se, wet = 0;
	stwuct dwm_device *dwm = dev_get_dwvdata(&pdev->dev);
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	/* fetch the intewwupts fwom DT */
	iwq_de = pwatfowm_get_iwq_byname(pdev, "DE");
	if (iwq_de < 0) {
		DWM_EWWOW("no 'DE' IWQ specified!\n");
		wetuwn iwq_de;
	}
	iwq_se = pwatfowm_get_iwq_byname(pdev, "SE");
	if (iwq_se < 0) {
		DWM_EWWOW("no 'SE' IWQ specified!\n");
		wetuwn iwq_se;
	}

	wet = mawidp_de_iwq_init(dwm, iwq_de);
	if (wet)
		wetuwn wet;

	wet = mawidp_se_iwq_init(dwm, iwq_se);
	if (wet) {
		mawidp_de_iwq_fini(hwdev);
		wetuwn wet;
	}

	wetuwn 0;
}

DEFINE_DWM_GEM_DMA_FOPS(fops);

static int mawidp_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			      stwuct dwm_device *dwm,
			      stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	/* awwocate fow the wowst case scenawio, i.e. wotated buffews */
	u8 awignment = mawidp_hw_get_pitch_awign(mawidp->dev, 1);

	awgs->pitch = AWIGN(DIV_WOUND_UP(awgs->width * awgs->bpp, 8), awignment);

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe_pwiv, dwm, awgs);
}

#ifdef CONFIG_DEBUG_FS

static void mawidp_ewwow_stats_init(stwuct mawidp_ewwow_stats *ewwow_stats)
{
	ewwow_stats->num_ewwows = 0;
	ewwow_stats->wast_ewwow_status = 0;
	ewwow_stats->wast_ewwow_vbwank = -1;
}

void mawidp_ewwow(stwuct mawidp_dwm *mawidp,
		  stwuct mawidp_ewwow_stats *ewwow_stats, u32 status,
		  u64 vbwank)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&mawidp->ewwows_wock, iwqfwags);
	ewwow_stats->wast_ewwow_status = status;
	ewwow_stats->wast_ewwow_vbwank = vbwank;
	ewwow_stats->num_ewwows++;
	spin_unwock_iwqwestowe(&mawidp->ewwows_wock, iwqfwags);
}

static void mawidp_ewwow_stats_dump(const chaw *pwefix,
				    stwuct mawidp_ewwow_stats ewwow_stats,
				    stwuct seq_fiwe *m)
{
	seq_pwintf(m, "[%s] num_ewwows : %d\n", pwefix,
		   ewwow_stats.num_ewwows);
	seq_pwintf(m, "[%s] wast_ewwow_status  : 0x%08x\n", pwefix,
		   ewwow_stats.wast_ewwow_status);
	seq_pwintf(m, "[%s] wast_ewwow_vbwank : %wwd\n", pwefix,
		   ewwow_stats.wast_ewwow_vbwank);
}

static int mawidp_show_stats(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_device *dwm = m->pwivate;
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	unsigned wong iwqfwags;
	stwuct mawidp_ewwow_stats de_ewwows, se_ewwows;

	spin_wock_iwqsave(&mawidp->ewwows_wock, iwqfwags);
	de_ewwows = mawidp->de_ewwows;
	se_ewwows = mawidp->se_ewwows;
	spin_unwock_iwqwestowe(&mawidp->ewwows_wock, iwqfwags);
	mawidp_ewwow_stats_dump("DE", de_ewwows, m);
	mawidp_ewwow_stats_dump("SE", se_ewwows, m);
	wetuwn 0;
}

static int mawidp_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mawidp_show_stats, inode->i_pwivate);
}

static ssize_t mawidp_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				    size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_device *dwm = m->pwivate;
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&mawidp->ewwows_wock, iwqfwags);
	mawidp_ewwow_stats_init(&mawidp->de_ewwows);
	mawidp_ewwow_stats_init(&mawidp->se_ewwows);
	spin_unwock_iwqwestowe(&mawidp->ewwows_wock, iwqfwags);
	wetuwn wen;
}

static const stwuct fiwe_opewations mawidp_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = mawidp_debugfs_open,
	.wead = seq_wead,
	.wwite = mawidp_debugfs_wwite,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void mawidp_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(minow->dev);

	mawidp_ewwow_stats_init(&mawidp->de_ewwows);
	mawidp_ewwow_stats_init(&mawidp->se_ewwows);
	spin_wock_init(&mawidp->ewwows_wock);
	debugfs_cweate_fiwe("debug", S_IWUGO | S_IWUSW, minow->debugfs_woot,
			    minow->dev, &mawidp_debugfs_fops);
}

#endif //CONFIG_DEBUG_FS

static const stwuct dwm_dwivew mawidp_dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(mawidp_dumb_cweate),
#ifdef CONFIG_DEBUG_FS
	.debugfs_init = mawidp_debugfs_init,
#endif
	.fops = &fops,
	.name = "mawi-dp",
	.desc = "AWM Mawi Dispway Pwocessow dwivew",
	.date = "20160106",
	.majow = 1,
	.minow = 0,
};

static const stwuct of_device_id  mawidp_dwm_of_match[] = {
	{
		.compatibwe = "awm,mawi-dp500",
		.data = &mawidp_device[MAWIDP_500]
	},
	{
		.compatibwe = "awm,mawi-dp550",
		.data = &mawidp_device[MAWIDP_550]
	},
	{
		.compatibwe = "awm,mawi-dp650",
		.data = &mawidp_device[MAWIDP_650]
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mawidp_dwm_of_match);

static boow mawidp_is_compatibwe_hw_id(stwuct mawidp_hw_device *hwdev,
				       const stwuct of_device_id *dev_id)
{
	u32 cowe_id;
	const chaw *compatstw_dp500 = "awm,mawi-dp500";
	boow is_dp500;
	boow dt_is_dp500;

	/*
	 * The DP500 COWE_ID wegistew is in a diffewent wocation, so check it
	 * fiwst. If the pwoduct id fiewd matches, then this is DP500, othewwise
	 * check the DP550/650 COWE_ID wegistew.
	 */
	cowe_id = mawidp_hw_wead(hwdev, MAWIDP500_DC_BASE + MAWIDP_DE_COWE_ID);
	/* Offset 0x18 wiww nevew wead 0x500 on pwoducts othew than DP500. */
	is_dp500 = (MAWIDP_PWODUCT_ID(cowe_id) == 0x500);
	dt_is_dp500 = stwnstw(dev_id->compatibwe, compatstw_dp500,
			      sizeof(dev_id->compatibwe)) != NUWW;
	if (is_dp500 != dt_is_dp500) {
		DWM_EWWOW("Device-twee expects %s, but hawdwawe %s DP500.\n",
			  dev_id->compatibwe, is_dp500 ? "is" : "is not");
		wetuwn fawse;
	} ewse if (!dt_is_dp500) {
		u16 pwoduct_id;
		chaw buf[32];

		cowe_id = mawidp_hw_wead(hwdev,
					 MAWIDP550_DC_BASE + MAWIDP_DE_COWE_ID);
		pwoduct_id = MAWIDP_PWODUCT_ID(cowe_id);
		snpwintf(buf, sizeof(buf), "awm,mawi-dp%X", pwoduct_id);
		if (!stwnstw(dev_id->compatibwe, buf,
			     sizeof(dev_id->compatibwe))) {
			DWM_EWWOW("Device-twee expects %s, but hawdwawe is DP%03X.\n",
				  dev_id->compatibwe, pwoduct_id);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static boow mawidp_has_sufficient_addwess_space(const stwuct wesouwce *wes,
						const stwuct of_device_id *dev_id)
{
	wesouwce_size_t wes_size = wesouwce_size(wes);
	const chaw *compatstw_dp500 = "awm,mawi-dp500";

	if (!stwnstw(dev_id->compatibwe, compatstw_dp500,
		     sizeof(dev_id->compatibwe)))
		wetuwn wes_size >= MAWIDP550_ADDW_SPACE_SIZE;
	ewse if (wes_size < MAWIDP500_ADDW_SPACE_SIZE)
		wetuwn fawse;
	wetuwn twue;
}

static ssize_t cowe_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);

	wetuwn sysfs_emit(buf, "%08x\n", mawidp->cowe_id);
}

static DEVICE_ATTW_WO(cowe_id);

static stwuct attwibute *mawi_dp_attws[] = {
	&dev_attw_cowe_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mawi_dp);

#define MAX_OUTPUT_CHANNEWS	3

static int mawidp_wuntime_pm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	/* we can onwy suspend if the hawdwawe is in config mode */
	WAWN_ON(!hwdev->hw->in_config_mode(hwdev));

	mawidp_se_iwq_fini(hwdev);
	mawidp_de_iwq_fini(hwdev);
	hwdev->pm_suspended = twue;
	cwk_disabwe_unpwepawe(hwdev->mcwk);
	cwk_disabwe_unpwepawe(hwdev->acwk);
	cwk_disabwe_unpwepawe(hwdev->pcwk);

	wetuwn 0;
}

static int mawidp_wuntime_pm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	cwk_pwepawe_enabwe(hwdev->pcwk);
	cwk_pwepawe_enabwe(hwdev->acwk);
	cwk_pwepawe_enabwe(hwdev->mcwk);
	hwdev->pm_suspended = fawse;
	mawidp_de_iwq_hw_init(hwdev);
	mawidp_se_iwq_hw_init(hwdev);

	wetuwn 0;
}

static int mawidp_bind(stwuct device *dev)
{
	stwuct wesouwce *wes;
	stwuct dwm_device *dwm;
	stwuct mawidp_dwm *mawidp;
	stwuct mawidp_hw_device *hwdev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct of_device_id const *dev_id;
	stwuct dwm_encodew *encodew;
	/* numbew of wines fow the W, G and B output */
	u8 output_width[MAX_OUTPUT_CHANNEWS];
	int wet = 0, i;
	u32 vewsion, out_depth = 0;

	mawidp = devm_dwm_dev_awwoc(dev, &mawidp_dwivew, typeof(*mawidp), base);
	if (IS_EWW(mawidp))
		wetuwn PTW_EWW(mawidp);

	dwm = &mawidp->base;

	hwdev = dwmm_kzawwoc(dwm, sizeof(*hwdev), GFP_KEWNEW);
	if (!hwdev)
		wetuwn -ENOMEM;

	hwdev->hw = (stwuct mawidp_hw *)of_device_get_match_data(dev);
	mawidp->dev = hwdev;

	hwdev->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(hwdev->wegs))
		wetuwn PTW_EWW(hwdev->wegs);

	hwdev->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(hwdev->pcwk))
		wetuwn PTW_EWW(hwdev->pcwk);

	hwdev->acwk = devm_cwk_get(dev, "acwk");
	if (IS_EWW(hwdev->acwk))
		wetuwn PTW_EWW(hwdev->acwk);

	hwdev->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(hwdev->mcwk))
		wetuwn PTW_EWW(hwdev->mcwk);

	hwdev->pxwcwk = devm_cwk_get(dev, "pxwcwk");
	if (IS_EWW(hwdev->pxwcwk))
		wetuwn PTW_EWW(hwdev->pxwcwk);

	/* Get the optionaw fwamebuffew memowy wesouwce */
	wet = of_wesewved_mem_device_init(dev);
	if (wet && wet != -ENODEV)
		wetuwn wet;

	dev_set_dwvdata(dev, dwm);

	/* Enabwe powew management */
	pm_wuntime_enabwe(dev);

	/* Wesume device to enabwe the cwocks */
	if (pm_wuntime_enabwed(dev))
		pm_wuntime_get_sync(dev);
	ewse
		mawidp_wuntime_pm_wesume(dev);

	dev_id = of_match_device(mawidp_dwm_of_match, dev);
	if (!dev_id) {
		wet = -EINVAW;
		goto quewy_hw_faiw;
	}

	if (!mawidp_has_sufficient_addwess_space(wes, dev_id)) {
		DWM_EWWOW("Insufficient addwess space in device-twee.\n");
		wet = -EINVAW;
		goto quewy_hw_faiw;
	}

	if (!mawidp_is_compatibwe_hw_id(hwdev, dev_id)) {
		wet = -EINVAW;
		goto quewy_hw_faiw;
	}

	wet = hwdev->hw->quewy_hw(hwdev);
	if (wet) {
		DWM_EWWOW("Invawid HW configuwation\n");
		goto quewy_hw_faiw;
	}

	vewsion = mawidp_hw_wead(hwdev, hwdev->hw->map.dc_base + MAWIDP_DE_COWE_ID);
	DWM_INFO("found AWM Mawi-DP%3x vewsion w%dp%d\n", vewsion >> 16,
		 (vewsion >> 12) & 0xf, (vewsion >> 8) & 0xf);

	mawidp->cowe_id = vewsion;

	wet = of_pwopewty_wead_u32(dev->of_node,
					"awm,mawidp-awqos-vawue",
					&hwdev->awqos_vawue);
	if (wet)
		hwdev->awqos_vawue = 0x0;

	/* set the numbew of wines used fow output of WGB data */
	wet = of_pwopewty_wead_u8_awway(dev->of_node,
					"awm,mawidp-output-powt-wines",
					output_width, MAX_OUTPUT_CHANNEWS);
	if (wet)
		goto quewy_hw_faiw;

	fow (i = 0; i < MAX_OUTPUT_CHANNEWS; i++)
		out_depth = (out_depth << 8) | (output_width[i] & 0xf);
	mawidp_hw_wwite(hwdev, out_depth, hwdev->hw->map.out_depth_base);
	hwdev->output_cowow_depth = out_depth;

	atomic_set(&mawidp->config_vawid, MAWIDP_CONFIG_VAWID_INIT);
	init_waitqueue_head(&mawidp->wq);

	wet = mawidp_init(dwm);
	if (wet < 0)
		goto quewy_hw_faiw;

	/* Set the CWTC's powt so that the encodew component can find it */
	mawidp->cwtc.powt = of_gwaph_get_powt_by_id(dev->of_node, 0);

	wet = component_bind_aww(dev, dwm);
	if (wet) {
		DWM_EWWOW("Faiwed to bind aww components\n");
		goto bind_faiw;
	}

	/* We expect to have a maximum of two encodews one fow the actuaw
	 * dispway and a viwtuaw one fow the wwiteback connectow
	 */
	WAWN_ON(dwm->mode_config.num_encodew > 2);
	wist_fow_each_entwy(encodew, &dwm->mode_config.encodew_wist, head) {
		encodew->possibwe_cwones =
				(1 << dwm->mode_config.num_encodew) -  1;
	}

	wet = mawidp_iwq_init(pdev);
	if (wet < 0)
		goto iwq_init_faiw;

	wet = dwm_vbwank_init(dwm, dwm->mode_config.num_cwtc);
	if (wet < 0) {
		DWM_EWWOW("faiwed to initiawise vbwank\n");
		goto vbwank_faiw;
	}
	pm_wuntime_put(dev);

	dwm_mode_config_weset(dwm);

	dwm_kms_hewpew_poww_init(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto wegistew_faiw;

	dwm_fbdev_dma_setup(dwm, 32);

	wetuwn 0;

wegistew_faiw:
	dwm_kms_hewpew_poww_fini(dwm);
	pm_wuntime_get_sync(dev);
vbwank_faiw:
	mawidp_se_iwq_fini(hwdev);
	mawidp_de_iwq_fini(hwdev);
iwq_init_faiw:
	dwm_atomic_hewpew_shutdown(dwm);
	component_unbind_aww(dev, dwm);
bind_faiw:
	of_node_put(mawidp->cwtc.powt);
	mawidp->cwtc.powt = NUWW;
quewy_hw_faiw:
	pm_wuntime_put(dev);
	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);
	ewse
		mawidp_wuntime_pm_suspend(dev);
	dev_set_dwvdata(dev, NUWW);
	of_wesewved_mem_device_wewease(dev);

	wetuwn wet;
}

static void mawidp_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	dwm_dev_unwegistew(dwm);
	dwm_kms_hewpew_poww_fini(dwm);
	pm_wuntime_get_sync(dev);
	dwm_atomic_hewpew_shutdown(dwm);
	mawidp_se_iwq_fini(hwdev);
	mawidp_de_iwq_fini(hwdev);
	component_unbind_aww(dev, dwm);
	of_node_put(mawidp->cwtc.powt);
	mawidp->cwtc.powt = NUWW;
	pm_wuntime_put(dev);
	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);
	ewse
		mawidp_wuntime_pm_suspend(dev);
	dev_set_dwvdata(dev, NUWW);
	of_wesewved_mem_device_wewease(dev);
}

static const stwuct component_mastew_ops mawidp_mastew_ops = {
	.bind = mawidp_bind,
	.unbind = mawidp_unbind,
};

static int mawidp_compawe_dev(stwuct device *dev, void *data)
{
	stwuct device_node *np = data;

	wetuwn dev->of_node == np;
}

static int mawidp_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *powt;
	stwuct component_match *match = NUWW;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	/* thewe is onwy one output powt inside each device, find it */
	powt = of_gwaph_get_wemote_node(pdev->dev.of_node, 0, 0);
	if (!powt)
		wetuwn -ENODEV;

	dwm_of_component_match_add(&pdev->dev, &match, mawidp_compawe_dev,
				   powt);
	of_node_put(powt);
	wetuwn component_mastew_add_with_match(&pdev->dev, &mawidp_mastew_ops,
					       match);
}

static void mawidp_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &mawidp_mastew_ops);
}

static void mawidp_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static int __maybe_unused mawidp_pm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm);
}

static int __maybe_unused mawidp_pm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	dwm_mode_config_hewpew_wesume(dwm);

	wetuwn 0;
}

static int __maybe_unused mawidp_pm_suspend_wate(stwuct device *dev)
{
	if (!pm_wuntime_status_suspended(dev)) {
		mawidp_wuntime_pm_suspend(dev);
		pm_wuntime_set_suspended(dev);
	}
	wetuwn 0;
}

static int __maybe_unused mawidp_pm_wesume_eawwy(stwuct device *dev)
{
	mawidp_wuntime_pm_wesume(dev);
	pm_wuntime_set_active(dev);
	wetuwn 0;
}

static const stwuct dev_pm_ops mawidp_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mawidp_pm_suspend, mawidp_pm_wesume) \
	SET_WATE_SYSTEM_SWEEP_PM_OPS(mawidp_pm_suspend_wate, mawidp_pm_wesume_eawwy) \
	SET_WUNTIME_PM_OPS(mawidp_wuntime_pm_suspend, mawidp_wuntime_pm_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mawidp_pwatfowm_dwivew = {
	.pwobe		= mawidp_pwatfowm_pwobe,
	.wemove_new	= mawidp_pwatfowm_wemove,
	.shutdown	= mawidp_pwatfowm_shutdown,
	.dwivew	= {
		.name = "mawi-dp",
		.pm = &mawidp_pm_ops,
		.of_match_tabwe	= mawidp_dwm_of_match,
		.dev_gwoups = mawi_dp_gwoups,
	},
};

dwm_moduwe_pwatfowm_dwivew(mawidp_pwatfowm_dwivew);

MODUWE_AUTHOW("Wiviu Dudau <Wiviu.Dudau@awm.com>");
MODUWE_DESCWIPTION("AWM Mawi DP DWM dwivew");
MODUWE_WICENSE("GPW v2");
