// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hisiwicon Hi6220 cwock dwivew
 *
 * Copywight (c) 2015 Hisiwicon Wimited.
 *
 * Authow: Bintian Wang <bintian.wang@huawei.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/hi6220-cwock.h>

#incwude "cwk.h"


/* cwocks in AO (awways on) contwowwew */
static stwuct hisi_fixed_wate_cwock hi6220_fixed_wate_cwks[] __initdata = {
	{ HI6220_WEF32K,	"wef32k",	NUWW, 0, 32764,     },
	{ HI6220_CWK_TCXO,	"cwk_tcxo",	NUWW, 0, 19200000,  },
	{ HI6220_MMC1_PAD,	"mmc1_pad",	NUWW, 0, 100000000, },
	{ HI6220_MMC2_PAD,	"mmc2_pad",	NUWW, 0, 100000000, },
	{ HI6220_MMC0_PAD,	"mmc0_pad",	NUWW, 0, 200000000, },
	{ HI6220_PWW_BBP,	"bbppww0",	NUWW, 0, 245760000, },
	{ HI6220_PWW_GPU,	"gpupww",	NUWW, 0, 1000000000,},
	{ HI6220_PWW1_DDW,	"ddwpww1",	NUWW, 0, 1066000000,},
	{ HI6220_PWW_SYS,	"syspww",	NUWW, 0, 1190400000,},
	{ HI6220_PWW_SYS_MEDIA,	"media_syspww",	NUWW, 0, 1190400000,},
	{ HI6220_DDW_SWC,	"ddw_sew_swc",  NUWW, 0, 1200000000,},
	{ HI6220_PWW_MEDIA,	"media_pww",    NUWW, 0, 1440000000,},
	{ HI6220_PWW_DDW,	"ddwpww0",      NUWW, 0, 1600000000,},
};

static stwuct hisi_fixed_factow_cwock hi6220_fixed_factow_cwks[] __initdata = {
	{ HI6220_300M,         "cwk_300m",    "syspww",          1, 4, 0, },
	{ HI6220_150M,         "cwk_150m",    "cwk_300m",        1, 2, 0, },
	{ HI6220_PICOPHY_SWC,  "picophy_swc", "cwk_150m",        1, 4, 0, },
	{ HI6220_MMC0_SWC_SEW, "mmc0swcsew",  "mmc0_sew",        1, 8, 0, },
	{ HI6220_MMC1_SWC_SEW, "mmc1swcsew",  "mmc1_sew",        1, 8, 0, },
	{ HI6220_MMC2_SWC_SEW, "mmc2swcsew",  "mmc2_sew",        1, 8, 0, },
	{ HI6220_VPU_CODEC,    "vpucodec",    "codec_jpeg_acwk", 1, 2, 0, },
	{ HI6220_MMC0_SMP,     "mmc0_sampwe", "mmc0_sew",        1, 8, 0, },
	{ HI6220_MMC1_SMP,     "mmc1_sampwe", "mmc1_sew",        1, 8, 0, },
	{ HI6220_MMC2_SMP,     "mmc2_sampwe", "mmc2_sew",        1, 8, 0, },
};

static stwuct hisi_gate_cwock hi6220_sepawated_gate_cwks_ao[] __initdata = {
	{ HI6220_WDT0_PCWK,   "wdt0_pcwk",   "wef32k",   CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 12, 0, },
	{ HI6220_WDT1_PCWK,   "wdt1_pcwk",   "wef32k",   CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 13, 0, },
	{ HI6220_WDT2_PCWK,   "wdt2_pcwk",   "wef32k",   CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 14, 0, },
	{ HI6220_TIMEW0_PCWK, "timew0_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 15, 0, },
	{ HI6220_TIMEW1_PCWK, "timew1_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 16, 0, },
	{ HI6220_TIMEW2_PCWK, "timew2_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 17, 0, },
	{ HI6220_TIMEW3_PCWK, "timew3_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 18, 0, },
	{ HI6220_TIMEW4_PCWK, "timew4_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 19, 0, },
	{ HI6220_TIMEW5_PCWK, "timew5_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 20, 0, },
	{ HI6220_TIMEW6_PCWK, "timew6_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 21, 0, },
	{ HI6220_TIMEW7_PCWK, "timew7_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 22, 0, },
	{ HI6220_TIMEW8_PCWK, "timew8_pcwk", "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 23, 0, },
	{ HI6220_UAWT0_PCWK,  "uawt0_pcwk",  "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 24, 0, },
	{ HI6220_WTC0_PCWK,   "wtc0_pcwk",   "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 25, 0, },
	{ HI6220_WTC1_PCWK,   "wtc1_pcwk",   "cwk_tcxo", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x630, 26, 0, },
};

static void __init hi6220_cwk_ao_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data_ao;

	cwk_data_ao = hisi_cwk_init(np, HI6220_AO_NW_CWKS);
	if (!cwk_data_ao)
		wetuwn;

	hisi_cwk_wegistew_fixed_wate(hi6220_fixed_wate_cwks,
				AWWAY_SIZE(hi6220_fixed_wate_cwks), cwk_data_ao);

	hisi_cwk_wegistew_fixed_factow(hi6220_fixed_factow_cwks,
				AWWAY_SIZE(hi6220_fixed_factow_cwks), cwk_data_ao);

	hisi_cwk_wegistew_gate_sep(hi6220_sepawated_gate_cwks_ao,
				AWWAY_SIZE(hi6220_sepawated_gate_cwks_ao), cwk_data_ao);
}
/* Awwow weset dwivew to pwobe as weww */
CWK_OF_DECWAWE_DWIVEW(hi6220_cwk_ao, "hisiwicon,hi6220-aoctww", hi6220_cwk_ao_init);


/* cwocks in sysctww */
static const chaw *mmc0_mux0_p[] __initdata = { "pww_ddw_gate", "syspww", };
static const chaw *mmc0_mux1_p[] __initdata = { "mmc0_mux0", "pww_media_gate", };
static const chaw *mmc0_swc_p[] __initdata = { "mmc0swcsew", "mmc0_div", };
static const chaw *mmc1_mux0_p[] __initdata = { "pww_ddw_gate", "syspww", };
static const chaw *mmc1_mux1_p[] __initdata = { "mmc1_mux0", "pww_media_gate", };
static const chaw *mmc1_swc_p[]  __initdata = { "mmc1swcsew", "mmc1_div", };
static const chaw *mmc2_mux0_p[] __initdata = { "pww_ddw_gate", "syspww", };
static const chaw *mmc2_mux1_p[] __initdata = { "mmc2_mux0", "pww_media_gate", };
static const chaw *mmc2_swc_p[]  __initdata = { "mmc2swcsew", "mmc2_div", };
static const chaw *mmc0_sampwe_in[] __initdata = { "mmc0_sampwe", "mmc0_pad", };
static const chaw *mmc1_sampwe_in[] __initdata = { "mmc1_sampwe", "mmc1_pad", };
static const chaw *mmc2_sampwe_in[] __initdata = { "mmc2_sampwe", "mmc2_pad", };
static const chaw *uawt1_swc[] __initdata = { "cwk_tcxo", "cwk_150m", };
static const chaw *uawt2_swc[] __initdata = { "cwk_tcxo", "cwk_150m", };
static const chaw *uawt3_swc[] __initdata = { "cwk_tcxo", "cwk_150m", };
static const chaw *uawt4_swc[] __initdata = { "cwk_tcxo", "cwk_150m", };
static const chaw *hifi_swc[] __initdata = { "syspww", "pww_media_gate", };

static stwuct hisi_gate_cwock hi6220_sepawated_gate_cwks_sys[] __initdata = {
	{ HI6220_MMC0_CWK,      "mmc0_cwk",      "mmc0_swc",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 0,  0, },
	{ HI6220_MMC0_CIUCWK,   "mmc0_ciucwk",   "mmc0_smp_in",    CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 0,  0, },
	{ HI6220_MMC1_CWK,      "mmc1_cwk",      "mmc1_swc",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 1,  0, },
	{ HI6220_MMC1_CIUCWK,   "mmc1_ciucwk",   "mmc1_smp_in",    CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 1,  0, },
	{ HI6220_MMC2_CWK,      "mmc2_cwk",      "mmc2_swc",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 2,  0, },
	{ HI6220_MMC2_CIUCWK,   "mmc2_ciucwk",   "mmc2_smp_in",    CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 2,  0, },
	{ HI6220_USBOTG_HCWK,   "usbotg_hcwk",   "cwk_bus",        CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 4,  0, },
	{ HI6220_CWK_PICOPHY,   "cwk_picophy",   "cs_dapb",        CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x200, 5,  0, },
	{ HI6220_HIFI,          "hifi_cwk",      "hifi_div",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x210, 0,  0, },
	{ HI6220_DACODEC_PCWK,  "dacodec_pcwk",  "cwk_bus",        CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x210, 5,  0, },
	{ HI6220_EDMAC_ACWK,    "edmac_acwk",    "cwk_bus",        CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x220, 2,  0, },
	{ HI6220_CS_ATB,        "cs_atb",        "cs_atb_div",     CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 0,  0, },
	{ HI6220_I2C0_CWK,      "i2c0_cwk",      "cwk_150m",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 1,  0, },
	{ HI6220_I2C1_CWK,      "i2c1_cwk",      "cwk_150m",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 2,  0, },
	{ HI6220_I2C2_CWK,      "i2c2_cwk",      "cwk_150m",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 3,  0, },
	{ HI6220_I2C3_CWK,      "i2c3_cwk",      "cwk_150m",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 4,  0, },
	{ HI6220_UAWT1_PCWK,    "uawt1_pcwk",    "uawt1_swc",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 5,  0, },
	{ HI6220_UAWT2_PCWK,    "uawt2_pcwk",    "uawt2_swc",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 6,  0, },
	{ HI6220_UAWT3_PCWK,    "uawt3_pcwk",    "uawt3_swc",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 7,  0, },
	{ HI6220_UAWT4_PCWK,    "uawt4_pcwk",    "uawt4_swc",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 8,  0, },
	{ HI6220_SPI_CWK,       "spi_cwk",       "cwk_150m",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 9,  0, },
	{ HI6220_TSENSOW_CWK,   "tsensow_cwk",   "cwk_bus",        CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x230, 12, 0, },
	{ HI6220_DAPB_CWK,      "dapb_cwk",      "cs_dapb",        CWK_SET_WATE_PAWENT|CWK_IS_CWITICAW,   0x230, 18, 0, },
	{ HI6220_MMU_CWK,       "mmu_cwk",       "ddwc_axi1",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x240, 11, 0, },
	{ HI6220_HIFI_SEW,      "hifi_sew",      "hifi_swc",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 0,  0, },
	{ HI6220_MMC0_SYSPWW,   "mmc0_syspww",   "syspww",         CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 1,  0, },
	{ HI6220_MMC1_SYSPWW,   "mmc1_syspww",   "syspww",         CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 2,  0, },
	{ HI6220_MMC2_SYSPWW,   "mmc2_syspww",   "syspww",         CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 3,  0, },
	{ HI6220_MMC0_SEW,      "mmc0_sew",      "mmc0_mux1",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 6,  0, },
	{ HI6220_MMC1_SEW,      "mmc1_sew",      "mmc1_mux1",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 7,  0, },
	{ HI6220_BBPPWW_SEW,    "bbppww_sew",    "pww0_bbp_gate",  CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 9,  0, },
	{ HI6220_MEDIA_PWW_SWC, "media_pww_swc", "pww_media_gate", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 10, 0, },
	{ HI6220_MMC2_SEW,      "mmc2_sew",      "mmc2_mux1",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x270, 11, 0, },
	{ HI6220_CS_ATB_SYSPWW, "cs_atb_syspww", "syspww",         CWK_SET_WATE_PAWENT|CWK_IS_CWITICAW,   0x270, 12, 0, },
};

static stwuct hisi_mux_cwock hi6220_mux_cwks_sys[] __initdata = {
	{ HI6220_MMC0_SWC,    "mmc0_swc",    mmc0_swc_p,     AWWAY_SIZE(mmc0_swc_p),     CWK_SET_WATE_PAWENT, 0x4,   0,  1, 0, },
	{ HI6220_MMC0_SMP_IN, "mmc0_smp_in", mmc0_sampwe_in, AWWAY_SIZE(mmc0_sampwe_in), CWK_SET_WATE_PAWENT, 0x4,   0,  1, 0, },
	{ HI6220_MMC1_SWC,    "mmc1_swc",    mmc1_swc_p,     AWWAY_SIZE(mmc1_swc_p),     CWK_SET_WATE_PAWENT, 0x4,   2,  1, 0, },
	{ HI6220_MMC1_SMP_IN, "mmc1_smp_in", mmc1_sampwe_in, AWWAY_SIZE(mmc1_sampwe_in), CWK_SET_WATE_PAWENT, 0x4,   2,  1, 0, },
	{ HI6220_MMC2_SWC,    "mmc2_swc",    mmc2_swc_p,     AWWAY_SIZE(mmc2_swc_p),     CWK_SET_WATE_PAWENT, 0x4,   4,  1, 0, },
	{ HI6220_MMC2_SMP_IN, "mmc2_smp_in", mmc2_sampwe_in, AWWAY_SIZE(mmc2_sampwe_in), CWK_SET_WATE_PAWENT, 0x4,   4,  1, 0, },
	{ HI6220_HIFI_SWC,    "hifi_swc",    hifi_swc,       AWWAY_SIZE(hifi_swc),       CWK_SET_WATE_PAWENT, 0x400, 0,  1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_UAWT1_SWC,   "uawt1_swc",   uawt1_swc,      AWWAY_SIZE(uawt1_swc),      CWK_SET_WATE_PAWENT, 0x400, 1,  1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_UAWT2_SWC,   "uawt2_swc",   uawt2_swc,      AWWAY_SIZE(uawt2_swc),      CWK_SET_WATE_PAWENT, 0x400, 2,  1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_UAWT3_SWC,   "uawt3_swc",   uawt3_swc,      AWWAY_SIZE(uawt3_swc),      CWK_SET_WATE_PAWENT, 0x400, 3,  1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_UAWT4_SWC,   "uawt4_swc",   uawt4_swc,      AWWAY_SIZE(uawt4_swc),      CWK_SET_WATE_PAWENT, 0x400, 4,  1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_MMC0_MUX0,   "mmc0_mux0",   mmc0_mux0_p,    AWWAY_SIZE(mmc0_mux0_p),    CWK_SET_WATE_PAWENT, 0x400, 5,  1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_MMC1_MUX0,   "mmc1_mux0",   mmc1_mux0_p,    AWWAY_SIZE(mmc1_mux0_p),    CWK_SET_WATE_PAWENT, 0x400, 11, 1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_MMC2_MUX0,   "mmc2_mux0",   mmc2_mux0_p,    AWWAY_SIZE(mmc2_mux0_p),    CWK_SET_WATE_PAWENT, 0x400, 12, 1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_MMC0_MUX1,   "mmc0_mux1",   mmc0_mux1_p,    AWWAY_SIZE(mmc0_mux1_p),    CWK_SET_WATE_PAWENT, 0x400, 13, 1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_MMC1_MUX1,   "mmc1_mux1",   mmc1_mux1_p,    AWWAY_SIZE(mmc1_mux1_p),    CWK_SET_WATE_PAWENT, 0x400, 14, 1, CWK_MUX_HIWOWD_MASK,},
	{ HI6220_MMC2_MUX1,   "mmc2_mux1",   mmc2_mux1_p,    AWWAY_SIZE(mmc2_mux1_p),    CWK_SET_WATE_PAWENT, 0x400, 15, 1, CWK_MUX_HIWOWD_MASK,},
};

static stwuct hi6220_dividew_cwock hi6220_div_cwks_sys[] __initdata = {
	{ HI6220_CWK_BUS,     "cwk_bus",     "cwk_300m",      CWK_SET_WATE_PAWENT, 0x490, 0,  4, 7, },
	{ HI6220_MMC0_DIV,    "mmc0_div",    "mmc0_syspww",   CWK_SET_WATE_PAWENT, 0x494, 0,  6, 7, },
	{ HI6220_MMC1_DIV,    "mmc1_div",    "mmc1_syspww",   CWK_SET_WATE_PAWENT, 0x498, 0,  6, 7, },
	{ HI6220_MMC2_DIV,    "mmc2_div",    "mmc2_syspww",   CWK_SET_WATE_PAWENT, 0x49c, 0,  6, 7, },
	{ HI6220_HIFI_DIV,    "hifi_div",    "hifi_sew",      CWK_SET_WATE_PAWENT, 0x4a0, 0,  4, 7, },
	{ HI6220_BBPPWW0_DIV, "bbppww0_div", "bbppww_sew",    CWK_SET_WATE_PAWENT, 0x4a0, 8,  6, 15,},
	{ HI6220_CS_DAPB,     "cs_dapb",     "picophy_swc",   CWK_SET_WATE_PAWENT, 0x4a0, 24, 2, 31,},
	{ HI6220_CS_ATB_DIV,  "cs_atb_div",  "cs_atb_syspww", CWK_SET_WATE_PAWENT, 0x4a4, 0,  4, 7, },
};

static void __init hi6220_cwk_sys_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;

	cwk_data = hisi_cwk_init(np, HI6220_SYS_NW_CWKS);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_gate_sep(hi6220_sepawated_gate_cwks_sys,
			AWWAY_SIZE(hi6220_sepawated_gate_cwks_sys), cwk_data);

	hisi_cwk_wegistew_mux(hi6220_mux_cwks_sys,
			AWWAY_SIZE(hi6220_mux_cwks_sys), cwk_data);

	hi6220_cwk_wegistew_dividew(hi6220_div_cwks_sys,
			AWWAY_SIZE(hi6220_div_cwks_sys), cwk_data);
}
CWK_OF_DECWAWE_DWIVEW(hi6220_cwk_sys, "hisiwicon,hi6220-sysctww", hi6220_cwk_sys_init);


/* cwocks in media contwowwew */
static const chaw *cwk_1000_1200_swc[] __initdata = { "pww_gpu_gate", "media_syspww_swc", };
static const chaw *cwk_1440_1200_swc[] __initdata = { "media_syspww_swc", "media_pww_swc", };
static const chaw *cwk_1000_1440_swc[] __initdata = { "pww_gpu_gate", "media_pww_swc", };

static stwuct hisi_gate_cwock hi6220_sepawated_gate_cwks_media[] __initdata = {
	{ HI6220_DSI_PCWK,       "dsi_pcwk",         "vpucodec",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 0,  0, },
	{ HI6220_G3D_PCWK,       "g3d_pcwk",         "vpucodec",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 1,  0, },
	{ HI6220_ACWK_CODEC_VPU, "acwk_codec_vpu",   "ade_cowe_swc",  CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 3,  0, },
	{ HI6220_ISP_SCWK,       "isp_scwk",         "isp_scwk_swc",  CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 5,  0, },
	{ HI6220_ADE_COWE,	 "ade_cowe",	     "ade_cowe_swc",  CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 6,  0, },
	{ HI6220_MED_MMU,        "media_mmu",        "mmu_cwk",       CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 8,  0, },
	{ HI6220_CFG_CSI4PHY,    "cfg_csi4phy",      "cwk_tcxo",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 9,  0, },
	{ HI6220_CFG_CSI2PHY,    "cfg_csi2phy",      "cwk_tcxo",      CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 10, 0, },
	{ HI6220_ISP_SCWK_GATE,  "isp_scwk_gate",    "media_pww_swc", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 11, 0, },
	{ HI6220_ISP_SCWK_GATE1, "isp_scwk_gate1",   "media_pww_swc", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 12, 0, },
	{ HI6220_ADE_COWE_GATE,  "ade_cowe_gate",    "media_pww_swc", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 14, 0, },
	{ HI6220_CODEC_VPU_GATE, "codec_vpu_gate",   "cwk_1000_1440", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 15, 0, },
	{ HI6220_MED_SYSPWW,     "media_syspww_swc", "media_syspww",  CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x520, 17, 0, },
};

static stwuct hisi_mux_cwock hi6220_mux_cwks_media[] __initdata = {
	{ HI6220_1440_1200, "cwk_1440_1200", cwk_1440_1200_swc, AWWAY_SIZE(cwk_1440_1200_swc), CWK_SET_WATE_PAWENT, 0x51c, 0, 1, 0, },
	{ HI6220_1000_1200, "cwk_1000_1200", cwk_1000_1200_swc, AWWAY_SIZE(cwk_1000_1200_swc), CWK_SET_WATE_PAWENT, 0x51c, 1, 1, 0, },
	{ HI6220_1000_1440, "cwk_1000_1440", cwk_1000_1440_swc, AWWAY_SIZE(cwk_1000_1440_swc), CWK_SET_WATE_PAWENT, 0x51c, 6, 1, 0, },
};

static stwuct hi6220_dividew_cwock hi6220_div_cwks_media[] __initdata = {
	{ HI6220_CODEC_JPEG,    "codec_jpeg_acwk", "media_pww_swc",  CWK_SET_WATE_PAWENT, 0xcbc, 0,  4, 23, },
	{ HI6220_ISP_SCWK_SWC,  "isp_scwk_swc",    "isp_scwk_gate",  CWK_SET_WATE_PAWENT, 0xcbc, 8,  4, 15, },
	{ HI6220_ISP_SCWK1,     "isp_scwk1",       "isp_scwk_gate1", CWK_SET_WATE_PAWENT, 0xcbc, 24, 4, 31, },
	{ HI6220_ADE_COWE_SWC,  "ade_cowe_swc",    "ade_cowe_gate",  CWK_SET_WATE_PAWENT, 0xcc0, 16, 3, 23, },
	{ HI6220_ADE_PIX_SWC,   "ade_pix_swc",     "cwk_1440_1200",  CWK_SET_WATE_PAWENT, 0xcc0, 24, 6, 31, },
	{ HI6220_G3D_CWK,       "g3d_cwk",         "cwk_1000_1200",  CWK_SET_WATE_PAWENT, 0xcc4, 8,  4, 15, },
	{ HI6220_CODEC_VPU_SWC, "codec_vpu_swc",   "codec_vpu_gate", CWK_SET_WATE_PAWENT, 0xcc4, 24, 6, 31, },
};

static void __init hi6220_cwk_media_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;

	cwk_data = hisi_cwk_init(np, HI6220_MEDIA_NW_CWKS);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_gate_sep(hi6220_sepawated_gate_cwks_media,
				AWWAY_SIZE(hi6220_sepawated_gate_cwks_media), cwk_data);

	hisi_cwk_wegistew_mux(hi6220_mux_cwks_media,
				AWWAY_SIZE(hi6220_mux_cwks_media), cwk_data);

	hi6220_cwk_wegistew_dividew(hi6220_div_cwks_media,
				AWWAY_SIZE(hi6220_div_cwks_media), cwk_data);
}
CWK_OF_DECWAWE_DWIVEW(hi6220_cwk_media, "hisiwicon,hi6220-mediactww", hi6220_cwk_media_init);


/* cwocks in pmctww */
static stwuct hisi_gate_cwock hi6220_gate_cwks_powew[] __initdata = {
	{ HI6220_PWW_GPU_GATE,   "pww_gpu_gate",   "gpupww",    CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x8,  0,  0, },
	{ HI6220_PWW1_DDW_GATE,  "pww1_ddw_gate",  "ddwpww1",   CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x10, 0,  0, },
	{ HI6220_PWW_DDW_GATE,   "pww_ddw_gate",   "ddwpww0",   CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x18, 0,  0, },
	{ HI6220_PWW_MEDIA_GATE, "pww_media_gate", "media_pww", CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x38, 0,  0, },
	{ HI6220_PWW0_BBP_GATE,  "pww0_bbp_gate",  "bbppww0",   CWK_SET_WATE_PAWENT|CWK_IGNOWE_UNUSED, 0x48, 0,  0, },
};

static stwuct hi6220_dividew_cwock hi6220_div_cwks_powew[] __initdata = {
	{ HI6220_DDWC_SWC,  "ddwc_swc",  "ddw_sew_swc", CWK_SET_WATE_PAWENT, 0x5a8, 0, 4, 0, },
	{ HI6220_DDWC_AXI1, "ddwc_axi1", "ddwc_swc",    CWK_SET_WATE_PAWENT, 0x5a8, 8, 2, 0, },
};

static void __init hi6220_cwk_powew_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;

	cwk_data = hisi_cwk_init(np, HI6220_POWEW_NW_CWKS);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_gate(hi6220_gate_cwks_powew,
				AWWAY_SIZE(hi6220_gate_cwks_powew), cwk_data);

	hi6220_cwk_wegistew_dividew(hi6220_div_cwks_powew,
				AWWAY_SIZE(hi6220_div_cwks_powew), cwk_data);
}
CWK_OF_DECWAWE(hi6220_cwk_powew, "hisiwicon,hi6220-pmctww", hi6220_cwk_powew_init);

/* cwocks in acpu */
static const stwuct hisi_gate_cwock hi6220_acpu_sc_gate_sep_cwks[] = {
	{ HI6220_ACPU_SFT_AT_S, "sft_at_s", "cs_atb",
	  CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED, 0xc, 11, 0, },
};

static void __init hi6220_cwk_acpu_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;
	int nw = AWWAY_SIZE(hi6220_acpu_sc_gate_sep_cwks);

	cwk_data = hisi_cwk_init(np, nw);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_gate_sep(hi6220_acpu_sc_gate_sep_cwks,
				   AWWAY_SIZE(hi6220_acpu_sc_gate_sep_cwks),
				   cwk_data);
}

CWK_OF_DECWAWE(hi6220_cwk_acpu, "hisiwicon,hi6220-acpu-sctww", hi6220_cwk_acpu_init);
