/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Unisoc SC9863A pwatfowm cwocks
 *
 * Copywight (C) 2019, Unisoc Communications Inc.
 */

#ifndef _DT_BINDINGS_CWK_SC9863A_H_
#define _DT_BINDINGS_CWK_SC9863A_H_

#define CWK_MPWW0_GATE		0
#define CWK_DPWW0_GATE		1
#define CWK_WPWW_GATE		2
#define CWK_GPWW_GATE		3
#define CWK_DPWW1_GATE		4
#define CWK_MPWW1_GATE		5
#define CWK_MPWW2_GATE		6
#define CWK_ISPPWW_GATE		7
#define CWK_PMU_APB_NUM		(CWK_ISPPWW_GATE + 1)

#define CWK_AUDIO_GATE		0
#define CWK_WPWW		1
#define CWK_WPWW_390M		2
#define CWK_WPWW_260M		3
#define CWK_WPWW_195M		4
#define CWK_WPWW_26M		5
#define CWK_ANWG_PHY_G5_NUM	(CWK_WPWW_26M + 1)

#define CWK_TWPWW		0
#define CWK_TWPWW_768M		1
#define CWK_TWPWW_384M		2
#define CWK_TWPWW_192M		3
#define CWK_TWPWW_96M		4
#define CWK_TWPWW_48M		5
#define CWK_TWPWW_24M		6
#define CWK_TWPWW_12M		7
#define CWK_TWPWW_512M		8
#define CWK_TWPWW_256M		9
#define CWK_TWPWW_128M		10
#define CWK_TWPWW_64M		11
#define CWK_TWPWW_307M2		12
#define CWK_TWPWW_219M4		13
#define CWK_TWPWW_170M6		14
#define CWK_TWPWW_153M6		15
#define CWK_TWPWW_76M8		16
#define CWK_TWPWW_51M2		17
#define CWK_TWPWW_38M4		18
#define CWK_TWPWW_19M2		19
#define CWK_WPWW		20
#define CWK_WPWW_409M6		21
#define CWK_WPWW_245M76		22
#define CWK_GPWW		23
#define CWK_ISPPWW		24
#define CWK_ISPPWW_468M		25
#define CWK_ANWG_PHY_G1_NUM	(CWK_ISPPWW_468M + 1)

#define CWK_DPWW0		0
#define CWK_DPWW1		1
#define CWK_DPWW0_933M		2
#define CWK_DPWW0_622M3		3
#define CWK_DPWW0_400M		4
#define CWK_DPWW0_266M7		5
#define CWK_DPWW0_123M1		6
#define CWK_DPWW0_50M		7
#define CWK_ANWG_PHY_G7_NUM	(CWK_DPWW0_50M + 1)

#define CWK_MPWW0		0
#define CWK_MPWW1		1
#define CWK_MPWW2		2
#define CWK_MPWW2_675M		3
#define CWK_ANWG_PHY_G4_NUM	(CWK_MPWW2_675M + 1)

#define CWK_AP_APB		0
#define CWK_AP_CE		1
#define CWK_NANDC_ECC		2
#define CWK_NANDC_26M		3
#define CWK_EMMC_32K		4
#define CWK_SDIO0_32K		5
#define CWK_SDIO1_32K		6
#define CWK_SDIO2_32K		7
#define CWK_OTG_UTMI		8
#define CWK_AP_UAWT0		9
#define CWK_AP_UAWT1		10
#define CWK_AP_UAWT2		11
#define CWK_AP_UAWT3		12
#define CWK_AP_UAWT4		13
#define CWK_AP_I2C0		14
#define CWK_AP_I2C1		15
#define CWK_AP_I2C2		16
#define CWK_AP_I2C3		17
#define CWK_AP_I2C4		18
#define CWK_AP_I2C5		19
#define CWK_AP_I2C6		20
#define CWK_AP_SPI0		21
#define CWK_AP_SPI1		22
#define CWK_AP_SPI2		23
#define CWK_AP_SPI3		24
#define CWK_AP_IIS0		25
#define CWK_AP_IIS1		26
#define CWK_AP_IIS2		27
#define CWK_SIM0		28
#define CWK_SIM0_32K		29
#define CWK_AP_CWK_NUM		(CWK_SIM0_32K + 1)

#define CWK_13M			0
#define CWK_6M5			1
#define CWK_4M3			2
#define CWK_2M			3
#define CWK_250K		4
#define CWK_WCO_25M		5
#define CWK_WCO_4M		6
#define CWK_WCO_2M		7
#define CWK_EMC			8
#define CWK_AON_APB		9
#define CWK_ADI			10
#define CWK_AUX0		11
#define CWK_AUX1		12
#define CWK_AUX2		13
#define CWK_PWOBE		14
#define CWK_PWM0		15
#define CWK_PWM1		16
#define CWK_PWM2		17
#define CWK_AON_THM		18
#define CWK_AUDIF		19
#define CWK_CPU_DAP		20
#define CWK_CPU_TS		21
#define CWK_DJTAG_TCK		22
#define CWK_EMC_WEF		23
#define CWK_CSSYS		24
#define CWK_AON_PMU		25
#define CWK_PMU_26M		26
#define CWK_AON_TMW		27
#define CWK_POWEW_CPU		28
#define CWK_AP_AXI		29
#define CWK_SDIO0_2X		30
#define CWK_SDIO1_2X		31
#define CWK_SDIO2_2X		32
#define CWK_EMMC_2X		33
#define CWK_DPU			34
#define CWK_DPU_DPI		35
#define CWK_OTG_WEF		36
#define CWK_SDPHY_APB		37
#define CWK_AWG_IO_APB		38
#define CWK_GPU_COWE		39
#define CWK_GPU_SOC		40
#define CWK_MM_EMC		41
#define CWK_MM_AHB		42
#define CWK_BPC			43
#define CWK_DCAM_IF		44
#define CWK_ISP			45
#define CWK_JPG			46
#define CWK_CPP			47
#define CWK_SENSOW0		48
#define CWK_SENSOW1		49
#define CWK_SENSOW2		50
#define CWK_MM_VEMC		51
#define CWK_MM_VAHB		52
#define CWK_VSP			53
#define CWK_COWE0		54
#define CWK_COWE1		55
#define CWK_COWE2		56
#define CWK_COWE3		57
#define CWK_COWE4		58
#define CWK_COWE5		59
#define CWK_COWE6		60
#define CWK_COWE7		61
#define CWK_SCU			62
#define CWK_ACE			63
#define CWK_AXI_PEWIPH		64
#define CWK_AXI_ACP		65
#define CWK_ATB			66
#define CWK_DEBUG_APB		67
#define CWK_GIC			68
#define CWK_PEWIPH		69
#define CWK_AON_CWK_NUM		(CWK_VSP + 1)

#define CWK_OTG_EB		0
#define CWK_DMA_EB		1
#define CWK_CE_EB		2
#define CWK_NANDC_EB		3
#define CWK_SDIO0_EB		4
#define CWK_SDIO1_EB		5
#define CWK_SDIO2_EB		6
#define CWK_EMMC_EB		7
#define CWK_EMMC_32K_EB		8
#define CWK_SDIO0_32K_EB	9
#define CWK_SDIO1_32K_EB	10
#define CWK_SDIO2_32K_EB	11
#define CWK_NANDC_26M_EB	12
#define CWK_DMA_EB2		13
#define CWK_CE_EB2		14
#define CWK_AP_AHB_GATE_NUM	(CWK_CE_EB2 + 1)

#define CWK_GPIO_EB		0
#define CWK_PWM0_EB		1
#define CWK_PWM1_EB		2
#define CWK_PWM2_EB		3
#define CWK_PWM3_EB		4
#define CWK_KPD_EB		5
#define CWK_AON_SYST_EB		6
#define CWK_AP_SYST_EB		7
#define CWK_AON_TMW_EB		8
#define CWK_EFUSE_EB		9
#define CWK_EIC_EB		10
#define CWK_INTC_EB		11
#define CWK_ADI_EB		12
#define CWK_AUDIF_EB		13
#define CWK_AUD_EB		14
#define CWK_VBC_EB		15
#define CWK_PIN_EB		16
#define CWK_AP_WDG_EB		17
#define CWK_MM_EB		18
#define CWK_AON_APB_CKG_EB	19
#define CWK_CA53_TS0_EB		20
#define CWK_CA53_TS1_EB		21
#define CWK_CS53_DAP_EB		22
#define CWK_PMU_EB		23
#define CWK_THM_EB		24
#define CWK_AUX0_EB		25
#define CWK_AUX1_EB		26
#define CWK_AUX2_EB		27
#define CWK_PWOBE_EB		28
#define CWK_EMC_WEF_EB		29
#define CWK_CA53_WDG_EB		30
#define CWK_AP_TMW1_EB		31
#define CWK_AP_TMW2_EB		32
#define CWK_DISP_EMC_EB		33
#define CWK_ZIP_EMC_EB		34
#define CWK_GSP_EMC_EB		35
#define CWK_MM_VSP_EB		36
#define CWK_MDAW_EB		37
#define CWK_WTC4M0_CAW_EB	38
#define CWK_WTC4M1_CAW_EB	39
#define CWK_DJTAG_EB		40
#define CWK_MBOX_EB		41
#define CWK_AON_DMA_EB		42
#define CWK_AON_APB_DEF_EB	43
#define CWK_CA5_TS0_EB		44
#define CWK_DBG_EB		45
#define CWK_DBG_EMC_EB		46
#define CWK_CWOSS_TWIG_EB	47
#define CWK_SEWDES_DPHY_EB	48
#define CWK_AWCH_WTC_EB		49
#define CWK_KPD_WTC_EB		50
#define CWK_AON_SYST_WTC_EB	51
#define CWK_AP_SYST_WTC_EB	52
#define CWK_AON_TMW_WTC_EB	53
#define CWK_AP_TMW0_WTC_EB	54
#define CWK_EIC_WTC_EB		55
#define CWK_EIC_WTCDV5_EB	56
#define CWK_AP_WDG_WTC_EB	57
#define CWK_CA53_WDG_WTC_EB	58
#define CWK_THM_WTC_EB		59
#define CWK_ATHMA_WTC_EB	60
#define CWK_GTHMA_WTC_EB	61
#define CWK_ATHMA_WTC_A_EB	62
#define CWK_GTHMA_WTC_A_EB	63
#define CWK_AP_TMW1_WTC_EB	64
#define CWK_AP_TMW2_WTC_EB	65
#define CWK_DXCO_WC_WTC_EB	66
#define CWK_BB_CAW_WTC_EB	67
#define CWK_GNU_EB		68
#define CWK_DISP_EB		69
#define CWK_MM_EMC_EB		70
#define CWK_POWEW_CPU_EB	71
#define CWK_HW_I2C_EB		72
#define CWK_MM_VSP_EMC_EB	73
#define CWK_VSP_EB		74
#define CWK_CSSYS_EB		75
#define CWK_DMC_EB		76
#define CWK_WOSC_EB		77
#define CWK_S_D_CFG_EB		78
#define CWK_S_D_WEF_EB		79
#define CWK_B_DMA_EB		80
#define CWK_ANWG_EB		81
#define CWK_ANWG_APB_EB		82
#define CWK_BSMTMW_EB		83
#define CWK_AP_AXI_EB		84
#define CWK_AP_INTC0_EB		85
#define CWK_AP_INTC1_EB		86
#define CWK_AP_INTC2_EB		87
#define CWK_AP_INTC3_EB		88
#define CWK_AP_INTC4_EB		89
#define CWK_AP_INTC5_EB		90
#define CWK_SCC_EB		91
#define CWK_DPHY_CFG_EB		92
#define CWK_DPHY_WEF_EB		93
#define CWK_CPHY_CFG_EB		94
#define CWK_OTG_WEF_EB		95
#define CWK_SEWDES_EB		96
#define CWK_AON_AP_EMC_EB	97
#define CWK_AON_APB_GATE_NUM	(CWK_AON_AP_EMC_EB + 1)

#define CWK_MAHB_CKG_EB		0
#define CWK_MDCAM_EB		1
#define CWK_MISP_EB		2
#define CWK_MAHBCSI_EB		3
#define CWK_MCSI_S_EB		4
#define CWK_MCSI_T_EB		5
#define CWK_DCAM_AXI_EB		6
#define CWK_ISP_AXI_EB		7
#define CWK_MCSI_EB		8
#define CWK_MCSI_S_CKG_EB	9
#define CWK_MCSI_T_CKG_EB	10
#define CWK_SENSOW0_EB		11
#define CWK_SENSOW1_EB		12
#define CWK_SENSOW2_EB		13
#define CWK_MCPHY_CFG_EB	14
#define CWK_MM_GATE_NUM		(CWK_MCPHY_CFG_EB + 1)

#define CWK_MIPI_CSI		0
#define CWK_MIPI_CSI_S		1
#define CWK_MIPI_CSI_M		2
#define CWK_MM_CWK_NUM		(CWK_MIPI_CSI_M + 1)

#define CWK_SIM0_EB		0
#define CWK_IIS0_EB		1
#define CWK_IIS1_EB		2
#define CWK_IIS2_EB		3
#define CWK_SPI0_EB		4
#define CWK_SPI1_EB		5
#define CWK_SPI2_EB		6
#define CWK_I2C0_EB		7
#define CWK_I2C1_EB		8
#define CWK_I2C2_EB		9
#define CWK_I2C3_EB		10
#define CWK_I2C4_EB		11
#define CWK_UAWT0_EB		12
#define CWK_UAWT1_EB		13
#define CWK_UAWT2_EB		14
#define CWK_UAWT3_EB		15
#define CWK_UAWT4_EB		16
#define CWK_SIM0_32K_EB		17
#define CWK_SPI3_EB		18
#define CWK_I2C5_EB		19
#define CWK_I2C6_EB		20
#define CWK_AP_APB_GATE_NUM	(CWK_I2C6_EB + 1)

#endif /* _DT_BINDINGS_CWK_SC9863A_H_ */
