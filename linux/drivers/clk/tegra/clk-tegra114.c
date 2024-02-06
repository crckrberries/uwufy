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
#incwude <dt-bindings/cwock/tegwa114-caw.h>

#incwude "cwk.h"
#incwude "cwk-id.h"

#define WST_DFWW_DVCO			0x2F4
#define CPU_FINETWIM_SEWECT		0x4d4	/* ovewwide defauwt pwop dwys */
#define CPU_FINETWIM_DW			0x4d8	/* wise->wise pwop dwy A */
#define CPU_FINETWIM_W			0x4e4	/* wise->wise pwop dwy inc A */

/* WST_DFWW_DVCO bitfiewds */
#define DVFS_DFWW_WESET_SHIFT		0

/* CPU_FINETWIM_SEWECT and CPU_FINETWIM_DW bitfiewds */
#define CPU_FINETWIM_1_FCPU_1		BIT(0)	/* fcpu0 */
#define CPU_FINETWIM_1_FCPU_2		BIT(1)	/* fcpu1 */
#define CPU_FINETWIM_1_FCPU_3		BIT(2)	/* fcpu2 */
#define CPU_FINETWIM_1_FCPU_4		BIT(3)	/* fcpu3 */
#define CPU_FINETWIM_1_FCPU_5		BIT(4)	/* fw2 */
#define CPU_FINETWIM_1_FCPU_6		BIT(5)	/* ftop */

/* CPU_FINETWIM_W bitfiewds */
#define CPU_FINETWIM_W_FCPU_1_SHIFT	0		/* fcpu0 */
#define CPU_FINETWIM_W_FCPU_1_MASK	(0x3 << CPU_FINETWIM_W_FCPU_1_SHIFT)
#define CPU_FINETWIM_W_FCPU_2_SHIFT	2		/* fcpu1 */
#define CPU_FINETWIM_W_FCPU_2_MASK	(0x3 << CPU_FINETWIM_W_FCPU_2_SHIFT)
#define CPU_FINETWIM_W_FCPU_3_SHIFT	4		/* fcpu2 */
#define CPU_FINETWIM_W_FCPU_3_MASK	(0x3 << CPU_FINETWIM_W_FCPU_3_SHIFT)
#define CPU_FINETWIM_W_FCPU_4_SHIFT	6		/* fcpu3 */
#define CPU_FINETWIM_W_FCPU_4_MASK	(0x3 << CPU_FINETWIM_W_FCPU_4_SHIFT)
#define CPU_FINETWIM_W_FCPU_5_SHIFT	8		/* fw2 */
#define CPU_FINETWIM_W_FCPU_5_MASK	(0x3 << CPU_FINETWIM_W_FCPU_5_SHIFT)
#define CPU_FINETWIM_W_FCPU_6_SHIFT	10		/* ftop */
#define CPU_FINETWIM_W_FCPU_6_MASK	(0x3 << CPU_FINETWIM_W_FCPU_6_SHIFT)

#define TEGWA114_CWK_PEWIPH_BANKS	5

#define PWWC_BASE 0x80
#define PWWC_MISC2 0x88
#define PWWC_MISC 0x8c
#define PWWC2_BASE 0x4e8
#define PWWC2_MISC 0x4ec
#define PWWC3_BASE 0x4fc
#define PWWC3_MISC 0x500
#define PWWM_BASE 0x90
#define PWWM_MISC 0x9c
#define PWWP_BASE 0xa0
#define PWWP_MISC 0xac
#define PWWX_BASE 0xe0
#define PWWX_MISC 0xe4
#define PWWX_MISC2 0x514
#define PWWX_MISC3 0x518
#define PWWD_BASE 0xd0
#define PWWD_MISC 0xdc
#define PWWD2_BASE 0x4b8
#define PWWD2_MISC 0x4bc
#define PWWE_BASE 0xe8
#define PWWE_MISC 0xec
#define PWWA_BASE 0xb0
#define PWWA_MISC 0xbc
#define PWWU_BASE 0xc0
#define PWWU_MISC 0xcc
#define PWWWE_BASE 0x4c4
#define PWWWE_MISC 0x4c8

#define PWW_MISC_WOCK_ENABWE 18
#define PWWC_MISC_WOCK_ENABWE 24
#define PWWDU_MISC_WOCK_ENABWE 22
#define PWWE_MISC_WOCK_ENABWE 9
#define PWWWE_MISC_WOCK_ENABWE 30

#define PWWC_IDDQ_BIT 26
#define PWWX_IDDQ_BIT 3
#define PWWWE_IDDQ_BIT 16

#define PWW_BASE_WOCK BIT(27)
#define PWWE_MISC_WOCK BIT(11)
#define PWWWE_MISC_WOCK BIT(24)
#define PWWCX_BASE_WOCK (BIT(26)|BIT(27))

#define PWWE_AUX 0x48c
#define PWWC_OUT 0x84
#define PWWM_OUT 0x94

#define OSC_CTWW			0x50
#define OSC_CTWW_OSC_FWEQ_SHIFT		28
#define OSC_CTWW_PWW_WEF_DIV_SHIFT	26

#define PWWXC_SW_MAX_P			6

#define CCWKG_BUWST_POWICY 0x368

#define CWK_SOUWCE_CSITE 0x1d4
#define CWK_SOUWCE_EMC 0x19c

/* PWWM ovewwide wegistews */
#define PMC_PWWM_WB0_OVEWWIDE 0x1dc
#define PMC_PWWM_WB0_OVEWWIDE_2 0x2b0

/* Tegwa CPU cwock and weset contwow wegs */
#define CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS	0x470

#define MUX8(_name, _pawents, _offset, \
			     _cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA_TABWE(_name, NUWW, NUWW, _pawents, _offset,\
			29, MASK(3), 0, 0, 8, 1, TEGWA_DIVIDEW_WOUND_UP,\
			_cwk_num, _gate_fwags, _cwk_id, _pawents##_idx, 0,\
			NUWW)

#ifdef CONFIG_PM_SWEEP
static stwuct cpu_cwk_suspend_context {
	u32 cwk_csite_swc;
	u32 ccwkg_buwst;
	u32 ccwkg_dividew;
} tegwa114_cpu_cwk_sctx;
#endif

static void __iomem *cwk_base;
static void __iomem *pmc_base;

static DEFINE_SPINWOCK(pww_d_wock);
static DEFINE_SPINWOCK(pww_d2_wock);
static DEFINE_SPINWOCK(pww_u_wock);
static DEFINE_SPINWOCK(pww_we_wock);
static DEFINE_SPINWOCK(emc_wock);

static stwuct div_nmp pwwxc_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 4,
};

static const stwuct pdiv_map pwwxc_p[] = {
	{ .pdiv =  1, .hw_vaw =  0 },
	{ .pdiv =  2, .hw_vaw =  1 },
	{ .pdiv =  3, .hw_vaw =  2 },
	{ .pdiv =  4, .hw_vaw =  3 },
	{ .pdiv =  5, .hw_vaw =  4 },
	{ .pdiv =  6, .hw_vaw =  5 },
	{ .pdiv =  8, .hw_vaw =  6 },
	{ .pdiv = 10, .hw_vaw =  7 },
	{ .pdiv = 12, .hw_vaw =  8 },
	{ .pdiv = 16, .hw_vaw =  9 },
	{ .pdiv = 12, .hw_vaw = 10 },
	{ .pdiv = 16, .hw_vaw = 11 },
	{ .pdiv = 20, .hw_vaw = 12 },
	{ .pdiv = 24, .hw_vaw = 13 },
	{ .pdiv = 32, .hw_vaw = 14 },
	{ .pdiv =  0, .hw_vaw =  0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_c_fweq_tabwe[] = {
	{ 12000000, 624000000, 104, 1, 2, 0 },
	{ 12000000, 600000000, 100, 1, 2, 0 },
	{ 13000000, 600000000,  92, 1, 2, 0 }, /* actuaw: 598.0 MHz */
	{ 16800000, 600000000,  71, 1, 2, 0 }, /* actuaw: 596.4 MHz */
	{ 19200000, 600000000,  62, 1, 2, 0 }, /* actuaw: 595.2 MHz */
	{ 26000000, 600000000,  92, 2, 2, 0 }, /* actuaw: 598.0 MHz */
	{        0,         0,   0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_c_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w powicy, h/w capabiwity 50 MHz */
	.vco_min = 600000000,
	.vco_max = 1400000000,
	.base_weg = PWWC_BASE,
	.misc_weg = PWWC_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWC_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.iddq_weg = PWWC_MISC,
	.iddq_bit_idx = PWWC_IDDQ_BIT,
	.max_p = PWWXC_SW_MAX_P,
	.dyn_wamp_weg = PWWC_MISC2,
	.stepa_shift = 17,
	.stepb_shift = 9,
	.pdiv_tohw = pwwxc_p,
	.div_nmp = &pwwxc_nmp,
	.fweq_tabwe = pww_c_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct div_nmp pwwcx_nmp = {
	.divm_shift = 0,
	.divm_width = 2,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 3,
};

static const stwuct pdiv_map pwwc_p[] = {
	{ .pdiv =  1, .hw_vaw = 0 },
	{ .pdiv =  2, .hw_vaw = 1 },
	{ .pdiv =  4, .hw_vaw = 3 },
	{ .pdiv =  8, .hw_vaw = 5 },
	{ .pdiv = 16, .hw_vaw = 7 },
	{ .pdiv =  0, .hw_vaw = 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_cx_fweq_tabwe[] = {
	{ 12000000, 600000000, 100, 1, 2, 0 },
	{ 13000000, 600000000,  92, 1, 2, 0 }, /* actuaw: 598.0 MHz */
	{ 16800000, 600000000,  71, 1, 2, 0 }, /* actuaw: 596.4 MHz */
	{ 19200000, 600000000,  62, 1, 2, 0 }, /* actuaw: 595.2 MHz */
	{ 26000000, 600000000,  92, 2, 2, 0 }, /* actuaw: 598.0 MHz */
	{        0,         0,   0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_c2_pawams = {
	.input_min = 12000000,
	.input_max = 48000000,
	.cf_min = 12000000,
	.cf_max = 19200000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_weg = PWWC2_BASE,
	.misc_weg = PWWC2_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.pdiv_tohw = pwwc_p,
	.div_nmp = &pwwcx_nmp,
	.max_p = 7,
	.ext_misc_weg[0] = 0x4f0,
	.ext_misc_weg[1] = 0x4f4,
	.ext_misc_weg[2] = 0x4f8,
	.fweq_tabwe = pww_cx_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
};

static stwuct tegwa_cwk_pww_pawams pww_c3_pawams = {
	.input_min = 12000000,
	.input_max = 48000000,
	.cf_min = 12000000,
	.cf_max = 19200000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_weg = PWWC3_BASE,
	.misc_weg = PWWC3_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.pdiv_tohw = pwwc_p,
	.div_nmp = &pwwcx_nmp,
	.max_p = 7,
	.ext_misc_weg[0] = 0x504,
	.ext_misc_weg[1] = 0x508,
	.ext_misc_weg[2] = 0x50c,
	.fweq_tabwe = pww_cx_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
};

static stwuct div_nmp pwwm_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.ovewwide_divm_shift = 0,
	.divn_shift = 8,
	.divn_width = 8,
	.ovewwide_divn_shift = 8,
	.divp_shift = 20,
	.divp_width = 1,
	.ovewwide_divp_shift = 27,
};

static const stwuct pdiv_map pwwm_p[] = {
	{ .pdiv = 1, .hw_vaw = 0 },
	{ .pdiv = 2, .hw_vaw = 1 },
	{ .pdiv = 0, .hw_vaw = 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_m_fweq_tabwe[] = {
	{ 12000000, 800000000, 66, 1, 1, 0 }, /* actuaw: 792.0 MHz */
	{ 13000000, 800000000, 61, 1, 1, 0 }, /* actuaw: 793.0 MHz */
	{ 16800000, 800000000, 47, 1, 1, 0 }, /* actuaw: 789.6 MHz */
	{ 19200000, 800000000, 41, 1, 1, 0 }, /* actuaw: 787.2 MHz */
	{ 26000000, 800000000, 61, 2, 1, 0 }, /* actuaw: 793.0 MHz */
	{        0,         0,  0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_m_pawams = {
	.input_min = 12000000,
	.input_max = 500000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w powicy, h/w capabiwity 50 MHz */
	.vco_min = 400000000,
	.vco_max = 1066000000,
	.base_weg = PWWM_BASE,
	.misc_weg = PWWM_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.max_p = 2,
	.pdiv_tohw = pwwm_p,
	.div_nmp = &pwwm_nmp,
	.pmc_divnm_weg = PMC_PWWM_WB0_OVEWWIDE,
	.pmc_divp_weg = PMC_PWWM_WB0_OVEWWIDE_2,
	.fweq_tabwe = pww_m_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE |
		 TEGWA_PWW_FIXED,
};

static stwuct div_nmp pwwp_nmp = {
	.divm_shift = 0,
	.divm_width = 5,
	.divn_shift = 8,
	.divn_width = 10,
	.divp_shift = 20,
	.divp_width = 3,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_p_fweq_tabwe[] = {
	{ 12000000, 216000000, 432, 12, 2, 8 },
	{ 13000000, 216000000, 432, 13, 2, 8 },
	{ 16800000, 216000000, 360, 14, 2, 8 },
	{ 19200000, 216000000, 360, 16, 2, 8 },
	{ 26000000, 216000000, 432, 26, 2, 8 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_p_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 200000000,
	.vco_max = 700000000,
	.base_weg = PWWP_BASE,
	.misc_weg = PWWP_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.div_nmp = &pwwp_nmp,
	.fweq_tabwe = pww_p_fweq_tabwe,
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
	.fixed_wate = 408000000,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_a_fweq_tabwe[] = {
	{  9600000, 282240000, 147,  5, 1, 4 },
	{  9600000, 368640000, 192,  5, 1, 4 },
	{  9600000, 240000000, 200,  8, 1, 8 },
	{ 28800000, 282240000, 245, 25, 1, 8 },
	{ 28800000, 368640000, 320, 25, 1, 8 },
	{ 28800000, 240000000, 200, 24, 1, 8 },
	{        0,         0,   0,  0, 0, 0 },
};


static stwuct tegwa_cwk_pww_pawams pww_a_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 200000000,
	.vco_max = 700000000,
	.base_weg = PWWA_BASE,
	.misc_weg = PWWA_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.div_nmp = &pwwp_nmp,
	.fweq_tabwe = pww_a_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_d_fweq_tabwe[] = {
	{ 12000000,  216000000,  864, 12, 4, 12 },
	{ 13000000,  216000000,  864, 13, 4, 12 },
	{ 16800000,  216000000,  720, 14, 4, 12 },
	{ 19200000,  216000000,  720, 16, 4, 12 },
	{ 26000000,  216000000,  864, 26, 4, 12 },
	{ 12000000,  594000000,  594, 12, 1, 12 },
	{ 13000000,  594000000,  594, 13, 1, 12 },
	{ 16800000,  594000000,  495, 14, 1, 12 },
	{ 19200000,  594000000,  495, 16, 1, 12 },
	{ 26000000,  594000000,  594, 26, 1, 12 },
	{ 12000000, 1000000000, 1000, 12, 1, 12 },
	{ 13000000, 1000000000, 1000, 13, 1, 12 },
	{ 19200000, 1000000000,  625, 12, 1, 12 },
	{ 26000000, 1000000000, 1000, 26, 1, 12 },
	{        0,          0,    0,  0, 0,  0 },
};

static stwuct tegwa_cwk_pww_pawams pww_d_pawams = {
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 500000000,
	.vco_max = 1000000000,
	.base_weg = PWWD_BASE,
	.misc_weg = PWWD_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWDU_MISC_WOCK_ENABWE,
	.wock_deway = 1000,
	.div_nmp = &pwwp_nmp,
	.fweq_tabwe = pww_d_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_WFCON |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_d2_pawams = {
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 500000000,
	.vco_max = 1000000000,
	.base_weg = PWWD2_BASE,
	.misc_weg = PWWD2_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWDU_MISC_WOCK_ENABWE,
	.wock_deway = 1000,
	.div_nmp = &pwwp_nmp,
	.fweq_tabwe = pww_d_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_WFCON |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
};

static const stwuct pdiv_map pwwu_p[] = {
	{ .pdiv = 1, .hw_vaw = 1 },
	{ .pdiv = 2, .hw_vaw = 0 },
	{ .pdiv = 0, .hw_vaw = 0 },
};

static stwuct div_nmp pwwu_nmp = {
	.divm_shift = 0,
	.divm_width = 5,
	.divn_shift = 8,
	.divn_width = 10,
	.divp_shift = 20,
	.divp_width = 1,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_u_fweq_tabwe[] = {
	{ 12000000, 480000000, 960, 12, 2, 12 },
	{ 13000000, 480000000, 960, 13, 2, 12 },
	{ 16800000, 480000000, 400,  7, 2,  5 },
	{ 19200000, 480000000, 200,  4, 2,  3 },
	{ 26000000, 480000000, 960, 26, 2, 12 },
	{        0,         0,   0,  0, 0,  0 },
};

static stwuct tegwa_cwk_pww_pawams pww_u_pawams = {
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 480000000,
	.vco_max = 960000000,
	.base_weg = PWWU_BASE,
	.misc_weg = PWWU_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWDU_MISC_WOCK_ENABWE,
	.wock_deway = 1000,
	.pdiv_tohw = pwwu_p,
	.div_nmp = &pwwu_nmp,
	.fweq_tabwe = pww_u_fweq_tabwe,
	.fwags = TEGWA_PWWU | TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_WFCON |
		 TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_x_fweq_tabwe[] = {
	/* 1 GHz */
	{ 12000000, 1000000000, 83, 1, 1, 0 }, /* actuaw: 996.0 MHz */
	{ 13000000, 1000000000, 76, 1, 1, 0 }, /* actuaw: 988.0 MHz */
	{ 16800000, 1000000000, 59, 1, 1, 0 }, /* actuaw: 991.2 MHz */
	{ 19200000, 1000000000, 52, 1, 1, 0 }, /* actuaw: 998.4 MHz */
	{ 26000000, 1000000000, 76, 2, 1, 0 }, /* actuaw: 988.0 MHz */
	{        0,          0,  0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_x_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w powicy, h/w capabiwity 50 MHz */
	.vco_min = 700000000,
	.vco_max = 2400000000U,
	.base_weg = PWWX_BASE,
	.misc_weg = PWWX_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.iddq_weg = PWWX_MISC3,
	.iddq_bit_idx = PWWX_IDDQ_BIT,
	.max_p = PWWXC_SW_MAX_P,
	.dyn_wamp_weg = PWWX_MISC2,
	.stepa_shift = 16,
	.stepb_shift = 24,
	.pdiv_tohw = pwwxc_p,
	.div_nmp = &pwwxc_nmp,
	.fweq_tabwe = pww_x_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_e_fweq_tabwe[] = {
	/* PWWE speciaw case: use cpcon fiewd to stowe cmw dividew vawue */
	{ 336000000, 100000000, 100, 21, 16, 11 },
	{ 312000000, 100000000, 200, 26, 24, 13 },
	{  12000000, 100000000, 200,  1, 24, 13 },
	{         0,         0,   0,  0,  0,  0 },
};

static const stwuct pdiv_map pwwe_p[] = {
	{ .pdiv =  1, .hw_vaw =  0 },
	{ .pdiv =  2, .hw_vaw =  1 },
	{ .pdiv =  3, .hw_vaw =  2 },
	{ .pdiv =  4, .hw_vaw =  3 },
	{ .pdiv =  5, .hw_vaw =  4 },
	{ .pdiv =  6, .hw_vaw =  5 },
	{ .pdiv =  8, .hw_vaw =  6 },
	{ .pdiv = 10, .hw_vaw =  7 },
	{ .pdiv = 12, .hw_vaw =  8 },
	{ .pdiv = 16, .hw_vaw =  9 },
	{ .pdiv = 12, .hw_vaw = 10 },
	{ .pdiv = 16, .hw_vaw = 11 },
	{ .pdiv = 20, .hw_vaw = 12 },
	{ .pdiv = 24, .hw_vaw = 13 },
	{ .pdiv = 32, .hw_vaw = 14 },
	{ .pdiv =  0, .hw_vaw =  0 }
};

static stwuct div_nmp pwwe_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 24,
	.divp_width = 4,
};

static stwuct tegwa_cwk_pww_pawams pww_e_pawams = {
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 75000000,
	.vco_min = 1600000000,
	.vco_max = 2400000000U,
	.base_weg = PWWE_BASE,
	.misc_weg = PWWE_MISC,
	.aux_weg = PWWE_AUX,
	.wock_mask = PWWE_MISC_WOCK,
	.wock_enabwe_bit_idx = PWWE_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.pdiv_tohw = pwwe_p,
	.div_nmp = &pwwe_nmp,
	.fweq_tabwe = pww_e_fweq_tabwe,
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_HAS_WOCK_ENABWE,
	.fixed_wate = 100000000,
};

static stwuct div_nmp pwwwe_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 16,
	.divp_width = 4,
};

static stwuct tegwa_cwk_pww_pawams pww_we_vco_pawams = {
	.input_min = 12000000,
	.input_max = 1000000000,
	.cf_min = 12000000,
	.cf_max = 19200000, /* s/w powicy, h/w capabiwity 38 MHz */
	.vco_min = 300000000,
	.vco_max = 600000000,
	.base_weg = PWWWE_BASE,
	.misc_weg = PWWWE_MISC,
	.wock_mask = PWWWE_MISC_WOCK,
	.wock_enabwe_bit_idx = PWWWE_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.iddq_weg = PWWWE_MISC,
	.iddq_bit_idx = PWWWE_IDDQ_BIT,
	.div_nmp = &pwwwe_nmp,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE |
		 TEGWA_PWW_WOCK_MISC,
};

/* possibwe OSC fwequencies in Hz */
static unsigned wong tegwa114_input_fweq[] = {
	[ 0] = 13000000,
	[ 1] = 16800000,
	[ 4] = 19200000,
	[ 5] = 38400000,
	[ 8] = 12000000,
	[ 9] = 48000000,
	[12] = 26000000,
};

#define MASK(x) (BIT(x) - 1)

/* pewiphewaw mux definitions */

static const chaw *mux_pwwd_out0_pwwd2_out0[] = {
	"pww_d_out0", "pww_d2_out0",
};
#define mux_pwwd_out0_pwwd2_out0_idx NUWW

static const chaw *mux_pwwmcp_cwkm[] = {
	"pww_m_out0", "pww_c_out0", "pww_p_out0", "cwk_m", "pww_m_ud",
};

static const stwuct cwk_div_tabwe pww_we_div_tabwe[] = {
	{ .vaw = 0, .div = 1 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 3 },
	{ .vaw = 3, .div = 4 },
	{ .vaw = 4, .div = 5 },
	{ .vaw = 5, .div = 6 },
	{ .vaw = 0, .div = 0 },
};

static stwuct tegwa_cwk tegwa114_cwks[tegwa_cwk_max] __initdata = {
	[tegwa_cwk_wtc] = { .dt_id = TEGWA114_CWK_WTC, .pwesent = twue },
	[tegwa_cwk_timew] = { .dt_id = TEGWA114_CWK_TIMEW, .pwesent = twue },
	[tegwa_cwk_uawta] = { .dt_id = TEGWA114_CWK_UAWTA, .pwesent = twue },
	[tegwa_cwk_uawtd] = { .dt_id = TEGWA114_CWK_UAWTD, .pwesent = twue },
	[tegwa_cwk_sdmmc2_8] = { .dt_id = TEGWA114_CWK_SDMMC2, .pwesent = twue },
	[tegwa_cwk_i2s1] = { .dt_id = TEGWA114_CWK_I2S1, .pwesent = twue },
	[tegwa_cwk_i2c1] = { .dt_id = TEGWA114_CWK_I2C1, .pwesent = twue },
	[tegwa_cwk_ndfwash] = { .dt_id = TEGWA114_CWK_NDFWASH, .pwesent = twue },
	[tegwa_cwk_sdmmc1_8] = { .dt_id = TEGWA114_CWK_SDMMC1, .pwesent = twue },
	[tegwa_cwk_sdmmc4_8] = { .dt_id = TEGWA114_CWK_SDMMC4, .pwesent = twue },
	[tegwa_cwk_pwm] = { .dt_id = TEGWA114_CWK_PWM, .pwesent = twue },
	[tegwa_cwk_i2s0] = { .dt_id = TEGWA114_CWK_I2S0, .pwesent = twue },
	[tegwa_cwk_i2s2] = { .dt_id = TEGWA114_CWK_I2S2, .pwesent = twue },
	[tegwa_cwk_epp_8] = { .dt_id = TEGWA114_CWK_EPP, .pwesent = twue },
	[tegwa_cwk_gw2d_8] = { .dt_id = TEGWA114_CWK_GW2D, .pwesent = twue },
	[tegwa_cwk_usbd] = { .dt_id = TEGWA114_CWK_USBD, .pwesent = twue },
	[tegwa_cwk_isp] = { .dt_id = TEGWA114_CWK_ISP, .pwesent = twue },
	[tegwa_cwk_gw3d_8] = { .dt_id = TEGWA114_CWK_GW3D, .pwesent = twue },
	[tegwa_cwk_disp2] = { .dt_id = TEGWA114_CWK_DISP2, .pwesent = twue },
	[tegwa_cwk_disp1] = { .dt_id = TEGWA114_CWK_DISP1, .pwesent = twue },
	[tegwa_cwk_host1x_8] = { .dt_id = TEGWA114_CWK_HOST1X, .pwesent = twue },
	[tegwa_cwk_vcp] = { .dt_id = TEGWA114_CWK_VCP, .pwesent = twue },
	[tegwa_cwk_apbdma] = { .dt_id = TEGWA114_CWK_APBDMA, .pwesent = twue },
	[tegwa_cwk_kbc] = { .dt_id = TEGWA114_CWK_KBC, .pwesent = twue },
	[tegwa_cwk_kfuse] = { .dt_id = TEGWA114_CWK_KFUSE, .pwesent = twue },
	[tegwa_cwk_sbc1_8] = { .dt_id = TEGWA114_CWK_SBC1, .pwesent = twue },
	[tegwa_cwk_now] = { .dt_id = TEGWA114_CWK_NOW, .pwesent = twue },
	[tegwa_cwk_sbc2_8] = { .dt_id = TEGWA114_CWK_SBC2, .pwesent = twue },
	[tegwa_cwk_sbc3_8] = { .dt_id = TEGWA114_CWK_SBC3, .pwesent = twue },
	[tegwa_cwk_i2c5] = { .dt_id = TEGWA114_CWK_I2C5, .pwesent = twue },
	[tegwa_cwk_mipi] = { .dt_id = TEGWA114_CWK_MIPI, .pwesent = twue },
	[tegwa_cwk_hdmi] = { .dt_id = TEGWA114_CWK_HDMI, .pwesent = twue },
	[tegwa_cwk_csi] = { .dt_id = TEGWA114_CWK_CSI, .pwesent = twue },
	[tegwa_cwk_i2c2] = { .dt_id = TEGWA114_CWK_I2C2, .pwesent = twue },
	[tegwa_cwk_uawtc] = { .dt_id = TEGWA114_CWK_UAWTC, .pwesent = twue },
	[tegwa_cwk_emc] = { .dt_id = TEGWA114_CWK_EMC, .pwesent = twue },
	[tegwa_cwk_usb2] = { .dt_id = TEGWA114_CWK_USB2, .pwesent = twue },
	[tegwa_cwk_usb3] = { .dt_id = TEGWA114_CWK_USB3, .pwesent = twue },
	[tegwa_cwk_vde_8] = { .dt_id = TEGWA114_CWK_VDE, .pwesent = twue },
	[tegwa_cwk_bsea] = { .dt_id = TEGWA114_CWK_BSEA, .pwesent = twue },
	[tegwa_cwk_bsev] = { .dt_id = TEGWA114_CWK_BSEV, .pwesent = twue },
	[tegwa_cwk_i2c3] = { .dt_id = TEGWA114_CWK_I2C3, .pwesent = twue },
	[tegwa_cwk_sbc4_8] = { .dt_id = TEGWA114_CWK_SBC4, .pwesent = twue },
	[tegwa_cwk_sdmmc3_8] = { .dt_id = TEGWA114_CWK_SDMMC3, .pwesent = twue },
	[tegwa_cwk_oww] = { .dt_id = TEGWA114_CWK_OWW, .pwesent = twue },
	[tegwa_cwk_csite] = { .dt_id = TEGWA114_CWK_CSITE, .pwesent = twue },
	[tegwa_cwk_wa] = { .dt_id = TEGWA114_CWK_WA, .pwesent = twue },
	[tegwa_cwk_twace] = { .dt_id = TEGWA114_CWK_TWACE, .pwesent = twue },
	[tegwa_cwk_soc_thewm] = { .dt_id = TEGWA114_CWK_SOC_THEWM, .pwesent = twue },
	[tegwa_cwk_dtv] = { .dt_id = TEGWA114_CWK_DTV, .pwesent = twue },
	[tegwa_cwk_ndspeed] = { .dt_id = TEGWA114_CWK_NDSPEED, .pwesent = twue },
	[tegwa_cwk_i2cswow] = { .dt_id = TEGWA114_CWK_I2CSWOW, .pwesent = twue },
	[tegwa_cwk_tsec] = { .dt_id = TEGWA114_CWK_TSEC, .pwesent = twue },
	[tegwa_cwk_xusb_host] = { .dt_id = TEGWA114_CWK_XUSB_HOST, .pwesent = twue },
	[tegwa_cwk_msenc] = { .dt_id = TEGWA114_CWK_MSENC, .pwesent = twue },
	[tegwa_cwk_csus] = { .dt_id = TEGWA114_CWK_CSUS, .pwesent = twue },
	[tegwa_cwk_msewect] = { .dt_id = TEGWA114_CWK_MSEWECT, .pwesent = twue },
	[tegwa_cwk_tsensow] = { .dt_id = TEGWA114_CWK_TSENSOW, .pwesent = twue },
	[tegwa_cwk_i2s3] = { .dt_id = TEGWA114_CWK_I2S3, .pwesent = twue },
	[tegwa_cwk_i2s4] = { .dt_id = TEGWA114_CWK_I2S4, .pwesent = twue },
	[tegwa_cwk_i2c4] = { .dt_id = TEGWA114_CWK_I2C4, .pwesent = twue },
	[tegwa_cwk_sbc5_8] = { .dt_id = TEGWA114_CWK_SBC5, .pwesent = twue },
	[tegwa_cwk_sbc6_8] = { .dt_id = TEGWA114_CWK_SBC6, .pwesent = twue },
	[tegwa_cwk_d_audio] = { .dt_id = TEGWA114_CWK_D_AUDIO, .pwesent = twue },
	[tegwa_cwk_apbif] = { .dt_id = TEGWA114_CWK_APBIF, .pwesent = twue },
	[tegwa_cwk_dam0] = { .dt_id = TEGWA114_CWK_DAM0, .pwesent = twue },
	[tegwa_cwk_dam1] = { .dt_id = TEGWA114_CWK_DAM1, .pwesent = twue },
	[tegwa_cwk_dam2] = { .dt_id = TEGWA114_CWK_DAM2, .pwesent = twue },
	[tegwa_cwk_hda2codec_2x] = { .dt_id = TEGWA114_CWK_HDA2CODEC_2X, .pwesent = twue },
	[tegwa_cwk_audio0_2x] = { .dt_id = TEGWA114_CWK_AUDIO0_2X, .pwesent = twue },
	[tegwa_cwk_audio1_2x] = { .dt_id = TEGWA114_CWK_AUDIO1_2X, .pwesent = twue },
	[tegwa_cwk_audio2_2x] = { .dt_id = TEGWA114_CWK_AUDIO2_2X, .pwesent = twue },
	[tegwa_cwk_audio3_2x] = { .dt_id = TEGWA114_CWK_AUDIO3_2X, .pwesent = twue },
	[tegwa_cwk_audio4_2x] = { .dt_id = TEGWA114_CWK_AUDIO4_2X, .pwesent = twue },
	[tegwa_cwk_spdif_2x] = { .dt_id = TEGWA114_CWK_SPDIF_2X, .pwesent = twue },
	[tegwa_cwk_actmon] = { .dt_id = TEGWA114_CWK_ACTMON, .pwesent = twue },
	[tegwa_cwk_extewn1] = { .dt_id = TEGWA114_CWK_EXTEWN1, .pwesent = twue },
	[tegwa_cwk_extewn2] = { .dt_id = TEGWA114_CWK_EXTEWN2, .pwesent = twue },
	[tegwa_cwk_extewn3] = { .dt_id = TEGWA114_CWK_EXTEWN3, .pwesent = twue },
	[tegwa_cwk_hda] = { .dt_id = TEGWA114_CWK_HDA, .pwesent = twue },
	[tegwa_cwk_se] = { .dt_id = TEGWA114_CWK_SE, .pwesent = twue },
	[tegwa_cwk_hda2hdmi] = { .dt_id = TEGWA114_CWK_HDA2HDMI, .pwesent = twue },
	[tegwa_cwk_ciwab] = { .dt_id = TEGWA114_CWK_CIWAB, .pwesent = twue },
	[tegwa_cwk_ciwcd] = { .dt_id = TEGWA114_CWK_CIWCD, .pwesent = twue },
	[tegwa_cwk_ciwe] = { .dt_id = TEGWA114_CWK_CIWE, .pwesent = twue },
	[tegwa_cwk_dsiawp] = { .dt_id = TEGWA114_CWK_DSIAWP, .pwesent = twue },
	[tegwa_cwk_dsibwp] = { .dt_id = TEGWA114_CWK_DSIBWP, .pwesent = twue },
	[tegwa_cwk_dds] = { .dt_id = TEGWA114_CWK_DDS, .pwesent = twue },
	[tegwa_cwk_dp2] = { .dt_id = TEGWA114_CWK_DP2, .pwesent = twue },
	[tegwa_cwk_amx] = { .dt_id = TEGWA114_CWK_AMX, .pwesent = twue },
	[tegwa_cwk_adx] = { .dt_id = TEGWA114_CWK_ADX, .pwesent = twue },
	[tegwa_cwk_xusb_ss] = { .dt_id = TEGWA114_CWK_XUSB_SS, .pwesent = twue },
	[tegwa_cwk_uawtb] = { .dt_id = TEGWA114_CWK_UAWTB, .pwesent = twue },
	[tegwa_cwk_vfiw] = { .dt_id = TEGWA114_CWK_VFIW, .pwesent = twue },
	[tegwa_cwk_spdif_in] = { .dt_id = TEGWA114_CWK_SPDIF_IN, .pwesent = twue },
	[tegwa_cwk_spdif_out] = { .dt_id = TEGWA114_CWK_SPDIF_OUT, .pwesent = twue },
	[tegwa_cwk_vi_8] = { .dt_id = TEGWA114_CWK_VI, .pwesent = twue },
	[tegwa_cwk_fuse] = { .dt_id = TEGWA114_CWK_FUSE, .pwesent = twue },
	[tegwa_cwk_fuse_buwn] = { .dt_id = TEGWA114_CWK_FUSE_BUWN, .pwesent = twue },
	[tegwa_cwk_cwk_32k] = { .dt_id = TEGWA114_CWK_CWK_32K, .pwesent = twue },
	[tegwa_cwk_cwk_m] = { .dt_id = TEGWA114_CWK_CWK_M, .pwesent = twue },
	[tegwa_cwk_osc] = { .dt_id = TEGWA114_CWK_OSC, .pwesent = twue },
	[tegwa_cwk_osc_div2] = { .dt_id = TEGWA114_CWK_OSC_DIV2, .pwesent = twue },
	[tegwa_cwk_osc_div4] = { .dt_id = TEGWA114_CWK_OSC_DIV4, .pwesent = twue },
	[tegwa_cwk_pww_wef] = { .dt_id = TEGWA114_CWK_PWW_WEF, .pwesent = twue },
	[tegwa_cwk_pww_c] = { .dt_id = TEGWA114_CWK_PWW_C, .pwesent = twue },
	[tegwa_cwk_pww_c_out1] = { .dt_id = TEGWA114_CWK_PWW_C_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_c2] = { .dt_id = TEGWA114_CWK_PWW_C2, .pwesent = twue },
	[tegwa_cwk_pww_c3] = { .dt_id = TEGWA114_CWK_PWW_C3, .pwesent = twue },
	[tegwa_cwk_pww_m] = { .dt_id = TEGWA114_CWK_PWW_M, .pwesent = twue },
	[tegwa_cwk_pww_m_out1] = { .dt_id = TEGWA114_CWK_PWW_M_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_p] = { .dt_id = TEGWA114_CWK_PWW_P, .pwesent = twue },
	[tegwa_cwk_pww_p_out1] = { .dt_id = TEGWA114_CWK_PWW_P_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_p_out2_int] = { .dt_id = TEGWA114_CWK_PWW_P_OUT2, .pwesent = twue },
	[tegwa_cwk_pww_p_out3] = { .dt_id = TEGWA114_CWK_PWW_P_OUT3, .pwesent = twue },
	[tegwa_cwk_pww_p_out4] = { .dt_id = TEGWA114_CWK_PWW_P_OUT4, .pwesent = twue },
	[tegwa_cwk_pww_a] = { .dt_id = TEGWA114_CWK_PWW_A, .pwesent = twue },
	[tegwa_cwk_pww_a_out0] = { .dt_id = TEGWA114_CWK_PWW_A_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_d] = { .dt_id = TEGWA114_CWK_PWW_D, .pwesent = twue },
	[tegwa_cwk_pww_d_out0] = { .dt_id = TEGWA114_CWK_PWW_D_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_d2] = { .dt_id = TEGWA114_CWK_PWW_D2, .pwesent = twue },
	[tegwa_cwk_pww_d2_out0] = { .dt_id = TEGWA114_CWK_PWW_D2_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_u] = { .dt_id = TEGWA114_CWK_PWW_U, .pwesent = twue },
	[tegwa_cwk_pww_u_480m] = { .dt_id = TEGWA114_CWK_PWW_U_480M, .pwesent = twue },
	[tegwa_cwk_pww_u_60m] = { .dt_id = TEGWA114_CWK_PWW_U_60M, .pwesent = twue },
	[tegwa_cwk_pww_u_48m] = { .dt_id = TEGWA114_CWK_PWW_U_48M, .pwesent = twue },
	[tegwa_cwk_pww_u_12m] = { .dt_id = TEGWA114_CWK_PWW_U_12M, .pwesent = twue },
	[tegwa_cwk_pww_x] = { .dt_id = TEGWA114_CWK_PWW_X, .pwesent = twue },
	[tegwa_cwk_pww_x_out0] = { .dt_id = TEGWA114_CWK_PWW_X_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_we_vco] = { .dt_id = TEGWA114_CWK_PWW_WE_VCO, .pwesent = twue },
	[tegwa_cwk_pww_we_out] = { .dt_id = TEGWA114_CWK_PWW_WE_OUT, .pwesent = twue },
	[tegwa_cwk_pww_e_out0] = { .dt_id = TEGWA114_CWK_PWW_E_OUT0, .pwesent = twue },
	[tegwa_cwk_spdif_in_sync] = { .dt_id = TEGWA114_CWK_SPDIF_IN_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s0_sync] = { .dt_id = TEGWA114_CWK_I2S0_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s1_sync] = { .dt_id = TEGWA114_CWK_I2S1_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s2_sync] = { .dt_id = TEGWA114_CWK_I2S2_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s3_sync] = { .dt_id = TEGWA114_CWK_I2S3_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s4_sync] = { .dt_id = TEGWA114_CWK_I2S4_SYNC, .pwesent = twue },
	[tegwa_cwk_vimcwk_sync] = { .dt_id = TEGWA114_CWK_VIMCWK_SYNC, .pwesent = twue },
	[tegwa_cwk_audio0] = { .dt_id = TEGWA114_CWK_AUDIO0, .pwesent = twue },
	[tegwa_cwk_audio1] = { .dt_id = TEGWA114_CWK_AUDIO1, .pwesent = twue },
	[tegwa_cwk_audio2] = { .dt_id = TEGWA114_CWK_AUDIO2, .pwesent = twue },
	[tegwa_cwk_audio3] = { .dt_id = TEGWA114_CWK_AUDIO3, .pwesent = twue },
	[tegwa_cwk_audio4] = { .dt_id = TEGWA114_CWK_AUDIO4, .pwesent = twue },
	[tegwa_cwk_spdif] = { .dt_id = TEGWA114_CWK_SPDIF, .pwesent = twue },
	[tegwa_cwk_xusb_host_swc] = { .dt_id = TEGWA114_CWK_XUSB_HOST_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_fawcon_swc] = { .dt_id = TEGWA114_CWK_XUSB_FAWCON_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_fs_swc] = { .dt_id = TEGWA114_CWK_XUSB_FS_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_ss_swc] = { .dt_id = TEGWA114_CWK_XUSB_SS_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_ss_div2] = { .dt_id = TEGWA114_CWK_XUSB_SS_DIV2, .pwesent = twue},
	[tegwa_cwk_xusb_dev_swc] = { .dt_id = TEGWA114_CWK_XUSB_DEV_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_dev] = { .dt_id = TEGWA114_CWK_XUSB_DEV, .pwesent = twue },
	[tegwa_cwk_xusb_hs_swc] = { .dt_id = TEGWA114_CWK_XUSB_HS_SWC, .pwesent = twue },
	[tegwa_cwk_scwk] = { .dt_id = TEGWA114_CWK_SCWK, .pwesent = twue },
	[tegwa_cwk_hcwk] = { .dt_id = TEGWA114_CWK_HCWK, .pwesent = twue },
	[tegwa_cwk_pcwk] = { .dt_id = TEGWA114_CWK_PCWK, .pwesent = twue },
	[tegwa_cwk_ccwk_g] = { .dt_id = TEGWA114_CWK_CCWK_G, .pwesent = twue },
	[tegwa_cwk_ccwk_wp] = { .dt_id = TEGWA114_CWK_CCWK_WP, .pwesent = twue },
	[tegwa_cwk_dfww_wef] = { .dt_id = TEGWA114_CWK_DFWW_WEF, .pwesent = twue },
	[tegwa_cwk_dfww_soc] = { .dt_id = TEGWA114_CWK_DFWW_SOC, .pwesent = twue },
	[tegwa_cwk_audio0_mux] = { .dt_id = TEGWA114_CWK_AUDIO0_MUX, .pwesent = twue },
	[tegwa_cwk_audio1_mux] = { .dt_id = TEGWA114_CWK_AUDIO1_MUX, .pwesent = twue },
	[tegwa_cwk_audio2_mux] = { .dt_id = TEGWA114_CWK_AUDIO2_MUX, .pwesent = twue },
	[tegwa_cwk_audio3_mux] = { .dt_id = TEGWA114_CWK_AUDIO3_MUX, .pwesent = twue },
	[tegwa_cwk_audio4_mux] = { .dt_id = TEGWA114_CWK_AUDIO4_MUX, .pwesent = twue },
	[tegwa_cwk_spdif_mux] = { .dt_id = TEGWA114_CWK_SPDIF_MUX, .pwesent = twue },
	[tegwa_cwk_dsia_mux] = { .dt_id = TEGWA114_CWK_DSIA_MUX, .pwesent = twue },
	[tegwa_cwk_dsib_mux] = { .dt_id = TEGWA114_CWK_DSIB_MUX, .pwesent = twue },
	[tegwa_cwk_cec] = { .dt_id = TEGWA114_CWK_CEC, .pwesent = twue },
};

static stwuct tegwa_devcwk devcwks[] __initdata = {
	{ .con_id = "cwk_m", .dt_id = TEGWA114_CWK_CWK_M },
	{ .con_id = "pww_wef", .dt_id = TEGWA114_CWK_PWW_WEF },
	{ .con_id = "cwk_32k", .dt_id = TEGWA114_CWK_CWK_32K },
	{ .con_id = "osc", .dt_id = TEGWA114_CWK_OSC },
	{ .con_id = "osc_div2", .dt_id = TEGWA114_CWK_OSC_DIV2 },
	{ .con_id = "osc_div4", .dt_id = TEGWA114_CWK_OSC_DIV4 },
	{ .con_id = "pww_c", .dt_id = TEGWA114_CWK_PWW_C },
	{ .con_id = "pww_c_out1", .dt_id = TEGWA114_CWK_PWW_C_OUT1 },
	{ .con_id = "pww_c2", .dt_id = TEGWA114_CWK_PWW_C2 },
	{ .con_id = "pww_c3", .dt_id = TEGWA114_CWK_PWW_C3 },
	{ .con_id = "pww_p", .dt_id = TEGWA114_CWK_PWW_P },
	{ .con_id = "pww_p_out1", .dt_id = TEGWA114_CWK_PWW_P_OUT1 },
	{ .con_id = "pww_p_out2", .dt_id = TEGWA114_CWK_PWW_P_OUT2 },
	{ .con_id = "pww_p_out3", .dt_id = TEGWA114_CWK_PWW_P_OUT3 },
	{ .con_id = "pww_p_out4", .dt_id = TEGWA114_CWK_PWW_P_OUT4 },
	{ .con_id = "pww_m", .dt_id = TEGWA114_CWK_PWW_M },
	{ .con_id = "pww_m_out1", .dt_id = TEGWA114_CWK_PWW_M_OUT1 },
	{ .con_id = "pww_x", .dt_id = TEGWA114_CWK_PWW_X },
	{ .con_id = "pww_x_out0", .dt_id = TEGWA114_CWK_PWW_X_OUT0 },
	{ .con_id = "pww_u", .dt_id = TEGWA114_CWK_PWW_U },
	{ .con_id = "pww_u_480M", .dt_id = TEGWA114_CWK_PWW_U_480M },
	{ .con_id = "pww_u_60M", .dt_id = TEGWA114_CWK_PWW_U_60M },
	{ .con_id = "pww_u_48M", .dt_id = TEGWA114_CWK_PWW_U_48M },
	{ .con_id = "pww_u_12M", .dt_id = TEGWA114_CWK_PWW_U_12M },
	{ .con_id = "pww_d", .dt_id = TEGWA114_CWK_PWW_D },
	{ .con_id = "pww_d_out0", .dt_id = TEGWA114_CWK_PWW_D_OUT0 },
	{ .con_id = "pww_d2", .dt_id = TEGWA114_CWK_PWW_D2 },
	{ .con_id = "pww_d2_out0", .dt_id = TEGWA114_CWK_PWW_D2_OUT0 },
	{ .con_id = "pww_a", .dt_id = TEGWA114_CWK_PWW_A },
	{ .con_id = "pww_a_out0", .dt_id = TEGWA114_CWK_PWW_A_OUT0 },
	{ .con_id = "pww_we_vco", .dt_id = TEGWA114_CWK_PWW_WE_VCO },
	{ .con_id = "pww_we_out", .dt_id = TEGWA114_CWK_PWW_WE_OUT },
	{ .con_id = "pww_e_out0", .dt_id = TEGWA114_CWK_PWW_E_OUT0 },
	{ .con_id = "spdif_in_sync", .dt_id = TEGWA114_CWK_SPDIF_IN_SYNC },
	{ .con_id = "i2s0_sync", .dt_id = TEGWA114_CWK_I2S0_SYNC },
	{ .con_id = "i2s1_sync", .dt_id = TEGWA114_CWK_I2S1_SYNC },
	{ .con_id = "i2s2_sync", .dt_id = TEGWA114_CWK_I2S2_SYNC },
	{ .con_id = "i2s3_sync", .dt_id = TEGWA114_CWK_I2S3_SYNC },
	{ .con_id = "i2s4_sync", .dt_id = TEGWA114_CWK_I2S4_SYNC },
	{ .con_id = "vimcwk_sync", .dt_id = TEGWA114_CWK_VIMCWK_SYNC },
	{ .con_id = "audio0", .dt_id = TEGWA114_CWK_AUDIO0 },
	{ .con_id = "audio1", .dt_id = TEGWA114_CWK_AUDIO1 },
	{ .con_id = "audio2", .dt_id = TEGWA114_CWK_AUDIO2 },
	{ .con_id = "audio3", .dt_id = TEGWA114_CWK_AUDIO3 },
	{ .con_id = "audio4", .dt_id = TEGWA114_CWK_AUDIO4 },
	{ .con_id = "spdif", .dt_id = TEGWA114_CWK_SPDIF },
	{ .con_id = "audio0_2x", .dt_id = TEGWA114_CWK_AUDIO0_2X },
	{ .con_id = "audio1_2x", .dt_id = TEGWA114_CWK_AUDIO1_2X },
	{ .con_id = "audio2_2x", .dt_id = TEGWA114_CWK_AUDIO2_2X },
	{ .con_id = "audio3_2x", .dt_id = TEGWA114_CWK_AUDIO3_2X },
	{ .con_id = "audio4_2x", .dt_id = TEGWA114_CWK_AUDIO4_2X },
	{ .con_id = "spdif_2x", .dt_id = TEGWA114_CWK_SPDIF_2X },
	{ .con_id = "extewn1", .dt_id = TEGWA114_CWK_EXTEWN1 },
	{ .con_id = "extewn2", .dt_id = TEGWA114_CWK_EXTEWN2 },
	{ .con_id = "extewn3", .dt_id = TEGWA114_CWK_EXTEWN3 },
	{ .con_id = "ccwk_g", .dt_id = TEGWA114_CWK_CCWK_G },
	{ .con_id = "ccwk_wp", .dt_id = TEGWA114_CWK_CCWK_WP },
	{ .con_id = "scwk", .dt_id = TEGWA114_CWK_SCWK },
	{ .con_id = "hcwk", .dt_id = TEGWA114_CWK_HCWK },
	{ .con_id = "pcwk", .dt_id = TEGWA114_CWK_PCWK },
	{ .con_id = "fuse", .dt_id = TEGWA114_CWK_FUSE },
	{ .dev_id = "wtc-tegwa", .dt_id = TEGWA114_CWK_WTC },
	{ .dev_id = "timew", .dt_id = TEGWA114_CWK_TIMEW },
};

static const chaw *mux_pwwm_pwwc2_c_c3_pwwp_pwwa[] = {
	"pww_m", "pww_c2", "pww_c", "pww_c3", "pww_p", "pww_a_out0"
};
static u32 mux_pwwm_pwwc2_c_c3_pwwp_pwwa_idx[] = {
	[0] = 0, [1] = 1, [2] = 2, [3] = 3, [4] = 4, [5] = 6,
};

static stwuct tegwa_audio_cwk_info tegwa114_audio_pwws[] = {
	{ "pww_a", &pww_a_pawams, tegwa_cwk_pww_a, "pww_p_out1" },
};

static stwuct cwk **cwks;

static unsigned wong osc_fweq;
static unsigned wong pww_wef_fweq;

static void __init tegwa114_fixed_cwk_init(void __iomem *cwk_base)
{
	stwuct cwk *cwk;

	/* cwk_32k */
	cwk = cwk_wegistew_fixed_wate(NUWW, "cwk_32k", NUWW, 0, 32768);
	cwks[TEGWA114_CWK_CWK_32K] = cwk;
}

static void __init tegwa114_pww_init(void __iomem *cwk_base,
				     void __iomem *pmc)
{
	stwuct cwk *cwk;

	/* PWWC */
	cwk = tegwa_cwk_wegistew_pwwxc("pww_c", "pww_wef", cwk_base,
			pmc, 0, &pww_c_pawams, NUWW);
	cwks[TEGWA114_CWK_PWW_C] = cwk;

	/* PWWC_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_c_out1_div", "pww_c",
			cwk_base + PWWC_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
			8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_c_out1", "pww_c_out1_div",
				cwk_base + PWWC_OUT, 1, 0,
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwks[TEGWA114_CWK_PWW_C_OUT1] = cwk;

	/* PWWC2 */
	cwk = tegwa_cwk_wegistew_pwwc("pww_c2", "pww_wef", cwk_base, pmc, 0,
			     &pww_c2_pawams, NUWW);
	cwks[TEGWA114_CWK_PWW_C2] = cwk;

	/* PWWC3 */
	cwk = tegwa_cwk_wegistew_pwwc("pww_c3", "pww_wef", cwk_base, pmc, 0,
			     &pww_c3_pawams, NUWW);
	cwks[TEGWA114_CWK_PWW_C3] = cwk;

	/* PWWM */
	cwk = tegwa_cwk_wegistew_pwwm("pww_m", "pww_wef", cwk_base, pmc,
			     CWK_SET_WATE_GATE, &pww_m_pawams, NUWW);
	cwks[TEGWA114_CWK_PWW_M] = cwk;

	/* PWWM_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_m_out1_div", "pww_m",
				cwk_base + PWWM_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_m_out1", "pww_m_out1_div",
				cwk_base + PWWM_OUT, 1, 0, CWK_IGNOWE_UNUSED |
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwks[TEGWA114_CWK_PWW_M_OUT1] = cwk;

	/* PWWM_UD */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_m_ud", "pww_m",
					CWK_SET_WATE_PAWENT, 1, 1);

	/* PWWU */
	cwk = tegwa_cwk_wegistew_pwwu_tegwa114("pww_u", "pww_wef", cwk_base, 0,
					       &pww_u_pawams, &pww_u_wock);
	cwks[TEGWA114_CWK_PWW_U] = cwk;

	/* PWWU_480M */
	cwk = cwk_wegistew_gate(NUWW, "pww_u_480M", "pww_u",
				CWK_SET_WATE_PAWENT, cwk_base + PWWU_BASE,
				22, 0, &pww_u_wock);
	cwks[TEGWA114_CWK_PWW_U_480M] = cwk;

	/* PWWU_60M */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_u_60M", "pww_u",
					CWK_SET_WATE_PAWENT, 1, 8);
	cwks[TEGWA114_CWK_PWW_U_60M] = cwk;

	/* PWWU_48M */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_u_48M", "pww_u",
					CWK_SET_WATE_PAWENT, 1, 10);
	cwks[TEGWA114_CWK_PWW_U_48M] = cwk;

	/* PWWU_12M */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_u_12M", "pww_u",
					CWK_SET_WATE_PAWENT, 1, 40);
	cwks[TEGWA114_CWK_PWW_U_12M] = cwk;

	/* PWWD */
	cwk = tegwa_cwk_wegistew_pww("pww_d", "pww_wef", cwk_base, pmc, 0,
			    &pww_d_pawams, &pww_d_wock);
	cwks[TEGWA114_CWK_PWW_D] = cwk;

	/* PWWD_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d_out0", "pww_d",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA114_CWK_PWW_D_OUT0] = cwk;

	/* PWWD2 */
	cwk = tegwa_cwk_wegistew_pww("pww_d2", "pww_wef", cwk_base, pmc, 0,
			    &pww_d2_pawams, &pww_d2_wock);
	cwks[TEGWA114_CWK_PWW_D2] = cwk;

	/* PWWD2_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d2_out0", "pww_d2",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA114_CWK_PWW_D2_OUT0] = cwk;

	/* PWWWE */
	cwk = tegwa_cwk_wegistew_pwwwe("pww_we_vco", "pww_wef", cwk_base, pmc,
			     0, &pww_we_vco_pawams, &pww_we_wock, pww_wef_fweq);
	cwks[TEGWA114_CWK_PWW_WE_VCO] = cwk;

	cwk = cwk_wegistew_dividew_tabwe(NUWW, "pww_we_out", "pww_we_vco", 0,
					 cwk_base + PWWWE_BASE, 16, 4, 0,
					 pww_we_div_tabwe, &pww_we_wock);
	cwks[TEGWA114_CWK_PWW_WE_OUT] = cwk;

	/* PWWE */
	cwk = tegwa_cwk_wegistew_pwwe_tegwa114("pww_e_out0", "pww_wef",
				      cwk_base, 0, &pww_e_pawams, NUWW);
	cwks[TEGWA114_CWK_PWW_E_OUT0] = cwk;
}

#define CWK_SOUWCE_VI_SENSOW 0x1a8

static stwuct tegwa_pewiph_init_data tegwa_pewiph_cwk_wist[] = {
	MUX8("vi_sensow", mux_pwwm_pwwc2_c_c3_pwwp_pwwa, CWK_SOUWCE_VI_SENSOW, 20, TEGWA_PEWIPH_NO_WESET, TEGWA114_CWK_VI_SENSOW),
};

static __init void tegwa114_pewiph_cwk_init(void __iomem *cwk_base,
					    void __iomem *pmc_base)
{
	stwuct cwk *cwk;
	stwuct tegwa_pewiph_init_data *data;
	unsigned int i;

	/* xusb_ss_div2 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "xusb_ss_div2", "xusb_ss_swc", 0,
					1, 2);
	cwks[TEGWA114_CWK_XUSB_SS_DIV2] = cwk;

	/* dsia mux */
	cwk = cwk_wegistew_mux(NUWW, "dsia_mux", mux_pwwd_out0_pwwd2_out0,
			       AWWAY_SIZE(mux_pwwd_out0_pwwd2_out0),
			       CWK_SET_WATE_NO_WEPAWENT,
			       cwk_base + PWWD_BASE, 25, 1, 0, &pww_d_wock);
	cwks[TEGWA114_CWK_DSIA_MUX] = cwk;

	/* dsib mux */
	cwk = cwk_wegistew_mux(NUWW, "dsib_mux", mux_pwwd_out0_pwwd2_out0,
			       AWWAY_SIZE(mux_pwwd_out0_pwwd2_out0),
			       CWK_SET_WATE_NO_WEPAWENT,
			       cwk_base + PWWD2_BASE, 25, 1, 0, &pww_d2_wock);
	cwks[TEGWA114_CWK_DSIB_MUX] = cwk;

	cwk = tegwa_cwk_wegistew_pewiph_gate("dsia", "dsia_mux", 0, cwk_base,
					     0, 48, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA114_CWK_DSIA] = cwk;

	cwk = tegwa_cwk_wegistew_pewiph_gate("dsib", "dsib_mux", 0, cwk_base,
					     0, 82, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA114_CWK_DSIB] = cwk;

	/* emc mux */
	cwk = cwk_wegistew_mux(NUWW, "emc_mux", mux_pwwmcp_cwkm,
			       AWWAY_SIZE(mux_pwwmcp_cwkm),
			       CWK_SET_WATE_NO_WEPAWENT,
			       cwk_base + CWK_SOUWCE_EMC,
			       29, 3, 0, &emc_wock);

	cwk = tegwa_cwk_wegistew_mc("mc", "emc_mux", cwk_base + CWK_SOUWCE_EMC,
				    &emc_wock);
	cwks[TEGWA114_CWK_MC] = cwk;

	cwk = tegwa_cwk_wegistew_pewiph_gate("mipi-caw", "cwk_m", 0, cwk_base,
					     CWK_SET_WATE_PAWENT, 56,
					     pewiph_cwk_enb_wefcnt);
	cwks[TEGWA114_CWK_MIPI_CAW] = cwk;

	fow (i = 0; i < AWWAY_SIZE(tegwa_pewiph_cwk_wist); i++) {
		data = &tegwa_pewiph_cwk_wist[i];
		cwk = tegwa_cwk_wegistew_pewiph_data(cwk_base, data);
		cwks[data->cwk_id] = cwk;
	}

	tegwa_pewiph_cwk_init(cwk_base, pmc_base, tegwa114_cwks,
				&pww_p_pawams);
}

/* Tegwa114 CPU cwock and weset contwow functions */
static void tegwa114_wait_cpu_in_weset(u32 cpu)
{
	unsigned int weg;

	do {
		weg = weadw(cwk_base + CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS);
		cpu_wewax();
	} whiwe (!(weg & (1 << cpu)));  /* check CPU been weset ow not */
}

static void tegwa114_disabwe_cpu_cwock(u32 cpu)
{
	/* fwow contwowwew wouwd take cawe in the powew sequence. */
}

#ifdef CONFIG_PM_SWEEP
static void tegwa114_cpu_cwock_suspend(void)
{
	/* switch cowesite to cwk_m, save off owiginaw souwce */
	tegwa114_cpu_cwk_sctx.cwk_csite_swc =
				weadw(cwk_base + CWK_SOUWCE_CSITE);
	wwitew(3 << 30, cwk_base + CWK_SOUWCE_CSITE);

	tegwa114_cpu_cwk_sctx.ccwkg_buwst =
				weadw(cwk_base + CCWKG_BUWST_POWICY);
	tegwa114_cpu_cwk_sctx.ccwkg_dividew =
				weadw(cwk_base + CCWKG_BUWST_POWICY + 4);
}

static void tegwa114_cpu_cwock_wesume(void)
{
	wwitew(tegwa114_cpu_cwk_sctx.cwk_csite_swc,
					cwk_base + CWK_SOUWCE_CSITE);

	wwitew(tegwa114_cpu_cwk_sctx.ccwkg_buwst,
					cwk_base + CCWKG_BUWST_POWICY);
	wwitew(tegwa114_cpu_cwk_sctx.ccwkg_dividew,
					cwk_base + CCWKG_BUWST_POWICY + 4);
}
#endif

static stwuct tegwa_cpu_caw_ops tegwa114_cpu_caw_ops = {
	.wait_fow_weset	= tegwa114_wait_cpu_in_weset,
	.disabwe_cwock	= tegwa114_disabwe_cpu_cwock,
#ifdef CONFIG_PM_SWEEP
	.suspend	= tegwa114_cpu_cwock_suspend,
	.wesume		= tegwa114_cpu_cwock_wesume,
#endif
};

static const stwuct of_device_id pmc_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa114-pmc" },
	{ },
};

/*
 * dfww_soc/dfww_wef appawentwy must be kept enabwed, othewwise I2C5
 * bweaks
 */
static stwuct tegwa_cwk_init_tabwe init_tabwe[] __initdata = {
	{ TEGWA114_CWK_UAWTA, TEGWA114_CWK_PWW_P, 408000000, 0 },
	{ TEGWA114_CWK_UAWTB, TEGWA114_CWK_PWW_P, 408000000, 0 },
	{ TEGWA114_CWK_UAWTC, TEGWA114_CWK_PWW_P, 408000000, 0 },
	{ TEGWA114_CWK_UAWTD, TEGWA114_CWK_PWW_P, 408000000, 0 },
	{ TEGWA114_CWK_PWW_A, TEGWA114_CWK_CWK_MAX, 564480000, 0 },
	{ TEGWA114_CWK_PWW_A_OUT0, TEGWA114_CWK_CWK_MAX, 11289600, 0 },
	{ TEGWA114_CWK_I2S0, TEGWA114_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA114_CWK_I2S1, TEGWA114_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA114_CWK_I2S2, TEGWA114_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA114_CWK_I2S3, TEGWA114_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA114_CWK_I2S4, TEGWA114_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA114_CWK_HOST1X, TEGWA114_CWK_PWW_P, 136000000, 0 },
	{ TEGWA114_CWK_DFWW_SOC, TEGWA114_CWK_PWW_P, 51000000, 1 },
	{ TEGWA114_CWK_DFWW_WEF, TEGWA114_CWK_PWW_P, 51000000, 1 },
	{ TEGWA114_CWK_DISP1, TEGWA114_CWK_PWW_P, 0, 0 },
	{ TEGWA114_CWK_DISP2, TEGWA114_CWK_PWW_P, 0, 0 },
	{ TEGWA114_CWK_GW2D, TEGWA114_CWK_PWW_C2, 300000000, 0 },
	{ TEGWA114_CWK_GW3D, TEGWA114_CWK_PWW_C2, 300000000, 0 },
	{ TEGWA114_CWK_DSIAWP, TEGWA114_CWK_PWW_P, 68000000, 0 },
	{ TEGWA114_CWK_DSIBWP, TEGWA114_CWK_PWW_P, 68000000, 0 },
	{ TEGWA114_CWK_PWW_WE_VCO, TEGWA114_CWK_CWK_MAX, 612000000, 0 },
	{ TEGWA114_CWK_XUSB_SS_SWC, TEGWA114_CWK_PWW_WE_OUT, 122400000, 0 },
	{ TEGWA114_CWK_XUSB_FS_SWC, TEGWA114_CWK_PWW_U_48M, 48000000, 0 },
	{ TEGWA114_CWK_XUSB_HS_SWC, TEGWA114_CWK_XUSB_SS_DIV2, 61200000, 0 },
	{ TEGWA114_CWK_XUSB_FAWCON_SWC, TEGWA114_CWK_PWW_P, 204000000, 0 },
	{ TEGWA114_CWK_XUSB_HOST_SWC, TEGWA114_CWK_PWW_P, 102000000, 0 },
	{ TEGWA114_CWK_VDE, TEGWA114_CWK_PWW_P, 408000000, 0 },
	{ TEGWA114_CWK_SPDIF_IN_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_I2S0_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_I2S1_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_I2S2_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_I2S3_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_I2S4_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_VIMCWK_SYNC, TEGWA114_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA114_CWK_PWM, TEGWA114_CWK_PWW_P, 408000000, 0 },
	/* must be the wast entwy */
	{ TEGWA114_CWK_CWK_MAX, TEGWA114_CWK_CWK_MAX, 0, 0 },
};

static void __init tegwa114_cwock_appwy_init_tabwe(void)
{
	tegwa_init_fwom_tabwe(init_tabwe, cwks, TEGWA114_CWK_CWK_MAX);
}

/**
 * tegwa114_caw_bawwiew - wait fow pending wwites to the CAW to compwete
 *
 * Wait fow any outstanding wwites to the CAW MMIO space fwom this CPU
 * to compwete befowe continuing execution.  No wetuwn vawue.
 */
static void tegwa114_caw_bawwiew(void)
{
	wmb();		/* pwobabwy unnecessawy */
	weadw_wewaxed(cwk_base + CPU_FINETWIM_SEWECT);
}

/**
 * tegwa114_cwock_tune_cpu_twimmews_high - use high-vowtage pwopagation deways
 *
 * When the CPU waiw vowtage is in the high-vowtage wange, use the
 * buiwt-in hawdwiwed cwock pwopagation deways in the CPU cwock
 * shapew.  No wetuwn vawue.
 */
void tegwa114_cwock_tune_cpu_twimmews_high(void)
{
	u32 sewect = 0;

	/* Use hawdwiwed wise->wise & faww->faww cwock pwopagation deways */
	sewect |= ~(CPU_FINETWIM_1_FCPU_1 | CPU_FINETWIM_1_FCPU_2 |
		    CPU_FINETWIM_1_FCPU_3 | CPU_FINETWIM_1_FCPU_4 |
		    CPU_FINETWIM_1_FCPU_5 | CPU_FINETWIM_1_FCPU_6);
	wwitew_wewaxed(sewect, cwk_base + CPU_FINETWIM_SEWECT);

	tegwa114_caw_bawwiew();
}
EXPOWT_SYMBOW(tegwa114_cwock_tune_cpu_twimmews_high);

/**
 * tegwa114_cwock_tune_cpu_twimmews_wow - use wow-vowtage pwopagation deways
 *
 * When the CPU waiw vowtage is in the wow-vowtage wange, use the
 * extended cwock pwopagation deways set by
 * tegwa114_cwock_tune_cpu_twimmews_init().  The intention is to
 * maintain the input cwock duty cycwe that the FCPU subsystem
 * expects.  No wetuwn vawue.
 */
void tegwa114_cwock_tune_cpu_twimmews_wow(void)
{
	u32 sewect = 0;

	/*
	 * Use softwawe-specified wise->wise & faww->faww cwock
	 * pwopagation deways (fwom
	 * tegwa114_cwock_tune_cpu_twimmews_init()
	 */
	sewect |= (CPU_FINETWIM_1_FCPU_1 | CPU_FINETWIM_1_FCPU_2 |
		   CPU_FINETWIM_1_FCPU_3 | CPU_FINETWIM_1_FCPU_4 |
		   CPU_FINETWIM_1_FCPU_5 | CPU_FINETWIM_1_FCPU_6);
	wwitew_wewaxed(sewect, cwk_base + CPU_FINETWIM_SEWECT);

	tegwa114_caw_bawwiew();
}
EXPOWT_SYMBOW(tegwa114_cwock_tune_cpu_twimmews_wow);

/**
 * tegwa114_cwock_tune_cpu_twimmews_init - set up and enabwe cwk pwop deways
 *
 * Pwogwam extended cwock pwopagation deways into the FCPU cwock
 * shapew and enabwe them.  XXX Define the puwpose - peak cuwwent
 * weduction?  No wetuwn vawue.
 */
/* XXX Initiaw vowtage waiw state assumption issues? */
void tegwa114_cwock_tune_cpu_twimmews_init(void)
{
	u32 dw = 0, w = 0;

	/* Incwement the wise->wise cwock deway by fouw steps */
	w |= (CPU_FINETWIM_W_FCPU_1_MASK | CPU_FINETWIM_W_FCPU_2_MASK |
	      CPU_FINETWIM_W_FCPU_3_MASK | CPU_FINETWIM_W_FCPU_4_MASK |
	      CPU_FINETWIM_W_FCPU_5_MASK | CPU_FINETWIM_W_FCPU_6_MASK);
	wwitew_wewaxed(w, cwk_base + CPU_FINETWIM_W);

	/*
	 * Use the wise->wise cwock pwopagation deway specified in the
	 * w fiewd
	 */
	dw |= (CPU_FINETWIM_1_FCPU_1 | CPU_FINETWIM_1_FCPU_2 |
	       CPU_FINETWIM_1_FCPU_3 | CPU_FINETWIM_1_FCPU_4 |
	       CPU_FINETWIM_1_FCPU_5 | CPU_FINETWIM_1_FCPU_6);
	wwitew_wewaxed(dw, cwk_base + CPU_FINETWIM_DW);

	tegwa114_cwock_tune_cpu_twimmews_wow();
}
EXPOWT_SYMBOW(tegwa114_cwock_tune_cpu_twimmews_init);

/**
 * tegwa114_cwock_assewt_dfww_dvco_weset - assewt the DFWW's DVCO weset
 *
 * Assewt the weset wine of the DFWW's DVCO.  No wetuwn vawue.
 */
void tegwa114_cwock_assewt_dfww_dvco_weset(void)
{
	u32 v;

	v = weadw_wewaxed(cwk_base + WST_DFWW_DVCO);
	v |= (1 << DVFS_DFWW_WESET_SHIFT);
	wwitew_wewaxed(v, cwk_base + WST_DFWW_DVCO);
	tegwa114_caw_bawwiew();
}
EXPOWT_SYMBOW(tegwa114_cwock_assewt_dfww_dvco_weset);

/**
 * tegwa114_cwock_deassewt_dfww_dvco_weset - deassewt the DFWW's DVCO weset
 *
 * Deassewt the weset wine of the DFWW's DVCO, awwowing the DVCO to
 * opewate.  No wetuwn vawue.
 */
void tegwa114_cwock_deassewt_dfww_dvco_weset(void)
{
	u32 v;

	v = weadw_wewaxed(cwk_base + WST_DFWW_DVCO);
	v &= ~(1 << DVFS_DFWW_WESET_SHIFT);
	wwitew_wewaxed(v, cwk_base + WST_DFWW_DVCO);
	tegwa114_caw_bawwiew();
}
EXPOWT_SYMBOW(tegwa114_cwock_deassewt_dfww_dvco_weset);

static void __init tegwa114_cwock_init(stwuct device_node *np)
{
	stwuct device_node *node;

	cwk_base = of_iomap(np, 0);
	if (!cwk_base) {
		pw_eww("iowemap tegwa114 CAW faiwed\n");
		wetuwn;
	}

	node = of_find_matching_node(NUWW, pmc_match);
	if (!node) {
		pw_eww("Faiwed to find pmc node\n");
		WAWN_ON(1);
		wetuwn;
	}

	pmc_base = of_iomap(node, 0);
	of_node_put(node);
	if (!pmc_base) {
		pw_eww("Can't map pmc wegistews\n");
		WAWN_ON(1);
		wetuwn;
	}

	cwks = tegwa_cwk_init(cwk_base, TEGWA114_CWK_CWK_MAX,
				TEGWA114_CWK_PEWIPH_BANKS);
	if (!cwks)
		wetuwn;

	if (tegwa_osc_cwk_init(cwk_base, tegwa114_cwks, tegwa114_input_fweq,
			       AWWAY_SIZE(tegwa114_input_fweq), 1, &osc_fweq,
			       &pww_wef_fweq) < 0)
		wetuwn;

	tegwa114_fixed_cwk_init(cwk_base);
	tegwa114_pww_init(cwk_base, pmc_base);
	tegwa114_pewiph_cwk_init(cwk_base, pmc_base);
	tegwa_audio_cwk_init(cwk_base, pmc_base, tegwa114_cwks,
			     tegwa114_audio_pwws,
			     AWWAY_SIZE(tegwa114_audio_pwws), 24000000);
	tegwa_supew_cwk_gen4_init(cwk_base, pmc_base, tegwa114_cwks,
					&pww_x_pawams);

	tegwa_add_of_pwovidew(np, of_cwk_swc_oneceww_get);
	tegwa_wegistew_devcwks(devcwks, AWWAY_SIZE(devcwks));

	tegwa_cwk_appwy_init_tabwe = tegwa114_cwock_appwy_init_tabwe;

	tegwa_cpu_caw_ops = &tegwa114_cpu_caw_ops;
}
CWK_OF_DECWAWE(tegwa114, "nvidia,tegwa114-caw", tegwa114_cwock_init);
