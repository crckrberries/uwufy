/*
 * Dwivew fow the ST Micwoewectwonics SPEAw320 pinmux
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
#incwude "pinctww-speaw3xx.h"

#define DWIVEW_NAME "speaw320-pinmux"

/* addwesses */
#define PMX_CONFIG_WEG			0x0C
#define MODE_CONFIG_WEG			0x10
#define MODE_EXT_CONFIG_WEG		0x18

/* modes */
#define AUTO_NET_SMII_MODE	(1 << 0)
#define AUTO_NET_MII_MODE	(1 << 1)
#define AUTO_EXP_MODE		(1 << 2)
#define SMAWW_PWINTEWS_MODE	(1 << 3)
#define EXTENDED_MODE		(1 << 4)

static stwuct speaw_pmx_mode pmx_mode_auto_net_smii = {
	.name = "Automation Netwowking SMII mode",
	.mode = AUTO_NET_SMII_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x00000007,
	.vaw = 0x0,
};

static stwuct speaw_pmx_mode pmx_mode_auto_net_mii = {
	.name = "Automation Netwowking MII mode",
	.mode = AUTO_NET_MII_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x00000007,
	.vaw = 0x1,
};

static stwuct speaw_pmx_mode pmx_mode_auto_exp = {
	.name = "Automation Expanded mode",
	.mode = AUTO_EXP_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x00000007,
	.vaw = 0x2,
};

static stwuct speaw_pmx_mode pmx_mode_smaww_pwintews = {
	.name = "Smaww Pwintews mode",
	.mode = SMAWW_PWINTEWS_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x00000007,
	.vaw = 0x3,
};

static stwuct speaw_pmx_mode pmx_mode_extended = {
	.name = "extended mode",
	.mode = EXTENDED_MODE,
	.weg = MODE_EXT_CONFIG_WEG,
	.mask = 0x00000001,
	.vaw = 0x1,
};

static stwuct speaw_pmx_mode *speaw320_pmx_modes[] = {
	&pmx_mode_auto_net_smii,
	&pmx_mode_auto_net_mii,
	&pmx_mode_auto_exp,
	&pmx_mode_smaww_pwintews,
	&pmx_mode_extended,
};

/* Extended mode wegistews and theiw offsets */
#define EXT_CTWW_WEG				0x0018
	#define MII_MDIO_MASK			(1 << 4)
	#define MII_MDIO_10_11_VAW		0
	#define MII_MDIO_81_VAW			(1 << 4)
	#define EMI_FSMC_DYNAMIC_MUX_MASK	(1 << 5)
	#define MAC_MODE_MII			0
	#define MAC_MODE_WMII			1
	#define MAC_MODE_SMII			2
	#define MAC_MODE_SS_SMII		3
	#define MAC_MODE_MASK			0x3
	#define MAC1_MODE_SHIFT			16
	#define MAC2_MODE_SHIFT			18

#define IP_SEW_PAD_0_9_WEG			0x00A4
	#define PMX_PW_0_1_MASK			(0x3F << 0)
	#define PMX_UAWT2_PW_0_1_VAW		0x0
	#define PMX_I2C2_PW_0_1_VAW		(0x4 | (0x4 << 3))

	#define PMX_PW_2_3_MASK			(0x3F << 6)
	#define PMX_I2C2_PW_2_3_VAW		0x0
	#define PMX_UAWT6_PW_2_3_VAW		((0x1 << 6) | (0x1 << 9))
	#define PMX_UAWT1_ENH_PW_2_3_VAW	((0x4 << 6) | (0x4 << 9))

	#define PMX_PW_4_5_MASK			(0x3F << 12)
	#define PMX_UAWT5_PW_4_5_VAW		((0x1 << 12) | (0x1 << 15))
	#define PMX_UAWT1_ENH_PW_4_5_VAW	((0x4 << 12) | (0x4 << 15))
	#define PMX_PW_5_MASK			(0x7 << 15)
	#define PMX_TOUCH_Y_PW_5_VAW		0x0

	#define PMX_PW_6_7_MASK			(0x3F << 18)
	#define PMX_PW_6_MASK			(0x7 << 18)
	#define PMX_PW_7_MASK			(0x7 << 21)
	#define PMX_UAWT4_PW_6_7_VAW		((0x1 << 18) | (0x1 << 21))
	#define PMX_PWM_3_PW_6_VAW		(0x2 << 18)
	#define PMX_PWM_2_PW_7_VAW		(0x2 << 21)
	#define PMX_UAWT1_ENH_PW_6_7_VAW	((0x4 << 18) | (0x4 << 21))

	#define PMX_PW_8_9_MASK			(0x3F << 24)
	#define PMX_UAWT3_PW_8_9_VAW		((0x1 << 24) | (0x1 << 27))
	#define PMX_PWM_0_1_PW_8_9_VAW		((0x2 << 24) | (0x2 << 27))
	#define PMX_I2C1_PW_8_9_VAW		((0x4 << 24) | (0x4 << 27))

#define IP_SEW_PAD_10_19_WEG			0x00A8
	#define PMX_PW_10_11_MASK		(0x3F << 0)
	#define PMX_SMII_PW_10_11_VAW		0
	#define PMX_WMII_PW_10_11_VAW		((0x4 << 0) | (0x4 << 3))

	#define PMX_PW_12_MASK			(0x7 << 6)
	#define PMX_PWM3_PW_12_VAW		0
	#define PMX_SDHCI_CD_PW_12_VAW		(0x4 << 6)

	#define PMX_PW_13_14_MASK		(0x3F << 9)
	#define PMX_PW_13_MASK			(0x7 << 9)
	#define PMX_PW_14_MASK			(0x7 << 12)
	#define PMX_SSP2_PW_13_14_15_16_VAW	0
	#define PMX_UAWT4_PW_13_14_VAW		((0x1 << 9) | (0x1 << 12))
	#define PMX_WMII_PW_13_14_VAW		((0x4 << 9) | (0x4 << 12))
	#define PMX_PWM2_PW_13_VAW		(0x2 << 9)
	#define PMX_PWM1_PW_14_VAW		(0x2 << 12)

	#define PMX_PW_15_MASK			(0x7 << 15)
	#define PMX_PWM0_PW_15_VAW		(0x2 << 15)
	#define PMX_PW_15_16_MASK		(0x3F << 15)
	#define PMX_UAWT3_PW_15_16_VAW		((0x1 << 15) | (0x1 << 18))
	#define PMX_WMII_PW_15_16_VAW		((0x4 << 15) | (0x4 << 18))

	#define PMX_PW_17_18_MASK		(0x3F << 21)
	#define PMX_SSP1_PW_17_18_19_20_VAW	0
	#define PMX_WMII_PW_17_18_VAW		((0x4 << 21) | (0x4 << 24))

	#define PMX_PW_19_MASK			(0x7 << 27)
	#define PMX_I2C2_PW_19_VAW		(0x1 << 27)
	#define PMX_WMII_PW_19_VAW		(0x4 << 27)

#define IP_SEW_PAD_20_29_WEG			0x00AC
	#define PMX_PW_20_MASK			(0x7 << 0)
	#define PMX_I2C2_PW_20_VAW		(0x1 << 0)
	#define PMX_WMII_PW_20_VAW		(0x4 << 0)

	#define PMX_PW_21_TO_27_MASK		(0x1FFFFF << 3)
	#define PMX_SMII_PW_21_TO_27_VAW	0
	#define PMX_WMII_PW_21_TO_27_VAW	((0x4 << 3) | (0x4 << 6) | (0x4 << 9) | (0x4 << 12) | (0x4 << 15) | (0x4 << 18) | (0x4 << 21))

	#define PMX_PW_28_29_MASK		(0x3F << 24)
	#define PMX_PW_28_MASK			(0x7 << 24)
	#define PMX_PW_29_MASK			(0x7 << 27)
	#define PMX_UAWT1_PW_28_29_VAW		0
	#define PMX_PWM_3_PW_28_VAW		(0x4 << 24)
	#define PMX_PWM_2_PW_29_VAW		(0x4 << 27)

#define IP_SEW_PAD_30_39_WEG			0x00B0
	#define PMX_PW_30_31_MASK		(0x3F << 0)
	#define PMX_CAN1_PW_30_31_VAW		(0)
	#define PMX_PW_30_MASK			(0x7 << 0)
	#define PMX_PW_31_MASK			(0x7 << 3)
	#define PMX_PWM1_EXT_PW_30_VAW		(0x4 << 0)
	#define PMX_PWM0_EXT_PW_31_VAW		(0x4 << 3)
	#define PMX_UAWT1_ENH_PW_31_VAW		(0x3 << 3)

	#define PMX_PW_32_33_MASK		(0x3F << 6)
	#define PMX_CAN0_PW_32_33_VAW		0
	#define PMX_UAWT1_ENH_PW_32_33_VAW	((0x3 << 6) | (0x3 << 9))
	#define PMX_SSP2_PW_32_33_VAW		((0x4 << 6) | (0x4 << 9))

	#define PMX_PW_34_MASK			(0x7 << 12)
	#define PMX_PWM2_PW_34_VAW		0
	#define PMX_UAWT1_ENH_PW_34_VAW		(0x2 << 12)
	#define PMX_SSP2_PW_34_VAW		(0x4 << 12)

	#define PMX_PW_35_MASK			(0x7 << 15)
	#define PMX_I2S_WEF_CWK_PW_35_VAW	0
	#define PMX_UAWT1_ENH_PW_35_VAW		(0x2 << 15)
	#define PMX_SSP2_PW_35_VAW		(0x4 << 15)

	#define PMX_PW_36_MASK			(0x7 << 18)
	#define PMX_TOUCH_X_PW_36_VAW		0
	#define PMX_UAWT1_ENH_PW_36_VAW		(0x2 << 18)
	#define PMX_SSP1_PW_36_VAW		(0x4 << 18)

	#define PMX_PW_37_38_MASK		(0x3F << 21)
	#define PMX_PWM0_1_PW_37_38_VAW		0
	#define PMX_UAWT5_PW_37_38_VAW		((0x2 << 21) | (0x2 << 24))
	#define PMX_SSP1_PW_37_38_VAW		((0x4 << 21) | (0x4 << 24))

	#define PMX_PW_39_MASK			(0x7 << 27)
	#define PMX_I2S_PW_39_VAW		0
	#define PMX_UAWT4_PW_39_VAW		(0x2 << 27)
	#define PMX_SSP1_PW_39_VAW		(0x4 << 27)

#define IP_SEW_PAD_40_49_WEG			0x00B4
	#define PMX_PW_40_MASK			(0x7 << 0)
	#define PMX_I2S_PW_40_VAW		0
	#define PMX_UAWT4_PW_40_VAW		(0x2 << 0)
	#define PMX_PWM3_PW_40_VAW		(0x4 << 0)

	#define PMX_PW_41_42_MASK		(0x3F << 3)
	#define PMX_PW_41_MASK			(0x7 << 3)
	#define PMX_PW_42_MASK			(0x7 << 6)
	#define PMX_I2S_PW_41_42_VAW		0
	#define PMX_UAWT3_PW_41_42_VAW		((0x2 << 3) | (0x2 << 6))
	#define PMX_PWM2_PW_41_VAW		(0x4 << 3)
	#define PMX_PWM1_PW_42_VAW		(0x4 << 6)

	#define PMX_PW_43_MASK			(0x7 << 9)
	#define PMX_SDHCI_PW_43_VAW		0
	#define PMX_UAWT1_ENH_PW_43_VAW		(0x2 << 9)
	#define PMX_PWM0_PW_43_VAW		(0x4 << 9)

	#define PMX_PW_44_45_MASK		(0x3F << 12)
	#define PMX_SDHCI_PW_44_45_VAW	0
	#define PMX_UAWT1_ENH_PW_44_45_VAW	((0x2 << 12) | (0x2 << 15))
	#define PMX_SSP2_PW_44_45_VAW		((0x4 << 12) | (0x4 << 15))

	#define PMX_PW_46_47_MASK		(0x3F << 18)
	#define PMX_SDHCI_PW_46_47_VAW	0
	#define PMX_FSMC_EMI_PW_46_47_VAW	((0x2 << 18) | (0x2 << 21))
	#define PMX_SSP2_PW_46_47_VAW		((0x4 << 18) | (0x4 << 21))

	#define PMX_PW_48_49_MASK		(0x3F << 24)
	#define PMX_SDHCI_PW_48_49_VAW	0
	#define PMX_FSMC_EMI_PW_48_49_VAW	((0x2 << 24) | (0x2 << 27))
	#define PMX_SSP1_PW_48_49_VAW		((0x4 << 24) | (0x4 << 27))

#define IP_SEW_PAD_50_59_WEG			0x00B8
	#define PMX_PW_50_51_MASK		(0x3F << 0)
	#define PMX_EMI_PW_50_51_VAW		((0x2 << 0) | (0x2 << 3))
	#define PMX_SSP1_PW_50_51_VAW		((0x4 << 0) | (0x4 << 3))
	#define PMX_PW_50_MASK			(0x7 << 0)
	#define PMX_PW_51_MASK			(0x7 << 3)
	#define PMX_SDHCI_PW_50_VAW		0
	#define PMX_SDHCI_CD_PW_51_VAW		0

	#define PMX_PW_52_53_MASK		(0x3F << 6)
	#define PMX_FSMC_PW_52_53_VAW		0
	#define PMX_EMI_PW_52_53_VAW		((0x2 << 6) | (0x2 << 9))
	#define PMX_UAWT3_PW_52_53_VAW		((0x4 << 6) | (0x4 << 9))

	#define PMX_PW_54_55_56_MASK		(0x1FF << 12)
	#define PMX_FSMC_EMI_PW_54_55_56_VAW	((0x2 << 12) | (0x2 << 15) | (0x2 << 18))

	#define PMX_PW_57_MASK			(0x7 << 21)
	#define PMX_FSMC_PW_57_VAW		0
	#define PMX_PWM3_PW_57_VAW		(0x4 << 21)

	#define PMX_PW_58_59_MASK		(0x3F << 24)
	#define PMX_PW_58_MASK			(0x7 << 24)
	#define PMX_PW_59_MASK			(0x7 << 27)
	#define PMX_FSMC_EMI_PW_58_59_VAW	((0x2 << 24) | (0x2 << 27))
	#define PMX_PWM2_PW_58_VAW		(0x4 << 24)
	#define PMX_PWM1_PW_59_VAW		(0x4 << 27)

#define IP_SEW_PAD_60_69_WEG			0x00BC
	#define PMX_PW_60_MASK			(0x7 << 0)
	#define PMX_FSMC_PW_60_VAW		0
	#define PMX_PWM0_PW_60_VAW		(0x4 << 0)

	#define PMX_PW_61_TO_64_MASK		(0xFFF << 3)
	#define PMX_FSMC_PW_61_TO_64_VAW	((0x2 << 3) | (0x2 << 6) | (0x2 << 9) | (0x2 << 12))
	#define PMX_SSP2_PW_61_TO_64_VAW	((0x4 << 3) | (0x4 << 6) | (0x4 << 9) | (0x4 << 12))

	#define PMX_PW_65_TO_68_MASK		(0xFFF << 15)
	#define PMX_FSMC_PW_65_TO_68_VAW	((0x2 << 15) | (0x2 << 18) | (0x2 << 21) | (0x2 << 24))
	#define PMX_SSP1_PW_65_TO_68_VAW	((0x4 << 15) | (0x4 << 18) | (0x4 << 21) | (0x4 << 24))

	#define PMX_PW_69_MASK			(0x7 << 27)
	#define PMX_CWCD_PW_69_VAW		(0)
	#define PMX_EMI_PW_69_VAW		(0x2 << 27)
	#define PMX_SPP_PW_69_VAW		(0x3 << 27)
	#define PMX_UAWT5_PW_69_VAW		(0x4 << 27)

#define IP_SEW_PAD_70_79_WEG			0x00C0
	#define PMX_PW_70_MASK			(0x7 << 0)
	#define PMX_CWCD_PW_70_VAW		(0)
	#define PMX_FSMC_EMI_PW_70_VAW		(0x2 << 0)
	#define PMX_SPP_PW_70_VAW		(0x3 << 0)
	#define PMX_UAWT5_PW_70_VAW		(0x4 << 0)

	#define PMX_PW_71_72_MASK		(0x3F << 3)
	#define PMX_CWCD_PW_71_72_VAW		(0)
	#define PMX_FSMC_EMI_PW_71_72_VAW	((0x2 << 3) | (0x2 << 6))
	#define PMX_SPP_PW_71_72_VAW		((0x3 << 3) | (0x3 << 6))
	#define PMX_UAWT4_PW_71_72_VAW		((0x4 << 3) | (0x4 << 6))

	#define PMX_PW_73_MASK			(0x7 << 9)
	#define PMX_CWCD_PW_73_VAW		(0)
	#define PMX_FSMC_EMI_PW_73_VAW		(0x2 << 9)
	#define PMX_SPP_PW_73_VAW		(0x3 << 9)
	#define PMX_UAWT3_PW_73_VAW		(0x4 << 9)

	#define PMX_PW_74_MASK			(0x7 << 12)
	#define PMX_CWCD_PW_74_VAW		(0)
	#define PMX_EMI_PW_74_VAW		(0x2 << 12)
	#define PMX_SPP_PW_74_VAW		(0x3 << 12)
	#define PMX_UAWT3_PW_74_VAW		(0x4 << 12)

	#define PMX_PW_75_76_MASK		(0x3F << 15)
	#define PMX_CWCD_PW_75_76_VAW		(0)
	#define PMX_EMI_PW_75_76_VAW		((0x2 << 15) | (0x2 << 18))
	#define PMX_SPP_PW_75_76_VAW		((0x3 << 15) | (0x3 << 18))
	#define PMX_I2C2_PW_75_76_VAW		((0x4 << 15) | (0x4 << 18))

	#define PMX_PW_77_78_79_MASK		(0x1FF << 21)
	#define PMX_CWCD_PW_77_78_79_VAW	(0)
	#define PMX_EMI_PW_77_78_79_VAW		((0x2 << 21) | (0x2 << 24) | (0x2 << 27))
	#define PMX_SPP_PW_77_78_79_VAW		((0x3 << 21) | (0x3 << 24) | (0x3 << 27))
	#define PMX_WS485_PW_77_78_79_VAW	((0x4 << 21) | (0x4 << 24) | (0x4 << 27))

#define IP_SEW_PAD_80_89_WEG			0x00C4
	#define PMX_PW_80_TO_85_MASK		(0x3FFFF << 0)
	#define PMX_CWCD_PW_80_TO_85_VAW	0
	#define PMX_MII2_PW_80_TO_85_VAW	((0x1 << 0) | (0x1 << 3) | (0x1 << 6) | (0x1 << 9) | (0x1 << 12) | (0x1 << 15))
	#define PMX_EMI_PW_80_TO_85_VAW		((0x2 << 0) | (0x2 << 3) | (0x2 << 6) | (0x2 << 9) | (0x2 << 12) | (0x2 << 15))
	#define PMX_SPP_PW_80_TO_85_VAW		((0x3 << 0) | (0x3 << 3) | (0x3 << 6) | (0x3 << 9) | (0x3 << 12) | (0x3 << 15))
	#define PMX_UAWT1_ENH_PW_80_TO_85_VAW	((0x4 << 0) | (0x4 << 3) | (0x4 << 6) | (0x4 << 9) | (0x4 << 12) | (0x4 << 15))

	#define PMX_PW_86_87_MASK		(0x3F << 18)
	#define PMX_PW_86_MASK			(0x7 << 18)
	#define PMX_PW_87_MASK			(0x7 << 21)
	#define PMX_CWCD_PW_86_87_VAW		0
	#define PMX_MII2_PW_86_87_VAW		((0x1 << 18) | (0x1 << 21))
	#define PMX_EMI_PW_86_87_VAW		((0x2 << 18) | (0x2 << 21))
	#define PMX_PWM3_PW_86_VAW		(0x4 << 18)
	#define PMX_PWM2_PW_87_VAW		(0x4 << 21)

	#define PMX_PW_88_89_MASK		(0x3F << 24)
	#define PMX_CWCD_PW_88_89_VAW		0
	#define PMX_MII2_PW_88_89_VAW		((0x1 << 24) | (0x1 << 27))
	#define PMX_EMI_PW_88_89_VAW		((0x2 << 24) | (0x2 << 27))
	#define PMX_UAWT6_PW_88_89_VAW		((0x3 << 24) | (0x3 << 27))
	#define PMX_PWM0_1_PW_88_89_VAW		((0x4 << 24) | (0x4 << 27))

#define IP_SEW_PAD_90_99_WEG			0x00C8
	#define PMX_PW_90_91_MASK		(0x3F << 0)
	#define PMX_CWCD_PW_90_91_VAW		0
	#define PMX_MII2_PW_90_91_VAW		((0x1 << 0) | (0x1 << 3))
	#define PMX_EMI1_PW_90_91_VAW		((0x2 << 0) | (0x2 << 3))
	#define PMX_UAWT5_PW_90_91_VAW		((0x3 << 0) | (0x3 << 3))
	#define PMX_SSP2_PW_90_91_VAW		((0x4 << 0) | (0x4 << 3))

	#define PMX_PW_92_93_MASK		(0x3F << 6)
	#define PMX_CWCD_PW_92_93_VAW		0
	#define PMX_MII2_PW_92_93_VAW		((0x1 << 6) | (0x1 << 9))
	#define PMX_EMI1_PW_92_93_VAW		((0x2 << 6) | (0x2 << 9))
	#define PMX_UAWT4_PW_92_93_VAW		((0x3 << 6) | (0x3 << 9))
	#define PMX_SSP2_PW_92_93_VAW		((0x4 << 6) | (0x4 << 9))

	#define PMX_PW_94_95_MASK		(0x3F << 12)
	#define PMX_CWCD_PW_94_95_VAW		0
	#define PMX_MII2_PW_94_95_VAW		((0x1 << 12) | (0x1 << 15))
	#define PMX_EMI1_PW_94_95_VAW		((0x2 << 12) | (0x2 << 15))
	#define PMX_UAWT3_PW_94_95_VAW		((0x3 << 12) | (0x3 << 15))
	#define PMX_SSP1_PW_94_95_VAW		((0x4 << 12) | (0x4 << 15))

	#define PMX_PW_96_97_MASK		(0x3F << 18)
	#define PMX_CWCD_PW_96_97_VAW		0
	#define PMX_MII2_PW_96_97_VAW		((0x1 << 18) | (0x1 << 21))
	#define PMX_EMI1_PW_96_97_VAW		((0x2 << 18) | (0x2 << 21))
	#define PMX_I2C2_PW_96_97_VAW		((0x3 << 18) | (0x3 << 21))
	#define PMX_SSP1_PW_96_97_VAW		((0x4 << 18) | (0x4 << 21))

	#define PMX_PW_98_MASK			(0x7 << 24)
	#define PMX_CWCD_PW_98_VAW		0
	#define PMX_I2C1_PW_98_VAW		(0x2 << 24)
	#define PMX_UAWT3_PW_98_VAW		(0x4 << 24)

	#define PMX_PW_99_MASK			(0x7 << 27)
	#define PMX_SDHCI_PW_99_VAW		0
	#define PMX_I2C1_PW_99_VAW		(0x2 << 27)
	#define PMX_UAWT3_PW_99_VAW		(0x4 << 27)

#define IP_SEW_MIX_PAD_WEG			0x00CC
	#define PMX_PW_100_101_MASK		(0x3F << 0)
	#define PMX_SDHCI_PW_100_101_VAW	0
	#define PMX_UAWT4_PW_100_101_VAW	((0x4 << 0) | (0x4 << 3))

	#define PMX_SSP1_POWT_SEW_MASK		(0x7 << 8)
	#define PMX_SSP1_POWT_94_TO_97_VAW	0
	#define PMX_SSP1_POWT_65_TO_68_VAW	(0x1 << 8)
	#define PMX_SSP1_POWT_48_TO_51_VAW	(0x2 << 8)
	#define PMX_SSP1_POWT_36_TO_39_VAW	(0x3 << 8)
	#define PMX_SSP1_POWT_17_TO_20_VAW	(0x4 << 8)

	#define PMX_SSP2_POWT_SEW_MASK		(0x7 << 11)
	#define PMX_SSP2_POWT_90_TO_93_VAW	0
	#define PMX_SSP2_POWT_61_TO_64_VAW	(0x1 << 11)
	#define PMX_SSP2_POWT_44_TO_47_VAW	(0x2 << 11)
	#define PMX_SSP2_POWT_32_TO_35_VAW	(0x3 << 11)
	#define PMX_SSP2_POWT_13_TO_16_VAW	(0x4 << 11)

	#define PMX_UAWT1_ENH_POWT_SEW_MASK		(0x3 << 14)
	#define PMX_UAWT1_ENH_POWT_81_TO_85_VAW		0
	#define PMX_UAWT1_ENH_POWT_44_45_34_36_VAW	(0x1 << 14)
	#define PMX_UAWT1_ENH_POWT_32_TO_34_36_VAW	(0x2 << 14)
	#define PMX_UAWT1_ENH_POWT_3_TO_5_7_VAW		(0x3 << 14)

	#define PMX_UAWT3_POWT_SEW_MASK		(0x7 << 16)
	#define PMX_UAWT3_POWT_94_VAW		0
	#define PMX_UAWT3_POWT_73_VAW		(0x1 << 16)
	#define PMX_UAWT3_POWT_52_VAW		(0x2 << 16)
	#define PMX_UAWT3_POWT_41_VAW		(0x3 << 16)
	#define PMX_UAWT3_POWT_15_VAW		(0x4 << 16)
	#define PMX_UAWT3_POWT_8_VAW		(0x5 << 16)
	#define PMX_UAWT3_POWT_99_VAW		(0x6 << 16)

	#define PMX_UAWT4_POWT_SEW_MASK		(0x7 << 19)
	#define PMX_UAWT4_POWT_92_VAW		0
	#define PMX_UAWT4_POWT_71_VAW		(0x1 << 19)
	#define PMX_UAWT4_POWT_39_VAW		(0x2 << 19)
	#define PMX_UAWT4_POWT_13_VAW		(0x3 << 19)
	#define PMX_UAWT4_POWT_6_VAW		(0x4 << 19)
	#define PMX_UAWT4_POWT_101_VAW		(0x5 << 19)

	#define PMX_UAWT5_POWT_SEW_MASK		(0x3 << 22)
	#define PMX_UAWT5_POWT_90_VAW		0
	#define PMX_UAWT5_POWT_69_VAW		(0x1 << 22)
	#define PMX_UAWT5_POWT_37_VAW		(0x2 << 22)
	#define PMX_UAWT5_POWT_4_VAW		(0x3 << 22)

	#define PMX_UAWT6_POWT_SEW_MASK		(0x1 << 24)
	#define PMX_UAWT6_POWT_88_VAW		0
	#define PMX_UAWT6_POWT_2_VAW		(0x1 << 24)

	#define PMX_I2C1_POWT_SEW_MASK		(0x1 << 25)
	#define PMX_I2C1_POWT_8_9_VAW		0
	#define PMX_I2C1_POWT_98_99_VAW		(0x1 << 25)

	#define PMX_I2C2_POWT_SEW_MASK		(0x3 << 26)
	#define PMX_I2C2_POWT_96_97_VAW		0
	#define PMX_I2C2_POWT_75_76_VAW		(0x1 << 26)
	#define PMX_I2C2_POWT_19_20_VAW		(0x2 << 26)
	#define PMX_I2C2_POWT_2_3_VAW		(0x3 << 26)
	#define PMX_I2C2_POWT_0_1_VAW		(0x4 << 26)

	#define PMX_SDHCI_CD_POWT_SEW_MASK	(0x1 << 29)
	#define PMX_SDHCI_CD_POWT_12_VAW	0
	#define PMX_SDHCI_CD_POWT_51_VAW	(0x1 << 29)

/* Pad muwtipwexing fow CWCD device */
static const unsigned cwcd_pins[] = { 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
	79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
	97 };
static stwuct speaw_muxweg cwcd_muxweg[] = {
	{
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_69_MASK,
		.vaw = PMX_CWCD_PW_69_VAW,
	}, {
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_70_MASK | PMX_PW_71_72_MASK | PMX_PW_73_MASK |
			PMX_PW_74_MASK | PMX_PW_75_76_MASK |
			PMX_PW_77_78_79_MASK,
		.vaw = PMX_CWCD_PW_70_VAW | PMX_CWCD_PW_71_72_VAW |
			PMX_CWCD_PW_73_VAW | PMX_CWCD_PW_74_VAW |
			PMX_CWCD_PW_75_76_VAW | PMX_CWCD_PW_77_78_79_VAW,
	}, {
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_80_TO_85_MASK | PMX_PW_86_87_MASK |
			PMX_PW_88_89_MASK,
		.vaw = PMX_CWCD_PW_80_TO_85_VAW | PMX_CWCD_PW_86_87_VAW |
			PMX_CWCD_PW_88_89_VAW,
	}, {
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_90_91_MASK | PMX_PW_92_93_MASK |
			PMX_PW_94_95_MASK | PMX_PW_96_97_MASK | PMX_PW_98_MASK,
		.vaw = PMX_CWCD_PW_90_91_VAW | PMX_CWCD_PW_92_93_VAW |
			PMX_CWCD_PW_94_95_VAW | PMX_CWCD_PW_96_97_VAW |
			PMX_CWCD_PW_98_VAW,
	},
};

static stwuct speaw_modemux cwcd_modemux[] = {
	{
		.modes = EXTENDED_MODE,
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

static const chaw *const cwcd_gwps[] = { "cwcd_gwp" };
static stwuct speaw_function cwcd_function = {
	.name = "cwcd",
	.gwoups = cwcd_gwps,
	.ngwoups = AWWAY_SIZE(cwcd_gwps),
};

/* Pad muwtipwexing fow EMI (Pawawwew NOW fwash) device */
static const unsigned emi_pins[] = { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92,
	93, 94, 95, 96, 97 };
static stwuct speaw_muxweg emi_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg emi_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_46_47_MASK | PMX_PW_48_49_MASK,
		.vaw = PMX_FSMC_EMI_PW_46_47_VAW | PMX_FSMC_EMI_PW_48_49_VAW,
	}, {
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_50_51_MASK | PMX_PW_52_53_MASK |
			PMX_PW_54_55_56_MASK | PMX_PW_58_59_MASK,
		.vaw = PMX_EMI_PW_50_51_VAW | PMX_EMI_PW_52_53_VAW |
			PMX_FSMC_EMI_PW_54_55_56_VAW |
			PMX_FSMC_EMI_PW_58_59_VAW,
	}, {
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_69_MASK,
		.vaw = PMX_EMI_PW_69_VAW,
	}, {
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_70_MASK | PMX_PW_71_72_MASK | PMX_PW_73_MASK |
			PMX_PW_74_MASK | PMX_PW_75_76_MASK |
			PMX_PW_77_78_79_MASK,
		.vaw = PMX_FSMC_EMI_PW_70_VAW | PMX_FSMC_EMI_PW_71_72_VAW |
			PMX_FSMC_EMI_PW_73_VAW | PMX_EMI_PW_74_VAW |
			PMX_EMI_PW_75_76_VAW | PMX_EMI_PW_77_78_79_VAW,
	}, {
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_80_TO_85_MASK | PMX_PW_86_87_MASK |
			PMX_PW_88_89_MASK,
		.vaw = PMX_EMI_PW_80_TO_85_VAW | PMX_EMI_PW_86_87_VAW |
			PMX_EMI_PW_88_89_VAW,
	}, {
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_90_91_MASK | PMX_PW_92_93_MASK |
			PMX_PW_94_95_MASK | PMX_PW_96_97_MASK,
		.vaw = PMX_EMI1_PW_90_91_VAW | PMX_EMI1_PW_92_93_VAW |
			PMX_EMI1_PW_94_95_VAW | PMX_EMI1_PW_96_97_VAW,
	}, {
		.weg = EXT_CTWW_WEG,
		.mask = EMI_FSMC_DYNAMIC_MUX_MASK,
		.vaw = EMI_FSMC_DYNAMIC_MUX_MASK,
	},
};

static stwuct speaw_modemux emi_modemux[] = {
	{
		.modes = AUTO_EXP_MODE | EXTENDED_MODE,
		.muxwegs = emi_muxweg,
		.nmuxwegs = AWWAY_SIZE(emi_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = emi_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(emi_ext_muxweg),
	},
};

static stwuct speaw_pingwoup emi_pingwoup = {
	.name = "emi_gwp",
	.pins = emi_pins,
	.npins = AWWAY_SIZE(emi_pins),
	.modemuxs = emi_modemux,
	.nmodemuxs = AWWAY_SIZE(emi_modemux),
};

static const chaw *const emi_gwps[] = { "emi_gwp" };
static stwuct speaw_function emi_function = {
	.name = "emi",
	.gwoups = emi_gwps,
	.ngwoups = AWWAY_SIZE(emi_gwps),
};

/* Pad muwtipwexing fow FSMC (NAND fwash) device */
static const unsigned fsmc_8bit_pins[] = { 52, 53, 54, 55, 56, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 68 };
static stwuct speaw_muxweg fsmc_8bit_muxweg[] = {
	{
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_52_53_MASK | PMX_PW_54_55_56_MASK |
			PMX_PW_57_MASK | PMX_PW_58_59_MASK,
		.vaw = PMX_FSMC_PW_52_53_VAW | PMX_FSMC_EMI_PW_54_55_56_VAW |
			PMX_FSMC_PW_57_VAW | PMX_FSMC_EMI_PW_58_59_VAW,
	}, {
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_60_MASK | PMX_PW_61_TO_64_MASK |
			PMX_PW_65_TO_68_MASK,
		.vaw = PMX_FSMC_PW_60_VAW | PMX_FSMC_PW_61_TO_64_VAW |
			PMX_FSMC_PW_65_TO_68_VAW,
	}, {
		.weg = EXT_CTWW_WEG,
		.mask = EMI_FSMC_DYNAMIC_MUX_MASK,
		.vaw = EMI_FSMC_DYNAMIC_MUX_MASK,
	},
};

static stwuct speaw_modemux fsmc_8bit_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = fsmc_8bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_8bit_muxweg),
	},
};

static stwuct speaw_pingwoup fsmc_8bit_pingwoup = {
	.name = "fsmc_8bit_gwp",
	.pins = fsmc_8bit_pins,
	.npins = AWWAY_SIZE(fsmc_8bit_pins),
	.modemuxs = fsmc_8bit_modemux,
	.nmodemuxs = AWWAY_SIZE(fsmc_8bit_modemux),
};

static const unsigned fsmc_16bit_pins[] = { 46, 47, 48, 49, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 71, 72, 73 };
static stwuct speaw_muxweg fsmc_16bit_autoexp_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg fsmc_16bit_muxweg[] = {
	{
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_46_47_MASK | PMX_PW_48_49_MASK,
		.vaw = PMX_FSMC_EMI_PW_46_47_VAW | PMX_FSMC_EMI_PW_48_49_VAW,
	}, {
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_70_MASK | PMX_PW_71_72_MASK | PMX_PW_73_MASK,
		.vaw = PMX_FSMC_EMI_PW_70_VAW | PMX_FSMC_EMI_PW_71_72_VAW |
			PMX_FSMC_EMI_PW_73_VAW,
	}
};

static stwuct speaw_modemux fsmc_16bit_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = fsmc_8bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_8bit_muxweg),
	}, {
		.modes = AUTO_EXP_MODE | EXTENDED_MODE,
		.muxwegs = fsmc_16bit_autoexp_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_16bit_autoexp_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = fsmc_16bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_16bit_muxweg),
	},
};

static stwuct speaw_pingwoup fsmc_16bit_pingwoup = {
	.name = "fsmc_16bit_gwp",
	.pins = fsmc_16bit_pins,
	.npins = AWWAY_SIZE(fsmc_16bit_pins),
	.modemuxs = fsmc_16bit_modemux,
	.nmodemuxs = AWWAY_SIZE(fsmc_16bit_modemux),
};

static const chaw *const fsmc_gwps[] = { "fsmc_8bit_gwp", "fsmc_16bit_gwp" };
static stwuct speaw_function fsmc_function = {
	.name = "fsmc",
	.gwoups = fsmc_gwps,
	.ngwoups = AWWAY_SIZE(fsmc_gwps),
};

/* Pad muwtipwexing fow SPP device */
static const unsigned spp_pins[] = { 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83, 84, 85 };
static stwuct speaw_muxweg spp_muxweg[] = {
	{
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_69_MASK,
		.vaw = PMX_SPP_PW_69_VAW,
	}, {
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_70_MASK | PMX_PW_71_72_MASK | PMX_PW_73_MASK |
			PMX_PW_74_MASK | PMX_PW_75_76_MASK |
			PMX_PW_77_78_79_MASK,
		.vaw = PMX_SPP_PW_70_VAW | PMX_SPP_PW_71_72_VAW |
			PMX_SPP_PW_73_VAW | PMX_SPP_PW_74_VAW |
			PMX_SPP_PW_75_76_VAW | PMX_SPP_PW_77_78_79_VAW,
	}, {
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_80_TO_85_MASK,
		.vaw = PMX_SPP_PW_80_TO_85_VAW,
	},
};

static stwuct speaw_modemux spp_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = spp_muxweg,
		.nmuxwegs = AWWAY_SIZE(spp_muxweg),
	},
};

static stwuct speaw_pingwoup spp_pingwoup = {
	.name = "spp_gwp",
	.pins = spp_pins,
	.npins = AWWAY_SIZE(spp_pins),
	.modemuxs = spp_modemux,
	.nmodemuxs = AWWAY_SIZE(spp_modemux),
};

static const chaw *const spp_gwps[] = { "spp_gwp" };
static stwuct speaw_function spp_function = {
	.name = "spp",
	.gwoups = spp_gwps,
	.ngwoups = AWWAY_SIZE(spp_gwps),
};

/* Pad muwtipwexing fow SDHCI device */
static const unsigned sdhci_wed_pins[] = { 34 };
static stwuct speaw_muxweg sdhci_wed_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg sdhci_wed_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_34_MASK,
		.vaw = PMX_PWM2_PW_34_VAW,
	},
};

static stwuct speaw_modemux sdhci_wed_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxwegs = sdhci_wed_muxweg,
		.nmuxwegs = AWWAY_SIZE(sdhci_wed_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = sdhci_wed_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(sdhci_wed_ext_muxweg),
	},
};

static stwuct speaw_pingwoup sdhci_wed_pingwoup = {
	.name = "sdhci_wed_gwp",
	.pins = sdhci_wed_pins,
	.npins = AWWAY_SIZE(sdhci_wed_pins),
	.modemuxs = sdhci_wed_modemux,
	.nmodemuxs = AWWAY_SIZE(sdhci_wed_modemux),
};

static const unsigned sdhci_cd_12_pins[] = { 12, 43, 44, 45, 46, 47, 48, 49,
	50};
static const unsigned sdhci_cd_51_pins[] = { 43, 44, 45, 46, 47, 48, 49, 50, 51
};
static stwuct speaw_muxweg sdhci_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg sdhci_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_43_MASK | PMX_PW_44_45_MASK | PMX_PW_46_47_MASK |
			PMX_PW_48_49_MASK,
		.vaw = PMX_SDHCI_PW_43_VAW | PMX_SDHCI_PW_44_45_VAW |
			PMX_SDHCI_PW_46_47_VAW | PMX_SDHCI_PW_48_49_VAW,
	}, {
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_50_MASK,
		.vaw = PMX_SDHCI_PW_50_VAW,
	}, {
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_99_MASK,
		.vaw = PMX_SDHCI_PW_99_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_PW_100_101_MASK,
		.vaw = PMX_SDHCI_PW_100_101_VAW,
	},
};

static stwuct speaw_muxweg sdhci_cd_12_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_12_MASK,
		.vaw = PMX_SDHCI_CD_PW_12_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SDHCI_CD_POWT_SEW_MASK,
		.vaw = PMX_SDHCI_CD_POWT_12_VAW,
	},
};

static stwuct speaw_muxweg sdhci_cd_51_muxweg[] = {
	{
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_51_MASK,
		.vaw = PMX_SDHCI_CD_PW_51_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SDHCI_CD_POWT_SEW_MASK,
		.vaw = PMX_SDHCI_CD_POWT_51_VAW,
	},
};

#define pmx_sdhci_common_modemux					\
	{								\
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE |	\
			SMAWW_PWINTEWS_MODE | EXTENDED_MODE,		\
		.muxwegs = sdhci_muxweg,				\
		.nmuxwegs = AWWAY_SIZE(sdhci_muxweg),			\
	}, {								\
		.modes = EXTENDED_MODE,					\
		.muxwegs = sdhci_ext_muxweg,				\
		.nmuxwegs = AWWAY_SIZE(sdhci_ext_muxweg),		\
	}

static stwuct speaw_modemux sdhci_modemux[][3] = {
	{
		/* sewect pin 12 fow cd */
		pmx_sdhci_common_modemux,
		{
			.modes = EXTENDED_MODE,
			.muxwegs = sdhci_cd_12_muxweg,
			.nmuxwegs = AWWAY_SIZE(sdhci_cd_12_muxweg),
		},
	}, {
		/* sewect pin 51 fow cd */
		pmx_sdhci_common_modemux,
		{
			.modes = EXTENDED_MODE,
			.muxwegs = sdhci_cd_51_muxweg,
			.nmuxwegs = AWWAY_SIZE(sdhci_cd_51_muxweg),
		},
	}
};

static stwuct speaw_pingwoup sdhci_pingwoup[] = {
	{
		.name = "sdhci_cd_12_gwp",
		.pins = sdhci_cd_12_pins,
		.npins = AWWAY_SIZE(sdhci_cd_12_pins),
		.modemuxs = sdhci_modemux[0],
		.nmodemuxs = AWWAY_SIZE(sdhci_modemux[0]),
	}, {
		.name = "sdhci_cd_51_gwp",
		.pins = sdhci_cd_51_pins,
		.npins = AWWAY_SIZE(sdhci_cd_51_pins),
		.modemuxs = sdhci_modemux[1],
		.nmodemuxs = AWWAY_SIZE(sdhci_modemux[1]),
	},
};

static const chaw *const sdhci_gwps[] = { "sdhci_cd_12_gwp", "sdhci_cd_51_gwp",
	"sdhci_wed_gwp" };

static stwuct speaw_function sdhci_function = {
	.name = "sdhci",
	.gwoups = sdhci_gwps,
	.ngwoups = AWWAY_SIZE(sdhci_gwps),
};

/* Pad muwtipwexing fow I2S device */
static const unsigned i2s_pins[] = { 35, 39, 40, 41, 42 };
static stwuct speaw_muxweg i2s_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK,
		.vaw = 0,
	}, {
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg i2s_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_35_MASK | PMX_PW_39_MASK,
		.vaw = PMX_I2S_WEF_CWK_PW_35_VAW | PMX_I2S_PW_39_VAW,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_40_MASK | PMX_PW_41_42_MASK,
		.vaw = PMX_I2S_PW_40_VAW | PMX_I2S_PW_41_42_VAW,
	},
};

static stwuct speaw_modemux i2s_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxwegs = i2s_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2s_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = i2s_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2s_ext_muxweg),
	},
};

static stwuct speaw_pingwoup i2s_pingwoup = {
	.name = "i2s_gwp",
	.pins = i2s_pins,
	.npins = AWWAY_SIZE(i2s_pins),
	.modemuxs = i2s_modemux,
	.nmodemuxs = AWWAY_SIZE(i2s_modemux),
};

static const chaw *const i2s_gwps[] = { "i2s_gwp" };
static stwuct speaw_function i2s_function = {
	.name = "i2s",
	.gwoups = i2s_gwps,
	.ngwoups = AWWAY_SIZE(i2s_gwps),
};

/* Pad muwtipwexing fow UAWT1 device */
static const unsigned uawt1_pins[] = { 28, 29 };
static stwuct speaw_muxweg uawt1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN0_MASK | PMX_GPIO_PIN1_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg uawt1_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_28_29_MASK,
		.vaw = PMX_UAWT1_PW_28_29_VAW,
	},
};

static stwuct speaw_modemux uawt1_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
		.muxwegs = uawt1_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = uawt1_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_ext_muxweg),
	},
};

static stwuct speaw_pingwoup uawt1_pingwoup = {
	.name = "uawt1_gwp",
	.pins = uawt1_pins,
	.npins = AWWAY_SIZE(uawt1_pins),
	.modemuxs = uawt1_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt1_modemux),
};

static const chaw *const uawt1_gwps[] = { "uawt1_gwp" };
static stwuct speaw_function uawt1_function = {
	.name = "uawt1",
	.gwoups = uawt1_gwps,
	.ngwoups = AWWAY_SIZE(uawt1_gwps),
};

/* Pad muwtipwexing fow UAWT1 Modem device */
static const unsigned uawt1_modem_2_to_7_pins[] = { 2, 3, 4, 5, 6, 7 };
static const unsigned uawt1_modem_31_to_36_pins[] = { 31, 32, 33, 34, 35, 36 };
static const unsigned uawt1_modem_34_to_45_pins[] = { 34, 35, 36, 43, 44, 45 };
static const unsigned uawt1_modem_80_to_85_pins[] = { 80, 81, 82, 83, 84, 85 };

static stwuct speaw_muxweg uawt1_modem_ext_2_to_7_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MASK | PMX_I2C_MASK | PMX_SSP_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_2_3_MASK | PMX_PW_6_7_MASK,
		.vaw = PMX_UAWT1_ENH_PW_2_3_VAW | PMX_UAWT1_ENH_PW_4_5_VAW |
			PMX_UAWT1_ENH_PW_6_7_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT1_ENH_POWT_SEW_MASK,
		.vaw = PMX_UAWT1_ENH_POWT_3_TO_5_7_VAW,
	},
};

static stwuct speaw_muxweg uawt1_modem_31_to_36_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN3_MASK | PMX_GPIO_PIN4_MASK |
			PMX_GPIO_PIN5_MASK | PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg uawt1_modem_ext_31_to_36_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_31_MASK | PMX_PW_32_33_MASK | PMX_PW_34_MASK |
			PMX_PW_35_MASK | PMX_PW_36_MASK,
		.vaw = PMX_UAWT1_ENH_PW_31_VAW | PMX_UAWT1_ENH_PW_32_33_VAW |
			PMX_UAWT1_ENH_PW_34_VAW | PMX_UAWT1_ENH_PW_35_VAW |
			PMX_UAWT1_ENH_PW_36_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT1_ENH_POWT_SEW_MASK,
		.vaw = PMX_UAWT1_ENH_POWT_32_TO_34_36_VAW,
	},
};

static stwuct speaw_muxweg uawt1_modem_34_to_45_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK |
			PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg uawt1_modem_ext_34_to_45_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_34_MASK | PMX_PW_35_MASK | PMX_PW_36_MASK,
		.vaw = PMX_UAWT1_ENH_PW_34_VAW | PMX_UAWT1_ENH_PW_35_VAW |
			PMX_UAWT1_ENH_PW_36_VAW,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_43_MASK | PMX_PW_44_45_MASK,
		.vaw = PMX_UAWT1_ENH_PW_43_VAW | PMX_UAWT1_ENH_PW_44_45_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT1_ENH_POWT_SEW_MASK,
		.vaw = PMX_UAWT1_ENH_POWT_44_45_34_36_VAW,
	},
};

static stwuct speaw_muxweg uawt1_modem_ext_80_to_85_muxweg[] = {
	{
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_80_TO_85_MASK,
		.vaw = PMX_UAWT1_ENH_PW_80_TO_85_VAW,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_43_MASK | PMX_PW_44_45_MASK,
		.vaw = PMX_UAWT1_ENH_PW_43_VAW | PMX_UAWT1_ENH_PW_44_45_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT1_ENH_POWT_SEW_MASK,
		.vaw = PMX_UAWT1_ENH_POWT_81_TO_85_VAW,
	},
};

static stwuct speaw_modemux uawt1_modem_2_to_7_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = uawt1_modem_ext_2_to_7_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_modem_ext_2_to_7_muxweg),
	},
};

static stwuct speaw_modemux uawt1_modem_31_to_36_modemux[] = {
	{
		.modes = SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
		.muxwegs = uawt1_modem_31_to_36_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_modem_31_to_36_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = uawt1_modem_ext_31_to_36_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_modem_ext_31_to_36_muxweg),
	},
};

static stwuct speaw_modemux uawt1_modem_34_to_45_modemux[] = {
	{
		.modes = AUTO_EXP_MODE | EXTENDED_MODE,
		.muxwegs = uawt1_modem_34_to_45_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_modem_34_to_45_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = uawt1_modem_ext_34_to_45_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_modem_ext_34_to_45_muxweg),
	},
};

static stwuct speaw_modemux uawt1_modem_80_to_85_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = uawt1_modem_ext_80_to_85_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_modem_ext_80_to_85_muxweg),
	},
};

static stwuct speaw_pingwoup uawt1_modem_pingwoup[] = {
	{
		.name = "uawt1_modem_2_to_7_gwp",
		.pins = uawt1_modem_2_to_7_pins,
		.npins = AWWAY_SIZE(uawt1_modem_2_to_7_pins),
		.modemuxs = uawt1_modem_2_to_7_modemux,
		.nmodemuxs = AWWAY_SIZE(uawt1_modem_2_to_7_modemux),
	}, {
		.name = "uawt1_modem_31_to_36_gwp",
		.pins = uawt1_modem_31_to_36_pins,
		.npins = AWWAY_SIZE(uawt1_modem_31_to_36_pins),
		.modemuxs = uawt1_modem_31_to_36_modemux,
		.nmodemuxs = AWWAY_SIZE(uawt1_modem_31_to_36_modemux),
	}, {
		.name = "uawt1_modem_34_to_45_gwp",
		.pins = uawt1_modem_34_to_45_pins,
		.npins = AWWAY_SIZE(uawt1_modem_34_to_45_pins),
		.modemuxs = uawt1_modem_34_to_45_modemux,
		.nmodemuxs = AWWAY_SIZE(uawt1_modem_34_to_45_modemux),
	}, {
		.name = "uawt1_modem_80_to_85_gwp",
		.pins = uawt1_modem_80_to_85_pins,
		.npins = AWWAY_SIZE(uawt1_modem_80_to_85_pins),
		.modemuxs = uawt1_modem_80_to_85_modemux,
		.nmodemuxs = AWWAY_SIZE(uawt1_modem_80_to_85_modemux),
	},
};

static const chaw *const uawt1_modem_gwps[] = { "uawt1_modem_2_to_7_gwp",
	"uawt1_modem_31_to_36_gwp", "uawt1_modem_34_to_45_gwp",
	"uawt1_modem_80_to_85_gwp" };
static stwuct speaw_function uawt1_modem_function = {
	.name = "uawt1_modem",
	.gwoups = uawt1_modem_gwps,
	.ngwoups = AWWAY_SIZE(uawt1_modem_gwps),
};

/* Pad muwtipwexing fow UAWT2 device */
static const unsigned uawt2_pins[] = { 0, 1 };
static stwuct speaw_muxweg uawt2_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_FIWDA_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg uawt2_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_0_1_MASK,
		.vaw = PMX_UAWT2_PW_0_1_VAW,
	},
};

static stwuct speaw_modemux uawt2_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
		.muxwegs = uawt2_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt2_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = uawt2_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt2_ext_muxweg),
	},
};

static stwuct speaw_pingwoup uawt2_pingwoup = {
	.name = "uawt2_gwp",
	.pins = uawt2_pins,
	.npins = AWWAY_SIZE(uawt2_pins),
	.modemuxs = uawt2_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt2_modemux),
};

static const chaw *const uawt2_gwps[] = { "uawt2_gwp" };
static stwuct speaw_function uawt2_function = {
	.name = "uawt2",
	.gwoups = uawt2_gwps,
	.ngwoups = AWWAY_SIZE(uawt2_gwps),
};

/* Pad muwtipwexing fow uawt3 device */
static const unsigned uawt3_pins[][2] = { { 8, 9 }, { 15, 16 }, { 41, 42 },
	{ 52, 53 }, { 73, 74 }, { 94, 95 }, { 98, 99 } };

static stwuct speaw_muxweg uawt3_ext_8_9_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_8_9_MASK,
		.vaw = PMX_UAWT3_PW_8_9_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_8_VAW,
	},
};

static stwuct speaw_muxweg uawt3_ext_15_16_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_15_16_MASK,
		.vaw = PMX_UAWT3_PW_15_16_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_15_VAW,
	},
};

static stwuct speaw_muxweg uawt3_ext_41_42_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_41_42_MASK,
		.vaw = PMX_UAWT3_PW_41_42_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_41_VAW,
	},
};

static stwuct speaw_muxweg uawt3_ext_52_53_muxweg[] = {
	{
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_52_53_MASK,
		.vaw = PMX_UAWT3_PW_52_53_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_52_VAW,
	},
};

static stwuct speaw_muxweg uawt3_ext_73_74_muxweg[] = {
	{
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_73_MASK | PMX_PW_74_MASK,
		.vaw = PMX_UAWT3_PW_73_VAW | PMX_UAWT3_PW_74_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_73_VAW,
	},
};

static stwuct speaw_muxweg uawt3_ext_94_95_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_94_95_MASK,
		.vaw = PMX_UAWT3_PW_94_95_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_94_VAW,
	},
};

static stwuct speaw_muxweg uawt3_ext_98_99_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_98_MASK | PMX_PW_99_MASK,
		.vaw = PMX_UAWT3_PW_98_VAW | PMX_UAWT3_PW_99_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT3_POWT_SEW_MASK,
		.vaw = PMX_UAWT3_POWT_99_VAW,
	},
};

static stwuct speaw_modemux uawt3_modemux[][1] = {
	{
		/* Sewect signaws on pins 8_9 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_8_9_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_8_9_muxweg),
		},
	}, {
		/* Sewect signaws on pins 15_16 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_15_16_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_15_16_muxweg),
		},
	}, {
		/* Sewect signaws on pins 41_42 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_41_42_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_41_42_muxweg),
		},
	}, {
		/* Sewect signaws on pins 52_53 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_52_53_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_52_53_muxweg),
		},
	}, {
		/* Sewect signaws on pins 73_74 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_73_74_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_73_74_muxweg),
		},
	}, {
		/* Sewect signaws on pins 94_95 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_94_95_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_94_95_muxweg),
		},
	}, {
		/* Sewect signaws on pins 98_99 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt3_ext_98_99_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt3_ext_98_99_muxweg),
		},
	},
};

static stwuct speaw_pingwoup uawt3_pingwoup[] = {
	{
		.name = "uawt3_8_9_gwp",
		.pins = uawt3_pins[0],
		.npins = AWWAY_SIZE(uawt3_pins[0]),
		.modemuxs = uawt3_modemux[0],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[0]),
	}, {
		.name = "uawt3_15_16_gwp",
		.pins = uawt3_pins[1],
		.npins = AWWAY_SIZE(uawt3_pins[1]),
		.modemuxs = uawt3_modemux[1],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[1]),
	}, {
		.name = "uawt3_41_42_gwp",
		.pins = uawt3_pins[2],
		.npins = AWWAY_SIZE(uawt3_pins[2]),
		.modemuxs = uawt3_modemux[2],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[2]),
	}, {
		.name = "uawt3_52_53_gwp",
		.pins = uawt3_pins[3],
		.npins = AWWAY_SIZE(uawt3_pins[3]),
		.modemuxs = uawt3_modemux[3],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[3]),
	}, {
		.name = "uawt3_73_74_gwp",
		.pins = uawt3_pins[4],
		.npins = AWWAY_SIZE(uawt3_pins[4]),
		.modemuxs = uawt3_modemux[4],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[4]),
	}, {
		.name = "uawt3_94_95_gwp",
		.pins = uawt3_pins[5],
		.npins = AWWAY_SIZE(uawt3_pins[5]),
		.modemuxs = uawt3_modemux[5],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[5]),
	}, {
		.name = "uawt3_98_99_gwp",
		.pins = uawt3_pins[6],
		.npins = AWWAY_SIZE(uawt3_pins[6]),
		.modemuxs = uawt3_modemux[6],
		.nmodemuxs = AWWAY_SIZE(uawt3_modemux[6]),
	},
};

static const chaw *const uawt3_gwps[] = { "uawt3_8_9_gwp", "uawt3_15_16_gwp",
	"uawt3_41_42_gwp", "uawt3_52_53_gwp", "uawt3_73_74_gwp",
	"uawt3_94_95_gwp", "uawt3_98_99_gwp" };

static stwuct speaw_function uawt3_function = {
	.name = "uawt3",
	.gwoups = uawt3_gwps,
	.ngwoups = AWWAY_SIZE(uawt3_gwps),
};

/* Pad muwtipwexing fow uawt4 device */
static const unsigned uawt4_pins[][2] = { { 6, 7 }, { 13, 14 }, { 39, 40 },
	{ 71, 72 }, { 92, 93 }, { 100, 101 } };

static stwuct speaw_muxweg uawt4_ext_6_7_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_6_7_MASK,
		.vaw = PMX_UAWT4_PW_6_7_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT4_POWT_SEW_MASK,
		.vaw = PMX_UAWT4_POWT_6_VAW,
	},
};

static stwuct speaw_muxweg uawt4_ext_13_14_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_13_14_MASK,
		.vaw = PMX_UAWT4_PW_13_14_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT4_POWT_SEW_MASK,
		.vaw = PMX_UAWT4_POWT_13_VAW,
	},
};

static stwuct speaw_muxweg uawt4_ext_39_40_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_39_MASK,
		.vaw = PMX_UAWT4_PW_39_VAW,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_40_MASK,
		.vaw = PMX_UAWT4_PW_40_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT4_POWT_SEW_MASK,
		.vaw = PMX_UAWT4_POWT_39_VAW,
	},
};

static stwuct speaw_muxweg uawt4_ext_71_72_muxweg[] = {
	{
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_71_72_MASK,
		.vaw = PMX_UAWT4_PW_71_72_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT4_POWT_SEW_MASK,
		.vaw = PMX_UAWT4_POWT_71_VAW,
	},
};

static stwuct speaw_muxweg uawt4_ext_92_93_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_92_93_MASK,
		.vaw = PMX_UAWT4_PW_92_93_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT4_POWT_SEW_MASK,
		.vaw = PMX_UAWT4_POWT_92_VAW,
	},
};

static stwuct speaw_muxweg uawt4_ext_100_101_muxweg[] = {
	{
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_PW_100_101_MASK |
			PMX_UAWT4_POWT_SEW_MASK,
		.vaw = PMX_UAWT4_PW_100_101_VAW |
			PMX_UAWT4_POWT_101_VAW,
	},
};

static stwuct speaw_modemux uawt4_modemux[][1] = {
	{
		/* Sewect signaws on pins 6_7 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt4_ext_6_7_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt4_ext_6_7_muxweg),
		},
	}, {
		/* Sewect signaws on pins 13_14 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt4_ext_13_14_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt4_ext_13_14_muxweg),
		},
	}, {
		/* Sewect signaws on pins 39_40 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt4_ext_39_40_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt4_ext_39_40_muxweg),
		},
	}, {
		/* Sewect signaws on pins 71_72 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt4_ext_71_72_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt4_ext_71_72_muxweg),
		},
	}, {
		/* Sewect signaws on pins 92_93 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt4_ext_92_93_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt4_ext_92_93_muxweg),
		},
	}, {
		/* Sewect signaws on pins 100_101_ */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt4_ext_100_101_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt4_ext_100_101_muxweg),
		},
	},
};

static stwuct speaw_pingwoup uawt4_pingwoup[] = {
	{
		.name = "uawt4_6_7_gwp",
		.pins = uawt4_pins[0],
		.npins = AWWAY_SIZE(uawt4_pins[0]),
		.modemuxs = uawt4_modemux[0],
		.nmodemuxs = AWWAY_SIZE(uawt4_modemux[0]),
	}, {
		.name = "uawt4_13_14_gwp",
		.pins = uawt4_pins[1],
		.npins = AWWAY_SIZE(uawt4_pins[1]),
		.modemuxs = uawt4_modemux[1],
		.nmodemuxs = AWWAY_SIZE(uawt4_modemux[1]),
	}, {
		.name = "uawt4_39_40_gwp",
		.pins = uawt4_pins[2],
		.npins = AWWAY_SIZE(uawt4_pins[2]),
		.modemuxs = uawt4_modemux[2],
		.nmodemuxs = AWWAY_SIZE(uawt4_modemux[2]),
	}, {
		.name = "uawt4_71_72_gwp",
		.pins = uawt4_pins[3],
		.npins = AWWAY_SIZE(uawt4_pins[3]),
		.modemuxs = uawt4_modemux[3],
		.nmodemuxs = AWWAY_SIZE(uawt4_modemux[3]),
	}, {
		.name = "uawt4_92_93_gwp",
		.pins = uawt4_pins[4],
		.npins = AWWAY_SIZE(uawt4_pins[4]),
		.modemuxs = uawt4_modemux[4],
		.nmodemuxs = AWWAY_SIZE(uawt4_modemux[4]),
	}, {
		.name = "uawt4_100_101_gwp",
		.pins = uawt4_pins[5],
		.npins = AWWAY_SIZE(uawt4_pins[5]),
		.modemuxs = uawt4_modemux[5],
		.nmodemuxs = AWWAY_SIZE(uawt4_modemux[5]),
	},
};

static const chaw *const uawt4_gwps[] = { "uawt4_6_7_gwp", "uawt4_13_14_gwp",
	"uawt4_39_40_gwp", "uawt4_71_72_gwp", "uawt4_92_93_gwp",
	"uawt4_100_101_gwp" };

static stwuct speaw_function uawt4_function = {
	.name = "uawt4",
	.gwoups = uawt4_gwps,
	.ngwoups = AWWAY_SIZE(uawt4_gwps),
};

/* Pad muwtipwexing fow uawt5 device */
static const unsigned uawt5_pins[][2] = { { 4, 5 }, { 37, 38 }, { 69, 70 },
	{ 90, 91 } };

static stwuct speaw_muxweg uawt5_ext_4_5_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_I2C_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_4_5_MASK,
		.vaw = PMX_UAWT5_PW_4_5_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT5_POWT_SEW_MASK,
		.vaw = PMX_UAWT5_POWT_4_VAW,
	},
};

static stwuct speaw_muxweg uawt5_ext_37_38_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_37_38_MASK,
		.vaw = PMX_UAWT5_PW_37_38_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT5_POWT_SEW_MASK,
		.vaw = PMX_UAWT5_POWT_37_VAW,
	},
};

static stwuct speaw_muxweg uawt5_ext_69_70_muxweg[] = {
	{
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_69_MASK,
		.vaw = PMX_UAWT5_PW_69_VAW,
	}, {
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_70_MASK,
		.vaw = PMX_UAWT5_PW_70_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT5_POWT_SEW_MASK,
		.vaw = PMX_UAWT5_POWT_69_VAW,
	},
};

static stwuct speaw_muxweg uawt5_ext_90_91_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_90_91_MASK,
		.vaw = PMX_UAWT5_PW_90_91_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT5_POWT_SEW_MASK,
		.vaw = PMX_UAWT5_POWT_90_VAW,
	},
};

static stwuct speaw_modemux uawt5_modemux[][1] = {
	{
		/* Sewect signaws on pins 4_5 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt5_ext_4_5_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt5_ext_4_5_muxweg),
		},
	}, {
		/* Sewect signaws on pins 37_38 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt5_ext_37_38_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt5_ext_37_38_muxweg),
		},
	}, {
		/* Sewect signaws on pins 69_70 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt5_ext_69_70_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt5_ext_69_70_muxweg),
		},
	}, {
		/* Sewect signaws on pins 90_91 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt5_ext_90_91_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt5_ext_90_91_muxweg),
		},
	},
};

static stwuct speaw_pingwoup uawt5_pingwoup[] = {
	{
		.name = "uawt5_4_5_gwp",
		.pins = uawt5_pins[0],
		.npins = AWWAY_SIZE(uawt5_pins[0]),
		.modemuxs = uawt5_modemux[0],
		.nmodemuxs = AWWAY_SIZE(uawt5_modemux[0]),
	}, {
		.name = "uawt5_37_38_gwp",
		.pins = uawt5_pins[1],
		.npins = AWWAY_SIZE(uawt5_pins[1]),
		.modemuxs = uawt5_modemux[1],
		.nmodemuxs = AWWAY_SIZE(uawt5_modemux[1]),
	}, {
		.name = "uawt5_69_70_gwp",
		.pins = uawt5_pins[2],
		.npins = AWWAY_SIZE(uawt5_pins[2]),
		.modemuxs = uawt5_modemux[2],
		.nmodemuxs = AWWAY_SIZE(uawt5_modemux[2]),
	}, {
		.name = "uawt5_90_91_gwp",
		.pins = uawt5_pins[3],
		.npins = AWWAY_SIZE(uawt5_pins[3]),
		.modemuxs = uawt5_modemux[3],
		.nmodemuxs = AWWAY_SIZE(uawt5_modemux[3]),
	},
};

static const chaw *const uawt5_gwps[] = { "uawt5_4_5_gwp", "uawt5_37_38_gwp",
	"uawt5_69_70_gwp", "uawt5_90_91_gwp" };
static stwuct speaw_function uawt5_function = {
	.name = "uawt5",
	.gwoups = uawt5_gwps,
	.ngwoups = AWWAY_SIZE(uawt5_gwps),
};

/* Pad muwtipwexing fow uawt6 device */
static const unsigned uawt6_pins[][2] = { { 2, 3 }, { 88, 89 } };
static stwuct speaw_muxweg uawt6_ext_2_3_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_2_3_MASK,
		.vaw = PMX_UAWT6_PW_2_3_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT6_POWT_SEW_MASK,
		.vaw = PMX_UAWT6_POWT_2_VAW,
	},
};

static stwuct speaw_muxweg uawt6_ext_88_89_muxweg[] = {
	{
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_88_89_MASK,
		.vaw = PMX_UAWT6_PW_88_89_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_UAWT6_POWT_SEW_MASK,
		.vaw = PMX_UAWT6_POWT_88_VAW,
	},
};

static stwuct speaw_modemux uawt6_modemux[][1] = {
	{
		/* Sewect signaws on pins 2_3 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt6_ext_2_3_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt6_ext_2_3_muxweg),
		},
	}, {
		/* Sewect signaws on pins 88_89 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = uawt6_ext_88_89_muxweg,
			.nmuxwegs = AWWAY_SIZE(uawt6_ext_88_89_muxweg),
		},
	},
};

static stwuct speaw_pingwoup uawt6_pingwoup[] = {
	{
		.name = "uawt6_2_3_gwp",
		.pins = uawt6_pins[0],
		.npins = AWWAY_SIZE(uawt6_pins[0]),
		.modemuxs = uawt6_modemux[0],
		.nmodemuxs = AWWAY_SIZE(uawt6_modemux[0]),
	}, {
		.name = "uawt6_88_89_gwp",
		.pins = uawt6_pins[1],
		.npins = AWWAY_SIZE(uawt6_pins[1]),
		.modemuxs = uawt6_modemux[1],
		.nmodemuxs = AWWAY_SIZE(uawt6_modemux[1]),
	},
};

static const chaw *const uawt6_gwps[] = { "uawt6_2_3_gwp", "uawt6_88_89_gwp" };
static stwuct speaw_function uawt6_function = {
	.name = "uawt6",
	.gwoups = uawt6_gwps,
	.ngwoups = AWWAY_SIZE(uawt6_gwps),
};

/* UAWT - WS485 pmx */
static const unsigned ws485_pins[] = { 77, 78, 79 };
static stwuct speaw_muxweg ws485_muxweg[] = {
	{
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_77_78_79_MASK,
		.vaw = PMX_WS485_PW_77_78_79_VAW,
	},
};

static stwuct speaw_modemux ws485_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ws485_muxweg,
		.nmuxwegs = AWWAY_SIZE(ws485_muxweg),
	},
};

static stwuct speaw_pingwoup ws485_pingwoup = {
	.name = "ws485_gwp",
	.pins = ws485_pins,
	.npins = AWWAY_SIZE(ws485_pins),
	.modemuxs = ws485_modemux,
	.nmodemuxs = AWWAY_SIZE(ws485_modemux),
};

static const chaw *const ws485_gwps[] = { "ws485_gwp" };
static stwuct speaw_function ws485_function = {
	.name = "ws485",
	.gwoups = ws485_gwps,
	.ngwoups = AWWAY_SIZE(ws485_gwps),
};

/* Pad muwtipwexing fow Touchscween device */
static const unsigned touchscween_pins[] = { 5, 36 };
static stwuct speaw_muxweg touchscween_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_I2C_MASK | PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg touchscween_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_5_MASK,
		.vaw = PMX_TOUCH_Y_PW_5_VAW,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_36_MASK,
		.vaw = PMX_TOUCH_X_PW_36_VAW,
	},
};

static stwuct speaw_modemux touchscween_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | EXTENDED_MODE,
		.muxwegs = touchscween_muxweg,
		.nmuxwegs = AWWAY_SIZE(touchscween_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = touchscween_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(touchscween_ext_muxweg),
	},
};

static stwuct speaw_pingwoup touchscween_pingwoup = {
	.name = "touchscween_gwp",
	.pins = touchscween_pins,
	.npins = AWWAY_SIZE(touchscween_pins),
	.modemuxs = touchscween_modemux,
	.nmodemuxs = AWWAY_SIZE(touchscween_modemux),
};

static const chaw *const touchscween_gwps[] = { "touchscween_gwp" };
static stwuct speaw_function touchscween_function = {
	.name = "touchscween",
	.gwoups = touchscween_gwps,
	.ngwoups = AWWAY_SIZE(touchscween_gwps),
};

/* Pad muwtipwexing fow CAN device */
static const unsigned can0_pins[] = { 32, 33 };
static stwuct speaw_muxweg can0_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN4_MASK | PMX_GPIO_PIN5_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg can0_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_32_33_MASK,
		.vaw = PMX_CAN0_PW_32_33_VAW,
	},
};

static stwuct speaw_modemux can0_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| EXTENDED_MODE,
		.muxwegs = can0_muxweg,
		.nmuxwegs = AWWAY_SIZE(can0_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = can0_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(can0_ext_muxweg),
	},
};

static stwuct speaw_pingwoup can0_pingwoup = {
	.name = "can0_gwp",
	.pins = can0_pins,
	.npins = AWWAY_SIZE(can0_pins),
	.modemuxs = can0_modemux,
	.nmodemuxs = AWWAY_SIZE(can0_modemux),
};

static const chaw *const can0_gwps[] = { "can0_gwp" };
static stwuct speaw_function can0_function = {
	.name = "can0",
	.gwoups = can0_gwps,
	.ngwoups = AWWAY_SIZE(can0_gwps),
};

static const unsigned can1_pins[] = { 30, 31 };
static stwuct speaw_muxweg can1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg can1_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_30_31_MASK,
		.vaw = PMX_CAN1_PW_30_31_VAW,
	},
};

static stwuct speaw_modemux can1_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | AUTO_EXP_MODE
			| EXTENDED_MODE,
		.muxwegs = can1_muxweg,
		.nmuxwegs = AWWAY_SIZE(can1_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = can1_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(can1_ext_muxweg),
	},
};

static stwuct speaw_pingwoup can1_pingwoup = {
	.name = "can1_gwp",
	.pins = can1_pins,
	.npins = AWWAY_SIZE(can1_pins),
	.modemuxs = can1_modemux,
	.nmodemuxs = AWWAY_SIZE(can1_modemux),
};

static const chaw *const can1_gwps[] = { "can1_gwp" };
static stwuct speaw_function can1_function = {
	.name = "can1",
	.gwoups = can1_gwps,
	.ngwoups = AWWAY_SIZE(can1_gwps),
};

/* Pad muwtipwexing fow PWM0_1 device */
static const unsigned pwm0_1_pins[][2] = { { 37, 38 }, { 14, 15 }, { 8, 9 },
	{ 30, 31 }, { 42, 43 }, { 59, 60 }, { 88, 89 } };

static stwuct speaw_muxweg pwm0_1_pin_8_9_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_8_9_MASK,
		.vaw = PMX_PWM_0_1_PW_8_9_VAW,
	},
};

static stwuct speaw_muxweg pwm0_1_autoexpsmawwpwi_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg pwm0_1_pin_14_15_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_14_MASK | PMX_PW_15_MASK,
		.vaw = PMX_PWM1_PW_14_VAW | PMX_PWM0_PW_15_VAW,
	},
};

static stwuct speaw_muxweg pwm0_1_pin_30_31_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_30_MASK | PMX_PW_31_MASK,
		.vaw = PMX_PWM1_EXT_PW_30_VAW | PMX_PWM0_EXT_PW_31_VAW,
	},
};

static stwuct speaw_muxweg pwm0_1_net_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg pwm0_1_pin_37_38_muxweg[] = {
	{
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_37_38_MASK,
		.vaw = PMX_PWM0_1_PW_37_38_VAW,
	},
};

static stwuct speaw_muxweg pwm0_1_pin_42_43_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK | PMX_TIMEW_0_1_MASK ,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_42_MASK | PMX_PW_43_MASK,
		.vaw = PMX_PWM1_PW_42_VAW |
			PMX_PWM0_PW_43_VAW,
	},
};

static stwuct speaw_muxweg pwm0_1_pin_59_60_muxweg[] = {
	{
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_59_MASK,
		.vaw = PMX_PWM1_PW_59_VAW,
	}, {
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_60_MASK,
		.vaw = PMX_PWM0_PW_60_VAW,
	},
};

static stwuct speaw_muxweg pwm0_1_pin_88_89_muxweg[] = {
	{
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_88_89_MASK,
		.vaw = PMX_PWM0_1_PW_88_89_VAW,
	},
};

static stwuct speaw_modemux pwm0_1_pin_8_9_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_8_9_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_8_9_muxweg),
	},
};

static stwuct speaw_modemux pwm0_1_pin_14_15_modemux[] = {
	{
		.modes = AUTO_EXP_MODE | SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
		.muxwegs = pwm0_1_autoexpsmawwpwi_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_autoexpsmawwpwi_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_14_15_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_14_15_muxweg),
	},
};

static stwuct speaw_modemux pwm0_1_pin_30_31_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_30_31_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_30_31_muxweg),
	},
};

static stwuct speaw_modemux pwm0_1_pin_37_38_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxwegs = pwm0_1_net_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_net_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_37_38_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_37_38_muxweg),
	},
};

static stwuct speaw_modemux pwm0_1_pin_42_43_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_42_43_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_42_43_muxweg),
	},
};

static stwuct speaw_modemux pwm0_1_pin_59_60_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_59_60_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_59_60_muxweg),
	},
};

static stwuct speaw_modemux pwm0_1_pin_88_89_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm0_1_pin_88_89_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm0_1_pin_88_89_muxweg),
	},
};

static stwuct speaw_pingwoup pwm0_1_pingwoup[] = {
	{
		.name = "pwm0_1_pin_8_9_gwp",
		.pins = pwm0_1_pins[0],
		.npins = AWWAY_SIZE(pwm0_1_pins[0]),
		.modemuxs = pwm0_1_pin_8_9_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_8_9_modemux),
	}, {
		.name = "pwm0_1_pin_14_15_gwp",
		.pins = pwm0_1_pins[1],
		.npins = AWWAY_SIZE(pwm0_1_pins[1]),
		.modemuxs = pwm0_1_pin_14_15_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_14_15_modemux),
	}, {
		.name = "pwm0_1_pin_30_31_gwp",
		.pins = pwm0_1_pins[2],
		.npins = AWWAY_SIZE(pwm0_1_pins[2]),
		.modemuxs = pwm0_1_pin_30_31_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_30_31_modemux),
	}, {
		.name = "pwm0_1_pin_37_38_gwp",
		.pins = pwm0_1_pins[3],
		.npins = AWWAY_SIZE(pwm0_1_pins[3]),
		.modemuxs = pwm0_1_pin_37_38_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_37_38_modemux),
	}, {
		.name = "pwm0_1_pin_42_43_gwp",
		.pins = pwm0_1_pins[4],
		.npins = AWWAY_SIZE(pwm0_1_pins[4]),
		.modemuxs = pwm0_1_pin_42_43_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_42_43_modemux),
	}, {
		.name = "pwm0_1_pin_59_60_gwp",
		.pins = pwm0_1_pins[5],
		.npins = AWWAY_SIZE(pwm0_1_pins[5]),
		.modemuxs = pwm0_1_pin_59_60_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_59_60_modemux),
	}, {
		.name = "pwm0_1_pin_88_89_gwp",
		.pins = pwm0_1_pins[6],
		.npins = AWWAY_SIZE(pwm0_1_pins[6]),
		.modemuxs = pwm0_1_pin_88_89_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm0_1_pin_88_89_modemux),
	},
};

static const chaw *const pwm0_1_gwps[] = { "pwm0_1_pin_8_9_gwp",
	"pwm0_1_pin_14_15_gwp", "pwm0_1_pin_30_31_gwp", "pwm0_1_pin_37_38_gwp",
	"pwm0_1_pin_42_43_gwp", "pwm0_1_pin_59_60_gwp", "pwm0_1_pin_88_89_gwp"
};

static stwuct speaw_function pwm0_1_function = {
	.name = "pwm0_1",
	.gwoups = pwm0_1_gwps,
	.ngwoups = AWWAY_SIZE(pwm0_1_gwps),
};

/* Pad muwtipwexing fow PWM2 device */
static const unsigned pwm2_pins[][1] = { { 7 }, { 13 }, { 29 }, { 34 }, { 41 },
	{ 58 }, { 87 } };
static stwuct speaw_muxweg pwm2_net_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg pwm2_pin_7_muxweg[] = {
	{
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_7_MASK,
		.vaw = PMX_PWM_2_PW_7_VAW,
	},
};

static stwuct speaw_muxweg pwm2_autoexpsmawwpwi_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg pwm2_pin_13_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_13_MASK,
		.vaw = PMX_PWM2_PW_13_VAW,
	},
};

static stwuct speaw_muxweg pwm2_pin_29_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN1_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_29_MASK,
		.vaw = PMX_PWM_2_PW_29_VAW,
	},
};

static stwuct speaw_muxweg pwm2_pin_34_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK,
		.vaw = 0,
	}, {
		.weg = MODE_CONFIG_WEG,
		.mask = PMX_PWM_MASK,
		.vaw = PMX_PWM_MASK,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_34_MASK,
		.vaw = PMX_PWM2_PW_34_VAW,
	},
};

static stwuct speaw_muxweg pwm2_pin_41_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_41_MASK,
		.vaw = PMX_PWM2_PW_41_VAW,
	},
};

static stwuct speaw_muxweg pwm2_pin_58_muxweg[] = {
	{
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_58_MASK,
		.vaw = PMX_PWM2_PW_58_VAW,
	},
};

static stwuct speaw_muxweg pwm2_pin_87_muxweg[] = {
	{
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_87_MASK,
		.vaw = PMX_PWM2_PW_87_VAW,
	},
};

static stwuct speaw_modemux pwm2_pin_7_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | AUTO_NET_MII_MODE | EXTENDED_MODE,
		.muxwegs = pwm2_net_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_net_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_7_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_7_muxweg),
	},
};
static stwuct speaw_modemux pwm2_pin_13_modemux[] = {
	{
		.modes = AUTO_EXP_MODE | SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
		.muxwegs = pwm2_autoexpsmawwpwi_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_autoexpsmawwpwi_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_13_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_13_muxweg),
	},
};
static stwuct speaw_modemux pwm2_pin_29_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_29_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_29_muxweg),
	},
};
static stwuct speaw_modemux pwm2_pin_34_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_34_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_34_muxweg),
	},
};

static stwuct speaw_modemux pwm2_pin_41_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_41_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_41_muxweg),
	},
};

static stwuct speaw_modemux pwm2_pin_58_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_58_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_58_muxweg),
	},
};

static stwuct speaw_modemux pwm2_pin_87_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm2_pin_87_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm2_pin_87_muxweg),
	},
};

static stwuct speaw_pingwoup pwm2_pingwoup[] = {
	{
		.name = "pwm2_pin_7_gwp",
		.pins = pwm2_pins[0],
		.npins = AWWAY_SIZE(pwm2_pins[0]),
		.modemuxs = pwm2_pin_7_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_7_modemux),
	}, {
		.name = "pwm2_pin_13_gwp",
		.pins = pwm2_pins[1],
		.npins = AWWAY_SIZE(pwm2_pins[1]),
		.modemuxs = pwm2_pin_13_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_13_modemux),
	}, {
		.name = "pwm2_pin_29_gwp",
		.pins = pwm2_pins[2],
		.npins = AWWAY_SIZE(pwm2_pins[2]),
		.modemuxs = pwm2_pin_29_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_29_modemux),
	}, {
		.name = "pwm2_pin_34_gwp",
		.pins = pwm2_pins[3],
		.npins = AWWAY_SIZE(pwm2_pins[3]),
		.modemuxs = pwm2_pin_34_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_34_modemux),
	}, {
		.name = "pwm2_pin_41_gwp",
		.pins = pwm2_pins[4],
		.npins = AWWAY_SIZE(pwm2_pins[4]),
		.modemuxs = pwm2_pin_41_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_41_modemux),
	}, {
		.name = "pwm2_pin_58_gwp",
		.pins = pwm2_pins[5],
		.npins = AWWAY_SIZE(pwm2_pins[5]),
		.modemuxs = pwm2_pin_58_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_58_modemux),
	}, {
		.name = "pwm2_pin_87_gwp",
		.pins = pwm2_pins[6],
		.npins = AWWAY_SIZE(pwm2_pins[6]),
		.modemuxs = pwm2_pin_87_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm2_pin_87_modemux),
	},
};

static const chaw *const pwm2_gwps[] = { "pwm2_pin_7_gwp", "pwm2_pin_13_gwp",
	"pwm2_pin_29_gwp", "pwm2_pin_34_gwp", "pwm2_pin_41_gwp",
	"pwm2_pin_58_gwp", "pwm2_pin_87_gwp" };
static stwuct speaw_function pwm2_function = {
	.name = "pwm2",
	.gwoups = pwm2_gwps,
	.ngwoups = AWWAY_SIZE(pwm2_gwps),
};

/* Pad muwtipwexing fow PWM3 device */
static const unsigned pwm3_pins[][1] = { { 6 }, { 12 }, { 28 }, { 40 }, { 57 },
	{ 86 } };
static stwuct speaw_muxweg pwm3_pin_6_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_6_MASK,
		.vaw = PMX_PWM_3_PW_6_VAW,
	},
};

static stwuct speaw_muxweg pwm3_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg pwm3_pin_12_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_12_MASK,
		.vaw = PMX_PWM3_PW_12_VAW,
	},
};

static stwuct speaw_muxweg pwm3_pin_28_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN0_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_28_MASK,
		.vaw = PMX_PWM_3_PW_28_VAW,
	},
};

static stwuct speaw_muxweg pwm3_pin_40_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_40_MASK,
		.vaw = PMX_PWM3_PW_40_VAW,
	},
};

static stwuct speaw_muxweg pwm3_pin_57_muxweg[] = {
	{
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_57_MASK,
		.vaw = PMX_PWM3_PW_57_VAW,
	},
};

static stwuct speaw_muxweg pwm3_pin_86_muxweg[] = {
	{
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_86_MASK,
		.vaw = PMX_PWM3_PW_86_VAW,
	},
};

static stwuct speaw_modemux pwm3_pin_6_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm3_pin_6_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_pin_6_muxweg),
	},
};

static stwuct speaw_modemux pwm3_pin_12_modemux[] = {
	{
		.modes = AUTO_EXP_MODE | SMAWW_PWINTEWS_MODE |
			AUTO_NET_SMII_MODE | EXTENDED_MODE,
		.muxwegs = pwm3_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = pwm3_pin_12_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_pin_12_muxweg),
	},
};

static stwuct speaw_modemux pwm3_pin_28_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm3_pin_28_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_pin_28_muxweg),
	},
};

static stwuct speaw_modemux pwm3_pin_40_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm3_pin_40_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_pin_40_muxweg),
	},
};

static stwuct speaw_modemux pwm3_pin_57_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm3_pin_57_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_pin_57_muxweg),
	},
};

static stwuct speaw_modemux pwm3_pin_86_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = pwm3_pin_86_muxweg,
		.nmuxwegs = AWWAY_SIZE(pwm3_pin_86_muxweg),
	},
};

static stwuct speaw_pingwoup pwm3_pingwoup[] = {
	{
		.name = "pwm3_pin_6_gwp",
		.pins = pwm3_pins[0],
		.npins = AWWAY_SIZE(pwm3_pins[0]),
		.modemuxs = pwm3_pin_6_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm3_pin_6_modemux),
	}, {
		.name = "pwm3_pin_12_gwp",
		.pins = pwm3_pins[1],
		.npins = AWWAY_SIZE(pwm3_pins[1]),
		.modemuxs = pwm3_pin_12_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm3_pin_12_modemux),
	}, {
		.name = "pwm3_pin_28_gwp",
		.pins = pwm3_pins[2],
		.npins = AWWAY_SIZE(pwm3_pins[2]),
		.modemuxs = pwm3_pin_28_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm3_pin_28_modemux),
	}, {
		.name = "pwm3_pin_40_gwp",
		.pins = pwm3_pins[3],
		.npins = AWWAY_SIZE(pwm3_pins[3]),
		.modemuxs = pwm3_pin_40_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm3_pin_40_modemux),
	}, {
		.name = "pwm3_pin_57_gwp",
		.pins = pwm3_pins[4],
		.npins = AWWAY_SIZE(pwm3_pins[4]),
		.modemuxs = pwm3_pin_57_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm3_pin_57_modemux),
	}, {
		.name = "pwm3_pin_86_gwp",
		.pins = pwm3_pins[5],
		.npins = AWWAY_SIZE(pwm3_pins[5]),
		.modemuxs = pwm3_pin_86_modemux,
		.nmodemuxs = AWWAY_SIZE(pwm3_pin_86_modemux),
	},
};

static const chaw *const pwm3_gwps[] = { "pwm3_pin_6_gwp", "pwm3_pin_12_gwp",
	"pwm3_pin_28_gwp", "pwm3_pin_40_gwp", "pwm3_pin_57_gwp",
	"pwm3_pin_86_gwp" };
static stwuct speaw_function pwm3_function = {
	.name = "pwm3",
	.gwoups = pwm3_gwps,
	.ngwoups = AWWAY_SIZE(pwm3_gwps),
};

/* Pad muwtipwexing fow SSP1 device */
static const unsigned ssp1_pins[][2] = { { 17, 20 }, { 36, 39 }, { 48, 51 },
	{ 65, 68 }, { 94, 97 } };
static stwuct speaw_muxweg ssp1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg ssp1_ext_17_20_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_17_18_MASK | PMX_PW_19_MASK,
		.vaw = PMX_SSP1_PW_17_18_19_20_VAW,
	}, {
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_20_MASK,
		.vaw = PMX_SSP1_PW_17_18_19_20_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP1_POWT_SEW_MASK,
		.vaw = PMX_SSP1_POWT_17_TO_20_VAW,
	},
};

static stwuct speaw_muxweg ssp1_ext_36_39_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK | PMX_SSP_CS_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_36_MASK | PMX_PW_37_38_MASK | PMX_PW_39_MASK,
		.vaw = PMX_SSP1_PW_36_VAW | PMX_SSP1_PW_37_38_VAW |
			PMX_SSP1_PW_39_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP1_POWT_SEW_MASK,
		.vaw = PMX_SSP1_POWT_36_TO_39_VAW,
	},
};

static stwuct speaw_muxweg ssp1_ext_48_51_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_48_49_MASK,
		.vaw = PMX_SSP1_PW_48_49_VAW,
	}, {
		.weg = IP_SEW_PAD_50_59_WEG,
		.mask = PMX_PW_50_51_MASK,
		.vaw = PMX_SSP1_PW_50_51_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP1_POWT_SEW_MASK,
		.vaw = PMX_SSP1_POWT_48_TO_51_VAW,
	},
};

static stwuct speaw_muxweg ssp1_ext_65_68_muxweg[] = {
	{
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_65_TO_68_MASK,
		.vaw = PMX_SSP1_PW_65_TO_68_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP1_POWT_SEW_MASK,
		.vaw = PMX_SSP1_POWT_65_TO_68_VAW,
	},
};

static stwuct speaw_muxweg ssp1_ext_94_97_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_94_95_MASK | PMX_PW_96_97_MASK,
		.vaw = PMX_SSP1_PW_94_95_VAW | PMX_SSP1_PW_96_97_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP1_POWT_SEW_MASK,
		.vaw = PMX_SSP1_POWT_94_TO_97_VAW,
	},
};

static stwuct speaw_modemux ssp1_17_20_modemux[] = {
	{
		.modes = SMAWW_PWINTEWS_MODE | AUTO_NET_SMII_MODE |
			EXTENDED_MODE,
		.muxwegs = ssp1_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = ssp1_ext_17_20_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_ext_17_20_muxweg),
	},
};

static stwuct speaw_modemux ssp1_36_39_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp1_ext_36_39_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_ext_36_39_muxweg),
	},
};

static stwuct speaw_modemux ssp1_48_51_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp1_ext_48_51_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_ext_48_51_muxweg),
	},
};
static stwuct speaw_modemux ssp1_65_68_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp1_ext_65_68_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_ext_65_68_muxweg),
	},
};

static stwuct speaw_modemux ssp1_94_97_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp1_ext_94_97_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp1_ext_94_97_muxweg),
	},
};

static stwuct speaw_pingwoup ssp1_pingwoup[] = {
	{
		.name = "ssp1_17_20_gwp",
		.pins = ssp1_pins[0],
		.npins = AWWAY_SIZE(ssp1_pins[0]),
		.modemuxs = ssp1_17_20_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp1_17_20_modemux),
	}, {
		.name = "ssp1_36_39_gwp",
		.pins = ssp1_pins[1],
		.npins = AWWAY_SIZE(ssp1_pins[1]),
		.modemuxs = ssp1_36_39_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp1_36_39_modemux),
	}, {
		.name = "ssp1_48_51_gwp",
		.pins = ssp1_pins[2],
		.npins = AWWAY_SIZE(ssp1_pins[2]),
		.modemuxs = ssp1_48_51_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp1_48_51_modemux),
	}, {
		.name = "ssp1_65_68_gwp",
		.pins = ssp1_pins[3],
		.npins = AWWAY_SIZE(ssp1_pins[3]),
		.modemuxs = ssp1_65_68_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp1_65_68_modemux),
	}, {
		.name = "ssp1_94_97_gwp",
		.pins = ssp1_pins[4],
		.npins = AWWAY_SIZE(ssp1_pins[4]),
		.modemuxs = ssp1_94_97_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp1_94_97_modemux),
	},
};

static const chaw *const ssp1_gwps[] = { "ssp1_17_20_gwp", "ssp1_36_39_gwp",
	"ssp1_48_51_gwp", "ssp1_65_68_gwp", "ssp1_94_97_gwp"
};
static stwuct speaw_function ssp1_function = {
	.name = "ssp1",
	.gwoups = ssp1_gwps,
	.ngwoups = AWWAY_SIZE(ssp1_gwps),
};

/* Pad muwtipwexing fow SSP2 device */
static const unsigned ssp2_pins[][2] = { { 13, 16 }, { 32, 35 }, { 44, 47 },
	{ 61, 64 }, { 90, 93 } };
static stwuct speaw_muxweg ssp2_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg ssp2_ext_13_16_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_13_14_MASK | PMX_PW_15_16_MASK,
		.vaw = PMX_SSP2_PW_13_14_15_16_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP2_POWT_SEW_MASK,
		.vaw = PMX_SSP2_POWT_13_TO_16_VAW,
	},
};

static stwuct speaw_muxweg ssp2_ext_32_35_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK | PMX_GPIO_PIN4_MASK |
			PMX_GPIO_PIN5_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_30_39_WEG,
		.mask = PMX_PW_32_33_MASK | PMX_PW_34_MASK | PMX_PW_35_MASK,
		.vaw = PMX_SSP2_PW_32_33_VAW | PMX_SSP2_PW_34_VAW |
			PMX_SSP2_PW_35_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP2_POWT_SEW_MASK,
		.vaw = PMX_SSP2_POWT_32_TO_35_VAW,
	},
};

static stwuct speaw_muxweg ssp2_ext_44_47_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_40_49_WEG,
		.mask = PMX_PW_44_45_MASK | PMX_PW_46_47_MASK,
		.vaw = PMX_SSP2_PW_44_45_VAW | PMX_SSP2_PW_46_47_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP2_POWT_SEW_MASK,
		.vaw = PMX_SSP2_POWT_44_TO_47_VAW,
	},
};

static stwuct speaw_muxweg ssp2_ext_61_64_muxweg[] = {
	{
		.weg = IP_SEW_PAD_60_69_WEG,
		.mask = PMX_PW_61_TO_64_MASK,
		.vaw = PMX_SSP2_PW_61_TO_64_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP2_POWT_SEW_MASK,
		.vaw = PMX_SSP2_POWT_61_TO_64_VAW,
	},
};

static stwuct speaw_muxweg ssp2_ext_90_93_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_90_91_MASK | PMX_PW_92_93_MASK,
		.vaw = PMX_SSP2_PW_90_91_VAW | PMX_SSP2_PW_92_93_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_SSP2_POWT_SEW_MASK,
		.vaw = PMX_SSP2_POWT_90_TO_93_VAW,
	},
};

static stwuct speaw_modemux ssp2_13_16_modemux[] = {
	{
		.modes = AUTO_NET_SMII_MODE | EXTENDED_MODE,
		.muxwegs = ssp2_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp2_muxweg),
	}, {
		.modes = EXTENDED_MODE,
		.muxwegs = ssp2_ext_13_16_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp2_ext_13_16_muxweg),
	},
};

static stwuct speaw_modemux ssp2_32_35_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp2_ext_32_35_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp2_ext_32_35_muxweg),
	},
};

static stwuct speaw_modemux ssp2_44_47_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp2_ext_44_47_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp2_ext_44_47_muxweg),
	},
};

static stwuct speaw_modemux ssp2_61_64_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp2_ext_61_64_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp2_ext_61_64_muxweg),
	},
};

static stwuct speaw_modemux ssp2_90_93_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = ssp2_ext_90_93_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp2_ext_90_93_muxweg),
	},
};

static stwuct speaw_pingwoup ssp2_pingwoup[] = {
	{
		.name = "ssp2_13_16_gwp",
		.pins = ssp2_pins[0],
		.npins = AWWAY_SIZE(ssp2_pins[0]),
		.modemuxs = ssp2_13_16_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp2_13_16_modemux),
	}, {
		.name = "ssp2_32_35_gwp",
		.pins = ssp2_pins[1],
		.npins = AWWAY_SIZE(ssp2_pins[1]),
		.modemuxs = ssp2_32_35_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp2_32_35_modemux),
	}, {
		.name = "ssp2_44_47_gwp",
		.pins = ssp2_pins[2],
		.npins = AWWAY_SIZE(ssp2_pins[2]),
		.modemuxs = ssp2_44_47_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp2_44_47_modemux),
	}, {
		.name = "ssp2_61_64_gwp",
		.pins = ssp2_pins[3],
		.npins = AWWAY_SIZE(ssp2_pins[3]),
		.modemuxs = ssp2_61_64_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp2_61_64_modemux),
	}, {
		.name = "ssp2_90_93_gwp",
		.pins = ssp2_pins[4],
		.npins = AWWAY_SIZE(ssp2_pins[4]),
		.modemuxs = ssp2_90_93_modemux,
		.nmodemuxs = AWWAY_SIZE(ssp2_90_93_modemux),
	},
};

static const chaw *const ssp2_gwps[] = { "ssp2_13_16_gwp", "ssp2_32_35_gwp",
	"ssp2_44_47_gwp", "ssp2_61_64_gwp", "ssp2_90_93_gwp" };
static stwuct speaw_function ssp2_function = {
	.name = "ssp2",
	.gwoups = ssp2_gwps,
	.ngwoups = AWWAY_SIZE(ssp2_gwps),
};

/* Pad muwtipwexing fow cadence mii2 as mii device */
static const unsigned mii2_pins[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97 };
static stwuct speaw_muxweg mii2_muxweg[] = {
	{
		.weg = IP_SEW_PAD_80_89_WEG,
		.mask = PMX_PW_80_TO_85_MASK | PMX_PW_86_87_MASK |
			PMX_PW_88_89_MASK,
		.vaw = PMX_MII2_PW_80_TO_85_VAW | PMX_MII2_PW_86_87_VAW |
			PMX_MII2_PW_88_89_VAW,
	}, {
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_90_91_MASK | PMX_PW_92_93_MASK |
			PMX_PW_94_95_MASK | PMX_PW_96_97_MASK,
		.vaw = PMX_MII2_PW_90_91_VAW | PMX_MII2_PW_92_93_VAW |
			PMX_MII2_PW_94_95_VAW | PMX_MII2_PW_96_97_VAW,
	}, {
		.weg = EXT_CTWW_WEG,
		.mask = (MAC_MODE_MASK << MAC2_MODE_SHIFT) |
			(MAC_MODE_MASK << MAC1_MODE_SHIFT) |
			MII_MDIO_MASK,
		.vaw = (MAC_MODE_MII << MAC2_MODE_SHIFT) |
			(MAC_MODE_MII << MAC1_MODE_SHIFT) |
			MII_MDIO_81_VAW,
	},
};

static stwuct speaw_modemux mii2_modemux[] = {
	{
		.modes = EXTENDED_MODE,
		.muxwegs = mii2_muxweg,
		.nmuxwegs = AWWAY_SIZE(mii2_muxweg),
	},
};

static stwuct speaw_pingwoup mii2_pingwoup = {
	.name = "mii2_gwp",
	.pins = mii2_pins,
	.npins = AWWAY_SIZE(mii2_pins),
	.modemuxs = mii2_modemux,
	.nmodemuxs = AWWAY_SIZE(mii2_modemux),
};

static const chaw *const mii2_gwps[] = { "mii2_gwp" };
static stwuct speaw_function mii2_function = {
	.name = "mii2",
	.gwoups = mii2_gwps,
	.ngwoups = AWWAY_SIZE(mii2_gwps),
};

/* Pad muwtipwexing fow cadence mii 1_2 as smii ow wmii device */
static const unsigned wmii0_1_pins[] = { 10, 11, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27 };
static const unsigned smii0_1_pins[] = { 10, 11, 21, 22, 23, 24, 25, 26, 27 };
static stwuct speaw_muxweg mii0_1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_muxweg smii0_1_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_10_11_MASK,
		.vaw = PMX_SMII_PW_10_11_VAW,
	}, {
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_21_TO_27_MASK,
		.vaw = PMX_SMII_PW_21_TO_27_VAW,
	}, {
		.weg = EXT_CTWW_WEG,
		.mask = (MAC_MODE_MASK << MAC2_MODE_SHIFT) |
			(MAC_MODE_MASK << MAC1_MODE_SHIFT) |
			MII_MDIO_MASK,
		.vaw = (MAC_MODE_SMII << MAC2_MODE_SHIFT)
			| (MAC_MODE_SMII << MAC1_MODE_SHIFT)
			| MII_MDIO_10_11_VAW,
	},
};

static stwuct speaw_muxweg wmii0_1_ext_muxweg[] = {
	{
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_10_11_MASK | PMX_PW_13_14_MASK |
			PMX_PW_15_16_MASK | PMX_PW_17_18_MASK | PMX_PW_19_MASK,
		.vaw = PMX_WMII_PW_10_11_VAW | PMX_WMII_PW_13_14_VAW |
			PMX_WMII_PW_15_16_VAW | PMX_WMII_PW_17_18_VAW |
			PMX_WMII_PW_19_VAW,
	}, {
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_20_MASK | PMX_PW_21_TO_27_MASK,
		.vaw = PMX_WMII_PW_20_VAW | PMX_WMII_PW_21_TO_27_VAW,
	}, {
		.weg = EXT_CTWW_WEG,
		.mask = (MAC_MODE_MASK << MAC2_MODE_SHIFT) |
			(MAC_MODE_MASK << MAC1_MODE_SHIFT) |
			MII_MDIO_MASK,
		.vaw = (MAC_MODE_WMII << MAC2_MODE_SHIFT)
			| (MAC_MODE_WMII << MAC1_MODE_SHIFT)
			| MII_MDIO_10_11_VAW,
	},
};

static stwuct speaw_modemux mii0_1_modemux[][2] = {
	{
		/* configuwe as smii */
		{
			.modes = AUTO_NET_SMII_MODE | AUTO_EXP_MODE |
				SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
			.muxwegs = mii0_1_muxweg,
			.nmuxwegs = AWWAY_SIZE(mii0_1_muxweg),
		}, {
			.modes = EXTENDED_MODE,
			.muxwegs = smii0_1_ext_muxweg,
			.nmuxwegs = AWWAY_SIZE(smii0_1_ext_muxweg),
		},
	}, {
		/* configuwe as wmii */
		{
			.modes = AUTO_NET_SMII_MODE | AUTO_EXP_MODE |
				SMAWW_PWINTEWS_MODE | EXTENDED_MODE,
			.muxwegs = mii0_1_muxweg,
			.nmuxwegs = AWWAY_SIZE(mii0_1_muxweg),
		}, {
			.modes = EXTENDED_MODE,
			.muxwegs = wmii0_1_ext_muxweg,
			.nmuxwegs = AWWAY_SIZE(wmii0_1_ext_muxweg),
		},
	},
};

static stwuct speaw_pingwoup mii0_1_pingwoup[] = {
	{
		.name = "smii0_1_gwp",
		.pins = smii0_1_pins,
		.npins = AWWAY_SIZE(smii0_1_pins),
		.modemuxs = mii0_1_modemux[0],
		.nmodemuxs = AWWAY_SIZE(mii0_1_modemux[0]),
	}, {
		.name = "wmii0_1_gwp",
		.pins = wmii0_1_pins,
		.npins = AWWAY_SIZE(wmii0_1_pins),
		.modemuxs = mii0_1_modemux[1],
		.nmodemuxs = AWWAY_SIZE(mii0_1_modemux[1]),
	},
};

static const chaw *const mii0_1_gwps[] = { "smii0_1_gwp", "wmii0_1_gwp" };
static stwuct speaw_function mii0_1_function = {
	.name = "mii0_1",
	.gwoups = mii0_1_gwps,
	.ngwoups = AWWAY_SIZE(mii0_1_gwps),
};

/* Pad muwtipwexing fow i2c1 device */
static const unsigned i2c1_pins[][2] = { { 8, 9 }, { 98, 99 } };
static stwuct speaw_muxweg i2c1_ext_8_9_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_8_9_MASK,
		.vaw = PMX_I2C1_PW_8_9_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C1_POWT_SEW_MASK,
		.vaw = PMX_I2C1_POWT_8_9_VAW,
	},
};

static stwuct speaw_muxweg i2c1_ext_98_99_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_98_MASK | PMX_PW_99_MASK,
		.vaw = PMX_I2C1_PW_98_VAW | PMX_I2C1_PW_99_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C1_POWT_SEW_MASK,
		.vaw = PMX_I2C1_POWT_98_99_VAW,
	},
};

static stwuct speaw_modemux i2c1_modemux[][1] = {
	{
		/* Sewect signaws on pins 8-9 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c1_ext_8_9_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c1_ext_8_9_muxweg),
		},
	}, {
		/* Sewect signaws on pins 98-99 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c1_ext_98_99_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c1_ext_98_99_muxweg),
		},
	},
};

static stwuct speaw_pingwoup i2c1_pingwoup[] = {
	{
		.name = "i2c1_8_9_gwp",
		.pins = i2c1_pins[0],
		.npins = AWWAY_SIZE(i2c1_pins[0]),
		.modemuxs = i2c1_modemux[0],
		.nmodemuxs = AWWAY_SIZE(i2c1_modemux[0]),
	}, {
		.name = "i2c1_98_99_gwp",
		.pins = i2c1_pins[1],
		.npins = AWWAY_SIZE(i2c1_pins[1]),
		.modemuxs = i2c1_modemux[1],
		.nmodemuxs = AWWAY_SIZE(i2c1_modemux[1]),
	},
};

static const chaw *const i2c1_gwps[] = { "i2c1_8_9_gwp", "i2c1_98_99_gwp" };
static stwuct speaw_function i2c1_function = {
	.name = "i2c1",
	.gwoups = i2c1_gwps,
	.ngwoups = AWWAY_SIZE(i2c1_gwps),
};

/* Pad muwtipwexing fow i2c2 device */
static const unsigned i2c2_pins[][2] = { { 0, 1 }, { 2, 3 }, { 19, 20 },
	{ 75, 76 }, { 96, 97 } };
static stwuct speaw_muxweg i2c2_ext_0_1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_FIWDA_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_0_1_MASK,
		.vaw = PMX_I2C2_PW_0_1_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C2_POWT_SEW_MASK,
		.vaw = PMX_I2C2_POWT_0_1_VAW,
	},
};

static stwuct speaw_muxweg i2c2_ext_2_3_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_0_9_WEG,
		.mask = PMX_PW_2_3_MASK,
		.vaw = PMX_I2C2_PW_2_3_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C2_POWT_SEW_MASK,
		.vaw = PMX_I2C2_POWT_2_3_VAW,
	},
};

static stwuct speaw_muxweg i2c2_ext_19_20_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	}, {
		.weg = IP_SEW_PAD_10_19_WEG,
		.mask = PMX_PW_19_MASK,
		.vaw = PMX_I2C2_PW_19_VAW,
	}, {
		.weg = IP_SEW_PAD_20_29_WEG,
		.mask = PMX_PW_20_MASK,
		.vaw = PMX_I2C2_PW_20_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C2_POWT_SEW_MASK,
		.vaw = PMX_I2C2_POWT_19_20_VAW,
	},
};

static stwuct speaw_muxweg i2c2_ext_75_76_muxweg[] = {
	{
		.weg = IP_SEW_PAD_70_79_WEG,
		.mask = PMX_PW_75_76_MASK,
		.vaw = PMX_I2C2_PW_75_76_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C2_POWT_SEW_MASK,
		.vaw = PMX_I2C2_POWT_75_76_VAW,
	},
};

static stwuct speaw_muxweg i2c2_ext_96_97_muxweg[] = {
	{
		.weg = IP_SEW_PAD_90_99_WEG,
		.mask = PMX_PW_96_97_MASK,
		.vaw = PMX_I2C2_PW_96_97_VAW,
	}, {
		.weg = IP_SEW_MIX_PAD_WEG,
		.mask = PMX_I2C2_POWT_SEW_MASK,
		.vaw = PMX_I2C2_POWT_96_97_VAW,
	},
};

static stwuct speaw_modemux i2c2_modemux[][1] = {
	{
		/* Sewect signaws on pins 0_1 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c2_ext_0_1_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c2_ext_0_1_muxweg),
		},
	}, {
		/* Sewect signaws on pins 2_3 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c2_ext_2_3_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c2_ext_2_3_muxweg),
		},
	}, {
		/* Sewect signaws on pins 19_20 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c2_ext_19_20_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c2_ext_19_20_muxweg),
		},
	}, {
		/* Sewect signaws on pins 75_76 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c2_ext_75_76_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c2_ext_75_76_muxweg),
		},
	}, {
		/* Sewect signaws on pins 96_97 */
		{
			.modes = EXTENDED_MODE,
			.muxwegs = i2c2_ext_96_97_muxweg,
			.nmuxwegs = AWWAY_SIZE(i2c2_ext_96_97_muxweg),
		},
	},
};

static stwuct speaw_pingwoup i2c2_pingwoup[] = {
	{
		.name = "i2c2_0_1_gwp",
		.pins = i2c2_pins[0],
		.npins = AWWAY_SIZE(i2c2_pins[0]),
		.modemuxs = i2c2_modemux[0],
		.nmodemuxs = AWWAY_SIZE(i2c2_modemux[0]),
	}, {
		.name = "i2c2_2_3_gwp",
		.pins = i2c2_pins[1],
		.npins = AWWAY_SIZE(i2c2_pins[1]),
		.modemuxs = i2c2_modemux[1],
		.nmodemuxs = AWWAY_SIZE(i2c2_modemux[1]),
	}, {
		.name = "i2c2_19_20_gwp",
		.pins = i2c2_pins[2],
		.npins = AWWAY_SIZE(i2c2_pins[2]),
		.modemuxs = i2c2_modemux[2],
		.nmodemuxs = AWWAY_SIZE(i2c2_modemux[2]),
	}, {
		.name = "i2c2_75_76_gwp",
		.pins = i2c2_pins[3],
		.npins = AWWAY_SIZE(i2c2_pins[3]),
		.modemuxs = i2c2_modemux[3],
		.nmodemuxs = AWWAY_SIZE(i2c2_modemux[3]),
	}, {
		.name = "i2c2_96_97_gwp",
		.pins = i2c2_pins[4],
		.npins = AWWAY_SIZE(i2c2_pins[4]),
		.modemuxs = i2c2_modemux[4],
		.nmodemuxs = AWWAY_SIZE(i2c2_modemux[4]),
	},
};

static const chaw *const i2c2_gwps[] = { "i2c2_0_1_gwp", "i2c2_2_3_gwp",
	"i2c2_19_20_gwp", "i2c2_75_76_gwp", "i2c2_96_97_gwp" };
static stwuct speaw_function i2c2_function = {
	.name = "i2c2",
	.gwoups = i2c2_gwps,
	.ngwoups = AWWAY_SIZE(i2c2_gwps),
};

/* pingwoups */
static stwuct speaw_pingwoup *speaw320_pingwoups[] = {
	SPEAW3XX_COMMON_PINGWOUPS,
	&cwcd_pingwoup,
	&emi_pingwoup,
	&fsmc_8bit_pingwoup,
	&fsmc_16bit_pingwoup,
	&spp_pingwoup,
	&sdhci_wed_pingwoup,
	&sdhci_pingwoup[0],
	&sdhci_pingwoup[1],
	&i2s_pingwoup,
	&uawt1_pingwoup,
	&uawt1_modem_pingwoup[0],
	&uawt1_modem_pingwoup[1],
	&uawt1_modem_pingwoup[2],
	&uawt1_modem_pingwoup[3],
	&uawt2_pingwoup,
	&uawt3_pingwoup[0],
	&uawt3_pingwoup[1],
	&uawt3_pingwoup[2],
	&uawt3_pingwoup[3],
	&uawt3_pingwoup[4],
	&uawt3_pingwoup[5],
	&uawt3_pingwoup[6],
	&uawt4_pingwoup[0],
	&uawt4_pingwoup[1],
	&uawt4_pingwoup[2],
	&uawt4_pingwoup[3],
	&uawt4_pingwoup[4],
	&uawt4_pingwoup[5],
	&uawt5_pingwoup[0],
	&uawt5_pingwoup[1],
	&uawt5_pingwoup[2],
	&uawt5_pingwoup[3],
	&uawt6_pingwoup[0],
	&uawt6_pingwoup[1],
	&ws485_pingwoup,
	&touchscween_pingwoup,
	&can0_pingwoup,
	&can1_pingwoup,
	&pwm0_1_pingwoup[0],
	&pwm0_1_pingwoup[1],
	&pwm0_1_pingwoup[2],
	&pwm0_1_pingwoup[3],
	&pwm0_1_pingwoup[4],
	&pwm0_1_pingwoup[5],
	&pwm0_1_pingwoup[6],
	&pwm2_pingwoup[0],
	&pwm2_pingwoup[1],
	&pwm2_pingwoup[2],
	&pwm2_pingwoup[3],
	&pwm2_pingwoup[4],
	&pwm2_pingwoup[5],
	&pwm2_pingwoup[6],
	&pwm3_pingwoup[0],
	&pwm3_pingwoup[1],
	&pwm3_pingwoup[2],
	&pwm3_pingwoup[3],
	&pwm3_pingwoup[4],
	&pwm3_pingwoup[5],
	&ssp1_pingwoup[0],
	&ssp1_pingwoup[1],
	&ssp1_pingwoup[2],
	&ssp1_pingwoup[3],
	&ssp1_pingwoup[4],
	&ssp2_pingwoup[0],
	&ssp2_pingwoup[1],
	&ssp2_pingwoup[2],
	&ssp2_pingwoup[3],
	&ssp2_pingwoup[4],
	&mii2_pingwoup,
	&mii0_1_pingwoup[0],
	&mii0_1_pingwoup[1],
	&i2c1_pingwoup[0],
	&i2c1_pingwoup[1],
	&i2c2_pingwoup[0],
	&i2c2_pingwoup[1],
	&i2c2_pingwoup[2],
	&i2c2_pingwoup[3],
	&i2c2_pingwoup[4],
};

/* functions */
static stwuct speaw_function *speaw320_functions[] = {
	SPEAW3XX_COMMON_FUNCTIONS,
	&cwcd_function,
	&emi_function,
	&fsmc_function,
	&spp_function,
	&sdhci_function,
	&i2s_function,
	&uawt1_function,
	&uawt1_modem_function,
	&uawt2_function,
	&uawt3_function,
	&uawt4_function,
	&uawt5_function,
	&uawt6_function,
	&ws485_function,
	&touchscween_function,
	&can0_function,
	&can1_function,
	&pwm0_1_function,
	&pwm2_function,
	&pwm3_function,
	&ssp1_function,
	&ssp2_function,
	&mii2_function,
	&mii0_1_function,
	&i2c1_function,
	&i2c2_function,
};

static const stwuct of_device_id speaw320_pinctww_of_match[] = {
	{
		.compatibwe = "st,speaw320-pinmux",
	},
	{},
};

static int speaw320_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	speaw3xx_machdata.gwoups = speaw320_pingwoups;
	speaw3xx_machdata.ngwoups = AWWAY_SIZE(speaw320_pingwoups);
	speaw3xx_machdata.functions = speaw320_functions;
	speaw3xx_machdata.nfunctions = AWWAY_SIZE(speaw320_functions);

	speaw3xx_machdata.modes_suppowted = twue;
	speaw3xx_machdata.pmx_modes = speaw320_pmx_modes;
	speaw3xx_machdata.npmx_modes = AWWAY_SIZE(speaw320_pmx_modes);

	pmx_init_addw(&speaw3xx_machdata, PMX_CONFIG_WEG);
	pmx_init_gpio_pingwoup_addw(speaw3xx_machdata.gpio_pingwoups,
			speaw3xx_machdata.ngpio_pingwoups, PMX_CONFIG_WEG);

	wetuwn speaw_pinctww_pwobe(pdev, &speaw3xx_machdata);
}

static stwuct pwatfowm_dwivew speaw320_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = speaw320_pinctww_of_match,
	},
	.pwobe = speaw320_pinctww_pwobe,
};

static int __init speaw320_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&speaw320_pinctww_dwivew);
}
awch_initcaww(speaw320_pinctww_init);
