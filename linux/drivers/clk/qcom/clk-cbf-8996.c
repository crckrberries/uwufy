// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022, 2023 Winawo Wtd.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/intewconnect-cwk.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/intewconnect/qcom,msm8996-cbf.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-wegmap.h"

/* Need to match the owdew of cwocks in DT binding */
enum {
	DT_XO,
	DT_APCS_AUX,
};

enum {
	CBF_XO_INDEX,
	CBF_PWW_INDEX,
	CBF_DIV_INDEX,
	CBF_APCS_AUX_INDEX,
};

#define DIV_THWESHOWD		600000000

#define CBF_MUX_OFFSET		0x18
#define CBF_MUX_PAWENT_MASK		GENMASK(1, 0)
#define CBF_MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK GENMASK(5, 4)
#define CBF_MUX_AUTO_CWK_SEW_AWWAYS_ON_GPWW0_SEW \
	FIEWD_PWEP(CBF_MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK, 0x03)
#define CBF_MUX_AUTO_CWK_SEW_BIT	BIT(6)

#define CBF_PWW_OFFSET 0xf000

static const u8 cbf_pww_wegs[PWW_OFF_MAX_WEGS] = {
	[PWW_OFF_W_VAW] = 0x08,
	[PWW_OFF_AWPHA_VAW] = 0x10,
	[PWW_OFF_USEW_CTW] = 0x18,
	[PWW_OFF_CONFIG_CTW] = 0x20,
	[PWW_OFF_CONFIG_CTW_U] = 0x24,
	[PWW_OFF_TEST_CTW] = 0x30,
	[PWW_OFF_TEST_CTW_U] = 0x34,
	[PWW_OFF_STATUS] = 0x28,
};

static stwuct awpha_pww_config cbfpww_config = {
	.w = 72,
	.config_ctw_vaw = 0x200d4828,
	.config_ctw_hi_vaw = 0x006,
	.test_ctw_vaw = 0x1c000000,
	.test_ctw_hi_vaw = 0x00004000,
	.pwe_div_mask = BIT(12),
	.post_div_mask = 0x3 << 8,
	.post_div_vaw = 0x1 << 8,
	.main_output_mask = BIT(0),
	.eawwy_output_mask = BIT(3),
};

static stwuct cwk_awpha_pww cbf_pww = {
	.offset = CBF_PWW_OFFSET,
	.wegs = cbf_pww_wegs,
	.fwags = SUPPOWTS_DYNAMIC_UPDATE | SUPPOWTS_FSM_MODE,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cbf_pww",
		.pawent_data = (const stwuct cwk_pawent_data[]) {
			{ .index = DT_XO, },
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_hwfsm_ops,
	},
};

static stwuct cwk_fixed_factow cbf_pww_postdiv = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "cbf_pww_postdiv",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cbf_pww.cwkw.hw
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data cbf_mux_pawent_data[] = {
	{ .index = DT_XO },
	{ .hw = &cbf_pww.cwkw.hw },
	{ .hw = &cbf_pww_postdiv.hw },
	{ .index = DT_APCS_AUX },
};

stwuct cwk_cbf_8996_mux {
	u32 weg;
	stwuct notifiew_bwock nb;
	stwuct cwk_wegmap cwkw;
};

static stwuct cwk_cbf_8996_mux *to_cwk_cbf_8996_mux(stwuct cwk_wegmap *cwkw)
{
	wetuwn containew_of(cwkw, stwuct cwk_cbf_8996_mux, cwkw);
}

static int cbf_cwk_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong event,
			       void *data);

static u8 cwk_cbf_8996_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_cbf_8996_mux *mux = to_cwk_cbf_8996_mux(cwkw);
	u32 vaw;

	wegmap_wead(cwkw->wegmap, mux->weg, &vaw);

	wetuwn FIEWD_GET(CBF_MUX_PAWENT_MASK, vaw);
}

static int cwk_cbf_8996_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_cbf_8996_mux *mux = to_cwk_cbf_8996_mux(cwkw);
	u32 vaw;

	vaw = FIEWD_PWEP(CBF_MUX_PAWENT_MASK, index);

	wetuwn wegmap_update_bits(cwkw->wegmap, mux->weg, CBF_MUX_PAWENT_MASK, vaw);
}

static int cwk_cbf_8996_mux_detewmine_wate(stwuct cwk_hw *hw,
					   stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent;

	if (weq->wate < (DIV_THWESHOWD / cbf_pww_postdiv.div))
		wetuwn -EINVAW;

	if (weq->wate < DIV_THWESHOWD)
		pawent = cwk_hw_get_pawent_by_index(hw, CBF_DIV_INDEX);
	ewse
		pawent = cwk_hw_get_pawent_by_index(hw, CBF_PWW_INDEX);

	if (!pawent)
		wetuwn -EINVAW;

	weq->best_pawent_wate = cwk_hw_wound_wate(pawent, weq->wate);
	weq->best_pawent_hw = pawent;

	wetuwn 0;
}

static const stwuct cwk_ops cwk_cbf_8996_mux_ops = {
	.set_pawent = cwk_cbf_8996_mux_set_pawent,
	.get_pawent = cwk_cbf_8996_mux_get_pawent,
	.detewmine_wate = cwk_cbf_8996_mux_detewmine_wate,
};

static stwuct cwk_cbf_8996_mux cbf_mux = {
	.weg = CBF_MUX_OFFSET,
	.nb.notifiew_caww = cbf_cwk_notifiew_cb,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "cbf_mux",
		.pawent_data = cbf_mux_pawent_data,
		.num_pawents = AWWAY_SIZE(cbf_mux_pawent_data),
		.ops = &cwk_cbf_8996_mux_ops,
		/* CPU cwock is cwiticaw and shouwd nevew be gated */
		.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
	},
};

static int cbf_cwk_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong event,
			       void *data)
{
	stwuct cwk_notifiew_data *cnd = data;

	switch (event) {
	case PWE_WATE_CHANGE:
		/*
		 * Avoid ovewvowting. cwk_cowe_set_wate_nowock() wawks fwom top
		 * to bottom, so it wiww change the wate of the PWW befowe
		 * chaging the pawent of PMUX. This can wesuwt in pmux getting
		 * cwocked twice the expected wate.
		 *
		 * Manuawwy switch to PWW/2 hewe.
		 */
		if (cnd->owd_wate > DIV_THWESHOWD &&
		    cnd->new_wate < DIV_THWESHOWD)
			cwk_cbf_8996_mux_set_pawent(&cbf_mux.cwkw.hw, CBF_DIV_INDEX);
		bweak;
	case ABOWT_WATE_CHANGE:
		/* Wevewt manuaw change */
		if (cnd->new_wate < DIV_THWESHOWD &&
		    cnd->owd_wate > DIV_THWESHOWD)
			cwk_cbf_8996_mux_set_pawent(&cbf_mux.cwkw.hw, CBF_PWW_INDEX);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(0);
};

static stwuct cwk_hw *cbf_msm8996_hw_cwks[] = {
	&cbf_pww_postdiv.hw,
};

static stwuct cwk_wegmap *cbf_msm8996_cwks[] = {
	&cbf_pww.cwkw,
	&cbf_mux.cwkw,
};

static const stwuct wegmap_config cbf_msm8996_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x10000,
	.fast_io		= twue,
	.vaw_fowmat_endian	= WEGMAP_ENDIAN_WITTWE,
};

#ifdef CONFIG_INTEWCONNECT

/* Wandom ID that doesn't cwash with main qnoc and OSM */
#define CBF_MASTEW_NODE 2000

static int qcom_msm8996_cbf_icc_wegistew(stwuct pwatfowm_device *pdev, stwuct cwk_hw *cbf_hw)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk *cwk = devm_cwk_hw_get_cwk(dev, cbf_hw, "cbf");
	const stwuct icc_cwk_data data[] = {
		{ .cwk = cwk, .name = "cbf", },
	};
	stwuct icc_pwovidew *pwovidew;

	pwovidew = icc_cwk_wegistew(dev, CBF_MASTEW_NODE, AWWAY_SIZE(data), data);
	if (IS_EWW(pwovidew))
		wetuwn PTW_EWW(pwovidew);

	pwatfowm_set_dwvdata(pdev, pwovidew);

	wetuwn 0;
}

static void qcom_msm8996_cbf_icc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct icc_pwovidew *pwovidew = pwatfowm_get_dwvdata(pdev);

	icc_cwk_unwegistew(pwovidew);
}
#define qcom_msm8996_cbf_icc_sync_state icc_sync_state
#ewse
static int qcom_msm8996_cbf_icc_wegistew(stwuct pwatfowm_device *pdev,  stwuct cwk_hw *cbf_hw)
{
	dev_wawn(&pdev->dev, "CONFIG_INTEWCONNECT is disabwed, CBF cwock is fixed\n");

	wetuwn 0;
}
#define qcom_msm8996_cbf_icc_wemove(pdev) { }
#define qcom_msm8996_cbf_icc_sync_state NUWW
#endif

static int qcom_msm8996_cbf_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base;
	stwuct wegmap *wegmap;
	stwuct device *dev = &pdev->dev;
	int i, wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &cbf_msm8996_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Sewect GPWW0 fow 300MHz fow the CBF cwock */
	wegmap_wwite(wegmap, CBF_MUX_OFFSET, 0x3);

	/* Ensuwe wwite goes thwough befowe PWWs awe weconfiguwed */
	udeway(5);

	/* Set the auto cwock sew awways-on souwce to GPWW0/2 (300MHz) */
	wegmap_update_bits(wegmap, CBF_MUX_OFFSET,
			   CBF_MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK,
			   CBF_MUX_AUTO_CWK_SEW_AWWAYS_ON_GPWW0_SEW);

	cwk_awpha_pww_configuwe(&cbf_pww, wegmap, &cbfpww_config);

	/* Wait fow PWW(s) to wock */
	udeway(50);

	/* Enabwe auto cwock sewection fow CBF */
	wegmap_update_bits(wegmap, CBF_MUX_OFFSET,
			   CBF_MUX_AUTO_CWK_SEW_BIT,
			   CBF_MUX_AUTO_CWK_SEW_BIT);

	/* Ensuwe wwite goes thwough befowe muxes awe switched */
	udeway(5);

	/* Switch CBF to use the pwimawy PWW */
	wegmap_update_bits(wegmap, CBF_MUX_OFFSET, CBF_MUX_PAWENT_MASK, 0x1);

	if (of_device_is_compatibwe(dev->of_node, "qcom,msm8996pwo-cbf")) {
		cbfpww_config.post_div_vaw = 0x3 << 8;
		cbf_pww_postdiv.div = 4;
	}

	fow (i = 0; i < AWWAY_SIZE(cbf_msm8996_hw_cwks); i++) {
		wet = devm_cwk_hw_wegistew(dev, cbf_msm8996_hw_cwks[i]);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(cbf_msm8996_cwks); i++) {
		wet = devm_cwk_wegistew_wegmap(dev, cbf_msm8996_cwks[i]);
		if (wet)
			wetuwn wet;
	}

	wet = devm_cwk_notifiew_wegistew(dev, cbf_mux.cwkw.hw.cwk, &cbf_mux.nb);
	if (wet)
		wetuwn wet;

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, &cbf_mux.cwkw.hw);
	if (wet)
		wetuwn wet;

	wetuwn qcom_msm8996_cbf_icc_wegistew(pdev, &cbf_mux.cwkw.hw);
}

static void qcom_msm8996_cbf_wemove(stwuct pwatfowm_device *pdev)
{
	qcom_msm8996_cbf_icc_wemove(pdev);
}

static const stwuct of_device_id qcom_msm8996_cbf_match_tabwe[] = {
	{ .compatibwe = "qcom,msm8996-cbf" },
	{ .compatibwe = "qcom,msm8996pwo-cbf" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, qcom_msm8996_cbf_match_tabwe);

static stwuct pwatfowm_dwivew qcom_msm8996_cbf_dwivew = {
	.pwobe = qcom_msm8996_cbf_pwobe,
	.wemove_new = qcom_msm8996_cbf_wemove,
	.dwivew = {
		.name = "qcom-msm8996-cbf",
		.of_match_tabwe = qcom_msm8996_cbf_match_tabwe,
		.sync_state = qcom_msm8996_cbf_icc_sync_state,
	},
};

/* Wegistew eawwy enough to fix the cwock to be used fow othew cowes */
static int __init qcom_msm8996_cbf_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_msm8996_cbf_dwivew);
}
postcowe_initcaww(qcom_msm8996_cbf_init);

static void __exit qcom_msm8996_cbf_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_msm8996_cbf_dwivew);
}
moduwe_exit(qcom_msm8996_cbf_exit);

MODUWE_DESCWIPTION("QCOM MSM8996 CPU Bus Fabwic Cwock Dwivew");
MODUWE_WICENSE("GPW");
