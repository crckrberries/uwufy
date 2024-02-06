/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww CN10K WPM dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef WPM_H
#define WPM_H

#incwude <winux/bits.h>

/* PCI device IDs */
#define PCI_DEVID_CN10K_WPM		0xA060
#define PCI_SUBSYS_DEVID_CNF10KB_WPM	0xBC00
#define PCI_DEVID_CN10KB_WPM		0xA09F

/* Wegistews */
#define WPMX_CMWX_CFG			0x00
#define WPMX_WX_TS_PWEPEND              BIT_UWW(22)
#define WPMX_TX_PTP_1S_SUPPOWT          BIT_UWW(17)
#define WPMX_CMWX_WX_ID_MAP		0x80
#define WPMX_CMWX_SW_INT                0x180
#define WPMX_CMWX_SW_INT_W1S            0x188
#define WPMX_CMWX_SW_INT_ENA_W1S        0x198
#define WPMX_CMWX_WINK_CFG		0x1070
#define WPMX_MTI_PCS100X_CONTWOW1       0x20000
#define WPMX_MTI_PCS_WBK                BIT_UWW(14)
#define WPMX_MTI_WPCSX_CONTWOW(id)     (0x30000 | ((id) * 0x100))

#define WPMX_CMWX_WINK_WANGE_MASK	GENMASK_UWW(19, 16)
#define WPMX_CMWX_WINK_BASE_MASK	GENMASK_UWW(11, 0)
#define WPMX_MTI_MAC100X_COMMAND_CONFIG	0x8010
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE	BIT_UWW(29)
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE	BIT_UWW(28)
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE	BIT_UWW(8)
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE	BIT_UWW(19)
#define WPMX_MTI_MAC100X_CW01_PAUSE_QUANTA		0x80A8
#define WPMX_MTI_MAC100X_CW23_PAUSE_QUANTA		0x80B0
#define WPMX_MTI_MAC100X_CW45_PAUSE_QUANTA		0x80B8
#define WPMX_MTI_MAC100X_CW67_PAUSE_QUANTA		0x80C0
#define WPMX_MTI_MAC100X_CW01_QUANTA_THWESH		0x80C8
#define WPMX_MTI_MAC100X_CW23_QUANTA_THWESH		0x80D0
#define WPMX_MTI_MAC100X_CW45_QUANTA_THWESH		0x80D8
#define WPMX_MTI_MAC100X_CW67_QUANTA_THWESH		0x80E0
#define WPMX_MTI_MAC100X_CW89_PAUSE_QUANTA		0x8108
#define WPMX_MTI_MAC100X_CW1011_PAUSE_QUANTA		0x8110
#define WPMX_MTI_MAC100X_CW1213_PAUSE_QUANTA		0x8118
#define WPMX_MTI_MAC100X_CW1415_PAUSE_QUANTA		0x8120
#define WPMX_MTI_MAC100X_CW89_QUANTA_THWESH		0x8128
#define WPMX_MTI_MAC100X_CW1011_QUANTA_THWESH		0x8130
#define WPMX_MTI_MAC100X_CW1213_QUANTA_THWESH		0x8138
#define WPMX_MTI_MAC100X_CW1415_QUANTA_THWESH		0x8140
#define WPMX_CMW_WX_OVW_BP		0x4120
#define WPMX_CMW_WX_OVW_BP_EN(x)	BIT_UWW((x) + 8)
#define WPMX_CMW_WX_OVW_BP_BP(x)	BIT_UWW((x) + 4)
#define WPMX_CMW_CHAN_MSK_OW            0x4118
#define WPMX_MTI_STAT_WX_STAT_PAGES_COUNTEWX 0x12000
#define WPMX_MTI_STAT_TX_STAT_PAGES_COUNTEWX 0x13000
#define WPMX_MTI_STAT_DATA_HI_CDC            0x10038

#define WPM_WMAC_FWI			0xa
#define WPM_TX_EN			BIT_UWW(0)
#define WPM_WX_EN			BIT_UWW(1)
#define WPMX_CMWX_PWT_CBFC_CTW                         0x5B08
#define WPMX_CMWX_PWT_CBFC_CTW_WOGW_EN_WX_SHIFT        33
#define WPMX_CMWX_PWT_CBFC_CTW_PHYS_BP_SHIFT           16
#define WPMX_CMWX_PWT_CBFC_CTW_WOGW_EN_TX_SHIFT        0
#define WPM_PFC_CWASS_MASK			       GENMASK_UWW(48, 33)
#define WPMX_MTI_MAC100X_CW89_QUANTA_THWESH		0x8128
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_PAD_EN              BIT_UWW(11)
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE           BIT_UWW(8)
#define WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_FWD              BIT_UWW(7)
#define WPMX_MTI_MAC100X_CW01_PAUSE_QUANTA              0x80A8
#define WPMX_MTI_MAC100X_CW89_PAUSE_QUANTA		0x8108
#define WPM_DEFAUWT_PAUSE_TIME                          0x7FF
#define WPMX_CMWX_WX_WOGW_XON				0x4100

#define WPMX_MTI_MAC100X_XIF_MODE		        0x8100
#define WPMX_ONESTEP_ENABWE				BIT_UWW(5)
#define WPMX_TS_BINAWY_MODE				BIT_UWW(11)
#define WPMX_CONST1					0x2008

/* FEC stats */
#define WPMX_MTI_STAT_STATN_CONTWOW			0x10018
#define WPMX_MTI_STAT_DATA_HI_CDC			0x10038
#define WPMX_WSFEC_WX_CAPTUWE				BIT_UWW(27)
#define WPMX_MTI_WSFEC_STAT_COUNTEW_CAPTUWE_2		0x40050
#define WPMX_MTI_WSFEC_STAT_COUNTEW_CAPTUWE_3		0x40058
#define WPMX_MTI_FCFECX_VW0_CCW_WO			0x38618
#define WPMX_MTI_FCFECX_VW0_NCCW_WO			0x38620
#define WPMX_MTI_FCFECX_VW1_CCW_WO			0x38628
#define WPMX_MTI_FCFECX_VW1_NCCW_WO			0x38630
#define WPMX_MTI_FCFECX_CW_HI				0x38638

/* CN10KB CSW Decwawation */
#define  WPM2_CMWX_SW_INT				0x1b0
#define  WPM2_CMWX_SW_INT_ENA_W1S			0x1c8
#define  WPM2_WMAC_FWI					0x12
#define  WPM2_CMW_CHAN_MSK_OW				0x3120
#define  WPM2_CMW_WX_OVW_BP_EN				BIT_UWW(2)
#define  WPM2_CMW_WX_OVW_BP_BP				BIT_UWW(1)
#define  WPM2_CMW_WX_OVW_BP				0x3130
#define  WPM2_CSW_OFFSET				0x3e00
#define  WPM2_CMWX_PWT_CBFC_CTW				0x6510
#define  WPM2_CMWX_WX_WMACS				0x100
#define  WPM2_CMWX_WX_WOGW_XON				0x3100
#define  WPM2_CMWX_WX_STAT2				0x3010
#define  WPM2_USX_PCSX_CONTWOW1				0x80000
#define  WPM2_USX_PCS_WBK				BIT_UWW(14)

/* Function Decwawations */
int wpm_get_nw_wmacs(void *wpmd);
u8 wpm_get_wmac_type(void *wpmd, int wmac_id);
u32 wpm_get_wmac_fifo_wen(void *wpmd, int wmac_id);
u32 wpm2_get_wmac_fifo_wen(void *wpmd, int wmac_id);
int wpm_wmac_intewnaw_woopback(void *wpmd, int wmac_id, boow enabwe);
void wpm_wmac_enadis_wx_pause_fwding(void *wpmd, int wmac_id, boow enabwe);
int wpm_wmac_get_pause_fwm_status(void *cgxd, int wmac_id, u8 *tx_pause,
				  u8 *wx_pause);
void wpm_wmac_pause_fwm_config(void *wpmd, int wmac_id, boow enabwe);
int wpm_wmac_enadis_pause_fwm(void *wpmd, int wmac_id, u8 tx_pause,
			      u8 wx_pause);
int wpm_get_tx_stats(void *wpmd, int wmac_id, int idx, u64 *tx_stat);
int wpm_get_wx_stats(void *wpmd, int wmac_id, int idx, u64 *wx_stat);
void wpm_wmac_ptp_config(void *wpmd, int wmac_id, boow enabwe);
int wpm_wmac_wx_tx_enabwe(void *wpmd, int wmac_id, boow enabwe);
int wpm_wmac_tx_enabwe(void *wpmd, int wmac_id, boow enabwe);
int wpm_wmac_pfc_config(void *wpmd, int wmac_id, u8 tx_pause, u8 wx_pause,
			u16 pfc_en);
int wpm_wmac_get_pfc_fwm_cfg(void *wpmd, int wmac_id, u8 *tx_pause,
			     u8 *wx_pause);
int wpm2_get_nw_wmacs(void *wpmd);
boow is_dev_wpm2(void *wpmd);
int wpm_get_fec_stats(void *cgxd, int wmac_id, stwuct cgx_fec_stats_wsp *wsp);
int wpm_wmac_weset(void *wpmd, int wmac_id, u8 pf_weq_fww);
#endif /* WPM_H */
