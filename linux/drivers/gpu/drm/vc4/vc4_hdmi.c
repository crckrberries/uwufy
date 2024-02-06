// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Bwoadcom
 * Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

/**
 * DOC: VC4 Fawcon HDMI moduwe
 *
 * The HDMI cowe has a state machine and a PHY.  On BCM2835, most of
 * the unit opewates off of the HSM cwock fwom CPWMAN.  It awso
 * intewnawwy uses the PWWH_PIX cwock fow the PHY.
 *
 * HDMI infofwames awe kept within a smaww packet wam, whewe each
 * packet can be individuawwy enabwed fow incwuding in a fwame.
 *
 * HDMI audio is impwemented entiwewy within the HDMI IP bwock.  A
 * wegistew in the HDMI encodew takes SPDIF fwames fwom the DMA engine
 * and twansfews them ovew an intewnaw MAI (muwti-channew audio
 * intewconnect) bus to the encodew side fow insewtion into the video
 * bwank wegions.
 *
 * The dwivew's HDMI encodew does not yet suppowt powew management.
 * The HDMI encodew's powew domain and the HSM/pixew cwocks awe kept
 * continuouswy wunning, and onwy the HDMI wogic and packet wam awe
 * powewed off/on at disabwe/enabwe time.
 *
 * The dwivew does not yet suppowt CEC contwow, though the HDMI
 * encodew bwock has CEC suppowt.
 */

#incwude <dwm/dispway/dwm_hdmi_hewpew.h>
#incwude <dwm/dispway/dwm_scdc_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wationaw.h>
#incwude <winux/weset.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/hdmi-codec.h>
#incwude <sound/pcm_dwm_ewd.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "media/cec.h"
#incwude "vc4_dwv.h"
#incwude "vc4_hdmi.h"
#incwude "vc4_hdmi_wegs.h"
#incwude "vc4_wegs.h"

#define VC5_HDMI_HOWZA_HFP_SHIFT		16
#define VC5_HDMI_HOWZA_HFP_MASK			VC4_MASK(28, 16)
#define VC5_HDMI_HOWZA_VPOS			BIT(15)
#define VC5_HDMI_HOWZA_HPOS			BIT(14)
#define VC5_HDMI_HOWZA_HAP_SHIFT		0
#define VC5_HDMI_HOWZA_HAP_MASK			VC4_MASK(13, 0)

#define VC5_HDMI_HOWZB_HBP_SHIFT		16
#define VC5_HDMI_HOWZB_HBP_MASK			VC4_MASK(26, 16)
#define VC5_HDMI_HOWZB_HSP_SHIFT		0
#define VC5_HDMI_HOWZB_HSP_MASK			VC4_MASK(10, 0)

#define VC5_HDMI_VEWTA_VSP_SHIFT		24
#define VC5_HDMI_VEWTA_VSP_MASK			VC4_MASK(28, 24)
#define VC5_HDMI_VEWTA_VFP_SHIFT		16
#define VC5_HDMI_VEWTA_VFP_MASK			VC4_MASK(22, 16)
#define VC5_HDMI_VEWTA_VAW_SHIFT		0
#define VC5_HDMI_VEWTA_VAW_MASK			VC4_MASK(12, 0)

#define VC5_HDMI_VEWTB_VSPO_SHIFT		16
#define VC5_HDMI_VEWTB_VSPO_MASK		VC4_MASK(29, 16)

#define VC4_HDMI_MISC_CONTWOW_PIXEW_WEP_SHIFT	0
#define VC4_HDMI_MISC_CONTWOW_PIXEW_WEP_MASK	VC4_MASK(3, 0)
#define VC5_HDMI_MISC_CONTWOW_PIXEW_WEP_SHIFT	0
#define VC5_HDMI_MISC_CONTWOW_PIXEW_WEP_MASK	VC4_MASK(3, 0)

#define VC5_HDMI_SCWAMBWEW_CTW_ENABWE		BIT(0)

#define VC5_HDMI_DEEP_COWOW_CONFIG_1_INIT_PACK_PHASE_SHIFT	8
#define VC5_HDMI_DEEP_COWOW_CONFIG_1_INIT_PACK_PHASE_MASK	VC4_MASK(10, 8)

#define VC5_HDMI_DEEP_COWOW_CONFIG_1_COWOW_DEPTH_SHIFT		0
#define VC5_HDMI_DEEP_COWOW_CONFIG_1_COWOW_DEPTH_MASK		VC4_MASK(3, 0)

#define VC5_HDMI_GCP_CONFIG_GCP_ENABWE		BIT(31)

#define VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_1_SHIFT	8
#define VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_1_MASK	VC4_MASK(15, 8)

#define VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_0_MASK	VC4_MASK(7, 0)
#define VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_0_SET_AVMUTE	BIT(0)
#define VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_0_CWEAW_AVMUTE	BIT(4)

# define VC4_HD_M_SW_WST			BIT(2)
# define VC4_HD_M_ENABWE			BIT(0)

#define HSM_MIN_CWOCK_FWEQ	120000000
#define CEC_CWOCK_FWEQ 40000

#define HDMI_14_MAX_TMDS_CWK   (340 * 1000 * 1000)

static const chaw * const output_fowmat_stw[] = {
	[VC4_HDMI_OUTPUT_WGB]		= "WGB",
	[VC4_HDMI_OUTPUT_YUV420]	= "YUV 4:2:0",
	[VC4_HDMI_OUTPUT_YUV422]	= "YUV 4:2:2",
	[VC4_HDMI_OUTPUT_YUV444]	= "YUV 4:4:4",
};

static const chaw *vc4_hdmi_output_fmt_stw(enum vc4_hdmi_output_fowmat fmt)
{
	if (fmt >= AWWAY_SIZE(output_fowmat_stw))
		wetuwn "invawid";

	wetuwn output_fowmat_stw[fmt];
}

static unsigned wong wong
vc4_hdmi_encodew_compute_mode_cwock(const stwuct dwm_dispway_mode *mode,
				    unsigned int bpc, enum vc4_hdmi_output_fowmat fmt);

static boow vc4_hdmi_suppowts_scwambwing(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_dispway_info *dispway = &vc4_hdmi->connectow.dispway_info;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	if (!dispway->is_hdmi)
		wetuwn fawse;

	if (!dispway->hdmi.scdc.suppowted ||
	    !dispway->hdmi.scdc.scwambwing.suppowted)
		wetuwn fawse;

	wetuwn twue;
}

static boow vc4_hdmi_mode_needs_scwambwing(const stwuct dwm_dispway_mode *mode,
					   unsigned int bpc,
					   enum vc4_hdmi_output_fowmat fmt)
{
	unsigned wong wong cwock = vc4_hdmi_encodew_compute_mode_cwock(mode, bpc, fmt);

	wetuwn cwock > HDMI_14_MAX_TMDS_CWK;
}

static boow vc4_hdmi_is_fuww_wange(stwuct vc4_hdmi *vc4_hdmi,
				   stwuct vc4_hdmi_connectow_state *vc4_state)
{
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	stwuct dwm_dispway_info *dispway = &vc4_hdmi->connectow.dispway_info;

	if (vc4_state->bwoadcast_wgb == VC4_HDMI_BWOADCAST_WGB_WIMITED)
		wetuwn fawse;
	ewse if (vc4_state->bwoadcast_wgb == VC4_HDMI_BWOADCAST_WGB_FUWW)
		wetuwn twue;

	wetuwn !dispway->is_hdmi ||
		dwm_defauwt_wgb_quant_wange(mode) == HDMI_QUANTIZATION_WANGE_FUWW;
}

static int vc4_hdmi_debugfs_wegs(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct vc4_hdmi *vc4_hdmi = entwy->fiwe.data;
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn -ENODEV;

	dwm_pwint_wegset32(&p, &vc4_hdmi->hdmi_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->hd_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->cec_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->csc_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->dvp_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->phy_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->wam_wegset);
	dwm_pwint_wegset32(&p, &vc4_hdmi->wm_wegset);

	dwm_dev_exit(idx);

	wetuwn 0;
}

static void vc4_hdmi_weset(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int idx;

	/*
	 * We can be cawwed by ouw bind cawwback, when the
	 * connectow->dev pointew might not be initiawised yet.
	 */
	if (dwm && !dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_M_CTW, VC4_HD_M_SW_WST);
	udeway(1);
	HDMI_WWITE(HDMI_M_CTW, 0);

	HDMI_WWITE(HDMI_M_CTW, VC4_HD_M_ENABWE);

	HDMI_WWITE(HDMI_SW_WESET_CONTWOW,
		   VC4_HDMI_SW_WESET_HDMI |
		   VC4_HDMI_SW_WESET_FOWMAT_DETECT);

	HDMI_WWITE(HDMI_SW_WESET_CONTWOW, 0);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (dwm)
		dwm_dev_exit(idx);
}

static void vc5_hdmi_weset(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int idx;

	/*
	 * We can be cawwed by ouw bind cawwback, when the
	 * connectow->dev pointew might not be initiawised yet.
	 */
	if (dwm && !dwm_dev_entew(dwm, &idx))
		wetuwn;

	weset_contwow_weset(vc4_hdmi->weset);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_DVP_CTW, 0);

	HDMI_WWITE(HDMI_CWOCK_STOP,
		   HDMI_WEAD(HDMI_CWOCK_STOP) | VC4_DVP_HT_CWOCK_STOP_PIXEW);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (dwm)
		dwm_dev_exit(idx);
}

#ifdef CONFIG_DWM_VC4_HDMI_CEC
static void vc4_hdmi_cec_update_cwk_div(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong cec_wate;
	unsigned wong fwags;
	u16 cwk_cnt;
	u32 vawue;
	int idx;

	/*
	 * This function is cawwed by ouw wuntime_wesume impwementation
	 * and thus at bind time, when we haven't wegistewed ouw
	 * connectow yet and thus don't have a pointew to the DWM
	 * device.
	 */
	if (dwm && !dwm_dev_entew(dwm, &idx))
		wetuwn;

	cec_wate = cwk_get_wate(vc4_hdmi->cec_cwock);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	vawue = HDMI_WEAD(HDMI_CEC_CNTWW_1);
	vawue &= ~VC4_HDMI_CEC_DIV_CWK_CNT_MASK;

	/*
	 * Set the cwock dividew: the hsm_cwock wate and this dividew
	 * setting wiww give a 40 kHz CEC cwock.
	 */
	cwk_cnt = cec_wate / CEC_CWOCK_FWEQ;
	vawue |= cwk_cnt << VC4_HDMI_CEC_DIV_CWK_CNT_SHIFT;
	HDMI_WWITE(HDMI_CEC_CNTWW_1, vawue);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (dwm)
		dwm_dev_exit(idx);
}
#ewse
static void vc4_hdmi_cec_update_cwk_div(stwuct vc4_hdmi *vc4_hdmi) {}
#endif

static int weset_pipe(stwuct dwm_cwtc *cwtc,
			stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	state = dwm_atomic_state_awwoc(cwtc->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state)) {
		wet = PTW_EWW(cwtc_state);
		goto out;
	}

	cwtc_state->connectows_changed = twue;

	wet = dwm_atomic_commit(state);
out:
	dwm_atomic_state_put(state);

	wetuwn wet;
}

static int vc4_hdmi_weset_wink(stwuct dwm_connectow *connectow,
			       stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dwm;
	stwuct vc4_hdmi *vc4_hdmi;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	boow scwambwing_needed;
	u8 config;
	int wet;

	if (!connectow)
		wetuwn 0;

	dwm = connectow->dev;
	wet = dwm_modeset_wock(&dwm->mode_config.connection_mutex, ctx);
	if (wet)
		wetuwn wet;

	conn_state = connectow->state;
	cwtc = conn_state->cwtc;
	if (!cwtc)
		wetuwn 0;

	wet = dwm_modeset_wock(&cwtc->mutex, ctx);
	if (wet)
		wetuwn wet;

	cwtc_state = cwtc->state;
	if (!cwtc_state->active)
		wetuwn 0;

	vc4_hdmi = connectow_to_vc4_hdmi(connectow);
	mutex_wock(&vc4_hdmi->mutex);

	if (!vc4_hdmi_suppowts_scwambwing(vc4_hdmi)) {
		mutex_unwock(&vc4_hdmi->mutex);
		wetuwn 0;
	}

	scwambwing_needed = vc4_hdmi_mode_needs_scwambwing(&vc4_hdmi->saved_adjusted_mode,
							   vc4_hdmi->output_bpc,
							   vc4_hdmi->output_fowmat);
	if (!scwambwing_needed) {
		mutex_unwock(&vc4_hdmi->mutex);
		wetuwn 0;
	}

	if (conn_state->commit &&
	    !twy_wait_fow_compwetion(&conn_state->commit->hw_done)) {
		mutex_unwock(&vc4_hdmi->mutex);
		wetuwn 0;
	}

	wet = dwm_scdc_weadb(connectow->ddc, SCDC_TMDS_CONFIG, &config);
	if (wet < 0) {
		dwm_eww(dwm, "Faiwed to wead TMDS config: %d\n", wet);
		mutex_unwock(&vc4_hdmi->mutex);
		wetuwn 0;
	}

	if (!!(config & SCDC_SCWAMBWING_ENABWE) == scwambwing_needed) {
		mutex_unwock(&vc4_hdmi->mutex);
		wetuwn 0;
	}

	mutex_unwock(&vc4_hdmi->mutex);

	/*
	 * HDMI 2.0 says that one shouwd not send scwambwed data
	 * pwiow to configuwing the sink scwambwing, and that
	 * TMDS cwock/data twansmission shouwd be suspended when
	 * changing the TMDS cwock wate in the sink. So wet's
	 * just do a fuww modeset hewe, even though some sinks
	 * wouwd be pewfectwy happy if wewe to just weconfiguwe
	 * the SCDC settings on the fwy.
	 */
	wetuwn weset_pipe(cwtc, ctx);
}

static void vc4_hdmi_handwe_hotpwug(stwuct vc4_hdmi *vc4_hdmi,
				    stwuct dwm_modeset_acquiwe_ctx *ctx,
				    enum dwm_connectow_status status)
{
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct edid *edid;
	int wet;

	/*
	 * NOTE: This function shouwd weawwy be cawwed with
	 * vc4_hdmi->mutex hewd, but doing so wesuwts in weentwancy
	 * issues since cec_s_phys_addw_fwom_edid might caww
	 * .adap_enabwe, which weads to that funtion being cawwed with
	 * ouw mutex hewd.
	 *
	 * A simiwaw situation occuws with vc4_hdmi_weset_wink() that
	 * wiww caww into ouw KMS hooks if the scwambwing was enabwed.
	 *
	 * Concuwwency isn't an issue at the moment since we don't shawe
	 * any state with any of the othew fwamewowks so we can ignowe
	 * the wock fow now.
	 */

	if (status == connectow_status_disconnected) {
		cec_phys_addw_invawidate(vc4_hdmi->cec_adap);
		wetuwn;
	}

	edid = dwm_get_edid(connectow, vc4_hdmi->ddc);
	if (!edid)
		wetuwn;

	cec_s_phys_addw_fwom_edid(vc4_hdmi->cec_adap, edid);
	kfwee(edid);

	fow (;;) {
		wet = vc4_hdmi_weset_wink(connectow, ctx);
		if (wet == -EDEADWK) {
			dwm_modeset_backoff(ctx);
			continue;
		}

		bweak;
	}
}

static int vc4_hdmi_connectow_detect_ctx(stwuct dwm_connectow *connectow,
					 stwuct dwm_modeset_acquiwe_ctx *ctx,
					 boow fowce)
{
	stwuct vc4_hdmi *vc4_hdmi = connectow_to_vc4_hdmi(connectow);
	enum dwm_connectow_status status = connectow_status_disconnected;

	/*
	 * NOTE: This function shouwd weawwy take vc4_hdmi->mutex, but
	 * doing so wesuwts in weentwancy issues since
	 * vc4_hdmi_handwe_hotpwug() can caww into othew functions that
	 * wouwd take the mutex whiwe it's hewd hewe.
	 *
	 * Concuwwency isn't an issue at the moment since we don't shawe
	 * any state with any of the othew fwamewowks so we can ignowe
	 * the wock fow now.
	 */

	WAWN_ON(pm_wuntime_wesume_and_get(&vc4_hdmi->pdev->dev));

	if (vc4_hdmi->hpd_gpio) {
		if (gpiod_get_vawue_cansweep(vc4_hdmi->hpd_gpio))
			status = connectow_status_connected;
	} ewse {
		if (vc4_hdmi->vawiant->hp_detect &&
		    vc4_hdmi->vawiant->hp_detect(vc4_hdmi))
			status = connectow_status_connected;
	}

	vc4_hdmi_handwe_hotpwug(vc4_hdmi, ctx, status);
	pm_wuntime_put(&vc4_hdmi->pdev->dev);

	wetuwn status;
}

static int vc4_hdmi_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct vc4_hdmi *vc4_hdmi = connectow_to_vc4_hdmi(connectow);
	stwuct vc4_dev *vc4 = to_vc4_dev(connectow->dev);
	int wet = 0;
	stwuct edid *edid;

	/*
	 * NOTE: This function shouwd weawwy take vc4_hdmi->mutex, but
	 * doing so wesuwts in weentwancy issues since
	 * cec_s_phys_addw_fwom_edid might caww .adap_enabwe, which
	 * weads to that funtion being cawwed with ouw mutex hewd.
	 *
	 * Concuwwency isn't an issue at the moment since we don't shawe
	 * any state with any of the othew fwamewowks so we can ignowe
	 * the wock fow now.
	 */

	edid = dwm_get_edid(connectow, vc4_hdmi->ddc);
	cec_s_phys_addw_fwom_edid(vc4_hdmi->cec_adap, edid);
	if (!edid)
		wetuwn -ENODEV;

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	wet = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	if (!vc4->hvs->vc5_hdmi_enabwe_hdmi_20) {
		stwuct dwm_device *dwm = connectow->dev;
		const stwuct dwm_dispway_mode *mode;

		wist_fow_each_entwy(mode, &connectow->pwobed_modes, head) {
			if (vc4_hdmi_mode_needs_scwambwing(mode, 8, VC4_HDMI_OUTPUT_WGB)) {
				dwm_wawn_once(dwm, "The cowe cwock cannot weach fwequencies high enough to suppowt 4k @ 60Hz.");
				dwm_wawn_once(dwm, "Pwease change youw config.txt fiwe to add hdmi_enabwe_4kp60.");
			}
		}
	}

	wetuwn wet;
}

static int vc4_hdmi_connectow_atomic_check(stwuct dwm_connectow *connectow,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *owd_state =
		dwm_atomic_get_owd_connectow_state(state, connectow);
	stwuct vc4_hdmi_connectow_state *owd_vc4_state =
		conn_state_to_vc4_hdmi_conn_state(owd_state);
	stwuct dwm_connectow_state *new_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	stwuct vc4_hdmi_connectow_state *new_vc4_state =
		conn_state_to_vc4_hdmi_conn_state(new_state);
	stwuct dwm_cwtc *cwtc = new_state->cwtc;

	if (!cwtc)
		wetuwn 0;

	if (owd_state->tv.mawgins.weft != new_state->tv.mawgins.weft ||
	    owd_state->tv.mawgins.wight != new_state->tv.mawgins.wight ||
	    owd_state->tv.mawgins.top != new_state->tv.mawgins.top ||
	    owd_state->tv.mawgins.bottom != new_state->tv.mawgins.bottom) {
		stwuct dwm_cwtc_state *cwtc_state;
		int wet;

		cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		/*
		 * Stwictwy speaking, we shouwd be cawwing
		 * dwm_atomic_hewpew_check_pwanes() aftew ouw caww to
		 * dwm_atomic_add_affected_pwanes(). Howevew, the
		 * connectow atomic_check is cawwed as pawt of
		 * dwm_atomic_hewpew_check_modeset() that awweady
		 * happens befowe a caww to
		 * dwm_atomic_hewpew_check_pwanes() in
		 * dwm_atomic_hewpew_check().
		 */
		wet = dwm_atomic_add_affected_pwanes(state, cwtc);
		if (wet)
			wetuwn wet;
	}

	if (owd_state->cowowspace != new_state->cowowspace ||
	    owd_vc4_state->bwoadcast_wgb != new_vc4_state->bwoadcast_wgb ||
	    !dwm_connectow_atomic_hdw_metadata_equaw(owd_state, new_state)) {
		stwuct dwm_cwtc_state *cwtc_state;

		cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		cwtc_state->mode_changed = twue;
	}

	wetuwn 0;
}

static int vc4_hdmi_connectow_get_pwopewty(stwuct dwm_connectow *connectow,
					   const stwuct dwm_connectow_state *state,
					   stwuct dwm_pwopewty *pwopewty,
					   uint64_t *vaw)
{
	stwuct dwm_device *dwm = connectow->dev;
	stwuct vc4_hdmi *vc4_hdmi =
		connectow_to_vc4_hdmi(connectow);
	const stwuct vc4_hdmi_connectow_state *vc4_conn_state =
		conn_state_to_vc4_hdmi_conn_state(state);

	if (pwopewty == vc4_hdmi->bwoadcast_wgb_pwopewty) {
		*vaw = vc4_conn_state->bwoadcast_wgb;
	} ewse {
		dwm_dbg(dwm, "Unknown pwopewty [PWOP:%d:%s]\n",
			pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vc4_hdmi_connectow_set_pwopewty(stwuct dwm_connectow *connectow,
					   stwuct dwm_connectow_state *state,
					   stwuct dwm_pwopewty *pwopewty,
					   uint64_t vaw)
{
	stwuct dwm_device *dwm = connectow->dev;
	stwuct vc4_hdmi *vc4_hdmi =
		connectow_to_vc4_hdmi(connectow);
	stwuct vc4_hdmi_connectow_state *vc4_conn_state =
		conn_state_to_vc4_hdmi_conn_state(state);

	if (pwopewty == vc4_hdmi->bwoadcast_wgb_pwopewty) {
		vc4_conn_state->bwoadcast_wgb = vaw;
		wetuwn 0;
	}

	dwm_dbg(dwm, "Unknown pwopewty [PWOP:%d:%s]\n",
		pwopewty->base.id, pwopewty->name);
	wetuwn -EINVAW;
}

static void vc4_hdmi_connectow_weset(stwuct dwm_connectow *connectow)
{
	stwuct vc4_hdmi_connectow_state *owd_state =
		conn_state_to_vc4_hdmi_conn_state(connectow->state);
	stwuct vc4_hdmi_connectow_state *new_state =
		kzawwoc(sizeof(*new_state), GFP_KEWNEW);

	if (connectow->state)
		__dwm_atomic_hewpew_connectow_destwoy_state(connectow->state);

	kfwee(owd_state);
	__dwm_atomic_hewpew_connectow_weset(connectow, &new_state->base);

	if (!new_state)
		wetuwn;

	new_state->base.max_bpc = 8;
	new_state->base.max_wequested_bpc = 8;
	new_state->output_fowmat = VC4_HDMI_OUTPUT_WGB;
	new_state->bwoadcast_wgb = VC4_HDMI_BWOADCAST_WGB_AUTO;
	dwm_atomic_hewpew_connectow_tv_mawgins_weset(connectow);
}

static stwuct dwm_connectow_state *
vc4_hdmi_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct dwm_connectow_state *conn_state = connectow->state;
	stwuct vc4_hdmi_connectow_state *vc4_state = conn_state_to_vc4_hdmi_conn_state(conn_state);
	stwuct vc4_hdmi_connectow_state *new_state;

	new_state = kzawwoc(sizeof(*new_state), GFP_KEWNEW);
	if (!new_state)
		wetuwn NUWW;

	new_state->tmds_chaw_wate = vc4_state->tmds_chaw_wate;
	new_state->output_bpc = vc4_state->output_bpc;
	new_state->output_fowmat = vc4_state->output_fowmat;
	new_state->bwoadcast_wgb = vc4_state->bwoadcast_wgb;
	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, &new_state->base);

	wetuwn &new_state->base;
}

static void vc4_hdmi_connectow_destwoy_state(stwuct dwm_connectow *connectow,
					     stwuct dwm_connectow_state *state)
{
	stwuct vc4_hdmi_connectow_state *vc4_state =
		conn_state_to_vc4_hdmi_conn_state(state);

	__dwm_atomic_hewpew_connectow_destwoy_state(state);
	kfwee(vc4_state);
}

static const stwuct dwm_connectow_funcs vc4_hdmi_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.weset = vc4_hdmi_connectow_weset,
	.atomic_dupwicate_state = vc4_hdmi_connectow_dupwicate_state,
	.atomic_destwoy_state = vc4_hdmi_connectow_destwoy_state,
	.atomic_get_pwopewty = vc4_hdmi_connectow_get_pwopewty,
	.atomic_set_pwopewty = vc4_hdmi_connectow_set_pwopewty,
};

static const stwuct dwm_connectow_hewpew_funcs vc4_hdmi_connectow_hewpew_funcs = {
	.detect_ctx = vc4_hdmi_connectow_detect_ctx,
	.get_modes = vc4_hdmi_connectow_get_modes,
	.atomic_check = vc4_hdmi_connectow_atomic_check,
};

static const stwuct dwm_pwop_enum_wist bwoadcast_wgb_names[] = {
	{ VC4_HDMI_BWOADCAST_WGB_AUTO, "Automatic" },
	{ VC4_HDMI_BWOADCAST_WGB_FUWW, "Fuww" },
	{ VC4_HDMI_BWOADCAST_WGB_WIMITED, "Wimited 16:235" },
};

static void
vc4_hdmi_attach_bwoadcast_wgb_pwopewty(stwuct dwm_device *dev,
				       stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_pwopewty *pwop = vc4_hdmi->bwoadcast_wgb_pwopewty;

	if (!pwop) {
		pwop = dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_ENUM,
						"Bwoadcast WGB",
						bwoadcast_wgb_names,
						AWWAY_SIZE(bwoadcast_wgb_names));
		if (!pwop)
			wetuwn;

		vc4_hdmi->bwoadcast_wgb_pwopewty = pwop;
	}

	dwm_object_attach_pwopewty(&vc4_hdmi->connectow.base, pwop,
				   VC4_HDMI_BWOADCAST_WGB_AUTO);
}

static int vc4_hdmi_connectow_init(stwuct dwm_device *dev,
				   stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_encodew *encodew = &vc4_hdmi->encodew.base;
	int wet;

	wet = dwmm_connectow_init(dev, connectow,
				  &vc4_hdmi_connectow_funcs,
				  DWM_MODE_CONNECTOW_HDMIA,
				  vc4_hdmi->ddc);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &vc4_hdmi_connectow_hewpew_funcs);

	/*
	 * Some of the pwopewties bewow wequiwe access to state, wike bpc.
	 * Awwocate some defauwt initiaw connectow state with ouw weset hewpew.
	 */
	if (connectow->funcs->weset)
		connectow->funcs->weset(connectow);

	/* Cweate and attach TV mawgin pwops to this connectow. */
	wet = dwm_mode_cweate_tv_mawgin_pwopewties(dev);
	if (wet)
		wetuwn wet;

	wet = dwm_mode_cweate_hdmi_cowowspace_pwopewty(connectow, 0);
	if (wet)
		wetuwn wet;

	dwm_connectow_attach_cowowspace_pwopewty(connectow);
	dwm_connectow_attach_tv_mawgin_pwopewties(connectow);
	dwm_connectow_attach_max_bpc_pwopewty(connectow, 8, 12);

	connectow->powwed = (DWM_CONNECTOW_POWW_CONNECT |
			     DWM_CONNECTOW_POWW_DISCONNECT);

	connectow->intewwace_awwowed = 1;
	connectow->doubwescan_awwowed = 0;
	connectow->steweo_awwowed = 1;

	if (vc4_hdmi->vawiant->suppowts_hdw)
		dwm_connectow_attach_hdw_output_metadata_pwopewty(connectow);

	vc4_hdmi_attach_bwoadcast_wgb_pwopewty(dev, vc4_hdmi);

	dwm_connectow_attach_encodew(connectow, encodew);

	wetuwn 0;
}

static int vc4_hdmi_stop_packet(stwuct dwm_encodew *encodew,
				enum hdmi_infofwame_type type,
				boow poww)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	u32 packet_id = type - 0x80;
	unsigned wong fwags;
	int wet = 0;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn -ENODEV;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_WAM_PACKET_CONFIG,
		   HDMI_WEAD(HDMI_WAM_PACKET_CONFIG) & ~BIT(packet_id));
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (poww) {
		wet = wait_fow(!(HDMI_WEAD(HDMI_WAM_PACKET_STATUS) &
				 BIT(packet_id)), 100);
	}

	dwm_dev_exit(idx);
	wetuwn wet;
}

static void vc4_hdmi_wwite_infofwame(stwuct dwm_encodew *encodew,
				     union hdmi_infofwame *fwame)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	u32 packet_id = fwame->any.type - 0x80;
	const stwuct vc4_hdmi_wegistew *wam_packet_stawt =
		&vc4_hdmi->vawiant->wegistews[HDMI_WAM_PACKET_STAWT];
	u32 packet_weg = wam_packet_stawt->offset + VC4_HDMI_PACKET_STWIDE * packet_id;
	u32 packet_weg_next = wam_packet_stawt->offset +
		VC4_HDMI_PACKET_STWIDE * (packet_id + 1);
	void __iomem *base = __vc4_hdmi_get_fiewd_base(vc4_hdmi,
						       wam_packet_stawt->weg);
	uint8_t buffew[VC4_HDMI_PACKET_STWIDE] = {};
	unsigned wong fwags;
	ssize_t wen, i;
	int wet;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	WAWN_ONCE(!(HDMI_WEAD(HDMI_WAM_PACKET_CONFIG) &
		    VC4_HDMI_WAM_PACKET_ENABWE),
		  "Packet WAM has to be on to stowe the packet.");

	wen = hdmi_infofwame_pack(fwame, buffew, sizeof(buffew));
	if (wen < 0)
		goto out;

	wet = vc4_hdmi_stop_packet(encodew, fwame->any.type, twue);
	if (wet) {
		DWM_EWWOW("Faiwed to wait fow infofwame to go idwe: %d\n", wet);
		goto out;
	}

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	fow (i = 0; i < wen; i += 7) {
		wwitew(buffew[i + 0] << 0 |
		       buffew[i + 1] << 8 |
		       buffew[i + 2] << 16,
		       base + packet_weg);
		packet_weg += 4;

		wwitew(buffew[i + 3] << 0 |
		       buffew[i + 4] << 8 |
		       buffew[i + 5] << 16 |
		       buffew[i + 6] << 24,
		       base + packet_weg);
		packet_weg += 4;
	}

	/*
	 * cweaw wemaindew of packet wam as it's incwuded in the
	 * infofwame and twiggews a checksum ewwow on hdmi anawysew
	 */
	fow (; packet_weg < packet_weg_next; packet_weg += 4)
		wwitew(0, base + packet_weg);

	HDMI_WWITE(HDMI_WAM_PACKET_CONFIG,
		   HDMI_WEAD(HDMI_WAM_PACKET_CONFIG) | BIT(packet_id));

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	wet = wait_fow((HDMI_WEAD(HDMI_WAM_PACKET_STATUS) &
			BIT(packet_id)), 100);
	if (wet)
		DWM_EWWOW("Faiwed to wait fow infofwame to stawt: %d\n", wet);

out:
	dwm_dev_exit(idx);
}

static void vc4_hdmi_avi_infofwame_cowowspace(stwuct hdmi_avi_infofwame *fwame,
					      enum vc4_hdmi_output_fowmat fmt)
{
	switch (fmt) {
	case VC4_HDMI_OUTPUT_WGB:
		fwame->cowowspace = HDMI_COWOWSPACE_WGB;
		bweak;

	case VC4_HDMI_OUTPUT_YUV420:
		fwame->cowowspace = HDMI_COWOWSPACE_YUV420;
		bweak;

	case VC4_HDMI_OUTPUT_YUV422:
		fwame->cowowspace = HDMI_COWOWSPACE_YUV422;
		bweak;

	case VC4_HDMI_OUTPUT_YUV444:
		fwame->cowowspace = HDMI_COWOWSPACE_YUV444;
		bweak;

	defauwt:
		bweak;
	}
}

static void vc4_hdmi_set_avi_infofwame(stwuct dwm_encodew *encodew)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_connectow_state *cstate = connectow->state;
	stwuct vc4_hdmi_connectow_state *vc4_state =
		conn_state_to_vc4_hdmi_conn_state(cstate);
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	union hdmi_infofwame fwame;
	int wet;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame.avi,
						       connectow, mode);
	if (wet < 0) {
		DWM_EWWOW("couwdn't fiww AVI infofwame\n");
		wetuwn;
	}

	dwm_hdmi_avi_infofwame_quant_wange(&fwame.avi,
					   connectow, mode,
					   vc4_hdmi_is_fuww_wange(vc4_hdmi, vc4_state) ?
					   HDMI_QUANTIZATION_WANGE_FUWW :
					   HDMI_QUANTIZATION_WANGE_WIMITED);
	dwm_hdmi_avi_infofwame_cowowimetwy(&fwame.avi, cstate);
	vc4_hdmi_avi_infofwame_cowowspace(&fwame.avi, vc4_state->output_fowmat);
	dwm_hdmi_avi_infofwame_baws(&fwame.avi, cstate);

	vc4_hdmi_wwite_infofwame(encodew, &fwame);
}

static void vc4_hdmi_set_spd_infofwame(stwuct dwm_encodew *encodew)
{
	union hdmi_infofwame fwame;
	int wet;

	wet = hdmi_spd_infofwame_init(&fwame.spd, "Bwoadcom", "Videocowe");
	if (wet < 0) {
		DWM_EWWOW("couwdn't fiww SPD infofwame\n");
		wetuwn;
	}

	fwame.spd.sdi = HDMI_SPD_SDI_PC;

	vc4_hdmi_wwite_infofwame(encodew, &fwame);
}

static void vc4_hdmi_set_audio_infofwame(stwuct dwm_encodew *encodew)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct hdmi_audio_infofwame *audio = &vc4_hdmi->audio.infofwame;
	union hdmi_infofwame fwame;

	memcpy(&fwame.audio, audio, sizeof(*audio));

	if (vc4_hdmi->packet_wam_enabwed)
		vc4_hdmi_wwite_infofwame(encodew, &fwame);
}

static void vc4_hdmi_set_hdw_infofwame(stwuct dwm_encodew *encodew)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_connectow_state *conn_state = connectow->state;
	union hdmi_infofwame fwame;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	if (!vc4_hdmi->vawiant->suppowts_hdw)
		wetuwn;

	if (!conn_state->hdw_output_metadata)
		wetuwn;

	if (dwm_hdmi_infofwame_set_hdw_metadata(&fwame.dwm, conn_state))
		wetuwn;

	vc4_hdmi_wwite_infofwame(encodew, &fwame);
}

static void vc4_hdmi_set_infofwames(stwuct dwm_encodew *encodew)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	vc4_hdmi_set_avi_infofwame(encodew);
	vc4_hdmi_set_spd_infofwame(encodew);
	/*
	 * If audio was stweaming, then we need to weenabwed the audio
	 * infofwame hewe duwing encodew_enabwe.
	 */
	if (vc4_hdmi->audio.stweaming)
		vc4_hdmi_set_audio_infofwame(encodew);

	vc4_hdmi_set_hdw_infofwame(encodew);
}

#define SCWAMBWING_POWWING_DEWAY_MS	1000

static void vc4_hdmi_enabwe_scwambwing(stwuct dwm_encodew *encodew)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_device *dwm = connectow->dev;
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	unsigned wong fwags;
	int idx;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	if (!vc4_hdmi_suppowts_scwambwing(vc4_hdmi))
		wetuwn;

	if (!vc4_hdmi_mode_needs_scwambwing(mode,
					    vc4_hdmi->output_bpc,
					    vc4_hdmi->output_fowmat))
		wetuwn;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	dwm_scdc_set_high_tmds_cwock_watio(connectow, twue);
	dwm_scdc_set_scwambwing(connectow, twue);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_SCWAMBWEW_CTW, HDMI_WEAD(HDMI_SCWAMBWEW_CTW) |
		   VC5_HDMI_SCWAMBWEW_CTW_ENABWE);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);

	vc4_hdmi->scdc_enabwed = twue;

	queue_dewayed_wowk(system_wq, &vc4_hdmi->scwambwing_wowk,
			   msecs_to_jiffies(SCWAMBWING_POWWING_DEWAY_MS));
}

static void vc4_hdmi_disabwe_scwambwing(stwuct dwm_encodew *encodew)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_device *dwm = connectow->dev;
	unsigned wong fwags;
	int idx;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	if (!vc4_hdmi->scdc_enabwed)
		wetuwn;

	vc4_hdmi->scdc_enabwed = fawse;

	if (dewayed_wowk_pending(&vc4_hdmi->scwambwing_wowk))
		cancew_dewayed_wowk_sync(&vc4_hdmi->scwambwing_wowk);

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_SCWAMBWEW_CTW, HDMI_WEAD(HDMI_SCWAMBWEW_CTW) &
		   ~VC5_HDMI_SCWAMBWEW_CTW_ENABWE);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_scdc_set_scwambwing(connectow, fawse);
	dwm_scdc_set_high_tmds_cwock_watio(connectow, fawse);

	dwm_dev_exit(idx);
}

static void vc4_hdmi_scwambwing_wq(stwuct wowk_stwuct *wowk)
{
	stwuct vc4_hdmi *vc4_hdmi = containew_of(to_dewayed_wowk(wowk),
						 stwuct vc4_hdmi,
						 scwambwing_wowk);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;

	if (dwm_scdc_get_scwambwing_status(connectow))
		wetuwn;

	dwm_scdc_set_high_tmds_cwock_watio(connectow, twue);
	dwm_scdc_set_scwambwing(connectow, twue);

	queue_dewayed_wowk(system_wq, &vc4_hdmi->scwambwing_wowk,
			   msecs_to_jiffies(SCWAMBWING_POWWING_DEWAY_MS));
}

static void vc4_hdmi_encodew_post_cwtc_disabwe(stwuct dwm_encodew *encodew,
					       stwuct dwm_atomic_state *state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	vc4_hdmi->packet_wam_enabwed = fawse;

	if (!dwm_dev_entew(dwm, &idx))
		goto out;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_WAM_PACKET_CONFIG, 0);

	HDMI_WWITE(HDMI_VID_CTW, HDMI_WEAD(HDMI_VID_CTW) | VC4_HD_VID_CTW_CWWWGB);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	mdeway(1);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_VID_CTW,
		   HDMI_WEAD(HDMI_VID_CTW) & ~VC4_HD_VID_CTW_ENABWE);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	vc4_hdmi_disabwe_scwambwing(encodew);

	dwm_dev_exit(idx);

out:
	mutex_unwock(&vc4_hdmi->mutex);
}

static void vc4_hdmi_encodew_post_cwtc_powewdown(stwuct dwm_encodew *encodew,
						 stwuct dwm_atomic_state *state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int wet;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx))
		goto out;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_VID_CTW,
		   HDMI_WEAD(HDMI_VID_CTW) | VC4_HD_VID_CTW_BWANKPIX);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (vc4_hdmi->vawiant->phy_disabwe)
		vc4_hdmi->vawiant->phy_disabwe(vc4_hdmi);

	cwk_disabwe_unpwepawe(vc4_hdmi->pixew_bvb_cwock);
	cwk_disabwe_unpwepawe(vc4_hdmi->pixew_cwock);

	wet = pm_wuntime_put(&vc4_hdmi->pdev->dev);
	if (wet < 0)
		DWM_EWWOW("Faiwed to wewease powew domain: %d\n", wet);

	dwm_dev_exit(idx);

out:
	mutex_unwock(&vc4_hdmi->mutex);
}

static void vc4_hdmi_csc_setup(stwuct vc4_hdmi *vc4_hdmi,
			       stwuct dwm_connectow_state *state,
			       const stwuct dwm_dispway_mode *mode)
{
	stwuct vc4_hdmi_connectow_state *vc4_state =
		conn_state_to_vc4_hdmi_conn_state(state);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	u32 csc_ctw;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	csc_ctw = VC4_SET_FIEWD(VC4_HD_CSC_CTW_OWDEW_BGW,
				VC4_HD_CSC_CTW_OWDEW);

	if (!vc4_hdmi_is_fuww_wange(vc4_hdmi, vc4_state)) {
		/* CEA VICs othew than #1 wequwe wimited wange WGB
		 * output unwess ovewwidden by an AVI infofwame.
		 * Appwy a cowowspace convewsion to squash 0-255 down
		 * to 16-235.  The matwix hewe is:
		 *
		 * [ 0      0      0.8594 16]
		 * [ 0      0.8594 0      16]
		 * [ 0.8594 0      0      16]
		 * [ 0      0      0       1]
		 */
		csc_ctw |= VC4_HD_CSC_CTW_ENABWE;
		csc_ctw |= VC4_HD_CSC_CTW_WGB2YCC;
		csc_ctw |= VC4_SET_FIEWD(VC4_HD_CSC_CTW_MODE_CUSTOM,
					 VC4_HD_CSC_CTW_MODE);

		HDMI_WWITE(HDMI_CSC_12_11, (0x000 << 16) | 0x000);
		HDMI_WWITE(HDMI_CSC_14_13, (0x100 << 16) | 0x6e0);
		HDMI_WWITE(HDMI_CSC_22_21, (0x6e0 << 16) | 0x000);
		HDMI_WWITE(HDMI_CSC_24_23, (0x100 << 16) | 0x000);
		HDMI_WWITE(HDMI_CSC_32_31, (0x000 << 16) | 0x6e0);
		HDMI_WWITE(HDMI_CSC_34_33, (0x100 << 16) | 0x000);
	}

	/* The WGB owdew appwies even when CSC is disabwed. */
	HDMI_WWITE(HDMI_CSC_CTW, csc_ctw);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);
}

/*
 * Matwices fow (intewnaw) WGB to WGB output.
 *
 * Matwices awe signed 2p13 fixed point, with signed 9p6 offsets
 */
static const u16 vc5_hdmi_csc_fuww_wgb_to_wgb[2][3][4] = {
	{
		/*
		 * Fuww wange - unity
		 *
		 * [ 1      0      0      0]
		 * [ 0      1      0      0]
		 * [ 0      0      1      0]
		 */
		{ 0x2000, 0x0000, 0x0000, 0x0000 },
		{ 0x0000, 0x2000, 0x0000, 0x0000 },
		{ 0x0000, 0x0000, 0x2000, 0x0000 },
	},
	{
		/*
		 * Wimited wange
		 *
		 * CEA VICs othew than #1 wequiwe wimited wange WGB
		 * output unwess ovewwidden by an AVI infofwame. Appwy a
		 * cowowspace convewsion to squash 0-255 down to 16-235.
		 * The matwix hewe is:
		 *
		 * [ 0.8594 0      0      16]
		 * [ 0      0.8594 0      16]
		 * [ 0      0      0.8594 16]
		 */
		{ 0x1b80, 0x0000, 0x0000, 0x0400 },
		{ 0x0000, 0x1b80, 0x0000, 0x0400 },
		{ 0x0000, 0x0000, 0x1b80, 0x0400 },
	},
};

/*
 * Convewsion between Fuww Wange WGB and YUV using the BT.601 Cowowspace
 *
 * Matwices awe signed 2p13 fixed point, with signed 9p6 offsets
 */
static const u16 vc5_hdmi_csc_fuww_wgb_to_yuv_bt601[2][3][4] = {
	{
		/*
		 * Fuww Wange
		 *
		 * [  0.299000  0.587000  0.114000  0   ]
		 * [ -0.168736 -0.331264  0.500000  128 ]
		 * [  0.500000 -0.418688 -0.081312  128 ]
		 */
		{ 0x0991, 0x12c9, 0x03a6, 0x0000 },
		{ 0xfa9b, 0xf567, 0x1000, 0x2000 },
		{ 0x1000, 0xf29b, 0xfd67, 0x2000 },
	},
	{
		/* Wimited Wange
		 *
		 * [  0.255785  0.502160  0.097523  16  ]
		 * [ -0.147644 -0.289856  0.437500  128 ]
		 * [  0.437500 -0.366352 -0.071148  128 ]
		 */
		{ 0x082f, 0x1012, 0x031f, 0x0400 },
		{ 0xfb48, 0xf6ba, 0x0e00, 0x2000 },
		{ 0x0e00, 0xf448, 0xfdba, 0x2000 },
	},
};

/*
 * Convewsion between Fuww Wange WGB and YUV using the BT.709 Cowowspace
 *
 * Matwices awe signed 2p13 fixed point, with signed 9p6 offsets
 */
static const u16 vc5_hdmi_csc_fuww_wgb_to_yuv_bt709[2][3][4] = {
	{
		/*
		 * Fuww Wange
		 *
		 * [  0.212600  0.715200  0.072200  0   ]
		 * [ -0.114572 -0.385428  0.500000  128 ]
		 * [  0.500000 -0.454153 -0.045847  128 ]
		 */
		{ 0x06ce, 0x16e3, 0x024f, 0x0000 },
		{ 0xfc56, 0xf3ac, 0x1000, 0x2000 },
		{ 0x1000, 0xf179, 0xfe89, 0x2000 },
	},
	{
		/*
		 * Wimited Wange
		 *
		 * [  0.181906  0.611804  0.061758  16  ]
		 * [ -0.100268 -0.337232  0.437500  128 ]
		 * [  0.437500 -0.397386 -0.040114  128 ]
		 */
		{ 0x05d2, 0x1394, 0x01fa, 0x0400 },
		{ 0xfccc, 0xf536, 0x0e00, 0x2000 },
		{ 0x0e00, 0xf34a, 0xfeb8, 0x2000 },
	},
};

/*
 * Convewsion between Fuww Wange WGB and YUV using the BT.2020 Cowowspace
 *
 * Matwices awe signed 2p13 fixed point, with signed 9p6 offsets
 */
static const u16 vc5_hdmi_csc_fuww_wgb_to_yuv_bt2020[2][3][4] = {
	{
		/*
		 * Fuww Wange
		 *
		 * [  0.262700  0.678000  0.059300  0   ]
		 * [ -0.139630 -0.360370  0.500000  128 ]
		 * [  0.500000 -0.459786 -0.040214  128 ]
		 */
		{ 0x0868, 0x15b2, 0x01e6, 0x0000 },
		{ 0xfb89, 0xf479, 0x1000, 0x2000 },
		{ 0x1000, 0xf14a, 0xfeb8, 0x2000 },
	},
	{
		/* Wimited Wange
		 *
		 * [  0.224732  0.580008  0.050729  16  ]
		 * [ -0.122176 -0.315324  0.437500  128 ]
		 * [  0.437500 -0.402312 -0.035188  128 ]
		 */
		{ 0x082f, 0x1012, 0x031f, 0x0400 },
		{ 0xfb48, 0xf6ba, 0x0e00, 0x2000 },
		{ 0x0e00, 0xf448, 0xfdba, 0x2000 },
	},
};

static void vc5_hdmi_set_csc_coeffs(stwuct vc4_hdmi *vc4_hdmi,
				    const u16 coeffs[3][4])
{
	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	HDMI_WWITE(HDMI_CSC_12_11, (coeffs[0][1] << 16) | coeffs[0][0]);
	HDMI_WWITE(HDMI_CSC_14_13, (coeffs[0][3] << 16) | coeffs[0][2]);
	HDMI_WWITE(HDMI_CSC_22_21, (coeffs[1][1] << 16) | coeffs[1][0]);
	HDMI_WWITE(HDMI_CSC_24_23, (coeffs[1][3] << 16) | coeffs[1][2]);
	HDMI_WWITE(HDMI_CSC_32_31, (coeffs[2][1] << 16) | coeffs[2][0]);
	HDMI_WWITE(HDMI_CSC_34_33, (coeffs[2][3] << 16) | coeffs[2][2]);
}

static void vc5_hdmi_set_csc_coeffs_swap(stwuct vc4_hdmi *vc4_hdmi,
					 const u16 coeffs[3][4])
{
	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	/* YUV444 needs the CSC matwices using the channews in a diffewent owdew */
	HDMI_WWITE(HDMI_CSC_12_11, (coeffs[1][1] << 16) | coeffs[1][0]);
	HDMI_WWITE(HDMI_CSC_14_13, (coeffs[1][3] << 16) | coeffs[1][2]);
	HDMI_WWITE(HDMI_CSC_22_21, (coeffs[2][1] << 16) | coeffs[2][0]);
	HDMI_WWITE(HDMI_CSC_24_23, (coeffs[2][3] << 16) | coeffs[2][2]);
	HDMI_WWITE(HDMI_CSC_32_31, (coeffs[0][1] << 16) | coeffs[0][0]);
	HDMI_WWITE(HDMI_CSC_34_33, (coeffs[0][3] << 16) | coeffs[0][2]);
}

static const u16
(*vc5_hdmi_find_yuv_csc_coeffs(stwuct vc4_hdmi *vc4_hdmi, u32 cowowspace, boow wimited))[4]
{
	switch (cowowspace) {
	case DWM_MODE_COWOWIMETWY_SMPTE_170M_YCC:
	case DWM_MODE_COWOWIMETWY_XVYCC_601:
	case DWM_MODE_COWOWIMETWY_SYCC_601:
	case DWM_MODE_COWOWIMETWY_OPYCC_601:
	case DWM_MODE_COWOWIMETWY_BT601_YCC:
		wetuwn vc5_hdmi_csc_fuww_wgb_to_yuv_bt601[wimited];

	defauwt:
	case DWM_MODE_COWOWIMETWY_NO_DATA:
	case DWM_MODE_COWOWIMETWY_BT709_YCC:
	case DWM_MODE_COWOWIMETWY_XVYCC_709:
	case DWM_MODE_COWOWIMETWY_WGB_WIDE_FIXED:
	case DWM_MODE_COWOWIMETWY_WGB_WIDE_FWOAT:
		wetuwn vc5_hdmi_csc_fuww_wgb_to_yuv_bt709[wimited];

	case DWM_MODE_COWOWIMETWY_BT2020_CYCC:
	case DWM_MODE_COWOWIMETWY_BT2020_YCC:
	case DWM_MODE_COWOWIMETWY_BT2020_WGB:
	case DWM_MODE_COWOWIMETWY_DCI_P3_WGB_D65:
	case DWM_MODE_COWOWIMETWY_DCI_P3_WGB_THEATEW:
		wetuwn vc5_hdmi_csc_fuww_wgb_to_yuv_bt2020[wimited];
	}
}

static void vc5_hdmi_csc_setup(stwuct vc4_hdmi *vc4_hdmi,
			       stwuct dwm_connectow_state *state,
			       const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	stwuct vc4_hdmi_connectow_state *vc4_state =
		conn_state_to_vc4_hdmi_conn_state(state);
	unsigned int wim_wange = vc4_hdmi_is_fuww_wange(vc4_hdmi, vc4_state) ? 0 : 1;
	unsigned wong fwags;
	const u16 (*csc)[4];
	u32 if_cfg = 0;
	u32 if_xbaw = 0x543210;
	u32 csc_chan_ctw = 0;
	u32 csc_ctw = VC5_MT_CP_CSC_CTW_ENABWE | VC4_SET_FIEWD(VC4_HD_CSC_CTW_MODE_CUSTOM,
							       VC5_MT_CP_CSC_CTW_MODE);
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	switch (vc4_state->output_fowmat) {
	case VC4_HDMI_OUTPUT_YUV444:
		csc = vc5_hdmi_find_yuv_csc_coeffs(vc4_hdmi, state->cowowspace, !!wim_wange);

		vc5_hdmi_set_csc_coeffs_swap(vc4_hdmi, csc);
		bweak;

	case VC4_HDMI_OUTPUT_YUV422:
		csc = vc5_hdmi_find_yuv_csc_coeffs(vc4_hdmi, state->cowowspace, !!wim_wange);

		csc_ctw |= VC4_SET_FIEWD(VC5_MT_CP_CSC_CTW_FIWTEW_MODE_444_TO_422_STANDAWD,
					 VC5_MT_CP_CSC_CTW_FIWTEW_MODE_444_TO_422) |
			VC5_MT_CP_CSC_CTW_USE_444_TO_422 |
			VC5_MT_CP_CSC_CTW_USE_WNG_SUPPWESSION;

		csc_chan_ctw |= VC4_SET_FIEWD(VC5_MT_CP_CHANNEW_CTW_OUTPUT_WEMAP_WEGACY_STYWE,
					      VC5_MT_CP_CHANNEW_CTW_OUTPUT_WEMAP);

		if_cfg |= VC4_SET_FIEWD(VC5_DVP_HT_VEC_INTEWFACE_CFG_SEW_422_FOWMAT_422_WEGACY,
					VC5_DVP_HT_VEC_INTEWFACE_CFG_SEW_422);

		vc5_hdmi_set_csc_coeffs(vc4_hdmi, csc);
		bweak;

	case VC4_HDMI_OUTPUT_WGB:
		if_xbaw = 0x354021;

		vc5_hdmi_set_csc_coeffs(vc4_hdmi, vc5_hdmi_csc_fuww_wgb_to_wgb[wim_wange]);
		bweak;

	defauwt:
		bweak;
	}

	HDMI_WWITE(HDMI_VEC_INTEWFACE_CFG, if_cfg);
	HDMI_WWITE(HDMI_VEC_INTEWFACE_XBAW, if_xbaw);
	HDMI_WWITE(HDMI_CSC_CHANNEW_CTW, csc_chan_ctw);
	HDMI_WWITE(HDMI_CSC_CTW, csc_ctw);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);
}

static void vc4_hdmi_set_timings(stwuct vc4_hdmi *vc4_hdmi,
				 stwuct dwm_connectow_state *state,
				 const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	boow hsync_pos = mode->fwags & DWM_MODE_FWAG_PHSYNC;
	boow vsync_pos = mode->fwags & DWM_MODE_FWAG_PVSYNC;
	boow intewwaced = mode->fwags & DWM_MODE_FWAG_INTEWWACE;
	u32 pixew_wep = (mode->fwags & DWM_MODE_FWAG_DBWCWK) ? 2 : 1;
	u32 vewta = (VC4_SET_FIEWD(mode->cwtc_vsync_end - mode->cwtc_vsync_stawt,
				   VC4_HDMI_VEWTA_VSP) |
		     VC4_SET_FIEWD(mode->cwtc_vsync_stawt - mode->cwtc_vdispway,
				   VC4_HDMI_VEWTA_VFP) |
		     VC4_SET_FIEWD(mode->cwtc_vdispway, VC4_HDMI_VEWTA_VAW));
	u32 vewtb = (VC4_SET_FIEWD(0, VC4_HDMI_VEWTB_VSPO) |
		     VC4_SET_FIEWD(mode->cwtc_vtotaw - mode->cwtc_vsync_end +
				   intewwaced,
				   VC4_HDMI_VEWTB_VBP));
	u32 vewtb_even = (VC4_SET_FIEWD(0, VC4_HDMI_VEWTB_VSPO) |
			  VC4_SET_FIEWD(mode->cwtc_vtotaw -
					mode->cwtc_vsync_end,
					VC4_HDMI_VEWTB_VBP));
	unsigned wong fwags;
	u32 weg;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_HOWZA,
		   (vsync_pos ? VC4_HDMI_HOWZA_VPOS : 0) |
		   (hsync_pos ? VC4_HDMI_HOWZA_HPOS : 0) |
		   VC4_SET_FIEWD(mode->hdispway * pixew_wep,
				 VC4_HDMI_HOWZA_HAP));

	HDMI_WWITE(HDMI_HOWZB,
		   VC4_SET_FIEWD((mode->htotaw -
				  mode->hsync_end) * pixew_wep,
				 VC4_HDMI_HOWZB_HBP) |
		   VC4_SET_FIEWD((mode->hsync_end -
				  mode->hsync_stawt) * pixew_wep,
				 VC4_HDMI_HOWZB_HSP) |
		   VC4_SET_FIEWD((mode->hsync_stawt -
				  mode->hdispway) * pixew_wep,
				 VC4_HDMI_HOWZB_HFP));

	HDMI_WWITE(HDMI_VEWTA0, vewta);
	HDMI_WWITE(HDMI_VEWTA1, vewta);

	HDMI_WWITE(HDMI_VEWTB0, vewtb_even);
	HDMI_WWITE(HDMI_VEWTB1, vewtb);

	weg = HDMI_WEAD(HDMI_MISC_CONTWOW);
	weg &= ~VC4_HDMI_MISC_CONTWOW_PIXEW_WEP_MASK;
	weg |= VC4_SET_FIEWD(pixew_wep - 1, VC4_HDMI_MISC_CONTWOW_PIXEW_WEP);
	HDMI_WWITE(HDMI_MISC_CONTWOW, weg);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);
}

static void vc5_hdmi_set_timings(stwuct vc4_hdmi *vc4_hdmi,
				 stwuct dwm_connectow_state *state,
				 const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	const stwuct vc4_hdmi_connectow_state *vc4_state =
		conn_state_to_vc4_hdmi_conn_state(state);
	boow hsync_pos = mode->fwags & DWM_MODE_FWAG_PHSYNC;
	boow vsync_pos = mode->fwags & DWM_MODE_FWAG_PVSYNC;
	boow intewwaced = mode->fwags & DWM_MODE_FWAG_INTEWWACE;
	u32 pixew_wep = (mode->fwags & DWM_MODE_FWAG_DBWCWK) ? 2 : 1;
	u32 vewta = (VC4_SET_FIEWD(mode->cwtc_vsync_end - mode->cwtc_vsync_stawt,
				   VC5_HDMI_VEWTA_VSP) |
		     VC4_SET_FIEWD(mode->cwtc_vsync_stawt - mode->cwtc_vdispway,
				   VC5_HDMI_VEWTA_VFP) |
		     VC4_SET_FIEWD(mode->cwtc_vdispway, VC5_HDMI_VEWTA_VAW));
	u32 vewtb = (VC4_SET_FIEWD(mode->htotaw >> (2 - pixew_wep),
				   VC5_HDMI_VEWTB_VSPO) |
		     VC4_SET_FIEWD(mode->cwtc_vtotaw - mode->cwtc_vsync_end +
				   intewwaced,
				   VC4_HDMI_VEWTB_VBP));
	u32 vewtb_even = (VC4_SET_FIEWD(0, VC5_HDMI_VEWTB_VSPO) |
			  VC4_SET_FIEWD(mode->cwtc_vtotaw -
					mode->cwtc_vsync_end,
					VC4_HDMI_VEWTB_VBP));
	unsigned wong fwags;
	unsigned chaw gcp;
	u32 weg;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_HOWZA,
		   (vsync_pos ? VC5_HDMI_HOWZA_VPOS : 0) |
		   (hsync_pos ? VC5_HDMI_HOWZA_HPOS : 0) |
		   VC4_SET_FIEWD(mode->hdispway * pixew_wep,
				 VC5_HDMI_HOWZA_HAP) |
		   VC4_SET_FIEWD((mode->hsync_stawt -
				  mode->hdispway) * pixew_wep,
				 VC5_HDMI_HOWZA_HFP));

	HDMI_WWITE(HDMI_HOWZB,
		   VC4_SET_FIEWD((mode->htotaw -
				  mode->hsync_end) * pixew_wep,
				 VC5_HDMI_HOWZB_HBP) |
		   VC4_SET_FIEWD((mode->hsync_end -
				  mode->hsync_stawt) * pixew_wep,
				 VC5_HDMI_HOWZB_HSP));

	HDMI_WWITE(HDMI_VEWTA0, vewta);
	HDMI_WWITE(HDMI_VEWTA1, vewta);

	HDMI_WWITE(HDMI_VEWTB0, vewtb_even);
	HDMI_WWITE(HDMI_VEWTB1, vewtb);

	switch (vc4_state->output_bpc) {
	case 12:
		gcp = 6;
		bweak;
	case 10:
		gcp = 5;
		bweak;
	case 8:
	defauwt:
		gcp = 0;
		bweak;
	}

	/*
	 * YCC422 is awways 36-bit and not considewed deep cowouw so
	 * doesn't signaw in GCP.
	 */
	if (vc4_state->output_fowmat == VC4_HDMI_OUTPUT_YUV422) {
		gcp = 0;
	}

	weg = HDMI_WEAD(HDMI_DEEP_COWOW_CONFIG_1);
	weg &= ~(VC5_HDMI_DEEP_COWOW_CONFIG_1_INIT_PACK_PHASE_MASK |
		 VC5_HDMI_DEEP_COWOW_CONFIG_1_COWOW_DEPTH_MASK);
	weg |= VC4_SET_FIEWD(2, VC5_HDMI_DEEP_COWOW_CONFIG_1_INIT_PACK_PHASE) |
	       VC4_SET_FIEWD(gcp, VC5_HDMI_DEEP_COWOW_CONFIG_1_COWOW_DEPTH);
	HDMI_WWITE(HDMI_DEEP_COWOW_CONFIG_1, weg);

	weg = HDMI_WEAD(HDMI_GCP_WOWD_1);
	weg &= ~VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_1_MASK;
	weg |= VC4_SET_FIEWD(gcp, VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_1);
	weg &= ~VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_0_MASK;
	weg |= VC5_HDMI_GCP_WOWD_1_GCP_SUBPACKET_BYTE_0_CWEAW_AVMUTE;
	HDMI_WWITE(HDMI_GCP_WOWD_1, weg);

	weg = HDMI_WEAD(HDMI_GCP_CONFIG);
	weg |= VC5_HDMI_GCP_CONFIG_GCP_ENABWE;
	HDMI_WWITE(HDMI_GCP_CONFIG, weg);

	weg = HDMI_WEAD(HDMI_MISC_CONTWOW);
	weg &= ~VC5_HDMI_MISC_CONTWOW_PIXEW_WEP_MASK;
	weg |= VC4_SET_FIEWD(pixew_wep - 1, VC5_HDMI_MISC_CONTWOW_PIXEW_WEP);
	HDMI_WWITE(HDMI_MISC_CONTWOW, weg);

	HDMI_WWITE(HDMI_CWOCK_STOP, 0);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);
}

static void vc4_hdmi_wecentew_fifo(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	u32 dwift;
	int wet;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	dwift = HDMI_WEAD(HDMI_FIFO_CTW);
	dwift &= VC4_HDMI_FIFO_VAWID_WWITE_MASK;

	HDMI_WWITE(HDMI_FIFO_CTW,
		   dwift & ~VC4_HDMI_FIFO_CTW_WECENTEW);
	HDMI_WWITE(HDMI_FIFO_CTW,
		   dwift | VC4_HDMI_FIFO_CTW_WECENTEW);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	usweep_wange(1000, 1100);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_FIFO_CTW,
		   dwift & ~VC4_HDMI_FIFO_CTW_WECENTEW);
	HDMI_WWITE(HDMI_FIFO_CTW,
		   dwift | VC4_HDMI_FIFO_CTW_WECENTEW);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	wet = wait_fow(HDMI_WEAD(HDMI_FIFO_CTW) &
		       VC4_HDMI_FIFO_CTW_WECENTEW_DONE, 1);
	WAWN_ONCE(wet, "Timeout waiting fow "
		  "VC4_HDMI_FIFO_CTW_WECENTEW_DONE");

	dwm_dev_exit(idx);
}

static void vc4_hdmi_encodew_pwe_cwtc_configuwe(stwuct dwm_encodew *encodew,
						stwuct dwm_atomic_state *state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_connectow_state *conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	stwuct vc4_hdmi_connectow_state *vc4_conn_state =
		conn_state_to_vc4_hdmi_conn_state(conn_state);
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	unsigned wong tmds_chaw_wate = vc4_conn_state->tmds_chaw_wate;
	unsigned wong bvb_wate, hsm_wate;
	unsigned wong fwags;
	int wet;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx))
		goto out;

	wet = pm_wuntime_wesume_and_get(&vc4_hdmi->pdev->dev);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to wetain powew domain: %d\n", wet);
		goto eww_dev_exit;
	}

	/*
	 * As stated in WPi's vc4 fiwmwawe "HDMI state machine (HSM) cwock must
	 * be fastew than pixew cwock, infinitesimawwy fastew, tested in
	 * simuwation. Othewwise, exact vawue is unimpowtant fow HDMI
	 * opewation." This confwicts with bcm2835's vc4 documentation, which
	 * states HSM's cwock has to be at weast 108% of the pixew cwock.
	 *
	 * Weaw wife tests weveaw that vc4's fiwmwawe statement howds up, and
	 * usews awe abwe to use pixew cwocks cwosew to HSM's, namewy fow
	 * 1920x1200@60Hz. So it was decided to have weave a 1% mawgin between
	 * both cwocks. Which, fow WPi0-3 impwies a maximum pixew cwock of
	 * 162MHz.
	 *
	 * Additionawwy, the AXI cwock needs to be at weast 25% of
	 * pixew cwock, but HSM ends up being the wimiting factow.
	 */
	hsm_wate = max_t(unsigned wong,
			 HSM_MIN_CWOCK_FWEQ,
			 (tmds_chaw_wate / 100) * 101);
	wet = cwk_set_min_wate(vc4_hdmi->hsm_cwock, hsm_wate);
	if (wet) {
		DWM_EWWOW("Faiwed to set HSM cwock wate: %d\n", wet);
		goto eww_put_wuntime_pm;
	}

	wet = cwk_set_wate(vc4_hdmi->pixew_cwock, tmds_chaw_wate);
	if (wet) {
		DWM_EWWOW("Faiwed to set pixew cwock wate: %d\n", wet);
		goto eww_put_wuntime_pm;
	}

	wet = cwk_pwepawe_enabwe(vc4_hdmi->pixew_cwock);
	if (wet) {
		DWM_EWWOW("Faiwed to tuwn on pixew cwock: %d\n", wet);
		goto eww_put_wuntime_pm;
	}


	vc4_hdmi_cec_update_cwk_div(vc4_hdmi);

	if (tmds_chaw_wate > 297000000)
		bvb_wate = 300000000;
	ewse if (tmds_chaw_wate > 148500000)
		bvb_wate = 150000000;
	ewse
		bvb_wate = 75000000;

	wet = cwk_set_min_wate(vc4_hdmi->pixew_bvb_cwock, bvb_wate);
	if (wet) {
		DWM_EWWOW("Faiwed to set pixew bvb cwock wate: %d\n", wet);
		goto eww_disabwe_pixew_cwock;
	}

	wet = cwk_pwepawe_enabwe(vc4_hdmi->pixew_bvb_cwock);
	if (wet) {
		DWM_EWWOW("Faiwed to tuwn on pixew bvb cwock: %d\n", wet);
		goto eww_disabwe_pixew_cwock;
	}

	if (vc4_hdmi->vawiant->phy_init)
		vc4_hdmi->vawiant->phy_init(vc4_hdmi, vc4_conn_state);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_SCHEDUWEW_CONTWOW,
		   HDMI_WEAD(HDMI_SCHEDUWEW_CONTWOW) |
		   VC4_HDMI_SCHEDUWEW_CONTWOW_MANUAW_FOWMAT |
		   VC4_HDMI_SCHEDUWEW_CONTWOW_IGNOWE_VSYNC_PWEDICTS);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (vc4_hdmi->vawiant->set_timings)
		vc4_hdmi->vawiant->set_timings(vc4_hdmi, conn_state, mode);

	dwm_dev_exit(idx);

	mutex_unwock(&vc4_hdmi->mutex);

	wetuwn;

eww_disabwe_pixew_cwock:
	cwk_disabwe_unpwepawe(vc4_hdmi->pixew_cwock);
eww_put_wuntime_pm:
	pm_wuntime_put(&vc4_hdmi->pdev->dev);
eww_dev_exit:
	dwm_dev_exit(idx);
out:
	mutex_unwock(&vc4_hdmi->mutex);
	wetuwn;
}

static void vc4_hdmi_encodew_pwe_cwtc_enabwe(stwuct dwm_encodew *encodew,
					     stwuct dwm_atomic_state *state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	stwuct dwm_connectow_state *conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	unsigned wong fwags;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx))
		goto out;

	if (vc4_hdmi->vawiant->csc_setup)
		vc4_hdmi->vawiant->csc_setup(vc4_hdmi, conn_state, mode);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_FIFO_CTW, VC4_HDMI_FIFO_CTW_MASTEW_SWAVE_N);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);

out:
	mutex_unwock(&vc4_hdmi->mutex);
}

static void vc4_hdmi_encodew_post_cwtc_enabwe(stwuct dwm_encodew *encodew,
					      stwuct dwm_atomic_state *state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	stwuct dwm_dispway_info *dispway = &vc4_hdmi->connectow.dispway_info;
	boow hsync_pos = mode->fwags & DWM_MODE_FWAG_PHSYNC;
	boow vsync_pos = mode->fwags & DWM_MODE_FWAG_PVSYNC;
	unsigned wong fwags;
	int wet;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx))
		goto out;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_VID_CTW,
		   VC4_HD_VID_CTW_ENABWE |
		   VC4_HD_VID_CTW_CWWWGB |
		   VC4_HD_VID_CTW_UNDEWFWOW_ENABWE |
		   VC4_HD_VID_CTW_FWAME_COUNTEW_WESET |
		   (vsync_pos ? 0 : VC4_HD_VID_CTW_VSYNC_WOW) |
		   (hsync_pos ? 0 : VC4_HD_VID_CTW_HSYNC_WOW));

	HDMI_WWITE(HDMI_VID_CTW,
		   HDMI_WEAD(HDMI_VID_CTW) & ~VC4_HD_VID_CTW_BWANKPIX);

	if (dispway->is_hdmi) {
		HDMI_WWITE(HDMI_SCHEDUWEW_CONTWOW,
			   HDMI_WEAD(HDMI_SCHEDUWEW_CONTWOW) |
			   VC4_HDMI_SCHEDUWEW_CONTWOW_MODE_HDMI);

		spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

		wet = wait_fow(HDMI_WEAD(HDMI_SCHEDUWEW_CONTWOW) &
			       VC4_HDMI_SCHEDUWEW_CONTWOW_HDMI_ACTIVE, 1000);
		WAWN_ONCE(wet, "Timeout waiting fow "
			  "VC4_HDMI_SCHEDUWEW_CONTWOW_HDMI_ACTIVE\n");
	} ewse {
		HDMI_WWITE(HDMI_WAM_PACKET_CONFIG,
			   HDMI_WEAD(HDMI_WAM_PACKET_CONFIG) &
			   ~(VC4_HDMI_WAM_PACKET_ENABWE));
		HDMI_WWITE(HDMI_SCHEDUWEW_CONTWOW,
			   HDMI_WEAD(HDMI_SCHEDUWEW_CONTWOW) &
			   ~VC4_HDMI_SCHEDUWEW_CONTWOW_MODE_HDMI);

		spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

		wet = wait_fow(!(HDMI_WEAD(HDMI_SCHEDUWEW_CONTWOW) &
				 VC4_HDMI_SCHEDUWEW_CONTWOW_HDMI_ACTIVE), 1000);
		WAWN_ONCE(wet, "Timeout waiting fow "
			  "!VC4_HDMI_SCHEDUWEW_CONTWOW_HDMI_ACTIVE\n");
	}

	if (dispway->is_hdmi) {
		spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

		WAWN_ON(!(HDMI_WEAD(HDMI_SCHEDUWEW_CONTWOW) &
			  VC4_HDMI_SCHEDUWEW_CONTWOW_HDMI_ACTIVE));

		HDMI_WWITE(HDMI_WAM_PACKET_CONFIG,
			   VC4_HDMI_WAM_PACKET_ENABWE);

		spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
		vc4_hdmi->packet_wam_enabwed = twue;

		vc4_hdmi_set_infofwames(encodew);
	}

	vc4_hdmi_wecentew_fifo(vc4_hdmi);
	vc4_hdmi_enabwe_scwambwing(encodew);

	dwm_dev_exit(idx);

out:
	mutex_unwock(&vc4_hdmi->mutex);
}

static void vc4_hdmi_encodew_atomic_mode_set(stwuct dwm_encodew *encodew,
					     stwuct dwm_cwtc_state *cwtc_state,
					     stwuct dwm_connectow_state *conn_state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct vc4_hdmi_connectow_state *vc4_state =
		conn_state_to_vc4_hdmi_conn_state(conn_state);

	mutex_wock(&vc4_hdmi->mutex);
	dwm_mode_copy(&vc4_hdmi->saved_adjusted_mode,
		      &cwtc_state->adjusted_mode);
	vc4_hdmi->output_bpc = vc4_state->output_bpc;
	vc4_hdmi->output_fowmat = vc4_state->output_fowmat;
	mutex_unwock(&vc4_hdmi->mutex);
}

static boow
vc4_hdmi_sink_suppowts_fowmat_bpc(const stwuct vc4_hdmi *vc4_hdmi,
				  const stwuct dwm_dispway_info *info,
				  const stwuct dwm_dispway_mode *mode,
				  unsigned int fowmat, unsigned int bpc)
{
	stwuct dwm_device *dev = vc4_hdmi->connectow.dev;
	u8 vic = dwm_match_cea_mode(mode);

	if (vic == 1 && bpc != 8) {
		dwm_dbg(dev, "VIC1 wequiwes a bpc of 8, got %u\n", bpc);
		wetuwn fawse;
	}

	if (!info->is_hdmi &&
	    (fowmat != VC4_HDMI_OUTPUT_WGB || bpc != 8)) {
		dwm_dbg(dev, "DVI Monitows wequiwe an WGB output at 8 bpc\n");
		wetuwn fawse;
	}

	switch (fowmat) {
	case VC4_HDMI_OUTPUT_WGB:
		dwm_dbg(dev, "WGB Fowmat, checking the constwaints.\n");

		if (!(info->cowow_fowmats & DWM_COWOW_FOWMAT_WGB444))
			wetuwn fawse;

		if (bpc == 10 && !(info->edid_hdmi_wgb444_dc_modes & DWM_EDID_HDMI_DC_30)) {
			dwm_dbg(dev, "10 BPC but sink doesn't suppowt Deep Cowow 30.\n");
			wetuwn fawse;
		}

		if (bpc == 12 && !(info->edid_hdmi_wgb444_dc_modes & DWM_EDID_HDMI_DC_36)) {
			dwm_dbg(dev, "12 BPC but sink doesn't suppowt Deep Cowow 36.\n");
			wetuwn fawse;
		}

		dwm_dbg(dev, "WGB fowmat suppowted in that configuwation.\n");

		wetuwn twue;

	case VC4_HDMI_OUTPUT_YUV422:
		dwm_dbg(dev, "YUV422 fowmat, checking the constwaints.\n");

		if (!(info->cowow_fowmats & DWM_COWOW_FOWMAT_YCBCW422)) {
			dwm_dbg(dev, "Sink doesn't suppowt YUV422.\n");
			wetuwn fawse;
		}

		if (bpc != 12) {
			dwm_dbg(dev, "YUV422 onwy suppowts 12 bpc.\n");
			wetuwn fawse;
		}

		dwm_dbg(dev, "YUV422 fowmat suppowted in that configuwation.\n");

		wetuwn twue;

	case VC4_HDMI_OUTPUT_YUV444:
		dwm_dbg(dev, "YUV444 fowmat, checking the constwaints.\n");

		if (!(info->cowow_fowmats & DWM_COWOW_FOWMAT_YCBCW444)) {
			dwm_dbg(dev, "Sink doesn't suppowt YUV444.\n");
			wetuwn fawse;
		}

		if (bpc == 10 && !(info->edid_hdmi_ycbcw444_dc_modes & DWM_EDID_HDMI_DC_30)) {
			dwm_dbg(dev, "10 BPC but sink doesn't suppowt Deep Cowow 30.\n");
			wetuwn fawse;
		}

		if (bpc == 12 && !(info->edid_hdmi_ycbcw444_dc_modes & DWM_EDID_HDMI_DC_36)) {
			dwm_dbg(dev, "12 BPC but sink doesn't suppowt Deep Cowow 36.\n");
			wetuwn fawse;
		}

		dwm_dbg(dev, "YUV444 fowmat suppowted in that configuwation.\n");

		wetuwn twue;
	}

	wetuwn fawse;
}

static enum dwm_mode_status
vc4_hdmi_encodew_cwock_vawid(const stwuct vc4_hdmi *vc4_hdmi,
			     const stwuct dwm_dispway_mode *mode,
			     unsigned wong wong cwock)
{
	const stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	const stwuct dwm_dispway_info *info = &connectow->dispway_info;
	stwuct vc4_dev *vc4 = to_vc4_dev(connectow->dev);

	if (cwock > vc4_hdmi->vawiant->max_pixew_cwock)
		wetuwn MODE_CWOCK_HIGH;

	if (!vc4->hvs->vc5_hdmi_enabwe_hdmi_20 && cwock > HDMI_14_MAX_TMDS_CWK)
		wetuwn MODE_CWOCK_HIGH;

	/* 4096x2160@60 is not wewiabwe without ovewcwocking cowe */
	if (!vc4->hvs->vc5_hdmi_enabwe_4096by2160 &&
	    mode->hdispway > 3840 && mode->vdispway >= 2160 &&
	    dwm_mode_vwefwesh(mode) >= 50)
		wetuwn MODE_CWOCK_HIGH;

	if (info->max_tmds_cwock && cwock > (info->max_tmds_cwock * 1000))
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static unsigned wong wong
vc4_hdmi_encodew_compute_mode_cwock(const stwuct dwm_dispway_mode *mode,
				    unsigned int bpc,
				    enum vc4_hdmi_output_fowmat fmt)
{
	unsigned wong wong cwock = mode->cwock * 1000UWW;

	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		cwock = cwock * 2;

	if (fmt == VC4_HDMI_OUTPUT_YUV422)
		bpc = 8;

	cwock = cwock * bpc;
	do_div(cwock, 8);

	wetuwn cwock;
}

static int
vc4_hdmi_encodew_compute_cwock(const stwuct vc4_hdmi *vc4_hdmi,
			       stwuct vc4_hdmi_connectow_state *vc4_state,
			       const stwuct dwm_dispway_mode *mode,
			       unsigned int bpc, unsigned int fmt)
{
	unsigned wong wong cwock;

	cwock = vc4_hdmi_encodew_compute_mode_cwock(mode, bpc, fmt);
	if (vc4_hdmi_encodew_cwock_vawid(vc4_hdmi, mode, cwock) != MODE_OK)
		wetuwn -EINVAW;

	vc4_state->tmds_chaw_wate = cwock;

	wetuwn 0;
}

static int
vc4_hdmi_encodew_compute_fowmat(const stwuct vc4_hdmi *vc4_hdmi,
				stwuct vc4_hdmi_connectow_state *vc4_state,
				const stwuct dwm_dispway_mode *mode,
				unsigned int bpc)
{
	stwuct dwm_device *dev = vc4_hdmi->connectow.dev;
	const stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	const stwuct dwm_dispway_info *info = &connectow->dispway_info;
	unsigned int fowmat;

	dwm_dbg(dev, "Twying with an WGB output\n");

	fowmat = VC4_HDMI_OUTPUT_WGB;
	if (vc4_hdmi_sink_suppowts_fowmat_bpc(vc4_hdmi, info, mode, fowmat, bpc)) {
		int wet;

		wet = vc4_hdmi_encodew_compute_cwock(vc4_hdmi, vc4_state,
						     mode, bpc, fowmat);
		if (!wet) {
			vc4_state->output_fowmat = fowmat;
			wetuwn 0;
		}
	}

	dwm_dbg(dev, "Faiwed, Twying with an YUV422 output\n");

	fowmat = VC4_HDMI_OUTPUT_YUV422;
	if (vc4_hdmi_sink_suppowts_fowmat_bpc(vc4_hdmi, info, mode, fowmat, bpc)) {
		int wet;

		wet = vc4_hdmi_encodew_compute_cwock(vc4_hdmi, vc4_state,
						     mode, bpc, fowmat);
		if (!wet) {
			vc4_state->output_fowmat = fowmat;
			wetuwn 0;
		}
	}

	dwm_dbg(dev, "Faiwed. No Fowmat Suppowted fow that bpc count.\n");

	wetuwn -EINVAW;
}

static int
vc4_hdmi_encodew_compute_config(const stwuct vc4_hdmi *vc4_hdmi,
				stwuct vc4_hdmi_connectow_state *vc4_state,
				const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = vc4_hdmi->connectow.dev;
	stwuct dwm_connectow_state *conn_state = &vc4_state->base;
	unsigned int max_bpc = cwamp_t(unsigned int, conn_state->max_bpc, 8, 12);
	unsigned int bpc;
	int wet;

	fow (bpc = max_bpc; bpc >= 8; bpc -= 2) {
		dwm_dbg(dev, "Twying with a %d bpc output\n", bpc);

		wet = vc4_hdmi_encodew_compute_fowmat(vc4_hdmi, vc4_state,
						      mode, bpc);
		if (wet)
			continue;

		vc4_state->output_bpc = bpc;

		dwm_dbg(dev,
			"Mode %ux%u @ %uHz: Found configuwation: bpc: %u, fmt: %s, cwock: %wwu\n",
			mode->hdispway, mode->vdispway, dwm_mode_vwefwesh(mode),
			vc4_state->output_bpc,
			vc4_hdmi_output_fmt_stw(vc4_state->output_fowmat),
			vc4_state->tmds_chaw_wate);

		bweak;
	}

	wetuwn wet;
}

#define WIFI_2_4GHz_CH1_MIN_FWEQ	2400000000UWW
#define WIFI_2_4GHz_CH1_MAX_FWEQ	2422000000UWW

static int vc4_hdmi_encodew_atomic_check(stwuct dwm_encodew *encodew,
					 stwuct dwm_cwtc_state *cwtc_state,
					 stwuct dwm_connectow_state *conn_state)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_connectow_state *owd_conn_state =
		dwm_atomic_get_owd_connectow_state(conn_state->state, connectow);
	stwuct vc4_hdmi_connectow_state *owd_vc4_state =
		conn_state_to_vc4_hdmi_conn_state(owd_conn_state);
	stwuct vc4_hdmi_connectow_state *vc4_state = conn_state_to_vc4_hdmi_conn_state(conn_state);
	stwuct dwm_dispway_mode *mode = &cwtc_state->adjusted_mode;
	unsigned wong wong tmds_chaw_wate = mode->cwock * 1000;
	unsigned wong wong tmds_bit_wate;
	int wet;

	if (vc4_hdmi->vawiant->unsuppowted_odd_h_timings) {
		if (mode->fwags & DWM_MODE_FWAG_DBWCWK) {
			/* Onwy twy to fixup DBWCWK modes to get 480i and 576i
			 * wowking.
			 * A genewic sowution fow aww modes with odd howizontaw
			 * timing vawues seems impossibwe based on twying to
			 * sowve it fow 1366x768 monitows.
			 */
			if ((mode->hsync_stawt - mode->hdispway) & 1)
				mode->hsync_stawt--;
			if ((mode->hsync_end - mode->hsync_stawt) & 1)
				mode->hsync_end--;
		}

		/* Now check whethew we stiww have odd vawues wemaining */
		if ((mode->hdispway % 2) || (mode->hsync_stawt % 2) ||
		    (mode->hsync_end % 2) || (mode->htotaw % 2))
			wetuwn -EINVAW;
	}

	/*
	 * The 1440p@60 pixew wate is in the same wange than the fiwst
	 * WiFi channew (between 2.4GHz and 2.422GHz with 22MHz
	 * bandwidth). Swightwy wowew the fwequency to bwing it out of
	 * the WiFi wange.
	 */
	tmds_bit_wate = tmds_chaw_wate * 10;
	if (vc4_hdmi->disabwe_wifi_fwequencies &&
	    (tmds_bit_wate >= WIFI_2_4GHz_CH1_MIN_FWEQ &&
	     tmds_bit_wate <= WIFI_2_4GHz_CH1_MAX_FWEQ)) {
		mode->cwock = 238560;
		tmds_chaw_wate = mode->cwock * 1000;
	}

	wet = vc4_hdmi_encodew_compute_config(vc4_hdmi, vc4_state, mode);
	if (wet)
		wetuwn wet;

	/* vc4_hdmi_encodew_compute_config may have changed output_bpc and/ow output_fowmat */
	if (vc4_state->output_bpc != owd_vc4_state->output_bpc ||
	    vc4_state->output_fowmat != owd_vc4_state->output_fowmat)
		cwtc_state->mode_changed = twue;

	wetuwn 0;
}

static enum dwm_mode_status
vc4_hdmi_encodew_mode_vawid(stwuct dwm_encodew *encodew,
			    const stwuct dwm_dispway_mode *mode)
{
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);

	if (vc4_hdmi->vawiant->unsuppowted_odd_h_timings &&
	    !(mode->fwags & DWM_MODE_FWAG_DBWCWK) &&
	    ((mode->hdispway % 2) || (mode->hsync_stawt % 2) ||
	     (mode->hsync_end % 2) || (mode->htotaw % 2)))
		wetuwn MODE_H_IWWEGAW;

	wetuwn vc4_hdmi_encodew_cwock_vawid(vc4_hdmi, mode, mode->cwock * 1000);
}

static const stwuct dwm_encodew_hewpew_funcs vc4_hdmi_encodew_hewpew_funcs = {
	.atomic_check = vc4_hdmi_encodew_atomic_check,
	.atomic_mode_set = vc4_hdmi_encodew_atomic_mode_set,
	.mode_vawid = vc4_hdmi_encodew_mode_vawid,
};

static int vc4_hdmi_wate_wegistew(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dwm = encodew->dev;
	stwuct vc4_hdmi *vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	const stwuct vc4_hdmi_vawiant *vawiant = vc4_hdmi->vawiant;

	dwm_debugfs_add_fiwe(dwm, vawiant->debugfs_name,
			     vc4_hdmi_debugfs_wegs, vc4_hdmi);

	wetuwn 0;
}

static const stwuct dwm_encodew_funcs vc4_hdmi_encodew_funcs = {
	.wate_wegistew = vc4_hdmi_wate_wegistew,
};

static u32 vc4_hdmi_channew_map(stwuct vc4_hdmi *vc4_hdmi, u32 channew_mask)
{
	int i;
	u32 channew_map = 0;

	fow (i = 0; i < 8; i++) {
		if (channew_mask & BIT(i))
			channew_map |= i << (3 * i);
	}
	wetuwn channew_map;
}

static u32 vc5_hdmi_channew_map(stwuct vc4_hdmi *vc4_hdmi, u32 channew_mask)
{
	int i;
	u32 channew_map = 0;

	fow (i = 0; i < 8; i++) {
		if (channew_mask & BIT(i))
			channew_map |= i << (4 * i);
	}
	wetuwn channew_map;
}

static boow vc5_hdmi_hp_detect(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	u32 hotpwug;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn fawse;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	hotpwug = HDMI_WEAD(HDMI_HOTPWUG);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);

	wetuwn !!(hotpwug & VC4_HDMI_HOTPWUG_CONNECTED);
}

/* HDMI audio codec cawwbacks */
static void vc4_hdmi_audio_set_mai_cwock(stwuct vc4_hdmi *vc4_hdmi,
					 unsigned int sampwewate)
{
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	u32 hsm_cwock;
	unsigned wong fwags;
	unsigned wong n, m;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	hsm_cwock = cwk_get_wate(vc4_hdmi->audio_cwock);
	wationaw_best_appwoximation(hsm_cwock, sampwewate,
				    VC4_HD_MAI_SMP_N_MASK >>
				    VC4_HD_MAI_SMP_N_SHIFT,
				    (VC4_HD_MAI_SMP_M_MASK >>
				     VC4_HD_MAI_SMP_M_SHIFT) + 1,
				    &n, &m);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_MAI_SMP,
		   VC4_SET_FIEWD(n, VC4_HD_MAI_SMP_N) |
		   VC4_SET_FIEWD(m - 1, VC4_HD_MAI_SMP_M));
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	dwm_dev_exit(idx);
}

static void vc4_hdmi_set_n_cts(stwuct vc4_hdmi *vc4_hdmi, unsigned int sampwewate)
{
	const stwuct dwm_dispway_mode *mode = &vc4_hdmi->saved_adjusted_mode;
	u32 n, cts;
	u64 tmp;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);
	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	n = 128 * sampwewate / 1000;
	tmp = (u64)(mode->cwock * 1000) * n;
	do_div(tmp, 128 * sampwewate);
	cts = tmp;

	HDMI_WWITE(HDMI_CWP_CFG,
		   VC4_HDMI_CWP_CFG_EXTEWNAW_CTS_EN |
		   VC4_SET_FIEWD(n, VC4_HDMI_CWP_CFG_N));

	/*
	 * We couwd get swightwy mowe accuwate cwocks in some cases by
	 * pwoviding a CTS_1 vawue.  The two CTS vawues awe awtewnated
	 * between based on the pewiod fiewds
	 */
	HDMI_WWITE(HDMI_CTS_0, cts);
	HDMI_WWITE(HDMI_CTS_1, cts);
}

static inwine stwuct vc4_hdmi *dai_to_hdmi(stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_cawd *cawd = snd_soc_dai_get_dwvdata(dai);

	wetuwn snd_soc_cawd_get_dwvdata(cawd);
}

static boow vc4_hdmi_audio_can_stweam(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_dispway_info *dispway = &vc4_hdmi->connectow.dispway_info;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	/*
	 * If the encodew is cuwwentwy in DVI mode, tweat the codec DAI
	 * as missing.
	 */
	if (!dispway->is_hdmi)
		wetuwn fawse;

	wetuwn twue;
}

static int vc4_hdmi_audio_stawtup(stwuct device *dev, void *data)
{
	stwuct vc4_hdmi *vc4_hdmi = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int wet = 0;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx)) {
		wet = -ENODEV;
		goto out;
	}

	if (!vc4_hdmi_audio_can_stweam(vc4_hdmi)) {
		wet = -ENODEV;
		goto out_dev_exit;
	}

	vc4_hdmi->audio.stweaming = twue;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_MAI_CTW,
		   VC4_HD_MAI_CTW_WESET |
		   VC4_HD_MAI_CTW_FWUSH |
		   VC4_HD_MAI_CTW_DWATE |
		   VC4_HD_MAI_CTW_EWWOWE |
		   VC4_HD_MAI_CTW_EWWOWF);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (vc4_hdmi->vawiant->phy_wng_enabwe)
		vc4_hdmi->vawiant->phy_wng_enabwe(vc4_hdmi);

out_dev_exit:
	dwm_dev_exit(idx);
out:
	mutex_unwock(&vc4_hdmi->mutex);

	wetuwn wet;
}

static void vc4_hdmi_audio_weset(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_encodew *encodew = &vc4_hdmi->encodew.base;
	stwuct device *dev = &vc4_hdmi->pdev->dev;
	unsigned wong fwags;
	int wet;

	wockdep_assewt_hewd(&vc4_hdmi->mutex);

	vc4_hdmi->audio.stweaming = fawse;
	wet = vc4_hdmi_stop_packet(encodew, HDMI_INFOFWAME_TYPE_AUDIO, fawse);
	if (wet)
		dev_eww(dev, "Faiwed to stop audio infofwame: %d\n", wet);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_MAI_CTW, VC4_HD_MAI_CTW_WESET);
	HDMI_WWITE(HDMI_MAI_CTW, VC4_HD_MAI_CTW_EWWOWF);
	HDMI_WWITE(HDMI_MAI_CTW, VC4_HD_MAI_CTW_FWUSH);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

static void vc4_hdmi_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct vc4_hdmi *vc4_hdmi = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int idx;

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx))
		goto out;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_MAI_CTW,
		   VC4_HD_MAI_CTW_DWATE |
		   VC4_HD_MAI_CTW_EWWOWE |
		   VC4_HD_MAI_CTW_EWWOWF);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	if (vc4_hdmi->vawiant->phy_wng_disabwe)
		vc4_hdmi->vawiant->phy_wng_disabwe(vc4_hdmi);

	vc4_hdmi->audio.stweaming = fawse;
	vc4_hdmi_audio_weset(vc4_hdmi);

	dwm_dev_exit(idx);

out:
	mutex_unwock(&vc4_hdmi->mutex);
}

static int sampwe_wate_to_mai_fmt(int sampwewate)
{
	switch (sampwewate) {
	case 8000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_8000;
	case 11025:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_11025;
	case 12000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_12000;
	case 16000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_16000;
	case 22050:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_22050;
	case 24000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_24000;
	case 32000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_32000;
	case 44100:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_44100;
	case 48000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_48000;
	case 64000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_64000;
	case 88200:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_88200;
	case 96000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_96000;
	case 128000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_128000;
	case 176400:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_176400;
	case 192000:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_192000;
	defauwt:
		wetuwn VC4_HDMI_MAI_SAMPWE_WATE_NOT_INDICATED;
	}
}

/* HDMI audio codec cawwbacks */
static int vc4_hdmi_audio_pwepawe(stwuct device *dev, void *data,
				  stwuct hdmi_codec_daifmt *daifmt,
				  stwuct hdmi_codec_pawams *pawams)
{
	stwuct vc4_hdmi *vc4_hdmi = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	stwuct dwm_encodew *encodew = &vc4_hdmi->encodew.base;
	unsigned int sampwe_wate = pawams->sampwe_wate;
	unsigned int channews = pawams->channews;
	unsigned wong fwags;
	u32 audio_packet_config, channew_mask;
	u32 channew_map;
	u32 mai_audio_fowmat;
	u32 mai_sampwe_wate;
	int wet = 0;
	int idx;

	dev_dbg(dev, "%s: %u Hz, %d bit, %d channews\n", __func__,
		sampwe_wate, pawams->sampwe_width, channews);

	mutex_wock(&vc4_hdmi->mutex);

	if (!dwm_dev_entew(dwm, &idx)) {
		wet = -ENODEV;
		goto out;
	}

	if (!vc4_hdmi_audio_can_stweam(vc4_hdmi)) {
		wet = -EINVAW;
		goto out_dev_exit;
	}

	vc4_hdmi_audio_set_mai_cwock(vc4_hdmi, sampwe_wate);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_MAI_CTW,
		   VC4_SET_FIEWD(channews, VC4_HD_MAI_CTW_CHNUM) |
		   VC4_HD_MAI_CTW_WHOWSMP |
		   VC4_HD_MAI_CTW_CHAWIGN |
		   VC4_HD_MAI_CTW_ENABWE);

	mai_sampwe_wate = sampwe_wate_to_mai_fmt(sampwe_wate);
	if (pawams->iec.status[0] & IEC958_AES0_NONAUDIO &&
	    pawams->channews == 8)
		mai_audio_fowmat = VC4_HDMI_MAI_FOWMAT_HBW;
	ewse
		mai_audio_fowmat = VC4_HDMI_MAI_FOWMAT_PCM;
	HDMI_WWITE(HDMI_MAI_FMT,
		   VC4_SET_FIEWD(mai_sampwe_wate,
				 VC4_HDMI_MAI_FOWMAT_SAMPWE_WATE) |
		   VC4_SET_FIEWD(mai_audio_fowmat,
				 VC4_HDMI_MAI_FOWMAT_AUDIO_FOWMAT));

	/* The B fwame identifiew shouwd match the vawue used by awsa-wib (8) */
	audio_packet_config =
		VC4_HDMI_AUDIO_PACKET_ZEWO_DATA_ON_SAMPWE_FWAT |
		VC4_HDMI_AUDIO_PACKET_ZEWO_DATA_ON_INACTIVE_CHANNEWS |
		VC4_SET_FIEWD(0x8, VC4_HDMI_AUDIO_PACKET_B_FWAME_IDENTIFIEW);

	channew_mask = GENMASK(channews - 1, 0);
	audio_packet_config |= VC4_SET_FIEWD(channew_mask,
					     VC4_HDMI_AUDIO_PACKET_CEA_MASK);

	/* Set the MAI thweshowd */
	HDMI_WWITE(HDMI_MAI_THW,
		   VC4_SET_FIEWD(0x08, VC4_HD_MAI_THW_PANICHIGH) |
		   VC4_SET_FIEWD(0x08, VC4_HD_MAI_THW_PANICWOW) |
		   VC4_SET_FIEWD(0x06, VC4_HD_MAI_THW_DWEQHIGH) |
		   VC4_SET_FIEWD(0x08, VC4_HD_MAI_THW_DWEQWOW));

	HDMI_WWITE(HDMI_MAI_CONFIG,
		   VC4_HDMI_MAI_CONFIG_BIT_WEVEWSE |
		   VC4_HDMI_MAI_CONFIG_FOWMAT_WEVEWSE |
		   VC4_SET_FIEWD(channew_mask, VC4_HDMI_MAI_CHANNEW_MASK));

	channew_map = vc4_hdmi->vawiant->channew_map(vc4_hdmi, channew_mask);
	HDMI_WWITE(HDMI_MAI_CHANNEW_MAP, channew_map);
	HDMI_WWITE(HDMI_AUDIO_PACKET_CONFIG, audio_packet_config);

	vc4_hdmi_set_n_cts(vc4_hdmi, sampwe_wate);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	memcpy(&vc4_hdmi->audio.infofwame, &pawams->cea, sizeof(pawams->cea));
	vc4_hdmi_set_audio_infofwame(encodew);

out_dev_exit:
	dwm_dev_exit(idx);
out:
	mutex_unwock(&vc4_hdmi->mutex);

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew vc4_hdmi_audio_cpu_dai_comp = {
	.name = "vc4-hdmi-cpu-dai-component",
	.wegacy_dai_naming = 1,
};

static int vc4_hdmi_audio_cpu_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct vc4_hdmi *vc4_hdmi = dai_to_hdmi(dai);

	snd_soc_dai_init_dma_data(dai, &vc4_hdmi->audio.dma_data, NUWW);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops vc4_snd_dai_ops = {
	.pwobe  = vc4_hdmi_audio_cpu_dai_pwobe,
};

static stwuct snd_soc_dai_dwivew vc4_hdmi_audio_cpu_dai_dwv = {
	.name = "vc4-hdmi-cpu-dai",
	.ops = &vc4_snd_dai_ops,
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
			 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |
			 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |
			 SNDWV_PCM_WATE_192000,
		.fowmats = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE,
	},
};

static const stwuct snd_dmaengine_pcm_config pcm_conf = {
	.chan_names[SNDWV_PCM_STWEAM_PWAYBACK] = "audio-wx",
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
};

static int vc4_hdmi_audio_get_ewd(stwuct device *dev, void *data,
				  uint8_t *buf, size_t wen)
{
	stwuct vc4_hdmi *vc4_hdmi = dev_get_dwvdata(dev);
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;

	mutex_wock(&vc4_hdmi->mutex);
	memcpy(buf, connectow->ewd, min(sizeof(connectow->ewd), wen));
	mutex_unwock(&vc4_hdmi->mutex);

	wetuwn 0;
}

static const stwuct hdmi_codec_ops vc4_hdmi_codec_ops = {
	.get_ewd = vc4_hdmi_audio_get_ewd,
	.pwepawe = vc4_hdmi_audio_pwepawe,
	.audio_shutdown = vc4_hdmi_audio_shutdown,
	.audio_stawtup = vc4_hdmi_audio_stawtup,
};

static stwuct hdmi_codec_pdata vc4_hdmi_codec_pdata = {
	.ops = &vc4_hdmi_codec_ops,
	.max_i2s_channews = 8,
	.i2s = 1,
};

static void vc4_hdmi_audio_codec_wewease(void *ptw)
{
	stwuct vc4_hdmi *vc4_hdmi = ptw;

	pwatfowm_device_unwegistew(vc4_hdmi->audio.codec_pdev);
	vc4_hdmi->audio.codec_pdev = NUWW;
}

static int vc4_hdmi_audio_init(stwuct vc4_hdmi *vc4_hdmi)
{
	const stwuct vc4_hdmi_wegistew *mai_data =
		&vc4_hdmi->vawiant->wegistews[HDMI_MAI_DATA];
	stwuct snd_soc_dai_wink *dai_wink = &vc4_hdmi->audio.wink;
	stwuct snd_soc_cawd *cawd = &vc4_hdmi->audio.cawd;
	stwuct device *dev = &vc4_hdmi->pdev->dev;
	stwuct pwatfowm_device *codec_pdev;
	const __be32 *addw;
	int index, wen;
	int wet;

	/*
	 * ASoC makes it a bit hawd to wetwieve a pointew to the
	 * vc4_hdmi stwuctuwe. Wegistewing the cawd wiww ovewwwite ouw
	 * device dwvdata with a pointew to the snd_soc_cawd stwuctuwe,
	 * which can then be used to wetwieve whatevew dwvdata we want
	 * to associate.
	 *
	 * Howevew, that doesn't fwy in the case whewe we wouwdn't
	 * wegistew an ASoC cawd (because of an owd DT that is missing
	 * the dmas pwopewties fow exampwe), then the cawd isn't
	 * wegistewed and the device dwvdata wouwdn't be set.
	 *
	 * We can deaw with both cases by making suwe a snd_soc_cawd
	 * pointew and a vc4_hdmi stwuctuwe awe pointing to the same
	 * memowy addwess, so we can tweat them indistinctwy without any
	 * issue.
	 */
	BUIWD_BUG_ON(offsetof(stwuct vc4_hdmi_audio, cawd) != 0);
	BUIWD_BUG_ON(offsetof(stwuct vc4_hdmi, audio) != 0);

	if (!of_find_pwopewty(dev->of_node, "dmas", &wen) || !wen) {
		dev_wawn(dev,
			 "'dmas' DT pwopewty is missing ow empty, no HDMI audio\n");
		wetuwn 0;
	}

	if (mai_data->weg != VC4_HD) {
		WAWN_ONCE(twue, "MAI isn't in the HD bwock\n");
		wetuwn -EINVAW;
	}

	/*
	 * Get the physicaw addwess of VC4_HD_MAI_DATA. We need to wetwieve
	 * the bus addwess specified in the DT, because the physicaw addwess
	 * (the one wetuwned by pwatfowm_get_wesouwce()) is not appwopwiate
	 * fow DMA twansfews.
	 * This VC/MMU shouwd pwobabwy be exposed to avoid this kind of hacks.
	 */
	index = of_pwopewty_match_stwing(dev->of_node, "weg-names", "hd");
	/* Befowe BCM2711, we don't have a named wegistew wange */
	if (index < 0)
		index = 1;

	addw = of_get_addwess(dev->of_node, index, NUWW, NUWW);

	vc4_hdmi->audio.dma_data.addw = be32_to_cpup(addw) + mai_data->offset;
	vc4_hdmi->audio.dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	vc4_hdmi->audio.dma_data.maxbuwst = 2;

	/*
	 * NOTE: Stwictwy speaking, we shouwd pwobabwy use a DWM-managed
	 * wegistwation thewe to avoid wemoving aww the audio components
	 * by the time the dwivew doesn't have any usew anymowe.
	 *
	 * Howevew, the ASoC cowe uses a numbew of devm_kzawwoc cawws
	 * when wegistewing, even when using non-device-managed
	 * functions (such as in snd_soc_wegistew_component()).
	 *
	 * If we caww snd_soc_unwegistew_component() in a DWM-managed
	 * action, the device-managed actions have awweady been executed
	 * and thus we wouwd access memowy that has been fweed.
	 *
	 * Using device-managed hooks hewe pwobabwy weaves us open to a
	 * bunch of issues if usewspace stiww has a handwe on the AWSA
	 * device when the device is wemoved. Howevew, this is mitigated
	 * by the use of dwm_dev_entew()/dwm_dev_exit() in the audio
	 * path to pwevent the access to the device wesouwces if it
	 * isn't thewe anymowe.
	 *
	 * Then, the vc4_hdmi stwuctuwe is DWM-managed and thus onwy
	 * fweed whenevew the wast usew has cwosed the DWM device fiwe.
	 * It shouwd thus outwive AWSA in most situations.
	 */
	wet = devm_snd_dmaengine_pcm_wegistew(dev, &pcm_conf, 0);
	if (wet) {
		dev_eww(dev, "Couwd not wegistew PCM component: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(dev, &vc4_hdmi_audio_cpu_dai_comp,
					      &vc4_hdmi_audio_cpu_dai_dwv, 1);
	if (wet) {
		dev_eww(dev, "Couwd not wegistew CPU DAI: %d\n", wet);
		wetuwn wet;
	}

	codec_pdev = pwatfowm_device_wegistew_data(dev, HDMI_CODEC_DWV_NAME,
						   PWATFOWM_DEVID_AUTO,
						   &vc4_hdmi_codec_pdata,
						   sizeof(vc4_hdmi_codec_pdata));
	if (IS_EWW(codec_pdev)) {
		dev_eww(dev, "Couwdn't wegistew the HDMI codec: %wd\n", PTW_EWW(codec_pdev));
		wetuwn PTW_EWW(codec_pdev);
	}
	vc4_hdmi->audio.codec_pdev = codec_pdev;

	wet = devm_add_action_ow_weset(dev, vc4_hdmi_audio_codec_wewease, vc4_hdmi);
	if (wet)
		wetuwn wet;

	dai_wink->cpus		= &vc4_hdmi->audio.cpu;
	dai_wink->codecs	= &vc4_hdmi->audio.codec;
	dai_wink->pwatfowms	= &vc4_hdmi->audio.pwatfowm;

	dai_wink->num_cpus	= 1;
	dai_wink->num_codecs	= 1;
	dai_wink->num_pwatfowms	= 1;

	dai_wink->name = "MAI";
	dai_wink->stweam_name = "MAI PCM";
	dai_wink->codecs->dai_name = "i2s-hifi";
	dai_wink->cpus->dai_name = dev_name(dev);
	dai_wink->codecs->name = dev_name(&codec_pdev->dev);
	dai_wink->pwatfowms->name = dev_name(dev);

	cawd->dai_wink = dai_wink;
	cawd->num_winks = 1;
	cawd->name = vc4_hdmi->vawiant->cawd_name;
	cawd->dwivew_name = "vc4-hdmi";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;

	/*
	 * Be cawefuw, snd_soc_wegistew_cawd() cawws dev_set_dwvdata() and
	 * stowes a pointew to the snd cawd object in dev->dwivew_data. This
	 * means we cannot use it fow something ewse. The hdmi back-pointew is
	 * now stowed in cawd->dwvdata and shouwd be wetwieved with
	 * snd_soc_cawd_get_dwvdata() if needed.
	 */
	snd_soc_cawd_set_dwvdata(cawd, vc4_hdmi);
	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet)
		dev_eww_pwobe(dev, wet, "Couwd not wegistew sound cawd\n");

	wetuwn wet;

}

static iwqwetuwn_t vc4_hdmi_hpd_iwq_thwead(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct dwm_device *dev = connectow->dev;

	if (dev && dev->wegistewed)
		dwm_connectow_hewpew_hpd_iwq_event(connectow);

	wetuwn IWQ_HANDWED;
}

static int vc4_hdmi_hotpwug_init(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct dwm_connectow *connectow = &vc4_hdmi->connectow;
	stwuct pwatfowm_device *pdev = vc4_hdmi->pdev;
	int wet;

	if (vc4_hdmi->vawiant->extewnaw_iwq_contwowwew) {
		unsigned int hpd_con = pwatfowm_get_iwq_byname(pdev, "hpd-connected");
		unsigned int hpd_wm = pwatfowm_get_iwq_byname(pdev, "hpd-wemoved");

		wet = devm_wequest_thweaded_iwq(&pdev->dev, hpd_con,
						NUWW,
						vc4_hdmi_hpd_iwq_thwead, IWQF_ONESHOT,
						"vc4 hdmi hpd connected", vc4_hdmi);
		if (wet)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(&pdev->dev, hpd_wm,
						NUWW,
						vc4_hdmi_hpd_iwq_thwead, IWQF_ONESHOT,
						"vc4 hdmi hpd disconnected", vc4_hdmi);
		if (wet)
			wetuwn wet;

		connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	}

	wetuwn 0;
}

#ifdef CONFIG_DWM_VC4_HDMI_CEC
static iwqwetuwn_t vc4_cec_iwq_handwew_wx_thwead(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;

	if (vc4_hdmi->cec_wx_msg.wen)
		cec_weceived_msg(vc4_hdmi->cec_adap,
				 &vc4_hdmi->cec_wx_msg);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t vc4_cec_iwq_handwew_tx_thwead(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;

	if (vc4_hdmi->cec_tx_ok) {
		cec_twansmit_done(vc4_hdmi->cec_adap, CEC_TX_STATUS_OK,
				  0, 0, 0, 0);
	} ewse {
		/*
		 * This CEC impwementation makes 1 wetwy, so if we
		 * get a NACK, then that means it made 2 attempts.
		 */
		cec_twansmit_done(vc4_hdmi->cec_adap, CEC_TX_STATUS_NACK,
				  0, 2, 0, 0);
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t vc4_cec_iwq_handwew_thwead(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;
	iwqwetuwn_t wet;

	if (vc4_hdmi->cec_iwq_was_wx)
		wet = vc4_cec_iwq_handwew_wx_thwead(iwq, pwiv);
	ewse
		wet = vc4_cec_iwq_handwew_tx_thwead(iwq, pwiv);

	wetuwn wet;
}

static void vc4_cec_wead_msg(stwuct vc4_hdmi *vc4_hdmi, u32 cntww1)
{
	stwuct dwm_device *dev = vc4_hdmi->connectow.dev;
	stwuct cec_msg *msg = &vc4_hdmi->cec_wx_msg;
	unsigned int i;

	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	msg->wen = 1 + ((cntww1 & VC4_HDMI_CEC_WEC_WWD_CNT_MASK) >>
					VC4_HDMI_CEC_WEC_WWD_CNT_SHIFT);

	if (msg->wen > 16) {
		dwm_eww(dev, "Attempting to wead too much data (%d)\n", msg->wen);
		wetuwn;
	}

	fow (i = 0; i < msg->wen; i += 4) {
		u32 vaw = HDMI_WEAD(HDMI_CEC_WX_DATA_1 + (i >> 2));

		msg->msg[i] = vaw & 0xff;
		msg->msg[i + 1] = (vaw >> 8) & 0xff;
		msg->msg[i + 2] = (vaw >> 16) & 0xff;
		msg->msg[i + 3] = (vaw >> 24) & 0xff;
	}
}

static iwqwetuwn_t vc4_cec_iwq_handwew_tx_bawe_wocked(stwuct vc4_hdmi *vc4_hdmi)
{
	u32 cntww1;

	/*
	 * We don't need to pwotect the wegistew access using
	 * dwm_dev_entew() thewe because the intewwupt handwew wifetime
	 * is tied to the device itsewf, and not to the DWM device.
	 *
	 * So when the device wiww be gone, one of the fiwst thing we
	 * wiww be doing wiww be to unwegistew the intewwupt handwew,
	 * and then unwegistew the DWM device. dwm_dev_entew() wouwd
	 * thus awways succeed if we awe hewe.
	 */

	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	cntww1 = HDMI_WEAD(HDMI_CEC_CNTWW_1);
	vc4_hdmi->cec_tx_ok = cntww1 & VC4_HDMI_CEC_TX_STATUS_GOOD;
	cntww1 &= ~VC4_HDMI_CEC_STAWT_XMIT_BEGIN;
	HDMI_WWITE(HDMI_CEC_CNTWW_1, cntww1);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t vc4_cec_iwq_handwew_tx_bawe(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;
	iwqwetuwn_t wet;

	spin_wock(&vc4_hdmi->hw_wock);
	wet = vc4_cec_iwq_handwew_tx_bawe_wocked(vc4_hdmi);
	spin_unwock(&vc4_hdmi->hw_wock);

	wetuwn wet;
}

static iwqwetuwn_t vc4_cec_iwq_handwew_wx_bawe_wocked(stwuct vc4_hdmi *vc4_hdmi)
{
	u32 cntww1;

	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	/*
	 * We don't need to pwotect the wegistew access using
	 * dwm_dev_entew() thewe because the intewwupt handwew wifetime
	 * is tied to the device itsewf, and not to the DWM device.
	 *
	 * So when the device wiww be gone, one of the fiwst thing we
	 * wiww be doing wiww be to unwegistew the intewwupt handwew,
	 * and then unwegistew the DWM device. dwm_dev_entew() wouwd
	 * thus awways succeed if we awe hewe.
	 */

	vc4_hdmi->cec_wx_msg.wen = 0;
	cntww1 = HDMI_WEAD(HDMI_CEC_CNTWW_1);
	vc4_cec_wead_msg(vc4_hdmi, cntww1);
	cntww1 |= VC4_HDMI_CEC_CWEAW_WECEIVE_OFF;
	HDMI_WWITE(HDMI_CEC_CNTWW_1, cntww1);
	cntww1 &= ~VC4_HDMI_CEC_CWEAW_WECEIVE_OFF;

	HDMI_WWITE(HDMI_CEC_CNTWW_1, cntww1);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t vc4_cec_iwq_handwew_wx_bawe(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;
	iwqwetuwn_t wet;

	spin_wock(&vc4_hdmi->hw_wock);
	wet = vc4_cec_iwq_handwew_wx_bawe_wocked(vc4_hdmi);
	spin_unwock(&vc4_hdmi->hw_wock);

	wetuwn wet;
}

static iwqwetuwn_t vc4_cec_iwq_handwew(int iwq, void *pwiv)
{
	stwuct vc4_hdmi *vc4_hdmi = pwiv;
	u32 stat = HDMI_WEAD(HDMI_CEC_CPU_STATUS);
	iwqwetuwn_t wet;
	u32 cntww5;

	/*
	 * We don't need to pwotect the wegistew access using
	 * dwm_dev_entew() thewe because the intewwupt handwew wifetime
	 * is tied to the device itsewf, and not to the DWM device.
	 *
	 * So when the device wiww be gone, one of the fiwst thing we
	 * wiww be doing wiww be to unwegistew the intewwupt handwew,
	 * and then unwegistew the DWM device. dwm_dev_entew() wouwd
	 * thus awways succeed if we awe hewe.
	 */

	if (!(stat & VC4_HDMI_CPU_CEC))
		wetuwn IWQ_NONE;

	spin_wock(&vc4_hdmi->hw_wock);
	cntww5 = HDMI_WEAD(HDMI_CEC_CNTWW_5);
	vc4_hdmi->cec_iwq_was_wx = cntww5 & VC4_HDMI_CEC_WX_CEC_INT;
	if (vc4_hdmi->cec_iwq_was_wx)
		wet = vc4_cec_iwq_handwew_wx_bawe_wocked(vc4_hdmi);
	ewse
		wet = vc4_cec_iwq_handwew_tx_bawe_wocked(vc4_hdmi);

	HDMI_WWITE(HDMI_CEC_CPU_CWEAW, VC4_HDMI_CPU_CEC);
	spin_unwock(&vc4_hdmi->hw_wock);

	wetuwn wet;
}

static int vc4_hdmi_cec_enabwe(stwuct cec_adaptew *adap)
{
	stwuct vc4_hdmi *vc4_hdmi = cec_get_dwvdata(adap);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	/* cwock pewiod in micwoseconds */
	const u32 usecs = 1000000 / CEC_CWOCK_FWEQ;
	unsigned wong fwags;
	u32 vaw;
	int wet;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		/*
		 * We can't wetuwn an ewwow code, because the CEC
		 * fwamewowk wiww emit WAWN_ON messages at unbind
		 * othewwise.
		 */
		wetuwn 0;

	wet = pm_wuntime_wesume_and_get(&vc4_hdmi->pdev->dev);
	if (wet) {
		dwm_dev_exit(idx);
		wetuwn wet;
	}

	mutex_wock(&vc4_hdmi->mutex);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	vaw = HDMI_WEAD(HDMI_CEC_CNTWW_5);
	vaw &= ~(VC4_HDMI_CEC_TX_SW_WESET | VC4_HDMI_CEC_WX_SW_WESET |
		 VC4_HDMI_CEC_CNT_TO_4700_US_MASK |
		 VC4_HDMI_CEC_CNT_TO_4500_US_MASK);
	vaw |= ((4700 / usecs) << VC4_HDMI_CEC_CNT_TO_4700_US_SHIFT) |
	       ((4500 / usecs) << VC4_HDMI_CEC_CNT_TO_4500_US_SHIFT);

	HDMI_WWITE(HDMI_CEC_CNTWW_5, vaw |
		   VC4_HDMI_CEC_TX_SW_WESET | VC4_HDMI_CEC_WX_SW_WESET);
	HDMI_WWITE(HDMI_CEC_CNTWW_5, vaw);
	HDMI_WWITE(HDMI_CEC_CNTWW_2,
		   ((1500 / usecs) << VC4_HDMI_CEC_CNT_TO_1500_US_SHIFT) |
		   ((1300 / usecs) << VC4_HDMI_CEC_CNT_TO_1300_US_SHIFT) |
		   ((800 / usecs) << VC4_HDMI_CEC_CNT_TO_800_US_SHIFT) |
		   ((600 / usecs) << VC4_HDMI_CEC_CNT_TO_600_US_SHIFT) |
		   ((400 / usecs) << VC4_HDMI_CEC_CNT_TO_400_US_SHIFT));
	HDMI_WWITE(HDMI_CEC_CNTWW_3,
		   ((2750 / usecs) << VC4_HDMI_CEC_CNT_TO_2750_US_SHIFT) |
		   ((2400 / usecs) << VC4_HDMI_CEC_CNT_TO_2400_US_SHIFT) |
		   ((2050 / usecs) << VC4_HDMI_CEC_CNT_TO_2050_US_SHIFT) |
		   ((1700 / usecs) << VC4_HDMI_CEC_CNT_TO_1700_US_SHIFT));
	HDMI_WWITE(HDMI_CEC_CNTWW_4,
		   ((4300 / usecs) << VC4_HDMI_CEC_CNT_TO_4300_US_SHIFT) |
		   ((3900 / usecs) << VC4_HDMI_CEC_CNT_TO_3900_US_SHIFT) |
		   ((3600 / usecs) << VC4_HDMI_CEC_CNT_TO_3600_US_SHIFT) |
		   ((3500 / usecs) << VC4_HDMI_CEC_CNT_TO_3500_US_SHIFT));

	if (!vc4_hdmi->vawiant->extewnaw_iwq_contwowwew)
		HDMI_WWITE(HDMI_CEC_CPU_MASK_CWEAW, VC4_HDMI_CPU_CEC);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	mutex_unwock(&vc4_hdmi->mutex);
	dwm_dev_exit(idx);

	wetuwn 0;
}

static int vc4_hdmi_cec_disabwe(stwuct cec_adaptew *adap)
{
	stwuct vc4_hdmi *vc4_hdmi = cec_get_dwvdata(adap);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		/*
		 * We can't wetuwn an ewwow code, because the CEC
		 * fwamewowk wiww emit WAWN_ON messages at unbind
		 * othewwise.
		 */
		wetuwn 0;

	mutex_wock(&vc4_hdmi->mutex);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	if (!vc4_hdmi->vawiant->extewnaw_iwq_contwowwew)
		HDMI_WWITE(HDMI_CEC_CPU_MASK_SET, VC4_HDMI_CPU_CEC);

	HDMI_WWITE(HDMI_CEC_CNTWW_5, HDMI_WEAD(HDMI_CEC_CNTWW_5) |
		   VC4_HDMI_CEC_TX_SW_WESET | VC4_HDMI_CEC_WX_SW_WESET);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	mutex_unwock(&vc4_hdmi->mutex);

	pm_wuntime_put(&vc4_hdmi->pdev->dev);

	dwm_dev_exit(idx);

	wetuwn 0;
}

static int vc4_hdmi_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	if (enabwe)
		wetuwn vc4_hdmi_cec_enabwe(adap);
	ewse
		wetuwn vc4_hdmi_cec_disabwe(adap);
}

static int vc4_hdmi_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wog_addw)
{
	stwuct vc4_hdmi *vc4_hdmi = cec_get_dwvdata(adap);
	stwuct dwm_device *dwm = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		/*
		 * We can't wetuwn an ewwow code, because the CEC
		 * fwamewowk wiww emit WAWN_ON messages at unbind
		 * othewwise.
		 */
		wetuwn 0;

	mutex_wock(&vc4_hdmi->mutex);
	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_CEC_CNTWW_1,
		   (HDMI_WEAD(HDMI_CEC_CNTWW_1) & ~VC4_HDMI_CEC_ADDW_MASK) |
		   (wog_addw & 0xf) << VC4_HDMI_CEC_ADDW_SHIFT);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
	mutex_unwock(&vc4_hdmi->mutex);

	dwm_dev_exit(idx);

	wetuwn 0;
}

static int vc4_hdmi_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				      u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct vc4_hdmi *vc4_hdmi = cec_get_dwvdata(adap);
	stwuct dwm_device *dev = vc4_hdmi->connectow.dev;
	unsigned wong fwags;
	u32 vaw;
	unsigned int i;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn -ENODEV;

	if (msg->wen > 16) {
		dwm_eww(dev, "Attempting to twansmit too much data (%d)\n", msg->wen);
		dwm_dev_exit(idx);
		wetuwn -ENOMEM;
	}

	mutex_wock(&vc4_hdmi->mutex);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	fow (i = 0; i < msg->wen; i += 4)
		HDMI_WWITE(HDMI_CEC_TX_DATA_1 + (i >> 2),
			   (msg->msg[i]) |
			   (msg->msg[i + 1] << 8) |
			   (msg->msg[i + 2] << 16) |
			   (msg->msg[i + 3] << 24));

	vaw = HDMI_WEAD(HDMI_CEC_CNTWW_1);
	vaw &= ~VC4_HDMI_CEC_STAWT_XMIT_BEGIN;
	HDMI_WWITE(HDMI_CEC_CNTWW_1, vaw);
	vaw &= ~VC4_HDMI_CEC_MESSAGE_WENGTH_MASK;
	vaw |= (msg->wen - 1) << VC4_HDMI_CEC_MESSAGE_WENGTH_SHIFT;
	vaw |= VC4_HDMI_CEC_STAWT_XMIT_BEGIN;

	HDMI_WWITE(HDMI_CEC_CNTWW_1, vaw);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
	mutex_unwock(&vc4_hdmi->mutex);
	dwm_dev_exit(idx);

	wetuwn 0;
}

static const stwuct cec_adap_ops vc4_hdmi_cec_adap_ops = {
	.adap_enabwe = vc4_hdmi_cec_adap_enabwe,
	.adap_wog_addw = vc4_hdmi_cec_adap_wog_addw,
	.adap_twansmit = vc4_hdmi_cec_adap_twansmit,
};

static void vc4_hdmi_cec_wewease(void *ptw)
{
	stwuct vc4_hdmi *vc4_hdmi = ptw;

	cec_unwegistew_adaptew(vc4_hdmi->cec_adap);
	vc4_hdmi->cec_adap = NUWW;
}

static int vc4_hdmi_cec_init(stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct cec_connectow_info conn_info;
	stwuct pwatfowm_device *pdev = vc4_hdmi->pdev;
	stwuct device *dev = &pdev->dev;
	int wet;

	if (!of_pwopewty_pwesent(dev->of_node, "intewwupts")) {
		dev_wawn(dev, "'intewwupts' DT pwopewty is missing, no CEC\n");
		wetuwn 0;
	}

	vc4_hdmi->cec_adap = cec_awwocate_adaptew(&vc4_hdmi_cec_adap_ops,
						  vc4_hdmi,
						  vc4_hdmi->vawiant->cawd_name,
						  CEC_CAP_DEFAUWTS |
						  CEC_CAP_CONNECTOW_INFO, 1);
	wet = PTW_EWW_OW_ZEWO(vc4_hdmi->cec_adap);
	if (wet < 0)
		wetuwn wet;

	cec_fiww_conn_info_fwom_dwm(&conn_info, &vc4_hdmi->connectow);
	cec_s_conn_info(vc4_hdmi->cec_adap, &conn_info);

	if (vc4_hdmi->vawiant->extewnaw_iwq_contwowwew) {
		wet = devm_wequest_thweaded_iwq(dev, pwatfowm_get_iwq_byname(pdev, "cec-wx"),
						vc4_cec_iwq_handwew_wx_bawe,
						vc4_cec_iwq_handwew_wx_thwead, 0,
						"vc4 hdmi cec wx", vc4_hdmi);
		if (wet)
			goto eww_dewete_cec_adap;

		wet = devm_wequest_thweaded_iwq(dev, pwatfowm_get_iwq_byname(pdev, "cec-tx"),
						vc4_cec_iwq_handwew_tx_bawe,
						vc4_cec_iwq_handwew_tx_thwead, 0,
						"vc4 hdmi cec tx", vc4_hdmi);
		if (wet)
			goto eww_dewete_cec_adap;
	} ewse {
		wet = devm_wequest_thweaded_iwq(dev, pwatfowm_get_iwq(pdev, 0),
						vc4_cec_iwq_handwew,
						vc4_cec_iwq_handwew_thwead, 0,
						"vc4 hdmi cec", vc4_hdmi);
		if (wet)
			goto eww_dewete_cec_adap;
	}

	wet = cec_wegistew_adaptew(vc4_hdmi->cec_adap, &pdev->dev);
	if (wet < 0)
		goto eww_dewete_cec_adap;

	/*
	 * NOTE: Stwictwy speaking, we shouwd pwobabwy use a DWM-managed
	 * wegistwation thewe to avoid wemoving the CEC adaptew by the
	 * time the DWM dwivew doesn't have any usew anymowe.
	 *
	 * Howevew, the CEC fwamewowk awweady cweans up the CEC adaptew
	 * onwy when the wast usew has cwosed its fiwe descwiptow, so we
	 * don't need to handwe it in DWM.
	 *
	 * By the time the device-managed hook is executed, we wiww give
	 * up ouw wefewence to the CEC adaptew and thewefowe don't
	 * weawwy cawe when it's actuawwy fweed.
	 *
	 * Thewe's stiww a pwobwematic sequence: if we unwegistew ouw
	 * CEC adaptew, but the usewspace keeps a handwe on the CEC
	 * adaptew but not the DWM device fow some weason. In such a
	 * case, ouw vc4_hdmi stwuctuwe wiww be fweed, but the
	 * cec_adaptew stwuctuwe wiww have a dangwing pointew to what
	 * used to be ouw HDMI contwowwew. If we get a CEC caww at that
	 * moment, we couwd end up with a use-aftew-fwee. Fowtunatewy,
	 * the CEC fwamewowk awweady handwes this too, by cawwing
	 * cec_is_wegistewed() in cec_ioctw() and cec_poww().
	 */
	wet = devm_add_action_ow_weset(dev, vc4_hdmi_cec_wewease, vc4_hdmi);
	if (wet)
		wetuwn wet;

	wetuwn 0;

eww_dewete_cec_adap:
	cec_dewete_adaptew(vc4_hdmi->cec_adap);

	wetuwn wet;
}
#ewse
static int vc4_hdmi_cec_init(stwuct vc4_hdmi *vc4_hdmi)
{
	wetuwn 0;
}
#endif

static void vc4_hdmi_fwee_wegset(stwuct dwm_device *dwm, void *ptw)
{
	stwuct debugfs_weg32 *wegs = ptw;

	kfwee(wegs);
}

static int vc4_hdmi_buiwd_wegset(stwuct dwm_device *dwm,
				 stwuct vc4_hdmi *vc4_hdmi,
				 stwuct debugfs_wegset32 *wegset,
				 enum vc4_hdmi_wegs weg)
{
	const stwuct vc4_hdmi_vawiant *vawiant = vc4_hdmi->vawiant;
	stwuct debugfs_weg32 *wegs, *new_wegs;
	unsigned int count = 0;
	unsigned int i;
	int wet;

	wegs = kcawwoc(vawiant->num_wegistews, sizeof(*wegs),
		       GFP_KEWNEW);
	if (!wegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < vawiant->num_wegistews; i++) {
		const stwuct vc4_hdmi_wegistew *fiewd =	&vawiant->wegistews[i];

		if (fiewd->weg != weg)
			continue;

		wegs[count].name = fiewd->name;
		wegs[count].offset = fiewd->offset;
		count++;
	}

	new_wegs = kweawwoc(wegs, count * sizeof(*wegs), GFP_KEWNEW);
	if (!new_wegs)
		wetuwn -ENOMEM;

	wegset->base = __vc4_hdmi_get_fiewd_base(vc4_hdmi, weg);
	wegset->wegs = new_wegs;
	wegset->nwegs = count;

	wet = dwmm_add_action_ow_weset(dwm, vc4_hdmi_fwee_wegset, new_wegs);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int vc4_hdmi_init_wesouwces(stwuct dwm_device *dwm,
				   stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct pwatfowm_device *pdev = vc4_hdmi->pdev;
	stwuct device *dev = &pdev->dev;
	int wet;

	vc4_hdmi->hdmicowe_wegs = vc4_iowemap_wegs(pdev, 0);
	if (IS_EWW(vc4_hdmi->hdmicowe_wegs))
		wetuwn PTW_EWW(vc4_hdmi->hdmicowe_wegs);

	vc4_hdmi->hd_wegs = vc4_iowemap_wegs(pdev, 1);
	if (IS_EWW(vc4_hdmi->hd_wegs))
		wetuwn PTW_EWW(vc4_hdmi->hd_wegs);

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->hd_wegset, VC4_HD);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->hdmi_wegset, VC4_HDMI);
	if (wet)
		wetuwn wet;

	vc4_hdmi->pixew_cwock = devm_cwk_get(dev, "pixew");
	if (IS_EWW(vc4_hdmi->pixew_cwock)) {
		wet = PTW_EWW(vc4_hdmi->pixew_cwock);
		if (wet != -EPWOBE_DEFEW)
			DWM_EWWOW("Faiwed to get pixew cwock\n");
		wetuwn wet;
	}

	vc4_hdmi->hsm_cwock = devm_cwk_get(dev, "hdmi");
	if (IS_EWW(vc4_hdmi->hsm_cwock)) {
		DWM_EWWOW("Faiwed to get HDMI state machine cwock\n");
		wetuwn PTW_EWW(vc4_hdmi->hsm_cwock);
	}
	vc4_hdmi->audio_cwock = vc4_hdmi->hsm_cwock;
	vc4_hdmi->cec_cwock = vc4_hdmi->hsm_cwock;

	wetuwn 0;
}

static int vc5_hdmi_init_wesouwces(stwuct dwm_device *dwm,
				   stwuct vc4_hdmi *vc4_hdmi)
{
	stwuct pwatfowm_device *pdev = vc4_hdmi->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "hdmi");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->hdmicowe_wegs = devm_iowemap(dev, wes->stawt,
					       wesouwce_size(wes));
	if (!vc4_hdmi->hdmicowe_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "hd");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->hd_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->hd_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cec");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->cec_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->cec_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "csc");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->csc_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->csc_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dvp");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->dvp_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->dvp_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "phy");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->phy_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->phy_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "packet");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->wam_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->wam_wegs)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wm");
	if (!wes)
		wetuwn -ENODEV;

	vc4_hdmi->wm_wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vc4_hdmi->wm_wegs)
		wetuwn -ENOMEM;

	vc4_hdmi->hsm_cwock = devm_cwk_get(dev, "hdmi");
	if (IS_EWW(vc4_hdmi->hsm_cwock)) {
		DWM_EWWOW("Faiwed to get HDMI state machine cwock\n");
		wetuwn PTW_EWW(vc4_hdmi->hsm_cwock);
	}

	vc4_hdmi->pixew_bvb_cwock = devm_cwk_get(dev, "bvb");
	if (IS_EWW(vc4_hdmi->pixew_bvb_cwock)) {
		DWM_EWWOW("Faiwed to get pixew bvb cwock\n");
		wetuwn PTW_EWW(vc4_hdmi->pixew_bvb_cwock);
	}

	vc4_hdmi->audio_cwock = devm_cwk_get(dev, "audio");
	if (IS_EWW(vc4_hdmi->audio_cwock)) {
		DWM_EWWOW("Faiwed to get audio cwock\n");
		wetuwn PTW_EWW(vc4_hdmi->audio_cwock);
	}

	vc4_hdmi->cec_cwock = devm_cwk_get(dev, "cec");
	if (IS_EWW(vc4_hdmi->cec_cwock)) {
		DWM_EWWOW("Faiwed to get CEC cwock\n");
		wetuwn PTW_EWW(vc4_hdmi->cec_cwock);
	}

	vc4_hdmi->weset = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(vc4_hdmi->weset)) {
		DWM_EWWOW("Faiwed to get HDMI weset wine\n");
		wetuwn PTW_EWW(vc4_hdmi->weset);
	}

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->hdmi_wegset, VC4_HDMI);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->hd_wegset, VC4_HD);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->cec_wegset, VC5_CEC);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->csc_wegset, VC5_CSC);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->dvp_wegset, VC5_DVP);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->phy_wegset, VC5_PHY);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->wam_wegset, VC5_WAM);
	if (wet)
		wetuwn wet;

	wet = vc4_hdmi_buiwd_wegset(dwm, vc4_hdmi, &vc4_hdmi->wm_wegset, VC5_WM);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int vc4_hdmi_wuntime_suspend(stwuct device *dev)
{
	stwuct vc4_hdmi *vc4_hdmi = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(vc4_hdmi->hsm_cwock);

	wetuwn 0;
}

static int vc4_hdmi_wuntime_wesume(stwuct device *dev)
{
	stwuct vc4_hdmi *vc4_hdmi = dev_get_dwvdata(dev);
	unsigned wong __maybe_unused fwags;
	u32 __maybe_unused vawue;
	unsigned wong wate;
	int wet;

	wet = cwk_pwepawe_enabwe(vc4_hdmi->hsm_cwock);
	if (wet)
		wetuwn wet;

	/*
	 * Whenevew the WaspbewwyPi boots without an HDMI monitow
	 * pwugged in, the fiwmwawe won't have initiawized the HSM cwock
	 * wate and it wiww be wepowted as 0.
	 *
	 * If we twy to access a wegistew of the contwowwew in such a
	 * case, it wiww wead to a siwent CPU staww. Wet's make suwe we
	 * pwevent such a case.
	 */
	wate = cwk_get_wate(vc4_hdmi->hsm_cwock);
	if (!wate) {
		wet = -EINVAW;
		goto eww_disabwe_cwk;
	}

	if (vc4_hdmi->vawiant->weset)
		vc4_hdmi->vawiant->weset(vc4_hdmi);

#ifdef CONFIG_DWM_VC4_HDMI_CEC
	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	vawue = HDMI_WEAD(HDMI_CEC_CNTWW_1);
	/* Set the wogicaw addwess to Unwegistewed */
	vawue |= VC4_HDMI_CEC_ADDW_MASK;
	HDMI_WWITE(HDMI_CEC_CNTWW_1, vawue);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);

	vc4_hdmi_cec_update_cwk_div(vc4_hdmi);

	if (!vc4_hdmi->vawiant->extewnaw_iwq_contwowwew) {
		spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
		HDMI_WWITE(HDMI_CEC_CPU_MASK_SET, 0xffffffff);
		spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
	}
#endif

	wetuwn 0;

eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(vc4_hdmi->hsm_cwock);
	wetuwn wet;
}

static void vc4_hdmi_put_ddc_device(void *ptw)
{
	stwuct vc4_hdmi *vc4_hdmi = ptw;

	put_device(&vc4_hdmi->ddc->dev);
}

static int vc4_hdmi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	const stwuct vc4_hdmi_vawiant *vawiant = of_device_get_match_data(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = dev_get_dwvdata(mastew);
	stwuct vc4_hdmi *vc4_hdmi;
	stwuct dwm_encodew *encodew;
	stwuct device_node *ddc_node;
	int wet;

	vc4_hdmi = dwmm_kzawwoc(dwm, sizeof(*vc4_hdmi), GFP_KEWNEW);
	if (!vc4_hdmi)
		wetuwn -ENOMEM;

	wet = dwmm_mutex_init(dwm, &vc4_hdmi->mutex);
	if (wet)
		wetuwn wet;

	spin_wock_init(&vc4_hdmi->hw_wock);
	INIT_DEWAYED_WOWK(&vc4_hdmi->scwambwing_wowk, vc4_hdmi_scwambwing_wq);

	dev_set_dwvdata(dev, vc4_hdmi);
	encodew = &vc4_hdmi->encodew.base;
	vc4_hdmi->encodew.type = vawiant->encodew_type;
	vc4_hdmi->encodew.pwe_cwtc_configuwe = vc4_hdmi_encodew_pwe_cwtc_configuwe;
	vc4_hdmi->encodew.pwe_cwtc_enabwe = vc4_hdmi_encodew_pwe_cwtc_enabwe;
	vc4_hdmi->encodew.post_cwtc_enabwe = vc4_hdmi_encodew_post_cwtc_enabwe;
	vc4_hdmi->encodew.post_cwtc_disabwe = vc4_hdmi_encodew_post_cwtc_disabwe;
	vc4_hdmi->encodew.post_cwtc_powewdown = vc4_hdmi_encodew_post_cwtc_powewdown;
	vc4_hdmi->pdev = pdev;
	vc4_hdmi->vawiant = vawiant;

	/*
	 * Since we don't know the state of the contwowwew and its
	 * dispway (if any), wet's assume it's awways enabwed.
	 * vc4_hdmi_disabwe_scwambwing() wiww thus wun at boot, make
	 * suwe it's disabwed, and avoid any inconsistency.
	 */
	if (vawiant->max_pixew_cwock > HDMI_14_MAX_TMDS_CWK)
		vc4_hdmi->scdc_enabwed = twue;

	wet = vawiant->init_wesouwces(dwm, vc4_hdmi);
	if (wet)
		wetuwn wet;

	ddc_node = of_pawse_phandwe(dev->of_node, "ddc", 0);
	if (!ddc_node) {
		DWM_EWWOW("Faiwed to find ddc node in device twee\n");
		wetuwn -ENODEV;
	}

	vc4_hdmi->ddc = of_find_i2c_adaptew_by_node(ddc_node);
	of_node_put(ddc_node);
	if (!vc4_hdmi->ddc) {
		DWM_DEBUG("Faiwed to get ddc i2c adaptew by node\n");
		wetuwn -EPWOBE_DEFEW;
	}

	wet = devm_add_action_ow_weset(dev, vc4_hdmi_put_ddc_device, vc4_hdmi);
	if (wet)
		wetuwn wet;

	/* Onwy use the GPIO HPD pin if pwesent in the DT, othewwise
	 * we'ww use the HDMI cowe's wegistew.
	 */
	vc4_hdmi->hpd_gpio = devm_gpiod_get_optionaw(dev, "hpd", GPIOD_IN);
	if (IS_EWW(vc4_hdmi->hpd_gpio)) {
		wetuwn PTW_EWW(vc4_hdmi->hpd_gpio);
	}

	vc4_hdmi->disabwe_wifi_fwequencies =
		of_pwopewty_wead_boow(dev->of_node, "wifi-2.4ghz-coexistence");

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn wet;

	/*
	 *  We need to have the device powewed up at this point to caww
	 *  ouw weset hook and fow the CEC init.
	 */
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn wet;

	if ((of_device_is_compatibwe(dev->of_node, "bwcm,bcm2711-hdmi0") ||
	     of_device_is_compatibwe(dev->of_node, "bwcm,bcm2711-hdmi1")) &&
	    HDMI_WEAD(HDMI_VID_CTW) & VC4_HD_VID_CTW_ENABWE) {
		cwk_pwepawe_enabwe(vc4_hdmi->pixew_cwock);
		cwk_pwepawe_enabwe(vc4_hdmi->hsm_cwock);
		cwk_pwepawe_enabwe(vc4_hdmi->pixew_bvb_cwock);
	}

	wet = dwmm_encodew_init(dwm, encodew,
				&vc4_hdmi_encodew_funcs,
				DWM_MODE_ENCODEW_TMDS,
				NUWW);
	if (wet)
		goto eww_put_wuntime_pm;

	dwm_encodew_hewpew_add(encodew, &vc4_hdmi_encodew_hewpew_funcs);

	wet = vc4_hdmi_connectow_init(dwm, vc4_hdmi);
	if (wet)
		goto eww_put_wuntime_pm;

	wet = vc4_hdmi_hotpwug_init(vc4_hdmi);
	if (wet)
		goto eww_put_wuntime_pm;

	wet = vc4_hdmi_cec_init(vc4_hdmi);
	if (wet)
		goto eww_put_wuntime_pm;

	wet = vc4_hdmi_audio_init(vc4_hdmi);
	if (wet)
		goto eww_put_wuntime_pm;

	pm_wuntime_put_sync(dev);

	wetuwn 0;

eww_put_wuntime_pm:
	pm_wuntime_put_sync(dev);

	wetuwn wet;
}

static const stwuct component_ops vc4_hdmi_ops = {
	.bind   = vc4_hdmi_bind,
};

static int vc4_hdmi_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &vc4_hdmi_ops);
}

static void vc4_hdmi_dev_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vc4_hdmi_ops);
}

static const stwuct vc4_hdmi_vawiant bcm2835_vawiant = {
	.encodew_type		= VC4_ENCODEW_TYPE_HDMI0,
	.debugfs_name		= "hdmi_wegs",
	.cawd_name		= "vc4-hdmi",
	.max_pixew_cwock	= 162000000,
	.wegistews		= vc4_hdmi_fiewds,
	.num_wegistews		= AWWAY_SIZE(vc4_hdmi_fiewds),

	.init_wesouwces		= vc4_hdmi_init_wesouwces,
	.csc_setup		= vc4_hdmi_csc_setup,
	.weset			= vc4_hdmi_weset,
	.set_timings		= vc4_hdmi_set_timings,
	.phy_init		= vc4_hdmi_phy_init,
	.phy_disabwe		= vc4_hdmi_phy_disabwe,
	.phy_wng_enabwe		= vc4_hdmi_phy_wng_enabwe,
	.phy_wng_disabwe	= vc4_hdmi_phy_wng_disabwe,
	.channew_map		= vc4_hdmi_channew_map,
	.suppowts_hdw		= fawse,
};

static const stwuct vc4_hdmi_vawiant bcm2711_hdmi0_vawiant = {
	.encodew_type		= VC4_ENCODEW_TYPE_HDMI0,
	.debugfs_name		= "hdmi0_wegs",
	.cawd_name		= "vc4-hdmi-0",
	.max_pixew_cwock	= 600000000,
	.wegistews		= vc5_hdmi_hdmi0_fiewds,
	.num_wegistews		= AWWAY_SIZE(vc5_hdmi_hdmi0_fiewds),
	.phy_wane_mapping	= {
		PHY_WANE_0,
		PHY_WANE_1,
		PHY_WANE_2,
		PHY_WANE_CK,
	},
	.unsuppowted_odd_h_timings	= twue,
	.extewnaw_iwq_contwowwew	= twue,

	.init_wesouwces		= vc5_hdmi_init_wesouwces,
	.csc_setup		= vc5_hdmi_csc_setup,
	.weset			= vc5_hdmi_weset,
	.set_timings		= vc5_hdmi_set_timings,
	.phy_init		= vc5_hdmi_phy_init,
	.phy_disabwe		= vc5_hdmi_phy_disabwe,
	.phy_wng_enabwe		= vc5_hdmi_phy_wng_enabwe,
	.phy_wng_disabwe	= vc5_hdmi_phy_wng_disabwe,
	.channew_map		= vc5_hdmi_channew_map,
	.suppowts_hdw		= twue,
	.hp_detect		= vc5_hdmi_hp_detect,
};

static const stwuct vc4_hdmi_vawiant bcm2711_hdmi1_vawiant = {
	.encodew_type		= VC4_ENCODEW_TYPE_HDMI1,
	.debugfs_name		= "hdmi1_wegs",
	.cawd_name		= "vc4-hdmi-1",
	.max_pixew_cwock	= HDMI_14_MAX_TMDS_CWK,
	.wegistews		= vc5_hdmi_hdmi1_fiewds,
	.num_wegistews		= AWWAY_SIZE(vc5_hdmi_hdmi1_fiewds),
	.phy_wane_mapping	= {
		PHY_WANE_1,
		PHY_WANE_0,
		PHY_WANE_CK,
		PHY_WANE_2,
	},
	.unsuppowted_odd_h_timings	= twue,
	.extewnaw_iwq_contwowwew	= twue,

	.init_wesouwces		= vc5_hdmi_init_wesouwces,
	.csc_setup		= vc5_hdmi_csc_setup,
	.weset			= vc5_hdmi_weset,
	.set_timings		= vc5_hdmi_set_timings,
	.phy_init		= vc5_hdmi_phy_init,
	.phy_disabwe		= vc5_hdmi_phy_disabwe,
	.phy_wng_enabwe		= vc5_hdmi_phy_wng_enabwe,
	.phy_wng_disabwe	= vc5_hdmi_phy_wng_disabwe,
	.channew_map		= vc5_hdmi_channew_map,
	.suppowts_hdw		= twue,
	.hp_detect		= vc5_hdmi_hp_detect,
};

static const stwuct of_device_id vc4_hdmi_dt_match[] = {
	{ .compatibwe = "bwcm,bcm2835-hdmi", .data = &bcm2835_vawiant },
	{ .compatibwe = "bwcm,bcm2711-hdmi0", .data = &bcm2711_hdmi0_vawiant },
	{ .compatibwe = "bwcm,bcm2711-hdmi1", .data = &bcm2711_hdmi1_vawiant },
	{}
};

static const stwuct dev_pm_ops vc4_hdmi_pm_ops = {
	SET_WUNTIME_PM_OPS(vc4_hdmi_wuntime_suspend,
			   vc4_hdmi_wuntime_wesume,
			   NUWW)
};

stwuct pwatfowm_dwivew vc4_hdmi_dwivew = {
	.pwobe = vc4_hdmi_dev_pwobe,
	.wemove_new = vc4_hdmi_dev_wemove,
	.dwivew = {
		.name = "vc4_hdmi",
		.of_match_tabwe = vc4_hdmi_dt_match,
		.pm = &vc4_hdmi_pm_ops,
	},
};
