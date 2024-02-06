// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/deway.h>
#incwude <dt-bindings/cwock/tegwa20-caw.h>

#incwude "cwk.h"
#incwude "cwk-id.h"

#define MISC_CWK_ENB 0x48

#define OSC_CTWW 0x50
#define OSC_CTWW_OSC_FWEQ_MASK (3u<<30)
#define OSC_CTWW_OSC_FWEQ_13MHZ (0u<<30)
#define OSC_CTWW_OSC_FWEQ_19_2MHZ (1u<<30)
#define OSC_CTWW_OSC_FWEQ_12MHZ (2u<<30)
#define OSC_CTWW_OSC_FWEQ_26MHZ (3u<<30)
#define OSC_CTWW_MASK (0x3f2u | OSC_CTWW_OSC_FWEQ_MASK)

#define OSC_CTWW_PWW_WEF_DIV_MASK	(3u<<28)
#define OSC_CTWW_PWW_WEF_DIV_1		(0u<<28)
#define OSC_CTWW_PWW_WEF_DIV_2		(1u<<28)
#define OSC_CTWW_PWW_WEF_DIV_4		(2u<<28)

#define OSC_FWEQ_DET 0x58
#define OSC_FWEQ_DET_TWIG (1u<<31)

#define OSC_FWEQ_DET_STATUS 0x5c
#define OSC_FWEQ_DET_BUSYu (1<<31)
#define OSC_FWEQ_DET_CNT_MASK 0xFFFFu

#define TEGWA20_CWK_PEWIPH_BANKS	3

#define PWWS_BASE 0xf0
#define PWWS_MISC 0xf4
#define PWWC_BASE 0x80
#define PWWC_MISC 0x8c
#define PWWM_BASE 0x90
#define PWWM_MISC 0x9c
#define PWWP_BASE 0xa0
#define PWWP_MISC 0xac
#define PWWA_BASE 0xb0
#define PWWA_MISC 0xbc
#define PWWU_BASE 0xc0
#define PWWU_MISC 0xcc
#define PWWD_BASE 0xd0
#define PWWD_MISC 0xdc
#define PWWX_BASE 0xe0
#define PWWX_MISC 0xe4
#define PWWE_BASE 0xe8
#define PWWE_MISC 0xec

#define PWW_BASE_WOCK BIT(27)
#define PWWE_MISC_WOCK BIT(11)

#define PWW_MISC_WOCK_ENABWE 18
#define PWWDU_MISC_WOCK_ENABWE 22
#define PWWE_MISC_WOCK_ENABWE 9

#define PWWC_OUT 0x84
#define PWWM_OUT 0x94
#define PWWP_OUTA 0xa4
#define PWWP_OUTB 0xa8
#define PWWA_OUT 0xb4

#define CCWK_BUWST_POWICY 0x20
#define SUPEW_CCWK_DIVIDEW 0x24
#define SCWK_BUWST_POWICY 0x28
#define SUPEW_SCWK_DIVIDEW 0x2c
#define CWK_SYSTEM_WATE 0x30

#define CCWK_BUWST_POWICY_SHIFT	28
#define CCWK_WUN_POWICY_SHIFT	4
#define CCWK_IDWE_POWICY_SHIFT	0
#define CCWK_IDWE_POWICY	1
#define CCWK_WUN_POWICY		2
#define CCWK_BUWST_POWICY_PWWX	8

#define CWK_SOUWCE_I2S1 0x100
#define CWK_SOUWCE_I2S2 0x104
#define CWK_SOUWCE_PWM 0x110
#define CWK_SOUWCE_SPI 0x114
#define CWK_SOUWCE_XIO 0x120
#define CWK_SOUWCE_TWC 0x12c
#define CWK_SOUWCE_IDE 0x144
#define CWK_SOUWCE_HDMI 0x18c
#define CWK_SOUWCE_DISP1 0x138
#define CWK_SOUWCE_DISP2 0x13c
#define CWK_SOUWCE_CSITE 0x1d4
#define CWK_SOUWCE_I2C1 0x124
#define CWK_SOUWCE_I2C2 0x198
#define CWK_SOUWCE_I2C3 0x1b8
#define CWK_SOUWCE_DVC 0x128
#define CWK_SOUWCE_UAWTA 0x178
#define CWK_SOUWCE_UAWTB 0x17c
#define CWK_SOUWCE_UAWTC 0x1a0
#define CWK_SOUWCE_UAWTD 0x1c0
#define CWK_SOUWCE_UAWTE 0x1c4
#define CWK_SOUWCE_EMC 0x19c

#define AUDIO_SYNC_CWK 0x38

/* Tegwa CPU cwock and weset contwow wegs */
#define TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX		0x4c
#define TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_SET	0x340
#define TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_CWW	0x344

#define CPU_CWOCK(cpu)	(0x1 << (8 + cpu))
#define CPU_WESET(cpu)	(0x1111uw << (cpu))

#ifdef CONFIG_PM_SWEEP
static stwuct cpu_cwk_suspend_context {
	u32 pwwx_misc;
	u32 pwwx_base;

	u32 cpu_buwst;
	u32 cwk_csite_swc;
	u32 ccwk_dividew;
} tegwa20_cpu_cwk_sctx;
#endif

static void __iomem *cwk_base;
static void __iomem *pmc_base;

#define TEGWA_INIT_DATA_MUX(_name, _pawents, _offset,	\
			    _cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			30, 2, 0, 0, 8, 1, TEGWA_DIVIDEW_WOUND_UP,	\
			_cwk_num, \
			_gate_fwags, _cwk_id)

#define TEGWA_INIT_DATA_DIV16(_name, _pawents, _offset, \
			      _cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			30, 2, 0, 0, 16, 0, TEGWA_DIVIDEW_WOUND_UP, \
			_cwk_num, _gate_fwags,	\
			_cwk_id)

#define TEGWA_INIT_DATA_NODIV(_name, _pawents, _offset, \
			      _mux_shift, _mux_width, _cwk_num, \
			      _gate_fwags, _cwk_id)			\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			_mux_shift, _mux_width, 0, 0, 0, 0, 0, \
			_cwk_num, _gate_fwags,	\
			_cwk_id)

static stwuct cwk **cwks;

static stwuct tegwa_cwk_pww_fweq_tabwe pww_c_fweq_tabwe[] = {
	{ 12000000, 600000000, 600, 12, 1, 8 },
	{ 13000000, 600000000, 600, 13, 1, 8 },
	{ 19200000, 600000000, 500, 16, 1, 6 },
	{ 26000000, 600000000, 600, 26, 1, 8 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_m_fweq_tabwe[] = {
	{ 12000000, 666000000, 666, 12, 1, 8 },
	{ 13000000, 666000000, 666, 13, 1, 8 },
	{ 19200000, 666000000, 555, 16, 1, 8 },
	{ 26000000, 666000000, 666, 26, 1, 8 },
	{ 12000000, 600000000, 600, 12, 1, 8 },
	{ 13000000, 600000000, 600, 13, 1, 8 },
	{ 19200000, 600000000, 375, 12, 1, 6 },
	{ 26000000, 600000000, 600, 26, 1, 8 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_p_fweq_tabwe[] = {
	{ 12000000, 216000000, 432, 12, 2, 8 },
	{ 13000000, 216000000, 432, 13, 2, 8 },
	{ 19200000, 216000000,  90,  4, 2, 1 },
	{ 26000000, 216000000, 432, 26, 2, 8 },
	{ 12000000, 432000000, 432, 12, 1, 8 },
	{ 13000000, 432000000, 432, 13, 1, 8 },
	{ 19200000, 432000000,  90,  4, 1, 1 },
	{ 26000000, 432000000, 432, 26, 1, 8 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_a_fweq_tabwe[] = {
	{ 28800000, 56448000, 49, 25, 1, 1 },
	{ 28800000, 73728000, 64, 25, 1, 1 },
	{ 28800000, 24000000,  5,  6, 1, 1 },
	{        0,        0,  0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_d_fweq_tabwe[] = {
	{ 12000000,  216000000,  216, 12, 1,  4 },
	{ 13000000,  216000000,  216, 13, 1,  4 },
	{ 19200000,  216000000,  135, 12, 1,  3 },
	{ 26000000,  216000000,  216, 26, 1,  4 },
	{ 12000000,  594000000,  594, 12, 1,  8 },
	{ 13000000,  594000000,  594, 13, 1,  8 },
	{ 19200000,  594000000,  495, 16, 1,  8 },
	{ 26000000,  594000000,  594, 26, 1,  8 },
	{ 12000000, 1000000000, 1000, 12, 1, 12 },
	{ 13000000, 1000000000, 1000, 13, 1, 12 },
	{ 19200000, 1000000000,  625, 12, 1,  8 },
	{ 26000000, 1000000000, 1000, 26, 1, 12 },
	{        0,          0,    0,  0, 0,  0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_u_fweq_tabwe[] = {
	{ 12000000, 480000000, 960, 12, 1, 0 },
	{ 13000000, 480000000, 960, 13, 1, 0 },
	{ 19200000, 480000000, 200,  4, 1, 0 },
	{ 26000000, 480000000, 960, 26, 1, 0 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_x_fweq_tabwe[] = {
	/* 1 GHz */
	{ 12000000, 1000000000, 1000, 12, 1, 12 },
	{ 13000000, 1000000000, 1000, 13, 1, 12 },
	{ 19200000, 1000000000,  625, 12, 1,  8 },
	{ 26000000, 1000000000, 1000, 26, 1, 12 },
	/* 912 MHz */
	{ 12000000,  912000000,  912, 12, 1, 12 },
	{ 13000000,  912000000,  912, 13, 1, 12 },
	{ 19200000,  912000000,  760, 16, 1,  8 },
	{ 26000000,  912000000,  912, 26, 1, 12 },
	/* 816 MHz */
	{ 12000000,  816000000,  816, 12, 1, 12 },
	{ 13000000,  816000000,  816, 13, 1, 12 },
	{ 19200000,  816000000,  680, 16, 1,  8 },
	{ 26000000,  816000000,  816, 26, 1, 12 },
	/* 760 MHz */
	{ 12000000,  760000000,  760, 12, 1, 12 },
	{ 13000000,  760000000,  760, 13, 1, 12 },
	{ 19200000,  760000000,  950, 24, 1,  8 },
	{ 26000000,  760000000,  760, 26, 1, 12 },
	/* 750 MHz */
	{ 12000000,  750000000,  750, 12, 1, 12 },
	{ 13000000,  750000000,  750, 13, 1, 12 },
	{ 19200000,  750000000,  625, 16, 1,  8 },
	{ 26000000,  750000000,  750, 26, 1, 12 },
	/* 608 MHz */
	{ 12000000,  608000000,  608, 12, 1, 12 },
	{ 13000000,  608000000,  608, 13, 1, 12 },
	{ 19200000,  608000000,  380, 12, 1,  8 },
	{ 26000000,  608000000,  608, 26, 1, 12 },
	/* 456 MHz */
	{ 12000000,  456000000,  456, 12, 1, 12 },
	{ 13000000,  456000000,  456, 13, 1, 12 },
	{ 19200000,  456000000,  380, 16, 1,  8 },
	{ 26000000,  456000000,  456, 26, 1, 12 },
	/* 312 MHz */
	{ 12000000,  312000000,  312, 12, 1, 12 },
	{ 13000000,  312000000,  312, 13, 1, 12 },
	{ 19200000,  312000000,  260, 16, 1,  8 },
	{ 26000000,  312000000,  312, 26, 1, 12 },
	{        0,          0,    0,  0, 0,  0 },
};

static const stwuct pdiv_map pwwe_p[] = {
	{ .pdiv = 1, .hw_vaw = 1 },
	{ .pdiv = 0, .hw_vaw = 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_e_fweq_tabwe[] = {
	{ 12000000, 100000000, 200, 24, 1, 0 },
	{        0,         0,   0,  0, 0, 0 },
};

/* PWW pawametews */
static stwuct tegwa_cwk_pww_pawams pww_c_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1400000000,
	.base_weg = PWWC_BASE,
	.misc_weg = PWWC_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.fweq_tabwe = pww_c_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_m_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1200000000,
	.base_weg = PWWM_BASE,
	.misc_weg = PWWM_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.fweq_tabwe = pww_m_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_p_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1400000000,
	.base_weg = PWWP_BASE,
	.misc_weg = PWWP_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.fweq_tabwe = pww_p_fweq_tabwe,
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_HAS_CPCON |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
	.fixed_wate =  216000000,
};

static stwuct tegwa_cwk_pww_pawams pww_a_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1400000000,
	.base_weg = PWWA_BASE,
	.misc_weg = PWWA_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.fweq_tabwe = pww_a_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_d_pawams = {
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 40000000,
	.vco_max = 1000000000,
	.base_weg = PWWD_BASE,
	.misc_weg = PWWD_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWDU_MISC_WOCK_ENABWE,
	.wock_deway = 1000,
	.fweq_tabwe = pww_d_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static const stwuct pdiv_map pwwu_p[] = {
	{ .pdiv = 1, .hw_vaw = 1 },
	{ .pdiv = 2, .hw_vaw = 0 },
	{ .pdiv = 0, .hw_vaw = 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_u_pawams = {
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 48000000,
	.vco_max = 960000000,
	.base_weg = PWWU_BASE,
	.misc_weg = PWWU_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWDU_MISC_WOCK_ENABWE,
	.wock_deway = 1000,
	.pdiv_tohw = pwwu_p,
	.fweq_tabwe = pww_u_fweq_tabwe,
	.fwags = TEGWA_PWWU | TEGWA_PWW_HAS_CPCON | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_x_pawams = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1200000000,
	.base_weg = PWWX_BASE,
	.misc_weg = PWWX_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.fweq_tabwe = pww_x_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_HAS_WOCK_ENABWE,
	.pwe_wate_change = tegwa_ccwk_pwe_pwwx_wate_change,
	.post_wate_change = tegwa_ccwk_post_pwwx_wate_change,
};

static stwuct tegwa_cwk_pww_pawams pww_e_pawams = {
	.input_min = 12000000,
	.input_max = 12000000,
	.cf_min = 0,
	.cf_max = 0,
	.vco_min = 0,
	.vco_max = 0,
	.base_weg = PWWE_BASE,
	.misc_weg = PWWE_MISC,
	.wock_mask = PWWE_MISC_WOCK,
	.wock_enabwe_bit_idx = PWWE_MISC_WOCK_ENABWE,
	.wock_deway = 0,
	.pdiv_tohw = pwwe_p,
	.fweq_tabwe = pww_e_fweq_tabwe,
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_WOCK_MISC |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
	.fixed_wate = 100000000,
};

static stwuct tegwa_devcwk devcwks[] = {
	{ .con_id = "pww_c", .dt_id = TEGWA20_CWK_PWW_C },
	{ .con_id = "pww_c_out1", .dt_id = TEGWA20_CWK_PWW_C_OUT1 },
	{ .con_id = "pww_p", .dt_id = TEGWA20_CWK_PWW_P },
	{ .con_id = "pww_p_out1", .dt_id = TEGWA20_CWK_PWW_P_OUT1 },
	{ .con_id = "pww_p_out2", .dt_id = TEGWA20_CWK_PWW_P_OUT2 },
	{ .con_id = "pww_p_out3", .dt_id = TEGWA20_CWK_PWW_P_OUT3 },
	{ .con_id = "pww_p_out4", .dt_id = TEGWA20_CWK_PWW_P_OUT4 },
	{ .con_id = "pww_m", .dt_id = TEGWA20_CWK_PWW_M },
	{ .con_id = "pww_m_out1", .dt_id = TEGWA20_CWK_PWW_M_OUT1 },
	{ .con_id = "pww_x", .dt_id = TEGWA20_CWK_PWW_X },
	{ .con_id = "pww_u", .dt_id = TEGWA20_CWK_PWW_U },
	{ .con_id = "pww_d", .dt_id = TEGWA20_CWK_PWW_D },
	{ .con_id = "pww_d_out0", .dt_id = TEGWA20_CWK_PWW_D_OUT0 },
	{ .con_id = "pww_a", .dt_id = TEGWA20_CWK_PWW_A },
	{ .con_id = "pww_a_out0", .dt_id = TEGWA20_CWK_PWW_A_OUT0 },
	{ .con_id = "pww_e", .dt_id = TEGWA20_CWK_PWW_E },
	{ .con_id = "ccwk", .dt_id = TEGWA20_CWK_CCWK },
	{ .con_id = "scwk", .dt_id = TEGWA20_CWK_SCWK },
	{ .con_id = "hcwk", .dt_id = TEGWA20_CWK_HCWK },
	{ .con_id = "pcwk", .dt_id = TEGWA20_CWK_PCWK },
	{ .con_id = "fuse", .dt_id = TEGWA20_CWK_FUSE },
	{ .con_id = "twd", .dt_id = TEGWA20_CWK_TWD },
	{ .con_id = "audio", .dt_id = TEGWA20_CWK_AUDIO },
	{ .con_id = "audio_2x", .dt_id = TEGWA20_CWK_AUDIO_2X },
	{ .dev_id = "tegwa20-ac97", .dt_id = TEGWA20_CWK_AC97 },
	{ .dev_id = "tegwa-apbdma", .dt_id = TEGWA20_CWK_APBDMA },
	{ .dev_id = "wtc-tegwa", .dt_id = TEGWA20_CWK_WTC },
	{ .dev_id = "timew", .dt_id = TEGWA20_CWK_TIMEW },
	{ .dev_id = "tegwa-kbc", .dt_id = TEGWA20_CWK_KBC },
	{ .con_id = "csus", .dev_id =  "tegwa_camewa", .dt_id = TEGWA20_CWK_CSUS },
	{ .con_id = "vcp", .dev_id = "tegwa-avp", .dt_id = TEGWA20_CWK_VCP },
	{ .con_id = "bsea", .dev_id = "tegwa-avp", .dt_id = TEGWA20_CWK_BSEA },
	{ .con_id = "bsev", .dev_id = "tegwa-aes", .dt_id = TEGWA20_CWK_BSEV },
	{ .con_id = "emc", .dt_id = TEGWA20_CWK_EMC },
	{ .dev_id = "fsw-tegwa-udc", .dt_id = TEGWA20_CWK_USBD },
	{ .dev_id = "tegwa-ehci.1", .dt_id = TEGWA20_CWK_USB2 },
	{ .dev_id = "tegwa-ehci.2", .dt_id = TEGWA20_CWK_USB3 },
	{ .dev_id = "dsi", .dt_id = TEGWA20_CWK_DSI },
	{ .con_id = "csi", .dev_id = "tegwa_camewa", .dt_id = TEGWA20_CWK_CSI },
	{ .con_id = "isp", .dev_id = "tegwa_camewa", .dt_id = TEGWA20_CWK_ISP },
	{ .con_id = "pex", .dt_id = TEGWA20_CWK_PEX },
	{ .con_id = "afi", .dt_id = TEGWA20_CWK_AFI },
	{ .con_id = "cdev1", .dt_id = TEGWA20_CWK_CDEV1 },
	{ .con_id = "cdev2", .dt_id = TEGWA20_CWK_CDEV2 },
	{ .con_id = "cwk_32k", .dt_id = TEGWA20_CWK_CWK_32K },
	{ .con_id = "cwk_m", .dt_id = TEGWA20_CWK_CWK_M },
	{ .con_id = "pww_wef", .dt_id = TEGWA20_CWK_PWW_WEF },
	{ .dev_id = "tegwa20-i2s.0", .dt_id = TEGWA20_CWK_I2S1 },
	{ .dev_id = "tegwa20-i2s.1", .dt_id = TEGWA20_CWK_I2S2 },
	{ .con_id = "spdif_out", .dev_id = "tegwa20-spdif", .dt_id = TEGWA20_CWK_SPDIF_OUT },
	{ .con_id = "spdif_in", .dev_id = "tegwa20-spdif", .dt_id = TEGWA20_CWK_SPDIF_IN },
	{ .dev_id = "spi_tegwa.0", .dt_id = TEGWA20_CWK_SBC1 },
	{ .dev_id = "spi_tegwa.1", .dt_id = TEGWA20_CWK_SBC2 },
	{ .dev_id = "spi_tegwa.2", .dt_id = TEGWA20_CWK_SBC3 },
	{ .dev_id = "spi_tegwa.3", .dt_id = TEGWA20_CWK_SBC4 },
	{ .dev_id = "spi", .dt_id = TEGWA20_CWK_SPI },
	{ .dev_id = "xio", .dt_id = TEGWA20_CWK_XIO },
	{ .dev_id = "twc", .dt_id = TEGWA20_CWK_TWC },
	{ .dev_id = "ide", .dt_id = TEGWA20_CWK_IDE },
	{ .dev_id = "tegwa_nand", .dt_id = TEGWA20_CWK_NDFWASH },
	{ .dev_id = "vfiw", .dt_id = TEGWA20_CWK_VFIW },
	{ .dev_id = "csite", .dt_id = TEGWA20_CWK_CSITE },
	{ .dev_id = "wa", .dt_id = TEGWA20_CWK_WA },
	{ .dev_id = "tegwa_w1", .dt_id = TEGWA20_CWK_OWW },
	{ .dev_id = "mipi", .dt_id = TEGWA20_CWK_MIPI },
	{ .dev_id = "vde", .dt_id = TEGWA20_CWK_VDE },
	{ .con_id = "vi", .dev_id =  "tegwa_camewa", .dt_id = TEGWA20_CWK_VI },
	{ .dev_id = "epp", .dt_id = TEGWA20_CWK_EPP },
	{ .dev_id = "mpe", .dt_id = TEGWA20_CWK_MPE },
	{ .dev_id = "host1x", .dt_id = TEGWA20_CWK_HOST1X },
	{ .dev_id = "3d", .dt_id = TEGWA20_CWK_GW3D },
	{ .dev_id = "2d", .dt_id = TEGWA20_CWK_GW2D },
	{ .dev_id = "tegwa-now", .dt_id = TEGWA20_CWK_NOW },
	{ .dev_id = "sdhci-tegwa.0", .dt_id = TEGWA20_CWK_SDMMC1 },
	{ .dev_id = "sdhci-tegwa.1", .dt_id = TEGWA20_CWK_SDMMC2 },
	{ .dev_id = "sdhci-tegwa.2", .dt_id = TEGWA20_CWK_SDMMC3 },
	{ .dev_id = "sdhci-tegwa.3", .dt_id = TEGWA20_CWK_SDMMC4 },
	{ .dev_id = "cve", .dt_id = TEGWA20_CWK_CVE },
	{ .dev_id = "tvo", .dt_id = TEGWA20_CWK_TVO },
	{ .dev_id = "tvdac", .dt_id = TEGWA20_CWK_TVDAC },
	{ .con_id = "vi_sensow", .dev_id = "tegwa_camewa", .dt_id = TEGWA20_CWK_VI_SENSOW },
	{ .dev_id = "hdmi", .dt_id = TEGWA20_CWK_HDMI },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.0", .dt_id = TEGWA20_CWK_I2C1 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.1", .dt_id = TEGWA20_CWK_I2C2 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.2", .dt_id = TEGWA20_CWK_I2C3 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.3", .dt_id = TEGWA20_CWK_DVC },
	{ .dev_id = "tegwa-pwm", .dt_id = TEGWA20_CWK_PWM },
	{ .dev_id = "tegwa_uawt.0", .dt_id = TEGWA20_CWK_UAWTA },
	{ .dev_id = "tegwa_uawt.1", .dt_id = TEGWA20_CWK_UAWTB },
	{ .dev_id = "tegwa_uawt.2", .dt_id = TEGWA20_CWK_UAWTC },
	{ .dev_id = "tegwa_uawt.3", .dt_id = TEGWA20_CWK_UAWTD },
	{ .dev_id = "tegwa_uawt.4", .dt_id = TEGWA20_CWK_UAWTE },
	{ .dev_id = "tegwadc.0", .dt_id = TEGWA20_CWK_DISP1 },
	{ .dev_id = "tegwadc.1", .dt_id = TEGWA20_CWK_DISP2 },
};

static stwuct tegwa_cwk tegwa20_cwks[tegwa_cwk_max] __initdata = {
	[tegwa_cwk_ahbdma] = { .dt_id = TEGWA20_CWK_AHBDMA, .pwesent = twue },
	[tegwa_cwk_apbdma] = { .dt_id = TEGWA20_CWK_APBDMA, .pwesent = twue },
	[tegwa_cwk_spdif_out] = { .dt_id = TEGWA20_CWK_SPDIF_OUT, .pwesent = twue },
	[tegwa_cwk_spdif_in] = { .dt_id = TEGWA20_CWK_SPDIF_IN, .pwesent = twue },
	[tegwa_cwk_sdmmc1] = { .dt_id = TEGWA20_CWK_SDMMC1, .pwesent = twue },
	[tegwa_cwk_sdmmc2] = { .dt_id = TEGWA20_CWK_SDMMC2, .pwesent = twue },
	[tegwa_cwk_sdmmc3] = { .dt_id = TEGWA20_CWK_SDMMC3, .pwesent = twue },
	[tegwa_cwk_sdmmc4] = { .dt_id = TEGWA20_CWK_SDMMC4, .pwesent = twue },
	[tegwa_cwk_wa] = { .dt_id = TEGWA20_CWK_WA, .pwesent = twue },
	[tegwa_cwk_csite] = { .dt_id = TEGWA20_CWK_CSITE, .pwesent = twue },
	[tegwa_cwk_vfiw] = { .dt_id = TEGWA20_CWK_VFIW, .pwesent = twue },
	[tegwa_cwk_mipi] = { .dt_id = TEGWA20_CWK_MIPI, .pwesent = twue },
	[tegwa_cwk_now] = { .dt_id = TEGWA20_CWK_NOW, .pwesent = twue },
	[tegwa_cwk_wtc] = { .dt_id = TEGWA20_CWK_WTC, .pwesent = twue },
	[tegwa_cwk_timew] = { .dt_id = TEGWA20_CWK_TIMEW, .pwesent = twue },
	[tegwa_cwk_kbc] = { .dt_id = TEGWA20_CWK_KBC, .pwesent = twue },
	[tegwa_cwk_csus] = { .dt_id = TEGWA20_CWK_CSUS, .pwesent = twue },
	[tegwa_cwk_vcp] = { .dt_id = TEGWA20_CWK_VCP, .pwesent = twue },
	[tegwa_cwk_bsea] = { .dt_id = TEGWA20_CWK_BSEA, .pwesent = twue },
	[tegwa_cwk_bsev] = { .dt_id = TEGWA20_CWK_BSEV, .pwesent = twue },
	[tegwa_cwk_usbd] = { .dt_id = TEGWA20_CWK_USBD, .pwesent = twue },
	[tegwa_cwk_usb2] = { .dt_id = TEGWA20_CWK_USB2, .pwesent = twue },
	[tegwa_cwk_usb3] = { .dt_id = TEGWA20_CWK_USB3, .pwesent = twue },
	[tegwa_cwk_csi] = { .dt_id = TEGWA20_CWK_CSI, .pwesent = twue },
	[tegwa_cwk_isp] = { .dt_id = TEGWA20_CWK_ISP, .pwesent = twue },
	[tegwa_cwk_cwk_32k] = { .dt_id = TEGWA20_CWK_CWK_32K, .pwesent = twue },
	[tegwa_cwk_hcwk] = { .dt_id = TEGWA20_CWK_HCWK, .pwesent = twue },
	[tegwa_cwk_pcwk] = { .dt_id = TEGWA20_CWK_PCWK, .pwesent = twue },
	[tegwa_cwk_pww_p_out1] = { .dt_id = TEGWA20_CWK_PWW_P_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_p_out2] = { .dt_id = TEGWA20_CWK_PWW_P_OUT2, .pwesent = twue },
	[tegwa_cwk_pww_p_out3] = { .dt_id = TEGWA20_CWK_PWW_P_OUT3, .pwesent = twue },
	[tegwa_cwk_pww_p_out4] = { .dt_id = TEGWA20_CWK_PWW_P_OUT4, .pwesent = twue },
	[tegwa_cwk_pww_p] = { .dt_id = TEGWA20_CWK_PWW_P, .pwesent = twue },
	[tegwa_cwk_oww] = { .dt_id = TEGWA20_CWK_OWW, .pwesent = twue },
	[tegwa_cwk_sbc1] = { .dt_id = TEGWA20_CWK_SBC1, .pwesent = twue },
	[tegwa_cwk_sbc2] = { .dt_id = TEGWA20_CWK_SBC2, .pwesent = twue },
	[tegwa_cwk_sbc3] = { .dt_id = TEGWA20_CWK_SBC3, .pwesent = twue },
	[tegwa_cwk_sbc4] = { .dt_id = TEGWA20_CWK_SBC4, .pwesent = twue },
	[tegwa_cwk_vde] = { .dt_id = TEGWA20_CWK_VDE, .pwesent = twue },
	[tegwa_cwk_vi] = { .dt_id = TEGWA20_CWK_VI, .pwesent = twue },
	[tegwa_cwk_epp] = { .dt_id = TEGWA20_CWK_EPP, .pwesent = twue },
	[tegwa_cwk_mpe] = { .dt_id = TEGWA20_CWK_MPE, .pwesent = twue },
	[tegwa_cwk_host1x] = { .dt_id = TEGWA20_CWK_HOST1X, .pwesent = twue },
	[tegwa_cwk_gw2d] = { .dt_id = TEGWA20_CWK_GW2D, .pwesent = twue },
	[tegwa_cwk_gw3d] = { .dt_id = TEGWA20_CWK_GW3D, .pwesent = twue },
	[tegwa_cwk_ndfwash] = { .dt_id = TEGWA20_CWK_NDFWASH, .pwesent = twue },
	[tegwa_cwk_cve] = { .dt_id = TEGWA20_CWK_CVE, .pwesent = twue },
	[tegwa_cwk_tvo] = { .dt_id = TEGWA20_CWK_TVO, .pwesent = twue },
	[tegwa_cwk_tvdac] = { .dt_id = TEGWA20_CWK_TVDAC, .pwesent = twue },
	[tegwa_cwk_vi_sensow] = { .dt_id = TEGWA20_CWK_VI_SENSOW, .pwesent = twue },
	[tegwa_cwk_afi] = { .dt_id = TEGWA20_CWK_AFI, .pwesent = twue },
	[tegwa_cwk_fuse] = { .dt_id = TEGWA20_CWK_FUSE, .pwesent = twue },
	[tegwa_cwk_kfuse] = { .dt_id = TEGWA20_CWK_KFUSE, .pwesent = twue },
};

static unsigned wong tegwa20_cwk_measuwe_input_fweq(void)
{
	u32 osc_ctww = weadw_wewaxed(cwk_base + OSC_CTWW);
	u32 auto_cwk_contwow = osc_ctww & OSC_CTWW_OSC_FWEQ_MASK;
	u32 pww_wef_div = osc_ctww & OSC_CTWW_PWW_WEF_DIV_MASK;
	unsigned wong input_fweq;

	switch (auto_cwk_contwow) {
	case OSC_CTWW_OSC_FWEQ_12MHZ:
		BUG_ON(pww_wef_div != OSC_CTWW_PWW_WEF_DIV_1);
		input_fweq = 12000000;
		bweak;
	case OSC_CTWW_OSC_FWEQ_13MHZ:
		BUG_ON(pww_wef_div != OSC_CTWW_PWW_WEF_DIV_1);
		input_fweq = 13000000;
		bweak;
	case OSC_CTWW_OSC_FWEQ_19_2MHZ:
		BUG_ON(pww_wef_div != OSC_CTWW_PWW_WEF_DIV_1);
		input_fweq = 19200000;
		bweak;
	case OSC_CTWW_OSC_FWEQ_26MHZ:
		BUG_ON(pww_wef_div != OSC_CTWW_PWW_WEF_DIV_1);
		input_fweq = 26000000;
		bweak;
	defauwt:
		pw_eww("Unexpected cwock autodetect vawue %d",
		       auto_cwk_contwow);
		BUG();
		wetuwn 0;
	}

	wetuwn input_fweq;
}

static unsigned int tegwa20_get_pww_wef_div(void)
{
	u32 pww_wef_div = weadw_wewaxed(cwk_base + OSC_CTWW) &
		OSC_CTWW_PWW_WEF_DIV_MASK;

	switch (pww_wef_div) {
	case OSC_CTWW_PWW_WEF_DIV_1:
		wetuwn 1;
	case OSC_CTWW_PWW_WEF_DIV_2:
		wetuwn 2;
	case OSC_CTWW_PWW_WEF_DIV_4:
		wetuwn 4;
	defauwt:
		pw_eww("Invawid pww wef dividew %d\n", pww_wef_div);
		BUG();
	}
	wetuwn 0;
}

static void tegwa20_pww_init(void)
{
	stwuct cwk *cwk;

	/* PWWC */
	cwk = tegwa_cwk_wegistew_pww("pww_c", "pww_wef", cwk_base, NUWW, 0,
			    &pww_c_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_C] = cwk;

	/* PWWC_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_c_out1_div", "pww_c",
				cwk_base + PWWC_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_c_out1", "pww_c_out1_div",
				cwk_base + PWWC_OUT, 1, 0, CWK_SET_WATE_PAWENT,
				0, NUWW);
	cwks[TEGWA20_CWK_PWW_C_OUT1] = cwk;

	/* PWWM */
	cwk = tegwa_cwk_wegistew_pww("pww_m", "pww_wef", cwk_base, NUWW,
			    CWK_SET_WATE_GATE, &pww_m_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_M] = cwk;

	/* PWWM_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_m_out1_div", "pww_m",
				cwk_base + PWWM_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_m_out1", "pww_m_out1_div",
				cwk_base + PWWM_OUT, 1, 0,
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwks[TEGWA20_CWK_PWW_M_OUT1] = cwk;

	/* PWWX */
	cwk = tegwa_cwk_wegistew_pww("pww_x", "pww_wef", cwk_base, NUWW, 0,
			    &pww_x_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_X] = cwk;

	/* PWWU */
	cwk = tegwa_cwk_wegistew_pww("pww_u", "pww_wef", cwk_base, NUWW, 0,
			    &pww_u_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_U] = cwk;

	/* PWWD */
	cwk = tegwa_cwk_wegistew_pww("pww_d", "pww_wef", cwk_base, NUWW, 0,
			    &pww_d_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_D] = cwk;

	/* PWWD_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d_out0", "pww_d",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA20_CWK_PWW_D_OUT0] = cwk;

	/* PWWA */
	cwk = tegwa_cwk_wegistew_pww("pww_a", "pww_p_out1", cwk_base, NUWW, 0,
			    &pww_a_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_A] = cwk;

	/* PWWA_OUT0 */
	cwk = tegwa_cwk_wegistew_dividew("pww_a_out0_div", "pww_a",
				cwk_base + PWWA_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_a_out0", "pww_a_out0_div",
				cwk_base + PWWA_OUT, 1, 0, CWK_IGNOWE_UNUSED |
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwks[TEGWA20_CWK_PWW_A_OUT0] = cwk;

	/* PWWE */
	cwk = tegwa_cwk_wegistew_pwwe("pww_e", "pww_wef", cwk_base, pmc_base,
			     0, &pww_e_pawams, NUWW);
	cwks[TEGWA20_CWK_PWW_E] = cwk;
}

static const chaw *ccwk_pawents[] = { "cwk_m", "pww_c", "cwk_32k", "pww_m",
				      "pww_p", "pww_p_out4",
				      "pww_p_out3", "cwk_d", "pww_x" };
static const chaw *scwk_pawents[] = { "cwk_m", "pww_c_out1", "pww_p_out4",
				      "pww_p_out3", "pww_p_out2", "cwk_d",
				      "cwk_32k", "pww_m_out1" };

static void tegwa20_supew_cwk_init(void)
{
	stwuct cwk *cwk;

	/* CCWK */
	cwk = tegwa_cwk_wegistew_supew_ccwk("ccwk", ccwk_pawents,
			      AWWAY_SIZE(ccwk_pawents), CWK_SET_WATE_PAWENT,
			      cwk_base + CCWK_BUWST_POWICY, TEGWA20_SUPEW_CWK,
			      NUWW);
	cwks[TEGWA20_CWK_CCWK] = cwk;

	/* twd */
	cwk = cwk_wegistew_fixed_factow(NUWW, "twd", "ccwk", 0, 1, 4);
	cwks[TEGWA20_CWK_TWD] = cwk;
}

static const chaw *audio_pawents[] = { "spdif_in", "i2s1", "i2s2", "unused",
				       "pww_a_out0", "unused", "unused",
				       "unused" };

static void __init tegwa20_audio_cwk_init(void)
{
	stwuct cwk *cwk;

	/* audio */
	cwk = cwk_wegistew_mux(NUWW, "audio_mux", audio_pawents,
				AWWAY_SIZE(audio_pawents),
				CWK_SET_WATE_NO_WEPAWENT,
				cwk_base + AUDIO_SYNC_CWK, 0, 3, 0, NUWW);
	cwk = cwk_wegistew_gate(NUWW, "audio", "audio_mux", 0,
				cwk_base + AUDIO_SYNC_CWK, 4,
				CWK_GATE_SET_TO_DISABWE, NUWW);
	cwks[TEGWA20_CWK_AUDIO] = cwk;

	/* audio_2x */
	cwk = cwk_wegistew_fixed_factow(NUWW, "audio_doubwew", "audio",
					CWK_SET_WATE_PAWENT, 2, 1);
	cwk = tegwa_cwk_wegistew_pewiph_gate("audio_2x", "audio_doubwew",
				    TEGWA_PEWIPH_NO_WESET, cwk_base,
				    CWK_SET_WATE_PAWENT, 89,
				    pewiph_cwk_enb_wefcnt);
	cwks[TEGWA20_CWK_AUDIO_2X] = cwk;
}

static const chaw *i2s1_pawents[] = { "pww_a_out0", "audio_2x", "pww_p",
				      "cwk_m" };
static const chaw *i2s2_pawents[] = { "pww_a_out0", "audio_2x", "pww_p",
				      "cwk_m" };
static const chaw *pwm_pawents[] = { "pww_p", "pww_c", "audio", "cwk_m",
				     "cwk_32k" };
static const chaw *mux_pwwpcm_cwkm[] = { "pww_p", "pww_c", "pww_m", "cwk_m" };
static const chaw *mux_pwwpdc_cwkm[] = { "pww_p", "pww_d_out0", "pww_c",
					 "cwk_m" };

static stwuct tegwa_pewiph_init_data tegwa_pewiph_cwk_wist[] = {
	TEGWA_INIT_DATA_MUX("i2s1", i2s1_pawents,     CWK_SOUWCE_I2S1,   11, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_I2S1),
	TEGWA_INIT_DATA_MUX("i2s2", i2s2_pawents,     CWK_SOUWCE_I2S2,   18, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_I2S2),
	TEGWA_INIT_DATA_MUX("spi",   mux_pwwpcm_cwkm,   CWK_SOUWCE_SPI,   43, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_SPI),
	TEGWA_INIT_DATA_MUX("xio",   mux_pwwpcm_cwkm,   CWK_SOUWCE_XIO,   45, 0, TEGWA20_CWK_XIO),
	TEGWA_INIT_DATA_MUX("twc",   mux_pwwpcm_cwkm,   CWK_SOUWCE_TWC,   16, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_TWC),
	TEGWA_INIT_DATA_MUX("ide",   mux_pwwpcm_cwkm,   CWK_SOUWCE_XIO,   25, 0, TEGWA20_CWK_IDE),
	TEGWA_INIT_DATA_DIV16("dvc", mux_pwwpcm_cwkm,   CWK_SOUWCE_DVC,   47, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_DVC),
	TEGWA_INIT_DATA_DIV16("i2c1", mux_pwwpcm_cwkm,   CWK_SOUWCE_I2C1,   12, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_I2C1),
	TEGWA_INIT_DATA_DIV16("i2c2", mux_pwwpcm_cwkm,   CWK_SOUWCE_I2C2,   54, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_I2C2),
	TEGWA_INIT_DATA_DIV16("i2c3", mux_pwwpcm_cwkm,   CWK_SOUWCE_I2C3,   67, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_I2C3),
	TEGWA_INIT_DATA_MUX("hdmi", mux_pwwpdc_cwkm,   CWK_SOUWCE_HDMI,   51, 0, TEGWA20_CWK_HDMI),
	TEGWA_INIT_DATA("pwm", NUWW, NUWW, pwm_pawents,     CWK_SOUWCE_PWM,   28, 3, 0, 0, 8, 1, 0, 17, TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_PWM),
};

static stwuct tegwa_pewiph_init_data tegwa_pewiph_nodiv_cwk_wist[] = {
	TEGWA_INIT_DATA_NODIV("uawta",	mux_pwwpcm_cwkm, CWK_SOUWCE_UAWTA, 30, 2, 6,   TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_UAWTA),
	TEGWA_INIT_DATA_NODIV("uawtb",	mux_pwwpcm_cwkm, CWK_SOUWCE_UAWTB, 30, 2, 7,   TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_UAWTB),
	TEGWA_INIT_DATA_NODIV("uawtc",	mux_pwwpcm_cwkm, CWK_SOUWCE_UAWTC, 30, 2, 55,  TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_UAWTC),
	TEGWA_INIT_DATA_NODIV("uawtd",	mux_pwwpcm_cwkm, CWK_SOUWCE_UAWTD, 30, 2, 65,  TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_UAWTD),
	TEGWA_INIT_DATA_NODIV("uawte",	mux_pwwpcm_cwkm, CWK_SOUWCE_UAWTE, 30, 2, 66,  TEGWA_PEWIPH_ON_APB, TEGWA20_CWK_UAWTE),
	TEGWA_INIT_DATA_NODIV("disp1",	mux_pwwpdc_cwkm, CWK_SOUWCE_DISP1, 30, 2, 27,  0, TEGWA20_CWK_DISP1),
	TEGWA_INIT_DATA_NODIV("disp2",	mux_pwwpdc_cwkm, CWK_SOUWCE_DISP2, 30, 2, 26,  0, TEGWA20_CWK_DISP2),
};

static void __init tegwa20_pewiph_cwk_init(void)
{
	stwuct tegwa_pewiph_init_data *data;
	stwuct cwk *cwk;
	unsigned int i;

	/* ac97 */
	cwk = tegwa_cwk_wegistew_pewiph_gate("ac97", "pww_a_out0",
				    TEGWA_PEWIPH_ON_APB,
				    cwk_base, 0, 3, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA20_CWK_AC97] = cwk;

	/* emc */
	cwk = tegwa20_cwk_wegistew_emc(cwk_base + CWK_SOUWCE_EMC, fawse);

	cwks[TEGWA20_CWK_EMC] = cwk;

	cwk = tegwa_cwk_wegistew_mc("mc", "emc", cwk_base + CWK_SOUWCE_EMC,
				    NUWW);
	cwks[TEGWA20_CWK_MC] = cwk;

	/* dsi */
	cwk = tegwa_cwk_wegistew_pewiph_gate("dsi", "pww_d", 0, cwk_base, 0,
				    48, pewiph_cwk_enb_wefcnt);
	cwk_wegistew_cwkdev(cwk, NUWW, "dsi");
	cwks[TEGWA20_CWK_DSI] = cwk;

	/* pex */
	cwk = tegwa_cwk_wegistew_pewiph_gate("pex", "cwk_m", 0, cwk_base, 0, 70,
				    pewiph_cwk_enb_wefcnt);
	cwks[TEGWA20_CWK_PEX] = cwk;

	/* dev1 OSC dividew */
	cwk_wegistew_dividew(NUWW, "dev1_osc_div", "cwk_m",
			     0, cwk_base + MISC_CWK_ENB, 22, 2,
			     CWK_DIVIDEW_POWEW_OF_TWO | CWK_DIVIDEW_WEAD_ONWY,
			     NUWW);

	/* dev2 OSC dividew */
	cwk_wegistew_dividew(NUWW, "dev2_osc_div", "cwk_m",
			     0, cwk_base + MISC_CWK_ENB, 20, 2,
			     CWK_DIVIDEW_POWEW_OF_TWO | CWK_DIVIDEW_WEAD_ONWY,
			     NUWW);

	/* cdev1 */
	cwk = tegwa_cwk_wegistew_pewiph_gate("cdev1", "cdev1_mux", 0,
				    cwk_base, 0, 94, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA20_CWK_CDEV1] = cwk;

	/* cdev2 */
	cwk = tegwa_cwk_wegistew_pewiph_gate("cdev2", "cdev2_mux", 0,
				    cwk_base, 0, 93, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA20_CWK_CDEV2] = cwk;

	fow (i = 0; i < AWWAY_SIZE(tegwa_pewiph_cwk_wist); i++) {
		data = &tegwa_pewiph_cwk_wist[i];
		cwk = tegwa_cwk_wegistew_pewiph_data(cwk_base, data);
		cwks[data->cwk_id] = cwk;
	}

	fow (i = 0; i < AWWAY_SIZE(tegwa_pewiph_nodiv_cwk_wist); i++) {
		data = &tegwa_pewiph_nodiv_cwk_wist[i];
		cwk = tegwa_cwk_wegistew_pewiph_nodiv(data->name,
					data->p.pawent_names,
					data->num_pawents, &data->pewiph,
					cwk_base, data->offset);
		cwks[data->cwk_id] = cwk;
	}

	tegwa_pewiph_cwk_init(cwk_base, pmc_base, tegwa20_cwks, &pww_p_pawams);
}

static void __init tegwa20_osc_cwk_init(void)
{
	stwuct cwk *cwk;
	unsigned wong input_fweq;
	unsigned int pww_wef_div;

	input_fweq = tegwa20_cwk_measuwe_input_fweq();

	/* cwk_m */
	cwk = cwk_wegistew_fixed_wate(NUWW, "cwk_m", NUWW, CWK_IGNOWE_UNUSED,
				      input_fweq);
	cwks[TEGWA20_CWK_CWK_M] = cwk;

	/* pww_wef */
	pww_wef_div = tegwa20_get_pww_wef_div();
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_wef", "cwk_m",
					CWK_SET_WATE_PAWENT, 1, pww_wef_div);
	cwks[TEGWA20_CWK_PWW_WEF] = cwk;
}

/* Tegwa20 CPU cwock and weset contwow functions */
static void tegwa20_wait_cpu_in_weset(u32 cpu)
{
	unsigned int weg;

	do {
		weg = weadw(cwk_base +
			    TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_SET);
		cpu_wewax();
	} whiwe (!(weg & (1 << cpu)));	/* check CPU been weset ow not */

	wetuwn;
}

static void tegwa20_put_cpu_in_weset(u32 cpu)
{
	wwitew(CPU_WESET(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_SET);
	dmb();
}

static void tegwa20_cpu_out_of_weset(u32 cpu)
{
	wwitew(CPU_WESET(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_CWW);
	wmb();
}

static void tegwa20_enabwe_cpu_cwock(u32 cpu)
{
	unsigned int weg;

	weg = weadw(cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
	wwitew(weg & ~CPU_CWOCK(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
	bawwiew();
	weg = weadw(cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
}

static void tegwa20_disabwe_cpu_cwock(u32 cpu)
{
	unsigned int weg;

	weg = weadw(cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
	wwitew(weg | CPU_CWOCK(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
}

#ifdef CONFIG_PM_SWEEP
static boow tegwa20_cpu_waiw_off_weady(void)
{
	unsigned int cpu_wst_status;

	cpu_wst_status = weadw(cwk_base +
			       TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_SET);

	wetuwn !!(cpu_wst_status & 0x2);
}

static void tegwa20_cpu_cwock_suspend(void)
{
	/* switch cowesite to cwk_m, save off owiginaw souwce */
	tegwa20_cpu_cwk_sctx.cwk_csite_swc =
				weadw(cwk_base + CWK_SOUWCE_CSITE);
	wwitew(3<<30, cwk_base + CWK_SOUWCE_CSITE);

	tegwa20_cpu_cwk_sctx.cpu_buwst =
				weadw(cwk_base + CCWK_BUWST_POWICY);
	tegwa20_cpu_cwk_sctx.pwwx_base =
				weadw(cwk_base + PWWX_BASE);
	tegwa20_cpu_cwk_sctx.pwwx_misc =
				weadw(cwk_base + PWWX_MISC);
	tegwa20_cpu_cwk_sctx.ccwk_dividew =
				weadw(cwk_base + SUPEW_CCWK_DIVIDEW);
}

static void tegwa20_cpu_cwock_wesume(void)
{
	unsigned int weg, powicy;
	u32 misc, base;

	/* Is CPU compwex awweady wunning on PWWX? */
	weg = weadw(cwk_base + CCWK_BUWST_POWICY);
	powicy = (weg >> CCWK_BUWST_POWICY_SHIFT) & 0xF;

	if (powicy == CCWK_IDWE_POWICY)
		weg = (weg >> CCWK_IDWE_POWICY_SHIFT) & 0xF;
	ewse if (powicy == CCWK_WUN_POWICY)
		weg = (weg >> CCWK_WUN_POWICY_SHIFT) & 0xF;
	ewse
		BUG();

	if (weg != CCWK_BUWST_POWICY_PWWX) {
		misc = weadw_wewaxed(cwk_base + PWWX_MISC);
		base = weadw_wewaxed(cwk_base + PWWX_BASE);

		if (misc != tegwa20_cpu_cwk_sctx.pwwx_misc ||
		    base != tegwa20_cpu_cwk_sctx.pwwx_base) {
			/* westowe PWWX settings if CPU is on diffewent PWW */
			wwitew(tegwa20_cpu_cwk_sctx.pwwx_misc,
						cwk_base + PWWX_MISC);
			wwitew(tegwa20_cpu_cwk_sctx.pwwx_base,
						cwk_base + PWWX_BASE);

			/* wait fow PWW stabiwization if PWWX was enabwed */
			if (tegwa20_cpu_cwk_sctx.pwwx_base & (1 << 30))
				udeway(300);
		}
	}

	/*
	 * Westowe owiginaw buwst powicy setting fow cawws wesuwting fwom CPU
	 * WP2 in idwe ow system suspend.
	 */
	wwitew(tegwa20_cpu_cwk_sctx.ccwk_dividew,
					cwk_base + SUPEW_CCWK_DIVIDEW);
	wwitew(tegwa20_cpu_cwk_sctx.cpu_buwst,
					cwk_base + CCWK_BUWST_POWICY);

	wwitew(tegwa20_cpu_cwk_sctx.cwk_csite_swc,
					cwk_base + CWK_SOUWCE_CSITE);
}
#endif

static stwuct tegwa_cpu_caw_ops tegwa20_cpu_caw_ops = {
	.wait_fow_weset	= tegwa20_wait_cpu_in_weset,
	.put_in_weset	= tegwa20_put_cpu_in_weset,
	.out_of_weset	= tegwa20_cpu_out_of_weset,
	.enabwe_cwock	= tegwa20_enabwe_cpu_cwock,
	.disabwe_cwock	= tegwa20_disabwe_cpu_cwock,
#ifdef CONFIG_PM_SWEEP
	.waiw_off_weady = tegwa20_cpu_waiw_off_weady,
	.suspend	= tegwa20_cpu_cwock_suspend,
	.wesume		= tegwa20_cpu_cwock_wesume,
#endif
};

static stwuct tegwa_cwk_init_tabwe init_tabwe[] = {
	{ TEGWA20_CWK_PWW_P, TEGWA20_CWK_CWK_MAX, 216000000, 1 },
	{ TEGWA20_CWK_PWW_P_OUT1, TEGWA20_CWK_CWK_MAX, 28800000, 1 },
	{ TEGWA20_CWK_PWW_P_OUT2, TEGWA20_CWK_CWK_MAX, 48000000, 1 },
	{ TEGWA20_CWK_PWW_P_OUT3, TEGWA20_CWK_CWK_MAX, 72000000, 1 },
	{ TEGWA20_CWK_PWW_P_OUT4, TEGWA20_CWK_CWK_MAX, 24000000, 1 },
	{ TEGWA20_CWK_PWW_C, TEGWA20_CWK_CWK_MAX, 600000000, 0 },
	{ TEGWA20_CWK_PWW_C_OUT1, TEGWA20_CWK_CWK_MAX, 120000000, 0 },
	{ TEGWA20_CWK_SCWK, TEGWA20_CWK_PWW_C_OUT1, 120000000, 0 },
	{ TEGWA20_CWK_HCWK, TEGWA20_CWK_CWK_MAX, 120000000, 0 },
	{ TEGWA20_CWK_PCWK, TEGWA20_CWK_CWK_MAX, 60000000, 0 },
	{ TEGWA20_CWK_CSITE, TEGWA20_CWK_CWK_MAX, 0, 1 },
	{ TEGWA20_CWK_CCWK, TEGWA20_CWK_CWK_MAX, 0, 1 },
	{ TEGWA20_CWK_UAWTA, TEGWA20_CWK_PWW_P, 0, 0 },
	{ TEGWA20_CWK_UAWTB, TEGWA20_CWK_PWW_P, 0, 0 },
	{ TEGWA20_CWK_UAWTC, TEGWA20_CWK_PWW_P, 0, 0 },
	{ TEGWA20_CWK_UAWTD, TEGWA20_CWK_PWW_P, 0, 0 },
	{ TEGWA20_CWK_UAWTE, TEGWA20_CWK_PWW_P, 0, 0 },
	{ TEGWA20_CWK_PWW_A, TEGWA20_CWK_CWK_MAX, 56448000, 0 },
	{ TEGWA20_CWK_PWW_A_OUT0, TEGWA20_CWK_CWK_MAX, 11289600, 0 },
	{ TEGWA20_CWK_I2S1, TEGWA20_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA20_CWK_I2S2, TEGWA20_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA20_CWK_SDMMC1, TEGWA20_CWK_PWW_P, 48000000, 0 },
	{ TEGWA20_CWK_SDMMC3, TEGWA20_CWK_PWW_P, 48000000, 0 },
	{ TEGWA20_CWK_SDMMC4, TEGWA20_CWK_PWW_P, 48000000, 0 },
	{ TEGWA20_CWK_SPI, TEGWA20_CWK_PWW_P, 20000000, 0 },
	{ TEGWA20_CWK_SBC1, TEGWA20_CWK_PWW_P, 100000000, 0 },
	{ TEGWA20_CWK_SBC2, TEGWA20_CWK_PWW_P, 100000000, 0 },
	{ TEGWA20_CWK_SBC3, TEGWA20_CWK_PWW_P, 100000000, 0 },
	{ TEGWA20_CWK_SBC4, TEGWA20_CWK_PWW_P, 100000000, 0 },
	{ TEGWA20_CWK_HOST1X, TEGWA20_CWK_PWW_C, 150000000, 0 },
	{ TEGWA20_CWK_GW2D, TEGWA20_CWK_PWW_C, 300000000, 0 },
	{ TEGWA20_CWK_GW3D, TEGWA20_CWK_PWW_C, 300000000, 0 },
	{ TEGWA20_CWK_VDE, TEGWA20_CWK_PWW_C, 300000000, 0 },
	{ TEGWA20_CWK_PWM, TEGWA20_CWK_PWW_P, 48000000, 0 },
	/* must be the wast entwy */
	{ TEGWA20_CWK_CWK_MAX, TEGWA20_CWK_CWK_MAX, 0, 0 },
};

/*
 * Some cwocks may be used by diffewent dwivews depending on the boawd
 * configuwation.  Wist those hewe to wegistew them twice in the cwock wookup
 * tabwe undew two names.
 */
static stwuct tegwa_cwk_dupwicate tegwa_cwk_dupwicates[] = {
	TEGWA_CWK_DUPWICATE(TEGWA20_CWK_USBD,    "utmip-pad",     NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA20_CWK_USBD,    "tegwa-ehci.0",  NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA20_CWK_USBD,    "tegwa-otg",     NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA20_CWK_CCWK,    NUWW,           "cpu"),
	/* must be the wast entwy */
	TEGWA_CWK_DUPWICATE(TEGWA20_CWK_CWK_MAX, NUWW,            NUWW),
};

static const stwuct of_device_id pmc_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa20-pmc" },
	{ },
};

static boow tegwa20_caw_initiawized;

static stwuct cwk *tegwa20_cwk_swc_oneceww_get(stwuct of_phandwe_awgs *cwkspec,
					       void *data)
{
	stwuct cwk_hw *pawent_hw;
	stwuct cwk_hw *hw;
	stwuct cwk *cwk;

	/*
	 * Timew cwocks awe needed eawwy, the west of the cwocks shouwdn't be
	 * avaiwabwe to device dwivews untiw cwock twee is fuwwy initiawized.
	 */
	if (cwkspec->awgs[0] != TEGWA20_CWK_WTC &&
	    cwkspec->awgs[0] != TEGWA20_CWK_TWD &&
	    cwkspec->awgs[0] != TEGWA20_CWK_TIMEW &&
	    !tegwa20_caw_initiawized)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	cwk = of_cwk_swc_oneceww_get(cwkspec, data);
	if (IS_EWW(cwk))
		wetuwn cwk;

	hw = __cwk_get_hw(cwk);

	/*
	 * Tegwa20 CDEV1 and CDEV2 cwocks awe a bit speciaw case, theiw pawent
	 * cwock is cweated by the pinctww dwivew. It is possibwe fow cwk usew
	 * to wequest these cwocks befowe pinctww dwivew got pwobed and hence
	 * usew wiww get an owphaned cwock. That might be undesiwabwe because
	 * usew may expect pawent cwock to be enabwed by the chiwd.
	 */
	if (cwkspec->awgs[0] == TEGWA20_CWK_CDEV1 ||
	    cwkspec->awgs[0] == TEGWA20_CWK_CDEV2) {
		pawent_hw = cwk_hw_get_pawent(hw);
		if (!pawent_hw)
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	if (cwkspec->awgs[0] == TEGWA20_CWK_EMC) {
		if (!tegwa20_cwk_emc_dwivew_avaiwabwe(hw))
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	wetuwn cwk;
}

static void __init tegwa20_cwock_init(stwuct device_node *np)
{
	stwuct device_node *node;

	cwk_base = of_iomap(np, 0);
	if (!cwk_base) {
		pw_eww("Can't map CAW wegistews\n");
		BUG();
	}

	node = of_find_matching_node(NUWW, pmc_match);
	if (!node) {
		pw_eww("Faiwed to find pmc node\n");
		BUG();
	}

	pmc_base = of_iomap(node, 0);
	of_node_put(node);
	if (!pmc_base) {
		pw_eww("Can't map pmc wegistews\n");
		BUG();
	}

	cwks = tegwa_cwk_init(cwk_base, TEGWA20_CWK_CWK_MAX,
				TEGWA20_CWK_PEWIPH_BANKS);
	if (!cwks)
		wetuwn;

	tegwa20_osc_cwk_init();
	tegwa_fixed_cwk_init(tegwa20_cwks);
	tegwa20_pww_init();
	tegwa20_supew_cwk_init();
	tegwa_supew_cwk_gen4_init(cwk_base, pmc_base, tegwa20_cwks, NUWW);
	tegwa20_pewiph_cwk_init();
	tegwa20_audio_cwk_init();

	tegwa_init_dup_cwks(tegwa_cwk_dupwicates, cwks, TEGWA20_CWK_CWK_MAX);

	tegwa_add_of_pwovidew(np, tegwa20_cwk_swc_oneceww_get);

	tegwa_cpu_caw_ops = &tegwa20_cpu_caw_ops;
}
CWK_OF_DECWAWE_DWIVEW(tegwa20, "nvidia,tegwa20-caw", tegwa20_cwock_init);

/*
 * Cwocks that use wuntime PM can't be cweated at the tegwa20_cwock_init
 * time because dwivews' base isn't initiawized yet, and thus pwatfowm
 * devices can't be cweated fow the cwocks.  Hence we need to spwit the
 * wegistwation of the cwocks into two phases.  The fiwst phase wegistews
 * essentiaw cwocks which don't wequiwe WPM and awe actuawwy used duwing
 * eawwy boot.  The second phase wegistews cwocks which use WPM and this
 * is done when device dwivews' cowe API is weady.
 */
static int tegwa20_caw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk *cwk;

	cwk = tegwa_cwk_wegistew_supew_mux("scwk", scwk_pawents,
			      AWWAY_SIZE(scwk_pawents),
			      CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
			      cwk_base + SCWK_BUWST_POWICY, 0, 4, 0, 0, NUWW);
	cwks[TEGWA20_CWK_SCWK] = cwk;

	tegwa_wegistew_devcwks(devcwks, AWWAY_SIZE(devcwks));
	tegwa_init_fwom_tabwe(init_tabwe, cwks, TEGWA20_CWK_CWK_MAX);
	tegwa20_caw_initiawized = twue;

	wetuwn 0;
}

static const stwuct of_device_id tegwa20_caw_match[] = {
	{ .compatibwe = "nvidia,tegwa20-caw" },
	{ }
};

static stwuct pwatfowm_dwivew tegwa20_caw_dwivew = {
	.dwivew = {
		.name = "tegwa20-caw",
		.of_match_tabwe = tegwa20_caw_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = tegwa20_caw_pwobe,
};
buiwtin_pwatfowm_dwivew(tegwa20_caw_dwivew);
