/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * Unisoc UMS512 SoC DTS fiwe
 *
 * Copywight (C) 2022, Unisoc Inc.
 */

#ifndef _DT_BINDINGS_CWK_UMS512_H_
#define _DT_BINDINGS_CWK_UMS512_H_

#define CWK_26M_AUD			0
#define CWK_13M				1
#define CWK_6M5				2
#define CWK_4M3				3
#define CWK_2M				4
#define CWK_1M				5
#define CWK_250K			6
#define CWK_WCO_25M			7
#define CWK_WCO_4M			8
#define CWK_WCO_2M			9
#define CWK_ISPPWW_GATE			10
#define CWK_DPWW0_GATE			11
#define CWK_DPWW1_GATE			12
#define CWK_WPWW_GATE			13
#define CWK_TWPWW_GATE			14
#define CWK_GPWW_GATE			15
#define CWK_WPWW_GATE			16
#define CWK_CPPWW_GATE			17
#define CWK_MPWW0_GATE			18
#define CWK_MPWW1_GATE			19
#define CWK_MPWW2_GATE			20
#define CWK_PMU_GATE_NUM		(CWK_MPWW2_GATE + 1)

#define CWK_DPWW0			0
#define CWK_DPWW0_58M31			1
#define CWK_ANWG_PHY_G0_NUM		(CWK_DPWW0_58M31 + 1)

#define CWK_MPWW1			0
#define CWK_MPWW1_63M38			1
#define CWK_ANWG_PHY_G2_NUM		(CWK_MPWW1_63M38 + 1)

#define CWK_WPWW			0
#define CWK_AUDIO_GATE			1
#define CWK_MPWW0			2
#define CWK_MPWW0_56M88			3
#define CWK_MPWW2			4
#define CWK_MPWW2_47M13			5
#define CWK_ANWG_PHY_G3_NUM		(CWK_MPWW2_47M13 + 1)

#define CWK_TWPWW			0
#define CWK_TWPWW_768M			1
#define CWK_TWPWW_384M			2
#define CWK_TWPWW_192M			3
#define CWK_TWPWW_96M			4
#define CWK_TWPWW_48M			5
#define CWK_TWPWW_24M			6
#define CWK_TWPWW_12M			7
#define CWK_TWPWW_512M			8
#define CWK_TWPWW_256M			9
#define CWK_TWPWW_128M			10
#define CWK_TWPWW_64M			11
#define CWK_TWPWW_307M2			12
#define CWK_TWPWW_219M4			13
#define CWK_TWPWW_170M6			14
#define CWK_TWPWW_153M6			15
#define CWK_TWPWW_76M8			16
#define CWK_TWPWW_51M2			17
#define CWK_TWPWW_38M4			18
#define CWK_TWPWW_19M2			19
#define CWK_TWPWW_12M29			20
#define CWK_WPWW			21
#define CWK_WPWW_614M4			22
#define CWK_WPWW_409M6			23
#define CWK_WPWW_245M76			24
#define CWK_WPWW_30M72			25
#define CWK_ISPPWW			26
#define CWK_ISPPWW_468M			27
#define CWK_ISPPWW_78M			28
#define CWK_GPWW			29
#define CWK_GPWW_40M			30
#define CWK_CPPWW			31
#define CWK_CPPWW_39M32			32
#define CWK_ANWG_PHY_GC_NUM		(CWK_CPPWW_39M32 + 1)

#define CWK_AP_APB			0
#define CWK_IPI			        1
#define CWK_AP_UAWT0			2
#define CWK_AP_UAWT1			3
#define CWK_AP_UAWT2			4
#define CWK_AP_I2C0			5
#define CWK_AP_I2C1			6
#define CWK_AP_I2C2			7
#define CWK_AP_I2C3			8
#define CWK_AP_I2C4			9
#define CWK_AP_SPI0			10
#define CWK_AP_SPI1			11
#define CWK_AP_SPI2			12
#define CWK_AP_SPI3			13
#define CWK_AP_IIS0			14
#define CWK_AP_IIS1			15
#define CWK_AP_IIS2			16
#define CWK_AP_SIM			17
#define CWK_AP_CE			18
#define CWK_SDIO0_2X			19
#define CWK_SDIO1_2X			20
#define CWK_EMMC_2X			21
#define CWK_VSP				22
#define CWK_DISPC0			23
#define CWK_DISPC0_DPI			24
#define CWK_DSI_APB			25
#define CWK_DSI_WXESC			26
#define CWK_DSI_WANEBYTE		27
#define CWK_VDSP		        28
#define CWK_VDSP_M		        29
#define CWK_AP_CWK_NUM			(CWK_VDSP_M + 1)

#define CWK_DSI_EB			0
#define CWK_DISPC_EB			1
#define CWK_VSP_EB			2
#define CWK_VDMA_EB			3
#define CWK_DMA_PUB_EB			4
#define CWK_DMA_SEC_EB			5
#define CWK_IPI_EB			6
#define CWK_AHB_CKG_EB			7
#define CWK_BM_CWK_EB			8
#define CWK_AP_AHB_GATE_NUM		(CWK_BM_CWK_EB + 1)

#define CWK_AON_APB			0
#define CWK_ADI				1
#define CWK_AUX0			2
#define CWK_AUX1			3
#define CWK_AUX2			4
#define CWK_PWOBE			5
#define CWK_PWM0			6
#define CWK_PWM1			7
#define CWK_PWM2			8
#define CWK_PWM3			9
#define CWK_EFUSE			10
#define CWK_UAWT0			11
#define CWK_UAWT1			12
#define CWK_THM0			13
#define CWK_THM1			14
#define CWK_THM2			15
#define CWK_THM3			16
#define CWK_AON_I2C			17
#define CWK_AON_IIS			18
#define CWK_SCC				19
#define CWK_APCPU_DAP			20
#define CWK_APCPU_DAP_MTCK		21
#define CWK_APCPU_TS			22
#define CWK_DEBUG_TS			23
#define CWK_DSI_TEST_S			24
#define CWK_DJTAG_TCK			25
#define CWK_DJTAG_TCK_HW		26
#define CWK_AON_TMW			27
#define CWK_AON_PMU			28
#define CWK_DEBOUNCE			29
#define CWK_APCPU_PMU			30
#define CWK_TOP_DVFS			31
#define CWK_OTG_UTMI			32
#define CWK_OTG_WEF			33
#define CWK_CSSYS			34
#define CWK_CSSYS_PUB			35
#define CWK_CSSYS_APB			36
#define CWK_AP_AXI			37
#define CWK_AP_MM			38
#define CWK_SDIO2_2X			39
#define CWK_ANAWOG_IO_APB		40
#define CWK_DMC_WEF_CWK			41
#define CWK_EMC				42
#define CWK_USB				43
#define CWK_26M_PMU			44
#define CWK_AON_APB_NUM			(CWK_26M_PMU + 1)

#define CWK_MM_AHB			0
#define CWK_MM_MTX			1
#define CWK_SENSOW0			2
#define CWK_SENSOW1			3
#define CWK_SENSOW2			4
#define CWK_CPP				5
#define CWK_JPG				6
#define CWK_FD				7
#define CWK_DCAM_IF			8
#define CWK_DCAM_AXI			9
#define CWK_ISP				10
#define CWK_MIPI_CSI0			11
#define CWK_MIPI_CSI1			12
#define CWK_MIPI_CSI2			13
#define CWK_MM_CWK_NUM			(CWK_MIPI_CSI2 + 1)

#define CWK_WC100M_CAW_EB		0
#define CWK_DJTAG_TCK_EB		1
#define CWK_DJTAG_EB			2
#define CWK_AUX0_EB			3
#define CWK_AUX1_EB			4
#define CWK_AUX2_EB			5
#define CWK_PWOBE_EB			6
#define CWK_MM_EB			7
#define CWK_GPU_EB			8
#define CWK_MSPI_EB			9
#define CWK_APCPU_DAP_EB		10
#define CWK_AON_CSSYS_EB		11
#define CWK_CSSYS_APB_EB		12
#define CWK_CSSYS_PUB_EB		13
#define CWK_SDPHY_CFG_EB		14
#define CWK_SDPHY_WEF_EB		15
#define CWK_EFUSE_EB			16
#define CWK_GPIO_EB			17
#define CWK_MBOX_EB			18
#define CWK_KPD_EB			19
#define CWK_AON_SYST_EB			20
#define CWK_AP_SYST_EB			21
#define CWK_AON_TMW_EB			22
#define CWK_OTG_UTMI_EB			23
#define CWK_OTG_PHY_EB			24
#define CWK_SPWK_EB			25
#define CWK_PIN_EB			26
#define CWK_ANA_EB			27
#define CWK_APCPU_TS0_EB		28
#define CWK_APB_BUSMON_EB		29
#define CWK_AON_IIS_EB			30
#define CWK_SCC_EB			31
#define CWK_THM0_EB			32
#define CWK_THM1_EB			33
#define CWK_THM2_EB			34
#define CWK_ASIM_TOP_EB			35
#define CWK_I2C_EB			36
#define CWK_PMU_EB			37
#define CWK_ADI_EB			38
#define CWK_EIC_EB			39
#define CWK_AP_INTC0_EB			40
#define CWK_AP_INTC1_EB			41
#define CWK_AP_INTC2_EB			42
#define CWK_AP_INTC3_EB			43
#define CWK_AP_INTC4_EB			44
#define CWK_AP_INTC5_EB			45
#define CWK_AUDCP_INTC_EB		46
#define CWK_AP_TMW0_EB			47
#define CWK_AP_TMW1_EB			48
#define CWK_AP_TMW2_EB			49
#define CWK_PWM0_EB			50
#define CWK_PWM1_EB			51
#define CWK_PWM2_EB			52
#define CWK_PWM3_EB			53
#define CWK_AP_WDG_EB			54
#define CWK_APCPU_WDG_EB		55
#define CWK_SEWDES_EB			56
#define CWK_AWCH_WTC_EB			57
#define CWK_KPD_WTC_EB			58
#define CWK_AON_SYST_WTC_EB		59
#define CWK_AP_SYST_WTC_EB		60
#define CWK_AON_TMW_WTC_EB		61
#define CWK_EIC_WTC_EB			62
#define CWK_EIC_WTCDV5_EB		63
#define CWK_AP_WDG_WTC_EB		64
#define CWK_AC_WDG_WTC_EB		65
#define CWK_AP_TMW0_WTC_EB		66
#define CWK_AP_TMW1_WTC_EB		67
#define CWK_AP_TMW2_WTC_EB		68
#define CWK_DCXO_WC_WTC_EB		69
#define CWK_BB_CAW_WTC_EB		70
#define CWK_AP_EMMC_WTC_EB		71
#define CWK_AP_SDIO0_WTC_EB		72
#define CWK_AP_SDIO1_WTC_EB		73
#define CWK_AP_SDIO2_WTC_EB		74
#define CWK_DSI_CSI_TEST_EB		75
#define CWK_DJTAG_TCK_EN		76
#define CWK_DPHY_WEF_EB			77
#define CWK_DMC_WEF_EB			78
#define CWK_OTG_WEF_EB			79
#define CWK_TSEN_EB			80
#define CWK_TMW_EB			81
#define CWK_WC100M_WEF_EB		82
#define CWK_WC100M_FDK_EB		83
#define CWK_DEBOUNCE_EB			84
#define CWK_DET_32K_EB			85
#define CWK_TOP_CSSYS_EB		86
#define CWK_AP_AXI_EN			87
#define CWK_SDIO0_2X_EN			88
#define CWK_SDIO0_1X_EN			89
#define CWK_SDIO1_2X_EN			90
#define CWK_SDIO1_1X_EN			91
#define CWK_SDIO2_2X_EN			92
#define CWK_SDIO2_1X_EN			93
#define CWK_EMMC_2X_EN			94
#define CWK_EMMC_1X_EN			95
#define CWK_PWW_TEST_EN			96
#define CWK_CPHY_CFG_EN			97
#define CWK_DEBUG_TS_EN			98
#define CWK_ACCESS_AUD_EN		99
#define CWK_AON_APB_GATE_NUM		(CWK_ACCESS_AUD_EN + 1)

#define CWK_MM_CPP_EB			0
#define CWK_MM_JPG_EB			1
#define CWK_MM_DCAM_EB			2
#define CWK_MM_ISP_EB			3
#define CWK_MM_CSI2_EB			4
#define CWK_MM_CSI1_EB			5
#define CWK_MM_CSI0_EB			6
#define CWK_MM_CKG_EB			7
#define CWK_ISP_AHB_EB			8
#define CWK_MM_DVFS_EB			9
#define CWK_MM_FD_EB			10
#define CWK_MM_SENSOW2_EB		11
#define CWK_MM_SENSOW1_EB		12
#define CWK_MM_SENSOW0_EB		13
#define CWK_MM_MIPI_CSI2_EB		14
#define CWK_MM_MIPI_CSI1_EB		15
#define CWK_MM_MIPI_CSI0_EB		16
#define CWK_DCAM_AXI_EB			17
#define CWK_ISP_AXI_EB			18
#define CWK_MM_CPHY_EB			19
#define CWK_MM_GATE_CWK_NUM		(CWK_MM_CPHY_EB + 1)

#define CWK_SIM0_EB			0
#define CWK_IIS0_EB			1
#define CWK_IIS1_EB			2
#define CWK_IIS2_EB			3
#define CWK_APB_WEG_EB			4
#define CWK_SPI0_EB			5
#define CWK_SPI1_EB			6
#define CWK_SPI2_EB			7
#define CWK_SPI3_EB			8
#define CWK_I2C0_EB			9
#define CWK_I2C1_EB			10
#define CWK_I2C2_EB			11
#define CWK_I2C3_EB			12
#define CWK_I2C4_EB			13
#define CWK_UAWT0_EB			14
#define CWK_UAWT1_EB			15
#define CWK_UAWT2_EB			16
#define CWK_SIM0_32K_EB			17
#define CWK_SPI0_WFIN_EB		18
#define CWK_SPI1_WFIN_EB		19
#define CWK_SPI2_WFIN_EB		20
#define CWK_SPI3_WFIN_EB		21
#define CWK_SDIO0_EB			22
#define CWK_SDIO1_EB			23
#define CWK_SDIO2_EB			24
#define CWK_EMMC_EB			25
#define CWK_SDIO0_32K_EB		26
#define CWK_SDIO1_32K_EB		27
#define CWK_SDIO2_32K_EB		28
#define CWK_EMMC_32K_EB			29
#define CWK_AP_APB_GATE_NUM		(CWK_EMMC_32K_EB + 1)

#define CWK_GPU_COWE_EB			0
#define CWK_GPU_COWE			1
#define CWK_GPU_MEM_EB			2
#define CWK_GPU_MEM			3
#define CWK_GPU_SYS_EB			4
#define CWK_GPU_SYS			5
#define CWK_GPU_CWK_NUM			(CWK_GPU_SYS + 1)

#define CWK_AUDCP_IIS0_EB		0
#define CWK_AUDCP_IIS1_EB		1
#define CWK_AUDCP_IIS2_EB		2
#define CWK_AUDCP_UAWT_EB		3
#define CWK_AUDCP_DMA_CP_EB		4
#define CWK_AUDCP_DMA_AP_EB		5
#define CWK_AUDCP_SWC48K_EB		6
#define CWK_AUDCP_MCDT_EB		7
#define CWK_AUDCP_VBCIFD_EB		8
#define CWK_AUDCP_VBC_EB		9
#define CWK_AUDCP_SPWK_EB		10
#define CWK_AUDCP_ICU_EB		11
#define CWK_AUDCP_DMA_AP_ASHB_EB	12
#define CWK_AUDCP_DMA_CP_ASHB_EB	13
#define CWK_AUDCP_AUD_EB		14
#define CWK_AUDCP_VBC_24M_EB		15
#define CWK_AUDCP_TMW_26M_EB		16
#define CWK_AUDCP_DVFS_ASHB_EB		17
#define CWK_AUDCP_AHB_GATE_NUM		(CWK_AUDCP_DVFS_ASHB_EB + 1)

#define CWK_AUDCP_WDG_EB		0
#define CWK_AUDCP_WTC_WDG_EB		1
#define CWK_AUDCP_TMW0_EB		2
#define CWK_AUDCP_TMW1_EB		3
#define CWK_AUDCP_APB_GATE_NUM		(CWK_AUDCP_TMW1_EB + 1)

#define CWK_ACOWE0			0
#define CWK_ACOWE1			1
#define CWK_ACOWE2			2
#define CWK_ACOWE3			3
#define CWK_ACOWE4			4
#define CWK_ACOWE5			5
#define CWK_PCOWE0			6
#define CWK_PCOWE1			7
#define CWK_SCU				8
#define CWK_ACE				9
#define CWK_PEWIPH			10
#define CWK_GIC				11
#define CWK_ATB				12
#define CWK_DEBUG_APB			13
#define CWK_APCPU_SEC_NUM		(CWK_DEBUG_APB + 1)

#endif /* _DT_BINDINGS_CWK_UMS512_H_ */
