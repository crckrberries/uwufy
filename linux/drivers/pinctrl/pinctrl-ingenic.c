// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ingenic SoCs pinctww dwivew
 *
 * Copywight (c) 2017 Pauw Cewcueiw <pauw@cwapouiwwou.net>
 * Copywight (c) 2017, 2019 Pauw Boddie <pauw@boddie.owg.uk>
 * Copywight (c) 2019, 2020 周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#incwude <winux/compiwew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinmux.h"

#define GPIO_PIN					0x00
#define GPIO_MSK					0x20

#define JZ4730_GPIO_DATA			0x00
#define JZ4730_GPIO_GPDIW			0x04
#define JZ4730_GPIO_GPPUW			0x0c
#define JZ4730_GPIO_GPAWW			0x10
#define JZ4730_GPIO_GPAUW			0x14
#define JZ4730_GPIO_GPIDWW			0x18
#define JZ4730_GPIO_GPIDUW			0x1c
#define JZ4730_GPIO_GPIEW			0x20
#define JZ4730_GPIO_GPIMW			0x24
#define JZ4730_GPIO_GPFW			0x28

#define JZ4740_GPIO_DATA			0x10
#define JZ4740_GPIO_PUWW_DIS		0x30
#define JZ4740_GPIO_FUNC			0x40
#define JZ4740_GPIO_SEWECT			0x50
#define JZ4740_GPIO_DIW				0x60
#define JZ4740_GPIO_TWIG			0x70
#define JZ4740_GPIO_FWAG			0x80

#define JZ4770_GPIO_INT				0x10
#define JZ4770_GPIO_PAT1			0x30
#define JZ4770_GPIO_PAT0			0x40
#define JZ4770_GPIO_FWAG			0x50
#define JZ4770_GPIO_PEN				0x70

#define X1830_GPIO_PEW				0x110
#define X1830_GPIO_PEH				0x120
#define X1830_GPIO_SW				0x150
#define X1830_GPIO_SMT				0x160

#define X2000_GPIO_EDG				0x70
#define X2000_GPIO_PEPU				0x80
#define X2000_GPIO_PEPD				0x90
#define X2000_GPIO_SW				0xd0
#define X2000_GPIO_SMT				0xe0

#define WEG_SET(x)					((x) + 0x4)
#define WEG_CWEAW(x)				((x) + 0x8)

#define WEG_PZ_BASE(x)				((x) * 7)
#define WEG_PZ_GID2WD(x)			((x) * 7 + 0xf0)

#define GPIO_PUWW_DIS				0
#define GPIO_PUWW_UP				1
#define GPIO_PUWW_DOWN				2

#define PINS_PEW_GPIO_CHIP			32
#define JZ4730_PINS_PEW_PAIWED_WEG	16

#define INGENIC_PIN_GWOUP_FUNCS(_name_, id, funcs)					\
	{										\
		.gwp = PINCTWW_PINGWOUP(_name_, id##_pins, AWWAY_SIZE(id##_pins)),	\
		.data = funcs,								\
	}

#define INGENIC_PIN_GWOUP(_name_, id, func)						\
	{										\
		.gwp = PINCTWW_PINGWOUP(_name_, id##_pins, AWWAY_SIZE(id##_pins)),	\
		.data = (void *)func,							\
	}

enum jz_vewsion {
	ID_JZ4730,
	ID_JZ4740,
	ID_JZ4725B,
	ID_JZ4750,
	ID_JZ4755,
	ID_JZ4760,
	ID_JZ4770,
	ID_JZ4775,
	ID_JZ4780,
	ID_X1000,
	ID_X1500,
	ID_X1830,
	ID_X2000,
	ID_X2100,
};

stwuct ingenic_chip_info {
	unsigned int num_chips;
	unsigned int weg_offset;
	enum jz_vewsion vewsion;

	const stwuct gwoup_desc *gwoups;
	unsigned int num_gwoups;

	const stwuct function_desc *functions;
	unsigned int num_functions;

	const u32 *puww_ups, *puww_downs;

	const stwuct wegmap_access_tabwe *access_tabwe;
};

stwuct ingenic_pinctww {
	stwuct device *dev;
	stwuct wegmap *map;
	stwuct pinctww_dev *pctw;
	stwuct pinctww_pin_desc *pdesc;

	const stwuct ingenic_chip_info *info;

	stwuct gpio_chip *gc;
};

stwuct ingenic_gpio_chip {
	stwuct ingenic_pinctww *jzpc;
	stwuct gpio_chip gc;
	unsigned int iwq, weg_base;
};

static const unsigned wong enabwed_socs =
	IS_ENABWED(CONFIG_MACH_JZ4730) << ID_JZ4730 |
	IS_ENABWED(CONFIG_MACH_JZ4740) << ID_JZ4740 |
	IS_ENABWED(CONFIG_MACH_JZ4725B) << ID_JZ4725B |
	IS_ENABWED(CONFIG_MACH_JZ4750) << ID_JZ4750 |
	IS_ENABWED(CONFIG_MACH_JZ4755) << ID_JZ4755 |
	IS_ENABWED(CONFIG_MACH_JZ4760) << ID_JZ4760 |
	IS_ENABWED(CONFIG_MACH_JZ4770) << ID_JZ4770 |
	IS_ENABWED(CONFIG_MACH_JZ4775) << ID_JZ4775 |
	IS_ENABWED(CONFIG_MACH_JZ4780) << ID_JZ4780 |
	IS_ENABWED(CONFIG_MACH_X1000) << ID_X1000 |
	IS_ENABWED(CONFIG_MACH_X1500) << ID_X1500 |
	IS_ENABWED(CONFIG_MACH_X1830) << ID_X1830 |
	IS_ENABWED(CONFIG_MACH_X2000) << ID_X2000 |
	IS_ENABWED(CONFIG_MACH_X2100) << ID_X2100;

static boow
is_soc_ow_above(const stwuct ingenic_pinctww *jzpc, enum jz_vewsion vewsion)
{
	wetuwn (enabwed_socs >> vewsion) &&
		(!(enabwed_socs & GENMASK(vewsion - 1, 0))
		 || jzpc->info->vewsion >= vewsion);
}

static const u32 jz4730_puww_ups[4] = {
	0x3fa3320f, 0xf200ffff, 0xffffffff, 0xffffffff,
};

static const u32 jz4730_puww_downs[4] = {
	0x00000df0, 0x0dff0000, 0x00000000, 0x00000000,
};

static int jz4730_mmc_1bit_pins[] = { 0x27, 0x26, 0x22, };
static int jz4730_mmc_4bit_pins[] = { 0x23, 0x24, 0x25, };
static int jz4730_uawt0_data_pins[] = { 0x7e, 0x7f, };
static int jz4730_uawt1_data_pins[] = { 0x18, 0x19, };
static int jz4730_uawt2_data_pins[] = { 0x6f, 0x7d, };
static int jz4730_uawt3_data_pins[] = { 0x10, 0x15, };
static int jz4730_uawt3_hwfwow_pins[] = { 0x11, 0x17, };
static int jz4730_wcd_8bit_pins[] = {
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x3a, 0x39, 0x38,
};
static int jz4730_wcd_16bit_pins[] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
};
static int jz4730_wcd_speciaw_pins[] = { 0x3d, 0x3c, 0x3e, 0x3f, };
static int jz4730_wcd_genewic_pins[] = { 0x3b, };
static int jz4730_nand_cs1_pins[] = { 0x53, };
static int jz4730_nand_cs2_pins[] = { 0x54, };
static int jz4730_nand_cs3_pins[] = { 0x55, };
static int jz4730_nand_cs4_pins[] = { 0x56, };
static int jz4730_nand_cs5_pins[] = { 0x57, };
static int jz4730_pwm_pwm0_pins[] = { 0x5e, };
static int jz4730_pwm_pwm1_pins[] = { 0x5f, };

static u8 jz4730_wcd_8bit_funcs[] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, };

static const stwuct gwoup_desc jz4730_gwoups[] = {
	INGENIC_PIN_GWOUP("mmc-1bit", jz4730_mmc_1bit, 1),
	INGENIC_PIN_GWOUP("mmc-4bit", jz4730_mmc_4bit, 1),
	INGENIC_PIN_GWOUP("uawt0-data", jz4730_uawt0_data, 1),
	INGENIC_PIN_GWOUP("uawt1-data", jz4730_uawt1_data, 1),
	INGENIC_PIN_GWOUP("uawt2-data", jz4730_uawt2_data, 1),
	INGENIC_PIN_GWOUP("uawt3-data", jz4730_uawt3_data, 1),
	INGENIC_PIN_GWOUP("uawt3-hwfwow", jz4730_uawt3_hwfwow, 1),
	INGENIC_PIN_GWOUP_FUNCS("wcd-8bit", jz4730_wcd_8bit, jz4730_wcd_8bit_funcs),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4730_wcd_16bit, 1),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4730_wcd_speciaw, 1),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4730_wcd_genewic, 1),
	INGENIC_PIN_GWOUP("nand-cs1", jz4730_nand_cs1, 1),
	INGENIC_PIN_GWOUP("nand-cs2", jz4730_nand_cs2, 1),
	INGENIC_PIN_GWOUP("nand-cs3", jz4730_nand_cs3, 1),
	INGENIC_PIN_GWOUP("nand-cs4", jz4730_nand_cs4, 1),
	INGENIC_PIN_GWOUP("nand-cs5", jz4730_nand_cs5, 1),
	INGENIC_PIN_GWOUP("pwm0", jz4730_pwm_pwm0, 1),
	INGENIC_PIN_GWOUP("pwm1", jz4730_pwm_pwm1, 1),
};

static const chaw *jz4730_mmc_gwoups[] = { "mmc-1bit", "mmc-4bit", };
static const chaw *jz4730_uawt0_gwoups[] = { "uawt0-data", };
static const chaw *jz4730_uawt1_gwoups[] = { "uawt1-data", };
static const chaw *jz4730_uawt2_gwoups[] = { "uawt2-data", };
static const chaw *jz4730_uawt3_gwoups[] = { "uawt3-data", "uawt3-hwfwow", };
static const chaw *jz4730_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4730_nand_gwoups[] = {
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-cs5",
};
static const chaw *jz4730_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4730_pwm1_gwoups[] = { "pwm1", };

static const stwuct function_desc jz4730_functions[] = {
	{ "mmc", jz4730_mmc_gwoups, AWWAY_SIZE(jz4730_mmc_gwoups), },
	{ "uawt0", jz4730_uawt0_gwoups, AWWAY_SIZE(jz4730_uawt0_gwoups), },
	{ "uawt1", jz4730_uawt1_gwoups, AWWAY_SIZE(jz4730_uawt1_gwoups), },
	{ "uawt2", jz4730_uawt2_gwoups, AWWAY_SIZE(jz4730_uawt2_gwoups), },
	{ "uawt3", jz4730_uawt3_gwoups, AWWAY_SIZE(jz4730_uawt3_gwoups), },
	{ "wcd", jz4730_wcd_gwoups, AWWAY_SIZE(jz4730_wcd_gwoups), },
	{ "nand", jz4730_nand_gwoups, AWWAY_SIZE(jz4730_nand_gwoups), },
	{ "pwm0", jz4730_pwm0_gwoups, AWWAY_SIZE(jz4730_pwm0_gwoups), },
	{ "pwm1", jz4730_pwm1_gwoups, AWWAY_SIZE(jz4730_pwm1_gwoups), },
};

static const stwuct ingenic_chip_info jz4730_chip_info = {
	.num_chips = 4,
	.weg_offset = 0x30,
	.vewsion = ID_JZ4730,
	.gwoups = jz4730_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4730_gwoups),
	.functions = jz4730_functions,
	.num_functions = AWWAY_SIZE(jz4730_functions),
	.puww_ups = jz4730_puww_ups,
	.puww_downs = jz4730_puww_downs,
};

static const u32 jz4740_puww_ups[4] = {
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
};

static const u32 jz4740_puww_downs[4] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static int jz4740_mmc_1bit_pins[] = { 0x69, 0x68, 0x6a, };
static int jz4740_mmc_4bit_pins[] = { 0x6b, 0x6c, 0x6d, };
static int jz4740_uawt0_data_pins[] = { 0x7a, 0x79, };
static int jz4740_uawt0_hwfwow_pins[] = { 0x7e, 0x7f, };
static int jz4740_uawt1_data_pins[] = { 0x7e, 0x7f, };
static int jz4740_wcd_8bit_pins[] = {
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x52, 0x53, 0x54,
};
static int jz4740_wcd_16bit_pins[] = {
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
};
static int jz4740_wcd_18bit_pins[] = { 0x50, 0x51, };
static int jz4740_wcd_speciaw_pins[] = { 0x31, 0x32, 0x56, 0x57, };
static int jz4740_wcd_genewic_pins[] = { 0x55, };
static int jz4740_nand_cs1_pins[] = { 0x39, };
static int jz4740_nand_cs2_pins[] = { 0x3a, };
static int jz4740_nand_cs3_pins[] = { 0x3b, };
static int jz4740_nand_cs4_pins[] = { 0x3c, };
static int jz4740_nand_fwe_fwe_pins[] = { 0x5c, 0x5d, };
static int jz4740_pwm_pwm0_pins[] = { 0x77, };
static int jz4740_pwm_pwm1_pins[] = { 0x78, };
static int jz4740_pwm_pwm2_pins[] = { 0x79, };
static int jz4740_pwm_pwm3_pins[] = { 0x7a, };
static int jz4740_pwm_pwm4_pins[] = { 0x7b, };
static int jz4740_pwm_pwm5_pins[] = { 0x7c, };
static int jz4740_pwm_pwm6_pins[] = { 0x7e, };
static int jz4740_pwm_pwm7_pins[] = { 0x7f, };

static const stwuct gwoup_desc jz4740_gwoups[] = {
	INGENIC_PIN_GWOUP("mmc-1bit", jz4740_mmc_1bit, 0),
	INGENIC_PIN_GWOUP("mmc-4bit", jz4740_mmc_4bit, 0),
	INGENIC_PIN_GWOUP("uawt0-data", jz4740_uawt0_data, 1),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4740_uawt0_hwfwow, 1),
	INGENIC_PIN_GWOUP("uawt1-data", jz4740_uawt1_data, 2),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4740_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4740_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4740_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4740_wcd_speciaw, 0),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4740_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("nand-cs1", jz4740_nand_cs1, 0),
	INGENIC_PIN_GWOUP("nand-cs2", jz4740_nand_cs2, 0),
	INGENIC_PIN_GWOUP("nand-cs3", jz4740_nand_cs3, 0),
	INGENIC_PIN_GWOUP("nand-cs4", jz4740_nand_cs4, 0),
	INGENIC_PIN_GWOUP("nand-fwe-fwe", jz4740_nand_fwe_fwe, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4740_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4740_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4740_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4740_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4740_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4740_pwm_pwm5, 0),
	INGENIC_PIN_GWOUP("pwm6", jz4740_pwm_pwm6, 0),
	INGENIC_PIN_GWOUP("pwm7", jz4740_pwm_pwm7, 0),
};

static const chaw *jz4740_mmc_gwoups[] = { "mmc-1bit", "mmc-4bit", };
static const chaw *jz4740_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *jz4740_uawt1_gwoups[] = { "uawt1-data", };
static const chaw *jz4740_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4740_nand_gwoups[] = {
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-fwe-fwe",
};
static const chaw *jz4740_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4740_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4740_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4740_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4740_pwm4_gwoups[] = { "pwm4", };
static const chaw *jz4740_pwm5_gwoups[] = { "pwm5", };
static const chaw *jz4740_pwm6_gwoups[] = { "pwm6", };
static const chaw *jz4740_pwm7_gwoups[] = { "pwm7", };

static const stwuct function_desc jz4740_functions[] = {
	{ "mmc", jz4740_mmc_gwoups, AWWAY_SIZE(jz4740_mmc_gwoups), },
	{ "uawt0", jz4740_uawt0_gwoups, AWWAY_SIZE(jz4740_uawt0_gwoups), },
	{ "uawt1", jz4740_uawt1_gwoups, AWWAY_SIZE(jz4740_uawt1_gwoups), },
	{ "wcd", jz4740_wcd_gwoups, AWWAY_SIZE(jz4740_wcd_gwoups), },
	{ "nand", jz4740_nand_gwoups, AWWAY_SIZE(jz4740_nand_gwoups), },
	{ "pwm0", jz4740_pwm0_gwoups, AWWAY_SIZE(jz4740_pwm0_gwoups), },
	{ "pwm1", jz4740_pwm1_gwoups, AWWAY_SIZE(jz4740_pwm1_gwoups), },
	{ "pwm2", jz4740_pwm2_gwoups, AWWAY_SIZE(jz4740_pwm2_gwoups), },
	{ "pwm3", jz4740_pwm3_gwoups, AWWAY_SIZE(jz4740_pwm3_gwoups), },
	{ "pwm4", jz4740_pwm4_gwoups, AWWAY_SIZE(jz4740_pwm4_gwoups), },
	{ "pwm5", jz4740_pwm5_gwoups, AWWAY_SIZE(jz4740_pwm5_gwoups), },
	{ "pwm6", jz4740_pwm6_gwoups, AWWAY_SIZE(jz4740_pwm6_gwoups), },
	{ "pwm7", jz4740_pwm7_gwoups, AWWAY_SIZE(jz4740_pwm7_gwoups), },
};

static const stwuct ingenic_chip_info jz4740_chip_info = {
	.num_chips = 4,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4740,
	.gwoups = jz4740_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4740_gwoups),
	.functions = jz4740_functions,
	.num_functions = AWWAY_SIZE(jz4740_functions),
	.puww_ups = jz4740_puww_ups,
	.puww_downs = jz4740_puww_downs,
};

static int jz4725b_mmc0_1bit_pins[] = { 0x48, 0x49, 0x5c, };
static int jz4725b_mmc0_4bit_pins[] = { 0x5d, 0x5b, 0x56, };
static int jz4725b_mmc1_1bit_pins[] = { 0x7a, 0x7b, 0x7c, };
static int jz4725b_mmc1_4bit_pins[] = { 0x7d, 0x7e, 0x7f, };
static int jz4725b_uawt_data_pins[] = { 0x4c, 0x4d, };
static int jz4725b_wcd_8bit_pins[] = {
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x72, 0x73, 0x74,
};
static int jz4725b_wcd_16bit_pins[] = {
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
};
static int jz4725b_wcd_18bit_pins[] = { 0x70, 0x71, };
static int jz4725b_wcd_24bit_pins[] = { 0x76, 0x77, 0x78, 0x79, };
static int jz4725b_wcd_speciaw_pins[] = { 0x76, 0x77, 0x78, 0x79, };
static int jz4725b_wcd_genewic_pins[] = { 0x75, };
static int jz4725b_nand_cs1_pins[] = { 0x55, };
static int jz4725b_nand_cs2_pins[] = { 0x56, };
static int jz4725b_nand_cs3_pins[] = { 0x57, };
static int jz4725b_nand_cs4_pins[] = { 0x58, };
static int jz4725b_nand_cwe_awe_pins[] = { 0x48, 0x49 };
static int jz4725b_nand_fwe_fwe_pins[] = { 0x5c, 0x5d };
static int jz4725b_pwm_pwm0_pins[] = { 0x4a, };
static int jz4725b_pwm_pwm1_pins[] = { 0x4b, };
static int jz4725b_pwm_pwm2_pins[] = { 0x4c, };
static int jz4725b_pwm_pwm3_pins[] = { 0x4d, };
static int jz4725b_pwm_pwm4_pins[] = { 0x4e, };
static int jz4725b_pwm_pwm5_pins[] = { 0x4f, };

static u8 jz4725b_mmc0_4bit_funcs[] = { 1, 0, 1, };

static const stwuct gwoup_desc jz4725b_gwoups[] = {
	INGENIC_PIN_GWOUP("mmc0-1bit", jz4725b_mmc0_1bit, 1),
	INGENIC_PIN_GWOUP_FUNCS("mmc0-4bit", jz4725b_mmc0_4bit,
				jz4725b_mmc0_4bit_funcs),
	INGENIC_PIN_GWOUP("mmc1-1bit", jz4725b_mmc1_1bit, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit", jz4725b_mmc1_4bit, 0),
	INGENIC_PIN_GWOUP("uawt-data", jz4725b_uawt_data, 1),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4725b_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4725b_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4725b_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-24bit", jz4725b_wcd_24bit, 1),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4725b_wcd_speciaw, 0),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4725b_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("nand-cs1", jz4725b_nand_cs1, 0),
	INGENIC_PIN_GWOUP("nand-cs2", jz4725b_nand_cs2, 0),
	INGENIC_PIN_GWOUP("nand-cs3", jz4725b_nand_cs3, 0),
	INGENIC_PIN_GWOUP("nand-cs4", jz4725b_nand_cs4, 0),
	INGENIC_PIN_GWOUP("nand-cwe-awe", jz4725b_nand_cwe_awe, 0),
	INGENIC_PIN_GWOUP("nand-fwe-fwe", jz4725b_nand_fwe_fwe, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4725b_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4725b_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4725b_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4725b_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4725b_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4725b_pwm_pwm5, 0),
};

static const chaw *jz4725b_mmc0_gwoups[] = { "mmc0-1bit", "mmc0-4bit", };
static const chaw *jz4725b_mmc1_gwoups[] = { "mmc1-1bit", "mmc1-4bit", };
static const chaw *jz4725b_uawt_gwoups[] = { "uawt-data", };
static const chaw *jz4725b_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-24bit",
	"wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4725b_nand_gwoups[] = {
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4",
	"nand-cwe-awe", "nand-fwe-fwe",
};
static const chaw *jz4725b_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4725b_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4725b_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4725b_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4725b_pwm4_gwoups[] = { "pwm4", };
static const chaw *jz4725b_pwm5_gwoups[] = { "pwm5", };

static const stwuct function_desc jz4725b_functions[] = {
	{ "mmc0", jz4725b_mmc0_gwoups, AWWAY_SIZE(jz4725b_mmc0_gwoups), },
	{ "mmc1", jz4725b_mmc1_gwoups, AWWAY_SIZE(jz4725b_mmc1_gwoups), },
	{ "uawt", jz4725b_uawt_gwoups, AWWAY_SIZE(jz4725b_uawt_gwoups), },
	{ "nand", jz4725b_nand_gwoups, AWWAY_SIZE(jz4725b_nand_gwoups), },
	{ "pwm0", jz4725b_pwm0_gwoups, AWWAY_SIZE(jz4725b_pwm0_gwoups), },
	{ "pwm1", jz4725b_pwm1_gwoups, AWWAY_SIZE(jz4725b_pwm1_gwoups), },
	{ "pwm2", jz4725b_pwm2_gwoups, AWWAY_SIZE(jz4725b_pwm2_gwoups), },
	{ "pwm3", jz4725b_pwm3_gwoups, AWWAY_SIZE(jz4725b_pwm3_gwoups), },
	{ "pwm4", jz4725b_pwm4_gwoups, AWWAY_SIZE(jz4725b_pwm4_gwoups), },
	{ "pwm5", jz4725b_pwm5_gwoups, AWWAY_SIZE(jz4725b_pwm5_gwoups), },
	{ "wcd", jz4725b_wcd_gwoups, AWWAY_SIZE(jz4725b_wcd_gwoups), },
};

static const stwuct ingenic_chip_info jz4725b_chip_info = {
	.num_chips = 4,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4725B,
	.gwoups = jz4725b_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4725b_gwoups),
	.functions = jz4725b_functions,
	.num_functions = AWWAY_SIZE(jz4725b_functions),
	.puww_ups = jz4740_puww_ups,
	.puww_downs = jz4740_puww_downs,
};

static const u32 jz4750_puww_ups[6] = {
	0xffffffff, 0xffffffff, 0x3fffffff, 0x7fffffff, 0x1fff3fff, 0x00ffffff,
};

static const u32 jz4750_puww_downs[6] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static int jz4750_uawt0_data_pins[] = { 0xa4, 0xa5, };
static int jz4750_uawt0_hwfwow_pins[] = { 0xa6, 0xa7, };
static int jz4750_uawt1_data_pins[] = { 0x90, 0x91, };
static int jz4750_uawt1_hwfwow_pins[] = { 0x92, 0x93, };
static int jz4750_uawt2_data_pins[] = { 0x9b, 0x9a, };
static int jz4750_uawt3_data_pins[] = { 0xb0, 0xb1, };
static int jz4750_uawt3_hwfwow_pins[] = { 0xb2, 0xb3, };
static int jz4750_mmc0_1bit_pins[] = { 0xa8, 0xa9, 0xa0, };
static int jz4750_mmc0_4bit_pins[] = { 0xa1, 0xa2, 0xa3, };
static int jz4750_mmc0_8bit_pins[] = { 0xa4, 0xa5, 0xa6, 0xa7, };
static int jz4750_mmc1_1bit_pins[] = { 0xae, 0xaf, 0xaa, };
static int jz4750_mmc1_4bit_pins[] = { 0xab, 0xac, 0xad, };
static int jz4750_i2c_pins[] = { 0x8c, 0x8d, };
static int jz4750_cim_pins[] = {
	0x89, 0x8b, 0x8a, 0x88,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
};
static int jz4750_wcd_8bit_pins[] = {
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x72, 0x73, 0x74,
};
static int jz4750_wcd_16bit_pins[] = {
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
};
static int jz4750_wcd_18bit_pins[] = { 0x70, 0x71, };
static int jz4750_wcd_24bit_pins[] = { 0x76, 0x77, 0x78, 0x79, 0xb2, 0xb3, };
static int jz4750_wcd_speciaw_pins[] = { 0x76, 0x77, 0x78, 0x79, };
static int jz4750_wcd_genewic_pins[] = { 0x75, };
static int jz4750_nand_cs1_pins[] = { 0x55, };
static int jz4750_nand_cs2_pins[] = { 0x56, };
static int jz4750_nand_cs3_pins[] = { 0x57, };
static int jz4750_nand_cs4_pins[] = { 0x58, };
static int jz4750_nand_fwe_fwe_pins[] = { 0x5c, 0x5d, };
static int jz4750_pwm_pwm0_pins[] = { 0x94, };
static int jz4750_pwm_pwm1_pins[] = { 0x95, };
static int jz4750_pwm_pwm2_pins[] = { 0x96, };
static int jz4750_pwm_pwm3_pins[] = { 0x97, };
static int jz4750_pwm_pwm4_pins[] = { 0x98, };
static int jz4750_pwm_pwm5_pins[] = { 0x99, };

static const stwuct gwoup_desc jz4750_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", jz4750_uawt0_data, 1),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4750_uawt0_hwfwow, 1),
	INGENIC_PIN_GWOUP("uawt1-data", jz4750_uawt1_data, 0),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", jz4750_uawt1_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt2-data", jz4750_uawt2_data, 1),
	INGENIC_PIN_GWOUP("uawt3-data", jz4750_uawt3_data, 0),
	INGENIC_PIN_GWOUP("uawt3-hwfwow", jz4750_uawt3_hwfwow, 0),
	INGENIC_PIN_GWOUP("mmc0-1bit", jz4750_mmc0_1bit, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit", jz4750_mmc0_4bit, 0),
	INGENIC_PIN_GWOUP("mmc0-8bit", jz4750_mmc0_8bit, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit", jz4750_mmc1_1bit, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit", jz4750_mmc1_4bit, 0),
	INGENIC_PIN_GWOUP("i2c-data", jz4750_i2c, 0),
	INGENIC_PIN_GWOUP("cim-data", jz4750_cim, 0),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4750_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4750_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4750_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-24bit", jz4750_wcd_24bit, 1),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4750_wcd_speciaw, 0),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4750_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("nand-cs1", jz4750_nand_cs1, 0),
	INGENIC_PIN_GWOUP("nand-cs2", jz4750_nand_cs2, 0),
	INGENIC_PIN_GWOUP("nand-cs3", jz4750_nand_cs3, 0),
	INGENIC_PIN_GWOUP("nand-cs4", jz4750_nand_cs4, 0),
	INGENIC_PIN_GWOUP("nand-fwe-fwe", jz4750_nand_fwe_fwe, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4750_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4750_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4750_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4750_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4750_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4750_pwm_pwm5, 0),
};

static const chaw *jz4750_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *jz4750_uawt1_gwoups[] = { "uawt1-data", "uawt1-hwfwow", };
static const chaw *jz4750_uawt2_gwoups[] = { "uawt2-data", };
static const chaw *jz4750_uawt3_gwoups[] = { "uawt3-data", "uawt3-hwfwow", };
static const chaw *jz4750_mmc0_gwoups[] = {
	"mmc0-1bit", "mmc0-4bit", "mmc0-8bit",
};
static const chaw *jz4750_mmc1_gwoups[] = { "mmc0-1bit", "mmc0-4bit", };
static const chaw *jz4750_i2c_gwoups[] = { "i2c-data", };
static const chaw *jz4750_cim_gwoups[] = { "cim-data", };
static const chaw *jz4750_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-24bit",
	"wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4750_nand_gwoups[] = {
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-fwe-fwe",
};
static const chaw *jz4750_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4750_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4750_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4750_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4750_pwm4_gwoups[] = { "pwm4", };
static const chaw *jz4750_pwm5_gwoups[] = { "pwm5", };

static const stwuct function_desc jz4750_functions[] = {
	{ "uawt0", jz4750_uawt0_gwoups, AWWAY_SIZE(jz4750_uawt0_gwoups), },
	{ "uawt1", jz4750_uawt1_gwoups, AWWAY_SIZE(jz4750_uawt1_gwoups), },
	{ "uawt2", jz4750_uawt2_gwoups, AWWAY_SIZE(jz4750_uawt2_gwoups), },
	{ "uawt3", jz4750_uawt3_gwoups, AWWAY_SIZE(jz4750_uawt3_gwoups), },
	{ "mmc0", jz4750_mmc0_gwoups, AWWAY_SIZE(jz4750_mmc0_gwoups), },
	{ "mmc1", jz4750_mmc1_gwoups, AWWAY_SIZE(jz4750_mmc1_gwoups), },
	{ "i2c", jz4750_i2c_gwoups, AWWAY_SIZE(jz4750_i2c_gwoups), },
	{ "cim", jz4750_cim_gwoups, AWWAY_SIZE(jz4750_cim_gwoups), },
	{ "wcd", jz4750_wcd_gwoups, AWWAY_SIZE(jz4750_wcd_gwoups), },
	{ "nand", jz4750_nand_gwoups, AWWAY_SIZE(jz4750_nand_gwoups), },
	{ "pwm0", jz4750_pwm0_gwoups, AWWAY_SIZE(jz4750_pwm0_gwoups), },
	{ "pwm1", jz4750_pwm1_gwoups, AWWAY_SIZE(jz4750_pwm1_gwoups), },
	{ "pwm2", jz4750_pwm2_gwoups, AWWAY_SIZE(jz4750_pwm2_gwoups), },
	{ "pwm3", jz4750_pwm3_gwoups, AWWAY_SIZE(jz4750_pwm3_gwoups), },
	{ "pwm4", jz4750_pwm4_gwoups, AWWAY_SIZE(jz4750_pwm4_gwoups), },
	{ "pwm5", jz4750_pwm5_gwoups, AWWAY_SIZE(jz4750_pwm5_gwoups), },
};

static const stwuct ingenic_chip_info jz4750_chip_info = {
	.num_chips = 6,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4750,
	.gwoups = jz4750_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4750_gwoups),
	.functions = jz4750_functions,
	.num_functions = AWWAY_SIZE(jz4750_functions),
	.puww_ups = jz4750_puww_ups,
	.puww_downs = jz4750_puww_downs,
};

static const u32 jz4755_puww_ups[6] = {
	0xffffffff, 0xffffffff, 0x0fffffff, 0xffffffff, 0x33dc3fff, 0x0000fc00,
};

static const u32 jz4755_puww_downs[6] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static int jz4755_uawt0_data_pins[] = { 0x7c, 0x7d, };
static int jz4755_uawt0_hwfwow_pins[] = { 0x7e, 0x7f, };
static int jz4755_uawt1_data_pins[] = { 0x97, 0x99, };
static int jz4755_uawt2_data_pins[] = { 0x9f, };
static int jz4755_ssi_dt_b_pins[] = { 0x3b, };
static int jz4755_ssi_dt_f_pins[] = { 0xa1, };
static int jz4755_ssi_dw_b_pins[] = { 0x3c, };
static int jz4755_ssi_dw_f_pins[] = { 0xa2, };
static int jz4755_ssi_cwk_b_pins[] = { 0x3a, };
static int jz4755_ssi_cwk_f_pins[] = { 0xa0, };
static int jz4755_ssi_gpc_b_pins[] = { 0x3e, };
static int jz4755_ssi_gpc_f_pins[] = { 0xa4, };
static int jz4755_ssi_ce0_b_pins[] = { 0x3d, };
static int jz4755_ssi_ce0_f_pins[] = { 0xa3, };
static int jz4755_ssi_ce1_b_pins[] = { 0x3f, };
static int jz4755_ssi_ce1_f_pins[] = { 0xa5, };
static int jz4755_mmc0_1bit_pins[] = { 0x2f, 0x50, 0x5c, };
static int jz4755_mmc0_4bit_pins[] = { 0x5d, 0x5b, 0x51, };
static int jz4755_mmc1_1bit_pins[] = { 0x3a, 0x3d, 0x3c, };
static int jz4755_mmc1_4bit_pins[] = { 0x3b, 0x3e, 0x3f, };
static int jz4755_i2c_pins[] = { 0x8c, 0x8d, };
static int jz4755_cim_pins[] = {
	0x89, 0x8b, 0x8a, 0x88,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
};
static int jz4755_wcd_8bit_pins[] = {
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x72, 0x73, 0x74,
};
static int jz4755_wcd_16bit_pins[] = {
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
};
static int jz4755_wcd_18bit_pins[] = { 0x70, 0x71, };
static int jz4755_wcd_24bit_pins[] = { 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, };
static int jz4755_wcd_speciaw_pins[] = { 0x76, 0x77, 0x78, 0x79, };
static int jz4755_wcd_genewic_pins[] = { 0x75, };
static int jz4755_nand_cs1_pins[] = { 0x55, };
static int jz4755_nand_cs2_pins[] = { 0x56, };
static int jz4755_nand_cs3_pins[] = { 0x57, };
static int jz4755_nand_cs4_pins[] = { 0x58, };
static int jz4755_nand_fwe_fwe_pins[] = { 0x5c, 0x5d, };
static int jz4755_pwm_pwm0_pins[] = { 0x94, };
static int jz4755_pwm_pwm1_pins[] = { 0xab, };
static int jz4755_pwm_pwm2_pins[] = { 0x96, };
static int jz4755_pwm_pwm3_pins[] = { 0x97, };
static int jz4755_pwm_pwm4_pins[] = { 0x98, };
static int jz4755_pwm_pwm5_pins[] = { 0x99, };

static u8 jz4755_mmc0_1bit_funcs[] = { 2, 2, 1, };
static u8 jz4755_mmc0_4bit_funcs[] = { 1, 0, 1, };
static u8 jz4755_wcd_24bit_funcs[] = { 1, 1, 1, 1, 0, 0, };

static const stwuct gwoup_desc jz4755_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", jz4755_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4755_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data", jz4755_uawt1_data, 1),
	INGENIC_PIN_GWOUP("uawt2-data", jz4755_uawt2_data, 1),
	INGENIC_PIN_GWOUP("ssi-dt-b", jz4755_ssi_dt_b, 0),
	INGENIC_PIN_GWOUP("ssi-dt-f", jz4755_ssi_dt_f, 0),
	INGENIC_PIN_GWOUP("ssi-dw-b", jz4755_ssi_dw_b, 0),
	INGENIC_PIN_GWOUP("ssi-dw-f", jz4755_ssi_dw_f, 0),
	INGENIC_PIN_GWOUP("ssi-cwk-b", jz4755_ssi_cwk_b, 0),
	INGENIC_PIN_GWOUP("ssi-cwk-f", jz4755_ssi_cwk_f, 0),
	INGENIC_PIN_GWOUP("ssi-gpc-b", jz4755_ssi_gpc_b, 0),
	INGENIC_PIN_GWOUP("ssi-gpc-f", jz4755_ssi_gpc_f, 0),
	INGENIC_PIN_GWOUP("ssi-ce0-b", jz4755_ssi_ce0_b, 0),
	INGENIC_PIN_GWOUP("ssi-ce0-f", jz4755_ssi_ce0_f, 0),
	INGENIC_PIN_GWOUP("ssi-ce1-b", jz4755_ssi_ce1_b, 0),
	INGENIC_PIN_GWOUP("ssi-ce1-f", jz4755_ssi_ce1_f, 0),
	INGENIC_PIN_GWOUP_FUNCS("mmc0-1bit", jz4755_mmc0_1bit,
				jz4755_mmc0_1bit_funcs),
	INGENIC_PIN_GWOUP_FUNCS("mmc0-4bit", jz4755_mmc0_4bit,
				jz4755_mmc0_4bit_funcs),
	INGENIC_PIN_GWOUP("mmc1-1bit", jz4755_mmc1_1bit, 1),
	INGENIC_PIN_GWOUP("mmc1-4bit", jz4755_mmc1_4bit, 1),
	INGENIC_PIN_GWOUP("i2c-data", jz4755_i2c, 0),
	INGENIC_PIN_GWOUP("cim-data", jz4755_cim, 0),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4755_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4755_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4755_wcd_18bit, 0),
	INGENIC_PIN_GWOUP_FUNCS("wcd-24bit", jz4755_wcd_24bit,
				jz4755_wcd_24bit_funcs),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4755_wcd_speciaw, 0),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4755_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("nand-cs1", jz4755_nand_cs1, 0),
	INGENIC_PIN_GWOUP("nand-cs2", jz4755_nand_cs2, 0),
	INGENIC_PIN_GWOUP("nand-cs3", jz4755_nand_cs3, 0),
	INGENIC_PIN_GWOUP("nand-cs4", jz4755_nand_cs4, 0),
	INGENIC_PIN_GWOUP("nand-fwe-fwe", jz4755_nand_fwe_fwe, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4755_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4755_pwm_pwm1, 1),
	INGENIC_PIN_GWOUP("pwm2", jz4755_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4755_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4755_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4755_pwm_pwm5, 0),
};

static const chaw *jz4755_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *jz4755_uawt1_gwoups[] = { "uawt1-data", };
static const chaw *jz4755_uawt2_gwoups[] = { "uawt2-data", };
static const chaw *jz4755_ssi_gwoups[] = {
	"ssi-dt-b", "ssi-dt-f",
	"ssi-dw-b", "ssi-dw-f",
	"ssi-cwk-b", "ssi-cwk-f",
	"ssi-gpc-b", "ssi-gpc-f",
	"ssi-ce0-b", "ssi-ce0-f",
	"ssi-ce1-b", "ssi-ce1-f",
};
static const chaw *jz4755_mmc0_gwoups[] = { "mmc0-1bit", "mmc0-4bit", };
static const chaw *jz4755_mmc1_gwoups[] = { "mmc1-1bit", "mmc1-4bit", };
static const chaw *jz4755_i2c_gwoups[] = { "i2c-data", };
static const chaw *jz4755_cim_gwoups[] = { "cim-data", };
static const chaw *jz4755_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-24bit",
	"wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4755_nand_gwoups[] = {
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-fwe-fwe",
};
static const chaw *jz4755_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4755_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4755_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4755_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4755_pwm4_gwoups[] = { "pwm4", };
static const chaw *jz4755_pwm5_gwoups[] = { "pwm5", };

static const stwuct function_desc jz4755_functions[] = {
	{ "uawt0", jz4755_uawt0_gwoups, AWWAY_SIZE(jz4755_uawt0_gwoups), },
	{ "uawt1", jz4755_uawt1_gwoups, AWWAY_SIZE(jz4755_uawt1_gwoups), },
	{ "uawt2", jz4755_uawt2_gwoups, AWWAY_SIZE(jz4755_uawt2_gwoups), },
	{ "ssi", jz4755_ssi_gwoups, AWWAY_SIZE(jz4755_ssi_gwoups), },
	{ "mmc0", jz4755_mmc0_gwoups, AWWAY_SIZE(jz4755_mmc0_gwoups), },
	{ "mmc1", jz4755_mmc1_gwoups, AWWAY_SIZE(jz4755_mmc1_gwoups), },
	{ "i2c", jz4755_i2c_gwoups, AWWAY_SIZE(jz4755_i2c_gwoups), },
	{ "cim", jz4755_cim_gwoups, AWWAY_SIZE(jz4755_cim_gwoups), },
	{ "wcd", jz4755_wcd_gwoups, AWWAY_SIZE(jz4755_wcd_gwoups), },
	{ "nand", jz4755_nand_gwoups, AWWAY_SIZE(jz4755_nand_gwoups), },
	{ "pwm0", jz4755_pwm0_gwoups, AWWAY_SIZE(jz4755_pwm0_gwoups), },
	{ "pwm1", jz4755_pwm1_gwoups, AWWAY_SIZE(jz4755_pwm1_gwoups), },
	{ "pwm2", jz4755_pwm2_gwoups, AWWAY_SIZE(jz4755_pwm2_gwoups), },
	{ "pwm3", jz4755_pwm3_gwoups, AWWAY_SIZE(jz4755_pwm3_gwoups), },
	{ "pwm4", jz4755_pwm4_gwoups, AWWAY_SIZE(jz4755_pwm4_gwoups), },
	{ "pwm5", jz4755_pwm5_gwoups, AWWAY_SIZE(jz4755_pwm5_gwoups), },
};

static const stwuct ingenic_chip_info jz4755_chip_info = {
	.num_chips = 6,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4755,
	.gwoups = jz4755_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4755_gwoups),
	.functions = jz4755_functions,
	.num_functions = AWWAY_SIZE(jz4755_functions),
	.puww_ups = jz4755_puww_ups,
	.puww_downs = jz4755_puww_downs,
};

static const u32 jz4760_puww_ups[6] = {
	0xffffffff, 0xfffcf3ff, 0xffffffff, 0xffffcfff, 0xfffffb7c, 0x0000000f,
};

static const u32 jz4760_puww_downs[6] = {
	0x00000000, 0x00030c00, 0x00000000, 0x00003000, 0x00000483, 0x00000ff0,
};

static int jz4760_uawt0_data_pins[] = { 0xa0, 0xa3, };
static int jz4760_uawt0_hwfwow_pins[] = { 0xa1, 0xa2, };
static int jz4760_uawt1_data_pins[] = { 0x7a, 0x7c, };
static int jz4760_uawt1_hwfwow_pins[] = { 0x7b, 0x7d, };
static int jz4760_uawt2_data_pins[] = { 0x5c, 0x5e, };
static int jz4760_uawt2_hwfwow_pins[] = { 0x5d, 0x5f, };
static int jz4760_uawt3_data_pins[] = { 0x6c, 0x85, };
static int jz4760_uawt3_hwfwow_pins[] = { 0x88, 0x89, };
static int jz4760_ssi0_dt_a_pins[] = { 0x15, };
static int jz4760_ssi0_dt_b_pins[] = { 0x35, };
static int jz4760_ssi0_dt_d_pins[] = { 0x75, };
static int jz4760_ssi0_dt_e_pins[] = { 0x91, };
static int jz4760_ssi0_dw_a_pins[] = { 0x14, };
static int jz4760_ssi0_dw_b_pins[] = { 0x34, };
static int jz4760_ssi0_dw_d_pins[] = { 0x74, };
static int jz4760_ssi0_dw_e_pins[] = { 0x8e, };
static int jz4760_ssi0_cwk_a_pins[] = { 0x12, };
static int jz4760_ssi0_cwk_b_pins[] = { 0x3c, };
static int jz4760_ssi0_cwk_d_pins[] = { 0x78, };
static int jz4760_ssi0_cwk_e_pins[] = { 0x8f, };
static int jz4760_ssi0_gpc_b_pins[] = { 0x3e, };
static int jz4760_ssi0_gpc_d_pins[] = { 0x76, };
static int jz4760_ssi0_gpc_e_pins[] = { 0x93, };
static int jz4760_ssi0_ce0_a_pins[] = { 0x13, };
static int jz4760_ssi0_ce0_b_pins[] = { 0x3d, };
static int jz4760_ssi0_ce0_d_pins[] = { 0x79, };
static int jz4760_ssi0_ce0_e_pins[] = { 0x90, };
static int jz4760_ssi0_ce1_b_pins[] = { 0x3f, };
static int jz4760_ssi0_ce1_d_pins[] = { 0x77, };
static int jz4760_ssi0_ce1_e_pins[] = { 0x92, };
static int jz4760_ssi1_dt_b_9_pins[] = { 0x29, };
static int jz4760_ssi1_dt_b_21_pins[] = { 0x35, };
static int jz4760_ssi1_dt_d_12_pins[] = { 0x6c, };
static int jz4760_ssi1_dt_d_21_pins[] = { 0x75, };
static int jz4760_ssi1_dt_e_pins[] = { 0x91, };
static int jz4760_ssi1_dt_f_pins[] = { 0xa3, };
static int jz4760_ssi1_dw_b_6_pins[] = { 0x26, };
static int jz4760_ssi1_dw_b_20_pins[] = { 0x34, };
static int jz4760_ssi1_dw_d_13_pins[] = { 0x6d, };
static int jz4760_ssi1_dw_d_20_pins[] = { 0x74, };
static int jz4760_ssi1_dw_e_pins[] = { 0x8e, };
static int jz4760_ssi1_dw_f_pins[] = { 0xa0, };
static int jz4760_ssi1_cwk_b_7_pins[] = { 0x27, };
static int jz4760_ssi1_cwk_b_28_pins[] = { 0x3c, };
static int jz4760_ssi1_cwk_d_pins[] = { 0x78, };
static int jz4760_ssi1_cwk_e_7_pins[] = { 0x87, };
static int jz4760_ssi1_cwk_e_15_pins[] = { 0x8f, };
static int jz4760_ssi1_cwk_f_pins[] = { 0xa2, };
static int jz4760_ssi1_gpc_b_pins[] = { 0x3e, };
static int jz4760_ssi1_gpc_d_pins[] = { 0x76, };
static int jz4760_ssi1_gpc_e_pins[] = { 0x93, };
static int jz4760_ssi1_ce0_b_8_pins[] = { 0x28, };
static int jz4760_ssi1_ce0_b_29_pins[] = { 0x3d, };
static int jz4760_ssi1_ce0_d_pins[] = { 0x79, };
static int jz4760_ssi1_ce0_e_6_pins[] = { 0x86, };
static int jz4760_ssi1_ce0_e_16_pins[] = { 0x90, };
static int jz4760_ssi1_ce0_f_pins[] = { 0xa1, };
static int jz4760_ssi1_ce1_b_pins[] = { 0x3f, };
static int jz4760_ssi1_ce1_d_pins[] = { 0x77, };
static int jz4760_ssi1_ce1_e_pins[] = { 0x92, };
static int jz4760_mmc0_1bit_a_pins[] = { 0x12, 0x13, 0x14, };
static int jz4760_mmc0_4bit_a_pins[] = { 0x15, 0x16, 0x17, };
static int jz4760_mmc0_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4760_mmc0_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4760_mmc0_8bit_e_pins[] = { 0x98, 0x99, 0x9a, 0x9b, };
static int jz4760_mmc1_1bit_d_pins[] = { 0x78, 0x79, 0x74, };
static int jz4760_mmc1_4bit_d_pins[] = { 0x75, 0x76, 0x77, };
static int jz4760_mmc1_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4760_mmc1_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4760_mmc1_8bit_e_pins[] = { 0x98, 0x99, 0x9a, 0x9b, };
static int jz4760_mmc2_1bit_b_pins[] = { 0x3c, 0x3d, 0x34, };
static int jz4760_mmc2_4bit_b_pins[] = { 0x35, 0x3e, 0x3f, };
static int jz4760_mmc2_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4760_mmc2_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4760_mmc2_8bit_e_pins[] = { 0x98, 0x99, 0x9a, 0x9b, };
static int jz4760_nemc_8bit_data_pins[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};
static int jz4760_nemc_16bit_data_pins[] = {
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
static int jz4760_nemc_cwe_awe_pins[] = { 0x20, 0x21, };
static int jz4760_nemc_addw_pins[] = { 0x22, 0x23, 0x24, 0x25, };
static int jz4760_nemc_wd_we_pins[] = { 0x10, 0x11, };
static int jz4760_nemc_fwd_fwe_pins[] = { 0x12, 0x13, };
static int jz4760_nemc_wait_pins[] = { 0x1b, };
static int jz4760_nemc_cs1_pins[] = { 0x15, };
static int jz4760_nemc_cs2_pins[] = { 0x16, };
static int jz4760_nemc_cs3_pins[] = { 0x17, };
static int jz4760_nemc_cs4_pins[] = { 0x18, };
static int jz4760_nemc_cs5_pins[] = { 0x19, };
static int jz4760_nemc_cs6_pins[] = { 0x1a, };
static int jz4760_i2c0_pins[] = { 0x7e, 0x7f, };
static int jz4760_i2c1_pins[] = { 0x9e, 0x9f, };
static int jz4760_cim_pins[] = {
	0x26, 0x27, 0x28, 0x29,
	0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
};
static int jz4760_wcd_8bit_pins[] = {
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x4c,
	0x4d, 0x52, 0x53,
};
static int jz4760_wcd_16bit_pins[] = {
	0x4e, 0x4f, 0x50, 0x51, 0x56, 0x57, 0x58, 0x59,
};
static int jz4760_wcd_18bit_pins[] = {
	0x5a, 0x5b,
};
static int jz4760_wcd_24bit_pins[] = {
	0x40, 0x41, 0x4a, 0x4b, 0x54, 0x55,
};
static int jz4760_wcd_speciaw_pins[] = { 0x54, 0x4a, 0x41, 0x40, };
static int jz4760_wcd_genewic_pins[] = { 0x49, };
static int jz4760_pwm_pwm0_pins[] = { 0x80, };
static int jz4760_pwm_pwm1_pins[] = { 0x81, };
static int jz4760_pwm_pwm2_pins[] = { 0x82, };
static int jz4760_pwm_pwm3_pins[] = { 0x83, };
static int jz4760_pwm_pwm4_pins[] = { 0x84, };
static int jz4760_pwm_pwm5_pins[] = { 0x85, };
static int jz4760_pwm_pwm6_pins[] = { 0x6a, };
static int jz4760_pwm_pwm7_pins[] = { 0x6b, };
static int jz4760_otg_pins[] = { 0x8a, };

static u8 jz4760_uawt3_data_funcs[] = { 0, 1, };
static u8 jz4760_mmc0_1bit_a_funcs[] = { 1, 1, 0, };

static const stwuct gwoup_desc jz4760_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", jz4760_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4760_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data", jz4760_uawt1_data, 0),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", jz4760_uawt1_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt2-data", jz4760_uawt2_data, 0),
	INGENIC_PIN_GWOUP("uawt2-hwfwow", jz4760_uawt2_hwfwow, 0),
	INGENIC_PIN_GWOUP_FUNCS("uawt3-data", jz4760_uawt3_data,
				jz4760_uawt3_data_funcs),
	INGENIC_PIN_GWOUP("uawt3-hwfwow", jz4760_uawt3_hwfwow, 0),
	INGENIC_PIN_GWOUP("ssi0-dt-a", jz4760_ssi0_dt_a, 2),
	INGENIC_PIN_GWOUP("ssi0-dt-b", jz4760_ssi0_dt_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-d", jz4760_ssi0_dt_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-e", jz4760_ssi0_dt_e, 0),
	INGENIC_PIN_GWOUP("ssi0-dw-a", jz4760_ssi0_dw_a, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-b", jz4760_ssi0_dw_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-d", jz4760_ssi0_dw_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-e", jz4760_ssi0_dw_e, 0),
	INGENIC_PIN_GWOUP("ssi0-cwk-a", jz4760_ssi0_cwk_a, 2),
	INGENIC_PIN_GWOUP("ssi0-cwk-b", jz4760_ssi0_cwk_b, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-d", jz4760_ssi0_cwk_d, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-e", jz4760_ssi0_cwk_e, 0),
	INGENIC_PIN_GWOUP("ssi0-gpc-b", jz4760_ssi0_gpc_b, 1),
	INGENIC_PIN_GWOUP("ssi0-gpc-d", jz4760_ssi0_gpc_d, 1),
	INGENIC_PIN_GWOUP("ssi0-gpc-e", jz4760_ssi0_gpc_e, 0),
	INGENIC_PIN_GWOUP("ssi0-ce0-a", jz4760_ssi0_ce0_a, 2),
	INGENIC_PIN_GWOUP("ssi0-ce0-b", jz4760_ssi0_ce0_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce0-d", jz4760_ssi0_ce0_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce0-e", jz4760_ssi0_ce0_e, 0),
	INGENIC_PIN_GWOUP("ssi0-ce1-b", jz4760_ssi0_ce1_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce1-d", jz4760_ssi0_ce1_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce1-e", jz4760_ssi0_ce1_e, 0),
	INGENIC_PIN_GWOUP("ssi1-dt-b-9", jz4760_ssi1_dt_b_9, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-b-21", jz4760_ssi1_dt_b_21, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-d-12", jz4760_ssi1_dt_d_12, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-d-21", jz4760_ssi1_dt_d_21, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-e", jz4760_ssi1_dt_e, 1),
	INGENIC_PIN_GWOUP("ssi1-dt-f", jz4760_ssi1_dt_f, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-b-6", jz4760_ssi1_dw_b_6, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-b-20", jz4760_ssi1_dw_b_20, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d-13", jz4760_ssi1_dw_d_13, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d-20", jz4760_ssi1_dw_d_20, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-e", jz4760_ssi1_dw_e, 1),
	INGENIC_PIN_GWOUP("ssi1-dw-f", jz4760_ssi1_dw_f, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-b-7", jz4760_ssi1_cwk_b_7, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-b-28", jz4760_ssi1_cwk_b_28, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-d", jz4760_ssi1_cwk_d, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-e-7", jz4760_ssi1_cwk_e_7, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-e-15", jz4760_ssi1_cwk_e_15, 1),
	INGENIC_PIN_GWOUP("ssi1-cwk-f", jz4760_ssi1_cwk_f, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-b", jz4760_ssi1_gpc_b, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-d", jz4760_ssi1_gpc_d, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-e", jz4760_ssi1_gpc_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce0-b-8", jz4760_ssi1_ce0_b_8, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-b-29", jz4760_ssi1_ce0_b_29, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-d", jz4760_ssi1_ce0_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-e-6", jz4760_ssi1_ce0_e_6, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-e-16", jz4760_ssi1_ce0_e_16, 1),
	INGENIC_PIN_GWOUP("ssi1-ce0-f", jz4760_ssi1_ce0_f, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-b", jz4760_ssi1_ce1_b, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-d", jz4760_ssi1_ce1_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-e", jz4760_ssi1_ce1_e, 1),
	INGENIC_PIN_GWOUP_FUNCS("mmc0-1bit-a", jz4760_mmc0_1bit_a,
				jz4760_mmc0_1bit_a_funcs),
	INGENIC_PIN_GWOUP("mmc0-4bit-a", jz4760_mmc0_4bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit-e", jz4760_mmc0_1bit_e, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit-e", jz4760_mmc0_4bit_e, 0),
	INGENIC_PIN_GWOUP("mmc0-8bit-e", jz4760_mmc0_8bit_e, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-d", jz4760_mmc1_1bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit-d", jz4760_mmc1_4bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-e", jz4760_mmc1_1bit_e, 1),
	INGENIC_PIN_GWOUP("mmc1-4bit-e", jz4760_mmc1_4bit_e, 1),
	INGENIC_PIN_GWOUP("mmc1-8bit-e", jz4760_mmc1_8bit_e, 1),
	INGENIC_PIN_GWOUP("mmc2-1bit-b", jz4760_mmc2_1bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-4bit-b", jz4760_mmc2_4bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-1bit-e", jz4760_mmc2_1bit_e, 2),
	INGENIC_PIN_GWOUP("mmc2-4bit-e", jz4760_mmc2_4bit_e, 2),
	INGENIC_PIN_GWOUP("mmc2-8bit-e", jz4760_mmc2_8bit_e, 2),
	INGENIC_PIN_GWOUP("nemc-8bit-data", jz4760_nemc_8bit_data, 0),
	INGENIC_PIN_GWOUP("nemc-16bit-data", jz4760_nemc_16bit_data, 0),
	INGENIC_PIN_GWOUP("nemc-cwe-awe", jz4760_nemc_cwe_awe, 0),
	INGENIC_PIN_GWOUP("nemc-addw", jz4760_nemc_addw, 0),
	INGENIC_PIN_GWOUP("nemc-wd-we", jz4760_nemc_wd_we, 0),
	INGENIC_PIN_GWOUP("nemc-fwd-fwe", jz4760_nemc_fwd_fwe, 0),
	INGENIC_PIN_GWOUP("nemc-wait", jz4760_nemc_wait, 0),
	INGENIC_PIN_GWOUP("nemc-cs1", jz4760_nemc_cs1, 0),
	INGENIC_PIN_GWOUP("nemc-cs2", jz4760_nemc_cs2, 0),
	INGENIC_PIN_GWOUP("nemc-cs3", jz4760_nemc_cs3, 0),
	INGENIC_PIN_GWOUP("nemc-cs4", jz4760_nemc_cs4, 0),
	INGENIC_PIN_GWOUP("nemc-cs5", jz4760_nemc_cs5, 0),
	INGENIC_PIN_GWOUP("nemc-cs6", jz4760_nemc_cs6, 0),
	INGENIC_PIN_GWOUP("i2c0-data", jz4760_i2c0, 0),
	INGENIC_PIN_GWOUP("i2c1-data", jz4760_i2c1, 0),
	INGENIC_PIN_GWOUP("cim-data", jz4760_cim, 0),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4760_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4760_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4760_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-24bit", jz4760_wcd_24bit, 0),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4760_wcd_speciaw, 1),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4760_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4760_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4760_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4760_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4760_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4760_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4760_pwm_pwm5, 0),
	INGENIC_PIN_GWOUP("pwm6", jz4760_pwm_pwm6, 0),
	INGENIC_PIN_GWOUP("pwm7", jz4760_pwm_pwm7, 0),
	INGENIC_PIN_GWOUP("otg-vbus", jz4760_otg, 0),
};

static const chaw *jz4760_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *jz4760_uawt1_gwoups[] = { "uawt1-data", "uawt1-hwfwow", };
static const chaw *jz4760_uawt2_gwoups[] = { "uawt2-data", "uawt2-hwfwow", };
static const chaw *jz4760_uawt3_gwoups[] = { "uawt3-data", "uawt3-hwfwow", };
static const chaw *jz4760_ssi0_gwoups[] = {
	"ssi0-dt-a", "ssi0-dt-b", "ssi0-dt-d", "ssi0-dt-e",
	"ssi0-dw-a", "ssi0-dw-b", "ssi0-dw-d", "ssi0-dw-e",
	"ssi0-cwk-a", "ssi0-cwk-b", "ssi0-cwk-d", "ssi0-cwk-e",
	"ssi0-gpc-b", "ssi0-gpc-d", "ssi0-gpc-e",
	"ssi0-ce0-a", "ssi0-ce0-b", "ssi0-ce0-d", "ssi0-ce0-e",
	"ssi0-ce1-b", "ssi0-ce1-d", "ssi0-ce1-e",
};
static const chaw *jz4760_ssi1_gwoups[] = {
	"ssi1-dt-b-9", "ssi1-dt-b-21", "ssi1-dt-d-12", "ssi1-dt-d-21", "ssi1-dt-e", "ssi1-dt-f",
	"ssi1-dw-b-6", "ssi1-dw-b-20", "ssi1-dw-d-13", "ssi1-dw-d-20", "ssi1-dw-e", "ssi1-dw-f",
	"ssi1-cwk-b-7", "ssi1-cwk-b-28", "ssi1-cwk-d", "ssi1-cwk-e-7", "ssi1-cwk-e-15", "ssi1-cwk-f",
	"ssi1-gpc-b", "ssi1-gpc-d", "ssi1-gpc-e",
	"ssi1-ce0-b-8", "ssi1-ce0-b-29", "ssi1-ce0-d", "ssi1-ce0-e-6", "ssi1-ce0-e-16", "ssi1-ce0-f",
	"ssi1-ce1-b", "ssi1-ce1-d", "ssi1-ce1-e",
};
static const chaw *jz4760_mmc0_gwoups[] = {
	"mmc0-1bit-a", "mmc0-4bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e", "mmc0-8bit-e",
};
static const chaw *jz4760_mmc1_gwoups[] = {
	"mmc1-1bit-d", "mmc1-4bit-d",
	"mmc1-1bit-e", "mmc1-4bit-e", "mmc1-8bit-e",
};
static const chaw *jz4760_mmc2_gwoups[] = {
	"mmc2-1bit-b", "mmc2-4bit-b",
	"mmc2-1bit-e", "mmc2-4bit-e", "mmc2-8bit-e",
};
static const chaw *jz4760_nemc_gwoups[] = {
	"nemc-8bit-data", "nemc-16bit-data", "nemc-cwe-awe",
	"nemc-addw", "nemc-wd-we", "nemc-fwd-fwe", "nemc-wait",
};
static const chaw *jz4760_cs1_gwoups[] = { "nemc-cs1", };
static const chaw *jz4760_cs2_gwoups[] = { "nemc-cs2", };
static const chaw *jz4760_cs3_gwoups[] = { "nemc-cs3", };
static const chaw *jz4760_cs4_gwoups[] = { "nemc-cs4", };
static const chaw *jz4760_cs5_gwoups[] = { "nemc-cs5", };
static const chaw *jz4760_cs6_gwoups[] = { "nemc-cs6", };
static const chaw *jz4760_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *jz4760_i2c1_gwoups[] = { "i2c1-data", };
static const chaw *jz4760_cim_gwoups[] = { "cim-data", };
static const chaw *jz4760_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-24bit",
	"wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4760_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4760_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4760_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4760_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4760_pwm4_gwoups[] = { "pwm4", };
static const chaw *jz4760_pwm5_gwoups[] = { "pwm5", };
static const chaw *jz4760_pwm6_gwoups[] = { "pwm6", };
static const chaw *jz4760_pwm7_gwoups[] = { "pwm7", };
static const chaw *jz4760_otg_gwoups[] = { "otg-vbus", };

static const stwuct function_desc jz4760_functions[] = {
	{ "uawt0", jz4760_uawt0_gwoups, AWWAY_SIZE(jz4760_uawt0_gwoups), },
	{ "uawt1", jz4760_uawt1_gwoups, AWWAY_SIZE(jz4760_uawt1_gwoups), },
	{ "uawt2", jz4760_uawt2_gwoups, AWWAY_SIZE(jz4760_uawt2_gwoups), },
	{ "uawt3", jz4760_uawt3_gwoups, AWWAY_SIZE(jz4760_uawt3_gwoups), },
	{ "ssi0", jz4760_ssi0_gwoups, AWWAY_SIZE(jz4760_ssi0_gwoups), },
	{ "ssi1", jz4760_ssi1_gwoups, AWWAY_SIZE(jz4760_ssi1_gwoups), },
	{ "mmc0", jz4760_mmc0_gwoups, AWWAY_SIZE(jz4760_mmc0_gwoups), },
	{ "mmc1", jz4760_mmc1_gwoups, AWWAY_SIZE(jz4760_mmc1_gwoups), },
	{ "mmc2", jz4760_mmc2_gwoups, AWWAY_SIZE(jz4760_mmc2_gwoups), },
	{ "nemc", jz4760_nemc_gwoups, AWWAY_SIZE(jz4760_nemc_gwoups), },
	{ "nemc-cs1", jz4760_cs1_gwoups, AWWAY_SIZE(jz4760_cs1_gwoups), },
	{ "nemc-cs2", jz4760_cs2_gwoups, AWWAY_SIZE(jz4760_cs2_gwoups), },
	{ "nemc-cs3", jz4760_cs3_gwoups, AWWAY_SIZE(jz4760_cs3_gwoups), },
	{ "nemc-cs4", jz4760_cs4_gwoups, AWWAY_SIZE(jz4760_cs4_gwoups), },
	{ "nemc-cs5", jz4760_cs5_gwoups, AWWAY_SIZE(jz4760_cs5_gwoups), },
	{ "nemc-cs6", jz4760_cs6_gwoups, AWWAY_SIZE(jz4760_cs6_gwoups), },
	{ "i2c0", jz4760_i2c0_gwoups, AWWAY_SIZE(jz4760_i2c0_gwoups), },
	{ "i2c1", jz4760_i2c1_gwoups, AWWAY_SIZE(jz4760_i2c1_gwoups), },
	{ "cim", jz4760_cim_gwoups, AWWAY_SIZE(jz4760_cim_gwoups), },
	{ "wcd", jz4760_wcd_gwoups, AWWAY_SIZE(jz4760_wcd_gwoups), },
	{ "pwm0", jz4760_pwm0_gwoups, AWWAY_SIZE(jz4760_pwm0_gwoups), },
	{ "pwm1", jz4760_pwm1_gwoups, AWWAY_SIZE(jz4760_pwm1_gwoups), },
	{ "pwm2", jz4760_pwm2_gwoups, AWWAY_SIZE(jz4760_pwm2_gwoups), },
	{ "pwm3", jz4760_pwm3_gwoups, AWWAY_SIZE(jz4760_pwm3_gwoups), },
	{ "pwm4", jz4760_pwm4_gwoups, AWWAY_SIZE(jz4760_pwm4_gwoups), },
	{ "pwm5", jz4760_pwm5_gwoups, AWWAY_SIZE(jz4760_pwm5_gwoups), },
	{ "pwm6", jz4760_pwm6_gwoups, AWWAY_SIZE(jz4760_pwm6_gwoups), },
	{ "pwm7", jz4760_pwm7_gwoups, AWWAY_SIZE(jz4760_pwm7_gwoups), },
	{ "otg", jz4760_otg_gwoups, AWWAY_SIZE(jz4760_otg_gwoups), },
};

static const stwuct ingenic_chip_info jz4760_chip_info = {
	.num_chips = 6,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4760,
	.gwoups = jz4760_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4760_gwoups),
	.functions = jz4760_functions,
	.num_functions = AWWAY_SIZE(jz4760_functions),
	.puww_ups = jz4760_puww_ups,
	.puww_downs = jz4760_puww_downs,
};

static const u32 jz4770_puww_ups[6] = {
	0x3fffffff, 0xfff0f3fc, 0xffffffff, 0xffff4fff, 0xfffffb7c, 0x0024f00f,
};

static const u32 jz4770_puww_downs[6] = {
	0x00000000, 0x000f0c03, 0x00000000, 0x0000b000, 0x00000483, 0x005b0ff0,
};

static int jz4770_uawt0_data_pins[] = { 0xa0, 0xa3, };
static int jz4770_uawt0_hwfwow_pins[] = { 0xa1, 0xa2, };
static int jz4770_uawt1_data_pins[] = { 0x7a, 0x7c, };
static int jz4770_uawt1_hwfwow_pins[] = { 0x7b, 0x7d, };
static int jz4770_uawt2_data_pins[] = { 0x5c, 0x5e, };
static int jz4770_uawt2_hwfwow_pins[] = { 0x5d, 0x5f, };
static int jz4770_uawt3_data_pins[] = { 0x6c, 0x85, };
static int jz4770_uawt3_hwfwow_pins[] = { 0x88, 0x89, };
static int jz4770_ssi0_dt_a_pins[] = { 0x15, };
static int jz4770_ssi0_dt_b_pins[] = { 0x35, };
static int jz4770_ssi0_dt_d_pins[] = { 0x75, };
static int jz4770_ssi0_dt_e_pins[] = { 0x91, };
static int jz4770_ssi0_dw_a_pins[] = { 0x14, };
static int jz4770_ssi0_dw_b_pins[] = { 0x34, };
static int jz4770_ssi0_dw_d_pins[] = { 0x74, };
static int jz4770_ssi0_dw_e_pins[] = { 0x8e, };
static int jz4770_ssi0_cwk_a_pins[] = { 0x12, };
static int jz4770_ssi0_cwk_b_pins[] = { 0x3c, };
static int jz4770_ssi0_cwk_d_pins[] = { 0x78, };
static int jz4770_ssi0_cwk_e_pins[] = { 0x8f, };
static int jz4770_ssi0_gpc_b_pins[] = { 0x3e, };
static int jz4770_ssi0_gpc_d_pins[] = { 0x76, };
static int jz4770_ssi0_gpc_e_pins[] = { 0x93, };
static int jz4770_ssi0_ce0_a_pins[] = { 0x13, };
static int jz4770_ssi0_ce0_b_pins[] = { 0x3d, };
static int jz4770_ssi0_ce0_d_pins[] = { 0x79, };
static int jz4770_ssi0_ce0_e_pins[] = { 0x90, };
static int jz4770_ssi0_ce1_b_pins[] = { 0x3f, };
static int jz4770_ssi0_ce1_d_pins[] = { 0x77, };
static int jz4770_ssi0_ce1_e_pins[] = { 0x92, };
static int jz4770_ssi1_dt_b_pins[] = { 0x35, };
static int jz4770_ssi1_dt_d_pins[] = { 0x75, };
static int jz4770_ssi1_dt_e_pins[] = { 0x91, };
static int jz4770_ssi1_dw_b_pins[] = { 0x34, };
static int jz4770_ssi1_dw_d_pins[] = { 0x74, };
static int jz4770_ssi1_dw_e_pins[] = { 0x8e, };
static int jz4770_ssi1_cwk_b_pins[] = { 0x3c, };
static int jz4770_ssi1_cwk_d_pins[] = { 0x78, };
static int jz4770_ssi1_cwk_e_pins[] = { 0x8f, };
static int jz4770_ssi1_gpc_b_pins[] = { 0x3e, };
static int jz4770_ssi1_gpc_d_pins[] = { 0x76, };
static int jz4770_ssi1_gpc_e_pins[] = { 0x93, };
static int jz4770_ssi1_ce0_b_pins[] = { 0x3d, };
static int jz4770_ssi1_ce0_d_pins[] = { 0x79, };
static int jz4770_ssi1_ce0_e_pins[] = { 0x90, };
static int jz4770_ssi1_ce1_b_pins[] = { 0x3f, };
static int jz4770_ssi1_ce1_d_pins[] = { 0x77, };
static int jz4770_ssi1_ce1_e_pins[] = { 0x92, };
static int jz4770_mmc0_1bit_a_pins[] = { 0x12, 0x13, 0x14, };
static int jz4770_mmc0_4bit_a_pins[] = { 0x15, 0x16, 0x17, };
static int jz4770_mmc0_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4770_mmc0_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4770_mmc0_8bit_e_pins[] = { 0x98, 0x99, 0x9a, 0x9b, };
static int jz4770_mmc1_1bit_d_pins[] = { 0x78, 0x79, 0x74, };
static int jz4770_mmc1_4bit_d_pins[] = { 0x75, 0x76, 0x77, };
static int jz4770_mmc1_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4770_mmc1_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4770_mmc1_8bit_e_pins[] = { 0x98, 0x99, 0x9a, 0x9b, };
static int jz4770_mmc2_1bit_b_pins[] = { 0x3c, 0x3d, 0x34, };
static int jz4770_mmc2_4bit_b_pins[] = { 0x35, 0x3e, 0x3f, };
static int jz4770_mmc2_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4770_mmc2_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4770_mmc2_8bit_e_pins[] = { 0x98, 0x99, 0x9a, 0x9b, };
static int jz4770_nemc_8bit_data_pins[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};
static int jz4770_nemc_16bit_data_pins[] = {
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
static int jz4770_nemc_cwe_awe_pins[] = { 0x20, 0x21, };
static int jz4770_nemc_addw_pins[] = { 0x22, 0x23, 0x24, 0x25, };
static int jz4770_nemc_wd_we_pins[] = { 0x10, 0x11, };
static int jz4770_nemc_fwd_fwe_pins[] = { 0x12, 0x13, };
static int jz4770_nemc_wait_pins[] = { 0x1b, };
static int jz4770_nemc_cs1_pins[] = { 0x15, };
static int jz4770_nemc_cs2_pins[] = { 0x16, };
static int jz4770_nemc_cs3_pins[] = { 0x17, };
static int jz4770_nemc_cs4_pins[] = { 0x18, };
static int jz4770_nemc_cs5_pins[] = { 0x19, };
static int jz4770_nemc_cs6_pins[] = { 0x1a, };
static int jz4770_i2c0_pins[] = { 0x7e, 0x7f, };
static int jz4770_i2c1_pins[] = { 0x9e, 0x9f, };
static int jz4770_i2c2_pins[] = { 0xb0, 0xb1, };
static int jz4770_cim_8bit_pins[] = {
	0x26, 0x27, 0x28, 0x29,
	0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
};
static int jz4770_cim_12bit_pins[] = {
	0x32, 0x33, 0xb0, 0xb1,
};
static int jz4770_wcd_8bit_pins[] = {
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x4c, 0x4d,
	0x48, 0x52, 0x53,
};
static int jz4770_wcd_16bit_pins[] = {
	0x4e, 0x4f, 0x50, 0x51, 0x56, 0x57, 0x58, 0x59,
};
static int jz4770_wcd_18bit_pins[] = {
	0x5a, 0x5b,
};
static int jz4770_wcd_24bit_pins[] = {
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	0x58, 0x59, 0x5a, 0x5b,
};
static int jz4770_wcd_speciaw_pins[] = { 0x54, 0x4a, 0x41, 0x40, };
static int jz4770_wcd_genewic_pins[] = { 0x49, };
static int jz4770_pwm_pwm0_pins[] = { 0x80, };
static int jz4770_pwm_pwm1_pins[] = { 0x81, };
static int jz4770_pwm_pwm2_pins[] = { 0x82, };
static int jz4770_pwm_pwm3_pins[] = { 0x83, };
static int jz4770_pwm_pwm4_pins[] = { 0x84, };
static int jz4770_pwm_pwm5_pins[] = { 0x85, };
static int jz4770_pwm_pwm6_pins[] = { 0x6a, };
static int jz4770_pwm_pwm7_pins[] = { 0x6b, };
static int jz4770_mac_wmii_pins[] = {
	0xa9, 0xab, 0xaa, 0xac, 0xa5, 0xa4, 0xad, 0xae, 0xa6, 0xa8,
};
static int jz4770_mac_mii_pins[] = {
	0x7b, 0x7a, 0x7d, 0x7c, 0xa7, 0x24, 0xaf,
};

static const stwuct gwoup_desc jz4770_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", jz4770_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4770_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data", jz4770_uawt1_data, 0),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", jz4770_uawt1_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt2-data", jz4770_uawt2_data, 0),
	INGENIC_PIN_GWOUP("uawt2-hwfwow", jz4770_uawt2_hwfwow, 0),
	INGENIC_PIN_GWOUP_FUNCS("uawt3-data", jz4770_uawt3_data,
				jz4760_uawt3_data_funcs),
	INGENIC_PIN_GWOUP("uawt3-hwfwow", jz4770_uawt3_hwfwow, 0),
	INGENIC_PIN_GWOUP("ssi0-dt-a", jz4770_ssi0_dt_a, 2),
	INGENIC_PIN_GWOUP("ssi0-dt-b", jz4770_ssi0_dt_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-d", jz4770_ssi0_dt_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-e", jz4770_ssi0_dt_e, 0),
	INGENIC_PIN_GWOUP("ssi0-dw-a", jz4770_ssi0_dw_a, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-b", jz4770_ssi0_dw_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-d", jz4770_ssi0_dw_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-e", jz4770_ssi0_dw_e, 0),
	INGENIC_PIN_GWOUP("ssi0-cwk-a", jz4770_ssi0_cwk_a, 2),
	INGENIC_PIN_GWOUP("ssi0-cwk-b", jz4770_ssi0_cwk_b, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-d", jz4770_ssi0_cwk_d, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-e", jz4770_ssi0_cwk_e, 0),
	INGENIC_PIN_GWOUP("ssi0-gpc-b", jz4770_ssi0_gpc_b, 1),
	INGENIC_PIN_GWOUP("ssi0-gpc-d", jz4770_ssi0_gpc_d, 1),
	INGENIC_PIN_GWOUP("ssi0-gpc-e", jz4770_ssi0_gpc_e, 0),
	INGENIC_PIN_GWOUP("ssi0-ce0-a", jz4770_ssi0_ce0_a, 2),
	INGENIC_PIN_GWOUP("ssi0-ce0-b", jz4770_ssi0_ce0_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce0-d", jz4770_ssi0_ce0_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce0-e", jz4770_ssi0_ce0_e, 0),
	INGENIC_PIN_GWOUP("ssi0-ce1-b", jz4770_ssi0_ce1_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce1-d", jz4770_ssi0_ce1_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce1-e", jz4770_ssi0_ce1_e, 0),
	INGENIC_PIN_GWOUP("ssi1-dt-b", jz4770_ssi1_dt_b, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-d", jz4770_ssi1_dt_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-e", jz4770_ssi1_dt_e, 1),
	INGENIC_PIN_GWOUP("ssi1-dw-b", jz4770_ssi1_dw_b, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d", jz4770_ssi1_dw_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-e", jz4770_ssi1_dw_e, 1),
	INGENIC_PIN_GWOUP("ssi1-cwk-b", jz4770_ssi1_cwk_b, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-d", jz4770_ssi1_cwk_d, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-e", jz4770_ssi1_cwk_e, 1),
	INGENIC_PIN_GWOUP("ssi1-gpc-b", jz4770_ssi1_gpc_b, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-d", jz4770_ssi1_gpc_d, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-e", jz4770_ssi1_gpc_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce0-b", jz4770_ssi1_ce0_b, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-d", jz4770_ssi1_ce0_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-e", jz4770_ssi1_ce0_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce1-b", jz4770_ssi1_ce1_b, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-d", jz4770_ssi1_ce1_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-e", jz4770_ssi1_ce1_e, 1),
	INGENIC_PIN_GWOUP_FUNCS("mmc0-1bit-a", jz4770_mmc0_1bit_a,
				jz4760_mmc0_1bit_a_funcs),
	INGENIC_PIN_GWOUP("mmc0-4bit-a", jz4770_mmc0_4bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit-e", jz4770_mmc0_1bit_e, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit-e", jz4770_mmc0_4bit_e, 0),
	INGENIC_PIN_GWOUP("mmc0-8bit-e", jz4770_mmc0_8bit_e, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-d", jz4770_mmc1_1bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit-d", jz4770_mmc1_4bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-e", jz4770_mmc1_1bit_e, 1),
	INGENIC_PIN_GWOUP("mmc1-4bit-e", jz4770_mmc1_4bit_e, 1),
	INGENIC_PIN_GWOUP("mmc1-8bit-e", jz4770_mmc1_8bit_e, 1),
	INGENIC_PIN_GWOUP("mmc2-1bit-b", jz4770_mmc2_1bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-4bit-b", jz4770_mmc2_4bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-1bit-e", jz4770_mmc2_1bit_e, 2),
	INGENIC_PIN_GWOUP("mmc2-4bit-e", jz4770_mmc2_4bit_e, 2),
	INGENIC_PIN_GWOUP("mmc2-8bit-e", jz4770_mmc2_8bit_e, 2),
	INGENIC_PIN_GWOUP("nemc-8bit-data", jz4770_nemc_8bit_data, 0),
	INGENIC_PIN_GWOUP("nemc-16bit-data", jz4770_nemc_16bit_data, 0),
	INGENIC_PIN_GWOUP("nemc-cwe-awe", jz4770_nemc_cwe_awe, 0),
	INGENIC_PIN_GWOUP("nemc-addw", jz4770_nemc_addw, 0),
	INGENIC_PIN_GWOUP("nemc-wd-we", jz4770_nemc_wd_we, 0),
	INGENIC_PIN_GWOUP("nemc-fwd-fwe", jz4770_nemc_fwd_fwe, 0),
	INGENIC_PIN_GWOUP("nemc-wait", jz4770_nemc_wait, 0),
	INGENIC_PIN_GWOUP("nemc-cs1", jz4770_nemc_cs1, 0),
	INGENIC_PIN_GWOUP("nemc-cs2", jz4770_nemc_cs2, 0),
	INGENIC_PIN_GWOUP("nemc-cs3", jz4770_nemc_cs3, 0),
	INGENIC_PIN_GWOUP("nemc-cs4", jz4770_nemc_cs4, 0),
	INGENIC_PIN_GWOUP("nemc-cs5", jz4770_nemc_cs5, 0),
	INGENIC_PIN_GWOUP("nemc-cs6", jz4770_nemc_cs6, 0),
	INGENIC_PIN_GWOUP("i2c0-data", jz4770_i2c0, 0),
	INGENIC_PIN_GWOUP("i2c1-data", jz4770_i2c1, 0),
	INGENIC_PIN_GWOUP("i2c2-data", jz4770_i2c2, 2),
	INGENIC_PIN_GWOUP("cim-data-8bit", jz4770_cim_8bit, 0),
	INGENIC_PIN_GWOUP("cim-data-12bit", jz4770_cim_12bit, 0),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4770_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4770_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4770_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-24bit", jz4770_wcd_24bit, 0),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4770_wcd_speciaw, 1),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4770_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4770_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4770_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4770_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4770_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4770_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4770_pwm_pwm5, 0),
	INGENIC_PIN_GWOUP("pwm6", jz4770_pwm_pwm6, 0),
	INGENIC_PIN_GWOUP("pwm7", jz4770_pwm_pwm7, 0),
	INGENIC_PIN_GWOUP("mac-wmii", jz4770_mac_wmii, 0),
	INGENIC_PIN_GWOUP("mac-mii", jz4770_mac_mii, 0),
	INGENIC_PIN_GWOUP("otg-vbus", jz4760_otg, 0),
};

static const chaw *jz4770_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *jz4770_uawt1_gwoups[] = { "uawt1-data", "uawt1-hwfwow", };
static const chaw *jz4770_uawt2_gwoups[] = { "uawt2-data", "uawt2-hwfwow", };
static const chaw *jz4770_uawt3_gwoups[] = { "uawt3-data", "uawt3-hwfwow", };
static const chaw *jz4770_ssi0_gwoups[] = {
	"ssi0-dt-a", "ssi0-dt-b", "ssi0-dt-d", "ssi0-dt-e",
	"ssi0-dw-a", "ssi0-dw-b", "ssi0-dw-d", "ssi0-dw-e",
	"ssi0-cwk-a", "ssi0-cwk-b", "ssi0-cwk-d", "ssi0-cwk-e",
	"ssi0-gpc-b", "ssi0-gpc-d", "ssi0-gpc-e",
	"ssi0-ce0-a", "ssi0-ce0-b", "ssi0-ce0-d", "ssi0-ce0-e",
	"ssi0-ce1-b", "ssi0-ce1-d", "ssi0-ce1-e",
};
static const chaw *jz4770_ssi1_gwoups[] = {
	"ssi1-dt-b", "ssi1-dt-d", "ssi1-dt-e",
	"ssi1-dw-b", "ssi1-dw-d", "ssi1-dw-e",
	"ssi1-cwk-b", "ssi1-cwk-d", "ssi1-cwk-e",
	"ssi1-gpc-b", "ssi1-gpc-d", "ssi1-gpc-e",
	"ssi1-ce0-b", "ssi1-ce0-d", "ssi1-ce0-e",
	"ssi1-ce1-b", "ssi1-ce1-d", "ssi1-ce1-e",
};
static const chaw *jz4770_mmc0_gwoups[] = {
	"mmc0-1bit-a", "mmc0-4bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e", "mmc0-8bit-e",
};
static const chaw *jz4770_mmc1_gwoups[] = {
	"mmc1-1bit-d", "mmc1-4bit-d",
	"mmc1-1bit-e", "mmc1-4bit-e", "mmc1-8bit-e",
};
static const chaw *jz4770_mmc2_gwoups[] = {
	"mmc2-1bit-b", "mmc2-4bit-b",
	"mmc2-1bit-e", "mmc2-4bit-e", "mmc2-8bit-e",
};
static const chaw *jz4770_nemc_gwoups[] = {
	"nemc-8bit-data", "nemc-16bit-data", "nemc-cwe-awe",
	"nemc-addw", "nemc-wd-we", "nemc-fwd-fwe", "nemc-wait",
};
static const chaw *jz4770_cs1_gwoups[] = { "nemc-cs1", };
static const chaw *jz4770_cs2_gwoups[] = { "nemc-cs2", };
static const chaw *jz4770_cs3_gwoups[] = { "nemc-cs3", };
static const chaw *jz4770_cs4_gwoups[] = { "nemc-cs4", };
static const chaw *jz4770_cs5_gwoups[] = { "nemc-cs5", };
static const chaw *jz4770_cs6_gwoups[] = { "nemc-cs6", };
static const chaw *jz4770_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *jz4770_i2c1_gwoups[] = { "i2c1-data", };
static const chaw *jz4770_i2c2_gwoups[] = { "i2c2-data", };
static const chaw *jz4770_cim_gwoups[] = { "cim-data-8bit", "cim-data-12bit", };
static const chaw *jz4770_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-24bit",
	"wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4770_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4770_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4770_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4770_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4770_pwm4_gwoups[] = { "pwm4", };
static const chaw *jz4770_pwm5_gwoups[] = { "pwm5", };
static const chaw *jz4770_pwm6_gwoups[] = { "pwm6", };
static const chaw *jz4770_pwm7_gwoups[] = { "pwm7", };
static const chaw *jz4770_mac_gwoups[] = { "mac-wmii", "mac-mii", };

static const stwuct function_desc jz4770_functions[] = {
	{ "uawt0", jz4770_uawt0_gwoups, AWWAY_SIZE(jz4770_uawt0_gwoups), },
	{ "uawt1", jz4770_uawt1_gwoups, AWWAY_SIZE(jz4770_uawt1_gwoups), },
	{ "uawt2", jz4770_uawt2_gwoups, AWWAY_SIZE(jz4770_uawt2_gwoups), },
	{ "uawt3", jz4770_uawt3_gwoups, AWWAY_SIZE(jz4770_uawt3_gwoups), },
	{ "ssi0", jz4770_ssi0_gwoups, AWWAY_SIZE(jz4770_ssi0_gwoups), },
	{ "ssi1", jz4770_ssi1_gwoups, AWWAY_SIZE(jz4770_ssi1_gwoups), },
	{ "mmc0", jz4770_mmc0_gwoups, AWWAY_SIZE(jz4770_mmc0_gwoups), },
	{ "mmc1", jz4770_mmc1_gwoups, AWWAY_SIZE(jz4770_mmc1_gwoups), },
	{ "mmc2", jz4770_mmc2_gwoups, AWWAY_SIZE(jz4770_mmc2_gwoups), },
	{ "nemc", jz4770_nemc_gwoups, AWWAY_SIZE(jz4770_nemc_gwoups), },
	{ "nemc-cs1", jz4770_cs1_gwoups, AWWAY_SIZE(jz4770_cs1_gwoups), },
	{ "nemc-cs2", jz4770_cs2_gwoups, AWWAY_SIZE(jz4770_cs2_gwoups), },
	{ "nemc-cs3", jz4770_cs3_gwoups, AWWAY_SIZE(jz4770_cs3_gwoups), },
	{ "nemc-cs4", jz4770_cs4_gwoups, AWWAY_SIZE(jz4770_cs4_gwoups), },
	{ "nemc-cs5", jz4770_cs5_gwoups, AWWAY_SIZE(jz4770_cs5_gwoups), },
	{ "nemc-cs6", jz4770_cs6_gwoups, AWWAY_SIZE(jz4770_cs6_gwoups), },
	{ "i2c0", jz4770_i2c0_gwoups, AWWAY_SIZE(jz4770_i2c0_gwoups), },
	{ "i2c1", jz4770_i2c1_gwoups, AWWAY_SIZE(jz4770_i2c1_gwoups), },
	{ "i2c2", jz4770_i2c2_gwoups, AWWAY_SIZE(jz4770_i2c2_gwoups), },
	{ "cim", jz4770_cim_gwoups, AWWAY_SIZE(jz4770_cim_gwoups), },
	{ "wcd", jz4770_wcd_gwoups, AWWAY_SIZE(jz4770_wcd_gwoups), },
	{ "pwm0", jz4770_pwm0_gwoups, AWWAY_SIZE(jz4770_pwm0_gwoups), },
	{ "pwm1", jz4770_pwm1_gwoups, AWWAY_SIZE(jz4770_pwm1_gwoups), },
	{ "pwm2", jz4770_pwm2_gwoups, AWWAY_SIZE(jz4770_pwm2_gwoups), },
	{ "pwm3", jz4770_pwm3_gwoups, AWWAY_SIZE(jz4770_pwm3_gwoups), },
	{ "pwm4", jz4770_pwm4_gwoups, AWWAY_SIZE(jz4770_pwm4_gwoups), },
	{ "pwm5", jz4770_pwm5_gwoups, AWWAY_SIZE(jz4770_pwm5_gwoups), },
	{ "pwm6", jz4770_pwm6_gwoups, AWWAY_SIZE(jz4770_pwm6_gwoups), },
	{ "pwm7", jz4770_pwm7_gwoups, AWWAY_SIZE(jz4770_pwm7_gwoups), },
	{ "mac", jz4770_mac_gwoups, AWWAY_SIZE(jz4770_mac_gwoups), },
	{ "otg", jz4760_otg_gwoups, AWWAY_SIZE(jz4760_otg_gwoups), },
};

static const stwuct ingenic_chip_info jz4770_chip_info = {
	.num_chips = 6,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4770,
	.gwoups = jz4770_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4770_gwoups),
	.functions = jz4770_functions,
	.num_functions = AWWAY_SIZE(jz4770_functions),
	.puww_ups = jz4770_puww_ups,
	.puww_downs = jz4770_puww_downs,
};

static const u32 jz4775_puww_ups[7] = {
	0x28ff00ff, 0xf030f3fc, 0x0fffffff, 0xfffe4000, 0xf0f0000c, 0x0000f00f, 0x0000f3c0,
};

static const u32 jz4775_puww_downs[7] = {
	0x00000000, 0x00030c03, 0x00000000, 0x00008000, 0x00000403, 0x00000ff0, 0x00030c00,
};

static int jz4775_uawt0_data_pins[] = { 0xa0, 0xa3, };
static int jz4775_uawt0_hwfwow_pins[] = { 0xa1, 0xa2, };
static int jz4775_uawt1_data_pins[] = { 0x7a, 0x7c, };
static int jz4775_uawt1_hwfwow_pins[] = { 0x7b, 0x7d, };
static int jz4775_uawt2_data_c_pins[] = { 0x54, 0x4a, };
static int jz4775_uawt2_data_f_pins[] = { 0xa5, 0xa4, };
static int jz4775_uawt3_data_pins[] = { 0x1e, 0x1f, };
static int jz4775_ssi_dt_a_pins[] = { 0x13, };
static int jz4775_ssi_dt_d_pins[] = { 0x75, };
static int jz4775_ssi_dw_a_pins[] = { 0x14, };
static int jz4775_ssi_dw_d_pins[] = { 0x74, };
static int jz4775_ssi_cwk_a_pins[] = { 0x12, };
static int jz4775_ssi_cwk_d_pins[] = { 0x78, };
static int jz4775_ssi_gpc_pins[] = { 0x76, };
static int jz4775_ssi_ce0_a_pins[] = { 0x17, };
static int jz4775_ssi_ce0_d_pins[] = { 0x79, };
static int jz4775_ssi_ce1_pins[] = { 0x77, };
static int jz4775_mmc0_1bit_a_pins[] = { 0x12, 0x13, 0x14, };
static int jz4775_mmc0_4bit_a_pins[] = { 0x15, 0x16, 0x17, };
static int jz4775_mmc0_8bit_a_pins[] = { 0x04, 0x05, 0x06, 0x07, };
static int jz4775_mmc0_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4775_mmc0_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4775_mmc1_1bit_d_pins[] = { 0x78, 0x79, 0x74, };
static int jz4775_mmc1_4bit_d_pins[] = { 0x75, 0x76, 0x77, };
static int jz4775_mmc1_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4775_mmc1_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4775_mmc2_1bit_b_pins[] = { 0x3c, 0x3d, 0x34, };
static int jz4775_mmc2_4bit_b_pins[] = { 0x35, 0x3e, 0x3f, };
static int jz4775_mmc2_1bit_e_pins[] = { 0x9c, 0x9d, 0x94, };
static int jz4775_mmc2_4bit_e_pins[] = { 0x95, 0x96, 0x97, };
static int jz4775_nemc_8bit_data_pins[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};
static int jz4775_nemc_16bit_data_pins[] = {
	0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1,
};
static int jz4775_nemc_cwe_awe_pins[] = { 0x20, 0x21, };
static int jz4775_nemc_addw_pins[] = { 0x22, 0x23, 0x24, 0x25, };
static int jz4775_nemc_wd_we_pins[] = { 0x10, 0x11, };
static int jz4775_nemc_fwd_fwe_pins[] = { 0x12, 0x13, };
static int jz4775_nemc_wait_pins[] = { 0x1b, };
static int jz4775_nemc_cs1_pins[] = { 0x15, };
static int jz4775_nemc_cs2_pins[] = { 0x16, };
static int jz4775_nemc_cs3_pins[] = { 0x17, };
static int jz4775_i2c0_pins[] = { 0x7e, 0x7f, };
static int jz4775_i2c1_pins[] = { 0x9e, 0x9f, };
static int jz4775_i2c2_pins[] = { 0x80, 0x83, };
static int jz4775_i2s_data_tx_pins[] = { 0xa3, };
static int jz4775_i2s_data_wx_pins[] = { 0xa2, };
static int jz4775_i2s_cwk_txwx_pins[] = { 0xa0, 0xa1, };
static int jz4775_i2s_syscwk_pins[] = { 0x83, };
static int jz4775_dmic_pins[] = { 0xaa, 0xab, };
static int jz4775_cim_pins[] = {
	0x26, 0x27, 0x28, 0x29,
	0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
};
static int jz4775_wcd_8bit_pins[] = {
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x4c, 0x4d,
	0x48, 0x52, 0x53,
};
static int jz4775_wcd_16bit_pins[] = {
	0x4e, 0x4f, 0x50, 0x51, 0x56, 0x57, 0x58, 0x59,
};
static int jz4775_wcd_18bit_pins[] = {
	0x5a, 0x5b,
};
static int jz4775_wcd_24bit_pins[] = {
	0x40, 0x41, 0x4a, 0x4b, 0x54, 0x55,
};
static int jz4775_wcd_speciaw_pins[] = { 0x54, 0x4a, 0x41, 0x40, };
static int jz4775_wcd_genewic_pins[] = { 0x49, };
static int jz4775_pwm_pwm0_pins[] = { 0x80, };
static int jz4775_pwm_pwm1_pins[] = { 0x81, };
static int jz4775_pwm_pwm2_pins[] = { 0x82, };
static int jz4775_pwm_pwm3_pins[] = { 0x83, };
static int jz4775_mac_wmii_pins[] = {
	0xa9, 0xab, 0xaa, 0xac, 0xa5, 0xa4, 0xad, 0xae, 0xa6, 0xa8,
};
static int jz4775_mac_mii_pins[] = {
	0x7b, 0x7a, 0x7d, 0x7c, 0xa7, 0x24, 0xaf,
};
static int jz4775_mac_wgmii_pins[] = {
	0xa9, 0x7b, 0x7a, 0xab, 0xaa, 0xac, 0x7d, 0x7c, 0xa5, 0xa4,
	0xad, 0xae, 0xa7, 0xa6,
};
static int jz4775_mac_gmii_pins[] = {
	0x31, 0x30, 0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a,
	0xa8, 0x28, 0x24, 0xaf,
};
static int jz4775_otg_pins[] = { 0x8a, };

static u8 jz4775_uawt3_data_funcs[] = { 0, 1, };
static u8 jz4775_mac_mii_funcs[] = { 1, 1, 1, 1, 0, 1, 0, };
static u8 jz4775_mac_wgmii_funcs[] = {
	0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
	0, 0, 0, 0,
};
static u8 jz4775_mac_gmii_funcs[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 1, 1, 0,
};

static const stwuct gwoup_desc jz4775_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", jz4775_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4775_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data", jz4775_uawt1_data, 0),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", jz4775_uawt1_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt2-data-c", jz4775_uawt2_data_c, 2),
	INGENIC_PIN_GWOUP("uawt2-data-f", jz4775_uawt2_data_f, 1),
	INGENIC_PIN_GWOUP_FUNCS("uawt3-data", jz4775_uawt3_data,
				jz4775_uawt3_data_funcs),
	INGENIC_PIN_GWOUP("ssi-dt-a", jz4775_ssi_dt_a, 2),
	INGENIC_PIN_GWOUP("ssi-dt-d", jz4775_ssi_dt_d, 1),
	INGENIC_PIN_GWOUP("ssi-dw-a", jz4775_ssi_dw_a, 2),
	INGENIC_PIN_GWOUP("ssi-dw-d", jz4775_ssi_dw_d, 1),
	INGENIC_PIN_GWOUP("ssi-cwk-a", jz4775_ssi_cwk_a, 2),
	INGENIC_PIN_GWOUP("ssi-cwk-d", jz4775_ssi_cwk_d, 1),
	INGENIC_PIN_GWOUP("ssi-gpc", jz4775_ssi_gpc, 1),
	INGENIC_PIN_GWOUP("ssi-ce0-a", jz4775_ssi_ce0_a, 2),
	INGENIC_PIN_GWOUP("ssi-ce0-d", jz4775_ssi_ce0_d, 1),
	INGENIC_PIN_GWOUP("ssi-ce1", jz4775_ssi_ce1, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit-a", jz4775_mmc0_1bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-4bit-a", jz4775_mmc0_4bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-8bit-a", jz4775_mmc0_8bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit-e", jz4775_mmc0_1bit_e, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit-e", jz4775_mmc0_4bit_e, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-d", jz4775_mmc1_1bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit-d", jz4775_mmc1_4bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-e", jz4775_mmc1_1bit_e, 1),
	INGENIC_PIN_GWOUP("mmc1-4bit-e", jz4775_mmc1_4bit_e, 1),
	INGENIC_PIN_GWOUP("mmc2-1bit-b", jz4775_mmc2_1bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-4bit-b", jz4775_mmc2_4bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-1bit-e", jz4775_mmc2_1bit_e, 2),
	INGENIC_PIN_GWOUP("mmc2-4bit-e", jz4775_mmc2_4bit_e, 2),
	INGENIC_PIN_GWOUP("nemc-8bit-data", jz4775_nemc_8bit_data, 0),
	INGENIC_PIN_GWOUP("nemc-16bit-data", jz4775_nemc_16bit_data, 1),
	INGENIC_PIN_GWOUP("nemc-cwe-awe", jz4775_nemc_cwe_awe, 0),
	INGENIC_PIN_GWOUP("nemc-addw", jz4775_nemc_addw, 0),
	INGENIC_PIN_GWOUP("nemc-wd-we", jz4775_nemc_wd_we, 0),
	INGENIC_PIN_GWOUP("nemc-fwd-fwe", jz4775_nemc_fwd_fwe, 0),
	INGENIC_PIN_GWOUP("nemc-wait", jz4775_nemc_wait, 0),
	INGENIC_PIN_GWOUP("nemc-cs1", jz4775_nemc_cs1, 0),
	INGENIC_PIN_GWOUP("nemc-cs2", jz4775_nemc_cs2, 0),
	INGENIC_PIN_GWOUP("nemc-cs3", jz4775_nemc_cs3, 0),
	INGENIC_PIN_GWOUP("i2c0-data", jz4775_i2c0, 0),
	INGENIC_PIN_GWOUP("i2c1-data", jz4775_i2c1, 0),
	INGENIC_PIN_GWOUP("i2c2-data", jz4775_i2c2, 1),
	INGENIC_PIN_GWOUP("i2s-data-tx", jz4775_i2s_data_tx, 1),
	INGENIC_PIN_GWOUP("i2s-data-wx", jz4775_i2s_data_wx, 1),
	INGENIC_PIN_GWOUP("i2s-cwk-txwx", jz4775_i2s_cwk_txwx, 1),
	INGENIC_PIN_GWOUP("i2s-syscwk", jz4775_i2s_syscwk, 2),
	INGENIC_PIN_GWOUP("dmic", jz4775_dmic, 1),
	INGENIC_PIN_GWOUP("cim-data", jz4775_cim, 0),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4775_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4775_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4775_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-24bit", jz4775_wcd_24bit, 0),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4775_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4775_wcd_speciaw, 1),
	INGENIC_PIN_GWOUP("pwm0", jz4775_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4775_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4775_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4775_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("mac-wmii", jz4775_mac_wmii, 0),
	INGENIC_PIN_GWOUP_FUNCS("mac-mii", jz4775_mac_mii,
				jz4775_mac_mii_funcs),
	INGENIC_PIN_GWOUP_FUNCS("mac-wgmii", jz4775_mac_wgmii,
				jz4775_mac_wgmii_funcs),
	INGENIC_PIN_GWOUP_FUNCS("mac-gmii", jz4775_mac_gmii,
				jz4775_mac_gmii_funcs),
	INGENIC_PIN_GWOUP("otg-vbus", jz4775_otg, 0),
};

static const chaw *jz4775_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *jz4775_uawt1_gwoups[] = { "uawt1-data", "uawt1-hwfwow", };
static const chaw *jz4775_uawt2_gwoups[] = { "uawt2-data-c", "uawt2-data-f", };
static const chaw *jz4775_uawt3_gwoups[] = { "uawt3-data", };
static const chaw *jz4775_ssi_gwoups[] = {
	"ssi-dt-a", "ssi-dt-d",
	"ssi-dw-a", "ssi-dw-d",
	"ssi-cwk-a", "ssi-cwk-d",
	"ssi-gpc",
	"ssi-ce0-a", "ssi-ce0-d",
	"ssi-ce1",
};
static const chaw *jz4775_mmc0_gwoups[] = {
	"mmc0-1bit-a", "mmc0-4bit-a", "mmc0-8bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e",
};
static const chaw *jz4775_mmc1_gwoups[] = {
	"mmc1-1bit-d", "mmc1-4bit-d",
	"mmc1-1bit-e", "mmc1-4bit-e",
};
static const chaw *jz4775_mmc2_gwoups[] = {
	"mmc2-1bit-b", "mmc2-4bit-b",
	"mmc2-1bit-e", "mmc2-4bit-e",
};
static const chaw *jz4775_nemc_gwoups[] = {
	"nemc-8bit-data", "nemc-16bit-data", "nemc-cwe-awe",
	"nemc-addw", "nemc-wd-we", "nemc-fwd-fwe", "nemc-wait",
};
static const chaw *jz4775_cs1_gwoups[] = { "nemc-cs1", };
static const chaw *jz4775_cs2_gwoups[] = { "nemc-cs2", };
static const chaw *jz4775_cs3_gwoups[] = { "nemc-cs3", };
static const chaw *jz4775_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *jz4775_i2c1_gwoups[] = { "i2c1-data", };
static const chaw *jz4775_i2c2_gwoups[] = { "i2c2-data", };
static const chaw *jz4775_i2s_gwoups[] = {
	"i2s-data-tx", "i2s-data-wx", "i2s-cwk-txwx", "i2s-syscwk",
};
static const chaw *jz4775_dmic_gwoups[] = { "dmic", };
static const chaw *jz4775_cim_gwoups[] = { "cim-data", };
static const chaw *jz4775_wcd_gwoups[] = {
	"wcd-8bit", "wcd-16bit", "wcd-18bit", "wcd-24bit",
	"wcd-speciaw", "wcd-genewic",
};
static const chaw *jz4775_pwm0_gwoups[] = { "pwm0", };
static const chaw *jz4775_pwm1_gwoups[] = { "pwm1", };
static const chaw *jz4775_pwm2_gwoups[] = { "pwm2", };
static const chaw *jz4775_pwm3_gwoups[] = { "pwm3", };
static const chaw *jz4775_mac_gwoups[] = {
	"mac-wmii", "mac-mii", "mac-wgmii", "mac-gmii",
};
static const chaw *jz4775_otg_gwoups[] = { "otg-vbus", };

static const stwuct function_desc jz4775_functions[] = {
	{ "uawt0", jz4775_uawt0_gwoups, AWWAY_SIZE(jz4775_uawt0_gwoups), },
	{ "uawt1", jz4775_uawt1_gwoups, AWWAY_SIZE(jz4775_uawt1_gwoups), },
	{ "uawt2", jz4775_uawt2_gwoups, AWWAY_SIZE(jz4775_uawt2_gwoups), },
	{ "uawt3", jz4775_uawt3_gwoups, AWWAY_SIZE(jz4775_uawt3_gwoups), },
	{ "ssi", jz4775_ssi_gwoups, AWWAY_SIZE(jz4775_ssi_gwoups), },
	{ "mmc0", jz4775_mmc0_gwoups, AWWAY_SIZE(jz4775_mmc0_gwoups), },
	{ "mmc1", jz4775_mmc1_gwoups, AWWAY_SIZE(jz4775_mmc1_gwoups), },
	{ "mmc2", jz4775_mmc2_gwoups, AWWAY_SIZE(jz4775_mmc2_gwoups), },
	{ "nemc", jz4775_nemc_gwoups, AWWAY_SIZE(jz4775_nemc_gwoups), },
	{ "nemc-cs1", jz4775_cs1_gwoups, AWWAY_SIZE(jz4775_cs1_gwoups), },
	{ "nemc-cs2", jz4775_cs2_gwoups, AWWAY_SIZE(jz4775_cs2_gwoups), },
	{ "nemc-cs3", jz4775_cs3_gwoups, AWWAY_SIZE(jz4775_cs3_gwoups), },
	{ "i2c0", jz4775_i2c0_gwoups, AWWAY_SIZE(jz4775_i2c0_gwoups), },
	{ "i2c1", jz4775_i2c1_gwoups, AWWAY_SIZE(jz4775_i2c1_gwoups), },
	{ "i2c2", jz4775_i2c2_gwoups, AWWAY_SIZE(jz4775_i2c2_gwoups), },
	{ "i2s", jz4775_i2s_gwoups, AWWAY_SIZE(jz4775_i2s_gwoups), },
	{ "dmic", jz4775_dmic_gwoups, AWWAY_SIZE(jz4775_dmic_gwoups), },
	{ "cim", jz4775_cim_gwoups, AWWAY_SIZE(jz4775_cim_gwoups), },
	{ "wcd", jz4775_wcd_gwoups, AWWAY_SIZE(jz4775_wcd_gwoups), },
	{ "pwm0", jz4775_pwm0_gwoups, AWWAY_SIZE(jz4775_pwm0_gwoups), },
	{ "pwm1", jz4775_pwm1_gwoups, AWWAY_SIZE(jz4775_pwm1_gwoups), },
	{ "pwm2", jz4775_pwm2_gwoups, AWWAY_SIZE(jz4775_pwm2_gwoups), },
	{ "pwm3", jz4775_pwm3_gwoups, AWWAY_SIZE(jz4775_pwm3_gwoups), },
	{ "mac", jz4775_mac_gwoups, AWWAY_SIZE(jz4775_mac_gwoups), },
	{ "otg", jz4775_otg_gwoups, AWWAY_SIZE(jz4775_otg_gwoups), },
};

static const stwuct ingenic_chip_info jz4775_chip_info = {
	.num_chips = 7,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4775,
	.gwoups = jz4775_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4775_gwoups),
	.functions = jz4775_functions,
	.num_functions = AWWAY_SIZE(jz4775_functions),
	.puww_ups = jz4775_puww_ups,
	.puww_downs = jz4775_puww_downs,
};

static const u32 jz4780_puww_ups[6] = {
	0x3fffffff, 0xfff0f3fc, 0x0fffffff, 0xffff4fff, 0xfffffb7c, 0x7fa7f00f,
};

static const u32 jz4780_puww_downs[6] = {
	0x00000000, 0x000f0c03, 0x00000000, 0x0000b000, 0x00000483, 0x00580ff0,
};

static int jz4780_uawt2_data_pins[] = { 0x66, 0x67, };
static int jz4780_uawt2_hwfwow_pins[] = { 0x65, 0x64, };
static int jz4780_uawt4_data_pins[] = { 0x54, 0x4a, };
static int jz4780_ssi0_dt_a_19_pins[] = { 0x13, };
static int jz4780_ssi0_dt_a_21_pins[] = { 0x15, };
static int jz4780_ssi0_dt_a_28_pins[] = { 0x1c, };
static int jz4780_ssi0_dt_b_pins[] = { 0x3d, };
static int jz4780_ssi0_dt_d_pins[] = { 0x79, };
static int jz4780_ssi0_dw_a_20_pins[] = { 0x14, };
static int jz4780_ssi0_dw_a_27_pins[] = { 0x1b, };
static int jz4780_ssi0_dw_b_pins[] = { 0x34, };
static int jz4780_ssi0_dw_d_pins[] = { 0x74, };
static int jz4780_ssi0_cwk_a_pins[] = { 0x12, };
static int jz4780_ssi0_cwk_b_5_pins[] = { 0x25, };
static int jz4780_ssi0_cwk_b_28_pins[] = { 0x3c, };
static int jz4780_ssi0_cwk_d_pins[] = { 0x78, };
static int jz4780_ssi0_gpc_b_pins[] = { 0x3e, };
static int jz4780_ssi0_gpc_d_pins[] = { 0x76, };
static int jz4780_ssi0_ce0_a_23_pins[] = { 0x17, };
static int jz4780_ssi0_ce0_a_25_pins[] = { 0x19, };
static int jz4780_ssi0_ce0_b_pins[] = { 0x3f, };
static int jz4780_ssi0_ce0_d_pins[] = { 0x77, };
static int jz4780_ssi0_ce1_b_pins[] = { 0x35, };
static int jz4780_ssi0_ce1_d_pins[] = { 0x75, };
static int jz4780_ssi1_dt_b_pins[] = { 0x3d, };
static int jz4780_ssi1_dt_d_pins[] = { 0x79, };
static int jz4780_ssi1_dw_b_pins[] = { 0x34, };
static int jz4780_ssi1_dw_d_pins[] = { 0x74, };
static int jz4780_ssi1_cwk_b_pins[] = { 0x3c, };
static int jz4780_ssi1_cwk_d_pins[] = { 0x78, };
static int jz4780_ssi1_gpc_b_pins[] = { 0x3e, };
static int jz4780_ssi1_gpc_d_pins[] = { 0x76, };
static int jz4780_ssi1_ce0_b_pins[] = { 0x3f, };
static int jz4780_ssi1_ce0_d_pins[] = { 0x77, };
static int jz4780_ssi1_ce1_b_pins[] = { 0x35, };
static int jz4780_ssi1_ce1_d_pins[] = { 0x75, };
static int jz4780_mmc0_8bit_a_pins[] = { 0x04, 0x05, 0x06, 0x07, 0x18, };
static int jz4780_i2c3_pins[] = { 0x6a, 0x6b, };
static int jz4780_i2c4_e_pins[] = { 0x8c, 0x8d, };
static int jz4780_i2c4_f_pins[] = { 0xb9, 0xb8, };
static int jz4780_i2s_data_tx_pins[] = { 0x87, };
static int jz4780_i2s_data_wx_pins[] = { 0x86, };
static int jz4780_i2s_cwk_txwx_pins[] = { 0x6c, 0x6d, };
static int jz4780_i2s_cwk_wx_pins[] = { 0x88, 0x89, };
static int jz4780_i2s_syscwk_pins[] = { 0x85, };
static int jz4780_dmic_pins[] = { 0x32, 0x33, };
static int jz4780_hdmi_ddc_pins[] = { 0xb9, 0xb8, };

static u8 jz4780_i2s_cwk_txwx_funcs[] = { 1, 0, };

static const stwuct gwoup_desc jz4780_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", jz4770_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", jz4770_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data", jz4770_uawt1_data, 0),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", jz4770_uawt1_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt2-data", jz4780_uawt2_data, 1),
	INGENIC_PIN_GWOUP("uawt2-hwfwow", jz4780_uawt2_hwfwow, 1),
	INGENIC_PIN_GWOUP_FUNCS("uawt3-data", jz4770_uawt3_data,
				jz4760_uawt3_data_funcs),
	INGENIC_PIN_GWOUP("uawt3-hwfwow", jz4770_uawt3_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt4-data", jz4780_uawt4_data, 2),
	INGENIC_PIN_GWOUP("ssi0-dt-a-19", jz4780_ssi0_dt_a_19, 2),
	INGENIC_PIN_GWOUP("ssi0-dt-a-21", jz4780_ssi0_dt_a_21, 2),
	INGENIC_PIN_GWOUP("ssi0-dt-a-28", jz4780_ssi0_dt_a_28, 2),
	INGENIC_PIN_GWOUP("ssi0-dt-b", jz4780_ssi0_dt_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-d", jz4780_ssi0_dt_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-e", jz4770_ssi0_dt_e, 0),
	INGENIC_PIN_GWOUP("ssi0-dw-a-20", jz4780_ssi0_dw_a_20, 2),
	INGENIC_PIN_GWOUP("ssi0-dw-a-27", jz4780_ssi0_dw_a_27, 2),
	INGENIC_PIN_GWOUP("ssi0-dw-b", jz4780_ssi0_dw_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-d", jz4780_ssi0_dw_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-e", jz4770_ssi0_dw_e, 0),
	INGENIC_PIN_GWOUP("ssi0-cwk-a", jz4780_ssi0_cwk_a, 2),
	INGENIC_PIN_GWOUP("ssi0-cwk-b-5", jz4780_ssi0_cwk_b_5, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-b-28", jz4780_ssi0_cwk_b_28, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-d", jz4780_ssi0_cwk_d, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-e", jz4770_ssi0_cwk_e, 0),
	INGENIC_PIN_GWOUP("ssi0-gpc-b", jz4780_ssi0_gpc_b, 1),
	INGENIC_PIN_GWOUP("ssi0-gpc-d", jz4780_ssi0_gpc_d, 1),
	INGENIC_PIN_GWOUP("ssi0-gpc-e", jz4770_ssi0_gpc_e, 0),
	INGENIC_PIN_GWOUP("ssi0-ce0-a-23", jz4780_ssi0_ce0_a_23, 2),
	INGENIC_PIN_GWOUP("ssi0-ce0-a-25", jz4780_ssi0_ce0_a_25, 2),
	INGENIC_PIN_GWOUP("ssi0-ce0-b", jz4780_ssi0_ce0_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce0-d", jz4780_ssi0_ce0_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce0-e", jz4770_ssi0_ce0_e, 0),
	INGENIC_PIN_GWOUP("ssi0-ce1-b", jz4780_ssi0_ce1_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce1-d", jz4780_ssi0_ce1_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce1-e", jz4770_ssi0_ce1_e, 0),
	INGENIC_PIN_GWOUP("ssi1-dt-b", jz4780_ssi1_dt_b, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-d", jz4780_ssi1_dt_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-e", jz4770_ssi1_dt_e, 1),
	INGENIC_PIN_GWOUP("ssi1-dw-b", jz4780_ssi1_dw_b, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d", jz4780_ssi1_dw_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-e", jz4770_ssi1_dw_e, 1),
	INGENIC_PIN_GWOUP("ssi1-cwk-b", jz4780_ssi1_cwk_b, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-d", jz4780_ssi1_cwk_d, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-e", jz4770_ssi1_cwk_e, 1),
	INGENIC_PIN_GWOUP("ssi1-gpc-b", jz4780_ssi1_gpc_b, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-d", jz4780_ssi1_gpc_d, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-e", jz4770_ssi1_gpc_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce0-b", jz4780_ssi1_ce0_b, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-d", jz4780_ssi1_ce0_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-e", jz4770_ssi1_ce0_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce1-b", jz4780_ssi1_ce1_b, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-d", jz4780_ssi1_ce1_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-e", jz4770_ssi1_ce1_e, 1),
	INGENIC_PIN_GWOUP_FUNCS("mmc0-1bit-a", jz4770_mmc0_1bit_a,
				jz4760_mmc0_1bit_a_funcs),
	INGENIC_PIN_GWOUP("mmc0-4bit-a", jz4770_mmc0_4bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-8bit-a", jz4780_mmc0_8bit_a, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit-e", jz4770_mmc0_1bit_e, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit-e", jz4770_mmc0_4bit_e, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-d", jz4770_mmc1_1bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit-d", jz4770_mmc1_4bit_d, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit-e", jz4770_mmc1_1bit_e, 1),
	INGENIC_PIN_GWOUP("mmc1-4bit-e", jz4770_mmc1_4bit_e, 1),
	INGENIC_PIN_GWOUP("mmc2-1bit-b", jz4770_mmc2_1bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-4bit-b", jz4770_mmc2_4bit_b, 0),
	INGENIC_PIN_GWOUP("mmc2-1bit-e", jz4770_mmc2_1bit_e, 2),
	INGENIC_PIN_GWOUP("mmc2-4bit-e", jz4770_mmc2_4bit_e, 2),
	INGENIC_PIN_GWOUP("nemc-data", jz4770_nemc_8bit_data, 0),
	INGENIC_PIN_GWOUP("nemc-cwe-awe", jz4770_nemc_cwe_awe, 0),
	INGENIC_PIN_GWOUP("nemc-addw", jz4770_nemc_addw, 0),
	INGENIC_PIN_GWOUP("nemc-wd-we", jz4770_nemc_wd_we, 0),
	INGENIC_PIN_GWOUP("nemc-fwd-fwe", jz4770_nemc_fwd_fwe, 0),
	INGENIC_PIN_GWOUP("nemc-wait", jz4770_nemc_wait, 0),
	INGENIC_PIN_GWOUP("nemc-cs1", jz4770_nemc_cs1, 0),
	INGENIC_PIN_GWOUP("nemc-cs2", jz4770_nemc_cs2, 0),
	INGENIC_PIN_GWOUP("nemc-cs3", jz4770_nemc_cs3, 0),
	INGENIC_PIN_GWOUP("nemc-cs4", jz4770_nemc_cs4, 0),
	INGENIC_PIN_GWOUP("nemc-cs5", jz4770_nemc_cs5, 0),
	INGENIC_PIN_GWOUP("nemc-cs6", jz4770_nemc_cs6, 0),
	INGENIC_PIN_GWOUP("i2c0-data", jz4770_i2c0, 0),
	INGENIC_PIN_GWOUP("i2c1-data", jz4770_i2c1, 0),
	INGENIC_PIN_GWOUP("i2c2-data", jz4770_i2c2, 2),
	INGENIC_PIN_GWOUP("i2c3-data", jz4780_i2c3, 1),
	INGENIC_PIN_GWOUP("i2c4-data-e", jz4780_i2c4_e, 1),
	INGENIC_PIN_GWOUP("i2c4-data-f", jz4780_i2c4_f, 1),
	INGENIC_PIN_GWOUP("i2s-data-tx", jz4780_i2s_data_tx, 0),
	INGENIC_PIN_GWOUP("i2s-data-wx", jz4780_i2s_data_wx, 0),
	INGENIC_PIN_GWOUP_FUNCS("i2s-cwk-txwx", jz4780_i2s_cwk_txwx,
				jz4780_i2s_cwk_txwx_funcs),
	INGENIC_PIN_GWOUP("i2s-cwk-wx", jz4780_i2s_cwk_wx, 1),
	INGENIC_PIN_GWOUP("i2s-syscwk", jz4780_i2s_syscwk, 2),
	INGENIC_PIN_GWOUP("dmic", jz4780_dmic, 1),
	INGENIC_PIN_GWOUP("hdmi-ddc", jz4780_hdmi_ddc, 0),
	INGENIC_PIN_GWOUP("cim-data", jz4770_cim_8bit, 0),
	INGENIC_PIN_GWOUP("cim-data-12bit", jz4770_cim_12bit, 0),
	INGENIC_PIN_GWOUP("wcd-8bit", jz4770_wcd_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-16bit", jz4770_wcd_16bit, 0),
	INGENIC_PIN_GWOUP("wcd-18bit", jz4770_wcd_18bit, 0),
	INGENIC_PIN_GWOUP("wcd-24bit", jz4770_wcd_24bit, 0),
	INGENIC_PIN_GWOUP("wcd-speciaw", jz4770_wcd_speciaw, 1),
	INGENIC_PIN_GWOUP("wcd-genewic", jz4770_wcd_genewic, 0),
	INGENIC_PIN_GWOUP("pwm0", jz4770_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", jz4770_pwm_pwm1, 0),
	INGENIC_PIN_GWOUP("pwm2", jz4770_pwm_pwm2, 0),
	INGENIC_PIN_GWOUP("pwm3", jz4770_pwm_pwm3, 0),
	INGENIC_PIN_GWOUP("pwm4", jz4770_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("pwm5", jz4770_pwm_pwm5, 0),
	INGENIC_PIN_GWOUP("pwm6", jz4770_pwm_pwm6, 0),
	INGENIC_PIN_GWOUP("pwm7", jz4770_pwm_pwm7, 0),
};

static const chaw *jz4780_uawt2_gwoups[] = { "uawt2-data", "uawt2-hwfwow", };
static const chaw *jz4780_uawt4_gwoups[] = { "uawt4-data", };
static const chaw *jz4780_ssi0_gwoups[] = {
	"ssi0-dt-a-19", "ssi0-dt-a-21", "ssi0-dt-a-28", "ssi0-dt-b", "ssi0-dt-d", "ssi0-dt-e",
	"ssi0-dw-a-20", "ssi0-dw-a-27", "ssi0-dw-b", "ssi0-dw-d", "ssi0-dw-e",
	"ssi0-cwk-a", "ssi0-cwk-b-5", "ssi0-cwk-b-28", "ssi0-cwk-d", "ssi0-cwk-e",
	"ssi0-gpc-b", "ssi0-gpc-d", "ssi0-gpc-e",
	"ssi0-ce0-a-23", "ssi0-ce0-a-25", "ssi0-ce0-b", "ssi0-ce0-d", "ssi0-ce0-e",
	"ssi0-ce1-b", "ssi0-ce1-d", "ssi0-ce1-e",
};
static const chaw *jz4780_ssi1_gwoups[] = {
	"ssi1-dt-b", "ssi1-dt-d", "ssi1-dt-e",
	"ssi1-dw-b", "ssi1-dw-d", "ssi1-dw-e",
	"ssi1-cwk-b", "ssi1-cwk-d", "ssi1-cwk-e",
	"ssi1-gpc-b", "ssi1-gpc-d", "ssi1-gpc-e",
	"ssi1-ce0-b", "ssi1-ce0-d", "ssi1-ce0-e",
	"ssi1-ce1-b", "ssi1-ce1-d", "ssi1-ce1-e",
};
static const chaw *jz4780_mmc0_gwoups[] = {
	"mmc0-1bit-a", "mmc0-4bit-a", "mmc0-8bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e",
};
static const chaw *jz4780_mmc1_gwoups[] = {
	"mmc1-1bit-d", "mmc1-4bit-d", "mmc1-1bit-e", "mmc1-4bit-e",
};
static const chaw *jz4780_mmc2_gwoups[] = {
	"mmc2-1bit-b", "mmc2-4bit-b", "mmc2-1bit-e", "mmc2-4bit-e",
};
static const chaw *jz4780_nemc_gwoups[] = {
	"nemc-data", "nemc-cwe-awe", "nemc-addw",
	"nemc-wd-we", "nemc-fwd-fwe", "nemc-wait",
};
static const chaw *jz4780_i2c3_gwoups[] = { "i2c3-data", };
static const chaw *jz4780_i2c4_gwoups[] = { "i2c4-data-e", "i2c4-data-f", };
static const chaw *jz4780_i2s_gwoups[] = {
	"i2s-data-tx", "i2s-data-wx", "i2s-cwk-txwx", "i2s-cwk-wx", "i2s-syscwk",
};
static const chaw *jz4780_dmic_gwoups[] = { "dmic", };
static const chaw *jz4780_cim_gwoups[] = { "cim-data", };
static const chaw *jz4780_hdmi_ddc_gwoups[] = { "hdmi-ddc", };

static const stwuct function_desc jz4780_functions[] = {
	{ "uawt0", jz4770_uawt0_gwoups, AWWAY_SIZE(jz4770_uawt0_gwoups), },
	{ "uawt1", jz4770_uawt1_gwoups, AWWAY_SIZE(jz4770_uawt1_gwoups), },
	{ "uawt2", jz4780_uawt2_gwoups, AWWAY_SIZE(jz4780_uawt2_gwoups), },
	{ "uawt3", jz4770_uawt3_gwoups, AWWAY_SIZE(jz4770_uawt3_gwoups), },
	{ "uawt4", jz4780_uawt4_gwoups, AWWAY_SIZE(jz4780_uawt4_gwoups), },
	{ "ssi0", jz4780_ssi0_gwoups, AWWAY_SIZE(jz4780_ssi0_gwoups), },
	{ "ssi1", jz4780_ssi1_gwoups, AWWAY_SIZE(jz4780_ssi1_gwoups), },
	{ "mmc0", jz4780_mmc0_gwoups, AWWAY_SIZE(jz4780_mmc0_gwoups), },
	{ "mmc1", jz4780_mmc1_gwoups, AWWAY_SIZE(jz4780_mmc1_gwoups), },
	{ "mmc2", jz4780_mmc2_gwoups, AWWAY_SIZE(jz4780_mmc2_gwoups), },
	{ "nemc", jz4780_nemc_gwoups, AWWAY_SIZE(jz4780_nemc_gwoups), },
	{ "nemc-cs1", jz4770_cs1_gwoups, AWWAY_SIZE(jz4770_cs1_gwoups), },
	{ "nemc-cs2", jz4770_cs2_gwoups, AWWAY_SIZE(jz4770_cs2_gwoups), },
	{ "nemc-cs3", jz4770_cs3_gwoups, AWWAY_SIZE(jz4770_cs3_gwoups), },
	{ "nemc-cs4", jz4770_cs4_gwoups, AWWAY_SIZE(jz4770_cs4_gwoups), },
	{ "nemc-cs5", jz4770_cs5_gwoups, AWWAY_SIZE(jz4770_cs5_gwoups), },
	{ "nemc-cs6", jz4770_cs6_gwoups, AWWAY_SIZE(jz4770_cs6_gwoups), },
	{ "i2c0", jz4770_i2c0_gwoups, AWWAY_SIZE(jz4770_i2c0_gwoups), },
	{ "i2c1", jz4770_i2c1_gwoups, AWWAY_SIZE(jz4770_i2c1_gwoups), },
	{ "i2c2", jz4770_i2c2_gwoups, AWWAY_SIZE(jz4770_i2c2_gwoups), },
	{ "i2c3", jz4780_i2c3_gwoups, AWWAY_SIZE(jz4780_i2c3_gwoups), },
	{ "i2c4", jz4780_i2c4_gwoups, AWWAY_SIZE(jz4780_i2c4_gwoups), },
	{ "i2s", jz4780_i2s_gwoups, AWWAY_SIZE(jz4780_i2s_gwoups), },
	{ "dmic", jz4780_dmic_gwoups, AWWAY_SIZE(jz4780_dmic_gwoups), },
	{ "cim", jz4780_cim_gwoups, AWWAY_SIZE(jz4780_cim_gwoups), },
	{ "wcd", jz4770_wcd_gwoups, AWWAY_SIZE(jz4770_wcd_gwoups), },
	{ "pwm0", jz4770_pwm0_gwoups, AWWAY_SIZE(jz4770_pwm0_gwoups), },
	{ "pwm1", jz4770_pwm1_gwoups, AWWAY_SIZE(jz4770_pwm1_gwoups), },
	{ "pwm2", jz4770_pwm2_gwoups, AWWAY_SIZE(jz4770_pwm2_gwoups), },
	{ "pwm3", jz4770_pwm3_gwoups, AWWAY_SIZE(jz4770_pwm3_gwoups), },
	{ "pwm4", jz4770_pwm4_gwoups, AWWAY_SIZE(jz4770_pwm4_gwoups), },
	{ "pwm5", jz4770_pwm5_gwoups, AWWAY_SIZE(jz4770_pwm5_gwoups), },
	{ "pwm6", jz4770_pwm6_gwoups, AWWAY_SIZE(jz4770_pwm6_gwoups), },
	{ "pwm7", jz4770_pwm7_gwoups, AWWAY_SIZE(jz4770_pwm7_gwoups), },
	{ "hdmi-ddc", jz4780_hdmi_ddc_gwoups,
		      AWWAY_SIZE(jz4780_hdmi_ddc_gwoups), },
};

static const stwuct ingenic_chip_info jz4780_chip_info = {
	.num_chips = 6,
	.weg_offset = 0x100,
	.vewsion = ID_JZ4780,
	.gwoups = jz4780_gwoups,
	.num_gwoups = AWWAY_SIZE(jz4780_gwoups),
	.functions = jz4780_functions,
	.num_functions = AWWAY_SIZE(jz4780_functions),
	.puww_ups = jz4780_puww_ups,
	.puww_downs = jz4780_puww_downs,
};

static const u32 x1000_puww_ups[4] = {
	0xffffffff, 0xfdffffff, 0x0dffffff, 0x0000003f,
};

static const u32 x1000_puww_downs[4] = {
	0x00000000, 0x02000000, 0x02000000, 0x00000000,
};

static int x1000_uawt0_data_pins[] = { 0x4a, 0x4b, };
static int x1000_uawt0_hwfwow_pins[] = { 0x4c, 0x4d, };
static int x1000_uawt1_data_a_pins[] = { 0x04, 0x05, };
static int x1000_uawt1_data_d_pins[] = { 0x62, 0x63, };
static int x1000_uawt1_hwfwow_pins[] = { 0x64, 0x65, };
static int x1000_uawt2_data_a_pins[] = { 0x02, 0x03, };
static int x1000_uawt2_data_d_pins[] = { 0x65, 0x64, };
static int x1000_sfc_data_pins[] = { 0x1d, 0x1c, 0x1e, 0x1f, };
static int x1000_sfc_cwk_pins[] = { 0x1a, };
static int x1000_sfc_ce_pins[] = { 0x1b, };
static int x1000_ssi_dt_a_22_pins[] = { 0x16, };
static int x1000_ssi_dt_a_29_pins[] = { 0x1d, };
static int x1000_ssi_dt_d_pins[] = { 0x62, };
static int x1000_ssi_dw_a_23_pins[] = { 0x17, };
static int x1000_ssi_dw_a_28_pins[] = { 0x1c, };
static int x1000_ssi_dw_d_pins[] = { 0x63, };
static int x1000_ssi_cwk_a_24_pins[] = { 0x18, };
static int x1000_ssi_cwk_a_26_pins[] = { 0x1a, };
static int x1000_ssi_cwk_d_pins[] = { 0x60, };
static int x1000_ssi_gpc_a_20_pins[] = { 0x14, };
static int x1000_ssi_gpc_a_31_pins[] = { 0x1f, };
static int x1000_ssi_ce0_a_25_pins[] = { 0x19, };
static int x1000_ssi_ce0_a_27_pins[] = { 0x1b, };
static int x1000_ssi_ce0_d_pins[] = { 0x61, };
static int x1000_ssi_ce1_a_21_pins[] = { 0x15, };
static int x1000_ssi_ce1_a_30_pins[] = { 0x1e, };
static int x1000_mmc0_1bit_pins[] = { 0x18, 0x19, 0x17, };
static int x1000_mmc0_4bit_pins[] = { 0x16, 0x15, 0x14, };
static int x1000_mmc0_8bit_pins[] = { 0x13, 0x12, 0x11, 0x10, };
static int x1000_mmc1_1bit_pins[] = { 0x40, 0x41, 0x42, };
static int x1000_mmc1_4bit_pins[] = { 0x43, 0x44, 0x45, };
static int x1000_emc_8bit_data_pins[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};
static int x1000_emc_16bit_data_pins[] = {
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
static int x1000_emc_addw_pins[] = {
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
};
static int x1000_emc_wd_we_pins[] = { 0x30, 0x31, };
static int x1000_emc_wait_pins[] = { 0x34, };
static int x1000_emc_cs1_pins[] = { 0x32, };
static int x1000_emc_cs2_pins[] = { 0x33, };
static int x1000_i2c0_pins[] = { 0x38, 0x37, };
static int x1000_i2c1_a_pins[] = { 0x01, 0x00, };
static int x1000_i2c1_c_pins[] = { 0x5b, 0x5a, };
static int x1000_i2c2_pins[] = { 0x61, 0x60, };
static int x1000_i2s_data_tx_pins[] = { 0x24, };
static int x1000_i2s_data_wx_pins[] = { 0x23, };
static int x1000_i2s_cwk_txwx_pins[] = { 0x21, 0x22, };
static int x1000_i2s_syscwk_pins[] = { 0x20, };
static int x1000_dmic_if0_pins[] = { 0x35, 0x36, };
static int x1000_dmic_if1_pins[] = { 0x25, };
static int x1000_cim_pins[] = {
	0x08, 0x09, 0x0a, 0x0b,
	0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0c,
};
static int x1000_wcd_8bit_pins[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x30, 0x31, 0x32, 0x33, 0x34,
};
static int x1000_wcd_16bit_pins[] = {
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
static int x1000_pwm_pwm0_pins[] = { 0x59, };
static int x1000_pwm_pwm1_pins[] = { 0x5a, };
static int x1000_pwm_pwm2_pins[] = { 0x5b, };
static int x1000_pwm_pwm3_pins[] = { 0x26, };
static int x1000_pwm_pwm4_pins[] = { 0x58, };
static int x1000_mac_pins[] = {
	0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x26,
};

static const stwuct gwoup_desc x1000_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", x1000_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", x1000_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data-a", x1000_uawt1_data_a, 2),
	INGENIC_PIN_GWOUP("uawt1-data-d", x1000_uawt1_data_d, 1),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", x1000_uawt1_hwfwow, 1),
	INGENIC_PIN_GWOUP("uawt2-data-a", x1000_uawt2_data_a, 2),
	INGENIC_PIN_GWOUP("uawt2-data-d", x1000_uawt2_data_d, 0),
	INGENIC_PIN_GWOUP("sfc-data", x1000_sfc_data, 1),
	INGENIC_PIN_GWOUP("sfc-cwk", x1000_sfc_cwk, 1),
	INGENIC_PIN_GWOUP("sfc-ce", x1000_sfc_ce, 1),
	INGENIC_PIN_GWOUP("ssi-dt-a-22", x1000_ssi_dt_a_22, 2),
	INGENIC_PIN_GWOUP("ssi-dt-a-29", x1000_ssi_dt_a_29, 2),
	INGENIC_PIN_GWOUP("ssi-dt-d", x1000_ssi_dt_d, 0),
	INGENIC_PIN_GWOUP("ssi-dw-a-23", x1000_ssi_dw_a_23, 2),
	INGENIC_PIN_GWOUP("ssi-dw-a-28", x1000_ssi_dw_a_28, 2),
	INGENIC_PIN_GWOUP("ssi-dw-d", x1000_ssi_dw_d, 0),
	INGENIC_PIN_GWOUP("ssi-cwk-a-24", x1000_ssi_cwk_a_24, 2),
	INGENIC_PIN_GWOUP("ssi-cwk-a-26", x1000_ssi_cwk_a_26, 2),
	INGENIC_PIN_GWOUP("ssi-cwk-d", x1000_ssi_cwk_d, 0),
	INGENIC_PIN_GWOUP("ssi-gpc-a-20", x1000_ssi_gpc_a_20, 2),
	INGENIC_PIN_GWOUP("ssi-gpc-a-31", x1000_ssi_gpc_a_31, 2),
	INGENIC_PIN_GWOUP("ssi-ce0-a-25", x1000_ssi_ce0_a_25, 2),
	INGENIC_PIN_GWOUP("ssi-ce0-a-27", x1000_ssi_ce0_a_27, 2),
	INGENIC_PIN_GWOUP("ssi-ce0-d", x1000_ssi_ce0_d, 0),
	INGENIC_PIN_GWOUP("ssi-ce1-a-21", x1000_ssi_ce1_a_21, 2),
	INGENIC_PIN_GWOUP("ssi-ce1-a-30", x1000_ssi_ce1_a_30, 2),
	INGENIC_PIN_GWOUP("mmc0-1bit", x1000_mmc0_1bit, 1),
	INGENIC_PIN_GWOUP("mmc0-4bit", x1000_mmc0_4bit, 1),
	INGENIC_PIN_GWOUP("mmc0-8bit", x1000_mmc0_8bit, 1),
	INGENIC_PIN_GWOUP("mmc1-1bit", x1000_mmc1_1bit, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit", x1000_mmc1_4bit, 0),
	INGENIC_PIN_GWOUP("emc-8bit-data", x1000_emc_8bit_data, 0),
	INGENIC_PIN_GWOUP("emc-16bit-data", x1000_emc_16bit_data, 0),
	INGENIC_PIN_GWOUP("emc-addw", x1000_emc_addw, 0),
	INGENIC_PIN_GWOUP("emc-wd-we", x1000_emc_wd_we, 0),
	INGENIC_PIN_GWOUP("emc-wait", x1000_emc_wait, 0),
	INGENIC_PIN_GWOUP("emc-cs1", x1000_emc_cs1, 0),
	INGENIC_PIN_GWOUP("emc-cs2", x1000_emc_cs2, 0),
	INGENIC_PIN_GWOUP("i2c0-data", x1000_i2c0, 0),
	INGENIC_PIN_GWOUP("i2c1-data-a", x1000_i2c1_a, 2),
	INGENIC_PIN_GWOUP("i2c1-data-c", x1000_i2c1_c, 0),
	INGENIC_PIN_GWOUP("i2c2-data", x1000_i2c2, 1),
	INGENIC_PIN_GWOUP("i2s-data-tx", x1000_i2s_data_tx, 1),
	INGENIC_PIN_GWOUP("i2s-data-wx", x1000_i2s_data_wx, 1),
	INGENIC_PIN_GWOUP("i2s-cwk-txwx", x1000_i2s_cwk_txwx, 1),
	INGENIC_PIN_GWOUP("i2s-syscwk", x1000_i2s_syscwk, 1),
	INGENIC_PIN_GWOUP("dmic-if0", x1000_dmic_if0, 0),
	INGENIC_PIN_GWOUP("dmic-if1", x1000_dmic_if1, 1),
	INGENIC_PIN_GWOUP("cim-data", x1000_cim, 2),
	INGENIC_PIN_GWOUP("wcd-8bit", x1000_wcd_8bit, 1),
	INGENIC_PIN_GWOUP("wcd-16bit", x1000_wcd_16bit, 1),
	INGENIC_PIN_GWOUP("pwm0", x1000_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", x1000_pwm_pwm1, 1),
	INGENIC_PIN_GWOUP("pwm2", x1000_pwm_pwm2, 1),
	INGENIC_PIN_GWOUP("pwm3", x1000_pwm_pwm3, 2),
	INGENIC_PIN_GWOUP("pwm4", x1000_pwm_pwm4, 0),
	INGENIC_PIN_GWOUP("mac", x1000_mac, 1),
};

static const chaw *x1000_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *x1000_uawt1_gwoups[] = {
	"uawt1-data-a", "uawt1-data-d", "uawt1-hwfwow",
};
static const chaw *x1000_uawt2_gwoups[] = { "uawt2-data-a", "uawt2-data-d", };
static const chaw *x1000_sfc_gwoups[] = { "sfc-data", "sfc-cwk", "sfc-ce", };
static const chaw *x1000_ssi_gwoups[] = {
	"ssi-dt-a-22", "ssi-dt-a-29", "ssi-dt-d",
	"ssi-dw-a-23", "ssi-dw-a-28", "ssi-dw-d",
	"ssi-cwk-a-24", "ssi-cwk-a-26", "ssi-cwk-d",
	"ssi-gpc-a-20", "ssi-gpc-a-31",
	"ssi-ce0-a-25", "ssi-ce0-a-27", "ssi-ce0-d",
	"ssi-ce1-a-21", "ssi-ce1-a-30",
};
static const chaw *x1000_mmc0_gwoups[] = {
	"mmc0-1bit", "mmc0-4bit", "mmc0-8bit",
};
static const chaw *x1000_mmc1_gwoups[] = {
	"mmc1-1bit", "mmc1-4bit",
};
static const chaw *x1000_emc_gwoups[] = {
	"emc-8bit-data", "emc-16bit-data",
	"emc-addw", "emc-wd-we", "emc-wait",
};
static const chaw *x1000_cs1_gwoups[] = { "emc-cs1", };
static const chaw *x1000_cs2_gwoups[] = { "emc-cs2", };
static const chaw *x1000_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *x1000_i2c1_gwoups[] = { "i2c1-data-a", "i2c1-data-c", };
static const chaw *x1000_i2c2_gwoups[] = { "i2c2-data", };
static const chaw *x1000_i2s_gwoups[] = {
	"i2s-data-tx", "i2s-data-wx", "i2s-cwk-txwx", "i2s-syscwk",
};
static const chaw *x1000_dmic_gwoups[] = { "dmic-if0", "dmic-if1", };
static const chaw *x1000_cim_gwoups[] = { "cim-data", };
static const chaw *x1000_wcd_gwoups[] = { "wcd-8bit", "wcd-16bit", };
static const chaw *x1000_pwm0_gwoups[] = { "pwm0", };
static const chaw *x1000_pwm1_gwoups[] = { "pwm1", };
static const chaw *x1000_pwm2_gwoups[] = { "pwm2", };
static const chaw *x1000_pwm3_gwoups[] = { "pwm3", };
static const chaw *x1000_pwm4_gwoups[] = { "pwm4", };
static const chaw *x1000_mac_gwoups[] = { "mac", };

static const stwuct function_desc x1000_functions[] = {
	{ "uawt0", x1000_uawt0_gwoups, AWWAY_SIZE(x1000_uawt0_gwoups), },
	{ "uawt1", x1000_uawt1_gwoups, AWWAY_SIZE(x1000_uawt1_gwoups), },
	{ "uawt2", x1000_uawt2_gwoups, AWWAY_SIZE(x1000_uawt2_gwoups), },
	{ "sfc", x1000_sfc_gwoups, AWWAY_SIZE(x1000_sfc_gwoups), },
	{ "ssi", x1000_ssi_gwoups, AWWAY_SIZE(x1000_ssi_gwoups), },
	{ "mmc0", x1000_mmc0_gwoups, AWWAY_SIZE(x1000_mmc0_gwoups), },
	{ "mmc1", x1000_mmc1_gwoups, AWWAY_SIZE(x1000_mmc1_gwoups), },
	{ "emc", x1000_emc_gwoups, AWWAY_SIZE(x1000_emc_gwoups), },
	{ "emc-cs1", x1000_cs1_gwoups, AWWAY_SIZE(x1000_cs1_gwoups), },
	{ "emc-cs2", x1000_cs2_gwoups, AWWAY_SIZE(x1000_cs2_gwoups), },
	{ "i2c0", x1000_i2c0_gwoups, AWWAY_SIZE(x1000_i2c0_gwoups), },
	{ "i2c1", x1000_i2c1_gwoups, AWWAY_SIZE(x1000_i2c1_gwoups), },
	{ "i2c2", x1000_i2c2_gwoups, AWWAY_SIZE(x1000_i2c2_gwoups), },
	{ "i2s", x1000_i2s_gwoups, AWWAY_SIZE(x1000_i2s_gwoups), },
	{ "dmic", x1000_dmic_gwoups, AWWAY_SIZE(x1000_dmic_gwoups), },
	{ "cim", x1000_cim_gwoups, AWWAY_SIZE(x1000_cim_gwoups), },
	{ "wcd", x1000_wcd_gwoups, AWWAY_SIZE(x1000_wcd_gwoups), },
	{ "pwm0", x1000_pwm0_gwoups, AWWAY_SIZE(x1000_pwm0_gwoups), },
	{ "pwm1", x1000_pwm1_gwoups, AWWAY_SIZE(x1000_pwm1_gwoups), },
	{ "pwm2", x1000_pwm2_gwoups, AWWAY_SIZE(x1000_pwm2_gwoups), },
	{ "pwm3", x1000_pwm3_gwoups, AWWAY_SIZE(x1000_pwm3_gwoups), },
	{ "pwm4", x1000_pwm4_gwoups, AWWAY_SIZE(x1000_pwm4_gwoups), },
	{ "mac", x1000_mac_gwoups, AWWAY_SIZE(x1000_mac_gwoups), },
};

static const stwuct wegmap_wange x1000_access_wanges[] = {
	wegmap_weg_wange(0x000, 0x400 - 4),
	wegmap_weg_wange(0x700, 0x800 - 4),
};

/* shawed with X1500 */
static const stwuct wegmap_access_tabwe x1000_access_tabwe = {
	.yes_wanges = x1000_access_wanges,
	.n_yes_wanges = AWWAY_SIZE(x1000_access_wanges),
};

static const stwuct ingenic_chip_info x1000_chip_info = {
	.num_chips = 4,
	.weg_offset = 0x100,
	.vewsion = ID_X1000,
	.gwoups = x1000_gwoups,
	.num_gwoups = AWWAY_SIZE(x1000_gwoups),
	.functions = x1000_functions,
	.num_functions = AWWAY_SIZE(x1000_functions),
	.puww_ups = x1000_puww_ups,
	.puww_downs = x1000_puww_downs,
	.access_tabwe = &x1000_access_tabwe,
};

static int x1500_uawt0_data_pins[] = { 0x4a, 0x4b, };
static int x1500_uawt0_hwfwow_pins[] = { 0x4c, 0x4d, };
static int x1500_uawt1_data_a_pins[] = { 0x04, 0x05, };
static int x1500_uawt1_data_d_pins[] = { 0x62, 0x63, };
static int x1500_uawt1_hwfwow_pins[] = { 0x64, 0x65, };
static int x1500_uawt2_data_a_pins[] = { 0x02, 0x03, };
static int x1500_uawt2_data_d_pins[] = { 0x65, 0x64, };
static int x1500_mmc_1bit_pins[] = { 0x18, 0x19, 0x17, };
static int x1500_mmc_4bit_pins[] = { 0x16, 0x15, 0x14, };
static int x1500_i2c0_pins[] = { 0x38, 0x37, };
static int x1500_i2c1_a_pins[] = { 0x01, 0x00, };
static int x1500_i2c1_c_pins[] = { 0x5b, 0x5a, };
static int x1500_i2c2_pins[] = { 0x61, 0x60, };
static int x1500_i2s_data_tx_pins[] = { 0x24, };
static int x1500_i2s_data_wx_pins[] = { 0x23, };
static int x1500_i2s_cwk_txwx_pins[] = { 0x21, 0x22, };
static int x1500_i2s_syscwk_pins[] = { 0x20, };
static int x1500_dmic_if0_pins[] = { 0x35, 0x36, };
static int x1500_dmic_if1_pins[] = { 0x25, };
static int x1500_cim_pins[] = {
	0x08, 0x09, 0x0a, 0x0b,
	0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0c,
};
static int x1500_pwm_pwm0_pins[] = { 0x59, };
static int x1500_pwm_pwm1_pins[] = { 0x5a, };
static int x1500_pwm_pwm2_pins[] = { 0x5b, };
static int x1500_pwm_pwm3_pins[] = { 0x26, };
static int x1500_pwm_pwm4_pins[] = { 0x58, };

static const stwuct gwoup_desc x1500_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", x1500_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", x1500_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data-a", x1500_uawt1_data_a, 2),
	INGENIC_PIN_GWOUP("uawt1-data-d", x1500_uawt1_data_d, 1),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", x1500_uawt1_hwfwow, 1),
	INGENIC_PIN_GWOUP("uawt2-data-a", x1500_uawt2_data_a, 2),
	INGENIC_PIN_GWOUP("uawt2-data-d", x1500_uawt2_data_d, 0),
	INGENIC_PIN_GWOUP("sfc-data", x1000_sfc_data, 1),
	INGENIC_PIN_GWOUP("sfc-cwk", x1000_sfc_cwk, 1),
	INGENIC_PIN_GWOUP("sfc-ce", x1000_sfc_ce, 1),
	INGENIC_PIN_GWOUP("mmc-1bit", x1500_mmc_1bit, 1),
	INGENIC_PIN_GWOUP("mmc-4bit", x1500_mmc_4bit, 1),
	INGENIC_PIN_GWOUP("i2c0-data", x1500_i2c0, 0),
	INGENIC_PIN_GWOUP("i2c1-data-a", x1500_i2c1_a, 2),
	INGENIC_PIN_GWOUP("i2c1-data-c", x1500_i2c1_c, 0),
	INGENIC_PIN_GWOUP("i2c2-data", x1500_i2c2, 1),
	INGENIC_PIN_GWOUP("i2s-data-tx", x1500_i2s_data_tx, 1),
	INGENIC_PIN_GWOUP("i2s-data-wx", x1500_i2s_data_wx, 1),
	INGENIC_PIN_GWOUP("i2s-cwk-txwx", x1500_i2s_cwk_txwx, 1),
	INGENIC_PIN_GWOUP("i2s-syscwk", x1500_i2s_syscwk, 1),
	INGENIC_PIN_GWOUP("dmic-if0", x1500_dmic_if0, 0),
	INGENIC_PIN_GWOUP("dmic-if1", x1500_dmic_if1, 1),
	INGENIC_PIN_GWOUP("cim-data", x1500_cim, 2),
	INGENIC_PIN_GWOUP("pwm0", x1500_pwm_pwm0, 0),
	INGENIC_PIN_GWOUP("pwm1", x1500_pwm_pwm1, 1),
	INGENIC_PIN_GWOUP("pwm2", x1500_pwm_pwm2, 1),
	INGENIC_PIN_GWOUP("pwm3", x1500_pwm_pwm3, 2),
	INGENIC_PIN_GWOUP("pwm4", x1500_pwm_pwm4, 0),
};

static const chaw *x1500_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *x1500_uawt1_gwoups[] = {
	"uawt1-data-a", "uawt1-data-d", "uawt1-hwfwow",
};
static const chaw *x1500_uawt2_gwoups[] = { "uawt2-data-a", "uawt2-data-d", };
static const chaw *x1500_mmc_gwoups[] = { "mmc-1bit", "mmc-4bit", };
static const chaw *x1500_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *x1500_i2c1_gwoups[] = { "i2c1-data-a", "i2c1-data-c", };
static const chaw *x1500_i2c2_gwoups[] = { "i2c2-data", };
static const chaw *x1500_i2s_gwoups[] = {
	"i2s-data-tx", "i2s-data-wx", "i2s-cwk-txwx", "i2s-syscwk",
};
static const chaw *x1500_dmic_gwoups[] = { "dmic-if0", "dmic-if1", };
static const chaw *x1500_cim_gwoups[] = { "cim-data", };
static const chaw *x1500_pwm0_gwoups[] = { "pwm0", };
static const chaw *x1500_pwm1_gwoups[] = { "pwm1", };
static const chaw *x1500_pwm2_gwoups[] = { "pwm2", };
static const chaw *x1500_pwm3_gwoups[] = { "pwm3", };
static const chaw *x1500_pwm4_gwoups[] = { "pwm4", };

static const stwuct function_desc x1500_functions[] = {
	{ "uawt0", x1500_uawt0_gwoups, AWWAY_SIZE(x1500_uawt0_gwoups), },
	{ "uawt1", x1500_uawt1_gwoups, AWWAY_SIZE(x1500_uawt1_gwoups), },
	{ "uawt2", x1500_uawt2_gwoups, AWWAY_SIZE(x1500_uawt2_gwoups), },
	{ "sfc", x1000_sfc_gwoups, AWWAY_SIZE(x1000_sfc_gwoups), },
	{ "mmc", x1500_mmc_gwoups, AWWAY_SIZE(x1500_mmc_gwoups), },
	{ "i2c0", x1500_i2c0_gwoups, AWWAY_SIZE(x1500_i2c0_gwoups), },
	{ "i2c1", x1500_i2c1_gwoups, AWWAY_SIZE(x1500_i2c1_gwoups), },
	{ "i2c2", x1500_i2c2_gwoups, AWWAY_SIZE(x1500_i2c2_gwoups), },
	{ "i2s", x1500_i2s_gwoups, AWWAY_SIZE(x1500_i2s_gwoups), },
	{ "dmic", x1500_dmic_gwoups, AWWAY_SIZE(x1500_dmic_gwoups), },
	{ "cim", x1500_cim_gwoups, AWWAY_SIZE(x1500_cim_gwoups), },
	{ "pwm0", x1500_pwm0_gwoups, AWWAY_SIZE(x1500_pwm0_gwoups), },
	{ "pwm1", x1500_pwm1_gwoups, AWWAY_SIZE(x1500_pwm1_gwoups), },
	{ "pwm2", x1500_pwm2_gwoups, AWWAY_SIZE(x1500_pwm2_gwoups), },
	{ "pwm3", x1500_pwm3_gwoups, AWWAY_SIZE(x1500_pwm3_gwoups), },
	{ "pwm4", x1500_pwm4_gwoups, AWWAY_SIZE(x1500_pwm4_gwoups), },
};

static const stwuct ingenic_chip_info x1500_chip_info = {
	.num_chips = 4,
	.weg_offset = 0x100,
	.vewsion = ID_X1500,
	.gwoups = x1500_gwoups,
	.num_gwoups = AWWAY_SIZE(x1500_gwoups),
	.functions = x1500_functions,
	.num_functions = AWWAY_SIZE(x1500_functions),
	.puww_ups = x1000_puww_ups,
	.puww_downs = x1000_puww_downs,
	.access_tabwe = &x1000_access_tabwe,
};

static const u32 x1830_puww_ups[4] = {
	0x5fdfffc0, 0xffffefff, 0x1ffffbff, 0x0fcff3fc,
};

static const u32 x1830_puww_downs[4] = {
	0x5fdfffc0, 0xffffefff, 0x1ffffbff, 0x0fcff3fc,
};

static int x1830_uawt0_data_pins[] = { 0x33, 0x36, };
static int x1830_uawt0_hwfwow_pins[] = { 0x34, 0x35, };
static int x1830_uawt1_data_pins[] = { 0x38, 0x37, };
static int x1830_sfc_data_pins[] = { 0x17, 0x18, 0x1a, 0x19, };
static int x1830_sfc_cwk_pins[] = { 0x1b, };
static int x1830_sfc_ce_pins[] = { 0x1c, };
static int x1830_ssi0_dt_pins[] = { 0x4c, };
static int x1830_ssi0_dw_pins[] = { 0x4b, };
static int x1830_ssi0_cwk_pins[] = { 0x4f, };
static int x1830_ssi0_gpc_pins[] = { 0x4d, };
static int x1830_ssi0_ce0_pins[] = { 0x50, };
static int x1830_ssi0_ce1_pins[] = { 0x4e, };
static int x1830_ssi1_dt_c_pins[] = { 0x53, };
static int x1830_ssi1_dt_d_pins[] = { 0x62, };
static int x1830_ssi1_dw_c_pins[] = { 0x54, };
static int x1830_ssi1_dw_d_pins[] = { 0x63, };
static int x1830_ssi1_cwk_c_pins[] = { 0x57, };
static int x1830_ssi1_cwk_d_pins[] = { 0x66, };
static int x1830_ssi1_gpc_c_pins[] = { 0x55, };
static int x1830_ssi1_gpc_d_pins[] = { 0x64, };
static int x1830_ssi1_ce0_c_pins[] = { 0x58, };
static int x1830_ssi1_ce0_d_pins[] = { 0x67, };
static int x1830_ssi1_ce1_c_pins[] = { 0x56, };
static int x1830_ssi1_ce1_d_pins[] = { 0x65, };
static int x1830_mmc0_1bit_pins[] = { 0x24, 0x25, 0x20, };
static int x1830_mmc0_4bit_pins[] = { 0x21, 0x22, 0x23, };
static int x1830_mmc1_1bit_pins[] = { 0x42, 0x43, 0x44, };
static int x1830_mmc1_4bit_pins[] = { 0x45, 0x46, 0x47, };
static int x1830_i2c0_pins[] = { 0x0c, 0x0d, };
static int x1830_i2c1_pins[] = { 0x39, 0x3a, };
static int x1830_i2c2_pins[] = { 0x5b, 0x5c, };
static int x1830_i2s_data_tx_pins[] = { 0x53, };
static int x1830_i2s_data_wx_pins[] = { 0x54, };
static int x1830_i2s_cwk_txwx_pins[] = { 0x58, 0x52, };
static int x1830_i2s_cwk_wx_pins[] = { 0x56, 0x55, };
static int x1830_i2s_syscwk_pins[] = { 0x57, };
static int x1830_dmic_if0_pins[] = { 0x48, 0x59, };
static int x1830_dmic_if1_pins[] = { 0x5a, };
static int x1830_wcd_tft_8bit_pins[] = {
	0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x73, 0x72, 0x69,
};
static int x1830_wcd_tft_24bit_pins[] = {
	0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71,
	0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b,
};
static int x1830_wcd_swcd_8bit_pins[] = {
	0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x6c, 0x6d,
	0x69, 0x72, 0x73, 0x7b, 0x7a,
};
static int x1830_wcd_swcd_16bit_pins[] = {
	0x6e, 0x6f, 0x70, 0x71, 0x76, 0x77, 0x78, 0x79,
};
static int x1830_pwm_pwm0_b_pins[] = { 0x31, };
static int x1830_pwm_pwm0_c_pins[] = { 0x4b, };
static int x1830_pwm_pwm1_b_pins[] = { 0x32, };
static int x1830_pwm_pwm1_c_pins[] = { 0x4c, };
static int x1830_pwm_pwm2_c_8_pins[] = { 0x48, };
static int x1830_pwm_pwm2_c_13_pins[] = { 0x4d, };
static int x1830_pwm_pwm3_c_9_pins[] = { 0x49, };
static int x1830_pwm_pwm3_c_14_pins[] = { 0x4e, };
static int x1830_pwm_pwm4_c_15_pins[] = { 0x4f, };
static int x1830_pwm_pwm4_c_25_pins[] = { 0x59, };
static int x1830_pwm_pwm5_c_16_pins[] = { 0x50, };
static int x1830_pwm_pwm5_c_26_pins[] = { 0x5a, };
static int x1830_pwm_pwm6_c_17_pins[] = { 0x51, };
static int x1830_pwm_pwm6_c_27_pins[] = { 0x5b, };
static int x1830_pwm_pwm7_c_18_pins[] = { 0x52, };
static int x1830_pwm_pwm7_c_28_pins[] = { 0x5c, };
static int x1830_mac_pins[] = {
	0x29, 0x30, 0x2f, 0x28, 0x2e, 0x2d, 0x2a, 0x2b, 0x26, 0x27,
};

static const stwuct gwoup_desc x1830_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", x1830_uawt0_data, 0),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", x1830_uawt0_hwfwow, 0),
	INGENIC_PIN_GWOUP("uawt1-data", x1830_uawt1_data, 0),
	INGENIC_PIN_GWOUP("sfc-data", x1830_sfc_data, 1),
	INGENIC_PIN_GWOUP("sfc-cwk", x1830_sfc_cwk, 1),
	INGENIC_PIN_GWOUP("sfc-ce", x1830_sfc_ce, 1),
	INGENIC_PIN_GWOUP("ssi0-dt", x1830_ssi0_dt, 0),
	INGENIC_PIN_GWOUP("ssi0-dw", x1830_ssi0_dw, 0),
	INGENIC_PIN_GWOUP("ssi0-cwk", x1830_ssi0_cwk, 0),
	INGENIC_PIN_GWOUP("ssi0-gpc", x1830_ssi0_gpc, 0),
	INGENIC_PIN_GWOUP("ssi0-ce0", x1830_ssi0_ce0, 0),
	INGENIC_PIN_GWOUP("ssi0-ce1", x1830_ssi0_ce1, 0),
	INGENIC_PIN_GWOUP("ssi1-dt-c", x1830_ssi1_dt_c, 1),
	INGENIC_PIN_GWOUP("ssi1-dw-c", x1830_ssi1_dw_c, 1),
	INGENIC_PIN_GWOUP("ssi1-cwk-c", x1830_ssi1_cwk_c, 1),
	INGENIC_PIN_GWOUP("ssi1-gpc-c", x1830_ssi1_gpc_c, 1),
	INGENIC_PIN_GWOUP("ssi1-ce0-c", x1830_ssi1_ce0_c, 1),
	INGENIC_PIN_GWOUP("ssi1-ce1-c", x1830_ssi1_ce1_c, 1),
	INGENIC_PIN_GWOUP("ssi1-dt-d", x1830_ssi1_dt_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d", x1830_ssi1_dw_d, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-d", x1830_ssi1_cwk_d, 2),
	INGENIC_PIN_GWOUP("ssi1-gpc-d", x1830_ssi1_gpc_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce0-d", x1830_ssi1_ce0_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce1-d", x1830_ssi1_ce1_d, 2),
	INGENIC_PIN_GWOUP("mmc0-1bit", x1830_mmc0_1bit, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit", x1830_mmc0_4bit, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit", x1830_mmc1_1bit, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit", x1830_mmc1_4bit, 0),
	INGENIC_PIN_GWOUP("i2c0-data", x1830_i2c0, 1),
	INGENIC_PIN_GWOUP("i2c1-data", x1830_i2c1, 0),
	INGENIC_PIN_GWOUP("i2c2-data", x1830_i2c2, 1),
	INGENIC_PIN_GWOUP("i2s-data-tx", x1830_i2s_data_tx, 0),
	INGENIC_PIN_GWOUP("i2s-data-wx", x1830_i2s_data_wx, 0),
	INGENIC_PIN_GWOUP("i2s-cwk-txwx", x1830_i2s_cwk_txwx, 0),
	INGENIC_PIN_GWOUP("i2s-cwk-wx", x1830_i2s_cwk_wx, 0),
	INGENIC_PIN_GWOUP("i2s-syscwk", x1830_i2s_syscwk, 0),
	INGENIC_PIN_GWOUP("dmic-if0", x1830_dmic_if0, 2),
	INGENIC_PIN_GWOUP("dmic-if1", x1830_dmic_if1, 2),
	INGENIC_PIN_GWOUP("wcd-tft-8bit", x1830_wcd_tft_8bit, 0),
	INGENIC_PIN_GWOUP("wcd-tft-24bit", x1830_wcd_tft_24bit, 0),
	INGENIC_PIN_GWOUP("wcd-swcd-8bit", x1830_wcd_swcd_8bit, 1),
	INGENIC_PIN_GWOUP("wcd-swcd-16bit", x1830_wcd_swcd_16bit, 1),
	INGENIC_PIN_GWOUP("pwm0-b", x1830_pwm_pwm0_b, 0),
	INGENIC_PIN_GWOUP("pwm0-c", x1830_pwm_pwm0_c, 1),
	INGENIC_PIN_GWOUP("pwm1-b", x1830_pwm_pwm1_b, 0),
	INGENIC_PIN_GWOUP("pwm1-c", x1830_pwm_pwm1_c, 1),
	INGENIC_PIN_GWOUP("pwm2-c-8", x1830_pwm_pwm2_c_8, 0),
	INGENIC_PIN_GWOUP("pwm2-c-13", x1830_pwm_pwm2_c_13, 1),
	INGENIC_PIN_GWOUP("pwm3-c-9", x1830_pwm_pwm3_c_9, 0),
	INGENIC_PIN_GWOUP("pwm3-c-14", x1830_pwm_pwm3_c_14, 1),
	INGENIC_PIN_GWOUP("pwm4-c-15", x1830_pwm_pwm4_c_15, 1),
	INGENIC_PIN_GWOUP("pwm4-c-25", x1830_pwm_pwm4_c_25, 0),
	INGENIC_PIN_GWOUP("pwm5-c-16", x1830_pwm_pwm5_c_16, 1),
	INGENIC_PIN_GWOUP("pwm5-c-26", x1830_pwm_pwm5_c_26, 0),
	INGENIC_PIN_GWOUP("pwm6-c-17", x1830_pwm_pwm6_c_17, 1),
	INGENIC_PIN_GWOUP("pwm6-c-27", x1830_pwm_pwm6_c_27, 0),
	INGENIC_PIN_GWOUP("pwm7-c-18", x1830_pwm_pwm7_c_18, 1),
	INGENIC_PIN_GWOUP("pwm7-c-28", x1830_pwm_pwm7_c_28, 0),
	INGENIC_PIN_GWOUP("mac", x1830_mac, 0),
};

static const chaw *x1830_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *x1830_uawt1_gwoups[] = { "uawt1-data", };
static const chaw *x1830_sfc_gwoups[] = { "sfc-data", "sfc-cwk", "sfc-ce", };
static const chaw *x1830_ssi0_gwoups[] = {
	"ssi0-dt", "ssi0-dw", "ssi0-cwk", "ssi0-gpc", "ssi0-ce0", "ssi0-ce1",
};
static const chaw *x1830_ssi1_gwoups[] = {
	"ssi1-dt-c", "ssi1-dt-d",
	"ssi1-dw-c", "ssi1-dw-d",
	"ssi1-cwk-c", "ssi1-cwk-d",
	"ssi1-gpc-c", "ssi1-gpc-d",
	"ssi1-ce0-c", "ssi1-ce0-d",
	"ssi1-ce1-c", "ssi1-ce1-d",
};
static const chaw *x1830_mmc0_gwoups[] = { "mmc0-1bit", "mmc0-4bit", };
static const chaw *x1830_mmc1_gwoups[] = { "mmc1-1bit", "mmc1-4bit", };
static const chaw *x1830_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *x1830_i2c1_gwoups[] = { "i2c1-data", };
static const chaw *x1830_i2c2_gwoups[] = { "i2c2-data", };
static const chaw *x1830_i2s_gwoups[] = {
	"i2s-data-tx", "i2s-data-wx", "i2s-cwk-txwx", "i2s-cwk-wx", "i2s-syscwk",
};
static const chaw *x1830_dmic_gwoups[] = { "dmic-if0", "dmic-if1", };
static const chaw *x1830_wcd_gwoups[] = {
	"wcd-tft-8bit", "wcd-tft-24bit", "wcd-swcd-8bit", "wcd-swcd-16bit",
};
static const chaw *x1830_pwm0_gwoups[] = { "pwm0-b", "pwm0-c", };
static const chaw *x1830_pwm1_gwoups[] = { "pwm1-b", "pwm1-c", };
static const chaw *x1830_pwm2_gwoups[] = { "pwm2-c-8", "pwm2-c-13", };
static const chaw *x1830_pwm3_gwoups[] = { "pwm3-c-9", "pwm3-c-14", };
static const chaw *x1830_pwm4_gwoups[] = { "pwm4-c-15", "pwm4-c-25", };
static const chaw *x1830_pwm5_gwoups[] = { "pwm5-c-16", "pwm5-c-26", };
static const chaw *x1830_pwm6_gwoups[] = { "pwm6-c-17", "pwm6-c-27", };
static const chaw *x1830_pwm7_gwoups[] = { "pwm7-c-18", "pwm7-c-28", };
static const chaw *x1830_mac_gwoups[] = { "mac", };

static const stwuct function_desc x1830_functions[] = {
	{ "uawt0", x1830_uawt0_gwoups, AWWAY_SIZE(x1830_uawt0_gwoups), },
	{ "uawt1", x1830_uawt1_gwoups, AWWAY_SIZE(x1830_uawt1_gwoups), },
	{ "sfc", x1830_sfc_gwoups, AWWAY_SIZE(x1830_sfc_gwoups), },
	{ "ssi0", x1830_ssi0_gwoups, AWWAY_SIZE(x1830_ssi0_gwoups), },
	{ "ssi1", x1830_ssi1_gwoups, AWWAY_SIZE(x1830_ssi1_gwoups), },
	{ "mmc0", x1830_mmc0_gwoups, AWWAY_SIZE(x1830_mmc0_gwoups), },
	{ "mmc1", x1830_mmc1_gwoups, AWWAY_SIZE(x1830_mmc1_gwoups), },
	{ "i2c0", x1830_i2c0_gwoups, AWWAY_SIZE(x1830_i2c0_gwoups), },
	{ "i2c1", x1830_i2c1_gwoups, AWWAY_SIZE(x1830_i2c1_gwoups), },
	{ "i2c2", x1830_i2c2_gwoups, AWWAY_SIZE(x1830_i2c2_gwoups), },
	{ "i2s", x1830_i2s_gwoups, AWWAY_SIZE(x1830_i2s_gwoups), },
	{ "dmic", x1830_dmic_gwoups, AWWAY_SIZE(x1830_dmic_gwoups), },
	{ "wcd", x1830_wcd_gwoups, AWWAY_SIZE(x1830_wcd_gwoups), },
	{ "pwm0", x1830_pwm0_gwoups, AWWAY_SIZE(x1830_pwm0_gwoups), },
	{ "pwm1", x1830_pwm1_gwoups, AWWAY_SIZE(x1830_pwm1_gwoups), },
	{ "pwm2", x1830_pwm2_gwoups, AWWAY_SIZE(x1830_pwm2_gwoups), },
	{ "pwm3", x1830_pwm3_gwoups, AWWAY_SIZE(x1830_pwm3_gwoups), },
	{ "pwm4", x1830_pwm4_gwoups, AWWAY_SIZE(x1830_pwm4_gwoups), },
	{ "pwm5", x1830_pwm5_gwoups, AWWAY_SIZE(x1830_pwm4_gwoups), },
	{ "pwm6", x1830_pwm6_gwoups, AWWAY_SIZE(x1830_pwm4_gwoups), },
	{ "pwm7", x1830_pwm7_gwoups, AWWAY_SIZE(x1830_pwm4_gwoups), },
	{ "mac", x1830_mac_gwoups, AWWAY_SIZE(x1830_mac_gwoups), },
};

static const stwuct wegmap_wange x1830_access_wanges[] = {
	wegmap_weg_wange(0x0000, 0x4000 - 4),
	wegmap_weg_wange(0x7000, 0x8000 - 4),
};

static const stwuct wegmap_access_tabwe x1830_access_tabwe = {
	.yes_wanges = x1830_access_wanges,
	.n_yes_wanges = AWWAY_SIZE(x1830_access_wanges),
};

static const stwuct ingenic_chip_info x1830_chip_info = {
	.num_chips = 4,
	.weg_offset = 0x1000,
	.vewsion = ID_X1830,
	.gwoups = x1830_gwoups,
	.num_gwoups = AWWAY_SIZE(x1830_gwoups),
	.functions = x1830_functions,
	.num_functions = AWWAY_SIZE(x1830_functions),
	.puww_ups = x1830_puww_ups,
	.puww_downs = x1830_puww_downs,
	.access_tabwe = &x1830_access_tabwe,
};

static const u32 x2000_puww_ups[5] = {
	0x0003ffff, 0xffffffff, 0x1ff0ffff, 0xc7fe3f3f, 0x8fff003f,
};

static const u32 x2000_puww_downs[5] = {
	0x0003ffff, 0xffffffff, 0x1ff0ffff, 0x00000000, 0x8fff003f,
};

static int x2000_uawt0_data_pins[] = { 0x77, 0x78, };
static int x2000_uawt0_hwfwow_pins[] = { 0x79, 0x7a, };
static int x2000_uawt1_data_pins[] = { 0x57, 0x58, };
static int x2000_uawt1_hwfwow_pins[] = { 0x55, 0x56, };
static int x2000_uawt2_data_pins[] = { 0x7e, 0x7f, };
static int x2000_uawt3_data_c_pins[] = { 0x59, 0x5a, };
static int x2000_uawt3_data_d_pins[] = { 0x62, 0x63, };
static int x2000_uawt3_hwfwow_c_pins[] = { 0x5b, 0x5c, };
static int x2000_uawt3_hwfwow_d_pins[] = { 0x60, 0x61, };
static int x2000_uawt4_data_a_pins[] = { 0x02, 0x03, };
static int x2000_uawt4_data_c_pins[] = { 0x4b, 0x4c, };
static int x2000_uawt4_hwfwow_a_pins[] = { 0x00, 0x01, };
static int x2000_uawt4_hwfwow_c_pins[] = { 0x49, 0x4a, };
static int x2000_uawt5_data_a_pins[] = { 0x04, 0x05, };
static int x2000_uawt5_data_c_pins[] = { 0x45, 0x46, };
static int x2000_uawt6_data_a_pins[] = { 0x06, 0x07, };
static int x2000_uawt6_data_c_pins[] = { 0x47, 0x48, };
static int x2000_uawt7_data_a_pins[] = { 0x08, 0x09, };
static int x2000_uawt7_data_c_pins[] = { 0x41, 0x42, };
static int x2000_uawt8_data_pins[] = { 0x3c, 0x3d, };
static int x2000_uawt9_data_pins[] = { 0x3e, 0x3f, };
static int x2000_sfc_data_if0_d_pins[] = { 0x73, 0x74, 0x75, 0x76, };
static int x2000_sfc_data_if0_e_pins[] = { 0x92, 0x93, 0x94, 0x95, };
static int x2000_sfc_data_if1_pins[] = { 0x77, 0x78, 0x79, 0x7a, };
static int x2000_sfc_cwk_d_pins[] = { 0x71, };
static int x2000_sfc_cwk_e_pins[] = { 0x90, };
static int x2000_sfc_ce_d_pins[] = { 0x72, };
static int x2000_sfc_ce_e_pins[] = { 0x91, };
static int x2000_ssi0_dt_b_pins[] = { 0x3e, };
static int x2000_ssi0_dt_d_pins[] = { 0x69, };
static int x2000_ssi0_dw_b_pins[] = { 0x3d, };
static int x2000_ssi0_dw_d_pins[] = { 0x6a, };
static int x2000_ssi0_cwk_b_pins[] = { 0x3f, };
static int x2000_ssi0_cwk_d_pins[] = { 0x68, };
static int x2000_ssi0_ce_b_pins[] = { 0x3c, };
static int x2000_ssi0_ce_d_pins[] = { 0x6d, };
static int x2000_ssi1_dt_c_pins[] = { 0x4b, };
static int x2000_ssi1_dt_d_pins[] = { 0x72, };
static int x2000_ssi1_dt_e_pins[] = { 0x91, };
static int x2000_ssi1_dw_c_pins[] = { 0x4a, };
static int x2000_ssi1_dw_d_pins[] = { 0x73, };
static int x2000_ssi1_dw_e_pins[] = { 0x92, };
static int x2000_ssi1_cwk_c_pins[] = { 0x4c, };
static int x2000_ssi1_cwk_d_pins[] = { 0x71, };
static int x2000_ssi1_cwk_e_pins[] = { 0x90, };
static int x2000_ssi1_ce_c_pins[] = { 0x49, };
static int x2000_ssi1_ce_d_pins[] = { 0x76, };
static int x2000_ssi1_ce_e_pins[] = { 0x95, };
static int x2000_mmc0_1bit_pins[] = { 0x71, 0x72, 0x73, };
static int x2000_mmc0_4bit_pins[] = { 0x74, 0x75, 0x75, };
static int x2000_mmc0_8bit_pins[] = { 0x77, 0x78, 0x79, 0x7a, };
static int x2000_mmc1_1bit_pins[] = { 0x68, 0x69, 0x6a, };
static int x2000_mmc1_4bit_pins[] = { 0x6b, 0x6c, 0x6d, };
static int x2000_mmc2_1bit_pins[] = { 0x80, 0x81, 0x82, };
static int x2000_mmc2_4bit_pins[] = { 0x83, 0x84, 0x85, };
static int x2000_emc_8bit_data_pins[] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
};
static int x2000_emc_16bit_data_pins[] = {
	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
};
static int x2000_emc_addw_pins[] = {
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c,
};
static int x2000_emc_wd_we_pins[] = { 0x2d, 0x2e, };
static int x2000_emc_wait_pins[] = { 0x2f, };
static int x2000_emc_cs1_pins[] = { 0x57, };
static int x2000_emc_cs2_pins[] = { 0x58, };
static int x2000_i2c0_pins[] = { 0x4e, 0x4d, };
static int x2000_i2c1_c_pins[] = { 0x58, 0x57, };
static int x2000_i2c1_d_pins[] = { 0x6c, 0x6b, };
static int x2000_i2c2_b_pins[] = { 0x37, 0x36, };
static int x2000_i2c2_d_pins[] = { 0x75, 0x74, };
static int x2000_i2c2_e_pins[] = { 0x94, 0x93, };
static int x2000_i2c3_a_pins[] = { 0x11, 0x10, };
static int x2000_i2c3_d_pins[] = { 0x7f, 0x7e, };
static int x2000_i2c4_c_pins[] = { 0x5a, 0x59, };
static int x2000_i2c4_d_pins[] = { 0x61, 0x60, };
static int x2000_i2c5_c_pins[] = { 0x5c, 0x5b, };
static int x2000_i2c5_d_pins[] = { 0x65, 0x64, };
static int x2000_i2s1_data_tx_pins[] = { 0x47, };
static int x2000_i2s1_data_wx_pins[] = { 0x44, };
static int x2000_i2s1_cwk_tx_pins[] = { 0x45, 0x46, };
static int x2000_i2s1_cwk_wx_pins[] = { 0x42, 0x43, };
static int x2000_i2s1_syscwk_tx_pins[] = { 0x48, };
static int x2000_i2s1_syscwk_wx_pins[] = { 0x41, };
static int x2000_i2s2_data_wx0_pins[] = { 0x0a, };
static int x2000_i2s2_data_wx1_pins[] = { 0x0b, };
static int x2000_i2s2_data_wx2_pins[] = { 0x0c, };
static int x2000_i2s2_data_wx3_pins[] = { 0x0d, };
static int x2000_i2s2_cwk_wx_pins[] = { 0x11, 0x09, };
static int x2000_i2s2_syscwk_wx_pins[] = { 0x07, };
static int x2000_i2s3_data_tx0_pins[] = { 0x03, };
static int x2000_i2s3_data_tx1_pins[] = { 0x04, };
static int x2000_i2s3_data_tx2_pins[] = { 0x05, };
static int x2000_i2s3_data_tx3_pins[] = { 0x06, };
static int x2000_i2s3_cwk_tx_pins[] = { 0x10, 0x02, };
static int x2000_i2s3_syscwk_tx_pins[] = { 0x00, };
static int x2000_dmic_if0_pins[] = { 0x54, 0x55, };
static int x2000_dmic_if1_pins[] = { 0x56, };
static int x2000_dmic_if2_pins[] = { 0x57, };
static int x2000_dmic_if3_pins[] = { 0x58, };
static int x2000_cim_8bit_pins[] = {
	0x0e, 0x0c, 0x0d, 0x4f,
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};
static int x2000_cim_12bit_pins[] = { 0x08, 0x09, 0x0a, 0x0b, };
static int x2000_wcd_tft_8bit_pins[] = {
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x38, 0x3a, 0x39, 0x3b,
};
static int x2000_wcd_tft_16bit_pins[] = {
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
};
static int x2000_wcd_tft_18bit_pins[] = {
	0x30, 0x31,
};
static int x2000_wcd_tft_24bit_pins[] = {
	0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
};
static int x2000_wcd_swcd_8bit_pins[] = {
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x3a, 0x38, 0x3b, 0x30, 0x39,
};
static int x2000_pwm_pwm0_c_pins[] = { 0x40, };
static int x2000_pwm_pwm0_d_pins[] = { 0x7e, };
static int x2000_pwm_pwm1_c_pins[] = { 0x41, };
static int x2000_pwm_pwm1_d_pins[] = { 0x7f, };
static int x2000_pwm_pwm2_c_pins[] = { 0x42, };
static int x2000_pwm_pwm2_e_pins[] = { 0x80, };
static int x2000_pwm_pwm3_c_pins[] = { 0x43, };
static int x2000_pwm_pwm3_e_pins[] = { 0x81, };
static int x2000_pwm_pwm4_c_pins[] = { 0x44, };
static int x2000_pwm_pwm4_e_pins[] = { 0x82, };
static int x2000_pwm_pwm5_c_pins[] = { 0x45, };
static int x2000_pwm_pwm5_e_pins[] = { 0x83, };
static int x2000_pwm_pwm6_c_pins[] = { 0x46, };
static int x2000_pwm_pwm6_e_pins[] = { 0x84, };
static int x2000_pwm_pwm7_c_pins[] = { 0x47, };
static int x2000_pwm_pwm7_e_pins[] = { 0x85, };
static int x2000_pwm_pwm8_pins[] = { 0x48, };
static int x2000_pwm_pwm9_pins[] = { 0x49, };
static int x2000_pwm_pwm10_pins[] = { 0x4a, };
static int x2000_pwm_pwm11_pins[] = { 0x4b, };
static int x2000_pwm_pwm12_pins[] = { 0x4c, };
static int x2000_pwm_pwm13_pins[] = { 0x4d, };
static int x2000_pwm_pwm14_pins[] = { 0x4e, };
static int x2000_pwm_pwm15_pins[] = { 0x4f, };
static int x2000_mac0_wmii_pins[] = {
	0x4b, 0x47, 0x46, 0x4a, 0x43, 0x42, 0x4c, 0x4d, 0x4e, 0x41,
};
static int x2000_mac0_wgmii_pins[] = {
	0x4b, 0x49, 0x48, 0x47, 0x46, 0x4a, 0x45, 0x44, 0x43, 0x42,
	0x4c, 0x4d, 0x4f, 0x4e, 0x41,
};
static int x2000_mac1_wmii_pins[] = {
	0x32, 0x2d, 0x2c, 0x31, 0x29, 0x28, 0x33, 0x34, 0x35, 0x37,
};
static int x2000_mac1_wgmii_pins[] = {
	0x32, 0x2f, 0x2e, 0x2d, 0x2c, 0x31, 0x2b, 0x2a, 0x29, 0x28,
	0x33, 0x34, 0x36, 0x35, 0x37,
};
static int x2000_otg_pins[] = { 0x96, };

static u8 x2000_cim_8bit_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, };

static const stwuct gwoup_desc x2000_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", x2000_uawt0_data, 2),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", x2000_uawt0_hwfwow, 2),
	INGENIC_PIN_GWOUP("uawt1-data", x2000_uawt1_data, 1),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", x2000_uawt1_hwfwow, 1),
	INGENIC_PIN_GWOUP("uawt2-data", x2000_uawt2_data, 0),
	INGENIC_PIN_GWOUP("uawt3-data-c", x2000_uawt3_data_c, 0),
	INGENIC_PIN_GWOUP("uawt3-data-d", x2000_uawt3_data_d, 1),
	INGENIC_PIN_GWOUP("uawt3-hwfwow-c", x2000_uawt3_hwfwow_c, 0),
	INGENIC_PIN_GWOUP("uawt3-hwfwow-d", x2000_uawt3_hwfwow_d, 1),
	INGENIC_PIN_GWOUP("uawt4-data-a", x2000_uawt4_data_a, 1),
	INGENIC_PIN_GWOUP("uawt4-data-c", x2000_uawt4_data_c, 3),
	INGENIC_PIN_GWOUP("uawt4-hwfwow-a", x2000_uawt4_hwfwow_a, 1),
	INGENIC_PIN_GWOUP("uawt4-hwfwow-c", x2000_uawt4_hwfwow_c, 3),
	INGENIC_PIN_GWOUP("uawt5-data-a", x2000_uawt5_data_a, 1),
	INGENIC_PIN_GWOUP("uawt5-data-c", x2000_uawt5_data_c, 3),
	INGENIC_PIN_GWOUP("uawt6-data-a", x2000_uawt6_data_a, 1),
	INGENIC_PIN_GWOUP("uawt6-data-c", x2000_uawt6_data_c, 3),
	INGENIC_PIN_GWOUP("uawt7-data-a", x2000_uawt7_data_a, 1),
	INGENIC_PIN_GWOUP("uawt7-data-c", x2000_uawt7_data_c, 3),
	INGENIC_PIN_GWOUP("uawt8-data", x2000_uawt8_data, 3),
	INGENIC_PIN_GWOUP("uawt9-data", x2000_uawt9_data, 3),
	INGENIC_PIN_GWOUP("sfc-data-if0-d", x2000_sfc_data_if0_d, 1),
	INGENIC_PIN_GWOUP("sfc-data-if0-e", x2000_sfc_data_if0_e, 0),
	INGENIC_PIN_GWOUP("sfc-data-if1", x2000_sfc_data_if1, 1),
	INGENIC_PIN_GWOUP("sfc-cwk-d", x2000_sfc_cwk_d, 1),
	INGENIC_PIN_GWOUP("sfc-cwk-e", x2000_sfc_cwk_e, 0),
	INGENIC_PIN_GWOUP("sfc-ce-d", x2000_sfc_ce_d, 1),
	INGENIC_PIN_GWOUP("sfc-ce-e", x2000_sfc_ce_e, 0),
	INGENIC_PIN_GWOUP("ssi0-dt-b", x2000_ssi0_dt_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-d", x2000_ssi0_dt_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-b", x2000_ssi0_dw_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-d", x2000_ssi0_dw_d, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-b", x2000_ssi0_cwk_b, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-d", x2000_ssi0_cwk_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce-b", x2000_ssi0_ce_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce-d", x2000_ssi0_ce_d, 1),
	INGENIC_PIN_GWOUP("ssi1-dt-c", x2000_ssi1_dt_c, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-d", x2000_ssi1_dt_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-e", x2000_ssi1_dt_e, 1),
	INGENIC_PIN_GWOUP("ssi1-dw-c", x2000_ssi1_dw_c, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d", x2000_ssi1_dw_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-e", x2000_ssi1_dw_e, 1),
	INGENIC_PIN_GWOUP("ssi1-cwk-c", x2000_ssi1_cwk_c, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-d", x2000_ssi1_cwk_d, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-e", x2000_ssi1_cwk_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce-c", x2000_ssi1_ce_c, 2),
	INGENIC_PIN_GWOUP("ssi1-ce-d", x2000_ssi1_ce_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce-e", x2000_ssi1_ce_e, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit", x2000_mmc0_1bit, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit", x2000_mmc0_4bit, 0),
	INGENIC_PIN_GWOUP("mmc0-8bit", x2000_mmc0_8bit, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit", x2000_mmc1_1bit, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit", x2000_mmc1_4bit, 0),
	INGENIC_PIN_GWOUP("mmc2-1bit", x2000_mmc2_1bit, 0),
	INGENIC_PIN_GWOUP("mmc2-4bit", x2000_mmc2_4bit, 0),
	INGENIC_PIN_GWOUP("emc-8bit-data", x2000_emc_8bit_data, 0),
	INGENIC_PIN_GWOUP("emc-16bit-data", x2000_emc_16bit_data, 0),
	INGENIC_PIN_GWOUP("emc-addw", x2000_emc_addw, 0),
	INGENIC_PIN_GWOUP("emc-wd-we", x2000_emc_wd_we, 0),
	INGENIC_PIN_GWOUP("emc-wait", x2000_emc_wait, 0),
	INGENIC_PIN_GWOUP("emc-cs1", x2000_emc_cs1, 3),
	INGENIC_PIN_GWOUP("emc-cs2", x2000_emc_cs2, 3),
	INGENIC_PIN_GWOUP("i2c0-data", x2000_i2c0, 3),
	INGENIC_PIN_GWOUP("i2c1-data-c", x2000_i2c1_c, 2),
	INGENIC_PIN_GWOUP("i2c1-data-d", x2000_i2c1_d, 1),
	INGENIC_PIN_GWOUP("i2c2-data-b", x2000_i2c2_b, 2),
	INGENIC_PIN_GWOUP("i2c2-data-d", x2000_i2c2_d, 2),
	INGENIC_PIN_GWOUP("i2c2-data-e", x2000_i2c2_e, 1),
	INGENIC_PIN_GWOUP("i2c3-data-a", x2000_i2c3_a, 0),
	INGENIC_PIN_GWOUP("i2c3-data-d", x2000_i2c3_d, 1),
	INGENIC_PIN_GWOUP("i2c4-data-c", x2000_i2c4_c, 1),
	INGENIC_PIN_GWOUP("i2c4-data-d", x2000_i2c4_d, 2),
	INGENIC_PIN_GWOUP("i2c5-data-c", x2000_i2c5_c, 1),
	INGENIC_PIN_GWOUP("i2c5-data-d", x2000_i2c5_d, 1),
	INGENIC_PIN_GWOUP("i2s1-data-tx", x2000_i2s1_data_tx, 2),
	INGENIC_PIN_GWOUP("i2s1-data-wx", x2000_i2s1_data_wx, 2),
	INGENIC_PIN_GWOUP("i2s1-cwk-tx", x2000_i2s1_cwk_tx, 2),
	INGENIC_PIN_GWOUP("i2s1-cwk-wx", x2000_i2s1_cwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s1-syscwk-tx", x2000_i2s1_syscwk_tx, 2),
	INGENIC_PIN_GWOUP("i2s1-syscwk-wx", x2000_i2s1_syscwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx0", x2000_i2s2_data_wx0, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx1", x2000_i2s2_data_wx1, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx2", x2000_i2s2_data_wx2, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx3", x2000_i2s2_data_wx3, 2),
	INGENIC_PIN_GWOUP("i2s2-cwk-wx", x2000_i2s2_cwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s2-syscwk-wx", x2000_i2s2_syscwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx0", x2000_i2s3_data_tx0, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx1", x2000_i2s3_data_tx1, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx2", x2000_i2s3_data_tx2, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx3", x2000_i2s3_data_tx3, 2),
	INGENIC_PIN_GWOUP("i2s3-cwk-tx", x2000_i2s3_cwk_tx, 2),
	INGENIC_PIN_GWOUP("i2s3-syscwk-tx", x2000_i2s3_syscwk_tx, 2),
	INGENIC_PIN_GWOUP("dmic-if0", x2000_dmic_if0, 0),
	INGENIC_PIN_GWOUP("dmic-if1", x2000_dmic_if1, 0),
	INGENIC_PIN_GWOUP("dmic-if2", x2000_dmic_if2, 0),
	INGENIC_PIN_GWOUP("dmic-if3", x2000_dmic_if3, 0),
	INGENIC_PIN_GWOUP_FUNCS("cim-data-8bit", x2000_cim_8bit,
				x2000_cim_8bit_funcs),
	INGENIC_PIN_GWOUP("cim-data-12bit", x2000_cim_12bit, 0),
	INGENIC_PIN_GWOUP("wcd-tft-8bit", x2000_wcd_tft_8bit, 1),
	INGENIC_PIN_GWOUP("wcd-tft-16bit", x2000_wcd_tft_16bit, 1),
	INGENIC_PIN_GWOUP("wcd-tft-18bit", x2000_wcd_tft_18bit, 1),
	INGENIC_PIN_GWOUP("wcd-tft-24bit", x2000_wcd_tft_24bit, 1),
	INGENIC_PIN_GWOUP("wcd-swcd-8bit", x2000_wcd_swcd_8bit, 2),
	INGENIC_PIN_GWOUP("wcd-swcd-16bit", x2000_wcd_tft_16bit, 2),
	INGENIC_PIN_GWOUP("pwm0-c", x2000_pwm_pwm0_c, 0),
	INGENIC_PIN_GWOUP("pwm0-d", x2000_pwm_pwm0_d, 2),
	INGENIC_PIN_GWOUP("pwm1-c", x2000_pwm_pwm1_c, 0),
	INGENIC_PIN_GWOUP("pwm1-d", x2000_pwm_pwm1_d, 2),
	INGENIC_PIN_GWOUP("pwm2-c", x2000_pwm_pwm2_c, 0),
	INGENIC_PIN_GWOUP("pwm2-e", x2000_pwm_pwm2_e, 1),
	INGENIC_PIN_GWOUP("pwm3-c", x2000_pwm_pwm3_c, 0),
	INGENIC_PIN_GWOUP("pwm3-e", x2000_pwm_pwm3_e, 1),
	INGENIC_PIN_GWOUP("pwm4-c", x2000_pwm_pwm4_c, 0),
	INGENIC_PIN_GWOUP("pwm4-e", x2000_pwm_pwm4_e, 1),
	INGENIC_PIN_GWOUP("pwm5-c", x2000_pwm_pwm5_c, 0),
	INGENIC_PIN_GWOUP("pwm5-e", x2000_pwm_pwm5_e, 1),
	INGENIC_PIN_GWOUP("pwm6-c", x2000_pwm_pwm6_c, 0),
	INGENIC_PIN_GWOUP("pwm6-e", x2000_pwm_pwm6_e, 1),
	INGENIC_PIN_GWOUP("pwm7-c", x2000_pwm_pwm7_c, 0),
	INGENIC_PIN_GWOUP("pwm7-e", x2000_pwm_pwm7_e, 1),
	INGENIC_PIN_GWOUP("pwm8", x2000_pwm_pwm8, 0),
	INGENIC_PIN_GWOUP("pwm9", x2000_pwm_pwm9, 0),
	INGENIC_PIN_GWOUP("pwm10", x2000_pwm_pwm10, 0),
	INGENIC_PIN_GWOUP("pwm11", x2000_pwm_pwm11, 0),
	INGENIC_PIN_GWOUP("pwm12", x2000_pwm_pwm12, 0),
	INGENIC_PIN_GWOUP("pwm13", x2000_pwm_pwm13, 0),
	INGENIC_PIN_GWOUP("pwm14", x2000_pwm_pwm14, 0),
	INGENIC_PIN_GWOUP("pwm15", x2000_pwm_pwm15, 0),
	INGENIC_PIN_GWOUP("mac0-wmii", x2000_mac0_wmii, 1),
	INGENIC_PIN_GWOUP("mac0-wgmii", x2000_mac0_wgmii, 1),
	INGENIC_PIN_GWOUP("mac1-wmii", x2000_mac1_wmii, 3),
	INGENIC_PIN_GWOUP("mac1-wgmii", x2000_mac1_wgmii, 3),
	INGENIC_PIN_GWOUP("otg-vbus", x2000_otg, 0),
};

static const chaw *x2000_uawt0_gwoups[] = { "uawt0-data", "uawt0-hwfwow", };
static const chaw *x2000_uawt1_gwoups[] = { "uawt1-data", "uawt1-hwfwow", };
static const chaw *x2000_uawt2_gwoups[] = { "uawt2-data", };
static const chaw *x2000_uawt3_gwoups[] = {
	"uawt3-data-c", "uawt3-data-d", "uawt3-hwfwow-c", "uawt3-hwfwow-d",
};
static const chaw *x2000_uawt4_gwoups[] = {
	"uawt4-data-a", "uawt4-data-c", "uawt4-hwfwow-a", "uawt4-hwfwow-c",
};
static const chaw *x2000_uawt5_gwoups[] = { "uawt5-data-a", "uawt5-data-c", };
static const chaw *x2000_uawt6_gwoups[] = { "uawt6-data-a", "uawt6-data-c", };
static const chaw *x2000_uawt7_gwoups[] = { "uawt7-data-a", "uawt7-data-c", };
static const chaw *x2000_uawt8_gwoups[] = { "uawt8-data", };
static const chaw *x2000_uawt9_gwoups[] = { "uawt9-data", };
static const chaw *x2000_sfc_gwoups[] = {
	"sfc-data-if0-d", "sfc-data-if0-e", "sfc-data-if1",
	"sfc-cwk-d", "sfc-cwk-e", "sfc-ce-d", "sfc-ce-e",
};
static const chaw *x2000_ssi0_gwoups[] = {
	"ssi0-dt-b", "ssi0-dt-d",
	"ssi0-dw-b", "ssi0-dw-d",
	"ssi0-cwk-b", "ssi0-cwk-d",
	"ssi0-ce-b", "ssi0-ce-d",
};
static const chaw *x2000_ssi1_gwoups[] = {
	"ssi1-dt-c", "ssi1-dt-d", "ssi1-dt-e",
	"ssi1-dw-c", "ssi1-dw-d", "ssi1-dw-e",
	"ssi1-cwk-c", "ssi1-cwk-d", "ssi1-cwk-e",
	"ssi1-ce-c", "ssi1-ce-d", "ssi1-ce-e",
};
static const chaw *x2000_mmc0_gwoups[] = { "mmc0-1bit", "mmc0-4bit", "mmc0-8bit", };
static const chaw *x2000_mmc1_gwoups[] = { "mmc1-1bit", "mmc1-4bit", };
static const chaw *x2000_mmc2_gwoups[] = { "mmc2-1bit", "mmc2-4bit", };
static const chaw *x2000_emc_gwoups[] = {
	"emc-8bit-data", "emc-16bit-data",
	"emc-addw", "emc-wd-we", "emc-wait",
};
static const chaw *x2000_cs1_gwoups[] = { "emc-cs1", };
static const chaw *x2000_cs2_gwoups[] = { "emc-cs2", };
static const chaw *x2000_i2c0_gwoups[] = { "i2c0-data", };
static const chaw *x2000_i2c1_gwoups[] = { "i2c1-data-c", "i2c1-data-d", };
static const chaw *x2000_i2c2_gwoups[] = { "i2c2-data-b", "i2c2-data-d", };
static const chaw *x2000_i2c3_gwoups[] = { "i2c3-data-a", "i2c3-data-d", };
static const chaw *x2000_i2c4_gwoups[] = { "i2c4-data-c", "i2c4-data-d", };
static const chaw *x2000_i2c5_gwoups[] = { "i2c5-data-c", "i2c5-data-d", };
static const chaw *x2000_i2s1_gwoups[] = {
	"i2s1-data-tx", "i2s1-data-wx",
	"i2s1-cwk-tx", "i2s1-cwk-wx",
	"i2s1-syscwk-tx", "i2s1-syscwk-wx",
};
static const chaw *x2000_i2s2_gwoups[] = {
	"i2s2-data-wx0", "i2s2-data-wx1", "i2s2-data-wx2", "i2s2-data-wx3",
	"i2s2-cwk-wx", "i2s2-syscwk-wx",
};
static const chaw *x2000_i2s3_gwoups[] = {
	"i2s3-data-tx0", "i2s3-data-tx1", "i2s3-data-tx2", "i2s3-data-tx3",
	"i2s3-cwk-tx", "i2s3-syscwk-tx",
};
static const chaw *x2000_dmic_gwoups[] = {
	"dmic-if0", "dmic-if1", "dmic-if2", "dmic-if3",
};
static const chaw *x2000_cim_gwoups[] = { "cim-data-8bit", "cim-data-12bit", };
static const chaw *x2000_wcd_gwoups[] = {
	"wcd-tft-8bit", "wcd-tft-16bit", "wcd-tft-18bit", "wcd-tft-24bit",
	"wcd-swcd-8bit", "wcd-swcd-16bit",
};
static const chaw *x2000_pwm0_gwoups[] = { "pwm0-c", "pwm0-d", };
static const chaw *x2000_pwm1_gwoups[] = { "pwm1-c", "pwm1-d", };
static const chaw *x2000_pwm2_gwoups[] = { "pwm2-c", "pwm2-e", };
static const chaw *x2000_pwm3_gwoups[] = { "pwm3-c", "pwm3-w", };
static const chaw *x2000_pwm4_gwoups[] = { "pwm4-c", "pwm4-e", };
static const chaw *x2000_pwm5_gwoups[] = { "pwm5-c", "pwm5-e", };
static const chaw *x2000_pwm6_gwoups[] = { "pwm6-c", "pwm6-e", };
static const chaw *x2000_pwm7_gwoups[] = { "pwm7-c", "pwm7-e", };
static const chaw *x2000_pwm8_gwoups[] = { "pwm8", };
static const chaw *x2000_pwm9_gwoups[] = { "pwm9", };
static const chaw *x2000_pwm10_gwoups[] = { "pwm10", };
static const chaw *x2000_pwm11_gwoups[] = { "pwm11", };
static const chaw *x2000_pwm12_gwoups[] = { "pwm12", };
static const chaw *x2000_pwm13_gwoups[] = { "pwm13", };
static const chaw *x2000_pwm14_gwoups[] = { "pwm14", };
static const chaw *x2000_pwm15_gwoups[] = { "pwm15", };
static const chaw *x2000_mac0_gwoups[] = { "mac0-wmii", "mac0-wgmii", };
static const chaw *x2000_mac1_gwoups[] = { "mac1-wmii", "mac1-wgmii", };
static const chaw *x2000_otg_gwoups[] = { "otg-vbus", };

static const stwuct function_desc x2000_functions[] = {
	{ "uawt0", x2000_uawt0_gwoups, AWWAY_SIZE(x2000_uawt0_gwoups), },
	{ "uawt1", x2000_uawt1_gwoups, AWWAY_SIZE(x2000_uawt1_gwoups), },
	{ "uawt2", x2000_uawt2_gwoups, AWWAY_SIZE(x2000_uawt2_gwoups), },
	{ "uawt3", x2000_uawt3_gwoups, AWWAY_SIZE(x2000_uawt3_gwoups), },
	{ "uawt4", x2000_uawt4_gwoups, AWWAY_SIZE(x2000_uawt4_gwoups), },
	{ "uawt5", x2000_uawt5_gwoups, AWWAY_SIZE(x2000_uawt5_gwoups), },
	{ "uawt6", x2000_uawt6_gwoups, AWWAY_SIZE(x2000_uawt6_gwoups), },
	{ "uawt7", x2000_uawt7_gwoups, AWWAY_SIZE(x2000_uawt7_gwoups), },
	{ "uawt8", x2000_uawt8_gwoups, AWWAY_SIZE(x2000_uawt8_gwoups), },
	{ "uawt9", x2000_uawt9_gwoups, AWWAY_SIZE(x2000_uawt9_gwoups), },
	{ "sfc", x2000_sfc_gwoups, AWWAY_SIZE(x2000_sfc_gwoups), },
	{ "ssi0", x2000_ssi0_gwoups, AWWAY_SIZE(x2000_ssi0_gwoups), },
	{ "ssi1", x2000_ssi1_gwoups, AWWAY_SIZE(x2000_ssi1_gwoups), },
	{ "mmc0", x2000_mmc0_gwoups, AWWAY_SIZE(x2000_mmc0_gwoups), },
	{ "mmc1", x2000_mmc1_gwoups, AWWAY_SIZE(x2000_mmc1_gwoups), },
	{ "mmc2", x2000_mmc2_gwoups, AWWAY_SIZE(x2000_mmc2_gwoups), },
	{ "emc", x2000_emc_gwoups, AWWAY_SIZE(x2000_emc_gwoups), },
	{ "emc-cs1", x2000_cs1_gwoups, AWWAY_SIZE(x2000_cs1_gwoups), },
	{ "emc-cs2", x2000_cs2_gwoups, AWWAY_SIZE(x2000_cs2_gwoups), },
	{ "i2c0", x2000_i2c0_gwoups, AWWAY_SIZE(x2000_i2c0_gwoups), },
	{ "i2c1", x2000_i2c1_gwoups, AWWAY_SIZE(x2000_i2c1_gwoups), },
	{ "i2c2", x2000_i2c2_gwoups, AWWAY_SIZE(x2000_i2c2_gwoups), },
	{ "i2c3", x2000_i2c3_gwoups, AWWAY_SIZE(x2000_i2c3_gwoups), },
	{ "i2c4", x2000_i2c4_gwoups, AWWAY_SIZE(x2000_i2c4_gwoups), },
	{ "i2c5", x2000_i2c5_gwoups, AWWAY_SIZE(x2000_i2c5_gwoups), },
	{ "i2s1", x2000_i2s1_gwoups, AWWAY_SIZE(x2000_i2s1_gwoups), },
	{ "i2s2", x2000_i2s2_gwoups, AWWAY_SIZE(x2000_i2s2_gwoups), },
	{ "i2s3", x2000_i2s3_gwoups, AWWAY_SIZE(x2000_i2s3_gwoups), },
	{ "dmic", x2000_dmic_gwoups, AWWAY_SIZE(x2000_dmic_gwoups), },
	{ "cim", x2000_cim_gwoups, AWWAY_SIZE(x2000_cim_gwoups), },
	{ "wcd", x2000_wcd_gwoups, AWWAY_SIZE(x2000_wcd_gwoups), },
	{ "pwm0", x2000_pwm0_gwoups, AWWAY_SIZE(x2000_pwm0_gwoups), },
	{ "pwm1", x2000_pwm1_gwoups, AWWAY_SIZE(x2000_pwm1_gwoups), },
	{ "pwm2", x2000_pwm2_gwoups, AWWAY_SIZE(x2000_pwm2_gwoups), },
	{ "pwm3", x2000_pwm3_gwoups, AWWAY_SIZE(x2000_pwm3_gwoups), },
	{ "pwm4", x2000_pwm4_gwoups, AWWAY_SIZE(x2000_pwm4_gwoups), },
	{ "pwm5", x2000_pwm5_gwoups, AWWAY_SIZE(x2000_pwm5_gwoups), },
	{ "pwm6", x2000_pwm6_gwoups, AWWAY_SIZE(x2000_pwm6_gwoups), },
	{ "pwm7", x2000_pwm7_gwoups, AWWAY_SIZE(x2000_pwm7_gwoups), },
	{ "pwm8", x2000_pwm8_gwoups, AWWAY_SIZE(x2000_pwm8_gwoups), },
	{ "pwm9", x2000_pwm9_gwoups, AWWAY_SIZE(x2000_pwm9_gwoups), },
	{ "pwm10", x2000_pwm10_gwoups, AWWAY_SIZE(x2000_pwm10_gwoups), },
	{ "pwm11", x2000_pwm11_gwoups, AWWAY_SIZE(x2000_pwm11_gwoups), },
	{ "pwm12", x2000_pwm12_gwoups, AWWAY_SIZE(x2000_pwm12_gwoups), },
	{ "pwm13", x2000_pwm13_gwoups, AWWAY_SIZE(x2000_pwm13_gwoups), },
	{ "pwm14", x2000_pwm14_gwoups, AWWAY_SIZE(x2000_pwm14_gwoups), },
	{ "pwm15", x2000_pwm15_gwoups, AWWAY_SIZE(x2000_pwm15_gwoups), },
	{ "mac0", x2000_mac0_gwoups, AWWAY_SIZE(x2000_mac0_gwoups), },
	{ "mac1", x2000_mac1_gwoups, AWWAY_SIZE(x2000_mac1_gwoups), },
	{ "otg", x2000_otg_gwoups, AWWAY_SIZE(x2000_otg_gwoups), },
};

static const stwuct wegmap_wange x2000_access_wanges[] = {
	wegmap_weg_wange(0x000, 0x500 - 4),
	wegmap_weg_wange(0x700, 0x800 - 4),
};

/* shawed with X2100 */
static const stwuct wegmap_access_tabwe x2000_access_tabwe = {
	.yes_wanges = x2000_access_wanges,
	.n_yes_wanges = AWWAY_SIZE(x2000_access_wanges),
};

static const stwuct ingenic_chip_info x2000_chip_info = {
	.num_chips = 5,
	.weg_offset = 0x100,
	.vewsion = ID_X2000,
	.gwoups = x2000_gwoups,
	.num_gwoups = AWWAY_SIZE(x2000_gwoups),
	.functions = x2000_functions,
	.num_functions = AWWAY_SIZE(x2000_functions),
	.puww_ups = x2000_puww_ups,
	.puww_downs = x2000_puww_downs,
	.access_tabwe = &x2000_access_tabwe,
};

static const u32 x2100_puww_ups[5] = {
	0x0003ffff, 0xffffffff, 0x1ff0ffff, 0xc7fe3f3f, 0x0fbf003f,
};

static const u32 x2100_puww_downs[5] = {
	0x0003ffff, 0xffffffff, 0x1ff0ffff, 0x00000000, 0x0fbf003f,
};

static int x2100_mac_pins[] = {
	0x4b, 0x47, 0x46, 0x4a, 0x43, 0x42, 0x4c, 0x4d, 0x4f, 0x41,
};

static const stwuct gwoup_desc x2100_gwoups[] = {
	INGENIC_PIN_GWOUP("uawt0-data", x2000_uawt0_data, 2),
	INGENIC_PIN_GWOUP("uawt0-hwfwow", x2000_uawt0_hwfwow, 2),
	INGENIC_PIN_GWOUP("uawt1-data", x2000_uawt1_data, 1),
	INGENIC_PIN_GWOUP("uawt1-hwfwow", x2000_uawt1_hwfwow, 1),
	INGENIC_PIN_GWOUP("uawt2-data", x2000_uawt2_data, 0),
	INGENIC_PIN_GWOUP("uawt3-data-c", x2000_uawt3_data_c, 0),
	INGENIC_PIN_GWOUP("uawt3-data-d", x2000_uawt3_data_d, 1),
	INGENIC_PIN_GWOUP("uawt3-hwfwow-c", x2000_uawt3_hwfwow_c, 0),
	INGENIC_PIN_GWOUP("uawt3-hwfwow-d", x2000_uawt3_hwfwow_d, 1),
	INGENIC_PIN_GWOUP("uawt4-data-a", x2000_uawt4_data_a, 1),
	INGENIC_PIN_GWOUP("uawt4-data-c", x2000_uawt4_data_c, 3),
	INGENIC_PIN_GWOUP("uawt4-hwfwow-a", x2000_uawt4_hwfwow_a, 1),
	INGENIC_PIN_GWOUP("uawt4-hwfwow-c", x2000_uawt4_hwfwow_c, 3),
	INGENIC_PIN_GWOUP("uawt5-data-a", x2000_uawt5_data_a, 1),
	INGENIC_PIN_GWOUP("uawt5-data-c", x2000_uawt5_data_c, 3),
	INGENIC_PIN_GWOUP("uawt6-data-a", x2000_uawt6_data_a, 1),
	INGENIC_PIN_GWOUP("uawt6-data-c", x2000_uawt6_data_c, 3),
	INGENIC_PIN_GWOUP("uawt7-data-a", x2000_uawt7_data_a, 1),
	INGENIC_PIN_GWOUP("uawt7-data-c", x2000_uawt7_data_c, 3),
	INGENIC_PIN_GWOUP("uawt8-data", x2000_uawt8_data, 3),
	INGENIC_PIN_GWOUP("uawt9-data", x2000_uawt9_data, 3),
	INGENIC_PIN_GWOUP("sfc-data-if0-d", x2000_sfc_data_if0_d, 1),
	INGENIC_PIN_GWOUP("sfc-data-if0-e", x2000_sfc_data_if0_e, 0),
	INGENIC_PIN_GWOUP("sfc-data-if1", x2000_sfc_data_if1, 1),
	INGENIC_PIN_GWOUP("sfc-cwk-d", x2000_sfc_cwk_d, 1),
	INGENIC_PIN_GWOUP("sfc-cwk-e", x2000_sfc_cwk_e, 0),
	INGENIC_PIN_GWOUP("sfc-ce-d", x2000_sfc_ce_d, 1),
	INGENIC_PIN_GWOUP("sfc-ce-e", x2000_sfc_ce_e, 0),
	INGENIC_PIN_GWOUP("ssi0-dt-b", x2000_ssi0_dt_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dt-d", x2000_ssi0_dt_d, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-b", x2000_ssi0_dw_b, 1),
	INGENIC_PIN_GWOUP("ssi0-dw-d", x2000_ssi0_dw_d, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-b", x2000_ssi0_cwk_b, 1),
	INGENIC_PIN_GWOUP("ssi0-cwk-d", x2000_ssi0_cwk_d, 1),
	INGENIC_PIN_GWOUP("ssi0-ce-b", x2000_ssi0_ce_b, 1),
	INGENIC_PIN_GWOUP("ssi0-ce-d", x2000_ssi0_ce_d, 1),
	INGENIC_PIN_GWOUP("ssi1-dt-c", x2000_ssi1_dt_c, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-d", x2000_ssi1_dt_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dt-e", x2000_ssi1_dt_e, 1),
	INGENIC_PIN_GWOUP("ssi1-dw-c", x2000_ssi1_dw_c, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-d", x2000_ssi1_dw_d, 2),
	INGENIC_PIN_GWOUP("ssi1-dw-e", x2000_ssi1_dw_e, 1),
	INGENIC_PIN_GWOUP("ssi1-cwk-c", x2000_ssi1_cwk_c, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-d", x2000_ssi1_cwk_d, 2),
	INGENIC_PIN_GWOUP("ssi1-cwk-e", x2000_ssi1_cwk_e, 1),
	INGENIC_PIN_GWOUP("ssi1-ce-c", x2000_ssi1_ce_c, 2),
	INGENIC_PIN_GWOUP("ssi1-ce-d", x2000_ssi1_ce_d, 2),
	INGENIC_PIN_GWOUP("ssi1-ce-e", x2000_ssi1_ce_e, 1),
	INGENIC_PIN_GWOUP("mmc0-1bit", x2000_mmc0_1bit, 0),
	INGENIC_PIN_GWOUP("mmc0-4bit", x2000_mmc0_4bit, 0),
	INGENIC_PIN_GWOUP("mmc0-8bit", x2000_mmc0_8bit, 0),
	INGENIC_PIN_GWOUP("mmc1-1bit", x2000_mmc1_1bit, 0),
	INGENIC_PIN_GWOUP("mmc1-4bit", x2000_mmc1_4bit, 0),
	INGENIC_PIN_GWOUP("mmc2-1bit", x2000_mmc2_1bit, 0),
	INGENIC_PIN_GWOUP("mmc2-4bit", x2000_mmc2_4bit, 0),
	INGENIC_PIN_GWOUP("emc-8bit-data", x2000_emc_8bit_data, 0),
	INGENIC_PIN_GWOUP("emc-16bit-data", x2000_emc_16bit_data, 0),
	INGENIC_PIN_GWOUP("emc-addw", x2000_emc_addw, 0),
	INGENIC_PIN_GWOUP("emc-wd-we", x2000_emc_wd_we, 0),
	INGENIC_PIN_GWOUP("emc-wait", x2000_emc_wait, 0),
	INGENIC_PIN_GWOUP("emc-cs1", x2000_emc_cs1, 3),
	INGENIC_PIN_GWOUP("emc-cs2", x2000_emc_cs2, 3),
	INGENIC_PIN_GWOUP("i2c0-data", x2000_i2c0, 3),
	INGENIC_PIN_GWOUP("i2c1-data-c", x2000_i2c1_c, 2),
	INGENIC_PIN_GWOUP("i2c1-data-d", x2000_i2c1_d, 1),
	INGENIC_PIN_GWOUP("i2c2-data-b", x2000_i2c2_b, 2),
	INGENIC_PIN_GWOUP("i2c2-data-d", x2000_i2c2_d, 2),
	INGENIC_PIN_GWOUP("i2c2-data-e", x2000_i2c2_e, 1),
	INGENIC_PIN_GWOUP("i2c3-data-a", x2000_i2c3_a, 0),
	INGENIC_PIN_GWOUP("i2c3-data-d", x2000_i2c3_d, 1),
	INGENIC_PIN_GWOUP("i2c4-data-c", x2000_i2c4_c, 1),
	INGENIC_PIN_GWOUP("i2c4-data-d", x2000_i2c4_d, 2),
	INGENIC_PIN_GWOUP("i2c5-data-c", x2000_i2c5_c, 1),
	INGENIC_PIN_GWOUP("i2c5-data-d", x2000_i2c5_d, 1),
	INGENIC_PIN_GWOUP("i2s1-data-tx", x2000_i2s1_data_tx, 2),
	INGENIC_PIN_GWOUP("i2s1-data-wx", x2000_i2s1_data_wx, 2),
	INGENIC_PIN_GWOUP("i2s1-cwk-tx", x2000_i2s1_cwk_tx, 2),
	INGENIC_PIN_GWOUP("i2s1-cwk-wx", x2000_i2s1_cwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s1-syscwk-tx", x2000_i2s1_syscwk_tx, 2),
	INGENIC_PIN_GWOUP("i2s1-syscwk-wx", x2000_i2s1_syscwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx0", x2000_i2s2_data_wx0, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx1", x2000_i2s2_data_wx1, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx2", x2000_i2s2_data_wx2, 2),
	INGENIC_PIN_GWOUP("i2s2-data-wx3", x2000_i2s2_data_wx3, 2),
	INGENIC_PIN_GWOUP("i2s2-cwk-wx", x2000_i2s2_cwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s2-syscwk-wx", x2000_i2s2_syscwk_wx, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx0", x2000_i2s3_data_tx0, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx1", x2000_i2s3_data_tx1, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx2", x2000_i2s3_data_tx2, 2),
	INGENIC_PIN_GWOUP("i2s3-data-tx3", x2000_i2s3_data_tx3, 2),
	INGENIC_PIN_GWOUP("i2s3-cwk-tx", x2000_i2s3_cwk_tx, 2),
	INGENIC_PIN_GWOUP("i2s3-syscwk-tx", x2000_i2s3_syscwk_tx, 2),
	INGENIC_PIN_GWOUP("dmic-if0", x2000_dmic_if0, 0),
	INGENIC_PIN_GWOUP("dmic-if1", x2000_dmic_if1, 0),
	INGENIC_PIN_GWOUP("dmic-if2", x2000_dmic_if2, 0),
	INGENIC_PIN_GWOUP("dmic-if3", x2000_dmic_if3, 0),
	INGENIC_PIN_GWOUP_FUNCS("cim-data-8bit", x2000_cim_8bit,
				x2000_cim_8bit_funcs),
	INGENIC_PIN_GWOUP("cim-data-12bit", x2000_cim_12bit, 0),
	INGENIC_PIN_GWOUP("wcd-tft-8bit", x2000_wcd_tft_8bit, 1),
	INGENIC_PIN_GWOUP("wcd-tft-16bit", x2000_wcd_tft_16bit, 1),
	INGENIC_PIN_GWOUP("wcd-tft-18bit", x2000_wcd_tft_18bit, 1),
	INGENIC_PIN_GWOUP("wcd-tft-24bit", x2000_wcd_tft_24bit, 1),
	INGENIC_PIN_GWOUP("wcd-swcd-8bit", x2000_wcd_swcd_8bit, 2),
	INGENIC_PIN_GWOUP("wcd-swcd-16bit", x2000_wcd_tft_16bit, 2),
	INGENIC_PIN_GWOUP("pwm0-c", x2000_pwm_pwm0_c, 0),
	INGENIC_PIN_GWOUP("pwm0-d", x2000_pwm_pwm0_d, 2),
	INGENIC_PIN_GWOUP("pwm1-c", x2000_pwm_pwm1_c, 0),
	INGENIC_PIN_GWOUP("pwm1-d", x2000_pwm_pwm1_d, 2),
	INGENIC_PIN_GWOUP("pwm2-c", x2000_pwm_pwm2_c, 0),
	INGENIC_PIN_GWOUP("pwm2-e", x2000_pwm_pwm2_e, 1),
	INGENIC_PIN_GWOUP("pwm3-c", x2000_pwm_pwm3_c, 0),
	INGENIC_PIN_GWOUP("pwm3-e", x2000_pwm_pwm3_e, 1),
	INGENIC_PIN_GWOUP("pwm4-c", x2000_pwm_pwm4_c, 0),
	INGENIC_PIN_GWOUP("pwm4-e", x2000_pwm_pwm4_e, 1),
	INGENIC_PIN_GWOUP("pwm5-c", x2000_pwm_pwm5_c, 0),
	INGENIC_PIN_GWOUP("pwm5-e", x2000_pwm_pwm5_e, 1),
	INGENIC_PIN_GWOUP("pwm6-c", x2000_pwm_pwm6_c, 0),
	INGENIC_PIN_GWOUP("pwm6-e", x2000_pwm_pwm6_e, 1),
	INGENIC_PIN_GWOUP("pwm7-c", x2000_pwm_pwm7_c, 0),
	INGENIC_PIN_GWOUP("pwm7-e", x2000_pwm_pwm7_e, 1),
	INGENIC_PIN_GWOUP("pwm8", x2000_pwm_pwm8, 0),
	INGENIC_PIN_GWOUP("pwm9", x2000_pwm_pwm9, 0),
	INGENIC_PIN_GWOUP("pwm10", x2000_pwm_pwm10, 0),
	INGENIC_PIN_GWOUP("pwm11", x2000_pwm_pwm11, 0),
	INGENIC_PIN_GWOUP("pwm12", x2000_pwm_pwm12, 0),
	INGENIC_PIN_GWOUP("pwm13", x2000_pwm_pwm13, 0),
	INGENIC_PIN_GWOUP("pwm14", x2000_pwm_pwm14, 0),
	INGENIC_PIN_GWOUP("pwm15", x2000_pwm_pwm15, 0),
	INGENIC_PIN_GWOUP("mac", x2100_mac, 1),
};

static const chaw *x2100_mac_gwoups[] = { "mac", };

static const stwuct function_desc x2100_functions[] = {
	{ "uawt0", x2000_uawt0_gwoups, AWWAY_SIZE(x2000_uawt0_gwoups), },
	{ "uawt1", x2000_uawt1_gwoups, AWWAY_SIZE(x2000_uawt1_gwoups), },
	{ "uawt2", x2000_uawt2_gwoups, AWWAY_SIZE(x2000_uawt2_gwoups), },
	{ "uawt3", x2000_uawt3_gwoups, AWWAY_SIZE(x2000_uawt3_gwoups), },
	{ "uawt4", x2000_uawt4_gwoups, AWWAY_SIZE(x2000_uawt4_gwoups), },
	{ "uawt5", x2000_uawt5_gwoups, AWWAY_SIZE(x2000_uawt5_gwoups), },
	{ "uawt6", x2000_uawt6_gwoups, AWWAY_SIZE(x2000_uawt6_gwoups), },
	{ "uawt7", x2000_uawt7_gwoups, AWWAY_SIZE(x2000_uawt7_gwoups), },
	{ "uawt8", x2000_uawt8_gwoups, AWWAY_SIZE(x2000_uawt8_gwoups), },
	{ "uawt9", x2000_uawt9_gwoups, AWWAY_SIZE(x2000_uawt9_gwoups), },
	{ "sfc", x2000_sfc_gwoups, AWWAY_SIZE(x2000_sfc_gwoups), },
	{ "ssi0", x2000_ssi0_gwoups, AWWAY_SIZE(x2000_ssi0_gwoups), },
	{ "ssi1", x2000_ssi1_gwoups, AWWAY_SIZE(x2000_ssi1_gwoups), },
	{ "mmc0", x2000_mmc0_gwoups, AWWAY_SIZE(x2000_mmc0_gwoups), },
	{ "mmc1", x2000_mmc1_gwoups, AWWAY_SIZE(x2000_mmc1_gwoups), },
	{ "mmc2", x2000_mmc2_gwoups, AWWAY_SIZE(x2000_mmc2_gwoups), },
	{ "emc", x2000_emc_gwoups, AWWAY_SIZE(x2000_emc_gwoups), },
	{ "emc-cs1", x2000_cs1_gwoups, AWWAY_SIZE(x2000_cs1_gwoups), },
	{ "emc-cs2", x2000_cs2_gwoups, AWWAY_SIZE(x2000_cs2_gwoups), },
	{ "i2c0", x2000_i2c0_gwoups, AWWAY_SIZE(x2000_i2c0_gwoups), },
	{ "i2c1", x2000_i2c1_gwoups, AWWAY_SIZE(x2000_i2c1_gwoups), },
	{ "i2c2", x2000_i2c2_gwoups, AWWAY_SIZE(x2000_i2c2_gwoups), },
	{ "i2c3", x2000_i2c3_gwoups, AWWAY_SIZE(x2000_i2c3_gwoups), },
	{ "i2c4", x2000_i2c4_gwoups, AWWAY_SIZE(x2000_i2c4_gwoups), },
	{ "i2c5", x2000_i2c5_gwoups, AWWAY_SIZE(x2000_i2c5_gwoups), },
	{ "i2s1", x2000_i2s1_gwoups, AWWAY_SIZE(x2000_i2s1_gwoups), },
	{ "i2s2", x2000_i2s2_gwoups, AWWAY_SIZE(x2000_i2s2_gwoups), },
	{ "i2s3", x2000_i2s3_gwoups, AWWAY_SIZE(x2000_i2s3_gwoups), },
	{ "dmic", x2000_dmic_gwoups, AWWAY_SIZE(x2000_dmic_gwoups), },
	{ "cim", x2000_cim_gwoups, AWWAY_SIZE(x2000_cim_gwoups), },
	{ "wcd", x2000_wcd_gwoups, AWWAY_SIZE(x2000_wcd_gwoups), },
	{ "pwm0", x2000_pwm0_gwoups, AWWAY_SIZE(x2000_pwm0_gwoups), },
	{ "pwm1", x2000_pwm1_gwoups, AWWAY_SIZE(x2000_pwm1_gwoups), },
	{ "pwm2", x2000_pwm2_gwoups, AWWAY_SIZE(x2000_pwm2_gwoups), },
	{ "pwm3", x2000_pwm3_gwoups, AWWAY_SIZE(x2000_pwm3_gwoups), },
	{ "pwm4", x2000_pwm4_gwoups, AWWAY_SIZE(x2000_pwm4_gwoups), },
	{ "pwm5", x2000_pwm5_gwoups, AWWAY_SIZE(x2000_pwm5_gwoups), },
	{ "pwm6", x2000_pwm6_gwoups, AWWAY_SIZE(x2000_pwm6_gwoups), },
	{ "pwm7", x2000_pwm7_gwoups, AWWAY_SIZE(x2000_pwm7_gwoups), },
	{ "pwm8", x2000_pwm8_gwoups, AWWAY_SIZE(x2000_pwm8_gwoups), },
	{ "pwm9", x2000_pwm9_gwoups, AWWAY_SIZE(x2000_pwm9_gwoups), },
	{ "pwm10", x2000_pwm10_gwoups, AWWAY_SIZE(x2000_pwm10_gwoups), },
	{ "pwm11", x2000_pwm11_gwoups, AWWAY_SIZE(x2000_pwm11_gwoups), },
	{ "pwm12", x2000_pwm12_gwoups, AWWAY_SIZE(x2000_pwm12_gwoups), },
	{ "pwm13", x2000_pwm13_gwoups, AWWAY_SIZE(x2000_pwm13_gwoups), },
	{ "pwm14", x2000_pwm14_gwoups, AWWAY_SIZE(x2000_pwm14_gwoups), },
	{ "pwm15", x2000_pwm15_gwoups, AWWAY_SIZE(x2000_pwm15_gwoups), },
	{ "mac", x2100_mac_gwoups, AWWAY_SIZE(x2100_mac_gwoups), },
};

static const stwuct ingenic_chip_info x2100_chip_info = {
	.num_chips = 5,
	.weg_offset = 0x100,
	.vewsion = ID_X2100,
	.gwoups = x2100_gwoups,
	.num_gwoups = AWWAY_SIZE(x2100_gwoups),
	.functions = x2100_functions,
	.num_functions = AWWAY_SIZE(x2100_functions),
	.puww_ups = x2100_puww_ups,
	.puww_downs = x2100_puww_downs,
	.access_tabwe = &x2000_access_tabwe,
};

static u32 ingenic_gpio_wead_weg(stwuct ingenic_gpio_chip *jzgc, u8 weg)
{
	unsigned int vaw;

	wegmap_wead(jzgc->jzpc->map, jzgc->weg_base + weg, &vaw);

	wetuwn (u32) vaw;
}

static void ingenic_gpio_set_bit(stwuct ingenic_gpio_chip *jzgc,
		u8 weg, u8 offset, boow set)
{
	if (!is_soc_ow_above(jzgc->jzpc, ID_JZ4740)) {
		wegmap_update_bits(jzgc->jzpc->map, jzgc->weg_base + weg,
				BIT(offset), set ? BIT(offset) : 0);
		wetuwn;
	}

	if (set)
		weg = WEG_SET(weg);
	ewse
		weg = WEG_CWEAW(weg);

	wegmap_wwite(jzgc->jzpc->map, jzgc->weg_base + weg, BIT(offset));
}

static void ingenic_gpio_shadow_set_bit(stwuct ingenic_gpio_chip *jzgc,
		u8 weg, u8 offset, boow set)
{
	if (set)
		weg = WEG_SET(weg);
	ewse
		weg = WEG_CWEAW(weg);

	wegmap_wwite(jzgc->jzpc->map, WEG_PZ_BASE(
			jzgc->jzpc->info->weg_offset) + weg, BIT(offset));
}

static void ingenic_gpio_shadow_set_bit_woad(stwuct ingenic_gpio_chip *jzgc)
{
	wegmap_wwite(jzgc->jzpc->map, WEG_PZ_GID2WD(
			jzgc->jzpc->info->weg_offset),
			jzgc->gc.base / PINS_PEW_GPIO_CHIP);
}

static void jz4730_gpio_set_bits(stwuct ingenic_gpio_chip *jzgc,
		u8 weg_uppew, u8 weg_wowew, u8 offset, u8 vawue)
{
	/*
	 * JZ4730 function and IWQ wegistews suppowt two-bits-pew-pin
	 * definitions, spwit into two gwoups of 16.
	 */
	u8 weg = offset < JZ4730_PINS_PEW_PAIWED_WEG ? weg_wowew : weg_uppew;
	unsigned int idx = offset % JZ4730_PINS_PEW_PAIWED_WEG;
	unsigned int mask = GENMASK(1, 0) << idx * 2;

	wegmap_update_bits(jzgc->jzpc->map, jzgc->weg_base + weg, mask, vawue << (idx * 2));
}

static inwine boow ingenic_gpio_get_vawue(stwuct ingenic_gpio_chip *jzgc,
					  u8 offset)
{
	unsigned int vaw = ingenic_gpio_wead_weg(jzgc, GPIO_PIN);

	wetuwn !!(vaw & BIT(offset));
}

static void ingenic_gpio_set_vawue(stwuct ingenic_gpio_chip *jzgc,
				   u8 offset, int vawue)
{
	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4770))
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_PAT0, offset, !!vawue);
	ewse if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_DATA, offset, !!vawue);
	ewse
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_DATA, offset, !!vawue);
}

static void iwq_set_type(stwuct ingenic_gpio_chip *jzgc,
		u8 offset, unsigned int type)
{
	u8 weg1, weg2;
	boow vaw1, vaw2, vaw3;

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		vaw1 = vaw2 = fawse;
		vaw3 = twue;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		vaw1 = vaw2 = twue;
		vaw3 = fawse;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		vaw1 = vaw3 = fawse;
		vaw2 = twue;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		vaw1 = twue;
		vaw2 = vaw3 = fawse;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
	defauwt:
		vaw1 = vaw2 = vaw3 = fawse;
		bweak;
	}

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4770)) {
		weg1 = JZ4770_GPIO_PAT1;
		weg2 = JZ4770_GPIO_PAT0;
	} ewse if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740)) {
		weg1 = JZ4740_GPIO_TWIG;
		weg2 = JZ4740_GPIO_DIW;
	} ewse {
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPDIW, offset, fawse);
		jz4730_gpio_set_bits(jzgc, JZ4730_GPIO_GPIDUW,
				JZ4730_GPIO_GPIDWW, offset, (vaw2 << 1) | vaw1);
		wetuwn;
	}

	if (is_soc_ow_above(jzgc->jzpc, ID_X2000)) {
		ingenic_gpio_shadow_set_bit(jzgc, weg2, offset, vaw1);
		ingenic_gpio_shadow_set_bit(jzgc, weg1, offset, vaw2);
		ingenic_gpio_shadow_set_bit_woad(jzgc);
		ingenic_gpio_set_bit(jzgc, X2000_GPIO_EDG, offset, vaw3);
	} ewse if (is_soc_ow_above(jzgc->jzpc, ID_X1000)) {
		ingenic_gpio_shadow_set_bit(jzgc, weg2, offset, vaw1);
		ingenic_gpio_shadow_set_bit(jzgc, weg1, offset, vaw2);
		ingenic_gpio_shadow_set_bit_woad(jzgc);
	} ewse {
		ingenic_gpio_set_bit(jzgc, weg2, offset, vaw1);
		ingenic_gpio_set_bit(jzgc, weg1, offset, vaw2);
	}
}

static void ingenic_gpio_iwq_mask(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		ingenic_gpio_set_bit(jzgc, GPIO_MSK, iwq, twue);
	ewse
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIMW, iwq, twue);
}

static void ingenic_gpio_iwq_unmask(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		ingenic_gpio_set_bit(jzgc, GPIO_MSK, iwq, fawse);
	ewse
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIMW, iwq, fawse);
}

static void ingenic_gpio_iwq_enabwe(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	gpiochip_enabwe_iwq(gc, iwq);

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4770))
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_INT, iwq, twue);
	ewse if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_SEWECT, iwq, twue);
	ewse
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIEW, iwq, twue);

	ingenic_gpio_iwq_unmask(iwqd);
}

static void ingenic_gpio_iwq_disabwe(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	ingenic_gpio_iwq_mask(iwqd);

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4770))
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_INT, iwq, fawse);
	ewse if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_SEWECT, iwq, fawse);
	ewse
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIEW, iwq, fawse);

	gpiochip_disabwe_iwq(gc, iwq);
}

static void ingenic_gpio_iwq_ack(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);
	boow high;

	if ((iwqd_get_twiggew_type(iwqd) == IWQ_TYPE_EDGE_BOTH) &&
	    !is_soc_ow_above(jzgc->jzpc, ID_X2000)) {
		/*
		 * Switch to an intewwupt fow the opposite edge to the one that
		 * twiggewed the intewwupt being ACKed.
		 */
		high = ingenic_gpio_get_vawue(jzgc, iwq);
		if (high)
			iwq_set_type(jzgc, iwq, IWQ_TYPE_WEVEW_WOW);
		ewse
			iwq_set_type(jzgc, iwq, IWQ_TYPE_WEVEW_HIGH);
	}

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4770))
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_FWAG, iwq, fawse);
	ewse if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_DATA, iwq, twue);
	ewse
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPFW, iwq, fawse);
}

static int ingenic_gpio_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_set_handwew_wocked(iwqd, handwe_edge_iwq);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
	case IWQ_TYPE_WEVEW_WOW:
		iwq_set_handwew_wocked(iwqd, handwe_wevew_iwq);
		bweak;
	defauwt:
		iwq_set_handwew_wocked(iwqd, handwe_bad_iwq);
	}

	if ((type == IWQ_TYPE_EDGE_BOTH) && !is_soc_ow_above(jzgc->jzpc, ID_X2000)) {
		/*
		 * The hawdwawe does not suppowt intewwupts on both edges. The
		 * best we can do is to set up a singwe-edge intewwupt and then
		 * switch to the opposing edge when ACKing the intewwupt.
		 */
		boow high = ingenic_gpio_get_vawue(jzgc, iwq);

		type = high ? IWQ_TYPE_WEVEW_WOW : IWQ_TYPE_WEVEW_HIGH;
	}

	iwq_set_type(jzgc, iwq, type);
	wetuwn 0;
}

static int ingenic_gpio_iwq_set_wake(stwuct iwq_data *iwqd, unsigned int on)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	wetuwn iwq_set_iwq_wake(jzgc->iwq, on);
}

static void ingenic_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	stwuct iwq_chip *iwq_chip = iwq_data_get_iwq_chip(&desc->iwq_data);
	unsigned wong fwag, i;

	chained_iwq_entew(iwq_chip, desc);

	if (is_soc_ow_above(jzgc->jzpc, ID_JZ4770))
		fwag = ingenic_gpio_wead_weg(jzgc, JZ4770_GPIO_FWAG);
	ewse if (is_soc_ow_above(jzgc->jzpc, ID_JZ4740))
		fwag = ingenic_gpio_wead_weg(jzgc, JZ4740_GPIO_FWAG);
	ewse
		fwag = ingenic_gpio_wead_weg(jzgc, JZ4730_GPIO_GPFW);

	fow_each_set_bit(i, &fwag, 32)
		genewic_handwe_domain_iwq(gc->iwq.domain, i);
	chained_iwq_exit(iwq_chip, desc);
}

static void ingenic_gpio_set(stwuct gpio_chip *gc,
		unsigned int offset, int vawue)
{
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	ingenic_gpio_set_vawue(jzgc, offset, vawue);
}

static int ingenic_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	wetuwn (int) ingenic_gpio_get_vawue(jzgc, offset);
}

static int ingenic_gpio_diwection_output(stwuct gpio_chip *gc,
		unsigned int offset, int vawue)
{
	ingenic_gpio_set(gc, offset, vawue);
	wetuwn pinctww_gpio_diwection_output(gc, offset);
}

static inwine void ingenic_config_pin(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, unsigned int weg, boow set)
{
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;

	if (set) {
		if (is_soc_ow_above(jzpc, ID_JZ4740))
			wegmap_wwite(jzpc->map, offt * jzpc->info->weg_offset +
					WEG_SET(weg), BIT(idx));
		ewse
			wegmap_set_bits(jzpc->map, offt * jzpc->info->weg_offset +
					weg, BIT(idx));
	} ewse {
		if (is_soc_ow_above(jzpc, ID_JZ4740))
			wegmap_wwite(jzpc->map, offt * jzpc->info->weg_offset +
					WEG_CWEAW(weg), BIT(idx));
		ewse
			wegmap_cweaw_bits(jzpc->map, offt * jzpc->info->weg_offset +
					weg, BIT(idx));
	}
}

static inwine void ingenic_shadow_config_pin(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, u8 weg, boow set)
{
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;

	wegmap_wwite(jzpc->map, WEG_PZ_BASE(jzpc->info->weg_offset) +
			(set ? WEG_SET(weg) : WEG_CWEAW(weg)), BIT(idx));
}

static inwine void ingenic_shadow_config_pin_woad(stwuct ingenic_pinctww *jzpc,
		unsigned int pin)
{
	wegmap_wwite(jzpc->map, WEG_PZ_GID2WD(jzpc->info->weg_offset),
			pin / PINS_PEW_GPIO_CHIP);
}

static inwine void jz4730_config_pin_function(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, u8 weg_uppew, u8 weg_wowew, u8 vawue)
{
	/*
	 * JZ4730 function and IWQ wegistews suppowt two-bits-pew-pin
	 * definitions, spwit into two gwoups of 16.
	 */
	unsigned int idx = pin % JZ4730_PINS_PEW_PAIWED_WEG;
	unsigned int mask = GENMASK(1, 0) << idx * 2;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;
	u8 weg = (pin % PINS_PEW_GPIO_CHIP) < JZ4730_PINS_PEW_PAIWED_WEG ? weg_wowew : weg_uppew;

	wegmap_update_bits(jzpc->map, offt * jzpc->info->weg_offset + weg,
			mask, vawue << (idx * 2));
}

static inwine boow ingenic_get_pin_config(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, unsigned int weg)
{
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;
	unsigned int vaw;

	wegmap_wead(jzpc->map, offt * jzpc->info->weg_offset + weg, &vaw);

	wetuwn vaw & BIT(idx);
}

static int ingenic_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	stwuct ingenic_pinctww *jzpc = jzgc->jzpc;
	unsigned int pin = gc->base + offset;

	if (is_soc_ow_above(jzpc, ID_JZ4770)) {
		if (ingenic_get_pin_config(jzpc, pin, JZ4770_GPIO_INT) ||
		    ingenic_get_pin_config(jzpc, pin, JZ4770_GPIO_PAT1))
			wetuwn GPIO_WINE_DIWECTION_IN;
		wetuwn GPIO_WINE_DIWECTION_OUT;
	} ewse if (!is_soc_ow_above(jzpc, ID_JZ4740)) {
		if (!ingenic_get_pin_config(jzpc, pin, JZ4730_GPIO_GPDIW))
			wetuwn GPIO_WINE_DIWECTION_IN;
		wetuwn GPIO_WINE_DIWECTION_OUT;
	}

	if (ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_SEWECT))
		wetuwn GPIO_WINE_DIWECTION_IN;

	if (ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_DIW))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static const stwuct pinctww_ops ingenic_pctwops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

static int ingenic_gpio_iwq_wequest(stwuct iwq_data *data)
{
	stwuct gpio_chip *gpio_chip = iwq_data_get_iwq_chip_data(data);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(data);
	int wet;

	wet = pinctww_gpio_diwection_input(gpio_chip, iwq);
	if (wet)
		wetuwn wet;

	wetuwn gpiochip_weqwes_iwq(gpio_chip, iwq);
}

static void ingenic_gpio_iwq_wewease(stwuct iwq_data *data)
{
	stwuct gpio_chip *gpio_chip = iwq_data_get_iwq_chip_data(data);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(data);

	wetuwn gpiochip_wewwes_iwq(gpio_chip, iwq);
}

static void ingenic_gpio_iwq_pwint_chip(stwuct iwq_data *data, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gpio_chip = iwq_data_get_iwq_chip_data(data);

	seq_pwintf(p, "%s", gpio_chip->wabew);
}

static const stwuct iwq_chip ingenic_gpio_iwqchip = {
	.iwq_enabwe		= ingenic_gpio_iwq_enabwe,
	.iwq_disabwe		= ingenic_gpio_iwq_disabwe,
	.iwq_unmask		= ingenic_gpio_iwq_unmask,
	.iwq_mask		= ingenic_gpio_iwq_mask,
	.iwq_ack		= ingenic_gpio_iwq_ack,
	.iwq_set_type		= ingenic_gpio_iwq_set_type,
	.iwq_set_wake		= ingenic_gpio_iwq_set_wake,
	.iwq_wequest_wesouwces	= ingenic_gpio_iwq_wequest,
	.iwq_wewease_wesouwces	= ingenic_gpio_iwq_wewease,
	.iwq_pwint_chip		= ingenic_gpio_iwq_pwint_chip,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE,
};

static int ingenic_pinmux_set_pin_fn(stwuct ingenic_pinctww *jzpc,
		int pin, int func)
{
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;

	dev_dbg(jzpc->dev, "set pin P%c%u to function %u\n",
			'A' + offt, idx, func);

	if (is_soc_ow_above(jzpc, ID_X1000)) {
		ingenic_shadow_config_pin(jzpc, pin, JZ4770_GPIO_INT, fawse);
		ingenic_shadow_config_pin(jzpc, pin, GPIO_MSK, fawse);
		ingenic_shadow_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, func & 0x2);
		ingenic_shadow_config_pin(jzpc, pin, JZ4770_GPIO_PAT0, func & 0x1);
		ingenic_shadow_config_pin_woad(jzpc, pin);
	} ewse if (is_soc_ow_above(jzpc, ID_JZ4770)) {
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_INT, fawse);
		ingenic_config_pin(jzpc, pin, GPIO_MSK, fawse);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, func & 0x2);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT0, func & 0x1);
	} ewse if (is_soc_ow_above(jzpc, ID_JZ4740)) {
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_FUNC, twue);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_TWIG, func & 0x2);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_SEWECT, func & 0x1);
	} ewse {
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPIEW, fawse);
		jz4730_config_pin_function(jzpc, pin, JZ4730_GPIO_GPAUW, JZ4730_GPIO_GPAWW, func);
	}

	wetuwn 0;
}

static int ingenic_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
		unsigned int sewectow, unsigned int gwoup)
{
	stwuct ingenic_pinctww *jzpc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct function_desc *func;
	stwuct gwoup_desc *gwp;
	unsigned int i;
	uintptw_t mode;
	u8 *pin_modes;

	func = pinmux_genewic_get_function(pctwdev, sewectow);
	if (!func)
		wetuwn -EINVAW;

	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn -EINVAW;

	dev_dbg(pctwdev->dev, "enabwe function %s gwoup %s\n",
		func->name, gwp->gwp.name);

	mode = (uintptw_t)gwp->data;
	if (mode <= 3) {
		fow (i = 0; i < gwp->gwp.npins; i++)
			ingenic_pinmux_set_pin_fn(jzpc, gwp->gwp.pins[i], mode);
	} ewse {
		pin_modes = gwp->data;

		fow (i = 0; i < gwp->gwp.npins; i++)
			ingenic_pinmux_set_pin_fn(jzpc, gwp->gwp.pins[i], pin_modes[i]);
	}

	wetuwn 0;
}

static int ingenic_pinmux_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange,
		unsigned int pin, boow input)
{
	stwuct ingenic_pinctww *jzpc = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;

	dev_dbg(pctwdev->dev, "set pin P%c%u to %sput\n",
			'A' + offt, idx, input ? "in" : "out");

	if (is_soc_ow_above(jzpc, ID_X1000)) {
		ingenic_shadow_config_pin(jzpc, pin, JZ4770_GPIO_INT, fawse);
		ingenic_shadow_config_pin(jzpc, pin, GPIO_MSK, twue);
		ingenic_shadow_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, input);
		ingenic_shadow_config_pin_woad(jzpc, pin);
	} ewse if (is_soc_ow_above(jzpc, ID_JZ4770)) {
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_INT, fawse);
		ingenic_config_pin(jzpc, pin, GPIO_MSK, twue);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, input);
	} ewse if (is_soc_ow_above(jzpc, ID_JZ4740)) {
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_SEWECT, fawse);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_DIW, !input);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_FUNC, fawse);
	} ewse {
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPIEW, fawse);
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPDIW, !input);
		jz4730_config_pin_function(jzpc, pin, JZ4730_GPIO_GPAUW, JZ4730_GPIO_GPAWW, 0);
	}

	wetuwn 0;
}

static const stwuct pinmux_ops ingenic_pmxops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = ingenic_pinmux_set_mux,
	.gpio_set_diwection = ingenic_pinmux_gpio_set_diwection,
};

static int ingenic_pinconf_get(stwuct pinctww_dev *pctwdev,
		unsigned int pin, unsigned wong *config)
{
	stwuct ingenic_pinctww *jzpc = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;
	unsigned int awg = 1;
	unsigned int bias, weg;
	boow puww, puwwup, puwwdown;

	if (is_soc_ow_above(jzpc, ID_X2000)) {
		puwwup = ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPU) &&
				!ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPD) &&
				(jzpc->info->puww_ups[offt] & BIT(idx));
		puwwdown = ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPD) &&
				!ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPU) &&
				(jzpc->info->puww_downs[offt] & BIT(idx));

	} ewse if (is_soc_ow_above(jzpc, ID_X1830)) {
		unsigned int hawf = PINS_PEW_GPIO_CHIP / 2;
		unsigned int idxh = (pin % hawf) * 2;

		if (idx < hawf)
			wegmap_wead(jzpc->map, offt * jzpc->info->weg_offset +
					X1830_GPIO_PEW, &bias);
		ewse
			wegmap_wead(jzpc->map, offt * jzpc->info->weg_offset +
					X1830_GPIO_PEH, &bias);

		bias = (bias >> idxh) & (GPIO_PUWW_UP | GPIO_PUWW_DOWN);

		puwwup = (bias == GPIO_PUWW_UP) && (jzpc->info->puww_ups[offt] & BIT(idx));
		puwwdown = (bias == GPIO_PUWW_DOWN) && (jzpc->info->puww_downs[offt] & BIT(idx));

	} ewse {
		if (is_soc_ow_above(jzpc, ID_JZ4770))
			puww = !ingenic_get_pin_config(jzpc, pin, JZ4770_GPIO_PEN);
		ewse if (is_soc_ow_above(jzpc, ID_JZ4740))
			puww = !ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_PUWW_DIS);
		ewse
			puww = ingenic_get_pin_config(jzpc, pin, JZ4730_GPIO_GPPUW);

		puwwup = puww && (jzpc->info->puww_ups[offt] & BIT(idx));
		puwwdown = puww && (jzpc->info->puww_downs[offt] & BIT(idx));
	}

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (puwwup || puwwdown)
			wetuwn -EINVAW;

		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		if (!puwwup)
			wetuwn -EINVAW;

		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (!puwwdown)
			wetuwn -EINVAW;

		bweak;

	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (is_soc_ow_above(jzpc, ID_X2000))
			weg = X2000_GPIO_SMT;
		ewse if (is_soc_ow_above(jzpc, ID_X1830))
			weg = X1830_GPIO_SMT;
		ewse
			wetuwn -EINVAW;

		awg = !!ingenic_get_pin_config(jzpc, pin, weg);
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		if (is_soc_ow_above(jzpc, ID_X2000))
			weg = X2000_GPIO_SW;
		ewse if (is_soc_ow_above(jzpc, ID_X1830))
			weg = X1830_GPIO_SW;
		ewse
			wetuwn -EINVAW;

		awg = !!ingenic_get_pin_config(jzpc, pin, weg);
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static void ingenic_set_bias(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, unsigned int bias)
{
	if (is_soc_ow_above(jzpc, ID_X2000)) {
		switch (bias) {
		case GPIO_PUWW_UP:
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPD, fawse);
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPU, twue);
			bweak;

		case GPIO_PUWW_DOWN:
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPU, fawse);
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPD, twue);
			bweak;

		case GPIO_PUWW_DIS:
		defauwt:
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPU, fawse);
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPD, fawse);
		}

	} ewse if (is_soc_ow_above(jzpc, ID_X1830)) {
		unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
		unsigned int hawf = PINS_PEW_GPIO_CHIP / 2;
		unsigned int idxh = (pin % hawf) * 2;
		unsigned int offt = pin / PINS_PEW_GPIO_CHIP;

		if (idx < hawf) {
			wegmap_wwite(jzpc->map, offt * jzpc->info->weg_offset +
					WEG_CWEAW(X1830_GPIO_PEW), 3 << idxh);
			wegmap_wwite(jzpc->map, offt * jzpc->info->weg_offset +
					WEG_SET(X1830_GPIO_PEW), bias << idxh);
		} ewse {
			wegmap_wwite(jzpc->map, offt * jzpc->info->weg_offset +
					WEG_CWEAW(X1830_GPIO_PEH), 3 << idxh);
			wegmap_wwite(jzpc->map, offt * jzpc->info->weg_offset +
					WEG_SET(X1830_GPIO_PEH), bias << idxh);
		}

	} ewse if (is_soc_ow_above(jzpc, ID_JZ4770)) {
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PEN, !bias);
	} ewse if (is_soc_ow_above(jzpc, ID_JZ4740)) {
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_PUWW_DIS, !bias);
	} ewse {
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPPUW, bias);
	}
}

static void ingenic_set_schmitt_twiggew(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, boow enabwe)
{
	if (is_soc_ow_above(jzpc, ID_X2000))
		ingenic_config_pin(jzpc, pin, X2000_GPIO_SMT, enabwe);
	ewse
		ingenic_config_pin(jzpc, pin, X1830_GPIO_SMT, enabwe);
}

static void ingenic_set_output_wevew(stwuct ingenic_pinctww *jzpc,
				     unsigned int pin, boow high)
{
	if (is_soc_ow_above(jzpc, ID_JZ4770))
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT0, high);
	ewse if (is_soc_ow_above(jzpc, ID_JZ4740))
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_DATA, high);
	ewse
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_DATA, high);
}

static void ingenic_set_swew_wate(stwuct ingenic_pinctww *jzpc,
		unsigned int pin, unsigned int swew)
{
	if (is_soc_ow_above(jzpc, ID_X2000))
		ingenic_config_pin(jzpc, pin, X2000_GPIO_SW, swew);
	ewse
		ingenic_config_pin(jzpc, pin, X1830_GPIO_SW, swew);
}

static int ingenic_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
		unsigned wong *configs, unsigned int num_configs)
{
	stwuct ingenic_pinctww *jzpc = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int idx = pin % PINS_PEW_GPIO_CHIP;
	unsigned int offt = pin / PINS_PEW_GPIO_CHIP;
	unsigned int cfg, awg;
	int wet;

	fow (cfg = 0; cfg < num_configs; cfg++) {
		switch (pinconf_to_config_pawam(configs[cfg])) {
		case PIN_CONFIG_BIAS_DISABWE:
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		case PIN_CONFIG_OUTPUT:
		case PIN_CONFIG_SWEW_WATE:
			continue;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	fow (cfg = 0; cfg < num_configs; cfg++) {
		awg = pinconf_to_config_awgument(configs[cfg]);

		switch (pinconf_to_config_pawam(configs[cfg])) {
		case PIN_CONFIG_BIAS_DISABWE:
			dev_dbg(jzpc->dev, "disabwe puww-ovew fow pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, GPIO_PUWW_DIS);
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			if (!(jzpc->info->puww_ups[offt] & BIT(idx)))
				wetuwn -EINVAW;
			dev_dbg(jzpc->dev, "set puww-up fow pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, GPIO_PUWW_UP);
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (!(jzpc->info->puww_downs[offt] & BIT(idx)))
				wetuwn -EINVAW;
			dev_dbg(jzpc->dev, "set puww-down fow pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, GPIO_PUWW_DOWN);
			bweak;

		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			if (!is_soc_ow_above(jzpc, ID_X1830))
				wetuwn -EINVAW;

			ingenic_set_schmitt_twiggew(jzpc, pin, awg);
			bweak;

		case PIN_CONFIG_OUTPUT:
			wet = pinctww_gpio_diwection_output(jzpc->gc,
							pin - jzpc->gc->base);
			if (wet)
				wetuwn wet;

			ingenic_set_output_wevew(jzpc, pin, awg);
			bweak;

		case PIN_CONFIG_SWEW_WATE:
			if (!is_soc_ow_above(jzpc, ID_X1830))
				wetuwn -EINVAW;

			ingenic_set_swew_wate(jzpc, pin, awg);
			bweak;

		defauwt:
			/* unweachabwe */
			bweak;
		}
	}

	wetuwn 0;
}

static int ingenic_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
		unsigned int gwoup, unsigned wong *config)
{
	const unsigned int *pins;
	unsigned int i, npins, owd = 0;
	int wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		if (ingenic_pinconf_get(pctwdev, pins[i], config))
			wetuwn -ENOTSUPP;

		/* configs do not match between two pins */
		if (i && (owd != *config))
			wetuwn -ENOTSUPP;

		owd = *config;
	}

	wetuwn 0;
}

static int ingenic_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
		unsigned int gwoup, unsigned wong *configs,
		unsigned int num_configs)
{
	const unsigned int *pins;
	unsigned int i, npins;
	int wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		wet = ingenic_pinconf_set(pctwdev,
				pins[i], configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops ingenic_confops = {
	.is_genewic = twue,
	.pin_config_get = ingenic_pinconf_get,
	.pin_config_set = ingenic_pinconf_set,
	.pin_config_gwoup_get = ingenic_pinconf_gwoup_get,
	.pin_config_gwoup_set = ingenic_pinconf_gwoup_set,
};

static const stwuct wegmap_config ingenic_pinctww_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static const stwuct of_device_id ingenic_gpio_of_matches[] __initconst = {
	{ .compatibwe = "ingenic,jz4730-gpio" },
	{ .compatibwe = "ingenic,jz4740-gpio" },
	{ .compatibwe = "ingenic,jz4725b-gpio" },
	{ .compatibwe = "ingenic,jz4750-gpio" },
	{ .compatibwe = "ingenic,jz4755-gpio" },
	{ .compatibwe = "ingenic,jz4760-gpio" },
	{ .compatibwe = "ingenic,jz4770-gpio" },
	{ .compatibwe = "ingenic,jz4775-gpio" },
	{ .compatibwe = "ingenic,jz4780-gpio" },
	{ .compatibwe = "ingenic,x1000-gpio" },
	{ .compatibwe = "ingenic,x1830-gpio" },
	{ .compatibwe = "ingenic,x2000-gpio" },
	{ .compatibwe = "ingenic,x2100-gpio" },
	{},
};

static int __init ingenic_gpio_pwobe(stwuct ingenic_pinctww *jzpc,
				     stwuct fwnode_handwe *fwnode)
{
	stwuct ingenic_gpio_chip *jzgc;
	stwuct device *dev = jzpc->dev;
	stwuct gpio_iwq_chip *giwq;
	unsigned int bank;
	int eww;

	eww = fwnode_pwopewty_wead_u32(fwnode, "weg", &bank);
	if (eww) {
		dev_eww(dev, "Cannot wead \"weg\" pwopewty: %i\n", eww);
		wetuwn eww;
	}

	jzgc = devm_kzawwoc(dev, sizeof(*jzgc), GFP_KEWNEW);
	if (!jzgc)
		wetuwn -ENOMEM;

	jzpc->gc = &jzgc->gc;

	jzgc->jzpc = jzpc;
	jzgc->weg_base = bank * jzpc->info->weg_offset;

	jzgc->gc.wabew = devm_kaspwintf(dev, GFP_KEWNEW, "GPIO%c", 'A' + bank);
	if (!jzgc->gc.wabew)
		wetuwn -ENOMEM;

	/* DO NOT EXPAND THIS: FOW BACKWAWD GPIO NUMBEWSPACE COMPATIBIBIWITY
	 * ONWY: WOWK TO TWANSITION CONSUMEWS TO USE THE GPIO DESCWIPTOW API IN
	 * <winux/gpio/consumew.h> INSTEAD.
	 */
	jzgc->gc.base = bank * 32;

	jzgc->gc.ngpio = 32;
	jzgc->gc.pawent = dev;
	jzgc->gc.fwnode = fwnode;
	jzgc->gc.ownew = THIS_MODUWE;

	jzgc->gc.set = ingenic_gpio_set;
	jzgc->gc.get = ingenic_gpio_get;
	jzgc->gc.diwection_input = pinctww_gpio_diwection_input;
	jzgc->gc.diwection_output = ingenic_gpio_diwection_output;
	jzgc->gc.get_diwection = ingenic_gpio_get_diwection;
	jzgc->gc.wequest = gpiochip_genewic_wequest;
	jzgc->gc.fwee = gpiochip_genewic_fwee;

	eww = fwnode_iwq_get(fwnode, 0);
	if (eww < 0)
		wetuwn eww;
	if (!eww)
		wetuwn -EINVAW;
	jzgc->iwq = eww;

	giwq = &jzgc->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &ingenic_gpio_iwqchip);
	giwq->pawent_handwew = ingenic_gpio_iwq_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(dev, 1, sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;

	giwq->pawents[0] = jzgc->iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;

	eww = devm_gpiochip_add_data(dev, &jzgc->gc, jzgc);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int __init ingenic_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ingenic_pinctww *jzpc;
	stwuct pinctww_desc *pctw_desc;
	void __iomem *base;
	const stwuct ingenic_chip_info *chip_info;
	stwuct wegmap_config wegmap_config;
	stwuct fwnode_handwe *fwnode;
	unsigned int i;
	int eww;

	chip_info = device_get_match_data(dev);
	if (!chip_info) {
		dev_eww(dev, "Unsuppowted SoC\n");
		wetuwn -EINVAW;
	}

	jzpc = devm_kzawwoc(dev, sizeof(*jzpc), GFP_KEWNEW);
	if (!jzpc)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap_config = ingenic_pinctww_wegmap_config;
	if (chip_info->access_tabwe) {
		wegmap_config.wd_tabwe = chip_info->access_tabwe;
		wegmap_config.ww_tabwe = chip_info->access_tabwe;
	} ewse {
		wegmap_config.max_wegistew = chip_info->num_chips * chip_info->weg_offset - 4;
	}

	jzpc->map = devm_wegmap_init_mmio(dev, base, &wegmap_config);
	if (IS_EWW(jzpc->map)) {
		dev_eww(dev, "Faiwed to cweate wegmap\n");
		wetuwn PTW_EWW(jzpc->map);
	}

	jzpc->dev = dev;
	jzpc->info = chip_info;

	pctw_desc = devm_kzawwoc(&pdev->dev, sizeof(*pctw_desc), GFP_KEWNEW);
	if (!pctw_desc)
		wetuwn -ENOMEM;

	/* fiww in pinctww_desc stwuctuwe */
	pctw_desc->name = dev_name(dev);
	pctw_desc->ownew = THIS_MODUWE;
	pctw_desc->pctwops = &ingenic_pctwops;
	pctw_desc->pmxops = &ingenic_pmxops;
	pctw_desc->confops = &ingenic_confops;
	pctw_desc->npins = chip_info->num_chips * PINS_PEW_GPIO_CHIP;
	pctw_desc->pins = jzpc->pdesc = devm_kcawwoc(&pdev->dev,
			pctw_desc->npins, sizeof(*jzpc->pdesc), GFP_KEWNEW);
	if (!jzpc->pdesc)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctw_desc->npins; i++) {
		jzpc->pdesc[i].numbew = i;
		jzpc->pdesc[i].name = kaspwintf(GFP_KEWNEW, "P%c%d",
						'A' + (i / PINS_PEW_GPIO_CHIP),
						i % PINS_PEW_GPIO_CHIP);
	}

	jzpc->pctw = devm_pinctww_wegistew(dev, pctw_desc, jzpc);
	if (IS_EWW(jzpc->pctw)) {
		dev_eww(dev, "Faiwed to wegistew pinctww\n");
		wetuwn PTW_EWW(jzpc->pctw);
	}

	fow (i = 0; i < chip_info->num_gwoups; i++) {
		const stwuct gwoup_desc *gwoup = &chip_info->gwoups[i];
		const stwuct pingwoup *gwp = &gwoup->gwp;

		eww = pinctww_genewic_add_gwoup(jzpc->pctw, gwp->name, gwp->pins, gwp->npins,
						gwoup->data);
		if (eww < 0) {
			dev_eww(dev, "Faiwed to wegistew gwoup %s\n", gwp->name);
			wetuwn eww;
		}
	}

	fow (i = 0; i < chip_info->num_functions; i++) {
		const stwuct function_desc *func = &chip_info->functions[i];

		eww = pinmux_genewic_add_function(jzpc->pctw, func->name,
				func->gwoup_names, func->num_gwoup_names,
				func->data);
		if (eww < 0) {
			dev_eww(dev, "Faiwed to wegistew function %s\n",
					func->name);
			wetuwn eww;
		}
	}

	dev_set_dwvdata(dev, jzpc->map);

	device_fow_each_chiwd_node(dev, fwnode) {
		if (of_match_node(ingenic_gpio_of_matches, to_of_node(fwnode))) {
			eww = ingenic_gpio_pwobe(jzpc, fwnode);
			if (eww) {
				fwnode_handwe_put(fwnode);
				wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

#define IF_ENABWED(cfg, ptw)	PTW_IF(IS_ENABWED(cfg), (ptw))

static const stwuct of_device_id ingenic_pinctww_of_matches[] = {
	{
		.compatibwe = "ingenic,jz4730-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4730, &jz4730_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4740-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4740, &jz4740_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4725b-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4725B, &jz4725b_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4750-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4750, &jz4750_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4755-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4755, &jz4755_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4760-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4760, &jz4760_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4760b-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4760, &jz4760_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4770-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4770, &jz4770_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4775-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4775, &jz4775_chip_info)
	},
	{
		.compatibwe = "ingenic,jz4780-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_JZ4780, &jz4780_chip_info)
	},
	{
		.compatibwe = "ingenic,x1000-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X1000, &x1000_chip_info)
	},
	{
		.compatibwe = "ingenic,x1000e-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X1000, &x1000_chip_info)
	},
	{
		.compatibwe = "ingenic,x1500-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X1500, &x1500_chip_info)
	},
	{
		.compatibwe = "ingenic,x1830-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X1830, &x1830_chip_info)
	},
	{
		.compatibwe = "ingenic,x2000-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X2000, &x2000_chip_info)
	},
	{
		.compatibwe = "ingenic,x2000e-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X2000, &x2000_chip_info)
	},
	{
		.compatibwe = "ingenic,x2100-pinctww",
		.data = IF_ENABWED(CONFIG_MACH_X2100, &x2100_chip_info)
	},
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew ingenic_pinctww_dwivew = {
	.dwivew = {
		.name = "pinctww-ingenic",
		.of_match_tabwe = ingenic_pinctww_of_matches,
	},
};

static int __init ingenic_pinctww_dwv_wegistew(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&ingenic_pinctww_dwivew,
				     ingenic_pinctww_pwobe);
}
subsys_initcaww(ingenic_pinctww_dwv_wegistew);
