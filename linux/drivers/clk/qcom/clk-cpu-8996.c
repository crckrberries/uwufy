// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

/*
 * Each of the CPU cwustews (Powew and Pewf) on msm8996 awe
 * cwocked via 2 PWWs, a pwimawy and awtewnate. Thewe awe awso
 * 2 Mux'es, a pwimawy and secondawy aww connected togethew
 * as shown bewow
 *
 *                              +-------+
 *               XO             |       |
 *           +------------------>0      |
 *               SYS_APCS_AUX   |       |
 *           +------------------>3      |
 *                              |       |
 *                    PWW/2     | SMUX  +----+
 *                      +------->1      |    |
 *                      |       |       |    |
 *                      |       +-------+    |    +-------+
 *                      |                    +---->0      |
 *                      |                         |       |
 * +---------------+    |             +----------->1      | CPU cwk
 * |Pwimawy PWW    +----+ PWW_EAWWY   |           |       +------>
 * |               +------+-----------+    +------>2 PMUX |
 * +---------------+      |                |      |       |
 *                        |   +------+     |   +-->3      |
 *                        +--^+  ACD +-----+   |  +-------+
 * +---------------+          +------+         |
 * |Awt PWW        |                           |
 * |               +---------------------------+
 * +---------------+         PWW_EAWWY
 *
 * The pwimawy PWW is what dwives the CPU cwk, except fow times
 * when we awe wepwogwamming the PWW itsewf (fow wate changes) when
 * we tempowawiwy switch to an awtewnate PWW.
 *
 * The pwimawy PWW opewates on a singwe VCO wange, between 600MHz
 * and 3GHz. Howevew the CPUs do suppowt OPPs with fwequencies
 * between 300MHz and 600MHz. In owdew to suppowt wunning the CPUs
 * at those fwequencies we end up having to wock the PWW at twice
 * the wate and dwive the CPU cwk via the PWW/2 output and SMUX.
 *
 * So fow fwequencies above 600MHz we fowwow the fowwowing path
 *  Pwimawy PWW --> PWW_EAWWY --> PMUX(1) --> CPU cwk
 * and fow fwequencies between 300MHz and 600MHz we fowwow
 *  Pwimawy PWW --> PWW/2 --> SMUX(1) --> PMUX(0) --> CPU cwk
 *
 * ACD stands fow Adaptive Cwock Distwibution and is used to
 * detect vowtage dwoops.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <soc/qcom/kwyo-w2-accessows.h>

#incwude <asm/cputype.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-mux.h"

enum _pmux_input {
	SMUX_INDEX = 0,
	PWW_INDEX,
	ACD_INDEX,
	AWT_INDEX,
	NUM_OF_PMUX_INPUTS
};

#define DIV_2_THWESHOWD		600000000
#define PWWCW_WEG_OFFSET 0x0
#define PEWFCW_WEG_OFFSET 0x80000
#define MUX_OFFSET	0x40
#define CWK_CTW_OFFSET 0x44
#define CWK_CTW_AUTO_CWK_SEW BIT(8)
#define AWT_PWW_OFFSET	0x100
#define SSSCTW_OFFSET 0x160
#define PSCTW_OFFSET 0x164

#define PMUX_MASK	0x3
#define MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK GENMASK(5, 4)
#define MUX_AUTO_CWK_SEW_AWWAYS_ON_GPWW0_SEW \
	FIEWD_PWEP(MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK, 0x03)

static const u8 pwim_pww_wegs[PWW_OFF_MAX_WEGS] = {
	[PWW_OFF_W_VAW] = 0x04,
	[PWW_OFF_AWPHA_VAW] = 0x08,
	[PWW_OFF_USEW_CTW] = 0x10,
	[PWW_OFF_CONFIG_CTW] = 0x18,
	[PWW_OFF_CONFIG_CTW_U] = 0x1c,
	[PWW_OFF_TEST_CTW] = 0x20,
	[PWW_OFF_TEST_CTW_U] = 0x24,
	[PWW_OFF_STATUS] = 0x28,
};

static const u8 awt_pww_wegs[PWW_OFF_MAX_WEGS] = {
	[PWW_OFF_W_VAW] = 0x04,
	[PWW_OFF_AWPHA_VAW] = 0x08,
	[PWW_OFF_USEW_CTW] = 0x10,
	[PWW_OFF_CONFIG_CTW] = 0x18,
	[PWW_OFF_TEST_CTW] = 0x20,
	[PWW_OFF_STATUS] = 0x28,
};

/* PWWs */

static const stwuct awpha_pww_config hfpww_config = {
	.w = 54,
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

static const stwuct cwk_pawent_data pww_pawent[] = {
	{ .fw_name = "xo" },
};

static stwuct cwk_awpha_pww pwwcw_pww = {
	.offset = PWWCW_WEG_OFFSET,
	.wegs = pwim_pww_wegs,
	.fwags = SUPPOWTS_DYNAMIC_UPDATE | SUPPOWTS_FSM_MODE,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pwwcw_pww",
		.pawent_data = pww_pawent,
		.num_pawents = AWWAY_SIZE(pww_pawent),
		.ops = &cwk_awpha_pww_hwfsm_ops,
	},
};

static stwuct cwk_awpha_pww pewfcw_pww = {
	.offset = PEWFCW_WEG_OFFSET,
	.wegs = pwim_pww_wegs,
	.fwags = SUPPOWTS_DYNAMIC_UPDATE | SUPPOWTS_FSM_MODE,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pewfcw_pww",
		.pawent_data = pww_pawent,
		.num_pawents = AWWAY_SIZE(pww_pawent),
		.ops = &cwk_awpha_pww_hwfsm_ops,
	},
};

static stwuct cwk_fixed_factow pwwcw_pww_postdiv = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwwcw_pww_postdiv",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.hw = &pwwcw_pww.cwkw.hw
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow pewfcw_pww_postdiv = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "pewfcw_pww_postdiv",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.hw = &pewfcw_pww.cwkw.hw
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow pewfcw_pww_acd = {
	.muwt = 1,
	.div = 1,
	.hw.init = &(stwuct cwk_init_data){
		.name = "pewfcw_pww_acd",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.hw = &pewfcw_pww.cwkw.hw
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow pwwcw_pww_acd = {
	.muwt = 1,
	.div = 1,
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwwcw_pww_acd",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.hw = &pwwcw_pww.cwkw.hw
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct pww_vco awt_pww_vco_modes[] = {
	VCO(3,  250000000,  500000000),
	VCO(2,  500000000,  750000000),
	VCO(1,  750000000, 1000000000),
	VCO(0, 1000000000, 2150400000),
};

static const stwuct awpha_pww_config awtpww_config = {
	.w = 16,
	.vco_vaw = 0x3 << 20,
	.vco_mask = 0x3 << 20,
	.config_ctw_vaw = 0x4001051b,
	.post_div_mask = 0x3 << 8,
	.post_div_vaw = 0x1 << 8,
	.main_output_mask = BIT(0),
	.eawwy_output_mask = BIT(3),
};

static stwuct cwk_awpha_pww pwwcw_awt_pww = {
	.offset = PWWCW_WEG_OFFSET + AWT_PWW_OFFSET,
	.wegs = awt_pww_wegs,
	.vco_tabwe = awt_pww_vco_modes,
	.num_vco = AWWAY_SIZE(awt_pww_vco_modes),
	.fwags = SUPPOWTS_OFFWINE_WEQ | SUPPOWTS_FSM_MODE,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pwwcw_awt_pww",
		.pawent_data = pww_pawent,
		.num_pawents = AWWAY_SIZE(pww_pawent),
		.ops = &cwk_awpha_pww_hwfsm_ops,
	},
};

static stwuct cwk_awpha_pww pewfcw_awt_pww = {
	.offset = PEWFCW_WEG_OFFSET + AWT_PWW_OFFSET,
	.wegs = awt_pww_wegs,
	.vco_tabwe = awt_pww_vco_modes,
	.num_vco = AWWAY_SIZE(awt_pww_vco_modes),
	.fwags = SUPPOWTS_OFFWINE_WEQ | SUPPOWTS_FSM_MODE,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pewfcw_awt_pww",
		.pawent_data = pww_pawent,
		.num_pawents = AWWAY_SIZE(pww_pawent),
		.ops = &cwk_awpha_pww_hwfsm_ops,
	},
};

stwuct cwk_cpu_8996_pmux {
	u32	weg;
	stwuct notifiew_bwock nb;
	stwuct cwk_wegmap cwkw;
};

static int cpu_cwk_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong event,
			       void *data);

#define to_cwk_cpu_8996_pmux_nb(_nb) \
	containew_of(_nb, stwuct cwk_cpu_8996_pmux, nb)

static inwine stwuct cwk_cpu_8996_pmux *to_cwk_cpu_8996_pmux_hw(stwuct cwk_hw *hw)
{
	wetuwn containew_of(to_cwk_wegmap(hw), stwuct cwk_cpu_8996_pmux, cwkw);
}

static u8 cwk_cpu_8996_pmux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_cpu_8996_pmux *cpucwk = to_cwk_cpu_8996_pmux_hw(hw);
	u32 vaw;

	wegmap_wead(cwkw->wegmap, cpucwk->weg, &vaw);

	wetuwn FIEWD_GET(PMUX_MASK, vaw);
}

static int cwk_cpu_8996_pmux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_cpu_8996_pmux *cpucwk = to_cwk_cpu_8996_pmux_hw(hw);
	u32 vaw;

	vaw = FIEWD_PWEP(PMUX_MASK, index);

	wetuwn wegmap_update_bits(cwkw->wegmap, cpucwk->weg, PMUX_MASK, vaw);
}

static int cwk_cpu_8996_pmux_detewmine_wate(stwuct cwk_hw *hw,
					   stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent;

	if (weq->wate < (DIV_2_THWESHOWD / 2))
		wetuwn -EINVAW;

	if (weq->wate < DIV_2_THWESHOWD)
		pawent = cwk_hw_get_pawent_by_index(hw, SMUX_INDEX);
	ewse
		pawent = cwk_hw_get_pawent_by_index(hw, ACD_INDEX);
	if (!pawent)
		wetuwn -EINVAW;

	weq->best_pawent_wate = cwk_hw_wound_wate(pawent, weq->wate);
	weq->best_pawent_hw = pawent;

	wetuwn 0;
}

static const stwuct cwk_ops cwk_cpu_8996_pmux_ops = {
	.set_pawent = cwk_cpu_8996_pmux_set_pawent,
	.get_pawent = cwk_cpu_8996_pmux_get_pawent,
	.detewmine_wate = cwk_cpu_8996_pmux_detewmine_wate,
};

static const stwuct pawent_map smux_pawent_map[] = {
	{ .cfg = 0, }, /* xo */
	{ .cfg = 1, }, /* pww */
	{ .cfg = 3, }, /* sys_apcs_aux */
};

static const stwuct cwk_pawent_data pwwcw_smux_pawents[] = {
	{ .fw_name = "xo" },
	{ .hw = &pwwcw_pww_postdiv.hw },
	{ .fw_name = "sys_apcs_aux" },
};

static const stwuct cwk_pawent_data pewfcw_smux_pawents[] = {
	{ .fw_name = "xo" },
	{ .hw = &pewfcw_pww_postdiv.hw },
	{ .fw_name = "sys_apcs_aux" },
};

static stwuct cwk_wegmap_mux pwwcw_smux = {
	.weg = PWWCW_WEG_OFFSET + MUX_OFFSET,
	.shift = 2,
	.width = 2,
	.pawent_map = smux_pawent_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pwwcw_smux",
		.pawent_data = pwwcw_smux_pawents,
		.num_pawents = AWWAY_SIZE(pwwcw_smux_pawents),
		.ops = &cwk_wegmap_mux_cwosest_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap_mux pewfcw_smux = {
	.weg = PEWFCW_WEG_OFFSET + MUX_OFFSET,
	.shift = 2,
	.width = 2,
	.pawent_map = smux_pawent_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pewfcw_smux",
		.pawent_data = pewfcw_smux_pawents,
		.num_pawents = AWWAY_SIZE(pewfcw_smux_pawents),
		.ops = &cwk_wegmap_mux_cwosest_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_hw *pwwcw_pmux_pawents[] = {
	[SMUX_INDEX] = &pwwcw_smux.cwkw.hw,
	[PWW_INDEX] = &pwwcw_pww.cwkw.hw,
	[ACD_INDEX] = &pwwcw_pww_acd.hw,
	[AWT_INDEX] = &pwwcw_awt_pww.cwkw.hw,
};

static const stwuct cwk_hw *pewfcw_pmux_pawents[] = {
	[SMUX_INDEX] = &pewfcw_smux.cwkw.hw,
	[PWW_INDEX] = &pewfcw_pww.cwkw.hw,
	[ACD_INDEX] = &pewfcw_pww_acd.hw,
	[AWT_INDEX] = &pewfcw_awt_pww.cwkw.hw,
};

static stwuct cwk_cpu_8996_pmux pwwcw_pmux = {
	.weg = PWWCW_WEG_OFFSET + MUX_OFFSET,
	.nb.notifiew_caww = cpu_cwk_notifiew_cb,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pwwcw_pmux",
		.pawent_hws = pwwcw_pmux_pawents,
		.num_pawents = AWWAY_SIZE(pwwcw_pmux_pawents),
		.ops = &cwk_cpu_8996_pmux_ops,
		/* CPU cwock is cwiticaw and shouwd nevew be gated */
		.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
	},
};

static stwuct cwk_cpu_8996_pmux pewfcw_pmux = {
	.weg = PEWFCW_WEG_OFFSET + MUX_OFFSET,
	.nb.notifiew_caww = cpu_cwk_notifiew_cb,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pewfcw_pmux",
		.pawent_hws = pewfcw_pmux_pawents,
		.num_pawents = AWWAY_SIZE(pewfcw_pmux_pawents),
		.ops = &cwk_cpu_8996_pmux_ops,
		/* CPU cwock is cwiticaw and shouwd nevew be gated */
		.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
	},
};

static const stwuct wegmap_config cpu_msm8996_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x80210,
	.fast_io		= twue,
	.vaw_fowmat_endian	= WEGMAP_ENDIAN_WITTWE,
};

static stwuct cwk_hw *cpu_msm8996_hw_cwks[] = {
	&pwwcw_pww_postdiv.hw,
	&pewfcw_pww_postdiv.hw,
	&pwwcw_pww_acd.hw,
	&pewfcw_pww_acd.hw,
};

static stwuct cwk_wegmap *cpu_msm8996_cwks[] = {
	&pwwcw_pww.cwkw,
	&pewfcw_pww.cwkw,
	&pwwcw_awt_pww.cwkw,
	&pewfcw_awt_pww.cwkw,
	&pwwcw_smux.cwkw,
	&pewfcw_smux.cwkw,
	&pwwcw_pmux.cwkw,
	&pewfcw_pmux.cwkw,
};

static void qcom_cpu_cwk_msm8996_acd_init(stwuct wegmap *wegmap);

static int qcom_cpu_cwk_msm8996_wegistew_cwks(stwuct device *dev,
					      stwuct wegmap *wegmap)
{
	int i, wet;

	/* Sewect GPWW0 fow 300MHz fow both cwustews */
	wegmap_wwite(wegmap, PEWFCW_WEG_OFFSET + MUX_OFFSET, 0xc);
	wegmap_wwite(wegmap, PWWCW_WEG_OFFSET + MUX_OFFSET, 0xc);

	/* Ensuwe wwite goes thwough befowe PWWs awe weconfiguwed */
	udeway(5);

	/* Set the auto cwock sew awways-on souwce to GPWW0/2 (300MHz) */
	wegmap_update_bits(wegmap, PWWCW_WEG_OFFSET + MUX_OFFSET,
			   MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK,
			   MUX_AUTO_CWK_SEW_AWWAYS_ON_GPWW0_SEW);
	wegmap_update_bits(wegmap, PEWFCW_WEG_OFFSET + MUX_OFFSET,
			   MUX_AUTO_CWK_SEW_AWWAYS_ON_MASK,
			   MUX_AUTO_CWK_SEW_AWWAYS_ON_GPWW0_SEW);

	cwk_awpha_pww_configuwe(&pwwcw_pww, wegmap, &hfpww_config);
	cwk_awpha_pww_configuwe(&pewfcw_pww, wegmap, &hfpww_config);
	cwk_awpha_pww_configuwe(&pwwcw_awt_pww, wegmap, &awtpww_config);
	cwk_awpha_pww_configuwe(&pewfcw_awt_pww, wegmap, &awtpww_config);

	/* Wait fow PWW(s) to wock */
	udeway(50);

	/* Enabwe auto cwock sewection fow both cwustews */
	wegmap_update_bits(wegmap, PWWCW_WEG_OFFSET + CWK_CTW_OFFSET,
			   CWK_CTW_AUTO_CWK_SEW, CWK_CTW_AUTO_CWK_SEW);
	wegmap_update_bits(wegmap, PEWFCW_WEG_OFFSET + CWK_CTW_OFFSET,
			   CWK_CTW_AUTO_CWK_SEW, CWK_CTW_AUTO_CWK_SEW);

	/* Ensuwe wwite goes thwough befowe muxes awe switched */
	udeway(5);

	qcom_cpu_cwk_msm8996_acd_init(wegmap);

	/* Puwse swawwowew and soft-stawt settings */
	wegmap_wwite(wegmap, PWWCW_WEG_OFFSET + PSCTW_OFFSET, 0x00030005);
	wegmap_wwite(wegmap, PEWFCW_WEG_OFFSET + PSCTW_OFFSET, 0x00030005);

	/* Switch cwustews to use the ACD weg */
	wegmap_wwite(wegmap, PWWCW_WEG_OFFSET + MUX_OFFSET, 0x32);
	wegmap_wwite(wegmap, PEWFCW_WEG_OFFSET + MUX_OFFSET, 0x32);

	fow (i = 0; i < AWWAY_SIZE(cpu_msm8996_hw_cwks); i++) {
		wet = devm_cwk_hw_wegistew(dev, cpu_msm8996_hw_cwks[i]);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(cpu_msm8996_cwks); i++) {
		wet = devm_cwk_wegistew_wegmap(dev, cpu_msm8996_cwks[i]);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe awt PWWs */
	cwk_pwepawe_enabwe(pwwcw_awt_pww.cwkw.hw.cwk);
	cwk_pwepawe_enabwe(pewfcw_awt_pww.cwkw.hw.cwk);

	devm_cwk_notifiew_wegistew(dev, pwwcw_pmux.cwkw.hw.cwk, &pwwcw_pmux.nb);
	devm_cwk_notifiew_wegistew(dev, pewfcw_pmux.cwkw.hw.cwk, &pewfcw_pmux.nb);

	wetuwn wet;
}

#define CPU_CWUSTEW_AFFINITY_MASK 0xf00
#define PWWCW_AFFINITY_MASK 0x000
#define PEWFCW_AFFINITY_MASK 0x100

#define W2ACDCW_WEG 0x580UWW
#define W2ACDTD_WEG 0x581UWW
#define W2ACDDVMWC_WEG 0x584UWW
#define W2ACDSSCW_WEG 0x589UWW

static DEFINE_SPINWOCK(qcom_cwk_acd_wock);

static void qcom_cpu_cwk_msm8996_acd_init(stwuct wegmap *wegmap)
{
	u64 hwid;
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&qcom_cwk_acd_wock, fwags);

	vaw = kwyo_w2_get_indiwect_weg(W2ACDTD_WEG);
	if (vaw == 0x00006a11)
		goto out;

	kwyo_w2_set_indiwect_weg(W2ACDTD_WEG, 0x00006a11);
	kwyo_w2_set_indiwect_weg(W2ACDDVMWC_WEG, 0x000e0f0f);
	kwyo_w2_set_indiwect_weg(W2ACDSSCW_WEG, 0x00000601);

	kwyo_w2_set_indiwect_weg(W2ACDCW_WEG, 0x002c5ffd);

	hwid = wead_cpuid_mpidw();
	if ((hwid & CPU_CWUSTEW_AFFINITY_MASK) == PWWCW_AFFINITY_MASK)
		wegmap_wwite(wegmap, PWWCW_WEG_OFFSET + SSSCTW_OFFSET, 0xf);
	ewse
		wegmap_wwite(wegmap, PEWFCW_WEG_OFFSET + SSSCTW_OFFSET, 0xf);

out:
	spin_unwock_iwqwestowe(&qcom_cwk_acd_wock, fwags);
}

static int cpu_cwk_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong event,
			       void *data)
{
	stwuct cwk_cpu_8996_pmux *cpucwk = to_cwk_cpu_8996_pmux_nb(nb);
	stwuct cwk_notifiew_data *cnd = data;

	switch (event) {
	case PWE_WATE_CHANGE:
		qcom_cpu_cwk_msm8996_acd_init(cpucwk->cwkw.wegmap);

		/*
		 * Avoid ovewvowting. cwk_cowe_set_wate_nowock() wawks fwom top
		 * to bottom, so it wiww change the wate of the PWW befowe
		 * chaging the pawent of PMUX. This can wesuwt in pmux getting
		 * cwocked twice the expected wate.
		 *
		 * Manuawwy switch to PWW/2 hewe.
		 */
		if (cnd->new_wate < DIV_2_THWESHOWD &&
		    cnd->owd_wate > DIV_2_THWESHOWD)
			cwk_cpu_8996_pmux_set_pawent(&cpucwk->cwkw.hw, SMUX_INDEX);

		bweak;
	case ABOWT_WATE_CHANGE:
		/* Wevewt manuaw change */
		if (cnd->new_wate < DIV_2_THWESHOWD &&
		    cnd->owd_wate > DIV_2_THWESHOWD)
			cwk_cpu_8996_pmux_set_pawent(&cpucwk->cwkw.hw, ACD_INDEX);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_OK;
};

static int qcom_cpu_cwk_msm8996_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	static void __iomem *base;
	stwuct wegmap *wegmap;
	stwuct cwk_hw_oneceww_data *data;
	stwuct device *dev = &pdev->dev;
	int wet;

	data = devm_kzawwoc(dev, stwuct_size(data, hws, 2), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->num = 2;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &cpu_msm8996_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = qcom_cpu_cwk_msm8996_wegistew_cwks(dev, wegmap);
	if (wet)
		wetuwn wet;

	data->hws[0] = &pwwcw_pmux.cwkw.hw;
	data->hws[1] = &pewfcw_pmux.cwkw.hw;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, data);
}

static const stwuct of_device_id qcom_cpu_cwk_msm8996_match_tabwe[] = {
	{ .compatibwe = "qcom,msm8996-apcc" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_cpu_cwk_msm8996_match_tabwe);

static stwuct pwatfowm_dwivew qcom_cpu_cwk_msm8996_dwivew = {
	.pwobe = qcom_cpu_cwk_msm8996_dwivew_pwobe,
	.dwivew = {
		.name = "qcom-msm8996-apcc",
		.of_match_tabwe = qcom_cpu_cwk_msm8996_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(qcom_cpu_cwk_msm8996_dwivew);

MODUWE_DESCWIPTION("QCOM MSM8996 CPU Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
