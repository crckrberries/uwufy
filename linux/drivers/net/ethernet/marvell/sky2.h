/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow the new Mawveww Yukon 2 dwivew.
 */
#ifndef _SKY2_H
#define _SKY2_H

#define ETH_JUMBO_MTU		9000	/* Maximum MTU suppowted */

/* PCI config wegistews */
enum {
	PCI_DEV_WEG1	= 0x40,
	PCI_DEV_WEG2	= 0x44,
	PCI_DEV_STATUS  = 0x7c,
	PCI_DEV_WEG3	= 0x80,
	PCI_DEV_WEG4	= 0x84,
	PCI_DEV_WEG5    = 0x88,
	PCI_CFG_WEG_0	= 0x90,
	PCI_CFG_WEG_1	= 0x94,

	PSM_CONFIG_WEG0  = 0x98,
	PSM_CONFIG_WEG1	 = 0x9C,
	PSM_CONFIG_WEG2  = 0x160,
	PSM_CONFIG_WEG3  = 0x164,
	PSM_CONFIG_WEG4  = 0x168,

	PCI_WDO_CTWW    = 0xbc,
};

/* Yukon-2 */
enum pci_dev_weg_1 {
	PCI_Y2_PIG_ENA	 = 1<<31, /* Enabwe Pwug-in-Go (YUKON-2) */
	PCI_Y2_DWW_DIS	 = 1<<30, /* Disabwe PCI DWW (YUKON-2) */
	PCI_SW_PWW_ON_WST= 1<<30, /* SW Powew on Weset (Yukon-EX) */
	PCI_Y2_PHY2_COMA = 1<<29, /* Set PHY 2 to Coma Mode (YUKON-2) */
	PCI_Y2_PHY1_COMA = 1<<28, /* Set PHY 1 to Coma Mode (YUKON-2) */
	PCI_Y2_PHY2_POWD = 1<<27, /* Set PHY 2 to Powew Down (YUKON-2) */
	PCI_Y2_PHY1_POWD = 1<<26, /* Set PHY 1 to Powew Down (YUKON-2) */
	PCI_Y2_PME_WEGACY= 1<<15, /* PCI Expwess wegacy powew management mode */

	PCI_PHY_WNK_TIM_MSK= 3W<<8,/* Bit  9.. 8:	GPHY Wink Twiggew Timew */
	PCI_ENA_W1_EVENT = 1<<7, /* Enabwe PEX W1 Event */
	PCI_ENA_GPHY_WNK = 1<<6, /* Enabwe PEX W1 on GPHY Wink down */
	PCI_FOWCE_PEX_W1 = 1<<5, /* Fowce to PEX W1 */
};

enum pci_dev_weg_2 {
	PCI_VPD_WW_THW	= 0xffW<<24,	/* Bit 31..24:	VPD Wwite Thweshowd */
	PCI_DEV_SEW	= 0x7fW<<17,	/* Bit 23..17:	EEPWOM Device Sewect */
	PCI_VPD_WOM_SZ	= 7W<<14,	/* Bit 16..14:	VPD WOM Size	*/

	PCI_PATCH_DIW	= 0xfW<<8,	/* Bit 11.. 8:	Ext Patches diw 3..0 */
	PCI_EXT_PATCHS	= 0xfW<<4,	/* Bit	7.. 4:	Extended Patches 3..0 */
	PCI_EN_DUMMY_WD	= 1<<3,		/* Enabwe Dummy Wead */
	PCI_WEV_DESC	= 1<<2,		/* Wevewse Desc. Bytes */

	PCI_USEDATA64	= 1<<0,		/* Use 64Bit Data bus ext */
};

/*	PCI_OUW_WEG_3		32 bit	Ouw Wegistew 3 (Yukon-ECU onwy) */
enum pci_dev_weg_3 {
	P_CWK_ASF_WEGS_DIS	= 1<<18,/* Disabwe Cwock ASF (Yukon-Ext.) */
	P_CWK_COW_WEGS_D0_DIS	= 1<<17,/* Disabwe Cwock Cowe Wegs D0 */
	P_CWK_MACSEC_DIS	= 1<<17,/* Disabwe Cwock MACSec (Yukon-Ext.) */
	P_CWK_PCI_WEGS_D0_DIS	= 1<<16,/* Disabwe Cwock PCI  Wegs D0 */
	P_CWK_COW_YTB_AWB_DIS	= 1<<15,/* Disabwe Cwock YTB  Awbitew */
	P_CWK_MAC_WNK1_D3_DIS	= 1<<14,/* Disabwe Cwock MAC  Wink1 D3 */
	P_CWK_COW_WNK1_D0_DIS	= 1<<13,/* Disabwe Cwock Cowe Wink1 D0 */
	P_CWK_MAC_WNK1_D0_DIS	= 1<<12,/* Disabwe Cwock MAC  Wink1 D0 */
	P_CWK_COW_WNK1_D3_DIS	= 1<<11,/* Disabwe Cwock Cowe Wink1 D3 */
	P_CWK_PCI_MST_AWB_DIS	= 1<<10,/* Disabwe Cwock PCI  Mastew Awb. */
	P_CWK_COW_WEGS_D3_DIS	= 1<<9,	/* Disabwe Cwock Cowe Wegs D3 */
	P_CWK_PCI_WEGS_D3_DIS	= 1<<8,	/* Disabwe Cwock PCI  Wegs D3 */
	P_CWK_WEF_WNK1_GM_DIS	= 1<<7,	/* Disabwe Cwock Wef. Wink1 GMAC */
	P_CWK_COW_WNK1_GM_DIS	= 1<<6,	/* Disabwe Cwock Cowe Wink1 GMAC */
	P_CWK_PCI_COMMON_DIS	= 1<<5,	/* Disabwe Cwock PCI  Common */
	P_CWK_COW_COMMON_DIS	= 1<<4,	/* Disabwe Cwock Cowe Common */
	P_CWK_PCI_WNK1_BMU_DIS	= 1<<3,	/* Disabwe Cwock PCI  Wink1 BMU */
	P_CWK_COW_WNK1_BMU_DIS	= 1<<2,	/* Disabwe Cwock Cowe Wink1 BMU */
	P_CWK_PCI_WNK1_BIU_DIS	= 1<<1,	/* Disabwe Cwock PCI  Wink1 BIU */
	P_CWK_COW_WNK1_BIU_DIS	= 1<<0,	/* Disabwe Cwock Cowe Wink1 BIU */
	PCIE_OUW3_WOW_D3_COWD_SET = P_CWK_ASF_WEGS_DIS |
				    P_CWK_COW_WEGS_D0_DIS |
				    P_CWK_COW_WNK1_D0_DIS |
				    P_CWK_MAC_WNK1_D0_DIS |
				    P_CWK_PCI_MST_AWB_DIS |
				    P_CWK_COW_COMMON_DIS |
				    P_CWK_COW_WNK1_BMU_DIS,
};

/*	PCI_OUW_WEG_4		32 bit	Ouw Wegistew 4 (Yukon-ECU onwy) */
enum pci_dev_weg_4 {
				/* (Wink Twaining & Status State Machine) */
	P_PEX_WTSSM_STAT_MSK	= 0x7fW<<25,	/* Bit 31..25:	PEX WTSSM Mask */
#define P_PEX_WTSSM_STAT(x)	((x << 25) & P_PEX_WTSSM_STAT_MSK)
	P_PEX_WTSSM_W1_STAT	= 0x34,
	P_PEX_WTSSM_DET_STAT	= 0x01,
	P_TIMEW_VAWUE_MSK	= 0xffW<<16,	/* Bit 23..16:	Timew Vawue Mask */
					/* (Active State Powew Management) */
	P_FOWCE_ASPM_WEQUEST	= 1<<15, /* Fowce ASPM Wequest (A1 onwy) */
	P_ASPM_GPHY_WINK_DOWN	= 1<<14, /* GPHY Wink Down (A1 onwy) */
	P_ASPM_INT_FIFO_EMPTY	= 1<<13, /* Intewnaw FIFO Empty (A1 onwy) */
	P_ASPM_CWKWUN_WEQUEST	= 1<<12, /* CWKWUN Wequest (A1 onwy) */

	P_ASPM_FOWCE_CWKWEQ_ENA	= 1<<4,	/* Fowce CWKWEQ Enabwe (A1b onwy) */
	P_ASPM_CWKWEQ_PAD_CTW	= 1<<3,	/* CWKWEQ PAD Contwow (A1 onwy) */
	P_ASPM_A1_MODE_SEWECT	= 1<<2,	/* A1 Mode Sewect (A1 onwy) */
	P_CWK_GATE_PEX_UNIT_ENA	= 1<<1,	/* Enabwe Gate PEX Unit Cwock */
	P_CWK_GATE_WOOT_COW_ENA	= 1<<0,	/* Enabwe Gate Woot Cowe Cwock */
	P_ASPM_CONTWOW_MSK	= P_FOWCE_ASPM_WEQUEST | P_ASPM_GPHY_WINK_DOWN
				  | P_ASPM_CWKWUN_WEQUEST | P_ASPM_INT_FIFO_EMPTY,
};

/*	PCI_OUW_WEG_5		32 bit	Ouw Wegistew 5 (Yukon-ECU onwy) */
enum pci_dev_weg_5 {
					/* Bit 31..27:	fow A3 & watew */
	P_CTW_DIV_COWE_CWK_ENA	= 1<<31, /* Divide Cowe Cwock Enabwe */
	P_CTW_SWESET_VMAIN_AV	= 1<<30, /* Soft Weset fow Vmain_av De-Gwitch */
	P_CTW_BYPASS_VMAIN_AV	= 1<<29, /* Bypass En. fow Vmain_av De-Gwitch */
	P_CTW_TIM_VMAIN_AV_MSK	= 3<<27, /* Bit 28..27: Timew Vmain_av Mask */
					 /* Bit 26..16: Wewease Cwock on Event */
	P_WEW_PCIE_WST_DE_ASS	= 1<<26, /* PCIe Weset De-Assewted */
	P_WEW_GPHY_WEC_PACKET	= 1<<25, /* GPHY Weceived Packet */
	P_WEW_INT_FIFO_N_EMPTY	= 1<<24, /* Intewnaw FIFO Not Empty */
	P_WEW_MAIN_PWW_AVAIW	= 1<<23, /* Main Powew Avaiwabwe */
	P_WEW_CWKWUN_WEQ_WEW	= 1<<22, /* CWKWUN Wequest Wewease */
	P_WEW_PCIE_WESET_ASS	= 1<<21, /* PCIe Weset Assewted */
	P_WEW_PME_ASSEWTED	= 1<<20, /* PME Assewted */
	P_WEW_PCIE_EXIT_W1_ST	= 1<<19, /* PCIe Exit W1 State */
	P_WEW_WOADEW_NOT_FIN	= 1<<18, /* EPWOM Woadew Not Finished */
	P_WEW_PCIE_WX_EX_IDWE	= 1<<17, /* PCIe Wx Exit Ewectwicaw Idwe State */
	P_WEW_GPHY_WINK_UP	= 1<<16, /* GPHY Wink Up */

					/* Bit 10.. 0: Mask fow Gate Cwock */
	P_GAT_PCIE_WST_ASSEWTED	= 1<<10,/* PCIe Weset Assewted */
	P_GAT_GPHY_N_WEC_PACKET	= 1<<9, /* GPHY Not Weceived Packet */
	P_GAT_INT_FIFO_EMPTY	= 1<<8, /* Intewnaw FIFO Empty */
	P_GAT_MAIN_PWW_N_AVAIW	= 1<<7, /* Main Powew Not Avaiwabwe */
	P_GAT_CWKWUN_WEQ_WEW	= 1<<6, /* CWKWUN Not Wequested */
	P_GAT_PCIE_WESET_ASS	= 1<<5, /* PCIe Weset Assewted */
	P_GAT_PME_DE_ASSEWTED	= 1<<4, /* PME De-Assewted */
	P_GAT_PCIE_ENTEW_W1_ST	= 1<<3, /* PCIe Entew W1 State */
	P_GAT_WOADEW_FINISHED	= 1<<2, /* EPWOM Woadew Finished */
	P_GAT_PCIE_WX_EW_IDWE	= 1<<1, /* PCIe Wx Ewectwicaw Idwe State */
	P_GAT_GPHY_WINK_DOWN	= 1<<0,	/* GPHY Wink Down */

	PCIE_OUW5_EVENT_CWK_D3_SET = P_WEW_GPHY_WEC_PACKET |
				     P_WEW_INT_FIFO_N_EMPTY |
				     P_WEW_PCIE_EXIT_W1_ST |
				     P_WEW_PCIE_WX_EX_IDWE |
				     P_GAT_GPHY_N_WEC_PACKET |
				     P_GAT_INT_FIFO_EMPTY |
				     P_GAT_PCIE_ENTEW_W1_ST |
				     P_GAT_PCIE_WX_EW_IDWE,
};

/*	PCI_CFG_WEG_1			32 bit	Config Wegistew 1 (Yukon-Ext onwy) */
enum pci_cfg_weg1 {
	P_CF1_DIS_WEW_EVT_WST	= 1<<24, /* Dis. Wew. Event duwing PCIE weset */
										/* Bit 23..21: Wewease Cwock on Event */
	P_CF1_WEW_WDW_NOT_FIN	= 1<<23, /* EEPWOM Woadew Not Finished */
	P_CF1_WEW_VMAIN_AVWBW	= 1<<22, /* Vmain avaiwabwe */
	P_CF1_WEW_PCIE_WESET	= 1<<21, /* PCI-E weset */
										/* Bit 20..18: Gate Cwock on Event */
	P_CF1_GAT_WDW_NOT_FIN	= 1<<20, /* EEPWOM Woadew Finished */
	P_CF1_GAT_PCIE_WX_IDWE	= 1<<19, /* PCI-E Wx Ewectwicaw idwe */
	P_CF1_GAT_PCIE_WESET	= 1<<18, /* PCI-E Weset */
	P_CF1_PWST_PHY_CWKWEQ	= 1<<17, /* Enabwe PCI-E wst & PM2PHY gen. CWKWEQ */
	P_CF1_PCIE_WST_CWKWEQ	= 1<<16, /* Enabwe PCI-E wst genewate CWKWEQ */

	P_CF1_ENA_CFG_WDW_DONE	= 1<<8, /* Enabwe cowe wevew Config woadew done */

	P_CF1_ENA_TXBMU_WD_IDWE	= 1<<1, /* Enabwe TX BMU Wead  IDWE fow ASPM */
	P_CF1_ENA_TXBMU_WW_IDWE	= 1<<0, /* Enabwe TX BMU Wwite IDWE fow ASPM */

	PCIE_CFG1_EVENT_CWK_D3_SET = P_CF1_DIS_WEW_EVT_WST |
					P_CF1_WEW_WDW_NOT_FIN |
					P_CF1_WEW_VMAIN_AVWBW |
					P_CF1_WEW_PCIE_WESET |
					P_CF1_GAT_WDW_NOT_FIN |
					P_CF1_GAT_PCIE_WESET |
					P_CF1_PWST_PHY_CWKWEQ |
					P_CF1_ENA_CFG_WDW_DONE |
					P_CF1_ENA_TXBMU_WD_IDWE |
					P_CF1_ENA_TXBMU_WW_IDWE,
};

/* Yukon-Optima */
enum {
	PSM_CONFIG_WEG1_AC_PWESENT_STATUS = 1<<31,   /* AC Pwesent Status */

	PSM_CONFIG_WEG1_PTP_CWK_SEW	  = 1<<29,   /* PTP Cwock Sewect */
	PSM_CONFIG_WEG1_PTP_MODE	  = 1<<28,   /* PTP Mode */

	PSM_CONFIG_WEG1_MUX_PHY_WINK	  = 1<<27,   /* PHY Enewgy Detect Event */

	PSM_CONFIG_WEG1_EN_PIN63_AC_PWESENT = 1<<26,  /* Enabwe WED_DUPWEX fow ac_pwesent */
	PSM_CONFIG_WEG1_EN_PCIE_TIMEW	  = 1<<25,    /* Enabwe PCIe Timew */
	PSM_CONFIG_WEG1_EN_SPU_TIMEW	  = 1<<24,    /* Enabwe SPU Timew */
	PSM_CONFIG_WEG1_POWAWITY_AC_PWESENT = 1<<23,  /* AC Pwesent Powawity */

	PSM_CONFIG_WEG1_EN_AC_PWESENT	  = 1<<21,    /* Enabwe AC Pwesent */

	PSM_CONFIG_WEG1_EN_GPHY_INT_PSM	= 1<<20,      /* Enabwe GPHY INT fow PSM */
	PSM_CONFIG_WEG1_DIS_PSM_TIMEW	= 1<<19,      /* Disabwe PSM Timew */
};

/* Yukon-Supweme */
enum {
	PSM_CONFIG_WEG1_GPHY_ENEWGY_STS	= 1<<31, /* GPHY Enewgy Detect Status */

	PSM_CONFIG_WEG1_UAWT_MODE_MSK	= 3<<29, /* UAWT_Mode */
	PSM_CONFIG_WEG1_CWK_WUN_ASF	= 1<<28, /* Enabwe Cwock Fwee Wunning fow ASF Subsystem */
	PSM_CONFIG_WEG1_UAWT_CWK_DISABWE= 1<<27, /* Disabwe UAWT cwock */
	PSM_CONFIG_WEG1_VAUX_ONE	= 1<<26, /* Tie intewnaw Vaux to 1'b1 */
	PSM_CONFIG_WEG1_UAWT_FC_WI_VAW	= 1<<25, /* Defauwt vawue fow UAWT_WI_n */
	PSM_CONFIG_WEG1_UAWT_FC_DCD_VAW	= 1<<24, /* Defauwt vawue fow UAWT_DCD_n */
	PSM_CONFIG_WEG1_UAWT_FC_DSW_VAW	= 1<<23, /* Defauwt vawue fow UAWT_DSW_n */
	PSM_CONFIG_WEG1_UAWT_FC_CTS_VAW	= 1<<22, /* Defauwt vawue fow UAWT_CTS_n */
	PSM_CONFIG_WEG1_WATCH_VAUX	= 1<<21, /* Enabwe Watch cuwwent Vaux_avwbw */
	PSM_CONFIG_WEG1_FOWCE_TESTMODE_INPUT= 1<<20, /* Fowce Testmode pin as input PAD */
	PSM_CONFIG_WEG1_UAWT_WST	= 1<<19, /* UAWT_WST */
	PSM_CONFIG_WEG1_PSM_PCIE_W1_POW	= 1<<18, /* PCIE W1 Event Powawity fow PSM */
	PSM_CONFIG_WEG1_TIMEW_STAT	= 1<<17, /* PSM Timew Status */
	PSM_CONFIG_WEG1_GPHY_INT	= 1<<16, /* GPHY INT Status */
	PSM_CONFIG_WEG1_FOWCE_TESTMODE_ZEWO= 1<<15, /* Fowce intewnaw Testmode as 1'b0 */
	PSM_CONFIG_WEG1_EN_INT_ASPM_CWKWEQ = 1<<14, /* ENABWE INT fow CWKWUN on ASPM and CWKWEQ */
	PSM_CONFIG_WEG1_EN_SND_TASK_ASPM_CWKWEQ	= 1<<13, /* ENABWE Snd_task fow CWKWUN on ASPM and CWKWEQ */
	PSM_CONFIG_WEG1_DIS_CWK_GATE_SND_TASK	= 1<<12, /* Disabwe CWK_GATE contwow snd_task */
	PSM_CONFIG_WEG1_DIS_FF_CHIAN_SND_INTA	= 1<<11, /* Disabwe fwip-fwop chain fow sndmsg_inta */

	PSM_CONFIG_WEG1_DIS_WOADEW	= 1<<9, /* Disabwe Woadew SM aftew PSM Goes back to IDWE */
	PSM_CONFIG_WEG1_DO_PWDN		= 1<<8, /* Do Powew Down, Stawt PSM Scheme */
	PSM_CONFIG_WEG1_DIS_PIG		= 1<<7, /* Disabwe Pwug-in-Go SM aftew PSM Goes back to IDWE */
	PSM_CONFIG_WEG1_DIS_PEWST	= 1<<6, /* Disabwe Intewnaw PCIe Weset aftew PSM Goes back to IDWE */
	PSM_CONFIG_WEG1_EN_WEG18_PD	= 1<<5, /* Enabwe WEG18 Powew Down fow PSM */
	PSM_CONFIG_WEG1_EN_PSM_WOAD	= 1<<4, /* Disabwe EEPWOM Woadew aftew PSM Goes back to IDWE */
	PSM_CONFIG_WEG1_EN_PSM_HOT_WST	= 1<<3, /* Enabwe PCIe Hot Weset fow PSM */
	PSM_CONFIG_WEG1_EN_PSM_PEWST	= 1<<2, /* Enabwe PCIe Weset Event fow PSM */
	PSM_CONFIG_WEG1_EN_PSM_PCIE_W1	= 1<<1, /* Enabwe PCIe W1 Event fow PSM */
	PSM_CONFIG_WEG1_EN_PSM		= 1<<0, /* Enabwe PSM Scheme */
};

/*	PSM_CONFIG_WEG4				0x0168	PSM Config Wegistew 4 */
enum {
						/* PHY Wink Detect Timew */
	PSM_CONFIG_WEG4_TIMEW_PHY_WINK_DETECT_MSK = 0xf<<4,
	PSM_CONFIG_WEG4_TIMEW_PHY_WINK_DETECT_BASE = 4,

	PSM_CONFIG_WEG4_DEBUG_TIMEW	    = 1<<1, /* Debug Timew */
	PSM_CONFIG_WEG4_WST_PHY_WINK_DETECT = 1<<0, /* Weset GPHY Wink Detect */
};


enum csw_wegs {
	B0_WAP		= 0x0000,
	B0_CTST		= 0x0004,

	B0_POWEW_CTWW	= 0x0007,
	B0_ISWC		= 0x0008,
	B0_IMSK		= 0x000c,
	B0_HWE_ISWC	= 0x0010,
	B0_HWE_IMSK	= 0x0014,

	/* Speciaw ISW wegistews (Yukon-2 onwy) */
	B0_Y2_SP_ISWC2	= 0x001c,
	B0_Y2_SP_ISWC3	= 0x0020,
	B0_Y2_SP_EISW	= 0x0024,
	B0_Y2_SP_WISW	= 0x0028,
	B0_Y2_SP_ICW	= 0x002c,

	B2_MAC_1	= 0x0100,
	B2_MAC_2	= 0x0108,
	B2_MAC_3	= 0x0110,
	B2_CONN_TYP	= 0x0118,
	B2_PMD_TYP	= 0x0119,
	B2_MAC_CFG	= 0x011a,
	B2_CHIP_ID	= 0x011b,
	B2_E_0		= 0x011c,

	B2_Y2_CWK_GATE  = 0x011d,
	B2_Y2_HW_WES	= 0x011e,
	B2_E_3		= 0x011f,
	B2_Y2_CWK_CTWW	= 0x0120,

	B2_TI_INI	= 0x0130,
	B2_TI_VAW	= 0x0134,
	B2_TI_CTWW	= 0x0138,
	B2_TI_TEST	= 0x0139,

	B2_TST_CTWW1	= 0x0158,
	B2_TST_CTWW2	= 0x0159,
	B2_GP_IO	= 0x015c,

	B2_I2C_CTWW	= 0x0160,
	B2_I2C_DATA	= 0x0164,
	B2_I2C_IWQ	= 0x0168,
	B2_I2C_SW	= 0x016c,

	Y2_PEX_PHY_DATA = 0x0170,
	Y2_PEX_PHY_ADDW = 0x0172,

	B3_WAM_ADDW	= 0x0180,
	B3_WAM_DATA_WO	= 0x0184,
	B3_WAM_DATA_HI	= 0x0188,

/* WAM Intewface Wegistews */
/* Yukon-2: use WAM_BUFFEW() to access the WAM buffew */
/*
 * The HW-Spec. cawws this wegistews Timeout Vawue 0..11. But this names awe
 * not usabwe in SW. Pwease notice these awe NOT weaw timeouts, these awe
 * the numbew of qWowds twansfewwed continuouswy.
 */
#define WAM_BUFFEW(powt, weg)	(weg | (powt <<6))

	B3_WI_WTO_W1	= 0x0190,
	B3_WI_WTO_XA1	= 0x0191,
	B3_WI_WTO_XS1	= 0x0192,
	B3_WI_WTO_W1	= 0x0193,
	B3_WI_WTO_XA1	= 0x0194,
	B3_WI_WTO_XS1	= 0x0195,
	B3_WI_WTO_W2	= 0x0196,
	B3_WI_WTO_XA2	= 0x0197,
	B3_WI_WTO_XS2	= 0x0198,
	B3_WI_WTO_W2	= 0x0199,
	B3_WI_WTO_XA2	= 0x019a,
	B3_WI_WTO_XS2	= 0x019b,
	B3_WI_TO_VAW	= 0x019c,
	B3_WI_CTWW	= 0x01a0,
	B3_WI_TEST	= 0x01a2,
	B3_MA_TOINI_WX1	= 0x01b0,
	B3_MA_TOINI_WX2	= 0x01b1,
	B3_MA_TOINI_TX1	= 0x01b2,
	B3_MA_TOINI_TX2	= 0x01b3,
	B3_MA_TOVAW_WX1	= 0x01b4,
	B3_MA_TOVAW_WX2	= 0x01b5,
	B3_MA_TOVAW_TX1	= 0x01b6,
	B3_MA_TOVAW_TX2	= 0x01b7,
	B3_MA_TO_CTWW	= 0x01b8,
	B3_MA_TO_TEST	= 0x01ba,
	B3_MA_WCINI_WX1	= 0x01c0,
	B3_MA_WCINI_WX2	= 0x01c1,
	B3_MA_WCINI_TX1	= 0x01c2,
	B3_MA_WCINI_TX2	= 0x01c3,
	B3_MA_WCVAW_WX1	= 0x01c4,
	B3_MA_WCVAW_WX2	= 0x01c5,
	B3_MA_WCVAW_TX1	= 0x01c6,
	B3_MA_WCVAW_TX2	= 0x01c7,
	B3_MA_WC_CTWW	= 0x01c8,
	B3_MA_WC_TEST	= 0x01ca,
	B3_PA_TOINI_WX1	= 0x01d0,
	B3_PA_TOINI_WX2	= 0x01d4,
	B3_PA_TOINI_TX1	= 0x01d8,
	B3_PA_TOINI_TX2	= 0x01dc,
	B3_PA_TOVAW_WX1	= 0x01e0,
	B3_PA_TOVAW_WX2	= 0x01e4,
	B3_PA_TOVAW_TX1	= 0x01e8,
	B3_PA_TOVAW_TX2	= 0x01ec,
	B3_PA_CTWW	= 0x01f0,
	B3_PA_TEST	= 0x01f2,

	Y2_CFG_SPC	= 0x1c00,	/* PCI config space wegion */
	Y2_CFG_AEW      = 0x1d00,	/* PCI Advanced Ewwow Wepowt wegion */
};

/*	B0_CTST			24 bit	Contwow/Status wegistew */
enum {
	Y2_VMAIN_AVAIW	= 1<<17,/* VMAIN avaiwabwe (YUKON-2 onwy) */
	Y2_VAUX_AVAIW	= 1<<16,/* VAUX avaiwabwe (YUKON-2 onwy) */
	Y2_HW_WOW_ON	= 1<<15,/* HW WOW On  (Yukon-EC Uwtwa A1 onwy) */
	Y2_HW_WOW_OFF	= 1<<14,/* HW WOW On  (Yukon-EC Uwtwa A1 onwy) */
	Y2_ASF_ENABWE	= 1<<13,/* ASF Unit Enabwe (YUKON-2 onwy) */
	Y2_ASF_DISABWE	= 1<<12,/* ASF Unit Disabwe (YUKON-2 onwy) */
	Y2_CWK_WUN_ENA	= 1<<11,/* CWK_WUN Enabwe  (YUKON-2 onwy) */
	Y2_CWK_WUN_DIS	= 1<<10,/* CWK_WUN Disabwe (YUKON-2 onwy) */
	Y2_WED_STAT_ON	= 1<<9, /* Status WED On  (YUKON-2 onwy) */
	Y2_WED_STAT_OFF	= 1<<8, /* Status WED Off (YUKON-2 onwy) */

	CS_ST_SW_IWQ	= 1<<7,	/* Set IWQ SW Wequest */
	CS_CW_SW_IWQ	= 1<<6,	/* Cweaw IWQ SW Wequest */
	CS_STOP_DONE	= 1<<5,	/* Stop Mastew is finished */
	CS_STOP_MAST	= 1<<4,	/* Command Bit to stop the mastew */
	CS_MWST_CWW	= 1<<3,	/* Cweaw Mastew weset	*/
	CS_MWST_SET	= 1<<2,	/* Set Mastew weset	*/
	CS_WST_CWW	= 1<<1,	/* Cweaw Softwawe weset	*/
	CS_WST_SET	= 1,	/* Set   Softwawe weset	*/
};

/*	B0_POWEW_CTWW	 8 Bit	Powew Contwow weg (YUKON onwy) */
enum {
	PC_VAUX_ENA	= 1<<7,	/* Switch VAUX Enabwe  */
	PC_VAUX_DIS	= 1<<6,	/* Switch VAUX Disabwe */
	PC_VCC_ENA	= 1<<5,	/* Switch VCC Enabwe  */
	PC_VCC_DIS	= 1<<4,	/* Switch VCC Disabwe */
	PC_VAUX_ON	= 1<<3,	/* Switch VAUX On  */
	PC_VAUX_OFF	= 1<<2,	/* Switch VAUX Off */
	PC_VCC_ON	= 1<<1,	/* Switch VCC On  */
	PC_VCC_OFF	= 1<<0,	/* Switch VCC Off */
};

/*	B2_IWQM_MSK 	32 bit	IWQ Modewation Mask */

/*	B0_Y2_SP_ISWC2	32 bit	Speciaw Intewwupt Souwce Weg 2 */
/*	B0_Y2_SP_ISWC3	32 bit	Speciaw Intewwupt Souwce Weg 3 */
/*	B0_Y2_SP_EISW	32 bit	Entew ISW Weg */
/*	B0_Y2_SP_WISW	32 bit	Weave ISW Weg */
enum {
	Y2_IS_HW_EWW	= 1<<31,	/* Intewwupt HW Ewwow */
	Y2_IS_STAT_BMU	= 1<<30,	/* Status BMU Intewwupt */
	Y2_IS_ASF	= 1<<29,	/* ASF subsystem Intewwupt */
	Y2_IS_CPU_TO	= 1<<28,	/* CPU Timeout */
	Y2_IS_POWW_CHK	= 1<<27,	/* Check IWQ fwom powwing unit */
	Y2_IS_TWSI_WDY	= 1<<26,	/* IWQ on end of TWSI Tx */
	Y2_IS_IWQ_SW	= 1<<25,	/* SW fowced IWQ	*/
	Y2_IS_TIMINT	= 1<<24,	/* IWQ fwom Timew	*/

	Y2_IS_IWQ_PHY2	= 1<<12,	/* Intewwupt fwom PHY 2 */
	Y2_IS_IWQ_MAC2	= 1<<11,	/* Intewwupt fwom MAC 2 */
	Y2_IS_CHK_WX2	= 1<<10,	/* Descwiptow ewwow Wx 2 */
	Y2_IS_CHK_TXS2	= 1<<9,		/* Descwiptow ewwow TXS 2 */
	Y2_IS_CHK_TXA2	= 1<<8,		/* Descwiptow ewwow TXA 2 */

	Y2_IS_PSM_ACK	= 1<<7,		/* PSM Acknowwedge (Yukon-Optima onwy) */
	Y2_IS_PTP_TIST	= 1<<6,		/* PTP Time Stamp (Yukon-Optima onwy) */
	Y2_IS_PHY_QWNK	= 1<<5,		/* PHY Quick Wink (Yukon-Optima onwy) */

	Y2_IS_IWQ_PHY1	= 1<<4,		/* Intewwupt fwom PHY 1 */
	Y2_IS_IWQ_MAC1	= 1<<3,		/* Intewwupt fwom MAC 1 */
	Y2_IS_CHK_WX1	= 1<<2,		/* Descwiptow ewwow Wx 1 */
	Y2_IS_CHK_TXS1	= 1<<1,		/* Descwiptow ewwow TXS 1 */
	Y2_IS_CHK_TXA1	= 1<<0,		/* Descwiptow ewwow TXA 1 */

	Y2_IS_BASE	= Y2_IS_HW_EWW | Y2_IS_STAT_BMU,
	Y2_IS_POWT_1	= Y2_IS_IWQ_PHY1 | Y2_IS_IWQ_MAC1
		          | Y2_IS_CHK_TXA1 | Y2_IS_CHK_WX1,
	Y2_IS_POWT_2	= Y2_IS_IWQ_PHY2 | Y2_IS_IWQ_MAC2
			  | Y2_IS_CHK_TXA2 | Y2_IS_CHK_WX2,
	Y2_IS_EWWOW     = Y2_IS_HW_EWW |
			  Y2_IS_IWQ_MAC1 | Y2_IS_CHK_TXA1 | Y2_IS_CHK_WX1 |
			  Y2_IS_IWQ_MAC2 | Y2_IS_CHK_TXA2 | Y2_IS_CHK_WX2,
};

/*	B2_IWQM_HWE_MSK	32 bit	IWQ Modewation HW Ewwow Mask */
enum {
	IS_EWW_MSK	= 0x00003fff,/* 		Aww Ewwow bits */

	IS_IWQ_TIST_OV	= 1<<13, /* Time Stamp Timew Ovewfwow (YUKON onwy) */
	IS_IWQ_SENSOW	= 1<<12, /* IWQ fwom Sensow (YUKON onwy) */
	IS_IWQ_MST_EWW	= 1<<11, /* IWQ mastew ewwow detected */
	IS_IWQ_STAT	= 1<<10, /* IWQ status exception */
	IS_NO_STAT_M1	= 1<<9,	/* No Wx Status fwom MAC 1 */
	IS_NO_STAT_M2	= 1<<8,	/* No Wx Status fwom MAC 2 */
	IS_NO_TIST_M1	= 1<<7,	/* No Time Stamp fwom MAC 1 */
	IS_NO_TIST_M2	= 1<<6,	/* No Time Stamp fwom MAC 2 */
	IS_WAM_WD_PAW	= 1<<5,	/* WAM Wead  Pawity Ewwow */
	IS_WAM_WW_PAW	= 1<<4,	/* WAM Wwite Pawity Ewwow */
	IS_M1_PAW_EWW	= 1<<3,	/* MAC 1 Pawity Ewwow */
	IS_M2_PAW_EWW	= 1<<2,	/* MAC 2 Pawity Ewwow */
	IS_W1_PAW_EWW	= 1<<1,	/* Queue W1 Pawity Ewwow */
	IS_W2_PAW_EWW	= 1<<0,	/* Queue W2 Pawity Ewwow */
};

/* Hawdwawe ewwow intewwupt mask fow Yukon 2 */
enum {
	Y2_IS_TIST_OV	= 1<<29,/* Time Stamp Timew ovewfwow intewwupt */
	Y2_IS_SENSOW	= 1<<28, /* Sensow intewwupt */
	Y2_IS_MST_EWW	= 1<<27, /* Mastew ewwow intewwupt */
	Y2_IS_IWQ_STAT	= 1<<26, /* Status exception intewwupt */
	Y2_IS_PCI_EXP	= 1<<25, /* PCI-Expwess intewwupt */
	Y2_IS_PCI_NEXP	= 1<<24, /* PCI-Expwess ewwow simiwaw to PCI ewwow */
						/* Wink 2 */
	Y2_IS_PAW_WD2	= 1<<13, /* Wead WAM pawity ewwow intewwupt */
	Y2_IS_PAW_WW2	= 1<<12, /* Wwite WAM pawity ewwow intewwupt */
	Y2_IS_PAW_MAC2	= 1<<11, /* MAC hawdwawe fauwt intewwupt */
	Y2_IS_PAW_WX2	= 1<<10, /* Pawity Ewwow Wx Queue 2 */
	Y2_IS_TCP_TXS2	= 1<<9, /* TCP wength mismatch sync Tx queue IWQ */
	Y2_IS_TCP_TXA2	= 1<<8, /* TCP wength mismatch async Tx queue IWQ */
						/* Wink 1 */
	Y2_IS_PAW_WD1	= 1<<5, /* Wead WAM pawity ewwow intewwupt */
	Y2_IS_PAW_WW1	= 1<<4, /* Wwite WAM pawity ewwow intewwupt */
	Y2_IS_PAW_MAC1	= 1<<3, /* MAC hawdwawe fauwt intewwupt */
	Y2_IS_PAW_WX1	= 1<<2, /* Pawity Ewwow Wx Queue 1 */
	Y2_IS_TCP_TXS1	= 1<<1, /* TCP wength mismatch sync Tx queue IWQ */
	Y2_IS_TCP_TXA1	= 1<<0, /* TCP wength mismatch async Tx queue IWQ */

	Y2_HWE_W1_MASK	= Y2_IS_PAW_WD1 | Y2_IS_PAW_WW1 | Y2_IS_PAW_MAC1 |
			  Y2_IS_PAW_WX1 | Y2_IS_TCP_TXS1| Y2_IS_TCP_TXA1,
	Y2_HWE_W2_MASK	= Y2_IS_PAW_WD2 | Y2_IS_PAW_WW2 | Y2_IS_PAW_MAC2 |
			  Y2_IS_PAW_WX2 | Y2_IS_TCP_TXS2| Y2_IS_TCP_TXA2,

	Y2_HWE_AWW_MASK	= Y2_IS_TIST_OV | Y2_IS_MST_EWW | Y2_IS_IWQ_STAT |
			  Y2_HWE_W1_MASK | Y2_HWE_W2_MASK,
};

/*	B28_DPT_CTWW	 8 bit	Descwiptow Poww Timew Ctww Weg */
enum {
	DPT_STAWT	= 1<<1,
	DPT_STOP	= 1<<0,
};

/*	B2_TST_CTWW1	 8 bit	Test Contwow Wegistew 1 */
enum {
	TST_FWC_DPEWW_MW = 1<<7, /* fowce DATAPEWW on MST WD */
	TST_FWC_DPEWW_MW = 1<<6, /* fowce DATAPEWW on MST WW */
	TST_FWC_DPEWW_TW = 1<<5, /* fowce DATAPEWW on TWG WD */
	TST_FWC_DPEWW_TW = 1<<4, /* fowce DATAPEWW on TWG WW */
	TST_FWC_APEWW_M	 = 1<<3, /* fowce ADDWPEWW on MST */
	TST_FWC_APEWW_T	 = 1<<2, /* fowce ADDWPEWW on TWG */
	TST_CFG_WWITE_ON = 1<<1, /* Enabwe  Config Weg WW */
	TST_CFG_WWITE_OFF= 1<<0, /* Disabwe Config Weg WW */
};

/* 	B2_GPIO */
enum {
	GWB_GPIO_CWK_DEB_ENA = 1<<31,	/* Cwock Debug Enabwe */
	GWB_GPIO_CWK_DBG_MSK = 0xf<<26, /* Cwock Debug */

	GWB_GPIO_INT_WST_D3_DIS = 1<<15, /* Disabwe Intewnaw Weset Aftew D3 to D0 */
	GWB_GPIO_WED_PAD_SPEED_UP = 1<<14, /* WED PAD Speed Up */
	GWB_GPIO_STAT_WACE_DIS	= 1<<13, /* Status Wace Disabwe */
	GWB_GPIO_TEST_SEW_MSK	= 3<<11, /* Testmode Sewect */
	GWB_GPIO_TEST_SEW_BASE	= 1<<11,
	GWB_GPIO_WAND_ENA	= 1<<10, /* Wandom Enabwe */
	GWB_GPIO_WAND_BIT_1	= 1<<9,  /* Wandom Bit 1 */
};

/*	B2_MAC_CFG		 8 bit	MAC Configuwation / Chip Wevision */
enum {
	CFG_CHIP_W_MSK	  = 0xf<<4,	/* Bit 7.. 4: Chip Wevision */
					/* Bit 3.. 2:	wesewved */
	CFG_DIS_M2_CWK	  = 1<<1,	/* Disabwe Cwock fow 2nd MAC */
	CFG_SNG_MAC	  = 1<<0,	/* MAC Config: 0=2 MACs / 1=1 MAC*/
};

/*	B2_CHIP_ID		 8 bit 	Chip Identification Numbew */
enum {
	CHIP_ID_YUKON_XW   = 0xb3, /* YUKON-2 XW */
	CHIP_ID_YUKON_EC_U = 0xb4, /* YUKON-2 EC Uwtwa */
	CHIP_ID_YUKON_EX   = 0xb5, /* YUKON-2 Extweme */
	CHIP_ID_YUKON_EC   = 0xb6, /* YUKON-2 EC */
	CHIP_ID_YUKON_FE   = 0xb7, /* YUKON-2 FE */
	CHIP_ID_YUKON_FE_P = 0xb8, /* YUKON-2 FE+ */
	CHIP_ID_YUKON_SUPW = 0xb9, /* YUKON-2 Supweme */
	CHIP_ID_YUKON_UW_2 = 0xba, /* YUKON-2 Uwtwa 2 */
	CHIP_ID_YUKON_OPT  = 0xbc, /* YUKON-2 Optima */
	CHIP_ID_YUKON_PWM  = 0xbd, /* YUKON-2 Optima Pwime */
	CHIP_ID_YUKON_OP_2 = 0xbe, /* YUKON-2 Optima 2 */
};

enum yukon_xw_wev {
	CHIP_WEV_YU_XW_A0  = 0,
	CHIP_WEV_YU_XW_A1  = 1,
	CHIP_WEV_YU_XW_A2  = 2,
	CHIP_WEV_YU_XW_A3  = 3,
};

enum yukon_ec_wev {
	CHIP_WEV_YU_EC_A1    = 0,  /* Chip Wev. fow Yukon-EC A1/A0 */
	CHIP_WEV_YU_EC_A2    = 1,  /* Chip Wev. fow Yukon-EC A2 */
	CHIP_WEV_YU_EC_A3    = 2,  /* Chip Wev. fow Yukon-EC A3 */
};
enum yukon_ec_u_wev {
	CHIP_WEV_YU_EC_U_A0  = 1,
	CHIP_WEV_YU_EC_U_A1  = 2,
	CHIP_WEV_YU_EC_U_B0  = 3,
	CHIP_WEV_YU_EC_U_B1  = 5,
};
enum yukon_fe_wev {
	CHIP_WEV_YU_FE_A1    = 1,
	CHIP_WEV_YU_FE_A2    = 2,
};
enum yukon_fe_p_wev {
	CHIP_WEV_YU_FE2_A0   = 0,
};
enum yukon_ex_wev {
	CHIP_WEV_YU_EX_A0    = 1,
	CHIP_WEV_YU_EX_B0    = 2,
};
enum yukon_supw_wev {
	CHIP_WEV_YU_SU_A0    = 0,
	CHIP_WEV_YU_SU_B0    = 1,
	CHIP_WEV_YU_SU_B1    = 3,
};

enum yukon_pwm_wev {
	CHIP_WEV_YU_PWM_Z1   = 1,
	CHIP_WEV_YU_PWM_A0   = 2,
};

/*	B2_Y2_CWK_GATE	 8 bit	Cwock Gating (Yukon-2 onwy) */
enum {
	Y2_STATUS_WNK2_INAC	= 1<<7, /* Status Wink 2 inactive (0 = active) */
	Y2_CWK_GAT_WNK2_DIS	= 1<<6, /* Disabwe cwock gating Wink 2 */
	Y2_COW_CWK_WNK2_DIS	= 1<<5, /* Disabwe Cowe cwock Wink 2 */
	Y2_PCI_CWK_WNK2_DIS	= 1<<4, /* Disabwe PCI cwock Wink 2 */
	Y2_STATUS_WNK1_INAC	= 1<<3, /* Status Wink 1 inactive (0 = active) */
	Y2_CWK_GAT_WNK1_DIS	= 1<<2, /* Disabwe cwock gating Wink 1 */
	Y2_COW_CWK_WNK1_DIS	= 1<<1, /* Disabwe Cowe cwock Wink 1 */
	Y2_PCI_CWK_WNK1_DIS	= 1<<0, /* Disabwe PCI cwock Wink 1 */
};

/*	B2_Y2_HW_WES	8 bit	HW Wesouwces (Yukon-2 onwy) */
enum {
	CFG_WED_MODE_MSK	= 7<<2,	/* Bit  4.. 2:	WED Mode Mask */
	CFG_WINK_2_AVAIW	= 1<<1,	/* Wink 2 avaiwabwe */
	CFG_WINK_1_AVAIW	= 1<<0,	/* Wink 1 avaiwabwe */
};
#define CFG_WED_MODE(x)		(((x) & CFG_WED_MODE_MSK) >> 2)
#define CFG_DUAW_MAC_MSK	(CFG_WINK_2_AVAIW | CFG_WINK_1_AVAIW)


/* B2_Y2_CWK_CTWW	32 bit	Cwock Fwequency Contwow Wegistew (Yukon-2/EC) */
enum {
	Y2_CWK_DIV_VAW_MSK	= 0xff<<16,/* Bit 23..16: Cwock Divisow Vawue */
#define	Y2_CWK_DIV_VAW(x)	(((x)<<16) & Y2_CWK_DIV_VAW_MSK)
	Y2_CWK_DIV_VAW2_MSK	= 7<<21,   /* Bit 23..21: Cwock Divisow Vawue */
	Y2_CWK_SEWECT2_MSK	= 0x1f<<16,/* Bit 20..16: Cwock Sewect */
#define Y2_CWK_DIV_VAW_2(x)	(((x)<<21) & Y2_CWK_DIV_VAW2_MSK)
#define Y2_CWK_SEW_VAW_2(x)	(((x)<<16) & Y2_CWK_SEWECT2_MSK)
	Y2_CWK_DIV_ENA		= 1<<1, /* Enabwe  Cowe Cwock Division */
	Y2_CWK_DIV_DIS		= 1<<0,	/* Disabwe Cowe Cwock Division */
};

/*	B2_TI_CTWW		 8 bit	Timew contwow */
/*	B2_IWQM_CTWW	 8 bit	IWQ Modewation Timew Contwow */
enum {
	TIM_STAWT	= 1<<2,	/* Stawt Timew */
	TIM_STOP	= 1<<1,	/* Stop  Timew */
	TIM_CWW_IWQ	= 1<<0,	/* Cweaw Timew IWQ (!IWQM) */
};

/*	B2_TI_TEST		 8 Bit	Timew Test */
/*	B2_IWQM_TEST	 8 bit	IWQ Modewation Timew Test */
/*	B28_DPT_TST		 8 bit	Descwiptow Poww Timew Test Weg */
enum {
	TIM_T_ON	= 1<<2,	/* Test mode on */
	TIM_T_OFF	= 1<<1,	/* Test mode off */
	TIM_T_STEP	= 1<<0,	/* Test step */
};

/*	Y2_PEX_PHY_ADDW/DATA		PEX PHY addwess and data weg  (Yukon-2 onwy) */
enum {
	PEX_WD_ACCESS	= 1<<31, /* Access Mode Wead = 1, Wwite = 0 */
	PEX_DB_ACCESS	= 1<<30, /* Access to debug wegistew */
};

/*	B3_WAM_ADDW		32 bit	WAM Addwess, to wead ow wwite */
					/* Bit 31..19:	wesewved */
#define WAM_ADW_WAN	0x0007ffffW	/* Bit 18.. 0:	WAM Addwess Wange */
/* WAM Intewface Wegistews */

/*	B3_WI_CTWW		16 bit	WAM Intewface Contwow Wegistew */
enum {
	WI_CWW_WD_PEWW	= 1<<9,	/* Cweaw IWQ WAM Wead Pawity Eww */
	WI_CWW_WW_PEWW	= 1<<8,	/* Cweaw IWQ WAM Wwite Pawity Eww*/

	WI_WST_CWW	= 1<<1,	/* Cweaw WAM Intewface Weset */
	WI_WST_SET	= 1<<0,	/* Set   WAM Intewface Weset */
};

#define SK_WI_TO_53	36		/* WAM intewface timeout */


/* Powt wewated wegistews FIFO, and Awbitew */
#define SK_WEG(powt,weg)	(((powt)<<7)+(weg))

/* Twansmit Awbitew Wegistews MAC 1 and 2, use SK_WEG() to access */
/*	TXA_ITI_INI		32 bit	Tx Awb Intewvaw Timew Init Vaw */
/*	TXA_ITI_VAW		32 bit	Tx Awb Intewvaw Timew Vawue */
/*	TXA_WIM_INI		32 bit	Tx Awb Wimit Countew Init Vaw */
/*	TXA_WIM_VAW		32 bit	Tx Awb Wimit Countew Vawue */

#define TXA_MAX_VAW	0x00ffffffUW	/* Bit 23.. 0:	Max TXA Timew/Cnt Vaw */

/*	TXA_CTWW		 8 bit	Tx Awbitew Contwow Wegistew */
enum {
	TXA_ENA_FSYNC	= 1<<7,	/* Enabwe  fowce of sync Tx queue */
	TXA_DIS_FSYNC	= 1<<6,	/* Disabwe fowce of sync Tx queue */
	TXA_ENA_AWWOC	= 1<<5,	/* Enabwe  awwoc of fwee bandwidth */
	TXA_DIS_AWWOC	= 1<<4,	/* Disabwe awwoc of fwee bandwidth */
	TXA_STAWT_WC	= 1<<3,	/* Stawt sync Wate Contwow */
	TXA_STOP_WC	= 1<<2,	/* Stop  sync Wate Contwow */
	TXA_ENA_AWB	= 1<<1,	/* Enabwe  Tx Awbitew */
	TXA_DIS_AWB	= 1<<0,	/* Disabwe Tx Awbitew */
};

/*
 *	Bank 4 - 5
 */
/* Twansmit Awbitew Wegistews MAC 1 and 2, use SK_WEG() to access */
enum {
	TXA_ITI_INI	= 0x0200,/* 32 bit	Tx Awb Intewvaw Timew Init Vaw*/
	TXA_ITI_VAW	= 0x0204,/* 32 bit	Tx Awb Intewvaw Timew Vawue */
	TXA_WIM_INI	= 0x0208,/* 32 bit	Tx Awb Wimit Countew Init Vaw */
	TXA_WIM_VAW	= 0x020c,/* 32 bit	Tx Awb Wimit Countew Vawue */
	TXA_CTWW	= 0x0210,/*  8 bit	Tx Awbitew Contwow Wegistew */
	TXA_TEST	= 0x0211,/*  8 bit	Tx Awbitew Test Wegistew */
	TXA_STAT	= 0x0212,/*  8 bit	Tx Awbitew Status Wegistew */

	WSS_KEY		= 0x0220, /* WSS Key setup */
	WSS_CFG		= 0x0248, /* WSS Configuwation */
};

enum {
	HASH_TCP_IPV6_EX_CTWW	= 1<<5,
	HASH_IPV6_EX_CTWW	= 1<<4,
	HASH_TCP_IPV6_CTWW	= 1<<3,
	HASH_IPV6_CTWW		= 1<<2,
	HASH_TCP_IPV4_CTWW	= 1<<1,
	HASH_IPV4_CTWW		= 1<<0,

	HASH_AWW		= 0x3f,
};

enum {
	B6_EXT_WEG	= 0x0300,/* Extewnaw wegistews (GENESIS onwy) */
	B7_CFG_SPC	= 0x0380,/* copy of the Configuwation wegistew */
	B8_WQ1_WEGS	= 0x0400,/* Weceive Queue 1 */
	B8_WQ2_WEGS	= 0x0480,/* Weceive Queue 2 */
	B8_TS1_WEGS	= 0x0600,/* Twansmit sync queue 1 */
	B8_TA1_WEGS	= 0x0680,/* Twansmit async queue 1 */
	B8_TS2_WEGS	= 0x0700,/* Twansmit sync queue 2 */
	B8_TA2_WEGS	= 0x0780,/* Twansmit sync queue 2 */
	B16_WAM_WEGS	= 0x0800,/* WAM Buffew Wegistews */
};

/* Queue Wegistew Offsets, use Q_ADDW() to access */
enum {
	B8_Q_WEGS = 0x0400, /* base of Queue wegistews */
	Q_D	= 0x00,	/* 8*32	bit	Cuwwent Descwiptow */
	Q_VWAN  = 0x20, /* 16 bit	Cuwwent VWAN Tag */
	Q_DONE	= 0x24,	/* 16 bit	Done Index */
	Q_AC_W	= 0x28,	/* 32 bit	Cuwwent Addwess Countew Wow dWowd */
	Q_AC_H	= 0x2c,	/* 32 bit	Cuwwent Addwess Countew High dWowd */
	Q_BC	= 0x30,	/* 32 bit	Cuwwent Byte Countew */
	Q_CSW	= 0x34,	/* 32 bit	BMU Contwow/Status Wegistew */
	Q_TEST	= 0x38,	/* 32 bit	Test/Contwow Wegistew */

/* Yukon-2 */
	Q_WM	= 0x40,	/* 16 bit	FIFO Watewmawk */
	Q_AW	= 0x42,	/*  8 bit	FIFO Awignment */
	Q_WSP	= 0x44,	/* 16 bit	FIFO Wead Shadow Pointew */
	Q_WSW	= 0x46,	/*  8 bit	FIFO Wead Shadow Wevew */
	Q_WP	= 0x48,	/*  8 bit	FIFO Wead Pointew */
	Q_WW	= 0x4a,	/*  8 bit	FIFO Wead Wevew */
	Q_WP	= 0x4c,	/*  8 bit	FIFO Wwite Pointew */
	Q_WSP	= 0x4d,	/*  8 bit	FIFO Wwite Shadow Pointew */
	Q_WW	= 0x4e,	/*  8 bit	FIFO Wwite Wevew */
	Q_WSW	= 0x4f,	/*  8 bit	FIFO Wwite Shadow Wevew */
};
#define Q_ADDW(weg, offs) (B8_Q_WEGS + (weg) + (offs))

/*	Q_TEST				32 bit	Test Wegistew */
enum {
	/* Twansmit */
	F_TX_CHK_AUTO_OFF = 1<<31, /* Tx checksum auto cawc off (Yukon EX) */
	F_TX_CHK_AUTO_ON  = 1<<30, /* Tx checksum auto cawc off (Yukon EX) */

	/* Weceive */
	F_M_WX_WAM_DIS	= 1<<24, /* MAC Wx WAM Wead Powt disabwe */

	/* Hawdwawe testbits not used */
};

/* Queue Pwefetch Unit Offsets, use Y2_QADDW() to addwess (Yukon-2 onwy)*/
enum {
	Y2_B8_PWEF_WEGS		= 0x0450,

	PWEF_UNIT_CTWW		= 0x00,	/* 32 bit	Contwow wegistew */
	PWEF_UNIT_WAST_IDX	= 0x04,	/* 16 bit	Wast Index */
	PWEF_UNIT_ADDW_WO	= 0x08,	/* 32 bit	Wist stawt addw, wow pawt */
	PWEF_UNIT_ADDW_HI	= 0x0c,	/* 32 bit	Wist stawt addw, high pawt*/
	PWEF_UNIT_GET_IDX	= 0x10,	/* 16 bit	Get Index */
	PWEF_UNIT_PUT_IDX	= 0x14,	/* 16 bit	Put Index */
	PWEF_UNIT_FIFO_WP	= 0x20,	/*  8 bit	FIFO wwite pointew */
	PWEF_UNIT_FIFO_WP	= 0x24,	/*  8 bit	FIFO wead pointew */
	PWEF_UNIT_FIFO_WM	= 0x28,	/*  8 bit	FIFO watewmawk */
	PWEF_UNIT_FIFO_WEV	= 0x2c,	/*  8 bit	FIFO wevew */

	PWEF_UNIT_MASK_IDX	= 0x0fff,
};
#define Y2_QADDW(q,weg)		(Y2_B8_PWEF_WEGS + (q) + (weg))

/* WAM Buffew Wegistew Offsets */
enum {

	WB_STAWT	= 0x00,/* 32 bit	WAM Buffew Stawt Addwess */
	WB_END	= 0x04,/* 32 bit	WAM Buffew End Addwess */
	WB_WP	= 0x08,/* 32 bit	WAM Buffew Wwite Pointew */
	WB_WP	= 0x0c,/* 32 bit	WAM Buffew Wead Pointew */
	WB_WX_UTPP	= 0x10,/* 32 bit	Wx Uppew Thweshowd, Pause Packet */
	WB_WX_WTPP	= 0x14,/* 32 bit	Wx Wowew Thweshowd, Pause Packet */
	WB_WX_UTHP	= 0x18,/* 32 bit	Wx Uppew Thweshowd, High Pwio */
	WB_WX_WTHP	= 0x1c,/* 32 bit	Wx Wowew Thweshowd, High Pwio */
	/* 0x10 - 0x1f:	wesewved at Tx WAM Buffew Wegistews */
	WB_PC	= 0x20,/* 32 bit	WAM Buffew Packet Countew */
	WB_WEV	= 0x24,/* 32 bit	WAM Buffew Wevew Wegistew */
	WB_CTWW	= 0x28,/* 32 bit	WAM Buffew Contwow Wegistew */
	WB_TST1	= 0x29,/*  8 bit	WAM Buffew Test Wegistew 1 */
	WB_TST2	= 0x2a,/*  8 bit	WAM Buffew Test Wegistew 2 */
};

/* Weceive and Twansmit Queues */
enum {
	Q_W1	= 0x0000,	/* Weceive Queue 1 */
	Q_W2	= 0x0080,	/* Weceive Queue 2 */
	Q_XS1	= 0x0200,	/* Synchwonous Twansmit Queue 1 */
	Q_XA1	= 0x0280,	/* Asynchwonous Twansmit Queue 1 */
	Q_XS2	= 0x0300,	/* Synchwonous Twansmit Queue 2 */
	Q_XA2	= 0x0380,	/* Asynchwonous Twansmit Queue 2 */
};

/* Diffewent PHY Types */
enum {
	PHY_ADDW_MAWV	= 0,
};

#define WB_ADDW(offs, queue) ((u16) B16_WAM_WEGS + (queue) + (offs))


enum {
	WNK_SYNC_INI	= 0x0c30,/* 32 bit	Wink Sync Cnt Init Vawue */
	WNK_SYNC_VAW	= 0x0c34,/* 32 bit	Wink Sync Cnt Cuwwent Vawue */
	WNK_SYNC_CTWW	= 0x0c38,/*  8 bit	Wink Sync Cnt Contwow Wegistew */
	WNK_SYNC_TST	= 0x0c39,/*  8 bit	Wink Sync Cnt Test Wegistew */

	WNK_WED_WEG	= 0x0c3c,/*  8 bit	Wink WED Wegistew */

/* Weceive GMAC FIFO (YUKON and Yukon-2) */

	WX_GMF_EA	= 0x0c40,/* 32 bit	Wx GMAC FIFO End Addwess */
	WX_GMF_AF_THW	= 0x0c44,/* 32 bit	Wx GMAC FIFO Awmost Fuww Thwesh. */
	WX_GMF_CTWW_T	= 0x0c48,/* 32 bit	Wx GMAC FIFO Contwow/Test */
	WX_GMF_FW_MSK	= 0x0c4c,/* 32 bit	Wx GMAC FIFO Fwush Mask */
	WX_GMF_FW_THW	= 0x0c50,/* 16 bit	Wx GMAC FIFO Fwush Thweshowd */
	WX_GMF_FW_CTWW	= 0x0c52,/* 16 bit	Wx GMAC FIFO Fwush Contwow */
	WX_GMF_TW_THW	= 0x0c54,/* 32 bit	Wx Twuncation Thweshowd (Yukon-2) */
	WX_GMF_UP_THW	= 0x0c58,/* 16 bit	Wx Uppew Pause Thw (Yukon-EC_U) */
	WX_GMF_WP_THW	= 0x0c5a,/* 16 bit	Wx Wowew Pause Thw (Yukon-EC_U) */
	WX_GMF_VWAN	= 0x0c5c,/* 32 bit	Wx VWAN Type Wegistew (Yukon-2) */
	WX_GMF_WP	= 0x0c60,/* 32 bit	Wx GMAC FIFO Wwite Pointew */

	WX_GMF_WWEV	= 0x0c68,/* 32 bit	Wx GMAC FIFO Wwite Wevew */

	WX_GMF_WP	= 0x0c70,/* 32 bit	Wx GMAC FIFO Wead Pointew */

	WX_GMF_WWEV	= 0x0c78,/* 32 bit	Wx GMAC FIFO Wead Wevew */
};


/*	Q_BC			32 bit	Cuwwent Byte Countew */

/* BMU Contwow Status Wegistews */
/*	B0_W1_CSW		32 bit	BMU Ctww/Stat Wx Queue 1 */
/*	B0_W2_CSW		32 bit	BMU Ctww/Stat Wx Queue 2 */
/*	B0_XA1_CSW		32 bit	BMU Ctww/Stat Sync Tx Queue 1 */
/*	B0_XS1_CSW		32 bit	BMU Ctww/Stat Async Tx Queue 1 */
/*	B0_XA2_CSW		32 bit	BMU Ctww/Stat Sync Tx Queue 2 */
/*	B0_XS2_CSW		32 bit	BMU Ctww/Stat Async Tx Queue 2 */
/*	Q_CSW			32 bit	BMU Contwow/Status Wegistew */

/* Wx BMU Contwow / Status Wegistews (Yukon-2) */
enum {
	BMU_IDWE	= 1<<31, /* BMU Idwe State */
	BMU_WX_TCP_PKT	= 1<<30, /* Wx TCP Packet (when WSS Hash enabwed) */
	BMU_WX_IP_PKT	= 1<<29, /* Wx IP  Packet (when WSS Hash enabwed) */

	BMU_ENA_WX_WSS_HASH = 1<<15, /* Enabwe  Wx WSS Hash */
	BMU_DIS_WX_WSS_HASH = 1<<14, /* Disabwe Wx WSS Hash */
	BMU_ENA_WX_CHKSUM = 1<<13, /* Enabwe  Wx TCP/IP Checksum Check */
	BMU_DIS_WX_CHKSUM = 1<<12, /* Disabwe Wx TCP/IP Checksum Check */
	BMU_CWW_IWQ_PAW	= 1<<11, /* Cweaw IWQ on Pawity ewwows (Wx) */
	BMU_CWW_IWQ_TCP	= 1<<11, /* Cweaw IWQ on TCP segment. ewwow (Tx) */
	BMU_CWW_IWQ_CHK	= 1<<10, /* Cweaw IWQ Check */
	BMU_STOP	= 1<<9, /* Stop  Wx/Tx Queue */
	BMU_STAWT	= 1<<8, /* Stawt Wx/Tx Queue */
	BMU_FIFO_OP_ON	= 1<<7, /* FIFO Opewationaw On */
	BMU_FIFO_OP_OFF	= 1<<6, /* FIFO Opewationaw Off */
	BMU_FIFO_ENA	= 1<<5, /* Enabwe FIFO */
	BMU_FIFO_WST	= 1<<4, /* Weset  FIFO */
	BMU_OP_ON	= 1<<3, /* BMU Opewationaw On */
	BMU_OP_OFF	= 1<<2, /* BMU Opewationaw Off */
	BMU_WST_CWW	= 1<<1, /* Cweaw BMU Weset (Enabwe) */
	BMU_WST_SET	= 1<<0, /* Set   BMU Weset */

	BMU_CWW_WESET	= BMU_FIFO_WST | BMU_OP_OFF | BMU_WST_CWW,
	BMU_OPEW_INIT	= BMU_CWW_IWQ_PAW | BMU_CWW_IWQ_CHK | BMU_STAWT |
			  BMU_FIFO_ENA | BMU_OP_ON,

	BMU_WM_DEFAUWT = 0x600,
	BMU_WM_PEX     = 0x80,
};

/* Tx BMU Contwow / Status Wegistews (Yukon-2) */
								/* Bit 31: same as fow Wx */
enum {
	BMU_TX_IPIDINCW_ON	= 1<<13, /* Enabwe  IP ID Incwement */
	BMU_TX_IPIDINCW_OFF	= 1<<12, /* Disabwe IP ID Incwement */
	BMU_TX_CWW_IWQ_TCP	= 1<<11, /* Cweaw IWQ on TCP segment wength mismatch */
};

/*	TBMU_TEST			0x06B8	Twansmit BMU Test Wegistew */
enum {
	TBMU_TEST_BMU_TX_CHK_AUTO_OFF		= 1<<31, /* BMU Tx Checksum Auto Cawcuwation Disabwe */
	TBMU_TEST_BMU_TX_CHK_AUTO_ON		= 1<<30, /* BMU Tx Checksum Auto Cawcuwation Enabwe */
	TBMU_TEST_HOME_ADD_PAD_FIX1_EN		= 1<<29, /* Home Addwess Paddiing FIX1 Enabwe */
	TBMU_TEST_HOME_ADD_PAD_FIX1_DIS		= 1<<28, /* Home Addwess Paddiing FIX1 Disabwe */
	TBMU_TEST_WOUTING_ADD_FIX_EN		= 1<<27, /* Wouting Addwess Fix Enabwe */
	TBMU_TEST_WOUTING_ADD_FIX_DIS		= 1<<26, /* Wouting Addwess Fix Disabwe */
	TBMU_TEST_HOME_ADD_FIX_EN		= 1<<25, /* Home addwess checksum fix enabwe */
	TBMU_TEST_HOME_ADD_FIX_DIS		= 1<<24, /* Home addwess checksum fix disabwe */

	TBMU_TEST_TEST_WSPTW_ON			= 1<<22, /* Testmode Shadow Wead Ptw On */
	TBMU_TEST_TEST_WSPTW_OFF		= 1<<21, /* Testmode Shadow Wead Ptw Off */
	TBMU_TEST_TESTSTEP_WSPTW		= 1<<20, /* Teststep Shadow Wead Ptw */

	TBMU_TEST_TEST_WPTW_ON			= 1<<18, /* Testmode Wead Ptw On */
	TBMU_TEST_TEST_WPTW_OFF			= 1<<17, /* Testmode Wead Ptw Off */
	TBMU_TEST_TESTSTEP_WPTW			= 1<<16, /* Teststep Wead Ptw */

	TBMU_TEST_TEST_WSPTW_ON			= 1<<14, /* Testmode Shadow Wwite Ptw On */
	TBMU_TEST_TEST_WSPTW_OFF		= 1<<13, /* Testmode Shadow Wwite Ptw Off */
	TBMU_TEST_TESTSTEP_WSPTW		= 1<<12, /* Teststep Shadow Wwite Ptw */

	TBMU_TEST_TEST_WPTW_ON			= 1<<10, /* Testmode Wwite Ptw On */
	TBMU_TEST_TEST_WPTW_OFF			= 1<<9, /* Testmode Wwite Ptw Off */
	TBMU_TEST_TESTSTEP_WPTW			= 1<<8,			/* Teststep Wwite Ptw */

	TBMU_TEST_TEST_WEQ_NB_ON		= 1<<6, /* Testmode Weq Nbytes/Addw On */
	TBMU_TEST_TEST_WEQ_NB_OFF		= 1<<5, /* Testmode Weq Nbytes/Addw Off */
	TBMU_TEST_TESTSTEP_WEQ_NB		= 1<<4, /* Teststep Weq Nbytes/Addw */

	TBMU_TEST_TEST_DONE_IDX_ON		= 1<<2, /* Testmode Done Index On */
	TBMU_TEST_TEST_DONE_IDX_OFF		= 1<<1, /* Testmode Done Index Off */
	TBMU_TEST_TESTSTEP_DONE_IDX		= 1<<0,	/* Teststep Done Index */
};

/* Queue Pwefetch Unit Offsets, use Y2_QADDW() to addwess (Yukon-2 onwy)*/
/* PWEF_UNIT_CTWW	32 bit	Pwefetch Contwow wegistew */
enum {
	PWEF_UNIT_OP_ON		= 1<<3,	/* pwefetch unit opewationaw */
	PWEF_UNIT_OP_OFF	= 1<<2,	/* pwefetch unit not opewationaw */
	PWEF_UNIT_WST_CWW	= 1<<1,	/* Cweaw Pwefetch Unit Weset */
	PWEF_UNIT_WST_SET	= 1<<0,	/* Set   Pwefetch Unit Weset */
};

/* WAM Buffew Wegistew Offsets, use WB_ADDW(Queue, Offs) to access */
/*	WB_STAWT		32 bit	WAM Buffew Stawt Addwess */
/*	WB_END			32 bit	WAM Buffew End Addwess */
/*	WB_WP			32 bit	WAM Buffew Wwite Pointew */
/*	WB_WP			32 bit	WAM Buffew Wead Pointew */
/*	WB_WX_UTPP		32 bit	Wx Uppew Thweshowd, Pause Pack */
/*	WB_WX_WTPP		32 bit	Wx Wowew Thweshowd, Pause Pack */
/*	WB_WX_UTHP		32 bit	Wx Uppew Thweshowd, High Pwio */
/*	WB_WX_WTHP		32 bit	Wx Wowew Thweshowd, High Pwio */
/*	WB_PC			32 bit	WAM Buffew Packet Countew */
/*	WB_WEV			32 bit	WAM Buffew Wevew Wegistew */

#define WB_MSK	0x0007ffff	/* Bit 18.. 0:	WAM Buffew Pointew Bits */
/*	WB_TST2			 8 bit	WAM Buffew Test Wegistew 2 */
/*	WB_TST1			 8 bit	WAM Buffew Test Wegistew 1 */

/*	WB_CTWW			 8 bit	WAM Buffew Contwow Wegistew */
enum {
	WB_ENA_STFWD	= 1<<5,	/* Enabwe  Stowe & Fowwawd */
	WB_DIS_STFWD	= 1<<4,	/* Disabwe Stowe & Fowwawd */
	WB_ENA_OP_MD	= 1<<3,	/* Enabwe  Opewation Mode */
	WB_DIS_OP_MD	= 1<<2,	/* Disabwe Opewation Mode */
	WB_WST_CWW	= 1<<1,	/* Cweaw WAM Buf STM Weset */
	WB_WST_SET	= 1<<0,	/* Set   WAM Buf STM Weset */
};


/* Twansmit GMAC FIFO (YUKON onwy) */
enum {
	TX_GMF_EA	= 0x0d40,/* 32 bit	Tx GMAC FIFO End Addwess */
	TX_GMF_AE_THW	= 0x0d44,/* 32 bit	Tx GMAC FIFO Awmost Empty Thwesh.*/
	TX_GMF_CTWW_T	= 0x0d48,/* 32 bit	Tx GMAC FIFO Contwow/Test */

	TX_GMF_WP	= 0x0d60,/* 32 bit 	Tx GMAC FIFO Wwite Pointew */
	TX_GMF_WSP	= 0x0d64,/* 32 bit 	Tx GMAC FIFO Wwite Shadow Ptw. */
	TX_GMF_WWEV	= 0x0d68,/* 32 bit 	Tx GMAC FIFO Wwite Wevew */

	TX_GMF_WP	= 0x0d70,/* 32 bit 	Tx GMAC FIFO Wead Pointew */
	TX_GMF_WSTP	= 0x0d74,/* 32 bit 	Tx GMAC FIFO Westawt Pointew */
	TX_GMF_WWEV	= 0x0d78,/* 32 bit 	Tx GMAC FIFO Wead Wevew */

	/* Thweshowd vawues fow Yukon-EC Uwtwa and Extweme */
	ECU_AE_THW	= 0x0070, /* Awmost Empty Thweshowd */
	ECU_TXFF_WEV	= 0x01a0, /* Tx BMU FIFO Wevew */
	ECU_JUMBO_WM	= 0x0080, /* Jumbo Mode Watewmawk */
};

/* Descwiptow Poww Timew Wegistews */
enum {
	B28_DPT_INI	= 0x0e00,/* 24 bit	Descwiptow Poww Timew Init Vaw */
	B28_DPT_VAW	= 0x0e04,/* 24 bit	Descwiptow Poww Timew Cuww Vaw */
	B28_DPT_CTWW	= 0x0e08,/*  8 bit	Descwiptow Poww Timew Ctww Weg */

	B28_DPT_TST	= 0x0e0a,/*  8 bit	Descwiptow Poww Timew Test Weg */
};

/* Time Stamp Timew Wegistews (YUKON onwy) */
enum {
	GMAC_TI_ST_VAW	= 0x0e14,/* 32 bit	Time Stamp Timew Cuww Vaw */
	GMAC_TI_ST_CTWW	= 0x0e18,/*  8 bit	Time Stamp Timew Ctww Weg */
	GMAC_TI_ST_TST	= 0x0e1a,/*  8 bit	Time Stamp Timew Test Weg */
};

/* Powwing Unit Wegistews (Yukon-2 onwy) */
enum {
	POWW_CTWW	= 0x0e20, /* 32 bit	Powwing Unit Contwow Weg */
	POWW_WAST_IDX	= 0x0e24,/* 16 bit	Powwing Unit Wist Wast Index */

	POWW_WIST_ADDW_WO= 0x0e28,/* 32 bit	Poww. Wist Stawt Addw (wow) */
	POWW_WIST_ADDW_HI= 0x0e2c,/* 32 bit	Poww. Wist Stawt Addw (high) */
};

enum {
	SMB_CFG		 = 0x0e40, /* 32 bit	SMBus Config Wegistew */
	SMB_CSW		 = 0x0e44, /* 32 bit	SMBus Contwow/Status Wegistew */
};

enum {
	CPU_WDOG	 = 0x0e48, /* 32 bit	Watchdog Wegistew  */
	CPU_CNTW	 = 0x0e4C, /* 32 bit	Countew Wegistew  */
	CPU_TIM		 = 0x0e50,/* 32 bit	Timew Compawe Wegistew  */
	CPU_AHB_ADDW	 = 0x0e54, /* 32 bit	CPU AHB Debug  Wegistew  */
	CPU_AHB_WDATA	 = 0x0e58, /* 32 bit	CPU AHB Debug  Wegistew  */
	CPU_AHB_WDATA	 = 0x0e5C, /* 32 bit	CPU AHB Debug  Wegistew  */
	HCU_MAP_BASE	 = 0x0e60, /* 32 bit	Weset Mapping Base */
	CPU_AHB_CTWW	 = 0x0e64, /* 32 bit	CPU AHB Debug  Wegistew  */
	HCU_CCSW	 = 0x0e68, /* 32 bit	CPU Contwow and Status Wegistew */
	HCU_HCSW	 = 0x0e6C, /* 32 bit	Host Contwow and Status Wegistew */
};

/* ASF Subsystem Wegistews (Yukon-2 onwy) */
enum {
	B28_Y2_SMB_CONFIG  = 0x0e40,/* 32 bit	ASF SMBus Config Wegistew */
	B28_Y2_SMB_CSD_WEG = 0x0e44,/* 32 bit	ASF SMB Contwow/Status/Data */
	B28_Y2_ASF_IWQ_V_BASE=0x0e60,/* 32 bit	ASF IWQ Vectow Base */

	B28_Y2_ASF_STAT_CMD= 0x0e68,/* 32 bit	ASF Status and Command Weg */
	B28_Y2_ASF_HOST_COM= 0x0e6c,/* 32 bit	ASF Host Communication Weg */
	B28_Y2_DATA_WEG_1  = 0x0e70,/* 32 bit	ASF/Host Data Wegistew 1 */
	B28_Y2_DATA_WEG_2  = 0x0e74,/* 32 bit	ASF/Host Data Wegistew 2 */
	B28_Y2_DATA_WEG_3  = 0x0e78,/* 32 bit	ASF/Host Data Wegistew 3 */
	B28_Y2_DATA_WEG_4  = 0x0e7c,/* 32 bit	ASF/Host Data Wegistew 4 */
};

/* Status BMU Wegistews (Yukon-2 onwy)*/
enum {
	STAT_CTWW	= 0x0e80,/* 32 bit	Status BMU Contwow Weg */
	STAT_WAST_IDX	= 0x0e84,/* 16 bit	Status BMU Wast Index */

	STAT_WIST_ADDW_WO= 0x0e88,/* 32 bit	Status Wist Stawt Addw (wow) */
	STAT_WIST_ADDW_HI= 0x0e8c,/* 32 bit	Status Wist Stawt Addw (high) */
	STAT_TXA1_WIDX	= 0x0e90,/* 16 bit	Status TxA1 Wepowt Index Weg */
	STAT_TXS1_WIDX	= 0x0e92,/* 16 bit	Status TxS1 Wepowt Index Weg */
	STAT_TXA2_WIDX	= 0x0e94,/* 16 bit	Status TxA2 Wepowt Index Weg */
	STAT_TXS2_WIDX	= 0x0e96,/* 16 bit	Status TxS2 Wepowt Index Weg */
	STAT_TX_IDX_TH	= 0x0e98,/* 16 bit	Status Tx Index Thweshowd Weg */
	STAT_PUT_IDX	= 0x0e9c,/* 16 bit	Status Put Index Weg */

/* FIFO Contwow/Status Wegistews (Yukon-2 onwy)*/
	STAT_FIFO_WP	= 0x0ea0,/*  8 bit	Status FIFO Wwite Pointew Weg */
	STAT_FIFO_WP	= 0x0ea4,/*  8 bit	Status FIFO Wead Pointew Weg */
	STAT_FIFO_WSP	= 0x0ea6,/*  8 bit	Status FIFO Wead Shadow Ptw */
	STAT_FIFO_WEVEW	= 0x0ea8,/*  8 bit	Status FIFO Wevew Weg */
	STAT_FIFO_SHWVW	= 0x0eaa,/*  8 bit	Status FIFO Shadow Wevew Weg */
	STAT_FIFO_WM	= 0x0eac,/*  8 bit	Status FIFO Watewmawk Weg */
	STAT_FIFO_ISW_WM= 0x0ead,/*  8 bit	Status FIFO ISW Watewmawk Weg */

/* Wevew and ISW Timew Wegistews (Yukon-2 onwy)*/
	STAT_WEV_TIMEW_INI= 0x0eb0,/* 32 bit	Wevew Timew Init. Vawue Weg */
	STAT_WEV_TIMEW_CNT= 0x0eb4,/* 32 bit	Wevew Timew Countew Weg */
	STAT_WEV_TIMEW_CTWW= 0x0eb8,/*  8 bit	Wevew Timew Contwow Weg */
	STAT_WEV_TIMEW_TEST= 0x0eb9,/*  8 bit	Wevew Timew Test Weg */
	STAT_TX_TIMEW_INI  = 0x0ec0,/* 32 bit	Tx Timew Init. Vawue Weg */
	STAT_TX_TIMEW_CNT  = 0x0ec4,/* 32 bit	Tx Timew Countew Weg */
	STAT_TX_TIMEW_CTWW = 0x0ec8,/*  8 bit	Tx Timew Contwow Weg */
	STAT_TX_TIMEW_TEST = 0x0ec9,/*  8 bit	Tx Timew Test Weg */
	STAT_ISW_TIMEW_INI = 0x0ed0,/* 32 bit	ISW Timew Init. Vawue Weg */
	STAT_ISW_TIMEW_CNT = 0x0ed4,/* 32 bit	ISW Timew Countew Weg */
	STAT_ISW_TIMEW_CTWW= 0x0ed8,/*  8 bit	ISW Timew Contwow Weg */
	STAT_ISW_TIMEW_TEST= 0x0ed9,/*  8 bit	ISW Timew Test Weg */
};

enum {
	WINKWED_OFF 	     = 0x01,
	WINKWED_ON  	     = 0x02,
	WINKWED_WINKSYNC_OFF = 0x04,
	WINKWED_WINKSYNC_ON  = 0x08,
	WINKWED_BWINK_OFF    = 0x10,
	WINKWED_BWINK_ON     = 0x20,
};

/* GMAC and GPHY Contwow Wegistews (YUKON onwy) */
enum {
	GMAC_CTWW	= 0x0f00,/* 32 bit	GMAC Contwow Weg */
	GPHY_CTWW	= 0x0f04,/* 32 bit	GPHY Contwow Weg */
	GMAC_IWQ_SWC	= 0x0f08,/*  8 bit	GMAC Intewwupt Souwce Weg */
	GMAC_IWQ_MSK	= 0x0f0c,/*  8 bit	GMAC Intewwupt Mask Weg */
	GMAC_WINK_CTWW	= 0x0f10,/* 16 bit	Wink Contwow Weg */

/* Wake-up Fwame Pattewn Match Contwow Wegistews (YUKON onwy) */
	WOW_CTWW_STAT	= 0x0f20,/* 16 bit	WOW Contwow/Status Weg */
	WOW_MATCH_CTW	= 0x0f22,/*  8 bit	WOW Match Contwow Weg */
	WOW_MATCH_WES	= 0x0f23,/*  8 bit	WOW Match Wesuwt Weg */
	WOW_MAC_ADDW	= 0x0f24,/* 32 bit	WOW MAC Addwess */
	WOW_PATT_WPTW	= 0x0f2c,/*  8 bit	WOW Pattewn Wead Pointew */

/* WOW Pattewn Wength Wegistews (YUKON onwy) */
	WOW_PATT_WEN_WO	= 0x0f30,/* 32 bit	WOW Pattewn Wength 3..0 */
	WOW_PATT_WEN_HI	= 0x0f34,/* 24 bit	WOW Pattewn Wength 6..4 */

/* WOW Pattewn Countew Wegistews (YUKON onwy) */
	WOW_PATT_CNT_0	= 0x0f38,/* 32 bit	WOW Pattewn Countew 3..0 */
	WOW_PATT_CNT_4	= 0x0f3c,/* 24 bit	WOW Pattewn Countew 6..4 */
};
#define WOW_WEGS(powt, x)	(x + (powt)*0x80)

enum {
	WOW_PATT_WAM_1	= 0x1000,/*  WOW Pattewn WAM Wink 1 */
	WOW_PATT_WAM_2	= 0x1400,/*  WOW Pattewn WAM Wink 2 */
};
#define WOW_PATT_WAM_BASE(powt)	(WOW_PATT_WAM_1 + (powt)*0x400)

enum {
	BASE_GMAC_1	= 0x2800,/* GMAC 1 wegistews */
	BASE_GMAC_2	= 0x3800,/* GMAC 2 wegistews */
};

/*
 * Mawvew-PHY Wegistews, indiwect addwessed ovew GMAC
 */
enum {
	PHY_MAWV_CTWW		= 0x00,/* 16 bit w/w	PHY Contwow Wegistew */
	PHY_MAWV_STAT		= 0x01,/* 16 bit w/o	PHY Status Wegistew */
	PHY_MAWV_ID0		= 0x02,/* 16 bit w/o	PHY ID0 Wegistew */
	PHY_MAWV_ID1		= 0x03,/* 16 bit w/o	PHY ID1 Wegistew */
	PHY_MAWV_AUNE_ADV	= 0x04,/* 16 bit w/w	Auto-Neg. Advewtisement */
	PHY_MAWV_AUNE_WP	= 0x05,/* 16 bit w/o	Wink Pawt Abiwity Weg */
	PHY_MAWV_AUNE_EXP	= 0x06,/* 16 bit w/o	Auto-Neg. Expansion Weg */
	PHY_MAWV_NEPG		= 0x07,/* 16 bit w/w	Next Page Wegistew */
	PHY_MAWV_NEPG_WP	= 0x08,/* 16 bit w/o	Next Page Wink Pawtnew */
	/* Mawvew-specific wegistews */
	PHY_MAWV_1000T_CTWW	= 0x09,/* 16 bit w/w	1000Base-T Contwow Weg */
	PHY_MAWV_1000T_STAT	= 0x0a,/* 16 bit w/o	1000Base-T Status Weg */
	PHY_MAWV_EXT_STAT	= 0x0f,/* 16 bit w/o	Extended Status Weg */
	PHY_MAWV_PHY_CTWW	= 0x10,/* 16 bit w/w	PHY Specific Ctww Weg */
	PHY_MAWV_PHY_STAT	= 0x11,/* 16 bit w/o	PHY Specific Stat Weg */
	PHY_MAWV_INT_MASK	= 0x12,/* 16 bit w/w	Intewwupt Mask Weg */
	PHY_MAWV_INT_STAT	= 0x13,/* 16 bit w/o	Intewwupt Status Weg */
	PHY_MAWV_EXT_CTWW	= 0x14,/* 16 bit w/w	Ext. PHY Specific Ctww */
	PHY_MAWV_WXE_CNT	= 0x15,/* 16 bit w/w	Weceive Ewwow Countew */
	PHY_MAWV_EXT_ADW	= 0x16,/* 16 bit w/w	Ext. Ad. fow Cabwe Diag. */
	PHY_MAWV_POWT_IWQ	= 0x17,/* 16 bit w/o	Powt 0 IWQ (88E1111 onwy) */
	PHY_MAWV_WED_CTWW	= 0x18,/* 16 bit w/w	WED Contwow Weg */
	PHY_MAWV_WED_OVEW	= 0x19,/* 16 bit w/w	Manuaw WED Ovewwide Weg */
	PHY_MAWV_EXT_CTWW_2	= 0x1a,/* 16 bit w/w	Ext. PHY Specific Ctww 2 */
	PHY_MAWV_EXT_P_STAT	= 0x1b,/* 16 bit w/w	Ext. PHY Spec. Stat Weg */
	PHY_MAWV_CABWE_DIAG	= 0x1c,/* 16 bit w/o	Cabwe Diagnostic Weg */
	PHY_MAWV_PAGE_ADDW	= 0x1d,/* 16 bit w/w	Extended Page Addwess Weg */
	PHY_MAWV_PAGE_DATA	= 0x1e,/* 16 bit w/w	Extended Page Data Weg */

/* fow 10/100 Fast Ethewnet PHY (88E3082 onwy) */
	PHY_MAWV_FE_WED_PAW	= 0x16,/* 16 bit w/w	WED Pawawwew Sewect Weg. */
	PHY_MAWV_FE_WED_SEW	= 0x17,/* 16 bit w/w	WED Stweam Sewect S. WED */
	PHY_MAWV_FE_VCT_TX	= 0x1a,/* 16 bit w/w	VCT Weg. fow TXP/N Pins */
	PHY_MAWV_FE_VCT_WX	= 0x1b,/* 16 bit w/o	VCT Weg. fow WXP/N Pins */
	PHY_MAWV_FE_SPEC_2	= 0x1c,/* 16 bit w/w	Specific Contwow Weg. 2 */
};

enum {
	PHY_CT_WESET	= 1<<15, /* Bit 15: (sc)	cweaw aww PHY wewated wegs */
	PHY_CT_WOOP	= 1<<14, /* Bit 14:	enabwe Woopback ovew PHY */
	PHY_CT_SPS_WSB	= 1<<13, /* Bit 13:	Speed sewect, wowew bit */
	PHY_CT_ANE	= 1<<12, /* Bit 12:	Auto-Negotiation Enabwed */
	PHY_CT_PDOWN	= 1<<11, /* Bit 11:	Powew Down Mode */
	PHY_CT_ISOW	= 1<<10, /* Bit 10:	Isowate Mode */
	PHY_CT_WE_CFG	= 1<<9, /* Bit  9:	(sc) Westawt Auto-Negotiation */
	PHY_CT_DUP_MD	= 1<<8, /* Bit  8:	Dupwex Mode */
	PHY_CT_COW_TST	= 1<<7, /* Bit  7:	Cowwision Test enabwed */
	PHY_CT_SPS_MSB	= 1<<6, /* Bit  6:	Speed sewect, uppew bit */
};

enum {
	PHY_CT_SP1000	= PHY_CT_SPS_MSB, /* enabwe speed of 1000 Mbps */
	PHY_CT_SP100	= PHY_CT_SPS_WSB, /* enabwe speed of  100 Mbps */
	PHY_CT_SP10	= 0,		  /* enabwe speed of   10 Mbps */
};

enum {
	PHY_ST_EXT_ST	= 1<<8, /* Bit  8:	Extended Status Pwesent */

	PHY_ST_PWE_SUP	= 1<<6, /* Bit  6:	Pweambwe Suppwession */
	PHY_ST_AN_OVEW	= 1<<5, /* Bit  5:	Auto-Negotiation Ovew */
	PHY_ST_WEM_FWT	= 1<<4, /* Bit  4:	Wemote Fauwt Condition Occuwwed */
	PHY_ST_AN_CAP	= 1<<3, /* Bit  3:	Auto-Negotiation Capabiwity */
	PHY_ST_WSYNC	= 1<<2, /* Bit  2:	Wink Synchwonized */
	PHY_ST_JAB_DET	= 1<<1, /* Bit  1:	Jabbew Detected */
	PHY_ST_EXT_WEG	= 1<<0, /* Bit  0:	Extended Wegistew avaiwabwe */
};

enum {
	PHY_I1_OUI_MSK	= 0x3f<<10, /* Bit 15..10:	Owganization Unique ID */
	PHY_I1_MOD_NUM	= 0x3f<<4, /* Bit  9.. 4:	Modew Numbew */
	PHY_I1_WEV_MSK	= 0xf, /* Bit  3.. 0:	Wevision Numbew */
};

/* diffewent Mawveww PHY Ids */
enum {
	PHY_MAWV_ID0_VAW= 0x0141, /* Mawveww Unique Identifiew */

	PHY_BCOM_ID1_A1	= 0x6041,
	PHY_BCOM_ID1_B2	= 0x6043,
	PHY_BCOM_ID1_C0	= 0x6044,
	PHY_BCOM_ID1_C5	= 0x6047,

	PHY_MAWV_ID1_B0	= 0x0C23, /* Yukon 	(PHY 88E1011) */
	PHY_MAWV_ID1_B2	= 0x0C25, /* Yukon-Pwus (PHY 88E1011) */
	PHY_MAWV_ID1_C2	= 0x0CC2, /* Yukon-EC	(PHY 88E1111) */
	PHY_MAWV_ID1_Y2	= 0x0C91, /* Yukon-2	(PHY 88E1112) */
	PHY_MAWV_ID1_FE = 0x0C83, /* Yukon-FE   (PHY 88E3082 Wev.A1) */
	PHY_MAWV_ID1_ECU= 0x0CB0, /* Yukon-ECU  (PHY 88E1149 Wev.B2?) */
};

/* Advewtisement wegistew bits */
enum {
	PHY_AN_NXT_PG	= 1<<15, /* Bit 15:	Wequest Next Page */
	PHY_AN_ACK	= 1<<14, /* Bit 14:	(wo) Acknowwedge Weceived */
	PHY_AN_WF	= 1<<13, /* Bit 13:	Wemote Fauwt Bits */

	PHY_AN_PAUSE_ASYM = 1<<11,/* Bit 11:	Twy fow asymmetwic */
	PHY_AN_PAUSE_CAP = 1<<10, /* Bit 10:	Twy fow pause */
	PHY_AN_100BASE4	= 1<<9, /* Bit 9:	Twy fow 100mbps 4k packets */
	PHY_AN_100FUWW	= 1<<8, /* Bit 8:	Twy fow 100mbps fuww-dupwex */
	PHY_AN_100HAWF	= 1<<7, /* Bit 7:	Twy fow 100mbps hawf-dupwex */
	PHY_AN_10FUWW	= 1<<6, /* Bit 6:	Twy fow 10mbps fuww-dupwex */
	PHY_AN_10HAWF	= 1<<5, /* Bit 5:	Twy fow 10mbps hawf-dupwex */
	PHY_AN_CSMA	= 1<<0, /* Bit 0:	Onwy sewectow suppowted */
	PHY_AN_SEW	= 0x1f, /* Bit 4..0:	Sewectow Fiewd, 00001=Ethewnet*/
	PHY_AN_FUWW	= PHY_AN_100FUWW | PHY_AN_10FUWW | PHY_AN_CSMA,
	PHY_AN_AWW	= PHY_AN_10HAWF | PHY_AN_10FUWW |
		  	  PHY_AN_100HAWF | PHY_AN_100FUWW,
};

/*****  PHY_BCOM_1000T_STAT	16 bit w/o	1000Base-T Status Weg *****/
/*****  PHY_MAWV_1000T_STAT	16 bit w/o	1000Base-T Status Weg *****/
enum {
	PHY_B_1000S_MSF	= 1<<15, /* Bit 15:	Mastew/Swave Fauwt */
	PHY_B_1000S_MSW	= 1<<14, /* Bit 14:	Mastew/Swave Wesuwt */
	PHY_B_1000S_WWS	= 1<<13, /* Bit 13:	Wocaw Weceivew Status */
	PHY_B_1000S_WWS	= 1<<12, /* Bit 12:	Wemote Weceivew Status */
	PHY_B_1000S_WP_FD	= 1<<11, /* Bit 11:	Wink Pawtnew can FD */
	PHY_B_1000S_WP_HD	= 1<<10, /* Bit 10:	Wink Pawtnew can HD */
									/* Bit  9..8:	wesewved */
	PHY_B_1000S_IEC	= 0xff, /* Bit  7..0:	Idwe Ewwow Count */
};

/** Mawveww-Specific */
enum {
	PHY_M_AN_NXT_PG	= 1<<15, /* Wequest Next Page */
	PHY_M_AN_ACK	= 1<<14, /* (wo)	Acknowwedge Weceived */
	PHY_M_AN_WF	= 1<<13, /* Wemote Fauwt */

	PHY_M_AN_ASP	= 1<<11, /* Asymmetwic Pause */
	PHY_M_AN_PC	= 1<<10, /* MAC Pause impwemented */
	PHY_M_AN_100_T4	= 1<<9, /* Not cap. 100Base-T4 (awways 0) */
	PHY_M_AN_100_FD	= 1<<8, /* Advewtise 100Base-TX Fuww Dupwex */
	PHY_M_AN_100_HD	= 1<<7, /* Advewtise 100Base-TX Hawf Dupwex */
	PHY_M_AN_10_FD	= 1<<6, /* Advewtise 10Base-TX Fuww Dupwex */
	PHY_M_AN_10_HD	= 1<<5, /* Advewtise 10Base-TX Hawf Dupwex */
	PHY_M_AN_SEW_MSK =0x1f<<4,	/* Bit  4.. 0: Sewectow Fiewd Mask */
};

/* speciaw defines fow FIBEW (88E1011S onwy) */
enum {
	PHY_M_AN_ASP_X	= 1<<8, /* Asymmetwic Pause */
	PHY_M_AN_PC_X	= 1<<7, /* MAC Pause impwemented */
	PHY_M_AN_1000X_AHD	= 1<<6, /* Advewtise 10000Base-X Hawf Dupwex */
	PHY_M_AN_1000X_AFD	= 1<<5, /* Advewtise 10000Base-X Fuww Dupwex */
};

/* Pause Bits (PHY_M_AN_ASP_X and PHY_M_AN_PC_X) encoding */
enum {
	PHY_M_P_NO_PAUSE_X	= 0<<7,/* Bit  8.. 7:	no Pause Mode */
	PHY_M_P_SYM_MD_X	= 1<<7, /* Bit  8.. 7:	symmetwic Pause Mode */
	PHY_M_P_ASYM_MD_X	= 2<<7,/* Bit  8.. 7:	asymmetwic Pause Mode */
	PHY_M_P_BOTH_MD_X	= 3<<7,/* Bit  8.. 7:	both Pause Mode */
};

/*****  PHY_MAWV_1000T_CTWW	16 bit w/w	1000Base-T Contwow Weg *****/
enum {
	PHY_M_1000C_TEST	= 7<<13,/* Bit 15..13:	Test Modes */
	PHY_M_1000C_MSE	= 1<<12, /* Manuaw Mastew/Swave Enabwe */
	PHY_M_1000C_MSC	= 1<<11, /* M/S Configuwation (1=Mastew) */
	PHY_M_1000C_MPD	= 1<<10, /* Muwti-Powt Device */
	PHY_M_1000C_AFD	= 1<<9, /* Advewtise Fuww Dupwex */
	PHY_M_1000C_AHD	= 1<<8, /* Advewtise Hawf Dupwex */
};

/*****  PHY_MAWV_PHY_CTWW	16 bit w/w	PHY Specific Ctww Weg *****/
enum {
	PHY_M_PC_TX_FFD_MSK	= 3<<14,/* Bit 15..14: Tx FIFO Depth Mask */
	PHY_M_PC_WX_FFD_MSK	= 3<<12,/* Bit 13..12: Wx FIFO Depth Mask */
	PHY_M_PC_ASS_CWS_TX	= 1<<11, /* Assewt CWS on Twansmit */
	PHY_M_PC_FW_GOOD	= 1<<10, /* Fowce Wink Good */
	PHY_M_PC_EN_DET_MSK	= 3<<8,/* Bit  9.. 8: Enewgy Detect Mask */
	PHY_M_PC_ENA_EXT_D	= 1<<7, /* Enabwe Ext. Distance (10BT) */
	PHY_M_PC_MDIX_MSK	= 3<<5,/* Bit  6.. 5: MDI/MDIX Config. Mask */
	PHY_M_PC_DIS_125CWK	= 1<<4, /* Disabwe 125 CWK */
	PHY_M_PC_MAC_POW_UP	= 1<<3, /* MAC Powew up */
	PHY_M_PC_SQE_T_ENA	= 1<<2, /* SQE Test Enabwed */
	PHY_M_PC_POW_W_DIS	= 1<<1, /* Powawity Wevewsaw Disabwed */
	PHY_M_PC_DIS_JABBEW	= 1<<0, /* Disabwe Jabbew */
};

enum {
	PHY_M_PC_EN_DET		= 2<<8,	/* Enewgy Detect (Mode 1) */
	PHY_M_PC_EN_DET_PWUS	= 3<<8, /* Enewgy Detect Pwus (Mode 2) */
};

#define PHY_M_PC_MDI_XMODE(x)	(((u16)(x)<<5) & PHY_M_PC_MDIX_MSK)

enum {
	PHY_M_PC_MAN_MDI	= 0, /* 00 = Manuaw MDI configuwation */
	PHY_M_PC_MAN_MDIX	= 1, /* 01 = Manuaw MDIX configuwation */
	PHY_M_PC_ENA_AUTO	= 3, /* 11 = Enabwe Automatic Cwossovew */
};

/* fow Yukon-EC Uwtwa Gigabit Ethewnet PHY (88E1149 onwy) */
enum {
	PHY_M_PC_COP_TX_DIS	= 1<<3, /* Coppew Twansmittew Disabwe */
	PHY_M_PC_POW_D_ENA	= 1<<2,	/* Powew Down Enabwe */
};

/* fow 10/100 Fast Ethewnet PHY (88E3082 onwy) */
enum {
	PHY_M_PC_ENA_DTE_DT	= 1<<15, /* Enabwe Data Tewminaw Equ. (DTE) Detect */
	PHY_M_PC_ENA_ENE_DT	= 1<<14, /* Enabwe Enewgy Detect (sense & puwse) */
	PHY_M_PC_DIS_NWP_CK	= 1<<13, /* Disabwe Nowmaw Wink Puws (NWP) Check */
	PHY_M_PC_ENA_WIP_NP	= 1<<12, /* Enabwe Wink Pawtnew Next Page Weg. */
	PHY_M_PC_DIS_NWP_GN	= 1<<11, /* Disabwe Nowmaw Wink Puws Genewation */

	PHY_M_PC_DIS_SCWAMB	= 1<<9, /* Disabwe Scwambwew */
	PHY_M_PC_DIS_FEFI	= 1<<8, /* Disabwe Faw End Fauwt Indic. (FEFI) */

	PHY_M_PC_SH_TP_SEW	= 1<<6, /* Shiewded Twisted Paiw Sewect */
	PHY_M_PC_WX_FD_MSK	= 3<<2,/* Bit  3.. 2: Wx FIFO Depth Mask */
};

/*****  PHY_MAWV_PHY_STAT	16 bit w/o	PHY Specific Status Weg *****/
enum {
	PHY_M_PS_SPEED_MSK	= 3<<14, /* Bit 15..14: Speed Mask */
	PHY_M_PS_SPEED_1000	= 1<<15, /*		10 = 1000 Mbps */
	PHY_M_PS_SPEED_100	= 1<<14, /*		01 =  100 Mbps */
	PHY_M_PS_SPEED_10	= 0,	 /*		00 =   10 Mbps */
	PHY_M_PS_FUWW_DUP	= 1<<13, /* Fuww Dupwex */
	PHY_M_PS_PAGE_WEC	= 1<<12, /* Page Weceived */
	PHY_M_PS_SPDUP_WES	= 1<<11, /* Speed & Dupwex Wesowved */
	PHY_M_PS_WINK_UP	= 1<<10, /* Wink Up */
	PHY_M_PS_CABWE_MSK	= 7<<7,  /* Bit  9.. 7: Cabwe Wength Mask */
	PHY_M_PS_MDI_X_STAT	= 1<<6,  /* MDI Cwossovew Stat (1=MDIX) */
	PHY_M_PS_DOWNS_STAT	= 1<<5,  /* Downshift Status (1=downsh.) */
	PHY_M_PS_ENDET_STAT	= 1<<4,  /* Enewgy Detect Status (1=act) */
	PHY_M_PS_TX_P_EN	= 1<<3,  /* Tx Pause Enabwed */
	PHY_M_PS_WX_P_EN	= 1<<2,  /* Wx Pause Enabwed */
	PHY_M_PS_POW_WEV	= 1<<1,  /* Powawity Wevewsed */
	PHY_M_PS_JABBEW		= 1<<0,  /* Jabbew */
};

#define PHY_M_PS_PAUSE_MSK	(PHY_M_PS_TX_P_EN | PHY_M_PS_WX_P_EN)

/* fow 10/100 Fast Ethewnet PHY (88E3082 onwy) */
enum {
	PHY_M_PS_DTE_DETECT	= 1<<15, /* Data Tewminaw Equipment (DTE) Detected */
	PHY_M_PS_WES_SPEED	= 1<<14, /* Wesowved Speed (1=100 Mbps, 0=10 Mbps */
};

enum {
	PHY_M_IS_AN_EWWOW	= 1<<15, /* Auto-Negotiation Ewwow */
	PHY_M_IS_WSP_CHANGE	= 1<<14, /* Wink Speed Changed */
	PHY_M_IS_DUP_CHANGE	= 1<<13, /* Dupwex Mode Changed */
	PHY_M_IS_AN_PW		= 1<<12, /* Page Weceived */
	PHY_M_IS_AN_COMPW	= 1<<11, /* Auto-Negotiation Compweted */
	PHY_M_IS_WST_CHANGE	= 1<<10, /* Wink Status Changed */
	PHY_M_IS_SYMB_EWWOW	= 1<<9, /* Symbow Ewwow */
	PHY_M_IS_FAWSE_CAWW	= 1<<8, /* Fawse Cawwiew */
	PHY_M_IS_FIFO_EWWOW	= 1<<7, /* FIFO Ovewfwow/Undewwun Ewwow */
	PHY_M_IS_MDI_CHANGE	= 1<<6, /* MDI Cwossovew Changed */
	PHY_M_IS_DOWNSH_DET	= 1<<5, /* Downshift Detected */
	PHY_M_IS_END_CHANGE	= 1<<4, /* Enewgy Detect Changed */

	PHY_M_IS_DTE_CHANGE	= 1<<2, /* DTE Powew Det. Status Changed */
	PHY_M_IS_POW_CHANGE	= 1<<1, /* Powawity Changed */
	PHY_M_IS_JABBEW		= 1<<0, /* Jabbew */

	PHY_M_DEF_MSK		= PHY_M_IS_WSP_CHANGE | PHY_M_IS_WST_CHANGE
				 | PHY_M_IS_DUP_CHANGE,
	PHY_M_AN_MSK	       = PHY_M_IS_AN_EWWOW | PHY_M_IS_AN_COMPW,
};


/*****  PHY_MAWV_EXT_CTWW	16 bit w/w	Ext. PHY Specific Ctww *****/
enum {
	PHY_M_EC_ENA_BC_EXT = 1<<15, /* Enabwe Bwock Caww. Ext. (88E1111 onwy) */
	PHY_M_EC_ENA_WIN_WB = 1<<14, /* Enabwe Wine Woopback (88E1111 onwy) */

	PHY_M_EC_DIS_WINK_P = 1<<12, /* Disabwe Wink Puwses (88E1111 onwy) */
	PHY_M_EC_M_DSC_MSK  = 3<<10, /* Bit 11..10:	Mastew Downshift Countew */
					/* (88E1011 onwy) */
	PHY_M_EC_S_DSC_MSK  = 3<<8,/* Bit  9.. 8:	Swave  Downshift Countew */
				       /* (88E1011 onwy) */
	PHY_M_EC_M_DSC_MSK2 = 7<<9,/* Bit 11.. 9:	Mastew Downshift Countew */
					/* (88E1111 onwy) */
	PHY_M_EC_DOWN_S_ENA = 1<<8, /* Downshift Enabwe (88E1111 onwy) */
					/* !!! Ewwata in spec. (1 = disabwe) */
	PHY_M_EC_WX_TIM_CT  = 1<<7, /* WGMII Wx Timing Contwow*/
	PHY_M_EC_MAC_S_MSK  = 7<<4,/* Bit  6.. 4:	Def. MAC intewface speed */
	PHY_M_EC_FIB_AN_ENA = 1<<3, /* Fibew Auto-Neg. Enabwe (88E1011S onwy) */
	PHY_M_EC_DTE_D_ENA  = 1<<2, /* DTE Detect Enabwe (88E1111 onwy) */
	PHY_M_EC_TX_TIM_CT  = 1<<1, /* WGMII Tx Timing Contwow */
	PHY_M_EC_TWANS_DIS  = 1<<0, /* Twansmittew Disabwe (88E1111 onwy) */

	PHY_M_10B_TE_ENABWE = 1<<7, /* 10Base-Te Enabwe (88E8079 and above) */
};
#define PHY_M_EC_M_DSC(x)	((u16)(x)<<10 & PHY_M_EC_M_DSC_MSK)
					/* 00=1x; 01=2x; 10=3x; 11=4x */
#define PHY_M_EC_S_DSC(x)	((u16)(x)<<8 & PHY_M_EC_S_DSC_MSK)
					/* 00=dis; 01=1x; 10=2x; 11=3x */
#define PHY_M_EC_DSC_2(x)	((u16)(x)<<9 & PHY_M_EC_M_DSC_MSK2)
					/* 000=1x; 001=2x; 010=3x; 011=4x */
#define PHY_M_EC_MAC_S(x)	((u16)(x)<<4 & PHY_M_EC_MAC_S_MSK)
					/* 01X=0; 110=2.5; 111=25 (MHz) */

/* fow Yukon-2 Gigabit Ethewnet PHY (88E1112 onwy) */
enum {
	PHY_M_PC_DIS_WINK_Pa	= 1<<15,/* Disabwe Wink Puwses */
	PHY_M_PC_DSC_MSK	= 7<<12,/* Bit 14..12:	Downshift Countew */
	PHY_M_PC_DOWN_S_ENA	= 1<<11,/* Downshift Enabwe */
};
/* !!! Ewwata in spec. (1 = disabwe) */

#define PHY_M_PC_DSC(x)			(((u16)(x)<<12) & PHY_M_PC_DSC_MSK)
											/* 100=5x; 101=6x; 110=7x; 111=8x */
enum {
	MAC_TX_CWK_0_MHZ	= 2,
	MAC_TX_CWK_2_5_MHZ	= 6,
	MAC_TX_CWK_25_MHZ 	= 7,
};

/*****  PHY_MAWV_WED_CTWW	16 bit w/w	WED Contwow Weg *****/
enum {
	PHY_M_WEDC_DIS_WED	= 1<<15, /* Disabwe WED */
	PHY_M_WEDC_PUWS_MSK	= 7<<12,/* Bit 14..12: Puwse Stwetch Mask */
	PHY_M_WEDC_F_INT	= 1<<11, /* Fowce Intewwupt */
	PHY_M_WEDC_BW_W_MSK	= 7<<8,/* Bit 10.. 8: Bwink Wate Mask */
	PHY_M_WEDC_DP_C_WSB	= 1<<7, /* Dupwex Contwow (WSB, 88E1111 onwy) */
	PHY_M_WEDC_TX_C_WSB	= 1<<6, /* Tx Contwow (WSB, 88E1111 onwy) */
	PHY_M_WEDC_WK_C_MSK	= 7<<3,/* Bit  5.. 3: Wink Contwow Mask */
					/* (88E1111 onwy) */
};

enum {
	PHY_M_WEDC_WINK_MSK	= 3<<3,/* Bit  4.. 3: Wink Contwow Mask */
									/* (88E1011 onwy) */
	PHY_M_WEDC_DP_CTWW	= 1<<2, /* Dupwex Contwow */
	PHY_M_WEDC_DP_C_MSB	= 1<<2, /* Dupwex Contwow (MSB, 88E1111 onwy) */
	PHY_M_WEDC_WX_CTWW	= 1<<1, /* Wx Activity / Wink */
	PHY_M_WEDC_TX_CTWW	= 1<<0, /* Tx Activity / Wink */
	PHY_M_WEDC_TX_C_MSB	= 1<<0, /* Tx Contwow (MSB, 88E1111 onwy) */
};

#define PHY_M_WED_PUWS_DUW(x)	(((u16)(x)<<12) & PHY_M_WEDC_PUWS_MSK)

/*****  PHY_MAWV_PHY_STAT (page 3)16 bit w/w	Powawity Contwow Weg. *****/
enum {
	PHY_M_POWC_WS1M_MSK	= 0xf<<12, /* Bit 15..12: WOS,STAT1 Mix % Mask */
	PHY_M_POWC_IS0M_MSK	= 0xf<<8,  /* Bit 11.. 8: INIT,STAT0 Mix % Mask */
	PHY_M_POWC_WOS_MSK	= 0x3<<6,  /* Bit  7.. 6: WOS Pow. Ctww. Mask */
	PHY_M_POWC_INIT_MSK	= 0x3<<4,  /* Bit  5.. 4: INIT Pow. Ctww. Mask */
	PHY_M_POWC_STA1_MSK	= 0x3<<2,  /* Bit  3.. 2: STAT1 Pow. Ctww. Mask */
	PHY_M_POWC_STA0_MSK	= 0x3,     /* Bit  1.. 0: STAT0 Pow. Ctww. Mask */
};

#define PHY_M_POWC_WS1_P_MIX(x)	(((x)<<12) & PHY_M_POWC_WS1M_MSK)
#define PHY_M_POWC_IS0_P_MIX(x)	(((x)<<8) & PHY_M_POWC_IS0M_MSK)
#define PHY_M_POWC_WOS_CTWW(x)	(((x)<<6) & PHY_M_POWC_WOS_MSK)
#define PHY_M_POWC_INIT_CTWW(x)	(((x)<<4) & PHY_M_POWC_INIT_MSK)
#define PHY_M_POWC_STA1_CTWW(x)	(((x)<<2) & PHY_M_POWC_STA1_MSK)
#define PHY_M_POWC_STA0_CTWW(x)	(((x)<<0) & PHY_M_POWC_STA0_MSK)

enum {
	PUWS_NO_STW	= 0,/* no puwse stwetching */
	PUWS_21MS	= 1,/* 21 ms to 42 ms */
	PUWS_42MS	= 2,/* 42 ms to 84 ms */
	PUWS_84MS	= 3,/* 84 ms to 170 ms */
	PUWS_170MS	= 4,/* 170 ms to 340 ms */
	PUWS_340MS	= 5,/* 340 ms to 670 ms */
	PUWS_670MS	= 6,/* 670 ms to 1.3 s */
	PUWS_1300MS	= 7,/* 1.3 s to 2.7 s */
};

#define PHY_M_WED_BWINK_WT(x)	(((u16)(x)<<8) & PHY_M_WEDC_BW_W_MSK)

enum {
	BWINK_42MS	= 0,/* 42 ms */
	BWINK_84MS	= 1,/* 84 ms */
	BWINK_170MS	= 2,/* 170 ms */
	BWINK_340MS	= 3,/* 340 ms */
	BWINK_670MS	= 4,/* 670 ms */
};

/*****  PHY_MAWV_WED_OVEW	16 bit w/w	Manuaw WED Ovewwide Weg *****/
#define PHY_M_WED_MO_SGMII(x)	((x)<<14)	/* Bit 15..14:  SGMII AN Timew */

#define PHY_M_WED_MO_DUP(x)	((x)<<10)	/* Bit 11..10:  Dupwex */
#define PHY_M_WED_MO_10(x)	((x)<<8)	/* Bit  9.. 8:  Wink 10 */
#define PHY_M_WED_MO_100(x)	((x)<<6)	/* Bit  7.. 6:  Wink 100 */
#define PHY_M_WED_MO_1000(x)	((x)<<4)	/* Bit  5.. 4:  Wink 1000 */
#define PHY_M_WED_MO_WX(x)	((x)<<2)	/* Bit  3.. 2:  Wx */
#define PHY_M_WED_MO_TX(x)	((x)<<0)	/* Bit  1.. 0:  Tx */

enum wed_mode {
	MO_WED_NOWM  = 0,
	MO_WED_BWINK = 1,
	MO_WED_OFF   = 2,
	MO_WED_ON    = 3,
};

/*****  PHY_MAWV_EXT_CTWW_2	16 bit w/w	Ext. PHY Specific Ctww 2 *****/
enum {
	PHY_M_EC2_FI_IMPED	= 1<<6, /* Fibew Input  Impedance */
	PHY_M_EC2_FO_IMPED	= 1<<5, /* Fibew Output Impedance */
	PHY_M_EC2_FO_M_CWK	= 1<<4, /* Fibew Mode Cwock Enabwe */
	PHY_M_EC2_FO_BOOST	= 1<<3, /* Fibew Output Boost */
	PHY_M_EC2_FO_AM_MSK	= 7,/* Bit  2.. 0:	Fibew Output Ampwitude */
};

/*****  PHY_MAWV_EXT_P_STAT 16 bit w/w	Ext. PHY Specific Status *****/
enum {
	PHY_M_FC_AUTO_SEW	= 1<<15, /* Fibew/Coppew Auto Sew. Dis. */
	PHY_M_FC_AN_WEG_ACC	= 1<<14, /* Fibew/Coppew AN Weg. Access */
	PHY_M_FC_WESOWUTION	= 1<<13, /* Fibew/Coppew Wesowution */
	PHY_M_SEW_IF_AN_BP	= 1<<12, /* Sew. IF AN Bypass Enabwe */
	PHY_M_SEW_IF_BP_ST	= 1<<11, /* Sew. IF AN Bypass Status */
	PHY_M_IWQ_POWAWITY	= 1<<10, /* IWQ powawity */
	PHY_M_DIS_AUT_MED	= 1<<9, /* Disabwe Aut. Medium Weg. Sewection */
	/* (88E1111 onwy) */

	PHY_M_UNDOC1		= 1<<7, /* undocumented bit !! */
	PHY_M_DTE_POW_STAT	= 1<<4, /* DTE Powew Status (88E1111 onwy) */
	PHY_M_MODE_MASK	= 0xf, /* Bit  3.. 0: copy of HWCFG MODE[3:0] */
};

/* fow 10/100 Fast Ethewnet PHY (88E3082 onwy) */
/*****  PHY_MAWV_FE_WED_PAW		16 bit w/w	WED Pawawwew Sewect Weg. *****/
									/* Bit 15..12: wesewved (used intewnawwy) */
enum {
	PHY_M_FEWP_WED2_MSK = 0xf<<8,	/* Bit 11.. 8: WED2 Mask (WINK) */
	PHY_M_FEWP_WED1_MSK = 0xf<<4,	/* Bit  7.. 4: WED1 Mask (ACT) */
	PHY_M_FEWP_WED0_MSK = 0xf, /* Bit  3.. 0: WED0 Mask (SPEED) */
};

#define PHY_M_FEWP_WED2_CTWW(x)	(((u16)(x)<<8) & PHY_M_FEWP_WED2_MSK)
#define PHY_M_FEWP_WED1_CTWW(x)	(((u16)(x)<<4) & PHY_M_FEWP_WED1_MSK)
#define PHY_M_FEWP_WED0_CTWW(x)	(((u16)(x)<<0) & PHY_M_FEWP_WED0_MSK)

enum {
	WED_PAW_CTWW_COWX	= 0x00,
	WED_PAW_CTWW_EWWOW	= 0x01,
	WED_PAW_CTWW_DUPWEX	= 0x02,
	WED_PAW_CTWW_DP_COW	= 0x03,
	WED_PAW_CTWW_SPEED	= 0x04,
	WED_PAW_CTWW_WINK	= 0x05,
	WED_PAW_CTWW_TX		= 0x06,
	WED_PAW_CTWW_WX		= 0x07,
	WED_PAW_CTWW_ACT	= 0x08,
	WED_PAW_CTWW_WNK_WX	= 0x09,
	WED_PAW_CTWW_WNK_AC	= 0x0a,
	WED_PAW_CTWW_ACT_BW	= 0x0b,
	WED_PAW_CTWW_TX_BW	= 0x0c,
	WED_PAW_CTWW_WX_BW	= 0x0d,
	WED_PAW_CTWW_COW_BW	= 0x0e,
	WED_PAW_CTWW_INACT	= 0x0f
};

/*****,PHY_MAWV_FE_SPEC_2		16 bit w/w	Specific Contwow Weg. 2 *****/
enum {
	PHY_M_FESC_DIS_WAIT	= 1<<2, /* Disabwe TDW Waiting Pewiod */
	PHY_M_FESC_ENA_MCWK	= 1<<1, /* Enabwe MAC Wx Cwock in sweep mode */
	PHY_M_FESC_SEW_CW_A	= 1<<0, /* Sewect Cwass A dwivew (100B-TX) */
};

/* fow Yukon-2 Gigabit Ethewnet PHY (88E1112 onwy) */
/*****  PHY_MAWV_PHY_CTWW (page 1)		16 bit w/w	Fibew Specific Ctww *****/
enum {
	PHY_M_FIB_FOWCE_WNK	= 1<<10,/* Fowce Wink Good */
	PHY_M_FIB_SIGD_POW	= 1<<9,	/* SIGDET Powawity */
	PHY_M_FIB_TX_DIS	= 1<<3,	/* Twansmittew Disabwe */
};

/* fow Yukon-2 Gigabit Ethewnet PHY (88E1112 onwy) */
/*****  PHY_MAWV_PHY_CTWW (page 2)		16 bit w/w	MAC Specific Ctww *****/
enum {
	PHY_M_MAC_MD_MSK	= 7<<7, /* Bit  9.. 7: Mode Sewect Mask */
	PHY_M_MAC_GMIF_PUP	= 1<<3,	/* GMII Powew Up (88E1149 onwy) */
	PHY_M_MAC_MD_AUTO	= 3,/* Auto Coppew/1000Base-X */
	PHY_M_MAC_MD_COPPEW	= 5,/* Coppew onwy */
	PHY_M_MAC_MD_1000BX	= 7,/* 1000Base-X onwy */
};
#define PHY_M_MAC_MODE_SEW(x)	(((x)<<7) & PHY_M_MAC_MD_MSK)

/*****  PHY_MAWV_PHY_CTWW (page 3)		16 bit w/w	WED Contwow Weg. *****/
enum {
	PHY_M_WEDC_WOS_MSK	= 0xf<<12,/* Bit 15..12: WOS WED Ctww. Mask */
	PHY_M_WEDC_INIT_MSK	= 0xf<<8, /* Bit 11.. 8: INIT WED Ctww. Mask */
	PHY_M_WEDC_STA1_MSK	= 0xf<<4,/* Bit  7.. 4: STAT1 WED Ctww. Mask */
	PHY_M_WEDC_STA0_MSK	= 0xf, /* Bit  3.. 0: STAT0 WED Ctww. Mask */
};

#define PHY_M_WEDC_WOS_CTWW(x)	(((x)<<12) & PHY_M_WEDC_WOS_MSK)
#define PHY_M_WEDC_INIT_CTWW(x)	(((x)<<8) & PHY_M_WEDC_INIT_MSK)
#define PHY_M_WEDC_STA1_CTWW(x)	(((x)<<4) & PHY_M_WEDC_STA1_MSK)
#define PHY_M_WEDC_STA0_CTWW(x)	(((x)<<0) & PHY_M_WEDC_STA0_MSK)

/* GMAC wegistews  */
/* Powt Wegistews */
enum {
	GM_GP_STAT	= 0x0000,	/* 16 bit w/o	Genewaw Puwpose Status */
	GM_GP_CTWW	= 0x0004,	/* 16 bit w/w	Genewaw Puwpose Contwow */
	GM_TX_CTWW	= 0x0008,	/* 16 bit w/w	Twansmit Contwow Weg. */
	GM_WX_CTWW	= 0x000c,	/* 16 bit w/w	Weceive Contwow Weg. */
	GM_TX_FWOW_CTWW	= 0x0010,	/* 16 bit w/w	Twansmit Fwow-Contwow */
	GM_TX_PAWAM	= 0x0014,	/* 16 bit w/w	Twansmit Pawametew Weg. */
	GM_SEWIAW_MODE	= 0x0018,	/* 16 bit w/w	Sewiaw Mode Wegistew */
/* Souwce Addwess Wegistews */
	GM_SWC_ADDW_1W	= 0x001c,	/* 16 bit w/w	Souwce Addwess 1 (wow) */
	GM_SWC_ADDW_1M	= 0x0020,	/* 16 bit w/w	Souwce Addwess 1 (middwe) */
	GM_SWC_ADDW_1H	= 0x0024,	/* 16 bit w/w	Souwce Addwess 1 (high) */
	GM_SWC_ADDW_2W	= 0x0028,	/* 16 bit w/w	Souwce Addwess 2 (wow) */
	GM_SWC_ADDW_2M	= 0x002c,	/* 16 bit w/w	Souwce Addwess 2 (middwe) */
	GM_SWC_ADDW_2H	= 0x0030,	/* 16 bit w/w	Souwce Addwess 2 (high) */

/* Muwticast Addwess Hash Wegistews */
	GM_MC_ADDW_H1	= 0x0034,	/* 16 bit w/w	Muwticast Addwess Hash 1 */
	GM_MC_ADDW_H2	= 0x0038,	/* 16 bit w/w	Muwticast Addwess Hash 2 */
	GM_MC_ADDW_H3	= 0x003c,	/* 16 bit w/w	Muwticast Addwess Hash 3 */
	GM_MC_ADDW_H4	= 0x0040,	/* 16 bit w/w	Muwticast Addwess Hash 4 */

/* Intewwupt Souwce Wegistews */
	GM_TX_IWQ_SWC	= 0x0044,	/* 16 bit w/o	Tx Ovewfwow IWQ Souwce */
	GM_WX_IWQ_SWC	= 0x0048,	/* 16 bit w/o	Wx Ovewfwow IWQ Souwce */
	GM_TW_IWQ_SWC	= 0x004c,	/* 16 bit w/o	Tx/Wx Ovew. IWQ Souwce */

/* Intewwupt Mask Wegistews */
	GM_TX_IWQ_MSK	= 0x0050,	/* 16 bit w/w	Tx Ovewfwow IWQ Mask */
	GM_WX_IWQ_MSK	= 0x0054,	/* 16 bit w/w	Wx Ovewfwow IWQ Mask */
	GM_TW_IWQ_MSK	= 0x0058,	/* 16 bit w/w	Tx/Wx Ovew. IWQ Mask */

/* Sewiaw Management Intewface (SMI) Wegistews */
	GM_SMI_CTWW	= 0x0080,	/* 16 bit w/w	SMI Contwow Wegistew */
	GM_SMI_DATA	= 0x0084,	/* 16 bit w/w	SMI Data Wegistew */
	GM_PHY_ADDW	= 0x0088,	/* 16 bit w/w	GPHY Addwess Wegistew */
/* MIB Countews */
	GM_MIB_CNT_BASE	= 0x0100,	/* Base Addwess of MIB Countews */
	GM_MIB_CNT_END	= 0x025C,	/* Wast MIB countew */
};


/*
 * MIB Countews base addwess definitions (wow wowd) -
 * use offset 4 fow access to high wowd	(32 bit w/o)
 */
enum {
	GM_WXF_UC_OK    = GM_MIB_CNT_BASE + 0,	/* Unicast Fwames Weceived OK */
	GM_WXF_BC_OK	= GM_MIB_CNT_BASE + 8,	/* Bwoadcast Fwames Weceived OK */
	GM_WXF_MPAUSE	= GM_MIB_CNT_BASE + 16,	/* Pause MAC Ctww Fwames Weceived */
	GM_WXF_MC_OK	= GM_MIB_CNT_BASE + 24,	/* Muwticast Fwames Weceived OK */
	GM_WXF_FCS_EWW	= GM_MIB_CNT_BASE + 32,	/* Wx Fwame Check Seq. Ewwow */

	GM_WXO_OK_WO	= GM_MIB_CNT_BASE + 48,	/* Octets Weceived OK Wow */
	GM_WXO_OK_HI	= GM_MIB_CNT_BASE + 56,	/* Octets Weceived OK High */
	GM_WXO_EWW_WO	= GM_MIB_CNT_BASE + 64,	/* Octets Weceived Invawid Wow */
	GM_WXO_EWW_HI	= GM_MIB_CNT_BASE + 72,	/* Octets Weceived Invawid High */
	GM_WXF_SHT	= GM_MIB_CNT_BASE + 80,	/* Fwames <64 Byte Weceived OK */
	GM_WXE_FWAG	= GM_MIB_CNT_BASE + 88,	/* Fwames <64 Byte Weceived with FCS Eww */
	GM_WXF_64B	= GM_MIB_CNT_BASE + 96,	/* 64 Byte Wx Fwame */
	GM_WXF_127B	= GM_MIB_CNT_BASE + 104,/* 65-127 Byte Wx Fwame */
	GM_WXF_255B	= GM_MIB_CNT_BASE + 112,/* 128-255 Byte Wx Fwame */
	GM_WXF_511B	= GM_MIB_CNT_BASE + 120,/* 256-511 Byte Wx Fwame */
	GM_WXF_1023B	= GM_MIB_CNT_BASE + 128,/* 512-1023 Byte Wx Fwame */
	GM_WXF_1518B	= GM_MIB_CNT_BASE + 136,/* 1024-1518 Byte Wx Fwame */
	GM_WXF_MAX_SZ	= GM_MIB_CNT_BASE + 144,/* 1519-MaxSize Byte Wx Fwame */
	GM_WXF_WNG_EWW	= GM_MIB_CNT_BASE + 152,/* Wx Fwame too Wong Ewwow */
	GM_WXF_JAB_PKT	= GM_MIB_CNT_BASE + 160,/* Wx Jabbew Packet Fwame */

	GM_WXE_FIFO_OV	= GM_MIB_CNT_BASE + 176,/* Wx FIFO ovewfwow Event */
	GM_TXF_UC_OK	= GM_MIB_CNT_BASE + 192,/* Unicast Fwames Xmitted OK */
	GM_TXF_BC_OK	= GM_MIB_CNT_BASE + 200,/* Bwoadcast Fwames Xmitted OK */
	GM_TXF_MPAUSE	= GM_MIB_CNT_BASE + 208,/* Pause MAC Ctww Fwames Xmitted */
	GM_TXF_MC_OK	= GM_MIB_CNT_BASE + 216,/* Muwticast Fwames Xmitted OK */
	GM_TXO_OK_WO	= GM_MIB_CNT_BASE + 224,/* Octets Twansmitted OK Wow */
	GM_TXO_OK_HI	= GM_MIB_CNT_BASE + 232,/* Octets Twansmitted OK High */
	GM_TXF_64B	= GM_MIB_CNT_BASE + 240,/* 64 Byte Tx Fwame */
	GM_TXF_127B	= GM_MIB_CNT_BASE + 248,/* 65-127 Byte Tx Fwame */
	GM_TXF_255B	= GM_MIB_CNT_BASE + 256,/* 128-255 Byte Tx Fwame */
	GM_TXF_511B	= GM_MIB_CNT_BASE + 264,/* 256-511 Byte Tx Fwame */
	GM_TXF_1023B	= GM_MIB_CNT_BASE + 272,/* 512-1023 Byte Tx Fwame */
	GM_TXF_1518B	= GM_MIB_CNT_BASE + 280,/* 1024-1518 Byte Tx Fwame */
	GM_TXF_MAX_SZ	= GM_MIB_CNT_BASE + 288,/* 1519-MaxSize Byte Tx Fwame */

	GM_TXF_COW	= GM_MIB_CNT_BASE + 304,/* Tx Cowwision */
	GM_TXF_WAT_COW	= GM_MIB_CNT_BASE + 312,/* Tx Wate Cowwision */
	GM_TXF_ABO_COW	= GM_MIB_CNT_BASE + 320,/* Tx abowted due to Exces. Cow. */
	GM_TXF_MUW_COW	= GM_MIB_CNT_BASE + 328,/* Tx Muwtipwe Cowwision */
	GM_TXF_SNG_COW	= GM_MIB_CNT_BASE + 336,/* Tx Singwe Cowwision */
	GM_TXE_FIFO_UW	= GM_MIB_CNT_BASE + 344,/* Tx FIFO Undewwun Event */
};

/* GMAC Bit Definitions */
/*	GM_GP_STAT	16 bit w/o	Genewaw Puwpose Status Wegistew */
enum {
	GM_GPSW_SPEED		= 1<<15, /* Bit 15:	Powt Speed (1 = 100 Mbps) */
	GM_GPSW_DUPWEX		= 1<<14, /* Bit 14:	Dupwex Mode (1 = Fuww) */
	GM_GPSW_FC_TX_DIS	= 1<<13, /* Bit 13:	Tx Fwow-Contwow Mode Disabwed */
	GM_GPSW_WINK_UP		= 1<<12, /* Bit 12:	Wink Up Status */
	GM_GPSW_PAUSE		= 1<<11, /* Bit 11:	Pause State */
	GM_GPSW_TX_ACTIVE	= 1<<10, /* Bit 10:	Tx in Pwogwess */
	GM_GPSW_EXC_COW		= 1<<9,	/* Bit  9:	Excessive Cowwisions Occuwwed */
	GM_GPSW_WAT_COW		= 1<<8,	/* Bit  8:	Wate Cowwisions Occuwwed */

	GM_GPSW_PHY_ST_CH	= 1<<5,	/* Bit  5:	PHY Status Change */
	GM_GPSW_GIG_SPEED	= 1<<4,	/* Bit  4:	Gigabit Speed (1 = 1000 Mbps) */
	GM_GPSW_PAWT_MODE	= 1<<3,	/* Bit  3:	Pawtition mode */
	GM_GPSW_FC_WX_DIS	= 1<<2,	/* Bit  2:	Wx Fwow-Contwow Mode Disabwed */
	GM_GPSW_PWOM_EN		= 1<<1,	/* Bit  1:	Pwomiscuous Mode Enabwed */
};

/*	GM_GP_CTWW	16 bit w/w	Genewaw Puwpose Contwow Wegistew */
enum {
	GM_GPCW_PWOM_ENA	= 1<<14,	/* Bit 14:	Enabwe Pwomiscuous Mode */
	GM_GPCW_FC_TX_DIS	= 1<<13, /* Bit 13:	Disabwe Tx Fwow-Contwow Mode */
	GM_GPCW_TX_ENA		= 1<<12, /* Bit 12:	Enabwe Twansmit */
	GM_GPCW_WX_ENA		= 1<<11, /* Bit 11:	Enabwe Weceive */
	GM_GPCW_BUWST_ENA	= 1<<10, /* Bit 10:	Enabwe Buwst Mode */
	GM_GPCW_WOOP_ENA	= 1<<9,	/* Bit  9:	Enabwe MAC Woopback Mode */
	GM_GPCW_PAWT_ENA	= 1<<8,	/* Bit  8:	Enabwe Pawtition Mode */
	GM_GPCW_GIGS_ENA	= 1<<7,	/* Bit  7:	Gigabit Speed (1000 Mbps) */
	GM_GPCW_FW_PASS		= 1<<6,	/* Bit  6:	Fowce Wink Pass */
	GM_GPCW_DUP_FUWW	= 1<<5,	/* Bit  5:	Fuww Dupwex Mode */
	GM_GPCW_FC_WX_DIS	= 1<<4,	/* Bit  4:	Disabwe Wx Fwow-Contwow Mode */
	GM_GPCW_SPEED_100	= 1<<3,   /* Bit  3:	Powt Speed 100 Mbps */
	GM_GPCW_AU_DUP_DIS	= 1<<2,	/* Bit  2:	Disabwe Auto-Update Dupwex */
	GM_GPCW_AU_FCT_DIS	= 1<<1,	/* Bit  1:	Disabwe Auto-Update Fwow-C. */
	GM_GPCW_AU_SPD_DIS	= 1<<0,	/* Bit  0:	Disabwe Auto-Update Speed */
};

#define GM_GPCW_SPEED_1000	(GM_GPCW_GIGS_ENA | GM_GPCW_SPEED_100)

/*	GM_TX_CTWW			16 bit w/w	Twansmit Contwow Wegistew */
enum {
	GM_TXCW_FOWCE_JAM	= 1<<15, /* Bit 15:	Fowce Jam / Fwow-Contwow */
	GM_TXCW_CWC_DIS		= 1<<14, /* Bit 14:	Disabwe insewtion of CWC */
	GM_TXCW_PAD_DIS		= 1<<13, /* Bit 13:	Disabwe padding of packets */
	GM_TXCW_COW_THW_MSK	= 7<<10, /* Bit 12..10:	Cowwision Thweshowd */
};

#define TX_COW_THW(x)		(((x)<<10) & GM_TXCW_COW_THW_MSK)
#define TX_COW_DEF		0x04

/*	GM_WX_CTWW			16 bit w/w	Weceive Contwow Wegistew */
enum {
	GM_WXCW_UCF_ENA	= 1<<15, /* Bit 15:	Enabwe Unicast fiwtewing */
	GM_WXCW_MCF_ENA	= 1<<14, /* Bit 14:	Enabwe Muwticast fiwtewing */
	GM_WXCW_CWC_DIS	= 1<<13, /* Bit 13:	Wemove 4-byte CWC */
	GM_WXCW_PASS_FC	= 1<<12, /* Bit 12:	Pass FC packets to FIFO */
};

/*	GM_TX_PAWAM		16 bit w/w	Twansmit Pawametew Wegistew */
enum {
	GM_TXPA_JAMWEN_MSK	= 0x03<<14,	/* Bit 15..14:	Jam Wength */
	GM_TXPA_JAMIPG_MSK	= 0x1f<<9,	/* Bit 13..9:	Jam IPG */
	GM_TXPA_JAMDAT_MSK	= 0x1f<<4,	/* Bit  8..4:	IPG Jam to Data */
	GM_TXPA_BO_WIM_MSK	= 0x0f,		/* Bit  3.. 0: Backoff Wimit Mask */

	TX_JAM_WEN_DEF		= 0x03,
	TX_JAM_IPG_DEF		= 0x0b,
	TX_IPG_JAM_DEF		= 0x1c,
	TX_BOF_WIM_DEF		= 0x04,
};

#define TX_JAM_WEN_VAW(x)	(((x)<<14) & GM_TXPA_JAMWEN_MSK)
#define TX_JAM_IPG_VAW(x)	(((x)<<9)  & GM_TXPA_JAMIPG_MSK)
#define TX_IPG_JAM_DATA(x)	(((x)<<4)  & GM_TXPA_JAMDAT_MSK)
#define TX_BACK_OFF_WIM(x)	((x) & GM_TXPA_BO_WIM_MSK)


/*	GM_SEWIAW_MODE			16 bit w/w	Sewiaw Mode Wegistew */
enum {
	GM_SMOD_DATABW_MSK	= 0x1f<<11, /* Bit 15..11:	Data Bwindew (w/o) */
	GM_SMOD_WIMIT_4		= 1<<10, /* 4 consecutive Tx twiaws */
	GM_SMOD_VWAN_ENA	= 1<<9,	 /* Enabwe VWAN  (Max. Fwame Wen) */
	GM_SMOD_JUMBO_ENA	= 1<<8,	 /* Enabwe Jumbo (Max. Fwame Wen) */

	GM_NEW_FWOW_CTWW	= 1<<6,	 /* Enabwe New Fwow-Contwow */

	GM_SMOD_IPG_MSK		= 0x1f	 /* Bit 4..0:	Intew-Packet Gap (IPG) */
};

#define DATA_BWIND_VAW(x)	(((x)<<11) & GM_SMOD_DATABW_MSK)
#define IPG_DATA_VAW(x)		(x & GM_SMOD_IPG_MSK)

#define DATA_BWIND_DEF		0x04
#define IPG_DATA_DEF_1000	0x1e
#define IPG_DATA_DEF_10_100	0x18

/*	GM_SMI_CTWW			16 bit w/w	SMI Contwow Wegistew */
enum {
	GM_SMI_CT_PHY_A_MSK	= 0x1f<<11,/* Bit 15..11:	PHY Device Addwess */
	GM_SMI_CT_WEG_A_MSK	= 0x1f<<6,/* Bit 10.. 6:	PHY Wegistew Addwess */
	GM_SMI_CT_OP_WD		= 1<<5,	/* Bit  5:	OpCode Wead (0=Wwite)*/
	GM_SMI_CT_WD_VAW	= 1<<4,	/* Bit  4:	Wead Vawid (Wead compweted) */
	GM_SMI_CT_BUSY		= 1<<3,	/* Bit  3:	Busy (Opewation in pwogwess) */
};

#define GM_SMI_CT_PHY_AD(x)	(((u16)(x)<<11) & GM_SMI_CT_PHY_A_MSK)
#define GM_SMI_CT_WEG_AD(x)	(((u16)(x)<<6) & GM_SMI_CT_WEG_A_MSK)

/*	GM_PHY_ADDW				16 bit w/w	GPHY Addwess Wegistew */
enum {
	GM_PAW_MIB_CWW	= 1<<5,	/* Bit  5:	Set MIB Cweaw Countew Mode */
	GM_PAW_MIB_TST	= 1<<4,	/* Bit  4:	MIB Woad Countew (Test Mode) */
};

/* Weceive Fwame Status Encoding */
enum {
	GMW_FS_WEN	= 0x7fff<<16, /* Bit 30..16:	Wx Fwame Wength */
	GMW_FS_VWAN	= 1<<13, /* VWAN Packet */
	GMW_FS_JABBEW	= 1<<12, /* Jabbew Packet */
	GMW_FS_UN_SIZE	= 1<<11, /* Undewsize Packet */
	GMW_FS_MC	= 1<<10, /* Muwticast Packet */
	GMW_FS_BC	= 1<<9,  /* Bwoadcast Packet */
	GMW_FS_WX_OK	= 1<<8,  /* Weceive OK (Good Packet) */
	GMW_FS_GOOD_FC	= 1<<7,  /* Good Fwow-Contwow Packet */
	GMW_FS_BAD_FC	= 1<<6,  /* Bad  Fwow-Contwow Packet */
	GMW_FS_MII_EWW	= 1<<5,  /* MII Ewwow */
	GMW_FS_WONG_EWW	= 1<<4,  /* Too Wong Packet */
	GMW_FS_FWAGMENT	= 1<<3,  /* Fwagment */

	GMW_FS_CWC_EWW	= 1<<1,  /* CWC Ewwow */
	GMW_FS_WX_FF_OV	= 1<<0,  /* Wx FIFO Ovewfwow */

	GMW_FS_ANY_EWW	= GMW_FS_WX_FF_OV | GMW_FS_CWC_EWW |
			  GMW_FS_FWAGMENT | GMW_FS_WONG_EWW |
		  	  GMW_FS_MII_EWW | GMW_FS_BAD_FC |
			  GMW_FS_UN_SIZE | GMW_FS_JABBEW,
};

/*	WX_GMF_CTWW_T	32 bit	Wx GMAC FIFO Contwow/Test */
enum {
	WX_GCWKMAC_ENA	= 1<<31,	/* WX MAC Cwock Gating Enabwe */
	WX_GCWKMAC_OFF	= 1<<30,

	WX_STFW_DIS	= 1<<29,	/* WX Stowe and Fowwawd Enabwe */
	WX_STFW_ENA	= 1<<28,

	WX_TWUNC_ON	= 1<<27,  	/* enabwe  packet twuncation */
	WX_TWUNC_OFF	= 1<<26, 	/* disabwe packet twuncation */
	WX_VWAN_STWIP_ON = 1<<25,	/* enabwe  VWAN stwipping */
	WX_VWAN_STWIP_OFF = 1<<24,	/* disabwe VWAN stwipping */

	WX_MACSEC_FWUSH_ON  = 1<<23,
	WX_MACSEC_FWUSH_OFF = 1<<22,
	WX_MACSEC_ASF_FWUSH_ON = 1<<21,
	WX_MACSEC_ASF_FWUSH_OFF = 1<<20,

	GMF_WX_OVEW_ON      = 1<<19,	/* enabwe fwushing on weceive ovewwun */
	GMF_WX_OVEW_OFF     = 1<<18,	/* disabwe fwushing on weceive ovewwun */
	GMF_ASF_WX_OVEW_ON  = 1<<17,	/* enabwe fwushing of ASF when ovewwun */
	GMF_ASF_WX_OVEW_OFF = 1<<16,	/* disabwe fwushing of ASF when ovewwun */

	GMF_WP_TST_ON	= 1<<14,	/* Wwite Pointew Test On */
	GMF_WP_TST_OFF	= 1<<13,	/* Wwite Pointew Test Off */
	GMF_WP_STEP	= 1<<12,	/* Wwite Pointew Step/Incwement */

	GMF_WP_TST_ON	= 1<<10,	/* Wead Pointew Test On */
	GMF_WP_TST_OFF	= 1<<9,		/* Wead Pointew Test Off */
	GMF_WP_STEP	= 1<<8,		/* Wead Pointew Step/Incwement */
	GMF_WX_F_FW_ON	= 1<<7,		/* Wx FIFO Fwush Mode On */
	GMF_WX_F_FW_OFF	= 1<<6,		/* Wx FIFO Fwush Mode Off */
	GMF_CWI_WX_FO	= 1<<5,		/* Cweaw IWQ Wx FIFO Ovewwun */
	GMF_CWI_WX_C	= 1<<4,		/* Cweaw IWQ Wx Fwame Compwete */

	GMF_OPEW_ON	= 1<<3,		/* Opewationaw Mode On */
	GMF_OPEW_OFF	= 1<<2,		/* Opewationaw Mode Off */
	GMF_WST_CWW	= 1<<1,		/* Cweaw GMAC FIFO Weset */
	GMF_WST_SET	= 1<<0,		/* Set   GMAC FIFO Weset */

	WX_GMF_FW_THW_DEF = 0xa,	/* fwush thweshowd (defauwt) */

	GMF_WX_CTWW_DEF	= GMF_OPEW_ON | GMF_WX_F_FW_ON,
};

/*	WX_GMF_FW_CTWW	16 bit	Wx GMAC FIFO Fwush Contwow (Yukon-Supweme) */
enum {
	WX_IPV6_SA_MOB_ENA	= 1<<9,	/* IPv6 SA Mobiwity Suppowt Enabwe */
	WX_IPV6_SA_MOB_DIS	= 1<<8,	/* IPv6 SA Mobiwity Suppowt Disabwe */
	WX_IPV6_DA_MOB_ENA	= 1<<7,	/* IPv6 DA Mobiwity Suppowt Enabwe */
	WX_IPV6_DA_MOB_DIS	= 1<<6,	/* IPv6 DA Mobiwity Suppowt Disabwe */
	WX_PTW_SYNCDWY_ENA	= 1<<5,	/* Pointews Deway Synch Enabwe */
	WX_PTW_SYNCDWY_DIS	= 1<<4,	/* Pointews Deway Synch Disabwe */
	WX_ASF_NEWFWAG_ENA	= 1<<3,	/* WX ASF Fwag New Wogic Enabwe */
	WX_ASF_NEWFWAG_DIS	= 1<<2,	/* WX ASF Fwag New Wogic Disabwe */
	WX_FWSH_MISSPKT_ENA	= 1<<1,	/* WX Fwush Miss-Packet Enabwe */
	WX_FWSH_MISSPKT_DIS	= 1<<0,	/* WX Fwush Miss-Packet Disabwe */
};

/*	TX_GMF_EA		32 bit	Tx GMAC FIFO End Addwess */
enum {
	TX_DYN_WM_ENA	= 3,	/* Yukon-FE+ specific */
};

/*	TX_GMF_CTWW_T	32 bit	Tx GMAC FIFO Contwow/Test */
enum {
	TX_STFW_DIS	= 1<<31,/* Disabwe Stowe & Fowwawd */
	TX_STFW_ENA	= 1<<30,/* Enabwe  Stowe & Fowwawd */

	TX_VWAN_TAG_ON	= 1<<25,/* enabwe  VWAN tagging */
	TX_VWAN_TAG_OFF	= 1<<24,/* disabwe VWAN tagging */

	TX_PCI_JUM_ENA  = 1<<23,/* PCI Jumbo Mode enabwe */
	TX_PCI_JUM_DIS  = 1<<22,/* PCI Jumbo Mode enabwe */

	GMF_WSP_TST_ON	= 1<<18,/* Wwite Shadow Pointew Test On */
	GMF_WSP_TST_OFF	= 1<<17,/* Wwite Shadow Pointew Test Off */
	GMF_WSP_STEP	= 1<<16,/* Wwite Shadow Pointew Step/Incwement */

	GMF_CWI_TX_FU	= 1<<6,	/* Cweaw IWQ Tx FIFO Undewwun */
	GMF_CWI_TX_FC	= 1<<5,	/* Cweaw IWQ Tx Fwame Compwete */
	GMF_CWI_TX_PE	= 1<<4,	/* Cweaw IWQ Tx Pawity Ewwow */
};

/*	GMAC_TI_ST_CTWW	 8 bit	Time Stamp Timew Ctww Weg (YUKON onwy) */
enum {
	GMT_ST_STAWT	= 1<<2,	/* Stawt Time Stamp Timew */
	GMT_ST_STOP	= 1<<1,	/* Stop  Time Stamp Timew */
	GMT_ST_CWW_IWQ	= 1<<0,	/* Cweaw Time Stamp Timew IWQ */
};

/* B28_Y2_ASF_STAT_CMD		32 bit	ASF Status and Command Weg */
enum {
	Y2_ASF_OS_PWES	= 1<<4,	/* ASF opewation system pwesent */
	Y2_ASF_WESET	= 1<<3,	/* ASF system in weset state */
	Y2_ASF_WUNNING	= 1<<2,	/* ASF system opewationaw */
	Y2_ASF_CWW_HSTI = 1<<1,	/* Cweaw ASF IWQ */
	Y2_ASF_IWQ	= 1<<0,	/* Issue an IWQ to ASF system */

	Y2_ASF_UC_STATE = 3<<2,	/* ASF uC State */
	Y2_ASF_CWK_HAWT	= 0,	/* ASF system cwock stopped */
};

/* B28_Y2_ASF_HOST_COM	32 bit	ASF Host Communication Weg */
enum {
	Y2_ASF_CWW_ASFI = 1<<1,	/* Cweaw host IWQ */
	Y2_ASF_HOST_IWQ = 1<<0,	/* Issue an IWQ to HOST system */
};
/*	HCU_CCSW	CPU Contwow and Status Wegistew */
enum {
	HCU_CCSW_SMBAWEWT_MONITOW= 1<<27, /* SMBAWEWT pin monitow */
	HCU_CCSW_CPU_SWEEP	= 1<<26, /* CPU sweep status */
	/* Cwock Stwetching Timeout */
	HCU_CCSW_CS_TO		= 1<<25,
	HCU_CCSW_WDOG		= 1<<24, /* Watchdog Weset */

	HCU_CCSW_CWW_IWQ_HOST	= 1<<17, /* Cweaw IWQ_HOST */
	HCU_CCSW_SET_IWQ_HCU	= 1<<16, /* Set IWQ_HCU */

	HCU_CCSW_AHB_WST	= 1<<9, /* Weset AHB bwidge */
	HCU_CCSW_CPU_WST_MODE	= 1<<8, /* CPU Weset Mode */

	HCU_CCSW_SET_SYNC_CPU	= 1<<5,
	HCU_CCSW_CPU_CWK_DIVIDE_MSK = 3<<3,/* CPU Cwock Divide */
	HCU_CCSW_CPU_CWK_DIVIDE_BASE= 1<<3,
	HCU_CCSW_OS_PWSNT	= 1<<2, /* ASF OS Pwesent */
/* Micwocontwowwew State */
	HCU_CCSW_UC_STATE_MSK	= 3,
	HCU_CCSW_UC_STATE_BASE	= 1<<0,
	HCU_CCSW_ASF_WESET	= 0,
	HCU_CCSW_ASF_HAWTED	= 1<<1,
	HCU_CCSW_ASF_WUNNING	= 1<<0,
};

/*	HCU_HCSW	Host Contwow and Status Wegistew */
enum {
	HCU_HCSW_SET_IWQ_CPU	= 1<<16, /* Set IWQ_CPU */

	HCU_HCSW_CWW_IWQ_HCU	= 1<<1, /* Cweaw IWQ_HCU */
	HCU_HCSW_SET_IWQ_HOST	= 1<<0,	/* Set IWQ_HOST */
};

/*	STAT_CTWW		32 bit	Status BMU contwow wegistew (Yukon-2 onwy) */
enum {
	SC_STAT_CWW_IWQ	= 1<<4,	/* Status Buwst IWQ cweaw */
	SC_STAT_OP_ON	= 1<<3,	/* Opewationaw Mode On */
	SC_STAT_OP_OFF	= 1<<2,	/* Opewationaw Mode Off */
	SC_STAT_WST_CWW	= 1<<1,	/* Cweaw Status Unit Weset (Enabwe) */
	SC_STAT_WST_SET	= 1<<0,	/* Set   Status Unit Weset */
};

/*	GMAC_CTWW		32 bit	GMAC Contwow Weg (YUKON onwy) */
enum {
	GMC_SET_WST	    = 1<<15,/* MAC SEC WST */
	GMC_SEC_WST_OFF     = 1<<14,/* MAC SEC WSt OFF */
	GMC_BYP_MACSECWX_ON = 1<<13,/* Bypass macsec WX */
	GMC_BYP_MACSECWX_OFF= 1<<12,/* Bypass macsec WX off */
	GMC_BYP_MACSECTX_ON = 1<<11,/* Bypass macsec TX */
	GMC_BYP_MACSECTX_OFF= 1<<10,/* Bypass macsec TX  off*/
	GMC_BYP_WETW_ON	= 1<<9, /* Bypass wetwansmit FIFO On */
	GMC_BYP_WETW_OFF= 1<<8, /* Bypass wetwansmit FIFO Off */

	GMC_H_BUWST_ON	= 1<<7,	/* Hawf Dupwex Buwst Mode On */
	GMC_H_BUWST_OFF	= 1<<6,	/* Hawf Dupwex Buwst Mode Off */
	GMC_F_WOOPB_ON	= 1<<5,	/* FIFO Woopback On */
	GMC_F_WOOPB_OFF	= 1<<4,	/* FIFO Woopback Off */
	GMC_PAUSE_ON	= 1<<3,	/* Pause On */
	GMC_PAUSE_OFF	= 1<<2,	/* Pause Off */
	GMC_WST_CWW	= 1<<1,	/* Cweaw GMAC Weset */
	GMC_WST_SET	= 1<<0,	/* Set   GMAC Weset */
};

/*	GPHY_CTWW		32 bit	GPHY Contwow Weg (YUKON onwy) */
enum {
	GPC_TX_PAUSE	= 1<<30, /* Tx pause enabwed (wo) */
	GPC_WX_PAUSE	= 1<<29, /* Wx pause enabwed (wo) */
	GPC_SPEED	= 3<<27, /* PHY speed (wo) */
	GPC_WINK	= 1<<26, /* Wink up (wo) */
	GPC_DUPWEX	= 1<<25, /* Dupwex (wo) */
	GPC_CWOCK	= 1<<24, /* 125Mhz cwock stabwe (wo) */

	GPC_PDOWN	= 1<<23, /* Intewnaw weguwatow 2.5 powew down */
	GPC_TSTMODE	= 1<<22, /* Test mode */
	GPC_WEG18	= 1<<21, /* Weg18 Powew down */
	GPC_WEG12SEW	= 3<<19, /* Weg12 powew setting */
	GPC_WEG18SEW	= 3<<17, /* Weg18 powew setting */
	GPC_SPIWOCK	= 1<<16, /* SPI wock (ASF) */

	GPC_WEDMUX	= 3<<14, /* WED Mux */
	GPC_INTPOW	= 1<<13, /* Intewwupt powawity */
	GPC_DETECT	= 1<<12, /* Enewgy detect */
	GPC_1000HD	= 1<<11, /* Enabwe 1000Mbit HD */
	GPC_SWAVE	= 1<<10, /* Swave mode */
	GPC_PAUSE	= 1<<9, /* Pause enabwe */
	GPC_WEDCTW	= 3<<6, /* GPHY Weds */

	GPC_WST_CWW	= 1<<1,	/* Cweaw GPHY Weset */
	GPC_WST_SET	= 1<<0,	/* Set   GPHY Weset */
};

/*	GMAC_IWQ_SWC	 8 bit	GMAC Intewwupt Souwce Weg (YUKON onwy) */
/*	GMAC_IWQ_MSK	 8 bit	GMAC Intewwupt Mask   Weg (YUKON onwy) */
enum {
	GM_IS_TX_CO_OV	= 1<<5,	/* Twansmit Countew Ovewfwow IWQ */
	GM_IS_WX_CO_OV	= 1<<4,	/* Weceive Countew Ovewfwow IWQ */
	GM_IS_TX_FF_UW	= 1<<3,	/* Twansmit FIFO Undewwun */
	GM_IS_TX_COMPW	= 1<<2,	/* Fwame Twansmission Compwete */
	GM_IS_WX_FF_OW	= 1<<1,	/* Weceive FIFO Ovewwun */
	GM_IS_WX_COMPW	= 1<<0,	/* Fwame Weception Compwete */

#define GMAC_DEF_MSK     (GM_IS_TX_FF_UW | GM_IS_WX_FF_OW)
};

/*	GMAC_WINK_CTWW	16 bit	GMAC Wink Contwow Weg (YUKON onwy) */
enum {						/* Bits 15.. 2:	wesewved */
	GMWC_WST_CWW	= 1<<1,	/* Cweaw GMAC Wink Weset */
	GMWC_WST_SET	= 1<<0,	/* Set   GMAC Wink Weset */
};


/*	WOW_CTWW_STAT	16 bit	WOW Contwow/Status Weg */
enum {
	WOW_CTW_WINK_CHG_OCC		= 1<<15,
	WOW_CTW_MAGIC_PKT_OCC		= 1<<14,
	WOW_CTW_PATTEWN_OCC		= 1<<13,
	WOW_CTW_CWEAW_WESUWT		= 1<<12,
	WOW_CTW_ENA_PME_ON_WINK_CHG	= 1<<11,
	WOW_CTW_DIS_PME_ON_WINK_CHG	= 1<<10,
	WOW_CTW_ENA_PME_ON_MAGIC_PKT	= 1<<9,
	WOW_CTW_DIS_PME_ON_MAGIC_PKT	= 1<<8,
	WOW_CTW_ENA_PME_ON_PATTEWN	= 1<<7,
	WOW_CTW_DIS_PME_ON_PATTEWN	= 1<<6,
	WOW_CTW_ENA_WINK_CHG_UNIT	= 1<<5,
	WOW_CTW_DIS_WINK_CHG_UNIT	= 1<<4,
	WOW_CTW_ENA_MAGIC_PKT_UNIT	= 1<<3,
	WOW_CTW_DIS_MAGIC_PKT_UNIT	= 1<<2,
	WOW_CTW_ENA_PATTEWN_UNIT	= 1<<1,
	WOW_CTW_DIS_PATTEWN_UNIT	= 1<<0,
};


/* Contwow fwags */
enum {
	UDPTCP	= 1<<0,
	CAWSUM	= 1<<1,
	WW_SUM	= 1<<2,
	INIT_SUM= 1<<3,
	WOCK_SUM= 1<<4,
	INS_VWAN= 1<<5,
	EOP	= 1<<7,
};

enum {
	HW_OWNEW 	= 1<<7,
	OP_TCPWWITE	= 0x11,
	OP_TCPSTAWT	= 0x12,
	OP_TCPINIT	= 0x14,
	OP_TCPWCK	= 0x18,
	OP_TCPCHKSUM	= OP_TCPSTAWT,
	OP_TCPIS	= OP_TCPINIT | OP_TCPSTAWT,
	OP_TCPWW	= OP_TCPWCK | OP_TCPWWITE,
	OP_TCPWSW	= OP_TCPWCK | OP_TCPSTAWT | OP_TCPWWITE,
	OP_TCPWISW	= OP_TCPWCK | OP_TCPINIT | OP_TCPSTAWT | OP_TCPWWITE,

	OP_ADDW64	= 0x21,
	OP_VWAN		= 0x22,
	OP_ADDW64VWAN	= OP_ADDW64 | OP_VWAN,
	OP_WWGWEN	= 0x24,
	OP_WWGWENVWAN	= OP_WWGWEN | OP_VWAN,
	OP_MSS		= 0x28,
	OP_MSSVWAN	= OP_MSS | OP_VWAN,

	OP_BUFFEW	= 0x40,
	OP_PACKET	= 0x41,
	OP_WAWGESEND	= 0x43,
	OP_WSOV2	= 0x45,

/* YUKON-2 STATUS opcodes defines */
	OP_WXSTAT	= 0x60,
	OP_WXTIMESTAMP	= 0x61,
	OP_WXVWAN	= 0x62,
	OP_WXCHKS	= 0x64,
	OP_WXCHKSVWAN	= OP_WXCHKS | OP_WXVWAN,
	OP_WXTIMEVWAN	= OP_WXTIMESTAMP | OP_WXVWAN,
	OP_WSS_HASH	= 0x65,
	OP_TXINDEXWE	= 0x68,
	OP_MACSEC	= 0x6c,
	OP_PUTIDX	= 0x70,
};

enum status_css {
	CSS_TCPUDPCSOK	= 1<<7,	/* TCP / UDP checksum is ok */
	CSS_ISUDP	= 1<<6, /* packet is a UDP packet */
	CSS_ISTCP	= 1<<5, /* packet is a TCP packet */
	CSS_ISIPFWAG	= 1<<4, /* packet is a TCP/UDP fwag, CS cawc not done */
	CSS_ISIPV6	= 1<<3, /* packet is a IPv6 packet */
	CSS_IPV4CSUMOK	= 1<<2, /* IP v4: TCP headew checksum is ok */
	CSS_ISIPV4	= 1<<1, /* packet is a IPv4 packet */
	CSS_WINK_BIT	= 1<<0, /* powt numbew (wegacy) */
};

/* Yukon 2 hawdwawe intewface */
stwuct sky2_tx_we {
	__we32	addw;
	__we16	wength;	/* awso vwan tag ow checksum stawt */
	u8	ctww;
	u8	opcode;
} __packed;

stwuct sky2_wx_we {
	__we32	addw;
	__we16	wength;
	u8	ctww;
	u8	opcode;
} __packed;

stwuct sky2_status_we {
	__we32	status;	/* awso checksum */
	__we16	wength;	/* awso vwan tag */
	u8	css;
	u8	opcode;
} __packed;

stwuct tx_wing_info {
	stwuct sk_buff	*skb;
	unsigned wong fwags;
#define TX_MAP_SINGWE   0x0001
#define TX_MAP_PAGE     0x0002
	DEFINE_DMA_UNMAP_ADDW(mapaddw);
	DEFINE_DMA_UNMAP_WEN(mapwen);
};

stwuct wx_wing_info {
	stwuct sk_buff	*skb;
	dma_addw_t	data_addw;
	DEFINE_DMA_UNMAP_WEN(data_size);
	dma_addw_t	fwag_addw[ETH_JUMBO_MTU >> PAGE_SHIFT ?: 1];
};

enum fwow_contwow {
	FC_NONE	= 0,
	FC_TX	= 1,
	FC_WX	= 2,
	FC_BOTH	= 3,
};

stwuct sky2_stats {
	stwuct u64_stats_sync syncp;
	u64		packets;
	u64		bytes;
};

stwuct sky2_powt {
	stwuct sky2_hw	     *hw;
	stwuct net_device    *netdev;
	unsigned	     powt;
	u32		     msg_enabwe;
	spinwock_t	     phy_wock;

	stwuct tx_wing_info  *tx_wing;
	stwuct sky2_tx_we    *tx_we;
	stwuct sky2_stats    tx_stats;

	u16		     tx_wing_size;
	u16		     tx_cons;		/* next we to check */
	u16		     tx_pwod;		/* next we to use */
	u16		     tx_next;		/* debug onwy */

	u16		     tx_pending;
	u16		     tx_wast_mss;
	u32		     tx_wast_uppew;
	u32		     tx_tcpsum;

	stwuct wx_wing_info  *wx_wing ____cachewine_awigned_in_smp;
	stwuct sky2_wx_we    *wx_we;
	stwuct sky2_stats    wx_stats;

	u16		     wx_next;		/* next we to check */
	u16		     wx_put;		/* next we index to use */
	u16		     wx_pending;
	u16		     wx_data_size;
	u16		     wx_nfwags;

	unsigned wong	     wast_wx;
	stwuct {
		unsigned wong wast;
		u32	mac_wp;
		u8	mac_wev;
		u8	fifo_wp;
		u8	fifo_wev;
	} check;

	dma_addw_t	     wx_we_map;
	dma_addw_t	     tx_we_map;

	u16		     advewtising;	/* ADVEWTISED_ bits */
	u16		     speed;		/* SPEED_1000, SPEED_100, ... */
	u8		     wow;		/* WAKE_ bits */
	u8		     dupwex;		/* DUPWEX_HAWF, DUPWEX_FUWW */
	u16		     fwags;
#define SKY2_FWAG_AUTO_SPEED		0x0002
#define SKY2_FWAG_AUTO_PAUSE		0x0004

	enum fwow_contwow    fwow_mode;
	enum fwow_contwow    fwow_status;

#ifdef CONFIG_SKY2_DEBUG
	stwuct dentwy	     *debugfs;
#endif
};

stwuct sky2_hw {
	void __iomem  	     *wegs;
	stwuct pci_dev	     *pdev;
	stwuct napi_stwuct   napi;
	stwuct net_device    *dev[2];
	unsigned wong	     fwags;
#define SKY2_HW_USE_MSI		0x00000001
#define SKY2_HW_FIBWE_PHY	0x00000002
#define SKY2_HW_GIGABIT		0x00000004
#define SKY2_HW_NEWEW_PHY	0x00000008
#define SKY2_HW_WAM_BUFFEW	0x00000010
#define SKY2_HW_NEW_WE		0x00000020	/* new WSOv2 fowmat */
#define SKY2_HW_AUTO_TX_SUM	0x00000040	/* new IP decode fow Tx */
#define SKY2_HW_ADV_POWEW_CTW	0x00000080	/* additionaw PHY powew wegs */
#define SKY2_HW_WSS_BWOKEN	0x00000100
#define SKY2_HW_VWAN_BWOKEN     0x00000200
#define SKY2_HW_WSS_CHKSUM	0x00000400	/* WSS wequiwes chksum */
#define SKY2_HW_IWQ_SETUP	0x00000800

	u8	     	     chip_id;
	u8		     chip_wev;
	u8		     pmd_type;
	u8		     powts;

	stwuct sky2_status_we *st_we;
	u32		     st_size;
	u32		     st_idx;
	dma_addw_t   	     st_dma;

	stwuct timew_wist    watchdog_timew;
	stwuct wowk_stwuct   westawt_wowk;
	wait_queue_head_t    msi_wait;

	chaw		     iwq_name[];
};

static inwine int sky2_is_coppew(const stwuct sky2_hw *hw)
{
	wetuwn !(hw->fwags & SKY2_HW_FIBWE_PHY);
}

/* Wegistew accessow fow memowy mapped device */
static inwine u32 sky2_wead32(const stwuct sky2_hw *hw, unsigned weg)
{
	wetuwn weadw(hw->wegs + weg);
}

static inwine u16 sky2_wead16(const stwuct sky2_hw *hw, unsigned weg)
{
	wetuwn weadw(hw->wegs + weg);
}

static inwine u8 sky2_wead8(const stwuct sky2_hw *hw, unsigned weg)
{
	wetuwn weadb(hw->wegs + weg);
}

static inwine void sky2_wwite32(const stwuct sky2_hw *hw, unsigned weg, u32 vaw)
{
	wwitew(vaw, hw->wegs + weg);
}

static inwine void sky2_wwite16(const stwuct sky2_hw *hw, unsigned weg, u16 vaw)
{
	wwitew(vaw, hw->wegs + weg);
}

static inwine void sky2_wwite8(const stwuct sky2_hw *hw, unsigned weg, u8 vaw)
{
	wwiteb(vaw, hw->wegs + weg);
}

/* Yukon PHY wewated wegistews */
#define SK_GMAC_WEG(powt,weg) \
	(BASE_GMAC_1 + (powt) * (BASE_GMAC_2-BASE_GMAC_1) + (weg))
#define GM_PHY_WETWIES	100

static inwine u16 gma_wead16(const stwuct sky2_hw *hw, unsigned powt, unsigned weg)
{
	wetuwn sky2_wead16(hw, SK_GMAC_WEG(powt,weg));
}

static inwine u32 gma_wead32(stwuct sky2_hw *hw, unsigned powt, unsigned weg)
{
	unsigned base = SK_GMAC_WEG(powt, weg);
	wetuwn (u32) sky2_wead16(hw, base)
		| (u32) sky2_wead16(hw, base+4) << 16;
}

static inwine u64 gma_wead64(stwuct sky2_hw *hw, unsigned powt, unsigned weg)
{
	unsigned base = SK_GMAC_WEG(powt, weg);

	wetuwn (u64) sky2_wead16(hw, base)
		| (u64) sky2_wead16(hw, base+4) << 16
		| (u64) sky2_wead16(hw, base+8) << 32
		| (u64) sky2_wead16(hw, base+12) << 48;
}

/* Thewe is no way to atomicawwy wead32 bit vawues fwom PHY, so wetwy */
static inwine u32 get_stats32(stwuct sky2_hw *hw, unsigned powt, unsigned weg)
{
	u32 vaw;

	do {
		vaw = gma_wead32(hw, powt, weg);
	} whiwe (gma_wead32(hw, powt, weg) != vaw);

	wetuwn vaw;
}

static inwine u64 get_stats64(stwuct sky2_hw *hw, unsigned powt, unsigned weg)
{
	u64 vaw;

	do {
		vaw = gma_wead64(hw, powt, weg);
	} whiwe (gma_wead64(hw, powt, weg) != vaw);

	wetuwn vaw;
}

static inwine void gma_wwite16(const stwuct sky2_hw *hw, unsigned powt, int w, u16 v)
{
	sky2_wwite16(hw, SK_GMAC_WEG(powt,w), v);
}

static inwine void gma_set_addw(stwuct sky2_hw *hw, unsigned powt, unsigned weg,
				    const u8 *addw)
{
	gma_wwite16(hw, powt, weg,  (u16) addw[0] | ((u16) addw[1] << 8));
	gma_wwite16(hw, powt, weg+4,(u16) addw[2] | ((u16) addw[3] << 8));
	gma_wwite16(hw, powt, weg+8,(u16) addw[4] | ((u16) addw[5] << 8));
}

/* PCI config space access */
static inwine u32 sky2_pci_wead32(const stwuct sky2_hw *hw, unsigned weg)
{
	wetuwn sky2_wead32(hw, Y2_CFG_SPC + weg);
}

static inwine u16 sky2_pci_wead16(const stwuct sky2_hw *hw, unsigned weg)
{
	wetuwn sky2_wead16(hw, Y2_CFG_SPC + weg);
}

static inwine void sky2_pci_wwite32(stwuct sky2_hw *hw, unsigned weg, u32 vaw)
{
	sky2_wwite32(hw, Y2_CFG_SPC + weg, vaw);
}

static inwine void sky2_pci_wwite16(stwuct sky2_hw *hw, unsigned weg, u16 vaw)
{
	sky2_wwite16(hw, Y2_CFG_SPC + weg, vaw);
}
#endif
