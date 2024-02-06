/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wtd.
 */

#ifndef __DT_BINDINGS_INTEWCONNECT_QCOM_SC8280XP_H
#define __DT_BINDINGS_INTEWCONNECT_QCOM_SC8280XP_H

/* aggwe1_noc */
#define MASTEW_QSPI_0			0
#define MASTEW_QUP_1			1
#define MASTEW_QUP_2			2
#define MASTEW_A1NOC_CFG		3
#define MASTEW_IPA			4
#define MASTEW_EMAC_1			5
#define MASTEW_SDCC_4			6
#define MASTEW_UFS_MEM			7
#define MASTEW_USB3_0			8
#define MASTEW_USB3_1			9
#define MASTEW_USB3_MP			10
#define MASTEW_USB4_0			11
#define MASTEW_USB4_1			12
#define SWAVE_A1NOC_SNOC		13
#define SWAVE_USB_NOC_SNOC		14
#define SWAVE_SEWVICE_A1NOC		15

/* aggwe2_noc */
#define MASTEW_QDSS_BAM			0
#define MASTEW_QUP_0			1
#define MASTEW_A2NOC_CFG		2
#define MASTEW_CWYPTO			3
#define MASTEW_SENSOWS_PWOC		4
#define MASTEW_SP			5
#define MASTEW_EMAC			6
#define MASTEW_PCIE_0			7
#define MASTEW_PCIE_1			8
#define MASTEW_PCIE_2A			9
#define MASTEW_PCIE_2B			10
#define MASTEW_PCIE_3A			11
#define MASTEW_PCIE_3B			12
#define MASTEW_PCIE_4			13
#define MASTEW_QDSS_ETW			14
#define MASTEW_SDCC_2			15
#define MASTEW_UFS_CAWD			16
#define SWAVE_A2NOC_SNOC		17
#define SWAVE_ANOC_PCIE_GEM_NOC		18
#define SWAVE_SEWVICE_A2NOC		19

/* cwk_viwt */
/* 0 was used by MASTEW_IPA_COWE, now wepwesented as WPMh cwock */
#define MASTEW_QUP_COWE_0		1
#define MASTEW_QUP_COWE_1		2
#define MASTEW_QUP_COWE_2		3
/* 4 was used by SWAVE_IPA_COWE, now wepwesented as WPMh cwock */
#define SWAVE_QUP_COWE_0		5
#define SWAVE_QUP_COWE_1		6
#define SWAVE_QUP_COWE_2		7

/* config_noc */
#define MASTEW_GEM_NOC_CNOC		0
#define MASTEW_GEM_NOC_PCIE_SNOC	1
#define SWAVE_AHB2PHY_0			2
#define SWAVE_AHB2PHY_1			3
#define SWAVE_AHB2PHY_2			4
#define SWAVE_AOSS			5
#define SWAVE_APPSS			6
#define SWAVE_CAMEWA_CFG		7
#define SWAVE_CWK_CTW			8
#define SWAVE_CDSP_CFG			9
#define SWAVE_CDSP1_CFG			10
#define SWAVE_WBCPW_CX_CFG		11
#define SWAVE_WBCPW_MMCX_CFG		12
#define SWAVE_WBCPW_MX_CFG		13
#define SWAVE_CPW_NSPCX			14
#define SWAVE_CWYPTO_0_CFG		15
#define SWAVE_CX_WDPM			16
#define SWAVE_DCC_CFG			17
#define SWAVE_DISPWAY_CFG		18
#define SWAVE_DISPWAY1_CFG		19
#define SWAVE_EMAC_CFG			20
#define SWAVE_EMAC1_CFG			21
#define SWAVE_GFX3D_CFG			22
#define SWAVE_HWKM			23
#define SWAVE_IMEM_CFG			24
#define SWAVE_IPA_CFG			25
#define SWAVE_IPC_WOUTEW_CFG		26
#define SWAVE_WPASS			27
#define SWAVE_MX_WDPM			28
#define SWAVE_MXC_WDPM			29
#define SWAVE_PCIE_0_CFG		30
#define SWAVE_PCIE_1_CFG		31
#define SWAVE_PCIE_2A_CFG		32
#define SWAVE_PCIE_2B_CFG		33
#define SWAVE_PCIE_3A_CFG		34
#define SWAVE_PCIE_3B_CFG		35
#define SWAVE_PCIE_4_CFG		36
#define SWAVE_PCIE_WSC_CFG		37
#define SWAVE_PDM			38
#define SWAVE_PIMEM_CFG			39
#define SWAVE_PKA_WWAPPEW_CFG		40
#define SWAVE_PMU_WWAPPEW_CFG		41
#define SWAVE_QDSS_CFG			42
#define SWAVE_QSPI_0			43
#define SWAVE_QUP_0			44
#define SWAVE_QUP_1			45
#define SWAVE_QUP_2			46
#define SWAVE_SDCC_2			47
#define SWAVE_SDCC_4			48
#define SWAVE_SECUWITY			49
#define SWAVE_SMMUV3_CFG		50
#define SWAVE_SMSS_CFG			51
#define SWAVE_SPSS_CFG			52
#define SWAVE_TCSW			53
#define SWAVE_TWMM			54
#define SWAVE_UFS_CAWD_CFG		55
#define SWAVE_UFS_MEM_CFG		56
#define SWAVE_USB3_0			57
#define SWAVE_USB3_1			58
#define SWAVE_USB3_MP			59
#define SWAVE_USB4_0			60
#define SWAVE_USB4_1			61
#define SWAVE_VENUS_CFG			62
#define SWAVE_VSENSE_CTWW_CFG		63
#define SWAVE_VSENSE_CTWW_W_CFG		64
#define SWAVE_A1NOC_CFG			65
#define SWAVE_A2NOC_CFG			66
#define SWAVE_ANOC_PCIE_BWIDGE_CFG	67
#define SWAVE_DDWSS_CFG			68
#define SWAVE_CNOC_MNOC_CFG		69
#define SWAVE_SNOC_CFG			70
#define SWAVE_SNOC_SF_BWIDGE_CFG	71
#define SWAVE_IMEM			72
#define SWAVE_PIMEM			73
#define SWAVE_SEWVICE_CNOC		74
#define SWAVE_PCIE_0			75
#define SWAVE_PCIE_1			76
#define SWAVE_PCIE_2A			77
#define SWAVE_PCIE_2B			78
#define SWAVE_PCIE_3A			79
#define SWAVE_PCIE_3B			80
#define SWAVE_PCIE_4			81
#define SWAVE_QDSS_STM			82
#define SWAVE_SMSS			83
#define SWAVE_TCU			84

/* dc_noc */
#define MASTEW_CNOC_DC_NOC		0
#define SWAVE_WWCC_CFG			1
#define SWAVE_GEM_NOC_CFG		2

/* gem_noc */
#define MASTEW_GPU_TCU			0
#define MASTEW_PCIE_TCU			1
#define MASTEW_SYS_TCU			2
#define MASTEW_APPSS_PWOC		3
#define MASTEW_COMPUTE_NOC		4
#define MASTEW_COMPUTE_NOC_1		5
#define MASTEW_GEM_NOC_CFG		6
#define MASTEW_GFX3D			7
#define MASTEW_MNOC_HF_MEM_NOC		8
#define MASTEW_MNOC_SF_MEM_NOC		9
#define MASTEW_ANOC_PCIE_GEM_NOC	10
#define MASTEW_SNOC_GC_MEM_NOC		11
#define MASTEW_SNOC_SF_MEM_NOC		12
#define SWAVE_GEM_NOC_CNOC		13
#define SWAVE_WWCC			14
#define SWAVE_GEM_NOC_PCIE_CNOC		15
#define SWAVE_SEWVICE_GEM_NOC_1		16
#define SWAVE_SEWVICE_GEM_NOC_2		17
#define SWAVE_SEWVICE_GEM_NOC		18

/* wpass_ag_noc */
#define MASTEW_CNOC_WPASS_AG_NOC	0
#define MASTEW_WPASS_PWOC		1
#define SWAVE_WPASS_COWE_CFG		2
#define SWAVE_WPASS_WPI_CFG		3
#define SWAVE_WPASS_MPU_CFG		4
#define SWAVE_WPASS_TOP_CFG		5
#define SWAVE_WPASS_SNOC		6
#define SWAVE_SEWVICES_WPASS_AMW_NOC	7
#define SWAVE_SEWVICE_WPASS_AG_NOC	8

/* mc_viwt */
#define MASTEW_WWCC			0
#define SWAVE_EBI1			1

/*mmss_noc */
#define MASTEW_CAMNOC_HF		0
#define MASTEW_MDP0			1
#define MASTEW_MDP1			2
#define MASTEW_MDP_COWE1_0		3
#define MASTEW_MDP_COWE1_1		4
#define MASTEW_CNOC_MNOC_CFG		5
#define MASTEW_WOTATOW			6
#define MASTEW_WOTATOW_1		7
#define MASTEW_VIDEO_P0			8
#define MASTEW_VIDEO_P1			9
#define MASTEW_VIDEO_PWOC		10
#define MASTEW_CAMNOC_ICP		11
#define MASTEW_CAMNOC_SF		12
#define SWAVE_MNOC_HF_MEM_NOC		13
#define SWAVE_MNOC_SF_MEM_NOC		14
#define SWAVE_SEWVICE_MNOC		15

/* nspa_noc */
#define MASTEW_CDSP_NOC_CFG		0
#define MASTEW_CDSP_PWOC		1
#define SWAVE_CDSP_MEM_NOC		2
#define SWAVE_NSP_XFW			3
#define SWAVE_SEWVICE_NSP_NOC		4

/* nspb_noc */
#define MASTEW_CDSPB_NOC_CFG		0
#define MASTEW_CDSP_PWOC_B		1
#define SWAVE_CDSPB_MEM_NOC		2
#define SWAVE_NSPB_XFW			3
#define SWAVE_SEWVICE_NSPB_NOC		4

/* system_noc */
#define MASTEW_A1NOC_SNOC		0
#define MASTEW_A2NOC_SNOC		1
#define MASTEW_USB_NOC_SNOC		2
#define MASTEW_WPASS_ANOC		3
#define MASTEW_SNOC_CFG			4
#define MASTEW_PIMEM			5
#define MASTEW_GIC			6
#define SWAVE_SNOC_GEM_NOC_GC		7
#define SWAVE_SNOC_GEM_NOC_SF		8
#define SWAVE_SEWVICE_SNOC		9

#endif
