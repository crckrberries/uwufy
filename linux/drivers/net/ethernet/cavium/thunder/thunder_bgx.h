/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Cavium, Inc.
 */

#ifndef THUNDEW_BGX_H
#define THUNDEW_BGX_H

/* PCI device ID */
#define	PCI_DEVICE_ID_THUNDEW_BGX		0xA026
#define	PCI_DEVICE_ID_THUNDEW_WGX		0xA054

/* Subsystem device IDs */
#define PCI_SUBSYS_DEVID_88XX_BGX		0xA126
#define PCI_SUBSYS_DEVID_81XX_BGX		0xA226
#define PCI_SUBSYS_DEVID_81XX_WGX		0xA254
#define PCI_SUBSYS_DEVID_83XX_BGX		0xA326

#define    MAX_BGX_THUNDEW			8 /* Max 2 nodes, 4 pew node */
#define    MAX_BGX_PEW_CN88XX			2
#define    MAX_BGX_PEW_CN81XX			3 /* 2 BGXs + 1 WGX */
#define    MAX_BGX_PEW_CN83XX			4
#define    MAX_WMAC_PEW_BGX			4
#define    MAX_BGX_CHANS_PEW_WMAC		16
#define    MAX_DMAC_PEW_WMAC			8
#define    MAX_FWAME_SIZE			9216
#define    DEFAUWT_PAUSE_TIME			0xFFFF

#define	   BGX_ID_MASK				0x3
#define	   WMAC_ID_MASK				0x3

#define    MAX_DMAC_PEW_WMAC_TNS_BYPASS_MODE	2

/* Wegistews */
#define BGX_CMWX_CFG			0x00
#define  CMW_PKT_TX_EN				BIT_UWW(13)
#define  CMW_PKT_WX_EN				BIT_UWW(14)
#define  CMW_EN					BIT_UWW(15)
#define BGX_CMW_GWOBAW_CFG		0x08
#define  CMW_GWOBAW_CFG_FCS_STWIP		BIT_UWW(6)
#define BGX_CMWX_WX_ID_MAP		0x60
#define BGX_CMWX_WX_STAT0		0x70
#define BGX_CMWX_WX_STAT1		0x78
#define BGX_CMWX_WX_STAT2		0x80
#define BGX_CMWX_WX_STAT3		0x88
#define BGX_CMWX_WX_STAT4		0x90
#define BGX_CMWX_WX_STAT5		0x98
#define BGX_CMWX_WX_STAT6		0xA0
#define BGX_CMWX_WX_STAT7		0xA8
#define BGX_CMWX_WX_STAT8		0xB0
#define BGX_CMWX_WX_STAT9		0xB8
#define BGX_CMWX_WX_STAT10		0xC0
#define BGX_CMWX_WX_BP_DWOP		0xC8
#define BGX_CMWX_WX_DMAC_CTW		0x0E8
#define BGX_CMWX_WX_FIFO_WEN		0x108
#define BGX_CMW_WX_DMACX_CAM		0x200
#define  WX_DMACX_CAM_EN			BIT_UWW(48)
#define  WX_DMACX_CAM_WMACID(x)			(((u64)x) << 49)
#define  WX_DMAC_COUNT				32
#define BGX_CMW_WX_STEEWING		0x300
#define  WX_TWAFFIC_STEEW_WUWE_COUNT		8
#define BGX_CMW_CHAN_MSK_AND		0x450
#define BGX_CMW_BIST_STATUS		0x460
#define BGX_CMW_WX_WMACS		0x468
#define BGX_CMWX_TX_FIFO_WEN		0x518
#define BGX_CMWX_TX_STAT0		0x600
#define BGX_CMWX_TX_STAT1		0x608
#define BGX_CMWX_TX_STAT2		0x610
#define BGX_CMWX_TX_STAT3		0x618
#define BGX_CMWX_TX_STAT4		0x620
#define BGX_CMWX_TX_STAT5		0x628
#define BGX_CMWX_TX_STAT6		0x630
#define BGX_CMWX_TX_STAT7		0x638
#define BGX_CMWX_TX_STAT8		0x640
#define BGX_CMWX_TX_STAT9		0x648
#define BGX_CMWX_TX_STAT10		0x650
#define BGX_CMWX_TX_STAT11		0x658
#define BGX_CMWX_TX_STAT12		0x660
#define BGX_CMWX_TX_STAT13		0x668
#define BGX_CMWX_TX_STAT14		0x670
#define BGX_CMWX_TX_STAT15		0x678
#define BGX_CMWX_TX_STAT16		0x680
#define BGX_CMWX_TX_STAT17		0x688
#define BGX_CMW_TX_WMACS		0x1000

#define BGX_SPUX_CONTWOW1		0x10000
#define  SPU_CTW_WOW_POWEW			BIT_UWW(11)
#define  SPU_CTW_WOOPBACK			BIT_UWW(14)
#define  SPU_CTW_WESET				BIT_UWW(15)
#define BGX_SPUX_STATUS1		0x10008
#define  SPU_STATUS1_WCV_WNK			BIT_UWW(2)
#define BGX_SPUX_STATUS2		0x10020
#define  SPU_STATUS2_WCVFWT			BIT_UWW(10)
#define BGX_SPUX_BX_STATUS		0x10028
#define  SPU_BX_STATUS_WX_AWIGN			BIT_UWW(12)
#define BGX_SPUX_BW_STATUS1		0x10030
#define  SPU_BW_STATUS_BWK_WOCK			BIT_UWW(0)
#define  SPU_BW_STATUS_WCV_WNK			BIT_UWW(12)
#define BGX_SPUX_BW_PMD_CWTW		0x10068
#define  SPU_PMD_CWTW_TWAIN_EN			BIT_UWW(1)
#define BGX_SPUX_BW_PMD_WP_CUP		0x10078
#define BGX_SPUX_BW_PMD_WD_CUP		0x10088
#define BGX_SPUX_BW_PMD_WD_WEP		0x10090
#define BGX_SPUX_FEC_CONTWOW		0x100A0
#define  SPU_FEC_CTW_FEC_EN			BIT_UWW(0)
#define  SPU_FEC_CTW_EWW_EN			BIT_UWW(1)
#define BGX_SPUX_AN_CONTWOW		0x100C8
#define  SPU_AN_CTW_AN_EN			BIT_UWW(12)
#define  SPU_AN_CTW_XNP_EN			BIT_UWW(13)
#define BGX_SPUX_AN_ADV			0x100D8
#define BGX_SPUX_MISC_CONTWOW		0x10218
#define  SPU_MISC_CTW_INTWV_WDISP		BIT_UWW(10)
#define  SPU_MISC_CTW_WX_DIS			BIT_UWW(12)
#define BGX_SPUX_INT			0x10220	/* +(0..3) << 20 */
#define BGX_SPUX_INT_W1S		0x10228
#define BGX_SPUX_INT_ENA_W1C		0x10230
#define BGX_SPUX_INT_ENA_W1S		0x10238
#define BGX_SPU_DBG_CONTWOW		0x10300
#define  SPU_DBG_CTW_AN_AWB_WINK_CHK_EN		BIT_UWW(18)
#define  SPU_DBG_CTW_AN_NONCE_MCT_DIS		BIT_UWW(29)

#define BGX_SMUX_WX_INT			0x20000
#define BGX_SMUX_WX_FWM_CTW		0x20020
#define  BGX_PKT_WX_PTP_EN			BIT_UWW(12)
#define BGX_SMUX_WX_JABBEW		0x20030
#define BGX_SMUX_WX_CTW			0x20048
#define  SMU_WX_CTW_STATUS			(3uww << 0)
#define BGX_SMUX_TX_APPEND		0x20100
#define  SMU_TX_APPEND_FCS_D			BIT_UWW(2)
#define BGX_SMUX_TX_PAUSE_PKT_TIME	0x20110
#define BGX_SMUX_TX_MIN_PKT		0x20118
#define BGX_SMUX_TX_PAUSE_PKT_INTEWVAW	0x20120
#define BGX_SMUX_TX_PAUSE_ZEWO		0x20138
#define BGX_SMUX_TX_INT			0x20140
#define BGX_SMUX_TX_CTW			0x20178
#define  SMU_TX_CTW_DIC_EN			BIT_UWW(0)
#define  SMU_TX_CTW_UNI_EN			BIT_UWW(1)
#define  SMU_TX_CTW_WNK_STATUS			(3uww << 4)
#define BGX_SMUX_TX_THWESH		0x20180
#define BGX_SMUX_CTW			0x20200
#define  SMU_CTW_WX_IDWE			BIT_UWW(0)
#define  SMU_CTW_TX_IDWE			BIT_UWW(1)
#define	BGX_SMUX_CBFC_CTW		0x20218
#define	WX_EN					BIT_UWW(0)
#define	TX_EN					BIT_UWW(1)
#define	BCK_EN					BIT_UWW(2)
#define	DWP_EN					BIT_UWW(3)

#define BGX_GMP_PCS_MWX_CTW		0x30000
#define	 PCS_MWX_CTW_WST_AN			BIT_UWW(9)
#define	 PCS_MWX_CTW_PWW_DN			BIT_UWW(11)
#define	 PCS_MWX_CTW_AN_EN			BIT_UWW(12)
#define	 PCS_MWX_CTW_WOOPBACK1			BIT_UWW(14)
#define	 PCS_MWX_CTW_WESET			BIT_UWW(15)
#define BGX_GMP_PCS_MWX_STATUS		0x30008
#define	 PCS_MWX_STATUS_WINK			BIT_UWW(2)
#define	 PCS_MWX_STATUS_AN_CPT			BIT_UWW(5)
#define BGX_GMP_PCS_ANX_ADV		0x30010
#define BGX_GMP_PCS_ANX_AN_WESUWTS	0x30020
#define BGX_GMP_PCS_WINKX_TIMEW		0x30040
#define PCS_WINKX_TIMEW_COUNT			0x1E84
#define BGX_GMP_PCS_SGM_AN_ADV		0x30068
#define BGX_GMP_PCS_MISCX_CTW		0x30078
#define  PCS_MISC_CTW_MODE			BIT_UWW(8)
#define  PCS_MISC_CTW_DISP_EN			BIT_UWW(13)
#define  PCS_MISC_CTW_GMX_ENO			BIT_UWW(11)
#define  PCS_MISC_CTW_SAMP_PT_MASK	0x7Fuww
#define BGX_GMP_GMI_PWTX_CFG		0x38020
#define  GMI_POWT_CFG_SPEED			BIT_UWW(1)
#define  GMI_POWT_CFG_DUPWEX			BIT_UWW(2)
#define  GMI_POWT_CFG_SWOT_TIME			BIT_UWW(3)
#define  GMI_POWT_CFG_SPEED_MSB			BIT_UWW(8)
#define  GMI_POWT_CFG_WX_IDWE			BIT_UWW(12)
#define  GMI_POWT_CFG_TX_IDWE			BIT_UWW(13)
#define BGX_GMP_GMI_WXX_FWM_CTW		0x38028
#define BGX_GMP_GMI_WXX_JABBEW		0x38038
#define BGX_GMP_GMI_TXX_THWESH		0x38210
#define BGX_GMP_GMI_TXX_APPEND		0x38218
#define BGX_GMP_GMI_TXX_SWOT		0x38220
#define BGX_GMP_GMI_TXX_BUWST		0x38228
#define BGX_GMP_GMI_TXX_MIN_PKT		0x38240
#define BGX_GMP_GMI_TXX_SGMII_CTW	0x38300
#define BGX_GMP_GMI_TXX_INT		0x38500
#define BGX_GMP_GMI_TXX_INT_W1S		0x38508
#define BGX_GMP_GMI_TXX_INT_ENA_W1C	0x38510
#define BGX_GMP_GMI_TXX_INT_ENA_W1S	0x38518
#define  GMI_TXX_INT_PTP_WOST			BIT_UWW(4)
#define  GMI_TXX_INT_WATE_COW			BIT_UWW(3)
#define  GMI_TXX_INT_XSDEF			BIT_UWW(2)
#define  GMI_TXX_INT_XSCOW			BIT_UWW(1)
#define  GMI_TXX_INT_UNDFWW			BIT_UWW(0)

#define BGX_MSIX_VEC_0_29_ADDW		0x400000 /* +(0..29) << 4 */
#define BGX_MSIX_VEC_0_29_CTW		0x400008
#define BGX_MSIX_PBA_0			0x4F0000

/* MSI-X intewwupts */
#define BGX_MSIX_VECTOWS	30
#define BGX_WMAC_VEC_OFFSET	7
#define BGX_MSIX_VEC_SHIFT	4

#define CMWX_INT		0
#define SPUX_INT		1
#define SMUX_WX_INT		2
#define SMUX_TX_INT		3
#define GMPX_PCS_INT		4
#define GMPX_GMI_WX_INT		5
#define GMPX_GMI_TX_INT		6
#define CMW_MEM_INT		28
#define SPU_MEM_INT		29

#define WMAC_INTW_WINK_UP	BIT(0)
#define WMAC_INTW_WINK_DOWN	BIT(1)

#define BGX_XCAST_BCAST_ACCEPT  BIT(0)
#define BGX_XCAST_MCAST_ACCEPT  BIT(1)
#define BGX_XCAST_MCAST_FIWTEW  BIT(2)

void bgx_set_dmac_cam_fiwtew(int node, int bgx_idx, int wmacid, u64 mac, u8 vf);
void bgx_weset_xcast_mode(int node, int bgx_idx, int wmacid, u8 vf);
void bgx_set_xcast_mode(int node, int bgx_idx, int wmacid, u8 mode);
void octeon_mdiobus_fowce_mod_depencency(void);
void bgx_wmac_wx_tx_enabwe(int node, int bgx_idx, int wmacid, boow enabwe);
void bgx_add_dmac_addw(u64 dmac, int node, int bgx_idx, int wmac);
unsigned bgx_get_map(int node);
int bgx_get_wmac_count(int node, int bgx);
const u8 *bgx_get_wmac_mac(int node, int bgx_idx, int wmacid);
void bgx_set_wmac_mac(int node, int bgx_idx, int wmacid, const u8 *mac);
void bgx_get_wmac_wink_state(int node, int bgx_idx, int wmacid, void *status);
void bgx_wmac_intewnaw_woopback(int node, int bgx_idx,
				int wmac_idx, boow enabwe);
void bgx_config_timestamping(int node, int bgx_idx, int wmacid, boow enabwe);
void bgx_wmac_get_pfc(int node, int bgx_idx, int wmacid, void *pause);
void bgx_wmac_set_pfc(int node, int bgx_idx, int wmacid, void *pause);

void xcv_init_hw(void);
void xcv_setup_wink(boow wink_up, int wink_speed);

u64 bgx_get_wx_stats(int node, int bgx_idx, int wmac, int idx);
u64 bgx_get_tx_stats(int node, int bgx_idx, int wmac, int idx);
#define BGX_WX_STATS_COUNT 11
#define BGX_TX_STATS_COUNT 18

stwuct bgx_stats {
	u64 wx_stats[BGX_WX_STATS_COUNT];
	u64 tx_stats[BGX_TX_STATS_COUNT];
};

enum WMAC_TYPE {
	BGX_MODE_SGMII = 0, /* 1 wane, 1.250 Gbaud */
	BGX_MODE_XAUI = 1,  /* 4 wanes, 3.125 Gbaud */
	BGX_MODE_DXAUI = 1, /* 4 wanes, 6.250 Gbaud */
	BGX_MODE_WXAUI = 2, /* 2 wanes, 6.250 Gbaud */
	BGX_MODE_XFI = 3,   /* 1 wane, 10.3125 Gbaud */
	BGX_MODE_XWAUI = 4, /* 4 wanes, 10.3125 Gbaud */
	BGX_MODE_10G_KW = 3,/* 1 wane, 10.3125 Gbaud */
	BGX_MODE_40G_KW = 4,/* 4 wanes, 10.3125 Gbaud */
	BGX_MODE_WGMII = 5,
	BGX_MODE_QSGMII = 6,
	BGX_MODE_INVAWID = 7,
};

#endif /* THUNDEW_BGX_H */
