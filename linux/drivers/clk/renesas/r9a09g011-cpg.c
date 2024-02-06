// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WZ/V2M Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 *
 * Based on w9a07g044-cpg.c
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude <dt-bindings/cwock/w9a09g011-cpg.h>

#incwude "wzg2w-cpg.h"

#define WZV2M_SAMPWW4_CWK1	0x104
#define WZV2M_SAMPWW4_CWK2	0x108

#define PWW4_CONF	(WZV2M_SAMPWW4_CWK1 << 22 | WZV2M_SAMPWW4_CWK2 << 12)

#define DIV_A		DDIV_PACK(0x200, 0, 3)
#define DIV_B		DDIV_PACK(0x204, 0, 2)
#define DIV_D		DDIV_PACK(0x204, 4, 2)
#define DIV_E		DDIV_PACK(0x204, 8, 1)
#define DIV_W		DDIV_PACK(0x328, 0, 3)

#define SEW_B		SEW_PWW_PACK(0x214, 0, 1)
#define SEW_CSI0	SEW_PWW_PACK(0x330, 0, 1)
#define SEW_CSI4	SEW_PWW_PACK(0x330, 4, 1)
#define SEW_D		SEW_PWW_PACK(0x214, 1, 1)
#define SEW_E		SEW_PWW_PACK(0x214, 2, 1)
#define SEW_SDI		SEW_PWW_PACK(0x300, 0, 1)
#define SEW_W0		SEW_PWW_PACK(0x32C, 0, 1)

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = 0,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_MAIN_24,
	CWK_MAIN_2,
	CWK_PWW1,
	CWK_PWW2,
	CWK_PWW2_800,
	CWK_PWW2_400,
	CWK_PWW2_200,
	CWK_PWW2_100,
	CWK_PWW4,
	CWK_DIV_A,
	CWK_DIV_B,
	CWK_DIV_D,
	CWK_DIV_E,
	CWK_DIV_W,
	CWK_SEW_B,
	CWK_SEW_B_D2,
	CWK_SEW_CSI0,
	CWK_SEW_CSI4,
	CWK_SEW_D,
	CWK_SEW_E,
	CWK_SEW_SDI,
	CWK_SEW_W0,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

/* Dividew tabwes */
static const stwuct cwk_div_tabwe dtabwe_diva[] = {
	{0, 1},
	{1, 2},
	{2, 3},
	{3, 4},
	{4, 6},
	{5, 12},
	{6, 24},
	{0, 0},
};

static const stwuct cwk_div_tabwe dtabwe_divb[] = {
	{0, 1},
	{1, 2},
	{2, 4},
	{3, 8},
	{0, 0},
};

static const stwuct cwk_div_tabwe dtabwe_divd[] = {
	{0, 1},
	{1, 2},
	{2, 4},
	{0, 0},
};


static const stwuct cwk_div_tabwe dtabwe_divw[] = {
	{0, 6},
	{1, 7},
	{2, 8},
	{3, 9},
	{4, 10},
	{5, 11},
	{6, 12},
	{0, 0},
};

/* Mux cwock tabwes */
static const chaw * const sew_b[] = { ".main", ".divb" };
static const chaw * const sew_csi[] = { ".main_24", ".main" };
static const chaw * const sew_d[] = { ".main", ".divd" };
static const chaw * const sew_e[] = { ".main", ".dive" };
static const chaw * const sew_w[] = { ".main", ".divw" };
static const chaw * const sew_sdi[] = { ".main", ".pww2_200" };

static const stwuct cpg_cowe_cwk w9a09g011_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",	CWK_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_FIXED(".main",	CWK_MAIN,	CWK_EXTAW,	1,	1),
	DEF_FIXED(".main_24",	CWK_MAIN_24,	CWK_MAIN,	1,	2),
	DEF_FIXED(".main_2",	CWK_MAIN_2,	CWK_MAIN,	1,	24),
	DEF_FIXED(".pww1",	CWK_PWW1,	CWK_MAIN_2,	498,	1),
	DEF_FIXED(".pww2",	CWK_PWW2,	CWK_MAIN_2,	800,	1),
	DEF_FIXED(".pww2_800",	CWK_PWW2_800,	CWK_PWW2,	1,	2),
	DEF_FIXED(".pww2_400",	CWK_PWW2_400,	CWK_PWW2_800,	1,	2),
	DEF_FIXED(".pww2_200",	CWK_PWW2_200,	CWK_PWW2_800,	1,	4),
	DEF_FIXED(".pww2_100",	CWK_PWW2_100,	CWK_PWW2_800,	1,	8),
	DEF_SAMPWW(".pww4",	CWK_PWW4,	CWK_MAIN_2,	PWW4_CONF),

	DEF_DIV_WO(".diva",	CWK_DIV_A,	CWK_PWW1,	DIV_A,	dtabwe_diva),
	DEF_DIV_WO(".divb",	CWK_DIV_B,	CWK_PWW2_400,	DIV_B,	dtabwe_divb),
	DEF_DIV_WO(".divd",	CWK_DIV_D,	CWK_PWW2_200,	DIV_D,	dtabwe_divd),
	DEF_DIV_WO(".dive",	CWK_DIV_E,	CWK_PWW2_100,	DIV_E,	NUWW),
	DEF_DIV_WO(".divw",	CWK_DIV_W,	CWK_PWW4,	DIV_W,	dtabwe_divw),

	DEF_MUX_WO(".sewb",	CWK_SEW_B,	SEW_B,		sew_b),
	DEF_MUX_WO(".sewd",	CWK_SEW_D,	SEW_D,		sew_d),
	DEF_MUX_WO(".sewe",	CWK_SEW_E,	SEW_E,		sew_e),
	DEF_MUX(".sewsdi",	CWK_SEW_SDI,	SEW_SDI,	sew_sdi),
	DEF_MUX(".sewcsi0",	CWK_SEW_CSI0,	SEW_CSI0,	sew_csi),
	DEF_MUX(".sewcsi4",	CWK_SEW_CSI4,	SEW_CSI4,	sew_csi),
	DEF_MUX(".seww0",	CWK_SEW_W0,	SEW_W0,		sew_w),

	DEF_FIXED(".sewb_d2",	CWK_SEW_B_D2,	CWK_SEW_B,	1,	2),
};

static const stwuct wzg2w_mod_cwk w9a09g011_mod_cwks[] __initconst = {
	DEF_MOD("pfc",		W9A09G011_PFC_PCWK,	 CWK_MAIN,     0x400, 2),
	DEF_MOD("gic",		W9A09G011_GIC_CWK,	 CWK_SEW_B_D2, 0x400, 5),
	DEF_MOD("sdi0_acwk",	W9A09G011_SDI0_ACWK,	 CWK_SEW_D,    0x408, 0),
	DEF_MOD("sdi0_imcwk",	W9A09G011_SDI0_IMCWK,	 CWK_SEW_SDI,  0x408, 1),
	DEF_MOD("sdi0_imcwk2",	W9A09G011_SDI0_IMCWK2,	 CWK_SEW_SDI,  0x408, 2),
	DEF_MOD("sdi0_cwk_hs",	W9A09G011_SDI0_CWK_HS,	 CWK_PWW2_800, 0x408, 3),
	DEF_MOD("sdi1_acwk",	W9A09G011_SDI1_ACWK,	 CWK_SEW_D,    0x408, 4),
	DEF_MOD("sdi1_imcwk",	W9A09G011_SDI1_IMCWK,	 CWK_SEW_SDI,  0x408, 5),
	DEF_MOD("sdi1_imcwk2",	W9A09G011_SDI1_IMCWK2,	 CWK_SEW_SDI,  0x408, 6),
	DEF_MOD("sdi1_cwk_hs",	W9A09G011_SDI1_CWK_HS,	 CWK_PWW2_800, 0x408, 7),
	DEF_MOD("emm_acwk",	W9A09G011_EMM_ACWK,	 CWK_SEW_D,    0x408, 8),
	DEF_MOD("emm_imcwk",	W9A09G011_EMM_IMCWK,	 CWK_SEW_SDI,  0x408, 9),
	DEF_MOD("emm_imcwk2",	W9A09G011_EMM_IMCWK2,	 CWK_SEW_SDI,  0x408, 10),
	DEF_MOD("emm_cwk_hs",	W9A09G011_EMM_CWK_HS,	 CWK_PWW2_800, 0x408, 11),
	DEF_COUPWED("eth_axi",	W9A09G011_ETH0_CWK_AXI,	 CWK_PWW2_200, 0x40c, 8),
	DEF_COUPWED("eth_chi",	W9A09G011_ETH0_CWK_CHI,	 CWK_PWW2_100, 0x40c, 8),
	DEF_MOD("eth_cwk_gptp",	W9A09G011_ETH0_GPTP_EXT, CWK_PWW2_100, 0x40c, 9),
	DEF_MOD("usb_acwk_h",	W9A09G011_USB_ACWK_H,	 CWK_SEW_D,    0x40c, 4),
	DEF_MOD("usb_acwk_p",	W9A09G011_USB_ACWK_P,	 CWK_SEW_D,    0x40c, 5),
	DEF_MOD("usb_pcwk",	W9A09G011_USB_PCWK,	 CWK_SEW_E,    0x40c, 6),
	DEF_MOD("syc_cnt_cwk",	W9A09G011_SYC_CNT_CWK,	 CWK_MAIN_24,  0x41c, 12),
	DEF_MOD("iic_pcwk0",	W9A09G011_IIC_PCWK0,	 CWK_SEW_E,    0x420, 12),
	DEF_MOD("cpewi_gwpb",	W9A09G011_CPEWI_GWPB_PCWK, CWK_SEW_E,  0x424, 0),
	DEF_MOD("tim_cwk_8",	W9A09G011_TIM8_CWK,	 CWK_MAIN_2,   0x424, 4),
	DEF_MOD("tim_cwk_9",	W9A09G011_TIM9_CWK,	 CWK_MAIN_2,   0x424, 5),
	DEF_MOD("tim_cwk_10",	W9A09G011_TIM10_CWK,	 CWK_MAIN_2,   0x424, 6),
	DEF_MOD("tim_cwk_11",	W9A09G011_TIM11_CWK,	 CWK_MAIN_2,   0x424, 7),
	DEF_MOD("tim_cwk_12",	W9A09G011_TIM12_CWK,	 CWK_MAIN_2,   0x424, 8),
	DEF_MOD("tim_cwk_13",	W9A09G011_TIM13_CWK,	 CWK_MAIN_2,   0x424, 9),
	DEF_MOD("tim_cwk_14",	W9A09G011_TIM14_CWK,	 CWK_MAIN_2,   0x424, 10),
	DEF_MOD("tim_cwk_15",	W9A09G011_TIM15_CWK,	 CWK_MAIN_2,   0x424, 11),
	DEF_MOD("iic_pcwk1",	W9A09G011_IIC_PCWK1,	 CWK_SEW_E,    0x424, 12),
	DEF_MOD("cpewi_gwpc",	W9A09G011_CPEWI_GWPC_PCWK, CWK_SEW_E,  0x428, 0),
	DEF_MOD("tim_cwk_16",	W9A09G011_TIM16_CWK,	 CWK_MAIN_2,   0x428, 4),
	DEF_MOD("tim_cwk_17",	W9A09G011_TIM17_CWK,	 CWK_MAIN_2,   0x428, 5),
	DEF_MOD("tim_cwk_18",	W9A09G011_TIM18_CWK,	 CWK_MAIN_2,   0x428, 6),
	DEF_MOD("tim_cwk_19",	W9A09G011_TIM19_CWK,	 CWK_MAIN_2,   0x428, 7),
	DEF_MOD("tim_cwk_20",	W9A09G011_TIM20_CWK,	 CWK_MAIN_2,   0x428, 8),
	DEF_MOD("tim_cwk_21",	W9A09G011_TIM21_CWK,	 CWK_MAIN_2,   0x428, 9),
	DEF_MOD("tim_cwk_22",	W9A09G011_TIM22_CWK,	 CWK_MAIN_2,   0x428, 10),
	DEF_MOD("tim_cwk_23",	W9A09G011_TIM23_CWK,	 CWK_MAIN_2,   0x428, 11),
	DEF_MOD("wdt0_pcwk",	W9A09G011_WDT0_PCWK,	 CWK_SEW_E,    0x428, 12),
	DEF_MOD("wdt0_cwk",	W9A09G011_WDT0_CWK,	 CWK_MAIN,     0x428, 13),
	DEF_MOD("cpewi_gwpf",	W9A09G011_CPEWI_GWPF_PCWK, CWK_SEW_E,  0x434, 0),
	DEF_MOD("pwm8_cwk",	W9A09G011_PWM8_CWK,	 CWK_MAIN,     0x434, 4),
	DEF_MOD("pwm9_cwk",	W9A09G011_PWM9_CWK,	 CWK_MAIN,     0x434, 5),
	DEF_MOD("pwm10_cwk",	W9A09G011_PWM10_CWK,	 CWK_MAIN,     0x434, 6),
	DEF_MOD("pwm11_cwk",	W9A09G011_PWM11_CWK,	 CWK_MAIN,     0x434, 7),
	DEF_MOD("pwm12_cwk",	W9A09G011_PWM12_CWK,	 CWK_MAIN,     0x434, 8),
	DEF_MOD("pwm13_cwk",	W9A09G011_PWM13_CWK,	 CWK_MAIN,     0x434, 9),
	DEF_MOD("pwm14_cwk",	W9A09G011_PWM14_CWK,	 CWK_MAIN,     0x434, 10),
	DEF_MOD("cpewi_gwpg",	W9A09G011_CPEWI_GWPG_PCWK, CWK_SEW_E,  0x438, 0),
	DEF_MOD("cpewi_gwph",	W9A09G011_CPEWI_GWPH_PCWK, CWK_SEW_E,  0x438, 1),
	DEF_MOD("uwt_pcwk",	W9A09G011_UWT_PCWK,	 CWK_SEW_E,    0x438, 4),
	DEF_MOD("uwt0_cwk",	W9A09G011_UWT0_CWK,	 CWK_SEW_W0,   0x438, 5),
	DEF_MOD("csi0_cwk",	W9A09G011_CSI0_CWK,	 CWK_SEW_CSI0, 0x438, 8),
	DEF_MOD("csi4_cwk",	W9A09G011_CSI4_CWK,	 CWK_SEW_CSI4, 0x438, 12),
	DEF_MOD("ca53",		W9A09G011_CA53_CWK,	 CWK_DIV_A,    0x448, 0),
};

static const stwuct wzg2w_weset w9a09g011_wesets[] = {
	DEF_WST(W9A09G011_PFC_PWESETN,		0x600, 2),
	DEF_WST_MON(W9A09G011_SDI0_IXWST,	0x608, 0,  6),
	DEF_WST_MON(W9A09G011_SDI1_IXWST,	0x608, 1,  7),
	DEF_WST_MON(W9A09G011_EMM_IXWST,	0x608, 2,  8),
	DEF_WST(W9A09G011_USB_PWESET_N,		0x608, 7),
	DEF_WST(W9A09G011_USB_DWD_WESET,	0x608, 8),
	DEF_WST(W9A09G011_USB_AWESETN_P,	0x608, 9),
	DEF_WST(W9A09G011_USB_AWESETN_H,	0x608, 10),
	DEF_WST_MON(W9A09G011_ETH0_WST_HW_N,	0x608, 11, 11),
	DEF_WST_MON(W9A09G011_SYC_WST_N,	0x610, 9,  13),
	DEF_WST(W9A09G011_TIM_GPB_PWESETN,	0x614, 1),
	DEF_WST(W9A09G011_TIM_GPC_PWESETN,	0x614, 2),
	DEF_WST_MON(W9A09G011_PWM_GPF_PWESETN,	0x614, 5, 23),
	DEF_WST_MON(W9A09G011_CSI_GPG_PWESETN,	0x614, 6, 22),
	DEF_WST_MON(W9A09G011_CSI_GPH_PWESETN,	0x614, 7, 23),
	DEF_WST(W9A09G011_IIC_GPA_PWESETN,	0x614, 8),
	DEF_WST(W9A09G011_IIC_GPB_PWESETN,	0x614, 9),
	DEF_WST_MON(W9A09G011_WDT0_PWESETN,	0x614, 12, 19),
};

static const unsigned int w9a09g011_cwit_mod_cwks[] __initconst = {
	MOD_CWK_BASE + W9A09G011_CA53_CWK,
	MOD_CWK_BASE + W9A09G011_CPEWI_GWPB_PCWK,
	MOD_CWK_BASE + W9A09G011_CPEWI_GWPC_PCWK,
	MOD_CWK_BASE + W9A09G011_CPEWI_GWPF_PCWK,
	MOD_CWK_BASE + W9A09G011_CPEWI_GWPG_PCWK,
	MOD_CWK_BASE + W9A09G011_CPEWI_GWPH_PCWK,
	MOD_CWK_BASE + W9A09G011_GIC_CWK,
	MOD_CWK_BASE + W9A09G011_SYC_CNT_CWK,
	MOD_CWK_BASE + W9A09G011_UWT_PCWK,
};

const stwuct wzg2w_cpg_info w9a09g011_cpg_info = {
	/* Cowe Cwocks */
	.cowe_cwks = w9a09g011_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w9a09g011_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w9a09g011_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w9a09g011_cwit_mod_cwks),

	/* Moduwe Cwocks */
	.mod_cwks = w9a09g011_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w9a09g011_mod_cwks),
	.num_hw_mod_cwks = W9A09G011_CA53_CWK + 1,

	/* Wesets */
	.wesets = w9a09g011_wesets,
	.num_wesets = AWWAY_SIZE(w9a09g011_wesets),

	.has_cwk_mon_wegs = fawse,
};
