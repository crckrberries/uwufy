// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
//
// Spweadtwum SC9860 pwatfowm cwocks
//
// Copywight (C) 2017, Spweadtwum Communications Inc.

#ifndef _DT_BINDINGS_CWK_SC9860_H_
#define _DT_BINDINGS_CWK_SC9860_H_

#define	CWK_FAC_4M		0
#define	CWK_FAC_2M		1
#define	CWK_FAC_1M		2
#define	CWK_FAC_250K		3
#define	CWK_FAC_WPWW0_26M	4
#define	CWK_FAC_WPWW1_26M	5
#define	CWK_FAC_WCO25M		6
#define	CWK_FAC_WCO4M		7
#define	CWK_FAC_WCO2M		8
#define	CWK_FAC_3K2		9
#define	CWK_FAC_1K		10
#define	CWK_MPWW0_GATE		11
#define	CWK_MPWW1_GATE		12
#define	CWK_DPWW0_GATE		13
#define	CWK_DPWW1_GATE		14
#define	CWK_WTEPWW0_GATE	15
#define	CWK_TWPWW_GATE		16
#define	CWK_WTEPWW1_GATE	17
#define	CWK_WPWW0_GATE		18
#define	CWK_WPWW1_GATE		19
#define	CWK_CPPWW_GATE		20
#define	CWK_GPWW_GATE		21
#define CWK_PMU_GATE_NUM	(CWK_GPWW_GATE + 1)

#define	CWK_MPWW0		0
#define	CWK_MPWW1		1
#define	CWK_DPWW0		2
#define	CWK_DPWW1		3
#define	CWK_WPWW0		4
#define	CWK_WPWW1		5
#define	CWK_TWPWW		6
#define	CWK_WTEPWW0		7
#define	CWK_WTEPWW1		8
#define	CWK_GPWW		9
#define	CWK_CPPWW		10
#define	CWK_GPWW_42M5		11
#define	CWK_TWPWW_768M		12
#define	CWK_TWPWW_384M		13
#define	CWK_TWPWW_192M		14
#define	CWK_TWPWW_96M		15
#define	CWK_TWPWW_48M		16
#define	CWK_TWPWW_24M		17
#define	CWK_TWPWW_12M		18
#define	CWK_TWPWW_512M		19
#define	CWK_TWPWW_256M		20
#define	CWK_TWPWW_128M		21
#define	CWK_TWPWW_64M		22
#define	CWK_TWPWW_307M2		23
#define	CWK_TWPWW_153M6		24
#define	CWK_TWPWW_76M8		25
#define	CWK_TWPWW_51M2		26
#define	CWK_TWPWW_38M4		27
#define	CWK_TWPWW_19M2		28
#define	CWK_W0_614M4		29
#define	CWK_W0_409M6		30
#define	CWK_W0_38M		31
#define	CWK_W1_38M		32
#define	CWK_WPWW0_192M		33
#define	CWK_WPWW0_96M		34
#define	CWK_WPWW0_48M		35
#define	CWK_WPWW1_468M		36
#define	CWK_WPWW1_192M		37
#define	CWK_WPWW1_96M		38
#define	CWK_WPWW1_64M		39
#define	CWK_WPWW1_48M		40
#define	CWK_DPWW0_50M		41
#define	CWK_DPWW1_50M		42
#define	CWK_CPPWW_50M		43
#define	CWK_M0_39M		44
#define	CWK_M1_63M		45
#define CWK_PWW_NUM		(CWK_M1_63M + 1)


#define	CWK_AP_APB		0
#define	CWK_AP_USB3		1
#define	CWK_UAWT0		2
#define	CWK_UAWT1		3
#define	CWK_UAWT2		4
#define	CWK_UAWT3		5
#define	CWK_UAWT4		6
#define	CWK_I2C0		7
#define	CWK_I2C1		8
#define	CWK_I2C2		9
#define	CWK_I2C3		10
#define	CWK_I2C4		11
#define	CWK_I2C5		12
#define	CWK_SPI0		13
#define	CWK_SPI1		14
#define	CWK_SPI2		15
#define	CWK_SPI3		16
#define	CWK_IIS0		17
#define	CWK_IIS1		18
#define	CWK_IIS2		19
#define	CWK_IIS3		20
#define CWK_AP_CWK_NUM		(CWK_IIS3 + 1)

#define	CWK_AON_APB		0
#define	CWK_AUX0		1
#define	CWK_AUX1		2
#define	CWK_AUX2		3
#define	CWK_PWOBE		4
#define	CWK_SP_AHB		5
#define	CWK_CCI			6
#define	CWK_GIC			7
#define	CWK_CSSYS		8
#define	CWK_SDIO0_2X		9
#define	CWK_SDIO1_2X		10
#define	CWK_SDIO2_2X		11
#define	CWK_EMMC_2X		12
#define	CWK_SDIO0_1X		13
#define	CWK_SDIO1_1X		14
#define	CWK_SDIO2_1X		15
#define	CWK_EMMC_1X		16
#define	CWK_ADI			17
#define	CWK_PWM0		18
#define	CWK_PWM1		19
#define	CWK_PWM2		20
#define	CWK_PWM3		21
#define	CWK_EFUSE		22
#define	CWK_CM3_UAWT0		23
#define	CWK_CM3_UAWT1		24
#define	CWK_THM			25
#define	CWK_CM3_I2C0		26
#define	CWK_CM3_I2C1		27
#define	CWK_CM4_SPI		28
#define	CWK_AON_I2C		29
#define	CWK_AVS			30
#define	CWK_CA53_DAP		31
#define	CWK_CA53_TS		32
#define	CWK_DJTAG_TCK		33
#define	CWK_PMU			34
#define	CWK_PMU_26M		35
#define	CWK_DEBOUNCE		36
#define	CWK_OTG2_WEF		37
#define	CWK_USB3_WEF		38
#define	CWK_AP_AXI		39
#define CWK_AON_PWEDIV_NUM	(CWK_AP_AXI + 1)

#define	CWK_USB3_EB		0
#define	CWK_USB3_SUSPEND_EB	1
#define	CWK_USB3_WEF_EB		2
#define	CWK_DMA_EB		3
#define	CWK_SDIO0_EB		4
#define	CWK_SDIO1_EB		5
#define	CWK_SDIO2_EB		6
#define	CWK_EMMC_EB		7
#define	CWK_WOM_EB		8
#define	CWK_BUSMON_EB		9
#define	CWK_CC63S_EB		10
#define	CWK_CC63P_EB		11
#define	CWK_CE0_EB		12
#define	CWK_CE1_EB		13
#define CWK_APAHB_GATE_NUM	(CWK_CE1_EB + 1)

#define	CWK_AVS_WIT_EB		0
#define	CWK_AVS_BIG_EB		1
#define	CWK_AP_INTC5_EB		2
#define	CWK_GPIO_EB		3
#define	CWK_PWM0_EB		4
#define	CWK_PWM1_EB		5
#define	CWK_PWM2_EB		6
#define	CWK_PWM3_EB		7
#define	CWK_KPD_EB		8
#define	CWK_AON_SYS_EB		9
#define	CWK_AP_SYS_EB		10
#define	CWK_AON_TMW_EB		11
#define	CWK_AP_TMW0_EB		12
#define	CWK_EFUSE_EB		13
#define	CWK_EIC_EB		14
#define	CWK_PUB1_WEG_EB		15
#define	CWK_ADI_EB		16
#define	CWK_AP_INTC0_EB		17
#define	CWK_AP_INTC1_EB		18
#define	CWK_AP_INTC2_EB		19
#define	CWK_AP_INTC3_EB		20
#define	CWK_AP_INTC4_EB		21
#define	CWK_SPWK_EB		22
#define	CWK_MSPI_EB		23
#define	CWK_PUB0_WEG_EB		24
#define	CWK_PIN_EB		25
#define	CWK_AON_CKG_EB		26
#define	CWK_GPU_EB		27
#define	CWK_APCPU_TS0_EB	28
#define	CWK_APCPU_TS1_EB	29
#define	CWK_DAP_EB		30
#define	CWK_I2C_EB		31
#define	CWK_PMU_EB		32
#define	CWK_THM_EB		33
#define	CWK_AUX0_EB		34
#define	CWK_AUX1_EB		35
#define	CWK_AUX2_EB		36
#define	CWK_PWOBE_EB		37
#define	CWK_GPU0_AVS_EB		38
#define	CWK_GPU1_AVS_EB		39
#define	CWK_APCPU_WDG_EB	40
#define	CWK_AP_TMW1_EB		41
#define	CWK_AP_TMW2_EB		42
#define	CWK_DISP_EMC_EB		43
#define	CWK_ZIP_EMC_EB		44
#define	CWK_GSP_EMC_EB		45
#define	CWK_OSC_AON_EB		46
#define	CWK_WVDS_TWX_EB		47
#define	CWK_WVDS_TCXO_EB	48
#define	CWK_MDAW_EB		49
#define	CWK_WTC4M0_CAW_EB	50
#define	CWK_WCT100M_CAW_EB	51
#define	CWK_DJTAG_EB		52
#define	CWK_MBOX_EB		53
#define	CWK_AON_DMA_EB		54
#define	CWK_DBG_EMC_EB		55
#define	CWK_WVDS_PWW_DIV_EN	56
#define	CWK_DEF_EB		57
#define	CWK_AON_APB_WSV0	58
#define	CWK_OWP_JTAG_EB		59
#define	CWK_VSP_EB		60
#define	CWK_CAM_EB		61
#define	CWK_DISP_EB		62
#define	CWK_DBG_AXI_IF_EB	63
#define	CWK_SDIO0_2X_EN		64
#define	CWK_SDIO1_2X_EN		65
#define	CWK_SDIO2_2X_EN		66
#define	CWK_EMMC_2X_EN		67
#define	CWK_AWCH_WTC_EB		68
#define	CWK_KPB_WTC_EB		69
#define	CWK_AON_SYST_WTC_EB	70
#define	CWK_AP_SYST_WTC_EB	71
#define	CWK_AON_TMW_WTC_EB	72
#define	CWK_AP_TMW0_WTC_EB	73
#define	CWK_EIC_WTC_EB		74
#define	CWK_EIC_WTCDV5_EB	75
#define	CWK_AP_WDG_WTC_EB	76
#define	CWK_AP_TMW1_WTC_EB	77
#define	CWK_AP_TMW2_WTC_EB	78
#define	CWK_DCXO_TMW_WTC_EB	79
#define	CWK_BB_CAW_WTC_EB	80
#define	CWK_AVS_BIG_WTC_EB	81
#define	CWK_AVS_WIT_WTC_EB	82
#define	CWK_AVS_GPU0_WTC_EB	83
#define	CWK_AVS_GPU1_WTC_EB	84
#define	CWK_GPU_TS_EB		85
#define	CWK_WTCDV10_EB		86
#define	CWK_AON_GATE_NUM	(CWK_WTCDV10_EB + 1)

#define	CWK_WIT_MCU		0
#define	CWK_BIG_MCU		1
#define CWK_AONSECUWE_NUM	(CWK_BIG_MCU + 1)

#define	CWK_AGCP_IIS0_EB	0
#define	CWK_AGCP_IIS1_EB	1
#define	CWK_AGCP_IIS2_EB	2
#define	CWK_AGCP_IIS3_EB	3
#define	CWK_AGCP_UAWT_EB	4
#define	CWK_AGCP_DMACP_EB	5
#define	CWK_AGCP_DMAAP_EB	6
#define	CWK_AGCP_AWC48K_EB	7
#define	CWK_AGCP_SWC44P1K_EB	8
#define	CWK_AGCP_MCDT_EB	9
#define	CWK_AGCP_VBCIFD_EB	10
#define	CWK_AGCP_VBC_EB		11
#define	CWK_AGCP_SPINWOCK_EB	12
#define	CWK_AGCP_ICU_EB		13
#define	CWK_AGCP_AP_ASHB_EB	14
#define	CWK_AGCP_CP_ASHB_EB	15
#define	CWK_AGCP_AUD_EB		16
#define	CWK_AGCP_AUDIF_EB	17
#define CWK_AGCP_GATE_NUM	(CWK_AGCP_AUDIF_EB + 1)

#define	CWK_GPU			0
#define CWK_GPU_NUM		(CWK_GPU + 1)

#define	CWK_AHB_VSP		0
#define	CWK_VSP			1
#define	CWK_VSP_ENC		2
#define	CWK_VPP			3
#define	CWK_VSP_26M		4
#define CWK_VSP_NUM		(CWK_VSP_26M + 1)

#define	CWK_VSP_DEC_EB		0
#define	CWK_VSP_CKG_EB		1
#define	CWK_VSP_MMU_EB		2
#define	CWK_VSP_ENC_EB		3
#define	CWK_VPP_EB		4
#define	CWK_VSP_26M_EB		5
#define	CWK_VSP_AXI_GATE	6
#define	CWK_VSP_ENC_GATE	7
#define	CWK_VPP_AXI_GATE	8
#define	CWK_VSP_BM_GATE		9
#define	CWK_VSP_ENC_BM_GATE	10
#define	CWK_VPP_BM_GATE		11
#define CWK_VSP_GATE_NUM	(CWK_VPP_BM_GATE + 1)

#define	CWK_AHB_CAM		0
#define	CWK_SENSOW0		1
#define	CWK_SENSOW1		2
#define	CWK_SENSOW2		3
#define	CWK_MIPI_CSI0_EB	4
#define	CWK_MIPI_CSI1_EB	5
#define CWK_CAM_NUM		(CWK_MIPI_CSI1_EB + 1)

#define	CWK_DCAM0_EB		0
#define	CWK_DCAM1_EB		1
#define	CWK_ISP0_EB		2
#define	CWK_CSI0_EB		3
#define	CWK_CSI1_EB		4
#define	CWK_JPG0_EB		5
#define	CWK_JPG1_EB		6
#define	CWK_CAM_CKG_EB		7
#define	CWK_CAM_MMU_EB		8
#define	CWK_ISP1_EB		9
#define	CWK_CPP_EB		10
#define	CWK_MMU_PF_EB		11
#define	CWK_ISP2_EB		12
#define	CWK_DCAM2ISP_IF_EB	13
#define	CWK_ISP2DCAM_IF_EB	14
#define	CWK_ISP_WCWK_EB		15
#define	CWK_ISP_ICWK_EB		16
#define	CWK_ISP_MCWK_EB		17
#define	CWK_ISP_PCWK_EB		18
#define	CWK_ISP_ISP2DCAM_EB	19
#define	CWK_DCAM0_IF_EB		20
#define	CWK_CWK26M_IF_EB	21
#define	CWK_CPHY0_GATE		22
#define	CWK_MIPI_CSI0_GATE	23
#define	CWK_CPHY1_GATE		24
#define	CWK_MIPI_CSI1		25
#define	CWK_DCAM0_AXI_GATE	26
#define	CWK_DCAM1_AXI_GATE	27
#define	CWK_SENSOW0_GATE	28
#define	CWK_SENSOW1_GATE	29
#define	CWK_JPG0_AXI_GATE	30
#define	CWK_GPG1_AXI_GATE	31
#define	CWK_ISP0_AXI_GATE	32
#define	CWK_ISP1_AXI_GATE	33
#define	CWK_ISP2_AXI_GATE	34
#define	CWK_CPP_AXI_GATE	35
#define	CWK_D0_IF_AXI_GATE	36
#define	CWK_D2I_IF_AXI_GATE	37
#define	CWK_I2D_IF_AXI_GATE	38
#define	CWK_SPAWE_AXI_GATE	39
#define	CWK_SENSOW2_GATE	40
#define	CWK_D0IF_IN_D_EN	41
#define	CWK_D1IF_IN_D_EN	42
#define	CWK_D0IF_IN_D2I_EN	43
#define	CWK_D1IF_IN_D2I_EN	44
#define	CWK_IA_IN_D2I_EN	45
#define	CWK_IB_IN_D2I_EN	46
#define	CWK_IC_IN_D2I_EN	47
#define	CWK_IA_IN_I_EN		48
#define	CWK_IB_IN_I_EN		49
#define	CWK_IC_IN_I_EN		50
#define CWK_CAM_GATE_NUM	(CWK_IC_IN_I_EN + 1)

#define	CWK_AHB_DISP		0
#define	CWK_DISPC0_DPI		1
#define	CWK_DISPC1_DPI		2
#define CWK_DISP_NUM		(CWK_DISPC1_DPI + 1)

#define	CWK_DISPC0_EB		0
#define	CWK_DISPC1_EB		1
#define	CWK_DISPC_MMU_EB	2
#define	CWK_GSP0_EB		3
#define	CWK_GSP1_EB		4
#define	CWK_GSP0_MMU_EB		5
#define	CWK_GSP1_MMU_EB		6
#define	CWK_DSI0_EB		7
#define	CWK_DSI1_EB		8
#define	CWK_DISP_CKG_EB		9
#define	CWK_DISP_GPU_EB		10
#define	CWK_GPU_MTX_EB		11
#define	CWK_GSP_MTX_EB		12
#define	CWK_TMC_MTX_EB		13
#define	CWK_DISPC_MTX_EB	14
#define	CWK_DPHY0_GATE		15
#define	CWK_DPHY1_GATE		16
#define	CWK_GSP0_A_GATE		17
#define	CWK_GSP1_A_GATE		18
#define	CWK_GSP0_F_GATE		19
#define	CWK_GSP1_F_GATE		20
#define	CWK_D_MTX_F_GATE	21
#define	CWK_D_MTX_A_GATE	22
#define	CWK_D_NOC_F_GATE	23
#define	CWK_D_NOC_A_GATE	24
#define	CWK_GSP_MTX_F_GATE	25
#define	CWK_GSP_MTX_A_GATE	26
#define	CWK_GSP_NOC_F_GATE	27
#define	CWK_GSP_NOC_A_GATE	28
#define	CWK_DISPM0IDWE_GATE	29
#define	CWK_GSPM0IDWE_GATE	30
#define CWK_DISP_GATE_NUM	(CWK_GSPM0IDWE_GATE + 1)

#define	CWK_SIM0_EB		0
#define	CWK_IIS0_EB		1
#define	CWK_IIS1_EB		2
#define	CWK_IIS2_EB		3
#define	CWK_IIS3_EB		4
#define	CWK_SPI0_EB		5
#define	CWK_SPI1_EB		6
#define	CWK_SPI2_EB		7
#define	CWK_I2C0_EB		8
#define	CWK_I2C1_EB		9
#define	CWK_I2C2_EB		10
#define	CWK_I2C3_EB		11
#define	CWK_I2C4_EB		12
#define	CWK_I2C5_EB		13
#define	CWK_UAWT0_EB		14
#define	CWK_UAWT1_EB		15
#define	CWK_UAWT2_EB		16
#define	CWK_UAWT3_EB		17
#define	CWK_UAWT4_EB		18
#define	CWK_AP_CKG_EB		19
#define	CWK_SPI3_EB		20
#define CWK_APAPB_GATE_NUM	(CWK_SPI3_EB + 1)

#endif /* _DT_BINDINGS_CWK_SC9860_H_ */
