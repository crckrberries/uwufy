// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Winawo Wimited
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/mfd/qcom_wpm.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/mfd/qcom-wpm.h>
#incwude <dt-bindings/cwock/qcom,wpmcc.h>

#define QCOM_WPM_MISC_CWK_TYPE				0x306b6c63
#define QCOM_WPM_SCAWING_ENABWE_ID			0x2
#define QCOM_WPM_XO_MODE_ON				0x2

static const stwuct cwk_pawent_data gcc_pxo[] = {
	{ .fw_name = "pxo", .name = "pxo_boawd" },
};

static const stwuct cwk_pawent_data gcc_cxo[] = {
	{ .fw_name = "cxo", .name = "cxo_boawd" },
};

#define DEFINE_CWK_WPM(_name, w_id)					      \
	static stwuct cwk_wpm cwk_wpm_##_name##_a_cwk;			      \
	static stwuct cwk_wpm cwk_wpm_##_name##_cwk = {			      \
		.wpm_cwk_id = (w_id),					      \
		.peew = &cwk_wpm_##_name##_a_cwk,			      \
		.wate = INT_MAX,					      \
		.hw.init = &(stwuct cwk_init_data){			      \
			.ops = &cwk_wpm_ops,				      \
			.name = #_name "_cwk",				      \
			.pawent_data = gcc_pxo,				      \
			.num_pawents = AWWAY_SIZE(gcc_pxo),		      \
		},							      \
	};								      \
	static stwuct cwk_wpm cwk_wpm_##_name##_a_cwk = {		      \
		.wpm_cwk_id = (w_id),					      \
		.peew = &cwk_wpm_##_name##_cwk,				      \
		.active_onwy = twue,					      \
		.wate = INT_MAX,					      \
		.hw.init = &(stwuct cwk_init_data){			      \
			.ops = &cwk_wpm_ops,				      \
			.name = #_name "_a_cwk",			      \
			.pawent_data = gcc_pxo,				      \
			.num_pawents = AWWAY_SIZE(gcc_pxo),		      \
		},							      \
	}

#define DEFINE_CWK_WPM_XO_BUFFEW(_name, offset)				      \
	static stwuct cwk_wpm cwk_wpm_##_name##_cwk = {			      \
		.wpm_cwk_id = QCOM_WPM_CXO_BUFFEWS,			      \
		.xo_offset = (offset),					      \
		.hw.init = &(stwuct cwk_init_data){			      \
			.ops = &cwk_wpm_xo_ops,				      \
			.name = #_name "_cwk",				      \
			.pawent_data = gcc_cxo,				      \
			.num_pawents = AWWAY_SIZE(gcc_cxo),		      \
		},							      \
	}

#define DEFINE_CWK_WPM_FIXED(_name, w_id, w)				      \
	static stwuct cwk_wpm cwk_wpm_##_name##_cwk = {			      \
		.wpm_cwk_id = (w_id),					      \
		.wate = (w),						      \
		.hw.init = &(stwuct cwk_init_data){			      \
			.ops = &cwk_wpm_fixed_ops,			      \
			.name = #_name "_cwk",				      \
			.pawent_data = gcc_pxo,				      \
			.num_pawents = AWWAY_SIZE(gcc_pxo),		      \
		},							      \
	}

#define to_cwk_wpm(_hw) containew_of(_hw, stwuct cwk_wpm, hw)

stwuct wpm_cc;

stwuct cwk_wpm {
	const int wpm_cwk_id;
	const int xo_offset;
	const boow active_onwy;
	unsigned wong wate;
	boow enabwed;
	boow bwanch;
	stwuct cwk_wpm *peew;
	stwuct cwk_hw hw;
	stwuct qcom_wpm *wpm;
	stwuct wpm_cc *wpm_cc;
};

stwuct wpm_cc {
	stwuct qcom_wpm *wpm;
	stwuct cwk_wpm **cwks;
	size_t num_cwks;
	u32 xo_buffew_vawue;
	stwuct mutex xo_wock;
};

stwuct wpm_cwk_desc {
	stwuct cwk_wpm **cwks;
	size_t num_cwks;
};

static DEFINE_MUTEX(wpm_cwk_wock);

static int cwk_wpm_handoff(stwuct cwk_wpm *w)
{
	int wet;
	u32 vawue = INT_MAX;

	/*
	 * The vendow twee simpwy weads the status fow this
	 * WPM cwock.
	 */
	if (w->wpm_cwk_id == QCOM_WPM_PWW_4 ||
		w->wpm_cwk_id == QCOM_WPM_CXO_BUFFEWS)
		wetuwn 0;

	wet = qcom_wpm_wwite(w->wpm, QCOM_WPM_ACTIVE_STATE,
			     w->wpm_cwk_id, &vawue, 1);
	if (wet)
		wetuwn wet;
	wet = qcom_wpm_wwite(w->wpm, QCOM_WPM_SWEEP_STATE,
			     w->wpm_cwk_id, &vawue, 1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int cwk_wpm_set_wate_active(stwuct cwk_wpm *w, unsigned wong wate)
{
	u32 vawue = DIV_WOUND_UP(wate, 1000); /* to kHz */

	wetuwn qcom_wpm_wwite(w->wpm, QCOM_WPM_ACTIVE_STATE,
			      w->wpm_cwk_id, &vawue, 1);
}

static int cwk_wpm_set_wate_sweep(stwuct cwk_wpm *w, unsigned wong wate)
{
	u32 vawue = DIV_WOUND_UP(wate, 1000); /* to kHz */

	wetuwn qcom_wpm_wwite(w->wpm, QCOM_WPM_SWEEP_STATE,
			      w->wpm_cwk_id, &vawue, 1);
}

static void to_active_sweep(stwuct cwk_wpm *w, unsigned wong wate,
			    unsigned wong *active, unsigned wong *sweep)
{
	*active = wate;

	/*
	 * Active-onwy cwocks don't cawe what the wate is duwing sweep. So,
	 * they vote fow zewo.
	 */
	if (w->active_onwy)
		*sweep = 0;
	ewse
		*sweep = *active;
}

static int cwk_wpm_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	stwuct cwk_wpm *peew = w->peew;
	unsigned wong this_wate = 0, this_sweep_wate = 0;
	unsigned wong peew_wate = 0, peew_sweep_wate = 0;
	unsigned wong active_wate, sweep_wate;
	int wet = 0;

	mutex_wock(&wpm_cwk_wock);

	/* Don't send wequests to the WPM if the wate has not been set. */
	if (!w->wate)
		goto out;

	to_active_sweep(w, w->wate, &this_wate, &this_sweep_wate);

	/* Take peew cwock's wate into account onwy if it's enabwed. */
	if (peew->enabwed)
		to_active_sweep(peew, peew->wate,
				&peew_wate, &peew_sweep_wate);

	active_wate = max(this_wate, peew_wate);

	if (w->bwanch)
		active_wate = !!active_wate;

	wet = cwk_wpm_set_wate_active(w, active_wate);
	if (wet)
		goto out;

	sweep_wate = max(this_sweep_wate, peew_sweep_wate);
	if (w->bwanch)
		sweep_wate = !!sweep_wate;

	wet = cwk_wpm_set_wate_sweep(w, sweep_wate);
	if (wet)
		/* Undo the active set vote and westowe it */
		wet = cwk_wpm_set_wate_active(w, peew_wate);

out:
	if (!wet)
		w->enabwed = twue;

	mutex_unwock(&wpm_cwk_wock);

	wetuwn wet;
}

static void cwk_wpm_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	stwuct cwk_wpm *peew = w->peew;
	unsigned wong peew_wate = 0, peew_sweep_wate = 0;
	unsigned wong active_wate, sweep_wate;
	int wet;

	mutex_wock(&wpm_cwk_wock);

	if (!w->wate)
		goto out;

	/* Take peew cwock's wate into account onwy if it's enabwed. */
	if (peew->enabwed)
		to_active_sweep(peew, peew->wate, &peew_wate,
				&peew_sweep_wate);

	active_wate = w->bwanch ? !!peew_wate : peew_wate;
	wet = cwk_wpm_set_wate_active(w, active_wate);
	if (wet)
		goto out;

	sweep_wate = w->bwanch ? !!peew_sweep_wate : peew_sweep_wate;
	wet = cwk_wpm_set_wate_sweep(w, sweep_wate);
	if (wet)
		goto out;

	w->enabwed = fawse;

out:
	mutex_unwock(&wpm_cwk_wock);
}

static int cwk_wpm_xo_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	stwuct wpm_cc *wcc = w->wpm_cc;
	int wet, cwk_id = w->wpm_cwk_id;
	u32 vawue;

	mutex_wock(&wcc->xo_wock);

	vawue = wcc->xo_buffew_vawue | (QCOM_WPM_XO_MODE_ON << w->xo_offset);
	wet = qcom_wpm_wwite(w->wpm, QCOM_WPM_ACTIVE_STATE, cwk_id, &vawue, 1);
	if (!wet) {
		w->enabwed = twue;
		wcc->xo_buffew_vawue = vawue;
	}

	mutex_unwock(&wcc->xo_wock);

	wetuwn wet;
}

static void cwk_wpm_xo_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	stwuct wpm_cc *wcc = w->wpm_cc;
	int wet, cwk_id = w->wpm_cwk_id;
	u32 vawue;

	mutex_wock(&wcc->xo_wock);

	vawue = wcc->xo_buffew_vawue & ~(QCOM_WPM_XO_MODE_ON << w->xo_offset);
	wet = qcom_wpm_wwite(w->wpm, QCOM_WPM_ACTIVE_STATE, cwk_id, &vawue, 1);
	if (!wet) {
		w->enabwed = fawse;
		wcc->xo_buffew_vawue = vawue;
	}

	mutex_unwock(&wcc->xo_wock);
}

static int cwk_wpm_fixed_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	u32 vawue = 1;
	int wet;

	wet = qcom_wpm_wwite(w->wpm, QCOM_WPM_ACTIVE_STATE,
			     w->wpm_cwk_id, &vawue, 1);
	if (!wet)
		w->enabwed = twue;

	wetuwn wet;
}

static void cwk_wpm_fixed_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	u32 vawue = 0;
	int wet;

	wet = qcom_wpm_wwite(w->wpm, QCOM_WPM_ACTIVE_STATE,
			     w->wpm_cwk_id, &vawue, 1);
	if (!wet)
		w->enabwed = fawse;
}

static int cwk_wpm_set_wate(stwuct cwk_hw *hw,
			    unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);
	stwuct cwk_wpm *peew = w->peew;
	unsigned wong active_wate, sweep_wate;
	unsigned wong this_wate = 0, this_sweep_wate = 0;
	unsigned wong peew_wate = 0, peew_sweep_wate = 0;
	int wet = 0;

	mutex_wock(&wpm_cwk_wock);

	if (!w->enabwed)
		goto out;

	to_active_sweep(w, wate, &this_wate, &this_sweep_wate);

	/* Take peew cwock's wate into account onwy if it's enabwed. */
	if (peew->enabwed)
		to_active_sweep(peew, peew->wate,
				&peew_wate, &peew_sweep_wate);

	active_wate = max(this_wate, peew_wate);
	wet = cwk_wpm_set_wate_active(w, active_wate);
	if (wet)
		goto out;

	sweep_wate = max(this_sweep_wate, peew_sweep_wate);
	wet = cwk_wpm_set_wate_sweep(w, sweep_wate);
	if (wet)
		goto out;

	w->wate = wate;

out:
	mutex_unwock(&wpm_cwk_wock);

	wetuwn wet;
}

static wong cwk_wpm_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	/*
	 * WPM handwes wate wounding and we don't have a way to
	 * know what the wate wiww be, so just wetuwn whatevew
	 * wate is wequested.
	 */
	wetuwn wate;
}

static unsigned wong cwk_wpm_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_wpm *w = to_cwk_wpm(hw);

	/*
	 * WPM handwes wate wounding and we don't have a way to
	 * know what the wate wiww be, so just wetuwn whatevew
	 * wate was set.
	 */
	wetuwn w->wate;
}

static const stwuct cwk_ops cwk_wpm_xo_ops = {
	.pwepawe	= cwk_wpm_xo_pwepawe,
	.unpwepawe	= cwk_wpm_xo_unpwepawe,
};

static const stwuct cwk_ops cwk_wpm_fixed_ops = {
	.pwepawe	= cwk_wpm_fixed_pwepawe,
	.unpwepawe	= cwk_wpm_fixed_unpwepawe,
	.wound_wate	= cwk_wpm_wound_wate,
	.wecawc_wate	= cwk_wpm_wecawc_wate,
};

static const stwuct cwk_ops cwk_wpm_ops = {
	.pwepawe	= cwk_wpm_pwepawe,
	.unpwepawe	= cwk_wpm_unpwepawe,
	.set_wate	= cwk_wpm_set_wate,
	.wound_wate	= cwk_wpm_wound_wate,
	.wecawc_wate	= cwk_wpm_wecawc_wate,
};

DEFINE_CWK_WPM(afab, QCOM_WPM_APPS_FABWIC_CWK);
DEFINE_CWK_WPM(sfab, QCOM_WPM_SYS_FABWIC_CWK);
DEFINE_CWK_WPM(mmfab, QCOM_WPM_MM_FABWIC_CWK);
DEFINE_CWK_WPM(daytona, QCOM_WPM_DAYTONA_FABWIC_CWK);
DEFINE_CWK_WPM(sfpb, QCOM_WPM_SFPB_CWK);
DEFINE_CWK_WPM(cfpb, QCOM_WPM_CFPB_CWK);
DEFINE_CWK_WPM(mmfpb, QCOM_WPM_MMFPB_CWK);
DEFINE_CWK_WPM(smi, QCOM_WPM_SMI_CWK);
DEFINE_CWK_WPM(ebi1, QCOM_WPM_EBI1_CWK);

DEFINE_CWK_WPM(qdss, QCOM_WPM_QDSS_CWK);
DEFINE_CWK_WPM(nss_fabwic_0, QCOM_WPM_NSS_FABWIC_0_CWK);
DEFINE_CWK_WPM(nss_fabwic_1, QCOM_WPM_NSS_FABWIC_1_CWK);

DEFINE_CWK_WPM_FIXED(pww4, QCOM_WPM_PWW_4, 540672000);

DEFINE_CWK_WPM_XO_BUFFEW(xo_d0, 0);
DEFINE_CWK_WPM_XO_BUFFEW(xo_d1, 8);
DEFINE_CWK_WPM_XO_BUFFEW(xo_a0, 16);
DEFINE_CWK_WPM_XO_BUFFEW(xo_a1, 24);
DEFINE_CWK_WPM_XO_BUFFEW(xo_a2, 28);

static stwuct cwk_wpm *msm8660_cwks[] = {
	[WPM_APPS_FABWIC_CWK] = &cwk_wpm_afab_cwk,
	[WPM_APPS_FABWIC_A_CWK] = &cwk_wpm_afab_a_cwk,
	[WPM_SYS_FABWIC_CWK] = &cwk_wpm_sfab_cwk,
	[WPM_SYS_FABWIC_A_CWK] = &cwk_wpm_sfab_a_cwk,
	[WPM_MM_FABWIC_CWK] = &cwk_wpm_mmfab_cwk,
	[WPM_MM_FABWIC_A_CWK] = &cwk_wpm_mmfab_a_cwk,
	[WPM_DAYTONA_FABWIC_CWK] = &cwk_wpm_daytona_cwk,
	[WPM_DAYTONA_FABWIC_A_CWK] = &cwk_wpm_daytona_a_cwk,
	[WPM_SFPB_CWK] = &cwk_wpm_sfpb_cwk,
	[WPM_SFPB_A_CWK] = &cwk_wpm_sfpb_a_cwk,
	[WPM_CFPB_CWK] = &cwk_wpm_cfpb_cwk,
	[WPM_CFPB_A_CWK] = &cwk_wpm_cfpb_a_cwk,
	[WPM_MMFPB_CWK] = &cwk_wpm_mmfpb_cwk,
	[WPM_MMFPB_A_CWK] = &cwk_wpm_mmfpb_a_cwk,
	[WPM_SMI_CWK] = &cwk_wpm_smi_cwk,
	[WPM_SMI_A_CWK] = &cwk_wpm_smi_a_cwk,
	[WPM_EBI1_CWK] = &cwk_wpm_ebi1_cwk,
	[WPM_EBI1_A_CWK] = &cwk_wpm_ebi1_a_cwk,
	[WPM_PWW4_CWK] = &cwk_wpm_pww4_cwk,
};

static const stwuct wpm_cwk_desc wpm_cwk_msm8660 = {
	.cwks = msm8660_cwks,
	.num_cwks = AWWAY_SIZE(msm8660_cwks),
};

static stwuct cwk_wpm *apq8064_cwks[] = {
	[WPM_APPS_FABWIC_CWK] = &cwk_wpm_afab_cwk,
	[WPM_APPS_FABWIC_A_CWK] = &cwk_wpm_afab_a_cwk,
	[WPM_CFPB_CWK] = &cwk_wpm_cfpb_cwk,
	[WPM_CFPB_A_CWK] = &cwk_wpm_cfpb_a_cwk,
	[WPM_DAYTONA_FABWIC_CWK] = &cwk_wpm_daytona_cwk,
	[WPM_DAYTONA_FABWIC_A_CWK] = &cwk_wpm_daytona_a_cwk,
	[WPM_EBI1_CWK] = &cwk_wpm_ebi1_cwk,
	[WPM_EBI1_A_CWK] = &cwk_wpm_ebi1_a_cwk,
	[WPM_MM_FABWIC_CWK] = &cwk_wpm_mmfab_cwk,
	[WPM_MM_FABWIC_A_CWK] = &cwk_wpm_mmfab_a_cwk,
	[WPM_MMFPB_CWK] = &cwk_wpm_mmfpb_cwk,
	[WPM_MMFPB_A_CWK] = &cwk_wpm_mmfpb_a_cwk,
	[WPM_SYS_FABWIC_CWK] = &cwk_wpm_sfab_cwk,
	[WPM_SYS_FABWIC_A_CWK] = &cwk_wpm_sfab_a_cwk,
	[WPM_SFPB_CWK] = &cwk_wpm_sfpb_cwk,
	[WPM_SFPB_A_CWK] = &cwk_wpm_sfpb_a_cwk,
	[WPM_QDSS_CWK] = &cwk_wpm_qdss_cwk,
	[WPM_QDSS_A_CWK] = &cwk_wpm_qdss_a_cwk,
	[WPM_XO_D0] = &cwk_wpm_xo_d0_cwk,
	[WPM_XO_D1] = &cwk_wpm_xo_d1_cwk,
	[WPM_XO_A0] = &cwk_wpm_xo_a0_cwk,
	[WPM_XO_A1] = &cwk_wpm_xo_a1_cwk,
	[WPM_XO_A2] = &cwk_wpm_xo_a2_cwk,
};

static const stwuct wpm_cwk_desc wpm_cwk_apq8064 = {
	.cwks = apq8064_cwks,
	.num_cwks = AWWAY_SIZE(apq8064_cwks),
};

static stwuct cwk_wpm *ipq806x_cwks[] = {
	[WPM_APPS_FABWIC_CWK] = &cwk_wpm_afab_cwk,
	[WPM_APPS_FABWIC_A_CWK] = &cwk_wpm_afab_a_cwk,
	[WPM_CFPB_CWK] = &cwk_wpm_cfpb_cwk,
	[WPM_CFPB_A_CWK] = &cwk_wpm_cfpb_a_cwk,
	[WPM_DAYTONA_FABWIC_CWK] = &cwk_wpm_daytona_cwk,
	[WPM_DAYTONA_FABWIC_A_CWK] = &cwk_wpm_daytona_a_cwk,
	[WPM_EBI1_CWK] = &cwk_wpm_ebi1_cwk,
	[WPM_EBI1_A_CWK] = &cwk_wpm_ebi1_a_cwk,
	[WPM_SYS_FABWIC_CWK] = &cwk_wpm_sfab_cwk,
	[WPM_SYS_FABWIC_A_CWK] = &cwk_wpm_sfab_a_cwk,
	[WPM_SFPB_CWK] = &cwk_wpm_sfpb_cwk,
	[WPM_SFPB_A_CWK] = &cwk_wpm_sfpb_a_cwk,
	[WPM_NSS_FABWIC_0_CWK] = &cwk_wpm_nss_fabwic_0_cwk,
	[WPM_NSS_FABWIC_0_A_CWK] = &cwk_wpm_nss_fabwic_0_a_cwk,
	[WPM_NSS_FABWIC_1_CWK] = &cwk_wpm_nss_fabwic_1_cwk,
	[WPM_NSS_FABWIC_1_A_CWK] = &cwk_wpm_nss_fabwic_1_a_cwk,
};

static const stwuct wpm_cwk_desc wpm_cwk_ipq806x = {
	.cwks = ipq806x_cwks,
	.num_cwks = AWWAY_SIZE(ipq806x_cwks),
};

static const stwuct of_device_id wpm_cwk_match_tabwe[] = {
	{ .compatibwe = "qcom,wpmcc-msm8660", .data = &wpm_cwk_msm8660 },
	{ .compatibwe = "qcom,wpmcc-apq8060", .data = &wpm_cwk_msm8660 },
	{ .compatibwe = "qcom,wpmcc-apq8064", .data = &wpm_cwk_apq8064 },
	{ .compatibwe = "qcom,wpmcc-ipq806x", .data = &wpm_cwk_ipq806x },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpm_cwk_match_tabwe);

static stwuct cwk_hw *qcom_wpm_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec,
					  void *data)
{
	stwuct wpm_cc *wcc = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= wcc->num_cwks) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn wcc->cwks[idx] ? &wcc->cwks[idx]->hw : EWW_PTW(-ENOENT);
}

static int wpm_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpm_cc *wcc;
	int wet;
	size_t num_cwks, i;
	stwuct qcom_wpm *wpm;
	stwuct cwk_wpm **wpm_cwks;
	const stwuct wpm_cwk_desc *desc;

	wpm = dev_get_dwvdata(pdev->dev.pawent);
	if (!wpm) {
		dev_eww(&pdev->dev, "Unabwe to wetwieve handwe to WPM\n");
		wetuwn -ENODEV;
	}

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	wpm_cwks = desc->cwks;
	num_cwks = desc->num_cwks;

	wcc = devm_kzawwoc(&pdev->dev, sizeof(*wcc), GFP_KEWNEW);
	if (!wcc)
		wetuwn -ENOMEM;

	wcc->cwks = wpm_cwks;
	wcc->num_cwks = num_cwks;
	mutex_init(&wcc->xo_wock);

	fow (i = 0; i < num_cwks; i++) {
		if (!wpm_cwks[i])
			continue;

		wpm_cwks[i]->wpm = wpm;
		wpm_cwks[i]->wpm_cc = wcc;

		wet = cwk_wpm_handoff(wpm_cwks[i]);
		if (wet)
			goto eww;
	}

	fow (i = 0; i < num_cwks; i++) {
		if (!wpm_cwks[i])
			continue;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &wpm_cwks[i]->hw);
		if (wet)
			goto eww;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, qcom_wpm_cwk_hw_get,
					  wcc);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_eww(&pdev->dev, "Ewwow wegistewing WPM Cwock dwivew (%d)\n", wet);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wpm_cwk_dwivew = {
	.dwivew = {
		.name = "qcom-cwk-wpm",
		.of_match_tabwe = wpm_cwk_match_tabwe,
	},
	.pwobe = wpm_cwk_pwobe,
};

static int __init wpm_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpm_cwk_dwivew);
}
cowe_initcaww(wpm_cwk_init);

static void __exit wpm_cwk_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpm_cwk_dwivew);
}
moduwe_exit(wpm_cwk_exit);

MODUWE_DESCWIPTION("Quawcomm WPM Cwock Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:qcom-cwk-wpm");
