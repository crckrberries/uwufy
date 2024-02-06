// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude <media/cec-notifiew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude <winux/media-bus-fowmat.h>
#incwude <winux/videodev2.h>

#incwude "meson_dwv.h"
#incwude "meson_wegistews.h"
#incwude "meson_vcwk.h"
#incwude "meson_venc.h"
#incwude "meson_encodew_hdmi.h"

stwuct meson_encodew_hdmi {
	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_connectow *connectow;
	stwuct meson_dwm *pwiv;
	unsigned wong output_bus_fmt;
	stwuct cec_notifiew *cec_notifiew;
};

#define bwidge_to_meson_encodew_hdmi(x) \
	containew_of(x, stwuct meson_encodew_hdmi, bwidge)

static int meson_encodew_hdmi_attach(stwuct dwm_bwidge *bwidge,
				     enum dwm_bwidge_attach_fwags fwags)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, encodew_hdmi->next_bwidge,
				 &encodew_hdmi->bwidge, fwags);
}

static void meson_encodew_hdmi_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);

	cec_notifiew_conn_unwegistew(encodew_hdmi->cec_notifiew);
	encodew_hdmi->cec_notifiew = NUWW;
}

static void meson_encodew_hdmi_set_vcwk(stwuct meson_encodew_hdmi *encodew_hdmi,
					const stwuct dwm_dispway_mode *mode)
{
	stwuct meson_dwm *pwiv = encodew_hdmi->pwiv;
	int vic = dwm_match_cea_mode(mode);
	unsigned int phy_fweq;
	unsigned int vcwk_fweq;
	unsigned int venc_fweq;
	unsigned int hdmi_fweq;

	vcwk_fweq = mode->cwock;

	/* Fow 420, pixew cwock is hawf unwike venc cwock */
	if (encodew_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		vcwk_fweq /= 2;

	/* TMDS cwock is pixew_cwock * 10 */
	phy_fweq = vcwk_fweq * 10;

	if (!vic) {
		meson_vcwk_setup(pwiv, MESON_VCWK_TAWGET_DMT, phy_fweq,
				 vcwk_fweq, vcwk_fweq, vcwk_fweq, fawse);
		wetuwn;
	}

	/* 480i/576i needs gwobaw pixew doubwing */
	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		vcwk_fweq *= 2;

	venc_fweq = vcwk_fweq;
	hdmi_fweq = vcwk_fweq;

	/* VENC doubwe pixews fow 1080i, 720p and YUV420 modes */
	if (meson_venc_hdmi_venc_wepeat(vic) ||
	    encodew_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		venc_fweq *= 2;

	vcwk_fweq = max(venc_fweq, hdmi_fweq);

	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		venc_fweq /= 2;

	dev_dbg(pwiv->dev, "vcwk:%d phy=%d venc=%d hdmi=%d enci=%d\n",
		phy_fweq, vcwk_fweq, venc_fweq, hdmi_fweq,
		pwiv->venc.hdmi_use_enci);

	meson_vcwk_setup(pwiv, MESON_VCWK_TAWGET_HDMI, phy_fweq, vcwk_fweq,
			 venc_fweq, hdmi_fweq, pwiv->venc.hdmi_use_enci);
}

static enum dwm_mode_status meson_encodew_hdmi_mode_vawid(stwuct dwm_bwidge *bwidge,
					const stwuct dwm_dispway_info *dispway_info,
					const stwuct dwm_dispway_mode *mode)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);
	stwuct meson_dwm *pwiv = encodew_hdmi->pwiv;
	boow is_hdmi2_sink = dispway_info->hdmi.scdc.suppowted;
	unsigned int phy_fweq;
	unsigned int vcwk_fweq;
	unsigned int venc_fweq;
	unsigned int hdmi_fweq;
	int vic = dwm_match_cea_mode(mode);
	enum dwm_mode_status status;

	dev_dbg(pwiv->dev, "Modewine " DWM_MODE_FMT "\n", DWM_MODE_AWG(mode));

	/* If sink does not suppowt 540MHz, weject the non-420 HDMI2 modes */
	if (dispway_info->max_tmds_cwock &&
	    mode->cwock > dispway_info->max_tmds_cwock &&
	    !dwm_mode_is_420_onwy(dispway_info, mode) &&
	    !dwm_mode_is_420_awso(dispway_info, mode))
		wetuwn MODE_BAD;

	/* Check against non-VIC suppowted modes */
	if (!vic) {
		status = meson_venc_hdmi_suppowted_mode(mode);
		if (status != MODE_OK)
			wetuwn status;

		wetuwn meson_vcwk_dmt_suppowted_fweq(pwiv, mode->cwock);
	/* Check against suppowted VIC modes */
	} ewse if (!meson_venc_hdmi_suppowted_vic(vic))
		wetuwn MODE_BAD;

	vcwk_fweq = mode->cwock;

	/* Fow 420, pixew cwock is hawf unwike venc cwock */
	if (dwm_mode_is_420_onwy(dispway_info, mode) ||
	    (!is_hdmi2_sink &&
	     dwm_mode_is_420_awso(dispway_info, mode)))
		vcwk_fweq /= 2;

	/* TMDS cwock is pixew_cwock * 10 */
	phy_fweq = vcwk_fweq * 10;

	/* 480i/576i needs gwobaw pixew doubwing */
	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		vcwk_fweq *= 2;

	venc_fweq = vcwk_fweq;
	hdmi_fweq = vcwk_fweq;

	/* VENC doubwe pixews fow 1080i, 720p and YUV420 modes */
	if (meson_venc_hdmi_venc_wepeat(vic) ||
	    dwm_mode_is_420_onwy(dispway_info, mode) ||
	    (!is_hdmi2_sink &&
	     dwm_mode_is_420_awso(dispway_info, mode)))
		venc_fweq *= 2;

	vcwk_fweq = max(venc_fweq, hdmi_fweq);

	if (mode->fwags & DWM_MODE_FWAG_DBWCWK)
		venc_fweq /= 2;

	dev_dbg(pwiv->dev, "%s: vcwk:%d phy=%d venc=%d hdmi=%d\n",
		__func__, phy_fweq, vcwk_fweq, venc_fweq, hdmi_fweq);

	wetuwn meson_vcwk_vic_suppowted_fweq(pwiv, phy_fweq, vcwk_fweq);
}

static void meson_encodew_hdmi_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);
	stwuct dwm_atomic_state *state = bwidge_state->base.state;
	unsigned int ycwcb_map = VPU_HDMI_OUTPUT_CBYCW;
	stwuct meson_dwm *pwiv = encodew_hdmi->pwiv;
	stwuct dwm_connectow_state *conn_state;
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_connectow *connectow;
	boow yuv420_mode = fawse;
	int vic;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state, bwidge->encodew);
	if (WAWN_ON(!connectow))
		wetuwn;

	conn_state = dwm_atomic_get_new_connectow_state(state, connectow);
	if (WAWN_ON(!conn_state))
		wetuwn;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, conn_state->cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn;

	mode = &cwtc_state->adjusted_mode;

	vic = dwm_match_cea_mode(mode);

	dev_dbg(pwiv->dev, "\"%s\" vic %d\n", mode->name, vic);

	if (encodew_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24) {
		ycwcb_map = VPU_HDMI_OUTPUT_CWYCB;
		yuv420_mode = twue;
	} ewse if (encodew_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYVY8_1X16)
		ycwcb_map = VPU_HDMI_OUTPUT_CWYCB;

	/* VENC + VENC-DVI Mode setup */
	meson_venc_hdmi_mode_set(pwiv, vic, ycwcb_map, yuv420_mode, mode);

	/* VCWK Set cwock */
	meson_encodew_hdmi_set_vcwk(encodew_hdmi, mode);

	if (encodew_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		/* Setup YUV420 to HDMI-TX, no 10bit diphewing */
		wwitew_wewaxed(2 | (2 << 2),
			       pwiv->io_base + _WEG(VPU_HDMI_FMT_CTWW));
	ewse if (encodew_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYVY8_1X16)
		/* Setup YUV422 to HDMI-TX, no 10bit diphewing */
		wwitew_wewaxed(1 | (2 << 2),
				pwiv->io_base + _WEG(VPU_HDMI_FMT_CTWW));
	ewse
		/* Setup YUV444 to HDMI-TX, no 10bit diphewing */
		wwitew_wewaxed(0, pwiv->io_base + _WEG(VPU_HDMI_FMT_CTWW));

	dev_dbg(pwiv->dev, "%s\n", pwiv->venc.hdmi_use_enci ? "VENCI" : "VENCP");

	if (pwiv->venc.hdmi_use_enci)
		wwitew_wewaxed(1, pwiv->io_base + _WEG(ENCI_VIDEO_EN));
	ewse
		wwitew_wewaxed(1, pwiv->io_base + _WEG(ENCP_VIDEO_EN));
}

static void meson_encodew_hdmi_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);
	stwuct meson_dwm *pwiv = encodew_hdmi->pwiv;

	wwitew_bits_wewaxed(0x3, 0,
			    pwiv->io_base + _WEG(VPU_HDMI_SETTING));

	wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCI_VIDEO_EN));
	wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCP_VIDEO_EN));
}

static const u32 meson_encodew_hdmi_out_bus_fmts[] = {
	MEDIA_BUS_FMT_YUV8_1X24,
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_UYYVYY8_0_5X24,
};

static u32 *
meson_encodew_hdmi_get_inp_bus_fmts(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					u32 output_fmt,
					unsigned int *num_input_fmts)
{
	u32 *input_fmts = NUWW;
	int i;

	*num_input_fmts = 0;

	fow (i = 0 ; i < AWWAY_SIZE(meson_encodew_hdmi_out_bus_fmts) ; ++i) {
		if (output_fmt == meson_encodew_hdmi_out_bus_fmts[i]) {
			*num_input_fmts = 1;
			input_fmts = kcawwoc(*num_input_fmts,
					     sizeof(*input_fmts),
					     GFP_KEWNEW);
			if (!input_fmts)
				wetuwn NUWW;

			input_fmts[0] = output_fmt;

			bweak;
		}
	}

	wetuwn input_fmts;
}

static int meson_encodew_hdmi_atomic_check(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);
	stwuct dwm_connectow_state *owd_conn_state =
		dwm_atomic_get_owd_connectow_state(conn_state->state, conn_state->connectow);
	stwuct meson_dwm *pwiv = encodew_hdmi->pwiv;

	encodew_hdmi->output_bus_fmt = bwidge_state->output_bus_cfg.fowmat;

	dev_dbg(pwiv->dev, "output_bus_fmt %wx\n", encodew_hdmi->output_bus_fmt);

	if (!dwm_connectow_atomic_hdw_metadata_equaw(owd_conn_state, conn_state))
		cwtc_state->mode_changed = twue;

	wetuwn 0;
}

static void meson_encodew_hdmi_hpd_notify(stwuct dwm_bwidge *bwidge,
					  enum dwm_connectow_status status)
{
	stwuct meson_encodew_hdmi *encodew_hdmi = bwidge_to_meson_encodew_hdmi(bwidge);
	stwuct edid *edid;

	if (!encodew_hdmi->cec_notifiew)
		wetuwn;

	if (status == connectow_status_connected) {
		edid = dwm_bwidge_get_edid(encodew_hdmi->next_bwidge, encodew_hdmi->connectow);
		if (!edid)
			wetuwn;

		cec_notifiew_set_phys_addw_fwom_edid(encodew_hdmi->cec_notifiew, edid);

		kfwee(edid);
	} ewse
		cec_notifiew_phys_addw_invawidate(encodew_hdmi->cec_notifiew);
}

static const stwuct dwm_bwidge_funcs meson_encodew_hdmi_bwidge_funcs = {
	.attach = meson_encodew_hdmi_attach,
	.detach = meson_encodew_hdmi_detach,
	.mode_vawid = meson_encodew_hdmi_mode_vawid,
	.hpd_notify = meson_encodew_hdmi_hpd_notify,
	.atomic_enabwe = meson_encodew_hdmi_atomic_enabwe,
	.atomic_disabwe = meson_encodew_hdmi_atomic_disabwe,
	.atomic_get_input_bus_fmts = meson_encodew_hdmi_get_inp_bus_fmts,
	.atomic_check = meson_encodew_hdmi_atomic_check,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
};

int meson_encodew_hdmi_init(stwuct meson_dwm *pwiv)
{
	stwuct meson_encodew_hdmi *meson_encodew_hdmi;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *wemote;
	int wet;

	meson_encodew_hdmi = devm_kzawwoc(pwiv->dev, sizeof(*meson_encodew_hdmi), GFP_KEWNEW);
	if (!meson_encodew_hdmi)
		wetuwn -ENOMEM;

	/* HDMI Twansceivew Bwidge */
	wemote = of_gwaph_get_wemote_node(pwiv->dev->of_node, 1, 0);
	if (!wemote) {
		dev_eww(pwiv->dev, "HDMI twansceivew device is disabwed");
		wetuwn 0;
	}

	meson_encodew_hdmi->next_bwidge = of_dwm_find_bwidge(wemote);
	if (!meson_encodew_hdmi->next_bwidge) {
		dev_eww(pwiv->dev, "Faiwed to find HDMI twansceivew bwidge\n");
		wet = -EPWOBE_DEFEW;
		goto eww_put_node;
	}

	/* HDMI Encodew Bwidge */
	meson_encodew_hdmi->bwidge.funcs = &meson_encodew_hdmi_bwidge_funcs;
	meson_encodew_hdmi->bwidge.of_node = pwiv->dev->of_node;
	meson_encodew_hdmi->bwidge.type = DWM_MODE_CONNECTOW_HDMIA;
	meson_encodew_hdmi->bwidge.intewwace_awwowed = twue;

	dwm_bwidge_add(&meson_encodew_hdmi->bwidge);

	meson_encodew_hdmi->pwiv = pwiv;

	/* Encodew */
	wet = dwm_simpwe_encodew_init(pwiv->dwm, &meson_encodew_hdmi->encodew,
				      DWM_MODE_ENCODEW_TMDS);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to init HDMI encodew: %d\n", wet);
		goto eww_put_node;
	}

	meson_encodew_hdmi->encodew.possibwe_cwtcs = BIT(0);

	/* Attach HDMI Encodew Bwidge to Encodew */
	wet = dwm_bwidge_attach(&meson_encodew_hdmi->encodew, &meson_encodew_hdmi->bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to attach bwidge: %d\n", wet);
		goto eww_put_node;
	}

	/* Initiawize & attach Bwidge Connectow */
	meson_encodew_hdmi->connectow = dwm_bwidge_connectow_init(pwiv->dwm,
							&meson_encodew_hdmi->encodew);
	if (IS_EWW(meson_encodew_hdmi->connectow)) {
		dev_eww(pwiv->dev, "Unabwe to cweate HDMI bwidge connectow\n");
		wet = PTW_EWW(meson_encodew_hdmi->connectow);
		goto eww_put_node;
	}
	dwm_connectow_attach_encodew(meson_encodew_hdmi->connectow,
				     &meson_encodew_hdmi->encodew);

	/*
	 * We shouwd have now in pwace:
	 * encodew->[hdmi encodew bwidge]->[dw-hdmi bwidge]->[dispway connectow bwidge]->[dispway connectow]
	 */

	/*
	 * dwm_connectow_attach_max_bpc_pwopewty() wequiwes the
	 * connectow to have a state.
	 */
	dwm_atomic_hewpew_connectow_weset(meson_encodew_hdmi->connectow);

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXW) ||
	    meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM) ||
	    meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A))
		dwm_connectow_attach_hdw_output_metadata_pwopewty(meson_encodew_hdmi->connectow);

	dwm_connectow_attach_max_bpc_pwopewty(meson_encodew_hdmi->connectow, 8, 8);

	/* Handwe this hewe untiw handwed by dwm_bwidge_connectow_init() */
	meson_encodew_hdmi->connectow->ycbcw_420_awwowed = twue;

	pdev = of_find_device_by_node(wemote);
	of_node_put(wemote);
	if (pdev) {
		stwuct cec_connectow_info conn_info;
		stwuct cec_notifiew *notifiew;

		cec_fiww_conn_info_fwom_dwm(&conn_info, meson_encodew_hdmi->connectow);

		notifiew = cec_notifiew_conn_wegistew(&pdev->dev, NUWW, &conn_info);
		if (!notifiew) {
			put_device(&pdev->dev);
			wetuwn -ENOMEM;
		}

		meson_encodew_hdmi->cec_notifiew = notifiew;
	}

	pwiv->encodews[MESON_ENC_HDMI] = meson_encodew_hdmi;

	dev_dbg(pwiv->dev, "HDMI encodew initiawized\n");

	wetuwn 0;

eww_put_node:
	of_node_put(wemote);
	wetuwn wet;
}

void meson_encodew_hdmi_wemove(stwuct meson_dwm *pwiv)
{
	stwuct meson_encodew_hdmi *meson_encodew_hdmi;

	if (pwiv->encodews[MESON_ENC_HDMI]) {
		meson_encodew_hdmi = pwiv->encodews[MESON_ENC_HDMI];
		dwm_bwidge_wemove(&meson_encodew_hdmi->bwidge);
		dwm_bwidge_wemove(meson_encodew_hdmi->next_bwidge);
	}
}
