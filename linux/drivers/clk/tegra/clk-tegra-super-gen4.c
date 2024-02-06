// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk/tegwa.h>

#incwude "cwk.h"
#incwude "cwk-id.h"

#define PWWX_BASE 0xe0
#define PWWX_MISC 0xe4
#define PWWX_MISC2 0x514
#define PWWX_MISC3 0x518

#define CCWKG_BUWST_POWICY 0x368
#define CCWKWP_BUWST_POWICY 0x370
#define SCWK_BUWST_POWICY 0x028
#define SYSTEM_CWK_WATE 0x030
#define SCWK_DIVIDEW 0x2c

static DEFINE_SPINWOCK(syswate_wock);

enum tegwa_supew_gen {
	gen4 = 4,
	gen5,
};

stwuct tegwa_supew_gen_info {
	enum tegwa_supew_gen gen;
	const chaw **scwk_pawents;
	const chaw **ccwk_g_pawents;
	const chaw **ccwk_wp_pawents;
	int num_scwk_pawents;
	int num_ccwk_g_pawents;
	int num_ccwk_wp_pawents;
};

static const chaw *scwk_pawents[] = { "cwk_m", "pww_c_out1", "pww_p_out4",
			       "pww_p", "pww_p_out2", "unused",
			       "cwk_32k", "pww_m_out1" };

static const chaw *ccwk_g_pawents[] = { "cwk_m", "pww_c", "cwk_32k", "pww_m",
					"pww_p", "pww_p_out4", "unused",
					"unused", "pww_x", "unused", "unused",
					"unused", "unused", "unused", "unused",
					"dfwwCPU_out" };

static const chaw *ccwk_wp_pawents[] = { "cwk_m", "pww_c", "cwk_32k", "pww_m",
					 "pww_p", "pww_p_out4", "unused",
					 "unused", "pww_x", "pww_x_out0" };

static const stwuct tegwa_supew_gen_info tegwa_supew_gen_info_gen4 = {
	.gen = gen4,
	.scwk_pawents = scwk_pawents,
	.ccwk_g_pawents = ccwk_g_pawents,
	.ccwk_wp_pawents = ccwk_wp_pawents,
	.num_scwk_pawents = AWWAY_SIZE(scwk_pawents),
	.num_ccwk_g_pawents = AWWAY_SIZE(ccwk_g_pawents),
	.num_ccwk_wp_pawents = AWWAY_SIZE(ccwk_wp_pawents),
};

static const chaw *scwk_pawents_gen5[] = { "cwk_m", "pww_c_out1", "pww_c4_out3",
			       "pww_p", "pww_p_out2", "pww_c4_out1",
			       "cwk_32k", "pww_c4_out2" };

static const chaw *ccwk_g_pawents_gen5[] = { "cwk_m", "unused", "cwk_32k", "unused",
					"pww_p", "pww_p_out4", "unused",
					"unused", "pww_x", "unused", "unused",
					"unused", "unused", "unused", "unused",
					"dfwwCPU_out" };

static const chaw *ccwk_wp_pawents_gen5[] = { "cwk_m", "unused", "cwk_32k", "unused",
					"pww_p", "pww_p_out4", "unused",
					"unused", "pww_x", "unused", "unused",
					"unused", "unused", "unused", "unused",
					"dfwwCPU_out" };

static const stwuct tegwa_supew_gen_info tegwa_supew_gen_info_gen5 = {
	.gen = gen5,
	.scwk_pawents = scwk_pawents_gen5,
	.ccwk_g_pawents = ccwk_g_pawents_gen5,
	.ccwk_wp_pawents = ccwk_wp_pawents_gen5,
	.num_scwk_pawents = AWWAY_SIZE(scwk_pawents_gen5),
	.num_ccwk_g_pawents = AWWAY_SIZE(ccwk_g_pawents_gen5),
	.num_ccwk_wp_pawents = AWWAY_SIZE(ccwk_wp_pawents_gen5),
};

static void __init tegwa_scwk_init(void __iomem *cwk_base,
				stwuct tegwa_cwk *tegwa_cwks,
				const stwuct tegwa_supew_gen_info *gen_info)
{
	stwuct cwk *cwk;
	stwuct cwk **dt_cwk;

	/* SCWK_MUX */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_scwk_mux, tegwa_cwks);
	if (dt_cwk) {
		cwk = tegwa_cwk_wegistew_supew_mux("scwk_mux",
						gen_info->scwk_pawents,
						gen_info->num_scwk_pawents,
						CWK_SET_WATE_PAWENT,
						cwk_base + SCWK_BUWST_POWICY,
						0, 4, 0, 0, NUWW);
		*dt_cwk = cwk;


		/* SCWK */
		dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_scwk, tegwa_cwks);
		if (dt_cwk) {
			cwk = cwk_wegistew_dividew(NUWW, "scwk", "scwk_mux",
						CWK_IS_CWITICAW,
						cwk_base + SCWK_DIVIDEW, 0, 8,
						0, &syswate_wock);
			*dt_cwk = cwk;
		}
	} ewse {
		/* SCWK */
		dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_scwk, tegwa_cwks);
		if (dt_cwk) {
			cwk = tegwa_cwk_wegistew_supew_mux("scwk",
						gen_info->scwk_pawents,
						gen_info->num_scwk_pawents,
						CWK_SET_WATE_PAWENT |
						CWK_IS_CWITICAW,
						cwk_base + SCWK_BUWST_POWICY,
						0, 4, 0, 0, NUWW);
			*dt_cwk = cwk;
		}
	}

	/* HCWK */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_hcwk, tegwa_cwks);
	if (dt_cwk) {
		cwk = cwk_wegistew_dividew(NUWW, "hcwk_div", "scwk", 0,
				   cwk_base + SYSTEM_CWK_WATE, 4, 2, 0,
				   &syswate_wock);
		cwk = cwk_wegistew_gate(NUWW, "hcwk", "hcwk_div",
				CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
				cwk_base + SYSTEM_CWK_WATE,
				7, CWK_GATE_SET_TO_DISABWE, &syswate_wock);
		*dt_cwk = cwk;
	}

	/* PCWK */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_pcwk, tegwa_cwks);
	if (!dt_cwk)
		wetuwn;

	cwk = cwk_wegistew_dividew(NUWW, "pcwk_div", "hcwk", 0,
				   cwk_base + SYSTEM_CWK_WATE, 0, 2, 0,
				   &syswate_wock);
	cwk = cwk_wegistew_gate(NUWW, "pcwk", "pcwk_div", CWK_SET_WATE_PAWENT |
				CWK_IS_CWITICAW, cwk_base + SYSTEM_CWK_WATE,
				3, CWK_GATE_SET_TO_DISABWE, &syswate_wock);
	*dt_cwk = cwk;
}

static void __init tegwa_supew_cwk_init(void __iomem *cwk_base,
				void __iomem *pmc_base,
				stwuct tegwa_cwk *tegwa_cwks,
				stwuct tegwa_cwk_pww_pawams *pawams,
				const stwuct tegwa_supew_gen_info *gen_info)
{
	stwuct cwk *cwk;
	stwuct cwk **dt_cwk;

	/* CCWKG */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_ccwk_g, tegwa_cwks);
	if (dt_cwk) {
		if (gen_info->gen == gen5) {
			cwk = tegwa_cwk_wegistew_supew_mux("ccwk_g",
					gen_info->ccwk_g_pawents,
					gen_info->num_ccwk_g_pawents,
					CWK_SET_WATE_PAWENT,
					cwk_base + CCWKG_BUWST_POWICY,
					TEGWA210_CPU_CWK, 4, 8, 0, NUWW);
		} ewse {
			cwk = tegwa_cwk_wegistew_supew_mux("ccwk_g",
					gen_info->ccwk_g_pawents,
					gen_info->num_ccwk_g_pawents,
					CWK_SET_WATE_PAWENT,
					cwk_base + CCWKG_BUWST_POWICY,
					0, 4, 0, 0, NUWW);
		}
		*dt_cwk = cwk;
	}

	/* CCWKWP */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_ccwk_wp, tegwa_cwks);
	if (dt_cwk) {
		if (gen_info->gen == gen5) {
			/*
			 * TEGWA210_CPU_CWK fwag is not needed fow ccwk_wp as
			 * cwustew switching is not cuwwentwy suppowted on
			 * Tegwa210 and awso cpu_wp is not used.
			 */
			cwk = tegwa_cwk_wegistew_supew_mux("ccwk_wp",
					gen_info->ccwk_wp_pawents,
					gen_info->num_ccwk_wp_pawents,
					CWK_SET_WATE_PAWENT,
					cwk_base + CCWKWP_BUWST_POWICY,
					0, 4, 8, 0, NUWW);
		} ewse {
			cwk = tegwa_cwk_wegistew_supew_mux("ccwk_wp",
					gen_info->ccwk_wp_pawents,
					gen_info->num_ccwk_wp_pawents,
					CWK_SET_WATE_PAWENT,
					cwk_base + CCWKWP_BUWST_POWICY,
					TEGWA_DIVIDEW_2, 4, 8, 9, NUWW);
		}
		*dt_cwk = cwk;
	}

	tegwa_scwk_init(cwk_base, tegwa_cwks, gen_info);

#if defined(CONFIG_AWCH_TEGWA_114_SOC) || \
    defined(CONFIG_AWCH_TEGWA_124_SOC) || \
    defined(CONFIG_AWCH_TEGWA_210_SOC)
	/* PWWX */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_pww_x, tegwa_cwks);
	if (!dt_cwk)
		wetuwn;

#if defined(CONFIG_AWCH_TEGWA_210_SOC)
	if (gen_info->gen == gen5)
		cwk = tegwa_cwk_wegistew_pwwc_tegwa210("pww_x", "pww_wef",
			cwk_base, pmc_base, CWK_IGNOWE_UNUSED, pawams, NUWW);
	ewse
#endif
		cwk = tegwa_cwk_wegistew_pwwxc("pww_x", "pww_wef", cwk_base,
				pmc_base, CWK_IGNOWE_UNUSED, pawams, NUWW);

	*dt_cwk = cwk;

	/* PWWX_OUT0 */

	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_pww_x_out0, tegwa_cwks);
	if (!dt_cwk)
		wetuwn;
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_x_out0", "pww_x",
					CWK_SET_WATE_PAWENT, 1, 2);
	*dt_cwk = cwk;
#endif
}

void __init tegwa_supew_cwk_gen4_init(void __iomem *cwk_base,
				void __iomem *pmc_base,
				stwuct tegwa_cwk *tegwa_cwks,
				stwuct tegwa_cwk_pww_pawams *pawams)
{
	tegwa_supew_cwk_init(cwk_base, pmc_base, tegwa_cwks, pawams,
			     &tegwa_supew_gen_info_gen4);
}

void __init tegwa_supew_cwk_gen5_init(void __iomem *cwk_base,
				void __iomem *pmc_base,
				stwuct tegwa_cwk *tegwa_cwks,
				stwuct tegwa_cwk_pww_pawams *pawams)
{
	tegwa_supew_cwk_init(cwk_base, pmc_base, tegwa_cwks, pawams,
			     &tegwa_supew_gen_info_gen5);
}
