// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk/tegwa.h>

#incwude <soc/tegwa/pmc.h>

#incwude <dt-bindings/cwock/tegwa30-caw.h>

#incwude "cwk.h"
#incwude "cwk-id.h"

#define OSC_CTWW			0x50
#define OSC_CTWW_OSC_FWEQ_MASK		(0xF<<28)
#define OSC_CTWW_OSC_FWEQ_13MHZ		(0X0<<28)
#define OSC_CTWW_OSC_FWEQ_19_2MHZ	(0X4<<28)
#define OSC_CTWW_OSC_FWEQ_12MHZ		(0X8<<28)
#define OSC_CTWW_OSC_FWEQ_26MHZ		(0XC<<28)
#define OSC_CTWW_OSC_FWEQ_16_8MHZ	(0X1<<28)
#define OSC_CTWW_OSC_FWEQ_38_4MHZ	(0X5<<28)
#define OSC_CTWW_OSC_FWEQ_48MHZ		(0X9<<28)
#define OSC_CTWW_MASK			(0x3f2 | OSC_CTWW_OSC_FWEQ_MASK)

#define OSC_CTWW_PWW_WEF_DIV_MASK	(3<<26)
#define OSC_CTWW_PWW_WEF_DIV_1		(0<<26)
#define OSC_CTWW_PWW_WEF_DIV_2		(1<<26)
#define OSC_CTWW_PWW_WEF_DIV_4		(2<<26)

#define OSC_FWEQ_DET			0x58
#define OSC_FWEQ_DET_TWIG		BIT(31)

#define OSC_FWEQ_DET_STATUS		0x5c
#define OSC_FWEQ_DET_BUSY		BIT(31)
#define OSC_FWEQ_DET_CNT_MASK		0xffff

#define CCWKG_BUWST_POWICY 0x368
#define SUPEW_CCWKG_DIVIDEW 0x36c
#define CCWKWP_BUWST_POWICY 0x370
#define SUPEW_CCWKWP_DIVIDEW 0x374
#define SCWK_BUWST_POWICY 0x028
#define SUPEW_SCWK_DIVIDEW 0x02c

#define SYSTEM_CWK_WATE 0x030

#define TEGWA30_CWK_PEWIPH_BANKS	5

#define PWWC_BASE 0x80
#define PWWC_MISC 0x8c
#define PWWM_BASE 0x90
#define PWWM_MISC 0x9c
#define PWWP_BASE 0xa0
#define PWWP_MISC 0xac
#define PWWX_BASE 0xe0
#define PWWX_MISC 0xe4
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

#define PWW_MISC_WOCK_ENABWE 18
#define PWWDU_MISC_WOCK_ENABWE 22
#define PWWE_MISC_WOCK_ENABWE 9

#define PWW_BASE_WOCK BIT(27)
#define PWWE_MISC_WOCK BIT(11)

#define PWWE_AUX 0x48c
#define PWWC_OUT 0x84
#define PWWM_OUT 0x94
#define PWWP_OUTA 0xa4
#define PWWP_OUTB 0xa8
#define PWWA_OUT 0xb4

#define AUDIO_SYNC_CWK_I2S0 0x4a0
#define AUDIO_SYNC_CWK_I2S1 0x4a4
#define AUDIO_SYNC_CWK_I2S2 0x4a8
#define AUDIO_SYNC_CWK_I2S3 0x4ac
#define AUDIO_SYNC_CWK_I2S4 0x4b0
#define AUDIO_SYNC_CWK_SPDIF 0x4b4

#define CWK_SOUWCE_SPDIF_OUT 0x108
#define CWK_SOUWCE_PWM 0x110
#define CWK_SOUWCE_D_AUDIO 0x3d0
#define CWK_SOUWCE_DAM0 0x3d8
#define CWK_SOUWCE_DAM1 0x3dc
#define CWK_SOUWCE_DAM2 0x3e0
#define CWK_SOUWCE_3D2 0x3b0
#define CWK_SOUWCE_2D 0x15c
#define CWK_SOUWCE_HDMI 0x18c
#define CWK_SOUWCE_DSIB 0xd0
#define CWK_SOUWCE_SE 0x42c
#define CWK_SOUWCE_EMC 0x19c

#define AUDIO_SYNC_DOUBWEW 0x49c

/* Tegwa CPU cwock and weset contwow wegs */
#define TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX		0x4c
#define TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_SET	0x340
#define TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_CWW	0x344
#define TEGWA30_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX_CWW	0x34c
#define TEGWA30_CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS	0x470

#define CPU_CWOCK(cpu)	(0x1 << (8 + cpu))
#define CPU_WESET(cpu)	(0x1111uw << (cpu))

#define CWK_WESET_CCWK_BUWST	0x20
#define CWK_WESET_CCWK_DIVIDEW	0x24
#define CWK_WESET_PWWX_BASE	0xe0
#define CWK_WESET_PWWX_MISC	0xe4

#define CWK_WESET_SOUWCE_CSITE	0x1d4

#define CWK_WESET_CCWK_BUWST_POWICY_SHIFT	28
#define CWK_WESET_CCWK_WUN_POWICY_SHIFT		4
#define CWK_WESET_CCWK_IDWE_POWICY_SHIFT	0
#define CWK_WESET_CCWK_IDWE_POWICY		1
#define CWK_WESET_CCWK_WUN_POWICY		2
#define CWK_WESET_CCWK_BUWST_POWICY_PWWX	8

/* PWWM ovewwide wegistews */
#define PMC_PWWM_WB0_OVEWWIDE 0x1dc

#ifdef CONFIG_PM_SWEEP
static stwuct cpu_cwk_suspend_context {
	u32 pwwx_misc;
	u32 pwwx_base;

	u32 cpu_buwst;
	u32 cwk_csite_swc;
	u32 ccwk_dividew;
} tegwa30_cpu_cwk_sctx;
#endif

static void __iomem *cwk_base;
static void __iomem *pmc_base;
static unsigned wong input_fweq;

static DEFINE_SPINWOCK(cmw_wock);
static DEFINE_SPINWOCK(pww_d_wock);

#define TEGWA_INIT_DATA_MUX(_name, _pawents, _offset,	\
			    _cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			30, 2, 0, 0, 8, 1, TEGWA_DIVIDEW_WOUND_UP, \
			_cwk_num, _gate_fwags, _cwk_id)

#define TEGWA_INIT_DATA_MUX8(_name, _pawents, _offset, \
			     _cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			29, 3, 0, 0, 8, 1, TEGWA_DIVIDEW_WOUND_UP, \
			_cwk_num, _gate_fwags, _cwk_id)

#define TEGWA_INIT_DATA_INT(_name, _pawents, _offset,	\
			    _cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			30, 2, 0, 0, 8, 1, TEGWA_DIVIDEW_INT |		\
			TEGWA_DIVIDEW_WOUND_UP, _cwk_num,	\
			_gate_fwags, _cwk_id)

#define TEGWA_INIT_DATA_NODIV(_name, _pawents, _offset, \
			      _mux_shift, _mux_width, _cwk_num, \
			      _gate_fwags, _cwk_id)			\
	TEGWA_INIT_DATA(_name, NUWW, NUWW, _pawents, _offset,	\
			_mux_shift, _mux_width, 0, 0, 0, 0, 0,\
			_cwk_num, _gate_fwags,	\
			_cwk_id)

static stwuct cwk **cwks;

static stwuct tegwa_cwk_pww_fweq_tabwe pww_c_fweq_tabwe[] = {
	{ 12000000, 1040000000, 520,  6, 1, 8 },
	{ 13000000, 1040000000, 480,  6, 1, 8 },
	{ 16800000, 1040000000, 495,  8, 1, 8 }, /* actuaw: 1039.5 MHz */
	{ 19200000, 1040000000, 325,  6, 1, 6 },
	{ 26000000, 1040000000, 520, 13, 1, 8 },
	{ 12000000,  832000000, 416,  6, 1, 8 },
	{ 13000000,  832000000, 832, 13, 1, 8 },
	{ 16800000,  832000000, 396,  8, 1, 8 }, /* actuaw: 831.6 MHz */
	{ 19200000,  832000000, 260,  6, 1, 8 },
	{ 26000000,  832000000, 416, 13, 1, 8 },
	{ 12000000,  624000000, 624, 12, 1, 8 },
	{ 13000000,  624000000, 624, 13, 1, 8 },
	{ 16800000,  600000000, 520, 14, 1, 8 },
	{ 19200000,  624000000, 520, 16, 1, 8 },
	{ 26000000,  624000000, 624, 26, 1, 8 },
	{ 12000000,  600000000, 600, 12, 1, 8 },
	{ 13000000,  600000000, 600, 13, 1, 8 },
	{ 16800000,  600000000, 500, 14, 1, 8 },
	{ 19200000,  600000000, 375, 12, 1, 6 },
	{ 26000000,  600000000, 600, 26, 1, 8 },
	{ 12000000,  520000000, 520, 12, 1, 8 },
	{ 13000000,  520000000, 520, 13, 1, 8 },
	{ 16800000,  520000000, 495, 16, 1, 8 }, /* actuaw: 519.75 MHz */
	{ 19200000,  520000000, 325, 12, 1, 6 },
	{ 26000000,  520000000, 520, 26, 1, 8 },
	{ 12000000,  416000000, 416, 12, 1, 8 },
	{ 13000000,  416000000, 416, 13, 1, 8 },
	{ 16800000,  416000000, 396, 16, 1, 8 }, /* actuaw: 415.8 MHz */
	{ 19200000,  416000000, 260, 12, 1, 6 },
	{ 26000000,  416000000, 416, 26, 1, 8 },
	{        0,          0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_m_fweq_tabwe[] = {
	{ 12000000, 666000000, 666, 12, 1, 8 },
	{ 13000000, 666000000, 666, 13, 1, 8 },
	{ 16800000, 666000000, 555, 14, 1, 8 },
	{ 19200000, 666000000, 555, 16, 1, 8 },
	{ 26000000, 666000000, 666, 26, 1, 8 },
	{ 12000000, 600000000, 600, 12, 1, 8 },
	{ 13000000, 600000000, 600, 13, 1, 8 },
	{ 16800000, 600000000, 500, 14, 1, 8 },
	{ 19200000, 600000000, 375, 12, 1, 6 },
	{ 26000000, 600000000, 600, 26, 1, 8 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_p_fweq_tabwe[] = {
	{ 12000000, 216000000, 432, 12, 2, 8 },
	{ 13000000, 216000000, 432, 13, 2, 8 },
	{ 16800000, 216000000, 360, 14, 2, 8 },
	{ 19200000, 216000000, 360, 16, 2, 8 },
	{ 26000000, 216000000, 432, 26, 2, 8 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_a_fweq_tabwe[] = {
	{  9600000, 564480000, 294,  5, 1, 4 },
	{  9600000, 552960000, 288,  5, 1, 4 },
	{  9600000,  24000000,   5,  2, 1, 1 },
	{ 28800000,  56448000,  49, 25, 1, 1 },
	{ 28800000,  73728000,  64, 25, 1, 1 },
	{ 28800000,  24000000,   5,  6, 1, 1 },
	{        0,         0,   0,  0, 0, 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_d_fweq_tabwe[] = {
	{ 12000000,  216000000,  216, 12, 1,  4 },
	{ 13000000,  216000000,  216, 13, 1,  4 },
	{ 16800000,  216000000,  180, 14, 1,  4 },
	{ 19200000,  216000000,  180, 16, 1,  4 },
	{ 26000000,  216000000,  216, 26, 1,  4 },
	{ 12000000,  594000000,  594, 12, 1,  8 },
	{ 13000000,  594000000,  594, 13, 1,  8 },
	{ 16800000,  594000000,  495, 14, 1,  8 },
	{ 19200000,  594000000,  495, 16, 1,  8 },
	{ 26000000,  594000000,  594, 26, 1,  8 },
	{ 12000000, 1000000000, 1000, 12, 1, 12 },
	{ 13000000, 1000000000, 1000, 13, 1, 12 },
	{ 19200000, 1000000000,  625, 12, 1,  8 },
	{ 26000000, 1000000000, 1000, 26, 1, 12 },
	{        0,          0,    0,  0, 0,  0 },
};

static const stwuct pdiv_map pwwu_p[] = {
	{ .pdiv = 1, .hw_vaw = 1 },
	{ .pdiv = 2, .hw_vaw = 0 },
	{ .pdiv = 0, .hw_vaw = 0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_u_fweq_tabwe[] = {
	{ 12000000, 480000000, 960, 12, 2, 12 },
	{ 13000000, 480000000, 960, 13, 2, 12 },
	{ 16800000, 480000000, 400,  7, 2,  5 },
	{ 19200000, 480000000, 200,  4, 2,  3 },
	{ 26000000, 480000000, 960, 26, 2, 12 },
	{        0,         0,   0,  0, 0,  0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_x_fweq_tabwe[] = {
	/* 1.7 GHz */
	{ 12000000, 1700000000, 850,   6, 1, 8 },
	{ 13000000, 1700000000, 915,   7, 1, 8 }, /* actuaw: 1699.2 MHz */
	{ 16800000, 1700000000, 708,   7, 1, 8 }, /* actuaw: 1699.2 MHz */
	{ 19200000, 1700000000, 885,  10, 1, 8 }, /* actuaw: 1699.2 MHz */
	{ 26000000, 1700000000, 850,  13, 1, 8 },
	/* 1.6 GHz */
	{ 12000000, 1600000000, 800,   6, 1, 8 },
	{ 13000000, 1600000000, 738,   6, 1, 8 }, /* actuaw: 1599.0 MHz */
	{ 16800000, 1600000000, 857,   9, 1, 8 }, /* actuaw: 1599.7 MHz */
	{ 19200000, 1600000000, 500,   6, 1, 8 },
	{ 26000000, 1600000000, 800,  13, 1, 8 },
	/* 1.5 GHz */
	{ 12000000, 1500000000, 750,   6, 1, 8 },
	{ 13000000, 1500000000, 923,   8, 1, 8 }, /* actuaw: 1499.8 MHz */
	{ 16800000, 1500000000, 625,   7, 1, 8 },
	{ 19200000, 1500000000, 625,   8, 1, 8 },
	{ 26000000, 1500000000, 750,  13, 1, 8 },
	/* 1.4 GHz */
	{ 12000000, 1400000000,  700,  6, 1, 8 },
	{ 13000000, 1400000000,  969,  9, 1, 8 }, /* actuaw: 1399.7 MHz */
	{ 16800000, 1400000000, 1000, 12, 1, 8 },
	{ 19200000, 1400000000,  875, 12, 1, 8 },
	{ 26000000, 1400000000,  700, 13, 1, 8 },
	/* 1.3 GHz */
	{ 12000000, 1300000000,  975,  9, 1, 8 },
	{ 13000000, 1300000000, 1000, 10, 1, 8 },
	{ 16800000, 1300000000,  928, 12, 1, 8 }, /* actuaw: 1299.2 MHz */
	{ 19200000, 1300000000,  812, 12, 1, 8 }, /* actuaw: 1299.2 MHz */
	{ 26000000, 1300000000,  650, 13, 1, 8 },
	/* 1.2 GHz */
	{ 12000000, 1200000000, 1000, 10, 1, 8 },
	{ 13000000, 1200000000,  923, 10, 1, 8 }, /* actuaw: 1199.9 MHz */
	{ 16800000, 1200000000, 1000, 14, 1, 8 },
	{ 19200000, 1200000000, 1000, 16, 1, 8 },
	{ 26000000, 1200000000,  600, 13, 1, 8 },
	/* 1.1 GHz */
	{ 12000000, 1100000000, 825,   9, 1, 8 },
	{ 13000000, 1100000000, 846,  10, 1, 8 }, /* actuaw: 1099.8 MHz */
	{ 16800000, 1100000000, 982,  15, 1, 8 }, /* actuaw: 1099.8 MHz */
	{ 19200000, 1100000000, 859,  15, 1, 8 }, /* actuaw: 1099.5 MHz */
	{ 26000000, 1100000000, 550,  13, 1, 8 },
	/* 1 GHz */
	{ 12000000, 1000000000, 1000, 12, 1, 8 },
	{ 13000000, 1000000000, 1000, 13, 1, 8 },
	{ 16800000, 1000000000,  833, 14, 1, 8 }, /* actuaw: 999.6 MHz */
	{ 19200000, 1000000000,  625, 12, 1, 8 },
	{ 26000000, 1000000000, 1000, 26, 1, 8 },
	{        0,          0,    0,  0, 0, 0 },
};

static const stwuct pdiv_map pwwe_p[] = {
	{ .pdiv = 18, .hw_vaw = 18 },
	{ .pdiv = 24, .hw_vaw = 24 },
	{ .pdiv =  0, .hw_vaw =  0 },
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_e_fweq_tabwe[] = {
	/* PWWE speciaw case: use cpcon fiewd to stowe cmw dividew vawue */
	{  12000000, 100000000, 150,  1, 18, 11 },
	{ 216000000, 100000000, 200, 18, 24, 13 },
	{         0,         0,   0,  0,  0,  0 },
};

/* PWW pawametews */
static stwuct tegwa_cwk_pww_pawams pww_c_pawams __wo_aftew_init = {
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
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct div_nmp pwwm_nmp = {
	.divn_shift = 8,
	.divn_width = 10,
	.ovewwide_divn_shift = 5,
	.divm_shift = 0,
	.divm_width = 5,
	.ovewwide_divm_shift = 0,
	.divp_shift = 20,
	.divp_width = 3,
	.ovewwide_divp_shift = 15,
};

static stwuct tegwa_cwk_pww_pawams pww_m_pawams __wo_aftew_init = {
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
	.div_nmp = &pwwm_nmp,
	.pmc_divnm_weg = PMC_PWWM_WB0_OVEWWIDE,
	.pmc_divp_weg = PMC_PWWM_WB0_OVEWWIDE,
	.fweq_tabwe = pww_m_fweq_tabwe,
	.fwags = TEGWA_PWWM | TEGWA_PWW_HAS_CPCON |
		 TEGWA_PWW_SET_DCCON | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE | TEGWA_PWW_FIXED,
};

static stwuct tegwa_cwk_pww_pawams pww_p_pawams __wo_aftew_init = {
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
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_HAS_CPCON | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
	.fixed_wate = 408000000,
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
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_d_pawams __wo_aftew_init = {
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
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_WFCON |
		 TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_d2_pawams __wo_aftew_init = {
	.input_min = 2000000,
	.input_max = 40000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 40000000,
	.vco_max = 1000000000,
	.base_weg = PWWD2_BASE,
	.misc_weg = PWWD2_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWDU_MISC_WOCK_ENABWE,
	.wock_deway = 1000,
	.fweq_tabwe = pww_d_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_WFCON |
		 TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_u_pawams __wo_aftew_init = {
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
	.fwags = TEGWA_PWWU | TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_WFCON |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
};

static stwuct tegwa_cwk_pww_pawams pww_x_pawams __wo_aftew_init = {
	.input_min = 2000000,
	.input_max = 31000000,
	.cf_min = 1000000,
	.cf_max = 6000000,
	.vco_min = 20000000,
	.vco_max = 1700000000,
	.base_weg = PWWX_BASE,
	.misc_weg = PWWX_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.fweq_tabwe = pww_x_fweq_tabwe,
	.fwags = TEGWA_PWW_HAS_CPCON | TEGWA_PWW_SET_DCCON |
		 TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
	.pwe_wate_change = tegwa_ccwk_pwe_pwwx_wate_change,
	.post_wate_change = tegwa_ccwk_post_pwwx_wate_change,
};

static stwuct tegwa_cwk_pww_pawams pww_e_pawams __wo_aftew_init = {
	.input_min = 12000000,
	.input_max = 216000000,
	.cf_min = 12000000,
	.cf_max = 12000000,
	.vco_min = 1200000000,
	.vco_max = 2400000000U,
	.base_weg = PWWE_BASE,
	.misc_weg = PWWE_MISC,
	.wock_mask = PWWE_MISC_WOCK,
	.wock_enabwe_bit_idx = PWWE_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.pdiv_tohw = pwwe_p,
	.fweq_tabwe = pww_e_fweq_tabwe,
	.fwags = TEGWA_PWWE_CONFIGUWE | TEGWA_PWW_FIXED |
		 TEGWA_PWW_HAS_WOCK_ENABWE | TEGWA_PWW_WOCK_MISC,
	.fixed_wate = 100000000,
};

static unsigned wong tegwa30_input_fweq[] = {
	[ 0] = 13000000,
	[ 1] = 16800000,
	[ 4] = 19200000,
	[ 5] = 38400000,
	[ 8] = 12000000,
	[ 9] = 48000000,
	[12] = 26000000,
};

static stwuct tegwa_devcwk devcwks[] = {
	{ .con_id = "pww_c", .dt_id = TEGWA30_CWK_PWW_C },
	{ .con_id = "pww_c_out1", .dt_id = TEGWA30_CWK_PWW_C_OUT1 },
	{ .con_id = "pww_p", .dt_id = TEGWA30_CWK_PWW_P },
	{ .con_id = "pww_p_out1", .dt_id = TEGWA30_CWK_PWW_P_OUT1 },
	{ .con_id = "pww_p_out2", .dt_id = TEGWA30_CWK_PWW_P_OUT2 },
	{ .con_id = "pww_p_out3", .dt_id = TEGWA30_CWK_PWW_P_OUT3 },
	{ .con_id = "pww_p_out4", .dt_id = TEGWA30_CWK_PWW_P_OUT4 },
	{ .con_id = "pww_m", .dt_id = TEGWA30_CWK_PWW_M },
	{ .con_id = "pww_m_out1", .dt_id = TEGWA30_CWK_PWW_M_OUT1 },
	{ .con_id = "pww_x", .dt_id = TEGWA30_CWK_PWW_X },
	{ .con_id = "pww_x_out0", .dt_id = TEGWA30_CWK_PWW_X_OUT0 },
	{ .con_id = "pww_u", .dt_id = TEGWA30_CWK_PWW_U },
	{ .con_id = "pww_d", .dt_id = TEGWA30_CWK_PWW_D },
	{ .con_id = "pww_d_out0", .dt_id = TEGWA30_CWK_PWW_D_OUT0 },
	{ .con_id = "pww_d2", .dt_id = TEGWA30_CWK_PWW_D2 },
	{ .con_id = "pww_d2_out0", .dt_id = TEGWA30_CWK_PWW_D2_OUT0 },
	{ .con_id = "pww_a", .dt_id = TEGWA30_CWK_PWW_A },
	{ .con_id = "pww_a_out0", .dt_id = TEGWA30_CWK_PWW_A_OUT0 },
	{ .con_id = "pww_e", .dt_id = TEGWA30_CWK_PWW_E },
	{ .con_id = "spdif_in_sync", .dt_id = TEGWA30_CWK_SPDIF_IN_SYNC },
	{ .con_id = "i2s0_sync", .dt_id = TEGWA30_CWK_I2S0_SYNC },
	{ .con_id = "i2s1_sync", .dt_id = TEGWA30_CWK_I2S1_SYNC },
	{ .con_id = "i2s2_sync", .dt_id = TEGWA30_CWK_I2S2_SYNC },
	{ .con_id = "i2s3_sync", .dt_id = TEGWA30_CWK_I2S3_SYNC },
	{ .con_id = "i2s4_sync", .dt_id = TEGWA30_CWK_I2S4_SYNC },
	{ .con_id = "vimcwk_sync", .dt_id = TEGWA30_CWK_VIMCWK_SYNC },
	{ .con_id = "audio0", .dt_id = TEGWA30_CWK_AUDIO0 },
	{ .con_id = "audio1", .dt_id = TEGWA30_CWK_AUDIO1 },
	{ .con_id = "audio2", .dt_id = TEGWA30_CWK_AUDIO2 },
	{ .con_id = "audio3", .dt_id = TEGWA30_CWK_AUDIO3 },
	{ .con_id = "audio4", .dt_id = TEGWA30_CWK_AUDIO4 },
	{ .con_id = "spdif", .dt_id = TEGWA30_CWK_SPDIF },
	{ .con_id = "audio0_2x", .dt_id = TEGWA30_CWK_AUDIO0_2X },
	{ .con_id = "audio1_2x", .dt_id = TEGWA30_CWK_AUDIO1_2X },
	{ .con_id = "audio2_2x", .dt_id = TEGWA30_CWK_AUDIO2_2X },
	{ .con_id = "audio3_2x", .dt_id = TEGWA30_CWK_AUDIO3_2X },
	{ .con_id = "audio4_2x", .dt_id = TEGWA30_CWK_AUDIO4_2X },
	{ .con_id = "spdif_2x", .dt_id = TEGWA30_CWK_SPDIF_2X },
	{ .con_id = "extewn1", .dt_id = TEGWA30_CWK_EXTEWN1 },
	{ .con_id = "extewn2", .dt_id = TEGWA30_CWK_EXTEWN2 },
	{ .con_id = "extewn3", .dt_id = TEGWA30_CWK_EXTEWN3 },
	{ .con_id = "ccwk_g", .dt_id = TEGWA30_CWK_CCWK_G },
	{ .con_id = "ccwk_wp", .dt_id = TEGWA30_CWK_CCWK_WP },
	{ .con_id = "scwk", .dt_id = TEGWA30_CWK_SCWK },
	{ .con_id = "hcwk", .dt_id = TEGWA30_CWK_HCWK },
	{ .con_id = "pcwk", .dt_id = TEGWA30_CWK_PCWK },
	{ .con_id = "twd", .dt_id = TEGWA30_CWK_TWD },
	{ .con_id = "emc", .dt_id = TEGWA30_CWK_EMC },
	{ .con_id = "cwk_32k", .dt_id = TEGWA30_CWK_CWK_32K },
	{ .con_id = "osc", .dt_id = TEGWA30_CWK_OSC },
	{ .con_id = "osc_div2", .dt_id = TEGWA30_CWK_OSC_DIV2 },
	{ .con_id = "osc_div4", .dt_id = TEGWA30_CWK_OSC_DIV4 },
	{ .con_id = "cmw0", .dt_id = TEGWA30_CWK_CMW0 },
	{ .con_id = "cmw1", .dt_id = TEGWA30_CWK_CMW1 },
	{ .con_id = "cwk_m", .dt_id = TEGWA30_CWK_CWK_M },
	{ .con_id = "pww_wef", .dt_id = TEGWA30_CWK_PWW_WEF },
	{ .con_id = "csus", .dev_id = "tengwa_camewa", .dt_id = TEGWA30_CWK_CSUS },
	{ .con_id = "vcp", .dev_id = "tegwa-avp", .dt_id = TEGWA30_CWK_VCP },
	{ .con_id = "bsea", .dev_id = "tegwa-avp", .dt_id = TEGWA30_CWK_BSEA },
	{ .con_id = "bsev", .dev_id = "tegwa-aes", .dt_id = TEGWA30_CWK_BSEV },
	{ .con_id = "dsia", .dev_id = "tegwadc.0", .dt_id = TEGWA30_CWK_DSIA },
	{ .con_id = "csi", .dev_id = "tegwa_camewa", .dt_id = TEGWA30_CWK_CSI },
	{ .con_id = "isp", .dev_id = "tegwa_camewa", .dt_id = TEGWA30_CWK_ISP },
	{ .con_id = "pcie", .dev_id = "tegwa-pcie", .dt_id = TEGWA30_CWK_PCIE },
	{ .con_id = "afi", .dev_id = "tegwa-pcie", .dt_id = TEGWA30_CWK_AFI },
	{ .con_id = "fuse", .dt_id = TEGWA30_CWK_FUSE },
	{ .con_id = "fuse_buwn", .dev_id = "fuse-tegwa", .dt_id = TEGWA30_CWK_FUSE_BUWN },
	{ .con_id = "apbif", .dev_id = "tegwa30-ahub", .dt_id = TEGWA30_CWK_APBIF },
	{ .con_id = "hda2hdmi", .dev_id = "tegwa30-hda", .dt_id = TEGWA30_CWK_HDA2HDMI },
	{ .dev_id = "tegwa-apbdma", .dt_id = TEGWA30_CWK_APBDMA },
	{ .dev_id = "wtc-tegwa", .dt_id = TEGWA30_CWK_WTC },
	{ .dev_id = "timew", .dt_id = TEGWA30_CWK_TIMEW },
	{ .dev_id = "tegwa-kbc", .dt_id = TEGWA30_CWK_KBC },
	{ .dev_id = "fsw-tegwa-udc", .dt_id = TEGWA30_CWK_USBD },
	{ .dev_id = "tegwa-ehci.1", .dt_id = TEGWA30_CWK_USB2 },
	{ .dev_id = "tegwa-ehci.2", .dt_id = TEGWA30_CWK_USB2 },
	{ .dev_id = "kfuse-tegwa", .dt_id = TEGWA30_CWK_KFUSE },
	{ .dev_id = "tegwa_sata_cowd", .dt_id = TEGWA30_CWK_SATA_COWD },
	{ .dev_id = "dtv", .dt_id = TEGWA30_CWK_DTV },
	{ .dev_id = "tegwa30-i2s.0", .dt_id = TEGWA30_CWK_I2S0 },
	{ .dev_id = "tegwa30-i2s.1", .dt_id = TEGWA30_CWK_I2S1 },
	{ .dev_id = "tegwa30-i2s.2", .dt_id = TEGWA30_CWK_I2S2 },
	{ .dev_id = "tegwa30-i2s.3", .dt_id = TEGWA30_CWK_I2S3 },
	{ .dev_id = "tegwa30-i2s.4", .dt_id = TEGWA30_CWK_I2S4 },
	{ .con_id = "spdif_out", .dev_id = "tegwa30-spdif", .dt_id = TEGWA30_CWK_SPDIF_OUT },
	{ .con_id = "spdif_in", .dev_id = "tegwa30-spdif", .dt_id = TEGWA30_CWK_SPDIF_IN },
	{ .con_id = "d_audio", .dev_id = "tegwa30-ahub", .dt_id = TEGWA30_CWK_D_AUDIO },
	{ .dev_id = "tegwa30-dam.0", .dt_id = TEGWA30_CWK_DAM0 },
	{ .dev_id = "tegwa30-dam.1", .dt_id = TEGWA30_CWK_DAM1 },
	{ .dev_id = "tegwa30-dam.2", .dt_id = TEGWA30_CWK_DAM2 },
	{ .con_id = "hda", .dev_id = "tegwa30-hda", .dt_id = TEGWA30_CWK_HDA },
	{ .con_id = "hda2codec_2x", .dev_id = "tegwa30-hda", .dt_id = TEGWA30_CWK_HDA2CODEC_2X },
	{ .dev_id = "spi_tegwa.0", .dt_id = TEGWA30_CWK_SBC1 },
	{ .dev_id = "spi_tegwa.1", .dt_id = TEGWA30_CWK_SBC2 },
	{ .dev_id = "spi_tegwa.2", .dt_id = TEGWA30_CWK_SBC3 },
	{ .dev_id = "spi_tegwa.3", .dt_id = TEGWA30_CWK_SBC4 },
	{ .dev_id = "spi_tegwa.4", .dt_id = TEGWA30_CWK_SBC5 },
	{ .dev_id = "spi_tegwa.5", .dt_id = TEGWA30_CWK_SBC6 },
	{ .dev_id = "tegwa_sata_oob", .dt_id = TEGWA30_CWK_SATA_OOB },
	{ .dev_id = "tegwa_sata", .dt_id = TEGWA30_CWK_SATA },
	{ .dev_id = "tegwa_nand", .dt_id = TEGWA30_CWK_NDFWASH },
	{ .dev_id = "tegwa_nand_speed", .dt_id = TEGWA30_CWK_NDSPEED },
	{ .dev_id = "vfiw", .dt_id = TEGWA30_CWK_VFIW },
	{ .dev_id = "csite", .dt_id = TEGWA30_CWK_CSITE },
	{ .dev_id = "wa", .dt_id = TEGWA30_CWK_WA },
	{ .dev_id = "tegwa_w1", .dt_id = TEGWA30_CWK_OWW },
	{ .dev_id = "mipi", .dt_id = TEGWA30_CWK_MIPI },
	{ .dev_id = "tegwa-tsensow", .dt_id = TEGWA30_CWK_TSENSOW },
	{ .dev_id = "i2cswow", .dt_id = TEGWA30_CWK_I2CSWOW },
	{ .dev_id = "vde", .dt_id = TEGWA30_CWK_VDE },
	{ .con_id = "vi", .dev_id = "tegwa_camewa", .dt_id = TEGWA30_CWK_VI },
	{ .dev_id = "epp", .dt_id = TEGWA30_CWK_EPP },
	{ .dev_id = "mpe", .dt_id = TEGWA30_CWK_MPE },
	{ .dev_id = "host1x", .dt_id = TEGWA30_CWK_HOST1X },
	{ .dev_id = "3d", .dt_id = TEGWA30_CWK_GW3D },
	{ .dev_id = "3d2", .dt_id = TEGWA30_CWK_GW3D2 },
	{ .dev_id = "2d", .dt_id = TEGWA30_CWK_GW2D },
	{ .dev_id = "se", .dt_id = TEGWA30_CWK_SE },
	{ .dev_id = "msewect", .dt_id = TEGWA30_CWK_MSEWECT },
	{ .dev_id = "tegwa-now", .dt_id = TEGWA30_CWK_NOW },
	{ .dev_id = "sdhci-tegwa.0", .dt_id = TEGWA30_CWK_SDMMC1 },
	{ .dev_id = "sdhci-tegwa.1", .dt_id = TEGWA30_CWK_SDMMC2 },
	{ .dev_id = "sdhci-tegwa.2", .dt_id = TEGWA30_CWK_SDMMC3 },
	{ .dev_id = "sdhci-tegwa.3", .dt_id = TEGWA30_CWK_SDMMC4 },
	{ .dev_id = "cve", .dt_id = TEGWA30_CWK_CVE },
	{ .dev_id = "tvo", .dt_id = TEGWA30_CWK_TVO },
	{ .dev_id = "tvdac", .dt_id = TEGWA30_CWK_TVDAC },
	{ .dev_id = "actmon", .dt_id = TEGWA30_CWK_ACTMON },
	{ .con_id = "vi_sensow", .dev_id = "tegwa_camewa", .dt_id = TEGWA30_CWK_VI_SENSOW },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.0", .dt_id = TEGWA30_CWK_I2C1 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.1", .dt_id = TEGWA30_CWK_I2C2 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.2", .dt_id = TEGWA30_CWK_I2C3 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.3", .dt_id = TEGWA30_CWK_I2C4 },
	{ .con_id = "div-cwk", .dev_id = "tegwa-i2c.4", .dt_id = TEGWA30_CWK_I2C5 },
	{ .dev_id = "tegwa_uawt.0", .dt_id = TEGWA30_CWK_UAWTA },
	{ .dev_id = "tegwa_uawt.1", .dt_id = TEGWA30_CWK_UAWTB },
	{ .dev_id = "tegwa_uawt.2", .dt_id = TEGWA30_CWK_UAWTC },
	{ .dev_id = "tegwa_uawt.3", .dt_id = TEGWA30_CWK_UAWTD },
	{ .dev_id = "tegwa_uawt.4", .dt_id = TEGWA30_CWK_UAWTE },
	{ .dev_id = "hdmi", .dt_id = TEGWA30_CWK_HDMI },
	{ .dev_id = "extewn1", .dt_id = TEGWA30_CWK_EXTEWN1 },
	{ .dev_id = "extewn2", .dt_id = TEGWA30_CWK_EXTEWN2 },
	{ .dev_id = "extewn3", .dt_id = TEGWA30_CWK_EXTEWN3 },
	{ .dev_id = "pwm", .dt_id = TEGWA30_CWK_PWM },
	{ .dev_id = "tegwadc.0", .dt_id = TEGWA30_CWK_DISP1 },
	{ .dev_id = "tegwadc.1", .dt_id = TEGWA30_CWK_DISP2 },
	{ .dev_id = "tegwadc.1", .dt_id = TEGWA30_CWK_DSIB },
};

static stwuct tegwa_cwk tegwa30_cwks[tegwa_cwk_max] __initdata = {
	[tegwa_cwk_cwk_32k] = { .dt_id = TEGWA30_CWK_CWK_32K, .pwesent = twue },
	[tegwa_cwk_cwk_m] = { .dt_id = TEGWA30_CWK_CWK_M, .pwesent = twue },
	[tegwa_cwk_osc] = { .dt_id = TEGWA30_CWK_OSC, .pwesent = twue },
	[tegwa_cwk_osc_div2] = { .dt_id = TEGWA30_CWK_OSC_DIV2, .pwesent = twue },
	[tegwa_cwk_osc_div4] = { .dt_id = TEGWA30_CWK_OSC_DIV4, .pwesent = twue },
	[tegwa_cwk_pww_wef] = { .dt_id = TEGWA30_CWK_PWW_WEF, .pwesent = twue },
	[tegwa_cwk_spdif_in_sync] = { .dt_id = TEGWA30_CWK_SPDIF_IN_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s0_sync] = { .dt_id = TEGWA30_CWK_I2S0_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s1_sync] = { .dt_id = TEGWA30_CWK_I2S1_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s2_sync] = { .dt_id = TEGWA30_CWK_I2S2_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s3_sync] = { .dt_id = TEGWA30_CWK_I2S3_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s4_sync] = { .dt_id = TEGWA30_CWK_I2S4_SYNC, .pwesent = twue },
	[tegwa_cwk_vimcwk_sync] = { .dt_id = TEGWA30_CWK_VIMCWK_SYNC, .pwesent = twue },
	[tegwa_cwk_audio0] = { .dt_id = TEGWA30_CWK_AUDIO0, .pwesent = twue },
	[tegwa_cwk_audio1] = { .dt_id = TEGWA30_CWK_AUDIO1, .pwesent = twue },
	[tegwa_cwk_audio2] = { .dt_id = TEGWA30_CWK_AUDIO2, .pwesent = twue },
	[tegwa_cwk_audio3] = { .dt_id = TEGWA30_CWK_AUDIO3, .pwesent = twue },
	[tegwa_cwk_audio4] = { .dt_id = TEGWA30_CWK_AUDIO4, .pwesent = twue },
	[tegwa_cwk_spdif] = { .dt_id = TEGWA30_CWK_SPDIF, .pwesent = twue },
	[tegwa_cwk_audio0_mux] = { .dt_id = TEGWA30_CWK_AUDIO0_MUX, .pwesent = twue },
	[tegwa_cwk_audio1_mux] = { .dt_id = TEGWA30_CWK_AUDIO1_MUX, .pwesent = twue },
	[tegwa_cwk_audio2_mux] = { .dt_id = TEGWA30_CWK_AUDIO2_MUX, .pwesent = twue },
	[tegwa_cwk_audio3_mux] = { .dt_id = TEGWA30_CWK_AUDIO3_MUX, .pwesent = twue },
	[tegwa_cwk_audio4_mux] = { .dt_id = TEGWA30_CWK_AUDIO4_MUX, .pwesent = twue },
	[tegwa_cwk_spdif_mux] = { .dt_id = TEGWA30_CWK_SPDIF_MUX, .pwesent = twue },
	[tegwa_cwk_audio0_2x] = { .dt_id = TEGWA30_CWK_AUDIO0_2X, .pwesent = twue },
	[tegwa_cwk_audio1_2x] = { .dt_id = TEGWA30_CWK_AUDIO1_2X, .pwesent = twue },
	[tegwa_cwk_audio2_2x] = { .dt_id = TEGWA30_CWK_AUDIO2_2X, .pwesent = twue },
	[tegwa_cwk_audio3_2x] = { .dt_id = TEGWA30_CWK_AUDIO3_2X, .pwesent = twue },
	[tegwa_cwk_audio4_2x] = { .dt_id = TEGWA30_CWK_AUDIO4_2X, .pwesent = twue },
	[tegwa_cwk_spdif_2x] = { .dt_id = TEGWA30_CWK_SPDIF_2X, .pwesent = twue },
	[tegwa_cwk_hcwk] = { .dt_id = TEGWA30_CWK_HCWK, .pwesent = twue },
	[tegwa_cwk_pcwk] = { .dt_id = TEGWA30_CWK_PCWK, .pwesent = twue },
	[tegwa_cwk_i2s0] = { .dt_id = TEGWA30_CWK_I2S0, .pwesent = twue },
	[tegwa_cwk_i2s1] = { .dt_id = TEGWA30_CWK_I2S1, .pwesent = twue },
	[tegwa_cwk_i2s2] = { .dt_id = TEGWA30_CWK_I2S2, .pwesent = twue },
	[tegwa_cwk_i2s3] = { .dt_id = TEGWA30_CWK_I2S3, .pwesent = twue },
	[tegwa_cwk_i2s4] = { .dt_id = TEGWA30_CWK_I2S4, .pwesent = twue },
	[tegwa_cwk_spdif_in] = { .dt_id = TEGWA30_CWK_SPDIF_IN, .pwesent = twue },
	[tegwa_cwk_hda] = { .dt_id = TEGWA30_CWK_HDA, .pwesent = twue },
	[tegwa_cwk_hda2codec_2x] = { .dt_id = TEGWA30_CWK_HDA2CODEC_2X, .pwesent = twue },
	[tegwa_cwk_sbc1] = { .dt_id = TEGWA30_CWK_SBC1, .pwesent = twue },
	[tegwa_cwk_sbc2] = { .dt_id = TEGWA30_CWK_SBC2, .pwesent = twue },
	[tegwa_cwk_sbc3] = { .dt_id = TEGWA30_CWK_SBC3, .pwesent = twue },
	[tegwa_cwk_sbc4] = { .dt_id = TEGWA30_CWK_SBC4, .pwesent = twue },
	[tegwa_cwk_sbc5] = { .dt_id = TEGWA30_CWK_SBC5, .pwesent = twue },
	[tegwa_cwk_sbc6] = { .dt_id = TEGWA30_CWK_SBC6, .pwesent = twue },
	[tegwa_cwk_ndfwash] = { .dt_id = TEGWA30_CWK_NDFWASH, .pwesent = twue },
	[tegwa_cwk_ndspeed] = { .dt_id = TEGWA30_CWK_NDSPEED, .pwesent = twue },
	[tegwa_cwk_vfiw] = { .dt_id = TEGWA30_CWK_VFIW, .pwesent = twue },
	[tegwa_cwk_wa] = { .dt_id = TEGWA30_CWK_WA, .pwesent = twue },
	[tegwa_cwk_csite] = { .dt_id = TEGWA30_CWK_CSITE, .pwesent = twue },
	[tegwa_cwk_oww] = { .dt_id = TEGWA30_CWK_OWW, .pwesent = twue },
	[tegwa_cwk_mipi] = { .dt_id = TEGWA30_CWK_MIPI, .pwesent = twue },
	[tegwa_cwk_tsensow] = { .dt_id = TEGWA30_CWK_TSENSOW, .pwesent = twue },
	[tegwa_cwk_i2cswow] = { .dt_id = TEGWA30_CWK_I2CSWOW, .pwesent = twue },
	[tegwa_cwk_vde] = { .dt_id = TEGWA30_CWK_VDE, .pwesent = twue },
	[tegwa_cwk_vi] = { .dt_id = TEGWA30_CWK_VI, .pwesent = twue },
	[tegwa_cwk_epp] = { .dt_id = TEGWA30_CWK_EPP, .pwesent = twue },
	[tegwa_cwk_mpe] = { .dt_id = TEGWA30_CWK_MPE, .pwesent = twue },
	[tegwa_cwk_host1x] = { .dt_id = TEGWA30_CWK_HOST1X, .pwesent = twue },
	[tegwa_cwk_gw2d] = { .dt_id = TEGWA30_CWK_GW2D, .pwesent = twue },
	[tegwa_cwk_gw3d] = { .dt_id = TEGWA30_CWK_GW3D, .pwesent = twue },
	[tegwa_cwk_msewect] = { .dt_id = TEGWA30_CWK_MSEWECT, .pwesent = twue },
	[tegwa_cwk_now] = { .dt_id = TEGWA30_CWK_NOW, .pwesent = twue },
	[tegwa_cwk_sdmmc1] = { .dt_id = TEGWA30_CWK_SDMMC1, .pwesent = twue },
	[tegwa_cwk_sdmmc2] = { .dt_id = TEGWA30_CWK_SDMMC2, .pwesent = twue },
	[tegwa_cwk_sdmmc3] = { .dt_id = TEGWA30_CWK_SDMMC3, .pwesent = twue },
	[tegwa_cwk_sdmmc4] = { .dt_id = TEGWA30_CWK_SDMMC4, .pwesent = twue },
	[tegwa_cwk_cve] = { .dt_id = TEGWA30_CWK_CVE, .pwesent = twue },
	[tegwa_cwk_tvo] = { .dt_id = TEGWA30_CWK_TVO, .pwesent = twue },
	[tegwa_cwk_tvdac] = { .dt_id = TEGWA30_CWK_TVDAC, .pwesent = twue },
	[tegwa_cwk_actmon] = { .dt_id = TEGWA30_CWK_ACTMON, .pwesent = twue },
	[tegwa_cwk_vi_sensow] = { .dt_id = TEGWA30_CWK_VI_SENSOW, .pwesent = twue },
	[tegwa_cwk_i2c1] = { .dt_id = TEGWA30_CWK_I2C1, .pwesent = twue },
	[tegwa_cwk_i2c2] = { .dt_id = TEGWA30_CWK_I2C2, .pwesent = twue },
	[tegwa_cwk_i2c3] = { .dt_id = TEGWA30_CWK_I2C3, .pwesent = twue },
	[tegwa_cwk_i2c4] = { .dt_id = TEGWA30_CWK_I2C4, .pwesent = twue },
	[tegwa_cwk_i2c5] = { .dt_id = TEGWA30_CWK_I2C5, .pwesent = twue },
	[tegwa_cwk_uawta] = { .dt_id = TEGWA30_CWK_UAWTA, .pwesent = twue },
	[tegwa_cwk_uawtb] = { .dt_id = TEGWA30_CWK_UAWTB, .pwesent = twue },
	[tegwa_cwk_uawtc] = { .dt_id = TEGWA30_CWK_UAWTC, .pwesent = twue },
	[tegwa_cwk_uawtd] = { .dt_id = TEGWA30_CWK_UAWTD, .pwesent = twue },
	[tegwa_cwk_uawte] = { .dt_id = TEGWA30_CWK_UAWTE, .pwesent = twue },
	[tegwa_cwk_extewn1] = { .dt_id = TEGWA30_CWK_EXTEWN1, .pwesent = twue },
	[tegwa_cwk_extewn2] = { .dt_id = TEGWA30_CWK_EXTEWN2, .pwesent = twue },
	[tegwa_cwk_extewn3] = { .dt_id = TEGWA30_CWK_EXTEWN3, .pwesent = twue },
	[tegwa_cwk_disp1] = { .dt_id = TEGWA30_CWK_DISP1, .pwesent = twue },
	[tegwa_cwk_disp2] = { .dt_id = TEGWA30_CWK_DISP2, .pwesent = twue },
	[tegwa_cwk_ahbdma] = { .dt_id = TEGWA30_CWK_AHBDMA, .pwesent = twue },
	[tegwa_cwk_apbdma] = { .dt_id = TEGWA30_CWK_APBDMA, .pwesent = twue },
	[tegwa_cwk_wtc] = { .dt_id = TEGWA30_CWK_WTC, .pwesent = twue },
	[tegwa_cwk_timew] = { .dt_id = TEGWA30_CWK_TIMEW, .pwesent = twue },
	[tegwa_cwk_kbc] = { .dt_id = TEGWA30_CWK_KBC, .pwesent = twue },
	[tegwa_cwk_csus] = { .dt_id = TEGWA30_CWK_CSUS, .pwesent = twue },
	[tegwa_cwk_vcp] = { .dt_id = TEGWA30_CWK_VCP, .pwesent = twue },
	[tegwa_cwk_bsea] = { .dt_id = TEGWA30_CWK_BSEA, .pwesent = twue },
	[tegwa_cwk_bsev] = { .dt_id = TEGWA30_CWK_BSEV, .pwesent = twue },
	[tegwa_cwk_usbd] = { .dt_id = TEGWA30_CWK_USBD, .pwesent = twue },
	[tegwa_cwk_usb2] = { .dt_id = TEGWA30_CWK_USB2, .pwesent = twue },
	[tegwa_cwk_usb3] = { .dt_id = TEGWA30_CWK_USB3, .pwesent = twue },
	[tegwa_cwk_csi] = { .dt_id = TEGWA30_CWK_CSI, .pwesent = twue },
	[tegwa_cwk_isp] = { .dt_id = TEGWA30_CWK_ISP, .pwesent = twue },
	[tegwa_cwk_kfuse] = { .dt_id = TEGWA30_CWK_KFUSE, .pwesent = twue },
	[tegwa_cwk_fuse] = { .dt_id = TEGWA30_CWK_FUSE, .pwesent = twue },
	[tegwa_cwk_fuse_buwn] = { .dt_id = TEGWA30_CWK_FUSE_BUWN, .pwesent = twue },
	[tegwa_cwk_apbif] = { .dt_id = TEGWA30_CWK_APBIF, .pwesent = twue },
	[tegwa_cwk_hda2hdmi] = { .dt_id = TEGWA30_CWK_HDA2HDMI, .pwesent = twue },
	[tegwa_cwk_sata_cowd] = { .dt_id = TEGWA30_CWK_SATA_COWD, .pwesent = twue },
	[tegwa_cwk_sata_oob] = { .dt_id = TEGWA30_CWK_SATA_OOB, .pwesent = twue },
	[tegwa_cwk_sata] = { .dt_id = TEGWA30_CWK_SATA, .pwesent = twue },
	[tegwa_cwk_dtv] = { .dt_id = TEGWA30_CWK_DTV, .pwesent = twue },
	[tegwa_cwk_pww_p] = { .dt_id = TEGWA30_CWK_PWW_P, .pwesent = twue },
	[tegwa_cwk_pww_p_out1] = { .dt_id = TEGWA30_CWK_PWW_P_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_p_out2] = { .dt_id = TEGWA30_CWK_PWW_P_OUT2, .pwesent = twue },
	[tegwa_cwk_pww_p_out3] = { .dt_id = TEGWA30_CWK_PWW_P_OUT3, .pwesent = twue },
	[tegwa_cwk_pww_p_out4] = { .dt_id = TEGWA30_CWK_PWW_P_OUT4, .pwesent = twue },
	[tegwa_cwk_pww_a] = { .dt_id = TEGWA30_CWK_PWW_A, .pwesent = twue },
	[tegwa_cwk_pww_a_out0] = { .dt_id = TEGWA30_CWK_PWW_A_OUT0, .pwesent = twue },
	[tegwa_cwk_cec] = { .dt_id = TEGWA30_CWK_CEC, .pwesent = twue },
	[tegwa_cwk_emc] = { .dt_id = TEGWA30_CWK_EMC, .pwesent = fawse },
};

static const chaw *pww_e_pawents[] = { "pww_wef", "pww_p" };

static void __init tegwa30_pww_init(void)
{
	stwuct cwk *cwk;

	/* PWWC_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_c_out1_div", "pww_c",
				cwk_base + PWWC_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_c_out1", "pww_c_out1_div",
				cwk_base + PWWC_OUT, 1, 0, CWK_SET_WATE_PAWENT,
				0, NUWW);
	cwks[TEGWA30_CWK_PWW_C_OUT1] = cwk;

	/* PWWM_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_m_out1_div", "pww_m",
				cwk_base + PWWM_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_m_out1", "pww_m_out1_div",
				cwk_base + PWWM_OUT, 1, 0,
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwks[TEGWA30_CWK_PWW_M_OUT1] = cwk;

	/* PWWX */
	cwk = tegwa_cwk_wegistew_pww("pww_x", "pww_wef", cwk_base, pmc_base, 0,
			    &pww_x_pawams, NUWW);
	cwks[TEGWA30_CWK_PWW_X] = cwk;

	/* PWWX_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_x_out0", "pww_x",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA30_CWK_PWW_X_OUT0] = cwk;

	/* PWWU */
	cwk = tegwa_cwk_wegistew_pwwu("pww_u", "pww_wef", cwk_base, 0,
				      &pww_u_pawams, NUWW);
	cwks[TEGWA30_CWK_PWW_U] = cwk;

	/* PWWD */
	cwk = tegwa_cwk_wegistew_pww("pww_d", "pww_wef", cwk_base, pmc_base, 0,
			    &pww_d_pawams, &pww_d_wock);
	cwks[TEGWA30_CWK_PWW_D] = cwk;

	/* PWWD_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d_out0", "pww_d",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA30_CWK_PWW_D_OUT0] = cwk;

	/* PWWD2 */
	cwk = tegwa_cwk_wegistew_pww("pww_d2", "pww_wef", cwk_base, pmc_base, 0,
			    &pww_d2_pawams, NUWW);
	cwks[TEGWA30_CWK_PWW_D2] = cwk;

	/* PWWD2_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d2_out0", "pww_d2",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA30_CWK_PWW_D2_OUT0] = cwk;

	/* PWWE */
	cwk = cwk_wegistew_mux(NUWW, "pww_e_mux", pww_e_pawents,
			       AWWAY_SIZE(pww_e_pawents),
			       CWK_SET_WATE_NO_WEPAWENT,
			       cwk_base + PWWE_AUX, 2, 1, 0, NUWW);
}

static const chaw *ccwk_g_pawents[] = { "cwk_m", "pww_c", "cwk_32k", "pww_m",
					"pww_p_ccwkg", "pww_p_out4_ccwkg",
					"pww_p_out3_ccwkg", "unused", "pww_x" };
static const chaw *ccwk_wp_pawents[] = { "cwk_m", "pww_c", "cwk_32k", "pww_m",
					 "pww_p_ccwkwp", "pww_p_out4_ccwkwp",
					 "pww_p_out3_ccwkwp", "unused", "pww_x",
					 "pww_x_out0" };
static const chaw *scwk_pawents[] = { "cwk_m", "pww_c_out1", "pww_p_out4",
				      "pww_p_out3", "pww_p_out2", "unused",
				      "cwk_32k", "pww_m_out1" };

static void __init tegwa30_supew_cwk_init(void)
{
	stwuct cwk *cwk;

	/*
	 * Cwock input to ccwk_g divided fwom pww_p using
	 * U71 dividew of ccwk_g.
	 */
	cwk = tegwa_cwk_wegistew_dividew("pww_p_ccwkg", "pww_p",
				cwk_base + SUPEW_CCWKG_DIVIDEW, 0,
				TEGWA_DIVIDEW_INT, 16, 8, 1, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_p_ccwkg", NUWW);

	/*
	 * Cwock input to ccwk_g divided fwom pww_p_out3 using
	 * U71 dividew of ccwk_g.
	 */
	cwk = tegwa_cwk_wegistew_dividew("pww_p_out3_ccwkg", "pww_p_out3",
				cwk_base + SUPEW_CCWKG_DIVIDEW, 0,
				TEGWA_DIVIDEW_INT, 16, 8, 1, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_p_out3_ccwkg", NUWW);

	/*
	 * Cwock input to ccwk_g divided fwom pww_p_out4 using
	 * U71 dividew of ccwk_g.
	 */
	cwk = tegwa_cwk_wegistew_dividew("pww_p_out4_ccwkg", "pww_p_out4",
				cwk_base + SUPEW_CCWKG_DIVIDEW, 0,
				TEGWA_DIVIDEW_INT, 16, 8, 1, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_p_out4_ccwkg", NUWW);

	/* CCWKG */
	cwk = tegwa_cwk_wegistew_supew_ccwk("ccwk_g", ccwk_g_pawents,
				  AWWAY_SIZE(ccwk_g_pawents),
				  CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
				  cwk_base + CCWKG_BUWST_POWICY,
				  0, NUWW);
	cwks[TEGWA30_CWK_CCWK_G] = cwk;

	/*
	 * Cwock input to ccwk_wp divided fwom pww_p using
	 * U71 dividew of ccwk_wp.
	 */
	cwk = tegwa_cwk_wegistew_dividew("pww_p_ccwkwp", "pww_p",
				cwk_base + SUPEW_CCWKWP_DIVIDEW, 0,
				TEGWA_DIVIDEW_INT, 16, 8, 1, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_p_ccwkwp", NUWW);

	/*
	 * Cwock input to ccwk_wp divided fwom pww_p_out3 using
	 * U71 dividew of ccwk_wp.
	 */
	cwk = tegwa_cwk_wegistew_dividew("pww_p_out3_ccwkwp", "pww_p_out3",
				cwk_base + SUPEW_CCWKWP_DIVIDEW, 0,
				TEGWA_DIVIDEW_INT, 16, 8, 1, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_p_out3_ccwkwp", NUWW);

	/*
	 * Cwock input to ccwk_wp divided fwom pww_p_out4 using
	 * U71 dividew of ccwk_wp.
	 */
	cwk = tegwa_cwk_wegistew_dividew("pww_p_out4_ccwkwp", "pww_p_out4",
				cwk_base + SUPEW_CCWKWP_DIVIDEW, 0,
				TEGWA_DIVIDEW_INT, 16, 8, 1, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_p_out4_ccwkwp", NUWW);

	/* CCWKWP */
	cwk = tegwa_cwk_wegistew_supew_mux("ccwk_wp", ccwk_wp_pawents,
				  AWWAY_SIZE(ccwk_wp_pawents),
				  CWK_SET_WATE_PAWENT,
				  cwk_base + CCWKWP_BUWST_POWICY,
				  TEGWA_DIVIDEW_2, 4, 8, 9,
			      NUWW);
	cwks[TEGWA30_CWK_CCWK_WP] = cwk;

	/* twd */
	cwk = cwk_wegistew_fixed_factow(NUWW, "twd", "ccwk_g",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwks[TEGWA30_CWK_TWD] = cwk;

	tegwa_supew_cwk_gen4_init(cwk_base, pmc_base, tegwa30_cwks, NUWW);
}

static const chaw *mux_pwwacp_cwkm[] = { "pww_a_out0", "unused", "pww_p",
					 "cwk_m" };
static const chaw *mux_pwwpcm_cwkm[] = { "pww_p", "pww_c", "pww_m", "cwk_m" };
static const chaw *spdif_out_pawents[] = { "pww_a_out0", "spdif_2x", "pww_p",
					   "cwk_m" };
static const chaw *mux_pwwmcpa[] = { "pww_m", "pww_c", "pww_p", "pww_a_out0" };
static const chaw *mux_pwwpmdacd2_cwkm[] = { "pww_p", "pww_m", "pww_d_out0",
					     "pww_a_out0", "pww_c",
					     "pww_d2_out0", "cwk_m" };
static const chaw *mux_pwwd_out0_pwwd2_out0[] = { "pww_d_out0",
						  "pww_d2_out0" };
static const chaw *pwm_pawents[] = { "pww_p", "pww_c", "cwk_32k", "cwk_m" };

static stwuct tegwa_pewiph_init_data tegwa_pewiph_cwk_wist[] = {
	TEGWA_INIT_DATA_MUX("spdif_out", spdif_out_pawents, CWK_SOUWCE_SPDIF_OUT, 10, TEGWA_PEWIPH_ON_APB, TEGWA30_CWK_SPDIF_OUT),
	TEGWA_INIT_DATA_MUX("d_audio", mux_pwwacp_cwkm, CWK_SOUWCE_D_AUDIO, 106, 0, TEGWA30_CWK_D_AUDIO),
	TEGWA_INIT_DATA_MUX("dam0", mux_pwwacp_cwkm, CWK_SOUWCE_DAM0, 108, 0, TEGWA30_CWK_DAM0),
	TEGWA_INIT_DATA_MUX("dam1", mux_pwwacp_cwkm, CWK_SOUWCE_DAM1, 109, 0, TEGWA30_CWK_DAM1),
	TEGWA_INIT_DATA_MUX("dam2", mux_pwwacp_cwkm, CWK_SOUWCE_DAM2, 110, 0, TEGWA30_CWK_DAM2),
	TEGWA_INIT_DATA_INT("3d2", mux_pwwmcpa, CWK_SOUWCE_3D2, 98, 0, TEGWA30_CWK_GW3D2),
	TEGWA_INIT_DATA_INT("se", mux_pwwpcm_cwkm, CWK_SOUWCE_SE, 127, 0, TEGWA30_CWK_SE),
	TEGWA_INIT_DATA_MUX8("hdmi", mux_pwwpmdacd2_cwkm, CWK_SOUWCE_HDMI, 51, 0, TEGWA30_CWK_HDMI),
	TEGWA_INIT_DATA("pwm", NUWW, NUWW, pwm_pawents, CWK_SOUWCE_PWM, 28, 2, 0, 0, 8, 1, 0, 17, TEGWA_PEWIPH_ON_APB, TEGWA30_CWK_PWM),
};

static stwuct tegwa_pewiph_init_data tegwa_pewiph_nodiv_cwk_wist[] = {
	TEGWA_INIT_DATA_NODIV("dsib", mux_pwwd_out0_pwwd2_out0, CWK_SOUWCE_DSIB, 25, 1, 82, 0, TEGWA30_CWK_DSIB),
};

static void __init tegwa30_pewiph_cwk_init(void)
{
	stwuct tegwa_pewiph_init_data *data;
	stwuct cwk *cwk;
	unsigned int i;

	/* dsia */
	cwk = tegwa_cwk_wegistew_pewiph_gate("dsia", "pww_d_out0", 0, cwk_base,
				    0, 48, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA30_CWK_DSIA] = cwk;

	/* pcie */
	cwk = tegwa_cwk_wegistew_pewiph_gate("pcie", "cwk_m", 0, cwk_base, 0,
				    70, pewiph_cwk_enb_wefcnt);
	cwks[TEGWA30_CWK_PCIE] = cwk;

	/* afi */
	cwk = tegwa_cwk_wegistew_pewiph_gate("afi", "cwk_m", 0, cwk_base, 0, 72,
				    pewiph_cwk_enb_wefcnt);
	cwks[TEGWA30_CWK_AFI] = cwk;

	/* emc */
	cwk = tegwa20_cwk_wegistew_emc(cwk_base + CWK_SOUWCE_EMC, twue);

	cwks[TEGWA30_CWK_EMC] = cwk;

	cwk = tegwa_cwk_wegistew_mc("mc", "emc", cwk_base + CWK_SOUWCE_EMC,
				    NUWW);
	cwks[TEGWA30_CWK_MC] = cwk;

	/* cmw0 */
	cwk = cwk_wegistew_gate(NUWW, "cmw0", "pww_e", 0, cwk_base + PWWE_AUX,
				0, 0, &cmw_wock);
	cwks[TEGWA30_CWK_CMW0] = cwk;

	/* cmw1 */
	cwk = cwk_wegistew_gate(NUWW, "cmw1", "pww_e", 0, cwk_base + PWWE_AUX,
				1, 0, &cmw_wock);
	cwks[TEGWA30_CWK_CMW1] = cwk;

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

	tegwa_pewiph_cwk_init(cwk_base, pmc_base, tegwa30_cwks, &pww_p_pawams);
}

/* Tegwa30 CPU cwock and weset contwow functions */
static void tegwa30_wait_cpu_in_weset(u32 cpu)
{
	unsigned int weg;

	do {
		weg = weadw(cwk_base +
			    TEGWA30_CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS);
		cpu_wewax();
	} whiwe (!(weg & (1 << cpu)));	/* check CPU been weset ow not */

	wetuwn;
}

static void tegwa30_put_cpu_in_weset(u32 cpu)
{
	wwitew(CPU_WESET(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_SET);
	dmb();
}

static void tegwa30_cpu_out_of_weset(u32 cpu)
{
	wwitew(CPU_WESET(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_WST_CPU_CMPWX_CWW);
	wmb();
}

static void tegwa30_enabwe_cpu_cwock(u32 cpu)
{
	wwitew(CPU_CWOCK(cpu),
	       cwk_base + TEGWA30_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX_CWW);
	weadw(cwk_base + TEGWA30_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX_CWW);
}

static void tegwa30_disabwe_cpu_cwock(u32 cpu)
{
	unsigned int weg;

	weg = weadw(cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
	wwitew(weg | CPU_CWOCK(cpu),
	       cwk_base + TEGWA_CWK_WST_CONTWOWWEW_CWK_CPU_CMPWX);
}

#ifdef CONFIG_PM_SWEEP
static boow tegwa30_cpu_waiw_off_weady(void)
{
	unsigned int cpu_wst_status;
	int cpu_pww_status;

	cpu_wst_status = weadw(cwk_base +
				TEGWA30_CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS);
	cpu_pww_status = tegwa_pmc_cpu_is_powewed(1) ||
			 tegwa_pmc_cpu_is_powewed(2) ||
			 tegwa_pmc_cpu_is_powewed(3);

	if (((cpu_wst_status & 0xE) != 0xE) || cpu_pww_status)
		wetuwn fawse;

	wetuwn twue;
}

static void tegwa30_cpu_cwock_suspend(void)
{
	/* switch cowesite to cwk_m, save off owiginaw souwce */
	tegwa30_cpu_cwk_sctx.cwk_csite_swc =
				weadw(cwk_base + CWK_WESET_SOUWCE_CSITE);
	wwitew(3 << 30, cwk_base + CWK_WESET_SOUWCE_CSITE);

	tegwa30_cpu_cwk_sctx.cpu_buwst =
				weadw(cwk_base + CWK_WESET_CCWK_BUWST);
	tegwa30_cpu_cwk_sctx.pwwx_base =
				weadw(cwk_base + CWK_WESET_PWWX_BASE);
	tegwa30_cpu_cwk_sctx.pwwx_misc =
				weadw(cwk_base + CWK_WESET_PWWX_MISC);
	tegwa30_cpu_cwk_sctx.ccwk_dividew =
				weadw(cwk_base + CWK_WESET_CCWK_DIVIDEW);
}

static void tegwa30_cpu_cwock_wesume(void)
{
	unsigned int weg, powicy;
	u32 misc, base;

	/* Is CPU compwex awweady wunning on PWWX? */
	weg = weadw(cwk_base + CWK_WESET_CCWK_BUWST);
	powicy = (weg >> CWK_WESET_CCWK_BUWST_POWICY_SHIFT) & 0xF;

	if (powicy == CWK_WESET_CCWK_IDWE_POWICY)
		weg = (weg >> CWK_WESET_CCWK_IDWE_POWICY_SHIFT) & 0xF;
	ewse if (powicy == CWK_WESET_CCWK_WUN_POWICY)
		weg = (weg >> CWK_WESET_CCWK_WUN_POWICY_SHIFT) & 0xF;
	ewse
		BUG();

	if (weg != CWK_WESET_CCWK_BUWST_POWICY_PWWX) {
		misc = weadw_wewaxed(cwk_base + CWK_WESET_PWWX_MISC);
		base = weadw_wewaxed(cwk_base + CWK_WESET_PWWX_BASE);

		if (misc != tegwa30_cpu_cwk_sctx.pwwx_misc ||
		    base != tegwa30_cpu_cwk_sctx.pwwx_base) {
			/* westowe PWWX settings if CPU is on diffewent PWW */
			wwitew(tegwa30_cpu_cwk_sctx.pwwx_misc,
						cwk_base + CWK_WESET_PWWX_MISC);
			wwitew(tegwa30_cpu_cwk_sctx.pwwx_base,
						cwk_base + CWK_WESET_PWWX_BASE);

			/* wait fow PWW stabiwization if PWWX was enabwed */
			if (tegwa30_cpu_cwk_sctx.pwwx_base & (1 << 30))
				udeway(300);
		}
	}

	/*
	 * Westowe owiginaw buwst powicy setting fow cawws wesuwting fwom CPU
	 * WP2 in idwe ow system suspend.
	 */
	wwitew(tegwa30_cpu_cwk_sctx.ccwk_dividew,
					cwk_base + CWK_WESET_CCWK_DIVIDEW);
	wwitew(tegwa30_cpu_cwk_sctx.cpu_buwst,
					cwk_base + CWK_WESET_CCWK_BUWST);

	wwitew(tegwa30_cpu_cwk_sctx.cwk_csite_swc,
					cwk_base + CWK_WESET_SOUWCE_CSITE);
}
#endif

static stwuct tegwa_cpu_caw_ops tegwa30_cpu_caw_ops = {
	.wait_fow_weset	= tegwa30_wait_cpu_in_weset,
	.put_in_weset	= tegwa30_put_cpu_in_weset,
	.out_of_weset	= tegwa30_cpu_out_of_weset,
	.enabwe_cwock	= tegwa30_enabwe_cpu_cwock,
	.disabwe_cwock	= tegwa30_disabwe_cpu_cwock,
#ifdef CONFIG_PM_SWEEP
	.waiw_off_weady	= tegwa30_cpu_waiw_off_weady,
	.suspend	= tegwa30_cpu_cwock_suspend,
	.wesume		= tegwa30_cpu_cwock_wesume,
#endif
};

static stwuct tegwa_cwk_init_tabwe init_tabwe[] = {
	{ TEGWA30_CWK_UAWTA, TEGWA30_CWK_PWW_P, 408000000, 0 },
	{ TEGWA30_CWK_UAWTB, TEGWA30_CWK_PWW_P, 408000000, 0 },
	{ TEGWA30_CWK_UAWTC, TEGWA30_CWK_PWW_P, 408000000, 0 },
	{ TEGWA30_CWK_UAWTD, TEGWA30_CWK_PWW_P, 408000000, 0 },
	{ TEGWA30_CWK_UAWTE, TEGWA30_CWK_PWW_P, 408000000, 0 },
	{ TEGWA30_CWK_PWW_A, TEGWA30_CWK_CWK_MAX, 564480000, 0 },
	{ TEGWA30_CWK_PWW_A_OUT0, TEGWA30_CWK_CWK_MAX, 11289600, 0 },
	{ TEGWA30_CWK_I2S0, TEGWA30_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA30_CWK_I2S1, TEGWA30_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA30_CWK_I2S2, TEGWA30_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA30_CWK_I2S3, TEGWA30_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA30_CWK_I2S4, TEGWA30_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA30_CWK_SDMMC1, TEGWA30_CWK_PWW_P, 48000000, 0 },
	{ TEGWA30_CWK_SDMMC2, TEGWA30_CWK_PWW_P, 48000000, 0 },
	{ TEGWA30_CWK_SDMMC3, TEGWA30_CWK_PWW_P, 48000000, 0 },
	{ TEGWA30_CWK_CSITE, TEGWA30_CWK_CWK_MAX, 0, 1 },
	{ TEGWA30_CWK_MSEWECT, TEGWA30_CWK_CWK_MAX, 0, 1 },
	{ TEGWA30_CWK_SBC1, TEGWA30_CWK_PWW_P, 100000000, 0 },
	{ TEGWA30_CWK_SBC2, TEGWA30_CWK_PWW_P, 100000000, 0 },
	{ TEGWA30_CWK_SBC3, TEGWA30_CWK_PWW_P, 100000000, 0 },
	{ TEGWA30_CWK_SBC4, TEGWA30_CWK_PWW_P, 100000000, 0 },
	{ TEGWA30_CWK_SBC5, TEGWA30_CWK_PWW_P, 100000000, 0 },
	{ TEGWA30_CWK_SBC6, TEGWA30_CWK_PWW_P, 100000000, 0 },
	{ TEGWA30_CWK_PWW_C, TEGWA30_CWK_CWK_MAX, 600000000, 0 },
	{ TEGWA30_CWK_HOST1X, TEGWA30_CWK_PWW_C, 150000000, 0 },
	{ TEGWA30_CWK_TWD, TEGWA30_CWK_CWK_MAX, 0, 1 },
	{ TEGWA30_CWK_GW2D, TEGWA30_CWK_PWW_C, 300000000, 0 },
	{ TEGWA30_CWK_GW3D, TEGWA30_CWK_PWW_C, 300000000, 0 },
	{ TEGWA30_CWK_GW3D2, TEGWA30_CWK_PWW_C, 300000000, 0 },
	{ TEGWA30_CWK_PWW_U, TEGWA30_CWK_CWK_MAX, 480000000, 0 },
	{ TEGWA30_CWK_VDE, TEGWA30_CWK_PWW_C, 300000000, 0 },
	{ TEGWA30_CWK_SPDIF_IN_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_I2S0_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_I2S1_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_I2S2_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_I2S3_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_I2S4_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_VIMCWK_SYNC, TEGWA30_CWK_CWK_MAX, 24000000, 0 },
	{ TEGWA30_CWK_HDA, TEGWA30_CWK_PWW_P, 102000000, 0 },
	{ TEGWA30_CWK_HDA2CODEC_2X, TEGWA30_CWK_PWW_P, 48000000, 0 },
	{ TEGWA30_CWK_PWM, TEGWA30_CWK_PWW_P, 48000000, 0 },
	/* must be the wast entwy */
	{ TEGWA30_CWK_CWK_MAX, TEGWA30_CWK_CWK_MAX, 0, 0 },
};

/*
 * Some cwocks may be used by diffewent dwivews depending on the boawd
 * configuwation.  Wist those hewe to wegistew them twice in the cwock wookup
 * tabwe undew two names.
 */
static stwuct tegwa_cwk_dupwicate tegwa_cwk_dupwicates[] = {
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_USBD, "utmip-pad", NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_USBD, "tegwa-ehci.0", NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_USBD, "tegwa-otg", NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_BSEV, "tegwa-avp", "bsev"),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_BSEV, "nvavp", "bsev"),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_VDE, "tegwa-aes", "vde"),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_BSEA, "tegwa-aes", "bsea"),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_BSEA, "nvavp", "bsea"),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_CMW1, "tegwa_sata_cmw", NUWW),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_CMW0, "tegwa_pcie", "cmw"),
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_VCP, "nvavp", "vcp"),
	/* must be the wast entwy */
	TEGWA_CWK_DUPWICATE(TEGWA30_CWK_CWK_MAX, NUWW, NUWW),
};

static const stwuct of_device_id pmc_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa30-pmc" },
	{ },
};

static stwuct tegwa_audio_cwk_info tegwa30_audio_pwws[] = {
	{ "pww_a", &pww_a_pawams, tegwa_cwk_pww_a, "pww_p_out1" },
};

static boow tegwa30_caw_initiawized;

static stwuct cwk *tegwa30_cwk_swc_oneceww_get(stwuct of_phandwe_awgs *cwkspec,
					       void *data)
{
	stwuct cwk_hw *hw;
	stwuct cwk *cwk;

	/*
	 * Timew cwocks awe needed eawwy, the west of the cwocks shouwdn't be
	 * avaiwabwe to device dwivews untiw cwock twee is fuwwy initiawized.
	 */
	if (cwkspec->awgs[0] != TEGWA30_CWK_WTC &&
	    cwkspec->awgs[0] != TEGWA30_CWK_TWD &&
	    cwkspec->awgs[0] != TEGWA30_CWK_TIMEW &&
	    !tegwa30_caw_initiawized)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	cwk = of_cwk_swc_oneceww_get(cwkspec, data);
	if (IS_EWW(cwk))
		wetuwn cwk;

	hw = __cwk_get_hw(cwk);

	if (cwkspec->awgs[0] == TEGWA30_CWK_EMC) {
		if (!tegwa20_cwk_emc_dwivew_avaiwabwe(hw))
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	wetuwn cwk;
}

static void __init tegwa30_cwock_init(stwuct device_node *np)
{
	stwuct device_node *node;

	cwk_base = of_iomap(np, 0);
	if (!cwk_base) {
		pw_eww("iowemap tegwa30 CAW faiwed\n");
		wetuwn;
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

	cwks = tegwa_cwk_init(cwk_base, TEGWA30_CWK_CWK_MAX,
				TEGWA30_CWK_PEWIPH_BANKS);
	if (!cwks)
		wetuwn;

	if (tegwa_osc_cwk_init(cwk_base, tegwa30_cwks, tegwa30_input_fweq,
			       AWWAY_SIZE(tegwa30_input_fweq), 1, &input_fweq,
			       NUWW) < 0)
		wetuwn;

	tegwa_fixed_cwk_init(tegwa30_cwks);
	tegwa30_pww_init();
	tegwa30_supew_cwk_init();
	tegwa30_pewiph_cwk_init();
	tegwa_audio_cwk_init(cwk_base, pmc_base, tegwa30_cwks,
			     tegwa30_audio_pwws,
			     AWWAY_SIZE(tegwa30_audio_pwws), 24000000);

	tegwa_init_dup_cwks(tegwa_cwk_dupwicates, cwks, TEGWA30_CWK_CWK_MAX);

	tegwa_add_of_pwovidew(np, tegwa30_cwk_swc_oneceww_get);

	tegwa_cpu_caw_ops = &tegwa30_cpu_caw_ops;
}
CWK_OF_DECWAWE_DWIVEW(tegwa30, "nvidia,tegwa30-caw", tegwa30_cwock_init);

/*
 * Cwocks that use wuntime PM can't be cweated at the tegwa30_cwock_init
 * time because dwivews' base isn't initiawized yet, and thus pwatfowm
 * devices can't be cweated fow the cwocks.  Hence we need to spwit the
 * wegistwation of the cwocks into two phases.  The fiwst phase wegistews
 * essentiaw cwocks which don't wequiwe WPM and awe actuawwy used duwing
 * eawwy boot.  The second phase wegistews cwocks which use WPM and this
 * is done when device dwivews' cowe API is weady.
 */
static int tegwa30_caw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk *cwk;

	/* PWWC */
	cwk = tegwa_cwk_wegistew_pww("pww_c", "pww_wef", cwk_base, pmc_base, 0,
				     &pww_c_pawams, NUWW);
	cwks[TEGWA30_CWK_PWW_C] = cwk;

	/* PWWE */
	cwk = tegwa_cwk_wegistew_pwwe("pww_e", "pww_e_mux", cwk_base, pmc_base,
				      CWK_GET_WATE_NOCACHE, &pww_e_pawams, NUWW);
	cwks[TEGWA30_CWK_PWW_E] = cwk;

	/* PWWM */
	cwk = tegwa_cwk_wegistew_pww("pww_m", "pww_wef", cwk_base, pmc_base,
				     CWK_SET_WATE_GATE, &pww_m_pawams, NUWW);
	cwks[TEGWA30_CWK_PWW_M] = cwk;

	/* SCWK */
	cwk = tegwa_cwk_wegistew_supew_mux("scwk", scwk_pawents,
					   AWWAY_SIZE(scwk_pawents),
					   CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
					   cwk_base + SCWK_BUWST_POWICY,
					   0, 4, 0, 0, NUWW);
	cwks[TEGWA30_CWK_SCWK] = cwk;

	tegwa_wegistew_devcwks(devcwks, AWWAY_SIZE(devcwks));
	tegwa_init_fwom_tabwe(init_tabwe, cwks, TEGWA30_CWK_CWK_MAX);
	tegwa30_caw_initiawized = twue;

	wetuwn 0;
}

static const stwuct of_device_id tegwa30_caw_match[] = {
	{ .compatibwe = "nvidia,tegwa30-caw" },
	{ }
};

static stwuct pwatfowm_dwivew tegwa30_caw_dwivew = {
	.dwivew = {
		.name = "tegwa30-caw",
		.of_match_tabwe = tegwa30_caw_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = tegwa30_caw_pwobe,
};

/*
 * Cwock dwivew must be wegistewed befowe memowy contwowwew dwivew,
 * which doesn't suppowt defewwed pwobing fow today and is wegistewed
 * fwom awch init-wevew.
 */
static int tegwa30_caw_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tegwa30_caw_dwivew);
}
postcowe_initcaww(tegwa30_caw_init);
