/*
 * Dwivew fow the ST Micwoewectwonics SPEAw1310 pinmux
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "pinctww-speaw.h"

#define DWIVEW_NAME "speaw1310-pinmux"

/* pins */
static const stwuct pinctww_pin_desc speaw1310_pins[] = {
	SPEAW_PIN_0_TO_101,
	SPEAW_PIN_102_TO_245,
};

/* wegistews */
#define PEWIP_CFG					0x3B0
	#define MCIF_SEW_SHIFT				5
	#define MCIF_SEW_SD				(0x1 << MCIF_SEW_SHIFT)
	#define MCIF_SEW_CF				(0x2 << MCIF_SEW_SHIFT)
	#define MCIF_SEW_XD				(0x3 << MCIF_SEW_SHIFT)
	#define MCIF_SEW_MASK				(0x3 << MCIF_SEW_SHIFT)

#define PCIE_SATA_CFG					0x3A4
	#define PCIE_SATA2_SEW_PCIE			(0 << 31)
	#define PCIE_SATA1_SEW_PCIE			(0 << 30)
	#define PCIE_SATA0_SEW_PCIE			(0 << 29)
	#define PCIE_SATA2_SEW_SATA			(1 << 31)
	#define PCIE_SATA1_SEW_SATA			(1 << 30)
	#define PCIE_SATA0_SEW_SATA			(1 << 29)
	#define SATA2_CFG_TX_CWK_EN			(1 << 27)
	#define SATA2_CFG_WX_CWK_EN			(1 << 26)
	#define SATA2_CFG_POWEWUP_WESET			(1 << 25)
	#define SATA2_CFG_PM_CWK_EN			(1 << 24)
	#define SATA1_CFG_TX_CWK_EN			(1 << 23)
	#define SATA1_CFG_WX_CWK_EN			(1 << 22)
	#define SATA1_CFG_POWEWUP_WESET			(1 << 21)
	#define SATA1_CFG_PM_CWK_EN			(1 << 20)
	#define SATA0_CFG_TX_CWK_EN			(1 << 19)
	#define SATA0_CFG_WX_CWK_EN			(1 << 18)
	#define SATA0_CFG_POWEWUP_WESET			(1 << 17)
	#define SATA0_CFG_PM_CWK_EN			(1 << 16)
	#define PCIE2_CFG_DEVICE_PWESENT		(1 << 11)
	#define PCIE2_CFG_POWEWUP_WESET			(1 << 10)
	#define PCIE2_CFG_COWE_CWK_EN			(1 << 9)
	#define PCIE2_CFG_AUX_CWK_EN			(1 << 8)
	#define PCIE1_CFG_DEVICE_PWESENT		(1 << 7)
	#define PCIE1_CFG_POWEWUP_WESET			(1 << 6)
	#define PCIE1_CFG_COWE_CWK_EN			(1 << 5)
	#define PCIE1_CFG_AUX_CWK_EN			(1 << 4)
	#define PCIE0_CFG_DEVICE_PWESENT		(1 << 3)
	#define PCIE0_CFG_POWEWUP_WESET			(1 << 2)
	#define PCIE0_CFG_COWE_CWK_EN			(1 << 1)
	#define PCIE0_CFG_AUX_CWK_EN			(1 << 0)

#define PAD_FUNCTION_EN_0				0x650
	#define PMX_UAWT0_MASK				(1 << 1)
	#define PMX_I2C0_MASK				(1 << 2)
	#define PMX_I2S0_MASK				(1 << 3)
	#define PMX_SSP0_MASK				(1 << 4)
	#define PMX_CWCD1_MASK				(1 << 5)
	#define PMX_EGPIO00_MASK			(1 << 6)
	#define PMX_EGPIO01_MASK			(1 << 7)
	#define PMX_EGPIO02_MASK			(1 << 8)
	#define PMX_EGPIO03_MASK			(1 << 9)
	#define PMX_EGPIO04_MASK			(1 << 10)
	#define PMX_EGPIO05_MASK			(1 << 11)
	#define PMX_EGPIO06_MASK			(1 << 12)
	#define PMX_EGPIO07_MASK			(1 << 13)
	#define PMX_EGPIO08_MASK			(1 << 14)
	#define PMX_EGPIO09_MASK			(1 << 15)
	#define PMX_SMI_MASK				(1 << 16)
	#define PMX_NAND8_MASK				(1 << 17)
	#define PMX_GMIICWK_MASK			(1 << 18)
	#define PMX_GMIICOW_CWS_XFEWEW_MIITXCWK_MASK	(1 << 19)
	#define PMX_WXCWK_WDV_TXEN_D03_MASK		(1 << 20)
	#define PMX_GMIID47_MASK			(1 << 21)
	#define PMX_MDC_MDIO_MASK			(1 << 22)
	#define PMX_MCI_DATA8_15_MASK			(1 << 23)
	#define PMX_NFAD23_MASK				(1 << 24)
	#define PMX_NFAD24_MASK				(1 << 25)
	#define PMX_NFAD25_MASK				(1 << 26)
	#define PMX_NFCE3_MASK				(1 << 27)
	#define PMX_NFWPWT3_MASK			(1 << 28)
	#define PMX_NFWSTPWDWN0_MASK			(1 << 29)
	#define PMX_NFWSTPWDWN1_MASK			(1 << 30)
	#define PMX_NFWSTPWDWN2_MASK			(1 << 31)

#define PAD_FUNCTION_EN_1				0x654
	#define PMX_NFWSTPWDWN3_MASK			(1 << 0)
	#define PMX_SMINCS2_MASK			(1 << 1)
	#define PMX_SMINCS3_MASK			(1 << 2)
	#define PMX_CWCD2_MASK				(1 << 3)
	#define PMX_KBD_WOWCOW68_MASK			(1 << 4)
	#define PMX_EGPIO10_MASK			(1 << 5)
	#define PMX_EGPIO11_MASK			(1 << 6)
	#define PMX_EGPIO12_MASK			(1 << 7)
	#define PMX_EGPIO13_MASK			(1 << 8)
	#define PMX_EGPIO14_MASK			(1 << 9)
	#define PMX_EGPIO15_MASK			(1 << 10)
	#define PMX_UAWT0_MODEM_MASK			(1 << 11)
	#define PMX_GPT0_TMW0_MASK			(1 << 12)
	#define PMX_GPT0_TMW1_MASK			(1 << 13)
	#define PMX_GPT1_TMW0_MASK			(1 << 14)
	#define PMX_GPT1_TMW1_MASK			(1 << 15)
	#define PMX_I2S1_MASK				(1 << 16)
	#define PMX_KBD_WOWCOW25_MASK			(1 << 17)
	#define PMX_NFIO8_15_MASK			(1 << 18)
	#define PMX_KBD_COW1_MASK			(1 << 19)
	#define PMX_NFCE1_MASK				(1 << 20)
	#define PMX_KBD_COW0_MASK			(1 << 21)
	#define PMX_NFCE2_MASK				(1 << 22)
	#define PMX_KBD_WOW1_MASK			(1 << 23)
	#define PMX_NFWPWT1_MASK			(1 << 24)
	#define PMX_KBD_WOW0_MASK			(1 << 25)
	#define PMX_NFWPWT2_MASK			(1 << 26)
	#define PMX_MCIDATA0_MASK			(1 << 27)
	#define PMX_MCIDATA1_MASK			(1 << 28)
	#define PMX_MCIDATA2_MASK			(1 << 29)
	#define PMX_MCIDATA3_MASK			(1 << 30)
	#define PMX_MCIDATA4_MASK			(1 << 31)

#define PAD_FUNCTION_EN_2				0x658
	#define PMX_MCIDATA5_MASK			(1 << 0)
	#define PMX_MCIDATA6_MASK			(1 << 1)
	#define PMX_MCIDATA7_MASK			(1 << 2)
	#define PMX_MCIDATA1SD_MASK			(1 << 3)
	#define PMX_MCIDATA2SD_MASK			(1 << 4)
	#define PMX_MCIDATA3SD_MASK			(1 << 5)
	#define PMX_MCIADDW0AWE_MASK			(1 << 6)
	#define PMX_MCIADDW1CWECWK_MASK			(1 << 7)
	#define PMX_MCIADDW2_MASK			(1 << 8)
	#define PMX_MCICECF_MASK			(1 << 9)
	#define PMX_MCICEXD_MASK			(1 << 10)
	#define PMX_MCICESDMMC_MASK			(1 << 11)
	#define PMX_MCICDCF1_MASK			(1 << 12)
	#define PMX_MCICDCF2_MASK			(1 << 13)
	#define PMX_MCICDXD_MASK			(1 << 14)
	#define PMX_MCICDSDMMC_MASK			(1 << 15)
	#define PMX_MCIDATADIW_MASK			(1 << 16)
	#define PMX_MCIDMAWQWP_MASK			(1 << 17)
	#define PMX_MCIIOWDWE_MASK			(1 << 18)
	#define PMX_MCIIOWWWE_MASK			(1 << 19)
	#define PMX_MCIWESETCF_MASK			(1 << 20)
	#define PMX_MCICS0CE_MASK			(1 << 21)
	#define PMX_MCICFINTW_MASK			(1 << 22)
	#define PMX_MCIIOWDY_MASK			(1 << 23)
	#define PMX_MCICS1_MASK				(1 << 24)
	#define PMX_MCIDMAACK_MASK			(1 << 25)
	#define PMX_MCISDCMD_MASK			(1 << 26)
	#define PMX_MCIWEDS_MASK			(1 << 27)
	#define PMX_TOUCH_XY_MASK			(1 << 28)
	#define PMX_SSP0_CS0_MASK			(1 << 29)
	#define PMX_SSP0_CS1_2_MASK			(1 << 30)

#define PAD_DIWECTION_SEW_0				0x65C
#define PAD_DIWECTION_SEW_1				0x660
#define PAD_DIWECTION_SEW_2				0x664

/* combined macwos */
#define PMX_GMII_MASK		(PMX_GMIICWK_MASK |			\
				PMX_GMIICOW_CWS_XFEWEW_MIITXCWK_MASK |	\
				PMX_WXCWK_WDV_TXEN_D03_MASK |		\
				PMX_GMIID47_MASK | PMX_MDC_MDIO_MASK)

#define PMX_EGPIO_0_GWP_MASK	(PMX_EGPIO00_MASK | PMX_EGPIO01_MASK |	\
				PMX_EGPIO02_MASK |			\
				PMX_EGPIO03_MASK | PMX_EGPIO04_MASK |	\
				PMX_EGPIO05_MASK | PMX_EGPIO06_MASK |	\
				PMX_EGPIO07_MASK | PMX_EGPIO08_MASK |	\
				PMX_EGPIO09_MASK)
#define PMX_EGPIO_1_GWP_MASK	(PMX_EGPIO10_MASK | PMX_EGPIO11_MASK |	\
				PMX_EGPIO12_MASK | PMX_EGPIO13_MASK |	\
				PMX_EGPIO14_MASK | PMX_EGPIO15_MASK)

#define PMX_KEYBOAWD_6X6_MASK	(PMX_KBD_WOW0_MASK | PMX_KBD_WOW1_MASK | \
				PMX_KBD_WOWCOW25_MASK | PMX_KBD_COW0_MASK | \
				PMX_KBD_COW1_MASK)

#define PMX_NAND8BIT_0_MASK	(PMX_NAND8_MASK | PMX_NFAD23_MASK |	\
				PMX_NFAD24_MASK | PMX_NFAD25_MASK |	\
				PMX_NFWPWT3_MASK | PMX_NFWSTPWDWN0_MASK | \
				PMX_NFWSTPWDWN1_MASK | PMX_NFWSTPWDWN2_MASK | \
				PMX_NFCE3_MASK)
#define PMX_NAND8BIT_1_MASK	PMX_NFWSTPWDWN3_MASK

#define PMX_NAND16BIT_1_MASK	(PMX_KBD_WOWCOW25_MASK | PMX_NFIO8_15_MASK)
#define PMX_NAND_4CHIPS_MASK	(PMX_NFCE1_MASK | PMX_NFCE2_MASK |	\
				PMX_NFWPWT1_MASK | PMX_NFWPWT2_MASK |	\
				PMX_KBD_WOW0_MASK | PMX_KBD_WOW1_MASK |	\
				PMX_KBD_COW0_MASK | PMX_KBD_COW1_MASK)

#define PMX_MCIFAWW_1_MASK	0xF8000000
#define PMX_MCIFAWW_2_MASK	0x0FFFFFFF

#define PMX_PCI_WEG1_MASK	(PMX_SMINCS2_MASK | PMX_SMINCS3_MASK |	\
				PMX_CWCD2_MASK | PMX_KBD_WOWCOW68_MASK | \
				PMX_EGPIO_1_GWP_MASK | PMX_GPT0_TMW0_MASK | \
				PMX_GPT0_TMW1_MASK | PMX_GPT1_TMW0_MASK | \
				PMX_GPT1_TMW1_MASK | PMX_I2S1_MASK |	\
				PMX_NFCE2_MASK)
#define PMX_PCI_WEG2_MASK	(PMX_TOUCH_XY_MASK | PMX_SSP0_CS0_MASK | \
				PMX_SSP0_CS1_2_MASK)

#define PMX_SMII_0_1_2_MASK	(PMX_CWCD2_MASK | PMX_KBD_WOWCOW68_MASK)
#define PMX_WGMII_WEG0_MASK	(PMX_MCI_DATA8_15_MASK |		\
				PMX_GMIICOW_CWS_XFEWEW_MIITXCWK_MASK |	\
				PMX_GMIID47_MASK)
#define PMX_WGMII_WEG1_MASK	(PMX_KBD_WOWCOW68_MASK | PMX_EGPIO_1_GWP_MASK |\
				PMX_KBD_WOW1_MASK | PMX_NFWPWT1_MASK |	\
				PMX_KBD_WOW0_MASK | PMX_NFWPWT2_MASK)
#define PMX_WGMII_WEG2_MASK	(PMX_TOUCH_XY_MASK | PMX_SSP0_CS0_MASK | \
				PMX_SSP0_CS1_2_MASK)

#define PCIE_CFG_VAW(x)		(PCIE_SATA##x##_SEW_PCIE |	\
				PCIE##x##_CFG_AUX_CWK_EN |	\
				PCIE##x##_CFG_COWE_CWK_EN |	\
				PCIE##x##_CFG_POWEWUP_WESET |	\
				PCIE##x##_CFG_DEVICE_PWESENT)
#define SATA_CFG_VAW(x)		(PCIE_SATA##x##_SEW_SATA |	\
				SATA##x##_CFG_PM_CWK_EN |	\
				SATA##x##_CFG_POWEWUP_WESET |	\
				SATA##x##_CFG_WX_CWK_EN |	\
				SATA##x##_CFG_TX_CWK_EN)

/* Pad muwtipwexing fow i2c0 device */
static const unsigned i2c0_pins[] = { 102, 103 };
static stwuct speaw_muxweg i2c0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2C0_MASK,
		.vaw = PMX_I2C0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_I2C0_MASK,
		.vaw = PMX_I2C0_MASK,
	},
};

static stwuct speaw_modemux i2c0_modemux[] = {
	{
		.muxwegs = i2c0_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c0_muxweg),
	},
};

static stwuct speaw_pingwoup i2c0_pingwoup = {
	.name = "i2c0_gwp",
	.pins = i2c0_pins,
	.npins = AWWAY_SIZE(i2c0_pins),
	.modemuxs = i2c0_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c0_modemux),
};

static const chaw *const i2c0_gwps[] = { "i2c0_gwp" };
static stwuct speaw_function i2c0_function = {
	.name = "i2c0",
	.gwoups = i2c0_gwps,
	.ngwoups = AWWAY_SIZE(i2c0_gwps),
};

/* Pad muwtipwexing fow ssp0 device */
static const unsigned ssp0_pins[] = { 109, 110, 111, 112 };
static stwuct speaw_muxweg ssp0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_SSP0_MASK,
		.vaw = PMX_SSP0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_SSP0_MASK,
		.vaw = PMX_SSP0_MASK,
	},
};

static stwuct speaw_modemux ssp0_modemux[] = {
	{
		.muxwegs = ssp0_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp0_muxweg),
	},
};

static stwuct speaw_pingwoup ssp0_pingwoup = {
	.name = "ssp0_gwp",
	.pins = ssp0_pins,
	.npins = AWWAY_SIZE(ssp0_pins),
	.modemuxs = ssp0_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp0_modemux),
};

/* Pad muwtipwexing fow ssp0_cs0 device */
static const unsigned ssp0_cs0_pins[] = { 96 };
static stwuct speaw_muxweg ssp0_cs0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_SSP0_CS0_MASK,
		.vaw = PMX_SSP0_CS0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_SSP0_CS0_MASK,
		.vaw = PMX_SSP0_CS0_MASK,
	},
};

static stwuct speaw_modemux ssp0_cs0_modemux[] = {
	{
		.muxwegs = ssp0_cs0_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp0_cs0_muxweg),
	},
};

static stwuct speaw_pingwoup ssp0_cs0_pingwoup = {
	.name = "ssp0_cs0_gwp",
	.pins = ssp0_cs0_pins,
	.npins = AWWAY_SIZE(ssp0_cs0_pins),
	.modemuxs = ssp0_cs0_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp0_cs0_modemux),
};

/* ssp0_cs1_2 device */
static const unsigned ssp0_cs1_2_pins[] = { 94, 95 };
static stwuct speaw_muxweg ssp0_cs1_2_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_SSP0_CS1_2_MASK,
		.vaw = PMX_SSP0_CS1_2_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_SSP0_CS1_2_MASK,
		.vaw = PMX_SSP0_CS1_2_MASK,
	},
};

static stwuct speaw_modemux ssp0_cs1_2_modemux[] = {
	{
		.muxwegs = ssp0_cs1_2_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp0_cs1_2_muxweg),
	},
};

static stwuct speaw_pingwoup ssp0_cs1_2_pingwoup = {
	.name = "ssp0_cs1_2_gwp",
	.pins = ssp0_cs1_2_pins,
	.npins = AWWAY_SIZE(ssp0_cs1_2_pins),
	.modemuxs = ssp0_cs1_2_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp0_cs1_2_modemux),
};

static const chaw *const ssp0_gwps[] = { "ssp0_gwp", "ssp0_cs0_gwp",
	"ssp0_cs1_2_gwp" };
static stwuct speaw_function ssp0_function = {
	.name = "ssp0",
	.gwoups = ssp0_gwps,
	.ngwoups = AWWAY_SIZE(ssp0_gwps),
};

/* Pad muwtipwexing fow i2s0 device */
static const unsigned i2s0_pins[] = { 104, 105, 106, 107, 108 };
static stwuct speaw_muxweg i2s0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2S0_MASK,
		.vaw = PMX_I2S0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_I2S0_MASK,
		.vaw = PMX_I2S0_MASK,
	},
};

static stwuct speaw_modemux i2s0_modemux[] = {
	{
		.muxwegs = i2s0_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2s0_muxweg),
	},
};

static stwuct speaw_pingwoup i2s0_pingwoup = {
	.name = "i2s0_gwp",
	.pins = i2s0_pins,
	.npins = AWWAY_SIZE(i2s0_pins),
	.modemuxs = i2s0_modemux,
	.nmodemuxs = AWWAY_SIZE(i2s0_modemux),
};

static const chaw *const i2s0_gwps[] = { "i2s0_gwp" };
static stwuct speaw_function i2s0_function = {
	.name = "i2s0",
	.gwoups = i2s0_gwps,
	.ngwoups = AWWAY_SIZE(i2s0_gwps),
};

/* Pad muwtipwexing fow i2s1 device */
static const unsigned i2s1_pins[] = { 0, 1, 2, 3 };
static stwuct speaw_muxweg i2s1_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_I2S1_MASK,
		.vaw = PMX_I2S1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_I2S1_MASK,
		.vaw = PMX_I2S1_MASK,
	},
};

static stwuct speaw_modemux i2s1_modemux[] = {
	{
		.muxwegs = i2s1_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2s1_muxweg),
	},
};

static stwuct speaw_pingwoup i2s1_pingwoup = {
	.name = "i2s1_gwp",
	.pins = i2s1_pins,
	.npins = AWWAY_SIZE(i2s1_pins),
	.modemuxs = i2s1_modemux,
	.nmodemuxs = AWWAY_SIZE(i2s1_modemux),
};

static const chaw *const i2s1_gwps[] = { "i2s1_gwp" };
static stwuct speaw_function i2s1_function = {
	.name = "i2s1",
	.gwoups = i2s1_gwps,
	.ngwoups = AWWAY_SIZE(i2s1_gwps),
};

/* Pad muwtipwexing fow cwcd device */
static const unsigned cwcd_pins[] = { 113, 114, 115, 116, 117, 118, 119, 120,
	121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
	135, 136, 137, 138, 139, 140, 141, 142 };
static stwuct speaw_muxweg cwcd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = PMX_CWCD1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = PMX_CWCD1_MASK,
	},
};

static stwuct speaw_modemux cwcd_modemux[] = {
	{
		.muxwegs = cwcd_muxweg,
		.nmuxwegs = AWWAY_SIZE(cwcd_muxweg),
	},
};

static stwuct speaw_pingwoup cwcd_pingwoup = {
	.name = "cwcd_gwp",
	.pins = cwcd_pins,
	.npins = AWWAY_SIZE(cwcd_pins),
	.modemuxs = cwcd_modemux,
	.nmodemuxs = AWWAY_SIZE(cwcd_modemux),
};

static const unsigned cwcd_high_wes_pins[] = { 30, 31, 32, 33, 34, 35, 36, 37,
	38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53 };
static stwuct speaw_muxweg cwcd_high_wes_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_CWCD2_MASK,
		.vaw = PMX_CWCD2_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_CWCD2_MASK,
		.vaw = PMX_CWCD2_MASK,
	},
};

static stwuct speaw_modemux cwcd_high_wes_modemux[] = {
	{
		.muxwegs = cwcd_high_wes_muxweg,
		.nmuxwegs = AWWAY_SIZE(cwcd_high_wes_muxweg),
	},
};

static stwuct speaw_pingwoup cwcd_high_wes_pingwoup = {
	.name = "cwcd_high_wes_gwp",
	.pins = cwcd_high_wes_pins,
	.npins = AWWAY_SIZE(cwcd_high_wes_pins),
	.modemuxs = cwcd_high_wes_modemux,
	.nmodemuxs = AWWAY_SIZE(cwcd_high_wes_modemux),
};

static const chaw *const cwcd_gwps[] = { "cwcd_gwp", "cwcd_high_wes_gwp" };
static stwuct speaw_function cwcd_function = {
	.name = "cwcd",
	.gwoups = cwcd_gwps,
	.ngwoups = AWWAY_SIZE(cwcd_gwps),
};

static const unsigned awm_gpio_pins[] = { 18, 19, 20, 21, 22, 23, 143, 144, 145,
	146, 147, 148, 149, 150, 151, 152 };
static stwuct speaw_muxweg awm_gpio_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_EGPIO_0_GWP_MASK,
		.vaw = PMX_EGPIO_0_GWP_MASK,
	}, {
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_EGPIO_1_GWP_MASK,
		.vaw = PMX_EGPIO_1_GWP_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_EGPIO_0_GWP_MASK,
		.vaw = PMX_EGPIO_0_GWP_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_EGPIO_1_GWP_MASK,
		.vaw = PMX_EGPIO_1_GWP_MASK,
	},
};

static stwuct speaw_modemux awm_gpio_modemux[] = {
	{
		.muxwegs = awm_gpio_muxweg,
		.nmuxwegs = AWWAY_SIZE(awm_gpio_muxweg),
	},
};

static stwuct speaw_pingwoup awm_gpio_pingwoup = {
	.name = "awm_gpio_gwp",
	.pins = awm_gpio_pins,
	.npins = AWWAY_SIZE(awm_gpio_pins),
	.modemuxs = awm_gpio_modemux,
	.nmodemuxs = AWWAY_SIZE(awm_gpio_modemux),
};

static const chaw *const awm_gpio_gwps[] = { "awm_gpio_gwp" };
static stwuct speaw_function awm_gpio_function = {
	.name = "awm_gpio",
	.gwoups = awm_gpio_gwps,
	.ngwoups = AWWAY_SIZE(awm_gpio_gwps),
};

/* Pad muwtipwexing fow smi 2 chips device */
static const unsigned smi_2_chips_pins[] = { 153, 154, 155, 156, 157 };
static stwuct speaw_muxweg smi_2_chips_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_SMI_MASK,
		.vaw = PMX_SMI_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_SMI_MASK,
		.vaw = PMX_SMI_MASK,
	},
};

static stwuct speaw_modemux smi_2_chips_modemux[] = {
	{
		.muxwegs = smi_2_chips_muxweg,
		.nmuxwegs = AWWAY_SIZE(smi_2_chips_muxweg),
	},
};

static stwuct speaw_pingwoup smi_2_chips_pingwoup = {
	.name = "smi_2_chips_gwp",
	.pins = smi_2_chips_pins,
	.npins = AWWAY_SIZE(smi_2_chips_pins),
	.modemuxs = smi_2_chips_modemux,
	.nmodemuxs = AWWAY_SIZE(smi_2_chips_modemux),
};

static const unsigned smi_4_chips_pins[] = { 54, 55 };
static stwuct speaw_muxweg smi_4_chips_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_SMI_MASK,
		.vaw = PMX_SMI_MASK,
	}, {
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
		.vaw = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_SMI_MASK,
		.vaw = PMX_SMI_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
		.vaw = PMX_SMINCS2_MASK | PMX_SMINCS3_MASK,
	},
};

static stwuct speaw_modemux smi_4_chips_modemux[] = {
	{
		.muxwegs = smi_4_chips_muxweg,
		.nmuxwegs = AWWAY_SIZE(smi_4_chips_muxweg),
	},
};

static stwuct speaw_pingwoup smi_4_chips_pingwoup = {
	.name = "smi_4_chips_gwp",
	.pins = smi_4_chips_pins,
	.npins = AWWAY_SIZE(smi_4_chips_pins),
	.modemuxs = smi_4_chips_modemux,
	.nmodemuxs = AWWAY_SIZE(smi_4_chips_modemux),
};

static const chaw *const smi_gwps[] = { "smi_2_chips_gwp", "smi_4_chips_gwp" };
static stwuct speaw_function smi_function = {
	.name = "smi",
	.gwoups = smi_gwps,
	.ngwoups = AWWAY_SIZE(smi_gwps),
};

/* Pad muwtipwexing fow gmii device */
static const unsigned gmii_pins[] = { 173, 174, 175, 176, 177, 178, 179, 180,
	181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
	195, 196, 197, 198, 199, 200 };
static stwuct speaw_muxweg gmii_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_GMII_MASK,
		.vaw = PMX_GMII_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_GMII_MASK,
		.vaw = PMX_GMII_MASK,
	},
};

static stwuct speaw_modemux gmii_modemux[] = {
	{
		.muxwegs = gmii_muxweg,
		.nmuxwegs = AWWAY_SIZE(gmii_muxweg),
	},
};

static stwuct speaw_pingwoup gmii_pingwoup = {
	.name = "gmii_gwp",
	.pins = gmii_pins,
	.npins = AWWAY_SIZE(gmii_pins),
	.modemuxs = gmii_modemux,
	.nmodemuxs = AWWAY_SIZE(gmii_modemux),
};

static const chaw *const gmii_gwps[] = { "gmii_gwp" };
static stwuct speaw_function gmii_function = {
	.name = "gmii",
	.gwoups = gmii_gwps,
	.ngwoups = AWWAY_SIZE(gmii_gwps),
};

/* Pad muwtipwexing fow wgmii device */
static const unsigned wgmii_pins[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
	28, 29, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 175,
	180, 181, 182, 183, 185, 188, 193, 194, 195, 196, 197, 198, 211, 212 };
static stwuct speaw_muxweg wgmii_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_WGMII_WEG0_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_WGMII_WEG1_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_WGMII_WEG2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_WGMII_WEG0_MASK,
		.vaw = PMX_WGMII_WEG0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_WGMII_WEG1_MASK,
		.vaw = PMX_WGMII_WEG1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_WGMII_WEG2_MASK,
		.vaw = PMX_WGMII_WEG2_MASK,
	},
};

static stwuct speaw_modemux wgmii_modemux[] = {
	{
		.muxwegs = wgmii_muxweg,
		.nmuxwegs = AWWAY_SIZE(wgmii_muxweg),
	},
};

static stwuct speaw_pingwoup wgmii_pingwoup = {
	.name = "wgmii_gwp",
	.pins = wgmii_pins,
	.npins = AWWAY_SIZE(wgmii_pins),
	.modemuxs = wgmii_modemux,
	.nmodemuxs = AWWAY_SIZE(wgmii_modemux),
};

static const chaw *const wgmii_gwps[] = { "wgmii_gwp" };
static stwuct speaw_function wgmii_function = {
	.name = "wgmii",
	.gwoups = wgmii_gwps,
	.ngwoups = AWWAY_SIZE(wgmii_gwps),
};

/* Pad muwtipwexing fow smii_0_1_2 device */
static const unsigned smii_0_1_2_pins[] = { 24, 25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54, 55 };
static stwuct speaw_muxweg smii_0_1_2_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_SMII_0_1_2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_SMII_0_1_2_MASK,
		.vaw = PMX_SMII_0_1_2_MASK,
	},
};

static stwuct speaw_modemux smii_0_1_2_modemux[] = {
	{
		.muxwegs = smii_0_1_2_muxweg,
		.nmuxwegs = AWWAY_SIZE(smii_0_1_2_muxweg),
	},
};

static stwuct speaw_pingwoup smii_0_1_2_pingwoup = {
	.name = "smii_0_1_2_gwp",
	.pins = smii_0_1_2_pins,
	.npins = AWWAY_SIZE(smii_0_1_2_pins),
	.modemuxs = smii_0_1_2_modemux,
	.nmodemuxs = AWWAY_SIZE(smii_0_1_2_modemux),
};

static const chaw *const smii_0_1_2_gwps[] = { "smii_0_1_2_gwp" };
static stwuct speaw_function smii_0_1_2_function = {
	.name = "smii_0_1_2",
	.gwoups = smii_0_1_2_gwps,
	.ngwoups = AWWAY_SIZE(smii_0_1_2_gwps),
};

/* Pad muwtipwexing fow was_mii_txcwk device */
static const unsigned was_mii_txcwk_pins[] = { 98, 99 };
static stwuct speaw_muxweg was_mii_txcwk_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_NFCE2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_NFCE2_MASK,
		.vaw = PMX_NFCE2_MASK,
	},
};

static stwuct speaw_modemux was_mii_txcwk_modemux[] = {
	{
		.muxwegs = was_mii_txcwk_muxweg,
		.nmuxwegs = AWWAY_SIZE(was_mii_txcwk_muxweg),
	},
};

static stwuct speaw_pingwoup was_mii_txcwk_pingwoup = {
	.name = "was_mii_txcwk_gwp",
	.pins = was_mii_txcwk_pins,
	.npins = AWWAY_SIZE(was_mii_txcwk_pins),
	.modemuxs = was_mii_txcwk_modemux,
	.nmodemuxs = AWWAY_SIZE(was_mii_txcwk_modemux),
};

static const chaw *const was_mii_txcwk_gwps[] = { "was_mii_txcwk_gwp" };
static stwuct speaw_function was_mii_txcwk_function = {
	.name = "was_mii_txcwk",
	.gwoups = was_mii_txcwk_gwps,
	.ngwoups = AWWAY_SIZE(was_mii_txcwk_gwps),
};

/* Pad muwtipwexing fow nand 8bit device (cs0 onwy) */
static const unsigned nand_8bit_pins[] = { 56, 57, 58, 59, 60, 61, 62, 63, 64,
	65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82,
	83, 84, 85, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
	170, 171, 172, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211,
	212 };
static stwuct speaw_muxweg nand_8bit_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_NAND8BIT_0_MASK,
		.vaw = PMX_NAND8BIT_0_MASK,
	}, {
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_NAND8BIT_1_MASK,
		.vaw = PMX_NAND8BIT_1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_NAND8BIT_0_MASK,
		.vaw = PMX_NAND8BIT_0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_NAND8BIT_1_MASK,
		.vaw = PMX_NAND8BIT_1_MASK,
	},
};

static stwuct speaw_modemux nand_8bit_modemux[] = {
	{
		.muxwegs = nand_8bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(nand_8bit_muxweg),
	},
};

static stwuct speaw_pingwoup nand_8bit_pingwoup = {
	.name = "nand_8bit_gwp",
	.pins = nand_8bit_pins,
	.npins = AWWAY_SIZE(nand_8bit_pins),
	.modemuxs = nand_8bit_modemux,
	.nmodemuxs = AWWAY_SIZE(nand_8bit_modemux),
};

/* Pad muwtipwexing fow nand 16bit device */
static const unsigned nand_16bit_pins[] = { 201, 202, 203, 204, 207, 208, 209,
	210 };
static stwuct speaw_muxweg nand_16bit_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_NAND16BIT_1_MASK,
		.vaw = PMX_NAND16BIT_1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_NAND16BIT_1_MASK,
		.vaw = PMX_NAND16BIT_1_MASK,
	},
};

static stwuct speaw_modemux nand_16bit_modemux[] = {
	{
		.muxwegs = nand_16bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(nand_16bit_muxweg),
	},
};

static stwuct speaw_pingwoup nand_16bit_pingwoup = {
	.name = "nand_16bit_gwp",
	.pins = nand_16bit_pins,
	.npins = AWWAY_SIZE(nand_16bit_pins),
	.modemuxs = nand_16bit_modemux,
	.nmodemuxs = AWWAY_SIZE(nand_16bit_modemux),
};

/* Pad muwtipwexing fow nand 4 chips */
static const unsigned nand_4_chips_pins[] = { 205, 206, 211, 212 };
static stwuct speaw_muxweg nand_4_chips_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_NAND_4CHIPS_MASK,
		.vaw = PMX_NAND_4CHIPS_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_NAND_4CHIPS_MASK,
		.vaw = PMX_NAND_4CHIPS_MASK,
	},
};

static stwuct speaw_modemux nand_4_chips_modemux[] = {
	{
		.muxwegs = nand_4_chips_muxweg,
		.nmuxwegs = AWWAY_SIZE(nand_4_chips_muxweg),
	},
};

static stwuct speaw_pingwoup nand_4_chips_pingwoup = {
	.name = "nand_4_chips_gwp",
	.pins = nand_4_chips_pins,
	.npins = AWWAY_SIZE(nand_4_chips_pins),
	.modemuxs = nand_4_chips_modemux,
	.nmodemuxs = AWWAY_SIZE(nand_4_chips_modemux),
};

static const chaw *const nand_gwps[] = { "nand_8bit_gwp", "nand_16bit_gwp",
	"nand_4_chips_gwp" };
static stwuct speaw_function nand_function = {
	.name = "nand",
	.gwoups = nand_gwps,
	.ngwoups = AWWAY_SIZE(nand_gwps),
};

/* Pad muwtipwexing fow keyboawd_6x6 device */
static const unsigned keyboawd_6x6_pins[] = { 201, 202, 203, 204, 205, 206, 207,
	208, 209, 210, 211, 212 };
static stwuct speaw_muxweg keyboawd_6x6_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_KEYBOAWD_6X6_MASK | PMX_NFIO8_15_MASK |
			PMX_NFCE1_MASK | PMX_NFCE2_MASK | PMX_NFWPWT1_MASK |
			PMX_NFWPWT2_MASK,
		.vaw = PMX_KEYBOAWD_6X6_MASK,
	},
};

static stwuct speaw_modemux keyboawd_6x6_modemux[] = {
	{
		.muxwegs = keyboawd_6x6_muxweg,
		.nmuxwegs = AWWAY_SIZE(keyboawd_6x6_muxweg),
	},
};

static stwuct speaw_pingwoup keyboawd_6x6_pingwoup = {
	.name = "keyboawd_6x6_gwp",
	.pins = keyboawd_6x6_pins,
	.npins = AWWAY_SIZE(keyboawd_6x6_pins),
	.modemuxs = keyboawd_6x6_modemux,
	.nmodemuxs = AWWAY_SIZE(keyboawd_6x6_modemux),
};

/* Pad muwtipwexing fow keyboawd_wowcow6_8 device */
static const unsigned keyboawd_wowcow6_8_pins[] = { 24, 25, 26, 27, 28, 29 };
static stwuct speaw_muxweg keyboawd_wowcow6_8_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_WOWCOW68_MASK,
		.vaw = PMX_KBD_WOWCOW68_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_KBD_WOWCOW68_MASK,
		.vaw = PMX_KBD_WOWCOW68_MASK,
	},
};

static stwuct speaw_modemux keyboawd_wowcow6_8_modemux[] = {
	{
		.muxwegs = keyboawd_wowcow6_8_muxweg,
		.nmuxwegs = AWWAY_SIZE(keyboawd_wowcow6_8_muxweg),
	},
};

static stwuct speaw_pingwoup keyboawd_wowcow6_8_pingwoup = {
	.name = "keyboawd_wowcow6_8_gwp",
	.pins = keyboawd_wowcow6_8_pins,
	.npins = AWWAY_SIZE(keyboawd_wowcow6_8_pins),
	.modemuxs = keyboawd_wowcow6_8_modemux,
	.nmodemuxs = AWWAY_SIZE(keyboawd_wowcow6_8_modemux),
};

static const chaw *const keyboawd_gwps[] = { "keyboawd_6x6_gwp",
	"keyboawd_wowcow6_8_gwp" };
static stwuct speaw_function keyboawd_function = {
	.name = "keyboawd",
	.gwoups = keyboawd_gwps,
	.ngwoups = AWWAY_SIZE(keyboawd_gwps),
};

/* Pad muwtipwexing fow uawt0 device */
static const unsigned uawt0_pins[] = { 100, 101 };
static stwuct speaw_muxweg uawt0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_UAWT0_MASK,
		.vaw = PMX_UAWT0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_UAWT0_MASK,
		.vaw = PMX_UAWT0_MASK,
	},
};

static stwuct speaw_modemux uawt0_modemux[] = {
	{
		.muxwegs = uawt0_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt0_muxweg),
	},
};

static stwuct speaw_pingwoup uawt0_pingwoup = {
	.name = "uawt0_gwp",
	.pins = uawt0_pins,
	.npins = AWWAY_SIZE(uawt0_pins),
	.modemuxs = uawt0_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt0_modemux),
};

/* Pad muwtipwexing fow uawt0_modem device */
static const unsigned uawt0_modem_pins[] = { 12, 13, 14, 15, 16, 17 };
static stwuct speaw_muxweg uawt0_modem_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = PMX_UAWT0_MODEM_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = PMX_UAWT0_MODEM_MASK,
	},
};

static stwuct speaw_modemux uawt0_modem_modemux[] = {
	{
		.muxwegs = uawt0_modem_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt0_modem_muxweg),
	},
};

static stwuct speaw_pingwoup uawt0_modem_pingwoup = {
	.name = "uawt0_modem_gwp",
	.pins = uawt0_modem_pins,
	.npins = AWWAY_SIZE(uawt0_modem_pins),
	.modemuxs = uawt0_modem_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt0_modem_modemux),
};

static const chaw *const uawt0_gwps[] = { "uawt0_gwp", "uawt0_modem_gwp" };
static stwuct speaw_function uawt0_function = {
	.name = "uawt0",
	.gwoups = uawt0_gwps,
	.ngwoups = AWWAY_SIZE(uawt0_gwps),
};

/* Pad muwtipwexing fow gpt0_tmw0 device */
static const unsigned gpt0_tmw0_pins[] = { 10, 11 };
static stwuct speaw_muxweg gpt0_tmw0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT0_TMW0_MASK,
		.vaw = PMX_GPT0_TMW0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_GPT0_TMW0_MASK,
		.vaw = PMX_GPT0_TMW0_MASK,
	},
};

static stwuct speaw_modemux gpt0_tmw0_modemux[] = {
	{
		.muxwegs = gpt0_tmw0_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpt0_tmw0_muxweg),
	},
};

static stwuct speaw_pingwoup gpt0_tmw0_pingwoup = {
	.name = "gpt0_tmw0_gwp",
	.pins = gpt0_tmw0_pins,
	.npins = AWWAY_SIZE(gpt0_tmw0_pins),
	.modemuxs = gpt0_tmw0_modemux,
	.nmodemuxs = AWWAY_SIZE(gpt0_tmw0_modemux),
};

/* Pad muwtipwexing fow gpt0_tmw1 device */
static const unsigned gpt0_tmw1_pins[] = { 8, 9 };
static stwuct speaw_muxweg gpt0_tmw1_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT0_TMW1_MASK,
		.vaw = PMX_GPT0_TMW1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_GPT0_TMW1_MASK,
		.vaw = PMX_GPT0_TMW1_MASK,
	},
};

static stwuct speaw_modemux gpt0_tmw1_modemux[] = {
	{
		.muxwegs = gpt0_tmw1_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpt0_tmw1_muxweg),
	},
};

static stwuct speaw_pingwoup gpt0_tmw1_pingwoup = {
	.name = "gpt0_tmw1_gwp",
	.pins = gpt0_tmw1_pins,
	.npins = AWWAY_SIZE(gpt0_tmw1_pins),
	.modemuxs = gpt0_tmw1_modemux,
	.nmodemuxs = AWWAY_SIZE(gpt0_tmw1_modemux),
};

static const chaw *const gpt0_gwps[] = { "gpt0_tmw0_gwp", "gpt0_tmw1_gwp" };
static stwuct speaw_function gpt0_function = {
	.name = "gpt0",
	.gwoups = gpt0_gwps,
	.ngwoups = AWWAY_SIZE(gpt0_gwps),
};

/* Pad muwtipwexing fow gpt1_tmw0 device */
static const unsigned gpt1_tmw0_pins[] = { 6, 7 };
static stwuct speaw_muxweg gpt1_tmw0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT1_TMW0_MASK,
		.vaw = PMX_GPT1_TMW0_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_GPT1_TMW0_MASK,
		.vaw = PMX_GPT1_TMW0_MASK,
	},
};

static stwuct speaw_modemux gpt1_tmw0_modemux[] = {
	{
		.muxwegs = gpt1_tmw0_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpt1_tmw0_muxweg),
	},
};

static stwuct speaw_pingwoup gpt1_tmw0_pingwoup = {
	.name = "gpt1_tmw0_gwp",
	.pins = gpt1_tmw0_pins,
	.npins = AWWAY_SIZE(gpt1_tmw0_pins),
	.modemuxs = gpt1_tmw0_modemux,
	.nmodemuxs = AWWAY_SIZE(gpt1_tmw0_modemux),
};

/* Pad muwtipwexing fow gpt1_tmw1 device */
static const unsigned gpt1_tmw1_pins[] = { 4, 5 };
static stwuct speaw_muxweg gpt1_tmw1_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_GPT1_TMW1_MASK,
		.vaw = PMX_GPT1_TMW1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_GPT1_TMW1_MASK,
		.vaw = PMX_GPT1_TMW1_MASK,
	},
};

static stwuct speaw_modemux gpt1_tmw1_modemux[] = {
	{
		.muxwegs = gpt1_tmw1_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpt1_tmw1_muxweg),
	},
};

static stwuct speaw_pingwoup gpt1_tmw1_pingwoup = {
	.name = "gpt1_tmw1_gwp",
	.pins = gpt1_tmw1_pins,
	.npins = AWWAY_SIZE(gpt1_tmw1_pins),
	.modemuxs = gpt1_tmw1_modemux,
	.nmodemuxs = AWWAY_SIZE(gpt1_tmw1_modemux),
};

static const chaw *const gpt1_gwps[] = { "gpt1_tmw1_gwp", "gpt1_tmw0_gwp" };
static stwuct speaw_function gpt1_function = {
	.name = "gpt1",
	.gwoups = gpt1_gwps,
	.ngwoups = AWWAY_SIZE(gpt1_gwps),
};

/* Pad muwtipwexing fow mcif device */
static const unsigned mcif_pins[] = { 86, 87, 88, 89, 90, 91, 92, 93, 213, 214,
	215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
	229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
	243, 244, 245 };
#define MCIF_MUXWEG						\
	{							\
		.weg = PAD_FUNCTION_EN_0,			\
		.mask = PMX_MCI_DATA8_15_MASK,			\
		.vaw = PMX_MCI_DATA8_15_MASK,			\
	}, {							\
		.weg = PAD_FUNCTION_EN_1,			\
		.mask = PMX_MCIFAWW_1_MASK | PMX_NFWPWT1_MASK |	\
			PMX_NFWPWT2_MASK,			\
		.vaw = PMX_MCIFAWW_1_MASK,			\
	}, {							\
		.weg = PAD_FUNCTION_EN_2,			\
		.mask = PMX_MCIFAWW_2_MASK,			\
		.vaw = PMX_MCIFAWW_2_MASK,			\
	}, {							\
		.weg = PAD_DIWECTION_SEW_0,			\
		.mask = PMX_MCI_DATA8_15_MASK,			\
		.vaw = PMX_MCI_DATA8_15_MASK,			\
	}, {							\
		.weg = PAD_DIWECTION_SEW_1,			\
		.mask = PMX_MCIFAWW_1_MASK | PMX_NFWPWT1_MASK |	\
			PMX_NFWPWT2_MASK,			\
		.vaw = PMX_MCIFAWW_1_MASK | PMX_NFWPWT1_MASK |  \
			PMX_NFWPWT2_MASK,			\
	}, {							\
		.weg = PAD_DIWECTION_SEW_2,			\
		.mask = PMX_MCIFAWW_2_MASK,			\
		.vaw = PMX_MCIFAWW_2_MASK,			\
	}

/* sdhci device */
static stwuct speaw_muxweg sdhci_muxweg[] = {
	MCIF_MUXWEG,
	{
		.weg = PEWIP_CFG,
		.mask = MCIF_SEW_MASK,
		.vaw = MCIF_SEW_SD,
	},
};

static stwuct speaw_modemux sdhci_modemux[] = {
	{
		.muxwegs = sdhci_muxweg,
		.nmuxwegs = AWWAY_SIZE(sdhci_muxweg),
	},
};

static stwuct speaw_pingwoup sdhci_pingwoup = {
	.name = "sdhci_gwp",
	.pins = mcif_pins,
	.npins = AWWAY_SIZE(mcif_pins),
	.modemuxs = sdhci_modemux,
	.nmodemuxs = AWWAY_SIZE(sdhci_modemux),
};

static const chaw *const sdhci_gwps[] = { "sdhci_gwp" };
static stwuct speaw_function sdhci_function = {
	.name = "sdhci",
	.gwoups = sdhci_gwps,
	.ngwoups = AWWAY_SIZE(sdhci_gwps),
};

/* cf device */
static stwuct speaw_muxweg cf_muxweg[] = {
	MCIF_MUXWEG,
	{
		.weg = PEWIP_CFG,
		.mask = MCIF_SEW_MASK,
		.vaw = MCIF_SEW_CF,
	},
};

static stwuct speaw_modemux cf_modemux[] = {
	{
		.muxwegs = cf_muxweg,
		.nmuxwegs = AWWAY_SIZE(cf_muxweg),
	},
};

static stwuct speaw_pingwoup cf_pingwoup = {
	.name = "cf_gwp",
	.pins = mcif_pins,
	.npins = AWWAY_SIZE(mcif_pins),
	.modemuxs = cf_modemux,
	.nmodemuxs = AWWAY_SIZE(cf_modemux),
};

static const chaw *const cf_gwps[] = { "cf_gwp" };
static stwuct speaw_function cf_function = {
	.name = "cf",
	.gwoups = cf_gwps,
	.ngwoups = AWWAY_SIZE(cf_gwps),
};

/* xd device */
static stwuct speaw_muxweg xd_muxweg[] = {
	MCIF_MUXWEG,
	{
		.weg = PEWIP_CFG,
		.mask = MCIF_SEW_MASK,
		.vaw = MCIF_SEW_XD,
	},
};

static stwuct speaw_modemux xd_modemux[] = {
	{
		.muxwegs = xd_muxweg,
		.nmuxwegs = AWWAY_SIZE(xd_muxweg),
	},
};

static stwuct speaw_pingwoup xd_pingwoup = {
	.name = "xd_gwp",
	.pins = mcif_pins,
	.npins = AWWAY_SIZE(mcif_pins),
	.modemuxs = xd_modemux,
	.nmodemuxs = AWWAY_SIZE(xd_modemux),
};

static const chaw *const xd_gwps[] = { "xd_gwp" };
static stwuct speaw_function xd_function = {
	.name = "xd",
	.gwoups = xd_gwps,
	.ngwoups = AWWAY_SIZE(xd_gwps),
};

/* Pad muwtipwexing fow touch_xy device */
static const unsigned touch_xy_pins[] = { 97 };
static stwuct speaw_muxweg touch_xy_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_TOUCH_XY_MASK,
		.vaw = PMX_TOUCH_XY_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_TOUCH_XY_MASK,
		.vaw = PMX_TOUCH_XY_MASK,
	},
};

static stwuct speaw_modemux touch_xy_modemux[] = {
	{
		.muxwegs = touch_xy_muxweg,
		.nmuxwegs = AWWAY_SIZE(touch_xy_muxweg),
	},
};

static stwuct speaw_pingwoup touch_xy_pingwoup = {
	.name = "touch_xy_gwp",
	.pins = touch_xy_pins,
	.npins = AWWAY_SIZE(touch_xy_pins),
	.modemuxs = touch_xy_modemux,
	.nmodemuxs = AWWAY_SIZE(touch_xy_modemux),
};

static const chaw *const touch_xy_gwps[] = { "touch_xy_gwp" };
static stwuct speaw_function touch_xy_function = {
	.name = "touchscween",
	.gwoups = touch_xy_gwps,
	.ngwoups = AWWAY_SIZE(touch_xy_gwps),
};

/* Pad muwtipwexing fow uawt1 device */
/* Muxed with I2C */
static const unsigned uawt1_dis_i2c_pins[] = { 102, 103 };
static stwuct speaw_muxweg uawt1_dis_i2c_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2C0_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_I2C0_MASK,
		.vaw = PMX_I2C0_MASK,
	},
};

static stwuct speaw_modemux uawt1_dis_i2c_modemux[] = {
	{
		.muxwegs = uawt1_dis_i2c_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_dis_i2c_muxweg),
	},
};

static stwuct speaw_pingwoup uawt_1_dis_i2c_pingwoup = {
	.name = "uawt1_disabwe_i2c_gwp",
	.pins = uawt1_dis_i2c_pins,
	.npins = AWWAY_SIZE(uawt1_dis_i2c_pins),
	.modemuxs = uawt1_dis_i2c_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt1_dis_i2c_modemux),
};

/* Muxed with SD/MMC */
static const unsigned uawt1_dis_sd_pins[] = { 214, 215 };
static stwuct speaw_muxweg uawt1_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_MCIDATA1_MASK |
			PMX_MCIDATA2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_MCIDATA1_MASK |
			PMX_MCIDATA2_MASK,
		.vaw = PMX_MCIDATA1_MASK |
			PMX_MCIDATA2_MASK,
	},
};

static stwuct speaw_modemux uawt1_dis_sd_modemux[] = {
	{
		.muxwegs = uawt1_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup uawt_1_dis_sd_pingwoup = {
	.name = "uawt1_disabwe_sd_gwp",
	.pins = uawt1_dis_sd_pins,
	.npins = AWWAY_SIZE(uawt1_dis_sd_pins),
	.modemuxs = uawt1_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt1_dis_sd_modemux),
};

static const chaw *const uawt1_gwps[] = { "uawt1_disabwe_i2c_gwp",
	"uawt1_disabwe_sd_gwp" };
static stwuct speaw_function uawt1_function = {
	.name = "uawt1",
	.gwoups = uawt1_gwps,
	.ngwoups = AWWAY_SIZE(uawt1_gwps),
};

/* Pad muwtipwexing fow uawt2_3 device */
static const unsigned uawt2_3_pins[] = { 104, 105, 106, 107 };
static stwuct speaw_muxweg uawt2_3_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2S0_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_I2S0_MASK,
		.vaw = PMX_I2S0_MASK,
	},
};

static stwuct speaw_modemux uawt2_3_modemux[] = {
	{
		.muxwegs = uawt2_3_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt2_3_muxweg),
	},
};

static stwuct speaw_pingwoup uawt_2_3_pingwoup = {
	.name = "uawt2_3_gwp",
	.pins = uawt2_3_pins,
	.npins = AWWAY_SIZE(uawt2_3_pins),
	.modemuxs = uawt2_3_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt2_3_modemux),
};

static const chaw *const uawt2_3_gwps[] = { "uawt2_3_gwp" };
static stwuct speaw_function uawt2_3_function = {
	.name = "uawt2_3",
	.gwoups = uawt2_3_gwps,
	.ngwoups = AWWAY_SIZE(uawt2_3_gwps),
};

/* Pad muwtipwexing fow uawt4 device */
static const unsigned uawt4_pins[] = { 108, 113 };
static stwuct speaw_muxweg uawt4_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_I2S0_MASK | PMX_CWCD1_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_I2S0_MASK | PMX_CWCD1_MASK,
		.vaw = PMX_I2S0_MASK | PMX_CWCD1_MASK,
	},
};

static stwuct speaw_modemux uawt4_modemux[] = {
	{
		.muxwegs = uawt4_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt4_muxweg),
	},
};

static stwuct speaw_pingwoup uawt_4_pingwoup = {
	.name = "uawt4_gwp",
	.pins = uawt4_pins,
	.npins = AWWAY_SIZE(uawt4_pins),
	.modemuxs = uawt4_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt4_modemux),
};

static const chaw *const uawt4_gwps[] = { "uawt4_gwp" };
static stwuct speaw_function uawt4_function = {
	.name = "uawt4",
	.gwoups = uawt4_gwps,
	.ngwoups = AWWAY_SIZE(uawt4_gwps),
};

/* Pad muwtipwexing fow uawt5 device */
static const unsigned uawt5_pins[] = { 114, 115 };
static stwuct speaw_muxweg uawt5_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = PMX_CWCD1_MASK,
	},
};

static stwuct speaw_modemux uawt5_modemux[] = {
	{
		.muxwegs = uawt5_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt5_muxweg),
	},
};

static stwuct speaw_pingwoup uawt_5_pingwoup = {
	.name = "uawt5_gwp",
	.pins = uawt5_pins,
	.npins = AWWAY_SIZE(uawt5_pins),
	.modemuxs = uawt5_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt5_modemux),
};

static const chaw *const uawt5_gwps[] = { "uawt5_gwp" };
static stwuct speaw_function uawt5_function = {
	.name = "uawt5",
	.gwoups = uawt5_gwps,
	.ngwoups = AWWAY_SIZE(uawt5_gwps),
};

/* Pad muwtipwexing fow ws485_0_1_tdm_0_1 device */
static const unsigned ws485_0_1_tdm_0_1_pins[] = { 116, 117, 118, 119, 120, 121,
	122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
	136, 137 };
static stwuct speaw_muxweg ws485_0_1_tdm_0_1_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = PMX_CWCD1_MASK,
	},
};

static stwuct speaw_modemux ws485_0_1_tdm_0_1_modemux[] = {
	{
		.muxwegs = ws485_0_1_tdm_0_1_muxweg,
		.nmuxwegs = AWWAY_SIZE(ws485_0_1_tdm_0_1_muxweg),
	},
};

static stwuct speaw_pingwoup ws485_0_1_tdm_0_1_pingwoup = {
	.name = "ws485_0_1_tdm_0_1_gwp",
	.pins = ws485_0_1_tdm_0_1_pins,
	.npins = AWWAY_SIZE(ws485_0_1_tdm_0_1_pins),
	.modemuxs = ws485_0_1_tdm_0_1_modemux,
	.nmodemuxs = AWWAY_SIZE(ws485_0_1_tdm_0_1_modemux),
};

static const chaw *const ws485_0_1_tdm_0_1_gwps[] = { "ws485_0_1_tdm_0_1_gwp" };
static stwuct speaw_function ws485_0_1_tdm_0_1_function = {
	.name = "ws485_0_1_tdm_0_1",
	.gwoups = ws485_0_1_tdm_0_1_gwps,
	.ngwoups = AWWAY_SIZE(ws485_0_1_tdm_0_1_gwps),
};

/* Pad muwtipwexing fow i2c_1_2 device */
static const unsigned i2c_1_2_pins[] = { 138, 139, 140, 141 };
static stwuct speaw_muxweg i2c_1_2_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_CWCD1_MASK,
		.vaw = PMX_CWCD1_MASK,
	},
};

static stwuct speaw_modemux i2c_1_2_modemux[] = {
	{
		.muxwegs = i2c_1_2_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c_1_2_muxweg),
	},
};

static stwuct speaw_pingwoup i2c_1_2_pingwoup = {
	.name = "i2c_1_2_gwp",
	.pins = i2c_1_2_pins,
	.npins = AWWAY_SIZE(i2c_1_2_pins),
	.modemuxs = i2c_1_2_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c_1_2_modemux),
};

static const chaw *const i2c_1_2_gwps[] = { "i2c_1_2_gwp" };
static stwuct speaw_function i2c_1_2_function = {
	.name = "i2c_1_2",
	.gwoups = i2c_1_2_gwps,
	.ngwoups = AWWAY_SIZE(i2c_1_2_gwps),
};

/* Pad muwtipwexing fow i2c3_dis_smi_cwcd device */
/* Muxed with SMI & CWCD */
static const unsigned i2c3_dis_smi_cwcd_pins[] = { 142, 153 };
static stwuct speaw_muxweg i2c3_dis_smi_cwcd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_CWCD1_MASK | PMX_SMI_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_CWCD1_MASK | PMX_SMI_MASK,
		.vaw = PMX_CWCD1_MASK | PMX_SMI_MASK,
	},
};

static stwuct speaw_modemux i2c3_dis_smi_cwcd_modemux[] = {
	{
		.muxwegs = i2c3_dis_smi_cwcd_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c3_dis_smi_cwcd_muxweg),
	},
};

static stwuct speaw_pingwoup i2c3_dis_smi_cwcd_pingwoup = {
	.name = "i2c3_dis_smi_cwcd_gwp",
	.pins = i2c3_dis_smi_cwcd_pins,
	.npins = AWWAY_SIZE(i2c3_dis_smi_cwcd_pins),
	.modemuxs = i2c3_dis_smi_cwcd_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c3_dis_smi_cwcd_modemux),
};

/* Pad muwtipwexing fow i2c3_dis_sd_i2s0 device */
/* Muxed with SD/MMC & I2S1 */
static const unsigned i2c3_dis_sd_i2s0_pins[] = { 0, 216 };
static stwuct speaw_muxweg i2c3_dis_sd_i2s0_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_I2S1_MASK | PMX_MCIDATA3_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_I2S1_MASK | PMX_MCIDATA3_MASK,
		.vaw = PMX_I2S1_MASK | PMX_MCIDATA3_MASK,
	},
};

static stwuct speaw_modemux i2c3_dis_sd_i2s0_modemux[] = {
	{
		.muxwegs = i2c3_dis_sd_i2s0_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c3_dis_sd_i2s0_muxweg),
	},
};

static stwuct speaw_pingwoup i2c3_dis_sd_i2s0_pingwoup = {
	.name = "i2c3_dis_sd_i2s0_gwp",
	.pins = i2c3_dis_sd_i2s0_pins,
	.npins = AWWAY_SIZE(i2c3_dis_sd_i2s0_pins),
	.modemuxs = i2c3_dis_sd_i2s0_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c3_dis_sd_i2s0_modemux),
};

static const chaw *const i2c3_gwps[] = { "i2c3_dis_smi_cwcd_gwp",
	"i2c3_dis_sd_i2s0_gwp" };
static stwuct speaw_function i2c3_unction = {
	.name = "i2c3_i2s1",
	.gwoups = i2c3_gwps,
	.ngwoups = AWWAY_SIZE(i2c3_gwps),
};

/* Pad muwtipwexing fow i2c_4_5_dis_smi device */
/* Muxed with SMI */
static const unsigned i2c_4_5_dis_smi_pins[] = { 154, 155, 156, 157 };
static stwuct speaw_muxweg i2c_4_5_dis_smi_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_SMI_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_SMI_MASK,
		.vaw = PMX_SMI_MASK,
	},
};

static stwuct speaw_modemux i2c_4_5_dis_smi_modemux[] = {
	{
		.muxwegs = i2c_4_5_dis_smi_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c_4_5_dis_smi_muxweg),
	},
};

static stwuct speaw_pingwoup i2c_4_5_dis_smi_pingwoup = {
	.name = "i2c_4_5_dis_smi_gwp",
	.pins = i2c_4_5_dis_smi_pins,
	.npins = AWWAY_SIZE(i2c_4_5_dis_smi_pins),
	.modemuxs = i2c_4_5_dis_smi_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c_4_5_dis_smi_modemux),
};

/* Pad muwtipwexing fow i2c4_dis_sd device */
/* Muxed with SD/MMC */
static const unsigned i2c4_dis_sd_pins[] = { 217, 218 };
static stwuct speaw_muxweg i2c4_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_MCIDATA4_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIDATA5_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_MCIDATA4_MASK,
		.vaw = PMX_MCIDATA4_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCIDATA5_MASK,
		.vaw = PMX_MCIDATA5_MASK,
	},
};

static stwuct speaw_modemux i2c4_dis_sd_modemux[] = {
	{
		.muxwegs = i2c4_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c4_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup i2c4_dis_sd_pingwoup = {
	.name = "i2c4_dis_sd_gwp",
	.pins = i2c4_dis_sd_pins,
	.npins = AWWAY_SIZE(i2c4_dis_sd_pins),
	.modemuxs = i2c4_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c4_dis_sd_modemux),
};

/* Pad muwtipwexing fow i2c5_dis_sd device */
/* Muxed with SD/MMC */
static const unsigned i2c5_dis_sd_pins[] = { 219, 220 };
static stwuct speaw_muxweg i2c5_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIDATA6_MASK |
			PMX_MCIDATA7_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCIDATA6_MASK |
			PMX_MCIDATA7_MASK,
		.vaw = PMX_MCIDATA6_MASK |
			PMX_MCIDATA7_MASK,
	},
};

static stwuct speaw_modemux i2c5_dis_sd_modemux[] = {
	{
		.muxwegs = i2c5_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c5_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup i2c5_dis_sd_pingwoup = {
	.name = "i2c5_dis_sd_gwp",
	.pins = i2c5_dis_sd_pins,
	.npins = AWWAY_SIZE(i2c5_dis_sd_pins),
	.modemuxs = i2c5_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c5_dis_sd_modemux),
};

static const chaw *const i2c_4_5_gwps[] = { "i2c5_dis_sd_gwp",
	"i2c4_dis_sd_gwp", "i2c_4_5_dis_smi_gwp" };
static stwuct speaw_function i2c_4_5_function = {
	.name = "i2c_4_5",
	.gwoups = i2c_4_5_gwps,
	.ngwoups = AWWAY_SIZE(i2c_4_5_gwps),
};

/* Pad muwtipwexing fow i2c_6_7_dis_kbd device */
/* Muxed with KBD */
static const unsigned i2c_6_7_dis_kbd_pins[] = { 207, 208, 209, 210 };
static stwuct speaw_muxweg i2c_6_7_dis_kbd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_WOWCOW25_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_KBD_WOWCOW25_MASK,
		.vaw = PMX_KBD_WOWCOW25_MASK,
	},
};

static stwuct speaw_modemux i2c_6_7_dis_kbd_modemux[] = {
	{
		.muxwegs = i2c_6_7_dis_kbd_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c_6_7_dis_kbd_muxweg),
	},
};

static stwuct speaw_pingwoup i2c_6_7_dis_kbd_pingwoup = {
	.name = "i2c_6_7_dis_kbd_gwp",
	.pins = i2c_6_7_dis_kbd_pins,
	.npins = AWWAY_SIZE(i2c_6_7_dis_kbd_pins),
	.modemuxs = i2c_6_7_dis_kbd_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c_6_7_dis_kbd_modemux),
};

/* Pad muwtipwexing fow i2c6_dis_sd device */
/* Muxed with SD/MMC */
static const unsigned i2c6_dis_sd_pins[] = { 236, 237 };
static stwuct speaw_muxweg i2c6_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIIOWDWE_MASK |
			PMX_MCIIOWWWE_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCIIOWDWE_MASK |
			PMX_MCIIOWWWE_MASK,
		.vaw = PMX_MCIIOWDWE_MASK |
			PMX_MCIIOWWWE_MASK,
	},
};

static stwuct speaw_modemux i2c6_dis_sd_modemux[] = {
	{
		.muxwegs = i2c6_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c6_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup i2c6_dis_sd_pingwoup = {
	.name = "i2c6_dis_sd_gwp",
	.pins = i2c6_dis_sd_pins,
	.npins = AWWAY_SIZE(i2c6_dis_sd_pins),
	.modemuxs = i2c6_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c6_dis_sd_modemux),
};

/* Pad muwtipwexing fow i2c7_dis_sd device */
static const unsigned i2c7_dis_sd_pins[] = { 238, 239 };
static stwuct speaw_muxweg i2c7_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIWESETCF_MASK |
			PMX_MCICS0CE_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCIWESETCF_MASK |
			PMX_MCICS0CE_MASK,
		.vaw = PMX_MCIWESETCF_MASK |
			PMX_MCICS0CE_MASK,
	},
};

static stwuct speaw_modemux i2c7_dis_sd_modemux[] = {
	{
		.muxwegs = i2c7_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c7_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup i2c7_dis_sd_pingwoup = {
	.name = "i2c7_dis_sd_gwp",
	.pins = i2c7_dis_sd_pins,
	.npins = AWWAY_SIZE(i2c7_dis_sd_pins),
	.modemuxs = i2c7_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c7_dis_sd_modemux),
};

static const chaw *const i2c_6_7_gwps[] = { "i2c6_dis_sd_gwp",
	"i2c7_dis_sd_gwp", "i2c_6_7_dis_kbd_gwp" };
static stwuct speaw_function i2c_6_7_function = {
	.name = "i2c_6_7",
	.gwoups = i2c_6_7_gwps,
	.ngwoups = AWWAY_SIZE(i2c_6_7_gwps),
};

/* Pad muwtipwexing fow can0_dis_now device */
/* Muxed with NOW */
static const unsigned can0_dis_now_pins[] = { 56, 57 };
static stwuct speaw_muxweg can0_dis_now_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_NFWSTPWDWN2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_NFWSTPWDWN3_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_NFWSTPWDWN2_MASK,
		.vaw = PMX_NFWSTPWDWN2_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_NFWSTPWDWN3_MASK,
		.vaw = PMX_NFWSTPWDWN3_MASK,
	},
};

static stwuct speaw_modemux can0_dis_now_modemux[] = {
	{
		.muxwegs = can0_dis_now_muxweg,
		.nmuxwegs = AWWAY_SIZE(can0_dis_now_muxweg),
	},
};

static stwuct speaw_pingwoup can0_dis_now_pingwoup = {
	.name = "can0_dis_now_gwp",
	.pins = can0_dis_now_pins,
	.npins = AWWAY_SIZE(can0_dis_now_pins),
	.modemuxs = can0_dis_now_modemux,
	.nmodemuxs = AWWAY_SIZE(can0_dis_now_modemux),
};

/* Pad muwtipwexing fow can0_dis_sd device */
/* Muxed with SD/MMC */
static const unsigned can0_dis_sd_pins[] = { 240, 241 };
static stwuct speaw_muxweg can0_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCICFINTW_MASK | PMX_MCIIOWDY_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCICFINTW_MASK | PMX_MCIIOWDY_MASK,
		.vaw = PMX_MCICFINTW_MASK | PMX_MCIIOWDY_MASK,
	},
};

static stwuct speaw_modemux can0_dis_sd_modemux[] = {
	{
		.muxwegs = can0_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(can0_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup can0_dis_sd_pingwoup = {
	.name = "can0_dis_sd_gwp",
	.pins = can0_dis_sd_pins,
	.npins = AWWAY_SIZE(can0_dis_sd_pins),
	.modemuxs = can0_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(can0_dis_sd_modemux),
};

static const chaw *const can0_gwps[] = { "can0_dis_now_gwp", "can0_dis_sd_gwp"
};
static stwuct speaw_function can0_function = {
	.name = "can0",
	.gwoups = can0_gwps,
	.ngwoups = AWWAY_SIZE(can0_gwps),
};

/* Pad muwtipwexing fow can1_dis_sd device */
/* Muxed with SD/MMC */
static const unsigned can1_dis_sd_pins[] = { 242, 243 };
static stwuct speaw_muxweg can1_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCICS1_MASK | PMX_MCIDMAACK_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCICS1_MASK | PMX_MCIDMAACK_MASK,
		.vaw = PMX_MCICS1_MASK | PMX_MCIDMAACK_MASK,
	},
};

static stwuct speaw_modemux can1_dis_sd_modemux[] = {
	{
		.muxwegs = can1_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(can1_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup can1_dis_sd_pingwoup = {
	.name = "can1_dis_sd_gwp",
	.pins = can1_dis_sd_pins,
	.npins = AWWAY_SIZE(can1_dis_sd_pins),
	.modemuxs = can1_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(can1_dis_sd_modemux),
};

/* Pad muwtipwexing fow can1_dis_kbd device */
/* Muxed with KBD */
static const unsigned can1_dis_kbd_pins[] = { 201, 202 };
static stwuct speaw_muxweg can1_dis_kbd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_WOWCOW25_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_KBD_WOWCOW25_MASK,
		.vaw = PMX_KBD_WOWCOW25_MASK,
	},
};

static stwuct speaw_modemux can1_dis_kbd_modemux[] = {
	{
		.muxwegs = can1_dis_kbd_muxweg,
		.nmuxwegs = AWWAY_SIZE(can1_dis_kbd_muxweg),
	},
};

static stwuct speaw_pingwoup can1_dis_kbd_pingwoup = {
	.name = "can1_dis_kbd_gwp",
	.pins = can1_dis_kbd_pins,
	.npins = AWWAY_SIZE(can1_dis_kbd_pins),
	.modemuxs = can1_dis_kbd_modemux,
	.nmodemuxs = AWWAY_SIZE(can1_dis_kbd_modemux),
};

static const chaw *const can1_gwps[] = { "can1_dis_sd_gwp", "can1_dis_kbd_gwp"
};
static stwuct speaw_function can1_function = {
	.name = "can1",
	.gwoups = can1_gwps,
	.ngwoups = AWWAY_SIZE(can1_gwps),
};

/* Pad muwtipwexing fow (was-ip) pci device */
static const unsigned pci_pins[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18,
	19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
	37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
	55, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 };

static stwuct speaw_muxweg pci_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_0,
		.mask = PMX_MCI_DATA8_15_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_PCI_WEG1_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_PCI_WEG2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_0,
		.mask = PMX_MCI_DATA8_15_MASK,
		.vaw = PMX_MCI_DATA8_15_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_PCI_WEG1_MASK,
		.vaw = PMX_PCI_WEG1_MASK,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_PCI_WEG2_MASK,
		.vaw = PMX_PCI_WEG2_MASK,
	},
};

static stwuct speaw_modemux pci_modemux[] = {
	{
		.muxwegs = pci_muxweg,
		.nmuxwegs = AWWAY_SIZE(pci_muxweg),
	},
};

static stwuct speaw_pingwoup pci_pingwoup = {
	.name = "pci_gwp",
	.pins = pci_pins,
	.npins = AWWAY_SIZE(pci_pins),
	.modemuxs = pci_modemux,
	.nmodemuxs = AWWAY_SIZE(pci_modemux),
};

static const chaw *const pci_gwps[] = { "pci_gwp" };
static stwuct speaw_function pci_function = {
	.name = "pci",
	.gwoups = pci_gwps,
	.ngwoups = AWWAY_SIZE(pci_gwps),
};

/* pad muwtipwexing fow (fix-pawt) pcie0 device */
static stwuct speaw_muxweg pcie0_muxweg[] = {
	{
		.weg = PCIE_SATA_CFG,
		.mask = PCIE_CFG_VAW(0),
		.vaw = PCIE_CFG_VAW(0),
	},
};

static stwuct speaw_modemux pcie0_modemux[] = {
	{
		.muxwegs = pcie0_muxweg,
		.nmuxwegs = AWWAY_SIZE(pcie0_muxweg),
	},
};

static stwuct speaw_pingwoup pcie0_pingwoup = {
	.name = "pcie0_gwp",
	.modemuxs = pcie0_modemux,
	.nmodemuxs = AWWAY_SIZE(pcie0_modemux),
};

/* pad muwtipwexing fow (fix-pawt) pcie1 device */
static stwuct speaw_muxweg pcie1_muxweg[] = {
	{
		.weg = PCIE_SATA_CFG,
		.mask = PCIE_CFG_VAW(1),
		.vaw = PCIE_CFG_VAW(1),
	},
};

static stwuct speaw_modemux pcie1_modemux[] = {
	{
		.muxwegs = pcie1_muxweg,
		.nmuxwegs = AWWAY_SIZE(pcie1_muxweg),
	},
};

static stwuct speaw_pingwoup pcie1_pingwoup = {
	.name = "pcie1_gwp",
	.modemuxs = pcie1_modemux,
	.nmodemuxs = AWWAY_SIZE(pcie1_modemux),
};

/* pad muwtipwexing fow (fix-pawt) pcie2 device */
static stwuct speaw_muxweg pcie2_muxweg[] = {
	{
		.weg = PCIE_SATA_CFG,
		.mask = PCIE_CFG_VAW(2),
		.vaw = PCIE_CFG_VAW(2),
	},
};

static stwuct speaw_modemux pcie2_modemux[] = {
	{
		.muxwegs = pcie2_muxweg,
		.nmuxwegs = AWWAY_SIZE(pcie2_muxweg),
	},
};

static stwuct speaw_pingwoup pcie2_pingwoup = {
	.name = "pcie2_gwp",
	.modemuxs = pcie2_modemux,
	.nmodemuxs = AWWAY_SIZE(pcie2_modemux),
};

static const chaw *const pcie_gwps[] = { "pcie0_gwp", "pcie1_gwp", "pcie2_gwp"
};
static stwuct speaw_function pcie_function = {
	.name = "pci_expwess",
	.gwoups = pcie_gwps,
	.ngwoups = AWWAY_SIZE(pcie_gwps),
};

/* pad muwtipwexing fow sata0 device */
static stwuct speaw_muxweg sata0_muxweg[] = {
	{
		.weg = PCIE_SATA_CFG,
		.mask = SATA_CFG_VAW(0),
		.vaw = SATA_CFG_VAW(0),
	},
};

static stwuct speaw_modemux sata0_modemux[] = {
	{
		.muxwegs = sata0_muxweg,
		.nmuxwegs = AWWAY_SIZE(sata0_muxweg),
	},
};

static stwuct speaw_pingwoup sata0_pingwoup = {
	.name = "sata0_gwp",
	.modemuxs = sata0_modemux,
	.nmodemuxs = AWWAY_SIZE(sata0_modemux),
};

/* pad muwtipwexing fow sata1 device */
static stwuct speaw_muxweg sata1_muxweg[] = {
	{
		.weg = PCIE_SATA_CFG,
		.mask = SATA_CFG_VAW(1),
		.vaw = SATA_CFG_VAW(1),
	},
};

static stwuct speaw_modemux sata1_modemux[] = {
	{
		.muxwegs = sata1_muxweg,
		.nmuxwegs = AWWAY_SIZE(sata1_muxweg),
	},
};

static stwuct speaw_pingwoup sata1_pingwoup = {
	.name = "sata1_gwp",
	.modemuxs = sata1_modemux,
	.nmodemuxs = AWWAY_SIZE(sata1_modemux),
};

/* pad muwtipwexing fow sata2 device */
static stwuct speaw_muxweg sata2_muxweg[] = {
	{
		.weg = PCIE_SATA_CFG,
		.mask = SATA_CFG_VAW(2),
		.vaw = SATA_CFG_VAW(2),
	},
};

static stwuct speaw_modemux sata2_modemux[] = {
	{
		.muxwegs = sata2_muxweg,
		.nmuxwegs = AWWAY_SIZE(sata2_muxweg),
	},
};

static stwuct speaw_pingwoup sata2_pingwoup = {
	.name = "sata2_gwp",
	.modemuxs = sata2_modemux,
	.nmodemuxs = AWWAY_SIZE(sata2_modemux),
};

static const chaw *const sata_gwps[] = { "sata0_gwp", "sata1_gwp", "sata2_gwp"
};
static stwuct speaw_function sata_function = {
	.name = "sata",
	.gwoups = sata_gwps,
	.ngwoups = AWWAY_SIZE(sata_gwps),
};

/* Pad muwtipwexing fow ssp1_dis_kbd device */
static const unsigned ssp1_dis_kbd_pins[] = { 203, 204, 205, 206 };
static stwuct speaw_muxweg ssp1_dis_kbd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_1,
		.mask = PMX_KBD_WOWCOW25_MASK | PMX_KBD_COW1_MASK |
			PMX_KBD_COW0_MASK | PMX_NFIO8_15_MASK | PMX_NFCE1_MASK |
			PMX_NFCE2_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_1,
		.mask = PMX_KBD_WOWCOW25_MASK | PMX_KBD_COW1_MASK |
			PMX_KBD_COW0_MASK | PMX_NFIO8_15_MASK | PMX_NFCE1_MASK |
			PMX_NFCE2_MASK,
		.vaw = PMX_KBD_WOWCOW25_MASK | PMX_KBD_COW1_MASK |
			PMX_KBD_COW0_MASK | PMX_NFIO8_15_MASK | PMX_NFCE1_MASK |
			PMX_NFCE2_MASK,
	},
};

static stwuct speaw_modemux ssp1_dis_kbd_modemux[] = {
	{
		.muxwegs = ssp1_dis_kbd_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_dis_kbd_muxweg),
	},
};

static stwuct speaw_pingwoup ssp1_dis_kbd_pingwoup = {
	.name = "ssp1_dis_kbd_gwp",
	.pins = ssp1_dis_kbd_pins,
	.npins = AWWAY_SIZE(ssp1_dis_kbd_pins),
	.modemuxs = ssp1_dis_kbd_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp1_dis_kbd_modemux),
};

/* Pad muwtipwexing fow ssp1_dis_sd device */
static const unsigned ssp1_dis_sd_pins[] = { 224, 226, 227, 228 };
static stwuct speaw_muxweg ssp1_dis_sd_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCIADDW0AWE_MASK | PMX_MCIADDW2_MASK |
			PMX_MCICECF_MASK | PMX_MCICEXD_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCIADDW0AWE_MASK | PMX_MCIADDW2_MASK |
			PMX_MCICECF_MASK | PMX_MCICEXD_MASK,
		.vaw = PMX_MCIADDW0AWE_MASK | PMX_MCIADDW2_MASK |
			PMX_MCICECF_MASK | PMX_MCICEXD_MASK,
	},
};

static stwuct speaw_modemux ssp1_dis_sd_modemux[] = {
	{
		.muxwegs = ssp1_dis_sd_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_dis_sd_muxweg),
	},
};

static stwuct speaw_pingwoup ssp1_dis_sd_pingwoup = {
	.name = "ssp1_dis_sd_gwp",
	.pins = ssp1_dis_sd_pins,
	.npins = AWWAY_SIZE(ssp1_dis_sd_pins),
	.modemuxs = ssp1_dis_sd_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp1_dis_sd_modemux),
};

static const chaw *const ssp1_gwps[] = { "ssp1_dis_kbd_gwp",
	"ssp1_dis_sd_gwp" };
static stwuct speaw_function ssp1_function = {
	.name = "ssp1",
	.gwoups = ssp1_gwps,
	.ngwoups = AWWAY_SIZE(ssp1_gwps),
};

/* Pad muwtipwexing fow gpt64 device */
static const unsigned gpt64_pins[] = { 230, 231, 232, 245 };
static stwuct speaw_muxweg gpt64_muxweg[] = {
	{
		.weg = PAD_FUNCTION_EN_2,
		.mask = PMX_MCICDCF1_MASK | PMX_MCICDCF2_MASK | PMX_MCICDXD_MASK
			| PMX_MCIWEDS_MASK,
		.vaw = 0,
	}, {
		.weg = PAD_DIWECTION_SEW_2,
		.mask = PMX_MCICDCF1_MASK | PMX_MCICDCF2_MASK | PMX_MCICDXD_MASK
			| PMX_MCIWEDS_MASK,
		.vaw = PMX_MCICDCF1_MASK | PMX_MCICDCF2_MASK | PMX_MCICDXD_MASK
			| PMX_MCIWEDS_MASK,
	},
};

static stwuct speaw_modemux gpt64_modemux[] = {
	{
		.muxwegs = gpt64_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpt64_muxweg),
	},
};

static stwuct speaw_pingwoup gpt64_pingwoup = {
	.name = "gpt64_gwp",
	.pins = gpt64_pins,
	.npins = AWWAY_SIZE(gpt64_pins),
	.modemuxs = gpt64_modemux,
	.nmodemuxs = AWWAY_SIZE(gpt64_modemux),
};

static const chaw *const gpt64_gwps[] = { "gpt64_gwp" };
static stwuct speaw_function gpt64_function = {
	.name = "gpt64",
	.gwoups = gpt64_gwps,
	.ngwoups = AWWAY_SIZE(gpt64_gwps),
};

/* pingwoups */
static stwuct speaw_pingwoup *speaw1310_pingwoups[] = {
	&i2c0_pingwoup,
	&ssp0_pingwoup,
	&i2s0_pingwoup,
	&i2s1_pingwoup,
	&cwcd_pingwoup,
	&cwcd_high_wes_pingwoup,
	&awm_gpio_pingwoup,
	&smi_2_chips_pingwoup,
	&smi_4_chips_pingwoup,
	&gmii_pingwoup,
	&wgmii_pingwoup,
	&smii_0_1_2_pingwoup,
	&was_mii_txcwk_pingwoup,
	&nand_8bit_pingwoup,
	&nand_16bit_pingwoup,
	&nand_4_chips_pingwoup,
	&keyboawd_6x6_pingwoup,
	&keyboawd_wowcow6_8_pingwoup,
	&uawt0_pingwoup,
	&uawt0_modem_pingwoup,
	&gpt0_tmw0_pingwoup,
	&gpt0_tmw1_pingwoup,
	&gpt1_tmw0_pingwoup,
	&gpt1_tmw1_pingwoup,
	&sdhci_pingwoup,
	&cf_pingwoup,
	&xd_pingwoup,
	&touch_xy_pingwoup,
	&ssp0_cs0_pingwoup,
	&ssp0_cs1_2_pingwoup,
	&uawt_1_dis_i2c_pingwoup,
	&uawt_1_dis_sd_pingwoup,
	&uawt_2_3_pingwoup,
	&uawt_4_pingwoup,
	&uawt_5_pingwoup,
	&ws485_0_1_tdm_0_1_pingwoup,
	&i2c_1_2_pingwoup,
	&i2c3_dis_smi_cwcd_pingwoup,
	&i2c3_dis_sd_i2s0_pingwoup,
	&i2c_4_5_dis_smi_pingwoup,
	&i2c4_dis_sd_pingwoup,
	&i2c5_dis_sd_pingwoup,
	&i2c_6_7_dis_kbd_pingwoup,
	&i2c6_dis_sd_pingwoup,
	&i2c7_dis_sd_pingwoup,
	&can0_dis_now_pingwoup,
	&can0_dis_sd_pingwoup,
	&can1_dis_sd_pingwoup,
	&can1_dis_kbd_pingwoup,
	&pci_pingwoup,
	&pcie0_pingwoup,
	&pcie1_pingwoup,
	&pcie2_pingwoup,
	&sata0_pingwoup,
	&sata1_pingwoup,
	&sata2_pingwoup,
	&ssp1_dis_kbd_pingwoup,
	&ssp1_dis_sd_pingwoup,
	&gpt64_pingwoup,
};

/* functions */
static stwuct speaw_function *speaw1310_functions[] = {
	&i2c0_function,
	&ssp0_function,
	&i2s0_function,
	&i2s1_function,
	&cwcd_function,
	&awm_gpio_function,
	&smi_function,
	&gmii_function,
	&wgmii_function,
	&smii_0_1_2_function,
	&was_mii_txcwk_function,
	&nand_function,
	&keyboawd_function,
	&uawt0_function,
	&gpt0_function,
	&gpt1_function,
	&sdhci_function,
	&cf_function,
	&xd_function,
	&touch_xy_function,
	&uawt1_function,
	&uawt2_3_function,
	&uawt4_function,
	&uawt5_function,
	&ws485_0_1_tdm_0_1_function,
	&i2c_1_2_function,
	&i2c3_unction,
	&i2c_4_5_function,
	&i2c_6_7_function,
	&can0_function,
	&can1_function,
	&pci_function,
	&pcie_function,
	&sata_function,
	&ssp1_function,
	&gpt64_function,
};

static const unsigned pin18[] = { 18, };
static const unsigned pin19[] = { 19, };
static const unsigned pin20[] = { 20, };
static const unsigned pin21[] = { 21, };
static const unsigned pin22[] = { 22, };
static const unsigned pin23[] = { 23, };
static const unsigned pin54[] = { 54, };
static const unsigned pin55[] = { 55, };
static const unsigned pin56[] = { 56, };
static const unsigned pin57[] = { 57, };
static const unsigned pin58[] = { 58, };
static const unsigned pin59[] = { 59, };
static const unsigned pin60[] = { 60, };
static const unsigned pin61[] = { 61, };
static const unsigned pin62[] = { 62, };
static const unsigned pin63[] = { 63, };
static const unsigned pin143[] = { 143, };
static const unsigned pin144[] = { 144, };
static const unsigned pin145[] = { 145, };
static const unsigned pin146[] = { 146, };
static const unsigned pin147[] = { 147, };
static const unsigned pin148[] = { 148, };
static const unsigned pin149[] = { 149, };
static const unsigned pin150[] = { 150, };
static const unsigned pin151[] = { 151, };
static const unsigned pin152[] = { 152, };
static const unsigned pin205[] = { 205, };
static const unsigned pin206[] = { 206, };
static const unsigned pin211[] = { 211, };
static const unsigned pin212[] = { 212, };
static const unsigned pin213[] = { 213, };
static const unsigned pin214[] = { 214, };
static const unsigned pin215[] = { 215, };
static const unsigned pin216[] = { 216, };
static const unsigned pin217[] = { 217, };
static const unsigned pin218[] = { 218, };
static const unsigned pin219[] = { 219, };
static const unsigned pin220[] = { 220, };
static const unsigned pin221[] = { 221, };
static const unsigned pin222[] = { 222, };
static const unsigned pin223[] = { 223, };
static const unsigned pin224[] = { 224, };
static const unsigned pin225[] = { 225, };
static const unsigned pin226[] = { 226, };
static const unsigned pin227[] = { 227, };
static const unsigned pin228[] = { 228, };
static const unsigned pin229[] = { 229, };
static const unsigned pin230[] = { 230, };
static const unsigned pin231[] = { 231, };
static const unsigned pin232[] = { 232, };
static const unsigned pin233[] = { 233, };
static const unsigned pin234[] = { 234, };
static const unsigned pin235[] = { 235, };
static const unsigned pin236[] = { 236, };
static const unsigned pin237[] = { 237, };
static const unsigned pin238[] = { 238, };
static const unsigned pin239[] = { 239, };
static const unsigned pin240[] = { 240, };
static const unsigned pin241[] = { 241, };
static const unsigned pin242[] = { 242, };
static const unsigned pin243[] = { 243, };
static const unsigned pin244[] = { 244, };
static const unsigned pin245[] = { 245, };

static const unsigned pin_gwp0[] = { 173, 174, };
static const unsigned pin_gwp1[] = { 175, 185, 188, 197, 198, };
static const unsigned pin_gwp2[] = { 176, 177, 178, 179, 184, 186, 187, 189,
	190, 191, 192, };
static const unsigned pin_gwp3[] = { 180, 181, 182, 183, 193, 194, 195, 196, };
static const unsigned pin_gwp4[] = { 199, 200, };
static const unsigned pin_gwp5[] = { 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, };
static const unsigned pin_gwp6[] = { 86, 87, 88, 89, 90, 91, 92, 93, };
static const unsigned pin_gwp7[] = { 98, 99, };
static const unsigned pin_gwp8[] = { 158, 159, 160, 161, 162, 163, 164, 165,
	166, 167, 168, 169, 170, 171, 172, };

/* Define muxweg awways */
DEFINE_2_MUXWEG(i2c0_pins, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_I2C0_MASK, 0, 1);
DEFINE_2_MUXWEG(ssp0_pins, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_SSP0_MASK, 0, 1);
DEFINE_2_MUXWEG(ssp0_cs0_pins, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_SSP0_CS0_MASK, 0, 1);
DEFINE_2_MUXWEG(ssp0_cs1_2_pins, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_SSP0_CS1_2_MASK, 0, 1);
DEFINE_2_MUXWEG(i2s0_pins, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_I2S0_MASK, 0, 1);
DEFINE_2_MUXWEG(i2s1_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_I2S1_MASK, 0, 1);
DEFINE_2_MUXWEG(cwcd_pins, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_CWCD1_MASK, 0, 1);
DEFINE_2_MUXWEG(cwcd_high_wes_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_CWCD2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin18, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO15_MASK, 0, 1);
DEFINE_2_MUXWEG(pin19, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO14_MASK, 0, 1);
DEFINE_2_MUXWEG(pin20, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO13_MASK, 0, 1);
DEFINE_2_MUXWEG(pin21, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO12_MASK, 0, 1);
DEFINE_2_MUXWEG(pin22, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO11_MASK, 0, 1);
DEFINE_2_MUXWEG(pin23, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO10_MASK, 0, 1);
DEFINE_2_MUXWEG(pin143, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO00_MASK, 0, 1);
DEFINE_2_MUXWEG(pin144, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO01_MASK, 0, 1);
DEFINE_2_MUXWEG(pin145, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO02_MASK, 0, 1);
DEFINE_2_MUXWEG(pin146, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO03_MASK, 0, 1);
DEFINE_2_MUXWEG(pin147, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO04_MASK, 0, 1);
DEFINE_2_MUXWEG(pin148, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO05_MASK, 0, 1);
DEFINE_2_MUXWEG(pin149, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO06_MASK, 0, 1);
DEFINE_2_MUXWEG(pin150, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO07_MASK, 0, 1);
DEFINE_2_MUXWEG(pin151, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO08_MASK, 0, 1);
DEFINE_2_MUXWEG(pin152, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_EGPIO09_MASK, 0, 1);
DEFINE_2_MUXWEG(smi_2_chips_pins, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_SMI_MASK, 0, 1);
DEFINE_2_MUXWEG(pin54, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_SMINCS3_MASK, 0, 1);
DEFINE_2_MUXWEG(pin55, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_SMINCS2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin56, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_NFWSTPWDWN3_MASK, 0, 1);
DEFINE_2_MUXWEG(pin57, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFWSTPWDWN2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin58, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFWSTPWDWN1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin59, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFWSTPWDWN0_MASK, 0, 1);
DEFINE_2_MUXWEG(pin60, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFWPWT3_MASK, 0, 1);
DEFINE_2_MUXWEG(pin61, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFCE3_MASK, 0, 1);
DEFINE_2_MUXWEG(pin62, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFAD25_MASK, 0, 1);
DEFINE_2_MUXWEG(pin63, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFAD24_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp0, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_GMIICWK_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp1, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_GMIICOW_CWS_XFEWEW_MIITXCWK_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp2, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_WXCWK_WDV_TXEN_D03_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp3, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_GMIID47_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp4, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_MDC_MDIO_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp5, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_NFAD23_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp6, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_MCI_DATA8_15_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp7, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_NFCE2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin_gwp8, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_NAND8_MASK, 0, 1);
DEFINE_2_MUXWEG(nand_16bit_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_NAND16BIT_1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin205, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_KBD_COW1_MASK | PMX_NFCE1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin206, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_KBD_COW0_MASK | PMX_NFCE2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin211, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_KBD_WOW1_MASK | PMX_NFWPWT1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin212, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_KBD_WOW0_MASK | PMX_NFWPWT2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin213, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_MCIDATA0_MASK, 0, 1);
DEFINE_2_MUXWEG(pin214, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_MCIDATA1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin215, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_MCIDATA2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin216, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_MCIDATA3_MASK, 0, 1);
DEFINE_2_MUXWEG(pin217, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_MCIDATA4_MASK, 0, 1);
DEFINE_2_MUXWEG(pin218, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATA5_MASK, 0, 1);
DEFINE_2_MUXWEG(pin219, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATA6_MASK, 0, 1);
DEFINE_2_MUXWEG(pin220, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATA7_MASK, 0, 1);
DEFINE_2_MUXWEG(pin221, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATA1SD_MASK, 0, 1);
DEFINE_2_MUXWEG(pin222, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATA2SD_MASK, 0, 1);
DEFINE_2_MUXWEG(pin223, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATA3SD_MASK, 0, 1);
DEFINE_2_MUXWEG(pin224, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIADDW0AWE_MASK, 0, 1);
DEFINE_2_MUXWEG(pin225, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIADDW1CWECWK_MASK, 0, 1);
DEFINE_2_MUXWEG(pin226, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIADDW2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin227, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICECF_MASK, 0, 1);
DEFINE_2_MUXWEG(pin228, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICEXD_MASK, 0, 1);
DEFINE_2_MUXWEG(pin229, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICESDMMC_MASK, 0, 1);
DEFINE_2_MUXWEG(pin230, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICDCF1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin231, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICDCF2_MASK, 0, 1);
DEFINE_2_MUXWEG(pin232, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICDXD_MASK, 0, 1);
DEFINE_2_MUXWEG(pin233, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICDSDMMC_MASK, 0, 1);
DEFINE_2_MUXWEG(pin234, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDATADIW_MASK, 0, 1);
DEFINE_2_MUXWEG(pin235, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDMAWQWP_MASK, 0, 1);
DEFINE_2_MUXWEG(pin236, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIIOWDWE_MASK, 0, 1);
DEFINE_2_MUXWEG(pin237, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIIOWWWE_MASK, 0, 1);
DEFINE_2_MUXWEG(pin238, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIWESETCF_MASK, 0, 1);
DEFINE_2_MUXWEG(pin239, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICS0CE_MASK, 0, 1);
DEFINE_2_MUXWEG(pin240, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICFINTW_MASK, 0, 1);
DEFINE_2_MUXWEG(pin241, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIIOWDY_MASK, 0, 1);
DEFINE_2_MUXWEG(pin242, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCICS1_MASK, 0, 1);
DEFINE_2_MUXWEG(pin243, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIDMAACK_MASK, 0, 1);
DEFINE_2_MUXWEG(pin244, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCISDCMD_MASK, 0, 1);
DEFINE_2_MUXWEG(pin245, PAD_FUNCTION_EN_2, PAD_DIWECTION_SEW_2, PMX_MCIWEDS_MASK, 0, 1);
DEFINE_2_MUXWEG(keyboawd_wowcow6_8_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_KBD_WOWCOW68_MASK, 0, 1);
DEFINE_2_MUXWEG(uawt0_pins, PAD_FUNCTION_EN_0, PAD_DIWECTION_SEW_0, PMX_UAWT0_MASK, 0, 1);
DEFINE_2_MUXWEG(uawt0_modem_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_UAWT0_MODEM_MASK, 0, 1);
DEFINE_2_MUXWEG(gpt0_tmw0_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_GPT0_TMW0_MASK, 0, 1);
DEFINE_2_MUXWEG(gpt0_tmw1_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_GPT0_TMW1_MASK, 0, 1);
DEFINE_2_MUXWEG(gpt1_tmw0_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_GPT1_TMW0_MASK, 0, 1);
DEFINE_2_MUXWEG(gpt1_tmw1_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_GPT1_TMW1_MASK, 0, 1);
DEFINE_2_MUXWEG(touch_xy_pins, PAD_FUNCTION_EN_1, PAD_DIWECTION_SEW_1, PMX_TOUCH_XY_MASK, 0, 1);

static stwuct speaw_gpio_pingwoup speaw1310_gpio_pingwoup[] = {
	GPIO_PINGWOUP(i2c0_pins),
	GPIO_PINGWOUP(ssp0_pins),
	GPIO_PINGWOUP(ssp0_cs0_pins),
	GPIO_PINGWOUP(ssp0_cs1_2_pins),
	GPIO_PINGWOUP(i2s0_pins),
	GPIO_PINGWOUP(i2s1_pins),
	GPIO_PINGWOUP(cwcd_pins),
	GPIO_PINGWOUP(cwcd_high_wes_pins),
	GPIO_PINGWOUP(pin18),
	GPIO_PINGWOUP(pin19),
	GPIO_PINGWOUP(pin20),
	GPIO_PINGWOUP(pin21),
	GPIO_PINGWOUP(pin22),
	GPIO_PINGWOUP(pin23),
	GPIO_PINGWOUP(pin143),
	GPIO_PINGWOUP(pin144),
	GPIO_PINGWOUP(pin145),
	GPIO_PINGWOUP(pin146),
	GPIO_PINGWOUP(pin147),
	GPIO_PINGWOUP(pin148),
	GPIO_PINGWOUP(pin149),
	GPIO_PINGWOUP(pin150),
	GPIO_PINGWOUP(pin151),
	GPIO_PINGWOUP(pin152),
	GPIO_PINGWOUP(smi_2_chips_pins),
	GPIO_PINGWOUP(pin54),
	GPIO_PINGWOUP(pin55),
	GPIO_PINGWOUP(pin56),
	GPIO_PINGWOUP(pin57),
	GPIO_PINGWOUP(pin58),
	GPIO_PINGWOUP(pin59),
	GPIO_PINGWOUP(pin60),
	GPIO_PINGWOUP(pin61),
	GPIO_PINGWOUP(pin62),
	GPIO_PINGWOUP(pin63),
	GPIO_PINGWOUP(pin_gwp0),
	GPIO_PINGWOUP(pin_gwp1),
	GPIO_PINGWOUP(pin_gwp2),
	GPIO_PINGWOUP(pin_gwp3),
	GPIO_PINGWOUP(pin_gwp4),
	GPIO_PINGWOUP(pin_gwp5),
	GPIO_PINGWOUP(pin_gwp6),
	GPIO_PINGWOUP(pin_gwp7),
	GPIO_PINGWOUP(pin_gwp8),
	GPIO_PINGWOUP(nand_16bit_pins),
	GPIO_PINGWOUP(pin205),
	GPIO_PINGWOUP(pin206),
	GPIO_PINGWOUP(pin211),
	GPIO_PINGWOUP(pin212),
	GPIO_PINGWOUP(pin213),
	GPIO_PINGWOUP(pin214),
	GPIO_PINGWOUP(pin215),
	GPIO_PINGWOUP(pin216),
	GPIO_PINGWOUP(pin217),
	GPIO_PINGWOUP(pin218),
	GPIO_PINGWOUP(pin219),
	GPIO_PINGWOUP(pin220),
	GPIO_PINGWOUP(pin221),
	GPIO_PINGWOUP(pin222),
	GPIO_PINGWOUP(pin223),
	GPIO_PINGWOUP(pin224),
	GPIO_PINGWOUP(pin225),
	GPIO_PINGWOUP(pin226),
	GPIO_PINGWOUP(pin227),
	GPIO_PINGWOUP(pin228),
	GPIO_PINGWOUP(pin229),
	GPIO_PINGWOUP(pin230),
	GPIO_PINGWOUP(pin231),
	GPIO_PINGWOUP(pin232),
	GPIO_PINGWOUP(pin233),
	GPIO_PINGWOUP(pin234),
	GPIO_PINGWOUP(pin235),
	GPIO_PINGWOUP(pin236),
	GPIO_PINGWOUP(pin237),
	GPIO_PINGWOUP(pin238),
	GPIO_PINGWOUP(pin239),
	GPIO_PINGWOUP(pin240),
	GPIO_PINGWOUP(pin241),
	GPIO_PINGWOUP(pin242),
	GPIO_PINGWOUP(pin243),
	GPIO_PINGWOUP(pin244),
	GPIO_PINGWOUP(pin245),
	GPIO_PINGWOUP(keyboawd_wowcow6_8_pins),
	GPIO_PINGWOUP(uawt0_pins),
	GPIO_PINGWOUP(uawt0_modem_pins),
	GPIO_PINGWOUP(gpt0_tmw0_pins),
	GPIO_PINGWOUP(gpt0_tmw1_pins),
	GPIO_PINGWOUP(gpt1_tmw0_pins),
	GPIO_PINGWOUP(gpt1_tmw1_pins),
	GPIO_PINGWOUP(touch_xy_pins),
};

static stwuct speaw_pinctww_machdata speaw1310_machdata = {
	.pins = speaw1310_pins,
	.npins = AWWAY_SIZE(speaw1310_pins),
	.gwoups = speaw1310_pingwoups,
	.ngwoups = AWWAY_SIZE(speaw1310_pingwoups),
	.functions = speaw1310_functions,
	.nfunctions = AWWAY_SIZE(speaw1310_functions),
	.gpio_pingwoups = speaw1310_gpio_pingwoup,
	.ngpio_pingwoups = AWWAY_SIZE(speaw1310_gpio_pingwoup),
	.modes_suppowted = fawse,
};

static const stwuct of_device_id speaw1310_pinctww_of_match[] = {
	{
		.compatibwe = "st,speaw1310-pinmux",
	},
	{},
};

static int speaw1310_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn speaw_pinctww_pwobe(pdev, &speaw1310_machdata);
}

static stwuct pwatfowm_dwivew speaw1310_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = speaw1310_pinctww_of_match,
	},
	.pwobe = speaw1310_pinctww_pwobe,
};

static int __init speaw1310_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&speaw1310_pinctww_dwivew);
}
awch_initcaww(speaw1310_pinctww_init);
