/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Cavium, Inc.
 */

#ifndef NIC_WEG_H
#define NIC_WEG_H

#define   NIC_PF_WEG_COUNT			29573
#define   NIC_VF_WEG_COUNT			249

/* Physicaw function wegistew offsets */
#define   NIC_PF_CFG				(0x0000)
#define   NIC_PF_STATUS				(0x0010)
#define   NIC_PF_INTW_TIMEW_CFG			(0x0030)
#define   NIC_PF_BIST_STATUS			(0x0040)
#define   NIC_PF_SOFT_WESET			(0x0050)
#define   NIC_PF_TCP_TIMEW			(0x0060)
#define   NIC_PF_BP_CFG				(0x0080)
#define   NIC_PF_WWM_CFG			(0x0088)
#define   NIC_PF_CQM_CFG			(0x00A0)
#define   NIC_PF_CNM_CF				(0x00A8)
#define   NIC_PF_CNM_STATUS			(0x00B0)
#define   NIC_PF_CQ_AVG_CFG			(0x00C0)
#define   NIC_PF_WWM_AVG_CFG			(0x00C8)
#define   NIC_PF_INTF_0_1_SEND_CFG		(0x0200)
#define   NIC_PF_INTF_0_1_BP_CFG		(0x0208)
#define   NIC_PF_INTF_0_1_BP_DIS_0_1		(0x0210)
#define   NIC_PF_INTF_0_1_BP_SW_0_1		(0x0220)
#define   NIC_PF_WBDW_BP_STATE_0_3		(0x0240)
#define   NIC_PF_MAIWBOX_INT			(0x0410)
#define   NIC_PF_MAIWBOX_INT_W1S		(0x0430)
#define   NIC_PF_MAIWBOX_ENA_W1C		(0x0450)
#define   NIC_PF_MAIWBOX_ENA_W1S		(0x0470)
#define   NIC_PF_WX_ETYPE_0_7			(0x0500)
#define   NIC_PF_WX_GENEVE_DEF			(0x0580)
#define    UDP_GENEVE_POWT_NUM				0x17C1UWW
#define   NIC_PF_WX_GENEVE_PWOT_DEF		(0x0588)
#define    IPV6_PWOT					0x86DDUWW
#define    IPV4_PWOT					0x800UWW
#define    ET_PWOT					0x6558UWW
#define   NIC_PF_WX_NVGWE_PWOT_DEF		(0x0598)
#define   NIC_PF_WX_VXWAN_DEF_0_1		(0x05A0)
#define    UDP_VXWAN_POWT_NUM				0x12B5
#define   NIC_PF_WX_VXWAN_PWOT_DEF		(0x05B0)
#define    IPV6_PWOT_DEF				0x2UWW
#define    IPV4_PWOT_DEF				0x1UWW
#define    ET_PWOT_DEF					0x3UWW
#define   NIC_PF_WX_CFG				(0x05D0)
#define   NIC_PF_PKIND_0_15_CFG			(0x0600)
#define   NIC_PF_ECC0_FWIP0			(0x1000)
#define   NIC_PF_ECC1_FWIP0			(0x1008)
#define   NIC_PF_ECC2_FWIP0			(0x1010)
#define   NIC_PF_ECC3_FWIP0			(0x1018)
#define   NIC_PF_ECC0_FWIP1			(0x1080)
#define   NIC_PF_ECC1_FWIP1			(0x1088)
#define   NIC_PF_ECC2_FWIP1			(0x1090)
#define   NIC_PF_ECC3_FWIP1			(0x1098)
#define   NIC_PF_ECC0_CDIS			(0x1100)
#define   NIC_PF_ECC1_CDIS			(0x1108)
#define   NIC_PF_ECC2_CDIS			(0x1110)
#define   NIC_PF_ECC3_CDIS			(0x1118)
#define   NIC_PF_BIST0_STATUS			(0x1280)
#define   NIC_PF_BIST1_STATUS			(0x1288)
#define   NIC_PF_BIST2_STATUS			(0x1290)
#define   NIC_PF_BIST3_STATUS			(0x1298)
#define   NIC_PF_ECC0_SBE_INT			(0x2000)
#define   NIC_PF_ECC0_SBE_INT_W1S		(0x2008)
#define   NIC_PF_ECC0_SBE_ENA_W1C		(0x2010)
#define   NIC_PF_ECC0_SBE_ENA_W1S		(0x2018)
#define   NIC_PF_ECC0_DBE_INT			(0x2100)
#define   NIC_PF_ECC0_DBE_INT_W1S		(0x2108)
#define   NIC_PF_ECC0_DBE_ENA_W1C		(0x2110)
#define   NIC_PF_ECC0_DBE_ENA_W1S		(0x2118)
#define   NIC_PF_ECC1_SBE_INT			(0x2200)
#define   NIC_PF_ECC1_SBE_INT_W1S		(0x2208)
#define   NIC_PF_ECC1_SBE_ENA_W1C		(0x2210)
#define   NIC_PF_ECC1_SBE_ENA_W1S		(0x2218)
#define   NIC_PF_ECC1_DBE_INT			(0x2300)
#define   NIC_PF_ECC1_DBE_INT_W1S		(0x2308)
#define   NIC_PF_ECC1_DBE_ENA_W1C		(0x2310)
#define   NIC_PF_ECC1_DBE_ENA_W1S		(0x2318)
#define   NIC_PF_ECC2_SBE_INT			(0x2400)
#define   NIC_PF_ECC2_SBE_INT_W1S		(0x2408)
#define   NIC_PF_ECC2_SBE_ENA_W1C		(0x2410)
#define   NIC_PF_ECC2_SBE_ENA_W1S		(0x2418)
#define   NIC_PF_ECC2_DBE_INT			(0x2500)
#define   NIC_PF_ECC2_DBE_INT_W1S		(0x2508)
#define   NIC_PF_ECC2_DBE_ENA_W1C		(0x2510)
#define   NIC_PF_ECC2_DBE_ENA_W1S		(0x2518)
#define   NIC_PF_ECC3_SBE_INT			(0x2600)
#define   NIC_PF_ECC3_SBE_INT_W1S		(0x2608)
#define   NIC_PF_ECC3_SBE_ENA_W1C		(0x2610)
#define   NIC_PF_ECC3_SBE_ENA_W1S		(0x2618)
#define   NIC_PF_ECC3_DBE_INT			(0x2700)
#define   NIC_PF_ECC3_DBE_INT_W1S		(0x2708)
#define   NIC_PF_ECC3_DBE_ENA_W1C		(0x2710)
#define   NIC_PF_ECC3_DBE_ENA_W1S		(0x2718)
#define   NIC_PF_INTFX_SEND_CFG			(0x4000)
#define   NIC_PF_MCAM_0_191_ENA			(0x100000)
#define   NIC_PF_MCAM_0_191_M_0_5_DATA		(0x110000)
#define   NIC_PF_MCAM_CTWW			(0x120000)
#define   NIC_PF_CPI_0_2047_CFG			(0x200000)
#define   NIC_PF_MPI_0_2047_CFG			(0x210000)
#define   NIC_PF_WSSI_0_4097_WQ			(0x220000)
#define   NIC_PF_WMAC_0_7_CFG			(0x240000)
#define   NIC_PF_WMAC_0_7_CFG2			(0x240100)
#define   NIC_PF_WMAC_0_7_SW_XOFF		(0x242000)
#define   NIC_PF_WMAC_0_7_CWEDIT		(0x244000)
#define   NIC_PF_CHAN_0_255_TX_CFG		(0x400000)
#define   NIC_PF_CHAN_0_255_WX_CFG		(0x420000)
#define   NIC_PF_CHAN_0_255_SW_XOFF		(0x440000)
#define   NIC_PF_CHAN_0_255_CWEDIT		(0x460000)
#define   NIC_PF_CHAN_0_255_WX_BP_CFG		(0x480000)
#define   NIC_PF_SW_SYNC_WX			(0x490000)
#define   NIC_PF_SW_SYNC_WX_DONE		(0x490008)
#define   NIC_PF_TW2_0_63_CFG			(0x500000)
#define   NIC_PF_TW2_0_63_PWI			(0x520000)
#define   NIC_PF_TW2_WMAC			(0x540000)
#define   NIC_PF_TW2_0_63_SH_STATUS		(0x580000)
#define   NIC_PF_TW3A_0_63_CFG			(0x5F0000)
#define   NIC_PF_TW3_0_255_CFG			(0x600000)
#define   NIC_PF_TW3_0_255_CHAN			(0x620000)
#define   NIC_PF_TW3_0_255_PIW			(0x640000)
#define   NIC_PF_TW3_0_255_SW_XOFF		(0x660000)
#define   NIC_PF_TW3_0_255_CNM_WATE		(0x680000)
#define   NIC_PF_TW3_0_255_SH_STATUS		(0x6A0000)
#define   NIC_PF_TW4A_0_255_CFG			(0x6F0000)
#define   NIC_PF_TW4_0_1023_CFG			(0x800000)
#define   NIC_PF_TW4_0_1023_SW_XOFF		(0x820000)
#define   NIC_PF_TW4_0_1023_SH_STATUS		(0x840000)
#define   NIC_PF_TW4A_0_1023_CNM_WATE		(0x880000)
#define   NIC_PF_TW4A_0_1023_CNM_STATUS		(0x8A0000)
#define   NIC_PF_VF_0_127_MAIWBOX_0_1		(0x20002030)
#define   NIC_PF_VNIC_0_127_TX_STAT_0_4		(0x20004000)
#define   NIC_PF_VNIC_0_127_WX_STAT_0_13	(0x20004100)
#define   NIC_PF_QSET_0_127_WOCK_0_15		(0x20006000)
#define   NIC_PF_QSET_0_127_CFG			(0x20010000)
#define   NIC_PF_QSET_0_127_WQ_0_7_CFG		(0x20010400)
#define   NIC_PF_QSET_0_127_WQ_0_7_DWOP_CFG	(0x20010420)
#define   NIC_PF_QSET_0_127_WQ_0_7_BP_CFG	(0x20010500)
#define   NIC_PF_QSET_0_127_WQ_0_7_STAT_0_1	(0x20010600)
#define   NIC_PF_QSET_0_127_SQ_0_7_CFG		(0x20010C00)
#define   NIC_PF_QSET_0_127_SQ_0_7_CFG2		(0x20010C08)
#define   NIC_PF_QSET_0_127_SQ_0_7_STAT_0_1	(0x20010D00)

#define   NIC_PF_MSIX_VEC_0_18_ADDW		(0x000000)
#define   NIC_PF_MSIX_VEC_0_CTW			(0x000008)
#define   NIC_PF_MSIX_PBA_0			(0x0F0000)

/* Viwtuaw function wegistew offsets */
#define   NIC_VNIC_CFG				(0x000020)
#define   NIC_VF_PF_MAIWBOX_0_1			(0x000130)
#define   NIC_VF_INT				(0x000200)
#define   NIC_VF_INT_W1S			(0x000220)
#define   NIC_VF_ENA_W1C			(0x000240)
#define   NIC_VF_ENA_W1S			(0x000260)

#define   NIC_VNIC_WSS_CFG			(0x0020E0)
#define   NIC_VNIC_WSS_KEY_0_4			(0x002200)
#define   NIC_VNIC_TX_STAT_0_4			(0x004000)
#define   NIC_VNIC_WX_STAT_0_13			(0x004100)
#define   NIC_QSET_WQ_GEN_CFG			(0x010010)

#define   NIC_QSET_CQ_0_7_CFG			(0x010400)
#define   NIC_QSET_CQ_0_7_CFG2			(0x010408)
#define   NIC_QSET_CQ_0_7_THWESH		(0x010410)
#define   NIC_QSET_CQ_0_7_BASE			(0x010420)
#define   NIC_QSET_CQ_0_7_HEAD			(0x010428)
#define   NIC_QSET_CQ_0_7_TAIW			(0x010430)
#define   NIC_QSET_CQ_0_7_DOOW			(0x010438)
#define   NIC_QSET_CQ_0_7_STATUS		(0x010440)
#define   NIC_QSET_CQ_0_7_STATUS2		(0x010448)
#define   NIC_QSET_CQ_0_7_DEBUG			(0x010450)

#define   NIC_QSET_WQ_0_7_CFG			(0x010600)
#define   NIC_QSET_WQ_0_7_STAT_0_1		(0x010700)

#define   NIC_QSET_SQ_0_7_CFG			(0x010800)
#define   NIC_QSET_SQ_0_7_THWESH		(0x010810)
#define   NIC_QSET_SQ_0_7_BASE			(0x010820)
#define   NIC_QSET_SQ_0_7_HEAD			(0x010828)
#define   NIC_QSET_SQ_0_7_TAIW			(0x010830)
#define   NIC_QSET_SQ_0_7_DOOW			(0x010838)
#define   NIC_QSET_SQ_0_7_STATUS		(0x010840)
#define   NIC_QSET_SQ_0_7_DEBUG			(0x010848)
#define   NIC_QSET_SQ_0_7_STAT_0_1		(0x010900)

#define   NIC_QSET_WBDW_0_1_CFG			(0x010C00)
#define   NIC_QSET_WBDW_0_1_THWESH		(0x010C10)
#define   NIC_QSET_WBDW_0_1_BASE		(0x010C20)
#define   NIC_QSET_WBDW_0_1_HEAD		(0x010C28)
#define   NIC_QSET_WBDW_0_1_TAIW		(0x010C30)
#define   NIC_QSET_WBDW_0_1_DOOW		(0x010C38)
#define   NIC_QSET_WBDW_0_1_STATUS0		(0x010C40)
#define   NIC_QSET_WBDW_0_1_STATUS1		(0x010C48)
#define   NIC_QSET_WBDW_0_1_PWEFETCH_STATUS	(0x010C50)

#define   NIC_VF_MSIX_VECTOW_0_19_ADDW		(0x000000)
#define   NIC_VF_MSIX_VECTOW_0_19_CTW		(0x000008)
#define   NIC_VF_MSIX_PBA			(0x0F0000)

/* Offsets within wegistews */
#define   NIC_MSIX_VEC_SHIFT			4
#define   NIC_Q_NUM_SHIFT			18
#define   NIC_QS_ID_SHIFT			21
#define   NIC_VF_NUM_SHIFT			21

/* Powt kind configuwation wegistew */
stwuct pkind_cfg {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64 wesewved_42_63:22;
	u64 hdw_sw:5;	/* Headew skip wength */
	u64 wx_hdw:3;	/* TNS Weceive headew pwesent */
	u64 weneww_en:1;/* W2 wength ewwow check enabwe */
	u64 wesewved_32_32:1;
	u64 maxwen:16;	/* Max fwame size */
	u64 minwen:16;	/* Min fwame size */
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u64 minwen:16;
	u64 maxwen:16;
	u64 wesewved_32_32:1;
	u64 weneww_en:1;
	u64 wx_hdw:3;
	u64 hdw_sw:5;
	u64 wesewved_42_63:22;
#endif
};

#endif /* NIC_WEG_H */
