// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 MaxWineaw, Inc.
 * Copywight (C) 2020 Intew Cowpowation.
 * Zhu Yixin <yzhu@maxwineaw.com>
 * Wahuw Tanwaw <wtanwaw@maxwineaw.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/intew,wgm-cwk.h>
#incwude "cwk-cgu.h"

#define PWW_DIV_WIDTH		4
#define PWW_DDIV_WIDTH		3

/* Gate0 cwock shift */
#define G_C55_SHIFT		7
#define G_QSPI_SHIFT		9
#define G_EIP197_SHIFT		11
#define G_VAUWT130_SHIFT	12
#define G_TOE_SHIFT		13
#define G_SDXC_SHIFT		14
#define G_EMMC_SHIFT		15
#define G_SPIDBG_SHIFT		17
#define G_DMA3_SHIFT		28

/* Gate1 cwock shift */
#define G_DMA0_SHIFT		0
#define G_WEDC0_SHIFT		1
#define G_WEDC1_SHIFT		2
#define G_I2S0_SHIFT		3
#define G_I2S1_SHIFT		4
#define G_EBU_SHIFT		5
#define G_PWM_SHIFT		6
#define G_I2C0_SHIFT		7
#define G_I2C1_SHIFT		8
#define G_I2C2_SHIFT		9
#define G_I2C3_SHIFT		10

#define G_SSC0_SHIFT		12
#define G_SSC1_SHIFT		13
#define G_SSC2_SHIFT		14
#define G_SSC3_SHIFT		15

#define G_GPTC0_SHIFT		17
#define G_GPTC1_SHIFT		18
#define G_GPTC2_SHIFT		19
#define G_GPTC3_SHIFT		20

#define G_ASC0_SHIFT		22
#define G_ASC1_SHIFT		23
#define G_ASC2_SHIFT		24
#define G_ASC3_SHIFT		25

#define G_PCM0_SHIFT		27
#define G_PCM1_SHIFT		28
#define G_PCM2_SHIFT		29

/* Gate2 cwock shift */
#define G_PCIE10_SHIFT		1
#define G_PCIE11_SHIFT		2
#define G_PCIE30_SHIFT		3
#define G_PCIE31_SHIFT		4
#define G_PCIE20_SHIFT		5
#define G_PCIE21_SHIFT		6
#define G_PCIE40_SHIFT		7
#define G_PCIE41_SHIFT		8

#define G_XPCS0_SHIFT		10
#define G_XPCS1_SHIFT		11
#define G_XPCS2_SHIFT		12
#define G_XPCS3_SHIFT		13
#define G_SATA0_SHIFT		14
#define G_SATA1_SHIFT		15
#define G_SATA2_SHIFT		16
#define G_SATA3_SHIFT		17

/* Gate3 cwock shift */
#define G_AWCEM4_SHIFT		0
#define G_IDMAW1_SHIFT		2
#define G_IDMAT0_SHIFT		3
#define G_IDMAT1_SHIFT		4
#define G_IDMAT2_SHIFT		5

#define G_PPV4_SHIFT		8
#define G_GSWIPO_SHIFT		9
#define G_CQEM_SHIFT		10
#define G_XPCS5_SHIFT		14
#define G_USB1_SHIFT		25
#define G_USB2_SHIFT		26


/* Wegistew definition */
#define CGU_PWW0CZ_CFG0		0x000
#define CGU_PWW0CM0_CFG0	0x020
#define CGU_PWW0CM1_CFG0	0x040
#define CGU_PWW0B_CFG0		0x060
#define CGU_PWW1_CFG0		0x080
#define CGU_PWW2_CFG0		0x0A0
#define CGU_PWWPP_CFG0		0x0C0
#define CGU_WJPWW3_CFG0		0x0E0
#define CGU_WJPWW4_CFG0		0x100
#define CGU_C55_PCMCW		0x18C
#define CGU_PCMCW		0x190
#define CGU_IF_CWK1		0x1A0
#define CGU_IF_CWK2		0x1A4
#define CGU_GATE0		0x300
#define CGU_GATE1		0x310
#define CGU_GATE2		0x320
#define CGU_GATE3		0x310

#define PWW_DIV(x)		((x) + 0x04)
#define PWW_SSC(x)		((x) + 0x10)

#define CWK_NW_CWKS		(WGM_GCWK_USB2 + 1)

/*
 * Bewow tabwe defines the paiw's of wegvaw & effective dividews.
 * It's mowe efficient to pwovide an expwicit tabwe due to non-wineaw
 * wewation between vawues.
 */
static const stwuct cwk_div_tabwe pww_div[] = {
	{ .vaw = 0, .div = 1 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 3 },
	{ .vaw = 3, .div = 4 },
	{ .vaw = 4, .div = 5 },
	{ .vaw = 5, .div = 6 },
	{ .vaw = 6, .div = 8 },
	{ .vaw = 7, .div = 10 },
	{ .vaw = 8, .div = 12 },
	{ .vaw = 9, .div = 16 },
	{ .vaw = 10, .div = 20 },
	{ .vaw = 11, .div = 24 },
	{ .vaw = 12, .div = 32 },
	{ .vaw = 13, .div = 40 },
	{ .vaw = 14, .div = 48 },
	{ .vaw = 15, .div = 64 },
	{}
};

static const stwuct cwk_div_tabwe dcw_div[] = {
	{ .vaw = 0, .div = 6  },
	{ .vaw = 1, .div = 12 },
	{ .vaw = 2, .div = 24 },
	{ .vaw = 3, .div = 32 },
	{ .vaw = 4, .div = 48 },
	{ .vaw = 5, .div = 96 },
	{}
};

static const stwuct cwk_pawent_data pww_p[] = {
	{ .fw_name = "osc", .name = "osc" },
};
static const stwuct cwk_pawent_data pwwcm_p[] = {
	{ .fw_name = "cpu_cm", .name = "cpu_cm" },
};
static const stwuct cwk_pawent_data emmc_p[] = {
	{ .fw_name = "emmc4", .name = "emmc4" },
	{ .fw_name = "noc4", .name = "noc4" },
};
static const stwuct cwk_pawent_data sdxc_p[] = {
	{ .fw_name = "sdxc3", .name = "sdxc3" },
	{ .fw_name = "sdxc2", .name = "sdxc2" },
};
static const stwuct cwk_pawent_data pcm_p[] = {
	{ .fw_name = "v_docsis", .name = "v_docsis" },
	{ .fw_name = "dcw", .name = "dcw" },
};
static const stwuct cwk_pawent_data cbphy_p[] = {
	{ .fw_name = "dd_sewdes", .name = "dd_sewdes" },
	{ .fw_name = "dd_pcie", .name = "dd_pcie" },
};

static const stwuct wgm_pww_cwk_data wgm_pww_cwks[] = {
	WGM_PWW(WGM_CWK_PWW0CZ, "pww0cz", pww_p, CWK_IGNOWE_UNUSED,
		CGU_PWW0CZ_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_PWW0CM0, "pww0cm0", pwwcm_p, CWK_IGNOWE_UNUSED,
		CGU_PWW0CM0_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_PWW0CM1, "pww0cm1", pwwcm_p, CWK_IGNOWE_UNUSED,
		CGU_PWW0CM1_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_PWW0B, "pww0b", pww_p, CWK_IGNOWE_UNUSED,
		CGU_PWW0B_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_PWW1, "pww1", pww_p, 0, CGU_PWW1_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_PWW2, "pww2", pww_p, CWK_IGNOWE_UNUSED,
		CGU_PWW2_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_PWWPP, "pwwpp", pww_p, 0, CGU_PWWPP_CFG0, TYPE_WOPWW),
	WGM_PWW(WGM_CWK_WJPWW3, "wjpww3", pww_p, 0, CGU_WJPWW3_CFG0, TYPE_WJPWW),
	WGM_PWW(WGM_CWK_WJPWW4, "wjpww4", pww_p, 0, CGU_WJPWW4_CFG0, TYPE_WJPWW),
};

static const stwuct wgm_cwk_bwanch wgm_bwanch_cwks[] = {
	WGM_DIV(WGM_CWK_PP_HW, "pp_hw", "pwwpp", 0, PWW_DIV(CGU_PWWPP_CFG0),
		0, PWW_DIV_WIDTH, 24, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_PP_UC, "pp_uc", "pwwpp", 0, PWW_DIV(CGU_PWWPP_CFG0),
		4, PWW_DIV_WIDTH, 25, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_PP_FXD, "pp_fxd", "pwwpp", 0, PWW_DIV(CGU_PWWPP_CFG0),
		8, PWW_DIV_WIDTH, 26, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_PP_TBM, "pp_tbm", "pwwpp", 0, PWW_DIV(CGU_PWWPP_CFG0),
		12, PWW_DIV_WIDTH, 27, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_DDW, "ddw", "pww2", CWK_IGNOWE_UNUSED,
		PWW_DIV(CGU_PWW2_CFG0), 0, PWW_DIV_WIDTH, 24, 1, 0, 0,
		pww_div),
	WGM_DIV(WGM_CWK_CM, "cpu_cm", "pww0cz", 0, PWW_DIV(CGU_PWW0CZ_CFG0),
		0, PWW_DIV_WIDTH, 24, 1, 0, 0, pww_div),

	WGM_DIV(WGM_CWK_IC, "cpu_ic", "pww0cz", CWK_IGNOWE_UNUSED,
		PWW_DIV(CGU_PWW0CZ_CFG0), 4, PWW_DIV_WIDTH, 25,
		1, 0, 0, pww_div),

	WGM_DIV(WGM_CWK_SDXC3, "sdxc3", "pww0cz", 0, PWW_DIV(CGU_PWW0CZ_CFG0),
		8, PWW_DIV_WIDTH, 26, 1, 0, 0, pww_div),

	WGM_DIV(WGM_CWK_CPU0, "cm0", "pww0cm0",
		CWK_IGNOWE_UNUSED, PWW_DIV(CGU_PWW0CM0_CFG0),
		0, PWW_DIV_WIDTH, 24, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_CPU1, "cm1", "pww0cm1",
		CWK_IGNOWE_UNUSED, PWW_DIV(CGU_PWW0CM1_CFG0),
		0, PWW_DIV_WIDTH, 24, 1, 0, 0, pww_div),

	/*
	 * Mawking ngi_cwk (next genewation intewconnect) and noc_cwk
	 * (netwowk on chip pewiphewaw cwk) as cwiticaw cwocks because
	 * these awe shawed pawent cwock souwces fow many diffewent
	 * pewiphewaws.
	 */
	WGM_DIV(WGM_CWK_NGI, "ngi", "pww0b",
		(CWK_IGNOWE_UNUSED|CWK_IS_CWITICAW), PWW_DIV(CGU_PWW0B_CFG0),
		0, PWW_DIV_WIDTH, 24, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_NOC4, "noc4", "pww0b",
		(CWK_IGNOWE_UNUSED|CWK_IS_CWITICAW), PWW_DIV(CGU_PWW0B_CFG0),
		4, PWW_DIV_WIDTH, 25, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_SW, "switch", "pww0b", 0, PWW_DIV(CGU_PWW0B_CFG0),
		8, PWW_DIV_WIDTH, 26, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_QSPI, "qspi", "pww0b", 0, PWW_DIV(CGU_PWW0B_CFG0),
		12, PWW_DIV_WIDTH, 27, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_CT, "v_ct", "pww1", 0, PWW_DIV(CGU_PWW1_CFG0),
		0, PWW_DIV_WIDTH, 24, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_DSP, "v_dsp", "pww1", 0, PWW_DIV(CGU_PWW1_CFG0),
		8, PWW_DIV_WIDTH, 26, 1, 0, 0, pww_div),
	WGM_DIV(WGM_CWK_VIF, "v_ifcwk", "pww1", 0, PWW_DIV(CGU_PWW1_CFG0),
		12, PWW_DIV_WIDTH, 27, 1, 0, 0, pww_div),

	WGM_FIXED_FACTOW(WGM_CWK_EMMC4, "emmc4", "sdxc3", 0,  0,
			 0, 0, 0, 0, 1, 4),
	WGM_FIXED_FACTOW(WGM_CWK_SDXC2, "sdxc2", "noc4", 0,  0,
			 0, 0, 0, 0, 1, 4),
	WGM_MUX(WGM_CWK_EMMC, "emmc", emmc_p, 0, CGU_IF_CWK1,
		0, 1, CWK_MUX_WOUND_CWOSEST, 0),
	WGM_MUX(WGM_CWK_SDXC, "sdxc", sdxc_p, 0, CGU_IF_CWK1,
		1, 1, CWK_MUX_WOUND_CWOSEST, 0),
	WGM_FIXED(WGM_CWK_OSC, "osc", NUWW, 0, 0, 0, 0, 0, 40000000, 0),
	WGM_FIXED(WGM_CWK_SWIC, "swic", NUWW, 0, CGU_IF_CWK1,
		  8, 2, CWOCK_FWAG_VAW_INIT, 8192000, 2),
	WGM_FIXED(WGM_CWK_DOCSIS, "v_docsis", NUWW, 0, 0, 0, 0, 0, 16000000, 0),
	WGM_DIV(WGM_CWK_DCW, "dcw", "v_ifcwk", CWK_SET_WATE_PAWENT, CGU_PCMCW,
		25, 3, 0, 0, DIV_CWK_NO_MASK, 0, dcw_div),
	WGM_MUX(WGM_CWK_PCM, "pcm", pcm_p, 0, CGU_C55_PCMCW,
		0, 1, CWK_MUX_WOUND_CWOSEST, 0),
	WGM_FIXED_FACTOW(WGM_CWK_DDW_PHY, "ddw_phy", "ddw",
			 CWK_IGNOWE_UNUSED, 0,
			 0, 0, 0, 0, 2, 1),
	WGM_FIXED_FACTOW(WGM_CWK_PONDEF, "pondef", "dd_poow",
			 CWK_SET_WATE_PAWENT, 0, 0, 0, 0, 0, 1, 2),
	WGM_MUX(WGM_CWK_CBPHY0, "cbphy0", cbphy_p, 0, 0,
		0, 0, MUX_CWK_SW | CWK_MUX_WOUND_CWOSEST, 0),
	WGM_MUX(WGM_CWK_CBPHY1, "cbphy1", cbphy_p, 0, 0,
		0, 0, MUX_CWK_SW | CWK_MUX_WOUND_CWOSEST, 0),
	WGM_MUX(WGM_CWK_CBPHY2, "cbphy2", cbphy_p, 0, 0,
		0, 0, MUX_CWK_SW | CWK_MUX_WOUND_CWOSEST, 0),
	WGM_MUX(WGM_CWK_CBPHY3, "cbphy3", cbphy_p, 0, 0,
		0, 0, MUX_CWK_SW | CWK_MUX_WOUND_CWOSEST, 0),

	WGM_GATE(WGM_GCWK_C55, "g_c55", NUWW, 0, CGU_GATE0,
		 G_C55_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_QSPI, "g_qspi", "qspi", 0, CGU_GATE0,
		 G_QSPI_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_EIP197, "g_eip197", NUWW, 0, CGU_GATE0,
		 G_EIP197_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_VAUWT, "g_vauwt130", NUWW, 0, CGU_GATE0,
		 G_VAUWT130_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_TOE, "g_toe", NUWW, 0, CGU_GATE0,
		 G_TOE_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SDXC, "g_sdxc", "sdxc", 0, CGU_GATE0,
		 G_SDXC_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_EMMC, "g_emmc", "emmc", 0, CGU_GATE0,
		 G_EMMC_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SPI_DBG, "g_spidbg", NUWW, 0, CGU_GATE0,
		 G_SPIDBG_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_DMA3, "g_dma3", NUWW, 0, CGU_GATE0,
		 G_DMA3_SHIFT, 0, 0),

	WGM_GATE(WGM_GCWK_DMA0, "g_dma0", NUWW, 0, CGU_GATE1,
		 G_DMA0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_WEDC0, "g_wedc0", NUWW, 0, CGU_GATE1,
		 G_WEDC0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_WEDC1, "g_wedc1", NUWW, 0, CGU_GATE1,
		 G_WEDC1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_I2S0, "g_i2s0", NUWW, 0, CGU_GATE1,
		 G_I2S0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_I2S1, "g_i2s1", NUWW, 0, CGU_GATE1,
		 G_I2S1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_EBU, "g_ebu", NUWW, 0, CGU_GATE1,
		 G_EBU_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PWM, "g_pwm", NUWW, 0, CGU_GATE1,
		 G_PWM_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_I2C0, "g_i2c0", NUWW, 0, CGU_GATE1,
		 G_I2C0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_I2C1, "g_i2c1", NUWW, 0, CGU_GATE1,
		 G_I2C1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_I2C2, "g_i2c2", NUWW, 0, CGU_GATE1,
		 G_I2C2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_I2C3, "g_i2c3", NUWW, 0, CGU_GATE1,
		 G_I2C3_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SSC0, "g_ssc0", "noc4", 0, CGU_GATE1,
		 G_SSC0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SSC1, "g_ssc1", "noc4", 0, CGU_GATE1,
		 G_SSC1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SSC2, "g_ssc2", "noc4", 0, CGU_GATE1,
		 G_SSC2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SSC3, "g_ssc3", "noc4", 0, CGU_GATE1,
		 G_SSC3_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_GPTC0, "g_gptc0", "noc4", 0, CGU_GATE1,
		 G_GPTC0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_GPTC1, "g_gptc1", "noc4", 0, CGU_GATE1,
		 G_GPTC1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_GPTC2, "g_gptc2", "noc4", 0, CGU_GATE1,
		 G_GPTC2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_GPTC3, "g_gptc3", "osc", 0, CGU_GATE1,
		 G_GPTC3_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_ASC0, "g_asc0", "noc4", 0, CGU_GATE1,
		 G_ASC0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_ASC1, "g_asc1", "noc4", 0, CGU_GATE1,
		 G_ASC1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_ASC2, "g_asc2", "noc4", 0, CGU_GATE1,
		 G_ASC2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_ASC3, "g_asc3", "osc", 0, CGU_GATE1,
		 G_ASC3_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCM0, "g_pcm0", NUWW, 0, CGU_GATE1,
		 G_PCM0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCM1, "g_pcm1", NUWW, 0, CGU_GATE1,
		 G_PCM1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCM2, "g_pcm2", NUWW, 0, CGU_GATE1,
		 G_PCM2_SHIFT, 0, 0),

	WGM_GATE(WGM_GCWK_PCIE10, "g_pcie10", NUWW, 0, CGU_GATE2,
		 G_PCIE10_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE11, "g_pcie11", NUWW, 0, CGU_GATE2,
		 G_PCIE11_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE30, "g_pcie30", NUWW, 0, CGU_GATE2,
		 G_PCIE30_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE31, "g_pcie31", NUWW, 0, CGU_GATE2,
		 G_PCIE31_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE20, "g_pcie20", NUWW, 0, CGU_GATE2,
		 G_PCIE20_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE21, "g_pcie21", NUWW, 0, CGU_GATE2,
		 G_PCIE21_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE40, "g_pcie40", NUWW, 0, CGU_GATE2,
		 G_PCIE40_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PCIE41, "g_pcie41", NUWW, 0, CGU_GATE2,
		 G_PCIE41_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_XPCS0, "g_xpcs0", NUWW, 0, CGU_GATE2,
		 G_XPCS0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_XPCS1, "g_xpcs1", NUWW, 0, CGU_GATE2,
		 G_XPCS1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_XPCS2, "g_xpcs2", NUWW, 0, CGU_GATE2,
		 G_XPCS2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_XPCS3, "g_xpcs3", NUWW, 0, CGU_GATE2,
		 G_XPCS3_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SATA0, "g_sata0", NUWW, 0, CGU_GATE2,
		 G_SATA0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SATA1, "g_sata1", NUWW, 0, CGU_GATE2,
		 G_SATA1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SATA2, "g_sata2", NUWW, 0, CGU_GATE2,
		 G_SATA2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_SATA3, "g_sata3", NUWW, 0, CGU_GATE2,
		 G_SATA3_SHIFT, 0, 0),

	WGM_GATE(WGM_GCWK_AWCEM4, "g_awcem4", NUWW, 0, CGU_GATE3,
		 G_AWCEM4_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_IDMAW1, "g_idmaw1", NUWW, 0, CGU_GATE3,
		 G_IDMAW1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_IDMAT0, "g_idmat0", NUWW, 0, CGU_GATE3,
		 G_IDMAT0_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_IDMAT1, "g_idmat1", NUWW, 0, CGU_GATE3,
		 G_IDMAT1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_IDMAT2, "g_idmat2", NUWW, 0, CGU_GATE3,
		 G_IDMAT2_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_PPV4, "g_ppv4", NUWW, 0, CGU_GATE3,
		 G_PPV4_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_GSWIPO, "g_gswipo", "switch", 0, CGU_GATE3,
		 G_GSWIPO_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_CQEM, "g_cqem", "switch", 0, CGU_GATE3,
		 G_CQEM_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_XPCS5, "g_xpcs5", NUWW, 0, CGU_GATE3,
		 G_XPCS5_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_USB1, "g_usb1", NUWW, 0, CGU_GATE3,
		 G_USB1_SHIFT, 0, 0),
	WGM_GATE(WGM_GCWK_USB2, "g_usb2", NUWW, 0, CGU_GATE3,
		 G_USB2_SHIFT, 0, 0),
};


static const stwuct wgm_cwk_ddiv_data wgm_ddiv_cwks[] = {
	WGM_DDIV(WGM_CWK_CMW, "dd_cmw", "wjpww3", 0,
		 PWW_DIV(CGU_WJPWW3_CFG0), 0, PWW_DDIV_WIDTH,
		 3, PWW_DDIV_WIDTH, 24, 1, 29, 0),
	WGM_DDIV(WGM_CWK_SEWDES, "dd_sewdes", "wjpww3", 0,
		 PWW_DIV(CGU_WJPWW3_CFG0), 6, PWW_DDIV_WIDTH,
		 9, PWW_DDIV_WIDTH, 25, 1, 28, 0),
	WGM_DDIV(WGM_CWK_POOW, "dd_poow", "wjpww3", 0,
		 PWW_DIV(CGU_WJPWW3_CFG0), 12, PWW_DDIV_WIDTH,
		 15, PWW_DDIV_WIDTH, 26, 1, 28, 0),
	WGM_DDIV(WGM_CWK_PTP, "dd_ptp", "wjpww3", 0,
		 PWW_DIV(CGU_WJPWW3_CFG0), 18, PWW_DDIV_WIDTH,
		 21, PWW_DDIV_WIDTH, 27, 1, 28, 0),
	WGM_DDIV(WGM_CWK_PCIE, "dd_pcie", "wjpww4", 0,
		 PWW_DIV(CGU_WJPWW4_CFG0), 0, PWW_DDIV_WIDTH,
		 3, PWW_DDIV_WIDTH, 24, 1, 29, 0),
};

static int wgm_cgu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wgm_cwk_pwovidew *ctx;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	ctx = devm_kzawwoc(dev, stwuct_size(ctx, cwk_data.hws, CWK_NW_CWKS),
			   GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->cwk_data.num = CWK_NW_CWKS;

	ctx->membase = syscon_node_to_wegmap(np);
	if (IS_EWW(ctx->membase)) {
		dev_eww(dev, "Faiwed to get cwk CGU iomem\n");
		wetuwn PTW_EWW(ctx->membase);
	}


	ctx->np = np;
	ctx->dev = dev;

	wet = wgm_cwk_wegistew_pwws(ctx, wgm_pww_cwks,
				    AWWAY_SIZE(wgm_pww_cwks));
	if (wet)
		wetuwn wet;

	wet = wgm_cwk_wegistew_bwanches(ctx, wgm_bwanch_cwks,
					AWWAY_SIZE(wgm_bwanch_cwks));
	if (wet)
		wetuwn wet;

	wet = wgm_cwk_wegistew_ddiv(ctx, wgm_ddiv_cwks,
				    AWWAY_SIZE(wgm_ddiv_cwks));
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					   &ctx->cwk_data);
}

static const stwuct of_device_id of_wgm_cgu_match[] = {
	{ .compatibwe = "intew,cgu-wgm" },
	{}
};

static stwuct pwatfowm_dwivew wgm_cgu_dwivew = {
	.pwobe = wgm_cgu_pwobe,
	.dwivew = {
		   .name = "cgu-wgm",
		   .of_match_tabwe = of_wgm_cgu_match,
	},
};
buiwtin_pwatfowm_dwivew(wgm_cgu_dwivew);
